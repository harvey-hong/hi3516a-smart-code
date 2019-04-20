#ifndef T_SELECTOR_H

#define T_SELECTOR_H

#include "./TThread.h"
#include "./TResourceManager.h"
#include "../InternalCommon.h"
#include "../Property.h"
#include "ws_utility_api.h"
using namespace ws_utility;

#include "../Utility.h"

namespace   ApplicationLayer
{
template<class T_DISPOSE, int iResource>
class TSelector
{
public:
    TSelector()
    {
        Initialize();
    }
    ~TSelector()
    {
        Destroy();
    }
public:

    int Start()
    {
        m_state             = true;
        m_dwTickCount   = 0;

        if (0 != m_cMutex.create())
        {
            m_state = false;
            return 1;
        }

        m_cMutex.lock();

        if (0 != m_cSignal.create())
        {
            m_state = false;
            m_cMutex.unlock();
            m_cMutex.destroy();
            return 1;
        }

        m_cResource.Initialize();

        //启动任务线程
        if (0 != m_hThread.Start(this))
        {
            m_state     = false;
            m_cSignal.destroy();
            m_cMutex.unlock();
            m_cMutex.destroy();
            return 1;
        }

        m_cMutex.unlock();
        return 0;
    }

    int Stop()
    {
        m_state = false;
        m_cSignal.signal();
        int iResult = m_hThread.Stop();
        m_cMutex.lock();
        m_cSignal.destroy();
        m_cMutex.unlock();
        m_cMutex.destroy();
        return iResult;
    }

    int Insert(NET_SOCKET h, T_DISPOSE *pDispose)
    {
        if (!m_state)
        {
            return 1;
        }

        CGuard  guard(&m_cMutex);
        int         iIndex = 0;

        if (0 != m_cResource.Create(iIndex, h))
        {
            return 1;
        }

        m_dwTickCount       += 1;
        m_dwTick[iIndex]    = m_dwTickCount;
        m_pDispose[iIndex]  = pDispose;
        m_bListen[iIndex]   = 0;

        if (m_state)
        {
            m_cSignal.signal();
        }

        return 0;
    }

    int InsertListen(NET_SOCKET h, T_DISPOSE *pDispose)
    {
        if (!m_state)
        {
            return 1;
        }

        CGuard  guard(&m_cMutex);
        int         iIndex = 0;

        if (0 != m_cResource.Create(iIndex, h))
        {
            return 1;
        }

        m_dwTickCount       += 1;
        m_dwTick[iIndex]    = m_dwTickCount;
        m_pDispose[iIndex]  = pDispose;
        m_bListen[iIndex]   = 1;

        if (m_state)
        {
            m_cSignal.signal();
        }

        return 0;
    }

    int Remove(NET_SOCKET h, T_DISPOSE *pDispose)
    {
        if (!m_state)
        {
            return 1;
        }

        CGuard  guard(&m_cMutex);
        int     count ;

        for (count = 0; count < iResource; count++)
        {
            if (RET_CHECK_FAIL(m_cResource.CheckResourceIdle(count)) && h == m_cResource[count])
            {
                if (pDispose == m_pDispose[count])
                {
                    m_pDispose[count]   = NULL;
                    // 标记资源已经被删除，有可能出现新添加的句柄和之前是一样的，但是编号可以确保肯定不同
                    m_dwTick[count]     = 0;
                    m_bListen[count]    = 0;

                    if (0 != m_cResource.Destroy(count))
                    {
                        return 1;
                    }

                    return 0;
                }
            }
        }

        return 1;
    }

    int GetResourceNumber(int &iNumber)
    {
        iNumber = 0;

        if (0 != m_cResource.ResourceNumber(iNumber))
        {
            return 1;
        }

        return 0;
    }

    int RunTask()
    {
        int     iNumber = 0;
        int     iSocket = 0;

        if ((0 != m_cResource.ResourceNumber(iNumber)) || 0 == iNumber)
        {
            m_cSignal.wait();

            if (!m_state)
            {
                return 1;
            }
        }

        fd_set  rset;
        fd_set  wset;
        fd_set  eset;
        FD_ZERO(&rset);
        FD_ZERO(&wset);
        FD_ZERO(&eset);
        int     iCount;

        for (iCount = 0; iCount < iResource; iCount++)
        {
            if (RET_CHECK_FAIL(m_cResource.CheckResourceIdle(iCount)) && NULL != m_pDispose[iCount])
            {
                if (iSocket < m_cResource[iCount])
                {
                    iSocket = m_cResource[iCount];
                }

                FD_SET(m_cResource[iCount], &rset);
                FD_SET(m_cResource[iCount], &wset);
                FD_SET(m_cResource[iCount], &eset);
            }
        }

        const DWORD timeout = DEFAULT_SELECT_TIMEOUT;
        timeval     tv;
        tv.tv_sec   = timeout / 1000;
        tv.tv_usec  = (timeout - tv.tv_sec * 1000) * 1000;
        iSocket += 1;
        int iret = ::select(iSocket, &rset, NULL, &eset, &tv);  //&wset, &eset

        if (CHECK_VALUE_VALID(iret) && 0 != iret)               //no error timeout
        {
            for (iCount = 0; iCount < iResource; iCount++)
            {
                if (RET_CHECK_FAIL(m_cResource.CheckResourceIdle(iCount)))
                {
                    T_DISPOSE   *pDispose = m_pDispose[iCount];

                    if (CHECK_POINT_NO_NULL(pDispose) && CHECK_POINT_NO_NULL(m_pDispose[iCount]))
                    {
                        if (FD_ISSET(m_cResource[iCount], &rset) || FD_ISSET(m_cResource[iCount], &eset))
                        {
                            NET_SOCKET h = m_cResource[iCount];
                            DWORD dwTick = m_dwTick[iCount];

                            if (0 == m_bListen[iCount])
                            {
                                if (0 != pDispose->handle_recv(h))
                                {
                                    CGuard  guard(&m_cMutex);

                                    if (dwTick == m_dwTick[iCount])
                                    {
                                        m_dwTick[iCount]    = 0;
                                        m_bListen[iCount]   = 0;
                                        m_pDispose[iCount]  = NULL;
                                        m_cResource.Destroy(iCount);
                                    }
                                }
                            }
                            else if (1 == m_bListen[iCount])
                            {
                                if (0 != pDispose->handle_accept(h))
                                {
                                    CGuard  guard(&m_cMutex);

                                    if (dwTick == m_dwTick[iCount])
                                    {
                                        m_dwTick[iCount]    = 0;
                                        m_bListen[iCount]   = 0;
                                        m_pDispose[iCount]  = NULL;
                                        m_cResource.Destroy(iCount);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return 0;
    }

protected:
    TSelector(const TSelector &rObj)
    {
        (*this) = rObj;
    }
    TSelector &operator=(const TSelector &rObj)
    {
        return (*this);
    }

protected:
    int Initialize()
    {
        m_state = false;
        m_dwTickCount = 0;

        for (int iCount = 0; iCount < iResource; iCount++)
        {
            m_pDispose[iCount]  = NULL;
            m_dwTick[iCount]    = 0;
            m_bListen[iCount]   = 0;
        }

        return 0;
    }

    int Destroy()
    {
        return Initialize();
    }
private:
    bool            m_state;
    DWORD           m_dwTickCount;
    CSignal         m_cSignal;
    CMutex          m_cMutex;
    DWORD           m_dwTick[iResource];
    T_DISPOSE       *m_pDispose[iResource];
    DWORD           m_bListen[iResource];                                   // 是否为侦听SOCKET
    ApplicationLayer::TResourceManager<NET_SOCKET, iResource>  m_cResource;
    TThread< TSelector<T_DISPOSE, iResource> >  m_hThread;
};

}

#endif

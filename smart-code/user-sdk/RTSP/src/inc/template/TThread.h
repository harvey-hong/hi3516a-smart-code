#ifndef T_THREAD_H

#define T_THREAD_H

#include "../InternalCommon.h"
#include "./TSingletons.h"
#include "../Utility.h"

#include "ws_utility_api.h"
using namespace ws_utility;

namespace   ApplicationLayer
{

template<class T_RUN>
class TThread
{
public:
    TThread()
    {
        m_bRun = false;
        m_dwID = 0;
        m_pRun = NULL;
#ifdef SYSTEM_WIN32
        m_hThread = NULL;
#elif defined(SYSTEM_LINUX)
        m_hThread = 0;
#endif
    }
    ~TThread()
    {
        m_bRun = false;
        m_dwID = 0;
        m_pRun = NULL;
#ifdef SYSTEM_WIN32
        m_hThread = NULL;
#elif defined(SYSTEM_LINUX)
        m_hThread = 0;
#endif
    }
public:
    int Start(T_RUN *pObj)
    {
        m_pRun = pObj;
        m_bRun = true;

        if (0 != m_cThreadExit.create())
        {
            return 1;
        }

#ifdef  SYSTEM_WIN32
        m_hThread = ::CreateThread(NULL, 0, this->Thread, this, 0, &m_dwID);

        if (NULL == m_hThread)
        {
            OUTC_SYSTEM_ERROR;
            m_cThreadExit.destroy();
            return 1;
        }

#elif defined(SYSTEM_LINUX)
        int iresult = pthread_create(&m_hThread, NULL, Thread, this);

        if (0 != iresult || 0 == m_hThread)
        {
            OUTC_SYSTEM_ERROR;

            switch (iresult)
            {
                case EAGAIN:
                    OUTC_SIMPLE_STRING("*********pthread_create failed with EAGAIN (thread num limit arrived)*********\n");
                    break;

                case EINVAL:
                    OUTC_SIMPLE_STRING("*********pthread_create failed with EINVAL (create thread with invalid parameters)***********.\n");
                    break;

                case ENOMEM:
                    OUTC_SIMPLE_STRING("*********pthread_create failed with ENOMEM (no memeory to create thread)*********.\n");
                    break;

                default:
                    OUTC_SIMPLE_DWORD(iresult);
                    break;
            }

            m_hThread = 0;
            m_cThreadExit.destroy();
            return 1;
        }

#endif
        return 0;
    }
    int Stop()
    {
        int count = 0;
#ifdef SYSTEM_WIN32

        while (NULL == m_hThread && m_bRun && count < 10)
#elif defined(SYSTEM_LINUX)
        while (0 == m_hThread && m_bRun && count < 10)
#endif
        {
            ++count;
            ApplicationLayer::CUtility::Sleep(10);
        }

#ifdef SYSTEM_WIN32

        if (NULL != m_hThread)
#elif defined(SYSTEM_LINUX)
        if (0 != m_hThread)
#endif
        {
#ifdef SYSTEM_WIN32
            HANDLE  hThread = m_hThread;
            m_hThread = NULL;
#elif defined(SYSTEM_LINUX)
            pthread_t   hThread = m_hThread;
            m_hThread = 0;
#endif
            m_bRun = false;
            m_cThreadExit.wait();
#ifdef SYSTEM_WIN32
            ::CloseHandle(hThread);
#elif defined(SYSTEM_LINUX)
            pthread_join(hThread, NULL);
#endif
            m_cThreadExit.destroy();
            m_dwID = 0;
            m_pRun = NULL;
        }

        return 0;
    }
protected:
    TThread(const TThread &rObj)
    {
        (*this) = rObj;
    }
    TThread &operator=(const TThread &rObj)
    {
        return (*this);
    }
protected:

#ifdef SYSTEM_WIN32
    static DWORD WINAPI Thread(void *pParam)
    {
        return ThreadRun((TThread *)pParam);
    }
#elif defined(SYSTEM_LINUX)
    static void *Thread(void *pParam)
    {
        ThreadRun((TThread *)pParam);
        return NULL;
    }
#endif
    static int ThreadRun(TThread *pThis)
    {
        if (NULL == pThis)
        {
            return 1;
        }

        if (NULL == pThis->m_pRun)
        {
            return 1;
        }

        while (pThis->m_bRun && NULL != pThis->m_pRun)
        {
            if (0 != pThis->m_pRun->RunTask())
            {
                pThis->m_bRun = false;
            }
        }

        pThis->m_bRun = false;
        pThis->m_cThreadExit.signal();
        return 0;
    }
private:
    bool    m_bRun;
    T_RUN   *m_pRun;
    DWORD   m_dwID;
    CSignal m_cThreadExit;
#ifdef SYSTEM_WIN32
    HANDLE  m_hThread;
#elif defined(SYSTEM_LINUX)
    pthread_t   m_hThread;
#endif
};

}

#endif

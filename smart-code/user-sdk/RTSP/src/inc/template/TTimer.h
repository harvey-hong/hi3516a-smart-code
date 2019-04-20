#ifndef T_TIMER_H

#define T_TIMER_H

#include "../InternalCommon.h"
#include "./TThread.h"
#include "../Utility.h"

#include "ws_utility_api.h"
using namespace ws_utility;

namespace   ApplicationLayer
{

template<class T_DISPOSE>
class TTimer
{
public:
    TTimer()
    {
        Initialize();
    }
    ~TTimer()
    {
        Destroy();
    }
public:
    int Start(T_DISPOSE *pDispose, DWORD time)
    {
        if (0 == time)
        {
            OUTC_SIMPLE_FAILED;
            return 1;
        }

        //启动事件
        if (0 != m_cSignal.create())
        {
            OUTC_SIMPLE_FAILED;
            return 1;
        }

        m_bRun = true;
        m_pDispose = pDispose;
        m_dwTime = time;

        //启动任务线程
        if (0 != m_hThread.Start(this))
        {
            m_cSignal.destroy();
            OUTC_SIMPLE_FAILED;
            return 1;
        }

        return 0;
    }
    int Stop()
    {
        if (0 == m_dwTime)
        {
            OUTC_SIMPLE_FAILED;
            return 1;
        }

        m_bRun = false;
        //触发事件
        m_cSignal.signal();
        //停止任务线程
        m_hThread.Stop();
        m_dwTime = 0;
        //销毁事件
        m_cSignal.destroy();
        return 0;
    }
    int RunTask()
    {
        while (m_bRun && NULL != m_pDispose)
        {
            //等待事件
            m_cSignal.wait(m_dwTime);

            if (m_bRun && NULL != m_pDispose)
            {
                m_pDispose->RunTask();
            }
        }

        return 1;
    }
    int SetTimeInterval(DWORD time)
    {
        //更新时间
        m_dwTime = time;
        //触发事件，使其立即生效
        m_cSignal.signal();
        return 0;
    }
protected:
    TTimer(const TTimer &rObj)
    {
        (*this) = rObj;
    }
    TTimer &operator=(const TTimer &rObj)
    {
        return (*this);
    }
protected:
    int Initialize()
    {
        m_bRun = false;
        m_pDispose = NULL;
        m_dwTime = 0;
        return 0;
    }
    int Destroy()
    {
        return Initialize();
    }
private:
    bool        m_bRun;
    T_DISPOSE   *m_pDispose;
    DWORD       m_dwTime;
    CSignal     m_cSignal;
    TThread< TTimer >   m_hThread;
};

}

#endif

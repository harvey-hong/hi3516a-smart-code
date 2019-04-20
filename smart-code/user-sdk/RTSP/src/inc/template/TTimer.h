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

        //�����¼�
        if (0 != m_cSignal.create())
        {
            OUTC_SIMPLE_FAILED;
            return 1;
        }

        m_bRun = true;
        m_pDispose = pDispose;
        m_dwTime = time;

        //���������߳�
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
        //�����¼�
        m_cSignal.signal();
        //ֹͣ�����߳�
        m_hThread.Stop();
        m_dwTime = 0;
        //�����¼�
        m_cSignal.destroy();
        return 0;
    }
    int RunTask()
    {
        while (m_bRun && NULL != m_pDispose)
        {
            //�ȴ��¼�
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
        //����ʱ��
        m_dwTime = time;
        //�����¼���ʹ��������Ч
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

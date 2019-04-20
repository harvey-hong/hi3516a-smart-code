#ifndef T_ASYNC_NOTIFY_H

#define T_ASYNC_NOTIFY_H

#include "../InternalCommon.h"
#include "./TThread.h"
#include "ws_utility_api.h"
using namespace ws_utility;


namespace   ApplicationLayer
{

template <class T_DISPOSE, class T_PARAMETER>
class TAsyncNotify
{
public:
    TAsyncNotify()
    {
        Initialize();
    }
    ~TAsyncNotify()
    {
        Initialize();
    }
public:

    int Start(T_DISPOSE *pDispose)
    {
        if (m_bRun)
        {
            return 1;
        }

        m_bRun = true;

        if (0 != m_hMutex.create())
        {
            m_bRun = false;
            return 1;
        }

        m_hMutex.lock();

        if (0 != m_hSignal.create())
        {
            m_hMutex.unlock();
            m_hMutex.destroy();
            m_bRun = false;
            return 1;
        }

        m_pDispose  = pDispose;
        m_lsNotifyParameter.clear();

        if (0 != m_hThread.Start(this))
        {
            m_hSignal.destroy();
            m_hMutex.unlock();
            m_hMutex.destroy();
            m_bRun = false;
            return 1;
        }

        m_hMutex.unlock();
        return 0;
    }

    int Stop()
    {
        if (!m_bRun)
        {
            return 1;
        }

        m_bRun = false;
        //֪ͨ�����߳�
        m_hSignal.signal();
        //ֹͣ�����߳�
        m_hThread.Stop();
        m_hSignal.destroy();
        m_hMutex.lock();
        m_lsNotifyParameter.clear();
        m_pDispose = NULL;
        m_hMutex.unlock();
        m_hMutex.destroy();
        return 0;
    }
    //�첽֪ͨ
    int Notify(T_PARAMETER &para)
    {
        CGuard guard(&m_hMutex);
        //��ӵ�֪ͨ����
        m_lsNotifyParameter.push_back(para);
        //֪ͨ�����߳�
        m_hSignal.signal();
        return 0;
    }


    int RunTask()
    {
        while (m_bRun && NULL != m_pDispose)
        {
            m_hSignal.wait();

            if (!m_bRun || NULL == m_pDispose)
            {
                return 1;
            }

            m_hMutex.lock();

            while (m_bRun && m_lsNotifyParameter.size() > 0)
            {
                T_PARAMETER para(m_lsNotifyParameter.front());
                m_lsNotifyParameter.pop_front();
                m_hMutex.unlock();
                m_pDispose->Notify(para);
                m_hMutex.lock();
            }

            m_hMutex.unlock();
        }

        return 1;
    }
protected:
    TAsyncNotify(const TAsyncNotify &rObj)
    {
        (*this) = rObj;
    }
    TAsyncNotify &operator=(const TAsyncNotify &rObj)
    {
        return (*this);
    }
protected:
    int Initialize()
    {
        m_bRun = false;
        m_pDispose = NULL;
        return 0;
    }
private:
    //����״̬
    bool    m_bRun;
    //����������
    T_DISPOSE       *m_pDispose;
    //֪ͨ��Ϣ��
    typedef list<T_PARAMETER>   ListNotifyParameter;
    ListNotifyParameter m_lsNotifyParameter;
    //��Ϣ����������
    CMutex  m_hMutex;
    //�첽֪ͨ�¼�
    CSignal m_hSignal;
    //�첽�߳�
    TThread< TAsyncNotify<T_DISPOSE, T_PARAMETER> > m_hThread;
};

}

#endif

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
        //通知处理线程
        m_hSignal.signal();
        //停止工作线程
        m_hThread.Stop();
        m_hSignal.destroy();
        m_hMutex.lock();
        m_lsNotifyParameter.clear();
        m_pDispose = NULL;
        m_hMutex.unlock();
        m_hMutex.destroy();
        return 0;
    }
    //异步通知
    int Notify(T_PARAMETER &para)
    {
        CGuard guard(&m_hMutex);
        //添加到通知队列
        m_lsNotifyParameter.push_back(para);
        //通知处理线程
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
    //对象状态
    bool    m_bRun;
    //处理器对象
    T_DISPOSE       *m_pDispose;
    //通知信息表
    typedef list<T_PARAMETER>   ListNotifyParameter;
    ListNotifyParameter m_lsNotifyParameter;
    //信息表保护互斥量
    CMutex  m_hMutex;
    //异步通知事件
    CSignal m_hSignal;
    //异步线程
    TThread< TAsyncNotify<T_DISPOSE, T_PARAMETER> > m_hThread;
};

}

#endif

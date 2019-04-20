#include "../inc/RealStreamManager.h"

#include "ws_utility_api.h"
using namespace ws_utility;

namespace   ApplicationLayer
{

CRealStreamManager::CRealStreamManager()
{
}

CRealStreamManager::~CRealStreamManager()
{
}

CRealStream &CRealStreamManager::operator[](int iIndex)
{
    return m_cRealStreamManager[iIndex];
}

// 实时流资源管理器初始化，支持4/16个资源管理器
int CRealStreamManager::Initialize()
{
    if (RET_CHECK_FAIL(m_cMutex.create()))
    {
        return RET_FAIL;
    }

    m_cMutex.lock();

    if (RET_CHECK_FAIL(m_cRealStreamManager.Initialize()))
    {
        m_cMutex.unlock();
        m_cMutex.destroy();
        return RET_FAIL;
    }

    m_cMutex.unlock();
    return RET_SUCCESS;
}

//\\ 释放所有实时流会话资源
int CRealStreamManager::Destroy()
{
    m_cMutex.lock();
    int iCount;

    for (iCount = 0; iCount < MAX_CHANNEL_NUMBER; iCount++)
    {
        if (0 != m_cRealStreamManager.CheckResourceIdle(iCount))
        {
            m_cRealStreamManager[iCount].StopCapture();
            m_cRealStreamManager.Destroy(iCount);
        }
    }

    m_cRealStreamManager.Destroy();
    m_cMutex.unlock();
    m_cMutex.destroy();
    return RET_SUCCESS;
}

//\\ 获取可用的实时流资源编号
int CRealStreamManager::CreateStream(int &iResource)
{
    CGuard  guard(&m_cMutex);
    if (RET_CHECK_FAIL(m_cRealStreamManager.Create(iResource)))
    {
        return RET_FAIL;
    }

    return RET_SUCCESS;
}

//\\ 释放指定的实时流会话资源
int CRealStreamManager::DestroyStream(int iResource)
{
    CGuard  guard(&m_cMutex);
    if (RET_CHECK_FAIL(m_cRealStreamManager.Destroy(iResource)))
        return RET_FAIL;

    return RET_SUCCESS;
}

// 获取指定编号的实时流会话资源访问句柄
int CRealStreamManager::Stream(int iResource, CRealStream **pStream)
{
    CGuard  guard(&m_cMutex);
    if (RET_CHECK_SUCCESS(m_cRealStreamManager.CheckResourceIdle(iResource)))
    {
        return RET_FAIL;
    }

    (*pStream) = &(m_cRealStreamManager[iResource]);
    return RET_SUCCESS;
}
}

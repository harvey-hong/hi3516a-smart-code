#include "../inc/RtspSessionIdManager.h"
#include "../inc/GlobalObject.h"

#include "ws_utility_api.h"
using namespace ws_utility;

namespace   ApplicationLayer
{
CRtspSessionIdManager::CRtspSessionIdManager()
{
}

CRtspSessionIdManager::~CRtspSessionIdManager()
{
}

SessionStreamPair CRtspSessionIdManager::operator[](int iIndex)
{
    return m_cRtspSessionManager[iIndex];
}

// RTSP �Ự��������ʼ����֧��4/16��RTSP�Ự������
int CRtspSessionIdManager::Initialize()
{
    if (RET_CHECK_FAIL(m_cSessIdMutex.create()))
    {
        return RET_FAIL;
    }

    m_cSessIdMutex.lock();

    if (RET_CHECK_FAIL(m_cRtspSessionManager.Initialize()))
    {
        m_cSessIdMutex.unlock();
        m_cSessIdMutex.destroy();
        return RET_FAIL;
    }

    m_cSessIdMutex.unlock();
    return RET_SUCCESS;
}

//\\ ��������RTSP�Ự��Դ
int CRtspSessionIdManager::Destroy()
{
    m_cSessIdMutex.lock();
    int nStreamIndex;
    int iCount;

    for (iCount = 0; iCount < MAX_RTSP_SESSION_NUM; iCount++)
    {
        if (0 != m_cRtspSessionManager.CheckResourceIdle(iCount))
        {
            m_cRtspSessionManager.Destroy(iCount);
        }
    }

    m_cRtspSessionManager.Destroy();
    m_cSessIdMutex.unlock();
    m_cSessIdMutex.destroy();
    return RET_SUCCESS;
}

//\\ ��ȡ���õ�RTSP�Ự��Դ��ʵʱ���Ự��Դ������Ự�ṹ������Ϣ��ʵʱ���Ự��Դ����Ϣ��RTSP�Ự��Դ��
int CRtspSessionIdManager::AddSessionId(int nSessionId, eRtspStreamType eStreamType)
{
    if (nSessionId <= 0 || eStreamType <= eRtspStreamTypeBegin || eStreamType >= eRtspStreamTypeEnd)
    {
        return RET_FAIL;
    }

    CGuard  guard(&m_cSessIdMutex);
    int nResource = -1;

    if (RET_CHECK_FAIL(m_cRtspSessionManager.Create(nResource)))
    {
        return RET_FAIL;
    }

    if (nResource < 0 || nResource >= MAX_RTSP_SESSION_NUM)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    int nStreamIndex = -1;

    if (eRtspStreamReal == eStreamType)
    {
        nRet = TSingletons<CGlobalObject>::Instance().RealStreamMan().CreateStream(nStreamIndex);
    }

    if (RET_SUCCESS != nRet || -1 == nStreamIndex)
    {
        m_cRtspSessionManager.Destroy(nResource);
        return RET_FAIL;
    }

    if (eRtspStreamReal == eStreamType)
    {
        CRealStream     *pRealStream = NULL;
        nRet = TSingletons<CGlobalObject>::Instance().RealStreamMan().Stream(nStreamIndex, &pRealStream);

        if (RET_SUCCESS != nRet || NULL == pRealStream)
        {
            m_cRtspSessionManager.Destroy(nResource);
            TSingletons<CGlobalObject>::Instance().RealStreamMan().DestroyStream(nStreamIndex);
            return RET_FAIL;
        }

        m_cRtspSessionManager[nResource].pStream = (IRtspStream *)pRealStream;
    }

    m_cRtspSessionManager[nResource].eStreamType    = eStreamType;
    m_cRtspSessionManager[nResource].nSessionId         = nSessionId;
    m_cRtspSessionManager[nResource].nStreamIndex   = nStreamIndex;
    return RET_SUCCESS;
}

//\\ ����RTSP�Ự�ṹ�ͷ�ָ����ʵʱ���Ự��Դ��RTSP�Ự��Դ
int CRtspSessionIdManager::RemoveSessionId(int nSessionId)
{
    if (nSessionId <= 0)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    CGuard  guard(&m_cSessIdMutex);
    int nResource = -1;
    int nIndex;

    for (nIndex = 0; nIndex < MAX_RTSP_SESSION_NUM; nIndex++)
    {
        if (0 != m_cRtspSessionManager.CheckResourceIdle(nIndex))
        {
            if (RET_SUCCESS == nRet && nSessionId == m_cRtspSessionManager[nIndex].nSessionId)
            {
                nResource = nIndex;
                break;
            }
        }
    }

    if (nIndex == MAX_RTSP_SESSION_NUM || -1 == nResource)
    {
        return RET_FAIL;
    }

    //\\ �ͷ�ָ����ʵʱ���Ự��Դ
    eRtspStreamType     eStreamType = m_cRtspSessionManager[nResource].eStreamType;
    int     nStreamIndex = m_cRtspSessionManager[nResource].nStreamIndex;

    if (eRtspStreamReal == eStreamType && nStreamIndex >= 0 && nStreamIndex < MAX_CHANNEL_NUMBER)
    {
        TSingletons<CGlobalObject>::Instance().RealStreamMan().DestroyStream(nStreamIndex);
    }

    // ���³�ʼ������
    m_cRtspSessionManager[nResource].eStreamType = eRtspStreamTypeBegin;
    m_cRtspSessionManager[nResource].nSessionId = 0;
    m_cRtspSessionManager[nResource].nStreamIndex = -1;
    m_cRtspSessionManager[nResource].pStream = NULL;
    //\\ �ͷ�ָ����RTSP�Ự��Դ
    m_cRtspSessionManager.Destroy(nResource);
    return RET_SUCCESS;
}

//\\ ����RTSP�Ự�ṹ��ȡʵʱ���Ự��Դ���ʾ��
int CRtspSessionIdManager::GetStream(int nSessionId, IRtspStream **pStream)
{
    if (nSessionId <= 0 || NULL == pStream)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    CGuard  guard(&m_cSessIdMutex);
    int nResource = -1;
    int nStreamSessionId;
    int nIndex;

    for (nIndex = 0; nIndex < MAX_RTSP_SESSION_NUM; nIndex++)
    {
        if (0 != m_cRtspSessionManager.CheckResourceIdle(nIndex))
        {
            if (nSessionId == m_cRtspSessionManager[nIndex].nSessionId)
            {
                nResource = nIndex;
                break;
            }
        }
    }

    if (nIndex == MAX_RTSP_SESSION_NUM || -1 == nResource)
    {
        return RET_FAIL;
    }

    *pStream = m_cRtspSessionManager[nResource].pStream;
    return RET_SUCCESS;
}

}


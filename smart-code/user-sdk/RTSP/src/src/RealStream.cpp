#include "../inc/RealStream.h"
#include "../inc/GlobalObject.h"
#include "../inc/RtpRtspCommon.h"

#include "ws_utility_api.h"
using namespace ws_utility;

pthread_cond_t cond;
pthread_mutex_t mutex;

namespace   ApplicationLayer
{

CRealStream::CRealStream()
{
    m_nChannel          = -1;
    m_eCurCodeType      = eMediaCodeTypeBegin;
    m_eTaskStatus       = eTaskStatusNone;
    m_nClientConnCount  = 0;
    memset(m_acClientCoon, 0, sizeof(ClientConnStreamCtrl) * MAX_REAL_STREAM_NUMBER);
    m_eCaptureStatus = eTaskStatusStop;
    m_nFrameType            = 0;
    m_dwLastVideoTimeStamp  = 0;
    m_Iframe_Send_Status    = 0;
}

CRealStream::~CRealStream()
{
    Destroy();
}

// ����RTSP�Ự�ṹ�������Ϣ������ʵʱ������������ʼ��RTSP��������
int CRealStream::Initialize(int nSessionId, int nChannel, char *pStartTime, char *pEndTime, eRtspMediaCodeType m_eCodeType)
{
    if (nSessionId <= 0 || nChannel < 0 || nChannel >= MAX_CHANNEL_NUMBER)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    m_nChannel      = nChannel;

    if (m_eCodeType == eRtspMediaCodeMain)
    {
        m_eCurCodeType = eMediaCodeMain ;
    }
    else
    {
        m_eCurCodeType = eMediaCodeAssist ;
    }

    // ͨ��TThreadģ������ʵʱ��������
    if (RET_CHECK_FAIL(m_cRealStreamSender.Start(this, m_eCurCodeType)))
    {
        return RET_FAIL;
    }

    if (RET_CHECK_FAIL(m_cStreamMutex.create()))
    {
        m_cRealStreamSender.Stop();
        return RET_FAIL;
    }

    // ����ʵʱ���������󶨵���������RTSP�Ự�ṹ
    nRet = m_cStreamSender.Initialize(nSessionId, eRtspStreamReal);

    if (RET_SUCCESS != nRet)
    {
        m_cRealStreamSender.Stop();
        m_cStreamMutex.destroy();
        return RET_FAIL;
    }

        m_eTaskStatus   = eTaskStatusInitialize;
		/*cb change 2016.8.5 .���h265��֧�� start*/ 
		pthread_cond_init(&cond, NULL);
		pthread_mutex_init(&mutex, NULL);
		/*cb change 2016.8.5 .���h265��֧�� end*/ 
        return RET_SUCCESS;
}

int CRealStream::Destroy()
{
    int nRet = RET_SUCCESS;
    m_cRealStreamSender.Stop();
    nRet = m_cStreamSender.Destroy();
    m_cStreamMutex.destroy();
    m_nChannel = -1;
    m_eCurCodeType  = eMediaCodeTypeBegin;
    m_eTaskStatus   = eTaskStatusNone;
    m_nClientConnCount = 0;
    memset(m_acClientCoon, 0, sizeof(ClientConnStreamCtrl) * MAX_REAL_STREAM_NUMBER);
    m_eCaptureStatus = eTaskStatusStop;
    m_nFrameType = 0;
        m_dwLastVideoTimeStamp = 0;
		/*cb change 2016.8.5 .���h265��֧�� start*/ 
		pthread_cond_destroy(&cond);
		pthread_mutex_destroy(&mutex);
		/*cb change 2016.8.5 .���h265��֧�� end*/ 
        return RET_SUCCESS;
}

// ��ȡʵʱ���Ự��Դ��Ӧ����Ƶͨ����
int CRealStream::GetChannel(int &nChannel)
{
    nChannel = m_nChannel;
    return RET_SUCCESS;
}

// ����ϵͳ�ص��������ϲ��ʵʱ������
int CRealStream::Start()
{
    CGuard guard(&m_cStreamMutex);
    if (eTaskStatusInitialize != m_eTaskStatus)
    {
        return RET_FAIL;
    }

    m_cRealStreamSender.Resume();
    m_eTaskStatus       = eTaskStatusStart;
    return RET_SUCCESS;
}

int CRealStream::Stop()
{
    CGuard guard(&m_cStreamMutex);
    if (m_nClientConnCount > 0 || eTaskStatusStart != m_eTaskStatus)
    {
        return RET_FAIL;
    }

    // �ص�����ֹͣʵʱ��
    m_cRealStreamSender.Suspend();
    // ���³�ʼ������
    m_nChannel = -1;
    m_eCurCodeType = eMediaCodeTypeBegin;
    m_eTaskStatus = eTaskStatusNone;
    m_nClientConnCount = 0;
    memset(m_acClientCoon, 0, sizeof(ClientConnStreamCtrl) * MAX_REAL_STREAM_NUMBER);
    m_eCaptureStatus = eTaskStatusStop;
    m_nFrameType = 0;
    m_dwLastVideoTimeStamp = 0;
    return RET_SUCCESS;
}

// ��ͣ����
int CRealStream::Pause()
{
    return RET_SUCCESS;
}

// ���ͻ��Ự�ṹ���浽�ڲ�m_acClientCoon�У����ж��Ƿ���Ҫ������������
int CRealStream::AddClientConn(int nClientId, void *pConnParam)
{
    if (nClientId <= 0 || NULL == pConnParam)
    {
        return RET_FAIL;
    }

    eRtspMediaCodeType  eRtspCodeType = *(eRtspMediaCodeType *)pConnParam;

    if (eRtspCodeType <= eRtspMediaCodeTypeBegin || eRtspCodeType >= eRtspMediaCodeTypeEnd)
    {
        return RET_FAIL;
    }

    CGuard guard(&m_cStreamMutex);
    if (eTaskStatusStart != m_eTaskStatus)
    {
        return RET_FAIL;
    }

    int     nRet = RET_SUCCESS;
    int     nIndex;

    // ����ͻ�������Ϣ��m_acClientCoon���ݽṹ��
    for (nIndex = 0; nIndex < MAX_REAL_STREAM_NUMBER; nIndex++)
    {
        if (0 == m_acClientCoon[nIndex].nClientId)
        {
            eMediaCodeType  eCodeType = eMediaCodeMain;

            if (eRtspMediaCodeMain == eRtspCodeType)
            {
                eCodeType     = eMediaCodeMain;
            }
            else
            {
                eCodeType     = eMediaCodeAssist;
            }

            m_acClientCoon[nIndex].nClientId            = nClientId;
            m_acClientCoon[nIndex].eCodeType            = eCodeType;
            m_acClientCoon[nIndex].dwVideoTimeStamp     = 8000;
            m_nClientConnCount++;
            break;
        }
    }

    return RET_SUCCESS;
}

// �Ƴ��ͻ�������
int CRealStream::RemoveClientConn(int nClientId)
{
    if (nClientId <= 0)
    {
        return RET_FAIL;
    }

    CGuard guard(&m_cStreamMutex);
    int nRet = RET_SUCCESS;

    if (eTaskStatusStop == m_eTaskStatus)
    {
        return RET_FAIL;
    }

    int nIndex;

    for (nIndex = 0; nIndex < MAX_REAL_STREAM_NUMBER; nIndex++)
    {
        if (m_acClientCoon[nIndex].nClientId == nClientId)
        {
            memset(&m_acClientCoon[nIndex], 0, sizeof(ClientConnStreamCtrl));
            m_nClientConnCount--;
            break;
        }
    }

    return RET_SUCCESS;
}

// ����RTSP���������������ͱ�ʶ
int CRealStream::StartSend()
{
    int nRet = RET_SUCCESS;
    CGuard  guard(&m_cStreamMutex);
    if (eTaskStatusStart == m_eCaptureStatus)
    {
        nRet = m_cStreamSender.StartSend();
    }

    return nRet;
}

// ��������ʵʱ��
int CRealStream::StartCapture()
{
    int nRet = RET_SUCCESS;
    CGuard  guard(&m_cStreamMutex);

    if (1 == m_nClientConnCount)
    {
        m_cRealStreamSender.Resume();
        nRet = m_cStreamSender.StartCapture();
    }

    m_eCaptureStatus = eTaskStatusStart;
    return nRet;
}

// ֹͣ����ʵʱ��
int CRealStream::StopCapture()
{
    int nRet = RET_SUCCESS;
    CGuard  guard(&m_cStreamMutex);
    if (1 == m_nClientConnCount)
    {
        m_cRealStreamSender.Suspend();
        nRet = m_cStreamSender.StopCapture();
    }

    m_eCaptureStatus = eTaskStatusStop;
    return nRet;
}

// ��ȡSDP��Ϣ
int CRealStream::GetSDPInfo(char *pSDPInfo, INT32 &nSDPLen)
{
    if (NULL == pSDPInfo)
    {
        return RET_FAIL;
    }

    int nRet = m_cStreamSender.GetSDPInfo(pSDPInfo, nSDPLen);

    if (RET_SUCCESS != nRet)
    {
        return RET_FAIL;
    }

    return RET_SUCCESS;
}

// ��ȡ��ǰ��Ƶ֡���ͺ����뵽CRealStreamSender������
int CRealStream::Send(IN eMediaCodeType eCodeType, IN CMediaPacketRealStreamDepict &depict, IN LPBuffer stream)
{
    if (eTaskStatusStart != m_eTaskStatus)
    {
        return RET_FAIL;
    }

    if (m_eCurCodeType == eCodeType)
    {
        m_nFrameType = 0 ;
        memcpy(&m_nFrameType, stream->pBuffer + 4, 1);
        return m_cRealStreamSender.Send(depict, stream);
    }

    return RET_SUCCESS;
}

// ����ʱ���������������RTP
int CRealStream::Send(LPBuffer stream)
{
    if (NULL == stream || stream->dwBufLen <= 22)
    {
        return RET_FAIL;
    }

    int                 nRet = RET_SUCCESS;
    int                 nIndex;
    unsigned char    dwFrameType = 0;
    CGuard  guard(&m_cStreamMutex);
    dwFrameType     = *(stream->pBuffer + 4);  //DVR encoded frames : Got Video I frame type 0x01 or p frame type 0x02, Avudio frame type 0x08
    m_nFrameType    = dwFrameType;
    DWORD    nTimeStamp;
    memcpy(&nTimeStamp, stream->pBuffer + 9, 4);

    pthread_mutex_lock(&mutex);
    int video_code = *(stream->pBuffer + 13);
    if(video_code == 5)
        VideoCodec = eRtspVideoCodecH265;
    else if(video_code == 6)
        VideoCodec = eRtspVideoCodecH264;
		
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
		/*cb change 2016.8.5 .���h265��֧�� end*/ 
        // ����Ƶ֡�����µ�ʱ�����Ϣ
    if (0x08 != m_nFrameType)
    {
        DWORD dwDeltaTimeStamp = 3600;
        if (m_dwLastVideoTimeStamp > 0)
        {
            dwDeltaTimeStamp = nTimeStamp - m_dwLastVideoTimeStamp;
            if (dwDeltaTimeStamp < 0)
            {
                dwDeltaTimeStamp = 3600;
            }
        }


        int nIndex ;
        for (nIndex = 0; nIndex < MAX_REAL_STREAM_NUMBER; nIndex++)
        {
            if (0 == m_acClientCoon[nIndex].nClientId)
            {
                continue;
            }

            RTSPClient *pClient = (RTSPClient *)(m_acClientCoon[nIndex].nClientId);

            if (0 == pClient->IsFirstFrame)
            {
                m_acClientCoon[nIndex].dwVideoTimeStamp += dwDeltaTimeStamp;
                if(m_acClientCoon[nIndex].dwVideoTimeStamp >= 4015731839 )
                {
                    m_acClientCoon[nIndex].dwVideoTimeStamp = 8000;
                    nTimeStamp  = m_dwLastVideoTimeStamp;
                }
            }
            m_dwLastVideoTimeStamp = nTimeStamp;
        }
    }

    if (0 == m_Iframe_Send_Status)
    {
        if ((m_nFrameType != 0x01) && (m_nFrameType != 0x10) && (m_nFrameType != 0x11))
        {
            return RET_SUCCESS;
        }
        m_Iframe_Send_Status = 1;
    }

    // ����ʵʱ����������������
    nRet = m_cStreamSender.Send(stream, (void *)this);
    return RET_SUCCESS;
}

// ��׼��TCP ����UDP ����ʱ���ص�����ȡ��ǰ����֡��ʱ���
int CRealStream::GetClientConnInfo(int nClientId, int &nSendFalg, DWORD &dwVideoTimeStamp)
{
    if (nClientId <= 0)
    {
        return RET_FAIL;
    }

    RTSPClient *pClient = (RTSPClient *)nClientId;

    if (1 == pClient->IsFirstFrame)
    {
        if ((0x01 != m_nFrameType) && (0x11 != m_nFrameType) && (0x10 != m_nFrameType))
        {
            nSendFalg   = 0;
            return RET_SUCCESS;
        }
    }

    int     nIndex;

    for (nIndex = 0; nIndex < MAX_REAL_STREAM_NUMBER; nIndex++)
    {
        if (m_acClientCoon[nIndex].nClientId == nClientId)
        {
            break;
        }
    }

    if (MAX_REAL_STREAM_NUMBER == nIndex)
    {
        return RET_FAIL;
    }

    nSendFalg = 1;

    if (0x08 != m_nFrameType)
    {
        dwVideoTimeStamp = m_acClientCoon[nIndex].dwVideoTimeStamp;
    }

    return RET_SUCCESS;
}

// ��ȡ��ǰ����Ƶ�����׼
int CRealStream::GetCodecType(eRtspVideoCodecType &eVideoCodec, eRtspAudioCodecType &eAudioCodec)
    {
    	/*cb change 2016.8.5 .���h265��֧�� start*/ 
    	pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
		eVideoCodec = VideoCodec;
		pthread_mutex_unlock(&mutex);
		/*cb change 2016.8.5 .���h265��֧�� end*/ 
        eAudioCodec = eRtspAudioCodecNone;
        return RET_SUCCESS;
}

}


#include "../inc/HYRtspService.h"
#include "../inc/template/TSingletons.h"
#include "../inc/GlobalObject.h"
#include "../inc/RtpRtsp.h"
#include "../inc/RTCPTimeInterval.h"
#include "../inc/RtspUriParser.h"
#include "../inc/interface/IRtspStream.h"
#include "getlocalinfo.h"

using namespace GETLOCALINFO;

using namespace ApplicationLayer;

char g_cVersion[] = "Build 1.0.0.25599";
static int          m_iStatus = 0;

CHYPrivateService::CHYPrivateService()
{
    Initialize();
}

CHYPrivateService::~CHYPrivateService()
{
    Destroy();
}

// ��ʼ��rtsp��̬����
int CHYPrivateService::InitializeRtspParam()
{
    return RET_SUCCESS;
}

int CHYPrivateService::Start()
{
    RTSP_SER_PD("----------RTSPService::Start()----------\n");
    const int   base = 100;

    INT32   nErrorCode = 0;
    char    acServerIp[IP_ADDRESS_LEN] = {0};
    DWORD   dwCommand = 0;
    DWORD   dwMediaTCP = 0;
    DWORD   dwMediaRTP = 0;
    DWORD   dwMediaRTSP = 554;

    INT32   hRtspServer = 0;
    int         nRet = 0;

    RTSP_SER_PD("[FILE=%s][FUN=%s][LINE=%d] Enter --- \n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;

    if(RET_CHECK_FAIL(Login()) )
        goto FAILED_0;

    RTSP_SER_PD("[FILE=%s][FUN=%s][LINE=%d] Enter --- \n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;

    // ʵʱ����������ʼ����֧��4/16��ʵʱ��������
    if (RET_CHECK_FAIL(TSingletons<CGlobalObject>::Instance().RealStreamMan().Initialize()))
        goto FAILED_0;

    RTSP_SER_PD("[FILE=%s][FUN=%s][LINE=%d] Enter --- \n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;

    // RTSP �Ự��������ʼ����֧��4/16��RTSP�Ự������
    nRet = TSingletons<CGlobalObject>::Instance().RtspSessionMan().Initialize();
    if(RET_CHECK_FAIL(nRet))
        goto FAILED_0;

    RTSP_SER_PD("[FILE=%s][FUN=%s][LINE=%d] Enter --- \n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;

    // ˽�к�����ͨ���ϲ�ص���ȡ���ص�RTSP �˿�
    if (RET_CHECK_FAIL(GetServerPort(dwCommand, dwMediaTCP, dwMediaRTP, dwMediaRTSP)) || 0 == dwMediaRTSP)
        goto FAILED_0;

    RTSP_SER_PD("[FILE=%s][FUN=%s][LINE=%d] Enter --- \n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;
    RTSP_SER_PD("%s,%d,dwMediaRTSP = %u\n",__FILE__,__LINE__,dwMediaRTSP);
    memset(acServerIp, 0, sizeof(acServerIp));
    hRtspServer = RTSPServerStart((BYTE *)acServerIp, dwMediaRTSP, CHYPrivateService::RtspAddSessionCB, &nErrorCode);
    if(RTP_RTSP_ERROR == hRtspServer || RTP_RTSP_OK != nErrorCode)
        goto FAILED_0;

    RTSP_SER_PD("[FILE=%s][FUN=%s][LINE=%d] Enter --- \n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;

    TSingletons<CGlobalObject>::Instance().RtspServerHandle() = hRtspServer;

    if (RET_CHECK_FAIL(TSingletons<CGlobalObject>::Instance().Destroyer().Start()))
        goto FAILED_0;

    RTSP_SER_PD("[FILE=%s][FUN=%s][LINE=%d] Enter --- \n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;

    m_nStatus = 1 ;
    m_iStatus = 1 ;

    return RET_SUCCESS;

FAILED_0:
    return RET_FAIL;
}

int CHYPrivateService::Stop()
{
    int nStatus = 0;
    GetStatus(nStatus);

    if (1 == nStatus)
    {
        m_nStatus = 0 ;
    }
    else
    {
        return RET_FAIL;
    }
    m_iStatus = m_nStatus ;


    //\\ ֹͣ������.
    if (RET_CHECK_FAIL(TSingletons<CGlobalObject>::Instance().Destroyer().Stop()))
    {
        RTSP_SER_PE(" fail !\n");
    }

    //\\ ֹͣRTSP������.
    INT32 nRet = RTP_RTSP_OK;
    nRet = RTSPServerShutdown(TSingletons<CGlobalObject>::Instance().RtspServerHandle());
    if(RET_CHECK_FAIL(nRet))
    {
        RTSP_SER_PE(" fail , nRet=[%d]\n", nRet);
    }

    //\\ �ͷ�RTSP�Ự��Դ������.
    nRet = TSingletons<CGlobalObject>::Instance().RtspSessionMan().Destroy();
    if(RET_CHECK_FAIL(nRet))
    {
        RTSP_SER_PE(" fail !\n");
    }

    //\\ �ͷ�ʵʱ���Ự��Դ������.
    if (RET_CHECK_FAIL(TSingletons<CGlobalObject>::Instance().RealStreamMan().Destroy()))
    {
        RTSP_SER_PE(" fail !\n");
    }
    if (RET_CHECK_FAIL(Logout()))
    {
        RTSP_SER_PE(" fail !\n");
    }

    return RET_SUCCESS;
}


//\\ ��ʼ���û�ID
int CHYPrivateService::Login()
{
    //\\ ˽�к���
    TSingletons<CGlobalObject>::Instance().UserID() = (DWORD)VALUE_INVALID;
    return RET_SUCCESS;
}

//\\ ��ʼ���û�ID
int CHYPrivateService::Logout()
{
    TSingletons<CGlobalObject>::Instance().UserID() = (DWORD)VALUE_INVALID;
    return RET_SUCCESS;
}

//\\ ��ȡ�汾��Ϣ
int CHYPrivateService::GetVersion(char *&version)
{
    version = g_cVersion;
    return RET_SUCCESS;
}

/*
* @brief
*   ��ʼ��
* @return
*   ����0��ʾ�ɹ�, �����ʾ������
* @note
*   �ӿ�����: ����ʽ
*/
int CHYPrivateService::Initialize()
{
    m_nStatus = 0;
    m_iStatus = 0 ;
    return RET_SUCCESS;
}

/*
* @brief
*   ����
* @return
*   ����0��ʾ�ɹ�, �����ʾ������
* @note
*   �ӿ�����: ����ʽ
*/
int CHYPrivateService::Destroy()
{
    m_nStatus = 0;
    m_iStatus = 0 ;
    return RET_SUCCESS;
}

// ˽�к�����ͨ���ϲ�ص���ȡ���ص�RTSP �˿�
int CHYPrivateService::GetServerPort(DWORD &dwCommand, DWORD &dwMediaTCP, DWORD &dwMediaRTP, DWORD &dwMediaRTSP)
{
	int DeviceType;
	int ret = Get_DeviceType((DWORD)VALUE_INVALID,&DeviceType);
	if(RET_SUCCESS != ret)
	{
		return RET_FAIL;
	}
	if(1 == DeviceType)
	{
		HY_DVR_LISTENPORT_CONF 	cNetWorkConfig;
		memset(&cNetWorkConfig, 0, sizeof(cNetWorkConfig));
		DWORD dwBufferLen = sizeof(cNetWorkConfig);
		int ret = Get_local_port_info((DWORD)VALUE_INVALID, HY_DVR_GET_NETCFG, NETCFG_LISTENPORT_CONF, (BYTE *)&cNetWorkConfig, &dwBufferLen);
		if(RET_SUCCESS != ret)
		{
			return RET_FAIL;
		}
		if(sizeof(cNetWorkConfig) != dwBufferLen)
		{
			return RET_FAIL;
		}

		dwCommand 	= cNetWorkConfig.wLocalCmdPort;
		dwMediaTCP 	= cNetWorkConfig.wLocalMediaPort;
		dwMediaRTP = dwMediaRTSP = cNetWorkConfig.wRtpPort;	
	}
	else
	{
		Port_Info m_dwport_info;
		memset(&m_dwport_info, 0, sizeof(m_dwport_info));
		DWORD dwBufferLen = sizeof(m_dwport_info);
		int ret = Get_local_port_info((DWORD)VALUE_INVALID, 0, 0, (BYTE *)&m_dwport_info, &dwBufferLen);
		if(RET_SUCCESS != ret)
		{
			return RET_FAIL;
		}
		dwCommand  =  m_dwport_info.cmd_port;
		dwMediaTCP =  m_dwport_info.tcp_port;
		dwMediaRTP =  dwMediaRTSP = m_dwport_info.rtsp_port;
	}
    return RET_SUCCESS;
}

int CHYPrivateService::SetStatus(int nStatus)
{
    m_nStatus = nStatus;
    m_iStatus = nStatus;
    return RET_SUCCESS;
}

int CHYPrivateService::GetStatus(int &nStatus)
{
    nStatus = m_nStatus;
    return RET_SUCCESS;
}

//\\ ���RTSP�Ự�ص�����: ����RTSP�Ự�ṹ��ӵ�RTSP���������������У��ڲ�����RTSP�Ự��Դ��ʵʱ���Ự��Դ��ͨ���ص������ϲ���룬�ȴ�SDP��Ϣ����Ƶ������Ƶ��������ӵ��ûỰ�ṹ֧�ֵ����б���
INT32 CHYPrivateService::RtspAddSessionCB(INT32 nClientId, INT32 nSesseionId, INT32 nEvent, void *pArg)
{
    AddSessionParam *pSessionParam = (AddSessionParam *)pArg;

    if (NULL == pSessionParam || 0 == strlen(pSessionParam->acSessionName))
    {
        sleep(2);
        return RET_FAIL;
    }

    if (FS_ADD_SESS != nEvent)
    {
        return RET_FAIL;
    }

    int             nEnalbleRTCP            = 1;
    int             nRtcpSRInterval         = 1000;
    static int      nRtspMulticastPort = 10000;
    INT32   hRtspServer = TSingletons<CGlobalObject>::Instance().RtspServerHandle();
    IRtspStream *pStream = NULL;
    eRtspVideoCodecType eVideoCodec = eRtspVideoCodecTypeBegin;
    eRtspAudioCodecType eAudioCodec = eRtspAudioCodecTypeBegin;
    SupportedCodecs eSupportCodecs = INVALID_CODEC; // ��������
    int nClockRate = 0;                             // ʱ��Ƶ��
    int nNumberOfChannel = 0;                       // ͨ������only in audio
    int nErrorCode = RET_OK;
    int nFileEndTime = 0;
    //\\ ����RTSP�Ự�ṹ��ӵ�RTSP������������У����ûỰ�ͻ����ӻص�����ClientConnectionCB��RTSP�¼��ص�����RtspStreamEventCB
    INT32 hSession = RTSPSessionCreate(hRtspServer, (BYTE *)(pSessionParam->acSessionName), (BYTE *)NULL, 0, UDP_MTU_SIZE, TCP_MTU_SIZE, nEnalbleRTCP,
                                       nRtcpSRInterval, &nErrorCode, ClientConnectionCB, RtspStreamEventCB, nFileEndTime);

    if (RTP_RTSP_ERROR == hSession || hSession <= 0 || nErrorCode < 0)
    {
        return RET_FAIL;
    }

    //\\ ��ȡ���õ�RTSP�Ự��Դ��ʵʱ���Ự��Դ������Ự�ṹ������Ϣ��ʵʱ���Ự��Դ����Ϣ��RTSP�Ự��Դ��
    int nRet = TSingletons<CGlobalObject>::Instance().RtspSessionMan().AddSessionId(hSession, pSessionParam->eStreamType);

    if (RET_SUCCESS != nRet)
    {
        goto FAILED0;
    }

    //\\ ��ȡʵʱ���Ự��Դ���ʾ��
    nRet  = TSingletons<CGlobalObject>::Instance().RtspSessionMan().GetStream(hSession, &pStream);

    if (RET_SUCCESS != nRet || NULL == pStream)
    {
        goto FAILED1;
    }

    //\\ ����RTSP�Ự�ṹ�������Ϣ������ʵʱ������������ʼ��RTSP��������
    nRet = pStream->Initialize(hSession, pSessionParam->nChannel, pSessionParam->acBeginTime, pSessionParam->acEndTime, pSessionParam->eCodeType);

    if (RET_SUCCESS != nRet)
    {
        goto FAILED1;
    }

    //\\ ����ϵͳ�ص��������ϲ��ʵʱ������
    nRet = pStream->Start();

    if (RET_SUCCESS != nRet)
    {
        goto FAILED2;
    }

    //\\ ��ȡ��ǰ����Ƶ�����׼
    nRet = pStream->GetCodecType(eVideoCodec, eAudioCodec);

    if (RET_SUCCESS != nRet || eVideoCodec <= eRtspVideoCodecTypeBegin || eVideoCodec >= eRtspVideoCodecTypeEnd || eAudioCodec <= eRtspAudioCodecTypeBegin || eAudioCodec >= eRtspAudioCodecTypeEnd)
    {
        goto FAILED3;
    }

    // �����Ƶ�����Ự��
    eSupportCodecs  = INVALID_CODEC;
    nClockRate      = VIDEO_CLOCK_RATE;
    nNumberOfChannel  = 0;

    if (eRtspVideoCodecH264 == eVideoCodec)
    {
        eSupportCodecs = CODEC_H264;
    }
	else if(eRtspVideoCodecH265 == eVideoCodec)/*cb change 2016.8.5 .���h265��֧��*/ 
	{
		eSupportCodecs = CODEC_H265;
	}


    if (INVALID_CODEC != eSupportCodecs)
    {
        //\\ �ȴ��ϲ�������ݻ�ȡSPS��PPS��Ϣ
        char    acSDPInfo[MAX_SDP_LEN] = {0};
        int         nSDPLen = MAX_SDP_LEN;
        nRet = pStream->GetSDPInfo(acSDPInfo, nSDPLen);

        if (RET_SUCCESS != nRet)
        {
            goto FAILED3;
        }

        //\\ ����ָ��RTSP�Ự�ṹ֧�ֵ���������Ӷ�H264��Ƶ��֧��
        nRet = RTSPAddStreamToSession(hSession, eSupportCodecs, 1, nClockRate, nNumberOfChannel, nSDPLen, (BYTE *)acSDPInfo, nRtspMulticastPort);

        if (RET_SUCCESS != nRet)
        {
            goto FAILED3;
        }
    }

    // �����Ƶ�����Ự��
    eSupportCodecs = INVALID_CODEC;

    switch (eAudioCodec)
    {
        case eRtspAudioCodecG711A:
        {
            eSupportCodecs = CODEC_G711A;
            nClockRate = AUDIO_CLOCK_RATE;
            nNumberOfChannel = 1;
            break;
        }

        case eRtspAudioCodecG711U:
        {
            eSupportCodecs = CODEC_G711U;
            nClockRate = AUDIO_CLOCK_RATE;
            nNumberOfChannel = 1;
            break;
        }

        // note: ע��G726��ʱ��Ƶ�ʣ����ﲻ����8000, ʵ��������Ǳ�����
        case eRtspAudioCodecG726_40:
        {
            eSupportCodecs = CODEC_G726;
            nClockRate = 40000;  // 8000*(5bits/sample)
            nNumberOfChannel = 1;
            break;
        }

        case eRtspAudioCodecG726_32:
        {
            eSupportCodecs = CODEC_G726;
            nClockRate = 32000; // 8000*(4bits/sample)
            nNumberOfChannel = 1;
            break;
        }

        case eRtspAudioCodecG726_24:
        {
            eSupportCodecs = CODEC_G726;
            nClockRate = 24000; // 8000*(3bits/sample)
            nNumberOfChannel = 1;
            break;
        }

        case eRtspAudioCodecG726_16:
        {
            eSupportCodecs = CODEC_G726;
            nClockRate = 16000; // 8000*(2bits/sample)
            nNumberOfChannel = 1;
            break;
        }

        default:
            break;
    }

    //\\ ����ָ��RTSP�Ự�ṹ֧�ֵ���������Ӷ�G726��Ƶ��֧��
    if (INVALID_CODEC != eSupportCodecs)
    {
        nRet = RTSPAddStreamToSession(hSession, eSupportCodecs, 0, nClockRate,  nNumberOfChannel, 0, NULL, nRtspMulticastPort);
    }

    return RET_SUCCESS;
FAILED3:
    pStream->Stop();
FAILED2:
    pStream->Destroy();
FAILED1:
    TSingletons<CGlobalObject>::Instance().RtspSessionMan().RemoveSessionId(hSession);
FAILED0:
    RTSPSessionDestroy(hSession);
    return RET_FAIL;
}


//\\ RTSP���¼��ص�������ִ�ж�Ӧ��RTSP�Ự��Դ����
INT32 CHYPrivateService::RtspStreamEventCB(INT32 nClientId, INT32 nSesseionId, INT32 nEvent, void *pArg)
{
    if( m_iStatus < 1 )
        return RET_FAIL;

    if (nSesseionId <= 0)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;

    switch (nEvent)
    {
        case FS_START_CLIENT:
            nRet = ProcessStartClientEvent(nClientId, nSesseionId, pArg);
            break;

        case FS_DESTROY_CLIENT:
            nRet = ProcessDestroyClientEvent(nClientId, nSesseionId, pArg);
            break;

        case FS_PLAY:
            nRet = ProcessPlayEvent(nSesseionId, pArg);
            break;

        case FS_PAUSE:
            nRet = ProcessPauseEvent(nSesseionId, pArg);
            break;

        case FS_STOP:
            nRet = ProcessStopEvent(nSesseionId, pArg);
            break;

        case FS_REMOVE_SESS:
            nRet = ProcessRemoveSessionEvent(nSesseionId, pArg);
            break;

        case FS_REMOVE_SESS_STOP:
            nRet = ProcessRemoveSessionEventByStop(nSesseionId, pArg);
            break;

        case FS_BITRATE_CONTROL:
            break;

        default:
            nRet = RET_FAIL;
            break;
    }

    return nRet;
}

//\\ �պ���
INT32 CHYPrivateService::ClientConnectionCB(INT32 nConnectFlag, BYTE *sessionName)
{
    if (NULL == sessionName)
    {
        return RET_FAIL;
    }

    return RET_SUCCESS;
}

//\\ ��ָ��RTSP�Ự��Դ����ӿͻ���Ϣ�Լ���������������Ϣ
int CHYPrivateService::ProcessStartClientEvent(int nClientId, int nSessionId, void *pParam)
{
    if (nClientId <= 0 || nSessionId <= 0)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    eRtspMediaCodeType eCodeType = eRtspMediaCodeTypeBegin;

    if (NULL != pParam)
    {
        eCodeType = *(eRtspMediaCodeType *)pParam;
    }

    IRtspStream *pStream = NULL;
    nRet  = TSingletons<CGlobalObject>::Instance().RtspSessionMan().GetStream(nSessionId, &pStream);

    if (RET_SUCCESS != nRet || NULL == pStream)
    {
        return RET_FAIL;
    }

    nRet = pStream->AddClientConn(nClientId, (void *)&eCodeType);

    if (RET_SUCCESS != nRet)
    {
        return RET_FAIL;
    }

    return RET_SUCCESS;
}

//\\ ɾ��ָ��RTSP�Ự��Դ��ָ���ͻ���Ϣ
int CHYPrivateService::ProcessDestroyClientEvent(int nClientId, int nSessionId, void *pParam)
{
    if (nClientId <= 0 || nSessionId <= 0)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    IRtspStream *pStream = NULL;
    nRet  = TSingletons<CGlobalObject>::Instance().RtspSessionMan().GetStream(nSessionId, &pStream);

    if (RET_SUCCESS != nRet || NULL == pStream)
    {
        return RET_FAIL;
    }

    nRet = pStream->RemoveClientConn(nClientId);

    if (RET_SUCCESS != nRet)
    {
        return RET_FAIL;
    }

    return RET_SUCCESS;
}

//\\ ����ָ��RTSP�Ự��Դ�������ϴ�
int CHYPrivateService::ProcessPlayEvent(int nSessionId, void *pParam)
{
    if (nSessionId <= 0)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    IRtspStream *pStream = NULL;
    nRet  = TSingletons<CGlobalObject>::Instance().RtspSessionMan().GetStream(nSessionId, &pStream);

    if (RET_SUCCESS != nRet || NULL == pStream)
    {
        return RET_FAIL;
    }

    nRet = pStream->StartCapture();

    if (RET_SUCCESS != nRet)
    {
        return RET_FAIL;
    }

    nRet = pStream->StartSend();

    if (RET_SUCCESS != nRet)
    {
        return RET_FAIL;
    }

    return RET_SUCCESS;
}

//\\ ��ָͣ��RTSP�Ự��Դ�������ϴ�
int CHYPrivateService::ProcessPauseEvent(int nSessionId, void *pParam)
{
    if (nSessionId <= 0)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    IRtspStream *pStream = NULL;
    nRet  = TSingletons<CGlobalObject>::Instance().RtspSessionMan().GetStream(nSessionId, &pStream);

    if (RET_SUCCESS != nRet || NULL == pStream)
    {
        return RET_FAIL;
    }

    nRet = pStream->Pause();

    if (RET_SUCCESS != nRet)
    {
        return RET_FAIL;
    }

    return RET_SUCCESS;
}

//\\ ָֹͣ��RTSP�Ự��Դ�������ϴ�
int CHYPrivateService::ProcessStopEvent(int nSessionId, void *pParam)
{
    if (nSessionId <= 0)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    IRtspStream *pStream = NULL;
    nRet  = TSingletons<CGlobalObject>::Instance().RtspSessionMan().GetStream(nSessionId, &pStream);

    if (RET_SUCCESS != nRet || NULL == pStream)
    {
        return RET_FAIL;
    }

    nRet = pStream->StopCapture();

    if (RET_SUCCESS != nRet)
    {
        return RET_FAIL;
    }

    return RET_SUCCESS;
}

//\\ ����RTSP�Ự��Դ���ֹͣ���ͷ�ָ����RTSP�Ự��Դ�����ͷ�ָ����RTSP�Ự
int CHYPrivateService::ProcessRemoveSessionEvent(int nSessionId, void *pParam)
{
    if (nSessionId <= 0)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    IRtspStream *pStream = NULL;
    nRet  = TSingletons<CGlobalObject>::Instance().RtspSessionMan().GetStream(nSessionId, &pStream);

    if (RET_SUCCESS != nRet || NULL == pStream)
    {
        return RET_SUCCESS;
    }
    else
    {
        nRet = pStream->StopCapture();
        nRet = pStream->Stop();
        nRet = pStream->Destroy();
    }

    nRet = TSingletons<CGlobalObject>::Instance().RtspSessionMan().RemoveSessionId(nSessionId);
    nRet = RTSPSessionDestroy(nSessionId);
    return RET_SUCCESS;
}

//\\ ����RTSP�Ự��Դ���ֹͣ���ͷ�ָ����RTSP�Ự��Դ
int CHYPrivateService::ProcessRemoveSessionEventByStop(int nSessionId, void *pParam)
{
    if (nSessionId <= 0)
    {
        return RET_FAIL;
    }

    int nRet = RET_SUCCESS;
    IRtspStream *pStream = NULL;
    nRet  = TSingletons<CGlobalObject>::Instance().RtspSessionMan().GetStream(nSessionId, &pStream);

    if (RET_SUCCESS != nRet || NULL == pStream)
    {
        return RET_SUCCESS;
    }
    else
    {
        nRet = pStream->StopCapture();
        nRet = pStream->Stop();
        nRet = pStream->Destroy();
    }

    nRet = TSingletons<CGlobalObject>::Instance().RtspSessionMan().RemoveSessionId(nSessionId);
    return RET_SUCCESS;
}




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

// 初始化rtsp静态参数
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

    // 实时流管理器初始化，支持4/16个实时流管理器
    if (RET_CHECK_FAIL(TSingletons<CGlobalObject>::Instance().RealStreamMan().Initialize()))
        goto FAILED_0;

    RTSP_SER_PD("[FILE=%s][FUN=%s][LINE=%d] Enter --- \n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;

    // RTSP 会话管理器初始化，支持4/16个RTSP会话管理器
    nRet = TSingletons<CGlobalObject>::Instance().RtspSessionMan().Initialize();
    if(RET_CHECK_FAIL(nRet))
        goto FAILED_0;

    RTSP_SER_PD("[FILE=%s][FUN=%s][LINE=%d] Enter --- \n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;

    // 私有函数，通过上层回调获取本地的RTSP 端口
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


    //\\ 停止销毁器.
    if (RET_CHECK_FAIL(TSingletons<CGlobalObject>::Instance().Destroyer().Stop()))
    {
        RTSP_SER_PE(" fail !\n");
    }

    //\\ 停止RTSP服务器.
    INT32 nRet = RTP_RTSP_OK;
    nRet = RTSPServerShutdown(TSingletons<CGlobalObject>::Instance().RtspServerHandle());
    if(RET_CHECK_FAIL(nRet))
    {
        RTSP_SER_PE(" fail , nRet=[%d]\n", nRet);
    }

    //\\ 释放RTSP会话资源管理器.
    nRet = TSingletons<CGlobalObject>::Instance().RtspSessionMan().Destroy();
    if(RET_CHECK_FAIL(nRet))
    {
        RTSP_SER_PE(" fail !\n");
    }

    //\\ 释放实时流会话资源管理器.
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


//\\ 初始化用户ID
int CHYPrivateService::Login()
{
    //\\ 私有函数
    TSingletons<CGlobalObject>::Instance().UserID() = (DWORD)VALUE_INVALID;
    return RET_SUCCESS;
}

//\\ 初始化用户ID
int CHYPrivateService::Logout()
{
    TSingletons<CGlobalObject>::Instance().UserID() = (DWORD)VALUE_INVALID;
    return RET_SUCCESS;
}

//\\ 获取版本信息
int CHYPrivateService::GetVersion(char *&version)
{
    version = g_cVersion;
    return RET_SUCCESS;
}

/*
* @brief
*   初始化
* @return
*   返回0表示成功, 否则表示错误码
* @note
*   接口类型: 阻塞式
*/
int CHYPrivateService::Initialize()
{
    m_nStatus = 0;
    m_iStatus = 0 ;
    return RET_SUCCESS;
}

/*
* @brief
*   销毁
* @return
*   返回0表示成功, 否则表示错误码
* @note
*   接口类型: 阻塞式
*/
int CHYPrivateService::Destroy()
{
    m_nStatus = 0;
    m_iStatus = 0 ;
    return RET_SUCCESS;
}

// 私有函数，通过上层回调获取本地的RTSP 端口
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

//\\ 添加RTSP会话回调函数: 创建RTSP会话结构添加到RTSP服务器管理链表中，内部分配RTSP会话资源、实时流会话资源，通过回调启动上层编码，等待SDP信息后将视频流与音频流类型添加到该会话结构支持的流列表中
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
    SupportedCodecs eSupportCodecs = INVALID_CODEC; // 编码类型
    int nClockRate = 0;                             // 时钟频率
    int nNumberOfChannel = 0;                       // 通道数，only in audio
    int nErrorCode = RET_OK;
    int nFileEndTime = 0;
    //\\ 创建RTSP会话结构添加到RTSP服务管理链表中，设置会话客户连接回调函数ClientConnectionCB，RTSP事件回调函数RtspStreamEventCB
    INT32 hSession = RTSPSessionCreate(hRtspServer, (BYTE *)(pSessionParam->acSessionName), (BYTE *)NULL, 0, UDP_MTU_SIZE, TCP_MTU_SIZE, nEnalbleRTCP,
                                       nRtcpSRInterval, &nErrorCode, ClientConnectionCB, RtspStreamEventCB, nFileEndTime);

    if (RTP_RTSP_ERROR == hSession || hSession <= 0 || nErrorCode < 0)
    {
        return RET_FAIL;
    }

    //\\ 获取可用的RTSP会话资源与实时流会话资源，保存会话结构与流信息与实时流会话资源等信息到RTSP会话资源中
    int nRet = TSingletons<CGlobalObject>::Instance().RtspSessionMan().AddSessionId(hSession, pSessionParam->eStreamType);

    if (RET_SUCCESS != nRet)
    {
        goto FAILED0;
    }

    //\\ 获取实时流会话资源访问句柄
    nRet  = TSingletons<CGlobalObject>::Instance().RtspSessionMan().GetStream(hSession, &pStream);

    if (RET_SUCCESS != nRet || NULL == pStream)
    {
        goto FAILED1;
    }

    //\\ 保存RTSP会话结构与相关信息，启动实时流发送器，初始化RTSP流发生器
    nRet = pStream->Initialize(hSession, pSessionParam->nChannel, pSessionParam->acBeginTime, pSessionParam->acEndTime, pSessionParam->eCodeType);

    if (RET_SUCCESS != nRet)
    {
        goto FAILED1;
    }

    //\\ 调用系统回调，启动上层的实时流编码
    nRet = pStream->Start();

    if (RET_SUCCESS != nRet)
    {
        goto FAILED2;
    }

    //\\ 获取当前音视频编码标准
    nRet = pStream->GetCodecType(eVideoCodec, eAudioCodec);

    if (RET_SUCCESS != nRet || eVideoCodec <= eRtspVideoCodecTypeBegin || eVideoCodec >= eRtspVideoCodecTypeEnd || eAudioCodec <= eRtspAudioCodecTypeBegin || eAudioCodec >= eRtspAudioCodecTypeEnd)
    {
        goto FAILED3;
    }

    // 添加视频流到会话中
    eSupportCodecs  = INVALID_CODEC;
    nClockRate      = VIDEO_CLOCK_RATE;
    nNumberOfChannel  = 0;

    if (eRtspVideoCodecH264 == eVideoCodec)
    {
        eSupportCodecs = CODEC_H264;
    }
	else if(eRtspVideoCodecH265 == eVideoCodec)/*cb change 2016.8.5 .添加h265的支持*/ 
	{
		eSupportCodecs = CODEC_H265;
	}


    if (INVALID_CODEC != eSupportCodecs)
    {
        //\\ 等待上层编码数据获取SPS与PPS信息
        char    acSDPInfo[MAX_SDP_LEN] = {0};
        int         nSDPLen = MAX_SDP_LEN;
        nRet = pStream->GetSDPInfo(acSDPInfo, nSDPLen);

        if (RET_SUCCESS != nRet)
        {
            goto FAILED3;
        }

        //\\ 更新指定RTSP会话结构支持的流链表，添加对H264视频流支持
        nRet = RTSPAddStreamToSession(hSession, eSupportCodecs, 1, nClockRate, nNumberOfChannel, nSDPLen, (BYTE *)acSDPInfo, nRtspMulticastPort);

        if (RET_SUCCESS != nRet)
        {
            goto FAILED3;
        }
    }

    // 添加音频流到会话中
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

        // note: 注意G726的时钟频率，这里不是填8000, 实际上填的是比特率
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

    //\\ 更新指定RTSP会话结构支持的流链表，添加对G726音频流支持
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


//\\ RTSP流事件回调函数，执行对应的RTSP会话资源操作
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

//\\ 空函数
INT32 CHYPrivateService::ClientConnectionCB(INT32 nConnectFlag, BYTE *sessionName)
{
    if (NULL == sessionName)
    {
        return RET_FAIL;
    }

    return RET_SUCCESS;
}

//\\ 在指定RTSP会话资源中添加客户信息以及连接主从码流信息
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

//\\ 删除指定RTSP会话资源中指定客户信息
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

//\\ 启动指定RTSP会话资源的数据上传
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

//\\ 暂停指定RTSP会话资源的数据上传
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

//\\ 停止指定RTSP会话资源的数据上传
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

//\\ 根据RTSP会话资源编号停止并释放指定的RTSP会话资源，并释放指定的RTSP会话
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

//\\ 根据RTSP会话资源编号停止并释放指定的RTSP会话资源
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




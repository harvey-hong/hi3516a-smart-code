/*******************************************************************************
 * Copyright (c) 2007 eInfochips - All rights reserved.
 *
 * This software is authored by eInfochips and is eInfochips' intellectual
 * property, including the copyrights in all countries in the world.
 * This software is provided under a license to use only with all other rights,
 * including ownership rights, being retained by eInfochips.
 *
 * This file may not be distributed, copied, or reproduced in any manner,
 * electronic or otherwise, without the written consent of eInfochips.
 ******************************************************************************/

/*******************************************************************************
 *
 * File Name    :   RTSPServerInternal.c
 *
 * Description  :   This file contain the API implementation of RTSP protocol
 *
 * History:
 *  JUN/22/2007, UBV,   Created the file.
 *  JUN/25/2007, UBV,   Modified return value of APIs now it will return Error
 *                      codes.
 *  DEC/27/2007, ARJ,   Separated API and Internal functions in different files
 *  DEC/28/2007, ARJ,   RTP over TCP Feature Added
 *  MAY/07/2009, ARJ,   Modified few changes for RTSP over HTTP
 ******************************************************************************/

/****************
 * Include Files
 ****************/
#include "../inc/GlobalObject.h"
#include "../inc/RtspServer.h"
#include "../inc/RtpRtspCommon.h"
#include "../inc/DbgPrint.h"
#include "../inc/RtspUriParser.h"
#include "../inc/UserAuthorization.h"
#include "../inc/UserRightCheck.h"
#include "h265_decoder.h"/*cb change 2016.8.5 .添加h265的支持*/ 

#include "ws_comm_type.h"
#include "ws_model_api.h"
#include <fcntl.h>
using namespace ws_soft;
using namespace ApplicationLayer;

// 模拟手机监控上屏蔽用户登录
#define USRNOTINPUT

/*********************
 * Defines and Macros
 *********************/
#define MAX_REASON_ARR_SIZE         44           /* Response reason array size*/

#define HYRTSP_REALM                "higheasy"   /* realm macros              */

#define BASIC_AUTHEN                          // Basic 认证
/****************
 * Globals
 ****************/

#ifdef ENABLE_DBG_LEVEL
UINT32 gAppDbgLevel = ENABLE_DBG_LEVEL;
#else
UINT32 gAppDbgLevel = 0;
#endif

#ifndef TCP_USER_TIMEOUT
#define TCP_USER_TIMEOUT 18
#endif


extern RTSPServer *gblRtspServer;

/* Global RTP Server Send Port                                                */
UINT16 gblRtpPort = 2000;

/* Global Variable containing Status Code and Reason Phrase value             */
RTSPStatusReason StatusReasonPhrase[MAX_REASON_ARR_SIZE] =
{
    {0, ""},
    {100, "Continue"},                                     /* 100     */

    {200, "OK"},                                           /* 200     */
    {201, "Created"},                                      /* 201     */
    {250, "Low on Storage Space"},                         /* 250     */

    {300, "Multiple Choices"},                             /* 300     */
    {301, "Moved Permanently"},                            /* 301     */
    {302, "Moved Temporarily"},                            /* 302     */
    {303, "See Other"},                                    /* 303     */
    {305, "Use Proxy"},                                    /* 305     */

    {400, "Bad Request"},                                  /* 400     */
    {401, "Unauthorized"},                                 /* 401     */
    {402, "Payment Required"},                             /* 402     */
    {403, "Forbidden"},                                    /* 403     */
    {404, "Not Found"},                                    /* 404     */
    {405, "Method Not Allowed"},                           /* 405     */
    {406, "Not Acceptable"},                               /* 406     */
    {407, "Proxy Authentication Required"},                /* 407     */
    {408, "Request Time-out"},                             /* 408     */
    {410, "Gone"},                                         /* 410     */

    {411, "Length Required"},                              /* 411     */
    {412, "Precondition Failed"},                          /* 412     */
    {413, "Request Entity Too Large"},                     /* 413     */
    {414, "Request-URI Too Large"},                        /* 414     */
    {415, "Unsupported Media Type"},                       /* 415     */

    {451, "Parameter Not Understood"},                     /* 451     */
    {452, "Conference Not Found"},                         /* 452     */
    {453, "Not Enough Bandwidth"},                         /* 453     */
    {454, "Session Not Found"},                            /* 454     */
    {455, "Method Not Valid in this State"},               /* 455     */
    {456, "Header Field Not Valid For Resource"},          /* 456     */
    {457, "Invalid Range"},                                /* 457     */
    {458, "Parameter Is Read-Only"},                       /* 458     */
    {459, "Aggregate Option Not Allowed"},                 /* 459     */
    {460, "Only Aggregate Option Allowed"},                /* 460     */
    {461, "Unsupported Transport"},                        /* 461     */
    {462, "Destination Unreachable"},                      /* 462     */

    {500, "Internal Server Error"},                        /* 500     */
    {501, "Not Implemented"},                              /* 501     */
    {502, "Bad Gateway"},                                  /* 502     */
    {503, "Service Unavailable"},                          /* 503     */
    {504, "Gateway Timeout"},                              /* 504     */
    {505, "RTSP Version not supported"},                   /* 505     */
    {551, "Option Not Supported"},                         /* 551     */
};

/* Character set used for NAL header parsing                                  */
static const BYTE NALCharSet[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// 为每个连接的客户端启动工作线程: RTSPSessionThread
INT32 RTSPServerThreadFunc(RTSPServer *RtspServer)
{
    INT32                       retVal;             /* Store return value of func call    */
    INT32                       clientSocketAddrLen;/* Store the socket addr struct length*/
    SOCKET                    clientSocket;       /* Accepted client connection Socket  */
    RTSPClient                 *clientConn;        /* RTSP connection structure pointer  */
    SOCKETADDR_IN       clientSocketAddr;   /* Socket add struct  */
    char IpAddress[16];
    clientSocketAddrLen = sizeof(clientSocketAddr);

    int maxfd;  
    int nready;  
    fd_set rset, allset;        //select所需的文件描述符集合
    timeval tmOut;

    while (1)
    {
        memset(&tmOut, 0, sizeof(tmOut));
        tmOut.tv_sec= 1;
        tmOut.tv_usec= 0;
        maxfd = RtspServer->ServerSocket;

        FD_ZERO(&allset);
        FD_SET(maxfd, &allset);

        rset = allset;  
        nready = select(maxfd + 1, &rset, NULL, NULL, &tmOut);
        if (nready <= 0  || (!(FD_ISSET(maxfd, &rset))))
        {
            continue;
        }

        // 接受客户端连接...
        clientSocket = accept(RtspServer->ServerSocket, (struct sockaddr *) & (clientSocketAddr), (socklen_t *)&clientSocketAddrLen);
        if (clientSocket == INVALID_SOCKET)
        {
            ThreadExit(RtspServer->ServerThreadID);
            return RET_ERROR;
        }

        //获取对方的地址...
        if (getpeername(clientSocket, (struct sockaddr *)&clientSocketAddr, (socklen_t *)&clientSocketAddrLen) != 0)
        {
            CloseServerSock(clientSocket);
            continue;
        }

        const DWORD system_keepalive_time   = 5;
        const DWORD system_keepalive_interval   = 5;
        const DWORD system_keepalive_count  = 3;
        int             system_keepAlive            = 1;                            //设定KeepAlive
        int             system_keepIdle         = system_keepalive_time;        //开始首次KeepAlive探测前的TCP空闲时间
        int             system_keepInterval     = system_keepalive_interval;    //两次KeepAlive探测间的时间间隔
        int             system_keepCount        = system_keepalive_count;       //判定断开前的KeepAlive探测次数
        struct linger so_linger;
        so_linger.l_onoff = 1;
        so_linger.l_linger = 0;
        ::setsockopt(clientSocket, SOL_SOCKET, SO_KEEPALIVE, (void *)&system_keepAlive, sizeof(system_keepAlive));
        ::setsockopt(clientSocket, SOL_TCP, TCP_KEEPIDLE, (void *)&system_keepIdle, sizeof(system_keepIdle));
        ::setsockopt(clientSocket, SOL_TCP, TCP_KEEPINTVL, (void *)&system_keepInterval, sizeof(system_keepInterval));
        ::setsockopt(clientSocket, SOL_TCP, TCP_KEEPCNT, (void *)&system_keepCount, sizeof(system_keepCount));
        int flags = fcntl(clientSocket, F_GETFL, 0);
        fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
        ::setsockopt(clientSocket, SOL_TCP, SO_LINGER, &so_linger, sizeof(so_linger));
        clientConn = (RTSPClient *) malloc(sizeof(RTSPClient));

        if (clientConn == NULL)
        {
            CloseServerSock(clientSocket);
            continue;
        }

        memset(clientConn, 0x00, sizeof(RTSPClient));
        clientConn->ClientState                     = CLIENT_INIT_STATE;
        clientConn->ClientSocket                    = clientSocket;
        clientConn->RtspServerPtr                   = RtspServer;
        clientConn->NextClient                      = NULL;
        clientConn->PrevClient                      = NULL;
        clientConn->IsFirstFrame            = 1;
        strcpy((INT8 *)clientConn->ClientIp, inet_ntoa(clientSocketAddr.sin_addr));
        clientConn->ClientPort = ntohs(clientSocketAddr.sin_port);
        // 为每个客户启动工作线程RTSPSessionThread
        retVal = ThreadCreate(&(clientConn->ClientThreadID), (THREAD_FUNC) RTSPSessionThread, clientConn);
        if (retVal != RET_OK)
        {
            free(clientConn);
            clientConn = NULL;
            CloseServerSock(clientSocket);
            continue;
        }

        if (MutexInit(&(clientConn->RTSPClientSendmsgLock)) != RET_OK)
        {
            free(clientConn);
            clientConn = NULL;
            CloseServerSock(clientSocket);
            continue;
        }
    }

    ThreadExit(RtspServer->ServerThreadID);
    return RET_OK;
}

/*******************************************************************************
 * Function:    RTSPSessionThread
 *
 * Description: This is RTSP session thread which will receive RTSP request and
 *              parse it, generate appropriate response and send it back to
 *              client.
 *
 * Parameters:
 *      [IN]    RTSPClient *clientConn - RTSP connection struct pointer
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - successful
 *          RET_ERROR - Error
 ******************************************************************************/

// 构造并发送回复消息
static INT32 ComposeAndSendRespose(RTSPClient *ClientConn, INT32 nCode, ApplicationLayer::CUserAuthorization *userAuthorization = NULL)
{
    // userAuthorization可以为NULL，表示不需要认证相关信息
    if (NULL == ClientConn || nCode < 0)
    {
        return RET_ERROR;
    }

    /* Generate Response specified by nCode and send to client     */
    if (RTSPGenerateMethodResponse(ClientConn, nCode) == RET_ERROR)
    {
        RtpRtspErrorPrint("Cannot generate OK response\n");
    }

    /* Copy "CSeq" Header to Response from Request            */
    if (CopyResponseHeader(ClientConn->ClientRtspResMsg, ClientConn->ClientRtspReqMsg, (BYTE *)"CSeq") == RET_ERROR)
    {
        RtpRtspErrorPrint("Error in copying CSeq Header \n");
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Server", (BYTE *)RTSP_SERVER_NAME) == RET_ERROR)
    {
        RtpRtspErrorPrint("Error in Adding Server Header \n");
    }

#ifdef BASIC_AUTHEN

    if (401 == nCode)
    {
        OUTC_SIMPLE_STRING("Authenticate Failed");
#else

    if (401 == nCode && NULL != userAuthorization)
    {
#endif
        char acAuthenChalleng[128] = {0};
#ifdef BASIC_AUTHEN
        // basic认证
        sprintf(acAuthenChalleng, "Basic realm=\"/\"");
#else
        // digest认证
        userAuthorization.m_digestAuthen.SetRealmAndRandomNonce(HYRTSP_REALM);
        sprintf(acAuthenChalleng, "Digest realm=\"%s\",nonce=\"%s\"", userAuthorization.m_digestAuthen.GetRealm(),
                userAuthorization.m_digestAuthen.GetNonce());
#endif

        if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"WWW-Authenticate", (BYTE *)acAuthenChalleng) == RET_ERROR)
        {
            RtpRtspErrorPrint("Error in Adding Server Header \n");
        }
    }

    /* Send generated response to client                  */
    if (RTSPServerSendResponse(ClientConn) == RET_ERROR)
    {
        RtpRtspErrorPrint("Can not send generated RTSP response.\n");
    }

    /* Free the response msg memory                               */
    FreeResponseMsg(ClientConn->ClientRtspResMsg);
    ClientConn->ClientRtspResMsg = NULL;
    return RET_OK;
}

//\\ 根据RTSP请求包中首部结构与URI信息进行授权认证
static INT32 RTSPUserAuthorization(RTSPClient *ClientConn, CRtspUriParser *pRtspUriParser)
{
    CUserAuthorization      userAuthorization;          /* user authorization object          */
    RemoteUserInfo          clientUserInfo;
    const char             *pUserName = NULL;                                   /* Store the user name                */
    const char             *pPassword = NULL;                                   /* Store the password                 */
    int nRet = RET_OK;
    pUserName = pRtspUriParser->GetUserName();
    pPassword = pRtspUriParser->GetPassword();
    bool    bFlag = false;
    int         index;

    //判断RTSP请求包中是否有用户名和密码
    for (index = 0; index < ClientConn->ClientRtspReqMsg->ReqHeadersCount; index++)
    {
        if (!strcmp((char *)ClientConn->ClientRtspReqMsg->ReqMsgHeaders[index].HeaderName, "Authorization"))
        {
            bFlag   = true;
            break;
        }
    }

    //\\ 设置用户名、密码、认证信息
    if (0 != strlen(pUserName))
    {
        if (bFlag)
        {
            userAuthorization.SetParameter(pUserName, pPassword, (char *)ClientConn->ClientRtspReqMsg->ReqMsgHeaders[index].HeaderValue);
        }
        else
        {
            userAuthorization.SetParameter(pUserName, pPassword, "");
        }
    }
    else
    {
        if (bFlag)
        {
            userAuthorization.SetParameter("", "", (char *)ClientConn->ClientRtspReqMsg->ReqMsgHeaders[index].HeaderValue);
        }
    }

    //获取用户登录的用户名和密码
    nRet = userAuthorization.Authorize();

    if (AUTHORIZE_FAIL == nRet)
    {
        ComposeAndSendRespose(ClientConn, 401);
        return RET_ERROR;
    }
    else if (AUTHORIZE_NONE == nRet)
    {
        ComposeAndSendRespose(ClientConn, 401, &userAuthorization);
        return RET_ERROR;
    }
    else
    {
        return RET_OK;
    }

#if 0
    //\\ 回调函数用户登录，并做权限检查(但是代码应该进不来)
    memset(&clientUserInfo, 0, sizeof(clientUserInfo));
    strncpy(clientUserInfo.sUserName, userAuthorization.GetUserName(), USERNAME_LEN - 1);
    strncpy(clientUserInfo.sUserPass, userAuthorization.GetUserPasswd(), USERPASS_LEN - 1);
    strncpy(clientUserInfo.sUserIPAddress, (char *)ClientConn->ClientIp, IP_ADDRESS_LEN - 1);
    strcpy(clientUserInfo.sClientMACAddress, "00:00:35:07:00:2b");
    //if(RET_CHECK_FAIL(TSingletons<CGlobalObject>::Instance().PrivateUserActionInterface().Login(&(ApplicationLayer::TSingletons<CGlobalObject>::Instance().UserID()), &clientUserInfo)))
    //return AUTHORIZE_FAIL;//这里移到nvr上需要修改
    //验证用户名和密码
    WS_USR_HAND  hand;
    int ret = ws_soft::model_remote_login((const WS_CHAR *)&clientUserInfo.sUserName, (const char *)&clientUserInfo.sUserPass, (const char *)&clientUserInfo.sUserIPAddress, (const char *)&clientUserInfo.sClientMACAddress, &hand);
    if (AUTHORIZE_FAIL == ret)
    {
        ComposeAndSendRespose(ClientConn, 401);
        return RET_ERROR;
    }
    else if (AUTHORIZE_NONE == ret)
    {
        ComposeAndSendRespose(ClientConn, 401, &userAuthorization);
        return RET_ERROR;
    }
    else
    {
        ws_soft::model_logout(hand);
        return RET_OK;
    }

    // 认证成功后，还需要检查用户是否具有预览/回放的权限
    char *pUserNameRight = userAuthorization.GetUserName();

    if (NULL != pUserNameRight && strlen(pUserNameRight) > 0)
    {
        eRtspStreamType eStreamType = eRtspStreamTypeBegin;
        pRtspUriParser->GetRtspStreamType(eStreamType);
        int nChannel = -1;
        pRtspUriParser->GetChannel(nChannel);
        CUserRightCheck     cRightCheck;
        nRet = cRightCheck.RightCheck(pUserNameRight, eStreamType, nChannel);

        if (RET_SUCCESS == nRet)
        {
            return RET_OK;
        }
    }

    ComposeAndSendRespose(ClientConn, 401);
    return RET_ERROR;
#endif
}

#define RTSPSessionThread_FREERECEIVEBUFF()                                     \
    if(recvRTSPBuff)                                                                    \
    {                                                                               \
        if (recvRTSPBuff->DataBuff)                                                     \
        {                                                                           \
            free (recvRTSPBuff->DataBuff);                                              \
            recvRTSPBuff->DataBuff = NULL;                                              \
        }                                                                           \
        free (recvRTSPBuff);                                                            \
        recvRTSPBuff = NULL;                                                            \
    }                                                                               \
    FreeRequestMsg(ClientConn->ClientRtspReqMsg);                                       \
    ClientConn->ClientRtspReqMsg = NULL;

#define RTSPSessionThread_FREERECEIVEBUFF_EX()                                  \
    if(recvRTSPBuff)                                                                    \
    {                                                                               \
        if (recvRTSPBuff->DataBuff)                                                     \
        {                                                                           \
            free (recvRTSPBuff->DataBuff);                                              \
            recvRTSPBuff->DataBuff = NULL;                                              \
        }                                                                           \
        free (recvRTSPBuff);                                                            \
        recvRTSPBuff = NULL;                                                            \
    }


//\\ 客户句柄工作线程:  循环接收RTSP方法请求，对OPTION不做处理，在DESCRIBE时建立各种资源分配与RTSP会话启动，对除OPTION外的方法做回调处理
INT32 RTSPSessionThread(RTSPClient *ClientConn)
{
    INT32                   retVal;                         /* Return Value of Function           */
    INT32                   rtcpFound = 0;              /* Flag for RTCP Packet found         */
    INT32                   index;                          /* Loop counter                       */
    RTSPBuff                *recvRTSPBuff;              /* Received RTSP buffer pointer       */
    RTSPClient              *clientConnTemp;            /* Temporary Client Conn pointer      */
    RTSPSession         *rtspSession = NULL;        /* Found RTSP Session pointer         */
    RTPClientStream     *tmpRtpStreamData;          /* Temporary RTPClientStream          */
    THREAD_HANDLE   threadId;                       /* Variable to store Thread Id        */
    RTSPRequestMsg    *reqMsg;                      /* Request Message Pointer            */
    threadId = ClientConn->ClientThreadID;

    while (1)
    {
        //接收RTSP数据包
        recvRTSPBuff = RTSPServerReadMessage(ClientConn->ClientSocket);

        if (recvRTSPBuff == NULL)
        {
#if 0

            if (errno == 0)
            {
                RTSP_SER_PE("\n [FUN=%s] [LINE=%d] 接收客户数据缓冲区异常error = 0  ，重新获取数据\n" , __FUNCTION__ , __LINE__) ;
                continue ;
            }

#endif
            //销毁RTSP连接
            retVal = RTSPConnectionDestroyPassive(ClientConn);
            // 这里保证了当客户端异常断开时，资源也能正确被销毁
            retVal = RTSPConnectionDestroy(ClientConn);

            if (retVal == RET_ERROR)
            {
                RtpRtspErrorPrint("RTSPConnectionDestroy() failed !! \n");
            }

            break;
        }

        // 接收到RTSP 异常的协商命令
        if (!(strstr((INT8 *)recvRTSPBuff->DataBuff, "OPTIONS")           ||
              strstr((INT8 *)recvRTSPBuff->DataBuff, "DESCRIBE")            ||
              strstr((INT8 *)recvRTSPBuff->DataBuff, "SETUP")           ||
              strstr((INT8 *)recvRTSPBuff->DataBuff, "PLAY")                ||
              strstr((INT8 *)recvRTSPBuff->DataBuff, "PAUSE")           ||
              strstr((INT8 *)recvRTSPBuff->DataBuff, "TEARDOWN")        ||
              strstr((INT8 *)recvRTSPBuff->DataBuff, "GET_PARAMETER")   ||
              strstr((INT8 *)recvRTSPBuff->DataBuff, "SET_PARAMETER")   ||
              strstr((INT8 *)recvRTSPBuff->DataBuff, "ANNOUNCE")        ||
              strstr((INT8 *)recvRTSPBuff->DataBuff, "REDIRECT")            ||
              strstr((INT8 *)recvRTSPBuff->DataBuff, "RECORD")))
        {
            if (*((INT8 *)recvRTSPBuff->DataBuff) == '$')
            {
                rtcpFound           = 0;
                tmpRtpStreamData    = ClientConn->ClientStreamList;

                while (tmpRtpStreamData)
                {
                    if ((tmpRtpStreamData->ClientPort + 1) == (*(recvRTSPBuff->DataBuff + 1)))
                    {
                        rtcpFound = 1;
                        break;
                    }

                    tmpRtpStreamData = tmpRtpStreamData->Next;
                }

                //\\ 接收到RTCP数据包的处理
                if (tmpRtpStreamData != NULL)
                {
                    if (rtcpFound  && tmpRtpStreamData->rtcpSessionInfo)
                    {
                        recvRTSPBuff->DataBuffLen = 0;
                        recvRTSPBuff->DataBuffLen = recvRTSPBuff->DataBuff[2];
                        recvRTSPBuff->DataBuffLen = recvRTSPBuff->DataBuffLen << 8;
                        recvRTSPBuff->DataBuffLen |= recvRTSPBuff->DataBuff[3];

                        if (AddNewPacket(tmpRtpStreamData->rtcpSessionInfo, (recvRTSPBuff->DataBuff + 4), (recvRTSPBuff->DataBuffLen) != 0))
                        {
                            //ht 2016.2.16
                            RTSP_SER_PE("\n [FUN=%s] [LINE=%d] 接收到RTCP 处理失败  \n" , __FUNCTION__ , __LINE__ ) ;
                        }
                    }
                }

                free(recvRTSPBuff->DataBuff);
                free(recvRTSPBuff);
                continue;
            }
            else
            {
                if (recvRTSPBuff->DataBuff)
                {
                    free(recvRTSPBuff->DataBuff);
                }

                if (recvRTSPBuff)
                {
                    free(recvRTSPBuff);
                }

                continue;
            }
        }

        //\\ 首先获取OPTION,然后获取DESCRIBE，再获取SETUP，最后获取PLAY
        if ((recvRTSPBuff->DataBuffLen > 0) && (recvRTSPBuff->DataBuff != NULL))
        {
            //解析RTSP请求
            reqMsg = RTSPServerParseMessage(recvRTSPBuff);

            if (reqMsg != NULL)
            {
                ClientConn->ClientRtspReqMsg = reqMsg;
                //检查RTSP请求是否正确
                retVal = CommonMsgValidation(ClientConn);

                if (retVal != RET_OK)
                {
                    ComposeAndSendRespose(ClientConn, (retVal == RET_ERROR) ? 400 : retVal);
                    RTSPSessionThread_FREERECEIVEBUFF();
                    continue;
                }

                ApplicationLayer::CRtspUriParser rtspUriParser;

                if ((NULL != strstr((INT8 *)recvRTSPBuff->DataBuff, "DESCRIBE")) ||
                    (NULL != strstr((INT8 *)recvRTSPBuff->DataBuff, "SETUP")) ||
                    (NULL != strstr((INT8 *)recvRTSPBuff->DataBuff, "PLAY")))
                {
                    // 从URI中解析出通道号、主码流或者子码流信息、实时流或者历史流信息(目前只能解析实时流，多通道时异常)
                    retVal = rtspUriParser.SetURI((char *)ClientConn->ClientRtspReqMsg->ReqMsgURI);

                    //#ifdef USRNOTINPUT

                    //#else
                    if ((eErrorUserName == retVal) || (RET_FAIL == retVal))
                    {
                        ComposeAndSendRespose(ClientConn, 401);
                        RTSPSessionThread_FREERECEIVEBUFF();
                        continue;
                    }

                    // 根据RTSP请求包中首部结构与URI信息进行授权认证
                    retVal = RTSPUserAuthorization(ClientConn, &rtspUriParser);

                    if (RET_OK != retVal)
                    {
                        RTSPSessionThread_FREERECEIVEBUFF();
                        continue;
                    }

                    //#endif
                }

                //\\ 首先对OPTIONS方法不做处理直接返回应答数据包，然后接收到DESCRIBE包执行下列代码，后续方法都不再执行
                if (ClientConn->RtspSessionPtr == NULL && (RET_SUCCESS == rtspUriParser.IsParamValid()))
                {
                    eRtspStreamType         rtspStreamType  = eRtspStreamReal;
                    int                     nChannel        = -1;
                    eRtspMediaCodeType  rtspCodeType    = eRtspMediaCodeTypeBegin;
                    rtspUriParser.GetRtspStreamType(rtspStreamType);                   //获取流类型
                    rtspUriParser.GetChannel(nChannel);                     //获取通道号
                    rtspUriParser.GetMediaCodeType(rtspCodeType);               //获取编码类型
                    char sessionName[MAX_SESSION_NAME_LEN] = {0};

                    if (eRtspStreamReal == rtspStreamType)
                    {
                        if (eRtspMediaCodeMain == rtspCodeType)
                        {
                            sprintf(sessionName, "RealChannel%02d_s0_%08p", nChannel, ClientConn);
                        }
                        else if (eRtspMediaCodeSub1 == rtspCodeType)
                        {
                            sprintf(sessionName, "RealChannel%02d_s1_%08p", nChannel, ClientConn);
                        }
                    }

                    //\\  创建RTSP会话结构添加到RTSP服务器管理链表中，内部分配RTSP会话资源、实时流会话资源，通过回调启动上层编码，等待SDP信息后将视频流与音频流类型添加到该会话结构支持的流列表中
                    rtspSession = FindRTSPSession(ClientConn->RtspServerPtr, (BYTE *)sessionName);

                    if (rtspSession == NULL && sessionName != NULL)
                    {
                        if (ClientConn->RtspServerPtr->AddSession_Callback != NULL)
                        {
                            AddSessionParam         cSessionParam;
                            memset(&cSessionParam, 0, sizeof(AddSessionParam));
                            cSessionParam.nChannel      = nChannel;
                            cSessionParam.eStreamType       = rtspStreamType;
                            cSessionParam.eCodeType         = rtspCodeType;
                            memmove(cSessionParam.acBeginTime, rtspUriParser.GetHistoryStartTime(), DATE_TIME_LEN);
                            memmove(cSessionParam.acEndTime, rtspUriParser.GetHistoryEndTime(), DATE_TIME_LEN);
                            memmove(cSessionParam.acSessionName, sessionName, MAX_SESSION_NAME_LEN);
                            //调用AddSessionCB函数!
                            retVal = ClientConn->RtspServerPtr->AddSession_Callback((INT32)ClientConn, 0, FS_ADD_SESS, (void *)&cSessionParam);

                            if (RET_OK == retVal)
                            {
                                rtspSession = FindRTSPSession(ClientConn->RtspServerPtr, (BYTE *)sessionName);
                            }
                        }
                    }

                    if (rtspSession == NULL)
                    {
                        ComposeAndSendRespose(ClientConn, 454);
                        RTSPSessionThread_FREERECEIVEBUFF();
                        continue;
                    }

                    ClientConn->RtspSessionPtr  = rtspSession;

                    if (ClientConn->RtspSessionPtr->ClientConnectionCallback)
                    {
                        retVal = ClientConn->RtspSessionPtr->ClientConnectionCallback(1, (BYTE *)rtspSession->SessionName);

                        if (RET_OK != retVal)
                        {
                            ComposeAndSendRespose(ClientConn, 453);
                            RTSPSessionThread_FREERECEIVEBUFF();
                            free(ClientConn);
                            ClientConn = NULL;
                            break;
                        }
                    }

                    //\\ 建立客户结构与RTSP会话结构的交叉索引关系
                    clientConnTemp = rtspSession->SessionConnectedClientList;

                    if (clientConnTemp == NULL)
                    {
                        rtspSession->SessionConnectedClientCount++;
                        rtspSession->SessionConnectedClientList = ClientConn;
                    }
                    else
                    {
                        if (MutexLock(&(ClientConn->RtspSessionPtr->SessionClientListLock)) != RET_OK)
                        {
                            RTSPSessionThread_FREERECEIVEBUFF();
                            continue;
                        }

                        while (clientConnTemp)
                        {
                            if (clientConnTemp == ClientConn)
                            {
                                break;
                            }
                            else if (clientConnTemp->NextClient != NULL)
                            {
                                clientConnTemp = clientConnTemp->NextClient;
                            }
                            else
                            {
                                rtspSession->SessionConnectedClientCount++;
                                clientConnTemp->NextClient = ClientConn;
                                ClientConn->PrevClient = clientConnTemp;
                                break;
                            }
                        }

                        if (MutexUnlock(&(ClientConn->RtspSessionPtr->SessionClientListLock)) != RET_OK)
                        {
                            RTSPSessionThread_FREERECEIVEBUFF();
                            continue;
                        }
                    }

                    //\\ 调用对应的RTSP方法回调
                    if (ClientConn->RtspSessionPtr->RTPWriter_Callback != NULL)
                    {
                        //调用Rtsp Stream Event callback!
                        retVal = ClientConn->RtspSessionPtr->RTPWriter_Callback((INT32)ClientConn, (INT32)ClientConn->RtspSessionPtr, FS_START_CLIENT, (void *)&rtspCodeType);
                        ClientConn->FileStartTime = 0;
                    }
                } // end of if( ClientConn->RtspSessionPtr == NULL )

#if 0

                if ((ClientConn->ClientRtspReqMsg->ReqMethod == RTSP_METHOD_OPTIONS) ||
                    (ClientConn->ClientRtspReqMsg->ReqMethod == RTSP_METHOD_TEARDOWN))
                {
                    MutexLock(&(ClientConn->RTSPClientSendmsgLock));
                }

#endif
                // 创建指定方法的应答包，发送
                retVal = RTSPServerProcessMessage(ClientConn, 0);

                if (retVal != RET_OK)
                {
                    ComposeAndSendRespose(ClientConn, (retVal == RET_ERROR) ? 400 : retVal);
                    RTSPSessionThread_FREERECEIVEBUFF();
                    //                                  MutexUnlock(&(ClientConn->RTSPClientSendmsgLock));
                    continue;
                }
                if (RTSPServerSendResponse(ClientConn) == RET_ERROR)
                {
                    RtpRtspErrorPrint("Can not send generated RTSP response.\n");
                }
                //                           MutexUnlock(&(ClientConn->RTSPClientSendmsgLock));
                FreeRequestMsg(ClientConn->ClientRtspReqMsg);
                ClientConn->ClientRtspReqMsg    = NULL;
                FreeResponseMsg(ClientConn->ClientRtspResMsg);
                ClientConn->ClientRtspResMsg = NULL;
            }

            RTSPSessionThread_FREERECEIVEBUFF_EX();
        }
        else
        {
            RTSPSessionThread_FREERECEIVEBUFF_EX();
        }

        // TEARDOWN时会将客户端状态置为CLIENT_INVALID_STATE，所以这种情况下会调用RTSPConnectionDestroy，
        // 该函数会将连接的客户端数减1，当连接的客户端数为0时，在退出循环时就会调用回调移除相应会话
        if (ClientConn->ClientState == CLIENT_INVALID_STATE)
        {
            ThreadDetach(threadId);
            retVal = RTSPConnectionDestroy(ClientConn);

            if (retVal == RET_ERROR)
            {
                RtpRtspErrorPrint("Can not destroy the RTSP connection\n");
            }

            break;
        }
    } // end of while(1)

    if (rtspSession != NULL)
    {
        if (rtspSession->RTPWriter_Callback != NULL && rtspSession->SessionConnectedClientCount == 0)
        {
            //进入RTSP stream event callback !
            rtspSession->RTPWriter_Callback((INT32) NULL, (INT32)rtspSession, FS_REMOVE_SESS, (void *)NULL);
        }
    }

    ThreadExit(threadId);
    return RET_OK;
}

/*******************************************************************************
 * Function   : RTSPConnectionDestroyPassive
 *
 * Description: Destroy RTSP connected clients and frees its memory.
 *
 * Parameters :
 *      [IN]  RTSPClient *ClientConn  - Pointer to RTSP Client.
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - successful
 *          RET_ERROR - Error
 ******************************************************************************/
INT32 RTSPConnectionDestroyPassive(RTSPClient *ClientConn)
{
    RTPClientStream *rtpClientStream;   /* RTP Client Stream Struct Pointer   */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tClientConn = %d \n", ClientConn);

    /* Validate the input argument                                            */
    if (ClientConn == NULL)
    {
        RtpRtspErrorPrint("Invalid RTSP client connection pointer passed \n");
        return RET_ERROR;
    }

    /* Validate Client Handle                                                 */
    if (ValidateServersideClientHandle((INT32)ClientConn) != RET_OK)
    {
        RtpRtspErrorPrint("Invalid RTSP client connection pointer passed \n");
        return RET_ERROR;
    }

    /* Free RTPClientStream data                                              */
    rtpClientStream = ClientConn->ClientStreamList;

    while (rtpClientStream != NULL)
    {
        // Close RTP data socket in case of RTP over UDP
        if (!ClientConn->ClientInterleavedFlag && rtpClientStream->RTPConnSocket != INVALID_SOCKET)
        {
            CloseServerSock(rtpClientStream->RTPConnSocket);
            rtpClientStream->RTPConnSocket = INVALID_SOCKET;
        }

        ClientConn->ClientStreamList = rtpClientStream->Next;
        rtpClientStream = ClientConn->ClientStreamList;
    }

    /* Close connection socket to close RTSP session thread               */
    if (ClientConn->ClientSocket != INVALID_SOCKET)
    {
        CloseServerSock(ClientConn->ClientSocket);
        ClientConn->ClientSocket = INVALID_SOCKET;
    }

    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
    return RET_OK;
}

/*******************************************************************************
 * Function   : RTSPConnectionDestroy
 *
 * Description: Destroy RTSP connected clients and frees its memory.
 *
 * Parameters :
 *      [IN]  RTSPClient *ClientConn  - Pointer to RTSP Client.
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - successful
 *          RET_ERROR - Error
 ******************************************************************************/
INT32 RTSPConnectionDestroy(RTSPClient *ClientConn)
{
    RTPClientStream *rtpClientStream;   /* RTP Client Stream Struct Pointer   */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tClientConn = %d \n", ClientConn);

    /* Validate the input argument                                            */
    if (ClientConn == NULL)
    {
        RtpRtspErrorPrint("Invalid RTSP client connection pointer passed \n");
        return RET_ERROR;
    }

    /* Validate Client Handle                                                 */
    if (ValidateServersideClientHandle((INT32)ClientConn) != RET_OK)
    {
        RtpRtspErrorPrint("Invalid RTSP client connection pointer passed \n");
        return RET_ERROR;
    }

    if (ClientConn->RtspSessionPtr)
    {
        /* Lock ConnectedClient List                                              */
        if (MutexLock(&(ClientConn->RtspSessionPtr->SessionClientListLock)) != RET_OK)
        {
            RtpRtspErrorPrint("Connected Client List Lock Failed \n");
            return RTP_RTSP_LOCK_FAIL;
        }
    }

    ClientConn->ClientState = CLIENT_INVALID_STATE;

    if (ClientConn->RtspSessionPtr)
    {
        /* UnLock ConnectedClient List                                            */
        if (MutexUnlock(&(ClientConn->RtspSessionPtr->SessionClientListLock)) != RET_OK)
        {
            RtpRtspErrorPrint("Connected Client List UnLock Failed \n");
            return RTP_RTSP_LOCK_FAIL;
        }
    }

    if (ClientConn->RtspSessionPtr)
    {
        if (ClientConn->RtspSessionPtr->RTPWriter_Callback != NULL)
        {
            ClientConn->RtspSessionPtr->RTPWriter_Callback((INT32)ClientConn,
                    (INT32)ClientConn->RtspSessionPtr,
                    FS_DESTROY_CLIENT,
                    NULL);
        }
    }

    if (ClientConn->RtspSessionPtr)
    {
        /* Lock ConnectedClient List                                              */
        if (MutexLock(&(ClientConn->RtspSessionPtr->SessionClientListLock)) != RET_OK)
        {
            RtpRtspErrorPrint("Connected Client List Lock Failed \n");
            return RTP_RTSP_LOCK_FAIL;
        }
    }

    /* Free RTPClientStream data                                              */
    rtpClientStream = ClientConn->ClientStreamList;

    while (rtpClientStream != NULL)
    {
        /* Close the RTCP Session for this Stream                             */
        if (ClientConn->RtspSessionPtr->RtcpFlag == 1)
        {
            if (rtpClientStream->rtcpSessionInfo)
            {
                if (ClientConn->RtspSessionPtr)
                {
                    /* Lock ConnectedClient List                                              */
                    if (MutexUnlock(&(ClientConn->RtspSessionPtr->SessionClientListLock)) != RET_OK)
                    {
                        RtpRtspErrorPrint("Connected Client List  Unlock Failed \n");
                        return RTP_RTSP_LOCK_FAIL;
                    }
                }

                RTCPSendByePacket((INT32)rtpClientStream->rtcpSessionInfo, (BYTE *)"Closing the connection");

                if (ClientConn->RtspSessionPtr)
                {
                    /* Lock ConnectedClient List                                              */
                    if (MutexLock(&(ClientConn->RtspSessionPtr->SessionClientListLock)) != RET_OK)
                    {
                        RtpRtspErrorPrint("Connected Client List  Unlock Failed \n");
                        return RTP_RTSP_LOCK_FAIL;
                    }
                }

                if (RTCPStop((INT32)rtpClientStream->rtcpSessionInfo) < 0)
                {
                    RtpRtspErrorPrint("Error in stoping RTCP Session\n");
                }
            }
        }

        // Close RTP data socket in case of RTP over UDP
        if (!ClientConn->ClientInterleavedFlag && rtpClientStream->RTPConnSocket != INVALID_SOCKET)
        {
            CloseServerSock(rtpClientStream->RTPConnSocket);
            rtpClientStream->RTPConnSocket = INVALID_SOCKET;
        }

        ClientConn->ClientStreamList = rtpClientStream->Next;
        free(rtpClientStream);
        rtpClientStream = ClientConn->ClientStreamList;
    }

    /* Close connection socket to close RTSP session thread               */
    if (ClientConn->ClientSocket != INVALID_SOCKET)
    {
        CloseServerSock(ClientConn->ClientSocket);
        ClientConn->ClientSocket = INVALID_SOCKET;
    }

    /* Free RTSP request msg structure of the client                          */
    if (ClientConn->ClientRtspReqMsg)
    {
        FreeRequestMsg(ClientConn->ClientRtspReqMsg);
        ClientConn->ClientRtspReqMsg = NULL;
    }

    /* Free the response Msg struct of the client                             */
    if (ClientConn->ClientRtspResMsg)
    {
        /* Free the response msg memory                                       */
        FreeResponseMsg(ClientConn->ClientRtspResMsg);
        ClientConn->ClientRtspResMsg = NULL;
    }

    /* Reduce the connected client count                                      */
    if (ClientConn->RtspSessionPtr)
    {
        ClientConn->RtspSessionPtr->SessionConnectedClientCount--;

        if (ClientConn->ClientInterleavedFlag)
        {
            ClientConn->RtspSessionPtr->TCPClientCount --;
        }
        else
        {
            ClientConn->RtspSessionPtr->UDPClientCount --;
        }
    }

    /* Remove client from the server list                                     */
    if (ClientConn->PrevClient == NULL)
    {
        /* First client                                                       */
        if (ClientConn->RtspSessionPtr)
        {
            ClientConn->RtspSessionPtr->SessionConnectedClientList = ClientConn->NextClient;
        }

        if (ClientConn->NextClient)
        {
            ClientConn->NextClient->PrevClient          = NULL;
        }
        else
        {
            if (ClientConn->RtspSessionPtr)
            {
                ClientConn->RtspSessionPtr->SessionConnectedClientList = NULL;
            }
        }
    }
    else if (ClientConn->NextClient == NULL)
    {
        /* Last in the list                                                   */
        if (ClientConn->PrevClient)
        {
            ClientConn->PrevClient->NextClient          = NULL;
        }
        else
        {
            if (ClientConn->RtspSessionPtr)
            {
                ClientConn->RtspSessionPtr->SessionConnectedClientList = NULL;
            }
        }
    }
    else
    {
        /* In the middle of the list                                          */
        ClientConn->PrevClient->NextClient              = ClientConn->NextClient;
        ClientConn->NextClient->PrevClient              = ClientConn->PrevClient;
    }

    if (ClientConn->RtspSessionPtr)
    {
        if (ClientConn->RtspSessionPtr->ClientConnectionCallback)
        {
            ClientConn->RtspSessionPtr->ClientConnectionCallback(0 /* For CLOSE */,
                    ClientConn->RtspSessionPtr->SessionName);
        }

        /* UnLock ConnectedClient List                                            */
        if (MutexUnlock(&(ClientConn->RtspSessionPtr->SessionClientListLock)) != RET_OK)
        {
            RtpRtspErrorPrint("Connected Client List UnLock Failed \n");
            return RTP_RTSP_LOCK_FAIL;
        }
    }

    MutexDestroy(&(ClientConn->RTSPClientSendmsgLock));
    /* Free memory of RTSPClient structure                                    */
    free(ClientConn);
    ClientConn = NULL;
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
    return RET_OK;
}

//\\ 在SOCKET上接收RTSP数据包
RTSPBuff *RTSPServerReadMessage(SOCKET SessionSocket)
{
    INT32           recvLen;              /* Length of Data received from client  */
    INT32           RtcpOrRtpDataFlag = 0;  /* Flag to denote rtcp or rtp data    */
    INT32           FirstTime = 1;          /* Flag to denote first time data recv*/
    RTSPBuff        *recvDataBuff;        /* Buffer for storing Data              */
    INT32           totalrecvLen = 0;       /* Length of Total data received      */
    recvDataBuff = (RTSPBuff *) malloc(sizeof(RTSPBuff));

    if (recvDataBuff == NULL)
    {
        return recvDataBuff;
    }

    memset(recvDataBuff, 0x00, sizeof(RTSPBuff));
    recvDataBuff->DataBuff = (BYTE *) malloc(MAX_DATA_SIZE);

    if (recvDataBuff->DataBuff == NULL)
    {
        free(recvDataBuff);
        recvDataBuff = NULL;
        return NULL;
    }

    memset(recvDataBuff->DataBuff, 0x00, MAX_DATA_SIZE);
    bool  pos = false;

    //接收数据
    do
    {
        recvLen = recv(SessionSocket, recvDataBuff->DataBuff + totalrecvLen, MAX_DATA_SIZE - totalrecvLen, 0);

        if (recvLen <= 0)
        {
            if (errno == 4 || errno == 11 || errno == 41) // should not return NULL.
            {
                pos = true;
                MSecDelay(50);
                continue ;
            }

            if (recvDataBuff->DataBuff)
            {
                free(recvDataBuff->DataBuff);
                recvDataBuff->DataBuff = NULL;
            }

            if (recvDataBuff)
            {
                free(recvDataBuff);
                recvDataBuff = NULL;
            }

            return NULL;
        }

        /* Check whether it is RTCP packet                                    */
        if (*recvDataBuff->DataBuff == '$' && (FirstTime == 1))
        {
            RtcpOrRtpDataFlag = 1;
        }

        //\\ 好像有问题，需要放到if条件中去
        FirstTime = 0;
        totalrecvLen += recvLen;

        if ((totalrecvLen < 4) && (RtcpOrRtpDataFlag == 1))
        {
            continue; // RTCP packet starting with bytes '$' .
        }

        pos = false;
    }
    while (pos);

    recvDataBuff->DataBuffLen = totalrecvLen;

    if (recvDataBuff->DataBuffLen > 0)
    {
        return recvDataBuff;
    }
    else
    {
        if (recvDataBuff->DataBuff)
        {
            free(recvDataBuff->DataBuff);
            recvDataBuff->DataBuff = NULL;
        }

        if (recvDataBuff)
        {
            free(recvDataBuff);
            recvDataBuff = NULL;
        }

        return NULL;
    }
}

/*******************************************************************************
 * Function:    RTSPServerParseMessage
 *
 * Description: This function parse the RTSP buffer and return the RTSP
 *              request in the RTSPRequestMsg structure.
 *
 * Parameters :
 *      [IN]     RTSPBuff * RecvRTSPBuff - RTSP buffer struct pointer
 *
 * Return Value:
 *       RTSPRequestMsg * - Pointer to RTSPRequestMsg structure
 *                        - NULL in case of error in parsing buffer
 ******************************************************************************/
//\\ 从输入缓冲区中解析出RTSP请求
RTSPRequestMsg *RTSPServerParseMessage(RTSPBuff *RecvRTSPBuff)
{
    BYTE             *tempArray;                                  /* Temp buffer pointer                    */
    BYTE             *buffPtr;                                          /* Pointer of received data buffer        */
    INT32            buffLen;                                           /* Store the length of buffer             */
    INT32            indexCnt = 0;                                   /* Index counter                          */
    RTSPRequestMsg   *requestMsg;   /* Holds Parsed Data from Request Message */
    /* Get the length and local pointer of received buffer                    */
    buffLen = RecvRTSPBuff->DataBuffLen;
    buffPtr = RecvRTSPBuff->DataBuff;
    /* Allocate Memory to Request Message's pointer                           */
    requestMsg = (RTSPRequestMsg *) malloc(sizeof(RTSPRequestMsg));

    if (requestMsg == NULL)
    {
        //          RtpRtspErrorPrint ("Cannot Allocate Memory to Request Message's Pointer\n");
        return NULL;
    }

    memset(requestMsg, 0x00, sizeof(RTSPRequestMsg));

    /* Get the method from buffer and store it in to the message structure    */
    //\\ 从缓冲区中解析出RTSP方法
    if ((indexCnt = FindCharInBuffer(buffPtr, ' ', '\r', buffLen)))
    {
        buffLen  -= indexCnt;
        tempArray = (BYTE *)malloc(indexCnt + 1);

        if (tempArray != NULL)
        {
            memset(tempArray, 0x00, indexCnt + 1);
            memcpy(tempArray, buffPtr, indexCnt);
            buffPtr              += indexCnt + 1;
            requestMsg->ReqMethod = ConvertMethodString(tempArray);

            if (requestMsg->ReqMethod  == RTSP_METHOD_INVALID)
            {
                RtpRtspErrorPrint("Invalid Method received from client\n");
                free(requestMsg);
                requestMsg = NULL;
                free(tempArray);
                tempArray = NULL;
                return NULL;
            }

            RtpRtspDebugPrint(DBG_LEVEL_5, "Requested Method is = %s, value = %d\n", tempArray, requestMsg->ReqMethod);
            free(tempArray);
            tempArray = NULL;
        }
        else
        {
            RtpRtspErrorPrint("Cannot Allocate Memory for tempArray Pointer\n");
            free(requestMsg);
            requestMsg = NULL;
            return NULL;
        }
    }
    else
    {
        free(requestMsg);
        requestMsg = NULL;
        return NULL;
    }

    //\\ 从缓冲区中解析出RTSP的URI
    /* Get the URI from the buffer and store it into the message structure    */
    if ((indexCnt = FindCharInBuffer(buffPtr, ' ', '\r', buffLen)))
    {
        buffLen -= indexCnt;
        requestMsg->ReqMsgURI = (BYTE *)malloc(indexCnt + 1);

        if (requestMsg->ReqMsgURI != NULL)
        {
            memset(requestMsg->ReqMsgURI, 0x00, indexCnt + 1);
            memcpy(requestMsg->ReqMsgURI, buffPtr, indexCnt);
            buffPtr  += indexCnt + 1;
            //                  RtpRtspDebugPrint(DBG_LEVEL_5, "Requested URI is = %s\n", requestMsg->ReqMsgURI);
        }
        else
        {
            RtpRtspErrorPrint("Cannot Allocate Memory for Message URI Pointer\n");
            free(requestMsg);
            requestMsg = NULL;
            return NULL;
        }
    }
    else
    {
        free(requestMsg);
        requestMsg = NULL;
        return NULL;
    }

    //\\ 从缓冲区中解析出版本信息
    /* Get the version from the buffer                                        */
    if ((indexCnt = FindCharInBuffer(buffPtr, '\r', '\n', buffLen)))
    {
        buffLen -= indexCnt + 2;
        requestMsg->ReqRtspVersion = (BYTE *)malloc(indexCnt + 1);

        if (requestMsg->ReqRtspVersion != NULL)
        {
            memset(requestMsg->ReqRtspVersion, 0x00, indexCnt + 1);
            memcpy(requestMsg->ReqRtspVersion, buffPtr, indexCnt);
            buffPtr += indexCnt + 2;
            //                  RtpRtspDebugPrint(DBG_LEVEL_5, "Requested Msg's RTSPVersion is = %s\n", requestMsg->ReqRtspVersion);
        }
        else
        {
            RtpRtspErrorPrint("Cannot Allocate Memory for Message URI Pointer\n");

            if (requestMsg->ReqMsgURI)
            {
                free(requestMsg->ReqMsgURI);
                requestMsg->ReqMsgURI = NULL;
            }

            free(requestMsg);
            requestMsg = NULL;
            return NULL;
        }
    }
    else
    {
        free(requestMsg);
        requestMsg = NULL;
        return NULL;
    }

    /* Now all next request contain the headers so loop to extract name and
       value of each header                                                   */
    for (;;)
    {
        if (buffLen <= 2)
        {
            break;
        }

        //从缓冲区中解析出头的名字
        /* Get the name of header                                             */
        if ((indexCnt = FindCharInBuffer(buffPtr, ':', '\r', buffLen)))
        {
            requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderName = (BYTE *)malloc(indexCnt + 1);

            if (requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderName == NULL)
            {
                //                      RtpRtspErrorPrint("Memory Allocation Failed \n");
                break;
            }

            memset(requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderName,
                   0x00, indexCnt + 1);
            memcpy(requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderName,
                   buffPtr, indexCnt);
            buffPtr += indexCnt + 2;
            buffLen -= indexCnt + 2;

            //从缓冲区中解析出头的具体内容
            /* Get the value of header                                        */
            if ((indexCnt = FindCharInBuffer(buffPtr, '\r', '\n', buffLen)))
            {
                requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderValue =
                    (BYTE *)malloc(indexCnt + 1);

                if (requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderValue == NULL)
                {
                    RtpRtspErrorPrint("Memory Allocation Failed \n");
                    free(requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderName);
                    requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderName = NULL;
                    break;
                }

                memset(requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].
                       HeaderValue, 0x00, indexCnt + 1);
                memcpy(requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].
                       HeaderValue, buffPtr, indexCnt);
                buffPtr     += indexCnt + 2;
                buffLen     -= indexCnt + 2;

                //                      RtpRtspDebugPrint(DBG_LEVEL_5, "%s = %s\n",
                //                              requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderName,
                //                              requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderValue);
                if (!strcmp((INT8 *)requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderName, "CSeq"))
                {
                    requestMsg->ReqSeqNumber = atoi((INT8 *)requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderValue);
                }

                requestMsg->ReqHeadersCount++;
            }
            else
            {
                free(requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderName);
                requestMsg->ReqMsgHeaders[requestMsg->ReqHeadersCount].HeaderName = NULL;
                break;
            }
        }
        else
        {
            break;
        }
    }

    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tRequestMsg = %d \n", requestMsg);
    return requestMsg;
}

/*******************************************************************************
 * Function:    RTSPServerProcessMessage
 * Description: This function call appropriate handler function as per the RTSP message method
 * Parameters :
 *      [IN] RTSPClient * ClientConn - RTSP connection struct pointer
 *      [IN] int nChenkValid - 接收消息前是否需要检查接收消息的有效性
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - successful
 *          RET_ERROR - Error
 ******************************************************************************/
//\\ 创建指定方法的应答包
INT32 RTSPServerProcessMessage(RTSPClient *ClientConn, int nCheckValid)
{
    INT32       retVal = RET_ERROR; /* Return value                           */

    if (1 == nCheckValid)
    {
        //检查RTSP请求是否正确
        retVal = CommonMsgValidation(ClientConn);

        if (retVal != RET_OK)
        {
            return retVal;
        }
    }

    ClientConn->lastPktRecvTimeStamp = GetTimeValue();

    switch (ClientConn->ClientRtspReqMsg->ReqMethod)
    {
        case HTTP_METHOD_GET:
            //retVal = HTTPGetHandle (ClientConn);
            break;

        case RTSP_METHOD_OPTIONS:
            retVal = RTSPOptionHandle(ClientConn);
            break;

        //\\ DESCRIBE方法应答包，内部需要组建SDP信息，在发送该包之前需要收集好SPS与PPS信息
        case RTSP_METHOD_DESCRIBE:
            retVal = RTSPDescribeHandle(ClientConn);
            break;

        //\\ 构造SETUP方法应答包，内部有协商是UDP传输或者TCP传输
        case RTSP_METHOD_SETUP:
            retVal = RTSPSetupHandle(ClientConn);
            break;

        case RTSP_METHOD_PLAY:
            retVal = RTSPPlayHandle(ClientConn);
            break;

        case RTSP_METHOD_PAUSE:
            retVal = RTSPPauseHandle(ClientConn);
            break;

        case RTSP_METHOD_TEARDOWN:
            retVal = RTSPTeardownHandle(ClientConn);
            break;

        case RTSP_METHOD_ANNOUNCE:
        case RTSP_METHOD_GET_PARAMETER:
        case RTSP_METHOD_SET_PARAMETER:
        case RTSP_METHOD_REDIRECT:
        case RTSP_METHOD_RECORD:
            retVal = 501;
            break;

        default:
            retVal = 400;
            break;
    }

    return retVal;
}

/*******************************************************************************
 * Function:    RTSPServerSendResponse
 *
 * Description: This function send the passed response to client using connected
 *              socket
 *
 * Parameters :
 *      [IN]  RTSPClient * ClientConn - Pointer of RTSP Client connection struct
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Validation successful
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
//发送RTSP应答数据包
INT32 RTSPServerSendResponse(RTSPClient *ClientConn)
{
    BYTE    *rtspResponse;          /* RTSP response buffer pointer           */
    INT32   responseSize;           /* RTSP response size                     */
    INT32   indexCnt;               /* index counter                          */
    int ret = -1;
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tClientConn = %d\n", ClientConn);

    /* Validate Input Argument                                                */
    if (ClientConn  == NULL)
    {
        RtpRtspErrorPrint("Invalid Input Argument\n");
        return RET_ERROR;
    }

    /* Calculating Response Message size                                      */
    responseSize = (INT32) strlen(DEFAULT_RTSP_VERSION) + STRING_LEN_INT32 /* Status Code */ +
                   (INT32) strlen((INT8 *)ClientConn->ClientRtspResMsg->ResReasonPhrase) +
                   (INT32) strlen("  \r\n");

    for (indexCnt = 0; indexCnt < ClientConn->ClientRtspResMsg->ResHeadersCount; indexCnt++)
    {
        responseSize += (INT32) strlen((INT8 *)ClientConn->ClientRtspResMsg->ResMsgHeaders[indexCnt].HeaderName)  +
                        (INT32) strlen((INT8 *)ClientConn->ClientRtspResMsg->ResMsgHeaders[indexCnt].HeaderValue) +
                        (INT32) strlen(": \r\n");
    }

    responseSize += (INT32) strlen("\r\n") + 1;
    /* Allocating memory to rtspResponse                                      */
    rtspResponse = (BYTE *) malloc(responseSize);

    if (rtspResponse == NULL)
    {
        RtpRtspErrorPrint("Can not allocate memory for response string\n");
        return RET_ERROR;
    }

    memset(rtspResponse, 0x00, responseSize);
    responseSize = sprintf((INT8 *)rtspResponse, "%s %d %s\r\n",
                           DEFAULT_RTSP_VERSION,
                           ClientConn->ClientRtspResMsg->ResStatusCode,
                           ClientConn->ClientRtspResMsg->ResReasonPhrase);

    /* Loop to add all response header in the response                        */
    for (indexCnt = 0; indexCnt < ClientConn->ClientRtspResMsg->ResHeadersCount; indexCnt++)
    {
        responseSize += sprintf((INT8 *)(rtspResponse + responseSize), "%s: %s\r\n",
                                ClientConn->ClientRtspResMsg->ResMsgHeaders[indexCnt].HeaderName,
                                ClientConn->ClientRtspResMsg->ResMsgHeaders[indexCnt].HeaderValue);
    }

    responseSize += sprintf((INT8 *)(rtspResponse + responseSize), "\r\n");
    responseSize  =  strlen((INT8 *)rtspResponse);
    /* Send Response to the respective client                                 */
    /* MSG_NOSIGNAL flag to diasble SIGPIPE, in case of Socket error while
       attempting to write on a closed destination socket                     */

SEND_AGAIN :
    MutexLock(&(ClientConn->RTSPClientSendmsgLock));
    //    ret = send (ClientConn->ClientSocket, rtspResponse, responseSize , MSG_NOSIGNAL | MSG_DONTWAIT);
    ret = send(ClientConn->ClientSocket, rtspResponse, responseSize , MSG_NOSIGNAL);
    MutexUnlock(&(ClientConn->RTSPClientSendmsgLock));
    if (ret == -1)
    {
#if 0	/*cb change 2016.8.8 .修改rtsp在tcp模式下重连的问题*/	
        if (errno != 32)
        {
            MSecDelay(20);
            goto SEND_AGAIN;
        }
#endif
        free(rtspResponse);
        rtspResponse = NULL;
        return RET_ERROR;
    }
    if (ClientConn->ClientRtspReqMsg->ReqMethod == RTSP_METHOD_DESCRIBE &&
        ClientConn->ClientRtspResMsg->ResStatusCode != 454 &&
        ClientConn->ClientRtspResMsg->ResStatusCode != 401 &&
        ClientConn->ClientRtspResMsg->ResStatusCode != 403)
    {
        if (ClientConn->RtspSessionPtr != NULL)
        {
            if (ClientConn->RtspSessionPtr->SessionGeneratedSDP)
            {
                RtpRtspDebugPrint(DBG_LEVEL_5, "Sending SDP to client\n%s\n",
                                  ClientConn->RtspSessionPtr->SessionGeneratedSDP);
                MutexLock(&(ClientConn->RTSPClientSendmsgLock));

                /* Send Response to the respective client */
                /* MSG_NOSIGNAL flag to diasble SIGPIPE, in case of Socket error
                   while attempting to write on a closed destination socket */
                if (send(ClientConn->ClientSocket, ClientConn->RtspSessionPtr->SessionGeneratedSDP,
                         strlen((INT8 *)ClientConn->RtspSessionPtr->SessionGeneratedSDP), MSG_NOSIGNAL
                        ) == -1)
                {
                    MutexUnlock(&(ClientConn->RTSPClientSendmsgLock));
                    free(rtspResponse);
                    rtspResponse = NULL;
                    return RET_ERROR;
                }

                MutexUnlock(&(ClientConn->RTSPClientSendmsgLock));
	
            }
        }
        else
        {
            free(rtspResponse);
            rtspResponse = NULL;
            return RET_ERROR;
        }
    }

    ClientConn->ClientRtspResMsg->ResReasonPhrase = NULL;
    /* Free the memory                                                        */
    free(rtspResponse);
    rtspResponse = NULL;
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
    return RET_OK;
}

//\\ 创建指定客户句柄应答包
INT32 RTSPGenerateMethodResponse(RTSPClient *ClientConn, INT32 StatusCode)
{
    INT32 counter;              /* Local counter                              */
    ClientConn->ClientRtspResMsg = (RTSPResponseMsg *)malloc(sizeof(RTSPResponseMsg));

    if (ClientConn->ClientRtspResMsg == NULL)
    {
        return RET_ERROR;
    }

    memset(ClientConn->ClientRtspResMsg, 0x00, sizeof(RTSPResponseMsg));

    //\\ 设置应答包版本信息
    if (ClientConn->ClientRtspReqMsg->ReqRtspVersion)
    {
        ClientConn->ClientRtspResMsg->ResRtspVersion = (BYTE *)malloc(strlen((INT8 *)ClientConn->ClientRtspReqMsg->ReqRtspVersion) + 1);

        if (ClientConn->ClientRtspResMsg->ResRtspVersion == NULL)
        {
            free(ClientConn->ClientRtspResMsg);
            ClientConn->ClientRtspResMsg = NULL;
            return RET_ERROR;
        }

        memset(ClientConn->ClientRtspResMsg->ResRtspVersion, 0x00, strlen((INT8 *)ClientConn->ClientRtspReqMsg->ReqRtspVersion) + 1);
        strcpy((INT8 *)ClientConn->ClientRtspResMsg->ResRtspVersion, (INT8 *)ClientConn->ClientRtspReqMsg->ReqRtspVersion);
    }
    else
    {
        ClientConn->ClientRtspResMsg->ResRtspVersion = (BYTE *)malloc(strlen(DEFAULT_RTSP_VERSION) + 1);

        if (ClientConn->ClientRtspResMsg->ResRtspVersion == NULL)
        {
            free(ClientConn->ClientRtspResMsg);
            ClientConn->ClientRtspResMsg = NULL;
            return RET_ERROR;
        }

        memset(ClientConn->ClientRtspResMsg->ResRtspVersion, 0x00, strlen(DEFAULT_RTSP_VERSION) + 1);
        strcpy((INT8 *)ClientConn->ClientRtspResMsg->ResRtspVersion, DEFAULT_RTSP_VERSION);
    }

    for (counter = 0; counter < MAX_REASON_ARR_SIZE; counter++)
    {
        if (StatusReasonPhrase[counter].StatusCode == StatusCode)
        {
            ClientConn->ClientRtspResMsg->ResStatusCode   = StatusReasonPhrase[counter].StatusCode;
            ClientConn->ClientRtspResMsg->ResReasonPhrase = (BYTE *)StatusReasonPhrase[counter].ReasonPhrase;
            break;
        }
    }

    if (ClientConn->ClientRtspResMsg->ResReasonPhrase == NULL)
    {
        RtpRtspErrorPrint("Invalid status code \n", StatusCode);

        if (ClientConn->ClientRtspResMsg->ResRtspVersion)
        {
            free(ClientConn->ClientRtspResMsg->ResRtspVersion);
            ClientConn->ClientRtspResMsg->ResRtspVersion = NULL;
        }

        if (ClientConn->ClientRtspResMsg)
        {
            free(ClientConn->ClientRtspResMsg);
            ClientConn->ClientRtspResMsg = NULL;
        }

        return RET_ERROR;
    }

    if (ClientConn->ClientRtspReqMsg->ReqSeqNumber)
    {
        ClientConn->ClientRtspResMsg->ResSeqNumber = ClientConn->ClientRtspReqMsg->ReqSeqNumber;
    }
    else
    {
        ClientConn->ClientRtspResMsg->ResSeqNumber = 1;
    }

    return RET_OK;
}

/*******************************************************************************
 * Function:    RTSPOptionHandle
 * Description: This function generate the response for OPTIONS request method
 * Parameters :
 *      [IN]  RTSPClient * ClientConn - Pointer of RTSP Client connection struct
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Validation successful
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
//\\ 产生OPTION方法的应答包
INT32 RTSPOptionHandle(RTSPClient *ClientConn)
{
    if (RTSPGenerateMethodResponse(ClientConn, 200) == RET_ERROR)
    {
        return RET_ERROR;
    }

    if (CopyResponseHeader(ClientConn->ClientRtspResMsg, ClientConn->ClientRtspReqMsg, (BYTE *)"CSeq") == RET_ERROR)
    {
        return RET_ERROR;
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Server", (BYTE *)RTSP_SERVER_NAME) == RET_ERROR)
    {
        return RET_ERROR;
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Public", (BYTE *)RTSP_IMPLEMENTED_METHOD) == RET_ERROR)
    {
        return RET_ERROR;
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Content-Length", (BYTE *)"0") == RET_ERROR)
    {
        return RET_ERROR;
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Cache-Control", (BYTE *)"no-cache") == RET_ERROR)
    {
        return RET_ERROR;
    }

    return RET_OK;
}

/*******************************************************************************
 * Function:    RTSPDescribeHandle
 * Description: This function generate the response for DESCRIBE request method
 * Parameters :
 *      [IN]  RTSPClient * ClientConn - Pointer of RTSP Client connection struct
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Validation successful
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
//\\ DESCRIBE方法应答包，内部需要组建SDP信息，在发送该包之前需要收集好SPS与PPS信息
INT32 RTSPDescribeHandle(RTSPClient *ClientConn)
{
    INT32   counter;                /* Local Counter                          */

    /*
     Modified by hongzg, at 2014-06-30 10:33:59
     reason: live555 RTSP client send 2 Describe packet bug.
    */
    /*
        if (ClientConn->ClientState != CLIENT_INIT_STATE)
        {
            return 455;
        }
    */

    if (ClientConn->RtspSessionPtr->SessionStreamList == NULL)
    {
        return RET_ERROR;
    }

    for (counter = 0 ; counter < ClientConn->ClientRtspReqMsg->ReqHeadersCount; counter++)
    {
        if (!strcmp((INT8 *)ClientConn->ClientRtspReqMsg->ReqMsgHeaders[counter].HeaderName, "Accept"))
        {
            if (!strcmp((INT8 *)ClientConn->ClientRtspReqMsg->ReqMsgHeaders[counter].HeaderValue, "application/sdp"))
            {
                RtpRtspDebugPrint(DBG_LEVEL_5, "Describe request contain application-sdp in Accept header\n");
            }
            else
            {
                RTSP_SER_PE("Describe request does not contain application-sdp in Accept header\n");
            }

            break;
        }
    }

    /* Generate OK Response for describe method                               */
    if (RTSPGenerateMethodResponse(ClientConn, 200) == RET_ERROR)
    {
        return RET_ERROR;
    }

    if (CopyResponseHeader(ClientConn->ClientRtspResMsg, ClientConn->ClientRtspReqMsg, (BYTE *)"CSeq") == RET_ERROR)
    {
        return RET_ERROR;
    }

    /* Add "Server" Header Field to Response Header                           */
    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Server", (BYTE *)RTSP_SERVER_NAME) == RET_ERROR)
    {
        return RET_ERROR;
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Content-Type", (BYTE *)"application/sdp") == RET_ERROR)
    {
        return RET_ERROR;
    }

    //\\ DESCRIBE方法应答包，内部需要组建SDP信息，在发送该包之前需要收集好SPS与PPS信息
    if (RtspGenerateSDP(ClientConn) == RET_ERROR)
    {
        return RET_ERROR;
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Cache-Control", (BYTE *)"no-cache") == RET_ERROR)
    {
        return RET_ERROR;
    }
	
    /*
     Modified by hongzg, at 2014-06-30 10:36:06
     reason:  live555 RTSP client send 2 Describe packet bug.
    */
    if (ClientConn->ClientState == CLIENT_INIT_STATE)
    {
        ClientConn->ClientState = CLIENT_DESCRIBE_STATE;
    }

    return RET_OK;
}

/*******************************************************************************
 * Function:    RTSPSetupHandle
 * Description: This function generate the response for SETUP request method
 * Parameters :
 *      [IN]  RTSPClient * ClientConn - Pointer of RTSP Client connection struct
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Validation successful
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
//\\ 构造SETUP方法应答包，内部有协商是UDP传输或者TCP传输
INT32 RTSPSetupHandle(RTSPClient *ClientConn)
{
    BYTE    *transportHeader;           /* Store Transport header pointer     */
    BYTE    *portTemp;                  /* Store Port string pointer          */
    BYTE    *sessionIdString;           /* Store Session ID pointer           */
    BYTE    multicastTTL = 1;           /* TTL of multicast packets           */
    BYTE    *transportValue;            /* Value of Transport Header response */
    BYTE    *tempPtr;                   /* Local Temporary Pointer            */
    INT32   trackIDVal  = 0;            /* Local ID Value                     */
    INT32   streamIDVal = 0;            /* Stream ID Value                    */
    INT32   optVal = 1;                 /* Used for setsock option            */
    RTPClientStream *tempRTPClientStream;/*Temporary Connection Stream Pointer*/
    RTPClientStream *streamTemp;        /* Temporary Connection Stream Pointer*/
    RTPSessionStream *rtspStreamTemp;   /* RTSP Stream Pointer                */
    SOCKETADDR_IN    dataSocketAddr;    /* Sock addr struct of server         */
    SOCKETADDR_IN    rtpSocketAddr;     /* Sock addr struct of client         */

    if ((ClientConn->ClientState != CLIENT_DESCRIBE_STATE) && ((ClientConn->ClientState != CLIENT_READY_STATE)))
    {
        return 455;
    }

    transportHeader = GetRequestMsgHeader(ClientConn->ClientRtspReqMsg, (BYTE *)"Transport");

    if (transportHeader == NULL)
    {
        return RET_ERROR;
    }

    if ((strstr((INT8 *)transportHeader, "interleaved") != NULL) || (strstr((INT8 *)transportHeader, "TCP") != NULL))
    {
        ClientConn->ClientInterleavedFlag   =   1;
        ClientConn->RtspSessionPtr->TCPClientCount ++;
    }
    else
    {
        ClientConn->RtspSessionPtr->UDPClientCount ++;
    }

    tempPtr     = (BYTE *)strstr((INT8 *)ClientConn->ClientRtspReqMsg->ReqMsgURI, "trackID=");

    if (tempPtr == NULL)
    {
        if (ClientConn->RtspSessionPtr->StreamCount == 1)
        {
            trackIDVal = 0;
        }
        else
        {
            return 459;
        }
    }
    else
    {
        tempPtr    += strlen("trackID=");
        trackIDVal  = atoi((INT8 *)tempPtr);
    }

    rtspStreamTemp = ClientConn->RtspSessionPtr->SessionStreamList;

    while (rtspStreamTemp)
    {
        if (trackIDVal == streamIDVal)
        {
            if (trackIDVal == 0)
            {
                rtspStreamTemp->InterleavedVal = 0;
            }
            else
            {
                rtspStreamTemp->InterleavedVal = trackIDVal + trackIDVal;
            }

            break;
        }

        streamIDVal++;
        rtspStreamTemp = rtspStreamTemp->Next;
    }

    if (trackIDVal > streamIDVal)
    {
        return RET_ERROR;
    }

    tempRTPClientStream = (RTPClientStream *) malloc(sizeof(RTPClientStream));

    if (tempRTPClientStream == NULL)
    {
        return RET_ERROR;
    }

    memset(tempRTPClientStream , 0x00, sizeof(RTPClientStream));
    tempRTPClientStream->streamNumber = trackIDVal + 1;
    tempRTPClientStream->RTPConnSocket = INVALID_SOCKET;

    if (ClientConn->ClientInterleavedFlag)
    {
        // 如果SETUP时是RTP over TCP，则不重新创建socket
        tempRTPClientStream->ClientPort = rtspStreamTemp->InterleavedVal;
        /* Incrementing Interleaved value                                     */
        rtspStreamTemp->InterleavedVal++;
    }
    else
    {
        // 如果SETUP时是RTP over UDP，则创建新的UDP socket，将其绑定到多播地址/客户端地址和相应端口上
        /* Extract Client Port                                                */
        portTemp = (BYTE *)strrchr((INT8 *)transportHeader, '-');

        if (portTemp == NULL)
        {
            free(tempRTPClientStream);
            tempRTPClientStream = NULL;
            RtpRtspErrorPrint("Extraction of Client Port Failed \n");
            return RET_ERROR;
        }
        else
        {
            portTemp++;
            tempRTPClientStream->ClientPort = atoi((INT8 *)portTemp) - 1;
            RTSP_SER_PD("Client Port is  %d \n", tempRTPClientStream->ClientPort);
        }

        /* Delete any non existing client from the list                       */
        CheckAndDeleteClient(ClientConn, tempRTPClientStream->ClientPort);
        tempRTPClientStream->RTPConnSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (tempRTPClientStream->RTPConnSocket == INVALID_SOCKET)
        {
            free(tempRTPClientStream);
            tempRTPClientStream = NULL;
            return RET_ERROR;
        }

        /* set socket option to no check                                          */
        if (setsockopt(tempRTPClientStream->RTPConnSocket, SOL_SOCKET, SO_NO_CHECK, (const void *)&optVal, sizeof(optVal)) < 0)
        {
            CloseServerSock(tempRTPClientStream->RTPConnSocket);
            free(tempRTPClientStream);
            tempRTPClientStream = NULL;
            return RET_ERROR;
        }

        /* Loop to bind the socket to free port                                   */
        do
        {
            dataSocketAddr.sin_family       = AF_INET;
            dataSocketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
            dataSocketAddr.sin_port         = htons(gblRtpPort);
            tempRTPClientStream->ServerPort = gblRtpPort;
            gblRtpPort += 2;
        }
        while (bind(tempRTPClientStream->RTPConnSocket, (struct sockaddr *)&dataSocketAddr, sizeof(dataSocketAddr)) == SOCKET_ERROR);

        rtpSocketAddr.sin_family      = AF_INET;
        {
            rtpSocketAddr.sin_addr.s_addr   = inet_addr((INT8 *)ClientConn->ClientIp);
            rtpSocketAddr.sin_port              = htons((UINT16)tempRTPClientStream->ClientPort);
        }

        if (connect(tempRTPClientStream->RTPConnSocket, (struct sockaddr *)&rtpSocketAddr, sizeof(rtpSocketAddr)) == SOCKET_ERROR)
        {
            CloseServerSock(tempRTPClientStream->RTPConnSocket);
            free(tempRTPClientStream);
            tempRTPClientStream = NULL;
            return RET_ERROR;
        }
    }

    /* Copy Encoding Name as Stream Identifier name                           */
    strcpy((INT8 *)tempRTPClientStream->StreamIdentifier, (INT8 *)rtspStreamTemp->EncodingName);
    tempRTPClientStream->rtspConnectedClientPtr = ClientConn;

    if (ClientConn->ClientInterleavedFlag != 1)
    {
        tempRTPClientStream->rtspConnectedClientPtr->rtpTransportProtocol = UDP;
    }
    else
    {
        tempRTPClientStream->rtspConnectedClientPtr->rtpTransportProtocol = TCP;
    }

    if (RTSPGenerateMethodResponse(ClientConn, 200) == RET_ERROR)
    {
        CloseServerSock(tempRTPClientStream->RTPConnSocket);
        free(tempRTPClientStream);
        tempRTPClientStream = NULL;
        return RET_ERROR;
    }

    /* Copy "CSeq" Header to Response from Request                            */
    if (CopyResponseHeader(ClientConn->ClientRtspResMsg, ClientConn->ClientRtspReqMsg, (BYTE *)"CSeq") == RET_ERROR)
    {
        CloseServerSock(tempRTPClientStream->RTPConnSocket);
        free(tempRTPClientStream);
        tempRTPClientStream = NULL;
        return RET_ERROR;
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Server", (BYTE *)RTSP_SERVER_NAME) == RET_ERROR)
    {
        CloseServerSock(tempRTPClientStream->RTPConnSocket);
        free(tempRTPClientStream);
        tempRTPClientStream = NULL;
        return RET_ERROR;
    }

    transportValue = (BYTE *) malloc(MAX_SMALL_BUFF_SIZE * 4);

    if (transportValue == NULL)
    {
        CloseServerSock(tempRTPClientStream->RTPConnSocket);
        free(tempRTPClientStream);
        tempRTPClientStream = NULL;
        return RET_ERROR;
    }

    memset(transportValue, 0x00, MAX_SMALL_BUFF_SIZE);
    /* Generate Transport Header response value                               */
    {
        if (((strstr((INT8 *)transportHeader, "interleaved") == NULL) && (strstr((INT8 *)transportHeader, "TCP") == NULL)))
        {
            sprintf((INT8 *)transportValue, "RTP/AVP/UDP;unicast;source=%s;client_port=%d-%d;server_port=%d-%d",
                    ClientConn->RtspServerPtr->ServerIp, tempRTPClientStream->ClientPort, tempRTPClientStream->ClientPort + 1,
                    tempRTPClientStream->ServerPort, tempRTPClientStream->ServerPort + 1);

            if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Transport", (BYTE *)transportValue) == RET_ERROR)
            {
                CloseServerSock(tempRTPClientStream->RTPConnSocket);
                free(tempRTPClientStream);
                tempRTPClientStream = NULL;
                free(transportValue);
                transportValue = NULL;
                return RET_ERROR;
            }
        }
        else
        {
            sprintf((INT8 *)transportValue, "RTP/AVP/TCP;unicast;source=%s;interleaved=%d-%d;server_port=%d-%d",
                    ClientConn->RtspServerPtr->ServerIp, rtspStreamTemp->InterleavedVal - 1, rtspStreamTemp->InterleavedVal,
                    tempRTPClientStream->ServerPort, tempRTPClientStream->ServerPort + 1);

            if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Transport", (BYTE *)transportValue) == RET_ERROR)
            {
                CloseServerSock(tempRTPClientStream->RTPConnSocket);
                free(tempRTPClientStream);
                tempRTPClientStream = NULL;
                free(transportValue);
                transportValue = NULL;
                return RET_ERROR;
            }
        }

        free(transportValue);
    }

    /* Add "Cache-Control" Header Field to Response Header                    */
    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Cache-Control", (BYTE *)"no-cache") == RET_ERROR)
    {
        CloseServerSock(tempRTPClientStream->RTPConnSocket);
        free(tempRTPClientStream);
        tempRTPClientStream = NULL;
        return RET_ERROR;
    }

    if (ClientConn->ClientSessionId  == 0)
    {
        srand((unsigned)GetTimeValue);
        ClientConn->ClientSessionId = rand() + (INT32)ClientConn;
    }

    /* Converting Session ID Integer to byte                                  */
    sessionIdString = (BYTE *) malloc(STRING_LEN_INT32);

    if (sessionIdString  == NULL)
    {
        CloseServerSock(tempRTPClientStream->RTPConnSocket);
        free(tempRTPClientStream);
        tempRTPClientStream = NULL;
        return RET_ERROR;
    }

    memset(sessionIdString, 0x00, STRING_LEN_INT32);
    sprintf((INT8 *)sessionIdString, "%d", ClientConn->ClientSessionId);

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Session", (BYTE *)sessionIdString) == RET_ERROR)
    {
        CloseServerSock(tempRTPClientStream->RTPConnSocket);
        free(tempRTPClientStream);
        tempRTPClientStream = NULL;
        free(sessionIdString);
        sessionIdString = NULL;
        return RET_ERROR;
    }

    if (sessionIdString)
    {
        free(sessionIdString);
        sessionIdString = NULL;
    }

    tempRTPClientStream->StreamSSRC = GetNtpTime();
    ClientConn->ClientState = CLIENT_READY_STATE;

    if (ClientConn->ClientStreamList == NULL)
    {
        ClientConn->ClientStreamList = tempRTPClientStream;
    }
    else
    {
        streamTemp = ClientConn->ClientStreamList;

        while (streamTemp->Next != NULL)
        {
            streamTemp = streamTemp->Next;
        }

        streamTemp->Next             = tempRTPClientStream;
        tempRTPClientStream->Prev    = streamTemp;
    }

    return RET_OK;
}

/*******************************************************************************
 * Function:    CheckAndDeleteClient
 *
 * Description: This function checks whether any client with same and port is
 *              connected to the server and if present then delete the old one.
 *
 * Parameters :
 *      [IN]  RTSPClient * ClientConn - Pointer of RTSP Client connection struct
 *      [IN]  INT32  clientPort       - RTP port
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Successful
 *          RET_ERROR - Error in removing Client
 ******************************************************************************/
INT32 CheckAndDeleteClient(RTSPClient *ClientConn, INT32 clientPort)
{
    RTPClientStream     *tempClientStreamPtr = NULL;
    RTSPClient          *rtspConnClient = NULL;    /* RTSP Client Variable     */
    RTSPServer          *rtspServer = NULL;        /* RTSP Server Variable     */
    RTSPSession         *rtspSession = NULL;       /* RTSP Session Variable    */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tClientConn = %d\n", ClientConn);
    rtspServer = gblRtspServer;

    /* traverse all server's all session to validate the client handle        */
    if (rtspServer)
    {
        rtspSession = rtspServer->RtspSessionList;

        /* traverse all session's clientlist to validate client handle        */
        while (rtspSession)
        {
            /* Traverse client list to validate client handle                 */
            rtspConnClient = rtspSession->SessionConnectedClientList;

            if (MutexLock(&(rtspSession->SessionClientListLock)) != RET_OK)
            {
                RtpRtspErrorPrint("Connected Client List Lock Failed \n");
                return RET_ERROR;
            }

            while (rtspConnClient)
            {
                /* Check the Client IP Address                                */
                if (!strcmp((INT8 *)rtspConnClient->ClientIp, (INT8 *)ClientConn->ClientIp))
                {
                    /* Traverse through stream list of client to check port   */
                    tempClientStreamPtr = rtspConnClient->ClientStreamList;

                    while (tempClientStreamPtr)
                    {
                        if (tempClientStreamPtr->ClientPort == clientPort)
                        {
                            if (MutexUnlock(&(rtspSession->SessionClientListLock)) != RET_OK)
                            {
                                RtpRtspErrorPrint("Connected Client List Unlock Failed \n");
                                return RET_ERROR;
                            }

                            RTSP_SER_PW("Destroying the old client with same RTP port and IP\n");
                            rtspConnClient->ClientState = CLIENT_INVALID_STATE;
                            CloseServerSock(rtspConnClient->ClientSocket);
                            rtspConnClient->ClientSocket = INVALID_SOCKET;
                            return RET_OK;
                        }

                        tempClientStreamPtr = tempClientStreamPtr->Next;
                    }
                }

                rtspConnClient = rtspConnClient->NextClient;
            }

            if (MutexUnlock(&(rtspSession->SessionClientListLock)) != RET_OK)
            {
                RtpRtspErrorPrint("Connected Client List Unlock Failed \n");
                return RET_ERROR;
            }

            rtspSession = rtspSession->NextSession;
        }
    }

    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
    return RET_OK;
}

/*******************************************************************************
 * Function:    RTSPPlayHandle
 *
 * Description: This function generate the response for PLAY request method
 *
 * Parameters :
 *      [IN]  RTSPClient * ClientConn - Pointer of RTSP Client connection struct
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Validation successful
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
//\\ 构造PLAY方法的应答包，同时调用事件回调函数传递FS_PLAY信息
INT32 RTSPPlayHandle(RTSPClient *ClientConn)
{
    BYTE    *sessionIdString;        /*  Store the pointer to session ID string  */
    BYTE    rtpInfoString[256] = {0};   // Store RTPInfo string
    BYTE    rangeString[256]   = {0};   // Store Range string
    INT32   trackId            = 0;
    BYTE    *RangeHeader       = NULL;
    INT32   startTime          = -1;
    INT32   endTime            = -1;
    INT32    retVal            = 0;
    RTSPState prevState;
    RTPClientStream *tmpRtpClientStream;

    if ((ClientConn->ClientState != CLIENT_READY_STATE) && (ClientConn->ClientState != CLIENT_PAUSE_STATE) && (ClientConn->ClientState != CLIENT_PLAYING_STATE))
    {
        return 455;
    }

    prevState = ClientConn->ClientState;

    if (ClientConn->RtspSessionPtr->RTPWriter_Callback != NULL)
    {
        RangeHeader = GetRequestMsgHeader(ClientConn->ClientRtspReqMsg, (BYTE *)"Range");

        if (RangeHeader != NULL)
        {
            sscanf((INT8 *)RangeHeader, "npt=%d-%d", &startTime, &endTime);

            if ((endTime > ClientConn->RtspSessionPtr->FileEndTime) ||
                (startTime > ClientConn->RtspSessionPtr->FileEndTime) ||
                (endTime != -1 && endTime < startTime))
            {
                return 457;
            }

            if ((prevState == CLIENT_READY_STATE) && (ClientConn->FileStartTime > 0))
            {
                startTime = ClientConn->FileStartTime;
            }

            if (ClientConn->ClientState == CLIENT_PLAYING_STATE)
            {
                ClientConn->ClientState = CLIENT_PAUSE_STATE;
            }
        }
    }

    /* Generate OK response for PLAY Method                                   */
    if (RTSPGenerateMethodResponse(ClientConn, 200) == RET_ERROR)
    {
        ClientConn->ClientState = prevState;
        return RET_ERROR;
    }

    if (CopyResponseHeader(ClientConn->ClientRtspResMsg, ClientConn->ClientRtspReqMsg, (BYTE *)"CSeq") == RET_ERROR)
    {
        ClientConn->ClientState = prevState;
        return RET_ERROR;
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Server", (BYTE *)RTSP_SERVER_NAME) == RET_ERROR)
    {
        ClientConn->ClientState = prevState;
        return RET_ERROR;
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Content-Length", (BYTE *)"0") == RET_ERROR)
    {
        ClientConn->ClientState = prevState;
        return RET_ERROR;
    }

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Cache-Control", (BYTE *)"no-cache") == RET_ERROR)
    {
        ClientConn->ClientState = prevState;
        return RET_ERROR;
    }

    sessionIdString = (BYTE *) malloc(STRING_LEN_INT32);

    if (sessionIdString  == NULL)
    {
        ClientConn->ClientState = prevState;
        return RET_ERROR;
    }

    memset(sessionIdString, 0x00, STRING_LEN_INT32);
    sprintf((INT8 *)sessionIdString, "%d", ClientConn->ClientSessionId);

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Session", (BYTE *)sessionIdString) == RET_ERROR)
    {
        free(sessionIdString);
        sessionIdString = NULL;
        ClientConn->ClientState = prevState;
        return RET_ERROR;
    }

    if ((RangeHeader != NULL) && (startTime >= 0) && (ClientConn->RtspSessionPtr->RTPWriter_Callback != NULL))
    {
        if (endTime < 0)
        {
            endTime = ClientConn->RtspSessionPtr->FileEndTime;
        }

        if (endTime > 0)
        {
            sprintf((INT8 *)rangeString, "npt=%d-%d", startTime, endTime);
        }
        else
        {
            sprintf((INT8 *)rangeString, "npt=%d-", startTime);
        }

        if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Range", (BYTE *)rangeString) == RET_ERROR)
        {
            free(sessionIdString);
            sessionIdString = NULL;
            ClientConn->ClientState = prevState;
            return RET_ERROR;
        }

        tmpRtpClientStream = ClientConn->ClientStreamList;
        sprintf((INT8 *)rtpInfoString, "url=%s/trackID=%d;rtptime=%d;seq=%d", ClientConn->ClientRtspReqMsg->ReqMsgURI, trackId, (INT32)(startTime * 90000), tmpRtpClientStream->StreamSeqNo + 1);
        trackId ++;
        tmpRtpClientStream = tmpRtpClientStream->Next;

        while (tmpRtpClientStream)
        {
            sprintf((INT8 *)rtpInfoString, "%s,url=%s/trackID=%d;rtptime=%d;seq=%d", rtpInfoString, ClientConn->ClientRtspReqMsg->ReqMsgURI, trackId, (INT32)(startTime * 90000), tmpRtpClientStream->StreamSeqNo + 1);
            tmpRtpClientStream = tmpRtpClientStream->Next;
            trackId ++;
        }

        if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"RTP-Info", (BYTE *)rtpInfoString) == RET_ERROR)
        {
            free(sessionIdString);
            sessionIdString = NULL;
            ClientConn->ClientState = prevState;
            return RET_ERROR;
        }
    }

    if (ClientConn->RtspSessionPtr->RTPWriter_Callback != NULL)
    {
        if (startTime < 0)
        {
            ClientConn->RtspSessionPtr->RTPWriter_Callback((INT32)ClientConn, (INT32)ClientConn->RtspSessionPtr, FS_PLAY, NULL);
        }
        else
        {
            retVal = ClientConn->RtspSessionPtr->RTPWriter_Callback((INT32)ClientConn, (INT32)ClientConn->RtspSessionPtr, FS_PLAY, (void *)&startTime);

            if (retVal != 0)
            {
                ClientConn->ClientState = prevState;
                free(sessionIdString);
                sessionIdString = NULL;
                return 501;
            }
        }
    }

    if ((ClientConn->RtspSessionPtr->RtcpFlag == 1) && (ClientConn->RtspSessionPtr->SessionMulticastFlag != 1) && (ClientConn->ClientState < CLIENT_PLAYING_STATE))
    {
        tmpRtpClientStream = ClientConn->ClientStreamList;

        while (tmpRtpClientStream)
        {
            tmpRtpClientStream->rtcpSessionInfo = 0;//(RTCPSessionStruct *)RTCPStart((INT32)ClientConn,(INT32)tmpRtpClientStream);

            if (tmpRtpClientStream->rtcpSessionInfo == 0)
            {
                RtpRtspErrorPrint("Unable to start RTCP session for Session: %s Client: %d Stream: %d\n", ClientConn->RtspSessionPtr->SessionName, ClientConn, tmpRtpClientStream);
            }
            else
            {
                if (RTCPSendSenderReportPeriodic((INT32)tmpRtpClientStream->rtcpSessionInfo, ClientConn->RtspSessionPtr->RtcpSRInterval, 0) != RTP_RTSP_OK)
                {
                    RtpRtspErrorPrint("Can't send SR report periodically\n");
                }

                RTSP_SER_PD("RTCP:: Session Name: %s, Sender Report Interval: %d, Stream Id: %d, Client Id: %d\n", ClientConn->RtspSessionPtr->SessionName, ClientConn->RtspSessionPtr->RtcpSRInterval,tmpRtpClientStream,ClientConn);
            }

            tmpRtpClientStream = tmpRtpClientStream->Next;
        }
    }

    ClientConn->ClientState = CLIENT_PLAYING_STATE;
    free(sessionIdString);
    sessionIdString = NULL;
    return RET_OK;
}

/*******************************************************************************
 * Function:    RTSPPauseHandle
 *
 * Description: This function generate the response for PAUSE request method
 *
 * Parameters :
 *      [IN]  RTSPClient * ClientConn - Pointer of RTSP Client connection struct
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Validation successful
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
INT32 RTSPPauseHandle(RTSPClient *ClientConn)
{
    BYTE *sessionIdString;        /*  Store the pointer to session ID string  */
    RTSP_SER_PD("PAUSE Handle received from client\n");
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tClientConn = %d\n", ClientConn);

    /* Check the State of Client                                              */
    if (ClientConn->ClientState != CLIENT_PLAYING_STATE)
    {
        RtpRtspErrorPrint("Invalid Method PAUSE Received for this State \n");
        /* Generate Method not valid for this state response message          */
        return 455;
    }

    /* Generate OK response for PAUSE Method                                  */
    if (RTSPGenerateMethodResponse(ClientConn, 200) == RET_ERROR)
    {
        RtpRtspErrorPrint("Cannot generate OK response for DESCRIBE method\n");
        return RET_ERROR;
    }

    /* Copy "CSeq" Header to Response from Request                            */
    if (CopyResponseHeader(ClientConn->ClientRtspResMsg,
                           ClientConn->ClientRtspReqMsg, (BYTE *)"CSeq") == RET_ERROR)
    {
        RtpRtspErrorPrint("Error In Copying Response Header Field\n");
        return RET_ERROR;
    }

    /* Add "Server" Header Field to Response Header                           */
    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Server",
                          (BYTE *)RTSP_SERVER_NAME) == RET_ERROR)
    {
        RtpRtspErrorPrint("Error In Adding Response Header Field\n");
        return RET_ERROR;
    }

    /* Add "Content-Length" Header Field to Response Header                   */
    if (AddResponseHeader(ClientConn->ClientRtspResMsg,
                          (BYTE *)"Content-Length", (BYTE *)"0") == RET_ERROR)
    {
        RtpRtspErrorPrint("Error In Adding Response Header Field\n");
        return RET_ERROR;
    }

    /* Add "Cache-Control" Header Field to Response Header                    */
    if (AddResponseHeader(ClientConn->ClientRtspResMsg,
                          (BYTE *)"Cache-Control", (BYTE *)"no-cache") == RET_ERROR)
    {
        RtpRtspErrorPrint("Error In Adding Response Header Field\n");
        return RET_ERROR;
    }

    /* Converting Session ID Integer to byte                                  */
    sessionIdString = (BYTE *) malloc(STRING_LEN_INT32);

    if (sessionIdString  == NULL)
    {
        RtpRtspErrorPrint("Cannot allocate memory\n");
        return RET_ERROR;
    }

    memset(sessionIdString, 0x00, STRING_LEN_INT32);
    sprintf((INT8 *)sessionIdString, "%d", ClientConn->ClientSessionId);

    /* Add "Session" Header Field to Response Header                          */
    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Session",
                          (BYTE *)sessionIdString) == RET_ERROR)
    {
        /* Free the allocated memory                                          */
        free(sessionIdString);
        sessionIdString = NULL;
        RtpRtspErrorPrint("Error In Adding Response Header Field\n");
        return RET_ERROR;
    }

    /* Change the STATE of session to pause                                   */
    ClientConn->ClientState = CLIENT_PAUSE_STATE;

    if (ClientConn->RtspSessionPtr->RTPWriter_Callback != NULL)
    {
        ClientConn->RtspSessionPtr->RTPWriter_Callback((INT32)ClientConn,
                (INT32)ClientConn->RtspSessionPtr,
                FS_PAUSE,
                NULL);
    }

    /* Free the allocated memory                                              */
    free(sessionIdString);
    sessionIdString = NULL;
    RtpRtspDebugPrint(DBG_LEVEL_3, "\n\tEXIT : \nReturn Successfully\n");
    return RET_OK;
}

/*******************************************************************************
 * Function:    RTSPTeardownHandle
 *
 * Description: This function generate the response for TEARDOWN request method
 *
 * Parameters :
  *      [IN]  RTSPClient * ClientConn - Pointer of RTSP Client connection struct
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Validation successful
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
INT32 RTSPTeardownHandle(RTSPClient *ClientConn)
{
    //ht 2016.2.16
    RTSP_SER_PD("[FILE=%s][FUNCTION=%s][LINE=%d]\n",__FILE__,__FUNCTION__,__LINE__);
    BYTE *sessionIdString ;           /* Store the session Id string pointer  */
    RTSP_SER_PD("TEARDOWN Handle received from client\n");
    RTSP_SER_PD(" ENTER : \n\tClientConn = %d\n", ClientConn);

    /* Check the State of Client                                              */
    if (!((ClientConn->ClientState == CLIENT_PLAYING_STATE) ||
          (ClientConn->ClientState == CLIENT_PAUSE_STATE) ||
          (ClientConn->ClientState == CLIENT_READY_STATE) ||  /*cyf add 否则setup后再teardown就无法销毁资源*/
          (ClientConn->ClientState == CLIENT_INIT_STATE)))
    {
        RtpRtspErrorPrint("Invalid Method TEARDOWN Received for this State\n");
        /* Generate Method not valid for this state response message          */
        return 455;
    }

    /* Generate Method Response                                               */
    if (RTSPGenerateMethodResponse(ClientConn, 200) == RET_ERROR)
    {
        RtpRtspErrorPrint("Cannot generate OK response for DESCRIBE method\n");
        return RET_ERROR;
    }

    /* Copy "CSeq" Header to Response from Request                            */
    if (CopyResponseHeader
        (ClientConn->ClientRtspResMsg, ClientConn->ClientRtspReqMsg,
         (BYTE *)"CSeq") == RET_ERROR)
    {
        RtpRtspErrorPrint("Error In Copying Response Header Field\n");
        return RET_ERROR;
    }

    /* Add "Server" Header Field to Response Header                           */
    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Server",
                          (BYTE *)RTSP_SERVER_NAME) == RET_ERROR)
    {
        RtpRtspErrorPrint("Error In Adding Response Header Field\n");
        return RET_ERROR;
    }

    /* Add "Content-Length" Header Field to Response Header                   */
    if (AddResponseHeader(ClientConn->ClientRtspResMsg,
                          (BYTE *)"Content-Length", (BYTE *)"0") == RET_ERROR)
    {
        RtpRtspErrorPrint("Error In Adding Response Header Field\n");
        return RET_ERROR;
    }

    /* Add "Cache-Control" Header Field to Response Header                    */
    if (AddResponseHeader(ClientConn->ClientRtspResMsg,
                          (BYTE *)"Cache-Control", (BYTE *)"no-cache") == RET_ERROR)
    {
        RtpRtspErrorPrint("Error In Adding Response Header Field\n");
        return RET_ERROR;
    }

    /* Converting Session ID Integer to byte                                  */
    sessionIdString = (BYTE *) malloc(STRING_LEN_INT32);

    if (sessionIdString  == NULL)
    {
        RtpRtspErrorPrint("Cannot allocate memory\n");
        return RET_ERROR;
    }

    memset(sessionIdString, 0x00, STRING_LEN_INT32);
    sprintf((INT8 *)sessionIdString, "%d", ClientConn->ClientSessionId);

    /* Add "Session" Header Field to Response Header                          */
    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Session",
                          (BYTE *)sessionIdString) == RET_ERROR)
    {
        /* Free the allocated memory                                          */
        free(sessionIdString);
        sessionIdString = NULL;
        RtpRtspErrorPrint("Error In Adding Response Header Field\n");
        return RET_ERROR;
    }
    /* Change the STATE of session to Invalid                                 */
    ClientConn->ClientState = CLIENT_INVALID_STATE;

    if (ClientConn->RtspSessionPtr->RTPWriter_Callback != NULL)
    {
        ClientConn->RtspSessionPtr->RTPWriter_Callback((INT32)ClientConn,
                (INT32)ClientConn->RtspSessionPtr,
                FS_STOP,
                NULL);
    }
    free(sessionIdString);
    sessionIdString = NULL;
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
    return RET_OK;
}

/*******************************************************************************
 * Function:    CommonMsgValidation
 *
 * Description: This function verify the common field of message structure
 *
 * Parameters :
 *      [IN] RTSPClient * ClientConn - RTSP connection struct pointer
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Validation successful
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
//\\ 检查RTSP请求是否正确
INT32 CommonMsgValidation(RTSPClient *ClientConn)
{
    //RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tClientConn = %d\n", ClientConn);
    /* Check RTSP/HTTP Version, Is it valid or not ?                          */
    if (ClientConn->ClientRtspReqMsg->ReqMethod == HTTP_METHOD_GET)
    {
        if (!(strcmp((INT8 *)ClientConn->ClientRtspReqMsg->ReqRtspVersion, DEFAULT_HTTP_VERSION) == 0))
        {
            RtpRtspErrorPrint("Invalid HTTP Version Found in Request Message\n");
            /* Generate 505 Error Response                                    */
            return 505;
        }
    }
    else
    {
        if (!(strcmp((INT8 *)ClientConn->ClientRtspReqMsg->ReqRtspVersion, DEFAULT_RTSP_VERSION) == 0))
        {
            RtpRtspErrorPrint("Invalid RTSP Version Found in Request Message\n");
            /* Generate 505 Error Response                                        */
            return 505;
        }
    }

    /* Validate the method of the given request                               */
    if (ClientConn->ClientRtspReqMsg->ReqMethod > RTSP_METHOD_PAUSE)
    {
        RtpRtspErrorPrint("RTSP request method (%d) not supported \n", ClientConn->ClientRtspReqMsg->ReqMethod);
        /* Generate 501 Error Response                                        */
        return 501;
    }

    /* validation the sequence number                                         */
    if (ClientConn->ClientLastMsgSeqNo == 0)
    {
        ClientConn->ClientLastMsgSeqNo = ClientConn->ClientRtspReqMsg->ReqSeqNumber;
    }
    else
    {
        if ((ClientConn->ClientLastMsgSeqNo + 1) != ClientConn->ClientRtspReqMsg->ReqSeqNumber)
        {
            RTSP_SER_PD("Sequence Number (%d) not as per expected value (%d)\n",
                        ClientConn->ClientRtspReqMsg->ReqMethod,
                        (ClientConn->ClientRtspReqMsg->ReqSeqNumber + 1));
            /* Generate 400 Error Response                                    */
            return 400;
        }

        ClientConn->ClientLastMsgSeqNo = ClientConn->ClientRtspReqMsg->ReqSeqNumber;
    }

    //      RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
    return RET_OK;
}

/*******************************************************************************
 * Function:    ConvertMethodString
 *
 * Description: This function convert the method string to integer value.
 *
 * Parameters :
 *      [IN]  BYTE* Buffer - Pointer containing the name of METHOD
 *
 * Return Value:
 *      RTSPMsgMethod  - RTSP message method type
 ******************************************************************************/
RTSPMsgMethod ConvertMethodString(BYTE *Buffer)
{
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tBuffer : %s\n", Buffer);

    /* Compare the string and return the value                                */
    if (!strcmp((INT8 *)Buffer, "GET"))
    {
        return HTTP_METHOD_GET;
    }
    else if (!strcmp((INT8 *)Buffer, "POST"))
    {
        return HTTP_METHOD_POST;
    }
    else if (!strcmp((INT8 *)Buffer, "OPTIONS"))
    {
        return RTSP_METHOD_OPTIONS;
    }
    else if (!strcmp((INT8 *)Buffer, "DESCRIBE"))
    {
        return RTSP_METHOD_DESCRIBE;
    }
    else if (!strcmp((INT8 *)Buffer, "SETUP"))
    {
        return RTSP_METHOD_SETUP;
    }
    else if (!strcmp((INT8 *)Buffer, "PLAY"))
    {
        return RTSP_METHOD_PLAY;
    }
    else if (!strcmp((INT8 *)Buffer, "PAUSE"))
    {
        return RTSP_METHOD_PAUSE;
    }
    else if (!strcmp((INT8 *)Buffer, "TEARDOWN"))
    {
        return RTSP_METHOD_TEARDOWN;
    }
    else if (!strcmp((INT8 *)Buffer, "ANNOUNCE"))
    {
        return RTSP_METHOD_ANNOUNCE;
    }
    else if (!strcmp((INT8 *)Buffer, "GET_PARAMETER"))
    {
        return RTSP_METHOD_GET_PARAMETER;
    }
    else if (!strcmp((INT8 *)Buffer, "SET_PARAMETER"))
    {
        return RTSP_METHOD_SET_PARAMETER;
    }
    else if (!strcmp((INT8 *)Buffer, "REDIRECT"))
    {
        return RTSP_METHOD_REDIRECT;
    }
    else if (!strcmp((INT8 *)Buffer, "RECORD"))
    {
        return RTSP_METHOD_RECORD;
    }
    else
    {
        return RTSP_METHOD_INVALID;
    }
}

/*******************************************************************************
 * Function:    ConvertToNALString
 *
 * Description: This function convert the input string to NAL character string
 *
 * Parameters :
 *      [IN/OUT]  BYTE * DestPtr   - Pointer of destination buffer
 *      [IN]      BYTE * SourcePtr - Pointer of source buffer
 *      [IN]      INT32  DataLen   - Length of source buffer
 *
 * Return Value:
 *      INT32 - Number of string converted
 ******************************************************************************/
INT32 ConvertToNALString(BYTE *DestPtr, const BYTE *SourcePtr, INT32 DataLen)
{
    BYTE    *tempPtr;       /* Pointer to traverse the input string           */
    INT32   indexCnt;       /* Local counter                                  */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tDestPtr = %d \n\tSourcePtr = %d\n\tDataLen = %d",
                      DestPtr, SourcePtr, DataLen);
    /* Store the destination pointer to local variable                        */
    tempPtr = DestPtr;

    /* Loop to traverse the string and convert the string                     */
    for (indexCnt = 0; indexCnt < DataLen - 2; indexCnt += 3)
    {
        *tempPtr++ = NALCharSet[(SourcePtr[indexCnt] >> 2) & 0x3F];
        *tempPtr++ = NALCharSet[((SourcePtr[indexCnt] & 0x3) << 4) |
                                ((INT32)(SourcePtr[indexCnt + 1] & 0xF0) >> 4)];
        *tempPtr++ = NALCharSet[((SourcePtr[indexCnt + 1] & 0xF) << 2) |
                                ((INT32)(SourcePtr[indexCnt + 2] & 0xC0) >> 6)];
        *tempPtr++ = NALCharSet[SourcePtr[indexCnt + 2] & 0x3F];
    }

    /* If last character of string is not connected then convert them also    */
    if (indexCnt < DataLen)
    {
        *tempPtr++ = NALCharSet[(SourcePtr[indexCnt] >> 2) & 0x3F];

        if (indexCnt == (DataLen - 1))
        {
            *tempPtr++ = NALCharSet[((SourcePtr[indexCnt] & 0x3) << 4)];
            *tempPtr++ = '=';
        }
        else
        {
            *tempPtr++ = NALCharSet[((SourcePtr[indexCnt] & 0x3) << 4) |
                                    ((INT32)(SourcePtr[indexCnt + 1] & 0xF0) >> 4)];
            *tempPtr++ = NALCharSet[((SourcePtr[indexCnt + 1] & 0xF) << 2)];
        }

        *tempPtr++     = '=';
    }

    /* Add null string at the end of string                                   */
    *tempPtr++ = '\0';
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\ttempPtr - DestPtr = %d\n",
                      (tempPtr - DestPtr));
    return tempPtr - DestPtr;
}

/*******************************************************************************
 * Function:     AddResponseHeader
 *
 * Description:  This function add the given header and its value in the given
 *               RTSPResponseMsg structure.
 *
 * Parameters:
 *      [IN]    RTSPResponseMsg * ResponseMsg - RTSP Response msg structure
 *      [IN]    BYTE            * HeaderName  - Header name string pointer
 *      [IN]    BYTE            * HeaderValue - Header value string pointer
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Error code found and string stored given pointer
 *          RET_ERROR - Error code not found
 ******************************************************************************/
INT32 AddResponseHeader(RTSPResponseMsg *ResponseMsg, BYTE *HeaderName,
                        BYTE *HeaderValue)
{
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tResponseMsg = %d\n\tHeaderName = %s\n\tHeaderValue = %s\n",
                      ResponseMsg, HeaderName, HeaderValue);

    /* Maximum Number of Header Fields are added or not                       */
    if (ResponseMsg->ResHeadersCount == MAX_HEADER_NUMBER)
    {
        RtpRtspErrorPrint("Invalid header count of response message\n");
        return RET_ERROR;
    }

    /* Store Name of Header Field in MsgHeader                                */
    ResponseMsg->ResMsgHeaders[ResponseMsg->ResHeadersCount].HeaderName =
        (BYTE *) malloc(strlen((INT8 *)HeaderName) + 1);

    if (ResponseMsg->ResMsgHeaders[ResponseMsg->ResHeadersCount].HeaderName == NULL)
    {
        RtpRtspErrorPrint("Can not allocate memory for response header name\n");
        return RET_ERROR;
    }

    memset(ResponseMsg->ResMsgHeaders[ResponseMsg->ResHeadersCount].HeaderName, 0x00,
           strlen((INT8 *)HeaderName) + 1);
    memcpy(ResponseMsg->ResMsgHeaders[ResponseMsg->ResHeadersCount].HeaderName,
           HeaderName, strlen((INT8 *)HeaderName));
    /* Store Value of Header Field in MsgHeader                               */
    ResponseMsg->ResMsgHeaders[ResponseMsg->ResHeadersCount].HeaderValue =
        (BYTE *) malloc(strlen((INT8 *)HeaderValue) + 1);

    if (ResponseMsg->ResMsgHeaders[ResponseMsg->ResHeadersCount].HeaderValue == NULL)
    {
        RtpRtspErrorPrint("Can not allocate memory for response header value\n");
        free(ResponseMsg->ResMsgHeaders[ResponseMsg->ResHeadersCount].HeaderName);
        ResponseMsg->ResMsgHeaders[ResponseMsg->ResHeadersCount].HeaderName = NULL;
        return RET_ERROR;
    }

    memset(ResponseMsg->ResMsgHeaders[ResponseMsg->ResHeadersCount].HeaderValue, 0x00,
           strlen((INT8 *)HeaderValue) + 1);
    memcpy(ResponseMsg->ResMsgHeaders[ResponseMsg->ResHeadersCount].HeaderValue,
           HeaderValue, strlen((INT8 *)HeaderValue));
    /* Increment the Message Header Count                                     */
    ResponseMsg->ResHeadersCount++;
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
    return RET_OK;
}

/*******************************************************************************
 * Function:     CopyResponseHeader
 *
 * Description:  This function copy the given header from Request message struct
 *               to response Message structure.
 *
 * Parameters:
 *      [IN]    RTSPResponseMsg * ResponseMsg - RTSP Response message structure
 *      [IN]    RTSPRequestMsg  * RequestMsg  - RTSP Request message structure
 *      [IN]    BYTE            * HeaderName  - Header name string pointer
 *
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Error code found and string stored given pointer
 *          RET_ERROR - Error code not found
 ******************************************************************************/
INT32 CopyResponseHeader(RTSPResponseMsg *ResponseMsg,
                         RTSPRequestMsg   *RequestMsg,
                         BYTE             *HeaderName)
{
    INT32 counter;          /* Local counter variable                         */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tResponseMsg = %d \n\tRequestMsg = %d\
                        \n\tHeaderName = %s \n", ResponseMsg, RequestMsg, HeaderName);

    for (counter = 0; counter < RequestMsg->ReqHeadersCount; counter++)
    {
        if (!strcmp((INT8 *)RequestMsg->ReqMsgHeaders[counter].HeaderName, (INT8 *)HeaderName))
        {
            if (AddResponseHeader(ResponseMsg,
                                  RequestMsg->ReqMsgHeaders[counter].HeaderName,
                                  RequestMsg->ReqMsgHeaders[counter].HeaderValue
                                 ) == RET_OK)
            {
                RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
                return RET_OK;
            }
            else
            {
                return RET_ERROR;
            }
        }
    }

    return RET_ERROR;
}

/*******************************************************************************
 * Function:    GetRequestMsgHeader
 *
 * Description: This function return given header value from the request msg
 *              structure
 *
 * Parameters:
 *      [IN]  RTSPRequestMsg  *RequestMsg   - Pointer to Request msg struct
 *      [IN]  BYTE            *HeaderName   - Header Name string pointer
 *
 * Return Value:
 *      BYTE *Value - Value of Header Name, if Header is present, else NULL.
 *
 ******************************************************************************/
BYTE *GetRequestMsgHeader(RTSPRequestMsg  *RequestMsg, BYTE *HeaderName)
{
    INT32 indexCnt;                 /* Local counter                          */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tRequestMsg = %d \n\tHeaderName = %s",
                      RequestMsg, HeaderName);

    if (RequestMsg)
    {
        for (indexCnt = 0; indexCnt < RequestMsg->ReqHeadersCount; indexCnt++)
        {
            if (!strcmp((INT8 *)RequestMsg->ReqMsgHeaders[indexCnt].HeaderName, (INT8 *)HeaderName))
            {
                RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tMsgHeader Value = %s\n",
                                  RequestMsg->ReqMsgHeaders[indexCnt].HeaderValue);
                return RequestMsg->ReqMsgHeaders[indexCnt].HeaderValue;
            }
        }
    }

    return NULL;
}

/*******************************************************************************
 * Function:    ParseNALHeader
 *
 * Description: This function Parses NAL Header from data
 *
 * Parameters :
 *      [IN]  BYTE * InputBuff - Pointer of input buffer
 *      [IN]  INT32  InputLen  - Length of input buffer
 *      [OUT] BYTE * SpsBuff   - Pointer of SPS buffer
 *      [OUT] INT32* SpsLen    - Pointer to store the SPS buffer Length
 *      [OUT] BYTE * PpsBuff   - Pointer of PPS buffer
 *      [OUT] INT32* PpsLen    - Pointer to store the PPS buffer Length
 *
 * Return Value:
 *          RET_OK    - successful parsing of NAL header
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
INT32 ParseNALHeader(BYTE *InputBuff, INT32 InputLen,
                     BYTE *SpsBuff,   INT32 *SpsLen,
                     BYTE *PpsBuff,   INT32 *PpsLen, BYTE *profileLevelId
                    )
{
    INT32 nalType;              /* Local variable to store NAL header type    */
    INT32 nalOffset     = 1;    /* Local variable to store NAL header offset  */
    INT32 nalSize       = 0;    /* Local variable to store NAL header size    */
    INT32 nalStartCode  = 0;    /* Local variable - store NAL header startcode*/
    INT32 nalEncoded    = 0;    /* Local variable - store NAL encoded length  */
    INT32 sizeFlag      = 0;    /* Local variable - store Flag of size        */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tInputBuff = %d \n\tInputLen = %d\
                        \n\tspsBuff = %d \n\tspsLen = %d \n\tppsBuff = %d \n\tppsLen = %d \n",
                      InputBuff, InputLen, SpsBuff, SpsLen, PpsBuff, PpsLen);

    /* Validate the length of the input buffer                                */
    if (InputLen <= 4)
    {
        RtpRtspErrorPrint("Input length of NAL buffer is very less\n");
        return RET_ERROR;
    }

    if ((PpsLen == NULL) || (SpsLen == NULL))
    {
        RtpRtspErrorPrint("Input pointer(s) of SPS and PPS buffer or length is NULL\n");
        return RET_ERROR;
    }

    /* Loop to find the NAL header                                            */
    while (InputBuff[0] == 0 && InputBuff[1] == 0 &&
           InputBuff[2] == 0 && InputBuff[3] == 1)
    {
        sizeFlag = 0;
        nalType = InputBuff[4] & 0x1f;
        RtpRtspDebugPrint(DBG_LEVEL_5, "NAL Type = %d\n", nalType);

        /* Find the length till next NAL start                                */
        for (nalOffset = 1; nalOffset + 3 < InputLen; nalOffset++)
        {
            if ((InputBuff[nalOffset] == 0) && (InputBuff[nalOffset + 1] == 0) &&
                (InputBuff[nalOffset + 2] == 0) &&
                (InputBuff[nalOffset + 3] == 1))
            {
                nalStartCode = nalOffset;
                sizeFlag = 1;
                break;
            }

            nalStartCode = nalOffset;
        }

        nalSize = nalStartCode ? nalStartCode : InputLen;

        if (nalType == 7)
        {
            if (sizeFlag == 1)
            {
                nalEncoded         = ConvertToNALString(SpsBuff, &InputBuff[4], nalSize - 4);
            }
            else
            {
                nalEncoded         = ConvertToNALString(SpsBuff, &InputBuff[4], nalSize);
            }

            SpsBuff[nalEncoded] = '\0';
            *SpsLen            = nalSize;
            // cyf add
            profileLevelId[0] = InputBuff[5];
            profileLevelId[1] = InputBuff[6];
            profileLevelId[2] = InputBuff[7];
            RtpRtspDebugPrint(DBG_LEVEL_5, "SPS NAL Header = %s\n", SpsBuff);
        }

        if (nalType == 8)
        {
            if (sizeFlag == 1)
            {
                nalEncoded         = ConvertToNALString(PpsBuff, &InputBuff[4], nalSize - 4);
            }
            else
            {
                nalEncoded         = ConvertToNALString(PpsBuff, &InputBuff[4], nalSize);
            }

            PpsBuff[nalEncoded] = '\0';
            *PpsLen            = nalSize;
            RtpRtspDebugPrint(DBG_LEVEL_5, "PPS NAL Header = %s\n", PpsBuff);
            break;
        }

        InputLen  -= nalSize;
        InputBuff += nalSize;
    }

    if (SpsBuff == NULL || PpsBuff == NULL)
    {
        RtpRtspErrorPrint("SPS and PPS header not generated from given buffer \n");
        return RET_ERROR;
    }
    else
    {
        RtpRtspDebugPrint(DBG_LEVEL_5, "SPS and PPS header generated\n");
        RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
        return RET_OK;
    }
}

/*******************************************************************************
 * Function:    ParseNALHeader
 *
 * Description: This function Parses NAL Header from data
 *
 * Parameters :
 *      [IN]  BYTE * InputBuff - Pointer of input buffer
 *      [IN]  INT32  InputLen  - Length of input buffer
 *      [OUT] BYTE * SpsBuff   - Pointer of SPS buffer
 *      [OUT] INT32* SpsLen    - Pointer to store the SPS buffer Length
 *      [OUT] BYTE * PpsBuff   - Pointer of PPS buffer
 *      [OUT] INT32* PpsLen    - Pointer to store the PPS buffer Length
 *
 * Return Value:
 *          RET_OK    - successful parsing of NAL header
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
 /*cb change 2016.8.5 .添加h265的支持 start*/ 
INT32 ParseNALHeaderH265(BYTE *InputBuff, INT32 InputLen,
                         BYTE *VpsBuff,   INT32 *VpsLen,
                         BYTE *SpsBuff,   INT32 *SpsLen,
                         BYTE *PpsBuff,   INT32 *PpsLen, BYTE *profileLevelId
                        )
{
    // 在该帧视频找搜索sps和pps
    BYTE    *pFrameBuf = InputBuff;
    int     nRemainSz = InputLen;
    BYTE    *temppt = NULL;
    int     tempSz = 0;
    INT32 nalEncoded    = 0;

    char tmp_buf[52];
    int tmp_len = 0;
	
    // 找到第一个00 00 00 01
    while (nRemainSz >= 4 && (pFrameBuf[0] != 0 || pFrameBuf[1] != 0 || pFrameBuf[2] != 0 || pFrameBuf[3] != 1))
    {
        nRemainSz--;
        pFrameBuf++;
    }
    temppt = pFrameBuf++;
    tempSz = nRemainSz--;

    // 找到第二个00 00 00 01
    while (nRemainSz >= 4 && (pFrameBuf[0] != 0 || pFrameBuf[1] != 0 || pFrameBuf[2] != 0 || pFrameBuf[3] != 1))
    {
        nRemainSz--;
        pFrameBuf++;
    }
	
    nalEncoded  = ConvertToNALString(VpsBuff, &temppt[4], tempSz-nRemainSz - 4);
    VpsBuff[nalEncoded] = 0;
	*VpsLen = nalEncoded;

    temppt = pFrameBuf++;
    tempSz = nRemainSz--;
    // 找到第三个00 00 00 01
    while (nRemainSz >= 4 && (pFrameBuf[0] != 0 || pFrameBuf[1] != 0 || pFrameBuf[2] != 0 || pFrameBuf[3] != 1))
    {
        nRemainSz--;
        pFrameBuf++;
    }

    nalEncoded  = ConvertToNALString(SpsBuff, &temppt[4], tempSz-nRemainSz - 4);
    SpsBuff[nalEncoded] = 0;
	*SpsLen = nalEncoded;

    temppt = pFrameBuf++;
    tempSz = nRemainSz--;

    nalEncoded  = ConvertToNALString(PpsBuff, &temppt[4],tempSz - 4);
    PpsBuff[nalEncoded] = 0;
	*PpsLen = nalEncoded;

	

    if (VpsBuff == NULL || SpsBuff == NULL || PpsBuff == NULL)
    {
        RtpRtspErrorPrint("VpsBuff and SPS and PPS header not generated from given buffer \n");
        return RET_ERROR;
    }
    else
    {
        RtpRtspDebugPrint(DBG_LEVEL_5, "VpsBuff and SPS and PPS header generated\n");
        RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
        return RET_OK;
    }
}
/*cb change 2016.8.5 .添加h265的支持*/ 

/*******************************************************************************
 * Function:    ParseAACData
 *
 * Description: This function Parses the AAC Data and store config in Buffer
 *
 * Parameters :
 *      [IN]  BYTE * InputBuff - Pointer of input buffer
 *      [IN]  INT32  InputLen  - Length of input buffer
 *      [OUT] BYTE * AacBuff   - Pointer of AAC buffer
 *
 * Return Value:
 *          RET_OK    - sucessfull parsing of AAC header
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
INT32 ParseAACData(BYTE *InputBuff, INT32 InputLen, BYTE *AacBuff)
{
    BYTE    configArray[2];         /* Config character string                */
    INT32   profileVal;             /* Profile value                          */
    INT32   sampleRateId;           /* Sample rate ID                         */
    INT32   channelsVal;            /* Channel Value                          */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tInputBuff = %d\n\tInputLen = %d\
                                    \n\tAacBuff = %d\n", InputBuff, InputLen, AacBuff);

    if (InputBuff == NULL || InputLen < 3)
    {
        RtpRtspErrorPrint("Invalid input arguments passed\n");
        return RET_ERROR;
    }

    if (InputBuff[0] == 0xff && InputBuff[1] == 0xf1 /*&&
        InputBuff[2] == 0x4c && InputBuff[3] == 0x80 */)
    {
        profileVal      = InputBuff[2] >> 6;
        sampleRateId    = (InputBuff[2] >> 2) & 0x0f;
        channelsVal     = ((InputBuff[2] & 0x01) << 2) | ((InputBuff[3] >> 6) & 0x03);
        configArray[0]  = (profileVal + 1) << 3 | (sampleRateId >> 1);
        configArray[1]  = ((sampleRateId & 0x01) << 7) | (channelsVal << 3);
        ConvertToHex(AacBuff, configArray, 2);
        RtpRtspDebugPrint(DBG_LEVEL_5, "AAC Config Value = %s", AacBuff);
    }

    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
    return RET_OK;
}

/*******************************************************************************
 * Function:    ConverToHex
 *
 * Description: This function convert the input string to HEX character string
 *
 * Parameters :
 *      [IN]  BYTE * OutBuf   - Pointer of output buffer string
 *      [IN]  BYTE * PData    - Pointer of input buffer string
 *      [OUT] BYTE * DataSize - size of input string
 *
 * Return Value:
 *          None
 ******************************************************************************/
void ConvertToHex(BYTE *OutBuf, BYTE *PData, INT32 DataSize)
{
    static const BYTE hexArray[20] = "0123456789abcdef";/* Array of HEX digits*/
    INT32             indexCnt;                         /* Local Counter      */

    for (indexCnt = 0; indexCnt < DataSize; indexCnt++)
    {
        OutBuf[2 * indexCnt + 0] = hexArray[(PData[indexCnt] >> 4) & 0xf];
        OutBuf[2 * indexCnt + 1] = hexArray[(PData[indexCnt]) & 0xf];
    }

    OutBuf[2 * DataSize] = '\0';
}

/*******************************************************************************
 * Function:    ParseVOLHeader
 *
 * Description: This function Parses the VOL Header and store VOL in Buffer
 *
 * Parameters :
 *      [IN]  BYTE * InputBuff - Pointer of input buffer
 *      [IN]  INT32  InputLen  - Length of input buffer
 *      [OUT] BYTE * VolBuff   - Pointer of VOL buffer
 *
 * Return Value:
 *          RET_OK    - successful parsing of VOL header
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
INT32 ParseVOLHeader(BYTE *InputBuff, INT32 InputLen, BYTE *VolBuff)
{
    BYTE    parseVOLDataMem[MAX_SMALL_BUFF_SIZE];/*  Stores VOL Header        */
    INT32   outerCnt;               /* Local variable as a counter            */
    INT32   innerCnt;               /* Local variable as a counter            */
    INT32   ptr = 0;                /* Local Variable to store index value    */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tInputBuff = %d\n\tInputLen = %d\
                        \n\tVolBuff = %d \n", InputBuff, InputLen, VolBuff);

    if (InputBuff == NULL || InputLen < 3)
    {
        RtpRtspErrorPrint("Invalid input arguments passed\n");
        return RET_ERROR;
    }

    memset(parseVOLDataMem, 0x00, MAX_SMALL_BUFF_SIZE);

    for (outerCnt = 0; outerCnt < InputLen ; outerCnt++)
    {
        if (InputBuff[outerCnt]      == 0x00 &&
            InputBuff[outerCnt + 1]  == 0x00 &&
            InputBuff[outerCnt + 2]  == 0x01 &&
            InputBuff[outerCnt + 3]  == 0x20)
        {
            for (innerCnt = outerCnt; innerCnt < InputLen - outerCnt ; innerCnt++)
            {
                parseVOLDataMem[ptr] = InputBuff[innerCnt];
                ptr++;

                if (InputBuff[innerCnt + 1] == 0x00 &&
                    InputBuff[innerCnt + 2] == 0x00 &&
                    InputBuff[innerCnt + 3] == 0x01)
                {
                    ConvertToHex(VolBuff, parseVOLDataMem, ptr);
                    RtpRtspDebugPrint(DBG_LEVEL_5, "Vol Buffer Found  %s \n\n", VolBuff);
                    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
                    return RET_OK;
                }
            }
        }
    }

    return RET_ERROR;
}


int  buildSessionIDAndSessionVersion(char *session, int bufLength)
{
    struct timeval currentTime;
    unsigned long timeSeq = 0;
    char StringBuf[64];

    if(NULL == session || bufLength < 1)
    {
        RTSP_SER_PE("\n Invalid session buffer para !\n\r"); //ht 2016.2.16
        return -1;
    }


    memset(&currentTime, 0, sizeof(currentTime));
    gettimeofday(&currentTime, NULL);

    memset(StringBuf, 0, sizeof(StringBuf));
    timeSeq = (WS_U64)currentTime.tv_sec * (WS_U64)1000 * (WS_U64)1000 + (WS_U64)currentTime.tv_usec;                   // change by linhh 20160525
    snprintf(StringBuf, sizeof(StringBuf) - 1, "%lu", timeSeq);

    strncpy(session, StringBuf, bufLength - 1);

    return 0;
}
/*******************************************************************************
 * Function:    RtspGenerateSDP
 * Description: This function generate SDP response for DESCRIBE request method
 * Parameters :
 *      [IN]  RTSPClient * ClientConn - Pointer of Connected Client
 * Return Value:
 *      INT32 - Returns error/success code
 *          RET_OK    - Validation successful
 *          RET_ERROR - Error in validation.
 ******************************************************************************/
//\\ DESCRIBE方法应答包，内部需要组建SDP信息，在发送该包之前需要收集好SPS与PPS信息
INT32 RtspGenerateSDP(RTSPClient *ClientConn)
{
    BYTE            *sdpString = NULL;             /* Local SDP string pointer*/
    BYTE            *vpsHeader = NULL;             /* VPS Header data pointer *//*cb change 2016.8.5 .添加h265的支持*/ 
    BYTE            *spsHeader = NULL;             /* SPS Header data pointer */
    BYTE            *ppsHeader = NULL;             /* PPS Header data pointer */
    BYTE            *volHeader = NULL;             /* Vol Header Data Pointer */
    BYTE            *aacConfig = NULL;             /* AAC Config Data Pointer */
    BYTE            sdpSizeStr[STRING_LEN_INT32];  /* Store SDP size string   */
    BYTE            sdpSessionId[STRING_LEN_INT32 + STRING_LEN_INT32];        /* SDP Session ID          */
    BYTE            sdpSessionVersion[STRING_LEN_INT32 + STRING_LEN_INT32];/* SDP Session Version          */
    INT32           baseAddr = 0;                  /* Store SDP string end ptr*/
    INT32           vpsLen = 0;                    /* vps header length       *//*cb change 2016.8.5 .添加h265的支持*/ 
    INT32           spsLen = 0;                    /* sps header length       */
    INT32           ppsLen = 0;                    /* pps header length       */
    INT32           trackId = 0;                   /* Value of Track ID       */
    RTPSessionStream *rtspStream = NULL;           /* Local Stream Pointer    */
    RTSPSession     *rtspSession = NULL;           /* Local RTSPSession pointer*/
    sdpString = (BYTE *) malloc(MAX_BIG_BUFF_SIZE);

    if (sdpString == NULL)
    {
        return RET_ERROR;
    }

    memset(sdpString, 0, MAX_BIG_BUFF_SIZE);
    memset(sdpSessionId, 0, sizeof(sdpSessionId));
    buildSessionIDAndSessionVersion((char *)sdpSessionId, sizeof(sdpSessionId));
    memset(sdpSessionVersion, 0, sizeof(sdpSessionVersion));
    strncpy((char *)sdpSessionVersion, (char *)sdpSessionId, sizeof(sdpSessionVersion));
    rtspSession = ClientConn->RtspSessionPtr;

	if (rtspSession->SessionMulticastFlag == 0)
    {
        if (rtspSession->FileEndTime == 0)
        {
            baseAddr =  sprintf((INT8 *)sdpString, 
                "v=0\r\no=RTSP %s %s IN IP4 0.0.0.0\r\ns=RTSP Server\r\nc=IN IP4 0.0.0.0\r\nt=0 0\r\na=tool: %s\r\na=range:npt=%d-\r\n",
                                 sdpSessionId, sdpSessionVersion, RTSP_SERVER_NAME, ClientConn->FileStartTime);
        }
        else
        {
            baseAddr =  sprintf((INT8 *)sdpString, 
                "v=0\r\no=RTSP %s %s IN IP4 0.0.0.0\r\ns=RTSP Server\r\nc=IN IP4 0.0.0.0\r\nt=0 0\r\na=tool: %s\r\na=range:npt=%d-%d\r\n",
                                 sdpSessionId, sdpSessionVersion, RTSP_SERVER_NAME, ClientConn->FileStartTime, rtspSession->FileEndTime);
        }
    }

    rtspStream = rtspSession->SessionStreamList;
    while (rtspStream)
    {
		baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "m=%s 0 RTP/AVP %d\r\n", (rtspStream->CodecType) ? "video" : "audio", rtspStream->PayloadNumber);

        /* Video Stream is added                                              */
        if (rtspStream->CodecType == 1)
        {
            baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=rtpmap:%d %s/%d\r\n", rtspStream->PayloadNumber, rtspStream->EncodingName, rtspStream->ClockRate);
        }
        /* Audio Stream is added                                              */
        else if (rtspStream->CodecType == 0)
        {
            if (rtspStream->StreamCodec == CODEC_G726)
            {
                /* Clock Rate Fixed to 8k                                     */
                baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=rtpmap:%d %s/8000/%d\r\n", rtspStream->PayloadNumber, rtspStream->EncodingName, rtspStream->NoOfChannels);
            }
            else
            {
                baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=rtpmap:%d %s/%d/%d\r\n", rtspStream->PayloadNumber, rtspStream->EncodingName, rtspStream->ClockRate, rtspStream->NoOfChannels);
            }
        }
        else
        {
            baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=rtpmap:%d %s/%d/%d\r\n", rtspStream->PayloadNumber, rtspStream->EncodingName, rtspStream->ClockRate, rtspStream->NoOfChannels);
        }
		
        BYTE acProfileLevelId[3] = {0};  // cyf add
        switch (rtspStream->StreamCodec)
        {
            case CODEC_H264:
                spsHeader = (BYTE *) malloc(rtspStream->FormatDataSize * 2);

                if (spsHeader == NULL)
                {
                    free(sdpString);
                    return RET_ERROR;
                }

                memset(spsHeader, 0x00, rtspStream->FormatDataSize * 2);
                ppsHeader = (BYTE *) malloc(rtspStream->FormatDataSize * 2);

                if (ppsHeader == NULL)
                {
                    free(sdpString);
                    free(spsHeader);
                    return RET_ERROR;
                }

                memset(ppsHeader, 0x00, rtspStream->FormatDataSize * 2);

                if (ParseNALHeader(rtspStream->FormatDataPointer, rtspStream->FormatDataSize, spsHeader, &spsLen, ppsHeader, &ppsLen, acProfileLevelId) == RET_ERROR)
                {
                    RtpRtspErrorPrint("Cannot generate SPS and PPS header strings\n");
                    free(sdpString);
                    free(spsHeader);
                    free(ppsHeader);
                    return RET_ERROR;
                }

                baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=fmtp:%d packetization-mode=1;profile-level-id=%02x%02x%02x;sprop-parameter-sets=%s%c%s\r\n",
                                    rtspStream->PayloadNumber, acProfileLevelId[0], acProfileLevelId[1], acProfileLevelId[2], (spsHeader) ? spsHeader : NULL, (ppsHeader[0] && spsHeader[0]) ? ',' : ' ', (ppsHeader) ? ppsHeader : NULL);
                free(spsHeader);
                free(ppsHeader);
                break;
			/*cb change 2016.8.5 .添加h265的支持 start*/ 
            case CODEC_H265:
                vpsHeader = (BYTE *) malloc(rtspStream->FormatDataSize * 2);
                if (vpsHeader == NULL)
                {
                    free(sdpString);
                    return RET_ERROR;
                }
                memset(vpsHeader, 0x00, rtspStream->FormatDataSize * 2);

                spsHeader = (BYTE *) malloc(rtspStream->FormatDataSize * 2);
                if (spsHeader == NULL)
                {
                    free(sdpString);
                    return RET_ERROR;
                }
                memset(spsHeader, 0x00, rtspStream->FormatDataSize * 2);

                ppsHeader = (BYTE *) malloc(rtspStream->FormatDataSize * 2);
                if (ppsHeader == NULL)
                {
                    free(sdpString);
                    free(spsHeader);
                    return RET_ERROR;
                }
                memset(ppsHeader, 0x00, rtspStream->FormatDataSize * 2);

                if (ParseNALHeaderH265(rtspStream->FormatDataPointer, rtspStream->FormatDataSize, vpsHeader, &vpsLen, spsHeader, &spsLen, ppsHeader, &ppsLen, acProfileLevelId) == RET_ERROR)
                {
                    RtpRtspErrorPrint("Cannot generate SPS and PPS header strings\n");
                    free(sdpString);
                    free(spsHeader);
                    free(ppsHeader);
                    return RET_ERROR;
                }

                baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=fmtp:%d profile-space=0;profile-id=1;tier-flag=0;level-id=90;interop-constraints=B00000000000;sprop-vps=%s;sprop-sps=%s;sprop-pps=%s\r\n",
                                    rtspStream->PayloadNumber,(vpsHeader) ? vpsHeader : NULL,(spsHeader) ? spsHeader : NULL, (ppsHeader) ? ppsHeader : NULL);
                free(spsHeader);
                free(ppsHeader);
                break;
			/*cb change 2016.8.5 .添加h265的支持 end*/ 
            case CODEC_MPEG4V:
                volHeader = (BYTE *) malloc(rtspStream->FormatDataSize * 2);

                if (volHeader == NULL)
                {
                    free(sdpString);
                    return RET_ERROR;
                }

                memset(volHeader, 0x00, rtspStream->FormatDataSize * 2);

                if (ParseVOLHeader(rtspStream->FormatDataPointer, rtspStream->FormatDataSize, volHeader) == RET_ERROR)
                {
                    RtpRtspErrorPrint("Can not generate the VOL  header strings\n");
                    free(sdpString);
                    free(volHeader);
                    return RET_ERROR;
                }

                baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=fmtp:%d packetization-mode=1;profile-level-id=3;config=%s;\r\n", rtspStream->PayloadNumber, volHeader);
                free(volHeader);
                break;

            case CODEC_MJPEG:
            case CODEC_G711A:
            case CODEC_G711U:
            case CODEC_G726:
            case CODEC_L16:
            case CODEC_MPA:
            case CODEC_MP2T:
                rtspStream->FormatDataPointer   =   NULL;
                rtspStream->FormatDataSize      =   0;
                break;

            case CODEC_AAC:
                aacConfig = (BYTE *) malloc(rtspStream->FormatDataSize * 2);

                if (aacConfig == NULL)
                {
                    free(sdpString);
                    return RET_ERROR;
                }

                memset(aacConfig, 0x00, rtspStream->FormatDataSize * 2);

                if (ParseAACData(rtspStream->FormatDataPointer, rtspStream->FormatDataSize, aacConfig) == RET_ERROR)
                {
                    RtpRtspErrorPrint("Cannot generate Config field of SDP, Problem in parsing AAC header\n");
                    free(aacConfig);
                    free(sdpString);
                    return RET_ERROR;
                }

                if (aacConfig != NULL)
                {
                    baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=fmtp:%d streamtype=5; profile-level-id=15; mode=AAC-hbr; config=%s; SizeLength=13;IndexLength=3; IndexDeltaLength=3; Profile=1;\r\n", rtspStream->PayloadNumber, aacConfig);
                }
                else
                {
                    baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=fmtp:%d streamtype=5; profile-level-id=15; mode=AAC-hbr; SizeLength=13;IndexLength=3; IndexDeltaLength=3; Profile=1;\r\n", rtspStream->PayloadNumber);
                }

                free(aacConfig);
                break;

            default:
                break;
        }

        /* Add 'a=control' SDP field in SDP                                   */
        //baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=control:track1");
        baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "a=control:trackID=%d", trackId++);
        rtspStream  = rtspStream->Next;
    }

    baseAddr += sprintf((INT8 *)(sdpString + baseAddr), "\r\n");

    if (rtspSession->SessionGeneratedSDP)
    {
        free(rtspSession->SessionGeneratedSDP);
        rtspSession->SessionGeneratedSDP = NULL;
    }

    rtspSession->SessionGeneratedSDP = (BYTE *) malloc(strlen((INT8 *)sdpString) + 1);

    if (rtspSession->SessionGeneratedSDP == NULL)
    {
        free(sdpString);
        return RET_ERROR;
    }
	//printf("\n*********sdpString :\n%s\n\n",sdpString);
    memset(rtspSession->SessionGeneratedSDP, 0x00, strlen((INT8 *)sdpString) + 1);
    strcpy((INT8 *)rtspSession->SessionGeneratedSDP, (INT8 *)sdpString);
    sprintf((INT8 *)sdpSizeStr, "%d", strlen((INT8 *)rtspSession->SessionGeneratedSDP));

    if (AddResponseHeader(ClientConn->ClientRtspResMsg, (BYTE *)"Content-Length", (BYTE *)sdpSizeStr) == RET_ERROR)
    {
        free(sdpString);
        return RET_ERROR;
    }

    free(sdpString);
    return RET_OK;
}

/*******************************************************************************
 * Function:    FindCharInBuffer
 *
 * Description: This function find the location of given character in the buffer
 *               it parse the buffer till the end string[\r\n].
 *
 * Parameters :
 *      [IN]  BYTE* Buffer   - Pointer of buffer
 *      [IN]  BYTE  FindChar - Character to find in the buffer
 *      [IN]  BYTE  EndChar  - Character till find in the buffer
 *      [IN]  INT32 BufLen   - Length of the buffer
 *
 * Return Value:
 *      INT32 - Zero in case character not found
 *             - location of character in buffer
 ******************************************************************************/
INT32 FindCharInBuffer(BYTE *Buffer,  BYTE FindChar,
                       BYTE EndChar,  INT32 BufLen)
{
    INT32 retVal   = 0;                 /* Store the return value of function */

    /* Loop to compare the FindChar and EndChar with each member of buffer
       and return the index of find char                                      */
    for (;;)
    {
        if (Buffer[retVal] == FindChar)
        {
            break;
        }
        else if (Buffer[retVal] == EndChar)
        {
            retVal = 0;
            break;
        }
        else
        {
            retVal++;
        }

        /* Reached to end of buffer and encChar or FindChar not found         */
        if (retVal >= BufLen)
        {
            retVal = 0;
            break;
        }
    }

    return retVal;
}

// 获取指定会话名称的会话访问结构
RTSPSession *FindRTSPSession(RTSPServer   *RtspServer, BYTE *SessionName)
{
    RTSPSession   *rtspSession;
    rtspSession  =  RtspServer->RtspSessionList;

    while ((rtspSession != NULL) && (SessionName != NULL))
    {
        if (strcmp((INT8 *)rtspSession->SessionName, (INT8 *)SessionName) == 0)
        {
            RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tRtspSession = %d\n", rtspSession);
            return rtspSession;
        }

        rtspSession = rtspSession->NextSession;
    }

    return NULL;
}

/*******************************************************************************
 * Function:     FreeRequestMsg
 *
 * Description:  This function frees the request message pointer memory.
 *
 * Parameters :
 *      [IN] RTSPRequestMsg *RequestMsg - Pointer of RTSP request message.
 *
 * Return Value:
 *       None
 ******************************************************************************/
void FreeRequestMsg(RTSPRequestMsg *RequestMsg)
{
    INT32       indexCnt;            /* Local index counter                   */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tRequestMsg = %d\n", RequestMsg);

    /* Free memory used by local variables                                    */
    if (RequestMsg)
    {
        /* Free the response msg memory                                       */
        for (indexCnt = 0; indexCnt < RequestMsg->ReqHeadersCount; indexCnt++)
        {
            if (RequestMsg->ReqMsgHeaders[indexCnt].HeaderName)
            {
                free(RequestMsg->ReqMsgHeaders[indexCnt].HeaderName);
            }

            if (RequestMsg->ReqMsgHeaders[indexCnt].HeaderValue)
            {
                free(RequestMsg->ReqMsgHeaders[indexCnt].HeaderValue);
            }
        }

        if (RequestMsg->ReqMsgURI)
        {
            free(RequestMsg->ReqMsgURI);
            RequestMsg->ReqMsgURI = NULL;
        }

        if (RequestMsg->ReqRtspVersion)
        {
            free(RequestMsg->ReqRtspVersion);
            RequestMsg->ReqRtspVersion = NULL;
        }

        free(RequestMsg);
        RequestMsg = NULL;
    }

    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
}

/*******************************************************************************
 * Function:     FreeResponseMsg
 *
 * Description:  This function frees the response message pointer memory.
 *
 * Parameters :
 *      [IN] RTSPResponseMsg *ResponseMsg - Pointer of RTSP response message.
 *
 * Return Value:
 *       None
 ******************************************************************************/
void FreeResponseMsg(RTSPResponseMsg *ResponseMsg)
{
    INT32       indexCnt;            /* Local index counter                   */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tResponseMsg = %d\n", ResponseMsg);

    if (ResponseMsg)
    {
        /* Free the response msg memory                                       */
        for (indexCnt = 0; indexCnt < ResponseMsg->ResHeadersCount; indexCnt++)
        {
            if (ResponseMsg->ResMsgHeaders[indexCnt].HeaderName)
            {
                free(ResponseMsg->ResMsgHeaders[indexCnt].HeaderName);
                ResponseMsg->ResMsgHeaders[indexCnt].HeaderName = NULL;
            }

            if (ResponseMsg->ResMsgHeaders[indexCnt].HeaderValue)
            {
                free(ResponseMsg->ResMsgHeaders[indexCnt].HeaderValue);
                ResponseMsg->ResMsgHeaders[indexCnt].HeaderValue = NULL;
            }
        }

        if (ResponseMsg->ResRtspVersion)
        {
            free(ResponseMsg->ResRtspVersion);
            ResponseMsg->ResRtspVersion = NULL;
        }

        free(ResponseMsg);
        ResponseMsg = NULL;
    }

    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
}

/*******************************************************************************
 * Function:     ValidateServerHandle
 *
 * Description:  This function validates Server Handle.
 *
 * Parameters :
 *      [IN] INT32 ServerHandle - Handle of Server
 *
 * Return Value:
 *       INT32 - RET_OK     - Success, if Header is Valid
 *             - RET_ERROR  - Failure, if Header is not Valid.
 ******************************************************************************/
INT32 ValidateServerHandle(INT32 ServerHandle)
{
    RTSPServer          *rtspServer;        /*  RTSP Server Variable          */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tRtspServerHandle = %d\n",
                      ServerHandle);
    rtspServer = gblRtspServer;

    /* Traverse all server's all session to validate the client handle        */
    if (rtspServer)
    {
        if ((INT32)rtspServer == ServerHandle)
        {
            RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
            return RET_OK;
        }
    }

    return RET_ERROR;
}

/*******************************************************************************
 * Function:     ValidateSessionHandle
 *
 * Description:  This function validates Session Handle.
 *
 * Parameters :
 *      [IN] INT32 SessionHandle    - Handle of Session
 *
 * Return Value:
 *       INT32 - RET_OK     - Success, if Header is Valid
 *             - RET_ERROR  - Failure, if Header is not Valid.
 ******************************************************************************/
INT32 ValidateSessionHandle(INT32 SessionHandle)
{
    RTSPServer          *rtspServer;        /*  RTSP Server Variable          */
    RTSPSession         *rtspSession;       /* RTSP Session Variable          */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tRtspSessionHandle = %d\n",
                      SessionHandle);
    rtspServer = gblRtspServer;

    /* traverse all server's all session to validate the client handle        */
    if (rtspServer)
    {
        rtspSession = rtspServer->RtspSessionList;

        while (rtspSession)
        {
            if ((INT32)rtspSession == SessionHandle)
            {
                RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
                return RET_OK;
            }

            /* Move to next RTSP sessoin pointer in the list                  */
            rtspSession = rtspSession->NextSession;
        }
    }

    return RET_ERROR;
}

/*******************************************************************************
 * Function:     ValidateServersideClientHandle
 *
 * Description:  This function validates Server side Client Handle.
 *
 * Parameters :
 *      [IN] INT32 ClientHandle - Handle of Session
 *
 * Return Value:
 *       INT32 - RET_OK     - Success, if Header is Valid
 *             - RET_ERROR  - Failure, if Header is not Valid.
 ******************************************************************************/
INT32 ValidateServersideClientHandle(INT32 ClientHandle)
{
    RTSPClient          *rtspConnClient;    /* Connected Client Variable      */
    RTSPServer          *rtspServer;        /*  RTSP Server Variable          */
    RTSPSession         *rtspSession;       /* RTSP Session Variable          */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER : \n\tClientHandle = %d\n", ClientHandle);
    rtspServer = gblRtspServer;

    /* traverse all server's all session to validate the client handle        */
    if (rtspServer)
    {
        rtspSession = rtspServer->RtspSessionList;

        /* traverse all session's clientlist to validate client handle        */
        while (rtspSession)
        {
            /* Traverse client list to validate client handle                 */
            rtspConnClient = rtspSession->SessionConnectedClientList;

            while (rtspConnClient)
            {
                if ((INT32)rtspConnClient == ClientHandle)
                {
                    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
                    return RET_OK;
                }

                rtspConnClient = rtspConnClient->NextClient;
            }

            rtspSession = rtspSession->NextSession;
        }
    }

    // Client may not be in RtspSessionList if it is newly connected client with invalid session name.
    // In that case validate client pointer by using it's rtsp server pointer.
    rtspServer = gblRtspServer;
    rtspConnClient = (RTSPClient *)ClientHandle;

    if (rtspServer)
    {
        if (rtspConnClient->RtspServerPtr == rtspServer)
        {
            RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturn Successfully\n");
            return RET_OK;
        }
    }

    return RET_ERROR;
}

/*******************************************************************************
 * Function   : GetNtpTime
 *
 * Description: This function return the current system NTP Time
 *
 * Parameters : None
 *
 * Return Value:
 *      UINT64 : NTP Time
 ******************************************************************************/
DWORD GetNtpTime()
{
    DWORD  ntpTime = 0;            /* Variable for storing NTP Time Value    */
    UINT32  sec = 0;                /* Variable for storing Seconds           */
    UINT32  microsec = 0;           /* Variable for storing MicroSeconds      */
    UINT32  ntpSec = 0;             /* Variable for storing NTP Seconds       */
    UINT32  ntpFrac = 0;            /* Variable for storing NTP Fractions     */
    /* Get Current Time                                                       */
    GetPresentTimeInSec(&sec, &microsec);
    /* Convert in NTP Time Stamp                                              */
    /* Higher 32 bits                                                         */
    ntpSec = sec + 0x83AA7E80;
    /* Lower 32 bits                                                          */
    ntpFrac  = (UINT32)(((double)(microsec) * (double)0x4000000) / 15625.0);
    ntpTime  = ntpSec;
    ntpTime  = ntpTime << 32;
    ntpTime |= ntpFrac;
    return ntpTime;
}

/*******************************************************************************
 * Function:    ParseURI
 *
 * Description: This function extracts the name of session.
 *
 * Parameters:
 *      [IN]    BYTE*       ReqMsgURI   -   RTSP URI from Req Msg
 *      [IN]    INT32       Level       -   Level of searching specified string
 *      [IN]    INT8*       DestStr     -   Find this string
 *
 * Return Value:
 *      BYTE * - Returns NULL/Session Name
 *          RET_OK    - Name of Session
 *          RET_ERROR - NULL, in case of error
 ******************************************************************************/
BYTE *ParseURI(BYTE *ReqMsgURI, INT32 Level, INT8 *DestStr)
{
    BYTE            *tempBuff;          /* Temporary Buffer                   */
    BYTE            *tempPtr;           /* Temporary Pointer                  */
    BYTE            *sessionName = NULL;/* Store the Name of Session          */

    if (NULL == ReqMsgURI)
    {
        RtpRtspErrorPrint("ParseURI: the input parameter 'ReqMsgURI' is null \n");
        return NULL;
    }

    /* Get the request uri in local variable                                  */
    tempBuff = ReqMsgURI;

    do
    {
        tempBuff = (BYTE *)strstr((INT8 *)tempBuff, (INT8 *)DestStr);

        if (tempBuff == NULL)
        {
            break;
        }

        tempBuff = tempBuff + 1;
        Level--;
    }
    while (Level > 0);

    if (tempBuff)
    {
        tempPtr = (BYTE *)strstr((INT8 *)tempBuff, (INT8 *)DestStr);

        if (tempPtr == NULL)
        {
            sessionName = (BYTE *)malloc(strlen((INT8 *) tempBuff) + 1);

            if (sessionName == NULL)
            {
                RtpRtspErrorPrint("Unable to allocate memory \n");
                return NULL;
            }

            memset(sessionName, 0x00, strlen((INT8 *) tempBuff) + 1);
            memcpy(sessionName, tempBuff, strlen((INT8 *) tempBuff));
        }
        else
        {
            sessionName = (BYTE *)malloc(tempPtr - tempBuff + 1);

            if (sessionName == NULL)
            {
                RtpRtspErrorPrint("Unable to allocate memory \n");
                return NULL;
            }

            memset(sessionName, 0x00, tempPtr - tempBuff + 1);
            memcpy(sessionName, tempBuff, tempPtr - tempBuff);
        }
    }

    return sessionName;
}

/*******************************************************************************
 * Copyright (c) 2007 eInfochips - All rights reserved.
 *
 * This software is authored by eInfochips and is eInfochips' intellectual
 * property, including the copyrights in all countries in the world.
 * This software is provided under a license to use only with all other rights,
 * including ownership rights, being retained by eInfochips.
 *
 * This file may not be distributed, copied, or reproduced in any manner,
 * electronic or otherwise, without the written consent of eInfochips.
 ******************************************************************************/

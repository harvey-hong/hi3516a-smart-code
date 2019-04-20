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
 * File Name    :   RTSPServerAPI.c
 *
 * Description  :   This file contain the API implementation of RTSP protocol
 *
 * History:
 *  JUN/22/2007, UBV,   Created the file.
 *  JUN/25/2007, UBV,   Modified return value of APIs now it will return Error
 *                      codes.
 *  DEC/27/2007, ARJ,   Separated API and Internal functions in different files
 *  JAN/28/2008, ARJ,   Updated the changes as per code review XLS.
 *  MAY/01/2009, ARJ,   Added RTSP over HTTP feature
 *
 ******************************************************************************/

/****************
 * Include Files
 ****************/
#include "../inc/RtspServer.h"
#include "../inc/RtpServer.h"
#include "../inc/DbgPrint.h"
#include "../inc/HYRtspService.h"
/****************
 * Globals
 ****************/

RTSPServer *gblRtspServer = NULL;                /* List of Servers           */

RTP_RTSPLIB_API INT32 CreateRTSPServerListenPort(int NewPort)
{
    int  serverSocket = socket(AF_INET, SOCKET_TYPE, 0);
    if(-1 == serverSocket)
    {
        RTSP_SER_PE(" socket() fail, errno=[%d]\n", errno);
        return -1;
    }

    int resUseFlag = 1;
    if (setsockopt(serverSocket , SOL_SOCKET, SO_REUSEADDR, (char *)&resUseFlag, sizeof(int)) == (-1))
    {
        RTSP_SER_PW(" setsockopt( SO_REUSEADDR ) fail, errno=[%d]\n", errno);
        return -1;    
     }

    SOCKETADDR_IN    serverSocketAddr;
    memset(&serverSocketAddr, 0, sizeof(serverSocketAddr));
    serverSocketAddr.sin_family                    = AF_INET;
    serverSocketAddr.sin_addr.s_addr        = INADDR_ANY;
    serverSocketAddr.sin_port                   = htons((UINT16)NewPort);    

    if (bind(serverSocket, (struct sockaddr *)&serverSocketAddr, sizeof(serverSocketAddr)))
    {
        RTSP_SER_PW(" bind( ) fail, errno=[%d]\n", errno);
        close(serverSocket);
        serverSocket = INVALID_SOCKET;
        return -1;    
     }

    if (listen(serverSocket, MAX_LISTEN_CLIENT) != 0)
    {
        RTSP_SER_PW(" listen( ) fail, errno=[%d]\n", errno);
        close(serverSocket);
        serverSocket = INVALID_SOCKET;
        return -1;    
     }

    return serverSocket;
}

/*******************************************************************************
 * Function:    RTSPServerStart
 *
 * Description: This function start the RTSP server on given IP and port
 *
 * Parameters :
 *      [IN]  BYTE* ServerIP   - Pointer of server IP string
 *      [IN]  INT32 ServerPort - Port number on which server will listen
 *      [IN]  INT32 HttpPort    - Port number on which server will listen
 *                                  and respond as RTSP over HTTP
 *      [IN]  FS_EVENT_CALLBACK FS_Callback  - Callback funtion for filestreamer
 *      [OUT] INT32 *ErrorCode - It contains Error Code in case of error
 *
 * Return Value:
 *      INT32 - Handle of RTSP Server must be greater then 0
 *              OR
 *              RTP_RTSP_ERROR  - Error occurred.
 *
 *              Any of the Following Error codes will be ErrorCode
 *                                                      Argument in case of error:
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_MEMORY_ALLOCATION_FAIL - Memory allocation failed
 *              RTP_RTSP_SOCKET_CREATION_FAIL   - Socket creation failed
 *              RTP_RTSP_SOCKET_BIND_FAIL       - Socket bind failed
 *              RTP_RTSP_SERVER_THREAD_CREATION_FAIL  - Thread creation failed.
 *              RTP_RTSP_LOCK_INITIALIZATION_FAIL     - Lock Initialization failed.
 *              RTP_RTSP_SOCKET_LISTEN_FAIL     - Listen on Socket Failed
 ******************************************************************************/
// 启动RTSP服务器在指定端口上侦听，启动工作线程等待客户连接RTSPServerThreadFunc
RTP_RTSPLIB_API INT32 RTSPServerStart(BYTE *ServerIP, INT32 ServerPort,
                                      FS_EVENT_CALLBACK FS_Callback,
                                      INT32 *ErrorCode)
{
    INT32                    retVal;             /*  Store return value of func call   */
    INT32                    index;              /*  Loop counter                      */
    SOCKET                 serverSocket;       /*  Server Socket                     */
    RTSPServer            *rtspServer;        /*  RTSP Server Variable              */
    RTSPServer            *rtspServerTemp;    /*  RTSP Server Variable              */
    SOCKETADDR_IN    serverSocketAddr;   /*  Server socket addr structure      */

    //当服务端IP为空或者服务端端口小于0或者服务端IP长度大于IP的最大长度或者错误码为空
    if ((ServerIP == NULL) || (ServerPort <= 0) || ((INT32)strlen((INT8 *)ServerIP) >= MAX_IP_LENGTH) || (ErrorCode == NULL))
    {
        if (ErrorCode != NULL)
        {
            *ErrorCode = RTP_RTSP_INVALID_INPUT_VALUE;
        }

        return RTP_RTSP_ERROR;
    }

    HandleSignal();
    rtspServer = (RTSPServer *) malloc(sizeof(RTSPServer));
    if (rtspServer == NULL)
    {
        *ErrorCode = RTP_RTSP_MEMORY_ALLOCATION_FAIL;
        return RTP_RTSP_ERROR;
    }

    memset(rtspServer, 0, sizeof(RTSPServer));
    rtspServer->ServerRtspPort      = ServerPort;
    rtspServer->ServerSocket        = INVALID_SOCKET;
    strcpy((INT8 *)rtspServer->ServerIp, (INT8 *)ServerIP);

    serverSocket = CreateRTSPServerListenPort(rtspServer->ServerRtspPort);
    if(serverSocket == -1)
    {
        free(rtspServer);
        rtspServer = NULL;
        *ErrorCode = RTP_RTSP_SOCKET_CREATION_FAIL;
        return RTP_RTSP_ERROR;
    }
    
    rtspServer->ServerSocket = serverSocket;

    // 启动工作线程，等待用户连接，并配置用户连接回调处理函数..
    retVal = ThreadCreate(&(rtspServer->ServerThreadID), (THREAD_FUNC) RTSPServerThreadFunc, rtspServer);
    if (retVal != RET_OK)
    {
        RtpRtspErrorPrint("Can not start the RTSP server accept thread\n");
        free(rtspServer);
        rtspServer = NULL;
        CloseServerSock(serverSocket);
        *ErrorCode = RTP_RTSP_SERVER_THREAD_CREATION_FAIL;
        return RTP_RTSP_ERROR;
    }

    if (MutexInit(&(rtspServer->ServerRtspSessionLock)) != RET_OK)
    {
        free(rtspServer);
        rtspServer = NULL;
        CloseServerSock(serverSocket);
        *ErrorCode = RTP_RTSP_LOCK_INITIALIZATION_FAIL;
        return RTP_RTSP_ERROR;
    }

    rtspServer->AddSession_Callback = FS_Callback;
    gblRtspServer = rtspServer;
    return (INT32)rtspServer;
}


/*******************************************************************************
 * Function:    RTSPServerShutdown
 *
 * Description: This function shutdown the RTSP server thread and free memory
 *
 * Parameters :
 * Parameters :
 *      [IN]  INT32 ServerHandle - Handle of RTSP server
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_LOCK_DESTROY_FAIL      - Destroying of Lock Failed
 *              RTP_RTSP_WAIT_FOR_THREAD_FAILED - Wait for thread completion
 ******************************************************************************/
RTP_RTSPLIB_API INT32 RTSPServerShutdown(INT32 ServerHandle)
{
    RTSPServer      *rtspServer;        /* RTSP server structure pointer      */
    RTSPSession     *rtspSession;       /* RTSP session structure pointer     */
    RTSP_SER_PD( "ENTER : ServerHandle = %d\n", ServerHandle);

    RtpRtspDebugPrint(DBG_LEVEL_4, "Validating Input Arguments\n");

    /* Validate Input Arguments                                               */
    if (ServerHandle <= 0)
    {
        RtpRtspErrorPrint("Invalid RTSP server handle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Validating Server Handle                                               */
    if (ValidateServerHandle(ServerHandle) != RET_OK)
    {
        RtpRtspErrorPrint("Invalid RTSP server handle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Get the RTSP Server pointer                                            */
    rtspServer = (RTSPServer *)ServerHandle;

    if (rtspServer == NULL)
    {
        RtpRtspErrorPrint("Invalid RTSP server handle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    RtpRtspDebugPrint(DBG_LEVEL_4, "Closing Server Socket and \
                Waiting for Server Thread Completion\n");

    /* Close the Server Socket                                                */
    if (rtspServer->ServerSocket != INVALID_SOCKET)
    {
        CloseServerSock(rtspServer->ServerSocket);
        rtspServer->ServerSocket = INVALID_SOCKET;

        /* Wait for thread to complete                                        */
        if (WaitForThreadCompletion(rtspServer->ServerThreadID) != RET_OK)
        {
            RtpRtspErrorPrint("Wait For Thread Completion Failed \n");
            return RTP_RTSP_WAIT_FOR_THREAD_FAILED;
        }
    }

    RtpRtspDebugPrint(DBG_LEVEL_4, "Destroying All Sessions\n");
    /* Destroy all sessions                                                   */
    while (rtspServer->RtspSessionList != NULL)
    {
        rtspSession = rtspServer->RtspSessionList;
#if 0		
        if(RTSPSessionDestroy((INT32)rtspSession) == RET_ERROR)
        {
            RtpRtspErrorPrint("Can not destroy RTSP session\n");
        }
#endif
		// when usr vlc : change port in ie , vlc can not replay 
		// system reboot rtsp and vlc send "FS_REMOVE_SESS_STOP" message 
		CHYPrivateService::ProcessRemoveSessionEvent((int)rtspSession, NULL);
    }
    RtpRtspDebugPrint(DBG_LEVEL_4, "Destroying RTSP Session List Lock \n");

    /* Destroy RTSP Session List Lock                                         */
    if (rtspServer->RtspSessionList == NULL)
    {
        if (MutexDestroy(&(rtspServer->ServerRtspSessionLock)) != RET_OK)
        {
            RtpRtspErrorPrint("Destroying of RTSP Session List Lock Failed\n");
            return RTP_RTSP_LOCK_DESTROY_FAIL;
        }
    }
    /* Remove RTSPServer from the global RTSP server list                     */
    gblRtspServer = NULL;
    RtpRtspDebugPrint(DBG_LEVEL_4, "Freeing Server Memory\n");
    /* Free server memory                                                     */
    free(rtspServer);
    rtspServer = NULL;
    RtpRtspDebugPrint(DBG_LEVEL_1, "\nEXIT : \n\tReturning Successfully\n");
    return RTP_RTSP_OK;
}

//\\ 创建RTSP会话结构添加到RTSP服务管理链表中，设置会话客户连接回调函数ClientConnectionCB，RTP写回调函数RtspStreamEventCB
RTP_RTSPLIB_API INT32 RTSPSessionCreate(INT32 ServerHandle, BYTE *SessionName,
                                        BYTE *MulticastIP,
                                        INT32 SingleModeFlag, INT32  UdpMTUSize,
                                        INT32  TcpMTUSize, INT32 RtcpEnableFlag,
                                        INT32 RtcpSRInterval, INT32 *ErrorCode,
                                        CLIENT_CONNECTION_CALLBACK ConnCallback,
                                        FS_EVENT_CALLBACK FS_Callback, INT32 FileEndTime)
{
    RTSPServer      *rtspServer;        /* RTSP server structure pointer      */
    RTSPSession     *rtspSession;       /* RTSP session structure pointer     */
    RTSPSession     *rtspSessionTemp;   /* Temp. RTSP server structure pointer*/

    if (ValidateServerHandle(ServerHandle) != RET_OK)
    {
        if (ErrorCode != NULL)
        {
            *ErrorCode = RTP_RTSP_INVALID_INPUT_VALUE;
        }

        return RTP_RTSP_ERROR;
    }

    if ((SessionName == NULL) || (ServerHandle <= 0) || ((INT32) strlen((INT8 *)SessionName) >= MAX_SMALL_BUFF_SIZE) ||
        (ErrorCode == NULL) || (SingleModeFlag < 0) || (UdpMTUSize < 0) || (TcpMTUSize < 0) || (FileEndTime < 0))
    {
        RtpRtspErrorPrint("Invalid input argument passed\n");
        *ErrorCode = RTP_RTSP_INVALID_INPUT_VALUE;
        return RTP_RTSP_ERROR;
    }

    if (MulticastIP != NULL)
    {
        if ((strlen((INT8 *)MulticastIP) + 1) > MAX_IP_LENGTH)
        {
            RtpRtspErrorPrint("Invalid Multicast Ip Address Passed \n");
            *ErrorCode = RTP_RTSP_INVALID_INPUT_VALUE;
            return RTP_RTSP_ERROR;
        }
    }

    rtspServer = (RTSPServer *)ServerHandle;

    if ((RtcpEnableFlag == 1) && (RtcpSRInterval <= 0))
    {
        RtpRtspErrorPrint("Invalid RTCP parameters passed\n");
        *ErrorCode = RTP_RTSP_INVALID_INPUT_VALUE;
        return RTP_RTSP_ERROR;
    }

    if (MutexLock(&(rtspServer->ServerRtspSessionLock)) != RET_OK)
    {
        RtpRtspErrorPrint("Locking RTSPSession List Failed\n");
        *ErrorCode = RTP_RTSP_LOCK_FAIL;
        return RTP_RTSP_ERROR;
    }

    rtspSessionTemp = rtspServer->RtspSessionList;

    while (rtspSessionTemp != NULL)
    {
        if (!strcmp((INT8 *)rtspSessionTemp->SessionName, (INT8 *)SessionName))
        {
            RtpRtspErrorPrint("Invalid Session Name Passed. \nSession with this session name already exists\n");

            if (MutexUnlock(&(rtspServer->ServerRtspSessionLock)) != RET_OK)
            {
                *ErrorCode = RTP_RTSP_UNLOCK_FAIL;
                return RTP_RTSP_ERROR;
            }

            *ErrorCode = RTP_RTSP_INVALID_INPUT_VALUE;
            return RTP_RTSP_ERROR;
        }

        rtspSessionTemp = rtspSessionTemp->NextSession;
    }

    if (MutexUnlock(&(rtspServer->ServerRtspSessionLock)) != RET_OK)
    {
        *ErrorCode = RTP_RTSP_UNLOCK_FAIL;
        return RTP_RTSP_ERROR;
    }

    rtspSession = (RTSPSession *) malloc(sizeof(RTSPSession));

    if (rtspSession == NULL)
    {
        RtpRtspErrorPrint("Can not allocate memory for RTSP Session structure\n");
        *ErrorCode = RTP_RTSP_MEMORY_ALLOCATION_FAIL;
        return RTP_RTSP_ERROR;
    }

    memset(rtspSession, 0x00, sizeof(RTSPSession));
    sprintf((INT8 *)rtspSession->SessionName, "%s", SessionName);
    rtspSession->SessionConnectedClientCount    = 0;
    rtspSession->RtspServerPtr                      = rtspServer;
    rtspSession->SessionSingleMode                  = SingleModeFlag;
    rtspSession->ClientConnectionCallback       = ConnCallback;
    rtspSession->RtcpFlag                               = RtcpEnableFlag;
    rtspSession->RtcpSRInterval                     = RtcpSRInterval;

    if (UdpMTUSize == 0)
    {
        rtspSession->UdpMTUSize                     = UDP_MAX_PACKET_SIZE;
    }
    else
    {
        rtspSession->UdpMTUSize                     = UdpMTUSize;
    }

    if (TcpMTUSize == 0)
    {
        rtspSession->TcpMTUSize                     = TCP_MAX_PACKET_SIZE;
    }
    else
    {
        rtspSession->TcpMTUSize                     = TcpMTUSize;
    }

    /* Initialize RTSPClient Client List Lock                                 */
    if (MutexInit(&(rtspSession->SessionClientListLock)) != RET_OK)
    {
        RtpRtspErrorPrint("Cannot Initialize RTSPClient Client List Lock\n");
        free(rtspSession);
        rtspSession = NULL;
        *ErrorCode = RTP_RTSP_LOCK_INITIALIZATION_FAIL;
        return RTP_RTSP_ERROR;
    }

    rtspSession->RTPWriter_Callback = FS_Callback;
    rtspSession->FileEndTime = FileEndTime;

    //      RtpRtspDebugPrint(DBG_LEVEL_4, "Adding Session to RTSP Session List\n");

    if (MutexLock(&(rtspServer->ServerRtspSessionLock)) != RET_OK)
    {
        RtpRtspErrorPrint("RTSP Session List Lock Failed\n");
        free(rtspSession);
        rtspSession = NULL;
        *ErrorCode = RTP_RTSP_LOCK_FAIL;
        return RTP_RTSP_ERROR;
    }

    rtspSessionTemp = rtspServer->RtspSessionList;

    if (rtspSessionTemp == NULL)
    {
        rtspServer->RtspSessionList = rtspSession;
    }
    else
    {
        rtspSessionTemp = rtspServer->RtspSessionList;

        while (rtspSessionTemp->NextSession != NULL)
        {
            rtspSessionTemp          = rtspSessionTemp->NextSession;
        }

        rtspSessionTemp->NextSession = rtspSession;
        rtspSession->PrevSession     = rtspSessionTemp;
    }

    if (MutexUnlock(&(rtspServer->ServerRtspSessionLock)) != RET_OK)
    {
        free(rtspSession);
        rtspSession = NULL;
        RtpRtspErrorPrint("RTSP Session List Lock Failed\n");
        *ErrorCode = RTP_RTSP_UNLOCK_FAIL;
        return RTP_RTSP_ERROR;
    }

    //      RtpRtspDebugPrint(DBG_LEVEL_1, "\nEXIT : \n\tSessionHandle = %d\n", rtspSession);
    return (INT32)rtspSession;
}

/*******************************************************************************
 * Function   : RTSPSessionDestroy
 *
 * Description: Destroy RTSP Session and its connected clients
 *
 * Parameters :
 *      [IN]  INT32 SessionHandle - Handle of RTSP session
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_LOCK_FAIL              - Locking Failed
 *              RTP_RTSP_UNLOCK_FAIL            - Unlocking Failed
 *              RTP_RTSP_LOCK_DESTROY_FAIL      - Destroying of Lock failed
 *              RTP_RTSP_WAIT_FOR_THREAD_FAILED - Wait for thread completion
 ******************************************************************************/
RTP_RTSPLIB_API INT32 RTSPSessionDestroy(INT32 SessionHandle)
{
    THREAD_HANDLE   threadId;           /* Handle of Thread                   */
    RTSPClient      *clientConn;        /* RTSP connected client pointer      */
    RTSPSession     *rtspSession;       /* RTSP session structure pointer     */
    RTPSessionStream *rtspStream;       /* RTP Session Stream struct pointer  */
    RtpRtspDebugPrint(DBG_LEVEL_1, "\nENTER : \n\tSessionHandle = %d\n",
                      SessionHandle);
    RtpRtspDebugPrint(DBG_LEVEL_4, "Validating Input Arguments\n");
    /* Validating Session Handle                                              */
    if (ValidateSessionHandle(SessionHandle) != RET_OK)
    {
        RtpRtspErrorPrint("Invalid RTSP session Handle passed \n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }
    rtspSession = (RTSPSession *)SessionHandle;

    if (rtspSession == NULL)
    {
        RtpRtspErrorPrint("Invalid RTSP session passed \n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }
    /* Validating Server Handle                                               */
    if (ValidateServerHandle((INT32) rtspSession->RtspServerPtr) != RET_OK)
    {
        RtpRtspErrorPrint("Invalid RTSP server handle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }
    RtpRtspDebugPrint(DBG_LEVEL_4, "Freeing SDP Memory\n");

    /* Lock RTSP Session List                                                 */
    if (MutexLock(&(rtspSession->RtspServerPtr->ServerRtspSessionLock)) != RET_OK)
    {
        RtpRtspErrorPrint("RTSP Session List Lock Failed \n");
        return RTP_RTSP_LOCK_FAIL;
    }
    /* Free SDP memory                                                        */
    if (rtspSession->SessionGeneratedSDP)
    {
        free(rtspSession->SessionGeneratedSDP);
        rtspSession->SessionGeneratedSDP = NULL;
    }

    /* Removing Streams from Session                                          */
    rtspStream = rtspSession->SessionStreamList;
    while (rtspStream != NULL)
    {
        rtspSession->SessionStreamList = rtspStream->Next;

        if (rtspStream->FormatDataPointer)
        {
            free(rtspStream->FormatDataPointer);
            rtspStream->FormatDataPointer = NULL;
        }

        free(rtspStream);
        rtspStream = NULL;
        rtspStream = rtspSession->SessionStreamList;
    }
    RtpRtspDebugPrint(DBG_LEVEL_4, "Closing RTSP Connection Socket\n");

    /* Destroy all connected RTSP client structure                            */
    while (rtspSession->SessionConnectedClientList != NULL)
    {
        /* Lock ConnectedClient List                                          */
        if (MutexLock(&(rtspSession->SessionClientListLock)) != RET_OK)
        {
            RtpRtspErrorPrint("Connected Client List Lock Failed \n");
            return RTP_RTSP_LOCK_FAIL;
        }
        clientConn  = rtspSession->SessionConnectedClientList;
        threadId    = clientConn->ClientThreadID;

        /* Close connection socket to close RTSP session thread               */
        if (clientConn->ClientSocket != INVALID_SOCKET)
        {
            CloseServerSock(clientConn->ClientSocket);
            clientConn->ClientSocket = INVALID_SOCKET;
        }
        /* UnLock ConnectedClient List                                        */
        if (MutexUnlock(&(rtspSession->SessionClientListLock)) != RET_OK)
        {
            RtpRtspErrorPrint("Unlocking of Connected Client List Failed\n");
            return RTP_RTSP_UNLOCK_FAIL;
        }
        /* Wait for thread completion                                         */
        if (WaitForThreadCompletion(threadId) != RET_OK)
        {
            RtpRtspErrorPrint("Wait for Thread completion failed \n");
            return RTP_RTSP_WAIT_FOR_THREAD_FAILED;
        }
    }

    RtpRtspDebugPrint(DBG_LEVEL_4, "Removing Session from Session List\n");
    /* Remove the session from the list                                       */
    if (rtspSession->PrevSession)
    {
        rtspSession->PrevSession->NextSession     = rtspSession->NextSession;

        if (rtspSession->NextSession)
        {
            rtspSession->NextSession->PrevSession = rtspSession->PrevSession;
        }
    }
    else if (rtspSession->NextSession)
    {
        rtspSession->RtspServerPtr->RtspSessionList = rtspSession->NextSession;
        rtspSession->NextSession->PrevSession       = NULL;
    }
    else
    {
        rtspSession->RtspServerPtr->RtspSessionList = NULL;
    }
    /* UnLock RTSP Session List                                               */
    if (MutexUnlock(&(rtspSession->RtspServerPtr->ServerRtspSessionLock)) != RET_OK)
    {
        RtpRtspErrorPrint("Unlocking RTSP Session List Lock Failed\n");
        return RTP_RTSP_UNLOCK_FAIL;
    }
    RtpRtspDebugPrint(DBG_LEVEL_4, "Destroying Client List Lock\n");

    /* Destroy Client List Lock                                               */
    if (MutexDestroy(&(rtspSession->SessionClientListLock)) != RET_OK)
    {
        RtpRtspErrorPrint("Destroying of Connected Client List Lock Failed \n");
        return RTP_RTSP_LOCK_DESTROY_FAIL;
    }
    RtpRtspDebugPrint(DBG_LEVEL_4, "Freeing RTSP Session Pointer \n");
    /* free RTSP session memory                                               */
    free(rtspSession);
    rtspSession = NULL;
    RtpRtspDebugPrint(DBG_LEVEL_1, "\nEXIT : \n\tReturning Successfully\n");
    return RTP_RTSP_OK;
}

/*******************************************************************************
 * Function   : RTSPAddStreamToSession
 * Description: This API is used to add stream to session.
 * Parameters :
 *      [IN]  INT32 SessionHandle           -   RTSP session handle
 *      [IN]  SupportedCodecs StreamCodec   -   Stream Codec
 *                                              (H264/MPEG4V/MJPEG/G711/AAC)
 *      [IN]  INT32 CodecType               -   0 is for Audio and 1 is for Video
 *      [IN]  INT32 ClockRate               -   Clock Rate of Codec
 *      [IN]  INT32 NumberOfChannels        -   Number of Channels (only in audio)
 *      [IN]  INT32 FormatDataSize          -   Size of Format Data Pointer
 *      [IN]  BYTE *FormatDataPointer       -   Pointer to SDP related data
 *      [IN]  UINT16 MulticastPort          -   Multicast Port Number
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_MEMORY_ALLOCATION_FAIL - Memory Allocation Fail
 *              RTP_RTSP_LOCK_FAIL              - Locking Failed
 *              RTP_RTSP_UNLOCK_FAIL            - Unlocking Failed
 ******************************************************************************/
//\\ 更新指定RTSP会话结构支持的流链表
RTP_RTSPLIB_API INT32 RTSPAddStreamToSession(INT32 SessionHandle,
        SupportedCodecs StreamCodec,    INT32 CodecType,
        INT32           ClockRate,      INT32 NumberOfChannels,
        INT32           FormatDataSize, BYTE *FormatDataPointer,
        UINT16          MulticastPort)
{
    RTPSessionStream    *rtspStream;        /* RTSP stream structure pointer  */
    RTPSessionStream    *rtspStreamTemp;    /* RTSP stream structure pointer  */
    RTSPSession         *rtspSession;       /* RTSP session structure pointer */

    if (ValidateSessionHandle(SessionHandle) != RET_OK)
    {
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    rtspSession = (RTSPSession *)SessionHandle;

    if (rtspSession == NULL)
    {
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    if (ValidateServerHandle((INT32) rtspSession->RtspServerPtr) != RET_OK)
    {
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    //\\ 0表示输入的是音频
    if (CodecType == 0)
    {
        if ((StreamCodec != CODEC_G711A) && (StreamCodec != CODEC_AAC)   && (StreamCodec != CODEC_MPA)   &&
            (StreamCodec != CODEC_G711U) && (StreamCodec != CODEC_G726) && (StreamCodec != CODEC_L16))
        {
            return RTP_RTSP_INVALID_INPUT_VALUE;
        }

        if ((ClockRate <= 0) || (NumberOfChannels <= 0))
        {
            return RTP_RTSP_INVALID_INPUT_VALUE;
        }
    }
    else if (CodecType == 1)
    {
    	/*cb change 2016.8.5 .添加h265的支持*/ 
        if ((StreamCodec != CODEC_H265) && (StreamCodec != CODEC_H264) && (StreamCodec != CODEC_MPEG4V) && (StreamCodec != CODEC_MJPEG))
        {
            return RTP_RTSP_INVALID_INPUT_VALUE;
        }

        if ((ClockRate <= 0) || ((FormatDataSize > 0) && (FormatDataPointer == NULL)) || ((FormatDataSize <= 0) && (FormatDataPointer != NULL)))
        {
            return RTP_RTSP_INVALID_INPUT_VALUE;
        }

        if (NumberOfChannels > 0)
        {
            return RTP_RTSP_INVALID_INPUT_VALUE;
        }
    }
    else
    {
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    rtspStream = (RTPSessionStream *) malloc(sizeof(RTPSessionStream));

    if (rtspStream == NULL)
    {
        return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
    }

    memset(rtspStream, 0x00, sizeof(RTPSessionStream));
    /* Copy Data in structure                                                 */
    rtspStream->ClockRate               =   ClockRate;
    rtspStream->CodecType               =   CodecType;
    rtspStream->NoOfChannels            =   NumberOfChannels;
    rtspStream->StreamCodec             =   StreamCodec;
    rtspStream->FormatDataSize        =   FormatDataSize;

    //\\ 保存SDP信息
    if (FormatDataSize)
    {
        rtspStream->FormatDataPointer = (BYTE *) malloc(FormatDataSize);

        if (rtspStream->FormatDataPointer == NULL)
        {
            free(rtspStream);
            rtspStream = NULL;
            return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
        }

        memset(rtspStream->FormatDataPointer , 0x00, FormatDataSize);
        memcpy(rtspStream->FormatDataPointer , FormatDataPointer, FormatDataSize);
    }

    switch (StreamCodec)
    {
    	/*cb change 2016.8.5 .添加h265的支持*/ 
        case CODEC_H265:
			strcpy((INT8 *)rtspStream->EncodingName, "H265");
			rtspStream->PayloadNumber   =   96;
            break;
		case CODEC_H264:
            strcpy((INT8 *)rtspStream->EncodingName, "H264");
            rtspStream->PayloadNumber   =   96;
            break;

        case CODEC_MPEG4V:
            strcpy((INT8 *)rtspStream->EncodingName, "MP4V-ES");
            rtspStream->PayloadNumber   =   97;
            break;

        case CODEC_MJPEG:
            strcpy((INT8 *)rtspStream->EncodingName, "JPEG");
            rtspStream->PayloadNumber   =   26;
            break;

        case CODEC_G711A:
            strcpy((INT8 *)rtspStream->EncodingName, "PCMA");
            rtspStream->PayloadNumber   =   8;
            break;

        case CODEC_G711U:
            strcpy((INT8 *)rtspStream->EncodingName, "PCMU");
            rtspStream->PayloadNumber   =   0;
            break;

        case CODEC_AAC:
            strcpy((INT8 *)rtspStream->EncodingName, "mpeg4-generic");
            rtspStream->PayloadNumber   =   98;
            break;

        case CODEC_MPA:
            strcpy((INT8 *)rtspStream->EncodingName, "MPA");
            rtspStream->PayloadNumber   =   14;
            break;

        case CODEC_G726:
            if (rtspStream->ClockRate == 16000)
            {
                strcpy((INT8 *)rtspStream->EncodingName, "G726-16");
            }
            else if (rtspStream->ClockRate == 24000)
            {
                strcpy((INT8 *)rtspStream->EncodingName, "G726-24");
            }
            else if (rtspStream->ClockRate == 32000)
            {
                strcpy((INT8 *)rtspStream->EncodingName, "G726-32");
            }
            else if (rtspStream->ClockRate == 40000)
            {
                strcpy((INT8 *)rtspStream->EncodingName, "G726-40");
            }
            else
            {
                if (rtspStream->FormatDataPointer)
                {
                    free(rtspStream->FormatDataPointer);
                    rtspStream->FormatDataPointer = NULL;
                }

                free(rtspStream);
                rtspStream = NULL;
                return RTP_RTSP_ERROR;
            }

            rtspStream->PayloadNumber   =   100; /*TODO */
            break;

        default:
            break;
    }

    if (MutexLock(&(rtspSession->RtspServerPtr->ServerRtspSessionLock)) != RET_OK)
    {
        if (rtspStream->FormatDataPointer)
        {
            free(rtspStream->FormatDataPointer);
            rtspStream->FormatDataPointer = NULL;
        }

        free(rtspStream);
        rtspStream = NULL;
        return RTP_RTSP_LOCK_FAIL;
    }

    if (rtspSession->SessionStreamList == NULL)
    {
        rtspSession->SessionStreamList = rtspStream;
    }
    else
    {
        rtspStreamTemp = rtspSession->SessionStreamList;

        while (rtspStreamTemp->Next != NULL)
        {
            rtspStreamTemp   = rtspStreamTemp->Next;
        }

        rtspStreamTemp->Next = rtspStream;
        rtspStream->Prev     = rtspStreamTemp;
    }

    if (MutexUnlock(&(rtspSession->RtspServerPtr->ServerRtspSessionLock)) != RET_OK)
    {
        if (rtspStream->FormatDataPointer)
        {
            free(rtspStream->FormatDataPointer);
            rtspStream->FormatDataPointer = NULL;
        }

        free(rtspStream);
        rtspStream = NULL;
        return RTP_RTSP_UNLOCK_FAIL;
    }

    rtspSession->StreamCount++;
    return RTP_RTSP_OK;
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

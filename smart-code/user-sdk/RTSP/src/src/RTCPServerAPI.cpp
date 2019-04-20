/*******************************************************************************
 * Copyright (c) 2009 eInfochips - All rights reserved.
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
 * File Name    :   RTCPServerAPI.c
 *
 * Description  :   This file contains the API implementation of RTCP protocol
 *
 * History:
 *  JUN/11/2009, NOS,   Created the file.
 *  JUN/12/2009, NOS,   Changes done due to integration of some structures of
 *                      RTCP into RTSP structures.
 *
 ******************************************************************************/



/*********************
 * Includes Files
 *********************/
#include "../inc/RtpRtspInclude.h"
#include "../inc/BasicTypes.h"
#include "../inc/RtpRtspCommon.h"
#include "../inc/DbgPrint.h"
#include "../inc/RtspServer.h"
#include "../inc/RtcpServer.h"
#include "../inc/NetStatusEvaluate.h"

/************************
 * Globals & Externs
 ***********************/


/* RTCPStop and RTSPSessionDestroy APIs are called from Application and
 * stack as well,so there is possibility of handle curruption                 */
/* Global Lock to Protect RTCP and RTSP Session list                          */
LOCK_HANDLE     gblRtpRtspListLock;


/*******************************************************************************
 * Function:    RTCPStart
 *
 * Description: This API creates a new RTCP session. It will return the handle
 *              of the new RTCP session. This handle will be used for subsequent
 *              RTCP API calls to send and receive RTCP packets.
 *
 * Parameters :
 *      [IN]  INT32 ClientHandle  - Handle to client structure
 *      [IN]  UINT32 streamNo  - The number of the stream for which user wants
 *                               to open the RTCP session.
 *      [OUT] INT32 *ErrorCode - It will contain Error Code in case of error
 *
 * Return Value:
 *      INT32 - Handle of RTCP Stream
 *              OR
 *              RTP_RTSP_ERROR  - Error occurred.
 *
 *              Any of the Following Error codes will be ErrorCode
 *              Argument in case of error:
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_MEMORY_ALLOCATION_FAIL - Memory allocation failed
 *              RTP_RTSP_SOCKET_CREATION_FAIL   - Socket creation failed
 *              RTP_RTSP_SOCKET_BIND_FAIL       - Socket bind failed
 *              RTP_RTSP_SERVER_THREAD_CREATION_FAIL - Thread Creation failed
 *              RTP_RTSP_LOCK_INITIALIZATION_FAIL - Lock Initialization failed.
 ******************************************************************************/


RTP_RTSPLIB_API INT32 RTCPStart(INT32 ConnClient, INT32 CliStreamHandle)
{
    BYTE           *ip = NULL;          /* IP address for udp socket          */
    UINT16          udpRTCPPort = 0;    /* RTCP Port number for UDP           */
    SOCKET          udpSocket = INVALID_SOCKET;/*UDP receive socket RTCP packet*/
    INT32           resUseFlag = 1 ;    /* Reuse Flag for setsockopt          */
    INT32           windowSize = 0;     /* TCP Windows size                   */
    INT32           windowSizeLen = 0;  /* TCP Windows size Length            */
    INT32           rtcpProtocol = 0;   /* Protocol for RTCP connection       */
    INT32           length = 0;         /*Temporary Variable                  */
    INT32           retVal = 0;         /*Temporary Variable                  */
    SOCKETADDR_IN   server;             /* Socket Info structure              */
    RTCPSessionStruct *rtcpSession = NULL;/* RTCP session to be created       */
    RTSPClient      *conClient = NULL;  /* 'handle' at RTSP Server side       */
    RTPClientStream *tmpData = NULL;    /* Session Data at Server side        */
    RTPClientStream *cliStreamHandle = NULL;    /* Session Data at Server side*/
    RtpRtspDebugPrint(DBG_LEVEL_1, "\nENTER :  \n\tClientHandle = %d\
                                    \n\tstreamHandle = %d\n"\
                      , ConnClient, CliStreamHandle);

    /* Input Argument validation                                              */
    if (!ConnClient)
    {
        RtpRtspDebugPrint(DBG_LEVEL_5, "ClientHandle is %d and cliStreamHandle is %d\n",
                          ConnClient, cliStreamHandle);
        RtpRtspErrorPrint("Invalid Input arguments\n");
        return 0;
    }

    conClient = (RTSPClient *)ConnClient;
    /* Validating the client stream handle                                    */
    tmpData = conClient->ClientStreamList;

    while (tmpData)
    {
        if ((INT32)tmpData == CliStreamHandle)
        {
            break;
        }

        tmpData = tmpData->Next;
    }

    if (!tmpData)
    {
        RtpRtspErrorPrint("Invalid Stream handle passed\n");
        return 0;
    }

    cliStreamHandle = (RTPClientStream *)CliStreamHandle;
    /* Allocate a RTCP session structure for new session                      */
    rtcpSession = (RTCPSessionStruct *) malloc(sizeof(RTCPSessionStruct));

    if (!rtcpSession)
    {
        RtpRtspErrorPrint("Memory Allocation failed\n");
        return 0;
    }

    memset(rtcpSession, 0x00, sizeof(RTCPSessionStruct));
    /* Allocate Memory for Sender statistics of RTCP Session                  */
    rtcpSession->sendRTCPStat = (RTCPSendStats *) malloc(sizeof(RTCPSendStats));

    if (!rtcpSession->sendRTCPStat)
    {
        free(rtcpSession);
        rtcpSession = NULL;
        RtpRtspErrorPrint("Memory Allocation failed\n");
        return 0;
    }

    memset(rtcpSession->sendRTCPStat, 0x00, sizeof(RTCPSendStats));
    RtpRtspDebugPrint(DBG_LEVEL_2, "Memory allocated for new RTCP session structure.\n");
    rtcpSession->packetListCount = 0; /* No packet in packet link list        */
    rtcpSession->parentHandle = (INT32)cliStreamHandle;
    udpRTCPPort = cliStreamHandle->ServerPort + 1;
    ip = conClient->RtspServerPtr->ServerIp;
    /* Check whether rtp is on TCP or UDP for this client                     */
    rtcpProtocol = conClient->rtpTransportProtocol;

    if (rtcpProtocol == UDP)
    {
        /* Create RTCP Receive UDP socket and bind to port number (RTP + 1)   */
        udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (udpSocket < 0)
        {
            RtpRtspErrorPrint("Error in Socket Creation\n");
            free(rtcpSession->sendRTCPStat);
            free(rtcpSession);
            rtcpSession = NULL;
            return 0;
        }

        /* Create RTCP Send UDP socket                                        */
        rtcpSession->rtcpSendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (rtcpSession->rtcpSendSocket < 0)
        {
            RtpRtspErrorPrint("Error in Socket Creation\n");
            CloseServerSock(udpSocket);
            udpSocket = INVALID_SOCKET;
            free(rtcpSession->sendRTCPStat);
            free(rtcpSession);
            rtcpSession = NULL;
            return 0;
        }

        if (setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, (INT8 *)&resUseFlag, sizeof(INT32)) == SOCKET_ERROR)
        {
            RTSP_SER_PE("Failed to set udpSocket SO_REUSEADDR\n");
        }

        length = sizeof(server);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;//inet_addr((INT8*)ip);
        /* Set RTCP port number as (RTP port + 1)                             */
        server.sin_port = htons(udpRTCPPort);

        /* Bind socket to RTCP port                                           */
        if (bind(udpSocket, (struct sockaddr *)&server, length) < 0)
        {
            RtpRtspErrorPrint("Error in Socket bind\n");
            CloseServerSock(udpSocket);
            udpSocket = INVALID_SOCKET;
            CloseServerSock(rtcpSession->rtcpSendSocket);
            rtcpSession->rtcpSendSocket = INVALID_SOCKET;
            free(rtcpSession->sendRTCPStat);
            free(rtcpSession);
            rtcpSession = NULL;
            return 0;
        }

        /* Set the send/recv window size of TCP stack                         */
        windowSize = 1024 * 1024;
        windowSizeLen = sizeof(INT32);

        if (setsockopt(udpSocket, SOL_SOCKET, SO_RCVBUF, (INT8 *)&windowSize, \
                       windowSizeLen) == SOCKET_ERROR)
        {
            RTSP_SER_PE("Failed to set SO_RCVBUF of UDP socket \n");
        }

        if (setsockopt(rtcpSession->rtcpSendSocket, SOL_SOCKET, \
                       SO_SNDBUF, (INT8 *)&windowSize, windowSizeLen) == SOCKET_ERROR)
        {
            RTSP_SER_PE("Failed to set SO_SNDBUF of UDP socket \n");
        }

        rtcpSession->rtcpRecvSocket = udpSocket;
    }

    ((RTPClientStream *)(rtcpSession->parentHandle))->rtcpSessionInfo = rtcpSession;
    /* Stream number found                                                    */
    /* Initialize mutex object of RTCP Session                                */
    MutexInit(&(rtcpSession->rtcpLock));
    /* Initialise rtcpSession->sendRTCPStat                                   */
    rtcpSession->sendRTCPStat->packetCount   = 0;
    rtcpSession->sendRTCPStat->octetCount    = 0;
    rtcpSession->sendRTCPStat->ntpSec        = 0;
    rtcpSession->sendRTCPStat->ntpFrac       = 0;
    rtcpSession->sendRTCPStat->arrivalTimeSR = 0;
    rtcpSession->StopRtcpSession = 0;
    rtcpSession->prtcpTimeInterval = new CRTCPTimeInterval();
    rtcpSession->pNetStatusEvaluate = new CNetStatusEvaluate();

    /* Create a thread to receive RTCP packet of session in case of UDP       */
    if (rtcpProtocol == UDP)
    {
        retVal = ThreadCreate(&(rtcpSession->packetRecvThread),
                              (THREAD_FUNC)RTCPPacketRecvThread, rtcpSession);

        if (retVal != RET_OK)
        {
            CloseServerSock(rtcpSession->rtcpRecvSocket);
            rtcpSession->rtcpRecvSocket = INVALID_SOCKET;
            CloseServerSock(rtcpSession->rtcpSendSocket);
            rtcpSession->rtcpSendSocket = INVALID_SOCKET;
            MutexDestroy(&(rtcpSession->rtcpLock));
            delete(rtcpSession->prtcpTimeInterval);
            rtcpSession->prtcpTimeInterval = NULL;
            delete(rtcpSession->pNetStatusEvaluate);
            rtcpSession->pNetStatusEvaluate = NULL;
            free(rtcpSession->sendRTCPStat);
            free(rtcpSession);
            rtcpSession = NULL;
            return 0;
        }
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "Thread created successfuly.\n");
    RtpRtspDebugPrint(DBG_LEVEL_1, "EXIT : \n\t Returning Successfully\n");
    /* Return RTCP session handle                                             */
    return ((INT32)rtcpSession);
}

/*******************************************************************************
 * Function:    RTCPStop
 *
 * Description: This API closes the RTCP session
 *
 * Parameters :
 *      [IN]  INT32 streamHandle - RTCP Session Handle
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error code:
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 ******************************************************************************/

RTP_RTSPLIB_API INT32 RTCPStop(INT32 streamHandle)
{
    UINT8                packetType = 0;        /* RTCP Packet Type           */
    INT32                rtcpProtocol = 0;      /*Protocol for RTCP connection*/
    RTCPSessionStruct   *rtcpStreamHandle = NULL;/* RTCP Session to be destroyed*/
    RTCPPacketListStruct *tailP = NULL, *tmpP = NULL;/* Local variables for RTCP
                                            Packet link list manipulation     */
    RTCPSSRCListStruct   *tailssrc = NULL, *tmpssrc = NULL;/* Local variables for RTCP
                                            SSRC link list manipulation     */
    RTCPReportBlockList  *tailRB = NULL;        /* Local variables for Report Block
                                               link list manipulation         */
    RtpRtspDebugPrint(DBG_LEVEL_1, "\nENTER:  \n\tstreamHandle = %d\n", \
                      streamHandle);

    /* Input Argument validation                                              */
    if (!streamHandle)
    {
        RtpRtspErrorPrint("Invalid RTCP Handle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Lock Critical Region, as this API can be called from stack as
       well as Application, so any time only one should destroy handle after
       validation                                                             */
    MutexLock(&gblRtpRtspListLock);

    /* Validate the RTCP handle                                               */
    if (ValidateRTCPStreamHandle((RTCPSessionStruct *)streamHandle))
    {
        RtpRtspErrorPrint("Invalid RTCP Handle passed\n");
        /* Unlock Global lock                                                 */
        MutexUnlock(&gblRtpRtspListLock);
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "Argument validation done.\n");
    /* Check for existence of RTCP session                                    */
    rtcpStreamHandle = (RTCPSessionStruct *) streamHandle;

    if (((RTPClientStream *)(rtcpStreamHandle->parentHandle))->rtcpSessionInfo == NULL)
    {
        RtpRtspErrorPrint("No Such RTCP Session exist\n");
        MutexUnlock(&gblRtpRtspListLock);
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Check Transport protocol                                               */
    rtcpProtocol = ((RTPClientStream *)(rtcpStreamHandle->parentHandle))->
                   rtspConnectedClientPtr->rtpTransportProtocol;

    if (rtcpProtocol == UDP)
    {
        /* Wait for thread completion.                                        */
        if (rtcpStreamHandle->packetRecvThread)
        {
            rtcpStreamHandle->StopRtcpSession = 1;
            WaitForThreadCompletion(rtcpStreamHandle->packetRecvThread);
        }

        /* Close udp socket on which thread is blocking                       */
        CloseServerSock(rtcpStreamHandle->rtcpRecvSocket);
        rtcpStreamHandle->rtcpRecvSocket = INVALID_SOCKET;
        /* Close Send Socket                                                  */
        CloseServerSock(rtcpStreamHandle->rtcpSendSocket);
        rtcpStreamHandle->rtcpSendSocket = INVALID_SOCKET;
    }

    /* Stop Timer if started                                                  */
    if (rtcpStreamHandle->hTimer)
    {
        if (RtpRtspStopTimer(rtcpStreamHandle->hTimer) != RET_OK)
        {
            RtpRtspErrorPrint("Error in Stoping the Timer\n");
        }

        rtcpStreamHandle->hTimer = 0;
    }

    /* Lock RTCP Handle                                                       */
    MutexLock(&(rtcpStreamHandle->rtcpLock));
    ((RTPClientStream *)(rtcpStreamHandle->parentHandle))->rtcpSessionInfo = NULL;

    /* Deallocate RTCP session statistics                                     */
    if (rtcpStreamHandle->sendRTCPStat)
    {
        free(rtcpStreamHandle->sendRTCPStat);
    }

    /* Deallocate memory of RTCP Packet and Report Block                      */
    tailP = rtcpStreamHandle->packetList;

    while (tailP != NULL)               /* Deallocate RTCP Packet List        */
    {
        rtcpStreamHandle->packetListCount--;
        /* store next packet list pointer                                     */
        tmpP = tailP->nextPacket;
        tailRB = tailP->rbList;
        free(tailRB);
        /* Deallocate memory of RTCP Packet and its content as per
         * packet type                                                        */
        packetType = tailP->packetType;

        switch (packetType)
        {
            case RTCP_BYE:
                free(tailP->RTCPPacket->byePacket->paddingData);
                free(tailP->RTCPPacket->byePacket->leavingReason);
                free(tailP->RTCPPacket->byePacket);
                break;

            case RTCP_RR:
                free(tailP->RTCPPacket->receiverReport->rb);
                free(tailP->RTCPPacket->receiverReport->paddingData);
                free(tailP->RTCPPacket->receiverReport);
                break;

            case RTCP_SR:
                free(tailP->RTCPPacket->senderReport->rb);
                free(tailP->RTCPPacket->senderReport->paddingData);
                free(tailP->RTCPPacket->senderReport);
                break;

            case RTCP_CUSTOM:
                free(tailP->RTCPPacket->customPacket->customData);
                free(tailP->RTCPPacket->customPacket);
                break;
        }

        /* Deallocate memory of RTCP Packet unioin                            */
        free(tailP->RTCPPacket);
        /* Deallocate memory of packetlist                                    */
        free(tailP);
        /* Get next packet list                                               */
        tailP = tmpP;
    }

    /* Deallocate memory of SSRC list                      */
    tailssrc = rtcpStreamHandle->ssrcList;

    while (tailssrc != NULL)               /* Deallocate SSRC list        */
    {
        rtcpStreamHandle->ssrcListCount--;
        /* store next packet list pointer                                     */
        tmpssrc = tailssrc->nextssrc;
        /* Deallocate memory of ssrclist                                    */
        free(tailssrc);
        /* Get next ssrc list                                               */
        tailssrc = tmpssrc;
    }

    delete(rtcpStreamHandle->prtcpTimeInterval);
    rtcpStreamHandle->prtcpTimeInterval = NULL;
    delete(rtcpStreamHandle->pNetStatusEvaluate);
    rtcpStreamHandle->pNetStatusEvaluate = NULL;
    /* Unlock RTCP Handle                                                     */
    MutexUnlock(&(rtcpStreamHandle->rtcpLock));
    /* Destroy mutex object                                                   */
    MutexDestroy(&(rtcpStreamHandle->rtcpLock));
    /* Deallocate memory of RTCPSession Handle                                */
    free(rtcpStreamHandle);
    rtcpStreamHandle = NULL;
    /* Unlock Global lock                                                     */
    MutexUnlock(&gblRtpRtspListLock);
    RtpRtspDebugPrint(DBG_LEVEL_2, "Freed memory for RTCP session structure.\n");
    RtpRtspDebugPrint(DBG_LEVEL_1, "\nEXIT : \n\tReturn Successfully\n");
    return RTP_RTSP_OK;
}

/*******************************************************************************
 * Function:    RTCPSendByePacket
 *
 * Description: This API generates and sends a BYE RTCP packet
 *
 * Parameters :
 *      [IN]  INT32     streamHandle    - RTCP Session Handle
 *      [IN]  BYTE*     leavingReason   - A string describing the reason for
 *                                      leaving the session.
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error Code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_MEMORY_ALLOCATION_FAIL - Memory allocation failed
 *              RTP_RTSP_SEND_PACKET_FAIL       - Packet Sending failed
 ******************************************************************************/
RTP_RTSPLIB_API INT32 RTCPSendByePacket(INT32   streamHandle, BYTE     *leavingReason)
{
    BYTE                   *packetData = NULL;      /* Packet Data Pointer    */
    BYTE                    *paddingData = NULL;    /* Padding Data           */
    UINT8                   padSize = 0;            /* Pad Size               */
    UINT32                  packetSize = 0;         /* Packet Data size       */
    UINT32                  byePacketLength = 0;    /* Length of Bye Packet   */
    RTCPByePacket           byePacket;              /* RTCP Bye Packet        */
    RTCPSessionStruct      *rtcpStreamHandle = NULL;/* RTCP Session Handle    */
    RTPClientStream        *rtpSessionDataServer = NULL;/* RTSP Server Side Parent*/
    RtpRtspDebugPrint(DBG_LEVEL_1, "\nENTER: \n\tstreamHandle = %d\n\tleavingReason = %s",
                      streamHandle, leavingReason);

    /* Input  Argument Validation                                             */
    if (!streamHandle)
    {
        RtpRtspErrorPrint("Invalid input arguments\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Check RTCP handle                                                      */
    if (ValidateRTCPStreamHandle((RTCPSessionStruct *)streamHandle) != RET_OK)
    {
        RtpRtspErrorPrint("Invalid RTCP Handle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "Argument validation done.\n");
    rtcpStreamHandle = (RTCPSessionStruct *)streamHandle;
    /* Create BYE packet                                                      */
    byePacket.header.version = RTCP_VERSION;
    byePacket.header.count   = 1;
    byePacket.paddingData    = NULL;
    byePacket.leavingReason  = NULL;

    /* Set Padding Bit if Padding data is available                           */
    if (!padSize)
    {
        byePacket.header.p = 0;
    }
    else
    {
        byePacket.header.p = 1;
    }

    byePacket.header.pt    = RTCP_BYE;
    /* Calculate Length of BYE Packet                                         */
    byePacketLength = RTCP_HEADER_SIZE            /* Common Header            */
                      + 4                       /* SSRC size                            */
                      +                         /* Optional leaving reason              */
                      ((leavingReason == NULL) ? 0 : (1 + (UINT32)strlen((INT8 *)leavingReason)))
                      + padSize;                /* Optional Pad Size                    */
    /* 'length' in header is in 32-bit words minus 1                          */
    byePacket.header.length = (round32(byePacketLength)) / 4 - 1;
    rtpSessionDataServer = (RTPClientStream *)rtcpStreamHandle->parentHandle;
    byePacket.ssrc = (UINT32)rtpSessionDataServer->StreamSSRC;

    if (!leavingReason)
    {
        byePacket.leavingReason = NULL;
    }

    packetSize = (byePacket.header.length + 1) * 4;
    /* Allocate memory for packet data                                        */
    packetData = (BYTE *) malloc(packetSize);

    if (NULL == packetData)
    {
        RtpRtspErrorPrint("Memory Allocation Failed\n");
        return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
    }

    memset(packetData, 0, packetSize);
    /* Form the Packet                                                        */
    packetData[0] =    byePacket.header.version << 6
                       |  byePacket.header.p << 5
                       |  byePacket.header.count;    /* 1 BYTE (V+P+SC)                  */
    packetData[1] = byePacket.header.pt;          /* 1 BYTE PT                */
    *(UINT16 *)(packetData + 2) = htons(byePacket.header.length);/*length     */
    *(UINT32 *)(packetData + 4) = htonl(byePacket.ssrc); /* 4 BYTE SSRC       */

    /* Append the leaving reason                                              */
    if (NULL != leavingReason)
    {
        packetData[8] = (BYTE)strlen((INT8 *)leavingReason);
        memcpy(&packetData[9], leavingReason, packetData[8]);
    }

    if (byePacket.header.p)
    {
        INT32 padStart = byePacketLength - padSize;
        memcpy(&packetData[padStart], paddingData, padSize);
        packetData[byePacketLength - 1] = padSize;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "BYE Packet created.Sending the packet...\n");

    /* Send BYE Packet                                                        */
    if (SendPacket(rtcpStreamHandle, packetData, packetSize))
    {
        RtpRtspErrorPrint("Error in Sending BYE Packet\n");
        free(packetData);
        return RTP_RTSP_SEND_PACKET_FAIL;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "BYE Packet sent.\n");

    /* free allocated memory if any                                           */
    if (packetData)
    {
        free(packetData);
    }

    RtpRtspDebugPrint(DBG_LEVEL_1, "\nEXIT: \n\tReturning Successfully\n");
    return RTP_RTSP_OK;
}


/*******************************************************************************
 * Function:    RTCPPacketRecv
 *
 * Description: This API retrieves a RTCP packet from the stack buffer,which is
 *              maintained in the FIFO link-list.
 *
 * Parameters :
 *      [IN]  INT32     streamHandle    - RTCP Session Handle
 *      [OUT] BYTE*     rtcpPacket      - RTCP Packet data
 *      [OUT] UINT32*   packetSize      - Pointer to RTCP Packet size variable
 *      [OUT] UINT8*    packetType      - Pointer to RTCP Packet type variable
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_PACKET_NOT_AVAILABLE   - Packet not available
 ******************************************************************************/

RTP_RTSPLIB_API INT32 RTCPPacketRecv(INT32      streamHandle,  BYTE     *rtcpPacket,
                                     UINT32      *packetSize,   UINT8    *packetType)
{
    RTCPPacketListStruct   *tmpPacketList = NULL;   /* RTCP Received Packets
                                                    link list                 */
    RTCPReportBlockList     *tail = NULL;           /* Report Block link list */
    RTCPSessionStruct       *rtcpStreamHandle = NULL;/* RTCP Session Handle   */
    RtpRtspDebugPrint(DBG_LEVEL_1,
                      "\nENTER:  \n\tstreamHandle = %d\n\trtcpPacket = %d\n\tpacketSize = %d\n\tpacketType = %d",
                      streamHandle, rtcpPacket, packetSize, packetType);

    /* Input Argument Validation                                              */
    if (!streamHandle || !rtcpPacket || !packetSize || !packetType)
    {
        RtpRtspErrorPrint("Invalid Input arguments passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Validate the RTCP Handle                                               */
    if (ValidateRTCPStreamHandle((RTCPSessionStruct *)streamHandle))
    {
        RtpRtspErrorPrint("Invalid RTCP Handle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "Argument validation done.\n");
    rtcpStreamHandle = (RTCPSessionStruct *)streamHandle;

    /* Check whether packet available or not                                  */
    if (!rtcpStreamHandle->packetList)
    {
        RtpRtspDebugPrint(DBG_LEVEL_3, "Exit :  Packet not available \n");
        return RTP_RTSP_PACKET_NOT_AVAILABLE;
    }

    /* Lock critical region                                                   */
    MutexLock(&(rtcpStreamHandle->rtcpLock));

    /* If Packet is already read, free memory of packet and remove from
       link list                                                              */
    if (rtcpStreamHandle->packetList->pktRead)
    {
        RtpRtspDebugPrint(DBG_LEVEL_2,
                          "Freeing memory for previously read packet.\n");
        rtcpStreamHandle->packetListCount--;
        tmpPacketList = rtcpStreamHandle->packetList;
        rtcpStreamHandle->packetList = rtcpStreamHandle->packetList->nextPacket;
        /* Packet is already read. So free the memory                         */
        /* First free the memory for 'rbList'                                 */
        tail = tmpPacketList->rbList;
        free(tmpPacketList->rbList);

        /* Free memory of RTCP Packet in  'RTCPPacket' as per type
         * of packet                                                          */
        switch (tmpPacketList->packetType)
        {
            case RTCP_BYE:
                free(tmpPacketList->RTCPPacket->byePacket);
                break;

            case RTCP_RR:
                free(tmpPacketList->RTCPPacket->receiverReport->rb);
                free(tmpPacketList->RTCPPacket->receiverReport);
                break;

            case RTCP_SR:
                free(tmpPacketList->RTCPPacket->senderReport->rb);
                free(tmpPacketList->RTCPPacket->senderReport);
                break;

            case RTCP_CUSTOM:
                free(tmpPacketList->RTCPPacket->customPacket);
                break;
        }

        /* Free memory of 'RTCPPacket;                                        */
        free(tmpPacketList->RTCPPacket);
        /* Free memory of 'packetList'                                        */
        free(tmpPacketList);
    }

    /* Again check whether there is RTCP packet or not                        */
    if (!rtcpStreamHandle->packetList)
    {
        RtpRtspDebugPrint(DBG_LEVEL_3, "Exit :  Packet not available \n");
        MutexUnlock(&(rtcpStreamHandle->rtcpLock));
        return RTP_RTSP_PACKET_NOT_AVAILABLE;
    }

    /* Check RTCP Packet buffer size                                          */
    if ((*packetSize)  < rtcpStreamHandle->packetList->packetLength)
    {
        RtpRtspErrorPrint("Small Buffer Size from Application\n");
        *packetSize = rtcpStreamHandle->packetList->packetLength;
        /* Unlock Critical Region                                             */
        MutexUnlock(&(rtcpStreamHandle->rtcpLock));
        return RTP_RTSP_SMALL_BUFF_FROM_APPLICATION;
    }

    /* Copy packet type and packet length                                     */
    *packetType = rtcpStreamHandle->packetList->packetType;
    *packetSize = rtcpStreamHandle->packetList->packetLength; /*In BYTEs      */

    /* Copy RTCP Packet and Padding data as per type of Packet                */
    /* free paddingdata                                                       */
    if (*packetType == RTCP_BYE)
    {
        if (rtcpStreamHandle->packetList->RTCPPacket->byePacket->header.p)
        {
            free(rtcpStreamHandle->packetList->RTCPPacket->byePacket->paddingData);
            rtcpStreamHandle->packetList->RTCPPacket->byePacket->paddingData = NULL;
        }

        memcpy(rtcpPacket,
               rtcpStreamHandle->packetList->RTCPPacket->byePacket,
               sizeof(RTCPUserByePacket) - 4);
        ((RTCPUserByePacket *)rtcpPacket)->leavingReason =
            rtcpPacket + sizeof(RTCPUserByePacket);
        memcpy(((RTCPUserByePacket *)rtcpPacket)->leavingReason, \
               rtcpStreamHandle->packetList->RTCPPacket->byePacket->leavingReason, \
               strlen((INT8 *)rtcpStreamHandle->packetList->RTCPPacket->byePacket->leavingReason) + 1);
        /* Free memory of leaving reason string                               */
        free(rtcpStreamHandle->packetList->RTCPPacket->byePacket->leavingReason);
        rtcpStreamHandle->packetList->RTCPPacket->byePacket->leavingReason = NULL;
    }
    else if (*packetType == RTCP_SR)
    {
        if (rtcpStreamHandle->packetList->RTCPPacket->senderReport->header.p)
        {
            free(rtcpStreamHandle->packetList->RTCPPacket->senderReport->paddingData);
            rtcpStreamHandle->packetList->RTCPPacket->senderReport->paddingData = NULL;
        }

        memcpy(rtcpPacket,
               rtcpStreamHandle->packetList->RTCPPacket->senderReport,
               sizeof(RTCPUserSenderReport));
    }
    else if (*packetType == RTCP_CUSTOM)
    {
        UINT32 customDataSize;
        customDataSize =
            (rtcpStreamHandle->packetList->RTCPPacket->customPacket->header.length + 1) * 4;
        memcpy(rtcpPacket,
               rtcpStreamHandle->packetList->RTCPPacket->customPacket->customData,
               customDataSize);
        free(rtcpStreamHandle->packetList->RTCPPacket->customPacket->customData);
        rtcpStreamHandle->packetList->RTCPPacket->customPacket->customData = NULL;
    }
    else
    {
        if (rtcpStreamHandle->packetList->RTCPPacket->receiverReport->header.p)
        {
            free(rtcpStreamHandle->packetList->RTCPPacket->receiverReport->paddingData);
            rtcpStreamHandle->packetList->RTCPPacket->receiverReport->paddingData = NULL;
        }

        memcpy(rtcpPacket,
               rtcpStreamHandle->packetList->RTCPPacket->receiverReport,
               sizeof(RTCPUserReceiverReport));
    }

    /* Mark this Packet as packet read                                        */
    rtcpStreamHandle->packetList->pktRead = 1;
    /* Unlock Critical Region                                                 */
    MutexUnlock(&(rtcpStreamHandle->rtcpLock));
    RtpRtspDebugPrint(DBG_LEVEL_1, "EXIT: \n\tReturning Successfully\n");
    return RET_OK;
}

/*******************************************************************************
 * Function:    RTCPGetNextReportBlock
 *
 * Description: This API gets a report block of the first available received and
 *              read packet.
 *
 * Parameters :
 *      [IN]  INT32     streamHandle        - RTCP Session Handle
 *      [OUT] RTCPReportBlock* reportBlock  - Pointer to report block
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_PACKET_NOT_AVAILABLE   - Packet not available
 *              RTP_RTSP_RB_NOT_AVAILABLE       - Report Block not available
 ******************************************************************************/
RTP_RTSPLIB_API INT32 RTCPGetNextReportBlock(INT32  streamHandle,
        RTCPReportBlock    *reportBlock)
{
    RTCPSessionStruct      *rtcpStreamHandle = NULL;    /* RTCP Session Handle*/
    RtpRtspDebugPrint(DBG_LEVEL_1, "ENTER:  \n\tstreamHandle = %d\
                                \n\treportBlock = %d",
                      streamHandle, reportBlock);

    /*  Input Arguments Validation                                            */
    if (!streamHandle || !reportBlock)
    {
        RtpRtspErrorPrint("Invalid Input arguments\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Check the RTCP Handle                                                  */
    if (ValidateRTCPStreamHandle((RTCPSessionStruct *)streamHandle))
    {
        RtpRtspErrorPrint("Invalid RTCP Handle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "Argument validation done.\n");
    rtcpStreamHandle = (RTCPSessionStruct *)streamHandle;

    /* Check if Any Packet List or Report Block List is available or not      */
    if (!rtcpStreamHandle->packetList)
    {
        reportBlock = NULL;
        RtpRtspDebugPrint(DBG_LEVEL_3, "Packet not available\n");
        return RTP_RTSP_PACKET_NOT_AVAILABLE;
    }

    if (!rtcpStreamHandle->packetList->rbList || !rtcpStreamHandle->packetList->rbList->reportBlock)
    {
        reportBlock = NULL;
        RtpRtspDebugPrint(DBG_LEVEL_3, "Report Block not available\n");
        return RTP_RTSP_RB_NOT_AVAILABLE;
    }

    /* Check whether any packet is read or not                                */
    if (!rtcpStreamHandle->packetList->pktRead)
    {
        reportBlock = NULL;
        RtpRtspErrorPrint("Still any packet is not read. RB not available\n");
        return RTP_RTSP_RB_NOT_AVAILABLE;
    }

    /* Lock critical Region                                                   */
    MutexLock(&(rtcpStreamHandle->rtcpLock));
    /* Copy Report Block to user buffer                                       */
    memcpy(reportBlock, rtcpStreamHandle->packetList->rbList->reportBlock, \
           sizeof(RTCPReportBlock));

    /* Move the pointer to the next Report Block                              */
    if (rtcpStreamHandle->packetList->rbList->nextRB)
    {
        rtcpStreamHandle->packetList->rbList->reportBlock = \
                rtcpStreamHandle->packetList->rbList->nextRB->reportBlock;
        rtcpStreamHandle->packetList->rbList->nextRB = \
                rtcpStreamHandle->packetList->rbList->nextRB->nextRB;
    }

    /* Unlock critical Region                                                 */
    MutexUnlock(&(rtcpStreamHandle->rtcpLock));
    RtpRtspDebugPrint(DBG_LEVEL_1, "EXIT: \n\tReturning Successfully\n");
    return RET_OK;
}


/*******************************************************************************
 * Function:    RTCPSendSenderReport
 *
 * Description: This API generates a SR, calculates the various fields of the SR
 *              and sends it to the receivers
 *
 * Parameters :
 *      [IN]  INT32     streamHandle        - RTCP Session Handle
 *      [IN]  UINT8     rbCount             - Count of RBs to be padded with this
 *                                              packet
 *      [IN]  RTCPReportBlock *reportBlock  - The Report Block to be padded
 *                                          after sender information in SR packet
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_SEND_PACKET_FAIL       - Packet Send failed
 *              RTP_RTSP_ERROR                  - General Error
 ******************************************************************************/

RTP_RTSPLIB_API INT32 RTCPSendSenderReport(INT32  streamHandle,
        UINT8 rbCount, RTCPReportBlock *reportBlock)
{
    BYTE                    *packetData = NULL;     /* Packet Data Pointer    */
    BYTE                    *paddingData = NULL;    /* Padding Data           */
    UINT8                   padSize = 0;            /* Pad Size               */
    INT32                   rbStack = 0;            /* RB in stack            */
    UINT32                  packetSize = 0;         /* Packet Data size       */
    UINT32                  sec = 0;                /* Current Seconds        */
    UINT32                  microsec = 0;           /* Current Micro seconds  */
    DWORD                   rtpTimestamp = 0;   /* RTP timestamp value    */
    DWORD                   tmpTimeStamp = 0;       /* temp timestamp value   */
    INT32                   indexCnt = 0;           /* Local Counter Variable */
    UINT32                  srPacketLength = 0;     /* Length of SR Packet    */
    RTSPSession             *rtspSession = NULL;    /* RTSP session pointer   */
    RTCPSenderReport        sr;                     /* Sender Report          */
    RTCPSessionStruct       *rtcpStreamHandle = NULL;/* RTCP Session Handle   */
    RTPClientStream         *rtpSessionDataServer = NULL;/* RTSP Server Side Parent*/
    RTPSessionStream        *streamParamsTemp = NULL;/* Stream Input Parameters*/
    RtpRtspDebugPrint(DBG_LEVEL_1, "ENTER:  \n\tstreamHandle = %d\
                    \n\trbCount = %d\n\t,reportBlock = %d",
                      streamHandle, rbCount, reportBlock);

    /* Input Argument Validation                                              */
    if (!streamHandle)
    {
        RtpRtspErrorPrint("Invalid streamHandle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    if (rbCount && (!reportBlock))
    {
        RtpRtspErrorPrint("Invalid RB count or RB\n");
        RtpRtspErrorPrint("RB count = %d \n", rbCount);
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Check the number of RBs passed                                         */
    if (rbCount > MAX_RTCP_REPORT_BLOCK)
    {
        RtpRtspErrorPrint("RB count can not be greater than %d\n", MAX_RTCP_REPORT_BLOCK);
        RtpRtspErrorPrint("RB count = %d \n", rbCount);
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Check the RTCP Handle                                                  */
    if (ValidateRTCPStreamHandle((RTCPSessionStruct *)streamHandle))
    {
        RtpRtspErrorPrint("Invalid streamHandle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "Argument validation done.\n");
    rtcpStreamHandle = (RTCPSessionStruct *)streamHandle;
    /* Create Sender Report packet                                            */
    sr.header.version  = RTCP_VERSION;
    sr.header.count    = 0;
    sr.paddingData     = NULL;
    rtpSessionDataServer = (RTPClientStream *)rtcpStreamHandle->parentHandle;
    sr.ssrc = (UINT32)rtpSessionDataServer->StreamSSRC;

    /* Get the current time                                                   */
    if (GetPresentTimeInSec(&sec, &microsec) != RET_OK)
    {
        RtpRtspErrorPrint("Unable to get the current time\n");
        return RTP_RTSP_ERROR;
    }

    /* Get NTP Time Stamp                                                     */
    GetNtpTs(&sr.ntpSec, &sr.ntpFrac, sec, microsec);
    /* Max packet size                                                        */
    packetSize  =   RTCP_HEADER_SIZE    /* Common Header                      */
                    + 4                         /* SSRC size                          */
                    + SENDER_INFO_SIZE          /* Sender info. in SR Packet          */
                    + 32 * (sizeof(RTCPReportBlock))
                    /* Variable Report Blocks                                         */
                    + padSize;                  /* Optional Pad Size                  */
    /* Allocate memory for packet data                                        */
    packetData = (BYTE *) malloc(packetSize);

    if (NULL == packetData)
    {
        RtpRtspErrorPrint("Memory Allocation Failed\n");
        return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
    }

    memset(packetData, 0, packetSize);
    /* Find Report Block in Stack if any                                      */
    rbStack = FindReportBlockInRTSPServer(packetData);
    sr.header.count = rbStack + rbCount;

    if (sr.header.count > MAX_RTCP_REPORT_BLOCK)
    {
        RtpRtspErrorPrint("Invalid Report Block Count\n");
        RtpRtspErrorPrint("Total RB count = %d \n", sr.header.count);
        RtpRtspErrorPrint("Input RB count = %d \n", rbCount);
        free(packetData);
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Set Padding Bit if Padding data is available                           */
    if (!padSize)
    {
        sr.header.p    = 0;
    }
    else
    {
        sr.header.p    = 1;
    }

    sr.header.pt     = RTCP_SR;
    /* Calculate Length of SR Packet in number of BYTEs                       */
    srPacketLength   =  RTCP_HEADER_SIZE          /* Common Header            */
                        + 4                       /* SSRC size                            */
                        + SENDER_INFO_SIZE        /* Sender info. in SR Packet            */
                        + (sr.header.count) * sizeof(RTCPReportBlock)
                        /* Variable Report Blocks                                         */
                        + padSize;                /* Optional Pad Size                    */
    sr.header.length = (round32(srPacketLength)) / 4 - 1;
    /* Calculate RTP Time Stamp of SR Packet                                  */
    rtspSession = rtpSessionDataServer->rtspConnectedClientPtr->RtspSessionPtr;
    /* Lock StreamInfo                                                        */
    MutexLock(&(rtspSession->streamListLock));
    streamParamsTemp = rtspSession->SessionStreamList;

    /* Find the Stream in the Session                                         */
    for (indexCnt = 1; indexCnt <= rtspSession->StreamCount; indexCnt++)
    {
        if (indexCnt == rtpSessionDataServer->streamNumber)
        {
            break;
        }
        else
        {
            streamParamsTemp = streamParamsTemp->Next;
        }
    }

    /* UnLock StreamInfo                                                      */
    MutexUnlock(&(rtspSession->streamListLock));
    tmpTimeStamp = sec * 1000;
    tmpTimeStamp += (microsec / 1000);  /*In milli seconds */

    if (strstr((INT8 *)streamParamsTemp->EncodingName, "G726"))
    {
        rtpTimestamp = ((tmpTimeStamp * (8000 / 1000)) - streamParamsTemp->rtpTimeStamp);
    }
    else
    {
        rtpTimestamp = ((tmpTimeStamp * streamParamsTemp->ClockRate / 1000) - streamParamsTemp->rtpTimeStamp);
    }

    sr.rtpTs      = (UINT32)rtpTimestamp;
    sr.packetSent = rtcpStreamHandle->sendRTCPStat->packetCount;
    sr.octetSent = rtcpStreamHandle->sendRTCPStat->octetCount;
    sr.rb = NULL;
    /* Form the Packet                                                        */
    packetData[0] =    sr.header.version << 6
                       |  sr.header.p << 5
                       |  sr.header.count;           /* 1 BYTE (V+P+SC)                  */
    packetData[1] = sr.header.pt;                 /* 1 BYTE PT                */
    *(UINT16 *)(packetData + 2) = htons(sr.header.length);/*2 BYTE length     */
    *(UINT32 *)(packetData + 4) = htonl(sr.ssrc);  /* 4 BYTE ssrc             */
    *(UINT32 *)(packetData + 8) = htonl(sr.ntpSec);/* 4 BYTE of NTP MSW       */
    *(UINT32 *)(packetData + 12) = htonl(sr.ntpFrac); /* 4 BYTE of NTP LSW      */
    *(UINT32 *)(packetData + 16) = htonl(sr.rtpTs); /* 4 BYTE of RTP TimeStamp  */
    *(UINT32 *)(packetData + 20) = htonl(sr.packetSent); /* 4 BYTE of Total Packet Sent*/
    *(UINT32 *)(packetData + 24) = htonl(sr.octetSent); /* 4 BYTE of Total Octet Sent */

    /* Copy User Report Blocks if any                                         */
    if (rbCount)
    {
        RTCPCopyReportBlocksInBuffer(packetData, rbCount, reportBlock,
                                     (RTCP_HEADER_SIZE + 4 + SENDER_INFO_SIZE + (rbStack * sizeof(RTCPReportBlock))));
    }

    /* Copy Padding data if available                                         */
    if (sr.header.p)
    {
        INT32 padStart = srPacketLength - padSize;
        memcpy(&packetData[padStart], paddingData, padSize);
        packetData[srPacketLength] = padSize;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "SR Packet created. Sending the packet..\n");
    packetSize = (sr.header.length + 1) * 4;

    /* Send Sendor Report Packet                                              */
    if (SendPacket(rtcpStreamHandle, packetData, packetSize))
    {
        RtpRtspErrorPrint("Error in Sending Packet\n");
        free(packetData);
        return RTP_RTSP_SEND_PACKET_FAIL;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "SR Packet sent.\n");

    /* free allocated memory if any                                           */
    if (packetData)
    {
        free(packetData);
    }

    RtpRtspDebugPrint(DBG_LEVEL_1, "EXIT:  \n\tReturning Successfully\n");
    return RET_OK;
}


/*******************************************************************************
 * Function:    RTCPSendSenderReportPeriodic
 *
 * Description: This API generates a SR, calculates the various fields of the SR
 *              and sends it to the receivers periodically specified by user.
 *
 * Parameters :
 *      [IN]  INT32     streamHandle        - RTCP Session Handle
 *      [IN]  UINT32    period              - The interval in millisec after
 *                                          which the SR packet should be send
 *      [IN]  UINT8     random              - If this flag is set,packet should
 *                                          sent randomly.
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_TIMER_NOT_INITIALIZED  - Timer not intialized
 ******************************************************************************/

RTP_RTSPLIB_API INT32 RTCPSendSenderReportPeriodic(INT32  streamHandle, UINT32 period,
        UINT8  random)
{
    RTCPSessionStruct      *rtcpStreamHandle = NULL;    /* RTCP Session Handle*/
    RtpRtspDebugPrint(DBG_LEVEL_1, "ENTER:  \n\tstreamHandle = %d\
                    \n\tperiod = %d\n\trandom = %d",
                      streamHandle, period, random);

    /* Input  Argument  Validation                                            */
    if (!streamHandle)
    {
        RtpRtspErrorPrint("Invalid RTCP Handle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Check the RTCP Handle                                                  */
    if (ValidateRTCPStreamHandle((RTCPSessionStruct *)streamHandle))
    {
        RtpRtspErrorPrint("Invalid RTCP Handle passed\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "Argument validation done.\n");
    rtcpStreamHandle = (RTCPSessionStruct *)streamHandle;

    if (random > 0)
    {
        random = 1;
    }

    RtpRtspDebugPrint(DBG_LEVEL_1, " EXIT : \n\tReturning Successfully\n");
    return RET_OK;
}

/*******************************************************************************
 * Copyright (c) 2009 eInfochips - All rights reserved.
 *
 * This software is authored by eInfochips and is eInfochips' intellectual
 * property, including the copyrights in all countries in the world.
 * This software is provided under a license to use only with all other rights,
 * including ownership rights, being retained by eInfochips.
 *
 * This file may not be distributed, copied, or reproduced in any manner,
 * electronic or otherwise, without the written consent of eInfochips.
 ******************************************************************************/

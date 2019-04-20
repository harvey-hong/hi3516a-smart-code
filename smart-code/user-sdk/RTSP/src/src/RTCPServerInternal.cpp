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
 * File Name    :   RTCPServerInternal.c
 *
 * Description  :   This file contains internal functions used by RTCP stack APIs
 *
 * History:
 *  JUN/12/2009, NOS,   Created the file.
 *
 ******************************************************************************/

/****************
 * Include Files
 ****************/

#include "../inc/RtpRtspInclude.h"
#include "../inc/BasicTypes.h"
#include "../inc/DbgPrint.h"
#include "../inc/RtspServer.h"
#include "../inc/RtcpServer.h"
#include "../inc/RtpRtspCommon.h"
#include "../inc/NetStatusEvaluate.h"

/************************
        Externs
************************/
extern RTSPServer       *gblRtspServer; /* Global Server List   */
extern INT32 tcpSendData;
/*******************************************************************************
 * Function:    SendPacket
 *
 * Description: This function is used to send a RTCP packet. This will be used
 *              by the SR/BYE packets send APIs
 *
 * Parameters :
 *      [IN]  RTCPSessionStruct streamHandle    - RTCP Session Handle
 *      [IN]  BYTE  *packetData     - Pointer to character string to packet data
 *      [IN]  UINT32    packetSize  - Packet size
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error code in case of error:
 *              RET_ERROR   or
 *              RTP_RTSP_MEMORY_ALLOCATION_FAIL - Memory Allocation failed
 *              RTP_RTSP_SOCKET_CREATION_FAIL   - Socket Creation Failed
 *              RTP_RTSP_DATA_SEND_SOCK_ERROR   - Data Sending failed
 *
 ******************************************************************************/

INT32 SendPacket(RTCPSessionStruct *rtcpStreamHandle,
                 BYTE              *packetData,
                 UINT32             packetSize)
{
    BYTE    *interLeavedPacketData = NULL;  /* Inter Leaved data packet for TCP*/
    BYTE    interleavedRTCPNumber = 0;      /* Inter Leaved RTCP Channel number*/
    UINT32  interLeavedPacketSize = 0;      /* Inter Leaved Data size         */
    INT32           bytesRemain = 0;        /* Temporary variable             */
    INT32           bytesSent = 0;          /* Temporary variable             */
    INT32           counter = 0;            /* Temporary variable             */
    INT32           retValue;               /* Store the return value of func */
    SOCKET          udpSocket = INVALID_SOCKET;/* UDP Socket to send RTCP Packet*/
    SOCKETADDR_IN   server;             /* Socket addr structure              */
    RTPClientStream *rtpSessionDataServer = NULL;/* Client Stream Struct ptr  */
    RTSPSession     *rtspSession;           /* RTSP session pointer           */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\tENTER: \n\trtcpStreamHandle = %d\
                        \n\tpacketData = %d\n\tpacketSize = %d",
                      rtcpStreamHandle, packetData, packetSize);
    /* RTSP Server Side implementation                                        */
    rtpSessionDataServer = (RTPClientStream *)(rtcpStreamHandle->parentHandle);

    if (rtpSessionDataServer->rtspConnectedClientPtr == NULL)
    {
        return RET_ERROR;
    }

    rtspSession = rtpSessionDataServer->rtspConnectedClientPtr->RtspSessionPtr;

    /* Lock Client List                                                       */
    if (MutexLock(&(rtspSession->SessionClientListLock)) != RET_OK)
    {
        RtpRtspErrorPrint("Locking of Connected Client List Failed \n");
        return RET_ERROR;
    }

    if (rtpSessionDataServer->rtspConnectedClientPtr->rtpTransportProtocol == TCP)
    {
        /* TCP Connection                                                     */
        /* TCP Interleaved data                                               */
        interleavedRTCPNumber = rtpSessionDataServer->ClientPort + 1;
        interLeavedPacketSize = packetSize
                                + 1    /* 1 byte for of '$'                  */
                                + 1    /* for interleaved RTCP number        */
                                + 2;   /* 2 byte of length                   */
        /* Allocate memory for interleaved data                               */
        interLeavedPacketData = (BYTE *)malloc(interLeavedPacketSize);

        if (NULL == interLeavedPacketData)
        {
            /* UnLock Client List                                                 */
            MutexUnlock(&(rtspSession->SessionClientListLock));
            RtpRtspErrorPrint("Memory Allocation Failed\n");
            return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
        }

        /* Create Interleaved Packet                                          */
        interLeavedPacketData[0] = 0x24;                 /* ASCII of '$'      */
        interLeavedPacketData[1] = interleavedRTCPNumber;/* RTCP Channel
                                                             indentifier      */
        interLeavedPacketData[2] = (0xFF00 & packetSize) >> 8; /*Packet size MSB */
        interLeavedPacketData[3] = 0x00FF & packetSize;  /*Packet size LSB    */
        memcpy(interLeavedPacketData + 4, packetData, packetSize);
        counter = MAX_RETRY;
        bytesSent = 0;
        bytesRemain = interLeavedPacketSize;

        while (1)
        {
            MutexLock(&(rtpSessionDataServer->rtspConnectedClientPtr->RTSPClientSendmsgLock));
            /* Now send the data using sendfile function for zero copy*/
            //            retValue = send(rtpSessionDataServer->rtspConnectedClientPtr->ClientSocket, &interLeavedPacketData[bytesSent], bytesRemain, 0);
            retValue = send(rtpSessionDataServer->rtspConnectedClientPtr->ClientSocket, &interLeavedPacketData[bytesSent], bytesRemain, MSG_NOSIGNAL);
            MutexUnlock(&(rtpSessionDataServer->rtspConnectedClientPtr->RTSPClientSendmsgLock));

            if (retValue == SOCKET_ERROR)
            {
                counter --;

                if (counter == 0)
                {
                    RtpRtspDebugPrint(DBG_LEVEL_3, "Droping Buffer\n");
                    break;
                }

                MSecDelay(10);
            }
            else if (retValue != bytesRemain)
            {
                bytesRemain -= retValue;
                bytesSent += retValue;
            }
            else
            {
                break;
            }
        }

        free(interLeavedPacketData);
    }
    else
    {
        /* UDP Connection                                                     */
        udpSocket = rtcpStreamHandle->rtcpSendSocket;
        server.sin_family = AF_INET;
        /* Set IP of RTSP Client                                              */
        server.sin_addr.s_addr =
            inet_addr((INT8 *)rtpSessionDataServer->rtspConnectedClientPtr->ClientIp);
        /* Set RTCP port number as (RTP port + 1)                             */
        server.sin_port = htons(rtpSessionDataServer->ClientPort + 1);
        /* Send Packet on UDP socket                                          */
        packetSize = sendto(udpSocket,
                            packetData,
                            packetSize,
                            0,
                            (const struct sockaddr *)&server,
                            sizeof(SOCKETADDR_IN));

        if (packetSize <= 0)
        {
            /* UnLock Client List                                                 */
            MutexUnlock(&(rtspSession->SessionClientListLock));
            RtpRtspErrorPrint("Error in Sending Data\n");
            return RTP_RTSP_DATA_SEND_SOCK_ERROR;
        }

        RtpRtspDebugPrint(DBG_LEVEL_2, "RTCP Packet sent.\n");
    }

    /* UnLock Client List                                                 */
    MutexUnlock(&(rtspSession->SessionClientListLock));
    RtpRtspDebugPrint(DBG_LEVEL_3, "\tEXIT :  \n\tReturning Successfully");
    return RET_OK;
}

/*******************************************************************************
 * Function:    RecvPacket
 *
 * Description: This function will be called by the RTCPRecvPacketThread\n
 *              to receive a RTCP packet.
 *
 * Parameters :
 *      [IN]  RTCPSessionStruct streamHandle    - RTCP Session Handle
 *      [IN]  void  *packetData     - Pointer to character string to packet data
 *      [IN]  UINT32    *packetSize - Pointer to Packet size
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error code in case of error:
 *              RET_ERROR   or
 *              RTP_RTSP_MEMORY_ALLOCATION_FAIL - Memory Allocation failed
 *              RTP_RTSP_SOCKET_CREATION_FAIL   - Socket Creation Failed
 *              RTP_RTSP_DATA_RECV_SOCK_ERROR   - Data receiving failed
 *
 ******************************************************************************/
INT32 RecvPacket(RTCPSessionStruct *rtcpStreamHandle,
                 void               *packetData,
                 UINT32             *packetSize)
{
    SOCKET              udpSocket = INVALID_SOCKET; /* UDP Socket to send RTCP Packet*/
    INT32               length = 0;                 /* Local Variable         */
    INT32               retVal = 0;                 /* Local Variable         */
    SOCKETADDR_IN       server;                     /* Socket Info structure  */
    RTPClientStream      *rtpSessionDataServer = NULL;/* Client Stream struct */
    fd_set fdset;
    struct timeval tv;
    RtpRtspDebugPrint(DBG_LEVEL_3, "\tENTER: \n\trtcpStreamHandle = %d\
                        \n\tpacketData = %d\n\tpacketSize = %d",
                      rtcpStreamHandle, packetData, packetSize);
    udpSocket = rtcpStreamHandle->rtcpRecvSocket;
    rtpSessionDataServer = (RTPClientStream *)(rtcpStreamHandle->parentHandle);
    *packetSize = 0;

    /* If UDP Connection                                                      */
    /* Receive Data from RTCP Port                                            */
    if (rtpSessionDataServer->rtspConnectedClientPtr->rtpTransportProtocol == UDP)
    {
        FD_ZERO(&fdset);
        FD_SET(udpSocket, &fdset);
        double dDelay = rtcpStreamHandle->prtcpTimeInterval->GetTransmissionDelay();
        tv.tv_sec = (UINT32)dDelay;
        tv.tv_usec = (UINT32)((dDelay - (double)tv.tv_sec) * 1000000);

        if (select(FD_SETSIZE, &fdset, 0, 0, &tv) < 0)
        {
            return RTP_RTSP_DATA_RECV_SOCK_ERROR;
        }

        if (FD_ISSET(udpSocket, &fdset))
        {
            length = sizeof(SOCKETADDR_IN);
            /* Receive Packet on UDP socket                                       */
            retVal = RtpRtspUDPSockRecv(udpSocket,
                                        (BYTE *)packetData,
                                        MAX_RTCP_PACKET_SIZE,
                                        &server,
                                        &length);

            if (retVal <= 0)
            {
                RtpRtspDebugPrint(DBG_LEVEL_3, "Error in Receiving Data\n");
                return RTP_RTSP_DATA_RECV_SOCK_ERROR;
            }

            *packetSize = retVal;
        }
    }

    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT :  \n\tReturning Succesfully\n");
    return RET_OK;
}

/*******************************************************************************
 * Function:    GetNtpTs
 *
 * Description: This function calculates the NTP Timestamp.
 *
 * Parameters :
 *      [IN]  UINT32 *ntpSec    - Pointer to integer part of NTP timestamp
 *      [IN]  UINT32 *ntpFrac   - Pointer to fractional part of NTP timestamp
 *      [IN]  UINT32 sec        - Current Seconds
 *      [IN]  UINT32 usec       - Current Micro Seconds
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error code in case of error:
 *              RET_ERROR   or
 *              RTP_RTSP_MEMORY_ALLOCATION_FAIL - Memory Allocation failed
 *              RTP_RTSP_SOCKET_CREATION_FAIL   - Socket Creation Failed
 *              RTP_RTSP_DATA_RECV_SOCK_ERROR   - Data receiving failed
 *
 ******************************************************************************/
void GetNtpTs(UINT32 *ntpSec, UINT32 *ntpFrac, UINT32  sec, UINT32  usec)
{
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER:  \n\tntpSec = %d\n\tntpFrac = %d\n", \
                      ntpSec, ntpFrac);
    /*0x83AA7E80 is the number of seconds from 1900 to 1970               */
    *ntpSec = sec + 0x83AA7E80;
    *ntpFrac = (UINT32)(((double)(usec) * (double)0x4000000) / 15625.0);
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT: \n\tReturning Successfully\n");
    return;
}

/*******************************************************************************
 * Function:    AddNewPacket
 *
 * Description: This function adds a new packet in the link list maintained in
 *              rtcpStreamHandle
 *
 * Parameters :
 *      [IN] RTCPSessionStruct* rtcpStreamHandle - RTCP Session handle.
 *      [IN] BYTE*   packetData - Pointer to packet data.
 *      [IN] UINT32  packetSize - Packet size.
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error code in case of error:
 *              RET_ERROR   or
 *              RTP_RTSP_MEMORY_ALLOCATION_FAIL - Memory Allocation failed
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid Input Value
 *              RTP_RTSP_RTCP_PACKET_LIMIT_EXCEEDED - RTCP Packets in List
 *                                                  exceeded Max. packets
 ******************************************************************************/
INT32 AddNewPacket(RTCPSessionStruct   *rtcpStreamHandle,
                   BYTE                *packetData,
                   UINT32               packetSize)
{
    UINT32                  currentSec = 0;     /* Current Number of seconds  */
    UINT32                  currentUsec = 0;    /* Current Number of micro sec*/
    UINT32                  reportBlockSize = 0;/* Total Report Block Size    */
    UINT32                  padSize = 0;        /*     Size of Padding Data   */
    UINT32                  rbCount = 0;        /*     Report Block count     */
    RTCPCommonHeader        header;             /*     RTCP Common Header     */
    RTCPReportBlockList     *tail = NULL;       /*     Report Block Link List */
    RTCPPacketListStruct    *newPacket = NULL;  /*     RTCP Packet Link list  */
    RTCPPacketListStruct    *tailPacket = NULL; /*     RTCP Packet Link list  */
    RTCPSSRCListStruct      *tailssrc = NULL, *tmpssrc = NULL;  /*     SSRC Link list         */
    UINT32                  nLastAdjustTime = 0;
    struct timeval          tv;
    RTSPClient              *pClient = NULL;
    UINT32                  nControlCode = 0;
    //  UINT32 nNetLevel = 0;
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER:  \n\trtcpStreamHandle = %d\n\tpacketData = %d\n\tpacketSize = %d",
                      rtcpStreamHandle, packetData, packetSize);

    /* Validate RTCP Handle                                                   */
    if (ValidateRTCPStreamHandle(rtcpStreamHandle))
    {
        RtpRtspErrorPrint("Invalid RTCP Handle passed \n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    gettimeofday(&tv, NULL);
    /* Parse Header from RTCP packet                                          */
    header.version = (packetData[0] & 0xC0) >> 6;
    header.p       = (packetData[0] & 0x20) >> 5;
    header.count   = packetData[0] & 0x1F;
    header.pt      = packetData[1];
    header.length  = ntohs(*(UINT16 *)(packetData + 2));

    /* RTCP Packet Validation                                                 */
    if (header.version != RTCP_VERSION)
    {
        RtpRtspErrorPrint("Invalid RTCP Version : %d Found \n", header.version);
        return RET_ERROR;
    }

    /* Return error if Payload Type is not supported                          */
    if ((header.pt != RTCP_SR) && (header.pt != RTCP_RR) &&
        (header.pt != RTCP_BYE) && (header.pt != RTCP_CUSTOM))
    {
        RtpRtspErrorPrint("Packet type not supported : %d \n", header.pt);
        return RET_ERROR;
    }

    /* Allocate Memory for RTCPPacketListStruct                               */
    newPacket = (RTCPPacketListStruct *) malloc(sizeof(RTCPPacketListStruct));

    if (NULL == newPacket)
    {
        RtpRtspErrorPrint("Memory Allocation Failed\n");
        return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
    }

    memset(newPacket, 0x00, (sizeof(RTCPPacketListStruct)));
    /* Allocate Memory for RTCP Packet Union                                  */
    newPacket->RTCPPacket = (RTCPPacketUnion *) malloc(sizeof(RTCPPacketUnion));

    if (!newPacket->RTCPPacket)
    {
        RtpRtspErrorPrint("Memory Allocation Failed\n");
        free(newPacket);
        return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
    }

    memset(newPacket->RTCPPacket, 0x00, (sizeof(RTCPPacketUnion)));
    newPacket->nextPacket = NULL;
    /* Copy packet type and packet size in RTCPPacketListStruct               */
    newPacket->packetType   = header.pt;
    newPacket->packetLength = packetSize;
    /* Calculate size of Report Blocks                                        */
    reportBlockSize = header.count * (sizeof(RTCPReportBlock));

    if (header.pt == RTCP_SR)
    {
        /* If Packet type is Sender Report                                    */
        /* Allocate Memory for Sender Report                                  */
        newPacket->RTCPPacket->senderReport =
            (RTCPSenderReport *) malloc(sizeof(RTCPSenderReport));

        if (NULL == newPacket->RTCPPacket->senderReport)
        {
            RtpRtspErrorPrint("Memory Allocation Failed\n");
            free(newPacket->RTCPPacket);
            free(newPacket);
            return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
        }

        memset(newPacket->RTCPPacket->senderReport, 0x00, (sizeof(RTCPSenderReport)));
        /* Fill common header and Sender Information                          */
        newPacket->RTCPPacket->senderReport->header     = header;
        newPacket->RTCPPacket->senderReport->ssrc       = ntohl(*(UINT32 *)(packetData + 4));
        newPacket->RTCPPacket->senderReport->ntpSec     = ntohl(*(UINT32 *)(packetData + 8));
        newPacket->RTCPPacket->senderReport->ntpFrac    = ntohl(*(UINT32 *)(packetData + 12));
        newPacket->RTCPPacket->senderReport->rtpTs      = ntohl(*(UINT32 *)(packetData + 16));
        newPacket->RTCPPacket->senderReport->packetSent = ntohl(*(UINT32 *)(packetData + 20));
        newPacket->RTCPPacket->senderReport->octetSent  = ntohl(*(UINT32 *)(packetData + 24));
        /* Copy the NTP Time                                                  */
        rtcpStreamHandle->sendRTCPStat->ntpSec
            = newPacket->RTCPPacket->senderReport->ntpSec;
        rtcpStreamHandle->sendRTCPStat->ntpFrac
            = newPacket->RTCPPacket->senderReport->ntpFrac;
        GetPresentTimeInSec(&currentSec, &currentUsec);
        /* Time in unit of 1/65536 second                                     */
        rtcpStreamHandle->sendRTCPStat->arrivalTimeSR
            = ((FLOAT)((currentSec * 1000000 + currentUsec) * 65536)) / (FLOAT)(1000000);
        /* Calculate size of Report Blocks                                    */
        reportBlockSize = header.count * (sizeof(RTCPReportBlock));

        if (!header.count)
        {
            newPacket->RTCPPacket->senderReport->rb = NULL;
            newPacket->rbList = NULL;
        }
        else
        {
            /* Allocate Memory for Report Blocks                              */
            newPacket->RTCPPacket->senderReport->rb =
                (RTCPReportBlock *) malloc(reportBlockSize);

            if (NULL == newPacket->RTCPPacket->senderReport->rb)
            {
                RtpRtspErrorPrint("Memory Allocation Failed\n");
                free(newPacket->RTCPPacket->senderReport);
                free(newPacket->RTCPPacket);
                free(newPacket);
                return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
            }

            memset(newPacket->RTCPPacket->senderReport->rb, 0x00, reportBlockSize);
            /* Copy Report Blocks in sender report structure                  */
            RTCPGetReportBlocksFromBuffer(packetData, header.count,
                                          newPacket->RTCPPacket->senderReport->rb,
                                          (sizeof(RTCPCommonHeader) + 4 + SENDER_INFO_SIZE));
            /* Initialize FIFO link list of RBs                               */
            /* Update rbList (type RTCPReportBlockList*)
               in struct RTCPPacketListStruct_                                */
            newPacket->rbList =
                (RTCPReportBlockList *) malloc(header.count * sizeof(RTCPReportBlockList));

            if (NULL == newPacket->rbList)
            {
                RtpRtspErrorPrint("Memory Allocation Failed\n");
                free(newPacket->RTCPPacket->senderReport->rb);
                free(newPacket->RTCPPacket->senderReport);
                free(newPacket->RTCPPacket);
                free(newPacket);
                return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
            }

            memset(newPacket->rbList, 0x00, (header.count * sizeof(RTCPReportBlockList)));
            rbCount = 0;
            tail = newPacket->rbList;

            /* Get the pointers of the RBs                                    */
            while (header.count != rbCount)
            {
                tail->reportBlock = &(newPacket->RTCPPacket->senderReport->rb[rbCount]);
                rbCount++;

                if (header.count != rbCount)
                {
                    tail->nextRB = &(newPacket->rbList[rbCount]);
                    tail = tail->nextRB;
                }
            }
        }

        if (!header.p)
        {
            newPacket->RTCPPacket->senderReport->paddingData = NULL;
            newPacket->RTCPPacket->senderReport->padSize = 0;
        }
        else
        {
            /* Calculate size of Padding Data                                 */
            padSize = packetSize -                      /* Total Packet size  */
                      (sizeof(RTCPCommonHeader)          /* RTCP Common Header */
                       + 4                             /* SSRC size          */
                       + SENDER_INFO_SIZE              /* Sender Information */
                       + reportBlockSize);             /* Report Block size  */
            newPacket->RTCPPacket->senderReport->padSize = padSize;
            /* Allocate Memory For Padding Data                               */
            newPacket->RTCPPacket->senderReport->paddingData =
                (BYTE *)malloc(padSize);

            if (NULL == newPacket->RTCPPacket->senderReport->paddingData)
            {
                RtpRtspErrorPrint("Memory Allocation Failed\n");

                if (newPacket->rbList)
                {
                    free(newPacket->rbList);
                }

                if (newPacket->RTCPPacket->senderReport->rb)
                {
                    free(newPacket->RTCPPacket->senderReport->rb);
                }

                free(newPacket->RTCPPacket->senderReport);
                free(newPacket->RTCPPacket);
                free(newPacket);
                return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
            }

            memset(newPacket->RTCPPacket->senderReport->paddingData, 0x00, padSize);
            /* Copy Padding Data                                              */
            memcpy(newPacket->RTCPPacket->senderReport->paddingData,
                   (packetData
                    + sizeof(RTCPCommonHeader)
                    + 4 /* SSRC size                                  */
                    + SENDER_INFO_SIZE
                    + reportBlockSize
                   ),
                   padSize);
        }
    }
    else if (header.pt == RTCP_RR)
    {
        /* Update the last packet receive time                                */
        ((RTPClientStream *)rtcpStreamHandle->parentHandle)->\
        rtspConnectedClientPtr->lastPktRecvTimeStamp = GetTimeValue();
        /* If Packet type is Receiver Report                                  */
        /* Allocate Memory for Receiver Report                                */
        newPacket->RTCPPacket->receiverReport =
            (RTCPReceiverReport *) malloc(sizeof(RTCPReceiverReport));

        if (NULL == newPacket->RTCPPacket->receiverReport)
        {
            RtpRtspErrorPrint("Memory Allocation Failed\n");
            free(newPacket->RTCPPacket);
            free(newPacket);
            return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
        }

        memset(newPacket->RTCPPacket->receiverReport, 0x00, sizeof(RTCPReceiverReport));
        /* Fill common header and SSRC Information                            */
        newPacket->RTCPPacket->receiverReport->header = header;
        newPacket->RTCPPacket->receiverReport->ssrc   = ntohl(*(UINT32 *)(packetData + 4));

        if (!header.count)
        {
            newPacket->RTCPPacket->receiverReport->rb = NULL;
            newPacket->rbList = NULL;
        }
        else
        {
            /* Allocate Memory for Report Blocks                              */
            newPacket->RTCPPacket->receiverReport->rb =
                (RTCPReportBlock *) malloc(reportBlockSize);

            if (NULL == newPacket->RTCPPacket->receiverReport->rb)
            {
                RtpRtspErrorPrint("Memory Allocation Failed\n");
                free(newPacket->RTCPPacket->receiverReport);
                free(newPacket->RTCPPacket);
                free(newPacket);
                return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
            }

            memset(newPacket->RTCPPacket->receiverReport->rb, 0x00, reportBlockSize);
            /* Copy Report Blocks in Receiver Report structure                */
            RTCPGetReportBlocksFromBuffer(packetData, header.count,
                                          newPacket->RTCPPacket->receiverReport->rb,
                                          (sizeof(RTCPCommonHeader) + 4));
            /* Initialize FIFO link list of RBs                               */
            /* Update rbList (type RTCPReportBlockList*) in
                                                struct RTCPPacketListStruct   */
            newPacket->rbList =
                (RTCPReportBlockList *) malloc(((header.count) * sizeof(RTCPReportBlockList)));

            if (NULL == newPacket->rbList)
            {
                RtpRtspErrorPrint("Memory Allocation Failed\n");
                free(newPacket->RTCPPacket->receiverReport->rb);
                free(newPacket->RTCPPacket->receiverReport);
                free(newPacket->RTCPPacket);
                free(newPacket);
                return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
            }

            memset(newPacket->rbList, 0x00, header.count * sizeof(RTCPReportBlockList));
            rbCount = 0;
            tail = newPacket->rbList;

            /* Get the pointers of RBs                                        */
            while (header.count != rbCount)
            {
                tail->reportBlock = &(newPacket->RTCPPacket->receiverReport->rb[rbCount]);
                rbCount++;

                if (header.count != rbCount)
                {
                    tail->nextRB = &(newPacket->rbList[rbCount]);
                    tail = tail->nextRB;
                }
            }

            /* Update the Last RB in RTCP Handle                              */
            rtcpStreamHandle->lastRB = *(newPacket->rbList->reportBlock);
        }

        if (!header.p)
        {
            newPacket->RTCPPacket->receiverReport->paddingData = NULL;
            newPacket->RTCPPacket->receiverReport->padSize = 0;
        }
        else
        {
            /* Calculate size of Padding Data                                 */
            padSize = packetSize -                  /* Total Packet size      */
                      (sizeof(RTCPCommonHeader)      /* RTCP Common Header     */
                       + 4                         /* SSRC size              */
                       + reportBlockSize);         /* Report Block size      */
            newPacket->RTCPPacket->receiverReport->padSize = padSize;
            /* Allocate Memory For Padding Data                               */
            newPacket->RTCPPacket->receiverReport->paddingData =
                (BYTE *)malloc(padSize);

            if (NULL == newPacket->RTCPPacket->receiverReport->paddingData)
            {
                RtpRtspErrorPrint("Memory Allocation Failed\n");

                if (newPacket->rbList)
                {
                    free(newPacket->rbList);
                }

                if (newPacket->RTCPPacket->receiverReport->rb)
                {
                    free(newPacket->RTCPPacket->receiverReport->rb);
                }

                free(newPacket->RTCPPacket->receiverReport);
                free(newPacket->RTCPPacket);
                free(newPacket);
                return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
            }

            memset(newPacket->RTCPPacket->receiverReport->paddingData, 0x00, padSize);
            /* Copy Padding Data                                              */
            memcpy(newPacket->RTCPPacket->receiverReport->paddingData,
                   (packetData
                    + sizeof(RTCPCommonHeader)
                    + 4 /* SSRC size                                  */
                    + reportBlockSize
                   ),
                   padSize);
        }

        //update ssrc list and the no. of the ssrc of the list
        tailssrc = rtcpStreamHandle->ssrcList;

        while (tailssrc != NULL)
        {
            tmpssrc = tailssrc;

            if (tailssrc->ssrc == newPacket->RTCPPacket->receiverReport->ssrc)
            {
                break;
            }

            tailssrc = tmpssrc->nextssrc;
        }

        if (tailssrc == NULL)
        {
            tailssrc = (RTCPSSRCListStruct *)malloc(sizeof(RTCPSSRCListStruct));

            if (tailssrc == NULL)
            {
                RtpRtspErrorPrint("Memory Allocation Failed\n");

                if (newPacket->rbList)
                {
                    free(newPacket->rbList);
                }

                if (newPacket->RTCPPacket->receiverReport->rb)
                {
                    free(newPacket->RTCPPacket->receiverReport->rb);
                }

                free(newPacket->RTCPPacket->receiverReport);
                free(newPacket->RTCPPacket);
                free(newPacket);
                return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
            }

            memset(tailssrc, 0, sizeof(RTCPSSRCListStruct));
            tailssrc->ssrc = newPacket->RTCPPacket->receiverReport->ssrc;
            tailssrc->nextssrc = NULL;

            if (tmpssrc == NULL)
            {
                rtcpStreamHandle->ssrcList = tailssrc;
            }
            else
            {
                tmpssrc->nextssrc = tailssrc;
            }

            rtcpStreamHandle->ssrcListCount++;
            rtcpStreamHandle->prtcpTimeInterval->SetMemberCount(rtcpStreamHandle->ssrcListCount);
        }

#if 0
        //Net status evaluate
        nLastAdjustTime = rtcpStreamHandle->pNetStatusEvaluate->GetLastAdjustTime();//记录上次调整码流时间，以判断离上次调整是否过去一分钟

        if (0 == nLastAdjustTime) //第一次收到RR包，记录为调整码流时间
        {
            rtcpStreamHandle->pNetStatusEvaluate->SetLastAdjustTime(tv.tv_sec);
        }

        rbCount = 0;

        while (header.count != rbCount)
        {
            if (newPacket->RTCPPacket->receiverReport->rb[rbCount].ssrc == (UINT32)((RTPClientStream *)(rtcpStreamHandle->parentHandle))->StreamSSRC)
            {
                RTSP_SER_PD("Set Report Block.\n");
                rtcpStreamHandle->pNetStatusEvaluate->SetReportBlock(&(newPacket->RTCPPacket->receiverReport->rb[rbCount]), &tv);
                break;
            }

            rbCount++;
        }

        if (nLastAdjustTime < tv.tv_sec - 60)
        {
            nNetLevel = rtcpStreamHandle->pNetStatusEvaluate->GetNetStatus();

            switch (nNetLevel)
            {
                case eNetIdle:
                    break;

                case eNetBusy:
                    break;

                case eNetNormal:
                case eNetLevelUnkown:
                    break;
            }

            rtcpStreamHandle->pNetStatusEvaluate->SetLastAdjustTime(tv.tv_sec);
            rtcpStreamHandle->pNetStatusEvaluate->Reset();
        }

#endif

        if (newPacket->RTCPPacket->receiverReport->rb)
        {
            //Net status evaluate
            nLastAdjustTime = rtcpStreamHandle->pNetStatusEvaluate->GetLastAdjustTime();//记录上次调整码流时间，以判断离上次调整是否过去30秒

            if (0 == nLastAdjustTime) //第一次收到RR包，记录为调整码流时间
            {
                rtcpStreamHandle->pNetStatusEvaluate->SetLastAdjustTime(tv.tv_sec);
                nLastAdjustTime = tv.tv_sec;
            }

            rbCount = 0;

            while (header.count != rbCount)
            {
                if (newPacket->RTCPPacket->receiverReport->rb[rbCount].ssrc == (UINT32)((RTPClientStream *)(rtcpStreamHandle->parentHandle))->StreamSSRC)
                {
                    rtcpStreamHandle->pNetStatusEvaluate->SetReportBlock(&(newPacket->RTCPPacket->receiverReport->rb[rbCount]), &tv);

                    if (rtcpStreamHandle->pNetStatusEvaluate->IsLost())
                    {
                        OUT_TRACK("lost packet,down to the stream, lost : %u, fraction : %u.\n",
                                  newPacket->RTCPPacket->receiverReport->rb->lost, newPacket->RTCPPacket->receiverReport->rb->fraction);
                        pClient = ((RTPClientStream *)(rtcpStreamHandle->parentHandle))->rtspConnectedClientPtr;
                        nControlCode = eBitrateCtrlDown;
                        pClient->RtspSessionPtr->RTPWriter_Callback((UINT32)pClient, (UINT32)pClient->RtspSessionPtr, FS_BITRATE_CONTROL, &nControlCode);
                        rtcpStreamHandle->pNetStatusEvaluate->SetLastAdjustTime(tv.tv_sec);
                    }

                    break;
                }

                rbCount++;
            }

            if (nLastAdjustTime < tv.tv_sec - 30)
            {
                pClient = ((RTPClientStream *)(rtcpStreamHandle->parentHandle))->rtspConnectedClientPtr;
                nControlCode = eBitrateCtrlUp;
                pClient->RtspSessionPtr->RTPWriter_Callback((INT32)pClient, (INT32)pClient->RtspSessionPtr, FS_BITRATE_CONTROL, &nControlCode);
                rtcpStreamHandle->pNetStatusEvaluate->SetLastAdjustTime(tv.tv_sec);
            }
        }
    }
    else if (header.pt == RTCP_CUSTOM)
    {
        /* If Packet type is Custom data                                      */
        /* Allocate Memory for Custom Packet                                  */
        UINT32 customSize = 0;
        newPacket->RTCPPacket->customPacket =
            (RTCPCustomPacket *) malloc(sizeof(RTCPCustomPacket));

        if (NULL == newPacket->RTCPPacket->customPacket)
        {
            RtpRtspErrorPrint("Memory Allocation Failed\n");
            free(newPacket->RTCPPacket);
            free(newPacket);
            return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
        }

        memset(newPacket->RTCPPacket->customPacket, 0x00, (sizeof(RTCPCustomPacket)));
        /* Fill common header                                                 */
        newPacket->RTCPPacket->customPacket->header = header;
        customSize = (newPacket->packetLength) - RTCP_HEADER_SIZE;
        /* Allocate memory for Custom Data                                    */
        newPacket->RTCPPacket->customPacket->customData =
            (BYTE *) malloc(customSize);

        if (NULL == newPacket->RTCPPacket->customPacket->customData)
        {
            RtpRtspErrorPrint("Memory Allocation Failed\n");
            free(newPacket->RTCPPacket->customPacket);
            free(newPacket->RTCPPacket);
            free(newPacket);
            return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
        }

        memset(newPacket->RTCPPacket->customPacket->customData, 0x00, customSize);
        /* Copy custom data                                                   */
        memcpy(newPacket->RTCPPacket->customPacket->customData,
               packetData + RTCP_HEADER_SIZE,
               newPacket->packetLength - RTCP_HEADER_SIZE
              );
        /* Initialize FIFO link list of RBs to NULL                           */
        /* Update rbList (type RTCPReportBlockList*) in
                struct RTCPPacketListStruct_                                  */
        newPacket->rbList = NULL;
    }
    else /* header.pt = RTCP_BYE                                              */
    {
        /* If Packet type is Bye Report                                       */
        /* Allocate Memory for BYE Packet                                     */
        newPacket->RTCPPacket->byePacket =
            (RTCPByePacket *) malloc(sizeof(RTCPByePacket));

        if (NULL == newPacket->RTCPPacket->byePacket)
        {
            RtpRtspErrorPrint("Memory Allocation Failed\n");
            free(newPacket->RTCPPacket);
            free(newPacket);
            return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
        }

        memset(newPacket->RTCPPacket->byePacket, 0x00, (sizeof(RTCPByePacket)));
        /* Fill common header and SSRC Information                            */
        newPacket->RTCPPacket->byePacket->header = header;
        newPacket->RTCPPacket->byePacket->ssrc   = ntohl(*(UINT32 *)(packetData + 4));

        /* Fill Leaving Reason and padding data if any                        */
        /* No leaving reason And No padding data                              */
        if (((header.length + 1) * 4) ==
            (sizeof(RTCPCommonHeader) + (4 * header.count)))
        {
            newPacket->RTCPPacket->byePacket->paddingData   = NULL;
            newPacket->RTCPPacket->byePacket->leavingReason = NULL;
            newPacket->RTCPPacket->byePacket->padSize = 0;
        }
        else
        {
            if (!header.p) /* No Padding Data                                  */
            {
                UINT8 leavingReasonLen = 0;
                leavingReasonLen = packetData[sizeof(RTCPCommonHeader)
                                              + 4 * (header.count)];
                newPacket->RTCPPacket->byePacket->paddingData = NULL;

                if (0 == leavingReasonLen)
                {
                    newPacket->RTCPPacket->byePacket->leavingReason = NULL;
                }
                else
                {
                    /* Allocate memory for Leaving Reason                     */
                    newPacket->RTCPPacket->byePacket->leavingReason =
                        (BYTE *) malloc(leavingReasonLen + 1);

                    if (NULL == newPacket->RTCPPacket->byePacket->leavingReason)
                    {
                        RtpRtspErrorPrint("Memory Allocation Failed\n");
                        free(newPacket->RTCPPacket->byePacket);
                        free(newPacket->RTCPPacket);
                        free(newPacket);
                        return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
                    }

                    memset(newPacket->RTCPPacket->byePacket->leavingReason,
                           0x00, leavingReasonLen + 1);
                    memcpy(newPacket->RTCPPacket->byePacket->leavingReason,
                           (packetData
                            + sizeof(RTCPCommonHeader)
                            + 4 * (header.count) /* SSRCxSC                    */
                            + 1 /* an octet for length of the LR string      */
                           ),
                           leavingReasonLen);
                }
            }
            else /* with Padding Data                                         */
            {
                /* Find Leaving reason of packet                              */
                UINT8 leavingReasonLen = 0, tmpIndex;
                leavingReasonLen = packetData[sizeof(RTCPCommonHeader)
                                              + 4 * (header.count)];

                if (0 == leavingReasonLen)
                {
                    newPacket->RTCPPacket->byePacket->leavingReason = NULL;
                }
                else
                {
                    /* Null Terminate Leaving reason                          */
                    /* Allocate memory for Leaving Reason                     */
                    newPacket->RTCPPacket->byePacket->leavingReason =
                        (BYTE *) malloc(leavingReasonLen + 1);

                    if (NULL == newPacket->RTCPPacket->byePacket->leavingReason)
                    {
                        RtpRtspErrorPrint("Memory Allocation Failed\n");
                        free(newPacket->RTCPPacket->byePacket);
                        free(newPacket->RTCPPacket);
                        free(newPacket);
                        return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
                    }

                    memset(newPacket->RTCPPacket->byePacket->leavingReason,
                           0x00, leavingReasonLen + 1);
                    memcpy(newPacket->RTCPPacket->byePacket->leavingReason,
                           (packetData
                            + sizeof(RTCPCommonHeader)
                            + 4 * (header.count) /* SSRCxSC                    */
                            + 1 /* an octet for length of the LR string      */
                           ),
                           leavingReasonLen);
                }

                /* Find Padsize in Padding data (last octet of padding )
                    or first non zero octet from end of packet                */
                tmpIndex = packetSize - 1;

                while (newPacket->RTCPPacket->byePacket->paddingData[tmpIndex])
                {
                    /* come back from end of packet to first non zero octet   */
                    tmpIndex--;
                    /* Go towards end of packet after leaving reason
                    tmpIndex++;                                               */
                }

                padSize = newPacket->RTCPPacket->byePacket->paddingData[tmpIndex];
                newPacket->RTCPPacket->byePacket->padSize = padSize;
                /* Allocate Memory For Padding Data                           */
                newPacket->RTCPPacket->byePacket->paddingData =
                    (BYTE *)malloc(padSize);

                if (NULL == newPacket->RTCPPacket->byePacket->paddingData)
                {
                    RtpRtspErrorPrint("Memory Allocation Failed\n");

                    if (newPacket->RTCPPacket->byePacket->leavingReason)
                    {
                        free(newPacket->RTCPPacket->byePacket->leavingReason);
                    }

                    free(newPacket->RTCPPacket->byePacket);
                    free(newPacket->RTCPPacket);
                    free(newPacket);
                    return RTP_RTSP_MEMORY_ALLOCATION_FAIL;
                }

                memset(newPacket->RTCPPacket->byePacket->paddingData,
                       0x00, padSize);
                tmpIndex = sizeof(RTCPCommonHeader) + 4 * (header.count) +
                           (leavingReasonLen) ? leavingReasonLen + 1 : 0;
                /* Copy Padding data after leaving reason if present          */
                memcpy(newPacket->RTCPPacket->byePacket->paddingData,
                       (packetData + tmpIndex), padSize);
                /* Initialize FIFO link list of RBs to NULL                   */
                /* Update rbList (type RTCPReportBlockList*) in
                  struct RTCPPacketListStruct_                                */
                newPacket->rbList = NULL;
            }

            //update ssrc list and the no. of the ssrc of the list
            tailssrc = rtcpStreamHandle->ssrcList;

            while (tailssrc != NULL)
            {
                if (tailssrc->ssrc == newPacket->RTCPPacket->receiverReport->ssrc)
                {
                    break;
                }

                tmpssrc = tailssrc;
                tailssrc = tmpssrc->nextssrc;
            }

            if (tailssrc != NULL)
            {
                if (tmpssrc == NULL)
                {
                    rtcpStreamHandle->ssrcList = tailssrc->nextssrc;
                    free(tailssrc);
                    tailssrc = NULL;
                }
                else
                {
                    tmpssrc->nextssrc = tailssrc->nextssrc;
                    free(tailssrc);
                    tailssrc = NULL;
                }

                rtcpStreamHandle->ssrcListCount--;
                rtcpStreamHandle->prtcpTimeInterval->SetMemberCount(rtcpStreamHandle->ssrcListCount);
            }
        }
    }

    /* Lock critical region                                                   */
    MutexLock(&(rtcpStreamHandle->rtcpLock));

    /* Add new packet to the tail of packet link list                         */
    if (rtcpStreamHandle->packetList == NULL)
    {
        rtcpStreamHandle->packetList = newPacket;
    }
    else
    {
        if (rtcpStreamHandle->packetListCount < MAX_NO_RTCP_PACKETS)
        {
            rtcpStreamHandle->packetListCount++; /* Increment Packet count    */
        }
        else
        {
            tailPacket = rtcpStreamHandle->packetList;
            rtcpStreamHandle->packetList = tailPacket->nextPacket;
            free(tailPacket->rbList);

            /* Free memory of RTCP packet and its content as per packet type  */
            switch (tailPacket->packetType)
            {
                case RTCP_BYE:
                    if (tailPacket->RTCPPacket->byePacket->paddingData)
                    {
                        free(tailPacket->RTCPPacket->byePacket->paddingData);
                    }

                    if (tailPacket->RTCPPacket->byePacket->leavingReason)
                    {
                        free(tailPacket->RTCPPacket->byePacket->leavingReason);
                    }

                    free(tailPacket->RTCPPacket->byePacket);
                    break;

                case RTCP_RR:
                    if (tailPacket->RTCPPacket->receiverReport->rb)
                    {
                        free(tailPacket->RTCPPacket->receiverReport->rb);
                    }

                    if (tailPacket->RTCPPacket->receiverReport->paddingData)
                    {
                        free(tailPacket->RTCPPacket->receiverReport->paddingData);
                    }

                    free(tailPacket->RTCPPacket->receiverReport);
                    break;

                case RTCP_SR:
                    if (tailPacket->RTCPPacket->senderReport->rb)
                    {
                        free(tailPacket->RTCPPacket->senderReport->rb);
                    }

                    if (tailPacket->RTCPPacket->senderReport->paddingData)
                    {
                        free(tailPacket->RTCPPacket->senderReport->paddingData);
                    }

                    free(tailPacket->RTCPPacket->senderReport);
                    break;

                case RTCP_CUSTOM:
                    if (tailPacket->RTCPPacket->customPacket->customData)
                    {
                        free(tailPacket->RTCPPacket->customPacket->customData);
                    }

                    free(tailPacket->RTCPPacket->customPacket);
                    break;
            }

            /* Free the memory of RTCP Packet union                           */
            free(tailPacket->RTCPPacket);
            /* Free Packet memory                                             */
            free(tailPacket);
        }

        /* Insert the newPacket in the link-list                              */
        tailPacket = rtcpStreamHandle->packetList;

        while (tailPacket->nextPacket != NULL)
        {
            tailPacket = tailPacket->nextPacket;
        }

        tailPacket->nextPacket = newPacket;
    }

    /* Unlock critical region                                                 */
    MutexUnlock(&(rtcpStreamHandle->rtcpLock));
    RtpRtspDebugPrint(DBG_LEVEL_3, "\tEXIT : \n\tReturning Successfully");
    return RET_OK;
}

/*******************************************************************************
 * Function:    RTCPPacketRecvThread
 *
 * Description: This thread receives RTCP packets and manages a FIFO link list
 *              of all these packets in the session structure.
 *
 * Parameters :
 *      [IN] void* rtcpStreamHandle - RTCP Session handle.
 * Return Value:
 *          None
 ******************************************************************************/

void RTCPPacketRecvThread(void *rtcpStreamHandle)
{
    UINT32  packetSize = 0;     /*      Size of Received Packet               */
    UINT32  retVal = 0;         /*  Temporary variable to store return value  */
    BYTE    packetData[MAX_RTCP_PACKET_SIZE] = {0};/* Received Packet buffer  */
    RTCPSessionStruct *prtcpStreamSession = (RTCPSessionStruct *)rtcpStreamHandle;
    UINT32  SRSize = 0;     /*  Size of SR Packet                       */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER: \n\trtcpStreamHandle = %d",
                      rtcpStreamHandle);

    while (!prtcpStreamSession->StopRtcpSession)
    {
        //Send RTCP packet
        if (prtcpStreamSession->prtcpTimeInterval->IsTime())
        {
            if (RET_OK == SRSend(prtcpStreamSession, &SRSize))
            {
                if (!prtcpStreamSession->prtcpTimeInterval->GetHasSentrtcp())
                {
                    prtcpStreamSession->prtcpTimeInterval->SetHasSentrtcp(true);
                }

                prtcpStreamSession->prtcpTimeInterval->CalculateAvgPackSize(SRSize);
            }
            else
            {
                RtpRtspDebugPrint(DBG_LEVEL_3, "Fail in send RTCP packet. Exiting from RTCP Packet Rx thread.\n");
                ThreadExit((THREAD_HANDLE)((RTCPSessionStruct *)rtcpStreamHandle)->packetRecvThread);
                return;
            }
        }

        /*  Receive RTCP Packet                                               */
        if (RecvPacket(prtcpStreamSession, (void *)packetData, &packetSize))
        {
            RtpRtspDebugPrint(DBG_LEVEL_3, "Fail in RecvPacket. Exiting from RTCP Packet Rx thread.\n");
            ThreadExit((THREAD_HANDLE)((RTCPSessionStruct *)rtcpStreamHandle)->packetRecvThread);
            return;
        }

        if (packetSize)
        {
            /* Add new RTCP packet on Link List                               */
            retVal = AddNewPacket(prtcpStreamSession, packetData, packetSize);

            if (retVal)
            {
                RtpRtspDebugPrint(DBG_LEVEL_3, "Fail to add new packet.Exiting from RTCP Packet Rx thread.\n");
                ThreadExit((THREAD_HANDLE)((RTCPSessionStruct *)rtcpStreamHandle)->packetRecvThread);
                return;
            }

            prtcpStreamSession->prtcpTimeInterval->CalculateAvgPackSize(packetSize);
        }
    }
}

/*******************************************************************************
 * Function:    SRPeriodicSend
 *
 * Description: This is the timer handler registered by the
 *              RTCPSendSenderReportPeriodic API.
 *
 * Parameters :
 *      [IN] void* rtcpStreamHandle - RTCP Session handle.
 * Return Value:
 *      INT32 - RTP_RTSP_OK - On success
 *              OR
 *              Following Error code in case of error:
 *              RTP_RTSP_MEMORY_ALLOCATION_FAIL - Memory Allocation failed
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid Input Value
 *              RTP_RTSP_SEND_PACKET_FAIL       - Packet sending failed
 *              RTP_RTSP_INVALID_STREAM_NUMBER  - Invalid Stream No.
 *              RTP_RTSP_TIMER_NOT_INITIALIZED  - Timer intialization failed
 ******************************************************************************/
INT32 SRPeriodicSend(void *rtcpStreamHandle)
{
    BYTE                *packetData = NULL;     /*    Packet Data Pointer     */
    INT32               rbStack = 0;            /* RB in stack                */
    INT32               indexCnt = 0;           /* Local Counter Variable     */
    UINT32              packetSize = 0;         /*    Packet Data size        */
    DWORD               rtpTimestamp = 0;   /* RTP timestamp value        */
    DWORD               tmpTimeStamp = 0;   /* temp timetsamp value       */
    UINT32              sec = 0;                /*    Current Seconds         */
    UINT32              microsec = 0;           /*    Current Micro seconds   */
    RTSPSession         *rtspSession = NULL;    /* RTSP session pointer       */
    RTCPSenderReport    sr;                     /*    Sender Report to be sent*/
    RTCPSessionStruct   *rtcpHandle = NULL;     /*    RTCP Session Handle     */
    RTPClientStream     *rtpSessionDataServer = NULL;/* Client Stream Info    */
    RTPSessionStream    *streamParamsTemp = NULL;/* Stream Input Parameters   */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER:  \n\t rtcpStreamHandle = %d",
                      rtcpStreamHandle);
    rtcpHandle = (RTCPSessionStruct *)rtcpStreamHandle;

    if (ValidateRTCPStreamHandle(rtcpHandle))
    {
        RtpRtspErrorPrint("Invalid RTCP Handle in Stack\n", rtcpHandle);
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Create SR packet                                                       */
    sr.header.version = RTCP_VERSION;
    sr.paddingData   = NULL;                 /* No Padding Data               */
    sr.header.p      = 0;                    /* Padding bit is reset to 0     */
    sr.header.pt     = RTCP_SR;

    if (GetPresentTimeInSec(&sec, &microsec) != RET_OK)
    {
        RtpRtspErrorPrint("Unable to get the current time\n");
        return RTP_RTSP_ERROR;
    }

    /* Get NTP Time Stamp                                                     */
    GetNtpTs(&sr.ntpSec, &sr.ntpFrac, sec, microsec);
    /* Max packet size                                                        */
    packetSize  = (RTCP_HEADER_SIZE             /* Common Header              */
                   + 4                         /* SSRC size                  */
                   + SENDER_INFO_SIZE          /* Sender info. in SR Packet  */
                   + 32 * (sizeof(RTCPReportBlock)));
    /* Variable Report Blocks     */
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
    sr.header.count = rbStack;
    sr.header.length = (RTCP_HEADER_SIZE
                        + 4 /* SSRC size                                      */
                        + SENDER_INFO_SIZE
                        + (sr.header.count) * sizeof(RTCPReportBlock));
    /* Variable Report Blocks   */
    packetSize = sr.header.length;
    sr.header.length = (round32(sr.header.length)) / 4 - 1;
    rtpSessionDataServer = (RTPClientStream *)(rtcpHandle->parentHandle);
    sr.ssrc = (UINT32)rtpSessionDataServer->StreamSSRC;
    rtspSession = rtpSessionDataServer->rtspConnectedClientPtr->RtspSessionPtr;
    /* Lock StreamInfo                                                        */
    MutexLock(&(rtspSession->streamListLock));
    streamParamsTemp = rtspSession->SessionStreamList;

    /* Find the stream in the session                                         */
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
    tmpTimeStamp += microsec / 1000;

    if (strstr((INT8 *)streamParamsTemp->EncodingName, "G726"))
    {
        rtpTimestamp = ((tmpTimeStamp * (8000 / 1000)) - streamParamsTemp->rtpTimeStamp);
    }
    else
    {
        rtpTimestamp = ((tmpTimeStamp * streamParamsTemp->ClockRate / 1000) - streamParamsTemp->rtpTimeStamp);
    }

    sr.rtpTs      = (UINT32)rtpTimestamp;
    sr.packetSent = rtcpHandle->sendRTCPStat->packetCount;
    sr.octetSent  = rtcpHandle->sendRTCPStat->octetCount;
    sr.rb         = NULL;
    /* Form the Packet                                                        */
    packetData[0] =    sr.header.version << 6
                       |  sr.header.p << 5
                       |  sr.header.count;                 /* 1 BYTE (V+P+SC)            */
    packetData[1] = sr.header.pt;               /* 1 BYTE PT                  */
    *(UINT16 *)(packetData + 2) = htons(sr.header.length);/* 2 BYTE length    */
    *(UINT32 *)(packetData + 4) = htonl(sr.ssrc);     /* 4 BYTE ssrc          */
    *(UINT32 *)(packetData + 8) = htonl(sr.ntpSec);   /* 4 BYTE of NTP MSW    */
    *(UINT32 *)(packetData + 12) = htonl(sr.ntpFrac); /* 4 BYTE of NTP LSW    */
    *(UINT32 *)(packetData + 16) = htonl(sr.rtpTs); /* 4 BYTE of RTP TimeStamp */
    *(UINT32 *)(packetData + 20) = htonl(sr.packetSent); /* 4 BYTE of Total Packet Sent*/
    *(UINT32 *)(packetData + 24) = htonl(sr.octetSent); /* 4 BYTE of Total Octet Sent */
    RtpRtspDebugPrint(DBG_LEVEL_2, "SR Packet created. Sending the packet..\n");

    /* Send Sender Report Packet                                              */
    if (SendPacket(rtcpHandle, packetData, packetSize))
    {
        RtpRtspErrorPrint("Error in Sending Packet.\n");
        free(packetData);
        return RTP_RTSP_SEND_PACKET_FAIL;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "SR Packet sent.\n");
    /* free allocated memory if any                                           */
    free(packetData);
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturning Successfully");
    return RET_OK;
}


/*******************************************************************************
 * Function:    UpdateRTCPSenderStatistics
 *
 * Description: This function updates sender's packet count and octet counts
 *
 * Parameters :
 *      [IN] RTCPSessionStruct *rtcpStreamHandle - RTCP Session handle.
 *      [IN] UINT32 payloadsize - size of payload to be sent in RTP Packet
 * Return Value:
 *          None
 ******************************************************************************/
void UpdateRTCPSenderStatistics(RTCPSessionStruct  *rtcpStreamHandle,
                                UINT32 payloadsize)
{
    rtcpStreamHandle->sendRTCPStat->packetCount++;
    rtcpStreamHandle->sendRTCPStat->octetCount += payloadsize;
}


/*******************************************************************************
 * Function:    ValidateRTCPStreamHandle
 *
 * Description: This function validates the rtcp session handle
 *
 * Parameters :
 *      [IN]    RTCPSessionStruct *rtcpSessionHandle - Pointer to RTCP Session
 * Return Value:
 *          INT32 :
 *                  RET_OK      - On Success
 *                  RET_ERROR   - On Error
 ******************************************************************************/
INT32 ValidateRTCPStreamHandle(RTCPSessionStruct *rtcpSessionHandle)
{
    RTSPServer          *tmpServer = NULL;  /* RTSP Server Link List variable */
    RTSPSession         *tmpSession = NULL; /* RTSP Session Link List variable*/
    RTSPClient          *tmpConnectedClient = NULL;/*Connected Client Link List*/
    RTPClientStream      *tmpRtpSessionData = NULL;/*Client Stream Struct     */
    RTCPSessionStruct   *tmpRtcpSession = NULL; /* RTCP session Link List     */
    RtpRtspDebugPrint(DBG_LEVEL_3, "ENTER: \n\trtcpSessionHandle = %d", rtcpSessionHandle);
    /* RTSP Server side validation                                            */
    tmpServer = gblRtspServer;

    /* Traverse RTSPServer Link List                                          */
    if (tmpServer != NULL)
    {
        tmpSession = tmpServer->RtspSessionList;

        /* Traverse RTSPSession Link List                                     */
        while (tmpSession != NULL)
        {
            tmpConnectedClient = tmpSession->SessionConnectedClientList;

            /* Traverse Connected  Client List List                           */
            while (tmpConnectedClient != NULL)
            {
                tmpRtpSessionData = tmpConnectedClient->ClientStreamList;

                /* Traverse RTP Session Link List                             */
                while (tmpRtpSessionData != NULL)
                {
                    /* Compare stored handle with input handle                */
                    tmpRtcpSession = tmpRtpSessionData->rtcpSessionInfo;

                    if (tmpRtcpSession == rtcpSessionHandle)
                    {
                        return RET_OK;
                    }

                    tmpRtpSessionData = tmpRtpSessionData->Next;
                }

                tmpConnectedClient = tmpConnectedClient->NextClient;
            }

            tmpSession = tmpSession->NextSession;
        }
    }

    RtpRtspDebugPrint(DBG_LEVEL_3, "EXIT :  \n\tReturning With error");
    return RET_ERROR;
}

/*******************************************************************************
 * Function:    FindReportBlockInRTSPServer
 *
 * Description: This function finds last received RB in RTSP Server Side
 *
 * Parameters :
 *      [OUT]   BYTE *packetData - Pointer RTCP Packet data
 * Return Value:
 *          INT32 : Number of Report Block(s)
 ******************************************************************************/
INT32   FindReportBlockInRTSPServer(BYTE *packetData)
{
    INT32               rbCount = 0;        /* Report Block Count in RTSP Server*/
    RTSPServer          *tmpServer = NULL;  /* RTSP Server Link List variable */
    RTSPSession         *tmpSession = NULL; /* RTSP Session Link List variable*/
    RTSPClient          *tmpConnectedClient = NULL;/*Connected Client Link List*/
    RTPClientStream     *tmpRtpSessionData = NULL;/* Client Stream Struct     */
    RTCPSessionStruct   *tmpRtcpSession = NULL; /* RTCP session Link List     */
    /* RTSP Server side validation                                            */
    tmpServer = gblRtspServer;

    /* Traverse RTSPServer Link List                                          */
    if (tmpServer != NULL)
    {
        tmpSession = tmpServer->RtspSessionList;

        /* Traverse RTSPSession Link List                                     */
        while (tmpSession != NULL)
        {
            tmpConnectedClient = tmpSession->SessionConnectedClientList;

            /* Traverse Connected  Client List List                           */
            while (tmpConnectedClient != NULL)
            {
                tmpRtpSessionData = tmpConnectedClient->ClientStreamList;

                /* Traverse RTP Session Link List                             */
                while (tmpRtpSessionData != NULL)
                {
                    /* Copy Report Block if Any                               */
                    tmpRtcpSession = tmpRtpSessionData->rtcpSessionInfo;

                    if (tmpRtcpSession != NULL)
                    {
                        if (tmpRtcpSession->lastRB.ssrc)
                        {
                            if (rbCount < MAX_RTCP_REPORT_BLOCK)
                            {
                                RTCPCopyReportBlocksInBuffer(packetData, 1, &(tmpRtcpSession->lastRB),
                                                             RTCP_HEADER_SIZE + 4 + SENDER_INFO_SIZE + (rbCount * sizeof(RTCPReportBlock)));
                                rbCount++;
                            }
                        }
                    }

                    tmpRtpSessionData = tmpRtpSessionData->Next;
                }

                tmpConnectedClient = tmpConnectedClient->NextClient;
            }

            tmpSession = tmpSession->NextSession;
        }
    }

    return rbCount;
}

/*******************************************************************************
 * Function:    RTCPCopyReportBlocksInBuffer
 *
 * Description: This function copies Report Blocks in Data buffer in network
 *              byte order.
 *
 * Parameters :
 *      [OUT]   BYTE *packetData    - Pointer RTCP Packet data
 *      [IN]    UINT32  rbCount     - Number of Report Blocks
 *      [IN]    RTCPReportBlock *rb - The Report Block to be padded
 *      [IN]    UINT32  rbStart     - Report Block start location in buffer
 *
 * Return Value:
 *      None
 ******************************************************************************/
void  RTCPCopyReportBlocksInBuffer(BYTE *packetData,
                                   UINT32 rbCount,
                                   RTCPReportBlock *rb,
                                   UINT32 rbStart)
{
    UINT32  rbNumber = 0;           /*  Report Block Number                   */
    UINT32  rbStartTmp = 0;         /* Temporary Report Block Start location  */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER: \n\tpacketData = %d\n\trbCount = %u\n\trb = %d\n\trbStart = %u\n",
                      packetData, rbCount, rb, rbStart);

    /* For each Report Block in list                                          */
    for (rbNumber = 0; rbNumber < rbCount; rbNumber++)
    {
        /*  Find RB Start Position in Buffer                                  */
        rbStartTmp = rbStart + (rbNumber * sizeof(RTCPReportBlock));
        /*  Copy 4 bytes of SSRC in buffer                                    */
        *(UINT32 *)(packetData +  rbStartTmp) = htonl(rb[rbNumber].ssrc);
        /* Copy 1 Byte 'fraction' field                                       */
        *(INT8 *)(packetData + rbStartTmp + sizeof(UINT32)) = rb[rbNumber].fraction;
        /* Copy 3 Bytes of 'lost' field                                       */
        *(INT8 *)(packetData + rbStartTmp + sizeof(UINT32) + 1) = \
                ((rb[rbNumber].lost) & 0xFF0000) >> 16;
        *(INT8 *)(packetData + rbStartTmp + sizeof(UINT32) + 2) = \
                ((rb[rbNumber].lost) & 0x00FF00) >> 8;
        *(INT8 *)(packetData + rbStartTmp + sizeof(UINT32) + 3) = \
                (rb[rbNumber].lost) & 0x0000FF;
        /*  Copy 4 bytes of 'lastSeq' in buffer                               */
        *(UINT32 *)(packetData + rbStartTmp + 2 * (sizeof(UINT32))) = \
                htonl(rb[rbNumber].lastSeq);
        /*  Copy 4 bytes of 'jitter' in buffer                                */
        *(UINT32 *)(packetData + rbStartTmp + 3 * (sizeof(UINT32))) = \
                htonl(rb[rbNumber].jitter);
        /*  Copy 4 bytes of 'lsr' in buffer                                   */
        *(UINT32 *)(packetData + rbStartTmp + 4 * (sizeof(UINT32))) = \
                htonl(rb[rbNumber].lsr);
        /*  Copy 4 bytes of 'dlsr' in buffer                                  */
        *(UINT32 *)(packetData + rbStartTmp + 5 * (sizeof(UINT32))) = \
                htonl(rb[rbNumber].dlsr);
    }

    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturning Successfully");
    return;
}
/*******************************************************************************
 * Function:    RTCPGetReportBlocksFromBuffer
 *
 * Description: This function retrieves Report Blocks from buffer.
 *
 * Parameters :
 *      [IN]    BYTE *packetData    - Pointer RTCP Packet data
 *      [IN]    UINT32  rbCount     - Number of Report Blocks
 *      [OUT]   RTCPReportBlock *rb - The Report Block to be padded
 *      [IN]    UINT32  rbStart     - Report Block start location in buffer
 *
 * Return Value:
 *      None
 ******************************************************************************/
void  RTCPGetReportBlocksFromBuffer(BYTE *packetData,
                                    UINT32 rbCount,
                                    RTCPReportBlock *rb,
                                    UINT32 rbStart)
{
    UINT32  rbNumber = 0;           /*  Report Block Number                   */
    UINT32  rbStartTmp = 0;         /* Temporary Report Block Start location  */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER: \n\tpacketData = %d\n\trbCount = %u\n\trb = %d\n\trbStart = %u\n",
                      packetData, rbCount, rb, rbStart);

    /* For each Report Block in list                                          */
    for (rbNumber = 0; rbNumber < rbCount; rbNumber++)
    {
        /*  Find RB Start Position in Buffer                                  */
        rbStartTmp = rbStart + (rbNumber * sizeof(RTCPReportBlock));
        /* Get 4 bytes of SSRC from buffer                                    */
        rb[rbNumber].ssrc = ntohl(*(UINT32 *)(packetData + rbStartTmp));
        /* Get 1 Byte 'fraction' field                                        */
        rb[rbNumber].fraction  = (*(char *)(packetData + rbStartTmp + \
                                            sizeof(UINT32))) & 0xFF;
        /* Get 3 Bytes of 'lost' field                                        */
        rb[rbNumber].lost  = 0;
        rb[rbNumber].lost  = (*(char *)(packetData + rbStartTmp + \
                                        sizeof(UINT32) + 1))  & 0xFF;
        rb[rbNumber].lost <<= 8;
        rb[rbNumber].lost  |= (*(char *)(packetData + rbStartTmp + \
                                         sizeof(UINT32) + 2)) & 0xFF;
        rb[rbNumber].lost <<= 8;
        rb[rbNumber].lost  |= (*(char *)(packetData + rbStartTmp + \
                                         sizeof(UINT32) + 3)) & 0xFF;
        /* Get 4 bytes of 'lastSeq' in buffer                                 */
        rb[rbNumber].lastSeq  = ntohl(*(UINT32 *)(packetData + rbStartTmp + \
                                      2 * (sizeof(UINT32))));
        /* Get 4 bytes of 'jitter' in buffer                                  */
        rb[rbNumber].jitter   = ntohl(*(UINT32 *)(packetData + rbStartTmp + \
                                      3 * (sizeof(UINT32))));
        /* Get 4 bytes of 'lsr' in buffer                                     */
        rb[rbNumber].lsr      = ntohl(*(UINT32 *)(packetData + rbStartTmp + \
                                      4 * (sizeof(UINT32))));
        /* Get 4 bytes of 'dlsr' in buffer                                    */
        rb[rbNumber].dlsr    = ntohl(*(UINT32 *)(packetData + rbStartTmp + \
                                     5 * (sizeof(UINT32))));
    }

    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT :  Return Successfully\n");
}

/*******************************************************************************
* Function:    SRSend
*
* Description: Send sender report.
*
* Parameters :
*      [IN] void* rtcpStreamHandle - RTCP Session handle.
*      [IN/OUT] UINT* pPacketSize- the size of RTCP sender report.
* Return Value:
*      INT32 - RTP_RTSP_OK - On success
*              OR
*              Following Error code in case of error:
*              RTP_RTSP_MEMORY_ALLOCATION_FAIL - Memory Allocation failed
*              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid Input Value
*              RTP_RTSP_SEND_PACKET_FAIL       - Packet sending failed
*              RTP_RTSP_INVALID_STREAM_NUMBER  - Invalid Stream No.
*              RTP_RTSP_TIMER_NOT_INITIALIZED  - Timer intialization failed
******************************************************************************/
INT32 SRSend(void *rtcpStreamHandle, UINT32 *pPacketSize)
{
    BYTE                *packetData = NULL;     /*    Packet Data Pointer     */
    INT32               rbStack = 0;            /* RB in stack                */
    INT32               indexCnt = 0;           /* Local Counter Variable     */
    UINT32              packetSize = 0;         /*    Packet Data size        */
    DWORD               rtpTimestamp = 0;   /* RTP timestamp value        */
   	DWORD               tmpTimeStamp = 0;   /* temp timetsamp value       */
    UINT32              sec = 0;                /*    Current Seconds         */
    UINT32              microsec = 0;           /*    Current Micro seconds   */
    RTSPSession         *rtspSession = NULL;    /* RTSP session pointer       */
    RTCPSenderReport    sr;                     /*    Sender Report to be sent*/
    RTCPSessionStruct   *rtcpHandle = NULL;     /*    RTCP Session Handle     */
    RTPClientStream     *rtpSessionDataServer = NULL;/* Client Stream Info    */
    RTPSessionStream    *streamParamsTemp = NULL;/* Stream Input Parameters   */
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nENTER:  \n\t rtcpStreamHandle = %d",
                      rtcpStreamHandle);
    rtcpHandle = (RTCPSessionStruct *)rtcpStreamHandle;

    if (ValidateRTCPStreamHandle(rtcpHandle))
    {
        RtpRtspErrorPrint("Invalid RTCP Handle in Stack\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    if (pPacketSize == NULL)
    {
        RtpRtspErrorPrint("Invalid pointer.\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    *pPacketSize = 0;
    /* Create SR packet                                                       */
    sr.header.version = RTCP_VERSION;
    sr.paddingData   = NULL;                 /* No Padding Data               */
    sr.header.p      = 0;                    /* Padding bit is reset to 0     */
    sr.header.pt     = RTCP_SR;

    if (GetPresentTimeInSec(&sec, &microsec) != RET_OK)
    {
        RtpRtspErrorPrint("Unable to get the current time\n");
        return RTP_RTSP_ERROR;
    }

    /* Get NTP Time Stamp                                                     */
    GetNtpTs(&sr.ntpSec, &sr.ntpFrac, sec, microsec);
    /* Max packet size                                                        */
    packetSize  = (RTCP_HEADER_SIZE             /* Common Header              */
                   + 4                         /* SSRC size                  */
                   + SENDER_INFO_SIZE          /* Sender info. in SR Packet  */
                   + 32 * (sizeof(RTCPReportBlock)));
    /* Variable Report Blocks     */
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
    sr.header.count = rbStack;
    sr.header.length = (RTCP_HEADER_SIZE
                        + 4 /* SSRC size                                      */
                        + SENDER_INFO_SIZE
                        + (sr.header.count) * sizeof(RTCPReportBlock));
    /* Variable Report Blocks   */
    packetSize = sr.header.length;
    sr.header.length = (round32(sr.header.length)) / 4 - 1;
    rtpSessionDataServer = (RTPClientStream *)(rtcpHandle->parentHandle);
    sr.ssrc = (UINT32)rtpSessionDataServer->StreamSSRC;
    rtspSession = rtpSessionDataServer->rtspConnectedClientPtr->RtspSessionPtr;
    /* Lock StreamInfo                                                        */
    MutexLock(&(rtspSession->streamListLock));
    streamParamsTemp = rtspSession->SessionStreamList;

    /* Find the stream in the session                                         */
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
    tmpTimeStamp += microsec / 1000;

    if (strstr((INT8 *)streamParamsTemp->EncodingName, "G726"))
    {
        rtpTimestamp = ((tmpTimeStamp * (8000 / 1000)) - streamParamsTemp->rtpTimeStamp);
    }
    else
    {
        rtpTimestamp = ((tmpTimeStamp * streamParamsTemp->ClockRate / 1000) - streamParamsTemp->rtpTimeStamp);
    }

    sr.rtpTs      = (UINT32)rtpTimestamp;
    sr.packetSent = rtcpHandle->sendRTCPStat->packetCount;
    sr.octetSent  = rtcpHandle->sendRTCPStat->octetCount;
    sr.rb         = NULL;
    /* Form the Packet                                                        */
    packetData[0] =    sr.header.version << 6
                       |  sr.header.p << 5
                       |  sr.header.count;                 /* 1 BYTE (V+P+SC)            */
    packetData[1] = sr.header.pt;               /* 1 BYTE PT                  */
    *(UINT16 *)(packetData + 2) = htons(sr.header.length);/* 2 BYTE length    */
    *(UINT32 *)(packetData + 4) = htonl(sr.ssrc);     /* 4 BYTE ssrc          */
    *(UINT32 *)(packetData + 8) = htonl(sr.ntpSec);   /* 4 BYTE of NTP MSW    */
    *(UINT32 *)(packetData + 12) = htonl(sr.ntpFrac); /* 4 BYTE of NTP LSW    */
    *(UINT32 *)(packetData + 16) = htonl(sr.rtpTs); /* 4 BYTE of RTP TimeStamp */
    *(UINT32 *)(packetData + 20) = htonl(sr.packetSent); /* 4 BYTE of Total Packet Sent*/
    *(UINT32 *)(packetData + 24) = htonl(sr.octetSent); /* 4 BYTE of Total Octet Sent */
    RtpRtspDebugPrint(DBG_LEVEL_2, "SR Packet created. Sending the packet..\n");

    /* Send Sender Report Packet                                              */
    if (SendPacket(rtcpHandle, packetData, packetSize))
    {
        RtpRtspErrorPrint("Error in Sending Packet.\n");
        free(packetData);
        return RTP_RTSP_SEND_PACKET_FAIL;
    }

    *pPacketSize = packetSize;
    RtpRtspDebugPrint(DBG_LEVEL_2, "SR Packet sent.\n");
    /* free allocated memory if any                                           */
    free(packetData);
    RtpRtspDebugPrint(DBG_LEVEL_3, "\nEXIT : \n\tReturning Successfully");
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

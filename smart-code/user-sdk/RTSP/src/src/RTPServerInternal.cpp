/*******************************************************************************
 * Copyright (c) 2007 eInfochips - All rights reserved.
 * This software is authored by eInfochips and is eInfochips' intellectual
 * property, including the copyrights in all countries in the world.
 * This software is provided under a license to use only with all other rights,
 * including ownership rights, being retained by eInfochips.
 * This file may not be distributed, copied, or reproduced in any manner,
 * electronic or otherwise, without the written consent of eInfochips.
 ******************************************************************************/

/*******************************************************************************
 *
 * File Name    :   RTPServerInternal.c
 *
 * Description  :   This is RTP server internal implementation file.
 *                  It contains functions for generating common RTP packet header
 *                  and sending data to client.
 *
 * History:
 *  JUN/22/2007, UBV,   Created the file.
 *  DEC/27/2007, ARJ,   Separated API and Internal functions in different files
 *  DEC/28/2007, ARJ,   RTP over TCP Feature Added
 *  DEC/30/2007, ARJ,   Updated as per Code Review Comments
 *
 ******************************************************************************/

/****************
 * Include Files
 ****************/
#include "../inc/RtpRtspCommon.h"
#include "../inc/RtspServer.h"
#include "../inc/RtpServer.h"
#include "../inc/DbgPrint.h"
#include <sys/sendfile.h>
#include <errno.h>

#include "../inc/interface/IRtspStream.h"
#include "../inc/GlobalObject.h"
#include "../inc/interface/IRtspStream.h"
using namespace ApplicationLayer;
/*******************************************************************************
 * Function   : GenerateRTPCommonPacketHeader
 *
 * Description: This function generate the common RTP packet header
 *
 * Parameters :
 *      [IN/OUT]  BYTE* pBuffer    - Pointer of buffer
 *      [IN]      ULONG  timeStamp - TimeStamp value
 *      [IN]      BYTE  FrameEnd   - Frame End flag
 *      [IN]      INT32 format     - codec type
 *      [IN]      INT32 ExtensionBit- Flag for Extension Bit
 *
 * Return Value:
 *      None
 ******************************************************************************/

/* cyf

0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|V=2|P|X|  CC   |M|     PT      |       sequence number         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                           timestamp                           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|           synchronization source (SSRC) identifier            |
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
|            contributing source (CSRC) identifiers             |
|                             ....                              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

*/

//是否使用RTCP策略丢包
//#define USE_RTCP_POLICY_LOST_PACKET

//\\ 产生数据包首部
void GenerateRTPCommonPacketHeader(BYTE *PBuffer,      DWORD TimeStamp,
                                   BYTE FrameEnd,      INT32 Format,
                                   INT32 ExtensionBit)
{
    static UINT16 seqno = 0;            /* Packet sequence number             */

    if (ExtensionBit == 0)
    {
        *PBuffer = 0x80;
    }
    else if (ExtensionBit == 1)
    {
        *PBuffer = 0x90;
    }

    // payload type
    *(PBuffer + 1)  = Format | (FrameEnd << 7);
    // sequence number
    ++seqno;
    *(PBuffer + 2)  = (seqno & 0xff00) >> 8;
    *(PBuffer + 3)  = (seqno & 0x00ff);
    // timestamp
    *(PBuffer + 4)  = (UCHAR)((TimeStamp & 0xff000000) >> 24);
    *(PBuffer + 5)  = (UCHAR)((TimeStamp & 0x00ff0000) >> 16);
    *(PBuffer + 6)  = (UCHAR)((TimeStamp & 0x0000ff00) >> 8);
    *(PBuffer + 7)  = (UCHAR)(TimeStamp & 0x000000ff);
    /* SSRC will be stored in these four bytes in RTPSendData functions       */
    *(PBuffer + 8)  =   0;
    *(PBuffer + 9)  =   0;
    *(PBuffer + 10) =   0;
    *(PBuffer + 11) =   0;
}

/*******************************************************************************
 * Function   : RTPSendData
 *
 * Description: Send RTP packet Data to all clients which are in playing state
 *
 * Parameters :
 *      [IN]  BYTE          *SendBuf        -   Send Data Buffer
 *      [IN]  INT32         SendSize        -   Size of Send Data Buffer
 *      [IN]  BYTE          *EncodingName   -   Encoding Name of Codec
 *      [IN]  RTSPSession   *RtspSession    -   Pointer to RTSPSession
 *      [IN]  INT32         DeviceFD        -   Device FD   for sendfile API
 *      [IN]  BYTE          *DataBuf        -   Pointer to data buffer
 *      [IN]  INT32         DataSize        -   Size of Data buffer
 *      [IN]  BYTE          *VZero          -   VZero   pointer for sendfile API
 *      [IN]  INT32         FlagTCPClient   -   Flag to indicate TCP client
 *      [IN]  void          *conn_node      -   Client connection pointer
 *
 * Return Value:
 *      INT32 - RET_OK,     On Success
 *              RET_ERROR,  On Failure
 ******************************************************************************/

// SendBuf中存放的是RTP头，DataBuf才是真正的负载数据
/*cb change 2016.8.5 .添加h265的支持*/ 
INT32 RTPSendData(BYTE *SendBuf, INT32 SendSize, BYTE *EncodingName,
                  RTSPSession *RtspSession,     INT32 nCodecType,
                  BYTE *DataBuf,                INT32 DataSize,
                  BYTE *VZero,                  INT32 FlagTCPClient,
                  void    *conn_node)
{

    struct iovec         msg_iov[3];             /* Pointers to data fragments     */
    struct msghdr     msg;                    /* Collection of data fragments   */
    INT32                 retValue;               /* Store the return value of func */
    INT32                 bytesRemain = 0;        /* Temporary variable             */
    INT32                 bytesSent = 0;          /* Temporary variable             */
    RTSPClient          *rtspClient = NULL;     /* RTSP Client Pointer            */
    RTSPClient          *removeClient = NULL;   /* RTSP Client Pointer            */
    RTPClientStream  *tempStream = NULL;     /* Pointer to Conn Stream         */
    RTPClientStream  *rtspStream = NULL;     /* Pointer to Conn Stream         */
    SOCKET              cliSocket;              /* Client network socket          */
    RTSPServer         *serverPtr = NULL;      /* RTSP Server Pointer            */
    INT32               clientClosed = 0;       /* Client closed flag             */
    INT32                  ret = -1;
    char                    tempIP[16];
    int                      count = 0;
    serverPtr = RtspSession->RtspServerPtr;

    if (NULL == conn_node)
    {
        return RET_ERROR;
    }

    ApplicationLayer::IRtspStream *pStream = (ApplicationLayer::IRtspStream *)conn_node;

    if (MutexLock(&(RtspSession->SessionClientListLock)) != RET_OK)
    {
        return RET_ERROR;
    }

    rtspClient =  RtspSession->SessionConnectedClientList;

    if (rtspClient == NULL)
    {
        MutexUnlock(&(RtspSession->SessionClientListLock));
        return RET_ERROR;
    }

    int         nSendFlag = 0;
    DWORD   dwVideoTimeStamp = 0;

    while (rtspClient)
    {
        // 获取当前帧的时间戳
        retValue = pStream->GetClientConnInfo((int)rtspClient, nSendFlag, dwVideoTimeStamp);
        memset(&msg, 0, sizeof(msg));
        msg_iov[0].iov_base     = SendBuf;
        msg_iov[0].iov_len      = SendSize;
        msg_iov[1].iov_base     = DataBuf;
        msg_iov[1].iov_len      = DataSize;
        msg.msg_iov             = &msg_iov[0];
        msg.msg_iovlen      = 1;
        tempStream = rtspClient->ClientStreamList;

        while (tempStream)
        {
            if (!(strcmp((INT8 *)tempStream->StreamIdentifier, (INT8 *)EncodingName)))
            {
                rtspStream = tempStream;
                break;
            }

            tempStream = tempStream->Next;
        }

        if (tempStream == NULL)
        {
            RtpRtspDebugPrint(DBG_LEVEL_5, "No Such Stream is present in this Client \n");
            rtspClient = rtspClient->NextClient;
            continue;
        }

        msg.msg_name                 = NULL;
        msg.msg_namelen             = 0;

        // 检查各个客户端的状态，只有在播放状态时才发送流
        if (rtspClient->ClientState == CLIENT_PLAYING_STATE)
        {
            rtspClient->IsFirstFrame = 0;

            if ((rtspClient->ClientInterleavedFlag == 0) && (FlagTCPClient == 0))
            {
                rtspStream->StreamSeqNo++;
                /* Store sequence number in send buffer                       */
                *(SendBuf + 2)  = (rtspStream->StreamSeqNo & 0xff00) >> 8;
                *(SendBuf + 3)  = (rtspStream->StreamSeqNo & 0x00ff);

                if (dwVideoTimeStamp > 0)
                {
                    *(SendBuf + 4)  = (UCHAR)((dwVideoTimeStamp & 0xff000000) >> 24);
                    *(SendBuf + 5)  = (UCHAR)((dwVideoTimeStamp & 0x00ff0000) >> 16);
                    *(SendBuf + 6)  = (UCHAR)((dwVideoTimeStamp & 0x0000ff00) >> 8);
                    *(SendBuf + 7)  = (UCHAR)(dwVideoTimeStamp & 0x000000ff);
                }

                *(SendBuf + 8)  = (UCHAR)((rtspStream->StreamSSRC  & 0xff000000) >> 24);
                *(SendBuf + 9)  = (UCHAR)((rtspStream->StreamSSRC  & 0x00ff0000) >> 16);
                *(SendBuf + 10) = (UCHAR)((rtspStream->StreamSSRC  & 0x0000ff00) >> 8);
                *(SendBuf + 11) = (UCHAR)(rtspStream->StreamSSRC  & 0x000000ff);
                cliSocket = rtspStream->RTPConnSocket;  // SETUP时建立的UDP连接
            }
            /* RTP is over TCP                                                */
            else if ((rtspClient->ClientInterleavedFlag == 1) && (FlagTCPClient == 1))
            {
                rtspStream->StreamSeqNo++;
                SendBuf [0]  = 0x24;                   /* 1 byte for '$'      */
                SendBuf [1]  = rtspStream->ClientPort; /* Channel identifier  */
                SendBuf [2]  = (0xff00 & (SendSize + DataSize - TCP_HEADER_SIZE)) >> 8; /* Packet size MSB */
                SendBuf [3]  = 0x00ff & (SendSize + DataSize - TCP_HEADER_SIZE);  /* Packet size LSB      */
                /* Store sequence number in send buffer                       */
                *(SendBuf + 2 + TCP_HEADER_SIZE)  = (rtspStream->StreamSeqNo & 0xff00) >> 8;
                *(SendBuf + 3 + TCP_HEADER_SIZE)  = (rtspStream->StreamSeqNo & 0x00ff);

                if (dwVideoTimeStamp > 0)
                {
                    *(SendBuf + 4 + TCP_HEADER_SIZE)  = (UCHAR)((dwVideoTimeStamp & 0xff000000) >> 24);
                    *(SendBuf + 5 + TCP_HEADER_SIZE)  = (UCHAR)((dwVideoTimeStamp & 0x00ff0000) >> 16);
                    *(SendBuf + 6 + TCP_HEADER_SIZE)  = (UCHAR)((dwVideoTimeStamp & 0x0000ff00) >> 8);
                    *(SendBuf + 7 + TCP_HEADER_SIZE)  = (UCHAR)(dwVideoTimeStamp & 0x000000ff);
                }

                *(SendBuf + 8 + TCP_HEADER_SIZE)  = (UCHAR)((rtspStream->StreamSSRC  & 0xff000000) >> 24);
                *(SendBuf + 9 + TCP_HEADER_SIZE)  = (UCHAR)((rtspStream->StreamSSRC  & 0x00ff0000) >> 16);
                *(SendBuf + 10 + TCP_HEADER_SIZE) = (UCHAR)((rtspStream->StreamSSRC  & 0x0000ff00) >> 8);
                *(SendBuf + 11 + TCP_HEADER_SIZE) = (UCHAR)(rtspStream->StreamSSRC  & 0x000000ff);
                cliSocket = rtspClient->ClientSocket;  // 客户端主动建立的TCP连接（共用RTSP的连接）
            }
            else
            {
                rtspClient = rtspClient->NextClient;
                continue;
            }

            MutexLock(&(rtspClient->RTSPClientSendmsgLock));
            bytesSent = 0;
            bytesRemain = SendSize;

            while (1 && (1 != clientClosed))
            {
                /* MSG_NOSIGNAL flag to diasble SIGPIPE, in case of Socket error while attempting to write on a closed destination socket    */
                //                      retValue = sendmsg(cliSocket, &msg, MSG_MORE | MSG_NOSIGNAL | MSG_DONTWAIT);
                retValue = sendmsg(cliSocket, &msg, MSG_MORE | MSG_NOSIGNAL);

                if (retValue == SOCKET_ERROR)
                {
                    // Set flag to destroy client which has closed its socket
                    if (errno == 32)
                    {
                        clientClosed = 1;
                        break;
                    }
                    else if (errno = 11)
                    {
                        count++;
                        MSecDelay(50);

                        if (count >= 10)
                        {
                            clientClosed = 1;
                            break;
                        }
                        else
                        {
                            msg_iov[0].iov_base = &SendBuf[bytesSent];
                            msg_iov[0].iov_len = bytesRemain;
                            msg.msg_iov = &msg_iov[0];
                            msg.msg_iovlen = 1;
                            continue;
                        }
                    }
                    else
                    {
                        MSecDelay(50);
                        msg_iov[0].iov_base = &SendBuf[bytesSent];
                        msg_iov[0].iov_len = bytesRemain;
                        msg.msg_iov = &msg_iov[0];
                        msg.msg_iovlen = 1;
                    }
                }
                else if (retValue != bytesRemain)
                {
                    bytesSent += retValue;
                    bytesRemain -= retValue;
                    msg_iov[0].iov_base = &SendBuf[bytesSent];
                    msg_iov[0].iov_len = bytesRemain;
                    msg.msg_iov = &msg_iov[0];
                    msg.msg_iovlen = 1;

                    if (retValue > 0)
                    {
                        count = 0;
                    }
                }
                else
                {
                    count = 0;
                    break;
                }
            }

            bytesSent = 0;
            bytesRemain = DataSize;
            msg_iov[0].iov_base     = &DataBuf[bytesSent];
            msg_iov[0].iov_len  = bytesRemain;

            while (1 && (1 != clientClosed))
            {
                /* MSG_NOSIGNAL flag to diasble SIGPIPE, in case of Socket error while attempting to write on a closed destination socket    */
                //                  retValue = sendmsg(cliSocket, &msg, MSG_NOSIGNAL | MSG_DONTWAIT);
                retValue = sendmsg(cliSocket, &msg, MSG_NOSIGNAL);

                if (retValue == SOCKET_ERROR)
                {
                    // Set flag to destroy client which has closed its socket
                    if (errno == 32)
                    {
                        clientClosed = 1;
                        break;
                    }
                    else if (errno = 11)
                    {
                        count++;
                        MSecDelay(50);

                        if (count >= 10)
                        {
                            clientClosed = 1;
                            break;
                        }
                        else
                        {
                            msg_iov[0].iov_base = &DataBuf[bytesSent];
                            msg_iov[0].iov_len = bytesRemain;
                            msg.msg_iov = &msg_iov[0];
                            msg.msg_iovlen = 1;
                            continue;
                        }
                    }
                    else
                    {
                        MSecDelay(50);
                        msg_iov[0].iov_base = &DataBuf[bytesSent];
                        msg_iov[0].iov_len = bytesRemain;
                        msg.msg_iov = &msg_iov[0];
                        msg.msg_iovlen = 1;
                    }
                }
                else if (retValue != bytesRemain)
                {
                    bytesSent += retValue;
                    bytesRemain -= retValue;
                    msg_iov[0].iov_base = &DataBuf[bytesSent];
                    msg_iov[0].iov_len = bytesRemain;
                    msg.msg_iov = &msg_iov[0];
                    msg.msg_iovlen = 1;

                    if (retValue > 0)
                    {
                        count = 0;
                    }
                }
                else
                {
                    count = 0;
                    break;
                }
            }

            MutexUnlock(&(rtspClient->RTSPClientSendmsgLock));

            /* Update the Sender Statistics for RTCP                      */
            if (rtspStream->rtcpSessionInfo)
            {
                UpdateRTCPSenderStatistics(rtspStream->rtcpSessionInfo, DataSize);
            }
        }//\\ end of if (rtspClient->ClientState == CLIENT_PLAYING_STATE)

    SOCKET_CLOSED :

        if (clientClosed == 1)
        {
            //removeClient = rtspClient;
            if ((rtspClient->ClientInterleavedFlag == 1) && (FlagTCPClient == 1))
            {
                CloseServerSock(rtspClient->ClientSocket);
            }
        }

        // Move to next client
        rtspClient = rtspClient->NextClient;

        // Remove client from list which has closed its socket
        if (clientClosed == 1)
        {
            clientClosed = 0;
        }
    } // end of while(rtspClient)

    /* UnLock Client List                                                     */
    if (MutexUnlock(&(RtspSession->SessionClientListLock)) != RET_OK)
    {
        RtpRtspErrorPrint("Unlocking of Connected Client List Lock Failed \n");
        return RET_ERROR;
    }

    return RET_OK;
}

/*******************************************************************************
 * Function:    SendH264DataToClient
 *
 * Description: This function packetize the buffer data as per H.264 RTP packet and send it to the connected UDP clients
 *
 * Parameters :
 *      [IN]  INT32 SessionHandle   - RTSP session Handle
 *      [IN]  BYTE* bufData         - Data buffer pointer from which RTP packets
 *                                    will be generated
 *      [IN]  INT32 BufSize         - Data length
 *      [IN]  BYTE  *HeaderExtension- Header Extension data pointer,
 *                                      this extension will be added in
 *                                      only first packet
 *      [IN]  INT32 HeaderExtensionSize - Size of Header Extension Data
 *      [IN]  UINT16 HeaderExtensionType - Type of Header Extension
 *      [IN]  RTPSessionStream *rtspStream - rtsp Stream pointer
 *      [IN]  INT64 rtpTimeStamp    - NTP format rtptime stamp from application
 *      [IN]  INT32 SendFileFlag    - Sendfile API usage flag
 *      [IN]  INT32 DeviceFD        - Device FD for sendfile API
 *      [IN]  BYTE  *VZero          - VZero pointer for sendfile API
 *      [IN]  BYTE  encodingName    - codec specific name
 *      [IN]  INT32 FlagTCPClient   - Flag to indicate TCP client
 *      [IN]  void  *conn_node      - Client connection pointer
 *      [IN]  INT32 endOfFrameFlag  - Flag to indicate end of frame
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_NO_CLIENT_CONNECTED    - No client connected
 *              RTP_RTSP_DATA_SEND_SOCK_ERROR   - Socket send failed
 *              RTP_RTSP_BAD_H264FRAME_DATA     - BAD H264 frame data
 *              RTP_RTSP_PAYLOAD_NOT_ADDED      - No Stream Added to session
 ******************************************************************************/
 /*cb change 2016.8.5 .添加h265的支持 start*/ 
INT32 SendH264DataToClient(RTSPSession *rtspSession,   BYTE *bufData,
                           INT32 bufSize,              BYTE  *HeaderExtension,
                           INT32 HeaderExtensionSize,
                           UINT16 HeaderExtensionType, RTPSessionStream *rtspStream,
                           DWORD rtpTimeStamp,         INT32 SendFileFlag,
                           INT32 nCodecType,             BYTE  *VZero,
                           BYTE *encodingName,         INT32 FlagTCPClient,
                           void *conn_node,            INT32 endOfFrameFlag)
{
    BYTE            videoSendBuf[5 * UDP_MAX_PACKET_SIZE];   /* Send buffer array */
    BYTE            start = 1;          /* Start value used for FU header     */
    BYTE            end   = 0;          /* End value used for FU header       */
    INT32           first = 0;          /* Counter to number of bytes sent    */
    INT32           nalType;            /* Stores The NAL Type                */
    INT32           maxPayload;         /* Max payload size                   */
    INT32           rtpPayload;         /* Payload size variable              */
    UINT32          headerExtStart = 0; /* Start Header Extension data        */
    UINT32          rtpDataStart = 0;   /* Start of RTP data                  */

    /*  If TCP client use Maximum MTU size 0x8000                             */
    if (FlagTCPClient)
    {
        maxPayload   = (rtspSession->TcpMTUSize) - RTPHEADERSIZE - ((HeaderExtensionSize > 0) ? ((round32(HeaderExtensionSize)) + 4) : 0);

        if ((rtspSession->SessionSingleMode) && (bufSize > (rtspSession->TcpMTUSize - RTPHEADERSIZE)))
        {
            RTSP_SER_PN("Nal Size Greater Than TCP MTU Size Ignor Frame. . .\n");
            return RTP_RTSP_OK;
        }
    }
    else
    {
        maxPayload   = (rtspSession->UdpMTUSize) - RTPHEADERSIZE - ((HeaderExtensionSize > 0) ? ((round32(HeaderExtensionSize)) + 4) : 0);

        if ((rtspSession->SessionSingleMode) && (bufSize > (rtspSession->UdpMTUSize - RTPHEADERSIZE)))
        {
            RTSP_SER_PN("Nal Size Greater Than UDP MTU Size Ignor Frame. . .\n");
            return RTP_RTSP_OK;
        }
    }

    if (bufSize < 5)
    {
        return RTP_RTSP_BAD_H264FRAME_DATA;
    }

    //  注意，在RTP over H264时，不传输NALU前的起始码，所以这里去掉了00 00 00 01
    bufData += 4;
    bufSize -= 4;

    if (bufSize <= maxPayload)
    {
        if (FlagTCPClient == 1)
        {
            rtpDataStart  = TCP_HEADER_SIZE;
        }
        else
        {
            rtpDataStart = 0;
        }

        rtpPayload = bufSize;
        GenerateRTPCommonPacketHeader(videoSendBuf + rtpDataStart, rtpTimeStamp, (BYTE)(endOfFrameFlag), rtspStream->PayloadNumber /*for H264, it equals 96 */, ((HeaderExtensionSize > 0) ? 1 : 0));
        /* Copy Header Extension in video send buffer                         */
        headerExtStart = 0;

        if (HeaderExtensionSize > 0)
        {
            headerExtStart = RTPHEADERSIZE + rtpDataStart;
            /* Header Extension type                                          */
            *(videoSendBuf + headerExtStart) = (HeaderExtensionType & 0xFF00) >> 8;
            *(videoSendBuf + headerExtStart + 1) = (HeaderExtensionType & 0xFF);
            /* Write Header Extension size in 32 bit words                    */
            *(videoSendBuf + headerExtStart + 2/* Two Profile Specific data */) = (((round32(HeaderExtensionSize)) / 4) & 0xff00) >> 8;
            *(videoSendBuf + headerExtStart + 3/* Two Profile Specific data */) = (((round32(HeaderExtensionSize)) / 4) & 0x00ff);
            /* Copy Header Extension Data                                     */
            memset(videoSendBuf + headerExtStart + 4, 0, round32(HeaderExtensionSize));
            memcpy(videoSendBuf + headerExtStart + 4, HeaderExtension, HeaderExtensionSize);
        }

        rtpDataStart +=  RTPHEADERSIZE                /* RTP Common Header     */
                         + ((HeaderExtensionSize > 0) ?  /* Extension data If any    */
                            ((round32(HeaderExtensionSize)) + 4) : 0
                            /* Extension size + Header    */
                           );

        /* Send the data to the connected clients                             */
        if (RTPSendData(videoSendBuf, rtpDataStart, encodingName, rtspSession,
                        nCodecType, bufData, rtpPayload, VZero , FlagTCPClient, conn_node) == RET_ERROR)
        {
            RtpRtspDebugPrint(DBG_LEVEL_5 , "Error in sending data over socket using Zero copy\n");
            return RTP_RTSP_DATA_SEND_SOCK_ERROR;
        }

        /* Header Extension Size is set to 0 so that only 1st packet contains header extension                                      */
        HeaderExtensionSize = 0;
    }
    else
    {
        if (rtspSession->SessionSingleMode)
        {
            RtpRtspErrorPrint("Single mode streaming is set so can not send packet(%d) more than MTU size(%d), payload = %d\n",
                              bufSize, (FlagTCPClient ? (rtspSession->TcpMTUSize) : (rtspSession->UdpMTUSize)), maxPayload);
            return RTP_RTSP_ERROR;
        }

        // 注意此处的nalType代表了NALU Header
        //nalType = *bufData;
        // 分段的NAL注意，NAL头不传输，有效负载从NAL头之后开始，根据NAL头的信息生成FU的头两个字节（相当于NAL头拆为两部分）
        //bufData++;
        //bufSize--;
        if(nCodecType == 5)
            maxPayload = ((FlagTCPClient ? (rtspSession->TcpMTUSize) : (rtspSession->UdpMTUSize))) -
                         RTPHEADERSIZE - H265HEADERSIZE
                         - ((HeaderExtensionSize > 0) ?    /* Extension data if any*/
                            ((round32(HeaderExtensionSize)) + 4) : 0
                            /* Extension size + Header    */
                           );
        else if(nCodecType == 6)
            maxPayload = ((FlagTCPClient ? (rtspSession->TcpMTUSize) : (rtspSession->UdpMTUSize))) -
                         RTPHEADERSIZE - H264HEADERSIZE
                         - ((HeaderExtensionSize > 0) ?    /* Extension data if any*/
                            ((round32(HeaderExtensionSize)) + 4) : 0
                            /* Extension size + Header    */
                           );

        while (end == 0)
        {
            if (FlagTCPClient == 1)
            {
                rtpDataStart  = TCP_HEADER_SIZE;
            }
            else
            {
                rtpDataStart = 0;
            }

            rtpPayload = maxPayload < bufSize ? maxPayload : bufSize;

            if (bufSize == rtpPayload)
            {
                end = 1;
            }

            GenerateRTPCommonPacketHeader(videoSendBuf + rtpDataStart, rtpTimeStamp, (BYTE)((end) ? endOfFrameFlag : 0),
                                          rtspStream->PayloadNumber, ((HeaderExtensionSize > 0) ? 1 : 0));
            /* Copy Header Extension in video send buffer                     */
            headerExtStart = 0;

            if (HeaderExtensionSize > 0)
            {
                headerExtStart = RTPHEADERSIZE + rtpDataStart;
                /* Header Extension type                                      */
                *(videoSendBuf + headerExtStart) = (HeaderExtensionType & 0xFF00) >> 8;
                *(videoSendBuf + headerExtStart + 1) = (HeaderExtensionType & 0xFF);
                /* Write Header Extension size in 32 bit words                */
                *(videoSendBuf + headerExtStart + 2/* Two Profile Specific data */) =
                    (((round32(HeaderExtensionSize)) / 4) & 0xff00) >> 8;
                *(videoSendBuf + headerExtStart + 3/* Two Profile Specific data */) =
                    (((round32(HeaderExtensionSize)) / 4) & 0x00ff);
                /* Copy Header Extension Data                                 */
                memset(videoSendBuf + headerExtStart + 4, 0, round32(HeaderExtensionSize));
                memcpy(videoSendBuf + headerExtStart + 4, HeaderExtension, HeaderExtensionSize);
            }

            rtpDataStart +=  RTPHEADERSIZE                /* RTP Common Header */
                             + ((HeaderExtensionSize > 0) ?   /* Extension data if any   */
                                ((round32(HeaderExtensionSize)) + 4) : 0
                                /* Extension size + Header    */
                               );

            //payload头部，h264需要2字节，h265需要3个字节..
            if(nCodecType == 6)
            {
                nalType  = bufData[0] & 0x1f;
				nalType = *bufData;
                /* FU indicator                                                   */
                videoSendBuf[rtpDataStart] = (nalType & 0x60) | 28;
                /* FU header                                                      */
                videoSendBuf[rtpDataStart + 1] = (start << 7) | (end << 6) | (nalType & 0x1f);
				if(start)
				{
					bufData += 1;
	                bufSize -= 1;
            	}
                /* Send the data to the connected clients                     */
                if (RTPSendData(videoSendBuf, rtpDataStart + H264HEADERSIZE,
                                encodingName, rtspSession,
                                nCodecType, bufData + first, rtpPayload, VZero , FlagTCPClient, conn_node) == RET_ERROR)
                {
                    RtpRtspDebugPrint(DBG_LEVEL_5 , "Error in sending data over socket using Zero copy\n");
                    return RTP_RTSP_DATA_SEND_SOCK_ERROR;
                }
            }
            else if(nCodecType == 5)
            {
                nalType = (bufData[0] >> 1) & 0x3F;
                videoSendBuf[rtpDataStart] = 49 << 1;
                videoSendBuf[rtpDataStart+1] = 1;
                videoSendBuf[rtpDataStart+2] = nalType;
                if(start)
                {
                    videoSendBuf[rtpDataStart+2] |= 1 << 7;
                    bufData += 2;
                    bufSize -= 2;
                }
                else if(end)
                    videoSendBuf[rtpDataStart+2] |= 1 << 6;
                else
                    videoSendBuf[rtpDataStart+2] &= ~(1 << 7);
                /* Send the data to the connected clients                     */
                if (RTPSendData(videoSendBuf, rtpDataStart + H265HEADERSIZE,
                                encodingName, rtspSession,
                                nCodecType, bufData + first, rtpPayload, VZero , FlagTCPClient, conn_node) == RET_ERROR)
                {
                    RtpRtspDebugPrint(DBG_LEVEL_5 , "Error in sending data over socket using Zero copy\n");
                    return RTP_RTSP_DATA_SEND_SOCK_ERROR;
                }
            }

            if (HeaderExtensionSize != 0)
            {
                maxPayload +=
                    ((HeaderExtensionSize > 0) ?  /* Extension data if any */
                     ((round32(HeaderExtensionSize)) + 4) : 0
                     /* Extension size + Header*/
                    );
            }

            /* Header Extension Size is set to 0 so that only 1st packet contains
                header extension                                      */
            HeaderExtensionSize = 0;
            bufSize -= rtpPayload;
            first   += rtpPayload;
            start    = 0;
        }
    }

    return RTP_RTSP_OK;
}
/*cb change 2016.8.5 .添加h265的支持 end*/ 

/*******************************************************************************
 * Function:    SendG711DataToClient
 *
 * Description: This function packetize the buffer data as per G711 RTP packet
 *              and send it to the connected UDP clients
 *
 * Parameters :
 *      [IN]  INT32 SessionHandle   - RTSP session Handle
 *      [IN]  BYTE* bufData         - Data buffer pointer from which RTP packets
 *                                    will be generated
 *      [IN]  INT32 bufSize         - Data length
 *      [IN]  BYTE  *HeaderExtension- Header Extension data pointer,
 *                                      this extension will be added in
 *                                      only first packet
 *      [IN]  INT32 HeaderExtensionSize - Size of Header Extension Data
 *      [IN]  UINT16 HeaderExtensionType - Type of Header Extension
 *      [IN]  RTPSessionStream *rtspStream - rtsp Stream pointer
 *      [IN]  INT64 rtpTimeStamp    - NTP format rtptime stamp from application
 *      [IN]  INT32 SendFileFlag    - Sendfile API usage flag
 *      [IN]  INT32 DeviceFD        - Device FD for sendfile API
 *      [IN]  BYTE  *VZero          - VZero pointer for sendfile API
 *      [IN]  BYTE  encodingName    - codec specific name
 *      [IN]  INT32 FlagTCPClient   - Flag to indicate TCP client
 *      [IN]  void  *conn_node      - Client connection pointer
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_NO_CLIENT_CONNECTED    - No client connected
 *              RTP_RTSP_DATA_SEND_SOCK_ERROR   - Socket send failed
 *              RTP_RTSP_BAD_H264FRAME_DATA     - BAD H264 frame data
 *              RTP_RTSP_PAYLOAD_NOT_ADDED      - No Stream Added to session
 ******************************************************************************/
INT32 SendG711DataToClient(RTSPSession *rtspSession,    BYTE *bufData,
                           INT32 bufSize,              BYTE  *HeaderExtension,
                           INT32 HeaderExtensionSize,
                           UINT16 HeaderExtensionType, RTPSessionStream *rtspStream,
                           DWORD rtpTimeStamp,         INT32 SendFileFlag,
                           INT32 DeviceFD,             BYTE  *VZero,
                           BYTE *encodingName,         INT32 FlagTCPClient,
                           void *conn_node)
{
    BYTE            audioSendBuf[5 * UDP_MAX_PACKET_SIZE];   /* Send buffer array */
    INT32           maxPayload;         /* Max payload size                   */
    INT32           rtpPayload;         /* Payload size variable              */
    UINT32          headerExtStart = 0; /* Start Header Extension data        */
    UINT32          rtpDataStart = 0;   /* Start of RTP data                  */

    /*  If TCP client use Maximum MTU size 0x8000                             */
    if (FlagTCPClient)
    {
        /* Calculating maximum Payload size                                       */
        maxPayload   = (rtspSession->TcpMTUSize) - RTPHEADERSIZE
                       - ((HeaderExtensionSize > 0) ?  /* Extension data if any  */
                          ((round32(HeaderExtensionSize)) + 4) : 0  /* Extension size + Header  */
                         );
    }
    /*  If UDP client use Default MTU Size                                        */
    else
    {
        /* Calculating maximum Payload size                                       */
        maxPayload   = (rtspSession->UdpMTUSize) - RTPHEADERSIZE
                       - ((HeaderExtensionSize > 0) ?  /* Extension data if any  */
                          ((round32(HeaderExtensionSize)) + 4) : 0  /* Extension size + Header  */
                         );
    }

    /* do the packetization of the given buffer                               */
    while (bufSize > 0)
    {
        if (FlagTCPClient == 1)
        {
            rtpDataStart  = TCP_HEADER_SIZE;
        }
        else
        {
            rtpDataStart = 0;
        }

        rtpPayload   = maxPayload < bufSize ? maxPayload : bufSize;
        GenerateRTPCommonPacketHeader(audioSendBuf + rtpDataStart, rtpTimeStamp,
                                      (BYTE)((rtpPayload == bufSize) ? 1 : 0),
                                      rtspStream->PayloadNumber, ((HeaderExtensionSize > 0) ? 1 : 0));
        /* Copy Header Extension in audio send buffer                         */
        headerExtStart = 0;

        if (HeaderExtensionSize > 0)
        {
            headerExtStart = RTPHEADERSIZE + rtpDataStart;
            /* Header Extension type                                          */
            *(audioSendBuf + headerExtStart) = (HeaderExtensionType & 0xFF00) >> 8;
            *(audioSendBuf + headerExtStart + 1) = (HeaderExtensionType & 0xFF);
            /* Write Header Extension size in 32 bit words                    */
            *(audioSendBuf + headerExtStart + 2/* Two Profile Specific data */) =
                (((round32(HeaderExtensionSize)) / 4) & 0xff00) >> 8;
            *(audioSendBuf + headerExtStart + 3/* Two Profile Specific data */) =
                (((round32(HeaderExtensionSize)) / 4) & 0x00ff);
            /* Copy Header Extension Data                                     */
            memset(audioSendBuf + headerExtStart + 4, 0, HeaderExtensionSize);
            memcpy(audioSendBuf + headerExtStart + 4, HeaderExtension, HeaderExtensionSize);
        }

        rtpDataStart +=  RTPHEADERSIZE                /* RTP Common Header     */
                         + ((HeaderExtensionSize > 0) ?   /* Extension data if any */
                            ((round32(HeaderExtensionSize)) + 4) : 0
                            /* Extension size + Header    */
                           );

        /* Send the data to the connected clients using
           ZeroCopy mechanism                                             */
        if (RTPSendData(audioSendBuf, rtpDataStart,
                        encodingName, rtspSession,
                        DeviceFD, bufData, rtpPayload, VZero, FlagTCPClient, conn_node) == RET_ERROR)
        {
            RtpRtspDebugPrint(DBG_LEVEL_5 , "Error in sending data over socket using Zero copy\n");
            return RTP_RTSP_DATA_SEND_SOCK_ERROR;
        }

        /* Header Extension Size is set to 0 so that only 1st packet contains
                        header extension                                      */
        HeaderExtensionSize = 0;
        bufSize -= rtpPayload;
        bufData += rtpPayload;
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "\nEXIT : \n\tReturn Successfully\n");
    return RTP_RTSP_OK;
}

/******************************************************************************
 * Copyright (c) 2007 eInfochips - All rights reserved.
 *
 * This software is authored by eInfochips and is eInfochips' intellectual
 * property, including the copyrights in all countries in the world.
 * This software is provided under a license to use only with all other rights,
 * including ownership rights, being retained by eInfochips.
 *
 * This file may not be distributed, copied, or reproduced in any manner,
 * electronic or otherwise, without the written consent of eInfochips.
 *****************************************************************************/

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
 * File Name    :   RtcpServer.h
 *
 * Description  :   This file has definitions of variable, structure, function
 *                  required for RTCP server implementation.
 *
 * History:
 *      JUN/09/2009, NOS, Created the file.
 ******************************************************************************/



#ifndef _RTCP_H
#define _RTCP_H

/***********************
 * Include Files
 * ********************/
#include "RtpRtspInclude.h"
#include "./BasicTypes.h"
#include "RTCPTimeInterval.h"
#include "InternalCommon.h"
class CNetStatusEvaluate;

/************************
  DEFINES
 ************************/

/* RTCP Version                                                               */
#define RTCP_VERSION                2

/* Size of sender information section in SR packet                            */
#define SENDER_INFO_SIZE            20

/* Size of common part in any of the RTCP packet                              */
#define RTCP_HEADER_SIZE            4

/* Size of Report Block section in SR packet                                  */
#define REPORT_BLOCK_SIZE           24

/* Maximum RTCP packet size                                                   */
#define MAX_RTCP_PACKET_SIZE        1024

/* Maximum number of RTCP Packets that can be stored in link list             */
#define MAX_NO_RTCP_PACKETS         32

/* Maximum Number of RTCP Report Block                                        */
#define MAX_RTCP_REPORT_BLOCK       31

/************************
  ENUMS
 ************************/

/* Enum for RTCP packet types                                                 */
typedef enum _RTCPPacketType
{
    RTCP_CUSTOM = 100,  /* Custom Data Packet                                 */
    RTCP_SR     = 200,  /*Sender Report                                       */
    RTCP_RR     = 201,  /*Receiver Report                                     */
    RTCP_SDES   = 202,  /*Source Description                                  */
    RTCP_BYE    = 203,  /*Bye Packet                                          */
    RTCP_APP    = 204   /* Application Packet                                 */
} RTCPPacketType;

/*********************
 *    Structures
 *********************/
/* Structure used for the Report Block                                        */
typedef struct _RTCPReportBlock
{
    UINT32              ssrc;           /*SSRC of this source                 */
    UINT32              fraction : 8;   /*Fraction lost since last SR         */
    UINT32              lost     : 24;  /*Cumulative. no. of packet lost      */
    UINT32              lastSeq;        /*Extended last sequence number received*/
    UINT32              jitter;         /*Inter-arrival jitter                */
    UINT32              lsr;            /*Last SR packet from this source     */
    UINT32              dlsr;           /*Delay since last SR packet          */
} RTCPReportBlock;

/* Structure to keep track on statistics of a sender                          */
typedef struct _RTCPSendStats
{
    INT32   packetCount;        /* Packet sent count of RTP Session           */
    INT32   octetCount;         /* Data sent count of RTP Session             */
    UINT32  ntpSec;             /* Last SR packet NTP timestamp integer part  */
    UINT32  ntpFrac;            /* Last SR packet NTP timestamp fractional part*/
    FLOAT   arrivalTimeSR;      /*The time whenever a SR packet is received
                              The time is expressed in units of 1/65536 sec   */
} RTCPSendStats;


/* Structure for RTCP SR packet                                               */
typedef struct _RTCPCommonHeader
{
    UINT32  version: 2;         /* 2 bit field contains protocol version      */
    UINT32  p: 1;               /* 1 bit flag for padding flag                */
    UINT32  count: 5;           /* 5 bit field for report block count         */
    UINT32  pt: 8;              /* 8 bit field for RTCP packet type           */
    UINT32  length: 16;         /* Packet length in words-1                   */
} RTCPCommonHeader;

/* Structure for the RTCP Sender Report                                       */
typedef struct _RTCPSenderReport
{
    RTCPCommonHeader header;    /* Common header of any RTCP packet           */
    UINT32  ssrc;               /* Sender generating this report              */
    UINT32  ntpSec;             /* Integer part of NTP timestamp              */
    UINT32  ntpFrac;            /* Fractional part of NTP timestamp           */
    UINT32  rtpTs;              /* RTP timestamp                              */
    UINT32  packetSent;         /* The total number of RTP data packets
                                   transmitted by the sender since starting
                                   transmission up until the time this SR
                                   packet was generated                       */
    UINT32  octetSent;          /* The total number of payload octets
                                   (i.e., not including header or padding)
                                   transmitted in RTP data packets by the
                                   sender since starting transmission up until
                                   the time this SR packet was generated      */
    RTCPReportBlock *rb;        /* Pointer to the first element of the RB array
                                   to be padded with this SR packet           */
    BYTE   *paddingData;        /* Padding Data pointer                       */
    UINT32  padSize;            /* Padding size                               */
} RTCPSenderReport;

/* Structure for RTCP RR packet                                               */
typedef struct _RTCPReceiverReport
{
    RTCPCommonHeader header;    /* Common header of any RTCP packet           */
    UINT32  ssrc;               /* Receiver generating this report            */
    RTCPReportBlock *rb;        /* Pointer to the first element of the RB
                                   array to be padded with this RR packet     */
    BYTE   *paddingData;        /* Padding Data pointer                       */
    UINT32  padSize;            /* Padding size                               */
} RTCPReceiverReport;

/* Structure for RTCP BYE packet                                              */
typedef struct _RTCPByePacket
{
    RTCPCommonHeader header;    /* Common header of any RTCP packet           */
    UINT32  ssrc;               /* SSRC of this source                        */
    BYTE   *leavingReason;      /* String describing reason for leaving
                                    the session                               */
    BYTE   *paddingData;        /* Pointer to the data that is to be padded
                                    with this packet                          */
    UINT32  padSize;            /* Padding size                               */
} RTCPByePacket;

/* Structure for RTCP Custom packet                                           */
typedef struct _RTCPCustomPacket
{
    RTCPCommonHeader header;    /* Common header of any RTCP packet           */
    BYTE   *customData;         /* RTCP Custom Data pointer                   */
} RTCPCustomPacket;

/* Union for RTCP packets                                                     */
typedef union _RTCPPacketUnion
{
    RTCPSenderReport   *senderReport;   /* Pointer to sender report packet    */
    RTCPReceiverReport *receiverReport; /* Pointer to receiver report packet  */
    RTCPByePacket      *byePacket;      /* Pointer to bye packet              */
    RTCPCustomPacket   *customPacket;   /* Pointer to Custom Data packet      */
} RTCPPacketUnion;

/* Report block link list of last SR packet                                   */
typedef struct _RTCPReportBlockList
{
    RTCPReportBlock    *reportBlock;    /* Pointer to a Report Block          */
    struct _RTCPReportBlockList    *nextRB;/* Pointer to next element in
                                            this FIFO linklist                */
} RTCPReportBlockList;

/* Structure to represent the FIFO link list of received RTCP RR packet       */
typedef struct _RTCPPacketListStruct
{
    UINT8       packetType;     /* Type of the packet at the head of the list */
    UINT32      packetLength;   /* Length of packet (in bytes) at head of list*/
    UINT8       pktRead;        /* Flag to indicate any previous packet read  */
    RTCPPacketUnion     *RTCPPacket;/* Union for RTCP packet                  */
    RTCPReportBlockList *rbList;/* Pointer to the next element in the link list*/
    struct _RTCPPacketListStruct    *nextPacket;/* Pointer to next packet     */
} RTCPPacketListStruct;

/* ssrc link list                                    */
typedef struct _RTCPSSRCListStruct
{
    UINT32  ssrc;               /* ssrc                                      */
    struct _RTCPSSRCListStruct    *nextssrc;/* Pointer to next element in
                                           this FIFO linklist                */
} RTCPSSRCListStruct;

/* Structure to maintain all information regarding a RTCP session             */

typedef struct _RTCPSessionStruct
{
    INT32                   parentHandle;   /* Handle of parent struct        */
    UINT32                  packetListCount;/*No. of packets in link list     */
    UINT32                  ssrcListCount;/*No. of ssrc in link list     */
    RTCPReportBlock         lastRB;         /* Last Report Block Received or
                                                Generated                     */
    RTCPSendStats           *sendRTCPStat;  /* Sender side statistics         */
    RTCPPacketListStruct    *packetList;    /* Head of RTCP Packets           */
    RTCPSSRCListStruct      *ssrcList;      /* Pointer to the ssrc link list*/
    CRTCPTimeInterval       *prtcpTimeInterval;/* Pointer to the rtcp time inteval object*/
    CNetStatusEvaluate      *pNetStatusEvaluate;/* Pointer to the net status evaluate object*/
    SOCKET                  rtcpRecvSocket; /* Socket to receive RTCP Packet  */
    SOCKET                  rtcpSendSocket; /* Socket to Send RTCP Packet     */
    RTP_RTSP_TIMER_HANDLE   hTimer;         /* Timer object handler           */
    LOCK_HANDLE             rtcpLock;       /* Mutex lock object              */
    THREAD_HANDLE           packetRecvThread;/* Thread Handle per RTCP Session*/
    INT32                   StopRtcpSession; // ֹͣRTCP�Ự
} RTCPSessionStruct;

/************************
 * Function declarations
 ************************/
/* This thread will be created in the RTCPStart API.
   It receives RTCP packets and manages a FIFO link list
   of all these packets in the session structure passed to it.                */
void RTCPPacketRecvThread(void *handle);

/* The function adds a new packet in the link list                            */
INT32 AddNewPacket(RTCPSessionStruct *hStream,
                   BYTE *packetData,
                   UINT32 packetSize);

/* This is the timer handler registered by the
   RTCPSenderReportPeriodicSend API.                                          */
INT32 SRPeriodicSend(void *rtcpStreamHandle);

/* This is the timer handler registered by the
   RTCPReceiverReportPeriodicSend API                                         */
INT32 RRPeriodicSend(void *rtcpStreamHandle);

/* This function is used to send a RTCP packet.
   This will be used by the SR/BYE packet sends APIs.                         */
INT32 SendPacket(RTCPSessionStruct *hStream,
                 BYTE *packetData,
                 UINT32 packetSize);

/* This function will be called by the RTCPRecvPAcketThread
   to receive a RTCP packet                                                   */
INT32 RecvPacket(RTCPSessionStruct *hStream, void *packetData, UINT32 *packetSize);

/* This function calculates the NTP timestamp                                 */
void GetNtpTs(UINT32 *ntpSec, UINT32 *ntpFrac, UINT32  sec, UINT32  usec);


/* This is function updates receiver statistics for RTCP.
   Function will be called every time RTP data is received.                   */
INT32 UpdateRTCPReceiverStatistics(RTCPSessionStruct  *rtcpStreamHandle,
                                   UINT16              seqNo,
                                   UINT32              arrival,
                                   UINT32              rtpTs);
/* This is function updates sender's packet count and octet counts
   Function will be called every time RTSP server sends RTP data              */
void UpdateRTCPSenderStatistics(RTCPSessionStruct  *rtcpStreamHandle,
                                UINT32 payloadsize);

/* This function validates the rtcp session handle                            */
INT32 ValidateRTCPStreamHandle(RTCPSessionStruct *rtcpSessionHandle);

/* This function finds last received RB in RTSP Server Side                   */
INT32   FindReportBlockInRTSPServer(BYTE *packetData);

/* This function finds last received RB in RTSP Client Side                   */
INT32   FindReportBlockInRTSPClient(BYTE *packetData, UINT32 ssrc);

/* This function copies Report Blocks in Data buffer in network
   byte order.                                                                */
void  RTCPCopyReportBlocksInBuffer(BYTE *packetData, UINT32 rbCount,
                                   RTCPReportBlock *rb, UINT32 rbStart);

/* This function Retrieves Report Blocks from buffer.                         */
void  RTCPGetReportBlocksFromBuffer(BYTE *packetData, UINT32 rbCount,
                                    RTCPReportBlock *rb, UINT32 rbStart);

/* Send sender report                                          */
INT32 SRSend(void *rtcpStreamHandle, UINT32 *pPacketSize);

#endif /* _RTCP_H */

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

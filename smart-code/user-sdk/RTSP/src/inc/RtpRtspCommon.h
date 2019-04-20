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
 * File Name    :   RtpRtspCommon.h
 *
 * Description  :   This file contains common function, structure and data type
 *                  declaration common for RTP and RTSP module.
 *
 * History:
 *  JUN/02/2007, UBV,   Created the file
 *  JUN/25/2007, UBV,   Shift the definitions of codec enums to RtpRtsp.h file
 *  DEC/28/2007, ARJ,   RTP over TCP Feature Added
 *  JAN/28/2008, ARJ,   Updated the changes as per code review XLS.
 *
 ******************************************************************************/

#ifndef _INCLUDE_RTPRTSP_COMMON_H
#define _INCLUDE_RTPRTSP_COMMON_H

/*********************
 * Include Files
 *********************/
#include "RtpRtspInclude.h"
#include "./BasicTypes.h"
#include "RtpRtsp.h"
#include "RtcpServer.h"

/*********************
 * Defines and Macros
 *********************/
#define MAX_IP_LENGTH           16               /* Maximum Size of IP Address*/
#define MAX_HEADER_NUMBER       32               /* Maximum Number of Header  */
#define MAX_SMALL_BUFF_SIZE     128              /* Max small size buffer Size*/
#define MAX_BIG_BUFF_SIZE       1024             /* Max big size buffer       */
#define STRING_LEN_INT32        12               /* String Length of INT32    */
#define TCP_HEADER_SIZE         4                /* Interleaved Header Size   */

#define MAX_CALLBACK            2                /* Maximum Number of callbacks
                                                    for adding new session    */
#define MAX_RETRY               10              /* Retry counter for sending 
                                      data*/

/*********************
 * Typedefs and Enums
 *********************/
/* RTSP Session state enum                                                    */
typedef enum _RTSPState
{
    CLIENT_INIT_STATE,      /* INIT state of session                          */
    CLIENT_DESCRIBE_STATE,  /* Response of DESCRIBE is sent and waiting for SETUP */
    CLIENT_READY_STATE,     /* Response of SETUP is sent and waiting for PLAY */
    CLIENT_PLAYING_STATE,   /* Response of PLAY is send and streaming data    */
    CLIENT_PAUSE_STATE,     /* PAUSE state                                    */
    CLIENT_INVALID_STATE,   /* INVALID State                                  */
    CLIENT_PORTCHANGE_STATE /* Client receiving port is changed for http
                               request messages                               */

} RTSPState;

/* RTSP Method enum                                                           */
typedef enum _RTSPMsgMethod
{
    HTTP_METHOD_GET,                         /* Method - GET                  */
    HTTP_METHOD_POST,                        /* Method - POST                 */
    RTSP_METHOD_OPTIONS,                     /* Method - OPTIONS              */
    RTSP_METHOD_DESCRIBE,                    /* Method - DESCRIBE             */
    RTSP_METHOD_SETUP,                       /* Method - SETUP                */
    RTSP_METHOD_PLAY,                        /* Method - PLAY                 */
    RTSP_METHOD_TEARDOWN,                    /* Method - TEARDOWN             */
    RTSP_METHOD_PAUSE,                       /* Method - PAUSE                */
    RTSP_METHOD_ANNOUNCE,                    /* Method - ANNOUNCE             */
    RTSP_METHOD_GET_PARAMETER,               /* Method - GET_PARAMETER        */
    RTSP_METHOD_SET_PARAMETER,               /* Method - SET_PARAMETER        */
    RTSP_METHOD_REDIRECT,                    /* Method - REDIRECT             */
    RTSP_METHOD_RECORD,                      /* Method - RECORD               */
    RTSP_METHOD_INVALID                      /* Method - INVALID              */

} RTSPMsgMethod;

/* Timer callback function pointer type                                       */
typedef INT32(*TIMER_CALLBACK)(void *);

/* Enum for Transport Protocol                                                */
enum _RTSPTransportProto
{
    UDP = 0,                                /* UDP Transport Protocol         */
    TCP                                     /* TCP Transport Protocol         */
};

/* Creates a typedefinition of Transport Protocol                             */
typedef enum _RTSPTransportProto RTSPTransportProto;

/*********************
 *    Structures
 *********************/
/* Structure for RTSP Headers                                                 */
typedef struct _RTSPHeaderStruct
{
    BYTE                 *HeaderName;         /* Name of RTSP Header          */
    BYTE                 *HeaderValue;        /* Value of RTSP Header         */

} RTSPHeaderStruct;

/* Structure for RTSP Response Message                                        */
typedef struct _RTSPResponseMsg
{
    INT32                ResStatusCode;          /* Status code of response   */
    INT32                ResSeqNumber;           /* RTSP Sequence Number      */
    INT32                ResHeadersCount;        /* RTSP Response Header count*/
    BYTE                 *ResReasonPhrase;       /* Pointer to reason string  */
    BYTE                 *ResRtspVersion;        /* RTSP message version      */
    RTSPHeaderStruct     ResMsgHeaders[MAX_HEADER_NUMBER];/* RTSP Resp headers*/

} RTSPResponseMsg;

/* Structure for RTSP Request Message                                         */
typedef struct _RTSPRequestMsg
{
    INT32                ReqSeqNumber;           /* RTSP Sequence Number      */
    INT32                ReqHeadersCount;        /* RTSP Request Header count */
    BYTE                 *ReqMsgURI;             /* RTSP mesaage URI          */
    BYTE                 *ReqRtspVersion;        /* RTSP message version      */
    RTSPMsgMethod        ReqMethod;              /* RTSP message method type  */
    RTSPHeaderStruct     ReqMsgHeaders[MAX_HEADER_NUMBER];/* RTSP Req headers */

} RTSPRequestMsg;

typedef struct _RTSPSession         RTSPSession;
typedef struct _RTSPServer          RTSPServer;
typedef struct _RTSPClient          RTSPClient;
typedef struct _RTPSessionStream    RTPSessionStream;
typedef struct _RTPClientStream     RTPClientStream;
typedef struct _TimerStruct TimerStruct;
typedef struct _RTSPBuff RTSPBuff;
typedef struct _RTCPUserByePacket RTCPUserByePacket;
typedef struct _RTCPUserSenderReport RTCPUserSenderReport;
typedef struct _RTCPUserReceiverReport RTCPUserReceiverReport;

/* Structure for Stream of RTSP Connection                                    */
struct _RTPClientStream
{
    BYTE                 StreamIdentifier[MAX_IP_LENGTH];/* Codec Encoding Name*/
    INT32                ClientPort;             /* Port of Client,
                                                    in case of RTP over TCP
                                                    this will contains
                                                    interleaved value         */
    INT32                ServerPort;             /* Port of Server,
                                                    in case of RTP over TCP
                                                    this will contains
                                                    interleaved value         */
    INT32                StreamSeqNo;            /* Stream sequence No        */
    DWORD               StreamSSRC;             /* Stream SSRC Value         */
    SOCKET               RTPConnSocket;          /* RTP Socket                */
    INT32                streamNumber;           /* Stream number             */
    INT32                StreamHandle;           /* Stream Handle for itself  */
    INT32                sessionStream;          /* Stream Handle from
                                                    Session-list              */
    RTCPSessionStruct    *rtcpSessionInfo;       /* Pointer to RTCP structure */
    RTSPClient           *rtspConnectedClientPtr;/* Pointer to parent struct  */

    struct _RTPClientStream  *Next;              /* Pointer to Next Stream    */
    struct _RTPClientStream  *Prev;              /* Pointer to Previous Stream*/
};

/* Structure for RTSP Connection                                              */
struct _RTSPClient
{
    BYTE                 ClientIp[MAX_IP_LENGTH]; /* IP address of Client     */
    INT32                ClientPort;                       /* Port of connected client */
    // 服务器的IP 地址
    BYTE                 LocalIp[MAX_IP_LENGTH];           /* IP address of local system */
    INT32                LocalPort;                        /* listening port of local system */
    BYTE                 ClientInterleavedFlag;   /* Flag for RTP over TCP    */
    INT32                ClientSessionId;         /* Session ID               */
    INT32                ClientLastMsgSeqNo;      /* Last Message Seq Number  */
    INT32                FileStartTime;           /* Start time of file in second  */
    // 当前客户端连接SOCKET
    SOCKET               ClientSocket;            /* RTSP Socket              */

    RTSPState            ClientState;             /* State of Client          */
    THREAD_HANDLE        ClientThreadID;          /* Thread ID                */
    RTSPRequestMsg       *ClientRtspReqMsg;       /* RTSP message struct ptr  */
    RTSPResponseMsg      *ClientRtspResMsg;       /* RTSP response mgs prt    */
    RTSPTransportProto   rtpTransportProtocol;    /*Transport Protocol for RTP*/
    DWORD                lastPktRecvTimeStamp;    /* Last alive packet received time */
    RTPClientStream      *ClientStreamList;       /* List of Stream requested */
    RTSPSession          *RtspSessionPtr;         /* RTSP Session pointer     */
    // RTSP 总服务数据结构访问指针
    RTSPServer              *RtspServerPtr;
    struct _RTSPClient   *NextClient;             /* Pointer to Next Client   */
    struct _RTSPClient   *PrevClient;             /* Pointer to Previous Client*/
    INT32                IsFirstFrame;            // 是否是发送的第一帧
    LOCK_HANDLE          RTSPClientSendmsgLock;  //\\保证信令处理成功，在收到RTSP请求时，暂停发送数据，优先回应信令RTSP包.

};

/* Structure for RTSP Stream                                                  */
struct _RTPSessionStream
{
    BYTE                CodecType;              /* 0=Audio, 1= Video          */
    BYTE                EncodingName[MAX_IP_LENGTH];/* Codec Encoding Name    */
    BYTE                *FormatDataPointer;     /* Pointer to SDP related data*/
    INT32               PayloadNumber;          /* Payload Number of Codec    */
    INT32               ClockRate;              /* Clock Rate                 */
    INT32               NoOfChannels;           /* Number of Channels
                                                    (only in Audio)           */
    INT32               FormatDataSize;         /* Size of Format Data        */
    UINT16              MulticastPort;          /* Multicast Port             */
    SupportedCodecs     StreamCodec;            /* Name of Codec              */
    DWORD              rtpTimeStamp;           /* Time StampValue            */
    INT32               InterleavedVal;         /* Value of the Interleaved   */
    struct _RTPSessionStream  *Next;            /* Pointer to Next Stream     */
    struct _RTPSessionStream  *Prev;            /* Pointer to Previous Stream */
};

/* Structure for RTSP Session                                                 */
struct _RTSPSession
{
    BYTE                 SessionName[MAX_SMALL_BUFF_SIZE];/* Session Name     */
    BYTE                 SessionMulticastIP[MAX_IP_LENGTH];/* Multicast Ip Address*/
    BYTE                 SessionMulticastFlag;    /* Flag for Multicast       */
    BYTE                 *SessionGeneratedSDP;   /* Pointer to SDP buffer     */
    BYTE                 RtcpDataReceive;        /* Flag to denote to receive
                                            reamining rtcp data for Http next time */
    INT32                SessionConnectedClientCount;/* Connected client count*/
    INT32                StreamCount;            /* Stream Count              */
    INT32                TCPClientCount;         /* Counter for Connected TCP Clients*/
    INT32                UDPClientCount;         /* Counter for Connected UDP Clients*/
    INT32                SessionSingleMode;      /* Single mode flag         */
    INT32                TcpMTUSize;             /* MTU Size for TCP         */
    INT32                UdpMTUSize;             /* MTU Size for UDP         */
    INT32                FileEndTime;            /* End time of file in second    */
    RTSPClient           *SessionConnectedClientList;/* Connected Clients List*/
    LOCK_HANDLE          SessionClientListLock;  /* Lock For Client List      */
    LOCK_HANDLE          streamListLock;         /* Stream List Lock          */
    RTPSessionStream     *SessionStreamList;     /* List of Streams           */
    RTSPServer           *RtspServerPtr;         /* RTSP server pointer       */
    INT32                RtcpFlag;               /* RTCP session flag         */
    INT32                RtcpSRInterval;         /* Interval between SRs      */
    CLIENT_CONNECTION_CALLBACK ClientConnectionCallback; /* callback for client
                                                            connection */
    FS_EVENT_CALLBACK    RTPWriter_Callback;     /* filestreamer callback     */
    struct _RTSPSession  *NextSession;           /* Next RTSP Session         */
    struct _RTSPSession  *PrevSession;           /* Previous RTSP Session     */

};

/* Structure for RTSP Server                                                  */
struct _RTSPServer
{
    BYTE                 ServerIp[MAX_IP_LENGTH];/* IP address of Server      */
    INT32                ServerRtspPort;         /* RTSP Connection Port
                                                                  of Server       */
    SOCKET               ServerSocket;                      // 侦听SOCKET

    LOCK_HANDLE          ServerRtspSessionLock;  /* Lock For RTSPSession      */
    THREAD_HANDLE        ServerThreadID;         /* Thread ID of Server       */
    THREAD_HANDLE        SrvHttpThreadID;        /* Thread ID of Server       */
    RTSPSession          *RtspSessionList;       /* RTSP Sessions list        */
    FS_EVENT_CALLBACK    AddSession_Callback;  /* filestreamer
                               callback for searching and adding  new session */
};

/* Structure for Timer                                                        */
struct _TimerStruct
{
    UINT8               randomFlag;          /*Random duration flag       */
    UINT32              timerPeriod;         /*Timer duration value       */
    INT32               hTimerQueue;         /*Handle of timer queue      */
    RTP_RTSP_TIMERID    hTimer;              /*Handle of timer            */
    TIMER_CALLBACK      callbackFunc;        /*Callback function pointer  */
    INT32               callbackArg;         /*Callback function argument */
};

/* RTSP Buff Structure                                                        */
struct _RTSPBuff
{
    INT32                DataBuffLen;       /* Data buffer length         */
    BYTE                 *DataBuff;         /* Pointer of Data buffer     */
};

/* Structure for User BYE RTCP Packet                                         */
struct _RTCPUserByePacket
{
    RTCPCommonHeader header;                /* Common header of any RTCP packet*/
    UINT32  ssrc;                           /* SSRC of this source            */
    BYTE   *leavingReason;                  /*Leaving Reason phrase           */
};

/* Structure for User SR RTCP Packet                                          */
struct _RTCPUserSenderReport
{
    RTCPCommonHeader header;    /*Common header of any RTCP packet            */
    UINT32  ssrc;               /* Sender generating this report              */
    UINT32  ntpSec;             /*Integer part of NTP timestamp               */
    UINT32  ntpFrac;            /*Fractional part of NTP timestamp            */
    UINT32  rtpTs;              /*RTP timestamp                               */
    UINT32  packetSent;         /*The total number of RTP data packets
                                transmitted by the sender since starting
                                transmission up until the time this SR
                                packet was generated                          */
    UINT32  octetSent;          /* The total number of payload octets
                               (i.e., not including header or padding)
                               transmitted in RTP data packets by the sender
                               since starting transmission up until the time
                               this SR packet was generated                   */
};

/* Structure for User RR RTCP packet                                          */
struct _RTCPUserReceiverReport
{
    RTCPCommonHeader header;        /* Common header of any RTCP packet       */
    UINT32  ssrc;                   /* Receiver generating this report        */
};

/************************
 * Function declarations
 ************************/

/* Function to create RTSP Server thread                                      */
INT32 ThreadCreate(THREAD_HANDLE *threadHandle, THREAD_FUNC threadFunction,
                   void *threadArg);

/* Function to exit the thread                                                */
INT32 ThreadExit(THREAD_HANDLE threadHandle);

/* Function to detach the thread                                              */
INT32 ThreadDetach(THREAD_HANDLE ThreadHandle);

/* Function to wait for thread completion                                     */
INT32 WaitForThreadCompletion(THREAD_HANDLE threadHandle);

/* Function to ignore SIGPIPE in case of socket error                         */
void HandleSignal(void);

/* Close server socket                                                        */
void CloseServerSock(SOCKET serverSock);

/* Initializes the mutex                                                      */
INT32 MutexInit(LOCK_HANDLE *criticalSection);

/* Locks the Critical Section                                                 */
INT32 MutexLock(LOCK_HANDLE *criticalSection);

/* Unlocks the Critical Section                                               */
INT32 MutexUnlock(LOCK_HANDLE *criticalSection);

/* Destroys the Mutex                                                         */
INT32 MutexDestroy(LOCK_HANDLE *criticalSection);

/* This function get the current system time value                            */
DWORD GetTimeValue();

/* This Function gets current time in seconds and micro seconds.              */
INT32 GetPresentTimeInSec(UINT32 *Sec, UINT32 *Microsec);

/* This function return the current system NTP Time                           */
DWORD GetNtpTime();

/* This function is used for giving delay                                     */
void MSecDelay(INT32  delayTime);

/* This function extracts the name of session                                 */
BYTE *ParseURI(BYTE *ReqMsgURI, INT32 Level, INT8 *DestStr);

/* This function is used to stop the timer                                    */
INT32 RtpRtspStopTimer(RTP_RTSP_TIMER_HANDLE timerHandle);

#ifdef WIN32
/* This function is callback function on expiration of timer                  */
void CALLBACK WinTimerCallback(PVOID lpParam, BOOL TimerOrWaitFired);
#endif

/* This function is used to receive data on UDP socket                        */
INT32 RtpRtspUDPSockRecv(SOCKET sockHandle, BYTE  *dataBuff,    INT32 dataSize,
                         SOCKETADDR_IN *sockAddr,   INT32 *sockAddrSize);


#endif  /* _INCLUDE_RTPRTSP_COMMON_H */

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

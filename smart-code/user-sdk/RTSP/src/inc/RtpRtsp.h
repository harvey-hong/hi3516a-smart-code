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
 * File Name    :   RtpRtsp.h
 *
 * Description  :   This file contains API list which is exported to application
 *
 * History:
 *  JUN/02/2007, UBV,   Created the file
 *  JUN/25/2007, UBV,   Added Error code constants and definitions of codec enums
 *  JAN/16/2008, ARJ,   Added Few Defines
 *  JAN/28/2008, ARJ,   Updated the changes as per code review XLS.
 *
 ******************************************************************************/

#ifndef _INCLUDE_RTPRTSP_H
#define _INCLUDE_RTPRTSP_H

/*********************
 * Include Files
 *********************/
#include "RtpRtspInclude.h"
#include "RtcpServer.h"
#include "./BasicTypes.h"
#include "./HYRtspCommon.h"

/*********************
 * Defines and Macros
 *********************/

/* Error codes return by RTP/RTSP APIs                                        */
#define RTP_RTSP_OK             (0)         /* Status ok                      */
#define RTP_RTSP_ERROR          (-1)        /* Status error                   */

#define FS_START_CLIENT         (1<<0)      /* New client connected           */
#define FS_DESTROY_CLIENT       (1<<1)      /* Client destroy                 */
#define FS_PLAY                 (1<<2)      /* Client is in playing state     */
#define FS_PAUSE                (1<<3)      /* Client is in pause state       */
#define FS_STOP                 (1<<4)      /* Client is now stopped          */
#define FS_ADD_SESS             (1<<5)      /* Client has requested to add new
                                                                      session */
#define FS_REMOVE_SESS          (1<<6)      /* Client has requested to remove session */

#define FS_BITRATE_CONTROL      (1<<7)      // 码率控制

#define FS_REMOVE_SESS_STOP          (1<<8)      /* Server requested to remove session */


/*********************
 * Typedefs and Enums
 *********************/

typedef enum _ErrorCodes
{
    RTP_RTSP_INVALID_INPUT_VALUE = -99,     /* Invalid input argument         */
    RTP_RTSP_MEMORY_ALLOCATION_FAIL,        /* Memory allocate failed         */
    RTP_RTSP_SOCKET_CREATION_FAIL,          /* Socket creation failed         */
    RTP_RTSP_SOCKET_BIND_FAIL,              /* Socket bind failed             */
    RTP_RTSP_SOCKET_LISTEN_FAIL,            /* Listening on Socket Failed     */
    RTP_RTSP_SERVER_THREAD_CREATION_FAIL,   /* RTSP server thread start failed */
    RTP_RTSP_WAIT_FOR_THREAD_FAILED,        /* Wait for Thread completion failed*/
    RTP_RTSP_NO_CLIENT_CONNECTED,           /* NO Client connected            */
    RTP_RTSP_BAD_H264FRAME_DATA,            /* BAD H264 Frame                 */
    RTP_RTSP_DATA_SEND_SOCK_ERROR,          /* Socket send error              */
    RTP_RTSP_DATA_RECV_SOCK_ERROR,          /* Socket recv error              */
    RTP_RTSP_PAYLOAD_NOT_ADDED,             /* No Stream added to session     */
    RTP_RTSP_LOCK_INITIALIZATION_FAIL,      /* Lock Initialization failed     */
    RTP_RTSP_LOCK_FAIL,                     /* Locking Failed                 */
    RTP_RTSP_UNLOCK_FAIL,                   /* Unlocking Failed               */
    RTP_RTSP_LOCK_DESTROY_FAIL,             /* Destroying Lock Failed         */
    RTP_RTSP_HTTP_SERVER_START_FAILED,      /* RTSP over HTTP server start failed*/
    RTP_RTSP_TIMER_NOT_INITIALIZED,         /* Timer Initialization Failed    */
    RTP_RTSP_SEND_PACKET_FAIL,              /* Packet Sending Failed          */
    RTP_RTSP_PACKET_NOT_AVAILABLE,          /* Packet Not availabled          */
    RTP_RTSP_RB_NOT_AVAILABLE,              /* Receive Block not available    */
    RTP_RTSP_RTCP_PACKET_LIMIT_EXCEEDED,    /*RTCP Recv Packet Link Max. limit exceeded*/
    RTP_RTSP_INVALID_STREAM_NUMBER,         /* Invalid Stream No              */
    RTP_RTSP_SMALL_BUFF_FROM_APPLICATION,   /*Small Buffer received from Application*/

} ErrorCodes;

/* Thread Function Pointer                                                    */
#ifdef LINUX
typedef void *(*THREAD_FUNC)(void *);
#endif

#ifdef WIN32
typedef INT32(WINAPI *THREAD_FUNC)(void *);
#endif

typedef INT32(*CLIENT_CONNECTION_CALLBACK)(INT32, BYTE *);
// 返回回调处理结果
typedef INT32(*FS_EVENT_CALLBACK)(INT32, INT32, INT32, void *);

/* Video Codec enums                                                          */
typedef enum _SupportedCodecs
{
    CODEC_H264 = 100,                            /* Video Codec H264          */
	CODEC_H265 = 101,                            /* Video Codec H265          *//*cb change 2016.8.5 .添加h265的支持*/ 
    CODEC_MPEG4V,                                /* Video Codec Mpeg4 Video   */
    CODEC_MJPEG,                                 /* Video Codec MJPEG         */
    CODEC_G711A = 200,                           /* Audio Codec G711 ALAW     */
    CODEC_G711U,                                 /* Audio Codec G711 ULAW     */
    CODEC_AAC,                                   /* Audio Codec AAC           */
    CODEC_G726,                                  /* Audio Codec G726          */
    CODEC_L16,                                   /* Audio Codec PCM           */
    CODEC_MPA,                                   /* Audio Codec MPEG          */
    CODEC_MP2T = 300,                            /* MPEG2-TS Codec            */
    INVALID_CODEC                                /* Invalid Audio Codec       */
} SupportedCodecs;

/************************
 * Function declarations
 ************************/

/* API to Start RTSP Server, Returns Handle to Server on Success and -1 on
   failure                                                                    */

RTP_RTSPLIB_API INT32 CreateRTSPServerListenPort(int NewPort);

RTP_RTSPLIB_API INT32 RTSPServerStart(BYTE *ServerIP, INT32 ServerPort,
                                      FS_EVENT_CALLBACK FS_Callback,
                                      INT32 *ErrorCode);

/* API to create a particular Session, Returns Handle of Session and -1 on
      failure                                                                 */
RTP_RTSPLIB_API INT32 RTSPSessionCreate(INT32  ServerHandle, BYTE *SessionName,
                                        BYTE  *MulticastIP,
                                        INT32  SingleModeFlag, INT32  UdpMTUSize,
                                        INT32  TcpMTUSize, INT32 RtcpFlag, INT32 RtcpSRInterval,
                                        INT32 *ErrorCode, CLIENT_CONNECTION_CALLBACK ConnCallback,
                                        FS_EVENT_CALLBACK FS_Callback,
                                        INT32 FileEndTime);

/* API to send the G711 ALaw data to the given session                        */
RTP_RTSPLIB_API INT32 RTPSendG711AData(INT32 SessionHandle, BYTE *BufferData,
                                       INT32 BufferLength,   BYTE *HeaderExtension,
                                       INT32 HeaderExtensionSize,
                                       UINT16 HeaderExtensionType,
                                       DWORD NTPTimeStamp,   INT32 SendFileFlag,
                                       INT32 DeviceFD,       BYTE  *VZero, void *conn_node);

/* API to send the G711 ULaw data to the given session                        */
RTP_RTSPLIB_API INT32 RTPSendG711UData(INT32 SessionHandle, BYTE *BufferData,
                                       INT32 BufferLength,   BYTE *HeaderExtension,
                                       INT32 HeaderExtensionSize,
                                       UINT16 HeaderExtensionType,
                                       DWORD NTPTimeStamp,   INT32 SendFileFlag,
                                       INT32 DeviceFD,       BYTE  *VZero, void *conn_node);


/* API to send the G726 data to the given session                         */
RTP_RTSPLIB_API INT32 RTPSendG726Data(INT32 SessionHandle,  BYTE  *BufferData,
                                      INT32 BufferLength,   BYTE  *HeaderExtension,
                                      INT32 HeaderExtensionSize,
                                      UINT16 HeaderExtensionType,
                                      DWORD NTPTimeStamp,   INT32 SendFileFlag,
                                      INT32 DeviceFD,       BYTE  *VZero, void *conn_node);

/* API to send the H264 data to the given session  */
/*cb change 2016.8.5 .添加h265的支持*/ 
RTP_RTSPLIB_API INT32 RTPSendH264Data(INT32 SessionHandle,  BYTE  *BufferData,
                                      INT32 BufferLength,   BYTE  *HeaderExtension,
                                      INT32 HeaderExtensionSize,
                                      UINT16 HeaderExtensionType,
                                      DWORD NTPTimeStamp, INT32 sendFileFlag,
                                      INT32 nCodecType, BYTE *VZero, void *conn_node,
                                      INT32 endOfFrameFlag);

/* API to shutdown the given RTSP server                                      */
RTP_RTSPLIB_API INT32 RTSPServerShutdown(INT32 ServerHandle);

/* API to shutdown the given RTSP session                                     */
RTP_RTSPLIB_API INT32 RTSPSessionDestroy(INT32 SessionHandle);

/* API to add stream in given RTSP session                                    */
RTP_RTSPLIB_API INT32 RTSPAddStreamToSession(INT32 SessionHandle,    SupportedCodecs StreamCodec,
        INT32 CodecType,        INT32 ClockRate,
        INT32 NumberOfChannels, INT32 FormatDataSize,
        BYTE *FormatDataPointer, UINT16 MulticastPort);

/* API to Start the RTCP  Session                                             */
RTP_RTSPLIB_API INT32 RTCPStart(INT32 cliHandle, INT32 cliStreamHandle);

/* API to Stop the RTCP Session                                               */
RTP_RTSPLIB_API INT32 RTCPStop(INT32 streamHandle);

/* API to send BYE RTCP Packet                                                */
RTP_RTSPLIB_API INT32 RTCPSendByePacket(INT32   streamHandle,  BYTE     *leavingReason);

/* API to retrieve RTCP Packet from the Stack Buffer                          */
RTP_RTSPLIB_API INT32 RTCPPacketRecv(INT32      streamHandle,  BYTE     *rtcpPacket,
                                     UINT32     *packetSize,   UINT8    *packetType);

/* API to Get Report Block from the first available received packet           */
RTP_RTSPLIB_API INT32 RTCPGetNextReportBlock(INT32 streamHandle, RTCPReportBlock   *reportBlock);

/* API to generate SR packet and send it to receivers                         */
RTP_RTSPLIB_API INT32 RTCPSendSenderReport(INT32  streamHandle, UINT8  rbCount,
        RTCPReportBlock *reportBlock);

/* API to generate SR packet and send it periodically                         */
RTP_RTSPLIB_API INT32 RTCPSendSenderReportPeriodic(INT32  streamHandle, UINT32 period,
        UINT8  random);

#endif  /* _INCLUDE_RTPRTSP_H */

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

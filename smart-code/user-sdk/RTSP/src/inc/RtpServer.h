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
 * File Name    :   RtpServer.h
 *
 * Description  :   This file has definitions of variable, structure, function
 *                  required for RTP server implementation.
 *
 * History:
 *  JUN/21/2007, UBV,   Created the file
 *  DEC/27/2007, ARJ,   Modified GenerateRTPCommonPacketHeader function
 *
 ******************************************************************************/
#ifndef _INCLUDE_RTP_SERVER_H
#define _INCLUDE_RTP_SERVER_H

/*********************
 * Include Files
 *********************/
#include "RtpRtspInclude.h"
#include "BasicTypes.h"
#include "RtpRtspCommon.h"
#include "RtpRtsp.h"

/*********************
 * Defines and Macros
 *********************/

#define RTPHEADERSIZE           12           /* RTP header size               */
#define H264HEADERSIZE          2            /* H264 header size              */
#define H265HEADERSIZE          3            /* H265 header size              *//*cb change 2016.8.5 .添加h265的支持*/
#define UDP_MAX_PACKET_SIZE     1450         /* Maximum Packet size           */
#define TCP_MAX_PACKET_SIZE     1452         /* Maximum Packet size for TCP   */
#define MJPEG_HEADER_SIZE       8            /* MJPEG Header Size in Bytes    */
#define EXTENSION_HEADER_SIZE   4            /* 4 bytes of Extension Header for
                                               Header Extension               */

/************************
 * Function declarations
 ************************/

/* Thread which Accepts the Connection from Client                            */
INT32 RTSPServerThreadFunc(RTSPServer *rtspServer);

/*cb change 2016.8.5 .添加h265的支持*/ 
/* It Sends data to connected clients which are in playing state              */
INT32 RTPSendData(BYTE *SendBuf, INT32 SendSize, BYTE *EncodingName,
                  RTSPSession *RtspSession, INT32 nCodecType,
                  BYTE *DataBuf, INT32 DataSize, BYTE *VZero,
                  INT32 FlagTCPClient, void *conn_node);

/* This function generates the common RTP header                              */
void GenerateRTPCommonPacketHeader(BYTE *PBuffer,      DWORD TimeStamp,
                                   BYTE FrameEnd,      INT32 Format,
                                   INT32 ExtensionBit);

/*cb change 2016.8.5 .添加h265的支持*/ 
INT32 SendH264DataToClient(RTSPSession *rtspSession,   BYTE  *bufData,
                           INT32 bufSize,              BYTE  *HeaderExtension,
                           INT32 HeaderExtensionSize,
                           UINT16 HeaderExtensionType, RTPSessionStream *rtspStream,
                           DWORD rtpTimeStamp,         INT32 SendFileFlag,
                           INT32 nCodecType,             BYTE  *VZero,
                           BYTE *encodingName,         INT32 FlagTCPClient,
                           void *conn_node,            INT32 endOfFrameFlag);

INT32 SendG711DataToClient(RTSPSession *rtspSession,   BYTE  *bufData,
                           INT32 bufSize,              BYTE  *HeaderExtension,
                           INT32 HeaderExtensionSize,
                           UINT16 HeaderExtensionType, RTPSessionStream *rtspStream,
                           DWORD rtpTimeStamp,         INT32 SendFileFlag,
                           INT32 DeviceFD,             BYTE  *VZero,
                           BYTE *encodingName,         INT32 FlagTCPClient,
                           void *conn_node);

#endif  /* _INCLUDE_RTP_SERVER_H */

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


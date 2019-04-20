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
 * File Name    :   RtspServer.h
 *
 * Description  :   This file has definitions of variable, structure, function
 *                  required for RTSP server implementation.
 *
 * History:
 *  JUN/21/2007, UBV,   Created the file
 *  DEC/27/2007, ARJ,   Added MJPEG Codec support
 *  DEC/28/2007, ARJ,   RTP over TCP Feature Added
 *  JAN/28/2008, ARJ,   Updated the changes as per code review XLS.
 *
 ******************************************************************************/
#ifndef _INCLUDE_RTSP_SERVER_H
#define _INCLUDE_RTSP_SERVER_H

/*********************
 * Include Files
 ********************/
#include "RtpRtspInclude.h"
#include "BasicTypes.h"
#include "RtpRtspCommon.h"
#include "RtpRtsp.h"

/*********************
 * Defines and Macros
 *********************/
#define MAX_LISTEN_CLIENT       10               /* Maximum listen clients    */
#define MAX_DATA_SIZE           1024             /* Maximum Data Size         */
#define DEFAULT_RTSP_VERSION    "RTSP/1.0"       /* Default Version of RTSP   */
#define DEFAULT_HTTP_VERSION    "HTTP/1.0"       /* Default Version of HTTP  */
#define SOCKET_TYPE             SOCK_STREAM      /* Socket Type               */
#define RTSP_SERVER_NAME        "RtpRtspFlyer"   /* Name of RTSP Server       */
#define RTP_JPEG_RESTART        0x40             /* JPEG file with Restart
                                                                        Marker*/
#define  SOF0                   0xFFC0           /* baseline DCT process
                                                                frame marker  */
#define  SOF1                   0xFFC1           /* extended sequential DCT
                                                            frame marker,
                                                            Huffman coding    */
#define  DQT                    0xFFDB           /* Define quantization table */
#define  DHT                    0xFFC4           /* Define Huffman table      */
#define  DAC                    0xFFCC           /* Define arithmetic
                                                        coding conditioning   */
#define  DRI                    0xFFDD           /* Define restart interval   */
#define  SOS                    0xFFDA           /* Start of scan             */
#define  EOI                    0xFFD9           /* End of image              */
#define  MJPEG_HEADER_SIZE      8                /* MJPEG Header Size in Bytes*/

/* List of Implemented Methods                                                */
#define RTSP_IMPLEMENTED_METHOD "DESCRIBE, SETUP, PLAY, PAUSE, TEARDOWN"

/* Macro to roundup the argument x to multiple of
            32 (rounded value is > x)                                         */
#define round32(x) ((x % 4) ? ((x+4)/4)*4 : x)

/*********************
 *    Structures
 *********************/
/* Structure for Common Buffer                                                */

/* Structure for Status and Reason Phrase of Response                         */
typedef struct _RTSPStatusReason
{
    INT32                StatusCode;             /* Status Code of Response   */
    INT8                 *ReasonPhrase;          /* Reason of Status Code     */

} RTSPStatusReason;

/* Structure for MJPEG Header                                                 */
typedef struct _JpegHdr
{
    UINT8                Type;                  /* id of jpeg decoder params  */
    UINT8                Qt;                    /* quantization factor        */
    UINT16               Width;                 /* frame width in 8 pixel
                                                                blocks        */
    UINT16               Height;                /* frame height in 8 pixel
                                                                blocks        */
    UINT32               Tspec;                 /* type-specific field        */
    UINT32               Off;                   /* fragment byte offset       */

} JpegHdr;

/*  This structure contains information about JPEG header quantization table  */
typedef struct _JpegHdrQtable
{
    UINT8                   Mbz;            /* MBZ                            */
    UINT8                   Precision;      /* Table Precision                */
    UINT16                  Length;         /* Length of Table Value Array    */

} JpegHdrQtable;

/************************
 * Function declarations
 ************************/

/* Thread which Accepts the Connection from Client                            */
INT32 RTSPServerThreadFunc(RTSPServer *rtspServer);

/* RTSP thread function                                                       */
INT32 RTSPSessionThread(RTSPClient *clientConn);

/* Free the memory of RTSP connection structure                               */
INT32 RTSPConnectionDestroy(RTSPClient *clientConn);

/* Passive Free the memory of RTSP connection structure                       */
INT32 RTSPConnectionDestroyPassive(RTSPClient *ClientConn);

/* Function to read RTSP server message from RTSP session socket              */
//RTSPBuff * RTSPServerReadMessage (SOCKET rtspSessionSocket, INT32 HttpFlag);
RTSPBuff *RTSPServerReadMessage(SOCKET rtspSessionSocket);

/* Function to parse the given RTSP message and generate RTSP request         */
RTSPRequestMsg *RTSPServerParseMessage(RTSPBuff *recvRTSPBuff);

/* Function to process the RTSP requests                                      */
// cyf: 处理消息前是否需要检查接收消息的有效性
INT32 RTSPServerProcessMessage(RTSPClient *rtspClientConn, int nCheckValid = 1);

/* Function to send RTSP response to the connected clients                    */
INT32 RTSPServerSendResponse(RTSPClient *rtspClientConn);

/* Function to generate RTSP response as per the status code                  */
INT32 RTSPGenerateMethodResponse(RTSPClient *rtspClientConn, INT32 statusCode);

/* Function to generate RTSP response for OPTIONS request                     */
INT32 RTSPOptionHandle(RTSPClient *clientConn);

/* Function to generate RTSP response for DESCRIBE request                    */
INT32 RTSPDescribeHandle(RTSPClient *rtspClientConn);

/* Function to generate RTSP response for SETUP request                       */
INT32 RTSPSetupHandle(RTSPClient *rtspClientConn);

/* Function to generate RTSP response for PLAY request                        */
INT32 RTSPPlayHandle(RTSPClient *rtspClientConn);

/* Function to generate RTSP response for PAUSE request                       */
INT32 RTSPPauseHandle(RTSPClient *rtspClientConn);

/* Function to generate RTSP response for TEARDOWN request                    */
INT32 RTSPTeardownHandle(RTSPClient *rtspClientConn);

/* Common RTSP request message validation function                            */
INT32 CommonMsgValidation(RTSPClient *clientConn);

/* Return the RTSP method for given string                                    */
RTSPMsgMethod ConvertMethodString(BYTE *buffer);

/* Convert the source string in to NAL string                                 */
INT32 ConvertToNALString(BYTE *destPtr, const BYTE *sourcePtr, INT32 dataLen);

/* Add response header to response message structure                          */
INT32 AddResponseHeader(RTSPResponseMsg *responseMsg, BYTE *headerName,
                        BYTE *headerValue);

/* Copy header from request message to response message structure             */
INT32 CopyResponseHeader(RTSPResponseMsg *responseMsg,
                         RTSPRequestMsg   *requestMsg,
                         BYTE             *headerName);

/* Get the Header value from Request Message structure                        */
BYTE *GetRequestMsgHeader(RTSPRequestMsg  *requestMsg, BYTE *headerName);

/* Parse NAL header and return SPS and PPS header                             */
INT32 ParseNALHeader(BYTE *inputBuff, INT32 inputLen,
                     BYTE *spsBuff,   INT32 *spsLen,
                     BYTE *ppsBuff,   INT32 *ppsLen,
                     BYTE *profileLevelId);

/* Parse AAC Data and set SDP's config field                                  */
INT32 ParseAACData(BYTE *inputBuff, INT32 inputLen, BYTE *aacBuff);

/*  This function convert the input string to HEX character string            */
void ConvertToHex(BYTE *outBuf, BYTE *pData, INT32 dataSize);

/* Parses Vol Header of Mpeg4 Video                                           */
INT32 ParseVOLHeader(BYTE *inputBuff, INT32 inputLen, BYTE *volBuff);

/* Generate SDP                                                               */
INT32 RtspGenerateSDP(RTSPClient *clientConn);

/* Find character in the given buffer                                         */
INT32 FindCharInBuffer(BYTE *buffer, BYTE findChar,
                       BYTE endChar,  INT32 bufLen);

/* Return the RTSP session of given name from given RTSP server               */
RTSPSession *FindRTSPSession(RTSPServer   *rtspServer, BYTE *sessionName);

/* Frees Request Message                                                      */
void FreeRequestMsg(RTSPRequestMsg *requestMsg);

/* Frees Response Message                                                     */
void FreeResponseMsg(RTSPResponseMsg *responseMsg);

/* This Function Validates the Server Handle                                  */
INT32 ValidateServerHandle(INT32 rtspServerHandle);

/* This Function Validates the Session Handle                                 */
INT32 ValidateSessionHandle(INT32 rtspSessionHandle);

/* This Function Validates the Server Side Client Handle                      */
INT32 ValidateServersideClientHandle(INT32 clientHandle);

/* This functions destroys the non existing client instance after checking    */
INT32 CheckAndDeleteClient(RTSPClient *clientConn, INT32 clientPort);

#endif  /* _INCLUDE_RTSP_SERVER_H */

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


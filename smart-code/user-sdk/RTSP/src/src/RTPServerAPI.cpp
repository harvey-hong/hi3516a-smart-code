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
 * File Name    :   RTPServerAPI.c
 *
 * Description  :   This is RTP server implementation file. Following codec
 *                   packetising is supported.
 *                   1) H.264 Video Codec.
 *                   2) MPEG4 Video Codec.
 *                   3) MJPEG Video Codec.
 *                   4) G711 Speech Codec.
 *                   5) AAC Audio Codec.
 *                   6) MPEG2 Transport Stream.
 *
 * History:
 *  JUN/22/2007, UBV,   Created the file.
 *  JUN/25/2007, UBV,   Modified return value of APIs now it will return Error
 *                      codes.
 *  DEC/27/2007, ARJ,   Separated API and Internal functions in different files
 *  DEC/28/2007, ARJ,   RTP over TCP Feature Added
 *
 ******************************************************************************/
/****************
 * Include Files
 ****************/
#include "../inc/RtpServer.h"
#include "../inc/RtspServer.h"
#include "../inc/DbgPrint.h"

/*******************************************************************************
 * Function:    RTPSendH264Data
 *
 * Description: This function packetize the buffer data as per H.264 RTP packet
 *              and send it to the connected clients
 *
 * Parameters :
 *      [IN]  INT32 SessionHandle   - RTSP session Handle
 *      [IN]  BYTE* BufferData      - Data buffer pointer from which RTP packets
 *                                      will be generated
 *      [IN]  INT32 BufferLength    - Data length
 *      [IN]  BYTE  *HeaderExtension- Header Extension data pointer,
 *                                      this extension will be added in
 *                                      only first packet
 *      [IN]  INT32 HeaderExtensionSize - Size of Header Extension Data
 *      [IN]  UINT16 HeaderExtensionType - Type of Header Extension
 *      [IN]  INT64 NTPTimeStamp    - NTP format rtptime stamp from application
 *      [IN]  INT32 SendFileFlag    - Sendfile API usage flag
 *      [IN]  INT32 DeviceFD        - Device FD for sendfile API
 *      [IN]  BYTE  *VZero          - VZero pointer for sendfile API
 *      [IN]  void *conn_node       - Client connection pointer
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
// cyf: 注意这里的conn_node
// 若conn_node为某个特定RTSPClient对象指针，则表示希望向该特定客户端连接发送数据
// 若conn_node为NULL时，表示希望向该会话的所有客户端连接发送数据
/*cb change 2016.8.5 .添加h265的支持*/ 
RTP_RTSPLIB_API INT32 RTPSendH264Data(INT32 SessionHandle,  BYTE  *BufferData,
                                      INT32 BufferLength,   BYTE  *HeaderExtension,
                                      INT32 HeaderExtensionSize,
                                      UINT16 HeaderExtensionType,
                                      DWORD NTPTimeStamp,   INT32 SendFileFlag,
                                      INT32 nCodecType,       BYTE  *VZero,
                                      void *conn_node,      INT32 endOfFrameFlag)
{
    BYTE            *bufData;                             /* local buffer pointer to traverse   */
    BYTE            encodingName[MAX_IP_LENGTH];          /* Encoding Name of H264     */
    INT32           bufSize;                                                 /* Local buffer size variable         */
    INT32           retVal = 0;                                             /* Local variable to store Return value*/
    DWORD           rtpTimeStamp = 0;                                /* RTP timestamp value                */
    RTPSessionStream *rtspStream;                                 /* Pointer to RTSP Stream             */
    RTSPSession     *rtspSession;                                    /* RTSP session pointer               */

    if (ValidateSessionHandle(SessionHandle) != RET_OK)
    {
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    if ((HeaderExtension != NULL) || (HeaderExtensionSize > 0))
    {
        if (((HeaderExtension == NULL) && (HeaderExtensionSize > 0)) ||
            ((HeaderExtension != NULL) && (HeaderExtensionSize <= 0)) ||
            (HeaderExtensionSize >= (((RTSPSession *)SessionHandle)->UdpMTUSize - RTPHEADERSIZE)) ||
            HeaderExtensionType == 0)
        {
            RtpRtspErrorPrint("Invalid input arguments\n");
            return RTP_RTSP_INVALID_INPUT_VALUE;
        }
    }

    rtspSession = (RTSPSession *)SessionHandle;
    bufSize     = BufferLength;
    bufData     = BufferData;

    if ((rtspSession == NULL) || (bufData == NULL))
    {
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    if (rtspSession->SessionStreamList == NULL)
    {
        return  RTP_RTSP_PAYLOAD_NOT_ADDED;
    }
	/*cb change 2016.8.5 .添加h265的支持 start*/ 
	if(nCodecType == 5)
	    strcpy((INT8 *)encodingName, "H265");
	else if(nCodecType == 6)
		strcpy((INT8 *)encodingName, "H264");
	/*cb change 2016.8.5 .添加h265的支持 end*/ 
    rtspStream = rtspSession->SessionStreamList;

    while (rtspStream)
    {
        if (!strcmp((INT8 *)rtspStream->EncodingName, (INT8 *)encodingName))
        {
            break;
        }

        rtspStream = rtspStream->Next;
    }

    if (rtspStream == NULL)
    {
        RtpRtspErrorPrint("H264 is not added in this session\n");
        return  RTP_RTSP_INVALID_INPUT_VALUE;
    }

    rtpTimeStamp = NTPTimeStamp;

    if (rtspSession->SessionConnectedClientList == NULL)
    {
        return  RTP_RTSP_NO_CLIENT_CONNECTED;
    }

    /* Store the first rtp-timestamp based on system time value               */
    if (!rtspStream->rtpTimeStamp)
    {
        rtspStream->rtpTimeStamp = (GetTimeValue() * rtspStream->ClockRate / 1000);
    }

    /*  Last argument set to 0 for UDP client                                 */
    /*  Send data to all UDP clients                                          */
    if (rtspSession->UDPClientCount)
    {
    	/*cb change 2016.8.5 .添加h265的支持*/ 
        retVal = SendH264DataToClient(rtspSession,    bufData,    bufSize,
                                      HeaderExtension,    HeaderExtensionSize,
                                      HeaderExtensionType,    rtspStream,
                                      rtpTimeStamp,   SendFileFlag,
                                      nCodecType,   VZero,  encodingName, 0,
                                      conn_node, endOfFrameFlag);

        if (retVal < 0)
        {
            return retVal;
        }
    }

    if (rtspSession->TCPClientCount)
    {
    	/*cb change 2016.8.5 .添加h265的支持*/ 
        retVal = SendH264DataToClient(rtspSession,  bufData,    bufSize,
                                      HeaderExtension,  HeaderExtensionSize,
                                      HeaderExtensionType,  rtspStream,
                                      rtpTimeStamp,     SendFileFlag,
                                      nCodecType,     VZero,  encodingName, 1,
                                      conn_node, endOfFrameFlag);

        if (retVal  < 0)
        {
            return retVal;
        }
    }

    return RTP_RTSP_OK;
}


/*******************************************************************************
 * Function:    RTPSendG711UData
 *
 * Description: This function packetize the buffer data as per G711 RTP packet
 *              and send it to the connected clients
 *
 * Parameters :
 *      [IN]  INT32 SessionHandle   - RTSP session Handle
 *      [IN]  BYTE* BufferData      - Data buffer pointer from which RTP packets
 *                                      will be generated
 *      [IN]  INT32 BufferLength    - Data length
 *      [IN]  BYTE  *HeaderExtension- Header Extension data pointer,
 *                                      this extension will be added in
 *                                      only first packet
 *      [IN]  INT32 HeaderExtensionSize - Size of Header Extension Data
 *      [IN]  UINT16 HeaderExtensionType - Type of Header Extension
 *      [IN]  INT64 NTPTimeStamp    - NTP format rtptime stamp from application
 *      [IN]  INT32 SendFileFlag    - Sendfile API usage flag
 *      [IN]  INT32 DeviceFD        - Device FD for sendfile API
 *      [IN]  BYTE  *VZero          - VZero pointer for sendfile API
 *      [IN]  void *conn_node       - Client connection pointer
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_NO_CLIENT_CONNECTED    - No client connected
 *              RTP_RTSP_DATA_SEND_SOCK_ERROR   - Socket send failed
 *              RTP_RTSP_PAYLOAD_NOT_ADDED  - No Stream Added to session
 ******************************************************************************/
RTP_RTSPLIB_API INT32 RTPSendG711UData(INT32 SessionHandle, BYTE  *BufferData,
                                       INT32 BufferLength,   BYTE  *HeaderExtension,
                                       INT32 HeaderExtensionSize,
                                       UINT16 HeaderExtensionType,
                                       DWORD NTPTimeStamp,   INT32 SendFileFlag,
                                       INT32 DeviceFD,       BYTE  *VZero,
                                       void *conn_node)
{
    INT32           retVal = 0;         /* Local Variable to store Return value*/
    BYTE            *bufData;           /* local buffer pointer to traverse   */
    BYTE            encodingName[MAX_IP_LENGTH]; /* Encoding Name of G711     */
    INT32           bufSize;            /* Local buffer size variable         */
    RTPSessionStream *rtspStream;       /* Pointer to RTSP Stream             */
    RTSPSession     *rtspSession;       /* RTSP session pointer               */
    DWORD           rtpTimeStamp = 0;   /* RTP timestamp value                */
    RtpRtspDebugPrint(DBG_LEVEL_2, "\nENTER : \n\tSessionHandle = %d\n\tBufferData = %d\
                        \n\tBufferLength = %d \n\tHeaderExtension = %d\
                        \n\tHeaderExtensionSize = %d\n\tHeaderExtensionType = %d \n",
                      SessionHandle, BufferData, BufferLength, HeaderExtension,
                      HeaderExtensionSize, HeaderExtensionType);
    RtpRtspDebugPrint(DBG_LEVEL_4, "Validating Input Arguments\n");

    /* Validating Session Handle                                              */
    if (ValidateSessionHandle(SessionHandle) != RET_OK)
    {
        RtpRtspErrorPrint("Invalid RTSP session Handle passed \n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Validate Input Arguments                                               */
    if ((SessionHandle <= 0) || (BufferData == NULL) || (BufferLength <= 0) ||
        ((BufferLength > 0) && (BufferData == NULL)) ||
        ((BufferLength <= 0) && (BufferData != NULL)))
    {
        RtpRtspErrorPrint("Invalid input arguments\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    if ((HeaderExtension != NULL) || (HeaderExtensionSize > 0))
    {
        if (((HeaderExtension == NULL) && (HeaderExtensionSize > 0)) ||
            ((HeaderExtension != NULL) && (HeaderExtensionSize <= 0)) ||
            (HeaderExtensionSize >= (((RTSPSession *)SessionHandle)->UdpMTUSize - RTPHEADERSIZE)) ||
            HeaderExtensionType == 0)
        {
            RtpRtspErrorPrint("Invalid input arguments\n");
            return RTP_RTSP_INVALID_INPUT_VALUE;
        }
    }

    /* Take Session Handle in local pointer                                   */
    rtspSession = (RTSPSession *)SessionHandle;
    bufSize = BufferLength;
    bufData = BufferData;

    if ((rtspSession == NULL) || (bufData == NULL))
    {
        RtpRtspErrorPrint("Invalid input arguments\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Check whether any stream is added to this session or not               */
    if (rtspSession->SessionStreamList == NULL)
    {
        RtpRtspErrorPrint("No stream added to this session\n");
        return  RTP_RTSP_PAYLOAD_NOT_ADDED;
    }

    RtpRtspDebugPrint(DBG_LEVEL_4, "Getting Stream Pointer from Stream List\n");
    /* Encoding Name of G711 ULaw                                             */
    strcpy((INT8 *)encodingName, "PCMU");
    /* Get Pointer of this stream                                             */
    rtspStream = rtspSession->SessionStreamList;

    while (rtspStream)
    {
        if (!strcmp((INT8 *)rtspStream->EncodingName, (INT8 *)encodingName))
        {
            break;
        }

        rtspStream = rtspStream->Next;
    }

    if (rtspStream == NULL)
    {
        RtpRtspErrorPrint("G711 ULaw is not added in this session\n");
        return  RTP_RTSP_INVALID_INPUT_VALUE;
    }

    RtpRtspDebugPrint(DBG_LEVEL_4, "Generating Time Stamp\n");
    rtpTimeStamp = (NTPTimeStamp * (rtspStream->ClockRate / 1000)) / 90;

    /* Checking whether any client is connected to this session or not        */
    if (rtspSession->SessionConnectedClientList == NULL)
    {
        RtpRtspDebugPrint(DBG_LEVEL_5, "No client is connected to this session\n");
        return RTP_RTSP_NO_CLIENT_CONNECTED;
    }

    if (!rtspStream->rtpTimeStamp)
    {
        /* Store the first rtp-timestamp based on system time value           */
        rtspStream->rtpTimeStamp = (GetTimeValue() * rtspStream->ClockRate / 1000);
    }

    /*  Last argument set to 0 for UDP client                                 */
    /*  Send data to all UDP clients                                          */
    if (rtspSession->UDPClientCount)
    {
        retVal = SendG711DataToClient(rtspSession,    bufData,    bufSize,
                                      HeaderExtension,    HeaderExtensionSize,
                                      HeaderExtensionType,    rtspStream,
                                      rtpTimeStamp,   SendFileFlag,
                                      DeviceFD,   VZero,  encodingName, 0, conn_node);

        if (retVal < 0)
        {
            RtpRtspErrorPrint("Error sending data To UDP client \n");
            return retVal;
        }
    }

    /*  Last argument set to 1 for TCP client                                 */
    /*  Send data to all TCP clients                                          */
    if (rtspSession->TCPClientCount)
    {
        retVal = SendG711DataToClient(rtspSession,  bufData,    bufSize,
                                      HeaderExtension,  HeaderExtensionSize,
                                      HeaderExtensionType,  rtspStream,
                                      rtpTimeStamp,     SendFileFlag,
                                      DeviceFD,     VZero,  encodingName, 1, conn_node);

        if (retVal  < 0)
        {
            RtpRtspErrorPrint("Error sending data To TCP client \n");
            return retVal;
        }
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "\nEXIT : \n\tReturn Successfully\n");
    return RTP_RTSP_OK;
}

/*******************************************************************************
 * Function:    RTPSendG711AData
 *
 * Description: This function packetize the buffer data as per G711 RTP packet
 *              and send it to the connected clients
 *
 * Parameters :
 *      [IN]  INT32 SessionHandle   - RTSP session Handle
 *      [IN]  BYTE* BufferData      - Data buffer pointer from which RTP packets
 *                                      will be generated
 *      [IN]  INT32 BufferLength    - Data length
 *      [IN]  BYTE  *HeaderExtension- Header Extension data pointer,
 *                                      this extension will be added in
 *                                      only first packet
 *      [IN]  INT32 HeaderExtensionSize - Size of Header Extension Data
 *      [IN]  UINT16 HeaderExtensionType - Type of Header Extension
 *      [IN]  INT64 NTPTimeStamp    - NTP format rtptime stamp from application
 *      [IN]  INT32 SendFileFlag    - Sendfile API usage flag
 *      [IN]  INT32 DeviceFD        - Device FD for sendfile API
 *      [IN]  BYTE  *VZero          - VZero pointer for sendfile API
 *      [IN]  void *conn_node       - Client connection pointer
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_NO_CLIENT_CONNECTED    - No client connected
 *              RTP_RTSP_DATA_SEND_SOCK_ERROR   - Socket send failed
 *              RTP_RTSP_PAYLOAD_NOT_ADDED  - No Stream Added to session
 ******************************************************************************/
RTP_RTSPLIB_API INT32 RTPSendG711AData(INT32 SessionHandle, BYTE  *BufferData,
                                       INT32 BufferLength,   BYTE  *HeaderExtension,
                                       INT32 HeaderExtensionSize,
                                       UINT16 HeaderExtensionType,
                                       DWORD NTPTimeStamp,   INT32 SendFileFlag,
                                       INT32 DeviceFD,       BYTE  *VZero,
                                       void *conn_node)
{
    INT32           retVal = 0;         /* Local Variable to store Return value*/
    BYTE            *bufData;           /* local buffer pointer to traverse   */
    BYTE            encodingName[MAX_IP_LENGTH]; /* Encoding Name of G711     */
    INT32           bufSize;            /* Local buffer size variable         */
    RTPSessionStream *rtspStream;       /* Pointer to RTSP Stream             */
    RTSPSession     *rtspSession;       /* RTSP session pointer               */
    DWORD           rtpTimeStamp = 0;   /* RTP timestamp value                */
    RtpRtspDebugPrint(DBG_LEVEL_2, "\nENTER : \n\tSessionHandle = %d\n\tBufferData = %d\
                        \n\tBufferLength = %d \n\tHeaderExtension = %d\
                        \n\tHeaderExtensionSize = %d\n\tHeaderExtensionType = %d \n",
                      SessionHandle, BufferData, BufferLength, HeaderExtension,
                      HeaderExtensionSize, HeaderExtensionType);
    RtpRtspDebugPrint(DBG_LEVEL_4, "Validating Input Arguments\n");

    /* Validating Session Handle                                              */
    if (ValidateSessionHandle(SessionHandle) != RET_OK)
    {
        RtpRtspErrorPrint("Invalid RTSP session Handle passed \n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Validate Input Arguments                                               */
    if ((SessionHandle <= 0) || (BufferData == NULL) || (BufferLength <= 0) ||
        ((BufferLength > 0) && (BufferData == NULL)) ||
        ((BufferLength <= 0) && (BufferData != NULL)))
    {
        RtpRtspErrorPrint("Invalid input arguments\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    if ((HeaderExtension != NULL) || (HeaderExtensionSize > 0))
    {
        if (((HeaderExtension == NULL) && (HeaderExtensionSize > 0)) ||
            ((HeaderExtension != NULL) && (HeaderExtensionSize <= 0)) ||
            (HeaderExtensionSize >= (((RTSPSession *)SessionHandle)->UdpMTUSize - RTPHEADERSIZE)) ||
            HeaderExtensionType == 0)
        {
            RtpRtspErrorPrint("Invalid input arguments\n");
            return RTP_RTSP_INVALID_INPUT_VALUE;
        }
    }

    /* Take Session Handle in local pointer                                   */
    rtspSession = (RTSPSession *)SessionHandle;
    bufSize = BufferLength;
    bufData = BufferData;

    if ((rtspSession == NULL) || (bufData == NULL))
    {
        RtpRtspErrorPrint("Invalid input arguments\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Check whether any stream is added to this session or not               */
    if (rtspSession->SessionStreamList == NULL)
    {
        RtpRtspErrorPrint("No stream added to this session\n");
        return  RTP_RTSP_PAYLOAD_NOT_ADDED;
    }

    RtpRtspDebugPrint(DBG_LEVEL_4, "Getting Stream Pointer from Stream List\n");
    /* Encoding Name of G711 ALaw                                             */
    strcpy((INT8 *)encodingName, "PCMA");
    /* Get Pointer of this stream                                             */
    rtspStream = rtspSession->SessionStreamList;

    while (rtspStream)
    {
        if (!strcmp((INT8 *)rtspStream->EncodingName, (INT8 *)encodingName))
        {
            break;
        }

        rtspStream = rtspStream->Next;
    }

    if (rtspStream == NULL)
    {
        RtpRtspErrorPrint("G711 ALaw is not added in this session\n");
        return  RTP_RTSP_INVALID_INPUT_VALUE;
    }

    RtpRtspDebugPrint(DBG_LEVEL_4, "Generating Time Stamp\n");
    rtpTimeStamp = (NTPTimeStamp * (rtspStream->ClockRate / 1000)) / 90;

    /* Checking whether any client is connected to this session or not        */
    if (rtspSession->SessionConnectedClientList == NULL)
    {
        RtpRtspDebugPrint(DBG_LEVEL_5, "No client is connected to this session\n");
        return RTP_RTSP_NO_CLIENT_CONNECTED;
    }

    if (!rtspStream->rtpTimeStamp)
    {
        /* Store the first rtp-timestamp based on system time value           */
        rtspStream->rtpTimeStamp = (GetTimeValue() * rtspStream->ClockRate / 1000);
    }

    RtpRtspDebugPrint(DBG_LEVEL_4, "Packetization Started\n");

    /*  Last argument set to 0 for UDP client                                 */
    /*  Send data to all UDP clients                                          */
    if (rtspSession->UDPClientCount)
    {
        retVal = SendG711DataToClient(rtspSession,    bufData,    bufSize,
                                      HeaderExtension,    HeaderExtensionSize,
                                      HeaderExtensionType,    rtspStream,
                                      rtpTimeStamp,   SendFileFlag,
                                      DeviceFD,   VZero,  encodingName, 0, conn_node);

        if (retVal < 0)
        {
            RtpRtspErrorPrint("Error sending data To UDP client \n");
            return retVal;
        }
    }

    /*  Last argument set to 1 for TCP client                                 */
    /*  Send data to all TCP clients                                          */
    if (rtspSession->TCPClientCount)
    {
        retVal = SendG711DataToClient(rtspSession,  bufData,    bufSize,
                                      HeaderExtension,  HeaderExtensionSize,
                                      HeaderExtensionType,  rtspStream,
                                      rtpTimeStamp,     SendFileFlag,
                                      DeviceFD,     VZero,  encodingName, 1, conn_node);

        if (retVal  < 0)
        {
            RtpRtspErrorPrint("Error sending data To TCP client \n");
            return retVal;
        }
    }

    RtpRtspDebugPrint(DBG_LEVEL_2, "\nEXIT : \n\tReturn Successfully\n");
    return RTP_RTSP_OK;
}


/*******************************************************************************
 * Function:    RTPSendG726Data
 *
 * Description: This function packetize the buffer data as per G726 RTP packet
 *              and send it to the connected clients
 *
 * Parameters :
 *      [IN]  INT32 SessionHandle   - RTSP session Handle
 *      [IN]  BYTE* BufferData      - Data buffer pointer from which RTP packets
 *                                      will be generated
 *      [IN]  INT32 BufferLength    - Data length
 *      [IN]  BYTE  *HeaderExtension- Header Extension data pointer,
 *                                      this extension will be added in
 *                                      only first packet
 *      [IN]  INT32 HeaderExtensionSize - Size of Header Extension Data
 *      [IN]  UINT16 HeaderExtensionType - Type of Header Extension
 *      [IN]  INT64 NTPTimeStamp    - NTP format rtptime stamp from application
 *      [IN]  INT32 SendFileFlag    - Sendfile API usage flag
 *      [IN]  INT32 DeviceFD        - Device FD for sendfile API
 *      [IN]  BYTE  *VZero          - VZero pointer for sendfile API
 *      [IN]  void *conn_node       - Client connection pointer
 *
 * Return Value:
 *      INT32 - RTP_RTSP_OK
 *              OR
 *              Following Error code
 *              RTP_RTSP_INVALID_INPUT_VALUE    - Invalid argument
 *              RTP_RTSP_NO_CLIENT_CONNECTED    - No client connected
 *              RTP_RTSP_DATA_SEND_SOCK_ERROR   - Socket send failed
 *              RTP_RTSP_PAYLOAD_NOT_ADDED  - No Stream Added to session
 ******************************************************************************/
RTP_RTSPLIB_API INT32 RTPSendG726Data(INT32 SessionHandle,  BYTE  *BufferData,
                                      INT32 BufferLength,   BYTE  *HeaderExtension,
                                      INT32 HeaderExtensionSize,
                                      UINT16 HeaderExtensionType,
                                      DWORD NTPTimeStamp,   INT32 SendFileFlag,
                                      INT32 DeviceFD,       BYTE  *VZero,
                                      void *conn_node)
{
    DWORD           rtpTimeStamp = 0;   /* RTP timestamp value                */
    INT32           retVal = 0;         /* Local Variable to store Return value*/
    INT32           bufSize;            /* Local buffer size variable         */
    BYTE            *bufData;           /* local buffer pointer to traverse   */
    BYTE            encodingName[MAX_IP_LENGTH]; /* Encoding Name of G711     */
    RTPSessionStream *rtspStream;       /* Pointer to RTSP Stream             */
    RTSPSession     *rtspSession;       /* RTSP session pointer               */
    RtpRtspDebugPrint(DBG_LEVEL_2, "\nENTER : \n\tSessionHandle = %d\n\tBufferData = %d\
                        \n\tBufferLength = %d \n\tHeaderExtension = %d\
                        \n\tHeaderExtensionSize = %d\n\tHeaderExtensionType = %d \n",
                      SessionHandle, BufferData, BufferLength, HeaderExtension,
                      HeaderExtensionSize, HeaderExtensionType);
    RtpRtspDebugPrint(DBG_LEVEL_4, "Validating Input Arguments\n");

    /* Validating Session Handle                                              */
    if (ValidateSessionHandle(SessionHandle) != RET_OK)
    {
        RtpRtspErrorPrint("Invalid RTSP session Handle passed \n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Validate Input Arguments                                               */
    if ((SessionHandle <= 0) || (BufferData == NULL) || (BufferLength <= 0) ||
        ((BufferLength > 0) && (BufferData == NULL)) ||
        ((BufferLength <= 0) && (BufferData != NULL)))
    {
        RtpRtspErrorPrint("Invalid input arguments\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    if ((HeaderExtension != NULL) || (HeaderExtensionSize > 0))
    {
        if (((HeaderExtension == NULL) && (HeaderExtensionSize > 0)) ||
            ((HeaderExtension != NULL) && (HeaderExtensionSize <= 0)) ||
            (HeaderExtensionSize >= (((RTSPSession *)SessionHandle)->UdpMTUSize - RTPHEADERSIZE)) ||
            HeaderExtensionType == 0)
        {
            RtpRtspErrorPrint("Invalid input arguments\n");
            return RTP_RTSP_INVALID_INPUT_VALUE;
        }
    }

    /* Take Session Handle in local pointer                                   */
    rtspSession = (RTSPSession *)SessionHandle;
    bufSize = BufferLength;
    bufData = BufferData;

    if ((rtspSession == NULL) || (bufData == NULL))
    {
        RtpRtspErrorPrint("Invalid input arguments\n");
        return RTP_RTSP_INVALID_INPUT_VALUE;
    }

    /* Check whether any stream is added to this session or not               */
    if (rtspSession->SessionStreamList == NULL)
    {
        RtpRtspErrorPrint("No stream added to this session\n");
        return  RTP_RTSP_PAYLOAD_NOT_ADDED;
    }

    RtpRtspDebugPrint(DBG_LEVEL_4, "Getting Stream Pointer from Stream List\n");
    /* Encoding Name of G726                                                  */
    strcpy((INT8 *)encodingName, "G726");
    /* Get Pointer of this stream                                             */
    rtspStream = rtspSession->SessionStreamList;

    while (rtspStream)
    {
        if (strstr((INT8 *)rtspStream->EncodingName, (INT8 *)encodingName))
        {
            break;
        }

        rtspStream = rtspStream->Next;
    }

    if (rtspStream == NULL)
    {
        RtpRtspErrorPrint("G726 is not added in this session\n");
        return  RTP_RTSP_INVALID_INPUT_VALUE;
    }

    RtpRtspDebugPrint(DBG_LEVEL_4, "Generating Time Stamp\n");
    /*  Clock Rate 8000 in case of G726                                       */
    rtpTimeStamp = (NTPTimeStamp * (8000 /*rtspStream->ClockRate*/ / 1000)) / 90;

    /* Checking whether any client is connected to this session or not        */
    if (rtspSession->SessionConnectedClientList == NULL)
    {
        RtpRtspDebugPrint(DBG_LEVEL_5, "No client is connected to this session\n");
        return RTP_RTSP_NO_CLIENT_CONNECTED;
    }

    if (!rtspStream->rtpTimeStamp)
    {
        /* Store the first rtp-timestamp based on system time value           */
        rtspStream->rtpTimeStamp = (GetTimeValue() * /*rtspStream->ClockRate*/ (8000 / 1000));
    }

    /*  Last argument set to 0 for UDP client                                 */
    /*  Send data to all UDP clients                                          */
    /*  Packatization same as G711                                            */
    if (rtspSession->UDPClientCount)
    {
        retVal = SendG711DataToClient(rtspSession,    bufData,    bufSize,
                                      HeaderExtension,    HeaderExtensionSize,
                                      HeaderExtensionType,    rtspStream,
                                      rtpTimeStamp,   SendFileFlag,
                                      DeviceFD,   VZero, rtspStream->EncodingName, 0, conn_node);

        if (retVal < 0)
        {
            RtpRtspErrorPrint("Error sending data To UDP client \n");
            return retVal;
        }
    }

    /*  Last argument set to 1 for TCP client                                 */
    /*  Send data to all TCP clients                                          */
    /*  Packatization same as G711                                            */
    if (rtspSession->TCPClientCount)
    {
        retVal = SendG711DataToClient(rtspSession,  bufData,    bufSize,
                                      HeaderExtension,  HeaderExtensionSize,
                                      HeaderExtensionType,  rtspStream,
                                      rtpTimeStamp,     SendFileFlag,
                                      DeviceFD,     VZero, rtspStream->EncodingName, 1, conn_node);

        if (retVal  < 0)
        {
            RtpRtspErrorPrint("Error sending data To TCP client \n");
            return retVal;
        }
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

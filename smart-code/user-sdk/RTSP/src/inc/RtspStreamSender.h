/*!
* @file
*  RtspStream.h
* @brief
*  RTSP流
* @author
*  Cheng Yanfang
* @date
*  2009年11月1日
* @version
*  1.0.0
*/

#ifndef RTSP_STREAM_SENDER_H

#define RTSP_STREAM_SENDER_H

#include "./InternalCommon.h"
#include "./Property.h"
#include "./HYRtspCommon.h"
#include "ws_utility_api.h"
using namespace ws_utility;

namespace   ApplicationLayer
{

class CRtspStreamSender
{
public:
    CRtspStreamSender();
    ~CRtspStreamSender();

public:
    // 初始化
    int Initialize(int nSessionId, eRtspStreamType eStreamType);
    // 销毁
    int Destroy();
    // 启动捕获
    int StartCapture();
    // 停止捕获
    int StopCapture();
    // 流媒体发送
    int Send(IN LPBuffer stream, void *pClientConn);
    // 获取SDP信息
    int GetSDPInfo(char *pSDPInfo, INT32 &nSDPLen);
    //\\ 设置开始传输的标识
    int StartSend();
    int GetRtspClientHandle();

private:
    // 发送H264数据
    int SendH264DataFrame(BYTE *pData, int nDataLen, DWORD nTimeStamp, void *pClientConn,int nCodecType);/*cb change 2016.8.5 .添加h265的支持*/
    // 获取SDP信息
    int GetSDPInfoFromFrame(LPBuffer pStream);

	int GetVpsFpsPps(LPBuffer pStream);/*cb change 2016.8.5 .添加h265的支持*/ 

	int GetFpsPps(LPBuffer pStream);/*cb change 2016.8.5 .添加h265的支持*/ 

private:

    eRtspStreamType m_eStreamType;                                  // rtsp流类型
    eTaskStatus m_eCaptureStatus;                                   // 捕获状态
    char m_acSDPInfo[MAX_SDP_LEN];                                  // SDP信息
    int m_nSDPInfoLen;                                              // SDP长度
    int m_nSpsFound;                                                // 是否找到sps
    int m_nPpsFound;                                                // 是否找到pps
    CSignal m_cSDPSignal;                                   // 获取sdp的信号量
    int m_nSessionId;                                               // 与该实时流关联的会话Id
    BYTE *m_pNaluPureData;                                          // 取出0x03后的NALU数据缓冲区
    CMutex m_cCapStatusMutex;                               // 捕获状态互斥量

    DWORD m_nNtpTimeStamp;                                          // 当前帧的时间戳
    DWORD m_dwLastTimeStamp;                                        // 上一帧的时间戳

    //\\ 设置允许发送标识
    eTaskStatus m_eSendStatus;
    //\\ 判断是否已经发送了I帧
    int         IsIFrameSend ;
};
}

#endif



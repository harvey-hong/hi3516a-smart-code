#ifndef RTSP_REAL_STREAM_H

#define RTSP_REAL_STREAM_H

#include "./InternalCommon.h"
#include "./Property.h"
#include "./HYRtspCommon.h"
#include "./interface/IRtspStream.h"
#include "./RtspStreamSender.h"
#include "./RealStreamSender.h"

#include "ws_utility_api.h"
using namespace ws_utility;

namespace   ApplicationLayer
{
// 客户端连接控制
typedef struct tagClientConnStreamCtrl
{
    eMediaCodeType eCodeType;                       // 编码类型
    int nClientId;                                  // 客户端连接Id
    int nMaxBitRate;                                // 该客户端连接的码率上限 (kb/s)
    int nMinBitRate;                                // 该客户端连接的码率下限 (kb/s)
    int nCurBitrate;                                // 当前码率大小 (kb/s)
    int nBitLimit;                                  // 以I帧为起始的数据大小限制 (B)
    int nDataSzSinceLastIFrame;                     // 上一个I帧以来已发送的数据量 (B)
    int nSendCurFrame;                              // 是否发送当前帧
    DWORD dwVideoTimeStamp;                         // 该客户端连接的视频帧时间戳
} ClientConnStreamCtrl;
/*
 * note: 分别计算每个客户端连接的时间戳，是因为realplayer起始时间戳太大时无法显示图像，
 * 所以，如果前面已经有客户端连接时，realplayer再连接，而由于时间戳已经被前面的连接
 * 逐渐累加大了，所以realplayer无法正常播放
 */

/*!
* \class CRealStream
* \brief 实时流
*/
class CRealStream : public IRtspStream
{
public:
    CRealStream();
    ~CRealStream();

    // 初始化
    //      int Initialize(int nSessionId, int nChannel, char *pStartTime, char *pEndTime);

    int Initialize(int nSessionId, int nChannel, char *pStartTime, char *pEndTime, eRtspMediaCodeType m_eCodeType);

    // 销毁
    int Destroy();

    // 启动
    int Start();
    // 停止
    int Stop();
    // 启动捕获
    int StartCapture();
    //\\ 启动发送标识
    int StartSend() ;
    // 停止捕获
    int StopCapture();
    // 暂停捕获
    int Pause();
    // 添加客户端连接
    int AddClientConn(int nClientId, void *pConnParam);
    // 移除客户端连接
    int RemoveClientConn(int nClientid);
    // 获取SDP信息
    int GetSDPInfo(char *pSDPInfo, INT32 &nSDPLen);

    // 流媒体发送
    int Send(IN eMediaCodeType eCodeType, IN CMediaPacketRealStreamDepict &depict, IN LPBuffer stream);
    // 流媒体发送
    int Send(IN LPBuffer stream);
    // 获取通道号
    int GetChannel(int &nChannel);
    // 获取音视频编码类型
    int GetCodecType(eRtspVideoCodecType &eVideoCodec, eRtspAudioCodecType &eAudioCodec);

    // 获取客户端连接信息
    int GetClientConnInfo(int nClientId, int &nSendFalg, DWORD &dwVideoTimeStamp);

private:

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRealStream);
private:

    eTaskStatus m_eTaskStatus;                                      // 实时流状态
    eTaskStatus m_eCaptureStatus;                                   // 捕获状态
    int m_nChannel;                                                 // 通道号
    eMediaCodeType m_eCurCodeType;                                  // 当前的实时流类型
    CMutex m_cStreamMutex;                                  // 实时流互斥量
    ClientConnStreamCtrl m_acClientCoon[MAX_REAL_STREAM_NUMBER];    // 该路实时流的客户端连接
    int m_nClientConnCount;                                         // 连接的客户端数
    CRealStreamSender m_cRealStreamSender;                          // 流发送器
    CRtspStreamSender m_cStreamSender;                              // 流发送器
    int m_nFrameType;                                               // 帧类型
    DWORD m_dwLastVideoTimeStamp;                                   // 上一帧视频时间戳
    DWORD m_dwLastIFrameTimeStamp;                                  // 上一个I帧时间戳
    DWORD m_Iframe_Send_Status;  //Hongzg added for Iframe send flag
    eRtspVideoCodecType VideoCodec;/*cb change 2016.8.5 .添加h265的支持*/
};

}

#endif



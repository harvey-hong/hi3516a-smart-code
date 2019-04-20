#ifndef IF_RTSP_STREAM_H

#define IF_RTSP_STREAM_H

#include "../InternalCommon.h"


namespace   ApplicationLayer
{
Interface IRtspStream
{
    // 初始化
    virtual int Initialize(int nSessionId, int nChannel, char *pStartTime, char *pEndTime, eRtspMediaCodeType m_eCodeType) = 0;
    // 销毁
    virtual int Destroy() = 0;
    // 启动
    virtual int Start() = 0;
    // 停止
    virtual int Stop() = 0;
    // 启动捕获
    virtual int StartCapture() = 0;
    //\\ 启动发送标识
    virtual int StartSend() = 0;
    // 停止捕获
    virtual int StopCapture() = 0;
    // 暂停捕获
    virtual int Pause() = 0;
    // 添加客户端连接
    virtual int AddClientConn(int nClientId, void *pConnParam) = 0 ;
    // 移除客户端连接
    virtual int RemoveClientConn(int nClientId) = 0;
    // 获取SDP信息
    virtual int GetSDPInfo(char *pSDPInfo, INT32 & nSDPLen) = 0;
    // 获取音视频编码类型
    virtual int GetCodecType(eRtspVideoCodecType & eVideoCodec, eRtspAudioCodecType & eAudioCodec) = 0;
    // 获取客户端连接信息
    virtual int GetClientConnInfo(int nClientId, int &nSendFalg, DWORD & dwVideoTimeStamp) = 0;
};

}

#endif

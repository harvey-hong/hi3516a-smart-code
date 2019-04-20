#ifndef REAL_STREAM_SENDER_H

#define REAL_STREAM_SENDER_H

#include "./InternalCommon.h"
#include "./template/TThread.h"
#include "ws_utility_api.h"
using namespace ws_utility;

#include "ws_comm_av.h"
#include "ws_model_api.h"

namespace   ApplicationLayer
{

using namespace ApplicationLayer;

class CRealStream;

class CRealStreamSender
{
public:
    CRealStreamSender();
    ~CRealStreamSender();
public:
    //启动实时流发送器
    int Start(ApplicationLayer::CRealStream *pSession, eMediaCodeType m_eCurCodeType);
    //恢复实时流发送
    int Resume();
    //暂停实时流发送
    int Suspend();
    //停止实时流发送器
    int Stop();
    //流媒体发送
    int Send(CMediaPacketRealStreamDepict &depict, LPBuffer stream);
    //运行任务
    int RunTask();
    int RunTaskSendData(char *pFramePointer , DWORD iFrameLen, ApplicationLayer::CRealStream *m_pSession);

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRealStreamSender);
protected:
    //初始化
    int Initialize();
    //销毁
    int Destory();
private:
    DWORD                               m_dwState;
    ApplicationLayer::CRealStream             *m_pSession;
    ApplicationLayer::TThread<CRealStreamSender>  m_cSendThread;
    CSignal     m_cSendSignal;
    CMutex      m_cMutex;
    unsigned int        m_iTaskId ;

    int                     m_channel_id;
    ws_venc_str_type        m_stream_type;
};

}

#endif

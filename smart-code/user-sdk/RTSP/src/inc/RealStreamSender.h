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
    //����ʵʱ��������
    int Start(ApplicationLayer::CRealStream *pSession, eMediaCodeType m_eCurCodeType);
    //�ָ�ʵʱ������
    int Resume();
    //��ͣʵʱ������
    int Suspend();
    //ֹͣʵʱ��������
    int Stop();
    //��ý�巢��
    int Send(CMediaPacketRealStreamDepict &depict, LPBuffer stream);
    //��������
    int RunTask();
    int RunTaskSendData(char *pFramePointer , DWORD iFrameLen, ApplicationLayer::CRealStream *m_pSession);

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRealStreamSender);
protected:
    //��ʼ��
    int Initialize();
    //����
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

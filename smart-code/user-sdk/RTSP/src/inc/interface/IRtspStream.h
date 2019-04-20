#ifndef IF_RTSP_STREAM_H

#define IF_RTSP_STREAM_H

#include "../InternalCommon.h"


namespace   ApplicationLayer
{
Interface IRtspStream
{
    // ��ʼ��
    virtual int Initialize(int nSessionId, int nChannel, char *pStartTime, char *pEndTime, eRtspMediaCodeType m_eCodeType) = 0;
    // ����
    virtual int Destroy() = 0;
    // ����
    virtual int Start() = 0;
    // ֹͣ
    virtual int Stop() = 0;
    // ��������
    virtual int StartCapture() = 0;
    //\\ �������ͱ�ʶ
    virtual int StartSend() = 0;
    // ֹͣ����
    virtual int StopCapture() = 0;
    // ��ͣ����
    virtual int Pause() = 0;
    // ��ӿͻ�������
    virtual int AddClientConn(int nClientId, void *pConnParam) = 0 ;
    // �Ƴ��ͻ�������
    virtual int RemoveClientConn(int nClientId) = 0;
    // ��ȡSDP��Ϣ
    virtual int GetSDPInfo(char *pSDPInfo, INT32 & nSDPLen) = 0;
    // ��ȡ����Ƶ��������
    virtual int GetCodecType(eRtspVideoCodecType & eVideoCodec, eRtspAudioCodecType & eAudioCodec) = 0;
    // ��ȡ�ͻ���������Ϣ
    virtual int GetClientConnInfo(int nClientId, int &nSendFalg, DWORD & dwVideoTimeStamp) = 0;
};

}

#endif

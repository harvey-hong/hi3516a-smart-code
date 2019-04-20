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
// �ͻ������ӿ���
typedef struct tagClientConnStreamCtrl
{
    eMediaCodeType eCodeType;                       // ��������
    int nClientId;                                  // �ͻ�������Id
    int nMaxBitRate;                                // �ÿͻ������ӵ��������� (kb/s)
    int nMinBitRate;                                // �ÿͻ������ӵ��������� (kb/s)
    int nCurBitrate;                                // ��ǰ���ʴ�С (kb/s)
    int nBitLimit;                                  // ��I֡Ϊ��ʼ�����ݴ�С���� (B)
    int nDataSzSinceLastIFrame;                     // ��һ��I֡�����ѷ��͵������� (B)
    int nSendCurFrame;                              // �Ƿ��͵�ǰ֡
    DWORD dwVideoTimeStamp;                         // �ÿͻ������ӵ���Ƶ֡ʱ���
} ClientConnStreamCtrl;
/*
 * note: �ֱ����ÿ���ͻ������ӵ�ʱ���������Ϊrealplayer��ʼʱ���̫��ʱ�޷���ʾͼ��
 * ���ԣ����ǰ���Ѿ��пͻ�������ʱ��realplayer�����ӣ�������ʱ����Ѿ���ǰ�������
 * ���ۼӴ��ˣ�����realplayer�޷���������
 */

/*!
* \class CRealStream
* \brief ʵʱ��
*/
class CRealStream : public IRtspStream
{
public:
    CRealStream();
    ~CRealStream();

    // ��ʼ��
    //      int Initialize(int nSessionId, int nChannel, char *pStartTime, char *pEndTime);

    int Initialize(int nSessionId, int nChannel, char *pStartTime, char *pEndTime, eRtspMediaCodeType m_eCodeType);

    // ����
    int Destroy();

    // ����
    int Start();
    // ֹͣ
    int Stop();
    // ��������
    int StartCapture();
    //\\ �������ͱ�ʶ
    int StartSend() ;
    // ֹͣ����
    int StopCapture();
    // ��ͣ����
    int Pause();
    // ��ӿͻ�������
    int AddClientConn(int nClientId, void *pConnParam);
    // �Ƴ��ͻ�������
    int RemoveClientConn(int nClientid);
    // ��ȡSDP��Ϣ
    int GetSDPInfo(char *pSDPInfo, INT32 &nSDPLen);

    // ��ý�巢��
    int Send(IN eMediaCodeType eCodeType, IN CMediaPacketRealStreamDepict &depict, IN LPBuffer stream);
    // ��ý�巢��
    int Send(IN LPBuffer stream);
    // ��ȡͨ����
    int GetChannel(int &nChannel);
    // ��ȡ����Ƶ��������
    int GetCodecType(eRtspVideoCodecType &eVideoCodec, eRtspAudioCodecType &eAudioCodec);

    // ��ȡ�ͻ���������Ϣ
    int GetClientConnInfo(int nClientId, int &nSendFalg, DWORD &dwVideoTimeStamp);

private:

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRealStream);
private:

    eTaskStatus m_eTaskStatus;                                      // ʵʱ��״̬
    eTaskStatus m_eCaptureStatus;                                   // ����״̬
    int m_nChannel;                                                 // ͨ����
    eMediaCodeType m_eCurCodeType;                                  // ��ǰ��ʵʱ������
    CMutex m_cStreamMutex;                                  // ʵʱ��������
    ClientConnStreamCtrl m_acClientCoon[MAX_REAL_STREAM_NUMBER];    // ��·ʵʱ���Ŀͻ�������
    int m_nClientConnCount;                                         // ���ӵĿͻ�����
    CRealStreamSender m_cRealStreamSender;                          // ��������
    CRtspStreamSender m_cStreamSender;                              // ��������
    int m_nFrameType;                                               // ֡����
    DWORD m_dwLastVideoTimeStamp;                                   // ��һ֡��Ƶʱ���
    DWORD m_dwLastIFrameTimeStamp;                                  // ��һ��I֡ʱ���
    DWORD m_Iframe_Send_Status;  //Hongzg added for Iframe send flag
    eRtspVideoCodecType VideoCodec;/*cb change 2016.8.5 .���h265��֧��*/
};

}

#endif



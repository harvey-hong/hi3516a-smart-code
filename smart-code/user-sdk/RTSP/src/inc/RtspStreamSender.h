/*!
* @file
*  RtspStream.h
* @brief
*  RTSP��
* @author
*  Cheng Yanfang
* @date
*  2009��11��1��
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
    // ��ʼ��
    int Initialize(int nSessionId, eRtspStreamType eStreamType);
    // ����
    int Destroy();
    // ��������
    int StartCapture();
    // ֹͣ����
    int StopCapture();
    // ��ý�巢��
    int Send(IN LPBuffer stream, void *pClientConn);
    // ��ȡSDP��Ϣ
    int GetSDPInfo(char *pSDPInfo, INT32 &nSDPLen);
    //\\ ���ÿ�ʼ����ı�ʶ
    int StartSend();
    int GetRtspClientHandle();

private:
    // ����H264����
    int SendH264DataFrame(BYTE *pData, int nDataLen, DWORD nTimeStamp, void *pClientConn,int nCodecType);/*cb change 2016.8.5 .���h265��֧��*/
    // ��ȡSDP��Ϣ
    int GetSDPInfoFromFrame(LPBuffer pStream);

	int GetVpsFpsPps(LPBuffer pStream);/*cb change 2016.8.5 .���h265��֧��*/ 

	int GetFpsPps(LPBuffer pStream);/*cb change 2016.8.5 .���h265��֧��*/ 

private:

    eRtspStreamType m_eStreamType;                                  // rtsp������
    eTaskStatus m_eCaptureStatus;                                   // ����״̬
    char m_acSDPInfo[MAX_SDP_LEN];                                  // SDP��Ϣ
    int m_nSDPInfoLen;                                              // SDP����
    int m_nSpsFound;                                                // �Ƿ��ҵ�sps
    int m_nPpsFound;                                                // �Ƿ��ҵ�pps
    CSignal m_cSDPSignal;                                   // ��ȡsdp���ź���
    int m_nSessionId;                                               // ���ʵʱ�������ĻỰId
    BYTE *m_pNaluPureData;                                          // ȡ��0x03���NALU���ݻ�����
    CMutex m_cCapStatusMutex;                               // ����״̬������

    DWORD m_nNtpTimeStamp;                                          // ��ǰ֡��ʱ���
    DWORD m_dwLastTimeStamp;                                        // ��һ֡��ʱ���

    //\\ ���������ͱ�ʶ
    eTaskStatus m_eSendStatus;
    //\\ �ж��Ƿ��Ѿ�������I֡
    int         IsIFrameSend ;
};
}

#endif



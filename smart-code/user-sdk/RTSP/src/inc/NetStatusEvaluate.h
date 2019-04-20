#ifndef _NET_STATUS_EVALUATE_H
#define _NET_STATUS_EVALUATE_H

#include "InternalCommon.h"
#include "RtcpServer.h"

#define MAX_TRANSFER_TIME           (1000.0)                            //RTCP�������ʱ��
//����״̬����RTCP������ʱ�䴦��300��������Ϊ������У�������������700��������Ϊ���緱æ�����С������300���뵽700����֮����ά������
#define LEVEL_IDLE_TIME             (300.0)
#define LEVEL_BUSY_TIME             (700.0)
typedef enum eNetLevel
{
    eNetLevelUnkown                 = 0,
    eNetIdle,
    eNetBusy,
    eNetNormal
};

//����Report Block

class CRBParse
{
public:
    CRBParse();
    virtual ~CRBParse();

    bool SetReportBlock(RTCPReportBlock *pReportBlock, struct timeval *pArrivalTime);
    UINT32 GetSRssrc();
    void SetSRssrc(UINT32 SRssrc);
    float GetFraction()
    {
        return (float)m_nFraction / 256;
    }
    //�жϴ�rtcp�����ϴν��յ�rtcp���Ƿ�����
    bool IsSequential();
    UINT32 GetJitter()
    {
        return m_nJitter;
    }
    //ʱ��
    float GetDelay();

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRBParse);

private:
    void Initialize();
private:
    UINT32 m_nSRssrc;                               //SR��ssrc
    UINT32 m_nFraction;                             //������
    UINT32 m_nLost;                                 //�ܶ�����
    UINT32 m_nLastSeq;                              //������
    UINT32 m_nPrevLost;                             //�ϴ��ܶ�����
    UINT32 m_nPrevLastSeq;                          //�ϴ�������
    UINT32 m_nJitter;                               //����
    UINT32 m_nLsr;                                  //��һ�����ͱ��ķ���ʱ��
    UINT32 m_nDlsr;                                 //���յ���һ�����ͱ��ĵ����ʹ˽��ձ����֮�����ʱ
    struct timeval  m_struArrivalTime;              //SR���ĵ���ʱ��
};

/* �ж��������һ�������ַ�����һ��ͨ�������ʣ�����ͨ��RTCP��ѭ��һȦ��ʱ��,����������������ԭ������������ȷ��ӳʵ�ִ���������
һ������UDP���Ľ���˳���ܱ�֤�����յ������ݰ����ܶ��ڷ��͵����ݰ����縴�����ݰ�����ɼ���Ķ����ʲ�����ȷ��ӳ�������
��һ��������RTCP�����ݰ����ܶ�ʧ��������ͷ�RTCP���ͻ㱨����ʧ������շ��������ݰ�����������ȷ���㣬����շ�RTCP���ջ㱨����ʧ�����ͷ����ܵõ������ʣ����Ҳ������ȷ��ӳ�������
���һ�����RTCP��ѭ��һȦ��ʱ�����ж������������RTCP��ѭ��һȦ��ʱ�䲻��׼ȷ��ӳ�����������ͨ��һЩ��ʩʹ֮����׼ȷ��
һ��ʹ�ö��RTCP���Ĵ���ʱ���ƽ��ֵ�ж��������������������Ķ��������������һ���ӽ���һ�ε�����
�������������ʱ�䣬�����ʧRTCP��������ͻȻ��������ʱ�Լ���ѭ��ʱ���ƽ��ֵ��ɵ�Ӱ�졣
ע�����ڶ�vlc���͵�RR����������������ʱ�ڸ������뵽��������֮�䣬������ȷ��ӳ����״������������Զ������������´���:
һ�����������������������С������
��������30��δ������������������
*/

class CNetStatusEvaluate
{
public:
    CNetStatusEvaluate();
    virtual ~CNetStatusEvaluate();

    void SetReportBlock(RTCPReportBlock *pReportBlock, struct timeval *pArrivalTime);
    UINT32 GetSRssrc();
    //��ȡ�ϴε�������ʱ��
    UINT32 GetLastAdjustTime();
    //�����ϴε�������ʱ��
    void SetLastAdjustTime(UINT32 nLastTime);
    //��ȡ����״��
    UINT32 GetNetStatus();
    //����������ʱ�Ͱ���
    void Reset();
    //�Ƿ�������
    bool IsLost();
protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CNetStatusEvaluate);
private:
    void Initialize();
    void ComputeDelay();
private:
    float  m_fDelay;                                //������ʱ,�Ժ���Ϊ��λ
    UINT32 m_nLastTime;                             //���һ�ε�������ʱ��
    UINT32 m_nRecvPacketNum;                        //�յ���RR����
    CRBParse m_cRBParse;                            //����Report Block
};

#endif

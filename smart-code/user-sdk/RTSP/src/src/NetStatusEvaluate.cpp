#include "../inc/InternalCommon.h"
#include "../inc/NetStatusEvaluate.h"


CRBParse::CRBParse()
{
    Initialize();
}

CRBParse::~CRBParse()
{
    Initialize();
}

void CRBParse::Initialize()
{
    m_nSRssrc = 0;
    m_nFraction = 0;
    m_nLost = 0;
    m_nLastSeq = 0;
    m_nPrevLost = 0;
    m_nPrevLastSeq = 0;
    m_nJitter = 0;
    m_nLsr = 0;
    m_nDlsr = 0;
    memset(&m_struArrivalTime, 0, sizeof(m_struArrivalTime));
}

bool CRBParse::SetReportBlock(RTCPReportBlock *pReportBlock, struct timeval *pArrivalTime)
{
    if (0 == m_nSRssrc)
    {
        m_nSRssrc = pReportBlock->ssrc;
    }

    if (m_nSRssrc != pReportBlock->ssrc)
    {
        return false;
    }

    m_nFraction = pReportBlock->fraction;
    m_nPrevLost = m_nLost;
    m_nPrevLastSeq = m_nLastSeq;
    m_nLost = pReportBlock->lost;
    m_nLastSeq = pReportBlock->lastSeq;
    m_nJitter = pReportBlock->jitter;
    m_nLsr = pReportBlock->lsr;
    m_nDlsr = pReportBlock->dlsr;
    m_struArrivalTime = *pArrivalTime;
    return true;
}

UINT32 CRBParse::GetSRssrc()
{
    return m_nSRssrc;
}

void CRBParse::SetSRssrc(UINT32 nSRssrc)
{
    m_nSRssrc = nSRssrc;
}

//������˵��:�Դ�ǰһSR����RR����������,��SSRC_n������RTP���ݰ�����ʧ����,
//�Թ̶���С������ʽ��ʾ,С�����ڴ�������,���ڽ���ʧ������256��ȡ��������
//.��ֵ����Ϊ��ʧ�������������յİ�����.
bool CRBParse::IsSequential()
{
    float fFraction = 0.0;

    //RR��δ���㶪���ʻ�Ϊ����������Ϊ��������
    if (0 == m_nFraction)
    {
        return true;
    }

    fFraction = ((float)(m_nLost - m_nPrevLost)) / ((float)(m_nLastSeq - m_nPrevLastSeq));

    //ͨ���Ƚ�RR���еĶ������������Ķ��������ж��Ƿ�rtcp���ǲ���������
    if (m_nFraction == (UINT32(fFraction * 256)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

float CRBParse::GetDelay()
{
    float fDelay = 0.0;//������ʱ������Ϊ��λ
    float fLsrTime = 0.0;//��һSR������ʱ�̣�����Ϊ��λ
    float fArrivalTime = 0.0;//RR������ʱ�̣�����Ϊ��λ
    float fDlsr = 0.0;//�������һSR�������ʱ�䣬����Ϊ��λ
    UINT32 nNtpSec = 0;
    UINT32 nNtpFrac = 0;

    //���LSR��DLSRΪ�㣬�޷����㻷·��ʱ������
    if (0 == m_nLsr || 0 == m_nDlsr)
    {
        return 0.0;
    }

    GetNtpTs(&nNtpSec, &nNtpFrac, m_struArrivalTime.tv_sec, m_struArrivalTime.tv_usec);
    //ȡ64λNTP�м��32λ�������Ӧʱ��
    fArrivalTime = (float)(nNtpSec & 0x0000FFFF) * 1000 + (float)(nNtpFrac & 0xFFFF0000) * (233.0 / 1000000000.0);
    fLsrTime = (float)((m_nLsr >> 16) & 0xFFFF) * 1000 + (float)((m_nLsr << 16) & 0xFFFF0000) * (233.0 / 1000000000.0);
    fDlsr = (float)m_nDlsr * (1000 / 65536.0);
    fDelay = fArrivalTime - fLsrTime - fDlsr;
    return (fDelay < 0) ? 0.0 : (fDelay / 2);
}

CNetStatusEvaluate::CNetStatusEvaluate()
{
    Initialize();
}

CNetStatusEvaluate::~CNetStatusEvaluate()
{
    Initialize();
}

void CNetStatusEvaluate::Initialize()
{
    m_fDelay = 0;
    m_nLastTime = 0;
    m_nRecvPacketNum = 0;
}

void CNetStatusEvaluate::SetReportBlock(RTCPReportBlock *pReportBlock, struct timeval *pArrivalTime)
{
    if (!m_cRBParse.SetReportBlock(pReportBlock, pArrivalTime))
    {
        return;
    }

    ComputeDelay();
}

void CNetStatusEvaluate::ComputeDelay()
{
    float fDelay = 0.0;
    fDelay = m_cRBParse.GetDelay();

    if (fDelay > -0.001 && fDelay < 0.001)
    {
        return;
    }

    //���RR�����������Զ�ʧһ��RR�����Ҵ���ʱ��Ϊ�����ʱ����㣬��������RR������������ʱ�����Ӱ��
    if (!m_cRBParse.IsSequential())
    {
        m_fDelay = m_fDelay + MAX_TRANSFER_TIME + fDelay;//��ʧRR����������ʱ�ͽ��յ���RR����������ʱ
        m_nRecvPacketNum += 2;
    }
    else
    {
        m_fDelay = m_fDelay + fDelay;
        m_nRecvPacketNum++;
    }
}

UINT32 CNetStatusEvaluate::GetSRssrc()
{
    return m_cRBParse.GetSRssrc();
}

UINT32 CNetStatusEvaluate::GetNetStatus()
{
    //������ʱΪ0ʱ��������RR����LSR��DLSRΪ�㣬�޷�������״����������
    if (m_fDelay > -0.001 && m_fDelay < 0.001)
    {
        return eNetLevelUnkown;
    }

    if (0 == m_nRecvPacketNum)
    {
        return eNetLevelUnkown;
    }

    if (m_fDelay / m_nRecvPacketNum < LEVEL_IDLE_TIME)
    {
        return eNetIdle;
    }

    if (m_fDelay / m_nRecvPacketNum > LEVEL_BUSY_TIME)
    {
        return eNetBusy;
    }

    return eNetNormal;
}

void CNetStatusEvaluate::SetLastAdjustTime(UINT32 nLastTime)
{
    m_nLastTime = nLastTime;
}

UINT32 CNetStatusEvaluate::GetLastAdjustTime()
{
    return m_nLastTime;
}

void CNetStatusEvaluate::Reset()
{
    m_fDelay = 0.0;
    m_nRecvPacketNum = 0;
}

bool CNetStatusEvaluate::IsLost()
{
    float fFraction = m_cRBParse.GetFraction();

    if (fFraction > -0.001 && fFraction < 0.001)
    {
        return false;
    }
    else
    {
        return true;
    }
}

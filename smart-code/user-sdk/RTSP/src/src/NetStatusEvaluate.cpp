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

//丢包率说明:自从前一SR包或RR包发射以来,从SSRC_n传来的RTP数据包的损失比例,
//以固定点小数的形式表示,小数点在此域的左侧,等于将损失比例乘256后取整数部分
//.该值定义为损失包数被期望接收的包数除.
bool CRBParse::IsSequential()
{
    float fFraction = 0.0;

    //RR包未计算丢包率或为丢包，都认为是连续的
    if (0 == m_nFraction)
    {
        return true;
    }

    fFraction = ((float)(m_nLost - m_nPrevLost)) / ((float)(m_nLastSeq - m_nPrevLastSeq));

    //通过比较RR包中的丢包率与计算出的丢包率来判断是否rtcp包是不是连续的
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
    float fDelay = 0.0;//网络延时，毫秒为单位
    float fLsrTime = 0.0;//上一SR包发送时刻，毫秒为单位
    float fArrivalTime = 0.0;//RR包接收时刻，毫秒为单位
    float fDlsr = 0.0;//离接收上一SR包至今的时间，毫秒为单位
    UINT32 nNtpSec = 0;
    UINT32 nNtpFrac = 0;

    //如果LSR或DLSR为零，无法计算环路延时，返回
    if (0 == m_nLsr || 0 == m_nDlsr)
    {
        return 0.0;
    }

    GetNtpTs(&nNtpSec, &nNtpFrac, m_struArrivalTime.tv_sec, m_struArrivalTime.tv_usec);
    //取64位NTP中间的32位计算出对应时刻
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

    //如果RR包不连续，以丢失一个RR包，且传输时间为最大传输时间计算，尽量减少RR丢包对网络延时计算的影响
    if (!m_cRBParse.IsSequential())
    {
        m_fDelay = m_fDelay + MAX_TRANSFER_TIME + fDelay;//丢失RR包的网络延时和接收到的RR包的网络延时
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
    //网络延时为0时，可能是RR包中LSR或DLSR为零，无法对网络状况进行评估
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

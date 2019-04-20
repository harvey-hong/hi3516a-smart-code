#include <sys/time.h>
#include <stdlib.h>
#include "../inc/RTCPTimeInterval.h"


CRTCPTimeInterval::CRTCPTimeInterval()
{
    Initialize();
}

CRTCPTimeInterval::~CRTCPTimeInterval()
{
    Initialize();
}

void CRTCPTimeInterval::Initialize()
{
    m_nBandWidth = UINT32(RTP_DEFAULTSESSIONBANDWIDTH * RTCP_DEFAULTBANDWIDTHFRACTION);
    m_fSenderFraction = RTCP_DEFAULTSENDERFRACTION;
    m_dMinInterval = RTCP_DEFAULTMININTERVAL;
    m_bUseHalfAtStartup = true;
    m_HeaderOverHead = 20;
    m_AvgrtcpPackSize = 20 + 8 + 20;
    m_bHasSentrtcp = false;
    m_nMemberCount = 0;
    m_bFirstCall = true;
    m_dPrevrtcpTime = 0.0;
    m_dNextrtcpTime = 0.0;
}

void CRTCPTimeInterval::SetBandWidth(UINT32 bandwidth)
{
    m_nBandWidth = bandwidth;
}

bool CRTCPTimeInterval::SetSenderFraction(float senderfraction)
{
    if (senderfraction < 0.0 || senderfraction > 1.0)
    {
        return false;
    }

    m_fSenderFraction = senderfraction;
    return true;
}

bool CRTCPTimeInterval::SetMinInterval(double mininterval)
{
    if (mininterval < RTCPSCHED_MININTERVAL)
    {
        return false;
    }

    m_dMinInterval = mininterval;
    return true;
}

void CRTCPTimeInterval::SetUseHalfAtStartup(bool usehalfatstartup)
{
    m_bUseHalfAtStartup = usehalfatstartup;
}

void CRTCPTimeInterval::SetHeaderOverhead(size_t numbytes)
{
    m_HeaderOverHead = numbytes;
}

void CRTCPTimeInterval::SetMemberCount(UINT32 membercount)
{
    m_nMemberCount = membercount;
}

void CRTCPTimeInterval::SetHasSentrtcp(bool hassentrtcp)
{
    m_bHasSentrtcp = hassentrtcp;
}

bool CRTCPTimeInterval::GetHasSentrtcp()
{
    return m_bHasSentrtcp;
}

void CRTCPTimeInterval::CalculateAvgPackSize(size_t rtcppacklen)
{
    size_t packsize = m_HeaderOverHead + rtcppacklen;
    m_AvgrtcpPackSize = (size_t)((1.0 / 16.0) * ((double)packsize) + (15.0 / 16.0) * ((double)m_AvgrtcpPackSize));
}

double CRTCPTimeInterval::CalculateDeterministicInterval()
{
    int numtotal = m_nMemberCount;

    // Try to avoid division by zero:
    if (numtotal == 0)
    {
        numtotal++;
    }

    double sfraction = ((double)1) / ((double)numtotal);
    double C, n;

    if (sfraction <= m_fSenderFraction)
    {
        C = ((double)m_AvgrtcpPackSize) / (m_fSenderFraction * m_nBandWidth);
        n = (double)1;
    }
    else
    {
        C = ((double)m_AvgrtcpPackSize) / m_nBandWidth;
        n = (double)numtotal;
    }

    double tmin = m_dMinInterval;

    if (!m_bHasSentrtcp && m_bUseHalfAtStartup)
    {
        tmin /= 2.0;
    }

    double ntimesC = n * C;
    return (tmin > ntimesC) ? tmin : ntimesC;
}

double CRTCPTimeInterval::CalculateTransmissionInterval()
{
    double deterministicInterval = CalculateDeterministicInterval();
    double random;
    srand((int)time(0));
    random = ((double)rand()) / ((double)RAND_MAX + 1.0) + 0.5; // gives random value between 0.5 and 1.5
    return (deterministicInterval * random) / 1.21828;
}

bool CRTCPTimeInterval::IsTime()
{
    if (m_bFirstCall)
    {
        m_bFirstCall = false;
        m_dPrevrtcpTime = CurrentTime();
        CalculateNextRTCPTime();
        return false;
    }

    double dCurrentTime = CurrentTime();

    if (dCurrentTime < m_dNextrtcpTime) // timer has not yet expired
    {
        return false;
    }

    double dCheckTime = CalculateTransmissionInterval();
    dCheckTime += m_dPrevrtcpTime;

    if (dCheckTime <= dCurrentTime) // Okay
    {
        m_dPrevrtcpTime = dCurrentTime;
        CalculateNextRTCPTime();
        return true;
    }

    m_dNextrtcpTime = dCheckTime;
    return false;
}

void CRTCPTimeInterval::CalculateNextRTCPTime()
{
    m_dNextrtcpTime = CurrentTime();
    m_dNextrtcpTime += CalculateTransmissionInterval();
}

double CRTCPTimeInterval::CurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000);
}

double CRTCPTimeInterval::GetTransmissionDelay()
{
    if (m_bFirstCall)
    {
        m_bFirstCall = false;
        m_dPrevrtcpTime = CurrentTime();
        CalculateNextRTCPTime();
    }

    double dCurrentTime = CurrentTime();

    if (dCurrentTime > m_dNextrtcpTime) // packet should be sent
    {
        return 0.0;
    }

    double dDelay = m_dNextrtcpTime;
    dDelay -= dCurrentTime;
    return dDelay;
}

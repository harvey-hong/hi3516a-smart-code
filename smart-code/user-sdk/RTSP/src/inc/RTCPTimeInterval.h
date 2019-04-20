#ifndef RTCPTIMEINTERVAL_H
#define RTCPTIMEINTERVAL_H

#include "BasicTypes.h"

#define RTCP_DEFAULTSENDERFRACTION                  0.25

#define RTCP_DEFAULTMININTERVAL                     5.0

#define RTCPSCHED_MININTERVAL                       1.0

#define RTP_DEFAULTSESSIONBANDWIDTH                 10000.0

#define RTCP_DEFAULTBANDWIDTHFRACTION                   0.05


//This class calculates the appropriate time interval of the RTCP packets to be sent.
class CRTCPTimeInterval
{
public:
    CRTCPTimeInterval();
    ~CRTCPTimeInterval();

    void Initialize();

    //Set band width.
    void SetBandWidth(UINT32 bandwidth);

    //Set sender fraction.
    bool SetSenderFraction(float senderfraction);

    //Set minimum interval.
    bool SetMinInterval(double mininterval);

    //Set the flag of use or not use half at startup.
    void SetUseHalfAtStartup(bool usehalfatstartup);

    //Set the header overhead from underlying protocols (for example UDP and IP) to numbytes.
    void SetHeaderOverhead(size_t numbytes);

    //Set the flag of has or not sent rtcp packets.
    void SetHasSentrtcp(bool hassentrtcp);

    //Get the flag of has or not sent rtcp packets.
    bool GetHasSentrtcp();

    //Set the member count of the session.
    void SetMemberCount(UINT32 membercount);

    //Calculates the avg packets size.
    void CalculateAvgPackSize(size_t rtcppacklen);

    //This function returns true if it's time to send an RTCP packet and false otherwise.
    bool IsTime();

    //Get the transmission delay.
    double GetTransmissionDelay();

private:
    //Calculates the deterministic interval at this time.
    double CalculateDeterministicInterval();

    //Get the current time.
    double CurrentTime();

    //Calculates the time at which the next RTCP packet to be sent.
    void CalculateNextRTCPTime();

    //Calculates the transmission interval at this time.
    double CalculateTransmissionInterval();

    UINT32 m_nBandWidth;
    float m_fSenderFraction;
    double m_dMinInterval;
    bool m_bUseHalfAtStartup;
    size_t m_HeaderOverHead;
    size_t m_AvgrtcpPackSize;
    bool m_bHasSentrtcp;
    UINT32 m_nMemberCount;
    bool m_bFirstCall;
    double m_dPrevrtcpTime;
    double m_dNextrtcpTime;
};

#endif // RTCPTIMEINTERVAL_H


#ifndef _NET_STATUS_EVALUATE_H
#define _NET_STATUS_EVALUATE_H

#include "InternalCommon.h"
#include "RtcpServer.h"

#define MAX_TRANSFER_TIME           (1000.0)                            //RTCP包最大传输时间
//网络状态级别，RTCP包传输时间处于300毫秒以下为网络空闲，需增大码流，700毫秒以上为网络繁忙，需减小码流，300毫秒到700毫秒之间则维持码流
#define LEVEL_IDLE_TIME             (300.0)
#define LEVEL_BUSY_TIME             (700.0)
typedef enum eNetLevel
{
    eNetLevelUnkown                 = 0,
    eNetIdle,
    eNetBusy,
    eNetNormal
};

//分析Report Block

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
    //判断此rtcp包与上次接收的rtcp包是否连续
    bool IsSequential();
    UINT32 GetJitter()
    {
        return m_nJitter;
    }
    //时延
    float GetDelay();

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRBParse);

private:
    void Initialize();
private:
    UINT32 m_nSRssrc;                               //SR的ssrc
    UINT32 m_nFraction;                             //丢包率
    UINT32 m_nLost;                                 //总丢包数
    UINT32 m_nLastSeq;                              //最大包数
    UINT32 m_nPrevLost;                             //上次总丢包数
    UINT32 m_nPrevLastSeq;                          //上次最大包数
    UINT32 m_nJitter;                               //抖动
    UINT32 m_nLsr;                                  //上一个发送报文发送时间
    UINT32 m_nDlsr;                                 //从收到上一个发送报文到发送此接收报告块之间的延时
    struct timeval  m_struArrivalTime;              //SR报文到达时刻
};

/* 判断网络带宽一般有两种方法：一是通过丢包率；二是通过RTCP包循环一圈的时间,但丢包率由于以下原因往往不能正确反映实现带宽的情况：
一是由于UDP包的接收顺序不能保证，接收到的数据包可能多于发送的数据包例如复制数据包，造成计算的丢包率不能正确反映网络带宽；
另一个问题是RTCP的数据包可能丢失，如果发送方RTCP发送汇报包丢失，则接收方接收数据包计数不能正确清零，如接收方RTCP接收汇报包丢失，则发送方不能得到丢包率，因此也不能正确反映网络带宽。
因此一般采用RTCP包循环一圈的时间来判断网络带宽。但是RTCP包循环一圈的时间不能准确反映网络带宽，我们通过一些措施使之尽量准确：
一是使用多个RTCP包的传输时间的平均值判断网络带宽，尽量避免网络的抖动情况，在这里一分钟进行一次调整；
二是设置最大传输时间，解决丢失RTCP包或网络突然发生抖动时对计算循环时间的平均值造成的影响。
注：由于对vlc发送的RR包分析出的网络延时在负几毫秒到正几毫秒之间，不能正确反映网络状况，在这里针对丢包来进行如下处理:
一是如果发生丢包，则立即减小码流；
二是连续30秒未丢包，则增大码流。
*/

class CNetStatusEvaluate
{
public:
    CNetStatusEvaluate();
    virtual ~CNetStatusEvaluate();

    void SetReportBlock(RTCPReportBlock *pReportBlock, struct timeval *pArrivalTime);
    UINT32 GetSRssrc();
    //获取上次调整码流时间
    UINT32 GetLastAdjustTime();
    //设置上次调整码流时间
    void SetLastAdjustTime(UINT32 nLastTime);
    //获取网络状况
    UINT32 GetNetStatus();
    //重置网络延时和包数
    void Reset();
    //是否发生丢包
    bool IsLost();
protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CNetStatusEvaluate);
private:
    void Initialize();
    void ComputeDelay();
private:
    float  m_fDelay;                                //网络延时,以毫秒为单位
    UINT32 m_nLastTime;                             //最近一次调整码流时间
    UINT32 m_nRecvPacketNum;                        //收到的RR包数
    CRBParse m_cRBParse;                            //解析Report Block
};

#endif

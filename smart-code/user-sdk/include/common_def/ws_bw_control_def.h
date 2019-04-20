#ifndef _WS_BW_CONTROL_DEF_H_
#define _WS_BW_CONTROL_DEF_H_

#include "HieServer_Common.h"
#include "ws_comm_debug.h"
#include "ws_comm_av.h"
#include "ws_comm_data.h"

using namespace ws_soft;

enum eBWControlType
{
    eBWControlTypeBegin        = 0,
    eBWControlRoute,    //以路由为单位进行调整
    eBWControlTerminal,//以终端为单位进行调整
    eBWControlClient,//以客户端为单位进行调整
    eBWControlTypeEnd,
};

enum eBWTaskType
{
    eBWTaskTypeBegin        = 0,
    eBWTaskSpeedAuto,
    eBWTaskSpeedManual,
    eBWTaskTypeEnd,
};

typedef struct _stream_info
{
    eProtocolID		protocol;
    DWORD           dwMediaSessionID;//!<媒体会话ID
    char            cRouteIP[IP_ADDRESS_LEN];            //路由WAN口IP地址；    // 局域网为0
    char            cRouteMAC[MAC_ADDRESS_LEN];      //路由WAN口MAC地址；   // 局域网为0
    char            cTeminalIP[IP_ADDRESS_LEN];             //终端IP地址；// 一个终端上可能有多个客户端
    char            cTeminalMAC[MAC_ADDRESS_LEN];       //终端MAC地址
    int                     iClientID;                      //客户端ID；    // 登录用户ID，设备层分配的ID
    eBWTaskType         BWTaskType;     //任务类型；// 低带宽协议自动调整还是用户手工调整
    int                     iVideoChannel;              //任务请求通道号；              // 视频通道号
    bool                bSameRoute;           //为真代表是同一个路由
    eMediaStreamType streamType;        //实时流、历史流、语音流
    ws_venc_str_type    streamVencType;//主码流还是子码流
} StreamInfo;

typedef struct _BWLostInfo   //客户反馈丢包信息
{
    char                cDeviceID[48];//设备UID
    DWORD              dwMediaSessionID;             //任务请求流的会话ID；
    int                     iRcvPacket;            //当前统计接收总包数；
    int                     iLostPacket;            //当前统计丢失总包数；
} BWLostInfo;

#define MAX_BW_LOST_LOG_COUNT (10)
#define MAX_MEDIA_SESSION (128 + 128 + 1)
#endif  /*#ifndef _WS_BW_CONTROL_DEF_H_*/

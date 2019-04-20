#ifndef _WS_REMOTE_AGENT_DEF_H_
#define _WS_REMOTE_AGENT_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"
#include "ws_comm_sys.h"

#include "ws_comm_av.h"
//add by qqy,start at 2016-07-26 18:47:29
#include "ws_comm_data.h"
#include "ws_ptz_def.h"
//add by qqy,end at 2016-07-26 18:47:31
#include "ws_platform_def.h"  //add by qqy, at 2016-09-06 10:07:45

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

const WS_U32  MAX_FRAME_INTERVAL_TIME  = 10; //add by qqy, at 2016-05-26 11:59:33

typedef enum
{
    WS_CONNECT_DISABLE, //不连接
    WS_CONNECT_AUTO,    //自动连接
    WS_CONNECT_CONFIRM, //指定连接
} ws_connect_mode;

typedef enum
{
    WS_FAMILY_VERSION=0,    //家用版本
    WS_PRO_VERSION, //专业版本
} ws_version;
//add by khs 2017.3.24
typedef struct
{
    WS_CHAR usr_name[ws_utility::WS_NVR_MAX_USR_NAME_LEN + 1];
    WS_CHAR password[ws_utility::WS_NVR_MAX_USR_PASSWD_LEN + 1];

    WS_CHAR ipv4[ws_utility::WS_USER_DOMAIN_NAME_LEN];//change by khs 2017.3.28
    WS_CHAR ipv6[ws_utility::WS_NVR_IPV6_STRING_LEN];
    WS_CHAR mac[ws_utility::WS_NVR_MAC_STRING_LEN];

    ws_connect_mode             connect_mode;
    ws_utility::ws_connet_protocol protocol;    //连接协议
    WS_U32                      cmd_port;
    WS_U32                      media_port;
    WS_U32                      http_port;
    WS_U32                      sub_ch; //连接哪个通道的数据，为DVR接入预留
    ws_version                  version;// add by khs 2017.3.24
    WS_BOOL                     bEnable;//channnel enable/disable  add by khs 2017.3.21 
} ws_connet_config;

typedef struct
{
    ws_connet_config    config;
} ws_connet_rule;

typedef struct
{
    WS_CHAR soft_version[32];
    WS_CHAR serial_no[48];
} ws_connect_dev_info;

typedef enum
{
    WS_AGENT_IDEL,                      //未启用
    WS_AGENT_CONNECTING,         //连接中
    WS_AGENT_CONNECTED,           //已连接
    WS_AGENT_DISCONNECTING,     //正在断开
    WS_AGENT_DISCONNECTED,     //已断开
    WS_AGENT_CONNECT_PROTECTED,     //保护状态，上层添加了任务，执行状态未知
} ws_agent_ch_state;



typedef enum
{
    ISP_BRIGHT = 0x03,  //亮度
    ISP_SHARP = 0x36,   //清晰度
    ISP_REV = 0x35, //行场翻转
    ISP_XDR = 0x0C,//数字宽动态
    ISP_DNIGHT = 0x12, //日页模式
    ISP_DNR = 0x39,//降噪
    ISP_SENS = 0x0E,//帧累计
    ISP_DZOOM = 0x30,//电子放大
    ISP_CROSS = 0x3a, //十字线
    ISP_WB = 0x10,//白平衡
    ISP_RGAIN = 0x13,//红增益
    ISP_BGAIN = 0x14,//蓝增益
    ISP_BLC_AREA = 0x05,//背光区域
    ISP_BLC = 0x04,//区域背光补偿
    ISP_PEAK = 0x0A,//峰值
    ISP_ECLIPSE = 0x0B,//日蚀 强光翻转
    ISP_EXPORT = 0x01,//曝光
    ISP_SHUTTER = 0x02,//快门速度
    ISP_AGC = 0x0D,//自动增益
    ISP_CONTRAST = 0x40,//对比度
    ISP_SATURATION = 0x41,//饱和度
    ISP_HUE = 0x42,//色度
    ISP_GAMMA = 0x45,
    ISP_SHADE = 0x46,//阴影矫正
    ISP_BAD = 0x47, //坏点矫正
    ISP_DIS = 0x48,//数字去抖
    ISP_FOG = 0x49,//数字去雾
    ISP_LENS_CORRE = 0x4a,//镜头矫正
    ISP_APERTURE_TYPE = 0x4b,//光圈类型
    ISP_AE_PRIORITY = 0x4c,//自动曝光优先级

    ISP_RECOVER_IMAGE = 0x4D,//恢复图像参数
    ISP_RECOVER_EXPOSURE = 0x4E,//恢复曝光参数
} ws_isp_type;

typedef enum
{
    DN_AUTO,
    DN_DAY,
    DN_NIGHT,
    DN_EXIT,
} ws_daynight_type;

typedef enum
{
    DNR_OFF,
    DNR_2D,
    DNR_3D,
    DNR_2_AND_3D,
} ws_dnr_type;

typedef enum
{
    REV_OFF,
    REV_H_FLIP,
    REV_V_FLIP,
    REV_H_AND_V_FLIP,
} ws_rev_type;

typedef struct
{
    int bright;             //亮度
    int contrast;           //对比度
    int saturation;         //饱和度
    int hue;                //色调
    int acutance;           //锐度

    WS_BOOL xdr;                    //数字宽动态
    ws_daynight_type  dn_type;      //昼夜切换
    ws_dnr_type      dnr_type;      //数字降噪
    ws_rev_type         rev_type;       //图像翻转
    int                 gamma_line; //gamma翻转

    WS_BOOL     shade;          //阴影矫正
    WS_BOOL     bad;                //坏点矫正
    WS_BOOL     dis;                //数字去抖
    WS_BOOL     fog;                //数字去雾
    WS_BOOL     lens_correction;        //畸形矫正

    int         amplification;          //数字放大
} ws_isp_image;

typedef enum
{
    AGC_OFF,
    AGC_LOW,
    AGC_MED,
    AGC_HIG,
} ws_agc_rank;


typedef enum
{
    FRAME_OFF,
    FRAME_LOW,
    FRAME_MED,
    FRAME_HIG,
} ws_frame_rank;

typedef struct
{
    int         ex_type;            //0自动曝光 1:手动曝光
    WS_BOOL         aperture;           //光圈类型
    WS_BOOL         agc_enable;     //曝光优先级
    int             agc_rank;
    int             frame_rank;
    int                 shutter_rank;

    int         wb_enable;      //白平衡模式 0 :自动 2:手动
    int                 read_gain;
    int                 blue_gain;
} ws_isp_exposure;


typedef enum eRemoteTaskType
{
    WS_REMOTE_TASK_TYPE_UNKNOW = 0,
    WS_REMOTE_TASK_CHANNEL_CONNECT,
    WS_REMOTE_TASK_CHANNEL_DISCONNECT,
    WS_REMOTE_TASK_CHANNEL_NEW_CONNECT, 

    // 向报警服务器发送订阅消息    
    WS_REMOTE_TASK_NOTIFY_DEVICE_CONNECT,

    // 向报警服务器发送取消订阅，目前没有被调用
    WS_REMOTE_TASK_NOTIFY_DEVICE_DISCONNECT,

    // 没有被调用
    WS_REMOTE_TASK_SUBSCRIBE_ALARM,//5

    // 没有被调用
    WS_REMOTE_TASK_UNSUBSCRIBE_ALARM,

    WS_REMOTE_TASK_GET_IPC_ALL_PARA,//7
    WS_REMOTE_TASK_GET_IPC_INFO,
    WS_REMOTE_TASK_GET_ALL_ENC_PARA,
    WS_REMOTE_TASK_GET_ISP_PARA,
    WS_REMOTE_TASK_GET_DEFAULT_ISP_PARA, 
    WS_REMOTE_TASK_GET_PTZ_PARA,
    WS_REMOTE_TASK_GET_MD_PARA,

    WS_REMOTE_TASK_GET_OSD_AREA,
    WS_REMOTE_TASK_GET_OSD_CH_NAME,

    WS_REMOTE_TASK_SET_PTZ_PARA,
    WS_REMOTE_TASK_SET_PTZ_SPEED,
    WS_REMOTE_TASK_SET_PTZ_CMD,
    WS_REMOTE_TASK_SET_ENC_PARA,
    WS_REMOTE_TASK_SET_ENC_DEFAULT,
    WS_REMOTE_TASK_SET_ISP_PARA,
    WS_REMOTE_TASK_SET_DEFAULT_ISP_PARA,
    WS_REMOTE_TASK_SET_DEFAULT_EXPOSURE_PARA,
    WS_REMOTE_TASK_SET_MD_PARA,
    WS_REMOTE_TASK_SET_HTTP_PORT,

    WS_REMOTE_TASK_SET_OSD_AREA,
    WS_REMOTE_TASK_SET_OSD_CH_NAME,

    WS_REMOTE_TASK_SYNC_TIME,//20
    WS_REMOTE_TASK_DOWNLOAD_CFG,
    WS_REMOTE_TASK_UPLOAD_CFG,
    WS_REMOTE_TASK_UPLOAD_SYS,
    WS_REMOTE_TASK_REBOOT,

    WS_REMOTE_TASK_REQUEST_SNAP_TASK_ID,    //24
    WS_REMOTE_TASK_INQUIRY_SNAP_STATUS,
    WS_REMOTE_TASK_GET_SNAP_FILE,

    WS_REMOTE_TASK_LOAD_PTZ,
    WS_REMOTE_TASK_GET_ALARM_INFO,	
    WS_REMOTE_TASK_UPGRADE_STATUS, 

    WS_REMOTE_TASK_GET_DEF_PARA,//获取默认的ISP、ENC、OSD、PTZ、MD
    WS_REMOTE_TASK_SET_DEF_ENC,
    WS_REMOTE_TASK_SET_DEF_OSD,
    WS_REMOTE_TASK_SET_DEF_PTZ,
    WS_REMOTE_TASK_SET_DEF_MD,
} ws_remote_task_type;

typedef union
{
    struct
    {
        ws_venc_str_type        str_type;
        ws_enc_para             enc_para;
    } enc_para;
    struct
    {
        ws_isp_type             set_type;
        int                     set_val;
    } isp_para;
    struct
    {
        char               *cmd_string;
        int                     cmd_length;
    } ptz_cmd;
    struct
    {
        char               *filebuf;
        int                     filesize;
    } upgrade_file;
    struct
    {
        int                     snap_task_id;
        time_t              event_time;
        ws_utility::ws_snap_file_trig_type trig_type;
        char file_name[ws_utility::WS_MAX_FILE_NAME_LEN];//绝对路径名
        WS_BOOL bRepeat; //add by qqy, at 2017-05-10 09:12:27
    } snap_config;

    struct
    {
        ws_osd_type         dp_tp;
        ws_location_type    loc_tp;
    } osd_position_config;

    struct
    {
        char ch_name[ws_utility::WS_MAX_OSD_NAME_LENTH];
    } osd_ch_name;

    ws_connet_config            connet_config;
    ws_md_arr               md_arr;
    ws_ptz_ctl_info         ptz_ctl_info;
    WS_S32                  http_port;
} ws_remote_task_data;

typedef struct ws_remote_task_node
{
    WS_U32                  channel;
    WS_U32                  iTaskId; 
    ws_remote_task_type     eTaskType;
    ws_remote_task_data     taskData;
    ws_remote_task_node        *pre;
    ws_remote_task_node        *next;
} ws_remote_task_node;

#define LOOP_IP             ("127.0.0.0")
#define INVALID_IP          ("0.0.0.0")
#define BROADCAST_IP        ("255.255.255.255")
#define INVALID2_IP        ("1.1.1.1")

#define MIN_PORT                (0)
#define MAX_PORT            (65535)

const unsigned int TRY_CONNECT_TIMES = 2; 

typedef enum
{
    WS_REMOTE_TASK_STATE_IDEL,
    WS_REMOTE_TASK_STATE_NO_RUN,
    WS_REMOTE_TASK_STATE_RUNNING,
    WS_REMOTE_TASK_STATE_SUCCESS,
    WS_REMOTE_TASK_STATE_FAIL,
} ws_remote_task_state;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_MODEL_DEF_H_

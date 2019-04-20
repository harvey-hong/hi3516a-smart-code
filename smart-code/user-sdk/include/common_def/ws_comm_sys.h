#ifndef _WS_COMM_SYS_H_
#define _WS_COMM_SYS_H_

#include <time.h>
#include <stdio.h>

#include "ws_common.h"
#include "ws_comm_type.h"

#ifdef __cplusplus
extern "C" {
namespace ws_utility 
{
#endif

typedef enum
{
    WS_DEVICE_UNKNOW,
    WS_DEVICE_NVR,
    WS_DEVICE_IPC,
    WS_ANOYMOUS_ONVIF_IPC,

    WS_DEVICE_SDI_DVR = 100,

    WS_DEVICE_DEC_BOX = 200,
    
    WS_DEVICE_HVR = 300,	
} ws_device_type;

typedef enum
{
    WS_PROTOCOL_PRIVITE,    
    WS_PROTOCOL_ONVIF,
} ws_connet_protocol;

typedef enum
{
    WS_RECFILE_FORMAT_UNKNOW,
    WS_RECFILE_FORMAT_PRIVATE,  
    WS_RECFILE_FORMAT_AVI,
    WS_RECFILE_FORMAT_ASF,
} ws_recfile_format;   

typedef struct
{
    WS_U32  base_version;
    WS_U32  minor_version;
    WS_U32  sub_version;
} ws_soft_version;

typedef enum
{
    WS_RECFILE_HARD_DISK,
    WS_RECFILE_USB_DISK,
} ws_recfile_disk_format;


typedef struct
{
    ws_device_type dev_type;
    char    product_name[32];
    char    serial_no[36];     

    // 视频通道总数，包括模拟通道与数字通道
    WS_U32      video_ch_num;   
    // 支持回放通道个数
    WS_U32      pb_ch_num;  

    // 支持传感器通道个数
    WS_U32  alarm_in_num;   

    // 支持报警器通道个数
    WS_U32  alarm_out_num;  

    WS_BOOL support_speaking;  

    // 支持移动侦测检测区域个数
    int     max_md_rect_num;   

    int     sata_slot_num;  

    ws_soft_version base_version; 
    ws_soft_version soft_version;  

    ws_soft_version hard_version; 
    char    date_buf[12];       
    char    description[48];     

    int dev_board_id;   

    int audio_ch_num;  

    int main_enc_size;  
    WS_U32 main_max_bps; 
    WS_U32 main_min_bps;  

    int sub_enc_size;
    WS_U32 sub_max_bps;
    WS_U32 sub_min_bps;

    WS_U32  audio_out_num;  

    WS_BOOL dev_type_for_720p;  

    ws_recfile_format rec_format;

    ws_recfile_disk_format rec_disk_format;
    WS_BOOL support_wifi;

    // 没有人使用它
    WS_BOOL is_slave_device;

    // 支持图片播放通道个数    
    WS_U32	  pb_pic_ch_num;
    WS_U32   phy_ch_mask[WS_NVR_MAX_MASK_NUM];		
    WS_U32   phy_ch_num;
    WS_U32   ipc_ch_mask[WS_NVR_MAX_MASK_NUM];		
    WS_U32   ipc_ch_num;	
    int           reserverd[18];
} ws_device_capability;

typedef struct
{
    char           res_name[32];
    int             width ;
    int             height;
} sm_status_resol;

typedef struct
{
    const char *name;  
    int  width;         
    int  height;        
} ws_resol_info;

typedef struct
{
    // 界面需要知道支持哪些分辨率
    int                  support_num;  
    ws_resol_info   *info;  
    const char *cur_resol_name; 
    int cur_resol_width;
    int cur_resol_height;
} ws_support_resol;

typedef enum
{
    WS_LOGO_UNKNOW,
    WS_LOGO_VIDEO_LOST,    
    WS_LOGO_PB_NO_FILE,     
    WS_LOGO_LOCK_OPS,       
    WS_LOGO_COMPANY,        
} ws_logo_type;

typedef enum
{
    WS_ALARM_IN_UNKNOW,
    WS_ALARM_IN_OPEN,  
    WS_ALARM_IN_CLOSE, 
} ws_ai_check_type;

 //Modified by qqy,start at 2017-01-19 11:25:55
typedef enum
{
    WS_ALARM_POS_UNKNOW,
    WS_ALARM_POS_ON_CHIP,
    WS_ALARM_POS_OFF_CHIP,
} ws_alarm_pos;

typedef struct
{
    WS_U32 ai_ch;
    char ai_name[64];
    ws_ai_check_type ai_type;
    ws_alarm_pos   ai_pos;
} ws_ai_config;

typedef enum
{
    WS_ALARM_OUT_TYPE_UNKNOW,
    WS_ALARM_OUT_TYPE_TTL,  //电平
    WS_ALARM_OUT_TYPE_FREQ,  //频率
} ws_ao_type;

typedef struct
{
    WS_U32 ao_ch;
    char ao_name[64];
    ws_ao_type ao_type;
    ws_alarm_pos   ao_pos;
    WS_U32 ao_hold_time;//msecs
} ws_ao_config;
 //Modified by qqy,end at 2017-01-19 11:25:58


typedef struct
{
    WS_BOOL is_24h;
    WS_BOOL is_syncrmt;
} ws_time_fmt_cfg;     

typedef struct
{
    WS_U32 volume_strength;
    WS_BOOL is_mute;
} ws_volume_cfg;    

typedef struct
{
    WS_U16  year;  
    WS_U16  month; 
    WS_U16  day;   

    WS_U16  hour;
    WS_U16  min;
    WS_U16  sec;
    WS_U16  wday; 
} ws_time_struct;

typedef enum
{
    WS_REC_FILE_TRIG_NONE,              
    WS_REC_FILE_TRIG_BY_TIMER   = 0x01,  
    WS_REC_FILE_TRIG_BY_MD      = 0x02,    
    WS_REC_FILE_TRIG_BY_AI      = 0x04,     
    WS_REC_FILE_TRIG_BY_MANUAL  = 0x08, 
    WS_REC_FILE_TRIG_BY_EXCEPTION   = 0x10, 
} ws_rec_file_trig_type;

typedef enum
{
    WS_SNAP_FILE_TRIG_NONE,            
    WS_SNAP_FILE_TRIG_BY_TIMER  = 0x01, 
    WS_SNAP_FILE_TRIG_BY_MD     = 0x02,   
    WS_SNAP_FILE_TRIG_BY_AI     = 0x04,    
    WS_SNAP_FILE_TRIG_BY_MANUAL = 0x08, 
    WS_SNAP_FILE_TRIG_BY_EXCEPTION  = 0x10,  
    WS_SNAP_DILE_TRIG_BY_LINKAGE	= 0x20,	
} ws_snap_file_trig_type;

typedef enum
{
    WS_TIME_FORMAT_UNKNOW,
    WS_YYYY_MM_DD_HH_MM_SS,
    WS_MM_DD_YYYY_HH_MM_SS,
} ws_sys_time_format;

// AVIOCTRL Event Type
typedef enum
{
    WS_AVIOCTRL_EVENT_ALL                  = 0x00, // all event type(general APP-->IPCamera)
    WS_AVIOCTRL_EVENT_MOTIONDECT           = 0x01, // motion detect start//==s==
    WS_AVIOCTRL_EVENT_VIDEOLOST            = 0x02, // video lost alarm
    WS_AVIOCTRL_EVENT_IOALARM              = 0x04, // io alarmin start //---s--

    WS_AVIOCTRL_EVENT_MOTIONPASS           = 0x08, // motion detect end  //==e==
    WS_AVIOCTRL_EVENT_VIDEORESUME          = 0x10, // video resume
    WS_AVIOCTRL_EVENT_IOALARMPASS          = 0x20, // IO alarmin end   //---e--

    WS_AVIOCTRL_EVENT_EXPT_REBOOT          = 0x40, // system exception reboot
    WS_AVIOCTRL_EVENT_SDFAULT              = 0x80, // sd record exception
} ws_enum_eventtype;

typedef struct
{
	time_t event_time;  
	ws_enum_eventtype event_type;   
	int event_recoed; 
}ws_event_list;

typedef struct
{
	int event_count; 
	ws_event_list  *list; 
}ws_stEvent;

typedef enum
{
    WS_EVENT_SERIAL_TYPE_NNKNOW,
    WS_EVENT_SERIAL_MD,
    WS_EVENT_SERIAL_AI,     
    WS_EVENT_SERIAL_VLOST, 
    WS_EVENT_SERIAL_NO_DISK,
    WS_EVENT_SERIAL_DISK_ERROR,
    WS_EVENT_SERIAL_NO_SPACE,
    WS_EVENT_SERIAL_NET_ERROR,
    WS_EVENT_SERIAL_IP_CONFLICT,
} ws_event_serial_type;

typedef enum
{
    WS_RESUME_DEF_NONE = 0,
    WS_RESUME_REC_SHEDULE   = 0x1,
    WS_RESUME_NET_CFG       = 0x2,
    WS_RESUME_ALARM_CFG     = 0x4,
    WS_RESUME_SYS_CFG       = 0x8,
    WS_RESUME_CHANNEL_CFG   = 0x10,
    WS_RESUME_PPPOE_CFG     = 0x20,
    WS_RESUME_DDNS_CFG      = 0x40,
    WS_RESUME_WIFI_CFG      = 0x80,
    WS_RESUME_SMTP_CFG      = 0x100,
    WS_RESUME_EXCEPTION_CFG     = 0x200,
    WS_RESUME_OSD_CFG = 0x500,
    WS_RESUME_ENC_CFG = 0x501,
    WS_RESUME_DEF_ALL = 0xFFFFFFFF,
} ws_resume_default_type;

 //modify by qqy,start at 2017-02-15 11:14::38
typedef enum
{
    WS_RESUME_CFG_TIMER_REC,
    WS_RESUME_CFG_HOLIDAY,
    WS_RESUME_CFG_ENC,
    WS_RESUME_CFG_CHANNEL,
    WS_RESUME_CFG_OSD,
    WS_RESUME_CFG_PTZ,
    WS_RESUME_CFG_MD,
    WS_RESUME_CFG_BASE,
    WS_RESUME_CFG_TIME,
    WS_RESUME_CFG_SENSOR,
    WS_RESUME_CFG_ALARM,
    WS_RESUME_CFG_MD_LINKAGE,
    WS_RESUME_CFG_EXCEPTION,
    WS_RESUME_CFG_BASIC_NET,
    WS_RESUME_CFG_PORT,
    WS_RESUME_CFG_PPPOE,
    WS_RESUME_CFG_DDNS,
    WS_RESUME_CFG_NTP,
    WS_RESUME_CFG_EMAIL,
} ws_resume_cfg_type;
 //modify by qqy,end at 2017-02-15 11:14::38
 
typedef struct
{
    time_t last_frame_time;
    int last_frame_width;
    int last_frame_height;

    int total_frame_size;
    int total_frame_num;

    time_t last_update_time;
    char fps;
    char fps_point;
    int  kbps;
} ws_rec_real_info;


#ifdef __cplusplus
}//namespace ws_utility {//changed by mjq 2014.11.26
}//extern "C" {
#endif

#endif  //_WS_COMM_SYS_H_


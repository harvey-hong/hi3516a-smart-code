#ifndef _WS_PLATFORM_DEF_H_
#define _WS_PLATFORM_DEF_H_

#include "ws_comm_type.h"
#include "ws_common.h"

using ws_utility::WS_MAX_DEV_NAME_LENTH;
#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

#define P1080_FOR_720P_DEV_MAX_FPS 12
//add by khs 2017.11.3 start
typedef enum
{
    VDEC_PIPE_WORK_STATE_START,
    VDEC_PIPE_WORK_STATE_STOP,
    VDEC_PIPE_WORK_STATE_DIS_LV,
    VDEC_PIPE_WORK_STATE_DIS_LOGO,
    VDEC_PIPE_WORK_STATE_DIS_FILE,
    VDEC_PIPE_WORK_STATE_DIS_SNAP,
    VDEC_PIPE_WORK_STATE_END,
} Vdec_Pipe_Work_state;
//add by khs 2017.11.3 end
typedef enum
{
    PLAT_VDEC_WORK_MODE_UNKNOW,
    PLAT_VDEC_LIVE_STREAM,
    PLAT_VDEC_PB_FILE,
    PLAT_VDEC_DIS_LOGO,
    PLAT_VDEC_SNAP_PIC,
} platform_vdec_work_mode;

typedef enum
{
    PLAT_FB_COLOR_UNKNOW,
    PLAT_FB_RGB_1555,
} platform_fb_color_mode;

typedef enum
{
    PLAT_AUDIO_SYNC_NONE,   
    PLAT_AUDIO_SYNC_GRP,
    PLAT_AUDIO_SYNC_CH,
} platform_audio_sync_mode;

typedef enum
{
    PLAT_ALARM_OUT_OPEN,
    PLAT_ALARM_OUT_CLOSE,
} platform_alarm_out_ctl;

typedef struct
{
    WS_U32 channel_idx;
    platform_alarm_out_ctl ao_stat; 
}platform_alarm_out_config;

typedef enum
{
    WS_TOP_LEFT,
    WS_TOP_CENTRE,
    WS_TOP_RIGHT,
    WS_BOTTOM_LEFT,
    WS_BOTTOM_CENTRE,
    WS_BOTTOM_RIGHT,
    WS_NO_DISPLAY,
} ws_location_type;        

typedef enum
{
    WS_OSD_NAME_AREA,
    WS_OSD_TIME_AREA,
} ws_osd_type;       

#define WS_PCIV_MSG_MAXLEN      532

typedef enum
{
    WS_PCIV_MSG_MAIN_UNKNOW = 0x0,
    WS_PCIV_MSG_MAIN_COMM,
    WS_PCIV_MSG_STREAM_TRANS,
    WS_PCIV_MSG_FOR_MD_STATUS,
    WS_PCIV_MSG_FOR_ENC_PARAM,
    WS_PCIV_MSG_FOR_VIDEO_INFO,
}ws_pciv_msg_main_type;

typedef enum
{
    WS_PCIV_MSG_SUB_UNKNOW = 0x0,
    WS_PCIV_MSG_SUB_INIT_PORT,
    WS_PCIV_MSG_SUB_INIT_VB,
    WS_PCIV_MSG_SUB_INIT_VI,
    WS_PCIV_MSG_SUB_INIT_CHIP,
    WS_PCIV_MSG_SUB_INIT_LV_CH,
    WS_PCIV_MSG_SUB_START_LV_CH,
    WS_PCIV_MSG_SUB_STOP_LV_CH,
    WS_PCIV_MSG_SUB_LV_CH_ROI,
    WS_PCIV_MSG_SUB_INIT_REC_CH,
    WS_PCIV_MSG_SUB_START_AUX,
    WS_PCIV_MSG_SUB_STOP_AUX,
    WS_PCIV_MSG_SUB_ENABLE_AUX,
    WS_PCIV_MSG_SUB_DISABLE_AUX,
    WS_PCIV_MSG_SUB_CFG_ENC_PARAM,
    WS_PCIV_MSG_SUB_GET_ENC_PARAM,
    WS_PCIV_MSG_SUB_GET_ENC_PARAM_ECHO,
    WS_PCIV_MSG_SUB_CREATE_POOL,
    WS_PCIV_MSG_SUB_WRITE_DONE,
    WS_PCIV_MSG_SUB_READ_DONE,
    WS_PCIV_MSG_SYNC_SYS_TIME,
    WS_PCIV_MSG_CFG_TIME_OSD,
    WS_PCIV_MSG_CFG_NAME_OSD,
    WS_PCIV_MSG_CFG_MD,
    WS_PCIV_MSG_GET_MD_STATUS,
    WS_PCIV_MSG_MD_STATUS_ECHO,
    WS_PCIV_MSG_GET_VIDEO_INFO,
    WS_PCIV_MSG_GET_VIDEO_INFO_ECHO,
    WS_PCIV_MSG_SNAP_PIC,
    WS_PCIV_MSG_SET_VPSS_PARAM,
    WS_PCIV_MSG_SUB_ECHO,
    WS_PCIV_MSG_SUB_GET_ENC_INPUT_FPS,  
    WS_PCIV_MSG_SNAP_PIC_BY_MASK,		
    WS_PCIV_MSG_CFG_TIME_TYPE_AND_STANDARD,
    WS_PCIV_MSG_CFG_LANGUAGE,
    WS_PCIV_MSG_SUB_GET_ENC_MAX_FPS,  
    WS_PCIV_MSG_SUB_CANCEL_ROI_TMP,   
     WS_PCIV_MSG_SUB_INIT_PLATFORM_OK, 
    
    WS_PCIV_MSG_SUB_INIT_VENC_CH,
    WS_PCIV_MSG_SUB_INIT_RGN_CH,
    WS_PCIV_MSG_SUB_INIT_VPSS_CH,

    WS_PCIV_MSG_SUB_TIME_DOT = 0x30, 
}ws_pciv_msg_sub_type;

typedef struct
{
    ws_pciv_msg_main_type main_type;
    ws_pciv_msg_sub_type sub_type;
}ws_pciv_msg_type;

typedef struct
{
    WS_U32  target_id;          //User Don't Fill This Data
    ws_pciv_msg_type  msg_type;
    WS_U32  msg_length;      //Not Include Message Head.

    WS_BOOL is_sync;
    WS_S32  return_val;
}ws_pciv_msg_head;

typedef struct 
{
    ws_pciv_msg_head   msg_head;
    WS_UCHAR             msg[WS_PCIV_MSG_MAXLEN];
}ws_pciv_msg;

typedef struct
{
    int language_idx;
    ws_location_type type;
} display_area;

typedef struct
{
    WS_BOOL get_data;           //
    ws_soft::ws_location_type name_type;
    ws_soft::ws_location_type time_type;
    int channel;
    int time; 
    char chn_name[ws_utility::WS_MAX_DEV_NAME_LENTH*2];
} channel_display_info;

//add by xrg 2015.03.31 end
#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_PLATFORM_DEF_H_


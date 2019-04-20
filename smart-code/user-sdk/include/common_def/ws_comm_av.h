#ifndef _WS_COMM_AV_H_
#define _WS_COMM_AV_H_

#include "ws_comm_type.h"
#include "ws_common.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef enum
{
    WS_VIDEO_UNKNOW,
    WS_VIDEO_PAL,
    WS_VIDEO_NTSC,
} ws_video_std;

typedef struct
{
    WS_S32  bright;    
    WS_S32  contrust;
    WS_S32  hue;       
    WS_S32  saturation; 
} ws_ch_color_para;

typedef enum
{
    WS_AI_STATE_UNKNOW,
    WS_AI_HAPPEN,
    WS_AI_DISAPPER,
} ws_ai_state;

typedef enum
{
    WS_VIDEO_STATE_UNKNOW, 
    WS_VIDEO_NORMAL,
    WS_VIDEO_LOST,
} ws_video_state;


typedef enum
{
    WS_VIDEO_TYPE_INPUT_UNKNOW = 0xFFFFFFFF,

    WS_VIDEO_TYPE_INPUT_1080I = 0x0,
    WS_VIDEO_TYPE_INPUT_1080I60,
    WS_VIDEO_TYPE_INPUT_1080I59,
    WS_VIDEO_TYPE_INPUT_1080I50,

    WS_VIDEO_TYPE_INPUT_1080P = 0x4,
    WS_VIDEO_TYPE_INPUT_1080P30,
    WS_VIDEO_TYPE_INPUT_1080P29,
    WS_VIDEO_TYPE_INPUT_1080P25,
    WS_VIDEO_TYPE_INPUT_1080P24,
    WS_VIDEO_TYPE_INPUT_1080P23,

    WS_VIDEO_TYPE_INPUT_720P = 0xa,
    WS_VIDEO_TYPE_INPUT_720P60,
    WS_VIDEO_TYPE_INPUT_720P59,
    WS_VIDEO_TYPE_INPUT_720P50,
    WS_VIDEO_TYPE_INPUT_720P30,
    WS_VIDEO_TYPE_INPUT_720P29,
    WS_VIDEO_TYPE_INPUT_720P25,
    WS_VIDEO_TYPE_INPUT_720P24,
    WS_VIDEO_TYPE_INPUT_720P23,
} ws_video_format;

typedef struct
{	
    	ws_video_state 		video_state;
    	ws_video_format 		video_format;
} ws_av_chip_ch_info;

typedef struct
{
    ws_av_chip_ch_info av_ch_info[_MAX_CHANNEL_NUM_];
    WS_BOOL video_is_change[_MAX_CHANNEL_NUM_];    
    WS_U32 time_count[_MAX_CHANNEL_NUM_];		
    WS_U32 vl_happent_delay_cnt;								
    WS_U32 check_vl_freq;
}ws_vlost_poll_info;

typedef enum
{
    WS_MD_STATE_UNKNOW, 
    WS_MD_HAPPEN,
    WS_MD_DISAPPER,
} ws_md_state;

typedef enum
{
    WS_ENC_SIZE_UNKNOW  = 0,
    WS_ENC_SIZE_CIF       = 0x0001,
    WS_ENC_SIZE_D1        = 0x0002,  // 4CIF == D1
    WS_ENC_SIZE_VGA      = 0x0004,
    WS_ENC_SIZE_720P    = 0x0008,
    WS_ENC_SIZE_960H    = 0x0010,
    WS_ENC_SIZE_1080P  = 0x0020,
    /* 20151120 hongzg add for 3M  4M 5M IPC suppoort start */
    WS_ENC_SIZE_3M       = 0x0040,
    WS_ENC_SIZE_4M       = 0x0080,
    WS_ENC_SIZE_5M       = 0x0100,
    /* 20151120 hongzg add for 3M  4M 5M IPC suppoort end */
} ws_enc_size;

typedef enum
{
    WS_BTS_CBR,
    WS_BTS_VBR,
} ws_bts_ctl_type;

typedef enum
{
    WS_PIC_QUALITY_NORMAL, 
    WS_PIC_QUALITY_HIGH,   
    WS_PIC_QUALITY_HIGHEST, 
} ws_pic_quality;

typedef enum
{
    WS_P_TYPE,
    WS_N_TYPE,
} ws_n_p_type;

typedef struct
{
    ws_bts_ctl_type bps_ctl;    
    ws_n_p_type     n_p_type;
    WS_U32           fps;        
    WS_U32           kbps;      
    ws_pic_quality  quality;  
    ws_enc_size     size;      
    WS_U32          support_size; 
} ws_enc_para;

typedef struct
{
    ws_enc_para para;
    WS_BOOL is_valid;
    WS_BOOL dirty;
    WS_S32 fps_change_value;
    WS_S32 dynamic_fps_change;
} ws_enc_info;

typedef enum
{
    WS_ENC_STR_UNKNOW = 0x00,
    WS_ENC_STR_MAIN = 0x01, 
    WS_ENC_STR_SUB1 = 0x02, 
    WS_ENC_STR_SUB2 = 0x04, 
    WS_ENC_STR_ALL	= 0x08,
} ws_venc_str_type;

typedef enum
{
    WS_MD_GRADE_NORMAL,
    WS_MD_GRADE_LOW,
    WS_MD_GRADE_LOWEST,

    WS_MD_GRADE_HIGH,
    WS_MD_GRADE_HIGHEST,
} ws_md_sensitivity;

typedef enum
{
    WS_VO_CSC_UNKONW = 0,
    WS_VO_CSC_MATRIX_IDENTITY,
    WS_VO_CSC_MATRIX_BT601_TO_BT709,
    WS_VO_CSC_MATRIX_BT709_TO_BT601,
    WS_VO_CSC_MATRIX_BT601_TO_RGB_PC,
    WS_VO_CSC_MATRIX_BT709_TO_RGB_PC,
    WS_VO_CSC_MATRIX_RGB_TO_BT601_PC,
    WS_VO_CSC_MATRIX_RGB_TO_BT709_PC,
} ws_color_space;

//Comments:Different Soc Has Different Limit.
//At Current For Hi3531 The Vo Dev ID From 0 to 7, Hisi3521  && Hisi3520D && Hisi3515A VO Dev ID From 0 to 2
typedef struct
{
    /*Notify That : color_space just can use VO_CSC_MATRIX_IDENTITY, VO_CSC_MATRIX_BT601_TO_BT709 ,VO_CSC_MATRIX_BT709_TO_BT601*/
    /*But When Set VO_CSC_MATRIX_BT709_TO_BT601 Hisi Api Describe VGA Can't Work Well, So We Should not Set That*/
    ws_color_space color_space;/*default: VO_CSC_MATRIX_IDENTITY, VO_CSC_MATRIX_BT601_TO_BT709(For Hisi3520D && Hisi 3515A HD)*/
    WS_U32 luminance;   /*luminance:0-100 default: 50*/
    WS_U32 contrast;      /*contrast:0-100  default: 50*/
    WS_U32 hue;              /*hue:0-100    default: 50*/
    WS_U32 satuature;   /*satuature:0-100   default: 50 or 59(For Hi3520D && Hi3515A HD))*/
} ws_vo_output_param;

//Comments:Different Soc Has Differnet Limit
//At Current For Hisi3531 The VO Dev ID From 0 to 7, Hisi3521 VO Dev ID From 0 to 2.
//Caution:For NVR 4, 8(Hisi3515A Hisi3520D) We Can't Use Adjust VGA Para, Hisi API Not Support Now.
typedef struct
{
    /*Notify That: color_sapce just can use VO_CSC_MATRIX_BT601_TO_RGB_PC, VO_CSC_MATRIX_BT709_TO_RGB_PC*/
    ws_color_space color_space;/*default:VO_CSC_MATRIX_BT601_TO_RGB_PC*/
    WS_U32 luminance;/*luminancan:0-100 default:50*/
    WS_U32 contrast;/*contrast:0-100    default:50*/
    WS_U32 hue;/*hue:0-100  default:50*/
    WS_U32 satuature;/*satuature:0-100  default:50(Hisi3531), 59(Hisi3521)*/
    WS_U32 gain; /*gain:0-63   default:10*/
} ws_vga_output_param;


typedef enum
{
    WS_VPSS_PARAM_TYPE_UNKNOW = 0,
    WS_VPSS_PARAM_FOR_PRE,
    WS_VPSS_PARAM_FOR_PLAYBACK,
} ws_vpss_param_type;
//ws_vpss_para decribe format--->Soc Type:[range] [default];
//if the soc not support one of para the format--->Soc Type:;

typedef struct
{
    WS_U32 luminance;/*Hi3521:;  Hi3531:[0-48] [32];  Hi3520D(Hi3515A):;*/
    WS_U32 contrast;/*Hi3521:;  Hi3531:[0-48] [8];  Hi3520D(Hi3515A):[0-255] [64];*/
    WS_U32 dark_enhance;/*Hi3521:;  Hi3531:[0-48] [16];  Hi3520D(Hi3515A):;*/
    WS_U32 bright_enhance;/*Hi3521:;  Hi3531:[0-48] [16];  Hi3520D(Hi3515A):;*/
    WS_U32 ie_strength;/*Hi3521:[0-8] [2];  Hi3531:[0-255] [32];  Hi3520D(Hi3515A):[0-255] [6];*/
    WS_U32 ie_sharp;/*Hi3521:[0-100] [10];  Hi3531:[0-7] [7];  Hi3520D(Hi3515A):;*/
    WS_U32 sf_strength;/*Hi3521:; Hi3531:[0-7] [3]; Hi3520D(Hi3515A):[0-255] [16];*/
    WS_U32 tf_strength;/*Hi3521:;  Hi3531:[0-15] [1];  Hi3520D(Hi3515A):[0-31] [4];*/
    WS_U32 chromat_range;/*Hi3521:; Hi3531:[0-31] [4];  Hi3520D(Hi3515A):;*/
    WS_U32  nr_window_for_tsr;/*Hi3521:;  Hi3531:[0-8] [8];  Hi3520D(Hi3515A):;*/
    WS_U32  en_sf_window;/*Hi3521:;  Hi3531:[0-4] [0];  Hi3520D(Hi3515A):;*/
} ws_vpss_param;

typedef struct
{
    ws_vpss_param_type param_type;
    ws_vpss_param vpss_param;
}ws_vpss_param_msg;
//#endif
//End By ZhangXinda Date:2014-08-20

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_COMM_AV_H_


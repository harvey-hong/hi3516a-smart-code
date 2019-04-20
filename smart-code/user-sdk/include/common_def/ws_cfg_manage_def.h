#ifndef _WS_CFG_MANAGE_DEF_H_
#define _WS_CFG_MANAGE_DEF_H_

#define WS_HI3515A_F_NVR_4_NAME     "ws_3515a_f_nvr_4"
#define WS_HI3515A_S_NVR_4_NAME     "ws_3515a_s_nvr_4"

#define WS_HI3520D_F_NVR_8_NAME     "ws_3520d_f_nvr_8"
#define WS_HI3520D_S_NVR_8_NAME     "ws_3520d_s_nvr_8"

#define WS_HI3531A_F_NVR_16_NAME    "ws_3531_f_nvr_16"
#define WS_HI3531A_S_NVR_16_NAME    "ws_3531_s_nvr_16"

#define WS_HI3531_F_1080P_DVR_4_NAME "ws_3531_f_1080p_dvr_4"
#define WS_HI3531_F_1080P_DVR_4_HVR_NAME "ws_3531_f_1080p_hvr_4"
#define WS_HI3531_F_1080P_DVR_8_NAME "ws_3531_f_1080p_dvr_8"
#define WS_HI3531_F_1080P_DVR_8_HVR_NAME "ws_3531_f_1080p_hvr_8"
#define WS_HI3531_F_1080P_DVR_16_NAME "ws_3531_f_1080p_dvr_16"

#define WS_HI3521_F_720P_DVR_4_NAME "ws_3521_f_720p_dvr_4"
#define WS_HI3521_F_720P_DVR_4_HVR_NAME "ws_3521_f_720p_hvr_4"
#define WS_HI3521_F_NVR_16_NAME "ws_3521_f_nvr_16"
#define WS_HI3535_F_NVR_16_NAME "ws_3535_f_nvr_16"
#define WS_HI3536_F_NVR_64_NAME "ws_3536_f_nvr_64"
#define WS_HI3536C_F_NVR_64_NAME "ws_3536c_f_nvr_64"
#define WS_HI3531_F_720P_DVR_8_NAME "ws_3531_f_720p_dvr_8"
#define WS_HI3531_F_720P_DVR_8_HVR_NAME "ws_3531_f_720p_hvr_8"
#define WS_HI3515A_F_DEC_BOX_4_NAME     "ws_3515a_f_dec_box_4"

#define WS_HI3531_F_720P_DVR_16_NAME "ws_3531_f_720p_dvr_16"
#define WS_HI3531_F_720P_DVR_16_HVR_NAME "ws_3531_f_720p_hvr_16"

#define  WS_HI3531_F_EX_1080P_DVR_4_NAME	"ws_3531_f_ex_1080p_dvr_4"
#define  WS_HI3531_F_EX_1080P_DVR_4_HVR_NAME	"ws_3531_f_ex_1080p_hvr_4"

#define  WS_HI3521_F_EX_720P_DVR_4_NAME		"ws_3521_f_ex_720p_dvr_4"
#define  WS_HI3521_F_EX_720P_DVR_4_HVR_NAME		"ws_3521_f_ex_720p_hvr_4"

#define  WS_HI3531_F_EX_720P_DVR_8_NAME  	"ws_3531_f_ex_720p_dvr_8"
#define  WS_HI3531_F_EX_720P_DVR_8_HVR_NAME  	"ws_3531_f_ex_720p_hvr_8"

#define WS_HI3531_F_EX_1080P_DVR_8_NAME  	"ws_3531_f_ex_1080p_dvr_8"
#define WS_HI3531_F_EX_1080P_DVR_8_HVR_NAME  	"ws_3531_f_ex_1080p_hvr_8"

#define  WS_HI3531_F_EX_720P_DVR_16_NAME 	"ws_3531_f_ex_720p_dvr_16"	

#define  WS_HI3521A_F_1080P_DVR_4_NAME 	"ws_3521a_f_1080p_dvr_4"	
#define  WS_HI3521A_F_1080P_DVR_4_HVR_NAME 	"ws_3521a_f_1080p_hvr_4"	

#define WS_HI3531_HVR_4_1080P_4IPC_NAME	    "ws_3531_HVR_4_1080p_4ipc"		
#define WS_HI3531_HVR_8_1080P_4IPC_NAME	    "ws_3531_HVR_8_1080p_4ipc"		

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef enum
{
    WS_HI3515A_F_NVR_4 = 0x80,  //HI3515A ֧4·1080PNVR
    WS_HI3515A_S_NVR_4 = 0x90,  //HI3515A ֧4·1080PNVR
    WS_HI3520D_F_NVR_8 = 0x81,  //3531
    WS_HI3520D_S_NVR_8 = 0x91,
    WS_HI3521_F_NVR_16 = 0x82,
    WS_HI3535_F_NVR_16 = 0x85,
    WS_HI3536_F_NVR_64 = 0x86,
    WS_HI3536C_F_NVR_64 =0x87,
    WS_HI3531A_S_NVR_16 = 0x92, //HI3531A ֧16·1080PNVR
    WS_HI3531_F_1080P_DVR_4 = 0xA0,     //HI3531 4· SDI_DVR
    WS_HI3531_F_1080P_DVR_4_NA = 0xB0,      //HI3531 4· SDI_DVR
    WS_HI3531_F_1080P_DVR_8 = 0xA1,     //HI3531 8· SDI_DVR
    WS_HI3531_F_1080P_DVR_16 = 0xA2,    //HI3531 16· SDI_DVR
    WS_HI3521_F_720P_DVR_4 = 0xA3,  //HI3521 4· SDI_DVR
    WS_HI3521_F_720P_DVR_4_NA = 0xB3,   //HI3521 4· SDI_DVR
    WS_HI3531_F_720P_DVR_8 = 0xA4,
    WS_HI3531_F_720P_DVR_8_OLD = 0xF4,
    WS_HI3531_F_720P_DVR_16 = 0xA5,
    WS_HI3531_F_EX_1080P_DVR_4 = 0xA6,
    WS_HI3521_F_EX_720P_DVR_4 = 0xA7,
    WS_HI3531_F_EX_720P_DVR_8  = 0xA8,
    WS_HI3531_F_EX_1080P_DVR_8 = 0xA9,
    WS_HI3531_F_EX_720P_DVR_16 = 0xAA,	
    WS_HI3521A_F_1080P_DVR_4 = 0xAB,	
    WS_DBG_XM_HI3520A_NVR_4 = 0x10000000
} ws_dev_board_type_id;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif


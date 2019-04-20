#ifndef _WS_PTZ_DEF_H_
#define _WS_PTZ_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include <termios.h>

#define WS_PTZ_PROTOCOL_LIB_PATH	"/mnt/mtd/app/protocol"
#define WS_PTZ_PELCO_D_NAME			"libptz_pelco_d-0.so"
#define WS_PTZ_PELCO_P_NAME			"libptz_pelco_p-1.so"
#define WS_PTZ_CG_PD_NAME			"libptz_cg_pd.so-2"
#define WS_PTZ_CLT_618_NAME			"libptz_ctl_618-3.so"
#define WS_PTZ_Dt_PelcoD_NAME		"libptz_dt_pelcod-4.so"
#define WS_PTZ_JG_Pelcod_NAME		"libptz_jg_pelcod-5.so"
#define WS_PTZ_JY2000_NAME			"libptz_jy2000-6.so"
#define WS_PTZ_Panasonic_NAME		"libptz_panasonic.so-7"
#define WS_PTZ_Panasonic_TS_NAME	"libptz_panasonic_ts-8.so"
#define WS_PTZ_PelcoD_BRE_NAME		"libptz_pelcod_bre-9.so"
#define WS_PTZ_PelcoD_CF_NAME		"libptz_pelcod_cf-10.so"
#define WS_PTZ_PelcoD_COP_NAME		"libptz_pelcod_cop-11.so"
#define WS_PTZ_PelcoD_Dsx_NAME		"libptz_pelcod_dsx-12.so"
#define WS_PTZ_Pelcod_FH_NAME		"libptz_pelcod_fh-13.so"
#define WS_PTZ_PelcoD_GT_NAME		"libptz_pelcod_gt-14.so"
#define WS_PTZ_PelcoD_HD_NAME		"libptz_pelcod_hd-15.so"
#define WS_PTZ_PelcoD_HS_NAME		"libptz_pelcod_hs-16.so"
#define WS_PTZ_PelcoD_Htz_NAME		"libptz_pelcod_htz-17.so"
#define WS_PTZ_PelcoD_jabsco_NAME	"libptz_pelcod_jabsco-18.so"
#define WS_PTZ_PelcoD_JY_NAME		"libptz_pelcod_jy-19.so"
#define WS_PTZ_PelcoD_KC_NAME		"libptz_pelcod_kc-20.so"
#define WS_PTZ_PelcoD_LX_NAME		"libptz_pelcod_lx-21.so"
#define WS_PTZ_PelcoD_Mj_NAME		"libptz_pelcod_mj-22.so"
#define WS_PTZ_PelcoD_WAD_NAME		"libptz_pelcod_wad-23.so"
#define WS_PTZ_PelcoD_XP_NAME		"libptz_pelcod_xp-24.so"
#define WS_PTZ_PelcoP_Call98_NAME	"libptz_pelcop_call98-25.so"
#define WS_PTZ_PelcoP_COP_NAME		"libptz_pelcop_cop-26.so"
#define WS_PTZ_PelcoP_HS_NAME		"libptz_pelcop_hs-27.so"
#define WS_PTZ_PelcoP_LX_NAME		"libptz_pelcop_lx-28.so"
#define WS_PTZ_Pelcop_Mj_NAME		"libptz_pelcop_mj-29.so"
#define WS_PTZ_PelcoP_MR_NAME		"libptz_pelcop_mr-30.so"
#define WS_PTZ_PelcoP_WAD_NAME		"libptz_pelcop_wad-31.so"
#define WS_PTZ_philip_NAME			"libptz_philip-32.so"
#define WS_PTZ_Pts_PelcoD_NAME		"libptz_pts_pelcod-33.so"
#define WS_PTZ_qg_pelcod_NAME		"libptz_qg_pelcod-34.so"
#define WS_PTZ_SAMSUNG_NAME			"libptz_samsung-35.so"
#define WS_PTZ_Samsung_PD_NAME		"libptz_samsung_pd-36.so"
#define WS_PTZ_SYYT_NAME			"libptz_syyt-37.so"
#define WS_PTZ_TD500_NAME			"libptz_td500-38.so"
#define WS_PTZ_tiandy_NAME			"libptz_tiandy-39.so"
#define WS_PTZ_VIDO_NAME			"libptz_vido-40.so"
#define WS_PTZ_VTS_NAME				"libptz_vts-41.so"
#define WS_PTZ_VTV_NAME				"libptz_vtv-42.so"
#define WS_PTZ_xz_Pelcod_NAME		"libptz_xz_pelcod-43.so"
#define WS_PTZ_YAAN_NAME			"libptz_yaan-44.so"
#define WS_PTZ_Yiboer_NAME			"libptz_yiboer-45.so"

/* add by zhangmq 20180527 start*/
//add zmq cfg模块ptz相关的宏[2018-05-07 20:25]
//------------------------save in dev_config.xml--------------------------------
#define WS_CFG_PTZ						"ptz"
#define WS_CFG_PTZ_CH					"ptz_ch"
#define WS_CFG_PTZ_PROTOCOL				"ptz_protocol"
#define WS_CFG_PTZ_ADDRESS				"ptz_address"
#define WS_CFG_PTZ_BAUDRATE				"ptz_baudrate"
#define WS_CFG_PTZ_SPEED				"ptz_speed"
//------------------------save in ptz_protocol.xml-------------------------------
#define WS_CFG_PTZ_CRUISE				"ptz_cruise"
#define WS_CFG_PTZ_POINT				"ptz_point"

/* add by zhangmq 20180527 end */

using ws_utility::WS_ERR;

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif


typedef enum
{
    //协议不同转换的字符控制码也不同
    PTZ_PRO_UNKNOW = 100,//Modified by peishunting 2015.03.18 start - end

    PTZ_PRO_D = 0,
    PTZ_PRO_P,
    PTZ_PRO_CG_PD,
    PTZ_PRO_CLT_618,
    PTZ_PRO_Dt_PelcoD,
    PTZ_PRO_JG_Pelcod,
    PTZ_PRO_JY2000,
    PTZ_PRO_Panasonic,
    PTZ_PRO_Panasonic_TS,
    PTZ_PRO_PelcoD_BRE,
    PTZ_PRO_PelcoD_CF,
    PTZ_PRO_PelcoD_COP,
    PTZ_PRO_PelcoD_Dsx,
    PTZ_PRO_Pelcod_FH,
    PTZ_PRO_PelcoD_GT,
    PTZ_PRO_PelcoD_HD,
    PTZ_PRO_PelcoD_HS,
    PTZ_PRO_PelcoD_Htz,
    PTZ_PRO_PelcoD_jabsco,
    PTZ_PRO_PelcoD_JY,
    PTZ_PRO_PelcoD_KC,
    PTZ_PRO_PelcoD_LX,
    PTZ_PRO_PelcoD_Mj,
    PTZ_PRO_PelcoD_WAD,
    PTZ_PRO_PelcoD_XP,
    PTZ_PRO_PelcoP_Call98,
    PTZ_PRO_PelcoP_COP,
    PTZ_PRO_PelcoP_HS,
    PTZ_PRO_PelcoP_LX,
    PTZ_PRO_Pelcop_Mj,
    PTZ_PRO_PelcoP_MR,
    PTZ_PRO_PelcoP_WAD,
    PTZ_PRO_philip,
    PTZ_PRO_Pts_PelcoD,
    PTZ_PRO_qg_pelcod,
    PTZ_PRO_SAMSUNG,
    PTZ_PRO_Samsung_PD,
    PTZ_PRO_SYYT,
    PTZ_PRO_TD500,
    PTZ_PRO_tiandy,
    PTZ_PRO_VIDO,
    PTZ_PRO_VTS,
    PTZ_PRO_VTV,
    PTZ_PRO_xz_Pelcod,
    PTZ_PRO_YAAN,
    PTZ_PRO_Yiboer,
    PTZ_PRO_END,
} ws_ptz_ctl_type;

typedef enum
{
    //波特率在设置一次后都按照之前设置的来
    PTZ_BAUDRATE_UNKNOW,

    PTZ_BAUDRATE_2400,// 2^0 * 2400  	-> (1 << 0) * 2400
    PTZ_BAUDRATE_4800,// 2^1 * 2400  	-> (1 << 1) * 2400
    PTZ_BAUDRATE_9600,// 2^2 * 2400	-> (1 << 2) * 2400
    PTZ_BAUDRATE_19200,// 2^3 * 2400	-> (1 << 3) * 2400

	PTZ_BAUDRATE_END,
} ws_ptz_baudrate;

typedef struct
{
    ws_ptz_ctl_type     type;
    char                     so_name[32];
    char                     display_name[32];
}ws_ptz_protocol_info_list;

typedef struct
{
    //支持的协议数目，和协议类型
    int support_num;
    ws_ptz_ctl_type protocol[ws_utility::WS_MAX_PTZ_PROTOCOL_NUM];
    WS_CHAR protocol_name[ws_utility::WS_MAX_PTZ_PROTOCOL_NUM][64];		// change by hzg 20160628  --
} ws_ptz_protocol_info;

#define WS_PTZ_BAUDRATE_NAME_LEN    (8)
typedef struct
{
    //支持的波特率的数目，以及名称
    int support_num;
    WS_CHAR baudrate_name[ws_utility::WS_MAX_PTZ_BAUDRATE_NUM][WS_PTZ_BAUDRATE_NAME_LEN];
} ws_ptz_baudrate_info;



typedef struct
{
    //ctl_info需要协议类型，波特率，云台地址
    ws_ptz_ctl_type protocol;
    ws_ptz_baudrate baudrate;
    int ptz_address;
    int ptz_speed;
    ws_ptz_protocol_info protocol_list;   
} ws_ptz_ctl_info;

//方向控制
typedef enum
{
    PTZ_DIRCTION_UNKNOW,

    PTZ_DIRCTION_UP,
    PTZ_DIRCTION_DOWN,
    PTZ_DIRCTION_LEFT,
    PTZ_DIRCTION_RIGHT,

    // 界面上暂时只提供了4 个方向
    PTZ_DIRCTION_LEFT_UP,
    PTZ_DIRCTION_LEFT_DOWN,
    PTZ_DIRCTION_RIGHT_UP,
    PTZ_DIRCTION_RIGHT_DOWN,
    
    PTZ_DIRCTION_END,
} ws_ptz_dirction_cmd;

//zoom
/// 缩放
typedef enum
{
    PTZ_ZOOM_UNKNOW,

    PTZ_ZOOM_WIDE,                  // 缩小
    PTZ_ZOOM_TELE,                  // 放大

    PTZ_ZOOM_END,
} ws_ptz_zoom_cmd;

//focus
/// 焦点
typedef enum
{
    PTZ_FOCUS_NEAR_UNKNOW,

    PTZ_FOCUS_NEAR,                 // 近(目标放大)
    PTZ_FOCUS_FAR,                  // 远(目标缩小)

    PTZ_FOCUS_END,
} ws_ptz_focus_cmd;

//iris
/// 光圈
typedef enum
{
    PTZ_IRIS_UNKONW,

    PTZ_IRIS_OPEN,                  // 光圈放大
    PTZ_IRIS_CLOSE,                 // 光圈缩小

    PTZ_IRIS_END,
} ws_ptz_iris_cmd;

//preset
/// 预置点
typedef enum
{
    PTZ_PRESET_UNKNOW,

    PTZ_PRESET_SET,                 // 设置预置点
    PTZ_PRESET_CLR,                 // 清除预置点
    PTZ_PRESET_GOTO,                // 跳转至预置点

    PTZ_PRESET_END,
} ws_ptz_preset_cmd;

//track
typedef enum
{
    PTZ_TRACK_UNKONW,

    PTZ_TRACK_START_SET,            // 开始录制轨迹
    PTZ_TRACK_STOP_SET,             // 停止录制轨迹
    PTZ_TRACK_RUN,                      // 运行轨迹
    PTZ_TRACK_STOP,                     //track _stop
    PTZ_TRACK_END,
} ws_ptz_track_cmd;

#if defined(__PTZ_FUNC_)
typedef struct
{
	WS_U32 preset_idx[256];            //预置点编号
}ws_ptz_preset_poine;
#endif 

typedef struct
{
    WS_U32 cruise_point;
    WS_U32 preset_idx;          //预置点编号
    WS_BOOL is_selected;
    WS_U32 hold_sec;            //维持时间
} ws_ptz_cruise_point;

typedef struct
{
    WS_U32 point_num;
    ws_ptz_cruise_point point[ws_utility::WS_MAX_PTZ_CRUISE_POINT_NUM];
} ws_ptz_cruise_line;

// 定义巡航状态
typedef enum 
{
    PTZ_CRUISE_STATUS_UNKNOWN,
    PTZ_CRUISE_STATUS_RUN,
    PTZ_CRUISE_STATUS_PAUSE,
    PTZ_CRUISE_STATUS_STOP,
}ws_ptz_cruise_status;

typedef enum
{
    //方位操作
    ptz_up = 100,
    ptz_down,
    ptz_left,
    ptz_right,
    
    ptz_left_up,
    ptz_left_down,
    ptz_right_up,
    ptz_right_down,

    //变倍
    ptz_zoom_increase = 120,
    ptz_zoom_decrease,

    //变焦
    ptz_focus_increase = 130,
    ptz_focus_decrease,

    //光圈
    ptz_iris_near = 140,
    ptz_iris_far,

    //雨刷
    ptz_wiper_open = 150,
    ptz_wiper_close,

    //灯光
    ptz_light_open = 160,
    ptz_light_close,

    //预置点
    ptz_preset_add = 170,
    ptz_preset_del,
    ptz_preset_apply,

    //速度
    ptz_speed_set = 180,

    //停滞
    ptz_stops = 190,

    ptz_cruise_set_line = 200, 
    ptz_cruise_start,
    ptz_cruise_pause,
    ptz_cruise_stop,
	
    ptz_track_start_set = 210,
    ptz_track_stop_set,
    ptz_track_run,

    ptz_end,
} PTZ_CMD_ID;

typedef struct ptz_cmd_node
{
    WS_U32 rmt_ch;//通道号
    char *cmd_string;//命令码
    int cmd_length;//命令码长度
    ptz_cmd_node *next;

    int reserve[32];
} ptz_cmd_node_t;


#if defined(__PTZ_FUNC_)
typedef struct
{
    WS_U32 ch;
    ws_ptz_ctl_type protocol;
    WS_U32 address;
    ws_ptz_baudrate baudrate;
    WS_U32 speed;
    WS_U32 ptz_preset_point[ws_utility::WS_MAX_PTZ_PRESET_NUM];
    WS_U32 cruise_line_index;
    ws_ptz_cruise_line cruise_line[ws_utility::WS_NVR_MAX_CH_NUM];	
}ws_ptz_ch_info;
#else
typedef struct
{
    WS_U32                  ch;
    ws_ptz_ctl_type       protocol;
    WS_U32                  address;
    ws_ptz_baudrate      baudrate;
    WS_U32                  speed;
    // 保存软巡航的信息
    ws_ptz_cruise_line   cruise_line[ws_utility::WS_MAX_PTZ_PROTOCOL_NUM];
}ws_ptz_ch_info;
#endif

typedef WS_ERR (*PTZ_DIRECTION_TRANSCODING)(char *, int , int , ws_ptz_dirction_cmd , int );
typedef WS_ERR (*PTZ_FOCUS_TRANSCODING)(char *, int , ws_ptz_focus_cmd , int );
typedef WS_ERR (*PTZ_ZOOM_TRANSCODING)(char *, int , ws_ptz_zoom_cmd , int );
typedef WS_ERR (*PTZ_IRIS_TRANSCODING)(char *, int , ws_ptz_iris_cmd , int );
typedef WS_ERR (*PTZ_PRESET_TRANSCODING)(char *, int , int , ws_ptz_preset_cmd , int );
typedef WS_ERR (*PTZ_LIGHT_TRANSCODING)(char *, int , WS_BOOL , int );
typedef WS_ERR (*PTZ_WIPER_TRANSCODING)(char *, int , WS_BOOL , int );
typedef WS_ERR (*PTZ_STOP_TRANSCODING)(char *, int , int );
typedef WS_ERR (*PTZ_TRACK_TRANSCODING)(char *, int , int , ws_ptz_track_cmd , int );

typedef struct
{
	PTZ_DIRECTION_TRANSCODING 	ptz_direction_transcoding;
	PTZ_FOCUS_TRANSCODING 		ptz_focus_transcoding;
	PTZ_ZOOM_TRANSCODING 		ptz_zoom_transcoding;
	PTZ_IRIS_TRANSCODING 		ptz_iris_transcoding;
	PTZ_PRESET_TRANSCODING 		ptz_preset_transcoding;
	PTZ_LIGHT_TRANSCODING 		ptz_light_transcoding;
	PTZ_WIPER_TRANSCODING 		ptz_wiper_transcoding;
	PTZ_STOP_TRANSCODING 		ptz_stop_transcoding;
	PTZ_TRACK_TRANSCODING		ptz_track_transcoding;
}WS_PTZ_OPS_S;

typedef struct
{
	ws_ptz_ctl_type type;
	WS_PTZ_OPS_S ptz_ops;
	void *ptz_lib_hand;
	WS_BOOL is_valid;
}ws_ptz_ops_info;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_MODEL_DEF_H_


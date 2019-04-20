#ifndef _WS_COMM_DISPLAY_H_
#define _WS_COMM_DISPLAY_H_

#include "ws_comm_type.h"
#include "ws_comm_sys.h"

#ifdef __cplusplus
extern "C" {
namespace ws_utility 
{
#endif

#define WS_LIVE_PTZ_OVER_LEN	32		// md by lz 20160113 start-end;
#define WS_LIVE_PTZ_GAP		48		// md by lz 20160217;
typedef struct
{
    WS_U32  numerator;      //分子
    WS_U32  denominator;    //分母
} ws_percent;

typedef struct
{
    ws_percent  x;  //区域起点x在屏宽中的比例
    ws_percent  y;  //区域起点y在屏高中的比例
    ws_percent  w;  //区域宽度在屏宽中的比例
    ws_percent  h;  //区域高度在屏高中的比例
} ws_abstract_rect;

//相对百分比坐标
typedef struct
{
    ws_percent  x;  //区域起点x在屏宽中的比例
    ws_percent  y;  //区域起点y在屏高中的比例
} ws_abstract_coordinate;

typedef struct
{
    WS_U32  x;  //区域起点x的实际坐标
    WS_U32  y;  //区域起点y的实际坐标
    WS_U32  w;  //区域宽度的实际宽度
    WS_U32  h;  //区域高度的实际高度
} ws_real_rect;

typedef enum
{
    WS_DISPLAY_UNKNOW,
    WS_DISPLAY_1,   //单画面预览
    WS_DISPLAY_4,   //四画面预览
    WS_DISPLAY_6,   //六画面预览
    WS_DISPLAY_8,   //八画面预览
    WS_DISPLAY_9,   //九画面预览
    WS_DISPLAY_16,  //16画面预览
// change by liuy 20160322 start;
    WS_DISPLAY_25,  //25画面预览
    WS_DISPLAY_36,  //36画面预览
    WS_DISPLAY_64,  //64画面预览
// change by liuy 20160322 end;
} ws_screen_div_mode;

typedef enum
{
    WS_DIS_CONTENT_UNKNOW,
    WS_DIS_CHANNEL,     //显示有效通道
    WS_DIS_LOGO,        //显示LOGO
} ws_display_content;

typedef struct
{
    ws_display_content content; //显示内容的类型
    union   //具体哪个通道或者哪种LOGO
    {
        WS_S32          channel;    //预览或者回放通道编号
        ws_logo_type    logo;       //显示某种Logo
    } para;
} ws_wind_content;

// ---------1024-------------
// |      ______________    |
// |      |             |   |
// |      |             |   |
// |      |             |  768
// |      |             |   |
// |      |             |   |
// |      |             |   |
// |      |_____________|   |
// --------------------------
typedef struct
{
    WS_U32              resol_w;    //实际分辨率的宽度，如上图1024所示
    WS_U32              resol_h;    //实际分辨率的高度，如上图768所示

    ws_screen_div_mode  div_mode;       //屏幕划分模式
    ws_abstract_rect    screen_rect;    //参与显示的屏幕在实际分辨率中的位置，上图内部小方框
} ws_display_screen_info;

// add by lz 20151222 start;
typedef enum
{
	WS_LIVE_PTZ_IDLE =0,			
	WS_LIVE_PTZ_READLY,
	WS_LIVE_VIR_PTZ_ACTIVE, 		
	WS_LIVE_REL_PTZ_ACTIVE, 		
}ws_live_ptz_state_e;

typedef enum
{
	WS_RRL_PTZ_STOP	= 0,		
	WS_REL_PTZ_UP,			
	WS_REL_PTZ_DOWN,		
	WS_REL_PTZ_LEFT,		
	WS_REL_PTZ_RIGHT,		
}ws_rel_ptz_state_e;

typedef enum
{
	WS_PB_PTZ_IDLE =0,			
	WS_PB_PTZ_READLY,
	WS_PB_VIR_PTZ_ACTIVE, 		
	WS_PB_REL_PTZ_ACTIVE, 		
}ws_pb_ptz_state_e;


#if defined(_SUPPORT_POLL_LIVE_)
typedef struct
{
    WS_S32  				interval_time;
    ws_screen_div_mode		used_div_mode;
    WS_U32				one_div[ws_utility::WS_NVR_MAX_CH_NUM][ws_utility::WS_NVR_MAX_MASK_NUM];
    WS_U32				four_div[(ws_utility::WS_NVR_MAX_CH_NUM+3)/4][ws_utility::WS_NVR_MAX_MASK_NUM];
}ws_user_cfg_poll_live_s;

typedef enum
{
	WS_LIVE_POLL_UNKNOW = 0,	
	WS_LIVE_POLL_NOR,		
	WS_LIVE_POLL_ALARM,		
}ws_poll_live_type_e;
#endif

#ifdef __cplusplus
}//namespace ws_utility {//changed by mjq 2014.11.26 
}//extern "C" {
#endif


#endif //#ifndef _WS_COMM_DISPLAY_H_


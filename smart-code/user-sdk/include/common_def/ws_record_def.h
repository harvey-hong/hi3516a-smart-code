#ifndef _WS_RECORD_DEF_H_
#define _WS_RECORD_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"
#include "ws_comm_sys.h"

/* add by zhangmq 20180527 start */
//add zmq 录像模块配置必须的宏[2018-05-03 14:33]
//----------------------------------------录像计划,节假日等----------------------------------------
#define WS_CFG_REC_MODE               "RecMode"      //通道相关  0--不录像   1--手动录像    2--计划录像.
#define WS_CFG_REC_HOLIDAY_ENABLE    "HdayEnable"        //通道相关  0--不启用节假日计划   1--使用节假日计划.

#define WS_CFG_REC_PLAN               "Plan"           //通道相关,一天的录像计划1-2-3-4
#define WS_CFG_REC_HOLIDAY_PLAN      "Holiday"        //节假日计划.
#define WS_CFG_REC_HOLIDAY_YEAR      "Y"                 //节假日年
#define WS_CFG_REC_HOLIDAY_MONTH     "M"                 //节假日月

//add zmq 部分用到
//--------------------------------------- 视频 通道参数配置 ---------------------------------
#define WS_CFG_VIDEO_CH_KEY1            "VideoCh"   //每个通道用VideoCh0,VideoCh1,VideoCh2等记录
#define WS_CFG_VIDEO_CH_MD_RECT     "MdRect"    //每个区域用MdRect0,MdRect1,MdRect2等等记录
#define WS_CFG_VIDEO_CH_MD_RECT_NUM "MdRectNum"  //移动侦测区域个数
#define WS_CFG_VIDEO_CH_MD_SENSITIVITY  "MdSensitivity" //移动侦测灵敏度           
#define WS_CFG_VIDEO_CH_MD_BRIGHTNESS      "Brightness"   //图像亮度                         
#define WS_CFG_VIDEO_CH_MD_CONTRAST        "Contrast"    //图像对比度                       
#define WS_CFG_VIDEO_CH_MD_SATURATION      "Saturation"   //图像饱和度                   
#define WS_CFG_VIDEO_CH_MD_TONE            "Tone"       //色调                     
#define WS_CFG_VIDEO_CH_MD_SHARPNESS       "Sharpness"   //锐度           
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

//ws_rec_file_trig_type详细描述了每种录像文件触发的类型，但是界面(控制)层可能因为不同的需求，会有不同的认知方式，
//例如，家用设备把MD和AI统一称作报警录像，而专业设备可能只把AI叫做报警录像
//这里封装一个专门针对界面(控制)层的解释枚举，不同的规格修改这个宏，重新编译就可以了
typedef enum
{
    WS_REC_SCHEDULE_UNKNOW = ws_utility::WS_REC_FILE_TRIG_NONE,
    WS_REC_SCHEDULE_COMM = ws_utility::WS_REC_FILE_TRIG_BY_TIMER|ws_utility::WS_REC_FILE_TRIG_BY_MANUAL,//普通录像 //Modified by qqy, at 2017-03-10 09:48:39
    WS_REC_SCHEDULE_ALARM = ws_utility::WS_REC_FILE_TRIG_BY_MD | ws_utility::WS_REC_FILE_TRIG_BY_AI,    //报警录像
    WS_REC_SCHEDULE_ALL = 0xFFFFFFFF,
} ws_rec_schedule_type;

typedef struct
{
    //开始时间
    WS_U16 start_hour;
    WS_U16 start_min;

    //结束时间
    WS_U16 stop_hour;
    WS_U16 stop_min;

    ws_rec_schedule_type type;
} ws_rec_sub_schedule;

typedef enum
{
    WS_SCHEDULE_SUN,    //周日
    WS_SCHEDULE_MON,    //周1
    WS_SCHEDULE_TUES,   //周2
    WS_SCHEDULE_WED,    //周3
    WS_SCHEDULE_THURS,  //周4
    WS_SCHEDULE_FRI,    //周5
    WS_SCHEDULE_SAT,    //周6
    WS_SCHEDULE_HOLIDAY, //节假日
    WS_SCHEDULE_END,
} ws_rec_schedule_day;

typedef struct
{
    ws_rec_sub_schedule sub_schedule[ws_utility::WS_NVR_MAX_SCHEDULE_PER_DAY];
} ws_rec_schedule_per_day;

typedef struct
{
	WS_BOOL    rec_holiday_enable;
	WS_U32      rec_holiday_plan[25 + 43][12];
}ws_rec_schedule_holiday;

typedef struct
{
    ws_rec_schedule_per_day m_schedule_time[ws_utility::WS_NVR_MAX_CH_NUM][WS_SCHEDULE_END];
}ws_rec_schedule_time;

typedef struct
{
    ws_rec_schedule_per_day m_schedule[WS_SCHEDULE_END];
}ws_channel_rec_schedule;  //add by khs 2017.3.21 


typedef struct
{
    WS_BOOL     rec_holiday_enable[ws_utility::WS_NVR_MAX_CH_NUM];
    WS_U32       rec_holiday_plan[25 + 43][12];
    ws_rec_schedule_per_day rec_week_plan[ws_utility::WS_NVR_MAX_CH_NUM][WS_SCHEDULE_END];
}ws_rec_schedule;


#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif //#ifndef _WS_RECORD_DEF_H_


#ifndef _WS_RECORD_DEF_H_
#define _WS_RECORD_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"
#include "ws_comm_sys.h"

/* add by zhangmq 20180527 start */
//add zmq ¼��ģ�����ñ���ĺ�[2018-05-03 14:33]
//----------------------------------------¼��ƻ�,�ڼ��յ�----------------------------------------
#define WS_CFG_REC_MODE               "RecMode"      //ͨ�����  0--��¼��   1--�ֶ�¼��    2--�ƻ�¼��.
#define WS_CFG_REC_HOLIDAY_ENABLE    "HdayEnable"        //ͨ�����  0--�����ýڼ��ռƻ�   1--ʹ�ýڼ��ռƻ�.

#define WS_CFG_REC_PLAN               "Plan"           //ͨ�����,һ���¼��ƻ�1-2-3-4
#define WS_CFG_REC_HOLIDAY_PLAN      "Holiday"        //�ڼ��ռƻ�.
#define WS_CFG_REC_HOLIDAY_YEAR      "Y"                 //�ڼ�����
#define WS_CFG_REC_HOLIDAY_MONTH     "M"                 //�ڼ�����

//add zmq �����õ�
//--------------------------------------- ��Ƶ ͨ���������� ---------------------------------
#define WS_CFG_VIDEO_CH_KEY1            "VideoCh"   //ÿ��ͨ����VideoCh0,VideoCh1,VideoCh2�ȼ�¼
#define WS_CFG_VIDEO_CH_MD_RECT     "MdRect"    //ÿ��������MdRect0,MdRect1,MdRect2�ȵȼ�¼
#define WS_CFG_VIDEO_CH_MD_RECT_NUM "MdRectNum"  //�ƶ�����������
#define WS_CFG_VIDEO_CH_MD_SENSITIVITY  "MdSensitivity" //�ƶ����������           
#define WS_CFG_VIDEO_CH_MD_BRIGHTNESS      "Brightness"   //ͼ������                         
#define WS_CFG_VIDEO_CH_MD_CONTRAST        "Contrast"    //ͼ��Աȶ�                       
#define WS_CFG_VIDEO_CH_MD_SATURATION      "Saturation"   //ͼ�񱥺Ͷ�                   
#define WS_CFG_VIDEO_CH_MD_TONE            "Tone"       //ɫ��                     
#define WS_CFG_VIDEO_CH_MD_SHARPNESS       "Sharpness"   //���           
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

//ws_rec_file_trig_type��ϸ������ÿ��¼���ļ����������ͣ����ǽ���(����)�������Ϊ��ͬ�����󣬻��в�ͬ����֪��ʽ��
//���磬�����豸��MD��AIͳһ��������¼�񣬶�רҵ�豸����ֻ��AI��������¼��
//�����װһ��ר����Խ���(����)��Ľ���ö�٣���ͬ�Ĺ���޸�����꣬���±���Ϳ�����
typedef enum
{
    WS_REC_SCHEDULE_UNKNOW = ws_utility::WS_REC_FILE_TRIG_NONE,
    WS_REC_SCHEDULE_COMM = ws_utility::WS_REC_FILE_TRIG_BY_TIMER|ws_utility::WS_REC_FILE_TRIG_BY_MANUAL,//��ͨ¼�� //Modified by qqy, at 2017-03-10 09:48:39
    WS_REC_SCHEDULE_ALARM = ws_utility::WS_REC_FILE_TRIG_BY_MD | ws_utility::WS_REC_FILE_TRIG_BY_AI,    //����¼��
    WS_REC_SCHEDULE_ALL = 0xFFFFFFFF,
} ws_rec_schedule_type;

typedef struct
{
    //��ʼʱ��
    WS_U16 start_hour;
    WS_U16 start_min;

    //����ʱ��
    WS_U16 stop_hour;
    WS_U16 stop_min;

    ws_rec_schedule_type type;
} ws_rec_sub_schedule;

typedef enum
{
    WS_SCHEDULE_SUN,    //����
    WS_SCHEDULE_MON,    //��1
    WS_SCHEDULE_TUES,   //��2
    WS_SCHEDULE_WED,    //��3
    WS_SCHEDULE_THURS,  //��4
    WS_SCHEDULE_FRI,    //��5
    WS_SCHEDULE_SAT,    //��6
    WS_SCHEDULE_HOLIDAY, //�ڼ���
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


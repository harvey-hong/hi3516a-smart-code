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
    WS_U32  numerator;      //����
    WS_U32  denominator;    //��ĸ
} ws_percent;

typedef struct
{
    ws_percent  x;  //�������x�������еı���
    ws_percent  y;  //�������y�������еı���
    ws_percent  w;  //�������������еı���
    ws_percent  h;  //����߶��������еı���
} ws_abstract_rect;

//��԰ٷֱ�����
typedef struct
{
    ws_percent  x;  //�������x�������еı���
    ws_percent  y;  //�������y�������еı���
} ws_abstract_coordinate;

typedef struct
{
    WS_U32  x;  //�������x��ʵ������
    WS_U32  y;  //�������y��ʵ������
    WS_U32  w;  //�����ȵ�ʵ�ʿ��
    WS_U32  h;  //����߶ȵ�ʵ�ʸ߶�
} ws_real_rect;

typedef enum
{
    WS_DISPLAY_UNKNOW,
    WS_DISPLAY_1,   //������Ԥ��
    WS_DISPLAY_4,   //�Ļ���Ԥ��
    WS_DISPLAY_6,   //������Ԥ��
    WS_DISPLAY_8,   //�˻���Ԥ��
    WS_DISPLAY_9,   //�Ż���Ԥ��
    WS_DISPLAY_16,  //16����Ԥ��
// change by liuy 20160322 start;
    WS_DISPLAY_25,  //25����Ԥ��
    WS_DISPLAY_36,  //36����Ԥ��
    WS_DISPLAY_64,  //64����Ԥ��
// change by liuy 20160322 end;
} ws_screen_div_mode;

typedef enum
{
    WS_DIS_CONTENT_UNKNOW,
    WS_DIS_CHANNEL,     //��ʾ��Чͨ��
    WS_DIS_LOGO,        //��ʾLOGO
} ws_display_content;

typedef struct
{
    ws_display_content content; //��ʾ���ݵ�����
    union   //�����ĸ�ͨ����������LOGO
    {
        WS_S32          channel;    //Ԥ�����߻ط�ͨ�����
        ws_logo_type    logo;       //��ʾĳ��Logo
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
    WS_U32              resol_w;    //ʵ�ʷֱ��ʵĿ�ȣ�����ͼ1024��ʾ
    WS_U32              resol_h;    //ʵ�ʷֱ��ʵĸ߶ȣ�����ͼ768��ʾ

    ws_screen_div_mode  div_mode;       //��Ļ����ģʽ
    ws_abstract_rect    screen_rect;    //������ʾ����Ļ��ʵ�ʷֱ����е�λ�ã���ͼ�ڲ�С����
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


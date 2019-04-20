#ifndef _WS_PLAYBACK_DEF_H_
#define _WS_PLAYBACK_DEF_H_

#include "ws_comm_type.h"
#include "ws_comm_flist.h"
#include "ws_comm_display.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef enum
{
    WS_PB_SPEED_SLOW_16 = -4,   //1/16����
    WS_PB_SPEED_SLOW_8  = -3,   //1/8����
    WS_PB_SPEED_SLOW_4  = -2,   //1/4����
    WS_PB_SPEED_SLOW_2  = -1,   //1/2����
    WS_PB_SPEED_NORMAL  = 0,
    WS_PB_SPEED_FAST_2  = 1,    //2����
    WS_PB_SPEED_FAST_4  = 2,    //4����
    WS_PB_SPEED_FAST_8  = 3,    //8����
    WS_PB_SPEED_FAST_16 = 4,    //16����
    WS_PB_SPEED_FAST_32 = 5,    //32����
} ws_playback_speed;

// add by liuyao 20160407 start ----
typedef enum
{
    WS_PB_CHANNEL_STATE_STOP = 0, 
    WS_PB_CHANNEL_STATE_REC,
    WS_PB_CHANNEL_STATE_SNAP,
    WS_PB_CHANNEL_STATE_IDLE,		
}ws_playback_chan_state;  // the state of channel playback is what is state !
// add by liuyao 20160407 end ----



typedef enum
{
    WS_PB_DIR_NORMAL=0,   //����
    WS_PB_DIR_REVERSE,  //����
} ws_playback_direction;

typedef enum
{
    WS_PB_MODE_UNKONW=0,
    WS_PB_REC_FILE,     //�ط�¼���ļ�
    WS_PB_SNAP_FILE,    //�ط�ץͼ�ļ�
} ws_playback_mode;

typedef enum
{
	WS_PB_FILE_CONTINUE,
	WS_PB_FILE_STOP,
}ws_playback_file_mode;		//�ط��ļ�ʱ���ͣ������ţ����Ƿ���ֹͣ

//add by khs 2017.11.3 start
typedef struct
{
    WS_BOOL need_dis;  
    ws_utility::ws_abstract_rect dis_rect;
    ws_utility::ws_logo_type logo_type;    
    int dec_pipe_idx;   
} ws_logo_wind_info;

typedef enum
{
    PB_RD_FILE_NORMAL,
    PB_RD_FILE_WAIT_START,      
    PB_RD_FILE_CHECK_FINISH,   
    PB_RD_FILE_COMPLETE,        
} play_file_read_state;
//add by khs 2017.11.3 end


typedef enum
{
    WS_PB_STEP_UNKONW,
    WS_PB_STEP_NEXT,    //��һ֡
    WS_PB_STEP_BACK,    //��һ֡
} ws_playback_step_mode;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //#ifndef _WS_COMM_PLAYBACK_H_

#ifndef _WS_EXCEPTION_PROC_DEF_H_
#define _WS_EXCEPTION_PROC_DEF_H_

#include "ws_comm_type.h"


#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

#if 0
typedef enum
{
    EXCEPTION_UNKOWN = 0,
	EXCEPTION_DISK_CHECKING,
    EXCEPTION_NO_DISK,
    EXCEPTION_DISK_ERROR,
    EXCEPTION_NO_SPACE,
    EXCEPTION_NET_ERROR,
    EXCEPTION_IP_CONFLICT,
    EXCEPTION_R_LOF,
    EXCEPTION_ABNORMAL_SHUTDOWN,
   	

    EXCEPTION_TOTAL_NUM,            //枚举个数
} exception_type;

typedef enum
{
    WS_IP_CONFLICT = 0x01,          //IP发生冲突
    WS_IP_DHCP = 0x02,              //此时为动态IP状态
    WS_IP_AUTO = 0x04,              //静态IP状态允许自动修改IP
} ws_exception_state;

typedef struct
{
    WS_BOOL is_enable;
    WS_BOOL is_email_linkage;
    WS_BOOL is_voice_alarm;
    WS_BOOL is_auto_ip;
    WS_BOOL is_linkage_rec;
	//add by mjq 20150522 start
	WS_BOOL is_alarm_out[4];
	//add by mjq 20150522 end
    WS_U32 ch_part; //参与通道
} exception_control;

typedef struct
{
    exception_type type;
    exception_control ctl;
} exception_linkage;

typedef enum
{
	WS_EXCEPTION_WORKING_UNKNOW,
	WS_EXCEPTION_WORKING_NORMAL,
	WS_EXCEPTION_WORKING_CLEAR,
	WS_EXCEPTION_WORKING_STOP,

}ws_exception_working_state;


#endif

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_MODEL_DEF_H_
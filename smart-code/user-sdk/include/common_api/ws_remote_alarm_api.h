#ifndef _WS_REMOTE_ALARM_API_H_
#define _WS_REMOTE_ALARM_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_sys.h" 

#include "ws_common.h"
#include "ws_comm_av.h"
#include "ws_comm_data.h"

using namespace ws_utility;

#ifdef __cplusplus
extern "C" {
namespace ws_remote_alarm
{
#endif

    // 数字模块初始化，包括共性内容初始化，解决内部对配置模块的调用
    WS_ERR alarm_remote_init(WS_U32 phyCnt, WS_U32 digitCnt,WS_S32 alarmport);
    WS_ERR alarm_notify_device_connect(WS_U32 rmt_ch, WS_U32 http_port, WS_CHAR *ipv4, WS_U32 ipLen, WS_CHAR *serial_no, WS_U32 serial_len);
    WS_ERR alarm_notify_device_disconnect(WS_U32 rmt_ch, WS_U32 http_port, WS_CHAR *ipv4, WS_U32 ipLen, WS_CHAR *serial_no, WS_U32 serial_len);    
    
#ifdef __cplusplus
}
}
#endif

#endif  


#ifndef _HTTP_ALARM_H__
#define _HTTP_ALARM_H__

#include "ws_comm_type.h"
#include "ws_comm_errno.h"

#if defined( __cplusplus)
#define HTTP_ALARM_API  extern "C" __attribute__((visibility("default")))
#else
#define HTTP_ALARM_API  __attribute__((visibility("default")))
#endif


//!<Æô¶¯º¯Êý......
HTTP_ALARM_API int  Alarm_Start(int port);
HTTP_ALARM_API int SetAlarmPort(int port);

#endif

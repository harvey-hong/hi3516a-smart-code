#ifndef _WS_HTTP_SERVER_H__
#define _WS_HTTP_SERVER_H__

#include "ws_comm_type.h"
#include "ws_comm_errno.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

/* 
 Modified by hongzg, at 2014-09-04 12:08:08 start
 reason: change for split HTTP server to web config upgrade and HTTP fd server, added alarm push
*/
WS_ERR http_init(void);
WS_ERR PushAlarmEvent(ws_utility::ws_event_serial_type evt,WS_U32 number,WS_U32 chan,time_t time); 
/* 
 Modified by hongzg, at 2014-09-04 12:08:08 end
 reason: change for split HTTP server to web config upgrade and HTTP fd server   
*/

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif


#endif

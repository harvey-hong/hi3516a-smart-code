#ifndef _WS_DEV_PROBE_API_H_
#define _WS_DEV_PROBE_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"

#include "ws_dev_probe_def.h"

using ws_utility::WS_ERR;
using namespace ws_soft;

#ifdef __cplusplus
extern "C" {
namespace ws_probe_man
{
#endif

WS_ERR devprobe_init(const ws_remote_dev_info *local_info);
WS_ERR devprobe_refresh();  //刷新探测远程设备
// del by linhh 20170330 

WS_VOID* devprobe_auto_refresh(void* para);       



WS_ERR devprobe_update_ip_ex(void *para);

#ifdef __cplusplus
}//namespace ws_probe_man {
}//extern "C" {
#endif

#endif  //_WS_MODEL_DEF_H_


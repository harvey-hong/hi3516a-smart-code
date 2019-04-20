#ifndef _WS_DST_API_H_
#define _WS_DST_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_dst_def.h"

using ws_utility::WS_ERR;
using namespace ws_soft;

#ifdef __cplusplus
extern "C" {
namespace ws_dst     
{
#endif

const ws_support_time_zone *dst_get_manage();
WS_ERR dst_init();
WS_ERR dst_change_time(time_zone_type type, const ws_utility::ws_time_struct *time, ws_utility::ws_time_struct *time_update);       //只在进入或出去DST时段时操作
WS_ERR dst_change_time_ex(time_zone_type type, const ws_utility::ws_time_struct *time, ws_utility::ws_time_struct *time_update);    //只要当前时段位于DST时段都进行操作
WS_ERR dst_change_dev_time(dst_setting * dst_config,const ws_utility :: ws_time_struct * befor_change_time,const ws_utility :: ws_time_struct *after_change_time,ws_utility :: ws_time_struct *time_update);
WS_ERR dst_get_zone_type_time(time_zone_type type, int *zone_hour, int *zone_min);

#ifdef __cplusplus
}//namespace ws_dst {
}//extern "C" {
#endif

#endif  //_WS_DST_DEF_H_



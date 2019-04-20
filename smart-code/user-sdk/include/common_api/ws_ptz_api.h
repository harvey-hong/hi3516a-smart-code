#ifndef _WS_PTZ_API_H_
#define _WS_PTZ_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_ptz_def.h"

using ws_soft::WS_PTZ_OPS_S;
using namespace ws_soft;    
#ifdef __cplusplus
extern "C" {

namespace ws_ptzm	
{
#endif

WS_ERR ptz_init();

WS_ERR ptz_get_protocol_list_info(ws_ptz_protocol_info_list **list_info, WS_U32 *protocol_num);

WS_ERR ptz_get_support_protocol(ws_ptz_protocol_info *protocol_info);
WS_ERR ptz_get_support_baudrate(ws_ptz_baudrate_info *baudrate_info);
WS_ERR ptz_get_protocol_ops(ws_ptz_ctl_type protocol, WS_PTZ_OPS_S *ops);
WS_ERR ptz_set_ctl_para(WS_U32 ch, const ws_ptz_ctl_info *ctl_info);
WS_ERR ptz_get_ctl_para(WS_U32 ch, ws_ptz_ctl_info *ctl_info);
WS_ERR ptz_ctl_dirction(WS_U32 ch, ws_ptz_dirction_cmd cmd);
WS_ERR ptz_ctl_zoom(WS_U32 ch, ws_ptz_zoom_cmd cmd);
WS_ERR ptz_ctl_focus(WS_U32 ch, ws_ptz_focus_cmd cmd);
WS_ERR ptz_ctl_iris(WS_U32 ch, ws_ptz_iris_cmd cmd);
WS_ERR ptz_ctl_light(WS_U32 ch, WS_BOOL enable);
WS_ERR ptz_ctl_wiper(WS_U32 ch, WS_BOOL enable);
WS_ERR ptz_ctl_track(WS_U32 ch, ws_ptz_track_cmd cmd, WS_U32 track_idx);	
WS_ERR ptz_ctl_preset(WS_U32 ch, ws_ptz_preset_cmd cmd, WS_U32 preset_idx);
WS_ERR ptz_ctl_stop(WS_U32 ch);
WS_ERR ptz_ctl_speed(WS_U32 ch, WS_U32 speed);
WS_ERR ptz_get_speed(WS_U32 ch, WS_U32 * speed);

/* add by zhangmq 20180527 start*/
//add zmq cfg模块移动ptz 接口
WS_ERR cfg_manage_set_ptz_speed(WS_U32 ch, WS_U32 speed);
WS_ERR cfg_manage_set_ptz_info(WS_U32 ch, const ws_ptz_ctl_info* ptz_info);

WS_ERR cfg_manage_del_ptz_cruise_point(WS_U32 ch, ws_ptz_ctl_type protocol, WS_U32 idx);
 WS_ERR cfg_manage_set_ptz_cruise_point(WS_U32 ch, ws_ptz_ctl_type protocol, const ws_ptz_cruise_point* cruise_point);
WS_ERR cfg_manage_get_ptz_speed(WS_U32 ch, WS_U32* speed);
WS_ERR cfg_manage_get_ptz_info(WS_U32 ch, ws_ptz_ctl_info* ptz_info);
WS_ERR cfg_manage_get_ptz_cruise_line(WS_U32 ch, ws_ptz_ctl_type protocol, ws_ptz_cruise_line* cruise_line);

WS_ERR cfg_fac_manage_get_ptz_cfg(WS_U32 ch, ws_ptz_ch_info * ptz_ch_info);
WS_ERR resume_ptz_cfg();
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //#ifndef _WS_PTZ_API_H_



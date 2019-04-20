#ifndef _WS_REMOTE_AGENT_API_H_
#define _WS_REMOTE_AGENT_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_sys.h" 

#include "ws_common.h"
#include "ws_comm_av.h"
#include "ws_comm_data.h"
#include "ws_ptz_def.h"
#include "ws_remote_agent_def.h"

using ws_utility::ws_module_id;
using ws_utility::WS_ERR;
using ws_utility::ws_snap_file_trig_type;
using namespace ws_soft;

#ifdef __cplusplus
extern "C" {
namespace ws_remote_agent
{
#endif

    // 数字模块初始化，包括共性内容初始化，解决内部对配置模块的调用
    WS_ERR rmta_init(WS_U32 rmt_ch,WS_S32 alarmport, WS_BOOL bSyncTime, WS_U32 data_magic);
    WS_ERR rmta_sync_local_time();
    WS_ERR rmta_set_new_magic(WS_U32 magic);

    //----------------------------------------------- 远程控制 --------------------------------------
    //由于远程控制需要知道对应设备的http端口 初始化时使用默认80端口
    WS_ERR rmta_set_connect_port(WS_U32 rmt_ch, WS_S32 port);

    WS_ERR rmta_set_default_isp_para(WS_U32 rmt_ch);
    WS_ERR rmta_set_default_exposure_para(WS_U32 rmt_ch);

    WS_ERR rmta_enable_sync_ipc_time(WS_BOOL enable);           //使能同步IPC时间
    WS_ERR rmta_sync_ipc_time();
    WS_ERR rmta_get_enc_para(WS_U32 rmt_ch, const ws_venc_str_type str_type, ws_enc_para *para);
    WS_ERR rmta_set_enc_para(WS_U32 rmt_ch, const ws_venc_str_type str_type, const ws_enc_para *para);
    WS_ERR rmta_set_enc_default(WS_U32 rmt_ch);

WS_ERR rmta_get_isp_para(WS_U32 rmt_ch, ws_isp_image *get_image, ws_isp_exposure *get_exposure);
WS_ERR rmta_get_default_isp_para(WS_U32 rmt_ch, ws_isp_image *get_image, ws_isp_exposure *get_exposure); 
WS_ERR rmta_set_isp_para(WS_U32 rmt_ch, ws_isp_type set_type, int set_val);

WS_ERR rmta_get_md_info(WS_U32 rmt_ch, ws_md_arr *md_arr);
WS_ERR rmta_set_md_info(WS_U32 rmt_ch, const ws_md_arr *md_arr);
WS_ERR rmta_chan_download_config(WS_U32 rmt_ch, char *recvbuf, int recvlen);

WS_ERR rmta_reboot_ipc(WS_U32 rmt_ch);

WS_ERR rmta_new_upload_cfg(WS_U32 rmt_ch, const char *senddata, int sendlen);
WS_ERR rmta_new_upload_sys(WS_U32 rmt_ch, const char *senddata, int sendlen,WS_U32 *taskId);
WS_ERR rmta_get_upgrade_status(WS_U32 rmt_ch, int *upgradeStatus); 

 WS_ERR rmta_get_remote_task_state(WS_U32 ch,WS_U32 taskId,ws_remote_task_state *state);
WS_ERR rmta_stop_remote_task(WS_U32 ch,WS_U32 taskId);

//------------------------------------------------ 连接控制 ------------------------------------
WS_ERR rmta_connect_dev(WS_U32 rmt_ch, /* const */ ws_connet_config *cfg,WS_U32 *TaskId);
WS_ERR rmta_disconnect_dev(WS_U32 rmt_ch,WS_U32 *TaskId);//与ipc进行断开
WS_ERR rmta_connect_new_dev(WS_U32 rmt_ch, ws_connet_config *cfg,WS_U32 *TaskId); //断开旧的，连接新的

WS_ERR rmta_get_ch_state(WS_U32 rmt_ch, ws_agent_ch_state *state);
WS_ERR rmta_get_dev_info(WS_U32 rmt_ch, ws_connect_dev_info *info); //获取连接设备的信息，譬如版本号、序列号之类的

WS_BOOL rmta_get_channel_lose(WS_U32 rmt_ch);
void rmta_get_channel_bit_rate(WS_U32 rmt_ch, WS_U32 *get_kb);
void rmta_get_bit_rate(WS_U32 rmt_ch, ws_venc_str_type type, STREAM_SPEED speed, WS_U32 *get_kb);   
void rmta_get_sub_channel_bit_rate(WS_U32 rmt_ch, WS_U32 *get_kb);
//----------------------------------------------- PTZ ----------------------------------------
WS_ERR rmta_get_ptz_ctl(WS_U32 rmt_ch, ws_ptz_ctl_info *ctl_info);
WS_ERR rmta_set_ptz_ctl(WS_U32 rmt_ch, const ws_ptz_ctl_info *ctl_info);

WS_ERR rmta_set_ptz_dirction(WS_U32 rmt_ch, ws_ptz_dirction_cmd cmd);
WS_ERR rmta_set_ptz_zoom(WS_U32 rmt_ch, ws_ptz_zoom_cmd cmd);
WS_ERR rmta_set_ptz_focus(WS_U32 rmt_ch, ws_ptz_focus_cmd cmd);
WS_ERR rmta_set_ptz_iris(WS_U32 rmt_ch, ws_ptz_iris_cmd cmd);

WS_ERR rmta_set_ptz_preset(WS_U32 rmt_ch, ws_ptz_preset_cmd cmd, WS_U32 preset_idx);

WS_ERR rmta_set_ptz_light(WS_U32 rmt_ch, WS_BOOL work_status);
WS_ERR rmta_set_ptz_wiper(WS_U32 rmt_ch, WS_BOOL work_status);
WS_ERR rmta_set_ptz_speed(WS_U32 rmt_ch, int speed);
WS_ERR rmta_set_ptz_stop(WS_U32 rmt_ch);
WS_ERR rmta_set_ptz_track(WS_U32 nvr_ch, ws_ptz_track_cmd cmd, WS_U32 track_idx);

//--------------------------------------抓图接口-----------------------------------------
//if trig_type is WS_SNAP_DILE_TRIG_BY_LINKAGE, snap will not be added to sql.
WS_ERR rmta_snap_pic(WS_U32 rmt_ch, snap_task_node_t *task_pointer);

//-------------------------------------查询IPC连接信息的接口(手动连接使用)--------------------------
WS_BOOL rmta_whether_IPC_is_connected(WS_U32 rmt_ch, const ws_connet_config *cfg, char *ipv4, int ip_length, char *mac, int mac_length);

WS_ERR rmta_get_osd_area(WS_U32 rmt_ch, ws_osd_type dp_tp, ws_location_type *loc_tp);
WS_ERR rmta_set_osd_area(WS_U32 rmt_ch, ws_osd_type dp_tp, ws_location_type loc_tp);
WS_ERR rmta_get_osd_ch_name(WS_U32 rmt_ch, char *name_buf, size_t size);
WS_ERR rmta_set_osd_ch_name(WS_U32 rmt_ch , const char *name_buf);  

WS_ERR rmta_set_default_enc(WS_U32 rmt_ch);
WS_ERR rmta_set_default_osd(WS_U32 rmt_ch);
WS_ERR rmta_set_default_ptz(WS_U32 rmt_ch);
WS_ERR rmta_set_default_md(WS_U32 rmt_ch);

#ifdef __cplusplus
}//namespace ws_remote_agent {
}//extern "C" {
#endif

#endif  //_WS_REMOTE_AGENT_API_H_


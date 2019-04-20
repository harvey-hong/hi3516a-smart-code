#ifndef _WS_STATUS_API_H_
#define _WS_STATUS_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_status_def.h"
#include "ws_comm_sys.h"
#include "ws_record_def.h"   
#include "ws_comm_av.h"
#include "ws_dev_probe_def.h"

using namespace ws_soft; 
using namespace ws_utility; 

using ws_utility::WS_ERR;

#ifdef __cplusplus
extern "C" {
namespace ws_status  
{
#endif

    WS_ERR status_init();
    WS_ERR status_set_support_resol(sm_status_resol *m_sys_resol, int m_sys_num);
    
    WS_ERR  status_set_rec_holiday_enable(WS_BOOL enable);
    WS_ERR  status_set_holiday(WS_U16 year, WS_U16 month, WS_U32 mask);
    WS_ERR status_set_event_deployment_time(WS_U32 nvr_ch, ws_event_type type , ws_rec_schedule_day day, const ws_rec_schedule_per_day *schedule);

    ws_rec_schedule_day status_get_today_name();    
    WS_ERR status_get_the_disk_part_info_by_part_name(const char *mount_dir, int *total_MB, int *avail_MB, int *avail_node);
    WS_BOOL status_event_is_happen(ws_event_type  event_type, WS_U32 *ch_mask, WS_U32 mask_num);
    WS_BOOL status_event_is_happen_single_channel(ws_event_type  event_type, WS_U32 ch_idx);	//单通道查询方式
    WS_ERR status_get_event_state(ws_event_type event_type, WS_U32 sub_ch, ws_event_state *event_state);
    WS_ERR status_set_event_state(ws_event_type event_type, WS_U32 sub_ch, ws_event_state event_state,time_t event_time); 
    WS_ERR status_try_set_event_state(ws_event_type event_type, WS_U32 sub_ch, ws_event_state event_state,time_t event_time); 
    WS_ERR status_set_event_mask (ws_event_type event_type, WS_U32 mask);
    WS_ERR status_get_event_info(ws_event_type type,WS_U32 ch_idx, ws_event_info *info);
    WS_ERR status_get_event_mask(ws_event_type event_type, WS_U32 *mask, int mask_num);	
    WS_ERR status_clean_event_state(ws_event_type type, WS_U32 ch_idx = 0xffffffff);
    WS_ERR status_set_exception_state(exception_type type, WS_U32 state);	
    /* 硬盘异常不能重复添加，专门添加判断 */
    int status_set_disk_exception_state(WS_U32 state);		                
    WS_ERR status_get_exception_state(exception_type type, WS_U32 *state);
    WS_ERR status_get_exception_stateEx(exception_type type, ws_soft::ws_event_state *state);   
    WS_ERR status_get_exception_info(exception_type type, ws_exception_info *info);
    WS_ERR status_get_exception_infoEx(exception_type type, WS_U32* state , ws_exception_info *info);     
    WS_ERR status_set_exception_info(exception_type type,ws_exception_info *info);
    WS_ERR status_clean_exception_state(exception_type type);
    WS_ERR status_set_disk_state(const WS_CHAR * serial, ws_hard_disk_state disk_state);
    WS_U32 status_get_disk_num();
    WS_ERR status_add_disk_info(ws_status_manage_disk_info *disk_info); 
    WS_ERR status_get_all_disk_info(ws_status_manage_disk_info* disk_info, WS_U32 inLen, WS_U32 *outLen); 
    WS_ERR status_remove_disk_info(WS_CHAR * serial);
    WS_ERR status_update_part_info(WS_CHAR * serial,ws_status_manage_change_info_m* part_info);

    WS_ERR status_set_operate_state(ws_operate_type  opt_type , WS_BOOL flag);
    WS_ERR status_get_operate_state(ws_operate_type  opt_type ,WS_BOOL  *flag);
    WS_ERR status_get_operate_info(ws_operate_type  opt_type ,ws_operate_info	*info);
    WS_ERR status_save_current_ip(const char *ip);
    WS_ERR status_get_current_ip(WS_CHAR *ip, size_t size);

    WS_ERR status_register_push_alarm_event(add_happen_event_node func);
    WS_ERR status_get_serial_event(ws_event_serial_type *type, WS_U32 *serial_num, WS_U32 *ch);

    WS_ERR status_set_local_mac_info(char *m_mac , int nLen);
    WS_ERR status_get_local_mac_info(char *m_mac, int *nLen);
    ws_support_resol *status_get_support_resol();
    WS_ERR status_set_local_resol(const WS_CHAR *resol);  

    WS_ERR status_add_fmt_pool(const char*  serial_no,WS_U32 part_idx);
    WS_ERR status_get_all_fmt_pool(ws_soft::ws_disk_serial* serial_no , WS_S32* nNum);
    WS_ERR status_remove_fmt_pool(const char*  serial_no);
    WS_ERR status_fetch_fmt_dev(WS_CHAR *serial_no, WS_U32 serial_no_len, WS_U32 *part_idx);

    // add by linhh 20170306 : 保存模拟通道视频相关信息
    WS_ERR status_set_channel_state(WS_U32 Ch,  ws_soft::ws_av_chip_ch_info av_info);   
    WS_ERR status_get_channel_state(WS_U32 Ch,  ws_soft::ws_av_chip_ch_info *av_info);   

    WS_ERR status_set_IPAddr_change(const char *ip_address);
    WS_ERR status_get_IPAddr_change(char *ip_address, size_t nLen , WS_BOOL *bChange);

    /*add by linhh 20170330 for network device manage*/
    WS_ERR status_dev_probe_get_dev_num(WS_U32 *dev_num);
    WS_ERR status_dev_probe_get_dev_info(int dev_idx, ws_remote_dev_info *info);
    WS_ERR status_dev_probe_get_ip_dev_info(char *ipv, ws_remote_dev_info *info);	
    WS_BOOL status_dev_probe_ipc_passwd_changed(const char *ipv);	
    WS_VOID status_dev_probe_add_new_ip_node(char *ipv, int length);
    WS_ERR status_dev_probe_discover_dev(WS_U32 nCnt , ws_remote_dev_info *info);

	//add by khs 2017.7.14    
 	WS_ERR status_set_file_state_lock(file_state* file_info);
 	WS_ERR status_set_file_state_unlock(file_state* file_info);
	WS_ERR status_get_file_state(ws_time_struct time,WS_U32 ch,WS_U32* lock_state);

    /*add by linhh 20171207 : 记录IPC的IP与超级用户密码复位，记录NVR的超级用户密码复位操作 */
    WS_ERR status_set_admin_reset(WS_U32 bSet);
    WS_ERR status_get_admin_reset(WS_U32 *bSet);

    WS_ERR status_add_last_picture_name(char* FileName);
    WS_ERR status_get_last_picture_name(char* FileName, int nLen);

    WS_ERR status_set_disk_full();
    WS_BOOL status_get_disk_full();
    
#ifdef __cplusplus
}//namespace ws_status {
}//extern "C" {
#endif

#endif //#ifndef _WS_STATUS_API_H_


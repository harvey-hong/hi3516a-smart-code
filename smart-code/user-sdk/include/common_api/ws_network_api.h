#ifndef _WS_NETWORK_API_H_
#define _WS_NETWORK_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_network_def.h"
#include "ws_comm_sys.h"
#include "ws_wifi_def.h"
#include "ws_comm_data.h" //add by lmw 20170512 
#include "ws_dst_def.h"

using ws_utility::WS_ERR;
using namespace ws_soft;
using ws_soft::recfile_requiry_snap_need_s;//add by lmw 20170512

#ifdef __cplusplus
extern "C" {
namespace ws_net		
{
#endif
WS_ERR network_init();
WS_ERR network_start();         //只能调用一次

/* hzg 20170411 Cmd control Private Protocol Server start stop  */
WS_ERR network_set_local_connect(const ws_local_connect_cfg *cfg);
WS_ERR network_get_local_connect(ws_local_connect_cfg *cfg);
WS_ERR network_set_net_port(const ws_net_port_cfg *port);
WS_ERR network_set_upnp_port(WS_BOOL enable, WS_S32 port);

WS_ERR network_set_email_cfg(const ws_email_sender_cfg *cfg);
WS_ERR network_add_email_receiver(const ws_reciver_add *name);
WS_ERR network_add_email_receiver_all(const ws_reciver_all *addr_all);          //一次添加一组接收地址
WS_ERR network_del_email_receiver(const ws_reciver_add *name);
//change by lmw 20170512 start
//该接口提供发送文件的位置 后续可以作为抓图所用
//WS_ERR network_send_email(const ws_email_attachment *attachment, const char *title, const char *buf, WS_BOOL is_sync);
WS_ERR network_send_email(const ws_email_attachment *attachment, const char *title, const char *buf, WS_BOOL is_sync,WS_BOOL snap_enable,recfile_requiry_snap_need_s * requiry_sanp_need);
//change by lmw 20170512 end
//该接口提供发送测试邮件，需提供发送者信息和接收者信息
WS_ERR network_send_email_tst(const ws_email_sender_cfg *cfg, const ws_reciver_all *reciver_addr, int reciver_num, const ws_email_attachment *attachment, const char *title, const char *buf);

WS_ERR network_set_ntp(const ws_ntpc_config *cfg);
WS_ERR network_get_ntp_config();
WS_ERR network_get_ip();

WS_ERR network_set_pppoe_config(const ws_pppoe_config *conf);
WS_ERR network_get_show_pppoe_config(show_pppoe_status *show_pppoe_status);   
    
WS_ERR network_start_dhcp();
WS_ERR network_stop_dhcp();
ws_net_link_state network_get_netlink_status(const char *if_name);
WS_ERR network_get_address(net_info_get type, const char *if_name, char *address, size_t buf_size);
char *network_getsegment(const char *localip, const char *netmask, char *semgentip);

WS_ERR network_set_wifi_enable(WS_BOOL enable);
int network_wifi_get_accesspoints(WLAN_ACCESSPOINT aps[ws_utility::WS_MAX_AP_NUM], int *count);
int network_set_wifi_connect(LPWLAN_CONNECTION conn);
WS_ERR network_get_wifi_conn_status(WS_BOOL *status, char ssid[ws_utility::WS_MAX_SSID_LEN], char mac[ws_utility::WS_NVR_MAC_STRING_LEN]);
WS_ERR network_get_wlan_connect(ws_local_connect_cfg *ip_info);
WS_ERR network_set_wlan_connect(const ws_local_connect_cfg *ip_info);
WS_ERR network_init_wifi(WS_BOOL bEnable, const ws_local_connect_cfg *ip_info);

void network_set_ntp_func(set_sys_new_time pcall);

/* add by zhangmq 20180527 start*/
//add zmq  cfg_manage模块相关的网络接口移入[2018-05-03 17:43]
WS_ERR resume_sys_cfg();
WS_ERR resume_net_cfg();
WS_ERR resume_basic_net_cfg();
WS_ERR resume_time_cfg();
WS_ERR resume_port_cfg();
WS_ERR resume_ntp_cfg();

WS_ERR cfg_manage_get_local_connnect_cfg(ws_local_connect_cfg *cfg);
WS_ERR cfg_fac_manage_get_local_connnect_cfg(ws_local_connect_cfg *cfg);
WS_ERR cfg_manage_set_local_connnect_cfg(const ws_local_connect_cfg *cfg);
WS_ERR cfg_manage_get_net_port_cfg(ws_net_port_cfg *cfg);
WS_ERR cfg_fac_manage_get_net_port_cfg(ws_net_port_cfg *cfg);
WS_ERR cfg_manage_set_net_port_cfg(const ws_net_port_cfg *cfg);


//add zmq  网络参数设置[2018-05-03 19:47]
//------------------------------------对ntp所需的配置文件------------------------------------------------------
WS_ERR cfg_manage_set_ntp_cfg(const ws_ntpc_config *ntp_ccfg);

#if defined(_SUPPORT_TIME_TYPE_AND_STANDARD_)
WS_ERR cfg_manage_set_time_type_cfg(ws_soft::ws_gui_show_time_type time_type);
WS_ERR cfg_manage_set_time_standard(ws_soft::ws_gui_time_standard time_standard);
WS_ERR  cfg_manage_set_dst_config(dst_setting dst_config);
WS_ERR cfg_manage_get_time_type(ws_gui_show_time_type *time_type);
WS_ERR cfg_manage_get_time_standard(ws_gui_time_standard *time_standard);
WS_ERR cfg_manage_get_dst_config(dst_setting *dst_config);
#endif 

WS_ERR cfg_manage_get_ntp_cfg(ws_ntpc_config *ntp_ccfg);
WS_ERR cfg_fac_manage_get_ntp_cfg(ws_ntpc_config *ntp_ccfg);

//-------------------------------------pppoe所需的配置文件-----------------------------------------------------
WS_ERR cfg_manage_get_pppoe_cfg(ws_pppoe_config *pppoe_config);
WS_ERR cfg_fac_manage_get_pppoe_cfg(ws_pppoe_config *pppoe_config);
WS_ERR cfg_manage_set_pppoe_cfg(const ws_pppoe_config *pppoe_config);
WS_ERR resume_pppoe_cfg();

//-------------------------------------私有DNS所需的配置文件-----------------------------------------------------
WS_ERR cfg_manage_get_pri_dns_cfg(ws_pri_dns_config *pri_dns);
WS_ERR cfg_fac_manage_get_pri_dns_cfg(ws_pri_dns_config *pri_dns);
WS_ERR cfg_manage_set_pri_dns_cfg(const ws_pri_dns_config *pri_dns);
WS_ERR resume_ddns_cfg();

//-------------------------------------smtp所需的配置文件-----------------------------------------------------
WS_ERR cfg_manage_get_email_cfg(ws_email_sender_cfg *email_sender);
WS_ERR cfg_fac_manage_get_email_cfg(ws_email_sender_cfg *email_sender);
WS_ERR cfg_manage_set_email_cfg(const ws_email_sender_cfg *email_sender);

WS_ERR cfg_manage_get_email_reciver_count(WS_S32 *recv_num);
WS_ERR cfg_fac_manage_get_email_reciver_count(WS_S32 *recv_num);
WS_ERR cfg_manage_get_email_reciver_cfg(WS_S32 recv_num, ws_reciver_add *reciver_addr);
WS_ERR cfg_fac_manage_get_email_reciver_cfg(WS_S32 recv_num, ws_reciver_add *reciver_addr);
WS_ERR cfg_manage_add_email_reciver_cfg(const ws_reciver_all *reciver_addr);

WS_ERR cfg_manage_get_receiver_all(WS_S32 *total_num, ws_reciver_all *reciver_addr);
WS_ERR resume_smtp_cfg();

//----------------------------------------时区----------------------------------------------------
WS_ERR cfg_manage_set_time_zone(time_zone_type set_num);
WS_ERR cfg_manage_get_time_zone(time_zone_type *set_num);
WS_ERR cfg_fac_manage_get_time_zone(time_zone_type *set_num);
WS_ERR cfg_manage_set_dst_enable(WS_BOOL is_enable);
WS_BOOL cfg_manage_get_dst_enable();

//---------------------------------------wifi-----------------------------------------------------
WS_ERR cfg_manage_set_wifi_enable(WS_BOOL is_enable);
WS_BOOL cfg_manage_get_wifi_enable();
WS_ERR cfg_manage_set_wifi_connect_mode(int mode);
WS_ERR cfg_manage_get_wifi_connect_mode(int *mode);
WS_ERR cfg_manage_get_wifi_ip_info(ws_local_connect_cfg *ip_info);
WS_ERR cfg_manage_set_wifi_ip_info(const ws_local_connect_cfg *ip_info);
WS_ERR cfg_manage_get_wifi_ap_info(LPWLAN_CONNECTION ap_info);
WS_ERR cfg_manage_set_wifi_ap_info(const LPWLAN_CONNECTION ap_info);
WS_ERR resume_wifi_cfg();

//--------------------------------ipc同步时间----------------------------------------------------
WS_BOOL cfg_manage_get_enable_sync_ipc_time();
WS_BOOL cfg_fac_manage_get_enable_sync_ipc_time(WS_BOOL *sync_ipc_time);
WS_ERR cfg_manage_set_enable_sync_ipc_time(WS_BOOL enable);
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_NETWORK_API_H_


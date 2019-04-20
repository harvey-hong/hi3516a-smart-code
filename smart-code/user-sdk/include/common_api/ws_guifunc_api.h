#ifndef _WS_GUIFUNC_API_H_
#define _WS_GUIFUNC_API_H_
#include <sys/types.h>
#include <unistd.h>

#include "ws_comm_debug.h"
#include "ws_comm_errno.h"
#include "ws_utility_api.h"
#include "ws_model_api.h"
#include "ws_comm_av.h"

using namespace ws_soft;
using namespace ws_utility;

namespace ws_guifunc
{
    int guifunc_enc_3des( const char *src_buf, size_t src_size, char *dst_buf,  const char *key);
    int guifunc_dec_3des(const char *src_buf, size_t src_size, char *dst_buf, const char *key);
    
    WS_ERR guifunc_PushAlarmEvent(ws_event_serial_type evt, WS_U32 number, WS_U32 chan, time_t time);
    WS_ERR guifunc_send_cancel_shutdown_to_mcu();
    WS_BOOL guifunc_playback_is_pb_ch_have_data(WS_U32 pb_ch);

#if defined(_SUPPORT_POLL_LIVE_)
    WS_ERR guifunc_get_live_poll_enabel_state(WS_BOOL *has_enable);
    WS_ERR guifunc_set_live_poll_enabe_state(WS_BOOL is_set);
    WS_ERR guifunc_get_live_poll_info(ws_utility::ws_poll_live_type_e poll_type, ws_utility::ws_user_cfg_poll_live_s *cfg_info, WS_U32 ch_max_num);
#endif

    WS_ERR guifunc_get_lv_last_div_info(ws_utility::ws_screen_div_mode *div_mode,WS_U32* ch_mask, WS_U32 ch_mask_num);
    /*change by linhh 20170428 for update device and save div_mode*/
    WS_ERR guifunc_set_lv_last_div_info(ws_utility::ws_screen_div_mode  div_mode,WS_U32 *ch_mask, WS_U32 ch_mask_num, WS_BOOL bCfgSave);
    WS_ERR guifunc_usr_manual_snap_pic(WS_U32 ch_idx);
    
WS_ERR guifunc_open_pack_for_xml(const WS_CHAR *directory,xml_file_attr_t *flist,size_t *flist_num,int *real_num);
WS_BOOL guifunc_open_pack(const WS_CHAR *directory,update_file_attr_t *flist,size_t *flist_num,int *real_num);

WS_ERR guifunc_get_dev_channel_num(WS_U32* analog, WS_U32* digit);

WS_ERR guifunc_check_login_authority(WS_USR_HAND login_hand,ws_authority_check_type check_type,WS_ERR *is_authority,WS_ERR *is_vailed );

const ws_utility::ws_device_capability* guifunc_get_dev_capability();

WS_ERR guifunc_get_trig_cfg(WS_USR_HAND hand, ws_trig_source src_type, WS_U32 src_ch, ws_trig_operation *operation);

WS_ERR guifunc_set_trig_cfg(WS_USR_HAND hand, ws_trig_source src_type, WS_U32 src_ch, ws_trig_operation *operation);

WS_ERR guifunc_set_link_rec_by_md(WS_USR_HAND hand, WS_U32 rec_ch, WS_U32 *md_link, WS_U32 mask_num);

WS_ERR guifunc_set_link_rec_by_ai(WS_USR_HAND hand, WS_U32 rec_ch, WS_U32 *ai_link, WS_U32 mask_num);
 
WS_ERR guifunc_get_live_poll_cfg_info(ws_soft::ws_event_type type, WS_BOOL* link_data,WS_U32* data_len);	

//==========================alarm_config=========================
WS_ERR guifunc_get_ai_check_type(WS_USR_HAND hand, WS_U32 ai_ch, ws_ai_check_type *type);

WS_ERR guifunc_set_ai_check_type(WS_USR_HAND hand, WS_U32 ai_ch, ws_ai_check_type type);

WS_ERR guifunc_get_ai_config(WS_USR_HAND hand,WS_U32 ch,ws_ai_config* config);
WS_ERR guifunc_set_ai_config(WS_USR_HAND hand,WS_U32 ch,ws_ai_config* config);
WS_ERR guifunc_get_ao_config(WS_USR_HAND hand,WS_U32 ch,ws_ao_config* config);
WS_ERR guifunc_set_ao_config(WS_USR_HAND hand,WS_U32 ch,ws_ao_config* config);
WS_ERR guifunc_get_event_info(WS_USR_HAND hand,ws_event_type type,WS_U32 ch_idx, ws_event_info *info);
WS_ERR guifunc_set_ao_hold_time(WS_USR_HAND hand,  WS_U32 ch,WS_U32 secs); 
WS_ERR guifunc_get_ao_hold_time(WS_USR_HAND hand,  WS_U32 ch,WS_U32* secs);

//add by qqy,start at 2017-02-09 16:18:18
WS_ERR guifunc_set_event_deployment_time(WS_USR_HAND hand ,WS_U32 ch_idx , ws_event_type type , ws_rec_schedule_day day, const ws_rec_schedule_per_day *schedule);

WS_ERR guifunc_get_event_deployment_time(WS_USR_HAND hand ,WS_U32 ch_idx , ws_event_type type , ws_rec_schedule_day day, ws_rec_schedule_per_day *schedule);

//change by khs 2017.3.21 start
WS_ERR guifunc_set_event_deployment_time_ex(WS_USR_HAND hand ,ws_event_type type ,WS_U32 ch_idx, const ws_channel_rec_schedule *schedule);

WS_ERR guifunc_get_event_deployment_time_ex(WS_USR_HAND hand ,ws_event_type type ,WS_U32 ch_idx, ws_channel_rec_schedule *schedule);
//change by khs 2017.3.21 end
//add by qqy,end at 2017-02-09 16:18:21

//==========================alarm_info=========================
WS_ERR guifunc_query_log_hand(WS_USR_HAND hand, const ws_log_inquiry_ctl *inquiry_ctl, ws_log_table_hand *log_hand, WS_U32 *log_num);
WS_ERR guifunc_get_log_result(WS_USR_HAND hand,const ws_log_table_hand log_hand,WS_U32 * start_num,WS_U32 * total_num,ws_log_inquiry_result_pro * log_result);
WS_ERR guifunc_free_log_result(WS_USR_HAND hand,ws_log_table_hand * log_hand);
WS_ERR guifunc_cancel_alarm(WS_USR_HAND hand);

//==========================back_up=========================

WS_ERR guifunc_get_search_time_wind(ws_time_struct *startTime,ws_time_struct *endTime,char edit_buf[][32]);

WS_ERR guifunc_get_backup_progress(WS_USR_HAND hand, WS_U32 *percent, WS_U32 disk_idx);       

WS_ERR guifunc_get_usb_disk_num(WS_U32 *num);

WS_ERR guifunc_get_usb_disk_info(WS_U32 disk_idx, ws_usb_disk_info *info);

WS_ERR guifunc_stop_backup(WS_USR_HAND hand);

WS_ERR guifunc_backup_get_last_type(ws_usb_dev_type *dev_type, WS_U32 disk_idx , ws_usb_disk_info *info);    

WS_ERR guifunc_start_backup(WS_USR_HAND hand, WS_U32 disk_idx,  WS_U32 part_idx , ws_backup_file_type file_type, 
        ws_rec_file_inquiry_result *inquiry_ret, ws_snap_file_inquiry_result *inquiry_snap_ret, WS_BOOL* file_operate, WS_U32 file_cnt );

//==========================bar=========================

WS_ERR guifunc_set_manual_rec_enable_ex(WS_USR_HAND hand, WS_BOOL enable);
WS_ERR guifunc_get_manual_rec_enable_ex(WS_U32 nvr_ch, WS_BOOL *enable);    

//==========================channel config=========================

WS_ERR guifunc_set_default_isp_para(WS_USR_HAND hand, WS_U32 rmt_ch);
WS_ERR guifunc_set_default_exposure_para(WS_USR_HAND hand, WS_U32 rmt_ch);
 
WS_ERR guifunc_get_cha_info(WS_USR_HAND hand, WS_U32 rmt_ch, const ws_venc_str_type str_type, ws_enc_para *para);

WS_ERR guifunc_set_cha_info(WS_USR_HAND hand, WS_U32 rmt_ch, const ws_venc_str_type str_type, ws_enc_para *para);

WS_ERR guifunc_get_cha_state(WS_USR_HAND hand, WS_U32 rmt_ch,ws_agent_ch_state * state);

WS_ERR guifunc_get_enc_input_fps(WS_U32 ch_idx, WS_S32 *enc_input_fps);

WS_ERR guifunc_resume_auto_search();

WS_ERR guifunc_set_rmt_connect_rule(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_connet_rule *rule,WS_U32* taskId); 

WS_ERR guifunc_get_rmt_connect_rule(WS_USR_HAND hand, WS_U32 nvr_ch, WS_BOOL *ch_state, ws_connet_rule *rule);

WS_ERR guifunc_refresh_probe();

WS_ERR guifunc_get_search_num(WS_U32 *dev_idx);

WS_ERR guifunc_get_remote_dev_info(WS_U32 dev_idx, ws_remote_dev_info *info);

WS_ERR guifunc_get_rmt_connect_info(WS_USR_HAND hand, WS_U32 nvr_ch, ws_connect_dev_info *info);

WS_ERR guifunc_cmp_channel_ip_addr(const char *ip);

WS_BOOL guifunc_inquiry_whether_IPC_is_connected(WS_U32 rmt_ch, const ws_connet_config *cfg, char *ipv4, int ip_length, char *mac, int mac_length);

WS_ERR guifunc_get_channel_bit_rate(WS_U32 rmt_ch, WS_U32 *get_bit);

WS_ERR guifunc_get_sub_channel_bit_rate(WS_U32 rmt_ch, WS_U32 *get_bit);

WS_ERR guifunc_get_sdi_connect_state(WS_U32 nvr_ch, WS_BOOL *ch_state);

ws_rec_file_trig_type guifunc_get_ch_rec_state(WS_U32 rec_ch); //Modified by qqy, at 2017-03-10 10:00:38

WS_ERR guifunc_set_pri_dns_cfg(WS_USR_HAND hand, const ws_pri_dns_config *pri_dns, WS_DDNS_ERR *status);

WS_ERR guifunc_get_pri_dns_cfg(WS_USR_HAND hand, ws_pri_dns_config *pri_dns);

WS_ERR guifunc_start_pri_ddns(WS_USR_HAND hand,char *user_domain,WS_DDNS_ERR *ser_return_status);

WS_ERR guifunc_start_ddns(WS_USR_HAND hand);

WS_ERR guifunc_stop_ddns(WS_USR_HAND hand);

WS_ERR guifunc_get_dns_connect_status(WS_USR_HAND hand, connect_status *con_status);

WS_ERR guifunc_get_dns_default_domain(char *def_domain, size_t def_domain_size);

const ws_support_resol *guifunc_get_support_resol();

WS_ERR guifunc_get_local_mac(char *macc,size_t mac_buf_size);

WS_ERR guifunc_get_screen_amout(int *screen_amount);

WS_ERR guifunc_register_pro_dest(log_content_trans_pro func,log_title_trans func2,set_language func3,get_support_language_num func4,get_support_language_name func5,get_time_zone_name func6,add_happen_event_node func7);

WS_ERR guifunc_get_ptz_speed(WS_USR_HAND hand, WS_U32 ch, WS_U32 *speed);

WS_ERR guifunc_get_protocol_list_info(WS_USR_HAND hand, ws_ptz_protocol_info_list * * list_info, WS_U32 * protocol_num);

WS_ERR guifunc_get_support_ptz_protocol(WS_USR_HAND hand, ws_ptz_protocol_info *protocol_info);

WS_ERR guifunc_get_support_ptz_baudrate(WS_USR_HAND hand, ws_ptz_baudrate_info *baudrate_info);

WS_ERR guifunc_set_ptz_speed(WS_USR_HAND hand, WS_U32 ch, WS_U32 speed);

WS_ERR guifunc_get_all_disk_info(WS_USR_HAND hand, ws_hard_disk_info *info, WS_U32 arr_len, WS_U32  *disk_num);

WS_ERR guifunc_get_hard_disk_info(WS_USR_HAND hand, const char*  serial_no, ws_hard_disk_info *info);

WS_ERR guifunc_filter_disk_info(WS_USR_HAND hand, ws_hard_disk_info *info, WS_U32 arr_len);

WS_ERR guifunc_get_completed_disk_info(WS_USR_HAND hand, ws_hard_disk_info *info, WS_U32 arr_len,WS_U32* num); 

WS_ERR guifunc_get_hard_disk_num(WS_USR_HAND hand, WS_U32 *num);

WS_U32 guifunc_qr_create(int nLevel, int nVersion , char *lpsSource, int sourcelen, char *QR_m_data, size_t QR_m_data_size);

WS_ERR guifunc_start_talking();
WS_ERR guifunc_stop_talking(); 
WS_ERR guifunc_play_talking(WS_USR_HAND hand); 

WS_ERR guifunc_buzzer_test(WS_USR_HAND hand, WS_U32 msecs);

WS_ERR guifunc_password_reset_test(WS_USR_HAND hand, WS_BOOL *reset_state);

WS_ERR guifunc_set_alarm_out_control(const WS_U32 pin, gpio_alarm_out_ctl ctl);

WS_ERR guifunc_set_ch_ptz_ctl(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_ptz_ctl_info *ctl_info);

WS_ERR guifunc_ptz_cmd_control(WS_USR_HAND hand, WS_U32 rmt_ch, PTZ_CMD_ID cmd, WS_U32 para);

WS_ERR guifunc_get_exception(WS_USR_HAND hand, exception_type type, exception_control *excep_ctr);

WS_ERR guifunc_set_exception(WS_USR_HAND hand, const exception_linkage *excep);

WS_ERR guifunc_sys_resume_default(WS_USR_HAND hand,  WS_U32 mask);

WS_ERR guifunc_sys_resume_default_ex(WS_USR_HAND hand,  WS_U32 mask); 

WS_ERR guifunc_sys_reboot(WS_USR_HAND hand,WS_BOOL flag=WS_FALSE);

WS_ERR guifunc_local_login(const WS_CHAR *usr_name, const char *password, WS_USR_HAND *hand);


WS_ERR guifunc_check_authority(WS_USR_HAND hand, ws_authority_check_type check_type);

WS_ERR guifunc_logout(WS_USR_HAND hand);

WS_ERR guifunc_set_channel_name(WS_USR_HAND hand, WS_U32 ch, const char *name_buf, const WS_VOID *bitmap, WS_U32 width, WS_U32 height);

WS_ERR guifunc_init_get_channel_name(WS_U32 ch, char *name_buf, size_t size);

WS_ERR guifunc_get_time_zone(WS_USR_HAND hand, time_zone_type *set_num);

WS_ERR guifunc_set_rmt_disconnect_rule(WS_USR_HAND hand, WS_U32 nvr_ch);

WS_ERR guifunc_set_resol();

WS_ERR guifunc_get_slot_num(WS_USR_HAND hand, WS_U32* slot_num);

WS_ERR guifunc_format_hard_disk(WS_USR_HAND hand, const char*  serial_no, WS_U32 part_idx = 0);

WS_ERR guifunc_format_hard_disk_get_info(WS_USR_HAND hand, ws_disk_serial*  serial_no, WS_S32* nNum );

WS_ERR guifunc_format_hard_disk_get_num_scsi(WS_USR_HAND hand, WS_S32* nNum , WS_S32* scsi_no);

WS_ERR guifunc_cancel_format_hard_disk(WS_USR_HAND hand, const char*  serial_no);

WS_ERR guifunc_get_hard_disk_state(WS_USR_HAND hand, const char*  serial_no, ws_hard_disk_state *state); 

WS_ERR guifunc_get_hard_disk_state_progress(WS_USR_HAND hand, const char*  serial_no, ws_hard_disk_state *state, int* percent); 

WS_ERR guifunc_set_isp_sdi_info(WS_USR_HAND hand,ws_isp_type set_type, int set_val);

WS_ERR guifunc_set_isp_info(WS_USR_HAND hand, WS_U32 rmt_ch, ws_isp_type set_type, int set_val);

WS_ERR guifunc_get_isp_info(WS_USR_HAND hand, WS_U32 rmt_ch, ws_isp_image *get_image, ws_isp_exposure *get_exposure);

WS_ERR guifunc_get_default_isp_info(WS_USR_HAND hand, WS_U32 rmt_ch, ws_isp_image *get_image, ws_isp_exposure *get_exposure);

WS_ERR guifunc_save_language(WS_USR_HAND hand, const WS_CHAR *language);

WS_ERR guifunc_get_cfg_language(WS_USR_HAND hand, WS_CHAR *language, size_t buf_size);

WS_BOOL guifunc_get_event_state(WS_U32 ch,ws_event_type  event_type); //add by qqy, at 2017-02-27 11:18:47

//live screen
WS_ERR guifunc_live_move_roi_rect(WS_S32 nvr_ch, const ws_abstract_coordinate *start, const ws_abstract_coordinate *stop);

WS_ERR guifunc_live_mouse_set_roi(WS_S32 nvr_ch, const ws_abstract_coordinate *roi_coor, WS_BOOL amplif);

WS_ERR guifunc_cancel_live_roi(WS_U32 nvr_ch);

WS_ERR guifunc_match_osd_info(int focus_channel,int *name_idx,int *time_idx,int *find_num,channel_display_info *g_chn_dp_area,display_area *display_control, int display_num);	// change by ljx date 2015.06.03

WS_ERR guifunc_set_osd_area(WS_USR_HAND hand, WS_U32 ch, ws_osd_type dp_tp, ws_location_type loc_tp);

WS_ERR guifunc_set_time_type_and_standard(WS_USR_HAND hand,ws_time_type_and_standard * time_type_and_standard);

WS_ERR guifunc_get_osd_channel_name(WS_USR_HAND hand, WS_U32 ch, char *name_buf, size_t size); //add by qqy, at 2017-01-17 19:45:33

WS_ERR guifunc_get_osd_area(WS_USR_HAND hand, WS_U32 ch, ws_osd_type dp_tp, ws_location_type *loc_tp);

WS_ERR guifunc_stop_audio_live(WS_U32 channel);

WS_ERR guifunc_start_audio_live(WS_U32 channel);

WS_ERR guifunc_stop_live();

WS_ERR guifunc_start_live(const ws_display_screen_info *screen_info, const ws_wind_content *wind_content, size_t content_dim);

WS_ERR guifunc_get_usr_num(WS_U32 *usr_num);

WS_ERR guifunc_get_usr_name(WS_U32 usr_idx, WS_CHAR *usr_name, size_t name_size);

WS_ERR guifunc_register_smtp_get_txt(ws_smpt_get_str_func pcall);

WS_ERR guifunc_register_set_channel_func(set_chn_name func);

WS_ERR guifunc_register_reset_admin_passwd_func(reset_admin func);	

WS_ERR guifunc_set_md_info(WS_USR_HAND hand, WS_U32 rmt_ch, const ws_md_arr *md_arr);

WS_ERR guifunc_get_md_info(WS_USR_HAND hand, WS_U32 rmt_ch, ws_md_arr *md_arr);

WS_ERR guifunc_get_md_allalarm(WS_USR_HAND hand, WS_U32 rmt_ch, WS_U32 *p_allalarm);

WS_ERR guifunc_get_local_connect_cfg(WS_USR_HAND hand, ws_local_connect_cfg *cfg);

WS_ERR guifunc_get_net_port_cfg(ws_net_port_cfg *cfg);

WS_ERR guifunc_set_local_connect_cfg(WS_USR_HAND hand, const ws_local_connect_cfg *cfg);

WS_ERR guifunc_set_net_port_cfg(WS_USR_HAND hand, ws_net_port_cfg *cfg);

WS_ERR guifunc_osd_check_legal(WS_U32 *channel_array, WS_U32 array_dim, WS_U32 *channel_count,channel_display_info *g_chn_dp_area);

WS_ERR guifunc_stop_audio_pb(WS_USR_HAND hand, WS_U32 pb_ch);

WS_ERR guifunc_set_pb_speed(WS_USR_HAND hand, ws_playback_speed speed);

WS_ERR guifunc_seek_pb_time(WS_USR_HAND hand, time_t time,WS_BOOL has_reflash = WS_FALSE,WS_BOOL need_lock=WS_FALSE);	

WS_ERR guifunc_inquiry_rec_by_month(WS_USR_HAND hand, const ws_time_struct *time, WS_U32 *mask);

WS_ERR guifunc_inquiry_snap_by_month(WS_USR_HAND hand, const ws_time_struct *time, WS_U32 *mask);

WS_ERR guifunc_get_pb_time(WS_USR_HAND hand, time_t *time);

WS_ERR guifunc_pause_pb(WS_USR_HAND hand);

WS_ERR guifunc_resume_pb(WS_USR_HAND hand);

WS_ERR guifunc_set_focus_channel(WS_USR_HAND hand,int ch);

WS_ERR guifunc_set_pb_dir(WS_USR_HAND hand, ws_playback_direction dir);

WS_ERR guifunc_stop_pb_wind(WS_USR_HAND hand);
WS_ERR guifunc_set_ch_mode(WS_USR_HAND hand,WS_BOOL ch_mode,WS_U32 ch);//add by khs 2017.6.28


WS_ERR guifunc_set_pb_mode(WS_USR_HAND hand, ws_playback_mode mode);

WS_ERR guifunc_set_channel(WS_USR_HAND hand,WS_U32 ch,WS_U32 channel);//add by khs 2017.7.14

WS_ERR guifunc_set_pb_rec_file(WS_USR_HAND hand, WS_U32 pb_ch, const /*ws_rec_file_inquiry_result */ws_pb_rec_file_inquiry_result*source, const file_result_handle* hdls);

WS_ERR guifunc_set_pb_snap_file(WS_USR_HAND hand, WS_U32 pb_ch, const /*ws_snap_file_inquiry_result*/ws_pb_snap_file_inquiry_result *source,const file_result_handle* hdls);

WS_ERR guifunc_set_pb_interval_time(WS_USR_HAND hand, WS_U32 interval_time_ms);

WS_BOOL guifunc_get_pb_is_end(WS_USR_HAND hand, WS_S32 nvr_ch);    
    
WS_ERR guifunc_start_pb(WS_USR_HAND hand, time_t time, time_t end_time = 0xffffffff);

WS_ERR guifunc_set_end_time(WS_USR_HAND hand,time_t end_time = 0xffffffff); 

WS_ERR guifunc_start_audio_pb(WS_USR_HAND hand, WS_U32 pb_ch);

WS_ERR guifunc_stop_pb(WS_USR_HAND hand);

WS_ERR guifunc_step_pb(WS_USR_HAND hand, ws_playback_step_mode mode);

WS_ERR guifunc_pb_move_roi_rect(WS_USR_HAND hand, WS_S32 nvr_ch, const ws_abstract_coordinate *start, const ws_abstract_coordinate *stop);

WS_ERR guifunc_pb_mouse_set_roi(WS_USR_HAND hand, WS_S32 nvr_ch, const ws_abstract_coordinate *roi_coor, WS_BOOL amplif);

WS_ERR guifunc_cancel_pb_roi(WS_USR_HAND hand, WS_U32 pb_ch);

WS_ERR guifunc_set_pb_wind(WS_USR_HAND hand, const ws_display_screen_info *screen_info, const ws_wind_content *wind_content, size_t content_dim);

WS_ERR guifunc_sys_poweroff(WS_USR_HAND hand);

//pppoe
WS_ERR guifunc_get_show_pppoe_status(WS_USR_HAND hand,show_pppoe_status *show_pppoe_status); 

WS_ERR guifunc_get_pppoe_cfg(WS_USR_HAND hand, ws_pppoe_config *cfg);

WS_ERR guifunc_set_pppoe_cfg(WS_USR_HAND hand, const ws_pppoe_config *cfg);

WS_ERR guifunc_get_exception_state(exception_type type, WS_U32 *exception_state);

WS_ERR guifunc_set_exception_state(exception_type type, WS_U32 exception_state);	

WS_ERR guifunc_get_operate_state(ws_operate_type  opt_type ,WS_BOOL	*flag);

WS_ERR guifunc_get_ptz_cruise_line(WS_USR_HAND hand, WS_U32 ch, ws_ptz_ctl_type protocol, ws_ptz_cruise_line * cruise_line);

WS_ERR guifunc_get_ch_ptz_ctl(WS_USR_HAND hand, WS_U32 nvr_ch, ws_ptz_ctl_info *ctl_info);

WS_ERR guifunc_get_rec_holiday_enable(WS_USR_HAND hand, WS_U32 nvr_ch, WS_BOOL *enable);

WS_ERR guifunc_record_apply_cfg_of_holiday(WS_USR_HAND hand, ws_rec_schedule_holiday* schedule);

void guifunc_copy_to_for_time(int ret,int chan_idx,int copy_all,ws_rec_schedule_time *m_schedule_time,ws_rec_schedule_per_day *g_record_all_day,WS_BOOL holiday_enable);
WS_ERR guifunc_record_read_cfg_of_holiday(WS_USR_HAND hand,ws_rec_schedule_holiday *m_schedule);

WS_ERR guifunc_record_apply_cfg_of_time(WS_USR_HAND hand, ws_rec_schedule_time* schedule);

WS_ERR guifunc_record_apply_cfg_of_time_ex(WS_USR_HAND hand, ws_channel_rec_schedule* schedule,int ch_idx);//add by khs 2017.3.29

WS_ERR guifunc_record_read_cfg_of_time(WS_USR_HAND hand,ws_rec_schedule_time *m_schedule);

WS_ERR guifunc_record_read_cfg_of_time_ex(WS_USR_HAND hand,ws_channel_rec_schedule *m_schedule,int ch_idx);//add by khs 2017.3.29

WS_ERR guifunc_set_resol(const WS_CHAR *resol);

WS_ERR guifunc_save_resol(const WS_CHAR *resol);     

WS_ERR guifunc_init_logo(ws_logo_type type, int *bit, int bit_w, int bit_h, int bg_color);

WS_ERR guifunc_get_channel_name(WS_U32 channel_count,WS_CHAR *channel_idx,WS_U32 *channel_array);

WS_ERR guifunc_init_channel_name(WS_U32 ch, const char *name_buf, const WS_VOID *bitmap, WS_U32 width, WS_U32 height);

WS_ERR guifunc_export_log_file_ex(WS_USR_HAND hand, const WS_CHAR *file_name, ws_language_type language, const ws_log_inquiry_ctl *inquiry_ctl);

//smtp
WS_ERR guifunc_get_email_sender_cfg(WS_USR_HAND hand, ws_email_sender_cfg *cfg);

WS_ERR guifunc_check_email_legal(WS_USR_HAND hand,WS_CHAR * check_name,WS_U32 num_of_check_name);//add by lmw 20170516

WS_ERR guifunc_get_email_receiver_num(WS_S32 *num);

WS_ERR guifunc_get_email_receiver_name(WS_S32 receiver_idx, ws_reciver_add *reciver_addr);

WS_ERR guifunc_send_email_tst(WS_USR_HAND hand, const ws_email_sender_cfg *cfg, const ws_reciver_all *reciver_addr, int reciver_num, const ws_email_attachment *attachment, const char *title, const char *buf);

WS_ERR guifunc_set_email_sender_cfg(WS_USR_HAND hand, ws_email_sender_cfg *cfg);

WS_ERR guifunc_add_email_receiver(WS_USR_HAND hand, const ws_reciver_all *reciver_addr);

WS_ERR guifunc_start_dhcp(WS_USR_HAND hand);

WS_ERR guifunc_stop_dhcp(WS_USR_HAND hand);

WS_ERR guifunc_get_dhcp(WS_USR_HAND hand);

WS_ERR guifunc_get_disk_work_ctl(WS_USR_HAND hand, ws_hard_disk_work_ctl *ctl);

WS_ERR guifunc_save_dev_name(WS_USR_HAND hand, const char *buf);

WS_ERR guifunc_save_lock_time(WS_USR_HAND hand,const char *buf);

WS_ERR guifunc_set_disk_work_ctl(WS_USR_HAND hand, const ws_hard_disk_work_ctl *ctl);

WS_ERR guifunc_get_dev_name(WS_USR_HAND hand, char *buf, size_t buf_size);

WS_ERR guifunc_check_legal(WS_USR_HAND hand,WS_CHAR * check_name,WS_U32 num_of_check_name);//add by lmw 20170516

#if defined(_SUPPORT_TIME_TYPE_AND_STANDARD_)
WS_ERR guifunc_dst_change_dev_time(WS_USR_HAND hand, char *date_buf,char *time_buf);
#endif

WS_BOOL guifunc_get_dst_enable();

WS_ERR guifunc_get_ntp_server(WS_USR_HAND hand, ws_ntpc_config *ntp_ccfg);
WS_ERR guifunc_get_ntp_status(WS_USR_HAND hand);
WS_ERR guifunc_get_time_type(WS_USR_HAND hand, ws_gui_show_time_type *time_type);
WS_ERR guifunc_get_time_standard(WS_USR_HAND hand,ws_gui_time_standard* time_standard);

const ws_support_time_zone *guifunc_get_support_time_zone();

WS_BOOL guifunc_get_sync_ipc_time_enbale();

WS_ERR guifunc_set_ntp_server(WS_USR_HAND hand, const ws_ntpc_config *ntp_ccfg);

#if defined(_SUPPORT_TIME_TYPE_AND_STANDARD_)
WS_ERR guifunc_set_show_time_type(WS_USR_HAND hand,ws_gui_show_time_type time_type);

WS_ERR guifunc_set_time_standard(WS_USR_HAND hand,ws_gui_time_standard time_standard);
WS_ERR guifunc_set_dst_config(WS_USR_HAND hand,dst_setting dst_config);
#endif 

WS_ERR guifunc_set_sync_ipc_time_enbale(WS_USR_HAND hand, WS_BOOL enable);

WS_ERR guifunc_set_dst_enable(WS_USR_HAND hand, WS_BOOL is_enable);

WS_ERR guifunc_set_time_zone(WS_USR_HAND hand, time_zone_type set_num);

WS_ERR guifunc_start_packet(WS_USR_HAND hand, const WS_CHAR *packet_fname, WS_BOOL auto_del_packet);

WS_U32 guifunc_get_update_percent();

WS_ERR guifunc_new_upload_sys_file(WS_USR_HAND hand, WS_U32 rmt_ch, const char *filename,WS_U32 *taskId);

WS_ERR guifunc_stop_remote_task(WS_USR_HAND hand,WS_U32 rmt_ch,WS_U32 taskId);

WS_ERR guifunc_get_remote_upgrade_status(WS_USR_HAND hand,WS_U32 rmt_ch, int *upgradeStatus); 

WS_ERR guifunc_get_group_num(WS_USR_HAND hand, WS_U32 *group_num);

/* add by zhangmq 20180527 */
//add zmq 仅为兼容内存文件的方式,增加此接口,上方只有一处调用[2018-05-16 15:19]
WS_ERR guifunc_get_valid_group_num(WS_USR_HAND hand, WS_U32 *group_num);

WS_ERR guifunc_get_group_authority(const WS_CHAR *group_name, ws_authority *authority);

WS_ERR guifunc_get_group_name(WS_USR_HAND hand, WS_U32 group_idx, WS_CHAR *group_name, size_t name_size);

WS_ERR guifunc_add_group(WS_USR_HAND hand, const WS_CHAR *group_name, const ws_authority *authority);

WS_ERR guifunc_del_group(WS_USR_HAND hand, const WS_CHAR *group_name);

WS_ERR guifunc_set_group_authority(WS_USR_HAND hand, const WS_CHAR *group_name, const ws_authority *authority);

WS_BOOL guifunc_is_supper_user(WS_USR_HAND hand);

WS_ERR guifunc_get_group_info_exclude_root(WS_USR_HAND hand, ws_user_group_info* m_group_info, int arry_len, int* nNum);

WS_ERR guifunc_del_usr(WS_USR_HAND hand, const WS_CHAR *usr_name);

WS_BOOL guifunc_is_supper_user_for_name(const char *name);

WS_ERR guifunc_add_usr(WS_USR_HAND hand, const WS_CHAR *usr_name, const char *password, const char *group_name);

WS_ERR guifunc_get_usr_password(WS_USR_HAND hand, WS_CHAR *password, size_t password_size);

WS_ERR guifunc_change_usr_group(WS_USR_HAND hand, const WS_CHAR *usr_name, const char *group);

WS_ERR guifunc_set_usr_passwd(WS_USR_HAND hand, const char *login_password, const WS_CHAR *usr_name, const char *password);

WS_ERR guifunc_get_local_user_show_info(WS_USR_HAND hand, ws_user_and_group_info *usr_info, int arry_len, int* nNum);

//vga setting
WS_ERR guifunc_get_hi_vga_param(HI_VGA_PARAM_S *para);

WS_ERR guifunc_set_hi_vga_param(const HI_VGA_PARAM_S *para);

/* add by zhangmq 20180527 start*/
//add zmq cfg_manage模块中的GUI 层添加接口[2018-03:29 10:03]
WS_ERR guifunc_set_alarm_server_param(LPHY_DVR_ALARMSERVERINFO_IF pcfg);
WS_ERR guifunc_get_alarm_server_param(LPHY_DVR_ALARMSERVERINFO_IF pcfg);
/* add by zhangmq 20180527 end*/

WS_ERR guifunc_set_wifi_enable_ip_ap_info(WS_USR_HAND hand, WS_BOOL is_enable,const ws_local_connect_cfg *ip_info,const LPWLAN_CONNECTION ap_info);

WS_ERR guifunc_get_wifi_ap_connect(WS_USR_HAND hand, ws_wifi_inquiry_result *result);

WS_BOOL guifunc_get_wifi_enable();

WS_ERR guifunc_get_wifi_ip_info(WS_USR_HAND hand, ws_local_connect_cfg *ip_info);

WS_ERR guifunc_get_wifi_ap_info(LPWLAN_CONNECTION ap_info);

WS_ERR guifunc_get_wifi_connect_mode(int *mode);

WS_ERR guifunc_get_wifi_conn_status(WS_BOOL *status, char ssid[WS_MAX_SSID_LEN], char mac[WS_NVR_MAC_STRING_LEN]);

WS_ERR guifunc_set_wifi_connect_mode(WS_USR_HAND hand, int mode);

WS_ERR guifunc_set_wifi_enable(WS_USR_HAND hand, WS_BOOL is_enable);

WS_ERR guifunc_set_wifi_ip_info(WS_USR_HAND hand, const ws_local_connect_cfg *ip_info);

WS_ERR guifunc_set_wifi_ap_info(WS_USR_HAND hand, const LPWLAN_CONNECTION ap_info);

WS_ERR guifunc_set_wifi_connect(WS_USR_HAND hand, const LPWLAN_CONNECTION connect);

/*del func guifunc_rec_schedule_copt_to and guifunc_record_read_cfg by linhh 20170502 */

WS_ERR guifunc_ScheduleTimeCmp(int start_hour,int end_hour,int start_min,int end_min);

WS_ERR guifunc_GetLogSearchTime(char edit_buf[][32],ws_time_struct *startTime,ws_time_struct *endTime);

WS_ERR guifunc_get_inquiry_ctl(int idx0,int idx1,ws_time_struct *start_time,ws_time_struct *endTime,ws_log_inquiry_ctl *inquity);

WS_ERR guifunc_time_is_valid(char edit_buf[][32]);

WS_ERR guifunc_set_playback_ch_pro(int num,ws_log_rec_result_pro *g_result,WS_S32 *ch);

WS_ERR guifunc_set_time_settime(WS_USR_HAND hand,char *date_buf,char *time_buf);

// 备份界面只要求获取数据，如何查询是功能层的事情
WS_ERR guifunc_inquiry_node_by_time(WS_USR_HAND hand, 
                                                                        int* ch_mask, int ch_len, 
                                                                        const ws_utility::ws_time_struct * start_time,const ws_utility::ws_time_struct * stop_time, 
                                                                        WS_U32 file_type,  WS_U32 record_type ,
                                                                        ws_rec_table_hand* rec_hand, ws_snap_table_hand * snap_hand, ws_rec_file_inquiry_result* rec_result, ws_snap_file_inquiry_result* snap_result,
                                                                        WS_U32 * rec_result_num, WS_U32 * snap_result_num, WS_U32 ch_cnt ); 
 
WS_ERR guifunc_free_rec_result(WS_USR_HAND hand,ws_rec_table_hand * rec_hdl);

WS_ERR guifunc_free_snap_result(WS_USR_HAND hand,ws_snap_table_hand * snap_hdl);
WS_BOOL guifunc_inquiry_have_recfile(WS_USR_HAND hand, WS_U32 nvr_ch,const ws_utility::ws_time_struct *start_time,const ws_utility::ws_time_struct *stop_time);
WS_ERR guifunc_clear_event_alarm(WS_USR_HAND hand,ws_soft::ws_event_type event_type, WS_U32 ch_mask);	
WS_ERR guifunc_get_ch_roi_rect_info(WS_U32 ch_idx,WS_BOOL* has_roi,ws_utility::ws_real_rect* rect);			
WS_ERR guifunc_cancel_roi_tmp(WS_U32 ch_idx, WS_BOOL is_cancel_roi);		

WS_ERR guifunc_get_recfile_by_day(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_utility::ws_time_struct *start_time, const ws_rec_file_inquiry_type file_type, ws_rec_table_hand * rec_hld, WS_U32 * rec_num, ws_pb_rec_file_inquiry_result *rec_result, time_t* min_time, time_t *max_time);

WS_ERR guifunc_get_snapfile_by_day(WS_USR_HAND hand,WS_U32 nvr_ch,const ws_time_struct *time, const ws_snap_file_inquiry_type file_type,ws_snap_table_hand * snap_hdl,WS_U32 * snap_num, ws_pb_snap_file_inquiry_result * snap_result, time_t* min_time, time_t *max_time);

WS_ERR guifunc_is_has_data_by_time(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_utility::ws_time_struct *start_time, const ws_utility::ws_time_struct * stop_time, file_inquiry_type file_type, WS_BOOL bRec, WS_U32 * rec_num);

WS_ERR guifunc_get_link_by_md(WS_U32 rec_ch, WS_U32 *md_link, WS_U32 mask_num);

WS_U32 guifunc_get_lock_screen_time();

WS_ERR guifunc_get_osd_info(WS_USR_HAND hand,WS_U32 ch, channel_display_info *osd_info);
void guifunc_copy_channel_location(WS_USR_HAND hand,WS_U32 channel_src, int channel_des,channel_display_info *g_chn_dp_area);
void guifunc_copy_time_location(WS_USR_HAND hand,WS_U32 channel_src, int channel_des,channel_display_info *g_chn_dp_area);

// 20170315 新添加封装
WS_ERR guifunc_get_pb_ch_roi_rect(WS_U32 pb_ch_idx,ws_utility::ws_real_rect* rect);

//add by lmw 20170413
#if 1
WS_ERR  guifunc_base_func_init(char* m_cfg_language, size_t buf_size);
WS_ERR guifunc_init_for_live_osd(const char * dot,WS_S32 dot_num,WS_S32 singel_dot_length, WS_CHAR *srcAsc, WS_U32 curLen);
WS_VOID guifunc_set_osd_time_dot(const char * dot,WS_S32 dot_num,WS_S32 single_dot_length, WS_CHAR *srcAsc, WS_U32 curLen);
#endif
WS_ERR guifunc_check_if_record(WS_USR_HAND hand, WS_BOOL *record_enable);//add by lmw 20170428 

};
#endif


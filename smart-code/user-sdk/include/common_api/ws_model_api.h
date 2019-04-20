#ifndef _WS_MODEL_API_H_
#define _WS_MODEL_API_H_

#include "ws_comm_sys.h"
#include "ws_comm_display.h"
#include "ws_comm_flist.h"
#include "ws_comm_av.h"
#include "ws_comm_type.h"
#include "ws_comm_data.h"
#include "ws_comm_errno.h"

#include "ws_model_def.h"
#include "ws_trigger_def.h"
#include "ws_record_def.h"
#include "ws_playback_def.h"
#include "ws_usr_manage_def.h"
#include "ws_remote_agent_def.h"
#include "ws_disk_manage_def.h"
#include "ws_log_manage_def.h"
#include "ws_ptz_def.h"
#include "ws_dst_def.h"
#include "ws_backup_def.h"
#include "ws_network_def.h"
#include "ws_dev_probe_def.h"
#include "ws_update_def.h"
#include "ws_platform_def.h"
#include "ws_wifi_def.h"
#include "ws_exception_proc_def.h"
#include "ws_utility_def.h"
#include "ws_ddns_def.h"
#include "ws_status_def.h"
#include "ws_utility_api.h"
#include "ws_common.h"     
#include "ws_gpio_def.h"  
#include "HieServer_Cfg.h"

using ws_utility::WS_ERR;           
using namespace ws_utility;       

using namespace ws_backup;

namespace ws_soft
{

    // add by lmw 20170413
#if 1
    WS_ERR      model_base_func_init(char* m_cfg_language, size_t buf_size);
    WS_VOID    model_set_osd_time_dot(const char * dot,WS_S32 dot_num,WS_S32 single_dot_length, WS_CHAR *srcAsc, WS_U32 curLen);
    WS_ERR      model_init_for_live_osd(const char * dot,WS_S32 dot_num,WS_S32 singel_dot_length, WS_CHAR *srcAsc, WS_U32 curLen);
    WS_ERR      model_get_language_of_init(WS_CHAR *language, size_t buf_size);
#endif

    int model_enc_3des( const char *src_buf, size_t src_size, char *dst_buf,  const char *key);
    int model_dec_3des(const char *src_buf, size_t src_size, char *dst_buf, const char *key);
    WS_ERR model_PushAlarmEvent(ws_event_serial_type evt, WS_U32 number, WS_U32 chan, time_t time);
    WS_ERR model_send_cancel_shutdown_to_mcu();
    WS_BOOL model_playback_is_pb_ch_have_data(WS_U32 pb_ch);

#if defined(_SUPPORT_POLL_LIVE_)
    WS_ERR model_get_live_poll_enabel_state(WS_BOOL *has_enable);
    WS_ERR model_get_live_poll_info(ws_utility::ws_poll_live_type_e poll_type, ws_utility::ws_user_cfg_poll_live_s *cfg_info, WS_U32 ch_max_num);
    WS_ERR model_set_live_poll_enabe_state(WS_BOOL is_set);
#endif

    //获取设备能力描述(固定信息，不能修改)
    const ws_utility::ws_device_capability* model_get_dev_capability();	

    //设置LOGO点阵，bg_color为RGB888格式的背景色，尺寸超过352*288后会自动裁剪，小于352*288会自动居中，不足部分填充bg_color
    //bit格式为RGB1888, 一个像素占32bit，alpha: bit31-24，R: bit23-16，G: bit15-8，B: bit7-0，
    //alpha为0显示bg_color，否则显示设置像素
    WS_ERR model_init_logo(ws_utility::ws_logo_type type, int *bit, int bit_w, int bit_h, int bg_color);    //设置LOGO图片
    WS_ERR model_set_sys_time(WS_USR_HAND hand, const ws_utility::ws_time_struct *time);	//设置系统时间

#if defined(_SUPPORT_TIME_TYPE_AND_STANDARD_)
    WS_ERR model_dst_change_dev_time(WS_USR_HAND hand,dst_setting * dst_config,const ws_utility :: ws_time_struct * befor_change_time,const ws_utility :: ws_time_struct *after_change_time,ws_utility :: ws_time_struct *time_update);
#endif 

    WS_ERR model_get_sys_standard(WS_USR_HAND hand, ws_video_std *std);
    WS_ERR model_set_sys_standard(WS_USR_HAND hand, ws_video_std std);

    //恢复默认ws_resume_default_type 里定义了恢复默认类型
    WS_ERR model_sys_resume_default(WS_USR_HAND hand, WS_U32 mask);	
    WS_ERR model_sys_resume_default_ex(WS_USR_HAND hand, WS_U32 mask); 
    WS_ERR model_sys_reboot(WS_USR_HAND hand,WS_BOOL flag=WS_FALSE);
    WS_ERR model_sys_poweroff(WS_USR_HAND hand);

    /* add by zhangmq 20180527 start*/
    //add zmq 配置文件整理, Model层 增加接口[2018-03-27 15:10]
    WS_ERR model_set_alarm_server(LPHY_DVR_ALARMSERVERINFO_IF pcfg);
    WS_ERR model_get_alarm_server(LPHY_DVR_ALARMSERVERINFO_IF pcfg);
    /* add by zhangmq 20180527 end*/
	
    const ws_utility::ws_support_resol* model_get_support_resol();	 
    WS_ERR model_set_resol(const WS_CHAR *resol);	
    WS_ERR model_save_resol(const WS_CHAR *resol);  

    WS_ERR model_get_resol(WS_CHAR *resol, size_t buf_size);
    WS_ERR model_get_cfg_language(WS_USR_HAND hand, WS_CHAR *language, size_t buf_size);
    WS_ERR model_save_language(WS_USR_HAND hand, const WS_CHAR *language);

    WS_ERR model_save_dev_name(WS_USR_HAND hand, const char *buf);

    WS_ERR model_save_lock_screen_time(WS_USR_HAND hand,const char*buf);

    WS_ERR model_get_dev_name(WS_USR_HAND hand, char *buf, size_t buf_size);
    WS_ERR model_save_dev_num(WS_USR_HAND hand, int num);
    WS_ERR model_get_dev_num(WS_USR_HAND hand, int *num);
    //----------------------------------------------- 用户管理 ----------------------------------
    WS_ERR model_get_group_num(WS_USR_HAND hand, WS_U32 *group_num);	//获取用户组数目
	/* add by zhangmq 20180527 */
    WS_ERR model_get_valid_group_num(WS_USR_HAND hand, WS_U32 *group_num); //获取有效用户数,仅用于兼容内存文件方式
    WS_ERR model_get_group_name(WS_USR_HAND hand, WS_U32 group_idx, WS_CHAR *group_name, size_t name_size);	//获取用户组名

    WS_ERR model_add_group(WS_USR_HAND hand, const WS_CHAR *group_name, const ws_authority *authority);
    WS_ERR model_del_group(WS_USR_HAND hand, const WS_CHAR *group_name);

    WS_ERR model_get_group_authority(const WS_CHAR *group_name, ws_authority *authority);
    WS_ERR model_set_group_authority(WS_USR_HAND hand, const WS_CHAR *group_name, const ws_authority *authority);

    WS_ERR model_get_usr_num(WS_U32 *usr_num);	    //获取用户数目
	/* add by zhangmq 20180527 */
    WS_ERR model_get_valid_usr_num(WS_U32 *usr_num); //add zmq 增加获取有效用户数的接口,兼容内存文件方式的操作
    WS_ERR model_get_usr_name(WS_U32 usr_idx, WS_CHAR *usr_name, size_t name_size);	//获取用户名

    WS_ERR model_local_login(const WS_CHAR *usr_name, const char *password, WS_USR_HAND *hand);	//本地登陆

    WS_ERR model_remote_login_protocol(const WS_CHAR *usr_name, const char *password, const char *ip, const char *mac,login_protocol_type protocol_type,WS_USR_HAND *hand);

    WS_ERR model_check_login_protocol(const WS_CHAR *usr_name,const char *password,const char* ip,const char *mac,login_protocol_type protocol_type,WS_USR_HAND *hand);
    
#if defined (_V_3_1_5_ZGF_FORCE_TO_QUIT_)
    
    WS_ERR rtma_model_force_to_quit(WS_USR_HAND usr_hand);
    WS_ERR rtma_model_find_all_usr(WS_USR_HAND usr_hand,ws_user_info *usr_node,WS_U32 *count);
    WS_ERR model_get_login_num(WS_USR_HAND usr_hand,WS_U32 *count);
    
#endif
    /* hzg 20170329 input param NOT use pointer type start */
    WS_ERR model_auth_login_info(const WS_CHAR *usr_name, const char *password, const char *ip, const char *mac, WS_USR_HAND hand);
    /* hzg 20170329 input param NOT use pointer type end */

    WS_ERR model_remote_login(const WS_CHAR *usr_name, const char *password, const char *ip, const char *mac, WS_USR_HAND *hand);	
    WS_ERR model_logout(WS_USR_HAND hand);	
    WS_ERR model_get_login_user_info(WS_USR_HAND hand, ws_usr_info_login *login_info);
    WS_ERR model_get_login_grp_name(WS_USR_HAND hand, WS_CHAR *grp_name, int name_length);
    WS_ERR model_check_login(const WS_CHAR *usr_name, const char *password, const char *ip, const char *mac, WS_USR_HAND *hand);
    WS_ERR model_check_logout(WS_USR_HAND hand);
    WS_ERR model_add_usr(WS_USR_HAND hand, const WS_CHAR *usr_name, const char *password, const char *group_name);	
    WS_ERR model_del_usr(WS_USR_HAND hand, const WS_CHAR *usr_name);
    WS_ERR model_set_usr_passwd(WS_USR_HAND hand, const char * login_password, const WS_CHAR *usr_name, const char *password);
    WS_ERR model_change_usr_group(WS_USR_HAND hand, const WS_CHAR *usr_name, const char *group);	        //改变用户所属的用户组
    WS_ERR model_get_usr_state(const WS_CHAR *usr_name, ws_usr_state_info *info);
    WS_ERR model_get_usr_password(WS_USR_HAND hand,WS_CHAR *password,size_t password_size);
    WS_ERR model_get_usr_password_byname(const char *usr_name, WS_CHAR *password,size_t password_size);
    WS_BOOL model_is_supper_user(WS_USR_HAND hand);

    WS_BOOL model_is_supper_user_for_name(const char *name);		//通过用户名查找是否为超级用户
    WS_ERR model_check_authority(WS_USR_HAND hand, ws_authority_check_type check_type);

    WS_ERR model_start_live(const ws_utility::ws_display_screen_info *screen_info, const ws_utility::ws_wind_content *wind_content, size_t content_dim);
    WS_ERR model_stop_live();	

    WS_ERR model_live_move_roi_rect(WS_S32 nvr_ch, const ws_utility::ws_abstract_coordinate *start, const ws_utility::ws_abstract_coordinate *stop);
    WS_ERR model_live_mouse_set_roi(WS_S32 nvr_ch, const ws_utility::ws_abstract_coordinate *roi_coor, WS_BOOL amplif);
    WS_ERR model_cancel_live_roi(WS_U32 nvr_ch);

    //-------------------------------------------------- 音频预览控制 -----------------------------
    WS_ERR model_start_audio_live(WS_U32 channel);       
    WS_ERR model_stop_audio_live(WS_U32 channel);

    WS_ERR model_start_audio_pb(WS_USR_HAND hand, WS_U32 pb_ch);
    WS_ERR model_stop_audio_pb(WS_USR_HAND hand, WS_U32 pb_ch);

    WS_ERR model_start_talking();
    WS_ERR model_stop_talking();

    WS_ERR model_get_talking_frame(WS_USR_HAND hand, ws_frame_info *frame_info, char *frame_data, WS_U32 buf_len);
    WS_ERR model_play_talking_stream(const ws_frame_info *frame_info, char *frame_data);

    //-------------------------------422------------------------------------------
    WS_ERR model_422_send(WS_U32 port_idx,const char* send_buf, size_t send_size, speed_t baudrate);
    WS_ERR model_422_receive(WS_U32 port_idx, char* receive_buf, size_t recv_size, speed_t baudrate);

    //-------------------------------485------------------------------------------
    WS_ERR model_485_send(WS_U32 port_idx,const char* send_buf, size_t send_size, speed_t baudrate);
    WS_ERR model_485_receive(WS_U32 port_idx, char* receive_buf, size_t recv_size, speed_t baudrate);

	//------------------------------------------------ 联动控制 ------------------------------
    WS_ERR model_get_ai_check_type(WS_USR_HAND hand, WS_U32 ai_ch, ws_utility::ws_ai_check_type *type);
    WS_ERR model_set_ai_check_type(WS_USR_HAND hand, WS_U32 ai_ch,ws_utility::ws_ai_check_type type);

    WS_ERR model_get_ai_config(WS_USR_HAND hand, WS_U32 ch, ws_utility::ws_ai_config *config);
    WS_ERR model_set_ai_config(WS_USR_HAND hand, WS_U32 ch, ws_utility::ws_ai_config *config);
    WS_ERR model_get_ao_config(WS_USR_HAND hand, WS_U32 ch, ws_utility::ws_ao_config *config);
    WS_ERR model_set_ao_config(WS_USR_HAND hand, WS_U32 ch, ws_utility::ws_ao_config *config);
    WS_ERR model_get_event_info(WS_USR_HAND hand,ws_event_type type,WS_U32 ch_idx, ws_event_info *info);
    WS_ERR model_set_ao_hold_time(WS_USR_HAND hand, WS_U32 ch,WS_U32 secs);
    WS_ERR model_get_ao_hold_time(WS_USR_HAND hand, WS_U32 ch,WS_U32* secs);
 
    WS_ERR model_set_alarm_out_control(const WS_U32 pin, gpio_alarm_out_ctl ctl);
    WS_ERR model_get_trig_cfg(WS_USR_HAND hand, ws_trig_source src_type, WS_U32 src_ch, ws_trig_operation *operation);
    WS_ERR model_set_trig_cfg(WS_USR_HAND hand, ws_trig_source src_type, WS_U32 src_ch, ws_trig_operation *operation);
    WS_ERR model_get_link_live_poll_cfg(ws_soft::ws_event_type type, WS_BOOL* link_data,WS_U32* data_len);	
    WS_ERR model_cancel_alarm(WS_USR_HAND hand);		//用户在界面层点击取消警报按钮
    WS_ERR model_buzzer_ms(WS_U32 msecs);				//参数为0表示长叫，外部模块调用该接口使蜂鸣器鸣叫msecs

    WS_BOOL model_get_event_state(WS_U32 ch,ws_event_type  event_type); 

    //------------------------------------------------ 录像控制 ------------------------------
    WS_ERR model_get_enc_input_fps(WS_U32 ch_idx, WS_S32 *enc_input_fps);
    WS_ERR model_get_ch_max_fps(WS_U32 dvr_ch, ws_venc_str_type str_type, WS_U32 *max_fps);
     WS_ERR model_set_default_isp_para(WS_USR_HAND hand, WS_U32 rmt_ch);
     WS_ERR model_set_default_exposure_para(WS_USR_HAND hand, WS_U32 rmt_ch);

    WS_ERR model_get_alarm_enc_para(WS_USR_HAND hand, WS_U32 nvr_ch, ws_enc_para *para);
    WS_ERR model_set_alarm_enc_para(WS_USR_HAND hand, WS_U32 nvr_ch,  const ws_enc_para *para);

    // 设置与获取当前通道工作模式
    WS_ERR model_set_record_mode(WS_USR_HAND hand, WS_U32 rec_ch, ws_soft::RECORD_MODE curMode);
    WS_ERR model_get_record_mode(WS_USR_HAND hand, WS_U32 rec_ch, ws_soft::RECORD_MODE *curMode);

    WS_ERR model_set_manual_rec_enable(WS_USR_HAND hand, WS_U32 nvr_ch, WS_BOOL enable);
    WS_ERR model_set_manual_rec_enable_ex(WS_USR_HAND hand, WS_BOOL enable);
    WS_ERR model_get_manual_rec_enable(WS_U32 nvr_ch,WS_BOOL *enable);			//获取手动录像使能状况

    WS_ERR model_set_pre_rec_sec(WS_USR_HAND hand,WS_U32 rec_ch, int sec);		//设置预录时间
    WS_ERR model_get_pre_rec_sec(WS_USR_HAND hand, WS_U32 rec_ch, int *sec);

    WS_ERR model_set_delay_rec_sec(WS_USR_HAND hand,WS_U32 rec_ch, int sec);	//设置延迟录像时间
    WS_ERR model_get_delay_rec_sec(WS_USR_HAND hand, WS_U32 rec_ch, int *sec);	

    WS_ERR model_get_rec_holiday_enable(WS_USR_HAND hand, WS_U32 nvr_ch, WS_BOOL *enable);
    WS_ERR model_set_rec_holiday_enable(WS_USR_HAND hand, WS_U32 nvr_ch, WS_BOOL enable);
    WS_ERR model_set_rec_holiday_enable_ex(WS_USR_HAND hand, ws_soft::ws_rec_schedule schedule);

    WS_ERR model_set_rec_holiday_enable_ex_special(WS_USR_HAND hand, ws_rec_schedule_holiday* schedule);
    WS_ERR model_set_holiday_ex_special(WS_USR_HAND hand, ws_rec_schedule_holiday* schedule);
    WS_ERR model_set_rec_schedule_ex_special(WS_USR_HAND hand, ws_rec_schedule_time* schedule);
	/*add by khs 2017.3.29*/
    WS_ERR model_set_rec_schedule_ex_special_ex(WS_USR_HAND hand, ws_channel_rec_schedule* schedule,int ch_idx);
    
    WS_ERR model_get_rec_schedule(WS_USR_HAND hand, WS_U32 nvr_ch, ws_rec_schedule_day day, ws_rec_schedule_per_day *schedule);		
    WS_ERR model_set_rec_schedule(WS_USR_HAND hand, WS_U32 nvr_ch, ws_rec_schedule_day day, const ws_rec_schedule_per_day *schedule);
    //WS_ERR model_set_rec_schedule_ex(WS_USR_HAND hand, const ws_rec_schedule schedule); //del by qqy, at 2017-05-04 15:28:09

 //Modified by qqy,start at 2017-03-10 09:59:03
    ws_rec_file_trig_type model_get_ch_rec_state(WS_U32 rec_ch);				//获取录像状态
 //Modified by qqy,end at 2017-03-10 09:59:05

    WS_ERR model_get_link_by_md(WS_U32 rec_ch, WS_U32 *md_link, WS_U32 mask_num);	

    //add by qqy,start at 2017-02-22 17:05:41
    WS_ERR model_set_link_rec_by_md(WS_USR_HAND hand, WS_U32 rec_ch, WS_U32 *md_link, WS_U32 mask_num);
    WS_ERR model_set_link_rec_by_ai(WS_USR_HAND hand, WS_U32 rec_ch, WS_U32 *ai_link, WS_U32 mask_num);
    //add by qqy,end at 2017-02-22 17:05:48
 
    WS_ERR model_get_holiday(WS_USR_HAND hand, WS_U16 year, WS_U16 month, WS_U32 *mask);			//查询指定月份哪些天是节假日，bit0-bit3对应1号-31号，0表示不是，1表示是
    WS_ERR model_set_holiday(WS_USR_HAND hand, WS_U16 year, WS_U16 month, WS_U32 mask); 
    WS_ERR model_set_holiday_ex(WS_USR_HAND hand, ws_rec_schedule schedule);

    //------------------------------------------------ 录像、抓图文件查询控制 ------------------------------
    WS_ERR model_inquiry_rec_by_month(WS_USR_HAND hand, const ws_utility::ws_time_struct *time, WS_U32 *mask);		//查询指定月份哪些天有录像，bit0-bit30对应1号-31号，0表示没有录像，1表示有录像
    WS_ERR model_inquiry_rec_by_day(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_utility::ws_time_struct *time, ws_rec_file_inquiry_type file_type, ws_rec_file_inquiry_result *result);	//查询指定日期的录像
    WS_ERR model_inquiry_rec_by_time(WS_USR_HAND hand, 
								 WS_U32 nvr_ch,
								 const ws_utility::ws_time_struct *start_time,
								 const ws_utility::ws_time_struct *stop_time,
								 ws_rec_file_inquiry_type file_type,
								 ws_rec_file_inquiry_result *result);					//查询指定时间段的录像
    WS_ERR model_free_inquiry_rec_result(WS_USR_HAND hand, const ws_rec_file_inquiry_result *result);		//释放查询结果
    WS_ERR model_inquiry_snap_by_month(WS_USR_HAND hand, const ws_utility::ws_time_struct *time, WS_U32 *mask);				//查询指定月份哪些天有录像，bit0-bit30对应1号-31号，0表示没有录像，1表示有录像
    WS_ERR model_inquiry_snap_by_day(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_utility::ws_time_struct *time, ws_snap_file_inquiry_type file_type, ws_snap_file_inquiry_result *result);		//查询指定日期的录像
    WS_ERR model_inquiry_snap_by_time(WS_USR_HAND hand, 
								 WS_U32 nvr_ch,
								 const ws_utility::ws_time_struct *start_time,
								 const ws_utility::ws_time_struct *stop_time,
								 ws_snap_file_inquiry_type file_type,
								 ws_snap_file_inquiry_result *result);	
    WS_ERR model_free_inquiry_snap_result(WS_USR_HAND hand, const ws_snap_file_inquiry_result *result);	

    //------------------------------------------------ 回放控制 ------------------------------
    WS_ERR model_set_pb_mode(WS_USR_HAND hand, ws_playback_mode mode);
    WS_ERR model_set_channel(WS_USR_HAND hand,WS_U32 ch,WS_U32 channel); //add by khs 2017.7.14

    WS_ERR model_set_pb_rec_file(WS_USR_HAND hand, WS_U32 pb_ch, const ws_pb_rec_file_inquiry_result *source,const file_result_handle* hdls);
    WS_ERR model_set_pb_snap_file(WS_USR_HAND hand, WS_U32 pb_ch, const ws_pb_snap_file_inquiry_result *source,const file_result_handle* hdls);

    WS_ERR model_stop_pb_wind(WS_USR_HAND hand);
    WS_ERR model_set_ch_mode(WS_USR_HAND hand,WS_BOOL ch_mode,WS_U32 ch);//add by khs 2017.6.28
    WS_ERR model_set_pb_wind(WS_USR_HAND hand, const ws_utility::ws_display_screen_info *screen_info, const ws_utility::ws_wind_content *wind_content, size_t content_dim);	
    WS_ERR model_set_pb_full_screen(WS_USR_HAND hand, ws_utility::ws_screen_div_mode div_mode, const WS_S32 *ch_idx, size_t ch_dim);

    WS_ERR model_set_pb_interval_time(WS_USR_HAND hand, WS_U32 interval_time_ms);

    WS_ERR model_set_pb_roi(WS_USR_HAND hand, WS_U32 pb_ch, const ws_utility::ws_abstract_rect *roi_rect);
    WS_ERR model_set_end_time(WS_USR_HAND hand, time_t end_time); 

    WS_ERR model_cancel_pb_roi(WS_USR_HAND hand, WS_U32 pb_ch);

    WS_ERR model_start_pb(WS_USR_HAND hand, time_t time, time_t end_time = 0xffffffff); 
    WS_ERR model_stop_pb(WS_USR_HAND hand); 
    WS_ERR model_seek_pb_time(WS_USR_HAND hand, time_t time,WS_BOOL has_reflash=WS_FALSE,WS_BOOL need_lock= WS_FALSE); 
    WS_ERR model_get_pb_time(WS_USR_HAND hand, time_t *time); 
    WS_ERR model_pause_pb(WS_USR_HAND hand);
    WS_ERR model_resume_pb(WS_USR_HAND hand);
    WS_ERR model_set_focus_channel(WS_USR_HAND hand,int ch);
    WS_ERR model_step_pb(WS_USR_HAND hand, ws_playback_step_mode mode);

    WS_ERR model_set_pb_speed(WS_USR_HAND hand, ws_playback_speed speed);
    WS_ERR model_set_pb_dir(WS_USR_HAND hand, ws_playback_direction dir);

    WS_ERR model_pb_mouse_set_roi(WS_USR_HAND hand, WS_S32 nvr_ch, const ws_utility::ws_abstract_coordinate *roi_coor, WS_BOOL amplif);
    WS_ERR model_pb_move_roi_rect(WS_USR_HAND hand, WS_S32 nvr_ch, const ws_utility::ws_abstract_coordinate *start, const ws_utility::ws_abstract_coordinate *stop);

    WS_BOOL model_get_pb_is_end(WS_USR_HAND hand, WS_S32 nvr_ch);
    WS_ERR model_ptz_cmd_control(WS_USR_HAND hand, WS_U32 rmt_ch, PTZ_CMD_ID cmd, WS_U32 para);

    WS_ERR model_set_ch_ptz_ctl(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_ptz_ctl_info *ctl_info);
    WS_ERR model_get_ch_ptz_ctl(WS_USR_HAND hand, WS_U32 nvr_ch, ws_ptz_ctl_info *ctl_info);

    WS_ERR model_set_ptz_speed(WS_USR_HAND hand, WS_U32 ch, WS_U32 speed);
    WS_ERR model_get_ptz_speed_cfg(WS_USR_HAND hand, WS_U32 ch, WS_U32 * speed);
    WS_ERR model_get_ptz_speed(WS_USR_HAND hand, WS_U32 ch, WS_U32 * speed);

    WS_ERR model_get_ptz_cruise_line(WS_USR_HAND hand, WS_U32 ch, ws_ptz_ctl_type protocol, ws_ptz_cruise_line * cruise_line);
    WS_ERR model_get_protocol_list_info(WS_USR_HAND hand, ws_ptz_protocol_info_list ** list_info,WS_U32 *protocol_num);
    WS_ERR model_get_support_ptz_protocol(WS_USR_HAND hand, ws_ptz_protocol_info *protocol_info); 
    WS_ERR model_get_support_ptz_baudrate(WS_USR_HAND hand, ws_ptz_baudrate_info *baudrate_info); 

    //------------------------------------------------ usb、硬盘控制 ------------------------------
    WS_ERR model_get_usb_disk_num(WS_U32 *num);
    WS_ERR model_get_usb_disk_info(WS_U32 disk_idx, ws_usb_disk_info *info);
    WS_ERR model_get_usb_disk_exist(WS_U32 disk_idx);

    WS_ERR model_get_all_disk_info(WS_USR_HAND hand, ws_hard_disk_info *info, WS_U32 arr_len, WS_U32  *disk_num);

    WS_ERR model_get_hard_disk_num(WS_USR_HAND hand, WS_U32 *num);
    WS_ERR model_get_hard_disk_info(WS_USR_HAND hand, WS_U32 disk_idx, ws_hard_disk_info *info);

    WS_ERR model_get_hard_disk_info(WS_USR_HAND hand, const char*  serial_no, ws_hard_disk_info *info);
    WS_ERR model_get_hard_disk_state(WS_USR_HAND hand, const char*  serial_no, ws_hard_disk_state *state);

    WS_ERR model_inquiry_rec_by_disk_num(WS_USR_HAND hand, int scsi_num, time_t *rec_start, time_t *rec_stop);		//通过制定的sata口号获取该硬盘录像的起始时间和结束时间
    WS_ERR model_get_slot_num(WS_USR_HAND hand, WS_U32 *slot_num);		

    WS_ERR model_format_hard_disk(WS_USR_HAND hand, const char*  serial_no, WS_U32 part_idx);
    WS_ERR model_format_hard_disk_get_info(WS_USR_HAND hand, ws_disk_serial* serial_no, WS_S32* nNum);    

    WS_ERR model_cancel_format_hard_disk(WS_USR_HAND hand, const char*  serial_no);

    WS_ERR model_get_fromat_progress(const char*  serial_no, int *percent);	

    WS_ERR model_get_disk_work_ctl(WS_USR_HAND hand, ws_hard_disk_work_ctl *ctl);			//设置硬盘工作模式
    WS_ERR model_set_disk_work_ctl(WS_USR_HAND hand, const ws_hard_disk_work_ctl *ctl);
	//------------------------------------------------ 备份控制 ------------------------------

    WS_ERR model_backup_get_last_type(ws_usb_dev_type *dev_type);         

#if not defined (_SUPPORT_PRO_BACKUP_)
    WS_ERR model_add_backup_rec_job(WS_USR_HAND hand, const ws_rec_file_inquiry_result *result, ws_backup_work_mode mode, time_t start_time, time_t stop_time);
    WS_ERR model_add_backup_snap_job(WS_USR_HAND hand, const ws_snap_file_inquiry_result *result, ws_backup_work_mode mode, time_t start_time, time_t stop_time);
#else
    WS_ERR model_add_rec_job(WS_USR_HAND hand, const ws_rec_file_inquiry_result *result);
    WS_ERR model_add_snap_job(WS_USR_HAND hand, const ws_snap_file_inquiry_result *result);
#endif

    WS_ERR model_cnt_backup_size(WS_USR_HAND hand, WS_U32 *size_MB);
#if not defined (_SUPPORT_PRO_BACKUP_)
    WS_ERR model_start_backup(WS_USR_HAND hand,  const WS_CHAR* scsi_name, const WS_CHAR * part_mount_dir, ws_backup_file_type file_type, ws_usb_dev_type dev_type);
#else
    WS_ERR model_start_backup(WS_USR_HAND hand,ws_dev_part_info * dev_info,WS_U32 dev_num,ws_backup_file_type file_type);
#endif
    WS_ERR model_get_backup_progress(WS_USR_HAND hand, WS_U32 *percent);	
    WS_ERR model_stop_backup(WS_USR_HAND hand);

	//------------------------------------------------ DST配置 ------------------------------
    WS_BOOL model_get_dst_enable();
    WS_ERR model_set_dst_enable(WS_USR_HAND hand, WS_BOOL is_enable);

    WS_ERR model_set_time_zone(WS_USR_HAND hand,time_zone_type set_num);	
    WS_ERR model_get_time_zone(WS_USR_HAND hand, time_zone_type *set_num);
    WS_ERR model_get_zone_type_time(WS_USR_HAND hand, time_zone_type type, int *zone_hour, int *zone_min);
    const ws_support_time_zone *model_get_support_time_zone();

	//------------------------------------------------ 网络配置 ------------------------------
    WS_ERR model_get_local_connect_cfg(WS_USR_HAND hand, ws_local_connect_cfg *cfg);
    WS_ERR model_set_local_connect_cfg(WS_USR_HAND hand, const ws_local_connect_cfg *cfg);

    WS_ERR model_get_pppoe_cfg(WS_USR_HAND hand, ws_pppoe_config *cfg);
    WS_ERR model_set_pppoe_cfg(WS_USR_HAND hand, const ws_pppoe_config *cfg);
    WS_ERR model_get_show_pppoe_status(WS_USR_HAND hand,show_pppoe_status *pppoe_status); 

    WS_ERR model_get_net_port_cfg(ws_net_port_cfg *cfg);
    WS_ERR model_set_net_port_cfg(WS_USR_HAND hand, ws_net_port_cfg *cfg);

    WS_ERR model_get_upnp_cfg(WS_BOOL *enable);
    WS_ERR model_set_upnp_cfg(WS_USR_HAND hand, WS_BOOL enable);

    WS_ERR model_get_email_sender_cfg(WS_USR_HAND hand, ws_email_sender_cfg *cfg);
    WS_ERR model_set_email_sender_cfg(WS_USR_HAND hand, ws_email_sender_cfg *cfg);

    WS_ERR model_get_email_receiver_num(WS_S32 *num);
    WS_ERR model_get_email_receiver_name(WS_S32 receiver_idx, ws_reciver_add *reciver_addr);
    WS_ERR model_add_email_receiver(WS_USR_HAND hand, const ws_reciver_all *reciver_addr);
    WS_ERR model_get_email_receiver_all(WS_USR_HAND hand, WS_S32 *total_num, ws_reciver_all *reciver_addr);

    WS_ERR model_send_email_tst(WS_USR_HAND hand, const ws_email_sender_cfg *cfg, const ws_reciver_all *reciver_addr, int reciver_num, const ws_email_attachment *attachment, const char *title, const char *buf);
    WS_ERR model_start_dhcp(WS_USR_HAND hand);
    WS_ERR model_stop_dhcp(WS_USR_HAND hand);
    WS_ERR model_register_smtp_get_txt(ws_smpt_get_str_func pcall);
    WS_ERR model_set_ntp_server(WS_USR_HAND hand, const ws_ntpc_config *ntp_ccfg);
    WS_ERR model_get_ntp_status(WS_USR_HAND hand);
    WS_ERR model_get_ip_status(WS_USR_HAND hand);
#if defined(_SUPPORT_TIME_TYPE_AND_STANDARD_)
    WS_ERR model_set_show_time_type(WS_USR_HAND hand,ws_gui_show_time_type  time_type);
    WS_ERR model_set_time_standard(WS_USR_HAND hand,ws_gui_time_standard time_standard);
    WS_ERR model_set_dst_config(WS_USR_HAND hand,dst_setting dst_config);
#endif
    WS_ERR model_get_ntp_server(WS_USR_HAND hand, ws_ntpc_config *ntp_ccfg);
    WS_ERR model_get_time_type(WS_USR_HAND hand,ws_gui_show_time_type* time_type);
    WS_ERR model_get_time_standard(WS_USR_HAND hand ,ws_gui_time_standard* time_standard);
    
#if defined(_SUPPORT_TIME_TYPE_AND_STANDARD_)
    WS_ERR model_get_dst_config(WS_USR_HAND hand,dst_setting *dst_config);
#endif 
    WS_ERR model_set_pri_dns_cfg(WS_USR_HAND hand, const ws_pri_dns_config *pri_dns, WS_DDNS_ERR *status);
    WS_ERR model_get_pri_dns_cfg(WS_USR_HAND hand, ws_pri_dns_config *pri_dns);
    WS_ERR model_try_user_domain(WS_USR_HAND hand, const char *user_domain, WS_DDNS_ERR *status);
    WS_ERR model_get_dns_connect_status(WS_USR_HAND hand, connect_status *con_status);
    WS_ERR model_get_dns_default_domain(char *def_domain, size_t def_domain_size);

	//------------------------------------------------ 威视设备探测 ------------------------------
    WS_ERR model_refresh_probe();
    WS_ERR model_get_search_num(WS_U32 *dev_idx);
    WS_ERR model_get_remote_dev_info(WS_U32 dev_idx, ws_remote_dev_info *info);

    WS_ERR model_get_rmt_connect_rule(WS_USR_HAND hand, WS_U32 nvr_ch, WS_BOOL *ch_state, ws_connet_rule *rule);
    WS_ERR model_set_rmt_connect_rule(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_connet_rule *rule,WS_U32* taskId); 
    WS_ERR model_set_rmt_disconnect_rule(WS_USR_HAND hand, WS_U32 nvr_ch);			//设置手动连接的时候会暂停该通道的自动连接，以免界面显示有歧义，完毕之后需要调用model_resume_auto_search来恢复自动连接
    WS_ERR model_cmp_channel_ip_addr(const char *ip);
    WS_ERR model_resume_auto_search();
    WS_ERR model_get_rmt_connect_info(WS_USR_HAND hand, WS_U32 nvr_ch, ws_connect_dev_info *info);

    WS_ERR model_get_channel_bit_rate(WS_U32 rmt_ch, WS_U32 *get_bit);
    WS_ERR model_get_sub_channel_bit_rate(WS_U32 rmt_ch, WS_U32 *get_bit);

    WS_ERR model_get_bit_rate(WS_U32 rmt_ch, ws_venc_str_type type, STREAM_SPEED speed, WS_U32 *get_bit);

    WS_ERR model_get_sdi_connect_state(WS_U32 nvr_ch, WS_BOOL *ch_state);

	//------------------------------------------------ 升级、配置导入导出 ------------------------------
    WS_ERR model_write_upgrade_file_block(WS_USR_HAND hand, const WS_CHAR *file_buffer,const WS_U32 buffer_length, WS_BOOL file_end);
    WS_ERR model_scan_packet(const char *directory, update_file_attr_t *flist, size_t flist_num, int *real_num);   //查找可用升级文件
	//auto_del_packet描述是否删除源文件，为了节约内存，网络升级的时候指定为TRUE，这样升级解压缩的时候可以讲文件删掉
    WS_ERR model_start_packet(WS_USR_HAND hand, const WS_CHAR *packet_fname, WS_BOOL auto_del_packet);
    WS_U32 model_get_update_percent();

    WS_ERR model_scan_cfg_file(ws_config_file *flle_array, size_t array_dim, WS_U32 *real_packet_num);
    WS_ERR model_export_cfg_file(WS_USR_HAND hand, WS_U32 usb_dev_idx, WS_U32 usb_part_idx);

	//------------------------------------------------ 日志查询、导出 ---------------------------------------
    WS_ERR model_query_log_hand(WS_USR_HAND hand, const ws_log_inquiry_ctl *inquiry_ctl, ws_log_table_hand *log_hand, WS_U32 *log_num);
    WS_ERR model_get_log_result(WS_USR_HAND hand, const ws_log_table_hand log_hand,WS_U32 * start_num,WS_U32 * total_num,ws_log_inquiry_result_pro * log_result);
    WS_ERR model_free_log_result(WS_USR_HAND hand, ws_log_table_hand * log_hand);
    WS_ERR model_export_log_file(WS_USR_HAND hand, WS_U32 usb_dev_idx, WS_U32 usb_part_idx);
    WS_ERR model_inquiry_log_ex(WS_USR_HAND hand, const ws_log_inquiry_ctl *inquiry_ctl, ws_utility::ws_language_type language, ws_net_log_inquiry_result *result); 
    WS_ERR model_free_inquiry_log_result_ex(WS_USR_HAND hand, ws_net_log_inquiry_result *result);	
    WS_ERR model_export_log_file_ex(WS_USR_HAND hand, const WS_CHAR *file_name, ws_utility::ws_language_type language, const ws_log_inquiry_ctl *inquiry_ctl);  //用于下载

    //注册日志类容翻译接口，用于将日志中的枚举变量翻译成具体需要显示的字符串(UTF-8格式)
    WS_ERR model_register_log_content_trans_pro_func(log_content_trans_pro func);
    //注册日志类容翻译接口，用于将html文件中的标题翻译成具体需要显示的字符串(UTF-8格式)
    WS_ERR model_register_log_title_cb(log_title_trans func);

    //------------------------------------------------ wifi配置 ------------------------------
    WS_BOOL model_get_wifi_enable();
    WS_ERR model_set_wifi_enable(WS_USR_HAND hand, WS_BOOL is_enable);
    WS_ERR model_get_wifi_connect_mode(int *mode);
    WS_ERR model_set_wifi_connect_mode(WS_USR_HAND hand, int mode);

    WS_ERR model_set_wifi_ap_info(WS_USR_HAND hand, const LPWLAN_CONNECTION ap_info);
    WS_ERR model_get_wifi_ap_info(LPWLAN_CONNECTION ap_info);
	
	//动态不需要调用,静态用于设置固定的信息
    WS_ERR model_set_wifi_ip_info(WS_USR_HAND hand, const ws_local_connect_cfg *ip_info);
    WS_ERR model_get_wifi_ip_info(WS_USR_HAND hand, ws_local_connect_cfg *ip_info);

    WS_ERR model_set_wifi_connect(WS_USR_HAND hand, const LPWLAN_CONNECTION connect);
    WS_ERR model_get_wifi_ap_connect(WS_USR_HAND hand, ws_wifi_inquiry_result *result);

    WS_ERR model_get_local_connect_wifi_info(WS_USR_HAND hand, ws_wifi_right_now_info *info);

 //Modified by qqy,start at 2016-11-07 20:52:20
	WS_ERR model_get_wifi_conn_status(WS_BOOL *status, char ssid[WS_MAX_SSID_LEN], char mac[WS_NVR_MAC_STRING_LEN]);
 //Modified by qqy,end at 2016-11-07 20:52:22
	//-----------------------------事件----------------------------------------------------
    WS_ERR model_set_exception(WS_USR_HAND hand, const exception_linkage *excep);
    WS_ERR model_get_exception(WS_USR_HAND hand, exception_type type, exception_control *excep_ctr);
    WS_ERR model_get_exception_state(exception_type type, WS_U32 *exception_state);
    WS_ERR model_set_exception_state(exception_type type, WS_U32 exception_state);	
    WS_ERR model_get_operate_state(ws_operate_type  opt_type ,WS_BOOL  *flag);
	
	//-----------------------------ipc同步时间---------------------------------------------
    WS_ERR model_set_sync_ipc_time_enbale(WS_USR_HAND hand, WS_BOOL enable);
    WS_BOOL model_get_sync_ipc_time_enbale();

	//----------------------------------------------- nvr 控制 ipc--------------------------------------------------------
    WS_ERR model_get_cha_state(WS_USR_HAND hand, WS_U32 rmt_ch, ws_agent_ch_state * state);
    WS_ERR model_get_cha_info(WS_USR_HAND hand, WS_U32 rmt_ch, const ws_venc_str_type str_type, ws_enc_para *para);
    WS_ERR model_set_cha_info(WS_USR_HAND hand, WS_U32 rmt_ch, const ws_venc_str_type str_type, const ws_enc_para *para);
    WS_ERR model_set_cha_info_default(WS_USR_HAND hand, WS_U32 rmt_ch);

    WS_ERR model_get_isp_info(WS_USR_HAND hand, WS_U32 rmt_ch, ws_isp_image *get_image, ws_isp_exposure *get_exposure);
    WS_ERR model_get_default_isp_info(WS_USR_HAND hand, WS_U32 rmt_ch, ws_isp_image *get_image, ws_isp_exposure *get_exposure);
    WS_ERR model_set_isp_info(WS_USR_HAND hand, WS_U32 rmt_ch, ws_isp_type set_type, int set_val);

	//下载ipc的配置文件
    WS_ERR model_download_ipc_config(WS_USR_HAND hand, WS_U32 rmt_ch, char *recvbuf, int recvlen);

	//手动连接的时候调用此接口，如果返回TRUE,表示该IPC已被其他NVR连接并填充连接NVR的IP和MAC否则返回FALSE
    WS_BOOL model_inquiry_whether_IPC_is_connected(WS_U32 rmt_ch, const ws_connet_config *cfg, char *ipv4, int ip_length, char *mac, int mac_length);

    WS_ERR model_get_md_info(WS_USR_HAND hand, WS_U32 rmt_ch, ws_md_arr *md_arr);
    WS_ERR model_get_md_allalarm(WS_USR_HAND hand, WS_U32 rmt_ch, WS_U32* p_allalarm);
    WS_ERR model_set_md_info(WS_USR_HAND hand, WS_U32 rmt_ch, const ws_md_arr *md_arr);


	//重启对应的ipc
    WS_ERR model_set_chan_reboot(WS_USR_HAND hand, WS_U32 rmt_ch);

    //--------------------------------------------------SDI OSD-------------------------------------------------------------
    WS_ERR model_get_channel_name(WS_USR_HAND hand, WS_U32 ch, char *name_buf, size_t size);
    WS_ERR model_set_channel_name(WS_USR_HAND hand, WS_U32 ch, const char *name_buf, const WS_VOID *bitmap, WS_U32 width, WS_U32 height);
    WS_ERR model_register_set_channel_func(set_chn_name func);
    WS_ERR model_register_reset_admin_passwd_func(reset_admin func);

    WS_ERR model_set_channel_name_web(WS_USR_HAND hand, WS_U32 ch, const char *name_buf);
    WS_ERR model_init_channel_name(WS_U32 ch, const char *name_buf, const WS_VOID *bitmap, WS_U32 width, WS_U32 height); 
    WS_ERR model_init_get_channel_name(WS_U32 ch, char *name_buf, size_t size);

    WS_ERR model_get_osd_area(WS_USR_HAND hand, WS_U32 ch, ws_osd_type dp_tp, ws_location_type *loc_tp);
    WS_ERR model_set_osd_area(WS_USR_HAND hand, WS_U32 ch, ws_osd_type dp_tp, ws_location_type loc_tp);
    
    WS_ERR model_set_time_type_and_standard(WS_USR_HAND hand,ws_time_type_and_standard *time_type_and_standard);      

	//--------------------------------------------- VGA输出效果控制 ------------------------------------------------------
    WS_ERR model_get_hi_vga_param(HI_VGA_PARAM_S *para);
    WS_ERR model_set_hi_vga_param(const HI_VGA_PARAM_S *para);

    //----------------------------------------------web->nvr 流数据接口-------------------------------------------------------------------------
    //每个通道的每一种类型数据都是以链表形式管理，都是生产者和消费者关系，消费者第一次获取某个通道的某种类型数据时，调用first_get接口，
    //接口成功会返回帧信息和节点编号(node_idx)，之后调用get接口，带上上次获取的node_idx，地下链表会根据该信息返回新的数据
    WS_ERR model_first_get_video_stream(WS_U32 rmt_ch,
                                    ws_utility::ws_module_id module_id,
                                    ws_venc_str_type type,
                                    ws_frame_info *frame_info,
                                    WS_UCHAR **frame_data,
                                    WS_U32 *node_idx);

    WS_ERR model_get_video_stream(WS_U32 rmt_ch,
                              ws_utility::ws_module_id module_id,
                              ws_venc_str_type type,
                              ws_frame_info *frame_info,
                              WS_UCHAR **frame_data,
                              WS_U32 last_node_idx,
                              WS_U32 *cur_node_idx);
    WS_ERR model_del_video_stream(WS_U32 rmt_ch,
                              ws_utility::ws_module_id module_id,
                              ws_venc_str_type type,
                              WS_U32 node_idx);

    WS_ERR model_new_upload_sys_file(WS_USR_HAND hand,WS_U32 rmt_ch,const char *filename,WS_U32 *taskId);	
    WS_ERR model_get_remote_upgrade_status(WS_USR_HAND hand,WS_U32 ch, int *upgradeStatus); 
    WS_ERR model_stop_remote_task(WS_USR_HAND hand,WS_U32 ch,WS_U32 taskId) ;
    /* hzg 20170411 Cmd control Private Protocol Server start stop  */
#if defined (_V_3_1_5_ZGF_FORCE_TO_QUIT_)
    WS_ERR model_register_protocol_stop(set_protocal_stop stop_func, ws_utility::login_protocol_type protocol_type);
#endif
   
    WS_ERR model_register_push_alarm_event(ws_soft::add_happen_event_node func);

    WS_S32 model_qr_create(int nLevel, int nVersion , char *lpsSource, int sourcelen, char *QR_m_data, size_t QR_m_data_size);
    WS_ERR model_get_serial_event(WS_USR_HAND hand, ws_utility::ws_event_serial_type *type, WS_U32 *serial_num, WS_U32 *ch);
    ws_utility::ws_stEvent *model_get_event_list(WS_USR_HAND hand, WS_U32 ch_idx, time_t start,time_t end, WS_U32 evt_mask);
    WS_ERR model_free_event_list(WS_USR_HAND hand, ws_utility::ws_stEvent *evt);

    WS_ERR model_set_ipdetection_callback();
    WS_ERR model_start_ddns(WS_USR_HAND hWnd);
    WS_ERR model_stop_ddns(WS_USR_HAND hWnd);
    void *watch_dog_thread(void *para);
    
    time_t get_no_opt_time();
    WS_U32 model_get_lock_screen_time();
    WS_ERR model_buzzer_test(WS_USR_HAND hand, WS_U32 msecs);
    WS_ERR model_password_reset_test(WS_USR_HAND hand, WS_BOOL *reset_state);


WS_ERR model_inquiry_recfile_by_day(WS_USR_HAND hand,WS_U32 nvr_ch, const ws_utility::ws_time_struct *start_time,const ws_rec_file_inquiry_type file_type,ws_rec_table_hand * rec_hld,WS_U32 * rec_num);
WS_ERR model_inquiry_recfile_by_time(WS_USR_HAND hand, WS_U32 nvr_ch,const ws_utility::ws_time_struct * start_time,const ws_utility::ws_time_struct * stop_time,ws_rec_file_inquiry_type file_type,ws_rec_table_hand * rec_hand,WS_U32 * result_num);
WS_ERR model_get_recfile_result_for_pb(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_rec_table_hand rec_hdl,ws_pb_rec_file_inquiry_result * rec_result, time_t* min_time, time_t* max_time);
WS_ERR model_get_recfile_result(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_rec_table_hand rec_hdl, WS_U32 *start_num, WS_U32 *total_num, ws_rec_file_inquiry_node * rec_result, WS_BOOL is_playback);
WS_ERR model_free_rec_result(WS_USR_HAND hand,ws_rec_table_hand * rec_hdl);
WS_ERR model_select_valid_recfile(WS_USR_HAND hand, WS_U32 *real_num,ws_rec_file_inquiry_node * rec_result,ws_rec_file_inquiry_node **dst_result);//add by lmw 20170509

WS_ERR model_inquiry_snapfile_by_day(WS_USR_HAND hand,WS_U32 nvr_ch,const ws_utility::ws_time_struct * time,const ws_snap_file_inquiry_type file_type,ws_snap_table_hand * snap_hdl,WS_U32 * snap_num);
WS_ERR model_inquiry_snapfile_by_time(WS_USR_HAND hand,WS_U32 nvr_ch,const ws_utility::ws_time_struct * start_time,const ws_utility::ws_time_struct * stop_time, ws_snap_file_inquiry_type file_type, ws_snap_table_hand * snap_hand,WS_U32 * result_num);
WS_ERR model_get_snapfile_result_for_pb(WS_USR_HAND hand ,WS_U32 nvr_ch, const ws_snap_table_hand snap_hdl,ws_pb_snap_file_inquiry_result * snap_result, time_t* min_time, time_t* max_time);
WS_ERR model_get_snapfile_result(WS_USR_HAND hand, WS_U32 nvr_ch, const ws_snap_table_hand snap_hdl, WS_U32 *start_num, WS_U32 *total_num, ws_snap_file_inquiry_node *snap_result);
WS_ERR model_free_snap_result(WS_USR_HAND hand,ws_snap_table_hand * snap_hdl);

WS_BOOL model_inquiry_have_recfile(WS_USR_HAND hand, WS_U32 nvr_ch,const ws_utility::ws_time_struct *start_time,const ws_utility::ws_time_struct *stop_time);

 //Modified by qqy,start at 2017-02-10 12:11:07
WS_ERR model_set_event_deployment_time(WS_USR_HAND hand ,WS_U32 ch_idx , ws_event_type type  , ws_rec_schedule_day day, const ws_rec_schedule_per_day *schedule);
WS_ERR model_get_event_deployment_time(WS_USR_HAND hand ,WS_U32 ch_idx , ws_event_type type, ws_rec_schedule_day day,  ws_rec_schedule_per_day *schedule);
//change by khs 2017.3.21 start
WS_ERR model_set_event_deployment_time_ex(WS_USR_HAND hand ,ws_event_type type ,WS_U32 ch_idx, const ws_channel_rec_schedule *schedule);
WS_ERR model_get_event_deployment_time_ex(WS_USR_HAND hand ,ws_event_type type ,WS_U32 ch_idx, ws_channel_rec_schedule *schedule);
//change by khs 2017.3.21 end
 //Modified by qqy,end at 2017-02-10 12:11:09

WS_ERR model_clear_event_alarm(WS_USR_HAND hand,ws_event_type event_type, WS_U32 ch_mask);
WS_ERR model_get_ch_roi_rect_info(WS_U32 ch_idx,WS_BOOL* has_roi,ws_utility::ws_real_rect* rect);	

WS_ERR model_get_lv_last_div_info(ws_utility::ws_screen_div_mode *div_mode,WS_U32 * ch_mask, WS_U32 mask_num);	
// change by linhh 20170428
WS_ERR model_set_lv_last_div_info(ws_utility::ws_screen_div_mode  div_mode,WS_U32 * ch_mask, WS_U32 mask_num, WS_BOOL bCfgSave);	
WS_ERR model_get_pb_ch_roi_rect(WS_U32 pb_ch_idx,ws_utility::ws_real_rect* rect);	

WS_ERR model_usr_manual_snap_pic(WS_U32 ch_idx);			
WS_ERR model_cancel_roi_temp(WS_U32 ch_idx, WS_BOOL is_cancel);

WS_ERR model_Pb_NewTaskId(unsigned int *iTaskId);
WS_ERR model_Pb_SetFile(unsigned int iTaskId ,const char *file_name);
WS_ERR model_Pb_SetMode(unsigned int iTaskId , unsigned int Mode); 
WS_ERR model_Pb_SetTime(unsigned int iTaskId , unsigned int time);
WS_ERR model_Pb_GetOneFrame(unsigned int iTaskId,char *buffer,int bufLen,ws_frame_info *frame_info);
WS_ERR model_Pb_GetFileInfo(unsigned int iTaskId,unsigned int * iFileFirstFrameNo, unsigned int * iFileLastFrameNo, struct timeval* start_time,struct timeval* end_time,int * iFileLen);
WS_ERR model_Pb_DelTaskId(unsigned int iTaskId);
WS_ERR model_open_pack_for_xml(const WS_CHAR *directory,xml_file_attr_t *flist,size_t *flist_num,int *real_num);

 WS_ERR model_check_rec_status(WS_U32 rec_ch ,WS_BOOL* rec_status);

/* add by zhangmq 20180527 start*/
//add zmq model层添加基本重置接口[2018-05-03 10:45]
WS_ERR model_resume_default(WS_U32 mask);
WS_ERR model_resume_default_ex(WS_U32 mask);
/* add by zhangmq 20180527 end*/

}

#endif  //_NVR_MODEL_API_H_


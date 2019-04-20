#ifndef _WS_CFG_MANAGE_API_H_
#define _WS_CFG_MANAGE_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_sys.h"
#include "ws_comm_display.h"
#include "ws_dst_def.h"

#include "ws_exception_proc_def.h"
#include "ws_remote_agent_def.h"
#include "ws_network_def.h"
#include "ws_disk_manage_def.h"
#include "ws_usr_manage_def.h"
#include "ws_record_def.h"
#include "ws_comm_av.h"
#include "ws_wifi_def.h"
#include "ws_trigger_def.h"
#include "ws_platform_def.h"
#include "ws_ptz_def.h"
#include "ws_status_def.h"
#include "HieServer_Cfg.h"

using ws_utility::WS_ERR;
#ifdef __cplusplus
extern "C" {
namespace ws_soft   
{
namespace ws_cfgm 
{
#endif

const ws_utility::ws_device_capability *cfg_manage_get_dev_cap();
WS_S32 cfg_get_board_id();	

WS_ERR cfg_manage_init();
WS_ERR cfg_manage_ReinitSerial();							/*add by linhh 20170425*/
WS_ERR cfg_manage_sync_file();                              //关机之前调用，强制保存文件
WS_ERR cfg_fac_manage_sync_file();
WS_ERR cfg_def_manage_video_sync_file();
/* add by zhangmq 20180527 start*/
//add zmq 为sync_file函数在API层增加接口[2018-05-03 11:20]
WS_ERR cfg_common_manage_sync_file();


//add zmq 添加接口[2018-03-27 14:37]
WS_ERR cfg_set_alarm_server(LPHY_DVR_ALARMSERVERINFO_IF pcfg);
WS_ERR cfg_get_alarm_server(LPHY_DVR_ALARMSERVERINFO_IF pcfg);
/* add by zhangmq 20180527 end*/

//--------------------------------- 系统设置 ------------------------------------------------
WS_ERR cfg_manage_save_resol(const char *resol);
WS_ERR cfg_manage_get_resol(char *resol, size_t buf_size);
WS_ERR cfg_fac_manage_get_resol(char *resol, size_t buf_size);

WS_ERR cfg_manage_get_cfg_language(char *language, size_t buf_size);
WS_ERR cfg_fac_manage_get_cfg_language(char *language, size_t buf_size);
WS_ERR cfg_manage_save_language(const char *language);

WS_ERR cfg_manage_get_time_fmt(ws_utility::ws_time_fmt_cfg *time_fmt);
WS_ERR cfg_manage_save_time_fmt(const ws_utility::ws_time_fmt_cfg *time_fmt);

WS_ERR cfg_manage_save_volume(const ws_utility::ws_volume_cfg *volume);
WS_ERR cfg_manage_get_volume(ws_utility::ws_volume_cfg *volume);
WS_ERR cfg_fac_manage_get_volume(ws_utility::ws_volume_cfg *volume);
WS_ERR cfg_def_manage_get_volume(ws_utility::ws_volume_cfg *volume);

WS_ERR cfg_manage_save_hdd_ctl(const ws_hard_disk_work_ctl *hdd_ctl);
WS_ERR cfg_manage_get_hdd_ctl(ws_hard_disk_work_ctl *hdd_ctl);
WS_ERR cfg_fac_manage_get_hdd_ctl(ws_hard_disk_work_ctl *hdd_ctl);

WS_ERR cfg_manage_save_dev_std(ws_video_std std);
WS_ERR cfg_manage_get_dev_std(ws_video_std *std);
WS_ERR cfg_manage_save_dev_name(const char *buf);
WS_ERR cfg_manage_get_dev_name(char *buf, size_t buf_size);


#if defined(_LOCK_SCREEN_)
WS_ERR cfg_manage_get_lock_screen_time(char *buf,size_t buf_size);
WS_ERR cfg_manage_save_lock_screen_time(const char* buf);
#endif

WS_ERR cfg_fac_manage_get_dev_name(char *buf, size_t buf_size);
WS_ERR cfg_def_manage_get_dev_name(char *buf, size_t buf_size);

WS_ERR cfg_manage_save_dev_num(int num);
WS_ERR cfg_manage_get_dev_num(int *num);
WS_ERR cfg_fac_manage_get_dev_num(int *num);
WS_ERR cfg_def_manage_get_dev_num(int *num);

WS_ERR cfg_manage_save_audio_lv_state(int support_audio_lv);
WS_ERR cfg_manage_get_audio_lv_state(int *support_audio_lv);
WS_ERR cfg_fac_manage_get_audio_lv_state(int *support_audio_lv);

/* del by zhangmq 20180527 */
#if 0
WS_ERR cfg_manage_resume_defult(WS_U32 mask);

 //Modified by qqy,start at 2017-02-15 10:53:58
WS_ERR resume_timer_rec_cfg();
WS_ERR resume_holiday_cfg();
WS_ERR resume_channel_cfg_ex();
WS_ERR resume_osd_cfg();
WS_ERR resume_ptz_cfg();
WS_ERR resume_md_cfg();
#endif

WS_ERR resume_basic_cfg();
/* del by zhangmq 20180527 */
#if 0
WS_ERR resume_time_cfg();
WS_ERR resume_basic_net_cfg();
WS_ERR resume_ao_cfg();
WS_ERR resume_ai_cfg();
WS_ERR resume_ai_linkage_cfg();
WS_ERR resume_md_linkage_cfg();
WS_ERR resume_port_cfg();
WS_ERR resume_ntp_cfg();
WS_ERR cfg_manage_resume_default_ex(WS_U32 mask); 
#endif

WS_ERR resume_sys_cfg();
/* del by zhangmq 20180527 */
#if 0

//----------------------------------录像计划,节假日----------------------------------------------

WS_ERR cfg_def_manage_get_holiday(WS_U16 year, WS_U16 month, WS_U32 *mask);

//设置指定月份哪些天是节假日，bit0-bit30对应1号-31号，0表示不是，1表示是.
WS_ERR resume_rec_shedule();

WS_ERR resume_net_cfg();

WS_ERR resume_channel_cfg();

WS_ERR resume_enc_cfg();

WS_ERR resume_alarm_enc_cfg();

WS_ERR cfg_fac_manage_get_md_rect(int nvr_ch, int rect_idx, ws_utility::ws_abstract_rect *rect);
WS_ERR cfg_def_manage_get_md_rect(int nvr_ch, int rect_idx, ws_utility::ws_abstract_rect *rect);

//-------------------------------------pppoe所需的配置文件-----------------------------------------------------
WS_ERR resume_pppoe_cfg();

//-------------------------------------私有DNS所需的配置文件-----------------------------------------------------
WS_ERR resume_ddns_cfg();

//-------------------------------------smtp所需的配置文件-----------------------------------------------------

WS_ERR resume_smtp_cfg();

WS_ERR resume_wifi_cfg();


#endif

WS_ERR resume_alarm_cfg();

WS_ERR resume_exception_cfg();

/* del by zhangmq 20180527 */
#if 0

//---------------------------------- ptz --------------------------------------------------------------------
WS_ERR cfg_manage_del_ptz_cruise_point(WS_U32 ch, ws_ptz_ctl_type protocol, WS_U32 idx);
WS_ERR cfg_manage_set_ptz_cruise_point(WS_U32 ch, ws_ptz_ctl_type protocol, const ws_ptz_cruise_point* cruise_point);
WS_ERR cfg_manage_get_ptz_speed(WS_U32 ch, WS_U32* speed);
WS_ERR cfg_manage_get_ptz_info(WS_U32 ch, ws_ptz_ctl_info* ptz_info);
WS_ERR cfg_manage_get_ptz_cruise_line(WS_U32 ch, ws_ptz_ctl_type protocol, ws_ptz_cruise_line* cruise_line);


WS_ERR cfg_fac_manage_get_ptz_cfg(WS_U32 ch, ws_ptz_ch_info * ptz_ch_info);

//--------------------------------ipc同步时间----------------------------------------------------
WS_BOOL cfg_manage_get_enable_sync_ipc_time();
WS_BOOL cfg_fac_manage_get_enable_sync_ipc_time(WS_BOOL *sync_ipc_time);
WS_ERR cfg_manage_set_enable_sync_ipc_time(WS_BOOL enable);

//-----------------------------------密码复位 -----------------------------------------------------------
WS_ERR cfg_manage_reset_admin();

//-----------------------------配置文件的导入----------------------------
WS_ERR cfg_import_cfg_file(const WS_CHAR *filename);
#endif

//-------------------------------------只用于sample生成默认配置文件--------------------------------
/**
  *
  *其他函数不要调用该接口
  *
  *
 **/
WS_ERR cfg_fac_manage_save_cfg_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_S32 para);
WS_ERR cfg_fac_manage_save_cfg_str(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, const char *str);

WS_ERR cfg_manage_read_cfg_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_S32 *para);
WS_ERR cfg_manage_read_cfg_str(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, char *str, size_t buf_size);

WS_ERR cfg_ptz_fac_manage_save_cfg_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_S32 para);

WS_ERR cfg_set_live_last_div_mode(ws_utility::ws_screen_div_mode div_mode,WS_U32 *ch_mask, WS_U32 mask_num);
WS_ERR cfg_get_live_last_div_mode(ws_utility::ws_screen_div_mode *div_mode,WS_U32* ch_mask, WS_U32 mask_num);

/**********  live poll *************/
#if defined(_SUPPORT_POLL_LIVE_)
WS_ERR cfg_set_live_poll_enabe_state(WS_BOOL is_set);			// is_set: 1  enable;  is_set:0 disable;
WS_ERR cfg_get_live_poll_enabel_state(WS_BOOL *has_enable);	
WS_ERR cfg_set_live_poll_info(ws_utility::ws_poll_live_type_e poll_type, ws_utility::ws_user_cfg_poll_live_s *cfg_info, WS_U32 ch_max_num); 
WS_ERR cfg_get_live_poll_info(ws_utility::ws_poll_live_type_e poll_type, ws_utility::ws_user_cfg_poll_live_s *cfg_info, WS_U32 ch_max_num) ;
#endif

/* add by zhangmq 20180527 start*/
//add zmq 在API层增加公开的XML 读写接口,供其它模块调用[2018-05-02 14:09]
WS_ERR proc_write_str(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, const WS_CHAR *str);
WS_ERR proc_fac_write_str(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, const WS_CHAR *str);
WS_ERR proc_read_str(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_CHAR *buf, size_t buf_size);
WS_ERR proc_fac_read_str(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_CHAR *buf, size_t buf_size);
WS_ERR proc_write_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_S32 para);
WS_ERR proc_fac_write_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, const WS_S32 para);
WS_ERR proc_read_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_S32 *para);
WS_ERR proc_fac_read_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_S32 *para);

WS_ERR proc_read_attr_str(const char *key1, const char *key2,const char *key3 ,const char *attr, char *buf, size_t buf_size);
WS_ERR proc_write_attr_str(const char *key1, const char *key2, const char *key3,const char *attr, const char *str);
WS_ERR proc_fac_read_attr_str(const char *key1, const char *key2,const char *key3 ,const char *attr, char *buf, size_t buf_size);
WS_ERR proc_fac_write_attr_str(const char *key1, const char *key2, const char *key3,const char *attr, const char *str);

WS_ERR proc_ptz_def_write_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, const WS_S32 para);
WS_ERR proc_ptz_fac_write_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, const WS_S32 para);
WS_ERR proc_ptz_write_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_S32 para);
WS_ERR proc_ptz_read_int(const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_S32 *para);

//add zmq API层添加基本的对内存镜像文件操作
WS_ERR proc_ugm_write_str(const WS_CHAR *key0,const WS_CHAR *key1, const char *key2, const char *key3,const WS_CHAR *str);
WS_ERR proc_ugm_write_int(const WS_CHAR *key0,const WS_CHAR *key1, const char *key2, const char *key3,WS_S32 para);
WS_ERR proc_ugm_read_str(const WS_CHAR *key0,const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_CHAR *buf, size_t buf_size);
WS_ERR proc_ugm_read_int(const WS_CHAR *key0,const WS_CHAR *key1, const WS_CHAR *key2, const char *key3, WS_S32 *para);


//add zmq 在API层针对密码口令增加公开的加解密接口[2018-05-02 15:15]
WS_ERR ws_cfg_enc(const char *need_enc, char *passwd, size_t pass_size);
WS_ERR ws_cfg_old_dec(const char *need_dec, char *noted, size_t noted_size);   
WS_ERR ws_cfg_dec(const char *need_dec, char *noted, size_t noted_size);

//add zmq 在API层添加公有接口[2018-05-02 10:07]
WS_BOOL is_valid_ch(int nvr_ch);
WS_BOOL is_valid_ai_ch(int nvr_ch);

//add zmq 在API层添加通用函数[2018-05-02 10:07]
void Fill_time_for_record_or_alarm(char* buffer, size_t nLen,  WS_ERR bSuccess, ws_soft::ws_rec_sub_schedule* m_time);
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
}//namespace ws_cfgm {
}//namespace ws_soft {
}//extern "C" {

#endif

#endif//#ifndef _WS_CFG_MANAGE_API_H_


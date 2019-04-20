#ifndef _WS_PLATFORM_API_H_
#define _WS_PLATFORM_API_H_

#include "ws_comm_sys.h"
#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_data.h"
#include "ws_comm_av.h"

#include "ws_platform_def.h"
#include "ws_playback_def.h"
#include <termios.h>
#include "ws_status_api.h" 
#include "ws_network_def.h"
#include "ws_remote_agent_def.h"
#include "ws_trigger_def.h"

using ws_utility::WS_ERR;

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

WS_ERR platform_init(ws_video_std std);

//设置LOGO点阵，bg_color为RGB888格式的背景色，尺寸超过352*288后会自动裁剪，小于352*288会自动居中，不足部分填充bg_color
//bit格式为RGB1888, 一个像素占32bit，alpha: bit31-24，R: bit23-16，G: bit15-8，B: bit7-0，
//alpha为0显示bg_color，否则显示设置像素
WS_ERR platform_set_logo(ws_utility::ws_logo_type type, int *bit, int bit_w, int bit_h, int bg_color);  //LOGO图片

WS_ERR platform_set_std(ws_video_std std);

WS_ERR platform_set_resol(const WS_CHAR *resol);   

/*****************************************************************************************************
    fb 为RGB1555式为思院3531colorkey丶色alpha模式实止丶色
    guiRGB155式墓丶色转RGB1555式医alpha位0色alpha位1实止丶色效

    为追效RGB8888式
*****************************************************************************************************/
WS_ERR platform_start_fb_dis(); 
WS_ERR platform_stop_fb_dis(); 
WS_ERR platform_set_fb_trans(int percent); 
WS_ERR platform_get_fb_addr(void **addr, int *max_fb_size);
WS_ERR platform_set_vdec_mode(WS_U32 vdec_pipe, platform_vdec_work_mode mode, ws_utility::ws_logo_type logo_type);  
WS_ERR platform_set_vdec_rect(WS_U32 vdec_pipe, const ws_utility::ws_abstract_rect *rect);
WS_ERR platform_stop_vdec_rect(WS_U32 vdec_pipe);

WS_ERR platform_set_vdec_roi(WS_U32 vdec_pipe, const ws_utility::ws_abstract_rect *roi_rect);
WS_ERR platform_cancel_vdec_roi(WS_U32 vdec_pipe);
WS_ERR platform_set_rect_is_change(WS_U32 vdec_pipe, WS_BOOL value); 

WS_ERR platform_send_vdec_data(WS_U32 vdec_pipe, const ws_frame_info *frame, const char *data, WS_U8 magic, WS_BOOL need_dis);
WS_ERR platform_set_vdec_magic(WS_U32 vdec_pipe, WS_U8 magic);
WS_ERR platform_set_vdec_dir(WS_U32 vdec_pipe, ws_playback_direction dir);
WS_ERR platform_pause_vdec(WS_U32 vdec_pipe);
WS_ERR platform_resume_vdec(WS_U32 vdec_pipe);
WS_ERR platform_step_vdec(WS_U32 vdec_pipe);
WS_ERR platform_set_vdec_speed(WS_U32 vdec_pipe, ws_playback_speed speed);
WS_ERR platform_set_sync_focus_channel(int ch);

WS_ERR platform_start_audio_rec(WS_U32 ch_idx);
WS_ERR platform_stop_audio_rec(WS_U32 ch_idx);

WS_ERR platform_start_audio_lv(WS_U32 ch_idx);
WS_ERR platform_stop_audio_lv(WS_U32 ch_idx);

WS_ERR platform_start_audio_pb(WS_U32 ch_idx);
WS_ERR platform_stop_audio_pb(WS_U32 ch_idx);

WS_ERR platform_start_audio_talking();
WS_ERR platform_stop_audio_talking();

WS_ERR platform_send_audio_frame(WS_U32 ch_idx, const ws_frame_info *frame, const char *data);
WS_ERR platform_get_audio_frame(WS_U32 ch_idx, ws_frame_info *frame, char *data, WS_U32 data_len);

WS_ERR platform_send_talking_frame(const ws_frame_info *frame, const char *data);
WS_ERR platform_get_talking_frame(ws_frame_info *frame, char *data, WS_U32 data_len);
WS_ERR platform_restart_venc_ch(WS_U32 dvr_ch,  ws_venc_str_type str_type);
//--------------------------------END--------------------------------------------------

WS_BOOL platform_is_vdec_finish(WS_U32 vdec_pipe);
WS_ERR platform_malloc_dec_pipe(ws_utility::ws_module_id usr_id, int *pipe_idx);
WS_ERR platform_free_dec_pipe(ws_utility::ws_module_id usr_id, int pipe_idx);

WS_ERR platform_get_vdec_time(WS_U32 vdec_pipe, struct timeval *time);

WS_ERR platform_get_sync_grp_time(struct timeval *time);  
WS_ERR platform_get_sync_wait_ch(int ch,WS_BOOL* is_wait,int* wait_time); 

WS_ERR platform_start_grp(time_t time);
WS_ERR platform_stop_grp();
WS_ERR platform_seek_grp(time_t time);

WS_ERR platform_set_grp_speed(ws_playback_speed speed);
WS_ERR platform_set_grp_dir(ws_playback_direction dir);

//-------------------------------------------------------------------------------

//--------------------------------------------- VGA效 ------------------------------------------------------
WS_ERR platform_get_hi_vga_param(HI_VGA_PARAM_S *para);
WS_ERR platform_set_hi_vga_param(const HI_VGA_PARAM_S *para);

WS_ERR platform_set_vo_param(const ws_soft::ws_vo_output_param *vo_output_param);
WS_ERR platform_get_vo_param(ws_soft::ws_vo_output_param *vo_output_param);

WS_ERR platform_set_vga_param(const ws_soft::ws_vga_output_param *vga_output_param);
WS_ERR platform_get_vga_param(ws_soft::ws_vga_output_param *vga_output_param);

WS_ERR platform_set_vpss_param(ws_soft::ws_vpss_param_type vpss_param_type, const ws_soft::ws_vpss_param *vpss_param);
WS_ERR platform_get_vpss_param(ws_soft::ws_vpss_param_type vpss_param_type, ws_soft::ws_vpss_param *vpss_param);

WS_ERR platform_vpss_NR_ctl(WS_BOOL enable);
WS_ERR platform_vpss_IE_ctl(WS_BOOL enable);
WS_ERR platform_vpss_SP_ctl(WS_BOOL enable);

WS_ERR platform_get_vpss_NR_status(WS_BOOL *enable);
WS_ERR platform_get_vpss_IE_status(WS_BOOL *enable);
WS_ERR platform_get_vpss_SP_status(WS_BOOL *enable);

WS_ERR  platform_enable_watch_dog();
WS_ERR platform_fetch_dog();
WS_ERR platform_disable_watch_dog();
WS_ERR platform_reboot();

WS_ERR platform_get_ch_roi_info(WS_U32 ch_idx,WS_BOOL* has_roi,ws_utility::ws_real_rect* rect);	
 
WS_ERR platform_start_live(const ws_utility::ws_display_screen_info *screen_info, const ws_utility::ws_wind_content *wind_content, size_t content_dim);

WS_ERR platform_stop_live();

WS_ERR platform_update_video_state(WS_U32 ch_idx, WS_BOOL is_lost, ws_soft::ws_video_format video_format);

WS_ERR platform_lv_mouse_set_roi(WS_U32 dvr_ch, const ws_utility::ws_abstract_coordinate *roi_coor, WS_BOOL amplif);
WS_ERR platform_lv_move_roi_rect(WS_U32 dvr_ch, const ws_utility::ws_abstract_coordinate *start, const ws_utility::ws_abstract_coordinate *stop);
WS_ERR platform_lv_cancel_roi(WS_U32 dvr_ch);

WS_ERR platform_cfg_md_info(WS_U32 dvr_ch, const ws_soft::ws_md_arr *md_info);

WS_ERR platform_get_md_cfg(WS_U32 dvr_ch, ws_soft::ws_md_arr *md_info);

WS_ERR platform_get_md_status(WS_U32 dvr_ch, ws_soft::ws_md_state *md_state);

WS_ERR platform_get_ch_std(WS_U32 dvr_ch, ws_soft::ws_video_std *video_std);

//-----------------------------------------------------------------------------------------------------
WS_ERR platform_set_enc_para(WS_U32 dvr_ch, ws_soft::ws_venc_str_type str_type, const ws_soft::ws_enc_para *para);
WS_ERR platform_get_enc_para(WS_U32 dvr_ch, ws_soft::ws_venc_str_type str_type, ws_soft::ws_enc_para *para);

WS_ERR platform_get_enc_input_fps(WS_U32 dvr_ch, WS_S32 *enc_input_fps);

WS_ERR platform_get_ch_max_fps(WS_U32 dvr_ch, ws_soft::ws_venc_str_type str_type, WS_U32 *max_fps);

WS_ERR platform_sync_list_time();
WS_ERR platform_set_list_new_magic(WS_U32 new_magic);
WS_ERR platform_get_channel_bit_rate(WS_U32 dvr_ch, WS_U32 *bit);
WS_ERR platform_get_sub_channel_bit_rate(WS_U32 dvr_ch, WS_U32 *bit);
WS_ERR platform_get_bit_rate(WS_U32 dvr_ch, ws_venc_str_type type, STREAM_SPEED speed, WS_U32 *bit);    

WS_ERR platform_set_osd_ch_name(WS_U32 dvr_ch, const WS_CHAR *ch_name, const WS_CHAR *bit_map, WS_U32 width, WS_U32 height);

WS_ERR platform_get_ch_name(WS_U32 dvr_ch, WS_CHAR *ch_name, size_t size);
WS_VOID platform_set_osd_time_dot(const char * dot,WS_S32 dot_num,WS_S32 single_dot_length, WS_CHAR *srcAsc, WS_U32 curLen);
WS_ERR platform_cfg_osd(WS_U32 dvr_ch, ws_soft::ws_osd_type osd_type, ws_soft::ws_location_type location_type);

#if defined(_SUPPORT_TIME_TYPE_AND_STANDARD_)
WS_ERR platform_cfg_time_type_and_standard(ws_soft::ws_time_type_and_standard *time_type_and_standard);
#endif 

WS_ERR platform_get_osd_cfg(WS_U32 dvr_ch, ws_soft::ws_osd_type osd_type, ws_soft::ws_location_type *location_type);

WS_ERR platform_snap_pic(WS_U32 dvr_ch, const WS_CHAR *file_name,time_t* frame_time);	
WS_ERR platform_snap_pic_by_mask(WS_U32 *ch_mask, WS_U32 mask_num,  WS_CHAR *file_name,time_t * real_time);
WS_ERR platform_user_snap_pic(WS_U32 dvr_ch, const WS_CHAR *absolute_path, WS_CHAR *picture_cache, WS_S32 pic_size, WS_U32 *pic_length, time_t* frame_time,ws_soft::ws_snap_type snap_type);

WS_ERR platform_get_chip_ch_info(WS_U32 ch_idx, ws_soft::ws_av_chip_ch_info *ch_info);

void load_av_driver(WS_S32 board_id);
WS_ERR platform_cancel_roi_temp(WS_U32 ch_idx,WS_BOOL is_cancel);	
WS_ERR platform_rel_remain_jpeg_frame(void);	

WS_ERR platform_live_send_vdec_data(WS_U32 vdec_pipe, const ws_frame_info *frame, const char *data, WS_U8 magic, WS_BOOL need_dis);
WS_ERR platform_live_malloc_dec_pipe(ws_utility::ws_module_id usr_id, int *pipe_idx, int nWnd);
WS_ERR platform_live_free_dec_pipe(ws_utility::ws_module_id usr_id, int pipe_idx);
WS_ERR platform_live_set_vdec_mode(WS_U32 vdec_pipe, platform_vdec_work_mode mode, ws_utility::ws_logo_type logo_type); 
WS_ERR platform_live_set_vdec_rect(WS_U32 vdec_pipe, const ws_utility::ws_abstract_rect *rect);
WS_ERR platform_live_stop_vdec_rect(WS_U32 vdec_pipe);
WS_ERR platform_live_set_vdec_roi(WS_U32 vdec_pipe, const ws_utility::ws_abstract_rect *roi_rect);
WS_ERR platform_live_cancel_vdec_roi(WS_U32 vdec_pipe);

// add by khs start 2017.11.3
WS_ERR platform_set_vdec_mode_pic(WS_U32 vdec_pipe, platform_vdec_work_mode mode, ws_utility::ws_logo_type logo_type);  
WS_ERR platform_set_vdec_rect_pic(WS_U32 vdec_pipe, const ws_utility::ws_abstract_rect *rect);
WS_ERR platform_stop_vdec_rect_pic(WS_U32 vdec_pipe);

WS_ERR platform_set_vdec_roi_pic(WS_U32 vdec_pipe, const ws_utility::ws_abstract_rect *roi_rect);
WS_ERR platform_cancel_vdec_roi_pic(WS_U32 vdec_pipe);
WS_ERR platform_set_rect_is_change_pic(WS_U32 vdec_pipe, WS_BOOL value); 
WS_ERR platform_send_vdec_jpeg_data_pic(WS_U32 vdec_pipe, const ws_frame_info *frame, const char *data, WS_U8 magic, WS_BOOL need_dis);

WS_ERR platform_set_vdec_magic_pic(WS_U32 vdec_pipe, WS_U8 magic);
WS_ERR platform_set_vdec_dir_pic(WS_U32 vdec_pipe, ws_playback_direction dir);
WS_ERR platform_pause_vdec_pic(WS_U32 vdec_pipe);
WS_ERR platform_resume_vdec_pic(WS_U32 vdec_pipe);
WS_ERR platform_step_vdec_pic(WS_U32 vdec_pipe);
WS_ERR platform_set_vdec_speed_pic(WS_U32 vdec_pipe, ws_playback_speed speed);
WS_ERR platform_malloc_dec_pipe_pic(ws_utility::ws_module_id usr_id, int *pipe_idx);
WS_ERR platform_free_dec_pipe_pic(ws_utility::ws_module_id usr_id, int pipe_idx);

WS_ERR platform_get_vdec_time_pic(WS_U32 vdec_pipe, struct timeval *time);
WS_ERR platform_stop_grp_pic();
WS_ERR platform_set_grp_speed_pic(ws_playback_speed speed);

/* add by zhangmq 20180527 start*/
//add zmq 预加载平台配置信息[2018-05-05 17:22]
void proc_platform_cfg();

//add zmq 将cfg模块的通道配置移入到platform模块中[2018-05-05 14:06]
WS_ERR cfg_manage_set_channel_cfg(WS_U32 index, ws_connet_rule *rule);
WS_ERR cfg_manage_get_channel_cfg(WS_U32 index, ws_connet_rule *rule);
WS_ERR cfg_fac_manage_get_channel_cfg(WS_U32 index, ws_connet_rule *rule);
WS_ERR resume_channel_cfg();
WS_ERR resume_channel_cfg_ex();

//add zmq 将cfg模块的编码配置移入到platform模块中[2018-05-05 10:52]
WS_ERR cfg_manage_set_enc_para(WS_U32 ch_idx, ws_venc_str_type stream_type, const ws_enc_para *enc_para);
WS_ERR cfg_manage_get_enc_para(WS_U32 ch_idx, ws_venc_str_type stream_type, ws_enc_para *enc_para);
WS_ERR cfg_fac_manage_get_enc_para(WS_U32 ch_idx, ws_venc_str_type stream_type, ws_enc_para *enc_para);
WS_ERR cfg_manage_set_alarm_enc_para(WS_U32 ch_idx,  const ws_enc_para *enc_para);
WS_ERR cfg_manage_get_alarm_enc_para(WS_U32 ch_idx,  ws_enc_para *enc_para);
WS_ERR cfg_fac_manage_get_alarm_enc_para(WS_U32 ch_idx,  ws_enc_para *enc_para);
WS_ERR resume_enc_cfg();
WS_ERR resume_alarm_enc_cfg();

//add zmq  将cfg模块的移动侦测接口移入到platform模块中[2018-05-05 14:07]
WS_ERR cfg_manage_get_md_rect(int nvr_ch, int rect_idx, ws_utility::ws_abstract_rect *rect);
WS_ERR cfg_fac_manage_get_md_rect(int nvr_ch, int rect_idx, ws_utility::ws_abstract_rect *rect);
WS_ERR cfg_def_manage_get_md_rect(int nvr_ch, int rect_idx, ws_utility::ws_abstract_rect *rect);
WS_ERR cfg_manage_save_md_rect(int nvr_ch, int rect_idx, const ws_utility::ws_abstract_rect *rect);
WS_ERR cfg_manage_get_md_rect_num(int ch_idx, WS_U32 *md_rect_num);
WS_ERR cfg_fac_manage_get_md_rect_num(int ch_idx, WS_U32 *md_rect_num);
WS_ERR cfg_manage_save_md_rect_num(int ch_idx, WS_U32 md_rect_num);
WS_ERR cfg_manage_get_md_sensitivity(int ch_idx, ws_soft::ws_md_sensitivity *md_sensitivity);
WS_ERR cfg_fac_manage_get_md_sensitivity(int ch_idx, ws_soft::ws_md_sensitivity *md_sensitivity);
WS_ERR cfg_manage_save_md_sensitivity(int ch_idx, ws_soft::ws_md_sensitivity md_sensitivity);
WS_ERR resume_md_cfg();

//add zmq 转移cfg模块中osd的配置[2018-05-05 14:38]
WS_ERR cfg_manage_set_chn_name(int ch, const char *name);
WS_ERR cfg_manage_get_chn_name(int ch, char *name, size_t name_size);
WS_ERR cfg_fac_manage_get_chn_name(int ch, char *name, size_t name_size);	
WS_ERR cfg_manage_set_osd_chn_name_pos(int ch, ws_location_type type);
WS_ERR cfg_manage_get_osd_chn_name_pos(int ch, ws_location_type *type);
WS_ERR cfg_fac_manage_get_osd_chn_name_pos(int ch, ws_location_type *type); 
WS_ERR cfg_manage_set_osd_time_pos(int ch, ws_location_type type);
WS_ERR cfg_manage_get_osd_time_pos(int ch, ws_location_type *type);
WS_ERR cfg_fac_manage_get_osd_time_pos(int ch, ws_location_type *type);
WS_ERR resume_osd_cfg();

//add zmq 转移cfg模块中告警配置接口[2018-05-05 18:23]
WS_ERR cfg_manage_set_ai_type(WS_U32 ai_channel, ws_utility::ws_ai_check_type ai_type);
WS_ERR cfg_manage_get_ai_type(WS_U32 ai_channel, ws_utility::ws_ai_check_type *ai_type);
WS_ERR cfg_fac_manage_get_ai_type(WS_U32 ai_channel, ws_utility::ws_ai_check_type *ai_type);

 //add by qqy,start at 2017-01-19 11:32:50
WS_ERR cfg_manage_set_ai_config(WS_U32 ch,ws_utility::ws_ai_config* config);
WS_ERR cfg_manage_get_ai_config(WS_U32 ch, ws_utility::ws_ai_config *config);
WS_ERR cfg_fac_manage_get_ai_config(WS_U32 ch, ws_utility::ws_ai_config *config);
WS_ERR cfg_manage_set_ao_config(WS_U32 ch,ws_utility::ws_ao_config* config);
WS_ERR cfg_manage_get_ao_config(WS_U32 ch, ws_utility::ws_ao_config *config);
WS_ERR cfg_fac_manage_get_ao_config(WS_U32 ch, ws_utility::ws_ao_config *config);
 //add by qqy,end at 2017-01-19 11:32:52
 
WS_ERR cfg_manage_set_ao_time(WS_U32 ms_sec);
WS_ERR cfg_manage_get_ao_time(WS_U32 *ms_sec);
WS_ERR cfg_fac_manage_get_ao_time(WS_U32 *ms_sec);

WS_ERR cfg_manage_set_event_deployment_time(WS_U32 ch_idx , ws_soft::ws_event_type type ,ws_rec_schedule_day day,   const ws_rec_schedule_per_day *schedule); 
WS_ERR cfg_manage_get_event_deployment_time(WS_U32 ch_idx , ws_soft::ws_event_type type , ws_rec_schedule_day day,  ws_rec_schedule_per_day *schedule ); 
WS_ERR cfg_fac_manage_get_event_deployment_time(WS_U32 ch_idx , ws_soft::ws_event_type type , ws_rec_schedule_day day,  ws_rec_schedule_per_day *schedule);

//-----------------------------事件----------------------------------------------------
WS_ERR cfg_manage_set_exception(const exception_linkage *excep);
WS_ERR cfg_manage_get_exception(exception_type type, exception_control *excep_ctr);
WS_ERR cfg_fac_manage_get_exception(exception_type type, exception_control *excep_ctr);

//---------------------------------- 报警联动 ----------------------------------------------------
WS_ERR cfg_manage_set_linkage_cfg(ws_trig_source src_type, WS_U32 src, const ws_trig_operation *operation);
WS_ERR cfg_manage_get_linkage_cfg(ws_trig_source src_type, WS_U32 src, ws_trig_operation *operation);
WS_ERR cfg_fac_manage_get_linkage_cfg(ws_trig_source src_type, WS_U32 src, ws_trig_operation *operation);

WS_ERR resume_ao_cfg();
WS_ERR resume_ai_cfg();
WS_ERR resume_ai_linkage_cfg();
WS_ERR resume_md_linkage_cfg();
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_PLATFORM_API_H_


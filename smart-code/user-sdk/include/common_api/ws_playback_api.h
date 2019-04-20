#ifndef _WS_PLAYBACK_API_H_
#define _WS_PLAYBACK_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_flist.h"

#include "ws_playback_def.h"
using ws_utility::WS_ERR;


#ifdef __cplusplus
extern "C" {
namespace ws_play 
{
#endif

WS_ERR playback_init(int pb_ch_num);

WS_ERR playback_set_pb_mode(ws_soft::ws_playback_mode mode);
WS_ERR playback_set_pb_rec_file(WS_U32 pb_ch, const ws_soft::ws_pb_rec_file_inquiry_result *source, const ws_soft::file_result_handle* hdls);
WS_ERR playback_set_pb_snap_file(WS_U32 pb_ch, const ws_soft::ws_pb_snap_file_inquiry_result *source, const ws_soft::file_result_handle* hdls); 

WS_ERR playback_start_audio(WS_U32 pb_ch);
WS_ERR playback_stop_audio();

WS_ERR playback_stop_rect();
WS_ERR playback_set_ch_mode(WS_BOOL ch_mode,WS_U32 ch); //add by khs 2017.6.28

WS_ERR playback_set_rect(const ws_utility::ws_display_screen_info *screen_info, const ws_utility::ws_wind_content *wind_content, size_t content_dim);   //设置回放显示窗口区域
WS_ERR playback_set_full_screen(ws_utility::ws_screen_div_mode div_mode, const WS_S32 *ch_idx, size_t ch_dim);		//设置回放显示窗口 全屏显示

WS_ERR playback_set_interval_time(WS_U32 interval_time_ms);
WS_ERR playback_set_roi(WS_U32 pb_ch, const ws_utility::ws_abstract_rect *roi_rect);
WS_ERR playback_cancel_roi(WS_U32 pb_ch);

WS_ERR playback_start(time_t time,time_t end_time = 0xffffffff); //启动回放
WS_ERR playback_set_end_time(time_t end_time = 0xffffffff); //启动回放
WS_ERR playback_stop(); //停止回放

WS_ERR playback_start_period(time_t start_time,time_t end_time);

WS_ERR playback_seek_time(time_t time,WS_BOOL has_reflash =WS_FALSE,WS_BOOL need_lock=WS_FALSE); //设置回放进度
WS_ERR playback_get_time(time_t *time); //获取回放进度

WS_ERR playback_pause_pb();
WS_ERR playback_resume_pb();
WS_ERR playback_set_focus_channel(int ch);//设置焦点通道

WS_ERR playback_step(ws_soft::ws_playback_step_mode mode);

WS_ERR playback_set_speed(ws_soft::ws_playback_speed speed);
WS_ERR playback_set_dir(ws_soft::ws_playback_direction dir); //设置回放方向

WS_ERR playback_mouse_set_roi(WS_S32 nvr_ch, const ws_utility::ws_abstract_coordinate *roi_coor, WS_BOOL amplif);
WS_ERR playback_move_roi_rect(WS_S32 nvr_ch, const ws_utility::ws_abstract_coordinate *start, const ws_utility::ws_abstract_coordinate *stop);

WS_BOOL playback_is_play_end(WS_S32 nvr_ch);		

WS_BOOL playback_is_pb_ch_have_data(WS_U32 ch_idx); 

WS_ERR playback_get_ch_roi_rect(WS_U32 pb_ch_idx,ws_utility::ws_real_rect* rect);	

WS_ERR playback_set_channel(WS_U32 ch,WS_U32 channel);//add by khs 2017.7.14

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //#ifndef _WS_COMM_PLAYBACK_H_


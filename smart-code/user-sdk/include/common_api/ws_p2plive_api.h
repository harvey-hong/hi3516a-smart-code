#ifndef _WS_P2PLIVE_H_
#define _WS_P2PLIVE_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_display.h"
#include "ws_p2plive_resource.h"


using ws_utility::WS_ERR;
#ifdef __cplusplus
extern "C" {

namespace ws_soft
{
#endif

WS_ERR p2plive_init(int nvr_ch);   

WS_ERR p2plive_set_authority_mask(WS_U32 *mask, WS_U32 mask_num);			
WS_ERR p2plive_start(const ws_utility::ws_display_screen_info *screen_info, const ws_utility::ws_wind_content *wind_content, size_t content_dim);
WS_ERR p2plive_stop();

WS_ERR p2plive_set_roi( WS_S32 nvr_ch,const ws_utility::ws_abstract_rect *roi_rect);
WS_ERR p2plive_mouse_set_roi( WS_S32 nvr_ch,const ws_utility::ws_abstract_coordinate *roi_coor, WS_BOOL amplif);
WS_ERR p2plive_move_roi_rect( WS_S32 nvr_ch,const ws_utility::ws_abstract_coordinate *start, const ws_utility::ws_abstract_coordinate *stop);
WS_ERR p2plive_cancel_roi(WS_S32 nvr_ch);
WS_ERR p2plive_get_roi_rect(WS_S32 nvr_ch,WS_BOOL* has_roi,ws_utility::ws_real_rect *rect);		// add by lz 20160217;

WS_ERR p2plive_stop_audio();
WS_ERR p2plive_set_enc_data_magic(WS_U32 magic);  


#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //#ifndef _UTILITY_API_H_



#ifndef _LIST_MANAGE_API_H__
#define _LIST_MANAGE_API_H__

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_sys.h" 
#include "ws_common.h"
#include "ws_comm_av.h"

#include "ws_comm_data.h"
#include "ws_ptz_def.h"
#include "list_manage.h"

using ws_utility::ws_module_id;
using namespace ws_utility;
using namespace ws_soft;

#ifdef __cplusplus
extern "C" {
namespace ws_listnode_manage
{
#endif

    // change by linhh 20170330 : create list 
    WS_VOID list_manage_init();
    WS_ERR list_manage_new_node(WS_U32 chIndex, WS_U32 max_node_num, int Mode);
    /* 为P2P 的测试代码服务，只能创建一个通道的数据链表，通道号内部固定为0xFF */
    WS_ERR get_list_manage_reource_api();
    WS_ERR list_manage_set_new_magic(WS_U32 chIndex, WS_U32 pmagic);     
    WS_ERR list_manage_change_local_pts_api(WS_U32 chIndex);
    WS_ERR list_manage_get_recv_pos_api(WS_U32 chIndex,int Mode, int len,WS_UCHAR ** frame_data);
    WS_ERR list_manage_delete_all_node_api(WS_U32 chIndex);
    WS_ERR list_manage_push_data_api(WS_U32 chIndex,int Mode,const ws_frame_info *frame_info, WS_UCHAR *buffadd);
    WS_ERR list_manage_first_get_list_data_api(WS_U32 chIndex,int Mode, ws_module_id module,
        ws_frame_info *frame_info, WS_UCHAR **frame_data, WS_U32 *node_idx);
    WS_ERR list_manage_get_list_data_api(WS_U32 chIndex,int Mode,ws_module_id module,
        ws_frame_info *frame_info, WS_UCHAR **frame_data, WS_U32 last_node_idx, WS_U32 *cur_node_idx);
    WS_ERR list_manage_rel_node_api(WS_U32 chIndex,int Mode,ws_module_id usr_id, WS_U32 node_idx);

    WS_ERR list_manage_get_bit_rate(WS_U32 chIndex, int Mode, STREAM_SPEED speed, WS_U32 *get_kb);
    WS_BOOL list_manage_get_connect_status(WS_U32 chIndex);

    WS_ERR list_manage_push_data_one_api(WS_U32 chIndex,int Mode,const ws_frame_info *frame_info, int *part_addr, int *part_len, int PartNum , int FrameLen);
#ifdef __cplusplus
}
}//extern "C" {
#endif  //_WS_REMOTE_AGENT_API_H_

#endif

#ifndef _WS_UPDATE_API_H_
#define _WS_UPDATE_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_update_def.h"


#ifdef __cplusplus
extern "C" {
namespace ws_update_name
{
#endif

WS_ERR update_init();

WS_ERR update_scan_packet(const char *directory, update_file_attr_t *flist, size_t flist_num, int *real_num);
WS_ERR update_start_work_for_local(const WS_CHAR *packet_fname, WS_BOOL auto_del_packet);

WS_ERR update_start_work_for_network(const WS_CHAR *file_buffer,const WS_U32 buffer_length, WS_BOOL file_end, WS_BOOL is_first_piece);	
WS_ERR update_get_progress(WS_U32 *percent);    //percent为100表示完成

WS_U32 update_get_percent();

WS_ERR update_start_packet(const WS_CHAR *packet_fname, WS_BOOL auto_del_packet);

/* add by zhangmq 20180527 start*/
//add zmq 设备升级[2018-05-05 11:37]
WS_ERR cfg_manage_query_cfg(const WS_CHAR *key1, const WS_CHAR *key2, const WS_CHAR *key3);  
WS_ERR cfg_manage_add_cfg(const WS_CHAR *key1, const WS_CHAR *key2, const WS_CHAR *key3, const WS_CHAR *str); //添加配置项
WS_ERR cfg_fac_manage_add_cfg(const WS_CHAR *key1, const WS_CHAR *key2, const WS_CHAR *key3, const WS_CHAR *str); 
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
}//namespace ws_update_name {
}//extern "C" {
#endif

#endif  //_WS_UPDATE_API_H_


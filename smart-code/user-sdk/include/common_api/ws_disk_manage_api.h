#ifndef _WS_DISK_MANAGE_API_H_
#define _WS_DISK_MANAGE_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_disk_manage_def.h"

using ws_utility::WS_ERR;
using namespace ws_soft;

#ifdef __cplusplus
extern "C" {
namespace ws_diskm  
{
#endif

WS_ERR diskm_init();
WS_ERR diskm_get_usb_disk_num(WS_U32 *num);
WS_ERR diskm_get_usb_disk_info(WS_U32 disk_idx, ws_usb_disk_info *info);
WS_ERR diskm_get_usb_disk_exist(WS_U32 disk_idx);

WS_ERR diskm_get_hard_disk_num(WS_U32 *num);
WS_ERR diskm_get_hard_disk_info(const char*  serial_no, ws_hard_disk_info *info);
WS_ERR diskm_get_hard_disk_state(const char*  serial_no, ws_soft::ws_hard_disk_state *state);
WS_ERR diskm_get_slot_num(WS_U32 * slot_num);	

//为备份到cd寻找临时空间
WS_ERR diskm_find_space_to_store_file(WS_CHAR *store_dir, WS_S32 size, WS_U64 file_size, const WS_CHAR* tmp_dir_name);
WS_ERR diskm_unmount_disk();    //卸载所有分区，不再自动挂载，为关机做准备
WS_ERR diskm_unmount_disk_for_reboot();    //卸载所有分区，不再自动挂载，为重启做准备
WS_ERR diskm_format_hard_disk(const char*  serial_no , WS_U32 part_idx = 0);
WS_ERR diskm_cancel_format_hard_disk(const char*  serial_no);
WS_ERR diskm_get_fromat_progress(const char*  serial_no, int *percent);   
WS_ERR diskm_get_format_info(ws_soft::ws_disk_serial* serial, WS_S32* nNum);      

//获取下一个格式化任务信息
WS_ERR diskm_get_next_format_task(char *dev_node,size_t node_size, WS_CHAR *serial_no, WS_U32 serial_no_len, WS_U32 *part_idx ); 

//执行格式化任务
WS_ERR diskm_do_format_task(char *dev_node, WS_CHAR *serial_no, WS_U32 part_idx ); 

//获取当前格式化进度，用来对格式化进行超时检查
WS_ERR diskm_get_current_format_progress( int *percent);

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_REMOTE_AGENT_API_H_


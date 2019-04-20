#ifndef _WS_UPGRADE_API_H_
#define _WS_UPGRADE_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"

#include "ws_update_def.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

WS_ERR upgrade_init();

WS_ERR upgrade_scan_packet(ws_upgrade_packet *packet_array, size_t array_dim, WS_U32 *real_packet_num);
WS_ERR upgrade_start_packet(const WS_CHAR *packet_fname);
WS_ERR upgrade_get_progress(WS_U32 *percent);   //percent为100表示完成

WS_ERR upgrade_scan_cfg_file(ws_config_file *flle_array, size_t array_dim, WS_U32 *real_packet_num);
WS_ERR upgrade_import_cfg_file(const WS_CHAR *file_fname);
WS_ERR upgrade_export_cfg_file(WS_U32 usb_dev_idx, WS_U32 usb_part_idx);

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_REMOTE_AGENT_API_H_


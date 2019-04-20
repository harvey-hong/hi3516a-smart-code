#ifndef _WS_LOG_MANAGE_API_H_
#define _WS_LOG_MANAGE_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_common.h"

#include "ws_log_manage_def.h"

using ws_utility::WS_ERR;
using namespace ws_soft; 


#ifdef __cplusplus
extern "C" {
namespace ws_logm
{
#endif

WS_ERR logm_init();

WS_ERR logm_close_log_database();
WS_ERR logm_add_log_to_sqlite(ws_soft::ws_log_content_pro *log);
WS_ERR logm_change_log_by_abnormal(time_t time);
WS_ERR logm_change_log_endtime(time_t time, WS_U32 node_idx);

WS_ERR logm_update_log_by_changtime(time_t old_time, time_t new_time);

WS_ERR logm_query_log_hand(const ws_soft::ws_log_inquiry_ctl *inquiry_ctl, ws_log_table_hand *log_hand, WS_U32 *log_num);

WS_ERR logm_get_log_result(const ws_log_table_hand log_hand, WS_U32 *start_num, WS_U32 *total_num, ws_soft::ws_log_inquiry_result_pro *log_result);
WS_ERR logm_free_log_result(ws_log_table_hand *log_hand);

WS_ERR logm_query_log_ex(const ws_log_inquiry_ctl *inquiry_ctl, ws_utility::ws_language_type language, ws_net_log_inquiry_result *result);
WS_ERR logm_free_query_log_ex(ws_net_log_inquiry_result *result);

WS_ERR logm_register_log_content_trans_pro_func(ws_soft::log_content_trans_pro func);

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_REMOTE_AGENT_API_H_


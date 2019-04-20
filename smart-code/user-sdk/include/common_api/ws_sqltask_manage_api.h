#ifndef _WS_SQLTASK_MANAGE_API_H_
#define _WS_SQLTASK_MANAGE_API_H_

#include "ws_comm_sys.h"
#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_flist.h"

#include "ws_sqltask_manage_def.h"
#include "ws_log_manage_def.h"	

using ws_utility::WS_ERR;
using namespace ws_soft;
using namespace ws_utility;

#ifdef __cplusplus
extern "C" {
namespace ws_sqltaskm 
{
#endif

WS_ERR sqltaskm_init();
WS_BOOL sqltaskm_check_database_is_corrupt(const char *database_name);
WS_ERR sqltaskm_register_check_database_and_repair_func(repair_database func, void *usr_para);
WS_ERR sqltaskm_get_rec_table_struct(ws_sqlite_table **rec_table, unsigned int *table_num);
WS_ERR sqltaskm_get_snap_table_struct(ws_sqlite_table **snap_table, unsigned int *table_num);
WS_ERR sqltaskm_rec_open_database(const char *db_name, int magic);	
WS_ERR sqltaskm_rec_close_database();
WS_ERR sqltaskm_rec_attach_database(const char *db_name, const char *product_name, int magic);	
WS_ERR sqltaskm_rec_detach_database(const char *db_name);
WS_ERR sqltaskm_rec_get_time_range(const char *db_name, ws_time_struct *rec_start_time, ws_time_struct *rec_end_time, ws_time_struct *snap_start_time, ws_time_struct *snap_end_time);
WS_ERR sqltaskm_rec_get_time_range_ex(const char *part_name, ws_time_struct *rec_start_time, ws_time_struct *rec_end_time, ws_time_struct *snap_start_time, ws_time_struct *snap_end_time);
WS_ERR sqltaskm_add_rec_info(ws_sqltaskm_task_node *task_node);
WS_ERR sqltaskm_del_rec_info(ws_sqltaskm_task_node *task_node);
WS_ERR sqltaskm_change_rec_info(ws_sqltaskm_task_node *task_node);
WS_ERR sqltaskm_change_rec_info_sync(ws_sqltaskm_task_node *task_node);
WS_ERR sqltaskm_search_rec_table_by_day(WS_U32 nvr_ch, const ws_time_struct *time, ws_rec_file_inquiry_type file_type, ws_rec_table_hand *rec_hand, WS_U32 *result_num);
WS_ERR sqltaskm_search_rec_table_by_time(WS_U32 nvr_ch, const ws_time_struct *start_time,const ws_time_struct *stop_time, ws_rec_file_inquiry_type file_type, ws_date_node_t *legal_data_node, ws_rec_table_hand *rec_hand, WS_U32 *result_num);

WS_ERR sqltaskm_free_rec_result(ws_rec_table_hand *rec_hand);

WS_ERR sqltaskm_add_snap_info(ws_sqltaskm_task_node *task_node);
WS_ERR sqltaskm_del_snap_info(ws_sqltaskm_task_node *task_node);
WS_ERR sqltaskm_change_snap_info(ws_sqltaskm_task_node *task_node);

WS_ERR sqltaskm_search_snap_table_by_day(WS_U32 nvr_ch, const ws_time_struct *time, ws_snap_file_inquiry_type file_type, ws_snap_table_hand *snap_hand, WS_U32 *result_num);
WS_ERR sqltaskm_search_snap_table_by_time(WS_U32 nvr_ch, const ws_time_struct * start_time,	const ws_time_struct * stop_time, ws_snap_file_inquiry_type file_type, ws_date_node_t *legal_data_node, ws_snap_table_hand *snap_hand, WS_U32 *result_num);

WS_ERR sqltaskm_free_snap_result(ws_snap_table_hand *snap_hand);

WS_ERR sqltaskm_get_table_list_by_hand(WS_U32 hand, ws_sqlite_result_table **result_table, WS_U32 *table_num);

WS_ERR sqltaskm_search_rec_by_keyword(const char *db_name, const char *table_name, ws_keyword_struct *keyword_struct, int keyword_num, WS_U32 *rec_num, void *info_data, int limit_line = 0);
WS_ERR sqltaskm_search_file_by_rotate(WS_U32 nvr_ch, const ws_utility::ws_time_struct *time, WS_BOOL is_rec, void * result_data, int *result_num);	
WS_BOOL sqltaskm_search_have_rec(WS_U32 nvr_ch, const ws_time_struct *start_time,const ws_time_struct *stop_time, ws_date_node_t *legal_data_node);
WS_ERR sqltaskm_drop_specified_table(const char *table_name);
WS_ERR sqltaskm_log_open_database(const char *db_name);
WS_ERR sqltaskm_log_close_database();

WS_ERR sqltaskm_log_create_table(ws_sqlite_table_list *table_list, const char *db_name);
WS_ERR sqltaskm_get_log_table_struct(ws_sqlite_table **log_table, unsigned int *table_num);
WS_ERR sqltaskm_log_get_keyword_max_min(const char *database_name, const char *table_name, ws_sqlite_table * keyword_item_p, void * keyword_min, void * keyword_max);

WS_ERR sqltaskm_add_log_info(ws_sqltaskm_task_node *task_node);
WS_ERR sqltaskm_del_log_info(ws_sqltaskm_task_node *task_node);
WS_ERR sqltaskm_change_log_info(ws_sqltaskm_task_node *task_node);
WS_ERR sqltaskm_search_log_by_keyword(const char * db_name,const char * table_name,ws_keyword_struct * keyword_struct,int keyword_num,WS_U32 * rec_num,void * info_data, int limit_line = 0);

WS_ERR sqltaskm_search_log(const char * table_name, const time_t * start_time,const time_t * stop_time, ws_soft::ws_log_main_type log_type, ws_log_table_hand *log_hand, WS_U32 *log_num, const WS_U32 *ch_mask = NULL, WS_U32 mask_num = 0);	
WS_ERR sqltaskm_free_log_result(ws_log_table_hand *log_hand);
WS_ERR sqltaskm_get_log_table_list_by_hand(WS_U32 hand, ws_sqlite_result_table **result_table, WS_U32 *table_num);

#ifdef __cplusplus
}//namespace ws_sqltaskm {
}//extern "C" {
#endif

#endif //#ifndef _WS_SQLTASK_MANAGE_API_H_


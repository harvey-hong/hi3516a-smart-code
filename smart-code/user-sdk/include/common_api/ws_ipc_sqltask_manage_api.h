#ifndef _WS_IPC_SQLTASK_MANAGE_API_H_
#define _WS_IPC_SQLTASK_MANAGE_API_H_

#include "ws_comm_sys.h"
#include "ws_comm_type.h"
#include "ws_comm_errno.h"

#include "ws_sqltask_manage_def.h"
#include "ws_recfile_rw_def.h"

using ws_utility::WS_ERR;
using namespace ws_soft;
using namespace ws_utility;

#ifdef __cplusplus
extern "C" {
namespace ws_sqltaskm
{
#endif

/*在IPC 上没有文件管理模块，add by linhh 20170532 start*/
/*linhh 20170532 其实我是不赞同放在这个地方的，后续再分析*/
typedef struct
{
    char fname[128];
    ws_utility::ws_rec_file_trig_type trig_type;

    time_t start_time;
    time_t end_time;

    WS_U32 file_size;   //文件关闭的时候才同步这个信息

    int reserved[16];
} ws_rec_list_file_node;

typedef struct
{
    char fname[128];        //Modified by qqy, at 2017-03-30 16:00:11
    ws_utility::ws_snap_file_trig_type trig_type;

    time_t file_time;
    WS_U32 file_size;   

    WS_BOOL is_exist;        
    int reserved[15];
} ws_snap_list_file_node;
/*在IPC 上没有文件管理模块，add by linhh 20170532 end*/

WS_ERR sqltaskm_ipc_init();

WS_BOOL sqltaskm_ipc_check_database_is_corrupt(const char *database_name);

WS_ERR sqltaskm_ipc_register_check_database_and_repair_func(repair_database func, void *usr_para);

WS_ERR sqltaskm_ipc_get_rec_table_struct(ws_sqlite_table **rec_table, unsigned int *table_num);
WS_ERR sqltaskm_ipc_get_snap_table_struct(ws_sqlite_table **snap_table, unsigned int *table_num);


WS_ERR sqltaskm_ipc_rec_open_database(const char *db_name, int magic);	
WS_ERR sqltaskm_ipc_rec_close_database();
WS_ERR sqltaskm_ipc_rec_attach_database(const char *db_name, const char *product_name, int magic);	
WS_ERR sqltaskm_ipc_rec_detach_database(const char *db_name);
WS_ERR sqltaskm_ipc_rec_get_time_range(const char *db_name, ws_time_struct *rec_start_time, ws_time_struct *rec_end_time, ws_time_struct *snap_start_time, ws_time_struct *snap_end_time);

WS_ERR sqltaskm_ipc_add_rec_info(const char *table_name, const char *database_name, ws_rec_list_file_node *node, int node_num);
WS_ERR sqltaskm_ipc_del_rec_info(const char *table_name, const char *database_name, const char *file_name);
WS_ERR sqltaskm_ipc_change_rec_info(const char *table_name, const char *database_name, const char *file_name,const ws_rec_file_trig_type *trig_type, const time_t *start_time, const time_t *end_time, const size_t *file_size);

WS_ERR sqltaskm_ipc_change_rec_info_sync(ws_sqltaskm_task_node *task_node);

WS_ERR sqltaskm_ipc_search_rec_info_by_day(WS_U32 nvr_ch, ws_time_struct *time, ws_rec_file_inquiry_type file_type, ws_rec_file_inquiry_result *result);
WS_ERR sqltaskm_ipc_search_rec_info_by_time(WS_U32 nvr_ch, const ws_time_struct *start_time,const ws_time_struct *stop_time, ws_rec_file_inquiry_type file_type, ws_rec_file_inquiry_result *result);
WS_ERR sqltaskm_ipc_search_rec_table_by_day(WS_U32 nvr_ch, const ws_time_struct *time, ws_rec_file_inquiry_type file_type, ws_rec_table_hand *rec_hand, WS_U32 *result_num);
WS_ERR sqltaskm_ipc_search_rec_table_by_time(WS_U32 nvr_ch, const ws_time_struct *start_time,const ws_time_struct *stop_time, ws_rec_file_inquiry_type file_type, ws_date_node_t *legal_data_node, ws_rec_table_hand *rec_hand, WS_U32 *result_num);

WS_ERR sqltaskm_ipc_free_rec_result(ws_rec_table_hand *rec_hand);

WS_ERR sqltaskm_ipc_add_snap_info(const char *table_name, const char *database_name, ws_snap_list_file_node *node, int node_num);
WS_ERR sqltaskm_ipc_del_snap_info(const char *table_name, const char *database_name, const char *file_name);
WS_ERR sqltaskm_ipc_change_snap_info(const char *table_name, const char *database_name, const char *file_name,const ws_snap_file_trig_type *trig_type, const time_t *start_time, const size_t *file_size);


WS_ERR sqltaskm_ipc_search_snap_info_by_day(WS_U32 nvr_ch, const ws_time_struct *time, ws_snap_file_inquiry_type file_type, ws_snap_file_inquiry_result *result);
WS_ERR sqltaskm_ipc_search_snap_info_by_time(WS_U32 nvr_ch, const ws_time_struct * start_time,	const ws_time_struct * stop_time, ws_snap_file_inquiry_type file_type, ws_snap_file_inquiry_result *result);
WS_ERR sqltaskm_ipc_search_snap_table_by_day(WS_U32 nvr_ch, const ws_time_struct *time, ws_snap_file_inquiry_type file_type, ws_snap_table_hand *snap_hand, WS_U32 *result_num);
WS_ERR sqltaskm_ipc_search_snap_table_by_time(WS_U32 nvr_ch, const ws_time_struct * start_time,	const ws_time_struct * stop_time, ws_snap_file_inquiry_type file_type, ws_date_node_t *legal_data_node, ws_snap_table_hand *snap_hand, WS_U32 *result_num);

WS_ERR sqltaskm_ipc_free_snap_result(ws_snap_table_hand *snap_hand);

WS_ERR sqltaskm_ipc_get_table_list_by_hand(WS_U32 hand, ws_sqlite_result_table **result_table, WS_U32 *table_num);

WS_ERR sqltaskm_ipc_search_rec_by_keyword(const char *db_name, const char *table_name, ws_keyword_struct *keyword_struct, int keyword_num, WS_U32 *rec_num, void *info_data, int limit_line = 0);// add by ljx date 2015.10.16 
WS_ERR sqltaskm_ipc_search_file_by_rotate(WS_U32 nvr_ch, const ws_utility::ws_time_struct *time, WS_BOOL is_rec, void * result_data, int *result_num);	// add by ljx date 20151020
WS_BOOL sqltaskm_ipc_search_have_rec(WS_U32 nvr_ch, const ws_time_struct *start_time,const ws_time_struct *stop_time, ws_date_node_t *legal_data_node);
WS_ERR sqltaskm_ipc_drop_specified_table(const char *table_name);


#ifdef __cplusplus
}
}
#endif

#endif //#ifndef _WS_IPC_SQLTASK_MANAGE_API_H_


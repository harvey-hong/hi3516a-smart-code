#ifndef _WS_SQLITE_API_H_
#define _WS_SQLITE_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_sqlite_def.h"
#include "ws_comm_sys.h"


using namespace ws_soft; 
using ws_utility::WS_ERR;
using ws_utility::ws_time_struct;
#ifdef __cplusplus
extern "C" {

namespace ws_sqlite     
{
#endif

    WS_ERR sqlite_get_time_range_for_disk(const char *part_name,ws_time_struct *rec_start_time, ws_time_struct *rec_end_time, ws_time_struct *snap_start_time, ws_time_struct *snap_end_time);
    WS_ERR sqlite_malloc_file_parser(WS_SQLITE_PARSER_ID *parser_id);
    WS_ERR sqlite_free_file_parser(WS_SQLITE_PARSER_ID parser_id);
    WS_ERR sqlite_open(const char *fname, int magic, WS_SQLITE_PARSER_ID parser_id);	
    WS_ERR sqlite_close(WS_SQLITE_PARSER_ID parser_id);

    WS_ERR sqlite_attach(const char *fname, const char *product_name, int magic, WS_SQLITE_PARSER_ID parser_id);
    WS_ERR sqlite_detach(const char *fname, WS_SQLITE_PARSER_ID parser_id);
    WS_ERR sqlite_create_table(ws_sqlite_table_list *table_list, const char *database_name, WS_SQLITE_PARSER_ID parser_id);

    // support add multiple records to one database
    WS_ERR sqlite_add_node(WS_SQLITE_PARSER_ID parser_id, const char *table_name, const ws_search_result *add_info, unsigned int info_num, unsigned int info_column, ws_sqlite_table *table_info, const char *database_name);
    WS_ERR sqlite_delete_node(WS_SQLITE_PARSER_ID parser_id, const char *table_name, const ws_sqlite_table *table, const void *keyword, WS_U32 keyword_num, const char *database_name, WS_BOOL need_del_empty_table = WS_TRUE);
    WS_ERR sqlite_change_node(WS_SQLITE_PARSER_ID parser_id, const char *table_name, const ws_sqlite_table *change_item, const void *change_info, int item_cnt, const ws_sqlite_table *item, const void *keyword, const char *database_name);

    WS_ERR sqlite_search_table_by_range(WS_SQLITE_PARSER_ID parser_id, const char *table_name, ws_sqlite_result_table *result_table, const ws_search_cond_group *cond_group,int cond_group_num, WS_U32 *num, const ws_sqlite_table * main_item);
    WS_ERR sqlite_search_table_all(WS_SQLITE_PARSER_ID parser_id, const char *table_name, ws_sqlite_result_table *result_table, WS_U32 * num, const ws_sqlite_table * main_item);
    WS_ERR sqlite_search_table_by_keyword(WS_SQLITE_PARSER_ID parser_id, const char *table_name, ws_sqlite_result_table *result_table, const ws_sqlite_table *table, const void *keyword, WS_U32 * num, const ws_sqlite_table * main_item);

    WS_ERR sqlite_search_by_keyword(WS_SQLITE_PARSER_ID parser_id, const char *db_name, ws_sqlite_table_list * table_info, ws_keyword_struct *keyword_struct, int keyword_num, WS_U32 *rec_num, void *info_data, const ws_sqlite_table * main_item, int limit_line);
    WS_ERR sqlite_search_by_unlock(WS_SQLITE_PARSER_ID parser_id, ws_sqlite_table_list *table_info, ws_keyword_struct *keyword_struct, int keyword_num, const char *keyword, int *result_num, void *result_data, const ws_sqlite_table * main_item);	
    WS_ERR sqlite_get_time_range(WS_SQLITE_PARSER_ID parser_id, const char *database_name, ws_time_struct *rec_start_time, ws_time_struct *rec_end_time, ws_time_struct *snap_start_time, ws_time_struct *snap_end_time);
    WS_ERR sqlite_free_search_table(WS_SQLITE_PARSER_ID parser_id, void * hand_t);

    WS_ERR sqlite_get_keyword_max_min(WS_SQLITE_PARSER_ID parser_id, const char *database_name, const char *table_name, ws_sqlite_table * keyword_item_p, void * keyword_min, void * keyword_max);
    WS_BOOL sqlite_check_database_is_corrupt(WS_SQLITE_PARSER_ID parser_id, const char *database_name);
    WS_BOOL sqlite_search_table_have_data(WS_SQLITE_PARSER_ID parser_id, const char *table_name, ws_keyword_struct *keyword_struct_start, ws_keyword_struct *keyword_struct_stop);
    WS_ERR sqlite_drop_specified_table(WS_SQLITE_PARSER_ID parser_id, const char *table_name);

#ifdef __cplusplus
}
}//extern "C" {
#endif

#endif  //_WS_SQLITE_API_H_

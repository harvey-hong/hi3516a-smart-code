#ifndef _WS_SQLTASK_MANAGE_DEF_H_
#define _WS_SQLTASK_MANAGE_DEF_H_

#include "ws_sqlite_def.h"
#include "ws_model_def.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef struct ws_path_node_t
{
    char path[64];
    ws_path_node_t *pre;
    ws_path_node_t *next;
} ws_path_node_t;

typedef struct ws_date_node_t
{
    char            date[sizeof("20130603")];
    ws_path_node_t  *path_node;
    ws_date_node_t  *pre;
    ws_date_node_t  *next;
} ws_date_node_t;

typedef enum {
	WS_SQLITE_FILE_REC_OPS = 0,
	WS_SQLITE_FILE_SNAP_OPS,
	WS_SQLITE_FILE_LOG_OPS,

	WS_SQLITE_FILE_TOTAL_OPS,
}ws_sqltaskm_file_type;

typedef enum {
	WS_DATABASE_UNKNOW = 0,
	WS_DATABASE_ADD,
	WS_DATABASE_DELETE,
	WS_DATABASE_CHANGE,
	WS_DATABASE_SEARCH,
}ws_sqltaskm_ops_type;


typedef struct {
	WS_U32 table_info_column;		// ����Ҫ�����ļ�¼��Ϣ������
	ws_sqlite_table *table_info;		// ��table_info_column��
	WS_U32 record_num;				// �ж�������¼�����������Ӳ�������ΪN���������һ�����һ��Ϊ1�������Ϊ1��ʾ������;
	void *info_data;					// �� table_info_column * record_num��
	char table_name[TNAME_SIZE];		// ����
	char database_name[FNAME_SIZE];	// ���ݿ����·����
	ws_sqltaskm_file_type file_type;// �ļ�����
	ws_sqltaskm_ops_type ops_type;	// ��������
}ws_sqltaskm_task_node;	

typedef struct ws_sqltaskm_task_node_list
{
	ws_sqltaskm_task_node task_node;
       char                                 *data_name_p;       
	ws_sqltaskm_task_node_list *pre;
	ws_sqltaskm_task_node_list *next;
}ws_sqltaskm_task_node_list;

#ifdef __cplusplus
}
}//extern "C" {
#endif



#endif //#ifndef _WS_SQLTASK_MANAGE_DEF_H_


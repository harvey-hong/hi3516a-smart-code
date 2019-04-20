#ifndef _WS_SQLITE_DEF_H_
#define _WS_SQLITE_DEF_H_

#include <stdio.h>
#include "ws_comm_sys.h"
#include "ws_comm_type.h"
#include "ws_comm_errno.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

#define FNAME_SIZE					64
#define TNAME_SIZE					64
#define SQLITE_BLOB_LENGTH 			16
#define SQLITE_ITEM_SIZE 			16		
#define WS_DB_MAX_SEARCH_NUM	 	5000	
#define WS_SQLITE_TRY_CNT			3

typedef enum
{
    WS_INT_T = 0,
    WS_CHAR_T,
    WS_BLOB_T,
}ws_data_type_t;

typedef struct{
	ws_data_type_t data_type; /*ʵ������ö�ٱ�ʾ ���� �ַ��� 2������*/
	WS_BOOL is_main;/*�Ƿ�Ϊ�ؼ���Ŀ һ�ݱ���ֻ������һ���ؼ��� �ҵ�һ���ؼ���󲻻�����ж�֮��ĸ�����һ���ؼ��û����Ĭ�ϵ�һ��Ϊ�ؼ���*/
	const char *data_name; /*��������*/
	size_t data_size;/*�����С int�͸ò�����Ч*/
}ws_sqlite_table;

typedef struct
{	
	ws_sqlite_table *table; /*�ṹ�������׵�ַָ��*/
	int table_num; /*�ṹ������ά��*/
	const char *table_name;  /*����*/
}ws_sqlite_table_list;

typedef struct {
    ws_sqlite_table *keyword_item_p;
    void * keyword_p;
}ws_keyword_struct;

typedef struct
{
    void *data; /*����ָ�� ���趨�ò��ҵı��󣬲��Һ���֪����������ʲô���ͣ��������߱���ҲӦ��֪����������*/
    size_t mem_size;/*���ڴ��С������2�������ݶ��ԣ��ô�СӦ��Ϊ��Ҫ��ȡ�����ݳ���*/
}ws_search_info;

typedef struct{
    ws_search_info *info;
    int num; /*���ݸ��������ֵ��ѯ��Ӧ��֪���Ƕ��ٸ�����������У��*/
}ws_search_result;

typedef struct
{
    ws_sqlite_table *s_item;
    ws_sqlite_table *e_item;
    int *start;
    int *end;
	/*linhh 20170532 IPC��Ŀǰû��type����*/
    int *type;
}ws_search_cond;

typedef struct
{
    ws_search_cond *cond;
    int cond_num;
}ws_search_cond_group;

typedef struct ws_search_result_node
{
    ws_search_result *result;
    ws_search_result_node *pre;
    ws_search_result_node *next;
}ws_search_result_node;

typedef struct ws_sqlite_attach_name
{
    char attach_name[FNAME_SIZE];                                   // database pathname
    char alias_name[FNAME_SIZE];                                     // database pathname and disk product name
    int attach_magic;	
}ws_sqlite_attach_name;

typedef struct
{
    char **table; //����ı�ʵ����һ��һά���飬���ڴ沼���ǣ��ֶ����ƣ������ǽ�������ÿ���ֶε�ֵ����
    int row;	//�����������������ͷ�У�
    int column;//�������
}ws_sqlite_result_table;

typedef struct ws_sqlite_result_table_list
{
    ws_sqlite_result_table *result_table;
    WS_U32 table_num;
    ws_sqlite_result_table_list *pre;
    ws_sqlite_result_table_list *next;
}ws_sqlite_result_table_list;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif //_WS_SQLITE_DEF_H_

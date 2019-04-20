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
	ws_data_type_t data_type; /*实际中用枚举表示 整型 字符型 2进制型*/
	WS_BOOL is_main;/*是否为关键项目 一份表单中只允许有一个关键项 找到一个关键项后不会继续判断之后的该项，如果一个关键项都没有则默认第一个为关键项*/
	const char *data_name; /*该项名字*/
	size_t data_size;/*该项大小 int型该参数无效*/
}ws_sqlite_table;

typedef struct
{	
	ws_sqlite_table *table; /*结构体数组首地址指针*/
	int table_num; /*结构体数组维数*/
	const char *table_name;  /*表名*/
}ws_sqlite_table_list;

typedef struct {
    ws_sqlite_table *keyword_item_p;
    void * keyword_p;
}ws_keyword_struct;

typedef struct
{
    void *data; /*数据指针 ，设定好查找的表单后，查找函数知道各参数是什么类型，而查找者本身也应该知道数据类型*/
    size_t mem_size;/*该内存大小，对于2进制数据而言，该大小应该为想要读取的数据长度*/
}ws_search_info;

typedef struct{
    ws_search_info *info;
    int num; /*数据个数，这个值查询者应该知道是多少个，可以用于校验*/
}ws_search_result;

typedef struct
{
    ws_sqlite_table *s_item;
    ws_sqlite_table *e_item;
    int *start;
    int *end;
	/*linhh 20170532 IPC上目前没有type定义*/
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
    char **table; //结果的表（实际是一个一维数组，它内存布局是：字段名称，后面是紧接着是每个字段的值。）
    int row;	//表的行数（不包括表头行）
    int column;//表的列数
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

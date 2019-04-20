#ifndef _WS_COMM_FLIST_H_
#define _WS_COMM_FLIST_H_

#include "ws_comm_type.h"
#include "ws_comm_sys.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

//ws_rec_file_trig_type详细描述了每种录像文件触发的类型，但是界面(控制)层可能因为不同的需求，会有不同的认知方式，
//例如，家用设备把MD和AI统一称作报警录像，而专业设备可能只把AI叫做报警录像
//这里封装一个专门针对界面(控制)层的解释枚举，不同的规格修改这个宏，重新编译就可以了
//如果添加了新的定义，需要修改add_rec_file_inquiry_result中的类型转换接口
typedef enum
{
    WS_REC_FILE_INQUIRY_UNKNOW,
    WS_REC_FILE_INQUIRY_COMM = ws_utility::WS_REC_FILE_TRIG_BY_TIMER | ws_utility::WS_REC_FILE_TRIG_BY_MANUAL,
    WS_REC_FILE_INQUIRY_ALARM = ws_utility::WS_REC_FILE_TRIG_BY_MD | ws_utility::WS_REC_FILE_TRIG_BY_AI, //查询报警录像

    /*TUTK模块中定义相关枚举*/
    WS_REC_FILE_INQUIRY_LIMIT_LINE = 0x0F0F0F0F,		// 查询前多少条记录，目前轮询时需要    
    WS_REC_FILE_INQUIRY_ALL = 0xFFFFFFFF,
} ws_rec_file_inquiry_type;

typedef enum
{
    WS_SNAP_FILE_INQUIRY_UNKNOW,
    WS_SNAP_FILE_INQUIRY_COMM = ws_utility::WS_SNAP_FILE_TRIG_BY_TIMER | ws_utility::WS_SNAP_FILE_TRIG_BY_MANUAL,
    WS_SNAP_FILE_INQUIRY_ALARM = ws_utility::WS_SNAP_FILE_TRIG_BY_MD | ws_utility::WS_SNAP_FILE_TRIG_BY_AI, //查询报警录像
    WS_SNAP_FILE_INQUIRY_LIMIT_LINE = 0x0F0F0F0F,		// 查询前多少条记录，目前轮询时需要
    WS_SNAP_FILE_INQUIRY_ALL = 0xFFFFFFFF,
} ws_snap_file_inquiry_type;

// change by linhh 20160718 
typedef union
{
	ws_soft::ws_snap_file_inquiry_type snap_file_type;
	ws_soft::ws_rec_file_inquiry_type rec_file_type;
}file_inquiry_type;

typedef struct ws_rec_file_inquiry_node
{
    time_t start_time;  //文件起始时间
    time_t end_time;    //文件结束时间
    WS_U32 file_size;   //文件大小
    WS_CHAR file_name[ws_utility::WS_MAX_FILE_NAME_LEN];    
    ws_rec_file_inquiry_type file_type; //文件类型

    WS_BOOL operation_tag;  //是否参与操作(回放或者备份)，默认全部参与操作
    WS_BOOL is_warning;		// 文件是否有问题(比如不存在等)，或者是正在录制的文件 
	
    ws_rec_file_inquiry_node *pre;
    ws_rec_file_inquiry_node *next;
} ws_rec_file_inquiry_node;

typedef struct
{
    WS_U32 nvr_ch;
    ws_rec_file_inquiry_node *head_node;
} ws_rec_file_inquiry_result;

typedef struct ws_snap_file_inquiry_node
{
    time_t file_time;   //文件时间
    WS_U32 file_size;   //文件大小
    WS_CHAR file_name[ws_utility::WS_MAX_FILE_NAME_LEN];    //据对路径文件名
    ws_snap_file_inquiry_type file_type;    //文件类型

    WS_BOOL operation_tag;  //是否参与操作(回放或者备份)，默认全部参与操作
	WS_BOOL is_warning; 	// 文件是否有问题(比如不存在等)	// add by ljx date 20151201

    ws_snap_file_inquiry_node *pre;
    ws_snap_file_inquiry_node *next;
} ws_snap_file_inquiry_node;

typedef struct
{
    WS_U32 nvr_ch;
    ws_snap_file_inquiry_node *head_node;
} ws_snap_file_inquiry_result;

typedef struct ws_pb_rec_file
{
    time_t start_time;  
    time_t end_time;   
    ws_rec_file_inquiry_type file_type; 
    ws_pb_rec_file *pre;
   ws_pb_rec_file *next;
} ws_pb_rec_file;

typedef struct
{
    WS_U32 nvr_ch;
    ws_pb_rec_file *head_node;
} ws_pb_rec_file_inquiry_result;

typedef struct ws_pb_snap_file
{
    time_t file_time;   
    ws_snap_file_inquiry_type file_type;    
    ws_pb_snap_file * pre;
    ws_pb_snap_file* next;
} ws_pb_snap_file;

typedef struct
{
    WS_U32 nvr_ch;
    ws_pb_snap_file *head_node;
} ws_pb_snap_file_inquiry_result;
// add by longzhou 20150730 end;


typedef struct
{
	WS_U32 is_empty;
	WS_U8 colo_info[1440*60];   
}ch_colo_info;

typedef struct ch_sel_ops_node
{
	WS_U8 ch_idx;
	//WS_U8 colo_idx;
	ch_sel_ops_node *next;
	ch_sel_ops_node *pre;
}ch_select_ops_node;

typedef union file_result_handle
{
	ws_rec_table_hand rec_handle;
	ws_snap_table_hand snap_handle;
}file_result_handle;

typedef enum
{
    WS_PARSER_RD_UNKNOW,
    WS_PARSER_RD_ONLY_I,
    WS_PARSER_RD_ONLY_I_2,  //跳两个I帧，在32倍速的时候用
    WS_PARSER_RD_ONLY_I_BACK,   //退放的读
    WS_PARSER_RD_ONLY_I_BACK_2, //退放的读，跳两个I帧，在32倍速的时候用
    WS_PARSER_RD_ONLY_VIDEO,
    WS_PARSER_RD_ONLY_AUDIO,
    WS_PARSER_RD_ALL_DATA,
} ws_parser_read_mode;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //#ifndef _WS_COMMON_H_


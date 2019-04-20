#ifndef _WS_UTILITY_DEF_H_
#define _WS_UTILITY_DEF_H_

#include "ws_comm_type.h" //add by yxl 2014.07.11 for push_event
#include "ws_comm_sys.h" //add by yxl 2014.07.15 for push_event
#include <sys/time.h>
#include "tinyxml.h"

typedef TiXmlElement WS_Xml_Node;

#ifdef __cplusplus
extern "C" {
namespace ws_utility//changed by mjq 2014.11.26

{
#endif

class ws_timer_client;

//线程函数
typedef WS_VOID *(*ws_thread_func)(void *);

//定时器回调函数
typedef WS_VOID(*ws_timer_func)();


//对系统而言，线程优先级分两种
//普通线程: 通用优先级的线程
//实时线程: 极高高优先级线程,可以阻塞中断，慎重
typedef enum
{
    WS_THR_MODE_UNKNOW,
    WS_COMM_THREAD,         //普通线程
    WS_REAL_TIME_THREAD,    //实时线程
} ws_thread_work_type;

typedef enum
{
    WS_THR_PRI_LV0 = 0,
    WS_THR_PRI_LV1 = 5,
    WS_THR_PRI_LV2 = 10,
    WS_THR_PRI_LV3 = 15,
    WS_THR_PRI_LV4 = 20,
    WS_THR_PRI_LV5 = 25,
    WS_THR_PRI_LV6 = 30,
    WS_THR_PRI_LV7 = 35,
    WS_THR_PRI_LV8 = 40,
    WS_THR_PRI_LV9 = 50,
    WS_THR_PRI_LV99 = 99,   //hongzhigang added for 16CH DVR test

    WS_THR_PRI_DEFAULT = WS_THR_PRI_LV0,        //默认优先级
} ws_thread_priority;

//定义文件的操作方式
typedef enum
{
    WS_FILE_OPEN_UNKNOW,

    WS_FILE_OPEN_RD,    //只读，不创建文件，如果成功，文件指针位于文件头
    WS_FILE_OPEN_RW,    //读写，不创建文件，如果成功，文件指针位于文件头

    WS_FILE_OPEN_RW_APPEND, //读写，如果不存在，创建文件，如果存在，继续添加类容，只能添加到文件末端，写入操作时会自动seek到文件尾
    WS_FILE_OPEN_RW_TRUNC,  //读写，如果不存在，创建文件，如果存在，覆盖原来的文件，如果成功，文件指针位于文件尾
	WS_FILE_OPEN_RW_DIRECT, //写，直接往硬盘中写，不需要内核缓冲 //add by mjq 20150731
} ws_file_open_mode;

typedef enum
{
    WS_FILE_CNT_OFSET_UNKNOW,

    WS_FILE_CNT_OFSET_HEAD, //按照文件头来计算偏移
    WS_FILE_CNT_OFSET_TAIL, //按照文件尾来计算偏移
    WS_FILE_CNT_OFSET_CUR,  //按照当前文件指针位置来计算偏移
} ws_file_cnt_ofset_mode;

typedef enum
{
    WS_COLOE_ARGB_1555,
    WS_COLOE_ARGB_8888,
} ws_rgb_color_mode;


typedef struct
{
	int sort_num;		//需要排序的数据
	int data;		//用于保留的字段，比如原编号或者需要排序的指针等，该结构体中这两个值都会成对变化，即对应关系永远是一样的
}ws_quick_sort;

#ifdef __cplusplus
}//namespace ws_utility //changed by mjq 2014.11.26 {
}//extern "C" {
#endif


#endif //#ifndef _WS_COMM_UTILITY_H_


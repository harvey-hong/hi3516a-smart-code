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

//�̺߳���
typedef WS_VOID *(*ws_thread_func)(void *);

//��ʱ���ص�����
typedef WS_VOID(*ws_timer_func)();


//��ϵͳ���ԣ��߳����ȼ�������
//��ͨ�߳�: ͨ�����ȼ����߳�
//ʵʱ�߳�: ���߸����ȼ��߳�,���������жϣ�����
typedef enum
{
    WS_THR_MODE_UNKNOW,
    WS_COMM_THREAD,         //��ͨ�߳�
    WS_REAL_TIME_THREAD,    //ʵʱ�߳�
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

    WS_THR_PRI_DEFAULT = WS_THR_PRI_LV0,        //Ĭ�����ȼ�
} ws_thread_priority;

//�����ļ��Ĳ�����ʽ
typedef enum
{
    WS_FILE_OPEN_UNKNOW,

    WS_FILE_OPEN_RD,    //ֻ�����������ļ�������ɹ����ļ�ָ��λ���ļ�ͷ
    WS_FILE_OPEN_RW,    //��д���������ļ�������ɹ����ļ�ָ��λ���ļ�ͷ

    WS_FILE_OPEN_RW_APPEND, //��д����������ڣ������ļ���������ڣ�����������ݣ�ֻ����ӵ��ļ�ĩ�ˣ�д�����ʱ���Զ�seek���ļ�β
    WS_FILE_OPEN_RW_TRUNC,  //��д����������ڣ������ļ���������ڣ�����ԭ�����ļ�������ɹ����ļ�ָ��λ���ļ�β
	WS_FILE_OPEN_RW_DIRECT, //д��ֱ����Ӳ����д������Ҫ�ں˻��� //add by mjq 20150731
} ws_file_open_mode;

typedef enum
{
    WS_FILE_CNT_OFSET_UNKNOW,

    WS_FILE_CNT_OFSET_HEAD, //�����ļ�ͷ������ƫ��
    WS_FILE_CNT_OFSET_TAIL, //�����ļ�β������ƫ��
    WS_FILE_CNT_OFSET_CUR,  //���յ�ǰ�ļ�ָ��λ��������ƫ��
} ws_file_cnt_ofset_mode;

typedef enum
{
    WS_COLOE_ARGB_1555,
    WS_COLOE_ARGB_8888,
} ws_rgb_color_mode;


typedef struct
{
	int sort_num;		//��Ҫ���������
	int data;		//���ڱ������ֶΣ�����ԭ��Ż�����Ҫ�����ָ��ȣ��ýṹ����������ֵ����ɶԱ仯������Ӧ��ϵ��Զ��һ����
}ws_quick_sort;

#ifdef __cplusplus
}//namespace ws_utility //changed by mjq 2014.11.26 {
}//extern "C" {
#endif


#endif //#ifndef _WS_COMM_UTILITY_H_


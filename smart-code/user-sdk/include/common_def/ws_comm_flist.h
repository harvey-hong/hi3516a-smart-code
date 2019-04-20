#ifndef _WS_COMM_FLIST_H_
#define _WS_COMM_FLIST_H_

#include "ws_comm_type.h"
#include "ws_comm_sys.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

//ws_rec_file_trig_type��ϸ������ÿ��¼���ļ����������ͣ����ǽ���(����)�������Ϊ��ͬ�����󣬻��в�ͬ����֪��ʽ��
//���磬�����豸��MD��AIͳһ��������¼�񣬶�רҵ�豸����ֻ��AI��������¼��
//�����װһ��ר����Խ���(����)��Ľ���ö�٣���ͬ�Ĺ���޸�����꣬���±���Ϳ�����
//���������µĶ��壬��Ҫ�޸�add_rec_file_inquiry_result�е�����ת���ӿ�
typedef enum
{
    WS_REC_FILE_INQUIRY_UNKNOW,
    WS_REC_FILE_INQUIRY_COMM = ws_utility::WS_REC_FILE_TRIG_BY_TIMER | ws_utility::WS_REC_FILE_TRIG_BY_MANUAL,
    WS_REC_FILE_INQUIRY_ALARM = ws_utility::WS_REC_FILE_TRIG_BY_MD | ws_utility::WS_REC_FILE_TRIG_BY_AI, //��ѯ����¼��

    /*TUTKģ���ж������ö��*/
    WS_REC_FILE_INQUIRY_LIMIT_LINE = 0x0F0F0F0F,		// ��ѯǰ��������¼��Ŀǰ��ѯʱ��Ҫ    
    WS_REC_FILE_INQUIRY_ALL = 0xFFFFFFFF,
} ws_rec_file_inquiry_type;

typedef enum
{
    WS_SNAP_FILE_INQUIRY_UNKNOW,
    WS_SNAP_FILE_INQUIRY_COMM = ws_utility::WS_SNAP_FILE_TRIG_BY_TIMER | ws_utility::WS_SNAP_FILE_TRIG_BY_MANUAL,
    WS_SNAP_FILE_INQUIRY_ALARM = ws_utility::WS_SNAP_FILE_TRIG_BY_MD | ws_utility::WS_SNAP_FILE_TRIG_BY_AI, //��ѯ����¼��
    WS_SNAP_FILE_INQUIRY_LIMIT_LINE = 0x0F0F0F0F,		// ��ѯǰ��������¼��Ŀǰ��ѯʱ��Ҫ
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
    time_t start_time;  //�ļ���ʼʱ��
    time_t end_time;    //�ļ�����ʱ��
    WS_U32 file_size;   //�ļ���С
    WS_CHAR file_name[ws_utility::WS_MAX_FILE_NAME_LEN];    
    ws_rec_file_inquiry_type file_type; //�ļ�����

    WS_BOOL operation_tag;  //�Ƿ�������(�طŻ��߱���)��Ĭ��ȫ���������
    WS_BOOL is_warning;		// �ļ��Ƿ�������(���粻���ڵ�)������������¼�Ƶ��ļ� 
	
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
    time_t file_time;   //�ļ�ʱ��
    WS_U32 file_size;   //�ļ���С
    WS_CHAR file_name[ws_utility::WS_MAX_FILE_NAME_LEN];    //�ݶ�·���ļ���
    ws_snap_file_inquiry_type file_type;    //�ļ�����

    WS_BOOL operation_tag;  //�Ƿ�������(�طŻ��߱���)��Ĭ��ȫ���������
	WS_BOOL is_warning; 	// �ļ��Ƿ�������(���粻���ڵ�)	// add by ljx date 20151201

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
    WS_PARSER_RD_ONLY_I_2,  //������I֡����32���ٵ�ʱ����
    WS_PARSER_RD_ONLY_I_BACK,   //�˷ŵĶ�
    WS_PARSER_RD_ONLY_I_BACK_2, //�˷ŵĶ���������I֡����32���ٵ�ʱ����
    WS_PARSER_RD_ONLY_VIDEO,
    WS_PARSER_RD_ONLY_AUDIO,
    WS_PARSER_RD_ALL_DATA,
} ws_parser_read_mode;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //#ifndef _WS_COMMON_H_


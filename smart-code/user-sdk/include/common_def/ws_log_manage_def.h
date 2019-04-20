#ifndef _WS_LOG_MANAGE_H_
#define _WS_LOG_MANAGE_H_

#include "ws_comm_type.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

#define WS_LOG_DB_NAME			"/config/sys_log.db"
#define WS_LOG_DB_TABLE_NAME	      "sys_log_table"
#define WS_LOG_ROTATE_NUM		100
#define WS_LOG_MAX_NUM			5000 
#define MAX_LINE_NUM                        10 

typedef enum
{
    LOG_MAIN_UNKNOW = 0,
    LOG_MAIN_ALARM      = 0x01, //�澯
    LOG_MAIN_MD            = 0x02, //�ƶ����
    LOG_MAIN_OPERATION  = 0x04, //����
    LOG_MAIN_GENERAL    = 0x08, //��ͨ
    LOG_MAIN_EXCEPTION  = 0x80, //�쳣
    LOG_MAIN_ALL = 0xFFFFFFFF,
} ws_log_main_type;

typedef enum
{
    LOG_SUB_UNKNOW,

    //---------- ϵͳ -----------------
    LOG_SUB_LOCAL_USR_LOGIN = 0x1000,   //�����û���¼
    LOG_SUB_LOCAL_USR_LOGOUT,   //�����û��ǳ�

    LOG_SUB_RMT_USR_LOGIN,  //Զ���û���¼
    LOG_SUB_RMT_USR_LOGOUT, //Զ���û��ǳ�

    LOG_SUB_POWER_ON,   //����
    LOG_SUB_POWER_OFF,  //�ػ�
    LOG_SUB_REBOOT,     //����

    //---------- MD -----------------
    LOG_SUB_MD = 0x2000,        //�ƶ����
    //LOG_SUB_MD_DISAPPEAR, //(�ƶ������ʧȡ����ͨ������ʱ���ж�)

    //---------- AI -----------------
    LOG_SUB_AI = 0x3000,        //��������
    //LOG_SUB_AI_DISAPPEAR, //(���������ʧȡ����ͨ������ʱ���ж�)

    //---------- ���� -----------------
    LOG_SUB_MODIFY_TIME = 0x4000,   //�޸�ϵͳʱ��
    LOG_SUB_DST_ON,                 //������ʱ�� 
    LOG_SUB_DST_OFF,                //�ر���ʱ�� 
    LOG_SUB_MODIFY_ALARM_LINK,      //�޸ı�������	
    LOG_SUB_BACKUP_FILE,            //����¼������
    LOG_SUB_RESUME_DEFAULT,         //�ָ�Ĭ��
    LOG_SUB_RESUME_FACTORY,         //�ָ�����		
    LOG_SUB_RECMANUAL_ON,           //�����ֶ�¼�� 
    LOG_SUB_RECMANUAL_OFF,          //�ر��ֶ�¼�� 
    LOG_SUB_UPGRADE,                //����
    LOG_SUB_RESET_PASSWORD,         //���븴λ
    LOG_SUB_CLR_ALARM,				//��������

    LOG_SUB_DISKMODE,				//Ӳ�̿���ģʽ
    LOG_SUB_RECPLAN,				//¼��ƻ��޸�
	
    LOG_SUB_DISKFORMAT, 			//Ӳ�̸�ʽ��
    LOG_SUB_AI_TYPECHANGE,			//�޸ı�����������
    LOG_SUB_MD_AREACHANGE,			//ͨ���ƶ���������޸�
    LOG_SUB_MD_SENS,				//�ƶ�����������޸�

    LOG_SUB_RECMANUAL,			// ¼��ģʽ�޸ģ��Ƕ�Ӳ�̿���ģʽ�Ĳ��䣬��¼Դģʽ��Ŀ��ģʽ
    LOG_SUB_MODIFY_IO_LINK,		// ���������������������������������޸ļ�¼��־
    LOG_SUB_MOTION_LINK,			// �ƶ���ⱨ���������ƶ���ⱨ���������޸ļ�¼��־
    LOG_SUB_VIDEO_LOST_LINK,		// ��Ƶ��ʧ������������Ƶ��ʧ�����������޸ļ�¼��־
    LOG_SUB_VIDEO_COVER_LINK,	// ��Ƶ�ڸǱ�����������Ƶ�ڸǱ����������޸ļ�¼��־
    LOG_SUB_DELETE_DATA,			// ����ɾ����Ӳ����������ɾ����¼��־


    //---------- �쳣 -----------------
    LOG_SUB_ABNORMAL_SHUTDOWN = 0x5000, //�쳣�ػ�

    LOG_SUB_ABNORMAL_NO_DISK,				//δ��Ӳ��
    LOG_SUB_ABNORMAL_DISK_ERROR,			//Ӳ�̷����쳣
    LOG_SUB_ABNORMAL_DISK_LOST,			//Ӳ�̶�ʧ
    LOG_SUB_ABNORMAL_NO_SPACE,			//Ӳ����
    LOG_SUB_ABNORMAL_NET_ERROR, 		//�����쳣
    LOG_SUB_ABNORMAL_IP_CONFLICT,
    LOG_SUB_VIDEO_LOSS = 0x6000,		// ��¼��Ƶ��ʧʱ�䣬�����߼�ͬ�ƶ�����߼�
    LOG_SUB_VIDEO_COVER,				// ��¼��Ƶ�ڸ�ʱ�䣬�����߼�ͬ�ƶ�����߼�
} ws_log_sub_type;

typedef struct
{
    time_t start_time;  //��־��ʼʱ��
    time_t stop_time;   //��־����ʱ��

    ws_log_main_type type;  //��ѯ����
    WS_U32 ch_mask[ws_utility::WS_NVR_MAX_MASK_NUM];	//change by khs 2017.4.14
} ws_log_inquiry_ctl;

typedef struct
{
    time_t time;    //��¼ʱ��
    time_t end_time; //�¼�����ʱ��(����Ҫ��¼����Ϊ-1)
    int ch_idx;     //ͨ��

    ws_log_main_type main_type;
    ws_log_sub_type sub_type;

    //�û���¼IP�������û�Ϊip_v4��ip_v6ȫ��Ϊ0
    WS_U32 ip_v4;
    WS_U32 ip_v6[4];

    WS_CHAR usr_name[32];

    WS_U32 node_idx;    //������ţ���־�ļ��ڲ�ʹ��
} ws_log_content;

typedef struct
{
    time_t time;        //��¼ʱ��
    time_t end_time; //�¼�����ʱ��(����Ҫ��¼����Ϊ-1)

    int ch_idx;     //ͨ��
    int ch_link_mask; // ����ͨ��mask		����������ch_link_mask_ex

    ws_log_main_type main_type;
    ws_log_sub_type sub_type;

    //�û���¼IP�������û�Ϊip_v4��ip_v6ȫ��Ϊ0
    WS_U32  ip_v4;
    WS_U32  ip_v6[4];

    WS_CHAR disk_name[48];	 // ��־�ļ��Ӿɰ汾���°汾�У�����������־�ļ��п���û��
    WS_CHAR usr_name[32];
    int 	ch_link_mask_ex[8];	 //��ǰ�汾��usr_name �ü�����һ�����ڱ���������Ŀ
    WS_U32 node_idx;                //������ţ���־�ļ��ڲ�ʹ��
}ws_log_content_pro;

typedef struct ws_logm_cache_list
{
	ws_log_content_pro log_node;
	WS_U32 log_idx;	// ����ģ������ͬ���õģ����ⷢ��ʱ����������־ͬ����������������
	ws_logm_cache_list *pre;
	ws_logm_cache_list *next;
}ws_logm_cache_list;

typedef struct
{
    WS_CHAR num[32];
    WS_CHAR time[32];
    WS_CHAR event[32];
    WS_CHAR user[32];
} ws_log_title;

typedef struct
{
    int log_num;                    //��־��Ŀ
    ws_log_content *log_content;    //��־����
} ws_log_inquiry_result;

typedef struct
{
    int log_num;                    //��־��Ŀ
    ws_log_content_pro *log_content;    //��־����
} ws_log_inquiry_result_pro;

typedef struct
{
    ws_soft::ws_log_inquiry_result log_result;
    WS_BOOL *ws_log_have_file;
} ws_log_rec_result;

typedef struct
{
	ws_soft::ws_log_inquiry_result_pro log_result;
	WS_BOOL page_valid[WS_LOG_MAX_NUM / MAX_LINE_NUM + 1];
	WS_BOOL log_have_recfile[WS_LOG_MAX_NUM / MAX_LINE_NUM + 1][MAX_LINE_NUM];
} ws_log_rec_result_pro;

//��ö�����ͷ����ʵ������֮�󴫵ݸ�����㣬������㴫�ݸ�IE�ͻ���ֱ����ʾ
typedef struct
{
    time_t time;    //��¼ʱ��
    WS_CHAR *content;
    WS_CHAR usr_name[32];
} ws_net_log_content;

typedef struct
{
    int         log_num;  
    ws_net_log_content *log_content;
} ws_net_log_inquiry_result;

typedef int (*log_content_trans)(const ws_log_content *src, ws_utility::ws_language_type language, char *content, size_t content_size); //
typedef int (*log_title_trans)(ws_utility::ws_language_type language, ws_log_title *title); //

typedef int (*log_content_trans_pro)(const ws_log_content_pro *src, ws_utility::ws_language_type language, char *content, size_t content_size);

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_LOG_MANAGE_H_


#ifndef _WS_THREAD_MANAGE_API_H_
#define _WS_THREAD_MANAGE_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_thread_manage_def.h"

using ws_utility::WS_ERR;
#ifdef __cplusplus

extern "C" {
namespace ws_thread_manage
{
#endif



typedef enum
{
	WORK_CREATE		= 0x0 ,				/* �´������� */
	WORK_EXEC		= 0x1 ,				/* ��������ִ���� */
	WORK_SUCCESS	= 0x2 ,				/* ����ִ�н������������񷵻�ֵΪ�ɹ�*/
	WORK_FAILED		= 0x4,				/* ����ִ�н������������񷵻�ֵΪʧ��*/
	WORK_UNKONW,						/* ��Ӧ�ó��ֵ�ö�� */
}ENUM_WORK_STATUS;

typedef struct worker
{
    thread_run_task	my_work;				/*�����壬�ȴ��ص��Ľӿں���*/	
    WS_VOID 		*arg;					/*�ص��������� */
    int				work_id;					/* ���ظ��ϲ�ģ�������ID*/

    ENUM_WORK_STATUS	work_status;			/* ��¼��ǰ�����״̬ */
    struct timeval 	exec_time;				/* ����ϣ���´�ִ��ʱ�� */

    /* ������Ҫ��ִ�д��� ��ֵӦΪ1-0xFFFFFFFF ����0xFFFFFFFF��ʾ������Զִ�� */
    WS_U32 			times; 					

    /* ������Ҫ���ִ��ʱ������ִ�м��ʱ�䣬��λΪ����*/
    WS_S32 			interval;     

    /* ����ÿһ������ϣ������Ӻ�����ִ�У�������ӵ���һ�α�ִ�еļ��ʱ�䣬��λΪ����*/
    WS_S32 			delay_time;						

    WS_U32			cur_time;					/* ��ǰ�Ѿ�ִ�д��� */


    /* ������ִ��ʧ��ʱ�Ƿ���Ҫ����ִ�� */
    WS_BOOL		fail_need_repeat;				

    /* ����ִ��ʧ�ܺ�����ִ�м��ʱ��:����*/
    WS_U32			fail_start_time;			

    WS_BOOL		usr_del_request;			/* �ϲ���������ɾ�� */
    WS_U32 			thread_id ;				/* �����ã���¼���ִ���̵߳�ID*/

    char                m_taskName[255];                /* ����ʹ�ã���������*/            
    struct worker 		*next;					/* ָ����һ�������ڵ��ָ�� */
} worker_node ;

struct task_para
{
	WS_U32 			times;				/* ִ�д��������������� */
	WS_S32 			interval;				/* ִ�м�������������� */
	WS_S32 			delay_time;			/* �ӳ�ʱ�䣬���������� */
	WS_BOOL		fail_need_repeat;		/* ʧ������������������*/
	WS_U32			fail_start_time;		/* �����ȴ�ʱ�䣬����������*/
};

WS_ERR  thread_manage_init();

WS_ERR  thread_manage_deinit();

WS_ERR  thread_manage_add_work(thread_run_task call_back, void *arg , struct task_para ws_task_para, int *work_id, const char* nameString);

WS_ERR  thread_manage_remove_work( int work_id);

WS_ERR  thread_manage_remove_work_need_del(int work_id);

void threadpool_excute_task(void* pParam);

void ws_time_thread();

WS_ERR thread_manage_change_time();



#ifdef __cplusplus
}	// namespace ws_thread_manage
}	// "C"
#endif

#endif  


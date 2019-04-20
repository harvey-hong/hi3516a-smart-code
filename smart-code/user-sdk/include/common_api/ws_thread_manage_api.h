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
	WORK_CREATE		= 0x0 ,				/* 新创建任务 */
	WORK_EXEC		= 0x1 ,				/* 任务正在执行中 */
	WORK_SUCCESS	= 0x2 ,				/* 任务执行结束，并且任务返回值为成功*/
	WORK_FAILED		= 0x4,				/* 任务执行结束，并且任务返回值为失败*/
	WORK_UNKONW,						/* 不应该出现的枚举 */
}ENUM_WORK_STATUS;

typedef struct worker
{
    thread_run_task	my_work;				/*任务体，既待回调的接口函数*/	
    WS_VOID 		*arg;					/*回调函数参数 */
    int				work_id;					/* 返回给上层模块的任务ID*/

    ENUM_WORK_STATUS	work_status;			/* 记录当前任务的状态 */
    struct timeval 	exec_time;				/* 任务希望下次执行时间 */

    /* 任务需要被执行次数 该值应为1-0xFFFFFFFF 其中0xFFFFFFFF表示期望永远执行 */
    WS_U32 			times; 					

    /* 任务需要多次执行时，任务执行间隔时间，单位为毫秒*/
    WS_S32 			interval;     

    /* 不是每一个任务都希望在添加后立即执行，任务添加到第一次被执行的间隔时间，单位为毫秒*/
    WS_S32 			delay_time;						

    WS_U32			cur_time;					/* 当前已经执行次数 */


    /* 当任务执行失败时是否需要重新执行 */
    WS_BOOL		fail_need_repeat;				

    /* 任务执行失败后重新执行间隔时间:毫秒*/
    WS_U32			fail_start_time;			

    WS_BOOL		usr_del_request;			/* 上层请求任务删除 */
    WS_U32 			thread_id ;				/* 调试用，记录最后执行线程的ID*/

    char                m_taskName[255];                /* 调试使用，任务名称*/            
    struct worker 		*next;					/* 指向下一个工作节点的指针 */
} worker_node ;

struct task_para
{
	WS_U32 			times;				/* 执行次数，见上文描述 */
	WS_S32 			interval;				/* 执行间隔，见上文描述 */
	WS_S32 			delay_time;			/* 延迟时间，见上文描述 */
	WS_BOOL		fail_need_repeat;		/* 失败重做，见上文描述*/
	WS_U32			fail_start_time;		/* 重做等待时间，见上文描述*/
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


#ifndef _WS_THREAD_MANAGE_DEF_H_
#define _WS_THREAD_MANAGE_DEF_H_

#include "ws_comm_type.h"

#ifdef __cplusplus
extern "C" {
namespace ws_thread_manage						//change by liuyao 20160408
{
#endif

typedef enum{
	WS_POOL_THR_PRI_LV0 = 9,
	WS_POOL_THR_PRI_LV1 = 8,
	WS_POOL_THR_PRI_LV2 = 7,
	WS_POOL_THR_PRI_LV3 = 6,
	WS_POOL_THR_PRI_LV4 = 5,
	WS_POOL_THR_PRI_LV5 = 4,
	WS_POOL_THR_PRI_LV6 = 3,
	WS_POOL_THR_PRI_LV7 = 2,
	WS_POOL_THR_PRI_LV8 = 1,
	WS_POOL_THR_PRI_LV9 = 0,
	WS_POOL_THR_PRI_MAX = 0,
	WS_POOL_THR_PRI_DEFAULT = WS_POOL_THR_PRI_LV0,
	
}ws_pool_thread_pri;				//线程优先级



typedef ws_utility::WS_ERR(*thread_run_task)(void *para);		// change by lmw 20160811 --



#ifdef __cplusplus
}//namespace ws_thread_manage {
}//extern "C" {
#endif

#endif  


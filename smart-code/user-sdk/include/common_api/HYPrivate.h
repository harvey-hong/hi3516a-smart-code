#ifndef HY_PRIVATE_H

#define HY_PRIVATE_H


#if defined( __cplusplus)
#define HYPRIVATE_API  extern "C" __attribute__((visibility("default")))
#else
#define HYPRIVATE_API  __attribute__((visibility("default")))
#endif

#include "HieServer_Common.h"

/*!
* @brief
*   启动服务
* @return
*   返回0表示成功, 否则表示错误码
* @note
*   启动服务后将会读取配置信息,
*   所以启动前需要先 设置配置信息读写接口
* @note
*   接口类型: 阻塞式
*/
HYPRIVATE_API int HYPrivate_Start();

/*!
* @brief
*   停止服务,断开所有协议及远程连接
* @return
*   返回0表示成功, 否则表示错误码
* @note
*   接口类型: 阻塞式
*/
HYPRIVATE_API int HYPrivate_Stop();

HYPRIVATE_API int HYPrivate_Restart();


HYPRIVATE_API int HYPrivate_GetLocalModuleVersion(char *ModuleVersion);
/*!
* @brief
*   更新事件通知
* @param dwEventType
*   事件类型
* @param dwParam1 -- dwParam3
*   参数表
* @return
*   返回0表示成功, 否则表示错误码
* @note
*   接口类型: 非阻塞式
*/
HYPRIVATE_API int HYPrivate_RefreshEvent(DWORD dwEventType, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3);

/*!
* @brief
*   更新系统时间
* @return
*   返回0表示成功, 否则表示错误码
* @note
*   接口类型: 阻塞
*/
HYPRIVATE_API int HYPrivate_SetNewTime(struct timeval newtime);
#endif


#ifndef HY_RTSP_H

//HYPrivate接口定义文件
#define HY_RTSP_H


#if defined( __cplusplus)
#define HYRTSP_API  extern "C" __attribute__((visibility("default")))
#else
#define HYRTSP_API  __attribute__((visibility("default")))
#endif

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
void *HYRtsp_Start(void *para);

#endif


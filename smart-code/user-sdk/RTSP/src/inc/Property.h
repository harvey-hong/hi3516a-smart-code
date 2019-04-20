#ifndef PROPERTY_H

#define PROPERTY_H

//////////////////////////////////////////////////////////////////////////
///////                             属性值                          //////
//////////////////////////////////////////////////////////////////////////

/** @brief 最大通道个数                                                         */
#define MAX_CHANNEL_NUMBER              32

/** @brief 最大实时流个数                                                       */
#define MAX_REAL_STREAM_NUMBER          32

/** @brief 默认RTSP媒体端口                                                     */
#define DEFAULT_MEDIA_PORT_RTSP         504

/** @brief 默认RTP媒体端口                                                      */
#define DEFAULT_MEDIA_PORT_RTP          6052

/** @brief 默认数据包缓冲区大小                                                 */
#define DEFAULT_COMMAND_BUFFER_LENGTH   256 * 1024

/** @brief 默认媒体数据包缓冲区大小                                             */
#define DEFAULT_MEDIA_BUFFER_LENGTH     256 * 1024

/** @brief 最大实时流发送缓冲区大小                                             */
#define MAX_REAL_STREAM_SEND_BUFFER     (12 * 1024 * 1024)

/** @brief 流媒体系统头长度                                                     */
#define MAX_SYSTEM_HEADER_LENGTH        19

/** @brief 默认SELECT超时时间                                                   */
#define DEFAULT_SELECT_TIMEOUT          1 * 1000

/** @brief 默认命令超时时间                                                     */
#define DEFAULT_COMMAND_TIMEOUT         30 * 1000

/** @brief 会话保活间隔时间                                                     */
#define SESSION_KEEPALIVE_INTERVAL      5 * 1000

#endif

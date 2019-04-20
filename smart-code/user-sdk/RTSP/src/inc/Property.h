#ifndef PROPERTY_H

#define PROPERTY_H

//////////////////////////////////////////////////////////////////////////
///////                             ����ֵ                          //////
//////////////////////////////////////////////////////////////////////////

/** @brief ���ͨ������                                                         */
#define MAX_CHANNEL_NUMBER              32

/** @brief ���ʵʱ������                                                       */
#define MAX_REAL_STREAM_NUMBER          32

/** @brief Ĭ��RTSPý��˿�                                                     */
#define DEFAULT_MEDIA_PORT_RTSP         504

/** @brief Ĭ��RTPý��˿�                                                      */
#define DEFAULT_MEDIA_PORT_RTP          6052

/** @brief Ĭ�����ݰ���������С                                                 */
#define DEFAULT_COMMAND_BUFFER_LENGTH   256 * 1024

/** @brief Ĭ��ý�����ݰ���������С                                             */
#define DEFAULT_MEDIA_BUFFER_LENGTH     256 * 1024

/** @brief ���ʵʱ�����ͻ�������С                                             */
#define MAX_REAL_STREAM_SEND_BUFFER     (12 * 1024 * 1024)

/** @brief ��ý��ϵͳͷ����                                                     */
#define MAX_SYSTEM_HEADER_LENGTH        19

/** @brief Ĭ��SELECT��ʱʱ��                                                   */
#define DEFAULT_SELECT_TIMEOUT          1 * 1000

/** @brief Ĭ�����ʱʱ��                                                     */
#define DEFAULT_COMMAND_TIMEOUT         30 * 1000

/** @brief �Ự������ʱ��                                                     */
#define SESSION_KEEPALIVE_INTERVAL      5 * 1000

#endif

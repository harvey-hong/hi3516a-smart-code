#ifndef HY_RTSP_H

//HYPrivate�ӿڶ����ļ�
#define HY_RTSP_H


#if defined( __cplusplus)
#define HYRTSP_API  extern "C" __attribute__((visibility("default")))
#else
#define HYRTSP_API  __attribute__((visibility("default")))
#endif

/*!
* @brief
*   ��������
* @return
*   ����0��ʾ�ɹ�, �����ʾ������
* @note
*   ��������󽫻��ȡ������Ϣ,
*   ��������ǰ��Ҫ�� ����������Ϣ��д�ӿ�
* @note
*   �ӿ�����: ����ʽ
*/
void *HYRtsp_Start(void *para);

#endif


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
*   ��������
* @return
*   ����0��ʾ�ɹ�, �����ʾ������
* @note
*   ��������󽫻��ȡ������Ϣ,
*   ��������ǰ��Ҫ�� ����������Ϣ��д�ӿ�
* @note
*   �ӿ�����: ����ʽ
*/
HYPRIVATE_API int HYPrivate_Start();

/*!
* @brief
*   ֹͣ����,�Ͽ�����Э�鼰Զ������
* @return
*   ����0��ʾ�ɹ�, �����ʾ������
* @note
*   �ӿ�����: ����ʽ
*/
HYPRIVATE_API int HYPrivate_Stop();

HYPRIVATE_API int HYPrivate_Restart();


HYPRIVATE_API int HYPrivate_GetLocalModuleVersion(char *ModuleVersion);
/*!
* @brief
*   �����¼�֪ͨ
* @param dwEventType
*   �¼�����
* @param dwParam1 -- dwParam3
*   ������
* @return
*   ����0��ʾ�ɹ�, �����ʾ������
* @note
*   �ӿ�����: ������ʽ
*/
HYPRIVATE_API int HYPrivate_RefreshEvent(DWORD dwEventType, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3);

/*!
* @brief
*   ����ϵͳʱ��
* @return
*   ����0��ʾ�ɹ�, �����ʾ������
* @note
*   �ӿ�����: ����
*/
HYPRIVATE_API int HYPrivate_SetNewTime(struct timeval newtime);
#endif


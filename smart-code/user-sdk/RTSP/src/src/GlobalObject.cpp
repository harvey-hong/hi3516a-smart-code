#include "../inc/GlobalObject.h"

CGlobalObject::CGlobalObject()
{
}

CGlobalObject::~CGlobalObject()
{
}

/*
* @brief
*   ��ȡ˽��Э�����
* @return
*   ���ض���
* @note
*   �ӿ�����: ����ʽ
*/
CHYPrivateService &CGlobalObject::PrivateService()
{
    return m_cPrivateService;
}

/*
* @brief
*   ��ȡ����������
* @return
*   ���ض���
* @note
*   �ӿ�����: ����ʽ
*/
CDestroyer &CGlobalObject::Destroyer()
{
    return m_cDestroyer;
}

/*
* @brief
*   ��ȡ��д�������ýӿ�
* @return
*   ���ض���
* @note
*   �ӿ�����: ����ʽ
*/
/*
CPrivateConfigureInterface& CGlobalObject::PrivateConfigureInterface()
{
    return m_cPrivateConfigureInterface;
}
*/
/*
* @brief
*   ��ȡ�û������ӿ�
* @return
*   ���ض���
* @note
*   �ӿ�����: ����ʽ
*/
//CPrivateUserActionInterface& CGlobalObject::PrivateUserActionInterface()
//{
//  return m_cPrivateUserActionInterface;
//}


/*
* @brief
*   ��ȡʵʱ���ӿ�
* @return
*   ���ض���
* @note
*   �ӿ�����: ����ʽ
*/
//CPrivateStreamCaptureInterface& CGlobalObject::PrivateStreamCaptureInterface()
//{
//  return m_cPrivateStreamCaptureInterface;
//}


/*
* @brief
*  ��ȡRTSP���������
* @return
*  ���ض���
* @note
*  �ӿ�����: ����ʽ
*/
INT32 &CGlobalObject::RtspServerHandle()
{
    return m_hRtspServer;
}

/*
* @brief
*  ��ȡRTSP�ỰID������
* @return
*  ���ض���
* @note
*  �ӿ�����: ����ʽ
*/
CRtspSessionIdManager &CGlobalObject::RtspSessionMan()
{
    return m_cRtspSessionIdMan;
}


/*
* @brief
*  ��ȡʵʱ��������
* @return
*  ���ض���
* @note
*  �ӿ�����: ����ʽ
*/
CRealStreamManager &CGlobalObject::RealStreamMan()
{
    return m_cRealStreamMan;
}

/*
* @brief
*  ��ȡ�û�ID�ӿ�
* @return
*  ���ض���
* @note
*  �ӿ�����: ����ʽ
*/
DWORD &CGlobalObject::UserID()
{
    return m_dwUserID;
}


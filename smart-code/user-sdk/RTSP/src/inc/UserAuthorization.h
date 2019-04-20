/*!
* \file     UserAuthorization.h
* \brief    �û���֤
* \author   lixiang
* \date     2010/08/16
* \version  1.0.0
*/

#ifndef USER_AUTHORIZATION_H

#define USER_AUTHORIZATION_H

#include "HYRtspCommon.h"
#include "DigestAuthen.h"
#include "AuthenHeaderParse.h"
#include "BasicAuthen.h"

namespace ApplicationLayer
{

#define AUTHORIZE_SUCCESS       0   // ��֤�ɹ�
#define AUTHORIZE_FAIL          1   // ��֤ʧ��     
#define AUTHORIZE_NONE          2   // δ��֤����ʱrtsp�뷵��401����
#define AUTHORIZE_NO_RIGHT      3   // ��Ԥ��/�ط�Ȩ��

class CUserAuthorization
{
public:
    CUserAuthorization();
    ~CUserAuthorization();

    // ���ò���
    int SetParameter(const char *pUserName, const char *pPassword, const char *pAuthorizeInfo);
    // �û���֤(����ֵ��0--��֤�ɹ��� 1--��֤ʧ�ܣ� 2--�û�δ��֤)
    int Authorize();
    //��ʼ��
    int Initialize();
    // ��ȡ�û���
    char *GetUserName();

    char *GetUserPasswd();

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CUserAuthorization);

private:
    // ͨ���û��������������֤
    int ValidateByUserNameAndPass();
    // ͨ��ժҪ��֤
    int ValidateByDigest();
    // ͨ��������֤
    int ValidateByBasic();

public:
    CAuthenHeaderParse m_authenHeaderParse;         //! <Authorizationͷ�ֶν�������
    CDigestAuthen m_digestAuthen;                   //!< ժҪ��֤����
    CBasicAuthen m_basicAuthen;                     //!< ������֤����

private:
    char m_acUserName[USERNAME_LEN];                //!< �û���
    char m_acPassword[USERPASS_LEN];                //!< �û�����
    char m_acAuthorizeInfo[MAX_AUTHORIZE_INFO_LEN]; //!< rtsp�����е���֤��Ϣ
};
}


#endif

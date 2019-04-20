/*!
* \file     AuthenHeaderParse.h
* \brief    Authorizationͷ�ֶν���
* \author   lixiang
* \date     2010/08/26
* \version  1.0.0
*/

#ifndef AUTHEN_HEADER_PARSER_H_

#define AUTHEN_HEADER_PARSER_H_

#include "HYRtspCommon.h"
#include "InternalCommon.h"
/* �û�digest��֤��ӦAuthorizationͷ�ֶθ�ʽΪ
//            Authorization:Digest username="[�û���]",realm="[realm]",nonce="[nonce]",uri="[uri]",response="[response]"
// �û�basic��֤��ӦAuthorizationͷ�ֶθ�ʽΪ
//            Authorization:Basic [response]
*/
namespace   ApplicationLayer
{
class CAuthenHeaderParse
{
public:
    CAuthenHeaderParse();
    ~CAuthenHeaderParse();
public:
    // ����Authorizationͷ�ֶ�
    int SetAuthenHeader(const char *pAuthenHeader);
    //��ȡ�û���֤��ʽ
    eAuthenType GetAuthenType();
    // ��ȡ�û���
    const char *GetUserName();
    const char *GetUserPasswd();
    // ��ȡrealm
    const char *GetRealm();
    // ��ȡnonce
    const char *GetNonce();
    // ��ȡrtsp uri
    const char *GetUri();
    // ��ȡresponse
    const char *GetResponse();

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CAuthenHeaderParse);

protected:
    // ��ʼ��
    int Initialize();

private:
    eAuthenType m_eAuthenType;                      //!< �û���֤��ʽ
    char m_acAuthenHeader[MAX_AUTHORIZE_INFO_LEN];  //!< Authorizationͷ�ֶ�
    char m_acUserName[USERNAME_LEN];                //!< �û���
    char m_acUserPasswd[USERPASS_LEN];              //!< ����
    char m_acRealm[MAX_REALM_STRING_LEN];           //!< realm
    char m_acNonce[MAX_NONCE_STRING_LEN];           //!< nonce
    char m_acUri[MAX_RTSP_URI_LEN];                 //!< rtsp uri
    char m_acResponse[MAX_RESPONSE_STRING_LEN];     //!< response
};
}

#endif

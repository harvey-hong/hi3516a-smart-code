/*!
* \file     AuthenHeaderParse.h
* \brief    Authorization头字段解析
* \author   lixiang
* \date     2010/08/26
* \version  1.0.0
*/

#ifndef AUTHEN_HEADER_PARSER_H_

#define AUTHEN_HEADER_PARSER_H_

#include "HYRtspCommon.h"
#include "InternalCommon.h"
/* 用户digest认证响应Authorization头字段格式为
//            Authorization:Digest username="[用户名]",realm="[realm]",nonce="[nonce]",uri="[uri]",response="[response]"
// 用户basic认证响应Authorization头字段格式为
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
    // 设置Authorization头字段
    int SetAuthenHeader(const char *pAuthenHeader);
    //获取用户认证方式
    eAuthenType GetAuthenType();
    // 获取用户名
    const char *GetUserName();
    const char *GetUserPasswd();
    // 获取realm
    const char *GetRealm();
    // 获取nonce
    const char *GetNonce();
    // 获取rtsp uri
    const char *GetUri();
    // 获取response
    const char *GetResponse();

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CAuthenHeaderParse);

protected:
    // 初始化
    int Initialize();

private:
    eAuthenType m_eAuthenType;                      //!< 用户认证方式
    char m_acAuthenHeader[MAX_AUTHORIZE_INFO_LEN];  //!< Authorization头字段
    char m_acUserName[USERNAME_LEN];                //!< 用户名
    char m_acUserPasswd[USERPASS_LEN];              //!< 密码
    char m_acRealm[MAX_REALM_STRING_LEN];           //!< realm
    char m_acNonce[MAX_NONCE_STRING_LEN];           //!< nonce
    char m_acUri[MAX_RTSP_URI_LEN];                 //!< rtsp uri
    char m_acResponse[MAX_RESPONSE_STRING_LEN];     //!< response
};
}

#endif

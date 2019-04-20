/*!
* \file     UserAuthorization.h
* \brief    用户认证
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

#define AUTHORIZE_SUCCESS       0   // 验证成功
#define AUTHORIZE_FAIL          1   // 验证失败     
#define AUTHORIZE_NONE          2   // 未验证，此时rtsp须返回401错误
#define AUTHORIZE_NO_RIGHT      3   // 无预览/回放权限

class CUserAuthorization
{
public:
    CUserAuthorization();
    ~CUserAuthorization();

    // 设置参数
    int SetParameter(const char *pUserName, const char *pPassword, const char *pAuthorizeInfo);
    // 用户验证(返回值：0--验证成功， 1--验证失败， 2--用户未验证)
    int Authorize();
    //初始化
    int Initialize();
    // 获取用户名
    char *GetUserName();

    char *GetUserPasswd();

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CUserAuthorization);

private:
    // 通过用户名和密码进行验证
    int ValidateByUserNameAndPass();
    // 通过摘要验证
    int ValidateByDigest();
    // 通过基本验证
    int ValidateByBasic();

public:
    CAuthenHeaderParse m_authenHeaderParse;         //! <Authorization头字段解析对象
    CDigestAuthen m_digestAuthen;                   //!< 摘要认证对象
    CBasicAuthen m_basicAuthen;                     //!< 基本认证对象

private:
    char m_acUserName[USERNAME_LEN];                //!< 用户名
    char m_acPassword[USERPASS_LEN];                //!< 用户密码
    char m_acAuthorizeInfo[MAX_AUTHORIZE_INFO_LEN]; //!< rtsp请求中的认证信息
};
}


#endif

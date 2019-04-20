#include "../inc/InternalCommon.h"
#include "../inc/GlobalObject.h"
#include "../inc/UserAuthorization.h"

#include "getlocalinfo.h"

using namespace GETLOCALINFO;

namespace ApplicationLayer
{
CUserAuthorization::CUserAuthorization()
{
    Initialize();
}

CUserAuthorization::~CUserAuthorization()
{
    Initialize();
}

// 初始化
int CUserAuthorization::Initialize()
{
    memset(m_acUserName, 0, USERNAME_LEN);
    memset(m_acPassword, 0, USERPASS_LEN);
    memset(m_acAuthorizeInfo, 0, MAX_AUTHORIZE_INFO_LEN);
    return RET_SUCCESS;
}

//\\ 设置用户名与密码与授权信息
int CUserAuthorization::SetParameter(const char *pUserName, const char *pPassword, const char *pAuthorizeInfo)
{
    if (NULL == pUserName || NULL == pPassword || NULL == pAuthorizeInfo)
    {
        return RET_FAIL;
    }

    Initialize();
    strcpy(m_acUserName, pUserName);
    strcpy(m_acPassword, pPassword);
    strcpy(m_acAuthorizeInfo, pAuthorizeInfo);
    return RET_SUCCESS;
}

//\\ 用户验证，包括3种方式，1是用户名与密码验证方式，2是Basic验证方式，3是Digest验证方式，2与3下保存用户名信息
int CUserAuthorization::Authorize()
{
    int nRet = RET_FAIL;

    if ((0 != strlen(m_acUserName)) && (0 != strlen(m_acPassword)))
    {
        //\\ 通过用户层回调函数验证用户名与密码是否正确
        nRet = ValidateByUserNameAndPass();
    }

    if (RET_SUCCESS != nRet && AUTHORIZE_SUCCESS != nRet && 0 != strlen(m_acAuthorizeInfo))
    {
        //\\ RTSP授权认证支持两种方式，eAuthenBasic方式则拷贝m_acResponse信息，eAuthenDigest方式则拷贝username、realm、nonce、uri、response信息
        if (RET_FAIL == m_authenHeaderParse.SetAuthenHeader(m_acAuthorizeInfo))
        {
            return AUTHORIZE_FAIL;
        }

        eAuthenType eType = m_authenHeaderParse.GetAuthenType();

        //\\ Basic验证方式下通过回调方式判断用户名与密码是否正确
        if (eAuthenBasic == eType)
        {
            nRet = ValidateByBasic();
        }
        //\\ 摘要验证方式下验证摘要与回调下验证用户名与密码是否正确
        else if (eAuthenDigest == eType)
        {
            nRet =  ValidateByDigest();
        }
        else
        {
            nRet = AUTHORIZE_NONE;
        }

        if (AUTHORIZE_SUCCESS == nRet)
        {
            memmove(m_acUserName, m_authenHeaderParse.GetUserName(), USERNAME_LEN);
            memmove(m_acPassword, m_authenHeaderParse.GetUserPasswd(), USERPASS_LEN);
        }
    }
    else if (RET_SUCCESS != nRet && AUTHORIZE_SUCCESS != nRet)
    {
        nRet = AUTHORIZE_FAIL;
    }

    return nRet;
}

//\\ 通过用户层回调函数验证用户名与密码是否正确
int CUserAuthorization::ValidateByUserNameAndPass()
{
    //\\ 私有函数
    char acPassword[USERPASS_LEN];
    memset(acPassword, 0, sizeof(acPassword));

    if (0 == strlen(m_acUserName))
    {
        return AUTHORIZE_NONE;
    }

	if(RET_CHECK_FAIL(GetPassByName(m_acUserName,acPassword,USERPASS_LEN)))
			return AUTHORIZE_FAIL;

    if (0 == strlen(acPassword))
    {
        return AUTHORIZE_NONE;
    }

    if (0 == strcmp(m_acPassword, acPassword))
    {
        return AUTHORIZE_SUCCESS;
    }
    else
    {
        return AUTHORIZE_FAIL;
    }
}

//\\ 摘要验证方式下验证摘要与回调下验证用户名与密码是否正确
int CUserAuthorization::ValidateByDigest()
{
    //\\ 私有函数
    char acPassword[USERPASS_LEN];
    const char *acResponse;
    memset(acPassword, 0, sizeof(acPassword));

    if (strlen(m_authenHeaderParse.GetUserName()) == 0 ||
        strlen(m_authenHeaderParse.GetRealm()) == 0 ||
        strlen(m_authenHeaderParse.GetNonce()) == 0)
    {
        return AUTHORIZE_NONE;
    }

    if (strcmp(m_digestAuthen.GetRealm(), m_authenHeaderParse.GetRealm()) || strcmp(m_digestAuthen.GetNonce(), m_authenHeaderParse.GetNonce()))
    {
        return AUTHORIZE_FAIL;
    }

	if(RET_CHECK_FAIL(GetPassByName(m_authenHeaderParse.GetUserName(),acPassword,USERPASS_LEN)))
			return RET_FAIL;
	
    m_digestAuthen.SetUsernameAndPassword(m_authenHeaderParse.GetUserName(), acPassword);
    acResponse = m_digestAuthen.ComputeDigestResponse("DESCRIBE", m_authenHeaderParse.GetUri());

    if (strcmp(acResponse, m_authenHeaderParse.GetResponse()))
    {
        free((char *)acResponse);
        return AUTHORIZE_FAIL;
    }
    else
    {
        free((char *)acResponse);
        return AUTHORIZE_SUCCESS;
    }
}

//\\ Basic验证方式下通过回调方式判断用户名与密码是否正确
int CUserAuthorization::ValidateByBasic()
{
    //\\ 私有函数
    char acPassword[USERPASS_LEN];
    memset(acPassword, 0, sizeof(acPassword));
    //\\ 从应答信息中解析出用户名与密码
    m_basicAuthen.SetResponse(m_authenHeaderParse.GetResponse());

    if (0 == strlen(m_basicAuthen.GetUserName()))
    {
        return AUTHORIZE_NONE;
    }

    if (0 == strlen(m_basicAuthen.GetPassword()))
    {
        return AUTHORIZE_NONE;
    }

    const char *basicus = m_basicAuthen.GetUserName();
    const char *basicpw = m_basicAuthen.GetPassword();
    if(RET_CHECK_FAIL(GetPassByName(basicus,acPassword,USERPASS_LEN)))
			return RET_FAIL;

		if ( !strcmp(basicpw, acPassword) )
		{
			return AUTHORIZE_SUCCESS;
		}
		else
		{
			return AUTHORIZE_FAIL;
		}
    return AUTHORIZE_SUCCESS;
}

// 获取用户名
char *CUserAuthorization::GetUserName()
{
    return m_acUserName;
}

//Get password
char *CUserAuthorization::GetUserPasswd()
{
    return m_acPassword;
}
}

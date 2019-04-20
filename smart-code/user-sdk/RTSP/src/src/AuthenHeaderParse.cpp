#include "../inc/InternalCommon.h"
#include "../inc/AuthenHeaderParse.h"

namespace ApplicationLayer
{
CAuthenHeaderParse::CAuthenHeaderParse()
{
    Initialize();
}

CAuthenHeaderParse::~CAuthenHeaderParse()
{
    Initialize();
}

// 初始化
int CAuthenHeaderParse::Initialize()
{
    m_eAuthenType = eAuthenUnknown;
    memset(m_acAuthenHeader, 0, MAX_AUTHORIZE_INFO_LEN);
    memset(m_acUserName, 0, USERNAME_LEN);
    memset(m_acRealm, 0, MAX_REALM_STRING_LEN);
    memset(m_acNonce, 0, MAX_NONCE_STRING_LEN);
    memset(m_acUri, 0, MAX_RTSP_URI_LEN);
    memset(m_acResponse, 0, MAX_RESPONSE_STRING_LEN);
    return RET_SUCCESS;
}

//\\ RTSP授权认证支持两种方式，eAuthenBasic方式则拷贝m_acResponse信息，eAuthenDigest方式则拷贝username、realm、nonce、uri、response信息
int CAuthenHeaderParse::SetAuthenHeader(const char *pAuthenHeader)
{
    const char *pBufTempStart = NULL;
    const char *pBufTempEnd = NULL;
    Initialize();

    if (CHECK_POINT_NULL(pAuthenHeader))
    {
        return RET_FAIL;
    }

    while (*pAuthenHeader != '\0' && *pAuthenHeader == ' ')
    {
        pAuthenHeader++;
    }

    //\\ 授权认证包括eAuthenBasic与eAuthenDigest两种方式
    if (!memcmp(pAuthenHeader, "Basic", strlen("Basic")))
    {
        pBufTempStart = strstr(pAuthenHeader, "Basic");
        m_eAuthenType = eAuthenBasic;
    }
    else if (!memcmp(pAuthenHeader, "basic", strlen("basic")))
    {
        pBufTempStart = strstr(pAuthenHeader, "basic");
        m_eAuthenType = eAuthenBasic;
    }
    else if (!memcmp(pAuthenHeader, "Digest", strlen("Digest")))
    {
        m_eAuthenType = eAuthenDigest;
    }
    else if (!memcmp(pAuthenHeader, "digest", strlen("digest")))
    {
        m_eAuthenType = eAuthenDigest;
    }
    else
    {
        m_eAuthenType = eAuthenUnknown;
    }

    switch (m_eAuthenType)
    {
        case eAuthenBasic:
            pBufTempEnd = pBufTempStart + strlen("Basic");

            while (*pBufTempEnd != '\0' && *pBufTempEnd == ' ')
            {
                pBufTempEnd++;
            }

            strcpy(m_acResponse, pBufTempEnd);
            break;

        case eAuthenDigest:

            //\\ 如果这五个属性不全包含在Authorization头字段，那么该Authorization头字段无效，返回失败
            if (NULL == strstr(pAuthenHeader, "username=") || NULL == strstr(pAuthenHeader, "realm=") ||
                NULL == strstr(pAuthenHeader, "nonce=") || NULL == strstr(pAuthenHeader, "uri=") ||
                NULL == strstr(pAuthenHeader, "response="))
            {
                return RET_FAIL;
            }

            if (sizeof(pAuthenHeader) > MAX_AUTHORIZE_INFO_LEN)
            {
                return RET_FAIL;
            }

            //\\ 获取用户名
            memcpy(m_acAuthenHeader, pAuthenHeader, sizeof(pAuthenHeader));
            pBufTempStart = strstr(pAuthenHeader, "username=\"");
            pBufTempStart += strlen("username=\"");
            pBufTempEnd = strstr(pBufTempStart, "\"");

            if (pBufTempEnd - pBufTempStart > USERNAME_LEN)
            {
                Initialize();
                return RET_FAIL;
            }

            memcpy(m_acUserName, pBufTempStart, pBufTempEnd - pBufTempStart);
            //\\ 获取realm信息
            pBufTempStart = strstr(pAuthenHeader, "realm=\"");
            pBufTempStart += strlen("realm=\"");
            pBufTempEnd = strstr(pBufTempStart, "\"");

            if (pBufTempEnd - pBufTempStart > MAX_REALM_STRING_LEN)
            {
                Initialize();
                return RET_FAIL;
            }

            memcpy(m_acRealm, pBufTempStart, pBufTempEnd - pBufTempStart);
            //\\ 获取nonce信息
            pBufTempStart = strstr(pAuthenHeader, "nonce=\"");
            pBufTempStart += strlen("nonce=\"");
            pBufTempEnd = strstr(pBufTempStart, "\"");

            if (pBufTempEnd - pBufTempStart > MAX_NONCE_STRING_LEN)
            {
                Initialize();
                return RET_FAIL;
            }

            memcpy(m_acNonce, pBufTempStart, pBufTempEnd - pBufTempStart);
            //\\ 获取url信息
            pBufTempStart = strstr(pAuthenHeader, "uri=\"");
            pBufTempStart += strlen("uri=\"");
            pBufTempEnd = strstr(pBufTempStart, "\"");

            if (pBufTempEnd - pBufTempStart > MAX_RTSP_URI_LEN)
            {
                Initialize();
                return RET_FAIL;
            }

            memcpy(m_acUri, pBufTempStart, pBufTempEnd - pBufTempStart);
            //\\ 获取response信息
            pBufTempStart = strstr(pAuthenHeader, "response=\"");
            pBufTempStart += strlen("response=\"");
            pBufTempEnd = strstr(pBufTempStart, "\"");

            if (pBufTempEnd - pBufTempStart > MAX_RESPONSE_STRING_LEN)
            {
                Initialize();
                return RET_FAIL;
            }

            memcpy(m_acResponse, pBufTempStart, pBufTempEnd - pBufTempStart);
            break;

        default:
            break;
    }

    return RET_SUCCESS;
}
//获取用户认证方式
eAuthenType CAuthenHeaderParse::GetAuthenType()
{
    return m_eAuthenType;
}
// 获取用户名
const char *CAuthenHeaderParse::GetUserName()
{
    return m_acUserName;
}

// 获取密码
const char *CAuthenHeaderParse::GetUserPasswd()
{
    return m_acUserPasswd;
}

// 获取realm
const char *CAuthenHeaderParse::GetRealm()
{
    return m_acRealm;
}

// 获取nonce
const char *CAuthenHeaderParse::GetNonce()
{
    return m_acNonce;
}

// 获取rtsp uri
const char *CAuthenHeaderParse::GetUri()
{
    return m_acUri;
}

// 获取response
const char *CAuthenHeaderParse::GetResponse()
{
    return m_acResponse;
}
}

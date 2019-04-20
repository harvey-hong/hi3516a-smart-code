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

// ��ʼ��
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

//\\ RTSP��Ȩ��֤֧�����ַ�ʽ��eAuthenBasic��ʽ�򿽱�m_acResponse��Ϣ��eAuthenDigest��ʽ�򿽱�username��realm��nonce��uri��response��Ϣ
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

    //\\ ��Ȩ��֤����eAuthenBasic��eAuthenDigest���ַ�ʽ
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

            //\\ �����������Բ�ȫ������Authorizationͷ�ֶΣ���ô��Authorizationͷ�ֶ���Ч������ʧ��
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

            //\\ ��ȡ�û���
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
            //\\ ��ȡrealm��Ϣ
            pBufTempStart = strstr(pAuthenHeader, "realm=\"");
            pBufTempStart += strlen("realm=\"");
            pBufTempEnd = strstr(pBufTempStart, "\"");

            if (pBufTempEnd - pBufTempStart > MAX_REALM_STRING_LEN)
            {
                Initialize();
                return RET_FAIL;
            }

            memcpy(m_acRealm, pBufTempStart, pBufTempEnd - pBufTempStart);
            //\\ ��ȡnonce��Ϣ
            pBufTempStart = strstr(pAuthenHeader, "nonce=\"");
            pBufTempStart += strlen("nonce=\"");
            pBufTempEnd = strstr(pBufTempStart, "\"");

            if (pBufTempEnd - pBufTempStart > MAX_NONCE_STRING_LEN)
            {
                Initialize();
                return RET_FAIL;
            }

            memcpy(m_acNonce, pBufTempStart, pBufTempEnd - pBufTempStart);
            //\\ ��ȡurl��Ϣ
            pBufTempStart = strstr(pAuthenHeader, "uri=\"");
            pBufTempStart += strlen("uri=\"");
            pBufTempEnd = strstr(pBufTempStart, "\"");

            if (pBufTempEnd - pBufTempStart > MAX_RTSP_URI_LEN)
            {
                Initialize();
                return RET_FAIL;
            }

            memcpy(m_acUri, pBufTempStart, pBufTempEnd - pBufTempStart);
            //\\ ��ȡresponse��Ϣ
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
//��ȡ�û���֤��ʽ
eAuthenType CAuthenHeaderParse::GetAuthenType()
{
    return m_eAuthenType;
}
// ��ȡ�û���
const char *CAuthenHeaderParse::GetUserName()
{
    return m_acUserName;
}

// ��ȡ����
const char *CAuthenHeaderParse::GetUserPasswd()
{
    return m_acUserPasswd;
}

// ��ȡrealm
const char *CAuthenHeaderParse::GetRealm()
{
    return m_acRealm;
}

// ��ȡnonce
const char *CAuthenHeaderParse::GetNonce()
{
    return m_acNonce;
}

// ��ȡrtsp uri
const char *CAuthenHeaderParse::GetUri()
{
    return m_acUri;
}

// ��ȡresponse
const char *CAuthenHeaderParse::GetResponse()
{
    return m_acResponse;
}
}

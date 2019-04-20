// A class used for basic authentication.
// Implementation

#include "../inc/BasicAuthen.h"
#include "ws_base64.h"

using namespace ws_base64;

CBasicAuthen::CBasicAuthen()
{
    m_pUsername = NULL;
    m_pPassword = NULL;
}

CBasicAuthen::~CBasicAuthen()
{
    if (m_pUsername != NULL)
    {
        free(m_pUsername);
        m_pUsername = NULL;
    }

    if (m_pPassword != NULL)
    {
        free(m_pPassword);
        m_pPassword = NULL;
    }
}

//\\ 从应答信息中获取用户名与密码
bool CBasicAuthen::SetResponse(const char *response)
{
    char  *pAuthenInfo = (char *)malloc(256);
    char        *pTemp = NULL;
    int size = 0;

    if( (NULL == response)||(NULL == pAuthenInfo) )
    {
        return false;
    }
    memset(pAuthenInfo, 0, 256);
    int RetLen = 256;

    if (NULL == GetAuthenInfoFromResponse(response, pAuthenInfo, &RetLen))
    {
        free(pAuthenInfo);
        return false;
    }

    if (NULL == (pTemp = strstr((char *)pAuthenInfo, ":")))
    {
        free(pAuthenInfo);
        return false;
    }

    size = pTemp - pAuthenInfo;
    m_pUsername = new char[size + 1];

    if (NULL == m_pUsername)
    {
        free(pAuthenInfo);
        return false;
    }

    memcpy(m_pUsername, pAuthenInfo, size);
    m_pUsername[size] = '\0';
    size = strlen(pTemp + 1) + 1;
    m_pPassword = new char[size];

    if (NULL == m_pPassword)
    {
        free(m_pUsername);
        m_pUsername = NULL;
        free(pAuthenInfo);
        return false;
    }

    strcpy(m_pPassword, pTemp + 1);
    free(pAuthenInfo);
    return true;
}

char *CBasicAuthen::strDup(const char *str)
{
    if (str == NULL)
    {
        return NULL;
    }

    size_t len = strlen(str) + 1;
    char *dest = new char[len];

    if (dest != NULL)
    {
        memcpy(dest, str, len);
    }

    return dest;
}

char *CBasicAuthen::GetAuthenInfoFromResponse(const char *response, char *DecText, int *TextLength)
{
    if( (NULL == response)||(NULL == DecText)||(NULL == TextLength)||(*TextLength <= 0) )
    {
        return NULL;
    }

    /* Decode it. */
    if(Base64Decode(response, strlen(response), DecText, TextLength) < 0 )
    {
        HTTP_PE("Base64Decode fail !!\n");
        return NULL;
    }
    else
    {
        return DecText;
    }
}


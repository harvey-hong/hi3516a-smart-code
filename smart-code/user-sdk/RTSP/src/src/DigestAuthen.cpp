// A class used for digest authentication.
// Implementation
#include "../inc/InternalCommon.h"
#include "../inc/DigestAuthen.h"
#include "../inc/md5.h"

char *strDup(const char *str)
{
    if (str == NULL)
    {
        return NULL;
    }

    size_t len = strlen(str) + 1;
    char *copy = new char[len];

    if (copy != NULL)
    {
        memcpy(copy, str, len);
    }

    return copy;
}

CDigestAuthen::CDigestAuthen()
{
    Assign(NULL, NULL, NULL, NULL);
}

CDigestAuthen::CDigestAuthen(const char *username, const char *password)
{
    SetUsernameAndPassword(username, password);
}

CDigestAuthen::~CDigestAuthen()
{
    ResetRealmAndNonce();
    ResetUsernameAndPassword();
}

void CDigestAuthen::SetRealmAndRandomNonce(const char *realm)
{
    ResetRealmAndNonce();
    // Construct data to seed the random nonce:
    struct
    {
        struct timeval timestamp;
        unsigned counter;
    } seedData;
    gettimeofday(&seedData.timestamp, NULL);
    static unsigned counter = 0;
    seedData.counter = ++counter;
    // Use MD5 to compute a 'random' nonce from this seed data:
    char nonceBuf[33];
    MD5Data((unsigned char *)(&seedData), sizeof seedData, nonceBuf);
    AssignRealmAndNonce(realm, nonceBuf);
}

void CDigestAuthen::SetUsernameAndPassword(const char *username, const char *password)
{
    ResetUsernameAndPassword();
    AssignUsernameAndPassword(username, password);
}

const char *CDigestAuthen::ComputeDigestResponse(const char *cmd, const char *url)
{
    // The "response" field is computed as:
    //    md5(md5(<username>:<realm>:<password>):<nonce>:md5(<cmd>:<url>))
    char ha1Buf[33];
    unsigned const ha1DataLen = strlen(GetUsername()) + 1 + strlen(GetRealm()) + 1 + strlen(GetPassword());
    unsigned char *ha1Data = new unsigned char[ha1DataLen + 1];
    sprintf((char *)ha1Data, "%s:%s:%s", GetUsername(), GetRealm(), GetPassword());
    MD5Data(ha1Data, ha1DataLen, ha1Buf);
    delete ha1Data;
    unsigned const ha2DataLen = strlen(cmd) + 1 + strlen(url);
    unsigned char *ha2Data = new unsigned char[ha2DataLen + 1];
    sprintf((char *)ha2Data, "%s:%s", cmd, url);
    char ha2Buf[33];
    MD5Data(ha2Data, ha2DataLen, ha2Buf);
    delete ha2Data;
    unsigned const digestDataLen = 32 + 1 + strlen(GetNonce()) + 1 + 32;
    unsigned char *digestData = new unsigned char[digestDataLen + 1];
    sprintf((char *)digestData, "%s:%s:%s", ha1Buf, GetNonce(), ha2Buf);
    const char *result = MD5Data(digestData, digestDataLen, NULL);
    delete digestData;
    return result;
}

void CDigestAuthen::ResetRealmAndNonce()
{
    delete m_pRealm;
    m_pRealm = NULL;
    delete m_pNonce;
    m_pNonce = NULL;
}

void CDigestAuthen::ResetUsernameAndPassword()
{
    delete m_pUsername;
    m_pUsername = NULL;
    delete m_pPassword;
    m_pPassword = NULL;
}

void CDigestAuthen::AssignRealmAndNonce(const char *realm, const char *nonce)
{
    m_pRealm = strDup(realm);
    m_pNonce = strDup(nonce);
}

void CDigestAuthen::AssignUsernameAndPassword(const char *username, const char *password)
{
    m_pUsername = strDup(username);
    m_pPassword = strDup(password);
}

void CDigestAuthen::Assign(const char *realm, const char *nonce, const char *username, const char *password)
{
    AssignRealmAndNonce(realm, nonce);
    AssignUsernameAndPassword(username, password);
}

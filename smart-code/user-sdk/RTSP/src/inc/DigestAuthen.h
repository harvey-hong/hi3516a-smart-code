#ifndef _DIGEST_AUTHEN_H
#define _DIGEST_AUTHEN_H

// A class used for digest authentication.
// The "realm", and "nonce" fields are supplied by the server
// (in a "401 Unauthorized" response).
// The "username" and "password" fields are supplied by the client.

class CDigestAuthen
{
public:
    CDigestAuthen();
    CDigestAuthen(const char *username, const char *password);
    virtual ~CDigestAuthen();

    void SetRealmAndRandomNonce(const char *realm);
    void SetUsernameAndPassword(const char *username, const char *password);

    char *GetRealm()
    {
        return m_pRealm;
    }
    char *GetNonce()
    {
        return m_pNonce;
    }
    char *GetUsername()
    {
        return m_pUsername;
    }
    char *GetPassword()
    {
        return m_pPassword;
    }

    const char *ComputeDigestResponse(const char *cmd, const char *url);

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CDigestAuthen);

private:
    void ResetRealmAndNonce();
    void ResetUsernameAndPassword();
    void AssignRealmAndNonce(const char *realm, const char *nonce);
    void AssignUsernameAndPassword(const char *username, const char *password);
    void Assign(const char *realm, const char *nonce, const char *username, const char *password);

private:
    char *m_pRealm;
    char *m_pNonce;
    char *m_pUsername;
    char *m_pPassword;
};

#endif

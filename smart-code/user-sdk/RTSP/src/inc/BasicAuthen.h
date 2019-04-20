#ifndef _BASIC_AUTHEN_H
#define _BASIC_AUTHEN_H

// A class used for basic authentication.

#include "InternalCommon.h"

class CBasicAuthen
{
public:
    CBasicAuthen();
    virtual ~CBasicAuthen();

    bool SetResponse(const char *response);
    const char *GetUserName()
    {
        return m_pUsername;
    }
    const char *GetPassword()
    {
        return m_pPassword;
    }

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CBasicAuthen);

private:
    char *strDup(const char *str);
    char *GetAuthenInfoFromResponse(const char *response, char *DecText, int *TextLength);

private:
    char *m_pUsername;
    char *m_pPassword;
};

#endif

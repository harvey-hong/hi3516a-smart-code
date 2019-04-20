#ifndef UTILITY_H

#define UTILITY_H

#include "../inc/InternalCommon.h"

namespace   ApplicationLayer
{

class CUtility
{
public:
    CUtility();
    ~CUtility();
public:
    static int  Sleep(DWORD time);
    static DWORD GetTickCount();
private:
    static DWORD Sleep_Linux(DWORD time);
    static DWORD GetTickCount_Linux();
private:
    static DWORD Sleep_Windows(DWORD time);
    static DWORD GetTickCount_Windows();
private:
    DWORD   m_dwTickExpend;
};

}

#endif

#include "../inc/Utility.h"

namespace   ApplicationLayer
{
CUtility::CUtility()
{
    m_dwTickExpend = 0;
}

CUtility::~CUtility()
{
    m_dwTickExpend = 0;
}

int CUtility::Sleep(DWORD time)
{
#ifdef SYSTEM_WIN32
    return Sleep_Windows(time);
#elif defined(SYSTEM_LINUX)
    return Sleep_Linux(time);
#else
    return 0;
#endif
}

DWORD CUtility::GetTickCount()
{
#ifdef SYSTEM_WIN32
    return GetTickCount_Windows();
#elif defined(SYSTEM_LINUX)
    return GetTickCount_Linux();
#else
    return 0;
#endif
}


DWORD CUtility::Sleep_Linux(DWORD time)
{
#ifdef SYSTEM_LINUX
    struct timeval tv;
    tv.tv_sec  = time / 1000;
    tv.tv_usec = (time % 1000) * 1000;
    ::select(0, 0, 0, 0, &tv);
#endif
    return 0;
}

DWORD CUtility::Sleep_Windows(DWORD time)
{
#ifdef SYSTEM_WIN32
    ::Sleep(time);
#endif
    return 0;
}

DWORD CUtility::GetTickCount_Linux()
{
#ifdef SYSTEM_LINUX
    timeval tstart;
    gettimeofday(&tstart, NULL);
    ULONGLONG v = tstart.tv_sec * 1000 + tstart.tv_usec / 1000;
    return (DWORD)(v & 0x00000000ffffffff);
#endif
    return 0;
}

DWORD CUtility::GetTickCount_Windows()
{
#ifdef SYSTEM_WIN32
    return ::GetTickCount();
#endif
    return 0;
}

}

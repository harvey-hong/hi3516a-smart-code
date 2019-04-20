#ifndef T_RESOURCE_MANAGER_H

#define T_RESOURCE_MANAGER_H

#include "ws_utility_api.h"
#include "ws_common.h"
#include "ws_comm_debug.h"
#include "ws_comm_errno.h"
using namespace ws_utility;
using namespace ws_soft;

namespace   ApplicationLayer
{

template<class T_TYPE, int tiResourceNumber>
class TResourceManager
{
public:
    TResourceManager()
    {
        if( WS_SUCCESS != m_cMutex.create() )
            return ;

        m_cMutex.lock();
        Initialize();
        m_cMutex.unlock();
    }
    ~TResourceManager()
    {
        m_cMutex.lock();
        Destroy();
        m_cMutex.unlock();
        m_cMutex.destroy();
    }

    T_TYPE &operator[](int iIndex)
    {
        return Resource(iIndex);
    }

protected:
    TResourceManager(const TResourceManager &rObj)
    {
        (*this) = rObj;
    }

    TResourceManager &operator=(const TResourceManager &rObj)
    {
        return (*this);
    }
public:
    int Initialize()
    {
        for (int iCount = 0; iCount < tiResourceNumber; iCount++)
        {
            m_eResourceState[iCount] = eResourceIdle;
        }

        return 0;
    }

    int Destroy()
    {
        Initialize();
        return 0;
    }

    int Create(int &iResource)
    {
        CGuard  guard(&m_cMutex);
        int         iCount ;

        for (iCount = 0; iCount < tiResourceNumber; iCount++)
        {
            if (eResourceIdle == m_eResourceState[iCount])
            {
                m_eResourceState[iCount]    = eResourceBusy;
                iResource               = iCount;
                return 0;
            }
        }

        return 1;
    }

    int Create(int &iResource, T_TYPE &cResource)
    {
        CGuard  guard(&m_cMutex);
        int         iCount ;

        for (iCount = 0; iCount < tiResourceNumber; iCount++)
        {
            if (eResourceIdle == m_eResourceState[iCount])
            {
                m_eResourceState[iCount]    = eResourceBusy;
                iResource               = iCount;
                m_cResource[iCount]         = cResource;
                return 0;
            }
        }

        return 1;
    }

    int Destroy(int iResource)
    {
        CGuard  guard(&m_cMutex);

        if (iResource >= tiResourceNumber)
        {
            return 1;
        }

        if (eResourceIdle == m_eResourceState[iResource])
        {
            return 1 ;
        }

        m_eResourceState[iResource] = eResourceIdle;
        return 0;
    }

    int DestroySession(T_TYPE cResource)
    {
        CGuard  guard(&m_cMutex);
        int         count ;

        for (count = 0; count < tiResourceNumber; count++)
        {
            if ((eResourceIdle != m_eResourceState[count]) && (m_cResource[count] == cResource))
            {
                m_eResourceState[count] = eResourceIdle;
            }
        }

        return 0;
    }

    int SearchResource(int &iResource, T_TYPE &cResource)
    {
        CGuard  guard(&m_cMutex);
        int         iCount ;

        for (iCount = 0; iCount < tiResourceNumber; iCount++)
        {
            if (eResourceIdle != m_eResourceState[iCount])
            {
                if (cResource == m_cResource[iCount])
                {
                    iResource = iCount;
                    return 0;
                }
            }
        }

        return 1;
    }

    T_TYPE &Resource(int iIndex)
    {
        return m_cResource[iIndex];
    }

    int ResourceNumber(int &iNumber)
    {
        CGuard  guard(&m_cMutex);
        iNumber         = 0;
        int             iCount ;

        for (iCount = 0; iCount < tiResourceNumber; iCount++)
        {
            if (eResourceIdle != m_eResourceState[iCount])
            {
                iNumber += 1;
            }
        }

        return 0;
    }

    int CheckResourceIdle(int iResource)
    {
        CGuard  guard(&m_cMutex);

        if (tiResourceNumber <= iResource)
        {
            return 0 ;
        }

        return ((eResourceIdle == m_eResourceState[iResource]) ? 0 : 1);
    }

protected:
    enum eResourceState
    {
        eResourceStateBegin         = 0,
        eResourceIdle,
        eResourceBusy,
        eResourceStateEnd,
    };

protected:
    int CreateResource(int iResource)
    {
        m_eResourceState[iResource] = eResourceBusy;
        return 0;
    }

    int DestroyResource(int iResource)
    {
        m_eResourceState[iResource] = eResourceIdle;
        return 0;
    }

private:

    T_TYPE  m_cResource[tiResourceNumber];

    eResourceState  m_eResourceState[tiResourceNumber];

    CMutex  m_cMutex;
};

}

#endif

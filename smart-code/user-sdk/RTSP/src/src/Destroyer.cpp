#include "../inc/Destroyer.h"
#include "../inc/Utility.h"

namespace   ApplicationLayer
{

CDestroyer::CDestroyer()
{
    m_lsDestroyer.clear();
}

CDestroyer::~CDestroyer() {}


int CDestroyer::Start()
{
    if (RET_CHECK_FAIL(m_cDestroyProxy.Register()))
    {
        return RET_FAIL;
    }

    if (0 != m_cAsyncNotifyDestroy.Start(this))
    {
        return RET_FAIL;
    }

    return RET_SUCCESS;
}

int CDestroyer::Stop()
{
    m_cAsyncNotifyDestroy.Stop();
    m_cDestroyProxy.UnRegister();
    return RET_SUCCESS;
}

int CDestroyer::Register(eDestroyResourceType eType, IDestroy *pDestroy)
{
    DestroyResourceTuple                    resource;
    resource.get<eDestroyResourceTupleType>() = eType;
    resource.get<eDestroyResourceTupleObject>() = pDestroy;
    m_lsDestroyer.push_back(resource);
    return RET_SUCCESS;
}

int CDestroyer::UnRegister(eDestroyResourceType eType)
{
    for (ListDestroyResource::iterator iter = m_lsDestroyer.begin(); iter != m_lsDestroyer.end(); ++iter)
    {
        if (eType == (*iter).get<eDestroyResourceTupleType>())
        {
            m_lsDestroyer.erase(iter);
            return RET_SUCCESS;
        }
    }

    return RET_FAIL;
}

CDestroyProxy &CDestroyer::GetProxy()
{
    return m_cDestroyProxy;
}

int CDestroyer::DestroyResource(DestroyParameter &para)
{
    m_cAsyncNotifyDestroy.Notify(para);
    return RET_SUCCESS;
}

int CDestroyer::Notify(DestroyParameter &para)
{
    for (ListDestroyResource::iterator iter = m_lsDestroyer.begin(); iter != m_lsDestroyer.end(); ++iter)
    {
        if (para.eType == (*iter).get<eDestroyResourceTupleType>())
        {
            (*iter).get<eDestroyResourceTupleObject>()->Destroy(para);
            return RET_SUCCESS;
        }
    }

    return RET_FAIL;
}

}

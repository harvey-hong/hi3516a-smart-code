#include "../inc/DestroyProxy.h"
#include "../inc/GlobalObject.h"

namespace   ApplicationLayer
{

CDestroyProxy::CDestroyProxy() {}

CDestroyProxy::~CDestroyProxy() {}

int CDestroyProxy::Register()
{
    TSingletons<CGlobalObject>::Instance().Destroyer().Register(eDestroyResourceReal, &m_cRealStreamDestroy);
    return RET_SUCCESS;
}

int CDestroyProxy::UnRegister()
{
    TSingletons<CGlobalObject>::Instance().Destroyer().UnRegister(eDestroyResourceReal);
    return RET_SUCCESS;
}

CRealStreamDestroy &CDestroyProxy::GetRealStreamDestroy()
{
    return m_cRealStreamDestroy;
}

}

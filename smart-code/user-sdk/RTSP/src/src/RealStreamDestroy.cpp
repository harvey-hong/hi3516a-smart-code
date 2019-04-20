#include "../inc/RealStreamDestroy.h"
#include "../inc/GlobalObject.h"

namespace   ApplicationLayer
{

CRealStreamDestroy::CRealStreamDestroy()
{
    memset(&m_cParameter, 0, sizeof(m_cParameter));
}

CRealStreamDestroy::~CRealStreamDestroy() {}

int CRealStreamDestroy::Destroy(DestroyParameter &para)
{
    return RET_SUCCESS;
}

}

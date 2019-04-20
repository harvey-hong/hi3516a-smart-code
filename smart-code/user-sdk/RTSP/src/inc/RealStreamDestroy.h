#ifndef REAL_STREAM_DESTROY_H

#define REAL_STREAM_DESTROY_H

#include "./InternalCommon.h"
#include "./interface/IDestroyer.h"

namespace   ApplicationLayer
{
class CRealStreamDestroy : public IDestroy
{
public:
    CRealStreamDestroy();
    ~CRealStreamDestroy();
public:
    int Destroy(DestroyParameter &para);
private:
    DestroyParameter    m_cParameter;
};

}

#endif

#ifndef DESTROY_PROXY_H

#define DESTROY_PROXY_H

#include "./InternalCommon.h"
#include "./RealStreamDestroy.h"

namespace   ApplicationLayer
{
class CDestroyProxy
{
public:
    CDestroyProxy();
    ~CDestroyProxy();
public:
    int Register();                                                                 //ע��
    int UnRegister();                                                               //ע��
    CRealStreamDestroy &GetRealStreamDestroy();                                     //��ȡʵʱ��������
protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CDestroyProxy);
private:
    CRealStreamDestroy          m_cRealStreamDestroy;                               //ʵʱ��������
};

}

#endif

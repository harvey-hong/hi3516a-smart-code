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
    int Register();                                                                 //注册
    int UnRegister();                                                               //注销
    CRealStreamDestroy &GetRealStreamDestroy();                                     //获取实时流销毁器
protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CDestroyProxy);
private:
    CRealStreamDestroy          m_cRealStreamDestroy;                               //实时流销毁器
};

}

#endif

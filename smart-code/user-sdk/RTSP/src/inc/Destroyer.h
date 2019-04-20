#ifndef DESTROYER_H

#define DESTROYER_H

#include "./InternalCommon.h"
#include "./interface/IDestroyer.h"
#include "./template/TAsyncNotify.h"
#include "./template/TTuple.h"
#include "./DestroyProxy.h"
#include "InternalCommon.h" 
namespace   ApplicationLayer
{
class CDestroyer : public IDestroyer
{
public:
    CDestroyer();
    ~CDestroyer();
public:
    int Start();                                                                                            //启动
    int Stop();                                                                                             //停止
    int Register(eDestroyResourceType eType, IDestroy *pDestroy);                                           //注册销毁器与类型
    int UnRegister(eDestroyResourceType eType);                                                             //注销销毁器与类型
    int DestroyResource(DestroyParameter &para);                                                            //销毁资源
    CDestroyProxy &GetProxy();                                                                              //获取销毁器代理
public:
    int Notify(DestroyParameter &para);                                                                     //通知销毁资源
protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CDestroyer);
private:
    //异步通知销毁器
    ApplicationLayer::TAsyncNotify<CDestroyer, DestroyParameter>  m_cAsyncNotifyDestroy;
    CDestroyProxy           m_cDestroyProxy;                                                                //!< 销毁器代理
    /*!
    *  @enum    eDestroyResourceTuple
    *  @brief   销毁器元组类型定义
    */
    enum eDestroyResourceTuple
    {
        eDestroyResourceTupleType                   = 0,                                                    //!< 销毁器类型
        eDestroyResourceTupleObject,                                                                        //!< 销毁器对象
    };
    //销毁器信息
    typedef ApplicationLayer::TTuple<eDestroyResourceType, IDestroy *>  DestroyResourceTuple;
    //销毁器表
    typedef list<DestroyResourceTuple>  ListDestroyResource;
    ListDestroyResource         m_lsDestroyer;
};

}

#endif

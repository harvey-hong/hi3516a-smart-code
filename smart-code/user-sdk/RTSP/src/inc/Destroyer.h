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
    int Start();                                                                                            //����
    int Stop();                                                                                             //ֹͣ
    int Register(eDestroyResourceType eType, IDestroy *pDestroy);                                           //ע��������������
    int UnRegister(eDestroyResourceType eType);                                                             //ע��������������
    int DestroyResource(DestroyParameter &para);                                                            //������Դ
    CDestroyProxy &GetProxy();                                                                              //��ȡ����������
public:
    int Notify(DestroyParameter &para);                                                                     //֪ͨ������Դ
protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CDestroyer);
private:
    //�첽֪ͨ������
    ApplicationLayer::TAsyncNotify<CDestroyer, DestroyParameter>  m_cAsyncNotifyDestroy;
    CDestroyProxy           m_cDestroyProxy;                                                                //!< ����������
    /*!
    *  @enum    eDestroyResourceTuple
    *  @brief   ������Ԫ�����Ͷ���
    */
    enum eDestroyResourceTuple
    {
        eDestroyResourceTupleType                   = 0,                                                    //!< ����������
        eDestroyResourceTupleObject,                                                                        //!< ����������
    };
    //��������Ϣ
    typedef ApplicationLayer::TTuple<eDestroyResourceType, IDestroy *>  DestroyResourceTuple;
    //��������
    typedef list<DestroyResourceTuple>  ListDestroyResource;
    ListDestroyResource         m_lsDestroyer;
};

}

#endif

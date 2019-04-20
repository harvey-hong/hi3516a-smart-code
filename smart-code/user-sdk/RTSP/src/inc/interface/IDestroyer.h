#ifndef IF_DESTROYER_H

#define IF_DESTROYER_H

#include "../InternalCommon.h"

namespace   ApplicationLayer
{

/*!
*  @enum    eDestroyResourceType
*  @brief   ������Դ���Ͷ���
*/
enum eDestroyResourceType
{
    eDestroyResourceTypeBegin                       = 0,                                                    //!< ��ʼֵ
    eDestroyResourceReal,                                                                                   //!< ʵʱ��
    eDestroyResourceHistory,                                                                                //!< ��ʷ��
    eDestroyResourceTypeEnd,                                                                                //!< ����ֵ
};

/*!
* \struct tagDestroyParameter
* \brief ���ٲ���
*/
typedef struct tagDestroyParameter
{
    eDestroyResourceType    eType;                                                                          //!< ��Դ����
    DWORD               dwFunctionIndex;                                                                    //!< ���ܶ�������
    DWORD               dwMediaFlag;                                                                        //!< ý���ʶ
    DWORD               dwUserData[5];                                                                      //!< �û�����
} DestroyParameter, *LPDestroyParameter;

Interface IDestroy
{
    virtual int Destroy(DestroyParameter & para) = 0;                                                       //������Դ
};

Interface IDestroyer
{
    virtual int Start() = 0;                                                                                //����
    virtual int Stop() = 0;                                                                                 //ֹͣ
    virtual int Register(eDestroyResourceType eType, IDestroy * pDestroy) = 0;                              //ע��������������
    virtual int UnRegister(eDestroyResourceType eType) = 0;                                                 //ע��������������
    virtual int DestroyResource(DestroyParameter & para) = 0;                                               //������Դ
};

}

#endif

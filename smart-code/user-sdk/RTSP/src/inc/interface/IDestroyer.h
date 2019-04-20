#ifndef IF_DESTROYER_H

#define IF_DESTROYER_H

#include "../InternalCommon.h"

namespace   ApplicationLayer
{

/*!
*  @enum    eDestroyResourceType
*  @brief   销毁资源类型定义
*/
enum eDestroyResourceType
{
    eDestroyResourceTypeBegin                       = 0,                                                    //!< 起始值
    eDestroyResourceReal,                                                                                   //!< 实时流
    eDestroyResourceHistory,                                                                                //!< 历史流
    eDestroyResourceTypeEnd,                                                                                //!< 结束值
};

/*!
* \struct tagDestroyParameter
* \brief 销毁参数
*/
typedef struct tagDestroyParameter
{
    eDestroyResourceType    eType;                                                                          //!< 资源类型
    DWORD               dwFunctionIndex;                                                                    //!< 功能对象索引
    DWORD               dwMediaFlag;                                                                        //!< 媒体标识
    DWORD               dwUserData[5];                                                                      //!< 用户数据
} DestroyParameter, *LPDestroyParameter;

Interface IDestroy
{
    virtual int Destroy(DestroyParameter & para) = 0;                                                       //销毁资源
};

Interface IDestroyer
{
    virtual int Start() = 0;                                                                                //启动
    virtual int Stop() = 0;                                                                                 //停止
    virtual int Register(eDestroyResourceType eType, IDestroy * pDestroy) = 0;                              //注册销毁器与类型
    virtual int UnRegister(eDestroyResourceType eType) = 0;                                                 //注销销毁器与类型
    virtual int DestroyResource(DestroyParameter & para) = 0;                                               //销毁资源
};

}

#endif

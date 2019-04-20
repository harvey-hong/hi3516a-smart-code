#ifndef GLOBAL_OBJECT_H

#define GLOBAL_OBJECT_H


#include "./InternalCommon.h"
#include "./template/TSingletons.h"
#include "./template/TResourceManager.h"
#include "./HYRtspCallBackFunc.h"

#include "./HYRtspService.h"
#include "./Destroyer.h"

#include "./RtspSessionIdManager.h"
#include "./RealStreamManager.h"

using namespace ApplicationLayer;

class CGlobalObject
{
public:
    CGlobalObject();
    virtual ~CGlobalObject();
public:
    CHYPrivateService &PrivateService();                                                //获取私有协议服务
    CDestroyer &Destroyer();                                                            //获取销毁器对象
    INT32 &RtspServerHandle();                                                          // 获取RTSP服务器句柄
    CRtspSessionIdManager &RtspSessionMan();                                            // RTSP会话ID管理器
    CRealStreamManager &RealStreamMan();                                                // 实时流管理器
    DWORD &UserID();                                                                    //获取用户ID接口

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CGlobalObject);
private:
    CHYPrivateService   m_cPrivateService;                                              //!< 私有协议服务
    CDestroyer      m_cDestroyer;                                                       //!< 销毁器

    //--CPrivateConfigureInterface m_cPrivateConfigureInterface;                            //!< 读写更新配置接口
    //--CPrivateStreamCaptureInterface m_cPrivateStreamCaptureInterface;                    //!< 实时流接口
    //--CPrivateUserActionInterface m_cPrivateUserActionInterface;                          //!< 用户动作接口
    INT32 m_hRtspServer;                                                                //!< RTSP服务器标识
    CRtspSessionIdManager m_cRtspSessionIdMan;                                          //!< RTSP会话Id管理器
    CRealStreamManager m_cRealStreamMan;                                                //!< 实时流管理器
    DWORD m_dwUserID;                                                                   //!< 用户Id

};

#endif

#include "../inc/GlobalObject.h"

CGlobalObject::CGlobalObject()
{
}

CGlobalObject::~CGlobalObject()
{
}

/*
* @brief
*   获取私有协议服务
* @return
*   返回对象
* @note
*   接口类型: 阻塞式
*/
CHYPrivateService &CGlobalObject::PrivateService()
{
    return m_cPrivateService;
}

/*
* @brief
*   获取销毁器对象
* @return
*   返回对象
* @note
*   接口类型: 阻塞式
*/
CDestroyer &CGlobalObject::Destroyer()
{
    return m_cDestroyer;
}

/*
* @brief
*   获取读写更新配置接口
* @return
*   返回对象
* @note
*   接口类型: 阻塞式
*/
/*
CPrivateConfigureInterface& CGlobalObject::PrivateConfigureInterface()
{
    return m_cPrivateConfigureInterface;
}
*/
/*
* @brief
*   获取用户动作接口
* @return
*   返回对象
* @note
*   接口类型: 阻塞式
*/
//CPrivateUserActionInterface& CGlobalObject::PrivateUserActionInterface()
//{
//  return m_cPrivateUserActionInterface;
//}


/*
* @brief
*   获取实时流接口
* @return
*   返回对象
* @note
*   接口类型: 阻塞式
*/
//CPrivateStreamCaptureInterface& CGlobalObject::PrivateStreamCaptureInterface()
//{
//  return m_cPrivateStreamCaptureInterface;
//}


/*
* @brief
*  获取RTSP服务器句柄
* @return
*  返回对象
* @note
*  接口类型: 阻塞式
*/
INT32 &CGlobalObject::RtspServerHandle()
{
    return m_hRtspServer;
}

/*
* @brief
*  获取RTSP会话ID管理器
* @return
*  返回对象
* @note
*  接口类型: 阻塞式
*/
CRtspSessionIdManager &CGlobalObject::RtspSessionMan()
{
    return m_cRtspSessionIdMan;
}


/*
* @brief
*  获取实时流管理器
* @return
*  返回对象
* @note
*  接口类型: 阻塞式
*/
CRealStreamManager &CGlobalObject::RealStreamMan()
{
    return m_cRealStreamMan;
}

/*
* @brief
*  获取用户ID接口
* @return
*  返回对象
* @note
*  接口类型: 阻塞式
*/
DWORD &CGlobalObject::UserID()
{
    return m_dwUserID;
}


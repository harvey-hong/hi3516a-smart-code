/*!
* @file
*  RtspSessionIdManager.h
* @brief
*  Rtsp会话Id管理器
* @author
*  Cheng Yanfang
* @date
*  2010年10月21日
* @version
*  1.0.0
*/

#ifndef RTSP_SESSION_ID_MANAGER_H

#define RTSP_SESSION_ID_MANAGER_H

#include "./InternalCommon.h"
#include "./HYRtspCommon.h"
#include "./Property.h"
#include "./template/TResourceManager.h"
#include "./interface/IRtspStream.h"

#include "ws_utility_api.h"
using namespace ws_utility;

namespace   ApplicationLayer
{

// 最大RTSP会话个数
#define MAX_RTSP_SESSION_NUM     (MAX_CHANNEL_NUMBER)

typedef struct tagSessionStreamPair
{
    int nSessionId;             // 会话Id
    eRtspStreamType eStreamType;// 流类型
    int nStreamIndex;           // 流资源索引
    IRtspStream *pStream;       // rtsp流

} SessionStreamPair, *LPSessionStreamPair;

/*!
* \class CRtspSessionIdManager
* \brief Rtsp会话Id管理器
*/
class CRtspSessionIdManager
{
public:
    CRtspSessionIdManager();
    ~CRtspSessionIdManager();
    SessionStreamPair operator[](int iIndex);
public:
    // 初始化
    int Initialize();
    // 销毁
    int Destroy();
    // 添加会话Id
    int AddSessionId(int nSessionId, eRtspStreamType eStreamType);
    // 移除会话Id
    int RemoveSessionId(int nSessionId);
    // 获取流
    int GetStream(int nSessionId, IRtspStream **pStream);

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRtspSessionIdManager);

private:
    // 会话Id守卫
    CMutex m_cSessIdMutex;
    // 会话Id管理
    ApplicationLayer::TResourceManager<SessionStreamPair, MAX_RTSP_SESSION_NUM> m_cRtspSessionManager;
};
}

#endif

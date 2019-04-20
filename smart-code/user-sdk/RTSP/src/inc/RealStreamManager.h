#ifndef REAL_STREAM_MANAGER_H

#define REAL_STREAM_MANAGER_H

#include "./InternalCommon.h"
#include "./Property.h"
#include "./template/TResourceManager.h"
#include "./RealStream.h"

#include "ws_utility_api.h"
using namespace ws_utility;
using namespace ApplicationLayer ;

namespace   ApplicationLayer
{

class CRealStreamManager
{
public:
    CRealStreamManager();
    ~CRealStreamManager();
    CRealStream    &operator[](int iIndex);
public:
    //初始化
    int Initialize();
    //销毁
    int Destroy();

    //创建流
    int CreateStream(int &iResource);

    //销毁流
    int DestroyStream(int iResource);

    //获取资源
    int Stream(int iResource, CRealStream **pStream);

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRealStreamManager);

private:
    //实时流管理器守卫
    CMutex  m_cMutex;
    //实时流管理
    ApplicationLayer::TResourceManager<CRealStream, MAX_CHANNEL_NUMBER>    m_cRealStreamManager;
};

}

#endif



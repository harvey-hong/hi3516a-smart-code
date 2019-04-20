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
    //��ʼ��
    int Initialize();
    //����
    int Destroy();

    //������
    int CreateStream(int &iResource);

    //������
    int DestroyStream(int iResource);

    //��ȡ��Դ
    int Stream(int iResource, CRealStream **pStream);

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRealStreamManager);

private:
    //ʵʱ������������
    CMutex  m_cMutex;
    //ʵʱ������
    ApplicationLayer::TResourceManager<CRealStream, MAX_CHANNEL_NUMBER>    m_cRealStreamManager;
};

}

#endif



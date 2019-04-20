/*!
* @file
*  RtspSessionIdManager.h
* @brief
*  Rtsp�ỰId������
* @author
*  Cheng Yanfang
* @date
*  2010��10��21��
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

// ���RTSP�Ự����
#define MAX_RTSP_SESSION_NUM     (MAX_CHANNEL_NUMBER)

typedef struct tagSessionStreamPair
{
    int nSessionId;             // �ỰId
    eRtspStreamType eStreamType;// ������
    int nStreamIndex;           // ����Դ����
    IRtspStream *pStream;       // rtsp��

} SessionStreamPair, *LPSessionStreamPair;

/*!
* \class CRtspSessionIdManager
* \brief Rtsp�ỰId������
*/
class CRtspSessionIdManager
{
public:
    CRtspSessionIdManager();
    ~CRtspSessionIdManager();
    SessionStreamPair operator[](int iIndex);
public:
    // ��ʼ��
    int Initialize();
    // ����
    int Destroy();
    // ��ӻỰId
    int AddSessionId(int nSessionId, eRtspStreamType eStreamType);
    // �Ƴ��ỰId
    int RemoveSessionId(int nSessionId);
    // ��ȡ��
    int GetStream(int nSessionId, IRtspStream **pStream);

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CRtspSessionIdManager);

private:
    // �ỰId����
    CMutex m_cSessIdMutex;
    // �ỰId����
    ApplicationLayer::TResourceManager<SessionStreamPair, MAX_RTSP_SESSION_NUM> m_cRtspSessionManager;
};
}

#endif

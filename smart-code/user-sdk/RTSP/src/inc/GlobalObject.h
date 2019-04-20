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
    CHYPrivateService &PrivateService();                                                //��ȡ˽��Э�����
    CDestroyer &Destroyer();                                                            //��ȡ����������
    INT32 &RtspServerHandle();                                                          // ��ȡRTSP���������
    CRtspSessionIdManager &RtspSessionMan();                                            // RTSP�ỰID������
    CRealStreamManager &RealStreamMan();                                                // ʵʱ��������
    DWORD &UserID();                                                                    //��ȡ�û�ID�ӿ�

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CGlobalObject);
private:
    CHYPrivateService   m_cPrivateService;                                              //!< ˽��Э�����
    CDestroyer      m_cDestroyer;                                                       //!< ������

    //--CPrivateConfigureInterface m_cPrivateConfigureInterface;                            //!< ��д�������ýӿ�
    //--CPrivateStreamCaptureInterface m_cPrivateStreamCaptureInterface;                    //!< ʵʱ���ӿ�
    //--CPrivateUserActionInterface m_cPrivateUserActionInterface;                          //!< �û������ӿ�
    INT32 m_hRtspServer;                                                                //!< RTSP��������ʶ
    CRtspSessionIdManager m_cRtspSessionIdMan;                                          //!< RTSP�ỰId������
    CRealStreamManager m_cRealStreamMan;                                                //!< ʵʱ��������
    DWORD m_dwUserID;                                                                   //!< �û�Id

};

#endif

#ifndef HY_RTSP_SERVICE_H
#define HY_RTSP_SERVICE_H


#include "./InternalCommon.h"
#include "./template/TValuePair.h"

using namespace ApplicationLayer;

class CHYPrivateService
{
public:
    CHYPrivateService();
    virtual ~CHYPrivateService();
public:
    int Start();                                                                                //!< 启动服务
    int Stop();                                                                                 //!< 停止服务
    int GetVersion(char *&version);                                                             //!< 获取版本信息
    int SetStatus(int nStatus);                                                                 //!< 完成启动服务置为1；进入停止服务置为0
    int GetStatus(int &nStatus);                                                                //!< 获取启动、停止服务状态
public:
    static INT32 RtspAddSessionCB(INT32 nClientId, INT32 nSesseionId, INT32 nEvent, void *pArg);//!< RTSPÌí¼Ó»á»°»Øµ÷
    static INT32 RtspStreamEventCB(INT32 nClientId, INT32 nSesseionId, INT32 nEvent, void *pArg);//!< RTSPÁ÷ÊÂ¼þ»Øµ÷
    static INT32 ClientConnectionCB(INT32 nConnectFlag, BYTE *sessionName);                     //!< ¿Í»§¶ËÁ¬½Ó»Øµ÷
    /*static */int InitializeRtspParam();                                                           //!< ³õÊ¼»¯rtsp¾²Ì¬³ÉÔ±

    static int ProcessStartClientEvent(int nClientId, int nSessionId, void *pParam);

    static int ProcessDestroyClientEvent(int nClientId, int nSessionId, void *pParam);

    static int ProcessPlayEvent(int nSessionId, void *pParam);

    static int ProcessPauseEvent(int nSeesionId, void *pParam);

    static int ProcessStopEvent(int nSessionId, void *pParam);

    static int ProcessRemoveSessionEvent(int nSessionId, void *pParam);

    static int ProcessRemoveSessionEventByStop(int nSessionId, void *pParam);

    int Login();

    int Logout();

protected:
    DISABLE_COPY_CAPABILITY_OBJECT(CHYPrivateService);
protected:
    int Initialize();                                                                               //!< ³õÊ¼»¯
    int Destroy();                                                                                  //!< Ïú»Ù
  	int GetServerPort(DWORD &dwCommand, DWORD &dwMediaTCP, DWORD &dwMediaRTP, DWORD &dwMediaRTSP);
private:
    int                             m_iRealStreamManager;                                           //!< ÊµÊ±Á÷¹ÜÀíÆ÷
    int                             m_nStatus;                                                      //!< Æô¶¯¡¢Í£Ö¹×´Ì¬

};

#endif

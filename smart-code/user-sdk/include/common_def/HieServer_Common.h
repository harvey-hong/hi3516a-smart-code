#ifndef HIE_SERVER_COMMON_H

#define HIE_SERVER_COMMON_H

//////////////////////////////////////////////////////////////////////////
//�궨��
//////////////////////////////////////////////////////////////////////////
//HieServerͨ����Ϣ�����ļ�

//��������

/** @brief ���                                                                         */
#define IN

/** @brief ����                                                                         */
#define OUT

/** @brief �����                                                                       */
#define IN_OUT

/** @brief ʵʱ�����ͻ���                                                             */
#define REAL_STREAM_LIMIT                   (8)

/** @brief ���������ͻ���                                                             */
#define VOICE_STREAM_LIMIT                  REAL_STREAM_LIMIT

/** @brief �û�������                                                                   */
#define USERNAME_LEN                        (32)

/** @brief ����ʱ�䳤��                                                                 */
#define DATE_TIME_LEN                       (15)

/** @brief �û����볤��                                                                 */
#define USERPASS_LEN                        (32)

/** @brief �豸ID����                                                                   */
#define MAX_DEVICE_ID_LEN                   (32)

/** @brief IP��ַ����(��������)                                                         */
#define IP_ADDRESS_LEN                      (16)

/** @brief MAC��ַ����(��������)                                                        */
#define MAC_ADDRESS_LEN                     (18)

/** @brief MAC��ַ�����Ƴ���                                                            */
#define MAC_BINARY_ADDRESS_LEN              (6)

/** @brief �汾��Ϣ����(��������)                                                       */
#define VERSION_INFO_LEN                    (20)

/** @brief ����ļ�������                                                               */
#define MAX_FILENAME                        (256)

/** @brief ��������(��������)                                                           */
#define DOMAIN_ADDRESS_LEN                  (256)

/** @brief ��ַ����(��������)                                                                       */
#define MAX_ADDRESS_LEN             (DOMAIN_ADDRESS_LEN)

/** @brief Ĭ�ϱ����ֶθ���                                                             */
#define DEF_RESERVE_NUM                     (3)

/** @brief ������Ϣ��󳤶�                                                             */
#define MAX_CFG_LEN                         (128 * 1024 * 2)

/** @brief ������Ϣ��󳤶�                                                             */
#define MAX_DESCRIPTION_INFO_LEN            (100)

/** @brief ��չ����Method����󳤶�                                                         */
#define MAX_METHOD_LEN                      (32)

/** @brief ��չ����Answer����󳤶�                                                         */
#define MAX_ANSWER_LEN                      (32)

/** @brief ��չ��������豸���ͳ���                                                         */
#define MAX_TYPE_LEN                        (128)

/** @brief ��չ����Usage����󳤶�                                                          */
#define MAX_USAGE_LEN                       (128)

/** @brief ��չ��Ϣ����󳤶�                                                               */
#define MAX_EX_INFO_LEN                     (32 * 1024)

/** @brief ����������Ϣ����󳤶�                                                           */
#define MAX_ERROE_MESSAGE_LEN               (256)

/** @brief Hxht����ʱ�䳤��                                                                 */
#define HXHT_DATA_TIME_LEN                  (32)

/** @brief Hxht�����ͳ���                                                                   */
#define HXHT_STREAM_TYPE_LEN                (32)

/** @brief Hxht��ͨ�ַ�������                                                               */
#define HXHT_COMMON_STRING_LEN              (32)

/** @brief Hxht�����ʱ����Ϣ����                                                           */
#define MAX_STREAM_TIME_INFO_ITEN           (50)

/** @brief Hxht���¼��Ƭ�θ���                                                             */
#define MAX_SEGMENT_ITEM                    (50)

/** @brief Hxht���Ԥ�õ����                                                               */
#define MAX_PRESET_POINT_NUM                (128)

/** @brief Hxht��������ظ���                                                             */
#define MAX_AUX_SWITCH_NUM                  (16)

/** @brief Hxht���֧�ֵ���̨��������Ÿ���                                                 */
#define MAX_SUPPORT_OP_CMD_NUM              (64)

/** @brief Hxht���ʮ������485���ݵĳ���                                                    */
#define MAX_485_DATA_LEN                    (128)

/** @brief Hxht֧�ֵ����������ѯ��                                                         */
#define MAX_QUERY_SUPPORT_NUM               (9)

/** @brief Hxht��������Ƴ���                                                             */
#define MAX_SUPPORT_NAME_LEN                (128)

/** @brief Hxht���ʱ��ƻ��ڵ���                                                           */
#define HXHT_MAX_ITEM_COUNT                 (32)

/** @brief Hxht����ַ�������                                                               */
#define HXHT_MAX_XML_STRING_LEN             (180)

/** @brief ��������������ͨ����                                           */
#define MAX_DEC_CHANNEL_NUMBER      (64)

/** @brief ���ſ��Ʋ�������                                                 */
#define MAX_PLAY_CONTROL_PARAMETER  (5)

/** @brief ������ͨ����ת��ƵԴ����                                                                           */
#define MAX_DECODER_CHANNEL_SOURCE  (16)

/** @brief ��Ļ���Ʋ�������                                                 */
#define MAX_SCREEN_CONTROL_PARAMETER    (5)

/** @brief ����������������                                                                       */
#define MAX_DISPLAY_SCREEN_NUMBER   (64)

/** @brief LOGOͼƬ��������                                                 */
#define MAX_LOGO_PICTURE_PARAMETER  (5)

/** @brief OSD�ı��ַ���                                                    */
#define MAX_OSD_TEXT_STRING_LENGTH  (64)

/** @brief RTSPԴ�ַ���                                                 */
#define MAX_RTSP_SOURCE_STRING_LENGTH   (128)

//////////////////////////////////////////////////////////////////////////
//��ʷ��֡�궨��
//////////////////////////////////////////////////////////////////////////

/** @brief ��ʷ���쳣����                                                               */
#define HISTORY_STREAM_EXCEPTION    (0x01000000)

/** @brief ��ʷ���л�֡�궨��                                                           */
#define HISTORY_STREAM_SWITCH_FRAME (0x02000000)

/** @brief ��ʷ�������µ�ʱ��Ƭ                                                         */
#define HISTORY_STREAM_TIME_JUMP    (0x03000000)

/** @brief ��ʷ������֡�궨��                                                           */
#define HISTORY_STREAM_TIME_END     (0x04000000)

/** @brief ��ʷ�����ݲ�ѯ���                                                           */
#define HISTORY_STREAM_TIME_CURR    (0x05000000)

//////////////////////////////////////////////////////////////////////////
//Զ���¼�����
//////////////////////////////////////////////////////////////////////////

/** @brief �����¼�                                                                     */
#define USEREVENT_ALARM_NOTICE          (0x00000001)

/** @brief ������ʧ,����Ͽ�                                                            */
#define USEREVENT_HEARTBEAT_LOST        (0x00000002)

/** @brief ���������ɹ�                                                                 */
#define USEREVENT_NET_RECOVER           (0x00000004)

/** @brief Զ���û��Ͽ�                                                                 */
#define USEREVENT_USER_DISCONNECT       (0x00000008)

/** @brief Զ����ý��Ͽ�                                                               */
#define USEREVENT_STREAM_DISCONNECT     (0x00000010)

/** @brief Ӳ��������¼�                                                               */
#define USEREVENT_DISKGROUP_MANAGE      (0x00000020)

/** @brief ��ʷ���¼�֪ͨ                                                               */
#define USEREVENT_HISTORYSTREAM_NOTICE  (0x00000040)

/** @brief ʵʱ����������ID֪ͨ                                                         */
#define USEREVENT_REALSTREAM_STARTLINK  (0x00000080)

/** @brief ʵʱ��ֹͣ����ID֪ͨ                                                         */
#define USEREVENT_REALSTREAM_STOPLINK   (0x00000100)

/** @brief ��������������ID֪ͨ                                                         */
#define USEREVENT_VOICESTREAM_STARTLINK (0x00000200)

/** @brief ������ֹͣ����ID֪ͨ                                                         */
#define USEREVENT_VOICESTREAM_STOPLINK  (0x00000400)

/** @brief ��ʷ�������¼�֪ͨ                                                           */
#define USEREVENT_HISTORYSTREAM_DESTROYLINK     (0X00000800)

/** @brief ��ʷ�������¼�֪ͨ                                                           */
#define USEREVENT_HISTORYSTREAM_STARTLINK       (0X00001000)

/** @brief ��ʷ��ֹͣ�¼�֪ͨ                                                           */
#define USEREVENT_HISTORYSTREAM_STOPLINK        (0X00002000)

/** @brief ��ʷ�������¼�֪ͨ                                                           */
#define USEREVENT_HISTORYSTREAM_CREATELINK      (0X00004000)


//////////////////////////////////////////////////////////////////////////
//��ʷ��¼�����ͺ궨��
//////////////////////////////////////////////////////////////////////////
/** @brief ��ͨ¼������                                                                             */
#define GENERAL_RECORD              (0X00000001)

/** @brief �ֶ�¼������                                                                             */
#define MANUAL_RECORD               (0X00000002)

/** @brief ����¼������                                                                             */
#define ALARM_RECORD                (0X00000004)

/** @brief �ƶ�¼������                                                                             */
#define MOTION_RECORD               (0X00000008)

/** @brief ����¼������                                                                             */
#define ALL_STREAM_MEDIA			(GENERAL_RECORD | MANUAL_RECORD | MOTION_RECORD | ALARM_RECORD)


#define  PrivateProtocolVersion_100   (10000)  /* version 1.0.0 == 1*10000 + 0*100 + 0*1 */
#define  PrivateProtocolVersion_101   (10001)  /* version 1.0.1 == 1*10000 + 0*100 + 1*1 */

//////////////////////////////////////////////////////////////////////////
//��������
//////////////////////////////////////////////////////////////////////////
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
//typedef void *HANDLE;					// change by linhh 20160508
#define	HANDLE	void*
//////////////////////////////////////////////////////////////////////////
//ö��
//////////////////////////////////////////////////////////////////////////

/* hzg added 20170410 for async control Private Protocol Server start */
enum eCmdControlPrivateServer
{
    WS_CMD_Begin = 0,
    WS_CMD_StartPrivateServer,              /*!< ����˽��Э�����   */
    WS_CMD_StopPrivateServer,               /*!< ֹͣ˽��Э�����   */
    WS_CMD_RestartPrivateServer,          /*!< ����˽��Э�����   */
};
/* hzg added 20170410 for async control Private Protocol Server end */

typedef struct tagPrivateServerCmdCtrlList
{
    eCmdControlPrivateServer eCmdCtrl;            /*!< һ��Cmd                       */
    struct tagPrivateServerCmdCtrlList *pNext;   /*!< ָ����һ��Cmd     */
} PrivateServerCmdCtrlList, *LPPrivateServerCmdCtrlList;
/* hzg added 20170410 for async control Private Protocol Server stop */

#ifndef DEF_ENUM_ALERT_TYPE
#define DEF_ENUM_ALERT_TYPE

/*!
*  @enum    eAlertType
*  @brief   �������쳣��������
*/
enum eAlertType
{
    ALERT_ALARMIN,              /*!< ��������                           */
    ALERT_MOTION,               /*!< �ƶ����                           */
    ALERT_ENCODEERROR,          /*!< �����쳣                           */
    ALERT_DISKERROR,            /*!< Ӳ�̴���                           */
    ALERT_DISKFULL,             /*!< Ӳ����                             */
    ALERT_IPCONFLICT,           /*!< IP��ͻ                             */
    ALERT_ILLEGEACCESS,         /*!< �Ƿ�����                           */
    ALERT_RETICLEDISCONNECT,    /*!< ���߶�                             */
    ALERT_VIDEOLOST,            /*!< ��Ƶ��ʧ                           */
    ALERT_VIDEOEXCEPTION,       /*!< ��Ƶ�쳣                           */
    ALERT_DISKGROUP_ERROR,      /*!< �����쳣                           */
};

#endif//DEF_ENUM_ALERT_TYPE

/*!
*  @enum    eProtocolID
*  @brief   Э������
*/
enum eProtocolID
{
    eProtocolBegin = -1,    //Э�鿪ʼ

    eProtocolHYPrivate,     //˽��Э��
    eProtocolTideMobile,    //TideMobile�ֻ�Э��
	eProtocolMegaEyes,		//���Ż�ͨ��ȫ���ۣ�
    eProtocolRTSP,          //RTSPЭ��
    eProtocolONVIF,
    eProtocolHTTP,
    eProtocolDiscovery,
    eProtocolRTMP,          //RTMPЭ��
    eProtocolIPDetection,          //IP��ͻ������
    eProtocolPDNS,          //Private DNS client service
	eProtocolTutkP2P,       //TUTK P2P device service protocol
	eProtocolUPNP,       //UPNP device discover protocol
    eProtocolEnd,           //Э�����
};

/*!
*  @enum    eErrorValue
*  @brief   ����ֵ���ͣ�������Ӵ�����ʱ�����������ӣ�
*/
enum eErrorValue
{
    eErrorNone = 0,             /*!< �޴���                                 */
    eErrorFailed,               /*!< ʧ��                                   */
    eErrorNoInitializeSDK,      /*!< δ��ʼ��SDK                            */
    eErrorHandle,               /*!< �������                               */
    eErrorParameter,            /*!< ��������                               */
    eErrorMemory,               /*!< �ڴ����                               */
    eErrorSystemFailed,         /*!< ����ϵͳ����                           */
    eErrorNoIdleResource,       /*!< �޿�����Դ                             */
    eErrorTimeOut,              /*!< ��ʱ����                               */
    eErrorFunctionVersionLow,   /*!< ���ܰ汾���ڷ�����                     */
    eErrorFunctionVersionHigh,  /*!< ���ܰ汾���ڷ�����                     */
    eErrorTaskNoRun,            /*!< ����δ����                             */
    eErrorAlreadyRun,           /*!< �ظ�����                               */
    eErrorConnectFailed,        /*!< ����ʧ��                               */
    eErrorSessionDisconnect,    /*!< ���ӶϿ�                               */
    eErrorCommandSendFailed,    /*!< �����ʧ��                           */
    eErrorServerReject,         /*!< �������ܾ�                             */
    eErrorInterfaceUnset,       /*!< �ӿ�δ����                             */
    eErrorHYPrivate,            /*!< ˽��Э��ⲻ����                       */
    eErrorMegaEyes,             /*!< ȫ����Э��ⲻ����                     */
    eErrorFunction,             /*!< Э���к���������                       */
    eErrorUserName,             /*!< �û�������                             */
    eErrorUserPass,             /*!< �û��������                           */
    eErrorIPLimited,            /*!< �û�IP����                             */
    eErrorMACLimited,           /*!< ��MAC����                              */
    eErrorUserNumOverflow,      /*!< ��½�û�����                           */
    eErrorUserHeartBeat,        /*!< �û���������ʧ��                       */
    eErrorGetConfigurationPort, /*!< ��½ʱ��ȡ�˿�������Ϣʧ��             */
    eErrorServiceReseting,      /*!< �������������                         */
    eErrorHistoryStreamCreate,  /*!< ��ʷ��������ָ��ΪNULL                 */
    eErrorGetDataSize,          /*!< ��ȡ��ʷ���ݴ�С��ָ��ΪNULL           */
    eErrorHistoryQueryCreate,   /*!< ��ʷ��ѯ������ָ��ΪNULL               */
    eErrorHistoryQueryNext,     /*!< ��ʷ��ѯ��һ����ָ��ΪNULL             */
    eErrorTideMobile,           /*!< TideMobileЭ�鲻����                   */
    eErrorHxht,                 /*!< MegaEyesЭ�鲻����(Hxht�Ǹ�Э�鹫˾������) */
    eErrorRTSP,                 /*!< RTSPЭ�鲻����                         */
    eErrorONVIF,
    eErrorHTTP,
    eErrorRTMP,
    eErrorNoSupportCommand,     /*!< ��֧�ֵ�����                           */
    eErrorUnserialize,          /*!< �����л�ʧ��                           */
    eErrorNoSupportBandwith,	/*!<��֧�ִ������		*/
};

/*!
*  @enum    eConfigureType
*  @brief   ������Ϣ����
*/
enum eConfigureType
{
    eConfigureTypeBegin = 0,    /*!< ��ʼֵ                                 */
    eConfigureDevice,           /*!< �豸��Ϣ                               */
    eConfigureNetWork,          /*!< ������Ϣ                               */
    eConfigureManagerServer,    /*!< �����������Ϣ                         */
    eConfigureTime,             /*!< ʱ����Ϣ                               */
    eConfigureChannel,          /*!< ͨ����Ϣ                               */
    eConfigureCompression,      /*!< ѹ����Ϣ                               */
    eConfigureTypeEnd,          /*!< ����ֵ                                 */
};

 enum ePDNSActionType
{
    eGetDefultUserDomain = 0,   /* Get the default user domain name string userDomain-string.ipcpddns.com */
    eGetServerDomain = 1,         /* Get PDDNS server domain name string  : ipcpddns.com */
    eGetConnectionStatus = 2,   /* Get current connection status */
    eSetUserDomain = 3,            /* Set new user domain name string, and then get the result */

    eInvalidAction = 4,
};
/*!
*  @enum    eGetServerStateType
*  @brief   ��ȡ����״̬����
*/
enum eGetServerStateType
{
    eGetServerStateTypeBegin = 0,   /*!< ��ʼֵ                                 */
    eRealStreamState,           /*!< ʵʱ��״̬                             */
    eRemoteUser,                /*!< �û�״̬                               */
    eHistroyState,              /*!< ��ʷ��״̬                             */
    eGetServerStateTypeEnd,     /*!< ����ֵ                                 */
};

/*!
*  @enum    eManagerServer
*  @brief   �������������
*/
enum eManagerServerType
{
    eManagerServerTypeBegin = 0,    /*!< ��ʼֵ                                 */
    eManagerCenter,             /*!< ���Ĺ��������                         */
    eManagerMediaStream,        /*!< ��ý�������                           */
    eManagerStorage,            /*!< �洢������                             */
    eManagerAlarm,              /*!< ����������                             */
    eManagerServerTypeEnd,      /*!< ����ֵ                                 */
};

/*!
*  @enum    eRemoteUserState
*  @brief   �û�״̬����
*/
enum eRemoteUserState
{
    eRemoteUserStateBegin = 0,  /*!< ��ʼֵ                                 */
    eUserTimeOut,               /*!< ��ʱ(������ʱ)                         */
    eUserNetWorkError,          /*!< �����쳣                               */
    eRemoteUserStateEnd,        /*!< ����ֵ                                 */
};

/*!
*  @enum    eMediaCodeType
*  @brief   ��ý����������
*/
enum eMediaCodeType
{
    eMediaCodeTypeBegin = 0,    /*!< ��ʼֵ                                 */
    eMediaCodeMain,             /*!< ������                                 */
    eMediaCodeAssist,           /*!< ������                                 */
    eMediaCodeHDAssist,         /*!< ���帨����                             */
    eMediaCodeOnlyMain,
    eMediaCodecOnlyAssist,			//2ֻ������������Ƶ
    eMediaCodecOnlyMainAndAssist,	//2ͬʱ��������������������Ƶ
    eMediaCodeNewHisMain,
    eMediaCodeNewHisAssist,
    eMediaCodeTypeEnd,          /*!< ����ֵ                                 */
};

/*!
*  @enum    eStreamMediaType
*  @brief   ��ý������
*/
enum eStreamMediaType
{
    eStreamMediaTypeBegin = 0,  /*!< ��ʼֵ                                 */
    eMainVideoAndSound,         /*!< ����������Ƶ                           */
    eMainVideo,                 /*!< ��������Ƶ                             */
    eMainSound,                 /*!< ��������Ƶ                             */
    eAssistVideo,               /*!< ��������Ƶ                             */
    eAssistHDVideo,             /*!< ������������Ƶ                         */
    eAssistOnlyVideo,					// ֻ������������Ƶ
    eAssistAndMainOnlyVideo,			// ͬʱ��������������������Ƶ

    eMainNewHisVideoAndSound,       //������ ��ʷ����Ƶ
    eMainNewHisVideo,                       //������ ��ʷ��Ƶ
    eAssistNewHisVideo,                     //������ ��ʷ��Ƶ
    eStreamMediaTypeEnd,        /*!< ����ֵ                                 */
};

/*!
*  @enum    eHistoryStreamType
*  @brief   ��ʷ������
*/
enum eHistoryStreamType
{
    eHistoryStreamTypeBegin = 0,    /*!< ��ʼֵ                                 */
    eAllStreamMedia,            /*!< ������ý��                             */
    eGeneralRecord,             /*!< ��ͨ¼��                               */
    eManualRecord,              /*!< �ֶ�¼��                               */
    eMotionRecord,              /*!< �ƶ�¼��                               */
    eAlarmRecord,               /*!< ����¼��                               */
    eHistoryStreamTypeEnd,      /*!< ����ֵ                                 */
};

/*!
*  @enum    eStreamActionType
*  @brief   ���¼�����
*/
enum eStreamActionType
{
    eStreamActionTypeBegin = 0, /*!< ��ʼֵ                                 */
    eRequestConnect,            /*!< ��������                               */
    eRequestDisConnect,         /*!< ����Ͽ�                               */
    eConnected,                 /*!< ������                                 */
    eDisconnected,              /*!< �ѶϿ�                                 */
    eStreamActionTypeEnd,       /*!< ����ֵ                                 */
};

/*!
*  @enum    eRemoteDownloadState
*  @brief   Զ������״̬
*/
enum eRemoteDownloadState
{
    eRemoteDownloadStateBegin = 0,  /*!< ��ʼֵ                                 */
    eTransferOver,              /*!< �ļ��������                           */
    eTransfer,                  /*!< �ļ�������                             */
    eRemoteDownloadStateEnd,    /*!< ����ֵ                                 */
};

/*!
*  @enum    eTransferSpeed
*  @brief   ���ݴ����ٶ�����
*/
enum eTransferSpeed
{
    eTransferSpeedBegin = 0,    /*!< ��ʼֵ                                 */
    eQuickSpeed,                /*!< ����ٶ�                               */
    eNormalSpeed,               /*!< ��ͨ�ٶ�                               */
    eSlowSpeed,                 /*!< �����ٶ�                               */
    eTransferSpeedEnd,          /*!< ����ֵ                                 */
};

/*!
*  @enum    eDetectAction
*  @brief   Զ��̽���¼�����
*/
enum eDetectAction
{
    eDetectActionBegin = 0,     /*!< ��ʼֵ                                 */
    eDetectGetCfg,              /*!< ��ȡ������Ϣ                           */
    eDetectSetCfg,              /*!< ����������Ϣ                           */
    eDetectActionEnd,           /*!< ����ֵ                                 */
};

/*!
*  @enum    eFileLockOperationCode
*  @brief   �ļ�������
*/
enum eFileLockOperationCode
{
    eUnlockFile = 0,            /*!< ����                                   */
    eLockFile,                  /*!< ����                                   */
};


/*!
*  @enum    eImageFormat
*  @brief   ץͼ�ļ���ʽ
*/
enum eImageFormat
{
    eImageFormatBegin = 0,      /*!< ��ʼֵ                                 */
    eBmpFormat,                 /*!< λͼ��ʽ                               */
    eJpgFormat,                 /*!< jpg��ʽ                                */
    eImageFormatEnd,            /*!< ����ֵ                                 */
};

/*!
*  @enum    eQueryStatus
*  @brief   ��ѯ״̬
*/
enum eQueryStatus
{
    eQueryOK = 0,               /*!< ��ѯ�ɹ�                               */
    eQueryFailed,               /*!< ��ѯʧ��                               */
    eQueryBusy,                 /*!< ��ѯæ                                 */
    eQueryFinished,             /*!< ��ѯ����                               */
};

/*!
*  @enum    eRemoteDeviceControl
*  @brief   Զ���豸����
*/
enum eRemoteDeviceControl
{
    eRemoteDeviceControlBegin = 0,  /*!< ��ʼֵ                                 */
    eDeviceReboot,                  /*!< ������                                 */
    eDeviceHalt,                    /*!< �ػ�                                   */
    eDeviceStandby,                 /*!< ����                                   */
    eDeviceSetDefault,              /*!< �ָ�ϵͳĬ��                           */
    eDeviceSendTestEmail,           /*!< ���Ͳ����ʼ�                           */
    eDeviceSetDefense,              /*!< ����                                   */
    eDeviceUnsetDefense,            /*!< ����                                   */
    eRemoteDeviceControlEnd,        /*!< ����ֵ                                 */
};

/*!
*  @enum    eDiskGroupType
*  @brief    ��������
*/
enum eDiskGroupType
{
    eDiskGroupTypeBegin = 0,    /*!< ��ʼֵ                                 */
    eDiskGroupNormal,           /*!< ��ͨ����                               */
    eDiskGroupAlarm,            /*!< ��������                               */
    eDiskGroupRedundance,       /*!< ��������                               */
    eDiskGroupBackup,           /*!< ��������                               */
    eDiskGroupTypeEnd,          /*!< ����ֵ                                 */
};


/*!
*  @enum    eDiskGroupOperation
*  @brief   Ӳ���������
*/
enum eDiskGroupOperation
{
    eDiskGroupOperationBegin = 0,   /*!< ��ʼֵ                                 */
    eUnMountDisk,               /*!< ж�ط���                               */
    eCreateNewPartition,        /*!< �����·���                             */
    eDeletePartition,           /*!< ɾ������                               */
    eFormatPartition,           /*!< ��ʽ������                             */
    eDiskGroupKeepTime,         /*!< ���鱣������ʱ��                       */
    eDiskGroupBindChannel,      /*!< �����ͨ��                           */
    eDiskGroupAddPartition,     /*!< ��ӷ���������                         */
    eDiskGroupDelPartition,     /*!< �ӷ���ɾ������                         */
    eInitializeDisk,            /*!< ��ʼ��Ӳ��                             */
    eDiskGroupOperationEnd,     /*!< ����ֵ                                 */
};

/*!
*  @enum    ePTZControlCodeType
*  @brief   PTZ��̨����������
*/
enum ePTZControlCmdCode
{
    ePTZControlCodeAllOff = 0,  //��   �ر�(��Ͽ�)���п���    (Param1: ��Ч, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeCameraPower = 1, //��   ��ͨ�������Դ      (Param1: 1-��ʼ/0-ֹͣ, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeLightPower = 2,  //��   ��ͨ�ƹ��Դ            (Param1: 1-��ʼ/0-ֹͣ, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeWiper = 3,   //��   ��ͨ��ˢ����            (Param1: 1-��ʼ/0-ֹͣ, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeFans = 4,    //��   ��ͨ���ȿ���            (Param1: 1-��ʼ/0-ֹͣ, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeHeater = 5,  //��   ��ͨ����������      (Param1: 1-��ʼ/0-ֹͣ, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeAuxEquiment = 6, //��   ��ͨ�����豸����        (Param1: 1-��ʼ/0-ֹͣ, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)

    ePTZControlCodeStopContinue = 10,   //��   ֹͣ����������(��ͷ,��̨)����   (Param1: ��Ч, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeZoomIn = 11, //��   ������(���ʱ��)      (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeZoomOut = 12,    //��   �����С(���ʱ�С)      (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeFocusNear = 13,  //��   ����ǰ��                (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeFocusFar = 14,   //��   ������                (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeApertureUp = 15, //��   ��Ȧ����                (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeApertureDown = 16,   //��   ��Ȧ��С                (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeAutoZoom = 17,   //��   ���Զ�����(�Զ�����)    (Param1: 1-��ʼ/0-ֹͣ, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeAutoFocus = 18,  //��   ���Զ�����          (Param1: 1-��ʼ/0-ֹͣ, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeAutoAperture = 19,   //��   ���Զ���Ȧ          (Param1: 1-��ʼ/0-ֹͣ, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeUp = 21,     //��   ��̨����                (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeDown = 22,   //��   ��̨�¸�                (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeLeft = 23,   //��   ��̨��ת                (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeRight = 24,  //��   ��̨��ת                (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeUpLeft = 25, //��   ��̨��������ת      (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeUpRight = 26,    //��   ��̨��������ת      (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeDownLeft = 27,   //��   ��̨�¸�����ת      (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeDownRight = 28,  //��   ��̨�¸�����ת      (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeAutoLeftRight = 29,  //��   ��̨�����Զ�ɨ��        (Param1: 1-��ʼ/0-ֹͣ, Param2: �ٶ� [0-10,0��ʾĬ���ٶ�,1-10��ʾ�ٶȼ���], Param3: ��Ч, Param4: ��Ч)

    ePTZControlCodePresetSet = 40,  //��   ����Ԥ�õ�          (Param1: Ԥ�õ����[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodePresetClear = 41,    //��   ���Ԥ�õ�          (Param1: Ԥ�õ����[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodePresetCall = 42, //��   ת��Ԥ�õ�          (Param1: Ԥ�õ����[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)

    ePTZControlCodeCuriserSetStart = 51,    //��   ����Ѳ������            (Param1: Ѳ��·�ߺ�[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeCuriserSetStop = 52, //��   �ر�Ѳ������            (Param1: Ѳ��·�ߺ�[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeCuriserAddPreset = 53,   //��   ��Ԥ�õ����Ѳ������    (Param1: Ѳ��·�ߺ�[>=0], Param2: Ԥ�õ����[>=0], Param3: ͣ��ʱ��[��,>=0], Param4: Ѳ���ٶ�[1-10])
    ePTZControlCodeCuriserRunStart = 54,    //��   ��ʼѲ��                (Param1: Ѳ��·�ߺ�[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeCuriserRunStop = 55, //��   ֹͣѲ��                (Param1: Ѳ��·�ߺ�[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)

    ePTZControlCodeTraceSetStart = 61,  //��   �����켣����            (Param1: �켣��[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeTraceSetStop = 62,   //��   �رչ켣����            (Param1: �켣��[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeTraceRunStart = 63,  //��   ��ʼ�켣                (Param1: �켣��[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeTraceRunStop = 64,   //��   ֹͣ�켣                (Param1: �켣��[>=0], Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)

    ePTZControlCodeSystemReset = 99,    //��   ϵͳ��λ                (Param1: ��Ч, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)
    ePTZControlCodeElctronicReset = 100,//��   ����PTZϵͳ��λ         (Param1: ��Ч, Param2: ��Ч, Param3: ��Ч, Param4: ��Ч)

};

/*!
*  @enum    ePTZControlCmdType
*  @brief   PTZ������������(���HxhtЭ��)
*/
enum ePTZControlCmdType
{
    ePTZCmdTypeBegin        = 0,        // PTZ����������ʼֵ
    ePTZCmdTypeGetStatus,               // ��ȡPTZ״̬
    ePTZCmdTypeControl,                 // PTZ����
    ePTZCmdTypeSet485Param,             // ����485����
    ePTZCmdTypeWrite485Data,            // ֱд485����
    ePTZCmdTypeEnd,                     // PTZ�����������ֵ
};

/*!
*  @enum    tagPTZControlOperation
*  @brief   PTZ������(���HxhtЭ��)
*/
enum ePTZControlOperation
{
    ePTZOperationaIRISControl   = 8300,             /*!< ��Ȧ����                                           */
    ePTZOperationIRISStop       = 8306,             /*!< ֹͣ��Ȧ����                                       */
    ePTZOperationDigitalControl = 8302,             /*!< ���ֱ䱶                                           */
    ePTZOperationDigitalStop    = 8308,             /*!< ֹͣ���ֱ䱶                                       */
    ePTZOperationStart          = 8200,             /*!< ��̨��ʼ����                                       */
    ePTZOperationStop           = 8202,             /*!< ��ֹ̨ͣ����                                       */
    ePTZOperationScanStart      = 8204,             /*!< ��ʼ�����ɨ                                       */
    ePTZOperationScanStop       = 8204,             /*!< ֹͣ�����ɨ                                       */
    ePTZOperationPresetSetting  = 8206,             /*!< Ԥ�õ�����                                         */
    ePTZOperationPresetClear    = 8208,             /*!< Ԥ�õ����                                         */
    ePTZOperationPresetCall     = 8210,             /*!< Ԥ�õ����                                         */
    ePTZOperationPresetClearAll = 8212,             /*!< �������                                           */
    ePTZOperationFocusControl   = 8304,             /*!< �Զ��۽�����                                       */
    ePTZOperationFocusStop      = 8310,             /*!< ֹͣ�Զ��۽�                                       */
    ePTZOperationLightOn        = 13,               /*!< �ƹ⿪                                             */
    ePTZOperationLightOff       = 14,               /*!< �ƹ��                                             */
    ePTZOperationRainBrushOn    = 15,               /*!< ��ˢ��                                             */
    ePTZOperationRainBrushOff   = 16,               /*!< ��ˢ��                                             */
    ePTZOperationDetectionOn    = 17,               /*!< ̽ͷ��                                             */
    ePTZOperationDetectionOff   = 18,               /*!< ̽ͷ��                                             */
    ePTZOperationCameraOn       = 19,               /*!< ��ͷ��                                             */
    ePTZOperationCameraOff      = 20,               /*!< ��ͷ��                                             */
};

/*!
*  @enum    eAppRefreshEvent
*  @brief   Ӧ�ø����¼�֪ͨ����
*/
enum eAppRefreshEvent
{
    eAppRefreshEventBegin = 0,  /*!< ��ʼֵ                                 */
    eManagerServerRefresh,      /*!< ���������״̬                         */
    eUserActionRefresh,         /*!< �û�����״̬                           */
    eRealStreamRefresh,         /*!< ʵʱ���¼�                             */
    eVoiceRefresh,              /*!< �������¼�                             */
    eRemoteDownloadRefresh,     /*!< Զ������״̬                           */
    eRemoteDetectRefresh,       /*!< Զ��̽��                               */
    eAppRefreshEventEnd,        /*!< ����ֵ                                 */
};

/*!
*  @enum    eStreamTransferMode
*  @brief   �����䷽ʽ
*/
enum eStreamTransferMode
{
    eStreamTransferModeBegin = 0,   /* ��ʼֵ                                 */

    eGeneralTCP,                /* ��ͨ��TCP                              */
    eGeneralRTP,                /* ��ͨ��RTP                              */
    eGeneralUDP,		    /*!< ��ͨ��UDP                              */

    eStreamTransferModeEnd,     /* ����ֵ                                 */
};

/*!
*  @enum    eVoiceMode
*  @brief   ���������ģʽ
*/
enum eVoiceMode
{
    eVoiceModeBegin = 0,        /*!< ��ʼֵ                                 */
    eVoiceG726,                 /*!< G726�����ģʽ                         */
    eVoiceG711U,                /*!< G711U�����ģʽ                        */
    eVoiceMPEG4AAC,             /*!< MPEG4 AAC�����ģʽ                    */
    eVoiceAutoDiscern,          /*!< �Զ�ʶ������ģʽ                     */
    eVoiceModeEnd,              /*!< ����ֵ                                 */
};

/*!
*  @enum    eVideoCodecMode
*  @brief   ��Ƶ�����ģʽ
*/
typedef enum eVideoCodecMode
{
    eVideoCodecModeBegin =   0, /*!< ��ʼֵ                                 */
    eVideoCodecH264,            /*!< ��׼H264�����ģʽ                     */
    eVideoCodecHYMpeg4,         /*!< HYMpeg4�����ģʽ                      */
    eVideoCodecHYH264,          /*!< HYH264�����ģʽ                       */
    eVideoCodecAutoDiscern,     /*!< �Զ�ʶ������ģʽ                     */
    eVideoCodecModeEnd,         /*!< ����ֵ                                 */
} eVideoCodecMode;

/*!
*  @enum    eTaskStatus
*  @brief   ����״̬
*/
enum eTaskStatus
{
    eTaskStatusBegin = 0,       /*!< ��ʼֵ                                 */
    eTaskStatusNone,            /*!< ������״̬                             */
    eTaskStatusInitialize,      /*!< �����ʼ��                             */
    eTaskStatusDestroy,         /*!< ��������                               */
    eTaskStatusStart,           /*!< ��������                               */
    eTaskStatusStop,            /*!< ����ֹͣ                               */
    eTaskStatusRun,             /*!< ����������                             */
    eTaskStatusRecover,         /*!< ����ָ�                               */
	eTaskStatusPause,			/*! ��ͣ*/
    eTaskStatusEnd,             /*!< ����ֵ                                 */
};

/*!
*  @enum    eMediaFunctionType
*  @brief   ý�幦������
*/
enum eMediaFunctionType
{
    eMediaFunctionTypeBegin = 0,    /*!< ��ʼֵ                                 */
    eMediaFunctionRealStream,   /*!< ʵʱ��                                 */
    eMediaFunctionVoiceStream,  /*!< ������                                 */
    eMediaFunctionHistoryStream,    /*!< ��ʷ��                                 */
    eMediaFunctionTransparent,  /*!< ͸��ͨ��                               */
    eMediaFunctionFileUpload,   /*!< �ļ��ϴ�                               */
    eMediaFunctionFileDownload, /*!< �ļ�����                               */
    eMediaFunctionTypeEnd,      /*!< ����ֵ                                 */
};

/*!
*  @enum    eFrameType
*  @brief   ֡����
*/
enum eFrameType
{
    eFrameError = 0x0000,
    eFrameIFrames = 0x0001,         //��������I֡
    eFramePFrames = 0x0002,

    eFrameBPFrames = 0x0020,
    eFrameBBPFrames = 0x0004,
    eFrameAudioFrames = 0x0008,

    eFrameQCIFIFrames = 0x0010,     //QCIF��I֡
    eFramePktSQCIFIFrames = 0x0011, //����������I֡

    eFrameQCIFPFrames = 0x0040,
    eFramePktSQCIFPFrames = 0x0041, //����������P֡

    eFrameBIFrames = 0x0090,
    eFrameBBIFrames = 0x00C0,
    eFrameSysHeader = 0x0080,           //������ϵͳͷ
    eFramePktSysHeaderAux = 0x0081,     //������ϵͳͷ
    eFramePktSysHeaderHDAux = 0x0082,   //����������ϵͳͷ
    eFrameSFrames = 0x0200,
    eFrameDspStatus = 0x0100,
    eFrameAimDetection = 0x0400,
    eFrameOrigImage = 0x0800,
    eFrameMotionDetection = 0x1000,
    eFrameFileEnd	= 0xFFFF,//Liujl change start-end at 20160520-1415  //�ļ�����
};

/*!
*  @enum    eSerialType
*  @brief   ��������
*/
enum eSerialType
{
    eTTY232 = 0,                            /*!< RS232����                               */
    eTTY485,                                /*!< RS485����                               */
    eTTY422,                                /*!< RS422����                               */
};

/*!
*  @enum    eDevType
*  @brief   �豸����
*/
enum eDevType
{
    eDevTypeTerminal = 2,               /*!< ǰ��(��Ƶ������) */
    eDevTypeStore = 4,                  /*!< �洢������ */
    eDevTypeCamera = 5,                 /*!< ����ͷ */
    eDevTypeAlarmin = 6,                /*!< �������� */
    eDevTypeAlarmout = 8,               /*!< ������� */
    eDevTypeAnalyse = 20,               /*!< ���ܷ�����Ԫ */
};

/*!
*  @enum    eAlarmEventType
*  @brief   ���������¼�����
*/
enum eAlarmEventType
{
    eAlarmEventTypeOverflow = 0,        /*!< Խ���� */
    eAlarmEventTypeResort = 1,          /*!< ������� */
    eAlarmEventTypeCarSpeed = 2,        /*!< ���ټ�� */
};

/*!
*  @enum    eFaultType
*  @brief   ��������
*/
enum eFaultType
{
    eFaultTypeDevice = 1,               /*!< �豸�澯 */
    eFaultTypeCapability = 2,           /*!< ���ܸ澯 */
    eFaultTypeProcess = 3,              /*!< �������澯 */
    eFaultTypeCommunication = 4,        /*!< ͨѶ�澯 */
    eFaultTypeEnvironment = 5,          /*!< �����澯 */
};

/*!
*  @enum    eFaultID
*  @brief   ���ϱ��
*/
enum eFaultID
{
    //�豸���ϱ��
    eFaultTypeFlash = 7,                /*!< ����Flashʧ�ܱ��� */
    eFaultTypeDisk = 8,                 /*!< Ӳ�̶�дʧ�ܸ澯����Ӳ�̹��ϱ��� */
    eFaultTypeDiskSpace = 501,          /*!< Ӳ�̿ռ�ʣ������������ֵ���� */
    eFaultTypeDiskFull = 502,           /*!< Ӳ�̿ռ������� */
    eFaultTypeStoreServer = 503,        /*!< �����Ĵ洢FTP�ļ�ʧ��*/

    //���ܹ��ϱ��
    eFaultTypeCpuUseRatio = 1,          /*!< ����Flashʧ�ܱ��� */
    eFaultTypeDiskUseRatio = 2,         /*!< Ӳ�̶�дʧ�ܸ澯����Ӳ�̹��ϱ��� */
    eFaultTypeMemoryUseRatio = 3,       /*!< Ӳ�̿ռ�ʣ������������ֵ���� */

    //ͨѶ���ϱ��
    eFaultTypeVideoLoss = 4,            /*!< ��Ƶ�ź��жϱ��� */
};

/*!
*  @enum    eFaultState
*  @brief   ����״̬
*/
enum eFaultState
{
    New = 0,            /*!< �¹��� */
    Resure = 1,         /*!< ���ϻָ� */
};

/*!
*  @enum    eConnectType
*  @brief   �����ӷ�ʽ
*/
enum eConnectType
{
    eConnectTypeBegin       = 0,
    eConnectActive,
    eConnectPassive,
    eConnectTypeEnd,
};

/*!
*  @struct  ePanelKeyBoardCodeType
*  @brief   ������ֵ����
*/
typedef enum ePanelKeyBoardCodeType
{
    ePanelKeyBoardTypeBegin                     = 0x0,      /*!< ��ʼֵ                                 */
    ePanelKeyBoardCode_0                        = 0x1,      /*!< ��Ӧ��:0                               */
    ePanelKeyBoardCode_1                        = 0x2,      /*!< ��Ӧ��:1                               */
    ePanelKeyBoardCode_2                        = 0x3,      /*!< ��Ӧ��:2                               */
    ePanelKeyBoardCode_3                        = 0x4,      /*!< ��Ӧ��:3                               */
    ePanelKeyBoardCode_4                        = 0x5,      /*!< ��Ӧ��:4                               */
    ePanelKeyBoardCode_5                        = 0x6,      /*!< ��Ӧ��:5                               */
    ePanelKeyBoardCode_6                        = 0x7,      /*!< ��Ӧ��:6                               */
    ePanelKeyBoardCode_7                        = 0x8,      /*!< ��Ӧ��:7                               */
    ePanelKeyBoardCode_8                        = 0x9,      /*!< ��Ӧ��:8                               */
    ePanelKeyBoardCode_9                        = 0xA,      /*!< ��Ӧ��:9                               */
    ePanelKeyBoardCode_10                       = 0xB,      /*!< ��Ӧ��:10                              */
    ePanelKeyBoardCode_11                       = 0xC,      /*!< ��Ӧ��:11                              */
    ePanelKeyBoardCode_12                       = 0xD,      /*!< ��Ӧ��:12                              */
    ePanelKeyBoardCode_13                       = 0xE,      /*!< ��Ӧ��:13                              */
    ePanelKeyBoardCode_14                       = 0xF,      /*!< ��Ӧ��:14                              */
    ePanelKeyBoardCode_15                       = 0x10,     /*!< ��Ӧ��:15                              */
    ePanelKeyBoardCode_16                       = 0x11,     /*!< ��Ӧ��:16                              */
    ePanelKeyBoardCode_PTZ                      = 0x40,     /*!< ��Ӧ��:��̨                            */
    ePanelKeyBoardCode_Copy                     = 0x41,     /*!< ��Ӧ��:����                            */
    ePanelKeyBoardCode_Multi                    = 0x42,     /*!< ��Ӧ��:�໭��                          */
    ePanelKeyBoardCode_Switch                   = 0x43,     /*!< ��Ӧ��:�л�                            */
    ePanelKeyBoardCode_Function                 = 0x44,     /*!< ��Ӧ��:����                            */
    ePanelKeyBoardCode_Play                     = 0x45,     /*!< ��Ӧ��:����                            */
    ePanelKeyBoardCode_Backward                 = 0x46,     /*!< ��Ӧ��:����                            */
    ePanelKeyBoardCode_Record                   = 0x47,     /*!< ��Ӧ��:¼��                            */
    ePanelKeyBoardCode_ESC                      = 0x48,     /*!< ��Ӧ��:�˳�                            */
    ePanelKeyBoardCode_Left                     = 0x49,     /*!< ��Ӧ��:��                              */
    ePanelKeyBoardCode_Right                    = 0x4A,     /*!< ��Ӧ��:��                              */
    ePanelKeyBoardCode_Up                       = 0x4B,     /*!< ��Ӧ��:��                              */
    ePanelKeyBoardCode_Down                     = 0x4C,     /*!< ��Ӧ��:��                              */
    ePanelKeyBoardCode_Enter                    = 0x4D,     /*!< ��Ӧ��:ȷ��                            */
    ePanelKeyBoardCode_Shutdown                 = 0x4E,     /*!< ��Ӧ��:�ػ�                            */
    ePanelKeyBoardCode_TV_VGA                   = 0x4F,     /*!< ��Ӧ��:TV/VGA                          */
    ePanelKeyBoardCode_Edit                     = 0x50,     /*!< ��Ӧ��:�༭                            */
    ePanelKeyBoardCode_Language                 = 0x51,     /*!< ��Ӧ��:����                            */
    ePanelKeyBoardCode_Mute                     = 0x52,     /*!< ��Ӧ��:����                            */
    ePanelKeyBoardCode_Pause                    = 0x53,     /*!< ��Ӧ��:��ͣ                            */
    ePanelKeyBoardCode_Stop                     = 0x54,     /*!< ��Ӧ��:ֹͣ                            */
    ePanelKeyBoardCode_AlarmClear               = 0x55,     /*!< ��Ӧ��:����                            */
    ePanelKeyBoardCode_Defence                  = 0x56,     /*!< ��Ӧ��:��������                        */
    ePanelKeyBoardCode_Capture                  = 0x57,     /*!< ��Ӧ��:ץͼ                            */
    ePanelKeyBoardCode_LightAdd                 = 0x58,     /*!< ��Ӧ��:��������                        */
    ePanelKeyBoardCode_LightSub                 = 0x59,     /*!< ��Ӧ��:���ȼ���                        */
    ePanelKeyBoardCode_ContrastAdd              = 0x5A,     /*!< ��Ӧ��:�Աȶ�����                      */
    ePanelKeyBoardCode_ContrastSub              = 0x5B,     /*!< ��Ӧ��:�Աȶȼ���                      */
    ePanelKeyBoardCode_SpeedAdd                 = 0x5C,     /*!< ��Ӧ��:�ٶ�����                        */
    ePanelKeyBoardCode_SpeedSub                 = 0x5D,     /*!< ��Ӧ��:�ٶȼ���                        */
    ePanelKeyBoardCode_Set                      = 0x5E,     /*!< ��Ӧ��:����                            */
    ePanelKeyBoardCode_F1                       = 0x5F,     /*!< ��Ӧ��:F1                              */
    ePanelKeyBoardTypeEnd,                                  /*!< ����ֵ                                 */
} ePanelKeyBoardCodeType;

/*!
*  @struct  ePanelControlType
*  @brief   ����������
*/
typedef enum ePanelControlType
{
    ePanelControlBegin                          = 0,        /*!< ��ʼֵ                                 */
    ePanelControlKeyDown,                                   /*!< ����                                   */
    ePanelControlKeyUp,                                     /*!< ����                                   */
    ePanelControlClick,                                     /*!< ���(���²�����)                       */
    ePanelControlEnd,                                       /*!< ����ֵ                                 */
} ePanelControlType;

/*!
*  @struct  eDecoderChannelStatus
*  @brief   ����ͨ��״̬
*/
typedef enum eDecoderChannelStatus
{
    eDecoderChannelStatusBegin                  = 0,        /*!< ��ʼֵ                                 */
    eDecoderChannelStatusOpen,                              /*!< ��                                   */
    eDecoderChannelStatusClose,                             /*!< �ر�                                   */
    eDecoderChannelStatusContinue,                          /*!< ����                                   */
    eDecoderChannelStatusEnd,                               /*!< ����ֵ                                 */
} eDecoderChannelStatus;

/*!
*  @struct  eStreamSourceType
*  @brief   ��ý��Դ����
*/
typedef enum eStreamSourceType
{
    eStreamSourceTypeBegin                      = 0,        /*!< ��ʼֵ                                 */
    eStreamSourceTypeReal,                                  /*!< ʵʱ��                                 */
    eStreamSourceTypeHistory,                               /*!< ��ʷ��                                 */
    eStreamSourceTypeEnd,                                   /*!< ����ֵ                                 */
} eStreamSourceType;

/*!
*  @struct  eStreamPlayControlStatus
*  @brief   ��ý�岥�ſ���״̬
*/
typedef enum eStreamPlayControlStatus
{
    eStreamPlayControlBegin                     = 0,        /*!< ��ʼֵ                                 */
    eStreamPlayControlPlay,                                 /*!< ����                                   */
    eStreamPlayControlSuspend,                              /*!< ��ͣ                                   */
    eStreamPlayControlResume,                               /*!< �ָ�                                   */
    eStreamPlayControlStop,                                 /*!< ֹͣ                                   */
    eStreamPlayControlFast,                                 /*!< ���ٲ���                               */
    eStreamPlayControlSlow,                                 /*!< ���ٲ���                               */
    eStreamPlayControlNormal,                               /*!< �����ٶ�                               */
    eStreamPlayControlOneByOne,                             /*!< ��֡����                               */
    eStreamPlayControlOpenAudio,                            /*!< ������                               */
    eStreamPlayControlCloseAudio,                           /*!< �ر�����                               */
    eStreamPlayControlSetPos,                               /*!< ����λ��                               */
    eStreamPlayControlClearBuffer,                          /*!< ��ջ�����                             */
    eStreamPlayControlEnd,                                  /*!< ����ֵ                                 */
} eStreamPlayControlStatus;

/*!
*  @struct  eDisplayControlStatus
*  @brief   ��ʾ����״̬
*/
typedef enum eDisplayControlStatus
{
    eDisplayControlStatusBegin                  = 0,        /*!< ��ʼֵ                                 */
    eDisplayControlStatusEnlarge,                           /*!< �Ŵ���ʾ                               */
    eDisplayControlStatusRenew,                             /*!< ��ԭ                                   */
    eDisplayControlStatusEnd,                               /*!< ����ֵ                                 */
} eDisplayControlStatus;


typedef enum eTaskSpeed
{
	eTaskSpeedBegin				=	0,			/*!< ��ʼֵ				*/
	eSpeedNormal,									/*!< �����ٶȲ���			*/
	eSpeedTwo,									/*!< 2���ٶȲ���			*/
	eSpeedFour,									/*!< 4���ٶȲ���			*/
	eSpeedEight,									/*!< 8���ٶȲ���			*/
	eSpeedSixteen,								/*!< 16���ٶȲ���			*/
	eSpeedHalf,									/*!< 1/2���ٶȲ���			*/
	eSpeedQuarter,								/*!< 1/4���ٶȲ���			*/
	eSpeedOneEighth,								/*!< 1/8���ٶȲ���			*/
	eSpeedOneSixteenth,							/*!< 1/16���ٶȲ���		*/
	eSpeedSingle,									/*!< ��֡���ٶȲ���		*/
	eTaskSpeedEnd,								/*!< ����ֵ				*/
}eTaskSpeed;
//////////////////////////////////////////////////////////////////////////
//�ṹ
//////////////////////////////////////////////////////////////////////////


typedef struct FrameSize
{
    unsigned int last_frame_width;
    unsigned int last_frame_height;
    unsigned int cur_frame_width;
    unsigned int cur_frame_height;
}FrameSize;

/*!
*  @struct  tagTimeInfo
*  @brief   ʱ����Ϣ
*/
typedef struct tagTimeInfo
{
    WORD wYear;                 /*!< ��                                     */
    WORD wMonth;                /*!< ��                                     */
    WORD wDay;                  /*!< ��                                     */
    WORD wHour;                 /*!< ʱ                                     */
    WORD wMinute;               /*!< ��                                     */
    WORD wSecond;               /*!< ��                                     */
} TimeInfo, *LPTimeInfo;

/*!
*  @struct  tagAbsoluteTime
*  @brief   ����ʱ����Ϣ
*/
typedef struct tagAbsoluteTime
{
    WORD wYear;                 /*!< ��                                     */
    WORD wMonth;                /*!< ��                                     */
    WORD wWeek;                 /*!< ��                                     */
    WORD wDay;                  /*!< ��                                     */
    WORD wHour;                 /*!< ʱ                                     */
    WORD wMinute;               /*!< ��                                     */
    WORD wSecond;               /*!< ��                                     */
    WORD wMillisecond;          /*!< ����                                   */
} AbsoluteTime, *LPAbsoluteTime;

/*!
*  @struct  tagBuffer
*  @brief   ��������Ϣ
*/
typedef struct tagBuffer
{
    BYTE *pBuffer;              /*!< ý�����ݻ�����                         */
    DWORD dwBufLen;             /*!< ý�����ݳ���                           */
} Buffer, *LPBuffer;

/*!
*  @struct  tagManagerServerState
*  @brief	���������״̬
*/
typedef struct tagManagerServerState
{
	enum eManagerServerType eType;	/*!< ��������                               */
	DWORD dwState;				/*!< ����״̬                               */
    char sServer[IP_ADDRESS_LEN];   /*!< ��������IP��ַ��Ϣ                     */
    DWORD dwServerDomainEnable; /*!<��������������Ϣ��Ч��־                */
    char sServerDomain[DOMAIN_ADDRESS_LEN]; /*!<��������������Ϣ                      */
    DWORD dwServerPort;         /*!<���������˿�                            */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!<����                                    */
} ManagerServerState, *LPManagerServerState;

/*!
*  @struct  tagRealStreamMedia
*  @brief	ʵʱ��ý��
*/
typedef struct tagRealStreamMedia
{
    enum eStreamMediaType eType;		/*!< ������                                 */
    Buffer cBuffer;             /*!< ��������Ϣ                             */
    AbsoluteTime cTime;         /*!< ֡ʱ��                                 */
    DWORD dwFrameType;          /*!< ֡����                                 */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< ����                                   */
} RealStreamMedia, *LPRealStreamMedia;

/*!
*  @struct  tagStreamTransferFrame
*  @brief	��ת��֡����
*/
typedef struct tagStreamTransferFrame
{
	enum eFrameType	eFrameTypeInfo;							/*!< ֡������Ϣ								*/
	DWORD	dwTimeStamp;								/*!< ֡ʱ���								*/
    AbsoluteTime cAbsoluteTime;                         /*!< ֡����ʱ���                           */
    DWORD   dwFrameNumber;                              /*!< ֡���                                 */
    Buffer  cFrameBuffer;                               /*!< ֡������                               */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< ����                                   */
} StreamTransferFrame, *LPStreamTransferFrame;

/*!
*  @struct  tagStreamFlowState
*  @brief   ������״̬
*/
typedef struct tagStreamFlowState
{
    DWORD dwBitrate;            /*!< ����(kbps)                             */
    DWORD dwWorkTime;           /*!< ������ʱ��                             */
    DWORD dwTotalFlow;          /*!< ������                                 */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< ����                                   */
} StreamFlowState, *LPStreamFlowState;

/*!
*  @struct  tagStreamState
*  @brief   ��״̬
*/
typedef struct tagStreamState
{
    DWORD dwClientNum;          /*!< �ͻ���                                 */
    DWORD dwUserID[REAL_STREAM_LIMIT];  /*!< �ͻ���Ϣ                               */
    StreamFlowState cStreamFlowState[REAL_STREAM_LIMIT];    /*!< ����״̬                   */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< ����                                   */
} StreamState, *LPStreamState;

/*!
*  @struct  tagRemoteUserInfo
*  @brief   Զ���û���Ϣ
*/
typedef struct tagRemoteUserInfo
{
    DWORD dwUserID;             /*!< �û�ID                                 */
    char sUserName[USERNAME_LEN];   /*!< �û���                                 */
    char sUserPass[USERPASS_LEN];   /*!< �û�����                               */
    char sUserIPAddress[IP_ADDRESS_LEN];    /*!< �û�IP��ַ                             */
    char sClientIPAddress[IP_ADDRESS_LEN];  /*!< �ͻ���IP��ַ */
    char sClientMACAddress[MAC_ADDRESS_LEN];    /*!< �ͻ���MAC��ַ                           */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< ����                                   */
} RemoteUserInfo, *LPRemoteUserInfo;

/*!
*  @struct  tagRealStreamAction
*  @brief   ʵʱ���¼�֪ͨ
*/
typedef struct tagRealStreamAction
{
	DWORD dwChannel;			/*!< ͨ����                                 */
	enum eStreamActionType eActionType;	/*!< �¼�����                               */
	DWORD dwReserve[DEF_RESERVE_NUM];	/*!< ����                                   */
} RealStreamAction, *LPRealStreamAction;

/*!
*  @struct  tagVoiceStreamAction
*  @brief   �������¼�֪ͨ
*/
typedef struct tagVoiceStreamAction
{
    DWORD dwChannel;            /*!< ͨ����                                 */
	enum eStreamActionType eActionType;	/*!< �¼�����                               */
	DWORD dwReserve[DEF_RESERVE_NUM];	/*!< ����                                   */
} VoiceStreamAction, *LPVoiceStreamAction;

/*!
*  @struct  tagAlarmNotify
*  @brief   ����֪ͨ��Ϣ
*/
typedef struct tagAlarmNotify
{
    DWORD dwType;               /*!< ��������                               */
    DWORD dwDepict;             /*!< ������Ϣ����                           */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< ����                                   */
} AlarmNotify, *LPAlarmNotify;

/*!
*  @struct  tagAppLogQuery
*  @brief   Ӧ�ò���־��ѯ��Ϣ
*/
typedef struct tagAppLogQuery
{
    BYTE bytQueryMode;          /*!< ��ѯģʽ                               */
    BYTE bytMajorType;          /*!< ������                                 */
    BYTE bytMinorType;          /*!< ������                                 */
    BYTE bytReserve[1];         /*!< ����                                   */
    DWORD dwChannel;            /*!< ͨ����                                 */
    TimeInfo cBeginTime;        /*!< ��ʼʱ��                               */
    TimeInfo cEndTime;          /*!< ����ʱ��                               */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< ����                                   */
} AppLogQuery, *LPAppLogQuery;

/*!
*  @struct  tagAppLogInfo
*  @brief   Ӧ�ò���־��Ϣ
*/
typedef struct tagAppLogInfo
{
    TimeInfo cLogTime;          /*!< ��־ʱ��                               */
    BYTE bytMajorType;          /*!< ������                                 */
    BYTE bytMinorType;          /*!< ������                                 */
    BYTE bytDetail;             /*!< ��ϸ��Ϣ                               */
    BYTE bytReserve[1];         /*!< ����                                   */
    DWORD dwChannel;            /*!< ͨ��                                   */
    char sUserName[USERNAME_LEN];   /*!< �����û�                               */
    DWORD dwUserIPAddress;      /*!< �����û�IP��ַ                         */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< ����                                   */
} AppLogInfo, *LPAppLogInfo;

/*!
*  @struct  tagHistoryQueryInfo
*  @brief   ��ʷ��ѯ��Ϣ
*/
typedef struct tagHistoryQueryInfo
{
    DWORD dwChannel;            /*!< ͨ����                                 */
	DWORD dwDiskGroup;			/*!< ������Ϣ                               */
	enum eHistoryStreamType eStreamType;	/*!< ��ʷ������                             */
    char cBeginTime[15];        /*!< ��ʼʱ��                               */
    char cEndTime[15];          /*!< ����ʱ��                               */
    char cTicket[HXHT_COMMON_STRING_LEN]; /*!< ��֤��Ϣ�����Hxht           */
} HistoryQueryInfo, *LPHistoryQueryInfo;

/*!
*  @struct  tagHistoryQueryInfo
*  @brief   ��ʷ��ѯ��Ϣ
*/
typedef struct tagHistoryQueryInfoMultiType
{
    DWORD dwChannel;            /*!< ͨ����                                 */
    DWORD dwDiskGroup;          /*!< ������Ϣ                               */
    DWORD dwStreamType;         /*!< ��ʷ������                             */
    char cBeginTime[15];        /*!< ��ʼʱ��                               */
    char cEndTime[15];          /*!< ����ʱ��                               */
} HistoryQueryInfoMultiType, *LPHistoryQueryInfoMultiType;

/*!
*  @struct  tagFileQueryInfo
*  @brief   �ļ���ѯ��Ϣ
*/
typedef struct tagFileQueryInfo
{
    DWORD dwChannel;            /*!< ͨ����                                 */
    DWORD dwFileType;           /*!< �ļ�������                             */
    char cBeginTime[DATE_TIME_LEN]; /*!< ��ʼʱ��                               */
    char cEndTime[DATE_TIME_LEN];   /*!< ����ʱ��                               */
} FileQueryInfo, *LPFileQueryInfo;

/*!
*  @struct  tagHistoryQueryResult
*  @brief   ��ʷ��ѯ�����Ϣ
*/
typedef struct tagHistoryQueryResultMultiType
{
    DWORD dwStreamType;         /*!< ��ʷ������                             */
    DWORD dwChannel;            /*!< ͨ����                                 */
    char cBeginTime[15];        /*!< ��ʼʱ��                               */
    char cEndTime[15];          /*!< ����ʱ��                               */
    DWORD dwDataSize;           /*!< ���ݴ�С                               */
} HistoryQueryResultMultiType, *LPHistoryQueryResultMultiType;

/*!
*  @struct  tagHistoryQueryResult
*  @brief	��ʷ��ѯ�����Ϣ
*/
typedef struct tagHistoryQueryResult
{
	enum eHistoryStreamType eStreamType;			/*!< ��ʷ������                             */
	DWORD dwChannel;			/*!< ͨ����                                 */
    char cBeginTime[15];        /*!< ��ʼʱ��                               */
    char cEndTime[15];          /*!< ����ʱ��                               */
    DWORD dwDataSize;           /*!< ���ݴ�С                               */
} HistoryQueryResult, *LPHistoryQueryResult;

/*!
*  @struct  tagFileQueryResult
*  @brief   �ļ���ѯ�����Ϣ
*/
typedef struct tagFileQueryResult
{
    DWORD dwChannel;            /*!< ͨ����                                 */
    DWORD dwLock;               /*�Ƿ�����                                  */
    DWORD dwDataSize;           /*!< ���ݴ�С                               */
    DWORD dwFileType;           /*!< ͼƬ����                               */
    char cCreateTime[DATE_TIME_LEN];    /*!< ͼƬʱ��                               */
    char cFileName[MAX_FILENAME];   /*!< ͼƬ�豸��·��                         */
} FileQueryResult, *LPFileQueryResult;

/*!
*  @struct	tagHistoryQueryResultSet
*  @brief	��ʷ��ѯ�����
*/
typedef struct tagHistoryQueryResultSet
{
	HistoryQueryResult cHistoryQueryResult;	/*!< ��ʷ��ѯ�����Ϣ                       */
	struct tagHistoryQueryResultSet *pNext;	/*!< ��һ�����                             */
} HistoryQueryResultSet, *LPHistoryQueryResultSet;



/*!
*  @enum	eHistoryLogMajorType
*  @brief	��־��ѯ������
*/
enum eHistoryLogMajorType
{
    eHistoryLogMajorTypeBegin = 0,  /*!< ��ʼֵ                                 */
    eHistoryLogSysOperation,    /*!< ϵͳ������־                           */
    eHistoryLogSysSetting,      /*!< ϵͳ������־                           */
    eHistoryLogRecord,          /*!< ¼����־                               */
    eHistoryLogUserManage,      /*!< �û�������־                           */
    eHistoryLogAlarm,           /*!< �豸������־                           */
    eHistoryLogException,       /*!< �豸�쳣��־                           */
    eHistoryLogStorage,         /*!< �洢������־                           */
    eHistoryLogMajorAll,        /*!< ����������                             */
    eHistoryLogMajorTypeEnd,    /*!< ����ֵ                                 */
};

/*!
*  @enum    eHistoryLogMinorType
*  @brief   ��־��ѯ������
*/
enum eHistoryLogMinorType
{
    eHistoryLogSysOp = 0,       /*!< ϵͳ������������                       */
    eHistoryLogSysOpUpdate,     /*!< ϵͳ����                               */
    eHistoryLogSysOpPTZControl, /*!< ��̨����                               */
    eHistoryLogSysOpIllShutdown,    /*!< �Ƿ��ػ�                               */
    eHistoryLogSysOpPowerOff,   /*!< �����ػ�                               */
    eHistoryLogSysOpPowerOn,    /*!< ����                                   */
    eHistoryLogSysOpRemoteReset,    /*!< Զ������                               */
    eHistoryLogSysOpClearAlarm, /*!< ����                                   */

    eHistoryLogSysSetAll = 100, /*!< ϵͳ������������                       */
    eHistoryLogSysSetTimeSetting,   /*!< ¼��ʱ�������                         */
    eHistoryLogSysSetCommonSetting, /*!< ��ͨ����                               */
    eHistoryLogSysSetCodecSetting,  /*!< ��������                               */
    eHistoryLogSysSetNetSetting,    /*!< ��������                               */
    eHistoryLogSysSetServerSetting, /*!< ����������                             */
    eHistoryLogSysSetMotionSetting, /*!< �ƶ��������                           */
    eHistoryLogSysSetPTZSetting,    /*!< ��̨����������                         */
    eHistoryLogSysSetDefaultSetting,    /*!< �ָ�Ĭ������                           */
    eHistoryLogSysSetDisplayDeviceSetting,  /*!< ������ʾ�豸����                       */
    eHistoryLogSysSetDisplayModeSetting,    /*!< ��ʾģʽ����                           */
    eHistoryLogSysSetPictureSetting,    /*!< ͼ����ɫ����                           */
    eHistoryLogSysSetMaintainSetting,   /*!< �Զ�ά������                           */
    eHistoryLogSysSetAlarmOutSetting,   /*!< �����������                           */
    eHistoryLogSysSetAlarmInSetting,    /*!< ������������                           */
    eHistoryLogSysSetCustomizeFunction, /*!< ���ܶ�������                           */
    eHistoryLogSysSetImportPTZProtocol, /*!< ������̨Э��                           */
    eHistoryLogSysSetExportPTZProtocol, /*!< ������̨Э��                           */
    eHistoryLogSysSetImportSettings,    /*!< �����������                           */
    eHistoryLogSysSetExportSettings,    /*!< �����������                           */
    eHistoryLogSysSetExceptionSetting,  /*!< �쳣��������                           */

    eHistoryLogRecordAll = 200, /*!< ¼�������������                       */
    eHistoryLogRecordStartManual,   /*!< �����ֶ�¼��                           */
    eHistoryLogRecordStartAuto, /*!< �����Զ�¼��                           */
    eHistoryLogRecordStop,      /*!< ֹͣ����                               */

    eHistoryLogUserAll = 300,   /*!< �û�������������                       */
    eHistoryLogUserAdd,         /*!< ����û�                               */
    eHistoryLogUserDelete,      /*!< ɾ���û�                               */
    eHistoryLogUserEdit,        /*!< �޸��û�����                           */
    eHistoryLogUserLogin,       /*!< �û���¼                               */
    eHistoryLogUserLogout,      /*!< �û��ǳ�                               */

    eHistoryLogAlarmAll = 400,  /*< ������������                            */
    eHistoryLogAlarmMotionStart,    /*!< �ƶ���⿪ʼ                           */
    eHistoryLogAlarmMotionStop, /*!< �ƶ�������                           */
    eHistoryLogAlarmInputAlarm, /*!< ���뱨����ʼ                           */

    eHistoryLogExceptionAll = 500,  /*!< �쳣��������                           */
    eHistoryLogExceptionIpConflict, /*!< IP��ͻ                                 */
    eHistoryLogExceptionHardDiskFull,   /*!< Ӳ����                                 */
    eHistoryLogExceptionHardDiskError,  /*!< Ӳ�̳���                               */
    eHistoryLogExceptionIllegalAccess,  /*!< �Ƿ�����                               */
    eHistoryLogExceptionSignalLost, /*!< �źŶ�ʧ                               */
    eHistoryLogExceptionSignalRecover,  /*!< �źŻָ�                               */
    eHistoryLogExceptionNetDisconnect,  /*!< ���߶�                                 */

    eHistoryLogStorageAll = 600,    /*!< �洢������������                       */
    eHistoryLogStorageFormatPartition,  /*!< ������ʽ��                             */
    eHistoryLogStorageAddPartition, /*!< ��ӷ���                               */
    eHistoryLogStorageRemovePartition,  /*!< ɾ��������                             */
    eHistoryLogStorageUnmountDisk,  /*!< ж��Ӳ��                               */
    eHistoryLogStorageDiskGroupOperation,   /*!< ���̷������                           */
};


/*!
*  @struct  tagLogQueryInfo
*  @brief   ��ʷ��ѯ��Ϣ
*/
typedef struct tagLogQueryInfo
{
	DWORD m_dwQueryMode;		/*!< ��ѯ��ʽ                               */
	enum eHistoryLogMajorType m_eMajorType;	/*!< ������                                 */
	enum eHistoryLogMinorType m_eMinorType;	/*!< ������                                 */
	DWORD m_dwChannel;			/*!< ͨ����                                 */
	char m_sStartTime[DATE_TIME_LEN];	/*!< ��ʼʱ��                               */
	char m_sStopTime[DATE_TIME_LEN];	/*!< ����ʱ��                               */
} LogQueryInfo, *LPLogQueryInfo;

/*!
*  @struct	tagLogQueryResult
*  @brief	��ʷ��ѯ�����Ϣ
*/
typedef struct tagLogQueryResult
{
	enum eHistoryLogMajorType m_eMajorType;	/*!< ������                                 */
	enum eHistoryLogMinorType m_eMinorType;	/*!< ������                                 */
	DWORD m_dwDetailInfo;		/*!< ��ϸ��Ϣ                               */
	char m_sUserName[USERNAME_LEN];	/*!< �����û�                               */
	char m_sUserIP[IP_ADDRESS_LEN];	/*!< �û�IP��ַ                             */
	char m_sLogTime[DATE_TIME_LEN];	/*!< ����ʱ��                               */
} LogQueryResult, *LPLogQueryResult;

/*!
*  @struct	tagHistoryQueryResultSet
*  @brief	��ʷ��ѯ�����
*/
typedef struct tagLogQueryResultSet
{
	LogQueryResult cLogQueryResult;	/*!< ��ʷ��ѯ�����Ϣ                       */
	struct tagLogQueryResultSet *pNext;	/*!< ��һ�����                             */
} LogQueryResultSet, *LPLogQueryResultSet;

/*!
*  @struct	tagHistoryChannelParaInfo
*  @brief   ��ʷͨ������������Ϣ
*/
typedef struct tagHistoryChannelParaInfo
{
    DWORD dwEnableEndTime;      /*!< ����ʱ���Ƿ���Ч                       */
    TimeInfo cBeginTime;        /*!< ��ʼʱ��                               */
    TimeInfo cEndTime;          /*!< ����ʱ��                               */
    DWORD dwChannel;            /*!< ¼��ͨ��                               */
	DWORD dwDiskGroup;			/*!< ������Ϣ                               */
	enum eHistoryStreamType eType;	/*!< ��ʷ������                             */
	DWORD dwTaskType;			/*!< ��������                               */
} HistoryChannelParaInfo, *LPHistoryChannelParaInfo;

/*!
*  @struct  tagHistoryChannelParaInfoMultiType
*  @brief   ��ʷͨ������������Ϣ(��չ)
*/
typedef struct tagHistoryChannelParaInfoMultiType
{
    DWORD dwEnableEndTime;      /*!< ����ʱ���Ƿ���Ч                       */
    TimeInfo cBeginTime;        /*!< ��ʼʱ��                               */
    TimeInfo cEndTime;          /*!< ����ʱ��                               */
    DWORD dwChannel;            /*!< ¼��ͨ��                               */
    DWORD dwDiskGroup;          /*!< ������Ϣ                               */
    DWORD dwType;               /*!< ��ʷ������                             */
    DWORD dwTaskType;           /*!< ��������                               */
} HistoryChannelParaInfoMultiType, *LPHistoryChannelParaInfoMultiType;

/*!
*  @struct  tagHistoryChannelStream
*  @brief   ��ʷͨ������Ϣ
*/
typedef struct tagHistoryChannelStream
{
    DWORD dwChannel;            /*!< ͨ����                                 */
    Buffer cBuffer;             /*!< ֡������                               */
    AbsoluteTime cTime;         /*!< ֡ʱ��                                 */
    /*!<
       ֡���ͣ�
       ��֡�ĸ�ʽ�任ʱ����֡������Ϊ HISTORY_STREAM_SWITCH_FRAME��
       ��֡Ϊ����֡ʱ����֡������Ϊ
     */
    DWORD dwFrameType;
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< ����                                   */
} HistoryChannelStream, *LPHistoryChannelStream;

/*!
*  @struct  tagHistoryChannelPositionInfo
*  @brief   ��ʷͨ����λ������Ϣ
*/
typedef struct tagHistoryChannelPositionInfo
{
    TimeInfo cSeekTime;         /*!< ��λʱ��                               */
} HistoryChannelPositionInfo, *LPHistoryChannelPositionInfo;


typedef struct tagServerInformation
{
    char cAddress[IP_ADDRESS_LEN];  /*!< ��ַ                                   */
    DWORD dwCommandPort;        /*!< ����˿�                               */
    DWORD dwMediaPort;          /*!< ý��˿�                               */
} ServerInformation, *LPServerInformation;


/*!
*  @struct  tagTransparentParaInfo
*  @brief   ͸�����������Ϣ
*/
typedef struct tagTransparentParaInfo
{
    DWORD dwMajorType;          /*!< ��������Ϣ                             */
    DWORD dwMinorType;          /*!< ��������Ϣ                             */
    Buffer cBuffer;             /*!< ������Ϣ                               */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< ����                                   */
} TransparentParaInfo, *LPTransparentParaInfo;


/*!
*  @struct  tagDeviceRegisterNetConfig
*  @brief   �豸ע����������
*/
typedef struct tagDeviceRegisterNetConfig
{
    char cCentralIP[IP_ADDRESS_LEN];    /*!< ע������IP��ַ                         */
    DWORD dwCentralPort;        /*!< ע�����Ķ˿�                           */
    DWORD dwInterval;           /*!< ע��ʱ����(s                         */
} DeviceRegisterNetConfig, *LPDeviceRegisterNetConfig;

/*!
*  @struct  tagDeviceRegisterInfo
*  @brief   �豸ע����Ϣ��˽��Э���ã��豸ID��DWORD�ͣ�
*/
typedef struct tagDeviceRegisterInfo
{
    DWORD dwDeviceID;                           /*!< �豸ID                             */
    char cDeviceIP[IP_ADDRESS_LEN];             /*!< �豸IP��ַ                         */
    char cDeviceMAC[MAC_ADDRESS_LEN];           /*!< �豸MAC��ַ                        */
    DWORD dwDeviceCmdPort;                      /*!< �豸����˿�                       */
    DWORD dwHTTPPort;                           /*!< HTTP�˿�                           */
    DWORD dwDeviceType;                         /*!< �豸����                           */
    char cDeviceVersion[VERSION_INFO_LEN];      /*!< �豸����汾��                     */
    DWORD dwDeviceMaxConnect;                   /*!< ��Ƶ�����������                   */
} DeviceRegisterInfo, *LPDeviceRegisterInfo;

/*!
*  @struct  tagDeviceRegisterInfoHxht
*  @brief   �豸ע����Ϣ��HxhtЭ���ã��豸ID���ַ�����
*/
typedef struct tagDeviceRegisterInfoHxht
{
    char cDeviceID[MAX_DEVICE_ID_LEN];          /*!< �豸���к�                         */
    char cDeviceIP[IP_ADDRESS_LEN];             /*!< �豸IP��ַ                         */
    char cDeviceMAC[MAC_ADDRESS_LEN];           /*!< �豸MAC��ַ                        */
    DWORD dwDeviceCmdPort;                      /*!< �豸����˿�                       */
    DWORD dwHTTPPort;                           /*!< HTTP�˿�                           */
    DWORD dwDeviceType;                         /*!< �豸����                           */
    char cDeviceVersion[VERSION_INFO_LEN];      /*!< �豸����汾��                     */
    DWORD dwDeviceMaxConnect;                   /*!< ��Ƶ�����������                   */
} DeviceRegisterInfoHxht, *LPDeviceRegisterInfoHxht;

/*!
*  @struct  tagDeviceStoreRegisterInfo
*  @brief   �豸�洢ע����Ϣ
*/
typedef struct tagDeviceStoreRegisterInfo
{
    char cDeviceID[MAX_DEVICE_ID_LEN];              /*!< �豸���кţ�"_T"                   */
    char cDeviceLinkType;                           /*!< �豸��������                       */
    char cDeviceIP[IP_ADDRESS_LEN];                 /*!< �豸IP��ַ                         */
    char cDeviceIP2[IP_ADDRESS_LEN];                /*!< �豸IP��ַ                         */
    DWORD dwDeviceMsgPort;                          /*!< �豸��Ϣ�˿�                       */
    DWORD dwDeviceVideoPort;                        /*!< �豸��Ƶ���Ӷ˿�                   */
} DeviceStoreRegisterInfo, *LPDeviceStoreRegisterInfo;

/*!
*  @struct  tagCentralRetInfo
*  @brief   ����ƽ̨ע����Ϣ
*/
typedef struct tagCentralRetInfo
{
    char cCentralTime[DATE_TIME_LEN];   /*!< ע��ƽ̨����ʱ��                   */
} CentralRetInfo, *LPCentralRetInfo;

typedef struct tagRegisterInfo
{
    DWORD dwDeviceID;           /*!< �豸ID                                 */
    BYTE cDeviceIP[IP_ADDRESS_LEN]; /*!< �豸IP                                 */
    DWORD dwDevicePort;         /*!< �豸ע��˿�                           */
    BYTE cDeviceMAC[MAC_ADDRESS_LEN];   /*!< �豸MAC��ַ                            */
    DWORD dwHttpPort;           /*!< Http�˿�                               */
    DWORD dwDeviceType;         /*!< �豸IP                                 */
    char cDeviceVersion[VERSION_INFO_LEN];  /*!< �豸�汾��Ϣ                           */
    DWORD dwDeviceMaxConnect;   /*!< �豸���������                         */
} RegisterInfo, *LPRegisterInfo;

/*!
*  @enum    eTransferFileType
*  @brief   �����ļ�����
*/
enum eTransferFileType
{
    eTransferFileTypeBegin = 0, /*!< ��ʼֵ                                 */
    eFileSystemUpdate,          /*!< �������ļ�                             */
    ePtzProtocol,               /*!< ��̨Э���ļ�                           */
    eDeviceConfig,              /*!< �豸�����ļ�                           */
    ePicture,                   /*!< ͼƬ�ļ�                               */
    eTransferFileTypeEnd,       /*!< ����ֵ                                 */
};


/*!
*  @struct  tagRemoteDownloadParaInfo
*  @brief	Զ���ļ���������������Ϣ
*/
typedef struct tagRemoteDownloadParaInfo
{
	enum eTransferSpeed eSpeed;		/*!< �����ٶ�����                           */
	enum eTransferFileType eFileType;	/*!< �ļ�����                               */
	char cFileName[MAX_FILENAME];	/*!< �ļ���                                 */
	DWORD dwFileTotalLen;		/*!< �ļ��ܴ�С                             */
} RemoteDownloadParaInfo, *LPRemoteDownloadParaInfo;

/*!
*  @struct	tagRemoteDownloadState
*  @brief	Զ���ļ�����״̬��Ϣ
*/
typedef struct tagRemoteDownloadState
{
	enum eTransferSpeed eSpeed;		/*!< �����ٶ�����                           */
	DWORD dwFileTransferLen;	/*!< �ļ��Ѵ����С                         */
	DWORD dwFileTotalLen;		/*!< �ļ��ܴ�С                             */
	enum eRemoteDownloadState eState;	/*!< �ļ�����״̬                           */
} RemoteDownloadState, *LPRemoteDownloadState;

/*!
*  @struct	tagFileUploadParaInfo
*  @brief	Զ���ļ��ϴ�����������Ϣ
*/
typedef struct tagFileUploadParaInfo
{
	enum eTransferSpeed eSpeed;		/*!< �����ٶ�����                           */
	enum eTransferFileType eFileType;	/*!< �ļ�����                               */
	char cFileName[MAX_FILENAME];	/*!< �ļ���                                 */
	DWORD dwFileTotalLen;		/*!< �ļ��ܴ�С                             */
} FileUploadParaInfo, *LPFileUploadParaInfo;

/*!
*  @struct	tagFileUploadState
*  @brief	Զ���ļ��ϴ�״̬��Ϣ
*/
typedef struct tagFileUploadState
{
	enum eTransferSpeed eSpeed;		/*!< �����ٶ�����                           */
	DWORD dwFileTransferLen;	/*!< �ļ��Ѵ����С                         */
	DWORD dwFileTotalLen;		/*!< �ļ��ܴ�С                             */
	enum eRemoteDownloadState eState;	/*!< �ļ�����״̬                           */
} FileUploadState, *LPFileUploadState;



/*!
*  @struct	tagFileDownloadParaInfo
*  @brief	Զ���ļ���������������Ϣ
*/
typedef struct tagFileDownloadParaInfo
{
	enum eTransferSpeed eSpeed;		/*!< �����ٶ�����                           */
	DWORD dwFileType;			/*!< �ļ�����                               */
	char cFileName[MAX_FILENAME];	/*!< �ļ���                                 */
	DWORD dwFileTotalLen;		/*!< �ļ��ܴ�С                             */
} FileDownloadParaInfo, *LPFileDownloadParaInfo;

/*!
*  @struct	tagFileDownloadState
*  @brief	Զ���ļ�����״̬��Ϣ
*/
typedef struct tagFileDownloadState
{
	enum eTransferSpeed eSpeed;		/*!< �����ٶ�����                           */
	DWORD dwFileTransferLen;	/*!< �ļ��Ѵ����С                         */
	DWORD dwFileTotalLen;		/*!< �ļ��ܴ�С                             */
	enum eRemoteDownloadState eState;	/*!< �ļ�����״̬                           */
} FileDownloadState, *LPFileDownloadState;

/*!
*  @struct	tagImageFileInfo
*  @brief    ץͼ�ļ���Ϣ
*/
typedef struct tagImageFileInfo
{
    DWORD m_dwFileSize;         /*!< �ļ���С                               */
    char m_sFileName[MAX_FILENAME]; /*!< �ļ���                                 */
    char m_sCreateTime[DATE_TIME_LEN];  /*!< �ļ�����ʱ��                           */
} ImageFileInfo, *LPImageFileInfo;

/*!
*  @struct  tagDataPacketType
*  @brief   �ļ�����ý�������
*/
typedef enum tagDataPacketType
{
    eDataTypeBegin = 0,
    eDataRequest,
    eDataPacket,
    eDataReply,
    eDataFinished,
    eDataCanceled,
    eDataError,
    eWriteError,
    eFlashFull,
    eFileCheckError,
    eFileAliveKeep,
    eDataTypeEnd,
} eDataPacketType;

/*!
*  @struct  tagFileTransferDataPacket
*  @brief   �ļ�����ý�������
*/
typedef struct tagFileTransferDataPacket
{
    eDataPacketType m_dwPacketType; /* 0:�����������ݴ��俪ʼ��   1:���ݰ���2:��Ӧ���� 3:������ */
    DWORD m_dwPacketSequence;
    DWORD m_dwPacketLen;
} FileTransferDataPacket, *LPFileTransferDataPacket;


/*!
*  @struct  tagDetectActionInfo
*  @brief	̽���¼���Ϣ
*/
typedef struct tagDetectActionInfo
{
	enum eDetectAction eType;		/*!< �¼�����                               */
	char cServerIP[IP_ADDRESS_LEN];	/*!< Զ�̷�������ַ                         */
	DWORD dwServerPort;			/*!< Զ�̷������˿�                         */
} DetectActionInfo, *LPDetectActionInfo;

/*!
*  @struct  tagDevAlarmInfo
*  @brief   �豸������Ϣ
*/
typedef struct tagDevAlarmInfo
{
    char szEventName[HXHT_MAX_XML_STRING_LEN];              /*!< �¼��� */
    char szDevName[HXHT_MAX_XML_STRING_LEN];                /*!< �����豸�� */
    DWORD dwDevType;                                        /*!< �����豸���ͣ�5������ͷ��6���������룬20�����ܷ�����Ԫ�� */
    char szAlarmTime[HXHT_MAX_XML_STRING_LEN];              /*!< ��������ʱ�� */
    DWORD dwAlarmType;                                      /*!< Խ���⡢������⡢���ټ�� */
    char szInfo[HXHT_MAX_XML_STRING_LEN];                   /*!< �Զ���Ĺ���Щ�����¼���˵�� */
} DevAlarmInfo, *LPDevAlarmInfo;

/*!
*  @struct  tagDevFaultInfo
*  @brief   �豸������Ϣ
*/
typedef struct tagDevFaultInfo
{
    char szDevIP[IP_ADDRESS_LEN];                           /*!< ǰ���豸IP */
    char szCurrentTime[HXHT_MAX_XML_STRING_LEN];            /*!< ��ǰʱ�� */
    char szDevID[HXHT_COMMON_STRING_LEN];                   /*!< �豸ID */
    DWORD dwDevType;                                        /*!< �豸���ͱ�� */
    DWORD dwFaultType;                                      /*!< �������ͱ�� */
    DWORD dwFaultID;                                        /*!< ���ϱ�� */
    char szFaultTime[HXHT_COMMON_STRING_LEN];               /*!< ���ϲ���ʱ�� */
    DWORD dwIsClear;                                        /*!< 0���¹��ϣ� or 1�����ϻָ��� */
} DevFaultInfo, *LPDevFaultInfo;

/*!
*  @struct  tagQuerySupport
*  @brief   ������ѯ��Ϣ
*/
typedef struct tagQuerySupportInfo
{
    char acIsSupport[MAX_QUERY_SUPPORT_NUM][MAX_SUPPORT_NAME_LEN]; /*!< ��������                        */
} QuerySupportInfo, *LPQuerySupportInfo;

/*!
*  @struct  tagQuerySupportResult
*  @brief   ������ѯ���
*/
typedef struct tagQuerySupportResult
{
    char acSupport[MAX_QUERY_SUPPORT_NUM][MAX_SUPPORT_NAME_LEN];    /*!< ֧�ֵĹ���                     */
    char acUnSupport[MAX_QUERY_SUPPORT_NUM][MAX_SUPPORT_NAME_LEN];  /*!< ��֧�ֵĹ���                   */
} QuerySupportResult, *LPQuerySupportResult;

/*!
*  @struct  tagSystemUpdateParam
*  @brief   ϵͳ��������
*/
typedef struct tagSystemUpdateParam
{
    char szFTPIP[IP_ADDRESS_LEN];                                   /*!< FTP������IP */
    DWORD dwFTPPort;                                                /*!< FTP�������˿� */
    char szFTPUserName[USERNAME_LEN];                               /*!< FTP�������û��� */
    char szFTPPassword[USERPASS_LEN];                               /*!< FTP�������û����� */
    char szFTPFilePath[MAX_FILENAME];                               /*!< FTP�����������ļ�·�� */
    char szFTPFileName[MAX_FILENAME];                               /*!< FTP�����������ļ��� */
} SystemUpdateParam, *LPSystemUpdateParam;

/*!
* @struct tagTimeSchemeItem
* @brief ʱ���
*/
typedef struct tagTimeSchemeItem
{
    char szItemDay[HXHT_COMMON_STRING_LEN];                         /*!< ��ʾ��ֹ���� */
    char szItemTime[HXHT_COMMON_STRING_LEN];                        /*!< ��ʾ��ֹʱ�� */
} TimeSchemeItem, *LPTimeSchemeItem;

/*!
* @struct tagScheme
* @brief ����ʱ��
*/
typedef struct tagScheme
{
    char szSchemeCycle[HXHT_COMMON_STRING_LEN];                     /*!< �ƻ����ڣ�day����Ϊ���ڣ�week����Ϊ���ڣ�month����Ϊ���� */
    TimeSchemeItem cTimeScheme[HXHT_MAX_ITEM_COUNT];                /*!< ʱ��ƻ��ڵ� */
    int nValidItem;                                                 /*!< TimeSchemeItem��Ч�ĸ��� */
} TimeScheme, *LPTimeScheme;

////////////////////////////////////Hxht//////////////////////////////////////

/*!
*  @struct  tagHxhtPTZSwitchStatus
*  @brief   Hxht PTZ����״̬
*/
typedef struct tagHxhtPTZSwitchStatus
{
    char acRandomScan[HXHT_COMMON_STRING_LEN];          /*!< �����ɨ���� on--�� off-��                                             */
    char acLight[HXHT_COMMON_STRING_LEN];               /*!< �ƹ⿪�� on--�� off-��                                                 */
    char acWiper[HXHT_COMMON_STRING_LEN];               /*!< ��ˢ���� on--�� off-��                                                 */
    char acProbe[HXHT_COMMON_STRING_LEN];               /*!< ̽ͷ���� on--�� off-��                                                 */
    char acPower[HXHT_COMMON_STRING_LEN];               /*!< ��Դ���� on--�� off-��                                                 */
    char acAutoFocus[HXHT_COMMON_STRING_LEN];           /*!< �Զ��۽����� on--�� off-��                                             */
    char acAutoBright[HXHT_COMMON_STRING_LEN];          /*!< �Զ���Ȧ���� on--�� off-��                                             */
    char acBackLight[HXHT_COMMON_STRING_LEN];           /*!< ���ⲹ������ on--�� off-��                                             */
    char acAutoNightVision[HXHT_COMMON_STRING_LEN];     /*!< �Զ�ҹ�ӿ��� on--�� off-��                                             */
    char acNightVision[HXHT_COMMON_STRING_LEN];         /*!< ҹ�ӿ��� on--�� off-��                                                 */
    char acWatchPoint[HXHT_COMMON_STRING_LEN];          /*!< ����λ����  on--�� off-��                                              */
    char acAid1[HXHT_COMMON_STRING_LEN];                /*!< ����1����   on--�� off-��                                              */
    char acAid2[HXHT_COMMON_STRING_LEN];                /*!< ����2����   on--�� off-��                                              */
} HxhtPTZSwitchStatus, *LPHxhtPTZSwitchStatus;

/*!
*  @struct  tagHxhtPTZAuxInfo
*  @brief   Hxht ����������Ϣ
*/
typedef struct tagHxhtPTZAuxInfo
{
    DWORD dwNum;                                        /*!< �������ر��                                                           */
    char acName[HXHT_COMMON_STRING_LEN];                /*!< ������������                                                           */
    char acSwitch[HXHT_COMMON_STRING_LEN];              /*!< on/off                                                                 */
} HxhtPTZAuxInfo, *LPHxhtPTZAuxInfo;

/*!
*  @struct  taHxhtPTZAuxSwitch
*  @brief   Hxht ��������
*/
typedef struct tagHxhtPTZAuxSwitch
{
    DWORD dwCount;                                      /*!< ֧�ֵĸ���������                                                       */
    HxhtPTZAuxInfo sAuxInfo[MAX_AUX_SWITCH_NUM];        /*!< ����������Ϣ                                                           */
} HxhtPTZAuxSwitch, *LPHxhtPTZAuxSwitch;

/*!
*  @struct  tagHxhtPresetPoint
*  @brief   HxhtԤ�õ���Ϣ
*/
typedef struct tagHxhtPresetPoint
{
    DWORD dwNum;                                        /*!< Ԥ�õ���                                                             */
    char acName[HXHT_COMMON_STRING_LEN];                /*!< Ԥ�õ�����                                                             */
} HxhtPresetPoint, *LPHxhtPresetPoint;

/*!
*  @struct  tagHxhtPresetPointSetting
*  @brief   HxhtԤ�õ�������Ϣ
*/
typedef struct tagHxhtPresetPointSetting
{
    DWORD dwCount;                                      /*!< ֧��Ԥ�õ���                                                           */
    HxhtPresetPoint sPoint[MAX_PRESET_POINT_NUM];       /*!< Ԥ�õ���Ϣ                                                             */
} HxhtPresetPointSetting, *LPHxhtPresetPointSetting;

/*!
*  @struct  tagHxhtPTZSupport
*  @brief   Hxht PTZ֧�ֹ���
*  @note    dwOpCmd˵����8300--��Ȧ��/С 8306--��Ȧֹͣ 8302--����䱶��/С 8308--���ֱ䱶ֹͣ
            8200--��̨��ʼ���� 8202--��ֹ̨ͣ���� 8204--�����ɨ��/�� 8206--Ԥ�õ�����
            8208--Ԥ�õ���� 8210--Ԥ�õ���� 8212--Ԥ�õ�������� 8304--�۽����ƴ�/С
            8310--�۽�ֹͣ 8400--�������� 0--ֹͣ 1--��̨�� 2--��̨�� 3--��̨�� 4--��̨��
            5--��Ȧ�� 6--��ȦС 7--�䱶�� 8--�䱶С 9--�۽��� 10--�۽�С 11--�����ɨ�� 12--�����ɨ��
            13--�ƹ⿪ 14--�ƹ�� 15--��ˢ�� 16--��ˢ�� 17--̽ͷ��Դ�� 18--̽ͷ��Դ��
            19--��ͷ��Դ�� 20--��ͷ��Դ��
*/
typedef struct tagHxhtPTZSupport
{
    char acDirect[HXHT_COMMON_STRING_LEN];              /*!< �Ƿ�֧�ַ������ y--֧�� n--��֧��                                     */
    char acBright[HXHT_COMMON_STRING_LEN];              /*!< �Ƿ�֧�ֹ�Ȧ(����)���� y--֧�� n--��֧��                               */
    char acZoom[HXHT_COMMON_STRING_LEN];                /*!< �Ƿ�֧�ֱ䱶���� y--֧�� n--��֧��                                     */
    char acFocus[HXHT_COMMON_STRING_LEN];               /*!< �Ƿ�֧�־۽����� y--֧�� n--��֧��                                     */
    char acFlip180[HXHT_COMMON_STRING_LEN];             /*!< �Ƿ�֧��180�ȷ�ת y--֧�� n--��֧��                                    */
    char acOriginalSetting[HXHT_COMMON_STRING_LEN];     /*!< �Ƿ�֧�ָֻ�ԭ������ y--֧�� n--��֧��                                 */
    char acEnterMenu[HXHT_COMMON_STRING_LEN];           /*!< �Ƿ�֧�ֽ���˵�ģʽ y--֧�� n--��֧��                                 */
    DWORD dwOpCmd[MAX_SUPPORT_OP_CMD_NUM];              /*!< ֧�ֵ���̨���������                                                   */
} HxhtPTZSupport, *LPHxhtPTZSupport;

/*!
*  @struct  tagHxhtPTZStatusInfo
*  @brief   Hxht PTZ״̬��Ϣ
*/
typedef struct tagPTZStatusInfo
{
    char acStatus[HXHT_COMMON_STRING_LEN];              /*!< ��̨״̬,����Ϊ5��'0'��'1' �ַ��������ַ�����5���ַ����δ��������ɨ���ƹ⡢��ˢ��̽ͷ����ͷ��״̬��'0'Ϊ�رգ�'1'Ϊ��*/
    HxhtPTZSwitchStatus sSwitchStatus;                  /*!< ����״̬                                                               */
    HxhtPTZAuxSwitch sAuxSwitch;                        /*!< ����������Ϣ                                                           */
    HxhtPresetPointSetting sPresetSetting;              /*!< Ԥ�õ�����                                                             */
    HxhtPTZSupport sSupport;                            /*!< ֧�ֵ�TPZ����                                                          */
} HxhtPTZStatusInfo, *LPHxhtPTZStatusInfo;

/*!
*  @struct  tagPanelStatusInfo
*  @brief   ���״̬��Ϣ
*/
typedef struct tagPanelStatusInfo
{
    DWORD dwStatus;                                     /*!< ���״̬,0Ϊδ����,1Ϊ������                                           */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                                                                   */
} PanelStatusInfo, *LPPanelStatusInfo;

/*!
*  @struct  tagPanelControlParameter
*  @brief   �����Ʋ���
*/
typedef struct tagPanelControlParameter
{
    DWORD dwControl;                                    /*!< ������,�μ�ePanelControlTypeֵ                                       */
    DWORD dwKeyBoardCode;                               /*!< ����ֵ,�μ�ePanelKeyBoardCodeTypeֵ                                  */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                                                                   */
} PanelControlParameter, *LPPanelControlParameter;

/*!
*  @enum    eRTPStreamTransferMode
*  @brief   RTP�����䷽ʽ
*/
typedef enum eRTPStreamTransferMode
{
    eRTPStreamTransferModeBegin     =   0,              /*!< ��ʼֵ                                 */
    eRTPGeneralTCP,                                     /*!< ��ͨ��TCP                              */
    eRTPGeneralUDP,                                     /*!< ��ͨ��UDP                              */
    eRTPStreamTransferModeEnd,                          /*!< ����ֵ                                 */
} eRTPStreamTransferMode;

/*!
*  @struct  eScreenControlStatus
*  @brief   ��Ļ����״̬
*/
typedef enum eScreenControlStatus
{
    eScreenControlStatusBegin                   = 0,    /*!< ��ʼֵ                                 */
    eScreenControlStatusLoopStart,                      /*!< ��ʼ��ת                               */
    eScreenControlStatusLoopStop,                       /*!< ֹͣ��ת                               */
    eScreenControlStatusSplitSingle,                    /*!< ������                                 */
    eScreenControlStatusSplitThree,                     /*!< ������                                 */
    eScreenControlStatusSplitFour,                      /*!< �Ļ���                                 */
    eScreenControlStatusSplitSix,                       /*!< ������                                 */
    eScreenControlStatusSplitNine,                      /*!< �Ż���                                 */
    eScreenControlStatusSplitTen,                       /*!< ʮ����                                 */
    eScreenControlStatusSplitTwelve,                    /*!< ʮ������                               */
    eScreenControlStatusSplitThirteen,                  /*!< ʮ������                               */
    eScreenControlStatusSplitFifteen,                   /*!< ʮ�廭��                               */
    eScreenControlStatusSplitSixteen,                   /*!< ʮ������                               */
    eScreenControlStatusEnd,                            /*!< ����ֵ                                 */
} eScreenControlStatus;

/*!
*  @enum    eResolutionMode
*  @brief   �ֱ���ģʽ
*/
typedef enum eResolutionMode
{
    eResolutionModeBegin                    =   0,          /*!< ��ʼֵ                                 */
    eResolutionModeAutoDiscern,                         /*!< �Զ�ʶ��ֱ���                             */
    eResolutionModeQCIF,                                    /*!< QCIF (176*144)                         */
    eResolutionModeCIF,                                     /*!< CIF (352*288 / 320*240 / 352*240)          */
    eResolutionModeHalfD1,                                  /*!< HalfD1 (704*288 / 640*240 / 704*240)       */
    eResolutionModeD1,                                      /*!< D1 (704*576 / 640*480 / 704*480)           */
    eResolutionModeDCIF,                                    /*!< DCIF (528*384 / 480*240)                   */
    eResolutionModeMD,                                      /*!< MD (512*288 / 416*240)                 */
    eResolutionModeVGA,                                     /*!< VGA (640*480)                          */
    eResolutionModeHD720,                                   /*!< HD720 (1280*720)                       */
    eResolutionModeQuadVGA,                                 /*!< QuadVGA (1280*960)                     */
    eResolutionModeUXGA,                                    /*!< UXGA (1600*1200)                       */
	eResolutionModeHD1080,									/*!< HD1080 (1920*1080)						*/
	eResolutionModeQXGA,									/*!< HD1080 (2048*1536)						*/
	eResolutionModeEnd,										/*!< ����ֵ									*/
} eResolutionMode;

/*!
*  @enum    eVGAResolutionMode
*  @brief   VGA�ֱ���
*/
typedef enum eVGAResolutionMode
{
    VGA_SVGA_800x600_60HZ                   = 0,
    VGA_SVGA_800x600_75HZ,
    VGA_XGA_1024x768_60HZ,
    VGA_XGA_1024x768_70HZ,
    VGA_SXGA_1280x1024_60HZ,
    VGA_1280x720P_60HZ,
    VGA_1920x1080i_60HZ,
    VGA_1920x1080p_60HZ
} eVGAResolutionMode;

/*!
*  @struct  eLogoPictureType
*  @brief   LogoͼƬ����
*/
typedef enum eLogoPictureType
{
    eLogoPictureTypeBegin                   = 0,        /*!< ��ʼֵ                                 */
    eLogoPictureTypeDecoderChannel,                     /*!< ����ͨ��LOGO                           */
    eLogoPictureTypeEnd,                                /*!< ����ֵ                                 */
} eLogoPictureType;

/*!
*  @enum    eDeviceChannelControl
*  @brief   �豸ͨ������
*/
typedef enum eDeviceChannelControl
{
    eDeviceChannelControlBegin       = 0,               /*!< ��ʼֵ                                 */
    eDeviceChannelControlShowLogo,                      /*!< ��ʾLOGO                               */
    eDeviceChannelControlHideLogo,                      /*!< ����LOGO                               */
    eDeviceChannelControlEnd,                           /*!< ����ֵ                                 */
} eDeviceChannelControl;

/*!
*  @enum    eDeviceProtocolType
*  @brief   �豸Э������
*/
typedef enum eDeviceProtocolType
{
    eDeviceProtocolTypeBegin         = 0,               /*!< ��ʼֵ                                 */
    eDeviceProtocolTypeAdapter,                         /*!< ����Ӧ�汾                             */
    eDeviceProtocolTypeClassics,                        /*!< ����汾                               */
    eDeviceProtocolTypeNewborn,                         /*!< �°汾                                 */
    eDeviceProtocolTypeEnd,                             /*!< ����ֵ                                 */
} eDeviceProtocolType;

/*!
*  @struct  tagRealStreamPara
*  @brief   ʵʱ�����Ӳ���
*/
typedef struct tagRealStreamPara
{
	DWORD	dwChannel;									/*!< ��ý��ͨ����							*/
	enum eStreamTransferMode	eTransferMode;					/*!< ����ģʽ								*/
	enum eStreamMediaType	eMediaType;						/*!< ��ý������								*/
	DWORD	dwReserve[DEF_RESERVE_NUM];					/*!< ����									*/
} RealStreamPara, *LPRealStreamPara;

/*!
*  @struct  tagUserLoginPara
*  @brief   �û���¼����
*/
typedef struct tagUserLoginPara
{
    char    sServerIP[MAX_ADDRESS_LEN];                 /*!< ��������IP��ַ                         */
    DWORD   dwCommandPort;                              /*!< ��¼���ӵ�����˿�                     */
    char    sUName[USERNAME_LEN];                       /*!< ��¼�û����û�����                     */
    char    sUPass[USERPASS_LEN];                       /*!< ��¼�û����û�����                     */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< ����                                   */
} UserLoginPara, *LPUserLoginPara;

/*!
*  @struct  tagHistoryStreamPara
*  @brief   ��ʷ�����Ӳ���
*/
typedef struct tagHistoryStreamPara
{
    DWORD   dwDiskGroup;                                /*!< ����                                   */
    DWORD   dwChannel;                                  /*!< ��ý��ͨ����                           */
    DWORD       dwEnableEndTime;                        /*!< ����ʱ���Ƿ���Ч                       */
    TimeInfo    cBeginTime;                             /*!< ��ʷ����ʼʱ��                         */
	TimeInfo	cEndTime;								/*!< ��ʷ������ʱ��							*/
	enum eHistoryStreamType	eStreamType;					/*!< ��ʷ������								*/
	enum eStreamTransferMode	eTransferMode;					/*!< ����ģʽ								*/
	DWORD	dwReserve[DEF_RESERVE_NUM];					/*!< ����									*/
} HistoryStreamPara, *LPHistoryStreamPara;

/*!
*  @struct  tagChannelOSDInformation
*  @brief   ͨ��OSD��Ϣ
*/
typedef struct tagChannelOSDInformation
{
    DWORD   dwEnable;                                   /*!< ����: 0Ϊ������, 1Ϊ����               */
    char    cOSDText[MAX_OSD_TEXT_STRING_LENGTH];       /*!< OSD��Ϣ                                */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< ����                                   */
} ChannelOSDInformation, *LPChannelOSDInformation;

/*!
*  @struct  tagStreamTransferPara
*  @brief	��ת�����Ӳ���
*/
typedef struct tagStreamTransferPara
{
	enum eStreamTransferMode	eTransferMode;					/*!< ����ģʽ								*/
	eStreamSourceType eStreamSourceTypeValue;			/*!< ��ý��Դ����							*/
	eVideoCodecMode	eVideoCodecType;					/*!< ��Ƶ�����ģʽ							*/
	enum eVoiceMode	eVoiceCoderType;						/*!< ��Ƶ�����ģʽ							*/
	eResolutionMode	eResolutionValue;					/*!< ͼ��ֱ���ģʽ							*/
    ChannelOSDInformation   cOSDInfo;                   /*!< OSD��Ϣ�ṹ                            */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< ����                                   */
} StreamTransferPara, *LPStreamTransferPara;

/*!
*  @struct  tagMediaServerInformation
*  @brief   ��ý���������Ϣ
*/
typedef struct tagMediaServerInformation
{
    DWORD   dwEnable;                                   /*!< ����: 0Ϊ������, 1Ϊ����               */
    char    sServerIP[MAX_ADDRESS_LEN];                 /*!< ��������IP��ַ                         */
    DWORD   dwServerPort;                               /*!< ��¼���ӵķ������˿�                   */
    char    sUName[USERNAME_LEN];                       /*!< ��¼�û����û�����                     */
    char    sUPass[USERPASS_LEN];                       /*!< ��¼�û����û�����                     */
    eRTPStreamTransferMode  eRTPStreamTransferValue;    /*!< RTP������ģʽ                          */
    char    sChannel[MAX_RTSP_SOURCE_STRING_LENGTH];    /*!< ��Ƶͨ��                               */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< ����                                   */
} MediaServerInformation, *LPMediaServerInformation;

/*!
*  @struct  tagHYPrivateServerInformation
*  @brief   HY˽��Э���������Ϣ
*/
typedef struct tagHYPrivateServerInformation
{
    DWORD   dwEnable;                                   /*!< ����: 0Ϊ������, 1Ϊ����               */
    eDeviceProtocolType eDeviceProtocolValue;           /*!< �豸Э��汾����                       */
    eStreamSourceType   eStreamSourceValue;             /*!< ��ý��Դ����                           */
    UserLoginPara   cUserLoginPara;                     /*!< ��¼������Ϣ                           */
    RealStreamPara  cRealStreamPara;                    /*!< ʵʱ��������Ϣ                         */
    HistoryStreamPara cHistoryStreamPara;               /*!< ��ʷ��������Ϣ                         */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< ����                                   */
} HYPrivateServerInformation, *LPHYPrivateServerInformation;

/*!
*  @struct  tagLocalHistoryInformation
*  @brief   ������ʷ����Ϣ
*/
typedef struct tagLocalHistoryInformation
{
    DWORD       dwEnable;                               /*!< ����: 0Ϊ������, 1Ϊ����               */
    DWORD       dwEnableEndTime;                        /*!< ����ʱ���Ƿ���Ч                       */
	TimeInfo	cBeginTime;								/*!< ��ʷ����ʼʱ��							*/
	TimeInfo	cEndTime;								/*!< ��ʷ������ʱ��							*/
	enum eHistoryStreamType	eStreamType;					/*!< ��ʷ������								*/
	DWORD	dwReserve[DEF_RESERVE_NUM];					/*!< ����									*/
} LocalHistoryInformation, *LPLocalHistoryInformation;

/*!
*  @struct  tagDecoderDynamicInformation
*  @brief   ��̬�����������Ϣ
*/
typedef struct tagDecoderDynamicInformation
{
    MediaServerInformation  cMediaServerInfo;           /*!< ��ý���������Ϣ                       */
    HYPrivateServerInformation  cHYPrivateServerInfo;   /*!< HY˽��Э���������Ϣ                   */
    LocalHistoryInformation cLocalHistoryInformation;   /*!< ������ʷ����Ϣ                         */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< ����                                   */
} DecoderDynamicInformation, *LPDecoderDynamicInformation;

/*!
*  @struct  tagDecoderChannelSourceConfig
*  @brief   ������ͨ����ƵԴ����
*/
typedef struct tagDecoderChannelSourceConfig
{
    MediaServerInformation  cMediaServerInfo;           /*!< ��ý���������Ϣ                           */
    HYPrivateServerInformation  cHYPrivateServerInfo;   /*!< HY˽��Э���������Ϣ                       */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< ����                                   */
} DecoderChannelSourceConfig, *LPDecoderChannelSourceConfig;

/*!
*  @struct  tagDecoderChannelLoopConfig
*  @brief   ������ͨ����ת����
*/
typedef struct tagDecoderChannelLoopConfig
{
    DWORD   dwEnable;                               /*!< �Ƿ�����                               */
    DWORD   dwPoolTime;                         /*!< ��Ѳʱ��                               */
    DecoderChannelSourceConfig cSource[MAX_DECODER_CHANNEL_SOURCE];/*!< ͨ����ƵԴ����                      */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< ����                                   */
} DecoderChannelLoopConfig, *LPDecoderChannelLoopConfig;

/*!
*  @struct  tagDecoderLoopStatus
*  @brief   ������ͨ����ѯ״̬
*/
typedef struct tagDecoderLoopStatus
{
    DWORD   dwChannelNumber;                            /*!< ͨ����                                 */
    eDecoderChannelStatus   eDecChStatus[MAX_DEC_CHANNEL_NUMBER];/*!< ͨ��״̬                      */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                                   */
} DecoderLoopStatus, *LPDecoderLoopStatus;

/*!
*  @struct  tagDecoderDeviceConfig
*  @brief   �������豸����
*/
typedef struct tagDecoderDeviceConfig
{
    DWORD   dwDecoderChannelNumber;                 /*!< ����ͨ������,���ݽ���ģʽ��������,ֻ��������   */
    eResolutionMode eDecodeMode;                    /*!< ����ģʽ                               */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< ����                                   */
} DecoderDeviceConfig, *LPDecoderDeviceConfig;

/*!
*  @struct  tagDecoderChannelInformation
*  @brief   ������ͨ����Ϣ
*/
typedef struct tagDecoderChannelInformation
{
    DWORD   dwDecoderState;                     /*!< ����ͨ��״̬��0-��̬���� 1��ѭ������           */
    DWORD   dwGetStreamMode;                        /*!< ȡ��ģʽ��0-δ���룬1-������2-����         */
    MediaServerInformation  cMediaServerInfo;           /*!< ��ý���������Ϣ                           */
    HYPrivateServerInformation  cHYPrivateServerInfo;   /*!< HY˽��Э���������Ϣ                       */
    LocalHistoryInformation cLocalHistoryInformation;       /*!< ������ʷ����Ϣ                         */
    StreamTransferPara  cStreamTransferPara;                /*!< ����������ת����Ϣ                     */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< ����                                   */
} DecoderChannelInformation, *LPDecoderChannelInformation;

/*!
*  @struct  tagDecoderChannelStatusInfo
*  @brief   ������ͨ��״̬��Ϣ
*/
typedef struct tagDecoderChannelStatusInfo
{
    eDecoderChannelStatus   eDecChStatus;               /*!< ͨ��״̬                   */
    eStreamSourceType   eStreamSourceTypeValue;         /*!< ��ý��Դ����               */
    DWORD   dwStreamBitrate;                        /*!< ��ý������(kbps)           */
    DWORD   dwVideoWidth;                           /*!< ��Ƶͼ����               */
    DWORD   dwVideoHeight;                      /*!< ��Ƶͼ��߶�               */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< ����                                   */
} DecoderChannelStatusInfo, *LPDecoderChannelStatusInfo;

/*!
*  @struct  tagDecoderChannelStatus
*  @brief   ������ͨ��״̬
*/
typedef struct tagDecoderChannelStatus
{
    DWORD   dwChannelNumber;                            /*!< ͨ����             */
    DecoderChannelStatusInfo    cDecChStatus[MAX_DEC_CHANNEL_NUMBER];/*!< ������ͨ��״̬��*/
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                   */
} DecoderChannelStatus, *LPDecoderChannelStatus;

/*!
*  @struct  tagDecoderChannelControl
*  @brief   ������ͨ������
*/
typedef struct tagDecoderChannelControl
{
    eDecoderChannelStatus   eDecChStatus[MAX_DEC_CHANNEL_NUMBER];/*!< ������ͨ��״̬*/
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< ����                                   */
} DecoderChannelControl, *LPDecoderChannelControl;

/*!
*  @struct  tagDecoderSetPlayStatusParameter
*  @brief   ���ý�����ͨ������״̬����
*/
typedef struct tagDecoderSetPlayStatusParameter
{
    eStreamPlayControlStatus    ePlayControlStatus;     /*!< ������״̬����     */
    DWORD dwParameter[MAX_PLAY_CONTROL_PARAMETER];          /*!< ������״̬���Ʋ���     */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                   */
} DecoderSetPlayStatusParameter, *LPDecoderSetPlayStatusParameter;

/*!
*  @struct  tagDecoderPlayStatusParameter
*  @brief   ������ͨ������״̬����
*/
typedef struct tagDecoderPlayStatusParameter
{
    eStreamSourceType   eStreamSourceTypeValue;             /*!< ��ý��Դ����           */
    DWORD       dwEnableEndTime;                        /*!< ����ʱ���Ƿ���Ч       */
    TimeInfo    cBeginTime;                             /*!< ��ʷ����ʼʱ��     */
    TimeInfo    cEndTime;                                   /*!< ��ʷ������ʱ��     */
    TimeInfo    cCurrentTime;                               /*!< ��ǰ���ŵ���ʷ��ʱ��   */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                   */
} DecoderPlayStatusParameter, *LPDecoderPlayStatusParameter;

/*!
*  @struct  tagDecoderGetPlayStatusParameter
*  @brief   ��ȡ������ͨ������״̬����
*/
typedef struct tagDecoderGetPlayStatusParameter
{
    DWORD   dwChannelNumber;                            /*!< ͨ����             */
    DecoderPlayStatusParameter  cDecChPlayStatus[MAX_DEC_CHANNEL_NUMBER];/*!< ������ͨ������״̬��Ϣ*/
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                   */
} DecoderGetPlayStatusParameter, *LPDecoderGetPlayStatusParameter;

/*!
*  @struct  tagDecoderSetDisplayStatusParameter
*  @brief   ���ý���ͨ����ʾ״̬����
*/
typedef struct tagDecoderSetDisplayStatusParameter
{
    eDisplayControlStatus   eDisplayControlStatusValue;     /*!< ��ʾ����״̬��Ϣ       */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                   */
} DecoderSetDisplayStatusParameter, *LPDecoderSetDisplayStatusParameter;

/*!
*  @struct  tagDecoderDisplayConfig
*  @brief   ������ʾ����
*/
typedef struct tagDecoderDisplayConfig
{
    eVGAResolutionMode  eVGAResolution;             /*!<    �ֱ���                              */
    eScreenControlStatus    eScreenControlStatusValue;      /*!< ��ʾ����״̬��Ϣ                           */
    DWORD   dwDecoderChannel[MAX_DISPLAY_SCREEN_NUMBER];    /*!< �󶨵Ľ���ͨ����                           */
    DWORD   dwEnlargeWindow;                        /*!< ���ڷŴ�, 0xFFFFFFFF��ʾ���Ŵ�,������ʾ���ڱ��    */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                                   */
} DecoderDisplayConfig, *LPDecoderDisplayConfig;

/*!
*  @struct  tagChannelChromaConfig
*  @brief   ����ͨ����ѧ����
*/
typedef struct tagChannelChromaConfig
{
    DWORD dwBrightness;                             /*!< ����,0-255                             */
    DWORD dwContrast;                               /*!< �Աȶ�,0-255                           */
    DWORD dwSaturation;                             /*!< ���Ͷ�,0-255                           */
    DWORD dwHue;                                    /*!< ɫ��,0-255                             */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                                   */
} ChannelChromaConfig, *LPChannelChromaConfig;

/*!
*  @struct  tagDecoderChannelConfig
*  @brief   ������ͨ������
*/
typedef struct tagDecoderChannelConfig
{
    DWORD   dwDecChanScaleStatus;                   /*!< ����ͨ����ʾ���ſ��ƣ�1-������ʾ��0-��ʵ��ʾ   */
    ChannelChromaConfig cChannelChromaConfig;           /*!< ��ѧ����                               */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< ����                                   */
} DecoderChannelConfig, *LPDecoderChannelConfig;

/*!
*  @struct  tagDecoderVideoStandardConfig
*  @brief   ������ͨ����Ƶ��ʽ
*/
typedef struct tagDecoderVideoStandardConfig
{
    DWORD   dwVideoStandard;                        /*!< ��������Ƶ��ʽ: 0-PAL��1-NTSC                  */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< ����                                   */
} DecoderVideoStandardConfig, *LPDecoderVideoStandardConfig;

/*!
*  @struct  tagHistoryStreamMultiTypeQueryFactor
*  @brief   ��ʷ����ѯ����
*/
typedef struct tagHistoryStreamMultiTypeQueryFactor
{
    DWORD               dwChannel;                      /*!< ͨ����                                 */
    DWORD               dwDiskGroup;                    /*!< ����                                   */
    DWORD               dwStreamType;                   /*!< ��ʷ������                             */
    char                cBeginTime[15];                 /*!< ��ʼʱ��                               */
    char                cEndTime[15];                   /*!< ����ʱ��                               */
} HistoryStreamMultiTypeQueryFactor, *LPHistoryStreamMultiTypeQueryFactor;

/*!
*  @struct  tagTransmitHistoryStreamQueryFactor
*  @brief   ת����ʷ����ѯ����
*/
typedef struct tagTransmitHistoryStreamQueryFactor
{
    UserLoginPara   cUserLoginPara;                 /*!< ��¼������Ϣ                           */
    eDeviceProtocolType eDeviceProtocolValue;           /*!< �豸Э��汾����                           */
    HistoryStreamMultiTypeQueryFactor cFactor;          /*!< ��ʷ��ѯ����                           */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< ����                                   */
} TransmitHistoryStreamQueryFactor, *LPTransmitHistoryStreamQueryFactor;

//////////////////////////////////////////////////////////////////////////
//�ӿ�
//////////////////////////////////////////////////////////////////////////
/////////////////////////////������Ϣ/////////////////////////////////////

#endif

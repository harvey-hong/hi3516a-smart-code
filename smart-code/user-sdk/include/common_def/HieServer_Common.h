#ifndef HIE_SERVER_COMMON_H

#define HIE_SERVER_COMMON_H

//////////////////////////////////////////////////////////////////////////
//宏定义
//////////////////////////////////////////////////////////////////////////
//HieServer通用信息定义文件

//参数属性

/** @brief 入参                                                                         */
#define IN

/** @brief 出参                                                                         */
#define OUT

/** @brief 入出参                                                                       */
#define IN_OUT

/** @brief 实时流最大客户数                                                             */
#define REAL_STREAM_LIMIT                   (8)

/** @brief 语音流最大客户端                                                             */
#define VOICE_STREAM_LIMIT                  REAL_STREAM_LIMIT

/** @brief 用户名长度                                                                   */
#define USERNAME_LEN                        (32)

/** @brief 日期时间长度                                                                 */
#define DATE_TIME_LEN                       (15)

/** @brief 用户密码长度                                                                 */
#define USERPASS_LEN                        (32)

/** @brief 设备ID长度                                                                   */
#define MAX_DEVICE_ID_LEN                   (32)

/** @brief IP地址长度(含结束符)                                                         */
#define IP_ADDRESS_LEN                      (16)

/** @brief MAC地址长度(含结束符)                                                        */
#define MAC_ADDRESS_LEN                     (18)

/** @brief MAC地址二进制长度                                                            */
#define MAC_BINARY_ADDRESS_LEN              (6)

/** @brief 版本信息长度(含结束符)                                                       */
#define VERSION_INFO_LEN                    (20)

/** @brief 最大文件名长度                                                               */
#define MAX_FILENAME                        (256)

/** @brief 域名长度(含结束符)                                                           */
#define DOMAIN_ADDRESS_LEN                  (256)

/** @brief 地址长度(含结束符)                                                                       */
#define MAX_ADDRESS_LEN             (DOMAIN_ADDRESS_LEN)

/** @brief 默认保留字段个数                                                             */
#define DEF_RESERVE_NUM                     (3)

/** @brief 配置信息最大长度                                                             */
#define MAX_CFG_LEN                         (128 * 1024 * 2)

/** @brief 描述信息最大长度                                                             */
#define MAX_DESCRIPTION_INFO_LEN            (100)

/** @brief 扩展信令Method的最大长度                                                         */
#define MAX_METHOD_LEN                      (32)

/** @brief 扩展信令Answer的最大长度                                                         */
#define MAX_ANSWER_LEN                      (32)

/** @brief 扩展信令最大设备类型长度                                                         */
#define MAX_TYPE_LEN                        (128)

/** @brief 扩展信令Usage的最大长度                                                          */
#define MAX_USAGE_LEN                       (128)

/** @brief 扩展信息的最大长度                                                               */
#define MAX_EX_INFO_LEN                     (32 * 1024)

/** @brief 错误描述信息的最大长度                                                           */
#define MAX_ERROE_MESSAGE_LEN               (256)

/** @brief Hxht日期时间长度                                                                 */
#define HXHT_DATA_TIME_LEN                  (32)

/** @brief Hxht流类型长度                                                                   */
#define HXHT_STREAM_TYPE_LEN                (32)

/** @brief Hxht普通字符串长度                                                               */
#define HXHT_COMMON_STRING_LEN              (32)

/** @brief Hxht最大流时间信息个数                                                           */
#define MAX_STREAM_TIME_INFO_ITEN           (50)

/** @brief Hxht最大录像片段个数                                                             */
#define MAX_SEGMENT_ITEM                    (50)

/** @brief Hxht最大预置点个数                                                               */
#define MAX_PRESET_POINT_NUM                (128)

/** @brief Hxht最大辅助开关个数                                                             */
#define MAX_AUX_SWITCH_NUM                  (16)

/** @brief Hxht最大支持的云台控制命令号个数                                                 */
#define MAX_SUPPORT_OP_CMD_NUM              (64)

/** @brief Hxht最大十六进制485数据的长度                                                    */
#define MAX_485_DATA_LEN                    (128)

/** @brief Hxht支持的最大能力查询数                                                         */
#define MAX_QUERY_SUPPORT_NUM               (9)

/** @brief Hxht最大功能名称长度                                                             */
#define MAX_SUPPORT_NAME_LEN                (128)

/** @brief Hxht最大时间计划节点数                                                           */
#define HXHT_MAX_ITEM_COUNT                 (32)

/** @brief Hxht最大字符串长度                                                               */
#define HXHT_MAX_XML_STRING_LEN             (180)

/** @brief 单服务器最大解码通道数                                           */
#define MAX_DEC_CHANNEL_NUMBER      (64)

/** @brief 播放控制参数个数                                                 */
#define MAX_PLAY_CONTROL_PARAMETER  (5)

/** @brief 最大解码通道轮转视频源个数                                                                           */
#define MAX_DECODER_CHANNEL_SOURCE  (16)

/** @brief 屏幕控制参数个数                                                 */
#define MAX_SCREEN_CONTROL_PARAMETER    (5)

/** @brief 单服务器最大分屏数                                                                       */
#define MAX_DISPLAY_SCREEN_NUMBER   (64)

/** @brief LOGO图片参数个数                                                 */
#define MAX_LOGO_PICTURE_PARAMETER  (5)

/** @brief OSD文本字符串                                                    */
#define MAX_OSD_TEXT_STRING_LENGTH  (64)

/** @brief RTSP源字符串                                                 */
#define MAX_RTSP_SOURCE_STRING_LENGTH   (128)

//////////////////////////////////////////////////////////////////////////
//历史流帧宏定义
//////////////////////////////////////////////////////////////////////////

/** @brief 历史流异常结束                                                               */
#define HISTORY_STREAM_EXCEPTION    (0x01000000)

/** @brief 历史流切换帧宏定义                                                           */
#define HISTORY_STREAM_SWITCH_FRAME (0x02000000)

/** @brief 历史流跳到新的时间片                                                         */
#define HISTORY_STREAM_TIME_JUMP    (0x03000000)

/** @brief 历史流结束帧宏定义                                                           */
#define HISTORY_STREAM_TIME_END     (0x04000000)

/** @brief 历史流数据查询完毕                                                           */
#define HISTORY_STREAM_TIME_CURR    (0x05000000)

//////////////////////////////////////////////////////////////////////////
//远程事件类型
//////////////////////////////////////////////////////////////////////////

/** @brief 报警事件                                                                     */
#define USEREVENT_ALARM_NOTICE          (0x00000001)

/** @brief 心跳丢失,网络断开                                                            */
#define USEREVENT_HEARTBEAT_LOST        (0x00000002)

/** @brief 网络重连成功                                                                 */
#define USEREVENT_NET_RECOVER           (0x00000004)

/** @brief 远程用户断开                                                                 */
#define USEREVENT_USER_DISCONNECT       (0x00000008)

/** @brief 远程流媒体断开                                                               */
#define USEREVENT_STREAM_DISCONNECT     (0x00000010)

/** @brief 硬盘组管理事件                                                               */
#define USEREVENT_DISKGROUP_MANAGE      (0x00000020)

/** @brief 历史流事件通知                                                               */
#define USEREVENT_HISTORYSTREAM_NOTICE  (0x00000040)

/** @brief 实时流启动连接ID通知                                                         */
#define USEREVENT_REALSTREAM_STARTLINK  (0x00000080)

/** @brief 实时流停止连接ID通知                                                         */
#define USEREVENT_REALSTREAM_STOPLINK   (0x00000100)

/** @brief 语音流启动连接ID通知                                                         */
#define USEREVENT_VOICESTREAM_STARTLINK (0x00000200)

/** @brief 语音流停止连接ID通知                                                         */
#define USEREVENT_VOICESTREAM_STOPLINK  (0x00000400)

/** @brief 历史流销毁事件通知                                                           */
#define USEREVENT_HISTORYSTREAM_DESTROYLINK     (0X00000800)

/** @brief 历史流启动事件通知                                                           */
#define USEREVENT_HISTORYSTREAM_STARTLINK       (0X00001000)

/** @brief 历史流停止事件通知                                                           */
#define USEREVENT_HISTORYSTREAM_STOPLINK        (0X00002000)

/** @brief 历史流创建事件通知                                                           */
#define USEREVENT_HISTORYSTREAM_CREATELINK      (0X00004000)


//////////////////////////////////////////////////////////////////////////
//历史流录像类型宏定义
//////////////////////////////////////////////////////////////////////////
/** @brief 普通录像类型                                                                             */
#define GENERAL_RECORD              (0X00000001)

/** @brief 手动录像类型                                                                             */
#define MANUAL_RECORD               (0X00000002)

/** @brief 报警录像类型                                                                             */
#define ALARM_RECORD                (0X00000004)

/** @brief 移动录像类型                                                                             */
#define MOTION_RECORD               (0X00000008)

/** @brief 所有录像类型                                                                             */
#define ALL_STREAM_MEDIA			(GENERAL_RECORD | MANUAL_RECORD | MOTION_RECORD | ALARM_RECORD)


#define  PrivateProtocolVersion_100   (10000)  /* version 1.0.0 == 1*10000 + 0*100 + 0*1 */
#define  PrivateProtocolVersion_101   (10001)  /* version 1.0.1 == 1*10000 + 0*100 + 1*1 */

//////////////////////////////////////////////////////////////////////////
//基本类型
//////////////////////////////////////////////////////////////////////////
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
//typedef void *HANDLE;					// change by linhh 20160508
#define	HANDLE	void*
//////////////////////////////////////////////////////////////////////////
//枚举
//////////////////////////////////////////////////////////////////////////

/* hzg added 20170410 for async control Private Protocol Server start */
enum eCmdControlPrivateServer
{
    WS_CMD_Begin = 0,
    WS_CMD_StartPrivateServer,              /*!< 启动私有协议服务   */
    WS_CMD_StopPrivateServer,               /*!< 停止私有协议服务   */
    WS_CMD_RestartPrivateServer,          /*!< 重启私有协议服务   */
};
/* hzg added 20170410 for async control Private Protocol Server end */

typedef struct tagPrivateServerCmdCtrlList
{
    eCmdControlPrivateServer eCmdCtrl;            /*!< 一条Cmd                       */
    struct tagPrivateServerCmdCtrlList *pNext;   /*!< 指向下一条Cmd     */
} PrivateServerCmdCtrlList, *LPPrivateServerCmdCtrlList;
/* hzg added 20170410 for async control Private Protocol Server stop */

#ifndef DEF_ENUM_ALERT_TYPE
#define DEF_ENUM_ALERT_TYPE

/*!
*  @enum    eAlertType
*  @brief   报警和异常警告类型
*/
enum eAlertType
{
    ALERT_ALARMIN,              /*!< 报警输入                           */
    ALERT_MOTION,               /*!< 移动侦测                           */
    ALERT_ENCODEERROR,          /*!< 编码异常                           */
    ALERT_DISKERROR,            /*!< 硬盘错误                           */
    ALERT_DISKFULL,             /*!< 硬盘满                             */
    ALERT_IPCONFLICT,           /*!< IP冲突                             */
    ALERT_ILLEGEACCESS,         /*!< 非法访问                           */
    ALERT_RETICLEDISCONNECT,    /*!< 网线断                             */
    ALERT_VIDEOLOST,            /*!< 视频丢失                           */
    ALERT_VIDEOEXCEPTION,       /*!< 视频异常                           */
    ALERT_DISKGROUP_ERROR,      /*!< 盘组异常                           */
};

#endif//DEF_ENUM_ALERT_TYPE

/*!
*  @enum    eProtocolID
*  @brief   协议类型
*/
enum eProtocolID
{
    eProtocolBegin = -1,    //协议开始

    eProtocolHYPrivate,     //私有协议
    eProtocolTideMobile,    //TideMobile手机协议
	eProtocolMegaEyes,		//互信互通（全球眼）
    eProtocolRTSP,          //RTSP协议
    eProtocolONVIF,
    eProtocolHTTP,
    eProtocolDiscovery,
    eProtocolRTMP,          //RTMP协议
    eProtocolIPDetection,          //IP冲突检测服务
    eProtocolPDNS,          //Private DNS client service
	eProtocolTutkP2P,       //TUTK P2P device service protocol
	eProtocolUPNP,       //UPNP device discover protocol
    eProtocolEnd,           //协议结束
};

/*!
*  @enum    eErrorValue
*  @brief   错误值类型（建议添加错误码时，在最后面添加）
*/
enum eErrorValue
{
    eErrorNone = 0,             /*!< 无错误                                 */
    eErrorFailed,               /*!< 失败                                   */
    eErrorNoInitializeSDK,      /*!< 未初始化SDK                            */
    eErrorHandle,               /*!< 句柄错误                               */
    eErrorParameter,            /*!< 参数错误                               */
    eErrorMemory,               /*!< 内存错误                               */
    eErrorSystemFailed,         /*!< 操作系统错误                           */
    eErrorNoIdleResource,       /*!< 无可用资源                             */
    eErrorTimeOut,              /*!< 超时错误                               */
    eErrorFunctionVersionLow,   /*!< 功能版本低于服务器                     */
    eErrorFunctionVersionHigh,  /*!< 功能版本高于服务器                     */
    eErrorTaskNoRun,            /*!< 任务未启动                             */
    eErrorAlreadyRun,           /*!< 重复启动                               */
    eErrorConnectFailed,        /*!< 连接失败                               */
    eErrorSessionDisconnect,    /*!< 连接断开                               */
    eErrorCommandSendFailed,    /*!< 命令发送失败                           */
    eErrorServerReject,         /*!< 服务器拒绝                             */
    eErrorInterfaceUnset,       /*!< 接口未设置                             */
    eErrorHYPrivate,            /*!< 私有协议库不存在                       */
    eErrorMegaEyes,             /*!< 全球眼协议库不存在                     */
    eErrorFunction,             /*!< 协议中函数不存在                       */
    eErrorUserName,             /*!< 用户名错误                             */
    eErrorUserPass,             /*!< 用户密码错误                           */
    eErrorIPLimited,            /*!< 用户IP限制                             */
    eErrorMACLimited,           /*!< 用MAC限制                              */
    eErrorUserNumOverflow,      /*!< 登陆用户过多                           */
    eErrorUserHeartBeat,        /*!< 用户心跳订阅失败                       */
    eErrorGetConfigurationPort, /*!< 登陆时获取端口配置信息失败             */
    eErrorServiceReseting,      /*!< 网络服务重启中                         */
    eErrorHistoryStreamCreate,  /*!< 历史流创建的指针为NULL                 */
    eErrorGetDataSize,          /*!< 获取历史数据大小的指针为NULL           */
    eErrorHistoryQueryCreate,   /*!< 历史查询创建的指针为NULL               */
    eErrorHistoryQueryNext,     /*!< 历史查询下一条的指针为NULL             */
    eErrorTideMobile,           /*!< TideMobile协议不存在                   */
    eErrorHxht,                 /*!< MegaEyes协议不存在(Hxht是该协议公司的名字) */
    eErrorRTSP,                 /*!< RTSP协议不存在                         */
    eErrorONVIF,
    eErrorHTTP,
    eErrorRTMP,
    eErrorNoSupportCommand,     /*!< 不支持的命令                           */
    eErrorUnserialize,          /*!< 反序列化失败                           */
    eErrorNoSupportBandwith,	/*!<不支持带宽估算		*/
};

/*!
*  @enum    eConfigureType
*  @brief   配置信息类型
*/
enum eConfigureType
{
    eConfigureTypeBegin = 0,    /*!< 起始值                                 */
    eConfigureDevice,           /*!< 设备信息                               */
    eConfigureNetWork,          /*!< 网络信息                               */
    eConfigureManagerServer,    /*!< 管理服务器信息                         */
    eConfigureTime,             /*!< 时间信息                               */
    eConfigureChannel,          /*!< 通道信息                               */
    eConfigureCompression,      /*!< 压缩信息                               */
    eConfigureTypeEnd,          /*!< 结束值                                 */
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
*  @brief   获取服务状态类型
*/
enum eGetServerStateType
{
    eGetServerStateTypeBegin = 0,   /*!< 起始值                                 */
    eRealStreamState,           /*!< 实时流状态                             */
    eRemoteUser,                /*!< 用户状态                               */
    eHistroyState,              /*!< 历史流状态                             */
    eGetServerStateTypeEnd,     /*!< 结束值                                 */
};

/*!
*  @enum    eManagerServer
*  @brief   管理服务器类型
*/
enum eManagerServerType
{
    eManagerServerTypeBegin = 0,    /*!< 起始值                                 */
    eManagerCenter,             /*!< 中心管理服务器                         */
    eManagerMediaStream,        /*!< 流媒体服务器                           */
    eManagerStorage,            /*!< 存储服务器                             */
    eManagerAlarm,              /*!< 报警服务器                             */
    eManagerServerTypeEnd,      /*!< 结束值                                 */
};

/*!
*  @enum    eRemoteUserState
*  @brief   用户状态类型
*/
enum eRemoteUserState
{
    eRemoteUserStateBegin = 0,  /*!< 起始值                                 */
    eUserTimeOut,               /*!< 超时(心跳超时)                         */
    eUserNetWorkError,          /*!< 连接异常                               */
    eRemoteUserStateEnd,        /*!< 结束值                                 */
};

/*!
*  @enum    eMediaCodeType
*  @brief   流媒体码流类型
*/
enum eMediaCodeType
{
    eMediaCodeTypeBegin = 0,    /*!< 起始值                                 */
    eMediaCodeMain,             /*!< 主码流                                 */
    eMediaCodeAssist,           /*!< 辅码流                                 */
    eMediaCodeHDAssist,         /*!< 高清辅码流                             */
    eMediaCodeOnlyMain,
    eMediaCodecOnlyAssist,			//2只传输子码流视频
    eMediaCodecOnlyMainAndAssist,	//2同时请求主码流与子码流视频
    eMediaCodeNewHisMain,
    eMediaCodeNewHisAssist,
    eMediaCodeTypeEnd,          /*!< 结束值                                 */
};

/*!
*  @enum    eStreamMediaType
*  @brief   流媒体类型
*/
enum eStreamMediaType
{
    eStreamMediaTypeBegin = 0,  /*!< 起始值                                 */
    eMainVideoAndSound,         /*!< 主码流音视频                           */
    eMainVideo,                 /*!< 主码流视频                             */
    eMainSound,                 /*!< 主码流音频                             */
    eAssistVideo,               /*!< 辅码流视频                             */
    eAssistHDVideo,             /*!< 高清子码流视频                         */
    eAssistOnlyVideo,					// 只传输子码流视频
    eAssistAndMainOnlyVideo,			// 同时请求主码流与子码流视频

    eMainNewHisVideoAndSound,       //主码流 历史音视频
    eMainNewHisVideo,                       //主码流 历史视频
    eAssistNewHisVideo,                     //子码流 历史视频
    eStreamMediaTypeEnd,        /*!< 结束值                                 */
};

/*!
*  @enum    eHistoryStreamType
*  @brief   历史流类型
*/
enum eHistoryStreamType
{
    eHistoryStreamTypeBegin = 0,    /*!< 起始值                                 */
    eAllStreamMedia,            /*!< 所有流媒体                             */
    eGeneralRecord,             /*!< 普通录像                               */
    eManualRecord,              /*!< 手动录像                               */
    eMotionRecord,              /*!< 移动录像                               */
    eAlarmRecord,               /*!< 报警录像                               */
    eHistoryStreamTypeEnd,      /*!< 结束值                                 */
};

/*!
*  @enum    eStreamActionType
*  @brief   流事件类型
*/
enum eStreamActionType
{
    eStreamActionTypeBegin = 0, /*!< 起始值                                 */
    eRequestConnect,            /*!< 请求连接                               */
    eRequestDisConnect,         /*!< 请求断开                               */
    eConnected,                 /*!< 已连接                                 */
    eDisconnected,              /*!< 已断开                                 */
    eStreamActionTypeEnd,       /*!< 结束值                                 */
};

/*!
*  @enum    eRemoteDownloadState
*  @brief   远程下载状态
*/
enum eRemoteDownloadState
{
    eRemoteDownloadStateBegin = 0,  /*!< 起始值                                 */
    eTransferOver,              /*!< 文件传输结束                           */
    eTransfer,                  /*!< 文件传输中                             */
    eRemoteDownloadStateEnd,    /*!< 结束值                                 */
};

/*!
*  @enum    eTransferSpeed
*  @brief   数据传输速度类型
*/
enum eTransferSpeed
{
    eTransferSpeedBegin = 0,    /*!< 起始值                                 */
    eQuickSpeed,                /*!< 最快速度                               */
    eNormalSpeed,               /*!< 普通速度                               */
    eSlowSpeed,                 /*!< 较慢速度                               */
    eTransferSpeedEnd,          /*!< 结束值                                 */
};

/*!
*  @enum    eDetectAction
*  @brief   远程探测事件类型
*/
enum eDetectAction
{
    eDetectActionBegin = 0,     /*!< 起始值                                 */
    eDetectGetCfg,              /*!< 获取配置信息                           */
    eDetectSetCfg,              /*!< 设置配置信息                           */
    eDetectActionEnd,           /*!< 结束值                                 */
};

/*!
*  @enum    eFileLockOperationCode
*  @brief   文件锁操作
*/
enum eFileLockOperationCode
{
    eUnlockFile = 0,            /*!< 解锁                                   */
    eLockFile,                  /*!< 开锁                                   */
};


/*!
*  @enum    eImageFormat
*  @brief   抓图文件格式
*/
enum eImageFormat
{
    eImageFormatBegin = 0,      /*!< 起始值                                 */
    eBmpFormat,                 /*!< 位图格式                               */
    eJpgFormat,                 /*!< jpg格式                                */
    eImageFormatEnd,            /*!< 结束值                                 */
};

/*!
*  @enum    eQueryStatus
*  @brief   查询状态
*/
enum eQueryStatus
{
    eQueryOK = 0,               /*!< 查询成功                               */
    eQueryFailed,               /*!< 查询失败                               */
    eQueryBusy,                 /*!< 查询忙                                 */
    eQueryFinished,             /*!< 查询结束                               */
};

/*!
*  @enum    eRemoteDeviceControl
*  @brief   远程设备控制
*/
enum eRemoteDeviceControl
{
    eRemoteDeviceControlBegin = 0,  /*!< 起始值                                 */
    eDeviceReboot,                  /*!< 重启动                                 */
    eDeviceHalt,                    /*!< 关机                                   */
    eDeviceStandby,                 /*!< 待机                                   */
    eDeviceSetDefault,              /*!< 恢复系统默认                           */
    eDeviceSendTestEmail,           /*!< 发送测试邮件                           */
    eDeviceSetDefense,              /*!< 布防                                   */
    eDeviceUnsetDefense,            /*!< 撤防                                   */
    eRemoteDeviceControlEnd,        /*!< 结束值                                 */
};

/*!
*  @enum    eDiskGroupType
*  @brief    盘组类型
*/
enum eDiskGroupType
{
    eDiskGroupTypeBegin = 0,    /*!< 起始值                                 */
    eDiskGroupNormal,           /*!< 普通盘组                               */
    eDiskGroupAlarm,            /*!< 报警盘组                               */
    eDiskGroupRedundance,       /*!< 冗余盘组                               */
    eDiskGroupBackup,           /*!< 备份盘组                               */
    eDiskGroupTypeEnd,          /*!< 结束值                                 */
};


/*!
*  @enum    eDiskGroupOperation
*  @brief   硬盘组操作　
*/
enum eDiskGroupOperation
{
    eDiskGroupOperationBegin = 0,   /*!< 起始值                                 */
    eUnMountDisk,               /*!< 卸载分区                               */
    eCreateNewPartition,        /*!< 建立新分区                             */
    eDeletePartition,           /*!< 删除分区                               */
    eFormatPartition,           /*!< 格式化分区                             */
    eDiskGroupKeepTime,         /*!< 分组保持数据时间                       */
    eDiskGroupBindChannel,      /*!< 分组绑定通道                           */
    eDiskGroupAddPartition,     /*!< 添加分区至分组                         */
    eDiskGroupDelPartition,     /*!< 从分组删除分区                         */
    eInitializeDisk,            /*!< 初始化硬盘                             */
    eDiskGroupOperationEnd,     /*!< 结束值                                 */
};

/*!
*  @enum    ePTZControlCodeType
*  @brief   PTZ云台控制码类型
*/
enum ePTZControlCmdCode
{
    ePTZControlCodeAllOff = 0,  //－   关闭(或断开)所有开关    (Param1: 无效, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeCameraPower = 1, //－   接通摄像机电源      (Param1: 1-开始/0-停止, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeLightPower = 2,  //－   接通灯光电源            (Param1: 1-开始/0-停止, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeWiper = 3,   //－   接通雨刷开关            (Param1: 1-开始/0-停止, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeFans = 4,    //－   接通风扇开关            (Param1: 1-开始/0-停止, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeHeater = 5,  //－   接通加热器开关      (Param1: 1-开始/0-停止, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeAuxEquiment = 6, //－   接通辅助设备开关        (Param1: 1-开始/0-停止, Param2: 无效, Param3: 无效, Param4: 无效)

    ePTZControlCodeStopContinue = 10,   //－   停止所有连续量(镜头,云台)动作   (Param1: 无效, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeZoomIn = 11, //－   焦距变大(倍率变大)      (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeZoomOut = 12,    //－   焦距变小(倍率变小)      (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeFocusNear = 13,  //－   焦点前调                (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeFocusFar = 14,   //－   焦点后调                (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeApertureUp = 15, //－   光圈扩大                (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeApertureDown = 16,   //－   光圈缩小                (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeAutoZoom = 17,   //－   开自动焦距(自动倍率)    (Param1: 1-开始/0-停止, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeAutoFocus = 18,  //－   开自动调焦          (Param1: 1-开始/0-停止, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeAutoAperture = 19,   //－   开自动光圈          (Param1: 1-开始/0-停止, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeUp = 21,     //－   云台上仰                (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeDown = 22,   //－   云台下俯                (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeLeft = 23,   //－   云台左转                (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeRight = 24,  //－   云台右转                (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeUpLeft = 25, //－   云台上仰和左转      (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeUpRight = 26,    //－   云台上仰和右转      (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeDownLeft = 27,   //－   云台下俯和左转      (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeDownRight = 28,  //－   云台下俯和右转      (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)
    ePTZControlCodeAutoLeftRight = 29,  //－   云台左右自动扫描        (Param1: 1-开始/0-停止, Param2: 速度 [0-10,0表示默认速度,1-10表示速度级别], Param3: 无效, Param4: 无效)

    ePTZControlCodePresetSet = 40,  //－   设置预置点          (Param1: 预置点序号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodePresetClear = 41,    //－   清除预置点          (Param1: 预置点序号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodePresetCall = 42, //－   转到预置点          (Param1: 预置点序号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)

    ePTZControlCodeCuriserSetStart = 51,    //－   启动巡航记忆            (Param1: 巡航路线号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeCuriserSetStop = 52, //－   关闭巡航记忆            (Param1: 巡航路线号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeCuriserAddPreset = 53,   //－   将预置点加入巡航序列    (Param1: 巡航路线号[>=0], Param2: 预置点序号[>=0], Param3: 停顿时间[秒,>=0], Param4: 巡航速度[1-10])
    ePTZControlCodeCuriserRunStart = 54,    //－   开始巡航                (Param1: 巡航路线号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeCuriserRunStop = 55, //－   停止巡航                (Param1: 巡航路线号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)

    ePTZControlCodeTraceSetStart = 61,  //－   启动轨迹记忆            (Param1: 轨迹号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeTraceSetStop = 62,   //－   关闭轨迹记忆            (Param1: 轨迹号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeTraceRunStart = 63,  //－   开始轨迹                (Param1: 轨迹号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeTraceRunStop = 64,   //－   停止轨迹                (Param1: 轨迹号[>=0], Param2: 无效, Param3: 无效, Param4: 无效)

    ePTZControlCodeSystemReset = 99,    //－   系统复位                (Param1: 无效, Param2: 无效, Param3: 无效, Param4: 无效)
    ePTZControlCodeElctronicReset = 100,//－   电子PTZ系统复位         (Param1: 无效, Param2: 无效, Param3: 无效, Param4: 无效)

};

/*!
*  @enum    ePTZControlCmdType
*  @brief   PTZ控制命令类型(针对Hxht协议)
*/
enum ePTZControlCmdType
{
    ePTZCmdTypeBegin        = 0,        // PTZ控制命令起始值
    ePTZCmdTypeGetStatus,               // 获取PTZ状态
    ePTZCmdTypeControl,                 // PTZ控制
    ePTZCmdTypeSet485Param,             // 设置485参数
    ePTZCmdTypeWrite485Data,            // 直写485数据
    ePTZCmdTypeEnd,                     // PTZ控制命令结束值
};

/*!
*  @enum    tagPTZControlOperation
*  @brief   PTZ控制码(针对Hxht协议)
*/
enum ePTZControlOperation
{
    ePTZOperationaIRISControl   = 8300,             /*!< 光圈调节                                           */
    ePTZOperationIRISStop       = 8306,             /*!< 停止光圈调节                                       */
    ePTZOperationDigitalControl = 8302,             /*!< 数字变倍                                           */
    ePTZOperationDigitalStop    = 8308,             /*!< 停止数字变倍                                       */
    ePTZOperationStart          = 8200,             /*!< 云台开始动作                                       */
    ePTZOperationStop           = 8202,             /*!< 云台停止动作                                       */
    ePTZOperationScanStart      = 8204,             /*!< 开始随机线扫                                       */
    ePTZOperationScanStop       = 8204,             /*!< 停止随机线扫                                       */
    ePTZOperationPresetSetting  = 8206,             /*!< 预置点设置                                         */
    ePTZOperationPresetClear    = 8208,             /*!< 预置点清除                                         */
    ePTZOperationPresetCall     = 8210,             /*!< 预置点调用                                         */
    ePTZOperationPresetClearAll = 8212,             /*!< 清除所有                                           */
    ePTZOperationFocusControl   = 8304,             /*!< 自动聚焦控制                                       */
    ePTZOperationFocusStop      = 8310,             /*!< 停止自动聚焦                                       */
    ePTZOperationLightOn        = 13,               /*!< 灯光开                                             */
    ePTZOperationLightOff       = 14,               /*!< 灯光关                                             */
    ePTZOperationRainBrushOn    = 15,               /*!< 雨刷开                                             */
    ePTZOperationRainBrushOff   = 16,               /*!< 雨刷开                                             */
    ePTZOperationDetectionOn    = 17,               /*!< 探头开                                             */
    ePTZOperationDetectionOff   = 18,               /*!< 探头开                                             */
    ePTZOperationCameraOn       = 19,               /*!< 摄头开                                             */
    ePTZOperationCameraOff      = 20,               /*!< 摄头开                                             */
};

/*!
*  @enum    eAppRefreshEvent
*  @brief   应用更新事件通知类型
*/
enum eAppRefreshEvent
{
    eAppRefreshEventBegin = 0,  /*!< 起始值                                 */
    eManagerServerRefresh,      /*!< 管理服务器状态                         */
    eUserActionRefresh,         /*!< 用户动作状态                           */
    eRealStreamRefresh,         /*!< 实时流事件                             */
    eVoiceRefresh,              /*!< 语音流事件                             */
    eRemoteDownloadRefresh,     /*!< 远程下载状态                           */
    eRemoteDetectRefresh,       /*!< 远程探测                               */
    eAppRefreshEventEnd,        /*!< 结束值                                 */
};

/*!
*  @enum    eStreamTransferMode
*  @brief   流传输方式
*/
enum eStreamTransferMode
{
    eStreamTransferModeBegin = 0,   /* 起始值                                 */

    eGeneralTCP,                /* 普通的TCP                              */
    eGeneralRTP,                /* 普通的RTP                              */
    eGeneralUDP,		    /*!< 普通的UDP                              */

    eStreamTransferModeEnd,     /* 结束值                                 */
};

/*!
*  @enum    eVoiceMode
*  @brief   语音编解码模式
*/
enum eVoiceMode
{
    eVoiceModeBegin = 0,        /*!< 起始值                                 */
    eVoiceG726,                 /*!< G726编解码模式                         */
    eVoiceG711U,                /*!< G711U编解码模式                        */
    eVoiceMPEG4AAC,             /*!< MPEG4 AAC编解码模式                    */
    eVoiceAutoDiscern,          /*!< 自动识别编解码模式                     */
    eVoiceModeEnd,              /*!< 结束值                                 */
};

/*!
*  @enum    eVideoCodecMode
*  @brief   视频编解码模式
*/
typedef enum eVideoCodecMode
{
    eVideoCodecModeBegin =   0, /*!< 起始值                                 */
    eVideoCodecH264,            /*!< 标准H264编解码模式                     */
    eVideoCodecHYMpeg4,         /*!< HYMpeg4编解码模式                      */
    eVideoCodecHYH264,          /*!< HYH264编解码模式                       */
    eVideoCodecAutoDiscern,     /*!< 自动识别编解码模式                     */
    eVideoCodecModeEnd,         /*!< 结束值                                 */
} eVideoCodecMode;

/*!
*  @enum    eTaskStatus
*  @brief   任务状态
*/
enum eTaskStatus
{
    eTaskStatusBegin = 0,       /*!< 起始值                                 */
    eTaskStatusNone,            /*!< 任务无状态                             */
    eTaskStatusInitialize,      /*!< 任务初始化                             */
    eTaskStatusDestroy,         /*!< 任务销毁                               */
    eTaskStatusStart,           /*!< 任务启动                               */
    eTaskStatusStop,            /*!< 任务停止                               */
    eTaskStatusRun,             /*!< 任务运行中                             */
    eTaskStatusRecover,         /*!< 任务恢复                               */
	eTaskStatusPause,			/*! 暂停*/
    eTaskStatusEnd,             /*!< 结束值                                 */
};

/*!
*  @enum    eMediaFunctionType
*  @brief   媒体功能类型
*/
enum eMediaFunctionType
{
    eMediaFunctionTypeBegin = 0,    /*!< 起始值                                 */
    eMediaFunctionRealStream,   /*!< 实时流                                 */
    eMediaFunctionVoiceStream,  /*!< 语音流                                 */
    eMediaFunctionHistoryStream,    /*!< 历史流                                 */
    eMediaFunctionTransparent,  /*!< 透明通道                               */
    eMediaFunctionFileUpload,   /*!< 文件上传                               */
    eMediaFunctionFileDownload, /*!< 文件下载                               */
    eMediaFunctionTypeEnd,      /*!< 结束值                                 */
};

/*!
*  @enum    eFrameType
*  @brief   帧类型
*/
enum eFrameType
{
    eFrameError = 0x0000,
    eFrameIFrames = 0x0001,         //主码流的I帧
    eFramePFrames = 0x0002,

    eFrameBPFrames = 0x0020,
    eFrameBBPFrames = 0x0004,
    eFrameAudioFrames = 0x0008,

    eFrameQCIFIFrames = 0x0010,     //QCIF的I帧
    eFramePktSQCIFIFrames = 0x0011, //高清子码流I帧

    eFrameQCIFPFrames = 0x0040,
    eFramePktSQCIFPFrames = 0x0041, //高清子码流P帧

    eFrameBIFrames = 0x0090,
    eFrameBBIFrames = 0x00C0,
    eFrameSysHeader = 0x0080,           //主码流系统头
    eFramePktSysHeaderAux = 0x0081,     //子码流系统头
    eFramePktSysHeaderHDAux = 0x0082,   //高清子码流系统头
    eFrameSFrames = 0x0200,
    eFrameDspStatus = 0x0100,
    eFrameAimDetection = 0x0400,
    eFrameOrigImage = 0x0800,
    eFrameMotionDetection = 0x1000,
    eFrameFileEnd	= 0xFFFF,//Liujl change start-end at 20160520-1415  //文件结束
};

/*!
*  @enum    eSerialType
*  @brief   串口类型
*/
enum eSerialType
{
    eTTY232 = 0,                            /*!< RS232串口                               */
    eTTY485,                                /*!< RS485串口                               */
    eTTY422,                                /*!< RS422串口                               */
};

/*!
*  @enum    eDevType
*  @brief   设备类型
*/
enum eDevType
{
    eDevTypeTerminal = 2,               /*!< 前端(视频服务器) */
    eDevTypeStore = 4,                  /*!< 存储服务器 */
    eDevTypeCamera = 5,                 /*!< 摄像头 */
    eDevTypeAlarmin = 6,                /*!< 报警输入 */
    eDevTypeAlarmout = 8,               /*!< 报警输出 */
    eDevTypeAnalyse = 20,               /*!< 智能分析单元 */
};

/*!
*  @enum    eAlarmEventType
*  @brief   报警输入事件类型
*/
enum eAlarmEventType
{
    eAlarmEventTypeOverflow = 0,        /*!< 越界检测 */
    eAlarmEventTypeResort = 1,          /*!< 滞留检测 */
    eAlarmEventTypeCarSpeed = 2,        /*!< 车速检测 */
};

/*!
*  @enum    eFaultType
*  @brief   故障类型
*/
enum eFaultType
{
    eFaultTypeDevice = 1,               /*!< 设备告警 */
    eFaultTypeCapability = 2,           /*!< 性能告警 */
    eFaultTypeProcess = 3,              /*!< 处理出错告警 */
    eFaultTypeCommunication = 4,        /*!< 通讯告警 */
    eFaultTypeEnvironment = 5,          /*!< 环境告警 */
};

/*!
*  @enum    eFaultID
*  @brief   故障编号
*/
enum eFaultID
{
    //设备故障编号
    eFaultTypeFlash = 7,                /*!< 操作Flash失败报警 */
    eFaultTypeDisk = 8,                 /*!< 硬盘读写失败告警或者硬盘故障报警 */
    eFaultTypeDiskSpace = 501,          /*!< 硬盘空间剩余容量低于阈值报警 */
    eFaultTypeDiskFull = 502,           /*!< 硬盘空间满报警 */
    eFaultTypeStoreServer = 503,        /*!< 向中心存储FTP文件失败*/

    //性能故障编号
    eFaultTypeCpuUseRatio = 1,          /*!< 操作Flash失败报警 */
    eFaultTypeDiskUseRatio = 2,         /*!< 硬盘读写失败告警或者硬盘故障报警 */
    eFaultTypeMemoryUseRatio = 3,       /*!< 硬盘空间剩余容量低于阈值报警 */

    //通讯故障编号
    eFaultTypeVideoLoss = 4,            /*!< 视频信号中断报警 */
};

/*!
*  @enum    eFaultState
*  @brief   故障状态
*/
enum eFaultState
{
    New = 0,            /*!< 新故障 */
    Resure = 1,         /*!< 故障恢复 */
};

/*!
*  @enum    eConnectType
*  @brief   流连接方式
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
*  @brief   面板键盘值类型
*/
typedef enum ePanelKeyBoardCodeType
{
    ePanelKeyBoardTypeBegin                     = 0x0,      /*!< 起始值                                 */
    ePanelKeyBoardCode_0                        = 0x1,      /*!< 对应键:0                               */
    ePanelKeyBoardCode_1                        = 0x2,      /*!< 对应键:1                               */
    ePanelKeyBoardCode_2                        = 0x3,      /*!< 对应键:2                               */
    ePanelKeyBoardCode_3                        = 0x4,      /*!< 对应键:3                               */
    ePanelKeyBoardCode_4                        = 0x5,      /*!< 对应键:4                               */
    ePanelKeyBoardCode_5                        = 0x6,      /*!< 对应键:5                               */
    ePanelKeyBoardCode_6                        = 0x7,      /*!< 对应键:6                               */
    ePanelKeyBoardCode_7                        = 0x8,      /*!< 对应键:7                               */
    ePanelKeyBoardCode_8                        = 0x9,      /*!< 对应键:8                               */
    ePanelKeyBoardCode_9                        = 0xA,      /*!< 对应键:9                               */
    ePanelKeyBoardCode_10                       = 0xB,      /*!< 对应键:10                              */
    ePanelKeyBoardCode_11                       = 0xC,      /*!< 对应键:11                              */
    ePanelKeyBoardCode_12                       = 0xD,      /*!< 对应键:12                              */
    ePanelKeyBoardCode_13                       = 0xE,      /*!< 对应键:13                              */
    ePanelKeyBoardCode_14                       = 0xF,      /*!< 对应键:14                              */
    ePanelKeyBoardCode_15                       = 0x10,     /*!< 对应键:15                              */
    ePanelKeyBoardCode_16                       = 0x11,     /*!< 对应键:16                              */
    ePanelKeyBoardCode_PTZ                      = 0x40,     /*!< 对应键:云台                            */
    ePanelKeyBoardCode_Copy                     = 0x41,     /*!< 对应键:备份                            */
    ePanelKeyBoardCode_Multi                    = 0x42,     /*!< 对应键:多画面                          */
    ePanelKeyBoardCode_Switch                   = 0x43,     /*!< 对应键:切换                            */
    ePanelKeyBoardCode_Function                 = 0x44,     /*!< 对应键:辅助                            */
    ePanelKeyBoardCode_Play                     = 0x45,     /*!< 对应键:播放                            */
    ePanelKeyBoardCode_Backward                 = 0x46,     /*!< 对应键:倒放                            */
    ePanelKeyBoardCode_Record                   = 0x47,     /*!< 对应键:录像                            */
    ePanelKeyBoardCode_ESC                      = 0x48,     /*!< 对应键:退出                            */
    ePanelKeyBoardCode_Left                     = 0x49,     /*!< 对应键:左                              */
    ePanelKeyBoardCode_Right                    = 0x4A,     /*!< 对应键:右                              */
    ePanelKeyBoardCode_Up                       = 0x4B,     /*!< 对应键:上                              */
    ePanelKeyBoardCode_Down                     = 0x4C,     /*!< 对应键:下                              */
    ePanelKeyBoardCode_Enter                    = 0x4D,     /*!< 对应键:确认                            */
    ePanelKeyBoardCode_Shutdown                 = 0x4E,     /*!< 对应键:关机                            */
    ePanelKeyBoardCode_TV_VGA                   = 0x4F,     /*!< 对应键:TV/VGA                          */
    ePanelKeyBoardCode_Edit                     = 0x50,     /*!< 对应键:编辑                            */
    ePanelKeyBoardCode_Language                 = 0x51,     /*!< 对应键:语言                            */
    ePanelKeyBoardCode_Mute                     = 0x52,     /*!< 对应键:静音                            */
    ePanelKeyBoardCode_Pause                    = 0x53,     /*!< 对应键:暂停                            */
    ePanelKeyBoardCode_Stop                     = 0x54,     /*!< 对应键:停止                            */
    ePanelKeyBoardCode_AlarmClear               = 0x55,     /*!< 对应键:消警                            */
    ePanelKeyBoardCode_Defence                  = 0x56,     /*!< 对应键:布防撤防                        */
    ePanelKeyBoardCode_Capture                  = 0x57,     /*!< 对应键:抓图                            */
    ePanelKeyBoardCode_LightAdd                 = 0x58,     /*!< 对应键:亮度增加                        */
    ePanelKeyBoardCode_LightSub                 = 0x59,     /*!< 对应键:亮度减少                        */
    ePanelKeyBoardCode_ContrastAdd              = 0x5A,     /*!< 对应键:对比度增加                      */
    ePanelKeyBoardCode_ContrastSub              = 0x5B,     /*!< 对应键:对比度减少                      */
    ePanelKeyBoardCode_SpeedAdd                 = 0x5C,     /*!< 对应键:速度增加                        */
    ePanelKeyBoardCode_SpeedSub                 = 0x5D,     /*!< 对应键:速度减少                        */
    ePanelKeyBoardCode_Set                      = 0x5E,     /*!< 对应键:设置                            */
    ePanelKeyBoardCode_F1                       = 0x5F,     /*!< 对应键:F1                              */
    ePanelKeyBoardTypeEnd,                                  /*!< 结束值                                 */
} ePanelKeyBoardCodeType;

/*!
*  @struct  ePanelControlType
*  @brief   面板控制类型
*/
typedef enum ePanelControlType
{
    ePanelControlBegin                          = 0,        /*!< 起始值                                 */
    ePanelControlKeyDown,                                   /*!< 按下                                   */
    ePanelControlKeyUp,                                     /*!< 弹起                                   */
    ePanelControlClick,                                     /*!< 点击(按下并弹起)                       */
    ePanelControlEnd,                                       /*!< 结束值                                 */
} ePanelControlType;

/*!
*  @struct  eDecoderChannelStatus
*  @brief   解码通道状态
*/
typedef enum eDecoderChannelStatus
{
    eDecoderChannelStatusBegin                  = 0,        /*!< 起始值                                 */
    eDecoderChannelStatusOpen,                              /*!< 打开                                   */
    eDecoderChannelStatusClose,                             /*!< 关闭                                   */
    eDecoderChannelStatusContinue,                          /*!< 保持                                   */
    eDecoderChannelStatusEnd,                               /*!< 结束值                                 */
} eDecoderChannelStatus;

/*!
*  @struct  eStreamSourceType
*  @brief   流媒体源类型
*/
typedef enum eStreamSourceType
{
    eStreamSourceTypeBegin                      = 0,        /*!< 起始值                                 */
    eStreamSourceTypeReal,                                  /*!< 实时流                                 */
    eStreamSourceTypeHistory,                               /*!< 历史流                                 */
    eStreamSourceTypeEnd,                                   /*!< 结束值                                 */
} eStreamSourceType;

/*!
*  @struct  eStreamPlayControlStatus
*  @brief   流媒体播放控制状态
*/
typedef enum eStreamPlayControlStatus
{
    eStreamPlayControlBegin                     = 0,        /*!< 起始值                                 */
    eStreamPlayControlPlay,                                 /*!< 播放                                   */
    eStreamPlayControlSuspend,                              /*!< 暂停                                   */
    eStreamPlayControlResume,                               /*!< 恢复                                   */
    eStreamPlayControlStop,                                 /*!< 停止                                   */
    eStreamPlayControlFast,                                 /*!< 快速播放                               */
    eStreamPlayControlSlow,                                 /*!< 慢速播放                               */
    eStreamPlayControlNormal,                               /*!< 正常速度                               */
    eStreamPlayControlOneByOne,                             /*!< 单帧播放                               */
    eStreamPlayControlOpenAudio,                            /*!< 打开声音                               */
    eStreamPlayControlCloseAudio,                           /*!< 关闭声音                               */
    eStreamPlayControlSetPos,                               /*!< 设置位置                               */
    eStreamPlayControlClearBuffer,                          /*!< 清空缓冲区                             */
    eStreamPlayControlEnd,                                  /*!< 结束值                                 */
} eStreamPlayControlStatus;

/*!
*  @struct  eDisplayControlStatus
*  @brief   显示控制状态
*/
typedef enum eDisplayControlStatus
{
    eDisplayControlStatusBegin                  = 0,        /*!< 起始值                                 */
    eDisplayControlStatusEnlarge,                           /*!< 放大显示                               */
    eDisplayControlStatusRenew,                             /*!< 还原                                   */
    eDisplayControlStatusEnd,                               /*!< 结束值                                 */
} eDisplayControlStatus;


typedef enum eTaskSpeed
{
	eTaskSpeedBegin				=	0,			/*!< 起始值				*/
	eSpeedNormal,									/*!< 正常速度播放			*/
	eSpeedTwo,									/*!< 2倍速度播放			*/
	eSpeedFour,									/*!< 4倍速度播放			*/
	eSpeedEight,									/*!< 8倍速度播放			*/
	eSpeedSixteen,								/*!< 16倍速度播放			*/
	eSpeedHalf,									/*!< 1/2倍速度播放			*/
	eSpeedQuarter,								/*!< 1/4倍速度播放			*/
	eSpeedOneEighth,								/*!< 1/8倍速度播放			*/
	eSpeedOneSixteenth,							/*!< 1/16倍速度播放		*/
	eSpeedSingle,									/*!< 单帧倍速度播放		*/
	eTaskSpeedEnd,								/*!< 结束值				*/
}eTaskSpeed;
//////////////////////////////////////////////////////////////////////////
//结构
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
*  @brief   时间信息
*/
typedef struct tagTimeInfo
{
    WORD wYear;                 /*!< 年                                     */
    WORD wMonth;                /*!< 月                                     */
    WORD wDay;                  /*!< 日                                     */
    WORD wHour;                 /*!< 时                                     */
    WORD wMinute;               /*!< 分                                     */
    WORD wSecond;               /*!< 秒                                     */
} TimeInfo, *LPTimeInfo;

/*!
*  @struct  tagAbsoluteTime
*  @brief   绝对时间信息
*/
typedef struct tagAbsoluteTime
{
    WORD wYear;                 /*!< 年                                     */
    WORD wMonth;                /*!< 月                                     */
    WORD wWeek;                 /*!< 周                                     */
    WORD wDay;                  /*!< 日                                     */
    WORD wHour;                 /*!< 时                                     */
    WORD wMinute;               /*!< 分                                     */
    WORD wSecond;               /*!< 秒                                     */
    WORD wMillisecond;          /*!< 毫秒                                   */
} AbsoluteTime, *LPAbsoluteTime;

/*!
*  @struct  tagBuffer
*  @brief   缓冲区信息
*/
typedef struct tagBuffer
{
    BYTE *pBuffer;              /*!< 媒体数据缓冲区                         */
    DWORD dwBufLen;             /*!< 媒体数据长度                           */
} Buffer, *LPBuffer;

/*!
*  @struct  tagManagerServerState
*  @brief	管理服务器状态
*/
typedef struct tagManagerServerState
{
	enum eManagerServerType eType;	/*!< 管理类型                               */
	DWORD dwState;				/*!< 管理状态                               */
    char sServer[IP_ADDRESS_LEN];   /*!< 管理主机IP地址信息                     */
    DWORD dwServerDomainEnable; /*!<管理主机域名信息有效标志                */
    char sServerDomain[DOMAIN_ADDRESS_LEN]; /*!<管理主机域名信息                      */
    DWORD dwServerPort;         /*!<管理主机端口                            */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!<保留                                    */
} ManagerServerState, *LPManagerServerState;

/*!
*  @struct  tagRealStreamMedia
*  @brief	实时流媒体
*/
typedef struct tagRealStreamMedia
{
    enum eStreamMediaType eType;		/*!< 流类型                                 */
    Buffer cBuffer;             /*!< 缓冲区信息                             */
    AbsoluteTime cTime;         /*!< 帧时间                                 */
    DWORD dwFrameType;          /*!< 帧类型                                 */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< 保留                                   */
} RealStreamMedia, *LPRealStreamMedia;

/*!
*  @struct  tagStreamTransferFrame
*  @brief	流转发帧参数
*/
typedef struct tagStreamTransferFrame
{
	enum eFrameType	eFrameTypeInfo;							/*!< 帧类型信息								*/
	DWORD	dwTimeStamp;								/*!< 帧时间戳								*/
    AbsoluteTime cAbsoluteTime;                         /*!< 帧绝对时间戳                           */
    DWORD   dwFrameNumber;                              /*!< 帧编号                                 */
    Buffer  cFrameBuffer;                               /*!< 帧缓冲区                               */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< 保留                                   */
} StreamTransferFrame, *LPStreamTransferFrame;

/*!
*  @struct  tagStreamFlowState
*  @brief   流流量状态
*/
typedef struct tagStreamFlowState
{
    DWORD dwBitrate;            /*!< 码率(kbps)                             */
    DWORD dwWorkTime;           /*!< 流工作时间                             */
    DWORD dwTotalFlow;          /*!< 总流量                                 */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< 保留                                   */
} StreamFlowState, *LPStreamFlowState;

/*!
*  @struct  tagStreamState
*  @brief   流状态
*/
typedef struct tagStreamState
{
    DWORD dwClientNum;          /*!< 客户数                                 */
    DWORD dwUserID[REAL_STREAM_LIMIT];  /*!< 客户信息                               */
    StreamFlowState cStreamFlowState[REAL_STREAM_LIMIT];    /*!< 流量状态                   */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< 保留                                   */
} StreamState, *LPStreamState;

/*!
*  @struct  tagRemoteUserInfo
*  @brief   远程用户信息
*/
typedef struct tagRemoteUserInfo
{
    DWORD dwUserID;             /*!< 用户ID                                 */
    char sUserName[USERNAME_LEN];   /*!< 用户名                                 */
    char sUserPass[USERPASS_LEN];   /*!< 用户密码                               */
    char sUserIPAddress[IP_ADDRESS_LEN];    /*!< 用户IP地址                             */
    char sClientIPAddress[IP_ADDRESS_LEN];  /*!< 客户端IP地址 */
    char sClientMACAddress[MAC_ADDRESS_LEN];    /*!< 客户端MAC地址                           */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< 保留                                   */
} RemoteUserInfo, *LPRemoteUserInfo;

/*!
*  @struct  tagRealStreamAction
*  @brief   实时流事件通知
*/
typedef struct tagRealStreamAction
{
	DWORD dwChannel;			/*!< 通道号                                 */
	enum eStreamActionType eActionType;	/*!< 事件类型                               */
	DWORD dwReserve[DEF_RESERVE_NUM];	/*!< 保留                                   */
} RealStreamAction, *LPRealStreamAction;

/*!
*  @struct  tagVoiceStreamAction
*  @brief   语音流事件通知
*/
typedef struct tagVoiceStreamAction
{
    DWORD dwChannel;            /*!< 通道号                                 */
	enum eStreamActionType eActionType;	/*!< 事件类型                               */
	DWORD dwReserve[DEF_RESERVE_NUM];	/*!< 保留                                   */
} VoiceStreamAction, *LPVoiceStreamAction;

/*!
*  @struct  tagAlarmNotify
*  @brief   报警通知信息
*/
typedef struct tagAlarmNotify
{
    DWORD dwType;               /*!< 报警类型                               */
    DWORD dwDepict;             /*!< 报警信息描述                           */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< 保留                                   */
} AlarmNotify, *LPAlarmNotify;

/*!
*  @struct  tagAppLogQuery
*  @brief   应用层日志查询信息
*/
typedef struct tagAppLogQuery
{
    BYTE bytQueryMode;          /*!< 查询模式                               */
    BYTE bytMajorType;          /*!< 主类型                                 */
    BYTE bytMinorType;          /*!< 次类型                                 */
    BYTE bytReserve[1];         /*!< 保留                                   */
    DWORD dwChannel;            /*!< 通道号                                 */
    TimeInfo cBeginTime;        /*!< 开始时间                               */
    TimeInfo cEndTime;          /*!< 结束时间                               */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< 保留                                   */
} AppLogQuery, *LPAppLogQuery;

/*!
*  @struct  tagAppLogInfo
*  @brief   应用层日志信息
*/
typedef struct tagAppLogInfo
{
    TimeInfo cLogTime;          /*!< 日志时间                               */
    BYTE bytMajorType;          /*!< 主类型                                 */
    BYTE bytMinorType;          /*!< 次类型                                 */
    BYTE bytDetail;             /*!< 详细信息                               */
    BYTE bytReserve[1];         /*!< 保留                                   */
    DWORD dwChannel;            /*!< 通道                                   */
    char sUserName[USERNAME_LEN];   /*!< 操作用户                               */
    DWORD dwUserIPAddress;      /*!< 操作用户IP地址                         */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< 保留                                   */
} AppLogInfo, *LPAppLogInfo;

/*!
*  @struct  tagHistoryQueryInfo
*  @brief   历史查询信息
*/
typedef struct tagHistoryQueryInfo
{
    DWORD dwChannel;            /*!< 通道号                                 */
	DWORD dwDiskGroup;			/*!< 盘组信息                               */
	enum eHistoryStreamType eStreamType;	/*!< 历史流类型                             */
    char cBeginTime[15];        /*!< 起始时间                               */
    char cEndTime[15];          /*!< 结束时间                               */
    char cTicket[HXHT_COMMON_STRING_LEN]; /*!< 验证信息，针对Hxht           */
} HistoryQueryInfo, *LPHistoryQueryInfo;

/*!
*  @struct  tagHistoryQueryInfo
*  @brief   历史查询信息
*/
typedef struct tagHistoryQueryInfoMultiType
{
    DWORD dwChannel;            /*!< 通道号                                 */
    DWORD dwDiskGroup;          /*!< 盘组信息                               */
    DWORD dwStreamType;         /*!< 历史流类型                             */
    char cBeginTime[15];        /*!< 起始时间                               */
    char cEndTime[15];          /*!< 结束时间                               */
} HistoryQueryInfoMultiType, *LPHistoryQueryInfoMultiType;

/*!
*  @struct  tagFileQueryInfo
*  @brief   文件查询信息
*/
typedef struct tagFileQueryInfo
{
    DWORD dwChannel;            /*!< 通道号                                 */
    DWORD dwFileType;           /*!< 文件流类型                             */
    char cBeginTime[DATE_TIME_LEN]; /*!< 起始时间                               */
    char cEndTime[DATE_TIME_LEN];   /*!< 结束时间                               */
} FileQueryInfo, *LPFileQueryInfo;

/*!
*  @struct  tagHistoryQueryResult
*  @brief   历史查询结果信息
*/
typedef struct tagHistoryQueryResultMultiType
{
    DWORD dwStreamType;         /*!< 历史流类型                             */
    DWORD dwChannel;            /*!< 通道号                                 */
    char cBeginTime[15];        /*!< 开始时间                               */
    char cEndTime[15];          /*!< 结束时间                               */
    DWORD dwDataSize;           /*!< 数据大小                               */
} HistoryQueryResultMultiType, *LPHistoryQueryResultMultiType;

/*!
*  @struct  tagHistoryQueryResult
*  @brief	历史查询结果信息
*/
typedef struct tagHistoryQueryResult
{
	enum eHistoryStreamType eStreamType;			/*!< 历史流类型                             */
	DWORD dwChannel;			/*!< 通道号                                 */
    char cBeginTime[15];        /*!< 开始时间                               */
    char cEndTime[15];          /*!< 结束时间                               */
    DWORD dwDataSize;           /*!< 数据大小                               */
} HistoryQueryResult, *LPHistoryQueryResult;

/*!
*  @struct  tagFileQueryResult
*  @brief   文件查询结果信息
*/
typedef struct tagFileQueryResult
{
    DWORD dwChannel;            /*!< 通道号                                 */
    DWORD dwLock;               /*是否锁定                                  */
    DWORD dwDataSize;           /*!< 数据大小                               */
    DWORD dwFileType;           /*!< 图片类型                               */
    char cCreateTime[DATE_TIME_LEN];    /*!< 图片时间                               */
    char cFileName[MAX_FILENAME];   /*!< 图片设备端路径                         */
} FileQueryResult, *LPFileQueryResult;

/*!
*  @struct	tagHistoryQueryResultSet
*  @brief	历史查询结果集
*/
typedef struct tagHistoryQueryResultSet
{
	HistoryQueryResult cHistoryQueryResult;	/*!< 历史查询结果信息                       */
	struct tagHistoryQueryResultSet *pNext;	/*!< 下一个结果                             */
} HistoryQueryResultSet, *LPHistoryQueryResultSet;



/*!
*  @enum	eHistoryLogMajorType
*  @brief	日志查询主类型
*/
enum eHistoryLogMajorType
{
    eHistoryLogMajorTypeBegin = 0,  /*!< 起始值                                 */
    eHistoryLogSysOperation,    /*!< 系统管理日志                           */
    eHistoryLogSysSetting,      /*!< 系统配置日志                           */
    eHistoryLogRecord,          /*!< 录像日志                               */
    eHistoryLogUserManage,      /*!< 用户管理日志                           */
    eHistoryLogAlarm,           /*!< 设备报警日志                           */
    eHistoryLogException,       /*!< 设备异常日志                           */
    eHistoryLogStorage,         /*!< 存储管理日志                           */
    eHistoryLogMajorAll,        /*!< 忽略主类型                             */
    eHistoryLogMajorTypeEnd,    /*!< 结束值                                 */
};

/*!
*  @enum    eHistoryLogMinorType
*  @brief   日志查询子类型
*/
enum eHistoryLogMinorType
{
    eHistoryLogSysOp = 0,       /*!< 系统操作所有子项                       */
    eHistoryLogSysOpUpdate,     /*!< 系统升级                               */
    eHistoryLogSysOpPTZControl, /*!< 云台控制                               */
    eHistoryLogSysOpIllShutdown,    /*!< 非法关机                               */
    eHistoryLogSysOpPowerOff,   /*!< 正常关机                               */
    eHistoryLogSysOpPowerOn,    /*!< 开机                                   */
    eHistoryLogSysOpRemoteReset,    /*!< 远程重启                               */
    eHistoryLogSysOpClearAlarm, /*!< 消警                                   */

    eHistoryLogSysSetAll = 100, /*!< 系统设置所有子项                       */
    eHistoryLogSysSetTimeSetting,   /*!< 录像时间表设置                         */
    eHistoryLogSysSetCommonSetting, /*!< 普通设置                               */
    eHistoryLogSysSetCodecSetting,  /*!< 编码设置                               */
    eHistoryLogSysSetNetSetting,    /*!< 网络设置                               */
    eHistoryLogSysSetServerSetting, /*!< 服务器设置                             */
    eHistoryLogSysSetMotionSetting, /*!< 移动侦测设置                           */
    eHistoryLogSysSetPTZSetting,    /*!< 云台解码器设置                         */
    eHistoryLogSysSetDefaultSetting,    /*!< 恢复默认设置                           */
    eHistoryLogSysSetDisplayDeviceSetting,  /*!< 设置显示设备参数                       */
    eHistoryLogSysSetDisplayModeSetting,    /*!< 显示模式设置                           */
    eHistoryLogSysSetPictureSetting,    /*!< 图像颜色设置                           */
    eHistoryLogSysSetMaintainSetting,   /*!< 自动维护设置                           */
    eHistoryLogSysSetAlarmOutSetting,   /*!< 报警输出设置                           */
    eHistoryLogSysSetAlarmInSetting,    /*!< 报警输入设置                           */
    eHistoryLogSysSetCustomizeFunction, /*!< 功能定制设置                           */
    eHistoryLogSysSetImportPTZProtocol, /*!< 导入云台协议                           */
    eHistoryLogSysSetExportPTZProtocol, /*!< 导出云台协议                           */
    eHistoryLogSysSetImportSettings,    /*!< 导入参数配置                           */
    eHistoryLogSysSetExportSettings,    /*!< 导入参数配置                           */
    eHistoryLogSysSetExceptionSetting,  /*!< 异常参数配置                           */

    eHistoryLogRecordAll = 200, /*!< 录像控制所有子项                       */
    eHistoryLogRecordStartManual,   /*!< 启动手动录像                           */
    eHistoryLogRecordStartAuto, /*!< 启动自动录像                           */
    eHistoryLogRecordStop,      /*!< 停止结束                               */

    eHistoryLogUserAll = 300,   /*!< 用户管理所有子项                       */
    eHistoryLogUserAdd,         /*!< 添加用户                               */
    eHistoryLogUserDelete,      /*!< 删除用户                               */
    eHistoryLogUserEdit,        /*!< 修改用户资料                           */
    eHistoryLogUserLogin,       /*!< 用户登录                               */
    eHistoryLogUserLogout,      /*!< 用户登出                               */

    eHistoryLogAlarmAll = 400,  /*< 报警所有子项                            */
    eHistoryLogAlarmMotionStart,    /*!< 移动侦测开始                           */
    eHistoryLogAlarmMotionStop, /*!< 移动侦测结束                           */
    eHistoryLogAlarmInputAlarm, /*!< 输入报警开始                           */

    eHistoryLogExceptionAll = 500,  /*!< 异常所有子项                           */
    eHistoryLogExceptionIpConflict, /*!< IP冲突                                 */
    eHistoryLogExceptionHardDiskFull,   /*!< 硬盘满                                 */
    eHistoryLogExceptionHardDiskError,  /*!< 硬盘出错                               */
    eHistoryLogExceptionIllegalAccess,  /*!< 非法访问                               */
    eHistoryLogExceptionSignalLost, /*!< 信号丢失                               */
    eHistoryLogExceptionSignalRecover,  /*!< 信号恢复                               */
    eHistoryLogExceptionNetDisconnect,  /*!< 网线断                                 */

    eHistoryLogStorageAll = 600,    /*!< 存储管理所有子项                       */
    eHistoryLogStorageFormatPartition,  /*!< 分区格式化                             */
    eHistoryLogStorageAddPartition, /*!< 添加分区                               */
    eHistoryLogStorageRemovePartition,  /*!< 删除分区　                             */
    eHistoryLogStorageUnmountDisk,  /*!< 卸载硬盘                               */
    eHistoryLogStorageDiskGroupOperation,   /*!< 磁盘分组管理                           */
};


/*!
*  @struct  tagLogQueryInfo
*  @brief   历史查询信息
*/
typedef struct tagLogQueryInfo
{
	DWORD m_dwQueryMode;		/*!< 查询方式                               */
	enum eHistoryLogMajorType m_eMajorType;	/*!< 主类型                                 */
	enum eHistoryLogMinorType m_eMinorType;	/*!< 次类型                                 */
	DWORD m_dwChannel;			/*!< 通道号                                 */
	char m_sStartTime[DATE_TIME_LEN];	/*!< 起始时间                               */
	char m_sStopTime[DATE_TIME_LEN];	/*!< 结束时间                               */
} LogQueryInfo, *LPLogQueryInfo;

/*!
*  @struct	tagLogQueryResult
*  @brief	历史查询结果信息
*/
typedef struct tagLogQueryResult
{
	enum eHistoryLogMajorType m_eMajorType;	/*!< 主类型                                 */
	enum eHistoryLogMinorType m_eMinorType;	/*!< 次类型                                 */
	DWORD m_dwDetailInfo;		/*!< 详细信息                               */
	char m_sUserName[USERNAME_LEN];	/*!< 操作用户                               */
	char m_sUserIP[IP_ADDRESS_LEN];	/*!< 用户IP地址                             */
	char m_sLogTime[DATE_TIME_LEN];	/*!< 操作时间                               */
} LogQueryResult, *LPLogQueryResult;

/*!
*  @struct	tagHistoryQueryResultSet
*  @brief	历史查询结果集
*/
typedef struct tagLogQueryResultSet
{
	LogQueryResult cLogQueryResult;	/*!< 历史查询结果信息                       */
	struct tagLogQueryResultSet *pNext;	/*!< 下一个结果                             */
} LogQueryResultSet, *LPLogQueryResultSet;

/*!
*  @struct	tagHistoryChannelParaInfo
*  @brief   历史通道启动参数信息
*/
typedef struct tagHistoryChannelParaInfo
{
    DWORD dwEnableEndTime;      /*!< 结束时间是否有效                       */
    TimeInfo cBeginTime;        /*!< 开始时间                               */
    TimeInfo cEndTime;          /*!< 结束时间                               */
    DWORD dwChannel;            /*!< 录像通道                               */
	DWORD dwDiskGroup;			/*!< 盘组信息                               */
	enum eHistoryStreamType eType;	/*!< 历史流类型                             */
	DWORD dwTaskType;			/*!< 任务类型                               */
} HistoryChannelParaInfo, *LPHistoryChannelParaInfo;

/*!
*  @struct  tagHistoryChannelParaInfoMultiType
*  @brief   历史通道启动参数信息(扩展)
*/
typedef struct tagHistoryChannelParaInfoMultiType
{
    DWORD dwEnableEndTime;      /*!< 结束时间是否有效                       */
    TimeInfo cBeginTime;        /*!< 开始时间                               */
    TimeInfo cEndTime;          /*!< 结束时间                               */
    DWORD dwChannel;            /*!< 录像通道                               */
    DWORD dwDiskGroup;          /*!< 盘组信息                               */
    DWORD dwType;               /*!< 历史流类型                             */
    DWORD dwTaskType;           /*!< 任务类型                               */
} HistoryChannelParaInfoMultiType, *LPHistoryChannelParaInfoMultiType;

/*!
*  @struct  tagHistoryChannelStream
*  @brief   历史通道流信息
*/
typedef struct tagHistoryChannelStream
{
    DWORD dwChannel;            /*!< 通道号                                 */
    Buffer cBuffer;             /*!< 帧缓冲区                               */
    AbsoluteTime cTime;         /*!< 帧时间                                 */
    /*!<
       帧类型：
       当帧的格式变换时，将帧类型置为 HISTORY_STREAM_SWITCH_FRAME；
       当帧为结束帧时，将帧类型置为
     */
    DWORD dwFrameType;
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< 保留                                   */
} HistoryChannelStream, *LPHistoryChannelStream;

/*!
*  @struct  tagHistoryChannelPositionInfo
*  @brief   历史通道定位参数信息
*/
typedef struct tagHistoryChannelPositionInfo
{
    TimeInfo cSeekTime;         /*!< 定位时间                               */
} HistoryChannelPositionInfo, *LPHistoryChannelPositionInfo;


typedef struct tagServerInformation
{
    char cAddress[IP_ADDRESS_LEN];  /*!< 地址                                   */
    DWORD dwCommandPort;        /*!< 信令端口                               */
    DWORD dwMediaPort;          /*!< 媒体端口                               */
} ServerInformation, *LPServerInformation;


/*!
*  @struct  tagTransparentParaInfo
*  @brief   透明传输参数信息
*/
typedef struct tagTransparentParaInfo
{
    DWORD dwMajorType;          /*!< 主类型信息                             */
    DWORD dwMinorType;          /*!< 子类型信息                             */
    Buffer cBuffer;             /*!< 参数信息                               */
    DWORD dwReserve[DEF_RESERVE_NUM];   /*!< 保留                                   */
} TransparentParaInfo, *LPTransparentParaInfo;


/*!
*  @struct  tagDeviceRegisterNetConfig
*  @brief   设备注册网络设置
*/
typedef struct tagDeviceRegisterNetConfig
{
    char cCentralIP[IP_ADDRESS_LEN];    /*!< 注册中心IP地址                         */
    DWORD dwCentralPort;        /*!< 注册中心端口                           */
    DWORD dwInterval;           /*!< 注册时间间隔(s                         */
} DeviceRegisterNetConfig, *LPDeviceRegisterNetConfig;

/*!
*  @struct  tagDeviceRegisterInfo
*  @brief   设备注册信息（私有协议用，设备ID是DWORD型）
*/
typedef struct tagDeviceRegisterInfo
{
    DWORD dwDeviceID;                           /*!< 设备ID                             */
    char cDeviceIP[IP_ADDRESS_LEN];             /*!< 设备IP地址                         */
    char cDeviceMAC[MAC_ADDRESS_LEN];           /*!< 设备MAC地址                        */
    DWORD dwDeviceCmdPort;                      /*!< 设备命令端口                       */
    DWORD dwHTTPPort;                           /*!< HTTP端口                           */
    DWORD dwDeviceType;                         /*!< 设备类型                           */
    char cDeviceVersion[VERSION_INFO_LEN];      /*!< 设备软件版本号                     */
    DWORD dwDeviceMaxConnect;                   /*!< 视频的最大连接数                   */
} DeviceRegisterInfo, *LPDeviceRegisterInfo;

/*!
*  @struct  tagDeviceRegisterInfoHxht
*  @brief   设备注册信息（Hxht协议用，设备ID是字符串）
*/
typedef struct tagDeviceRegisterInfoHxht
{
    char cDeviceID[MAX_DEVICE_ID_LEN];          /*!< 设备序列号                         */
    char cDeviceIP[IP_ADDRESS_LEN];             /*!< 设备IP地址                         */
    char cDeviceMAC[MAC_ADDRESS_LEN];           /*!< 设备MAC地址                        */
    DWORD dwDeviceCmdPort;                      /*!< 设备命令端口                       */
    DWORD dwHTTPPort;                           /*!< HTTP端口                           */
    DWORD dwDeviceType;                         /*!< 设备类型                           */
    char cDeviceVersion[VERSION_INFO_LEN];      /*!< 设备软件版本号                     */
    DWORD dwDeviceMaxConnect;                   /*!< 视频的最大连接数                   */
} DeviceRegisterInfoHxht, *LPDeviceRegisterInfoHxht;

/*!
*  @struct  tagDeviceStoreRegisterInfo
*  @brief   设备存储注册信息
*/
typedef struct tagDeviceStoreRegisterInfo
{
    char cDeviceID[MAX_DEVICE_ID_LEN];              /*!< 设备序列号＋"_T"                   */
    char cDeviceLinkType;                           /*!< 设备连接类型                       */
    char cDeviceIP[IP_ADDRESS_LEN];                 /*!< 设备IP地址                         */
    char cDeviceIP2[IP_ADDRESS_LEN];                /*!< 设备IP地址                         */
    DWORD dwDeviceMsgPort;                          /*!< 设备消息端口                       */
    DWORD dwDeviceVideoPort;                        /*!< 设备视频连接端口                   */
} DeviceStoreRegisterInfo, *LPDeviceStoreRegisterInfo;

/*!
*  @struct  tagCentralRetInfo
*  @brief   中心平台注册信息
*/
typedef struct tagCentralRetInfo
{
    char cCentralTime[DATE_TIME_LEN];   /*!< 注册平台中心时间                   */
} CentralRetInfo, *LPCentralRetInfo;

typedef struct tagRegisterInfo
{
    DWORD dwDeviceID;           /*!< 设备ID                                 */
    BYTE cDeviceIP[IP_ADDRESS_LEN]; /*!< 设备IP                                 */
    DWORD dwDevicePort;         /*!< 设备注册端口                           */
    BYTE cDeviceMAC[MAC_ADDRESS_LEN];   /*!< 设备MAC地址                            */
    DWORD dwHttpPort;           /*!< Http端口                               */
    DWORD dwDeviceType;         /*!< 设备IP                                 */
    char cDeviceVersion[VERSION_INFO_LEN];  /*!< 设备版本信息                           */
    DWORD dwDeviceMaxConnect;   /*!< 设备最大连接数                         */
} RegisterInfo, *LPRegisterInfo;

/*!
*  @enum    eTransferFileType
*  @brief   传输文件类型
*/
enum eTransferFileType
{
    eTransferFileTypeBegin = 0, /*!< 起始值                                 */
    eFileSystemUpdate,          /*!< 升级包文件                             */
    ePtzProtocol,               /*!< 云台协议文件                           */
    eDeviceConfig,              /*!< 设备配置文件                           */
    ePicture,                   /*!< 图片文件                               */
    eTransferFileTypeEnd,       /*!< 结束值                                 */
};


/*!
*  @struct  tagRemoteDownloadParaInfo
*  @brief	远程文件下载启动参数信息
*/
typedef struct tagRemoteDownloadParaInfo
{
	enum eTransferSpeed eSpeed;		/*!< 传输速度类型                           */
	enum eTransferFileType eFileType;	/*!< 文件类型                               */
	char cFileName[MAX_FILENAME];	/*!< 文件名                                 */
	DWORD dwFileTotalLen;		/*!< 文件总大小                             */
} RemoteDownloadParaInfo, *LPRemoteDownloadParaInfo;

/*!
*  @struct	tagRemoteDownloadState
*  @brief	远程文件下载状态信息
*/
typedef struct tagRemoteDownloadState
{
	enum eTransferSpeed eSpeed;		/*!< 传输速度类型                           */
	DWORD dwFileTransferLen;	/*!< 文件已传输大小                         */
	DWORD dwFileTotalLen;		/*!< 文件总大小                             */
	enum eRemoteDownloadState eState;	/*!< 文件传输状态                           */
} RemoteDownloadState, *LPRemoteDownloadState;

/*!
*  @struct	tagFileUploadParaInfo
*  @brief	远程文件上传启动参数信息
*/
typedef struct tagFileUploadParaInfo
{
	enum eTransferSpeed eSpeed;		/*!< 传输速度类型                           */
	enum eTransferFileType eFileType;	/*!< 文件类型                               */
	char cFileName[MAX_FILENAME];	/*!< 文件名                                 */
	DWORD dwFileTotalLen;		/*!< 文件总大小                             */
} FileUploadParaInfo, *LPFileUploadParaInfo;

/*!
*  @struct	tagFileUploadState
*  @brief	远程文件上传状态信息
*/
typedef struct tagFileUploadState
{
	enum eTransferSpeed eSpeed;		/*!< 传输速度类型                           */
	DWORD dwFileTransferLen;	/*!< 文件已传输大小                         */
	DWORD dwFileTotalLen;		/*!< 文件总大小                             */
	enum eRemoteDownloadState eState;	/*!< 文件传输状态                           */
} FileUploadState, *LPFileUploadState;



/*!
*  @struct	tagFileDownloadParaInfo
*  @brief	远程文件下载启动参数信息
*/
typedef struct tagFileDownloadParaInfo
{
	enum eTransferSpeed eSpeed;		/*!< 传输速度类型                           */
	DWORD dwFileType;			/*!< 文件类型                               */
	char cFileName[MAX_FILENAME];	/*!< 文件名                                 */
	DWORD dwFileTotalLen;		/*!< 文件总大小                             */
} FileDownloadParaInfo, *LPFileDownloadParaInfo;

/*!
*  @struct	tagFileDownloadState
*  @brief	远程文件下载状态信息
*/
typedef struct tagFileDownloadState
{
	enum eTransferSpeed eSpeed;		/*!< 传输速度类型                           */
	DWORD dwFileTransferLen;	/*!< 文件已传输大小                         */
	DWORD dwFileTotalLen;		/*!< 文件总大小                             */
	enum eRemoteDownloadState eState;	/*!< 文件传输状态                           */
} FileDownloadState, *LPFileDownloadState;

/*!
*  @struct	tagImageFileInfo
*  @brief    抓图文件信息
*/
typedef struct tagImageFileInfo
{
    DWORD m_dwFileSize;         /*!< 文件大小                               */
    char m_sFileName[MAX_FILENAME]; /*!< 文件名                                 */
    char m_sCreateTime[DATE_TIME_LEN];  /*!< 文件创建时间                           */
} ImageFileInfo, *LPImageFileInfo;

/*!
*  @struct  tagDataPacketType
*  @brief   文件传送媒体包类型
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
*  @brief   文件传送媒体包定义
*/
typedef struct tagFileTransferDataPacket
{
    eDataPacketType m_dwPacketType; /* 0:数据请求（数据传输开始）   1:数据包　2:回应包　 3:结束包 */
    DWORD m_dwPacketSequence;
    DWORD m_dwPacketLen;
} FileTransferDataPacket, *LPFileTransferDataPacket;


/*!
*  @struct  tagDetectActionInfo
*  @brief	探测事件信息
*/
typedef struct tagDetectActionInfo
{
	enum eDetectAction eType;		/*!< 事件类型                               */
	char cServerIP[IP_ADDRESS_LEN];	/*!< 远程服务器地址                         */
	DWORD dwServerPort;			/*!< 远程服务器端口                         */
} DetectActionInfo, *LPDetectActionInfo;

/*!
*  @struct  tagDevAlarmInfo
*  @brief   设备报警信息
*/
typedef struct tagDevAlarmInfo
{
    char szEventName[HXHT_MAX_XML_STRING_LEN];              /*!< 事件名 */
    char szDevName[HXHT_MAX_XML_STRING_LEN];                /*!< 报警设备名 */
    DWORD dwDevType;                                        /*!< 报警设备类型（5：摄像头，6：报警输入，20：智能分析单元） */
    char szAlarmTime[HXHT_MAX_XML_STRING_LEN];              /*!< 报警触发时间 */
    DWORD dwAlarmType;                                      /*!< 越界检测、滞留检测、车速检测 */
    char szInfo[HXHT_MAX_XML_STRING_LEN];                   /*!< 自定义的关于些报警事件的说明 */
} DevAlarmInfo, *LPDevAlarmInfo;

/*!
*  @struct  tagDevFaultInfo
*  @brief   设备故障信息
*/
typedef struct tagDevFaultInfo
{
    char szDevIP[IP_ADDRESS_LEN];                           /*!< 前端设备IP */
    char szCurrentTime[HXHT_MAX_XML_STRING_LEN];            /*!< 当前时间 */
    char szDevID[HXHT_COMMON_STRING_LEN];                   /*!< 设备ID */
    DWORD dwDevType;                                        /*!< 设备类型编号 */
    DWORD dwFaultType;                                      /*!< 故障类型编号 */
    DWORD dwFaultID;                                        /*!< 故障编号 */
    char szFaultTime[HXHT_COMMON_STRING_LEN];               /*!< 故障产生时间 */
    DWORD dwIsClear;                                        /*!< 0（新故障） or 1（故障恢复） */
} DevFaultInfo, *LPDevFaultInfo;

/*!
*  @struct  tagQuerySupport
*  @brief   能力查询信息
*/
typedef struct tagQuerySupportInfo
{
    char acIsSupport[MAX_QUERY_SUPPORT_NUM][MAX_SUPPORT_NAME_LEN]; /*!< 功能名称                        */
} QuerySupportInfo, *LPQuerySupportInfo;

/*!
*  @struct  tagQuerySupportResult
*  @brief   能力查询结果
*/
typedef struct tagQuerySupportResult
{
    char acSupport[MAX_QUERY_SUPPORT_NUM][MAX_SUPPORT_NAME_LEN];    /*!< 支持的功能                     */
    char acUnSupport[MAX_QUERY_SUPPORT_NUM][MAX_SUPPORT_NAME_LEN];  /*!< 不支持的功能                   */
} QuerySupportResult, *LPQuerySupportResult;

/*!
*  @struct  tagSystemUpdateParam
*  @brief   系统升级参数
*/
typedef struct tagSystemUpdateParam
{
    char szFTPIP[IP_ADDRESS_LEN];                                   /*!< FTP服务器IP */
    DWORD dwFTPPort;                                                /*!< FTP服务器端口 */
    char szFTPUserName[USERNAME_LEN];                               /*!< FTP服务器用户名 */
    char szFTPPassword[USERPASS_LEN];                               /*!< FTP服务器用户密码 */
    char szFTPFilePath[MAX_FILENAME];                               /*!< FTP服务器升级文件路径 */
    char szFTPFileName[MAX_FILENAME];                               /*!< FTP服务器升级文件名 */
} SystemUpdateParam, *LPSystemUpdateParam;

/*!
* @struct tagTimeSchemeItem
* @brief 时间段
*/
typedef struct tagTimeSchemeItem
{
    char szItemDay[HXHT_COMMON_STRING_LEN];                         /*!< 表示起止日期 */
    char szItemTime[HXHT_COMMON_STRING_LEN];                        /*!< 表示起止时间 */
} TimeSchemeItem, *LPTimeSchemeItem;

/*!
* @struct tagScheme
* @brief 布防时间
*/
typedef struct tagScheme
{
    char szSchemeCycle[HXHT_COMMON_STRING_LEN];                     /*!< 计划周期：day按天为周期，week按周为周期，month按月为周期 */
    TimeSchemeItem cTimeScheme[HXHT_MAX_ITEM_COUNT];                /*!< 时间计划节点 */
    int nValidItem;                                                 /*!< TimeSchemeItem有效的个数 */
} TimeScheme, *LPTimeScheme;

////////////////////////////////////Hxht//////////////////////////////////////

/*!
*  @struct  tagHxhtPTZSwitchStatus
*  @brief   Hxht PTZ开关状态
*/
typedef struct tagHxhtPTZSwitchStatus
{
    char acRandomScan[HXHT_COMMON_STRING_LEN];          /*!< 随机线扫开关 on--开 off-关                                             */
    char acLight[HXHT_COMMON_STRING_LEN];               /*!< 灯光开关 on--开 off-关                                                 */
    char acWiper[HXHT_COMMON_STRING_LEN];               /*!< 雨刷开关 on--开 off-关                                                 */
    char acProbe[HXHT_COMMON_STRING_LEN];               /*!< 探头开关 on--开 off-关                                                 */
    char acPower[HXHT_COMMON_STRING_LEN];               /*!< 电源开关 on--开 off-关                                                 */
    char acAutoFocus[HXHT_COMMON_STRING_LEN];           /*!< 自动聚焦开关 on--开 off-关                                             */
    char acAutoBright[HXHT_COMMON_STRING_LEN];          /*!< 自动光圈开关 on--开 off-关                                             */
    char acBackLight[HXHT_COMMON_STRING_LEN];           /*!< 背光补偿开关 on--开 off-关                                             */
    char acAutoNightVision[HXHT_COMMON_STRING_LEN];     /*!< 自动夜视开关 on--开 off-关                                             */
    char acNightVision[HXHT_COMMON_STRING_LEN];         /*!< 夜视开关 on--开 off-关                                                 */
    char acWatchPoint[HXHT_COMMON_STRING_LEN];          /*!< 看首位开关  on--开 off-关                                              */
    char acAid1[HXHT_COMMON_STRING_LEN];                /*!< 辅助1开关   on--开 off-关                                              */
    char acAid2[HXHT_COMMON_STRING_LEN];                /*!< 辅助2开关   on--开 off-关                                              */
} HxhtPTZSwitchStatus, *LPHxhtPTZSwitchStatus;

/*!
*  @struct  tagHxhtPTZAuxInfo
*  @brief   Hxht 辅助开关信息
*/
typedef struct tagHxhtPTZAuxInfo
{
    DWORD dwNum;                                        /*!< 辅助开关编号                                                           */
    char acName[HXHT_COMMON_STRING_LEN];                /*!< 辅助开关名称                                                           */
    char acSwitch[HXHT_COMMON_STRING_LEN];              /*!< on/off                                                                 */
} HxhtPTZAuxInfo, *LPHxhtPTZAuxInfo;

/*!
*  @struct  taHxhtPTZAuxSwitch
*  @brief   Hxht 辅助开关
*/
typedef struct tagHxhtPTZAuxSwitch
{
    DWORD dwCount;                                      /*!< 支持的辅助开关数                                                       */
    HxhtPTZAuxInfo sAuxInfo[MAX_AUX_SWITCH_NUM];        /*!< 辅助开关信息                                                           */
} HxhtPTZAuxSwitch, *LPHxhtPTZAuxSwitch;

/*!
*  @struct  tagHxhtPresetPoint
*  @brief   Hxht预置点信息
*/
typedef struct tagHxhtPresetPoint
{
    DWORD dwNum;                                        /*!< 预置点编号                                                             */
    char acName[HXHT_COMMON_STRING_LEN];                /*!< 预置点名称                                                             */
} HxhtPresetPoint, *LPHxhtPresetPoint;

/*!
*  @struct  tagHxhtPresetPointSetting
*  @brief   Hxht预置点设置信息
*/
typedef struct tagHxhtPresetPointSetting
{
    DWORD dwCount;                                      /*!< 支持预置点数                                                           */
    HxhtPresetPoint sPoint[MAX_PRESET_POINT_NUM];       /*!< 预置点信息                                                             */
} HxhtPresetPointSetting, *LPHxhtPresetPointSetting;

/*!
*  @struct  tagHxhtPTZSupport
*  @brief   Hxht PTZ支持功能
*  @note    dwOpCmd说明：8300--光圈大/小 8306--光圈停止 8302--数组变倍大/小 8308--数字变倍停止
            8200--云台开始动作 8202--云台停止动作 8204--随机线扫开/关 8206--预置点设置
            8208--预置点清除 8210--预置点调用 8212--预置点清除所有 8304--聚焦控制大/小
            8310--聚焦停止 8400--辅助开关 0--停止 1--云台上 2--云台下 3--云台左 4--云台右
            5--光圈大 6--光圈小 7--变倍大 8--变倍小 9--聚焦大 10--聚焦小 11--随机线扫开 12--随机线扫关
            13--灯光开 14--灯光关 15--雨刷开 16--雨刷关 17--探头电源开 18--探头电源关
            19--摄头电源开 20--摄头电源关
*/
typedef struct tagHxhtPTZSupport
{
    char acDirect[HXHT_COMMON_STRING_LEN];              /*!< 是否支持方向控制 y--支持 n--不支持                                     */
    char acBright[HXHT_COMMON_STRING_LEN];              /*!< 是否支持光圈(亮度)控制 y--支持 n--不支持                               */
    char acZoom[HXHT_COMMON_STRING_LEN];                /*!< 是否支持变倍控制 y--支持 n--不支持                                     */
    char acFocus[HXHT_COMMON_STRING_LEN];               /*!< 是否支持聚焦控制 y--支持 n--不支持                                     */
    char acFlip180[HXHT_COMMON_STRING_LEN];             /*!< 是否支持180度翻转 y--支持 n--不支持                                    */
    char acOriginalSetting[HXHT_COMMON_STRING_LEN];     /*!< 是否支持恢复原厂设置 y--支持 n--不支持                                 */
    char acEnterMenu[HXHT_COMMON_STRING_LEN];           /*!< 是否支持进入菜单模式 y--支持 n--不支持                                 */
    DWORD dwOpCmd[MAX_SUPPORT_OP_CMD_NUM];              /*!< 支持的云台控制命令号                                                   */
} HxhtPTZSupport, *LPHxhtPTZSupport;

/*!
*  @struct  tagHxhtPTZStatusInfo
*  @brief   Hxht PTZ状态信息
*/
typedef struct tagPTZStatusInfo
{
    char acStatus[HXHT_COMMON_STRING_LEN];              /*!< 云台状态,长度为5的'0'、'1' 字符串，该字符串的5个字符依次代表随机线扫、灯光、雨刷、探头、摄头的状态，'0'为关闭，'1'为打开*/
    HxhtPTZSwitchStatus sSwitchStatus;                  /*!< 开关状态                                                               */
    HxhtPTZAuxSwitch sAuxSwitch;                        /*!< 辅助开关信息                                                           */
    HxhtPresetPointSetting sPresetSetting;              /*!< 预置点设置                                                             */
    HxhtPTZSupport sSupport;                            /*!< 支持的TPZ功能                                                          */
} HxhtPTZStatusInfo, *LPHxhtPTZStatusInfo;

/*!
*  @struct  tagPanelStatusInfo
*  @brief   面板状态信息
*/
typedef struct tagPanelStatusInfo
{
    DWORD dwStatus;                                     /*!< 面板状态,0为未锁定,1为已锁定                                           */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                                                                   */
} PanelStatusInfo, *LPPanelStatusInfo;

/*!
*  @struct  tagPanelControlParameter
*  @brief   面板控制参数
*/
typedef struct tagPanelControlParameter
{
    DWORD dwControl;                                    /*!< 面板控制,参见ePanelControlType值                                       */
    DWORD dwKeyBoardCode;                               /*!< 面板键值,参见ePanelKeyBoardCodeType值                                  */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                                                                   */
} PanelControlParameter, *LPPanelControlParameter;

/*!
*  @enum    eRTPStreamTransferMode
*  @brief   RTP流传输方式
*/
typedef enum eRTPStreamTransferMode
{
    eRTPStreamTransferModeBegin     =   0,              /*!< 起始值                                 */
    eRTPGeneralTCP,                                     /*!< 普通的TCP                              */
    eRTPGeneralUDP,                                     /*!< 普通的UDP                              */
    eRTPStreamTransferModeEnd,                          /*!< 结束值                                 */
} eRTPStreamTransferMode;

/*!
*  @struct  eScreenControlStatus
*  @brief   屏幕控制状态
*/
typedef enum eScreenControlStatus
{
    eScreenControlStatusBegin                   = 0,    /*!< 起始值                                 */
    eScreenControlStatusLoopStart,                      /*!< 开始轮转                               */
    eScreenControlStatusLoopStop,                       /*!< 停止轮转                               */
    eScreenControlStatusSplitSingle,                    /*!< 单画面                                 */
    eScreenControlStatusSplitThree,                     /*!< 三画面                                 */
    eScreenControlStatusSplitFour,                      /*!< 四画面                                 */
    eScreenControlStatusSplitSix,                       /*!< 六画面                                 */
    eScreenControlStatusSplitNine,                      /*!< 九画面                                 */
    eScreenControlStatusSplitTen,                       /*!< 十画面                                 */
    eScreenControlStatusSplitTwelve,                    /*!< 十二画面                               */
    eScreenControlStatusSplitThirteen,                  /*!< 十三画面                               */
    eScreenControlStatusSplitFifteen,                   /*!< 十五画面                               */
    eScreenControlStatusSplitSixteen,                   /*!< 十六画面                               */
    eScreenControlStatusEnd,                            /*!< 结束值                                 */
} eScreenControlStatus;

/*!
*  @enum    eResolutionMode
*  @brief   分辨率模式
*/
typedef enum eResolutionMode
{
    eResolutionModeBegin                    =   0,          /*!< 起始值                                 */
    eResolutionModeAutoDiscern,                         /*!< 自动识别分辨率                             */
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
	eResolutionModeEnd,										/*!< 结束值									*/
} eResolutionMode;

/*!
*  @enum    eVGAResolutionMode
*  @brief   VGA分辨率
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
*  @brief   Logo图片类型
*/
typedef enum eLogoPictureType
{
    eLogoPictureTypeBegin                   = 0,        /*!< 起始值                                 */
    eLogoPictureTypeDecoderChannel,                     /*!< 解码通道LOGO                           */
    eLogoPictureTypeEnd,                                /*!< 结束值                                 */
} eLogoPictureType;

/*!
*  @enum    eDeviceChannelControl
*  @brief   设备通道控制
*/
typedef enum eDeviceChannelControl
{
    eDeviceChannelControlBegin       = 0,               /*!< 起始值                                 */
    eDeviceChannelControlShowLogo,                      /*!< 显示LOGO                               */
    eDeviceChannelControlHideLogo,                      /*!< 隐藏LOGO                               */
    eDeviceChannelControlEnd,                           /*!< 结束值                                 */
} eDeviceChannelControl;

/*!
*  @enum    eDeviceProtocolType
*  @brief   设备协议类型
*/
typedef enum eDeviceProtocolType
{
    eDeviceProtocolTypeBegin         = 0,               /*!< 起始值                                 */
    eDeviceProtocolTypeAdapter,                         /*!< 自适应版本                             */
    eDeviceProtocolTypeClassics,                        /*!< 经典版本                               */
    eDeviceProtocolTypeNewborn,                         /*!< 新版本                                 */
    eDeviceProtocolTypeEnd,                             /*!< 结束值                                 */
} eDeviceProtocolType;

/*!
*  @struct  tagRealStreamPara
*  @brief   实时流连接参数
*/
typedef struct tagRealStreamPara
{
	DWORD	dwChannel;									/*!< 流媒体通道号							*/
	enum eStreamTransferMode	eTransferMode;					/*!< 传输模式								*/
	enum eStreamMediaType	eMediaType;						/*!< 流媒体类型								*/
	DWORD	dwReserve[DEF_RESERVE_NUM];					/*!< 保留									*/
} RealStreamPara, *LPRealStreamPara;

/*!
*  @struct  tagUserLoginPara
*  @brief   用户登录参数
*/
typedef struct tagUserLoginPara
{
    char    sServerIP[MAX_ADDRESS_LEN];                 /*!< 服务器端IP地址                         */
    DWORD   dwCommandPort;                              /*!< 登录连接的信令端口                     */
    char    sUName[USERNAME_LEN];                       /*!< 登录用户的用户名称                     */
    char    sUPass[USERPASS_LEN];                       /*!< 登录用户的用户密码                     */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< 保留                                   */
} UserLoginPara, *LPUserLoginPara;

/*!
*  @struct  tagHistoryStreamPara
*  @brief   历史流连接参数
*/
typedef struct tagHistoryStreamPara
{
    DWORD   dwDiskGroup;                                /*!< 盘组                                   */
    DWORD   dwChannel;                                  /*!< 流媒体通道号                           */
    DWORD       dwEnableEndTime;                        /*!< 结束时间是否有效                       */
    TimeInfo    cBeginTime;                             /*!< 历史流起始时间                         */
	TimeInfo	cEndTime;								/*!< 历史流结束时间							*/
	enum eHistoryStreamType	eStreamType;					/*!< 历史流类型								*/
	enum eStreamTransferMode	eTransferMode;					/*!< 传输模式								*/
	DWORD	dwReserve[DEF_RESERVE_NUM];					/*!< 保留									*/
} HistoryStreamPara, *LPHistoryStreamPara;

/*!
*  @struct  tagChannelOSDInformation
*  @brief   通道OSD信息
*/
typedef struct tagChannelOSDInformation
{
    DWORD   dwEnable;                                   /*!< 启用: 0为不启用, 1为启用               */
    char    cOSDText[MAX_OSD_TEXT_STRING_LENGTH];       /*!< OSD信息                                */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< 保留                                   */
} ChannelOSDInformation, *LPChannelOSDInformation;

/*!
*  @struct  tagStreamTransferPara
*  @brief	流转发连接参数
*/
typedef struct tagStreamTransferPara
{
	enum eStreamTransferMode	eTransferMode;					/*!< 传输模式								*/
	eStreamSourceType eStreamSourceTypeValue;			/*!< 流媒体源类型							*/
	eVideoCodecMode	eVideoCodecType;					/*!< 视频编解码模式							*/
	enum eVoiceMode	eVoiceCoderType;						/*!< 音频编解码模式							*/
	eResolutionMode	eResolutionValue;					/*!< 图像分辨率模式							*/
    ChannelOSDInformation   cOSDInfo;                   /*!< OSD信息结构                            */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< 保留                                   */
} StreamTransferPara, *LPStreamTransferPara;

/*!
*  @struct  tagMediaServerInformation
*  @brief   流媒体服务器信息
*/
typedef struct tagMediaServerInformation
{
    DWORD   dwEnable;                                   /*!< 启用: 0为不启用, 1为启用               */
    char    sServerIP[MAX_ADDRESS_LEN];                 /*!< 服务器端IP地址                         */
    DWORD   dwServerPort;                               /*!< 登录连接的服务器端口                   */
    char    sUName[USERNAME_LEN];                       /*!< 登录用户的用户名称                     */
    char    sUPass[USERPASS_LEN];                       /*!< 登录用户的用户密码                     */
    eRTPStreamTransferMode  eRTPStreamTransferValue;    /*!< RTP流传输模式                          */
    char    sChannel[MAX_RTSP_SOURCE_STRING_LENGTH];    /*!< 视频通道                               */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< 保留                                   */
} MediaServerInformation, *LPMediaServerInformation;

/*!
*  @struct  tagHYPrivateServerInformation
*  @brief   HY私有协议服务器信息
*/
typedef struct tagHYPrivateServerInformation
{
    DWORD   dwEnable;                                   /*!< 启用: 0为不启用, 1为启用               */
    eDeviceProtocolType eDeviceProtocolValue;           /*!< 设备协议版本类型                       */
    eStreamSourceType   eStreamSourceValue;             /*!< 流媒体源类型                           */
    UserLoginPara   cUserLoginPara;                     /*!< 登录参数信息                           */
    RealStreamPara  cRealStreamPara;                    /*!< 实时流参数信息                         */
    HistoryStreamPara cHistoryStreamPara;               /*!< 历史流参数信息                         */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< 保留                                   */
} HYPrivateServerInformation, *LPHYPrivateServerInformation;

/*!
*  @struct  tagLocalHistoryInformation
*  @brief   本地历史流信息
*/
typedef struct tagLocalHistoryInformation
{
    DWORD       dwEnable;                               /*!< 启用: 0为不启用, 1为启用               */
    DWORD       dwEnableEndTime;                        /*!< 结束时间是否有效                       */
	TimeInfo	cBeginTime;								/*!< 历史流起始时间							*/
	TimeInfo	cEndTime;								/*!< 历史流结束时间							*/
	enum eHistoryStreamType	eStreamType;					/*!< 历史流类型								*/
	DWORD	dwReserve[DEF_RESERVE_NUM];					/*!< 保留									*/
} LocalHistoryInformation, *LPLocalHistoryInformation;

/*!
*  @struct  tagDecoderDynamicInformation
*  @brief   动态解码服务器信息
*/
typedef struct tagDecoderDynamicInformation
{
    MediaServerInformation  cMediaServerInfo;           /*!< 流媒体服务器信息                       */
    HYPrivateServerInformation  cHYPrivateServerInfo;   /*!< HY私有协议服务器信息                   */
    LocalHistoryInformation cLocalHistoryInformation;   /*!< 本地历史流信息                         */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< 保留                                   */
} DecoderDynamicInformation, *LPDecoderDynamicInformation;

/*!
*  @struct  tagDecoderChannelSourceConfig
*  @brief   解码器通道视频源配置
*/
typedef struct tagDecoderChannelSourceConfig
{
    MediaServerInformation  cMediaServerInfo;           /*!< 流媒体服务器信息                           */
    HYPrivateServerInformation  cHYPrivateServerInfo;   /*!< HY私有协议服务器信息                       */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< 保留                                   */
} DecoderChannelSourceConfig, *LPDecoderChannelSourceConfig;

/*!
*  @struct  tagDecoderChannelLoopConfig
*  @brief   解码器通道轮转配置
*/
typedef struct tagDecoderChannelLoopConfig
{
    DWORD   dwEnable;                               /*!< 是否启用                               */
    DWORD   dwPoolTime;                         /*!< 轮巡时间                               */
    DecoderChannelSourceConfig cSource[MAX_DECODER_CHANNEL_SOURCE];/*!< 通道视频源配置                      */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< 保留                                   */
} DecoderChannelLoopConfig, *LPDecoderChannelLoopConfig;

/*!
*  @struct  tagDecoderLoopStatus
*  @brief   解码器通道轮询状态
*/
typedef struct tagDecoderLoopStatus
{
    DWORD   dwChannelNumber;                            /*!< 通道数                                 */
    eDecoderChannelStatus   eDecChStatus[MAX_DEC_CHANNEL_NUMBER];/*!< 通道状态                      */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                                   */
} DecoderLoopStatus, *LPDecoderLoopStatus;

/*!
*  @struct  tagDecoderDeviceConfig
*  @brief   解码器设备配置
*/
typedef struct tagDecoderDeviceConfig
{
    DWORD   dwDecoderChannelNumber;                 /*!< 解码通道个数,根据解码模式决定个数,只读配置项   */
    eResolutionMode eDecodeMode;                    /*!< 解码模式                               */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< 保留                                   */
} DecoderDeviceConfig, *LPDecoderDeviceConfig;

/*!
*  @struct  tagDecoderChannelInformation
*  @brief   解码器通道信息
*/
typedef struct tagDecoderChannelInformation
{
    DWORD   dwDecoderState;                     /*!< 解码通道状态：0-动态解码 1－循环解码           */
    DWORD   dwGetStreamMode;                        /*!< 取流模式：0-未解码，1-主动，2-被动         */
    MediaServerInformation  cMediaServerInfo;           /*!< 流媒体服务器信息                           */
    HYPrivateServerInformation  cHYPrivateServerInfo;   /*!< HY私有协议服务器信息                       */
    LocalHistoryInformation cLocalHistoryInformation;       /*!< 本地历史流信息                         */
    StreamTransferPara  cStreamTransferPara;                /*!< 被动解码流转发信息                     */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< 保留                                   */
} DecoderChannelInformation, *LPDecoderChannelInformation;

/*!
*  @struct  tagDecoderChannelStatusInfo
*  @brief   解码器通道状态信息
*/
typedef struct tagDecoderChannelStatusInfo
{
    eDecoderChannelStatus   eDecChStatus;               /*!< 通道状态                   */
    eStreamSourceType   eStreamSourceTypeValue;         /*!< 流媒体源类型               */
    DWORD   dwStreamBitrate;                        /*!< 流媒体码率(kbps)           */
    DWORD   dwVideoWidth;                           /*!< 视频图像宽度               */
    DWORD   dwVideoHeight;                      /*!< 视频图像高度               */
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< 保留                                   */
} DecoderChannelStatusInfo, *LPDecoderChannelStatusInfo;

/*!
*  @struct  tagDecoderChannelStatus
*  @brief   解码器通道状态
*/
typedef struct tagDecoderChannelStatus
{
    DWORD   dwChannelNumber;                            /*!< 通道数             */
    DecoderChannelStatusInfo    cDecChStatus[MAX_DEC_CHANNEL_NUMBER];/*!< 解码器通道状态信*/
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                   */
} DecoderChannelStatus, *LPDecoderChannelStatus;

/*!
*  @struct  tagDecoderChannelControl
*  @brief   解码器通道控制
*/
typedef struct tagDecoderChannelControl
{
    eDecoderChannelStatus   eDecChStatus[MAX_DEC_CHANNEL_NUMBER];/*!< 解码器通道状态*/
    DWORD   dwReserve[DEF_RESERVE_NUM];                 /*!< 保留                                   */
} DecoderChannelControl, *LPDecoderChannelControl;

/*!
*  @struct  tagDecoderSetPlayStatusParameter
*  @brief   设置解码器通道播放状态参数
*/
typedef struct tagDecoderSetPlayStatusParameter
{
    eStreamPlayControlStatus    ePlayControlStatus;     /*!< 流播放状态控制     */
    DWORD dwParameter[MAX_PLAY_CONTROL_PARAMETER];          /*!< 流播放状态控制参数     */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                   */
} DecoderSetPlayStatusParameter, *LPDecoderSetPlayStatusParameter;

/*!
*  @struct  tagDecoderPlayStatusParameter
*  @brief   解码器通道播放状态参数
*/
typedef struct tagDecoderPlayStatusParameter
{
    eStreamSourceType   eStreamSourceTypeValue;             /*!< 流媒体源类型           */
    DWORD       dwEnableEndTime;                        /*!< 结束时间是否有效       */
    TimeInfo    cBeginTime;                             /*!< 历史流起始时间     */
    TimeInfo    cEndTime;                                   /*!< 历史流结束时间     */
    TimeInfo    cCurrentTime;                               /*!< 当前播放的历史流时间   */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                   */
} DecoderPlayStatusParameter, *LPDecoderPlayStatusParameter;

/*!
*  @struct  tagDecoderGetPlayStatusParameter
*  @brief   获取解码器通道播放状态参数
*/
typedef struct tagDecoderGetPlayStatusParameter
{
    DWORD   dwChannelNumber;                            /*!< 通道数             */
    DecoderPlayStatusParameter  cDecChPlayStatus[MAX_DEC_CHANNEL_NUMBER];/*!< 解码器通道播放状态信息*/
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                   */
} DecoderGetPlayStatusParameter, *LPDecoderGetPlayStatusParameter;

/*!
*  @struct  tagDecoderSetDisplayStatusParameter
*  @brief   设置解码通道显示状态参数
*/
typedef struct tagDecoderSetDisplayStatusParameter
{
    eDisplayControlStatus   eDisplayControlStatusValue;     /*!< 显示控制状态信息       */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                   */
} DecoderSetDisplayStatusParameter, *LPDecoderSetDisplayStatusParameter;

/*!
*  @struct  tagDecoderDisplayConfig
*  @brief   解码显示配置
*/
typedef struct tagDecoderDisplayConfig
{
    eVGAResolutionMode  eVGAResolution;             /*!<    分辨率                              */
    eScreenControlStatus    eScreenControlStatusValue;      /*!< 显示控制状态信息                           */
    DWORD   dwDecoderChannel[MAX_DISPLAY_SCREEN_NUMBER];    /*!< 绑定的解码通道号                           */
    DWORD   dwEnlargeWindow;                        /*!< 窗口放大, 0xFFFFFFFF表示不放大,其它表示窗口编号    */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                                   */
} DecoderDisplayConfig, *LPDecoderDisplayConfig;

/*!
*  @struct  tagChannelChromaConfig
*  @brief   解码通道光学参数
*/
typedef struct tagChannelChromaConfig
{
    DWORD dwBrightness;                             /*!< 亮度,0-255                             */
    DWORD dwContrast;                               /*!< 对比度,0-255                           */
    DWORD dwSaturation;                             /*!< 饱和度,0-255                           */
    DWORD dwHue;                                    /*!< 色调,0-255                             */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                                   */
} ChannelChromaConfig, *LPChannelChromaConfig;

/*!
*  @struct  tagDecoderChannelConfig
*  @brief   解码器通道配置
*/
typedef struct tagDecoderChannelConfig
{
    DWORD   dwDecChanScaleStatus;                   /*!< 解码通道显示缩放控制，1-缩放显示，0-真实显示   */
    ChannelChromaConfig cChannelChromaConfig;           /*!< 光学参数                               */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< 保留                                   */
} DecoderChannelConfig, *LPDecoderChannelConfig;

/*!
*  @struct  tagDecoderVideoStandardConfig
*  @brief   解码器通道视频制式
*/
typedef struct tagDecoderVideoStandardConfig
{
    DWORD   dwVideoStandard;                        /*!< 解码器视频制式: 0-PAL，1-NTSC                  */
    DWORD   dwReserve[DEF_RESERVE_NUM];             /*!< 保留                                   */
} DecoderVideoStandardConfig, *LPDecoderVideoStandardConfig;

/*!
*  @struct  tagHistoryStreamMultiTypeQueryFactor
*  @brief   历史流查询条件
*/
typedef struct tagHistoryStreamMultiTypeQueryFactor
{
    DWORD               dwChannel;                      /*!< 通道号                                 */
    DWORD               dwDiskGroup;                    /*!< 盘组                                   */
    DWORD               dwStreamType;                   /*!< 历史流类型                             */
    char                cBeginTime[15];                 /*!< 起始时间                               */
    char                cEndTime[15];                   /*!< 结束时间                               */
} HistoryStreamMultiTypeQueryFactor, *LPHistoryStreamMultiTypeQueryFactor;

/*!
*  @struct  tagTransmitHistoryStreamQueryFactor
*  @brief   转发历史流查询条件
*/
typedef struct tagTransmitHistoryStreamQueryFactor
{
    UserLoginPara   cUserLoginPara;                 /*!< 登录参数信息                           */
    eDeviceProtocolType eDeviceProtocolValue;           /*!< 设备协议版本类型                           */
    HistoryStreamMultiTypeQueryFactor cFactor;          /*!< 历史查询条件                           */
    DWORD dwReserve[DEF_RESERVE_NUM];                   /*!< 保留                                   */
} TransmitHistoryStreamQueryFactor, *LPTransmitHistoryStreamQueryFactor;

//////////////////////////////////////////////////////////////////////////
//接口
//////////////////////////////////////////////////////////////////////////
/////////////////////////////配置信息/////////////////////////////////////

#endif

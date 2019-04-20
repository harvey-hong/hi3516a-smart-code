#ifndef _INC_GLOBAL_MACRO_H_
#define _INC_GLOBAL_MACRO_H_

#ifndef BOOL
#define BOOL	int
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef TRUE
#define TRUE	1
#endif


#if defined(EGUI_FOR_ICAMERA_CI785_BASED_DVR) ||defined(EGUI_FOR_ICAMERA_NXP8850_BASED_DVR)
#define USE_ICAMERA	1
#endif

#define IDVR_LIL_ENDIAN  1234

#define IDVR_BIG_ENDIAN  4321


#if  defined(__i386__) || defined(__ia64__) || (defined(__alpha__) || defined(__alpha)) || defined(__arm__) || (defined(__mips__) && defined(__MIPSEL__)) || defined(__LITTLE_ENDIAN__)
#define IDVR_BYTEORDER   IDVR_LIL_ENDIAN
#else
#define IDVR_BYTEORDER   IDVR_BIG_ENDIAN
#endif

#ifndef iDvrArchSwap16
static inline unsigned short iDvrArchSwap16(unsigned short  D)
{
	return ((D << 8) | (D >> 8));
}
#endif

#ifndef iDvrArchSwap32
static inline unsigned int iDvrArchSwap32(unsigned int D)
{
	return ((D << 24) | ((D << 8) & 0x00FF0000) | ((D >> 8) & 0x0000FF00) | (D >> 24));
}
#endif


/* Byteswap item from the specified endianness to the native endianness */
#if IDVR_BYTEORDER == IDVR_LIL_ENDIAN

/** Swaps a 16-bit little endian integer to the native endianness. */
#define iDvrArchSwapLE16(X)        (X)

/** Swaps a 32-bit little endian integer to the native endianness. */
#define iDvrArchSwapLE32(X)        (X)

/** Swaps a 16-bit big endian integer to the native endianness. */
#define iDvrArchSwapBE16(X)        iDvrArchSwap16(X)

/** Swaps a 32-bit big endian integer to the native endianness. */
#define iDvrArchSwapBE32(X)        iDvrArchSwap32(X)
#else
#define iDvrArchSwapLE16(X)        iDvrArchSwap16(X)
#define iDvrArchSwapLE32(X)        iDvrArchSwap32(X)
#define iDvrArchSwapBE16(X)        (X)
#define iDvrArchSwapBE32(X)        (X)
#endif



/*!< 默认配置文件路径，一般用于恢复默认配置 */
#define IDVR_DEFAULT_CONFIG_FILE_PATH	"/usr/local/etc/Edvr.default"

/*!< 当前正在使用的配置文件路径 */
#define IDVR_CURRENT_CONFIG_FILE_PATH	"/usr/local/etc/Edvr.cfg"

/*!< 当前正在使用的配置文件的备份 */
#define IDVR_BACKUP_CONFIG_FILE_PATH	"/usr/local/etc/Edvr.cfg-bak"

/*!< 版本信息文件 */
#define IDVR_VERSION_CONFIG_FILE_PATH	"/root/edvr/DeviceVersion.ini"

/*!< 视频预览通道别名*/
#define IDVR_OSD_ALIAS		"/root/edvr/res/osd_CH%02d.bmp"
#define SECTION_OSD_ALIAS	"ChannelAlias_%d"
#define DEFNAME_OSD_ALIAS	"CH%02d"

/*!< 报警输入通道别名*/
#define IDVR_DIP_ALIAS		"/root/edvr/res/AlarmIn_%02d.bmp"
#define SECTION_DIP_ALIAS	"AlarmInAlias_%d"
#define DEFNAME_DIP_ALIAS	"AI%02d"

/*!< 报警输出通道别名*/
#define IDVR_DOP_ALIAS		"/root/edvr/res/AlarmOut_%02d.bmp"
#define SECTION_DOP_ALIAS	"AlarmOutAlias_%d"
#define DEFNAME_DOP_ALIAS	"AO%02d"

/*!< 设备别名*/
#define IDVR_DEV_ALIAS		"/root/edvr/res/dev_alias.bmp"
#define SECTION_DEV_ALIAS	"iDVR_Alias"
#define DEFNAME_DEV_ALIAS	"IPC"


// 最大支持编码、解码通道数、报警输入个数
#define MAX_ENC_CHANNEL_NUM		1
#define MAX_DEC_CHANNEL_NUM		0
#define MAX_ALARMIN_NUM 			4
#define MAX_ALARMOUT_NUM 			4

//spot口数目
#define MAX_SPOT_NUM (4)

/*! 字符串表示的时间长度，格式"YYYYmmDDHHMMSS\0"*/
#define REC_TIME_LEN			15


/* 播放模式 */
#define AVP_MODE_NORMAL				0
#define AVP_MODE_BROWSE				1
#define AVP_IS_NORMAL_MODE(x)		((x) == AVP_MODE_NORMAL)
#define AVP_IS_BROWSE_MODE(x)		((x) == AVP_MODE_BROWSE)


/* 播放方向 */
#define AVP_DIRECT_FORWARD			0
#define AVP_DIRECT_BACKWARD			1
#define AVP_IS_FORWARD(x)			((x) == AVP_DIRECT_FORWARD)
#define AVP_IS_BACKWARD(x)			((x) == AVP_DIRECT_BACKWARD)


/* others */
#define SET_BIT(x, i)				((x) |= (1 << i))
#define UNSET_BIT(x, i)				((x) &= ~(1 << i))
#define IS_SET_BIT(x, i)			((x) & (1 << i))

// Eliminate the warning yh start
//!\brief 管理员用户名
#define ADMIN_USRNAME (char *)"admin"

//!\brief 管理员和默认用户的初始密码
#define DEFAULT_PASSWORD (char *)"admin"
// Eliminate the warning yh end

#define	IDVR_MAX_USER			10

// 包含结束符:用户名和密码
#define 	MAX_USERNAME_LEN		17

// 密码字符串最大长度
#define 	MAX_PASSWORD_LEN		17

#define 	MAX_EMAIL_LEN			248

//!\brief MAC地址字节数
#define	MAC_ADDRESS_BYTES	6

//!\brief 云台协议名长度
#define	MAX_PROTONAME_LEN	48

//!\brief 内部/外部云台协议各256
#define	MAX_PROTOCOL_NUM		256

#define	NET_MAX_DOMAINNAME_LEN	(256)
#define	NET_MAX_EMAIL_LEN			(256)
#define	NET_MAX_PASSWORD_LEN		(64)

//!\brief IP白名单个数
#define	MAX_WHITEIP_NUM		10

//\\ 系统日志存放路径
#define	IDVR_PATH_LOG				(char *)"/usr/local/etc/log.db"
// Eliminate the warning yh end (char *)

//\\ 系统用户存放路径
#define	IDVR_PATH_USR				"/usr/local/etc/user.db"

//add by liuy date 2016-01-12 start
//\\ 系统用户存放路径 文本格式
#define	IDVR_PATH_USR_TXT			"/usr/local/etc/user.txt"
//add by liuy date 2016-01-12 end

#define	IDVR_PATH_DEF_CONFIG		"/usr/local/etc/Edvr.flag"

#define	IDVR_PATH_NET_PORT_CONFIG	"/home/http/Config.html"


#define	DISKMANGER_MAX_DISK_NUM		1
#define UPDATEFLAG  				"/root/edvr/.update_success"
#define UPDATEFILEPATH 				"/"
#ifdef _HISI_V300_
#define UPDATEFILEFILE 				"/bin/vs/tmpfs/hy_edvr_update.tar.gz"
#define UPDATEFILENAME 			"/bin/vs/tmpfs/hy_edvr_update.tar.gz"
#endif
#ifdef _HISI_V100_
#define UPDATEFILEFILE 				"/root/edvr/hy_edvr_update.tar.gz"
#define UPDATEFILENAME 			"/root/edvr/hy_edvr_update.tar.gz"
#endif
#define IMPORTFILENAME 				"/root/edvr/hy_edvr_remote_config.xml"
#define PTZ_PATH  					"/root/edvr/download"

#define FULL_DISK_SIZE   			500

//移动块宽高
#define  MAX_MAGIC_BLOCK_WIDTH    	(704/16)
#define  MAX_MAGIC_BLOCK_HEIGHT    (576/12)
//移动块个数
#define   MAX_MAGIC_BLOCK_NUM    	(16*12)

#define MAX_CH_NUM 				1

#define 	TTY_DEV 				(char *)"/dev/ttyS"

#define	PARTNAME_TF				"/dev/mmcblk0"

#define	MAX_RS_TYPE				3

#define NTP_SYNC_TIME_FILE 		"/var/run/sync_ntp"

/* 视频文件存储路径 */
#define VIDEODIR        			(char *)"videoout"

#define PICDIR                     (char*)"picout"

#define VIDEOSYSPLASE				"/sys/block/mmcblk0"

#define DEV_PATH_FORMAT  			"/dev/mmcblk%d"

#define DEV_PATH     					"/dev/mmcblk"

#define DEV_PATH_PART				"/dev/mmcblk0p1"

#define MOUNTPOINT 					"/dat"

#define MOUNTTFTMPFILE				"/dev/tf_tmp.dat"

#define DEV_PATH_INDEX				11

#define IS_FAT_PARTITION(x)			((0x6 == (x)) ||(0xB == (x)) || (0xC == (x)) || (0xE == (x)))

#define IS_EXTERN_PARTITION(x)		((0x5 == (x)) ||(0xF == (x)))

#define IS_SDCARD(dev)				((strstr(dev, DEV_PATH) == dev) && (strlen(dev) > 10))

#define IS_SDCARD_MOUNTPOINT(dev)	((strstr(dev, MOUNTPOINT) == dev))

#define IS_SDCARD_PARTITION(dev)	((strstr(dev, DEV_PATH) == dev) && (strlen(dev) >= 12) && ('p' == dev[12]))

/***********************************************************************/
//\\ NTP对应配置文件中Section 
#define	INTP_CfgSection				"INTP_Cfg"

//\\ DDNS对应配置文件中Section
#define	DDNS_CfgSection 			"DDNS_Cfg"

//\\ PPPOE对应配置文件中Section
#define 	IPPPOE_CfgSection 			"IPPPOE_Cfg"

//\\ INET对应配置文件中Section
#define 	INet_CfgSection 				"INet_Cfg"

#define     AlarmServer_CfgSection          "AlarmServerCfg" /* CB 20160223 报警服务器接口封装 start--end */
//\\ 用户非法访问
#define ILLEGEACCESS_SECTION 		"IllegeAccessCfg"

#define	NET_EMAIL_CFG				"Email_Cfg"

#define	MosaicCfgSection 			"MosaicCfg"

#define	MotionCfgSection 			"MotionCfg"

#define	OsdCfgSection 				"OsdCfg"

#define	RecordCfgSection 			"RecordCfg"

#define	AlarmOutSectionStr			"AlarmOutCfg"

#define	AlarmInSectionStr			"AlarmInCfg"

#define	DEV_PUB_CFG    				"PUB"

#define 	AuxCoderCfgSection 			"AuxCoderCfg"

#define	ISPCfgSection				"IMGISP"

/***********************************************************************/
#endif							/* #ifndef _INC_GLOBAL_MACRO_H_ */

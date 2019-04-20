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



/*!< Ĭ�������ļ�·����һ�����ڻָ�Ĭ������ */
#define IDVR_DEFAULT_CONFIG_FILE_PATH	"/usr/local/etc/Edvr.default"

/*!< ��ǰ����ʹ�õ������ļ�·�� */
#define IDVR_CURRENT_CONFIG_FILE_PATH	"/usr/local/etc/Edvr.cfg"

/*!< ��ǰ����ʹ�õ������ļ��ı��� */
#define IDVR_BACKUP_CONFIG_FILE_PATH	"/usr/local/etc/Edvr.cfg-bak"

/*!< �汾��Ϣ�ļ� */
#define IDVR_VERSION_CONFIG_FILE_PATH	"/root/edvr/DeviceVersion.ini"

/*!< ��ƵԤ��ͨ������*/
#define IDVR_OSD_ALIAS		"/root/edvr/res/osd_CH%02d.bmp"
#define SECTION_OSD_ALIAS	"ChannelAlias_%d"
#define DEFNAME_OSD_ALIAS	"CH%02d"

/*!< ��������ͨ������*/
#define IDVR_DIP_ALIAS		"/root/edvr/res/AlarmIn_%02d.bmp"
#define SECTION_DIP_ALIAS	"AlarmInAlias_%d"
#define DEFNAME_DIP_ALIAS	"AI%02d"

/*!< �������ͨ������*/
#define IDVR_DOP_ALIAS		"/root/edvr/res/AlarmOut_%02d.bmp"
#define SECTION_DOP_ALIAS	"AlarmOutAlias_%d"
#define DEFNAME_DOP_ALIAS	"AO%02d"

/*!< �豸����*/
#define IDVR_DEV_ALIAS		"/root/edvr/res/dev_alias.bmp"
#define SECTION_DEV_ALIAS	"iDVR_Alias"
#define DEFNAME_DEV_ALIAS	"IPC"


// ���֧�ֱ��롢����ͨ�����������������
#define MAX_ENC_CHANNEL_NUM		1
#define MAX_DEC_CHANNEL_NUM		0
#define MAX_ALARMIN_NUM 			4
#define MAX_ALARMOUT_NUM 			4

//spot����Ŀ
#define MAX_SPOT_NUM (4)

/*! �ַ�����ʾ��ʱ�䳤�ȣ���ʽ"YYYYmmDDHHMMSS\0"*/
#define REC_TIME_LEN			15


/* ����ģʽ */
#define AVP_MODE_NORMAL				0
#define AVP_MODE_BROWSE				1
#define AVP_IS_NORMAL_MODE(x)		((x) == AVP_MODE_NORMAL)
#define AVP_IS_BROWSE_MODE(x)		((x) == AVP_MODE_BROWSE)


/* ���ŷ��� */
#define AVP_DIRECT_FORWARD			0
#define AVP_DIRECT_BACKWARD			1
#define AVP_IS_FORWARD(x)			((x) == AVP_DIRECT_FORWARD)
#define AVP_IS_BACKWARD(x)			((x) == AVP_DIRECT_BACKWARD)


/* others */
#define SET_BIT(x, i)				((x) |= (1 << i))
#define UNSET_BIT(x, i)				((x) &= ~(1 << i))
#define IS_SET_BIT(x, i)			((x) & (1 << i))

// Eliminate the warning yh start
//!\brief ����Ա�û���
#define ADMIN_USRNAME (char *)"admin"

//!\brief ����Ա��Ĭ���û��ĳ�ʼ����
#define DEFAULT_PASSWORD (char *)"admin"
// Eliminate the warning yh end

#define	IDVR_MAX_USER			10

// ����������:�û���������
#define 	MAX_USERNAME_LEN		17

// �����ַ�����󳤶�
#define 	MAX_PASSWORD_LEN		17

#define 	MAX_EMAIL_LEN			248

//!\brief MAC��ַ�ֽ���
#define	MAC_ADDRESS_BYTES	6

//!\brief ��̨Э��������
#define	MAX_PROTONAME_LEN	48

//!\brief �ڲ�/�ⲿ��̨Э���256
#define	MAX_PROTOCOL_NUM		256

#define	NET_MAX_DOMAINNAME_LEN	(256)
#define	NET_MAX_EMAIL_LEN			(256)
#define	NET_MAX_PASSWORD_LEN		(64)

//!\brief IP����������
#define	MAX_WHITEIP_NUM		10

//\\ ϵͳ��־���·��
#define	IDVR_PATH_LOG				(char *)"/usr/local/etc/log.db"
// Eliminate the warning yh end (char *)

//\\ ϵͳ�û����·��
#define	IDVR_PATH_USR				"/usr/local/etc/user.db"

//add by liuy date 2016-01-12 start
//\\ ϵͳ�û����·�� �ı���ʽ
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

//�ƶ�����
#define  MAX_MAGIC_BLOCK_WIDTH    	(704/16)
#define  MAX_MAGIC_BLOCK_HEIGHT    (576/12)
//�ƶ������
#define   MAX_MAGIC_BLOCK_NUM    	(16*12)

#define MAX_CH_NUM 				1

#define 	TTY_DEV 				(char *)"/dev/ttyS"

#define	PARTNAME_TF				"/dev/mmcblk0"

#define	MAX_RS_TYPE				3

#define NTP_SYNC_TIME_FILE 		"/var/run/sync_ntp"

/* ��Ƶ�ļ��洢·�� */
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
//\\ NTP��Ӧ�����ļ���Section 
#define	INTP_CfgSection				"INTP_Cfg"

//\\ DDNS��Ӧ�����ļ���Section
#define	DDNS_CfgSection 			"DDNS_Cfg"

//\\ PPPOE��Ӧ�����ļ���Section
#define 	IPPPOE_CfgSection 			"IPPPOE_Cfg"

//\\ INET��Ӧ�����ļ���Section
#define 	INet_CfgSection 				"INet_Cfg"

#define     AlarmServer_CfgSection          "AlarmServerCfg" /* CB 20160223 �����������ӿڷ�װ start--end */
//\\ �û��Ƿ�����
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

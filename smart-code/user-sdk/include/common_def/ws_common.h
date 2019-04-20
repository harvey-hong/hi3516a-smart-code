#ifndef _WS_COMMON_H_
#define _WS_COMMON_H_

#include <string.h> 

#include "ws_comm_type.h"

#ifdef __cplusplus
extern "C" {

namespace ws_utility 
{
#endif

// 设备定时保存最后系统时间文件
#define WS_TIME_FILE_NAME  "/config/time.dat"

// 超级用户密码复位延迟判断时间
#define SUPER_USER_RESET_TIME 3  

// 网络相关宏定义
#define DNS_RESOLV_FILE  "/etc/resolv.conf"
#define WS_IF_ETH0_NAME "eth0"
#define WS_IF_WLAN0_NAME "wlan0"
#define ETH0_DHCP_INFO_FILE "/var/run/network.eth0"
#define WLAN0_DHCP_INFO_FILE "/var/run/network.wlan0"
#define WS_DNS_NAME "nameserver "
#define WS_DEFAULTE_NAME "default"

// 备份相关的宏定义
#define WS_CD_INFO_NAME                     "/usr/local/cd.info"  //cd信息的文件名，在创建之后由备份线程获取cd信息在获取信息之后删除
#define WS_FILE_NAME_OF_ISO               "smartech_nvr_bak.iso"
#define WS_MKISOFS_TOOL_SHM_KEY     "/mnt/mtd/app/libbackup.so"     //key值
#define WS_CDRECORD_TOOL_SHM_KEY  "/mnt/mtd/app/libbackup.so"    //key值

// 磁盘与刻录机相关宏定义
#define  WS_DISK_DEV_NODE                   "/dev/sd"
#define  WS_SCSI_DEV_NODE                   "/dev/sr"

#define  WS_SYS_PARTITION                   "/proc/partitions"
#define  WS_SYS_PARTITION_MOUNT      "/proc/mounts"
#define WS_DISK_FMT_LOG_FILE             "/config/fmt_log_"

// 日志相关宏定义
#define WS_LOG_FILE_NAME    	          "/config/sys_log.dat"

// 网络相关宏定义
#define APP_MUTTPATH            "/mnt/tool/mutt"		
#define APP_MSMTPPATH          "/mnt/tool/msmtp"       
#define RC_MUTTPATH              "/usr/local/rcmutt"
#define RC_MUTTPATH_TEST    "/usr/local/rcmutt_test"
#define RC_MSMTPPATH            "/usr/local/msmtprc"
#define RC_MSMTPPATH_TEST  "/usr/local/msmtprc_test"

// 数据库定义
#define WS_SQLITE_DATABASE_MAIN_BODY "ws_sqlite_list_file_v"
#define WS_SQLITE_DATABASE_VERSION_NO "6"	

// 设备支持文件解析器个数
const WS_U32 g_max_parser_num = 128;

const WS_U32 m_max_support_bd = 32;

const WS_U32 SQLITE_PARSER_MAX = 128;


const int MAX_REMOTE_TASK_NUM = 32;

// max IPC channel cnt 
const WS_U32 MAX_CLIENT_NUMBER = 16 ;

#define FOX_HELPER_DLL_EXPORT __attribute__ ((visibility("default")))
#define FOX_HELPER_DLL_LOCAL  __attribute__ ((visibility("hidden")))

#define WS_CHAR_2_INT(arg)      ((ws_force_char_2_int *)(arg))->para_int
#define WS_CHAR_2_SHORT(arg)    ((ws_force_char_2_short *)(arg))->para_short

#define WS_ARRAY_DIM(arg)   (WS_S32)(sizeof(arg) / sizeof(arg[0]))
#define WS_CLR_ARRAY(arg)   memset(arg, 0, sizeof(arg))
#define WS_SET_ARRAY(arg, value)    \
    do{                             \
        for(int ws_9527dsaf = 0; ws_9527dsaf < WS_ARRAY_DIM(arg); ws_9527dsaf++)    \
            arg[ws_9527dsaf] = value;   \
    }while(0)

#define WS_CLR_ARG(arg)     memset(&arg, 0, sizeof(arg))
#define WS_TST_BIT(arg, bit) (((arg) & (1 << (bit))) != 0)
#define WS_SET_BIT(arg, bit) ((arg) |= (1 << (bit)))
#define WS_CLR_BIT(arg, bit) ((arg) &= ~(1 << (bit)))

#define WS_TST_BIT_EX(arg,num,bit)		(((arg[(bit)/32]) & (1 << ((bit) % 32))) != 0)
#define WS_SET_BIT_EX(arg,num,bit)		((arg[(bit)/32]) |= (1 << ((bit) % 32)))
#define WS_CLR_BIT_EX(arg,num,bit) 		((arg[(bit)/32]) &= ~(1 << ((bit) % 32)))
#define WS_GET_BIT_EX(arg,num,bit)		((arg[(bit)/32]) & (1 << ((bit) % 32)))

#define WS_ANY(arg,ret)		\
	do{                             \
        for(int ws_9527dsaf = 0; ws_9527dsaf < WS_ARRAY_DIM(arg); ws_9527dsaf++)    \
		if(arg[ws_9527dsaf])			\
		{				\
            ret = 1;   \
			break;		\
		}				\
		else			\
			ret = 0;	\
    }while(0)


#define BACKUP_LIST_MAX_LINE        5000

const  WS_U32 WS_NVR_AI_MAX_DEV_NUM  = 5 ;
        
const  WS_U32 WS_NVR_AO_MAX_DEV_NUM  = 2 ;

const  WS_U32 WS_NVR_MAX_AUDIO_CH  = 16  ; 

const WS_U32 WS_NVR_MAX_AO_CH_NUM = 16 ; 

const  WS_U32 WS_NVR_MAX_ADEC_NUM =  _MAX_CHANNEL_NUM_ ;

const  WS_U32 WS_NVR_MAX_AENC_NUM = _MAX_CHANNEL_NUM_ ; 

#define WS_MEMBER_OFSET(s, m)   (WS_S32)&(((s *)0)->m)

const WS_U32 WS_NVR_MAX_CH_NUM = _MAX_CHANNEL_NUM_;

const WS_U32 WS_NVR_MAX_MASK_NUM = ((_MAX_CHANNEL_NUM_ + 32 - 1) & (~(32 - 1))) / 32;

const WS_U32 WS_NVR_MAX_PLAY_CH_NUM = _MAX_CHANNEL_NUM_;

const WS_U32 WS_NVR_MAX_VOLUME = 15;

const WS_U32 WS_NVR_MAX_COLOR_PARA = 255;

const WS_U32 WS_NVR_MAX_SCHEDULE_PER_DAY = 4;

#define WS_RESERVED_GROUP_NAME	"root"

#define WS_RESERVED_USR_NAME	"admin"	

const WS_U32 WS_NVR_MAX_GROUP_NUM = 8; 

const WS_U32 WS_NVR_MAX_USR_NUM = 10;  

const WS_U32 WS_NVR_MAX_GROUP_NAME_LEN = 32;

const WS_U32 WS_NVR_MAX_USR_NAME_LEN = 32; 

const WS_U32 WS_NVR_MAX_ADDR_LEN = 128;

const WS_U32 WS_NTP_SERVER_NAME_LEN = 128; 

const WS_U32 WS_USER_DOMAIN_NAME_LEN = 64;      

const WS_U32 WS_NVR_NAME_NUM = 32; 

const WS_U32 WS_NVR_MAX_USR_PASSWD_LEN = 32;

const WS_U32 WS_NVR_MAX_HDISK_NUM = 10;	

const WS_U32 WS_NVR_MAX_HDISK_PART_NUM = 16;

const WS_U32 WS_NVR_MAX_USB_PART_NUM = 4;

const WS_U32 WS_NVR_IPV4_STRING_LEN = sizeof("xxx.xxx.xxx.xxx");

const WS_U32 WS_NVR_IPV6_STRING_LEN = sizeof("xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx");

const WS_U32 WS_NVR_MAC_STRING_LEN = sizeof("xx:xx:xx:xx:xx:xx");

const WS_U32 WS_MAX_EMAIL_RECEIVER_NUM = 4;

const WS_U32 WS_MAX_EMAIL_ADDRESS_LEN = 128;

const WS_U32 WS_MAX_SERVER_NAME_LEN = 128;

const WS_U32 WS_MD_GRID_ROW_NUM = 18;

const WS_U32 WS_MD_GRID_COLUMN_NUM = 44;

const WS_U32 WS_MAX_PTZ_PROTOCOL_NUM = 64;

const WS_U32 WS_MAX_PTZ_BAUDRATE_NUM = 4;

const WS_U32 WS_MAX_PTZ_PRESET_NUM = 256;

const WS_U32 WS_MAX_PTZ_CRUISE_POINT_NUM = 256;

const WS_U32 WS_MAX_FILE_NAME_LEN = 64;

const WS_U32 WS_MAX_MD_RECT_NUM = 5;

const WS_U32 WS_MAX_ALARM_IN_NUM = 16;

const WS_U32 WS_MAX_ALARM_OUT_NUM = 4;

const WS_U32 WS_MAX_NETMASK_LEN = sizeof("255.255.255.255");

const WS_U32 WS_MAX_GETWAY_LEN = sizeof("255.255.255.255");

/*	dns */
const WS_U32 WS_MAX_DNS_LEN = sizeof("255.255.255.255");

const WS_U32 WS_MAX_SSID_LEN = 128;

const WS_U32 WS_MAX_WPA_LEN = 64;

const WS_U32 WS_MAX_WEP_LEN = 26;

const WS_U32 WS_MAX_AP_NUM = 10;

const WS_U32 WS_WLAN_MAX_KEY_LEN = 128;

const WS_S32 RECIVER_MAS_NUM = 4;    

const WS_U32 WS_MAX_DEV_NAME_LENTH = 32;

const WS_U32 WS_MAX_OSD_NAME_LENTH = 32;

const WS_U32 WS_MAX_EMAIL_TITLE_LENTH = 64;

const WS_U32 WS_MAX_EMAIL_ATTACHMENT = 64;

const WS_U32 WS_MAX_EMAIL_BUF_LENTH = 256;

const WS_U32 WS_MAX_AV_CHIP_NUM = 4;

const WS_U32 WS_MAX_PRE_CH_NUM = _MAX_CHANNEL_NUM_;            

const WS_U32 WS_SNAP_POOL_SIZE = 1024*1024;		

const WS_U32 WS_DELETE_FILE_CNT = 16 ;

const WS_U32 WS_SLAVE_ANALOG_CNT = 16 ;                                          // 1 个从片支持的模拟通道个数

const WS_U32 WS_MAX_PTZ_CRUISE_LINE = 4;


typedef enum
{
    WS_MODULE_ID_UNKNOW,

    WS_MODULE_ID_GUI = 0x100,
    WS_MODULE_ID_NET_SERVER,
    WS_MODULE_ID_PROC_TEST,

    WS_MODULE_ID_MODEL = 0x200,
    WS_MODULE_ID_TRIGGER,
    WS_MODULE_ID_RECORD,
    WS_MODULE_ID_PLAYBACK,
    WS_MODULE_ID_BACKUP,
    WS_MODULE_ID_NETWORK,
    WS_MODULE_ID_DST,
    WS_MODULE_ID_UPDATE,
    WS_MODULE_ID_DEV_PROBE,
    WS_MODULE_ID_CFG_MANAGE,
    WS_MODULE_ID_USR_MANAGE,
    WS_MODULE_ID_LOG_MANAGE,
    WS_MODULE_ID_EXTERNAL_DEV,
    WS_MODULE_ID_LIVE,
    WS_MODULE_ID_REMOTE_AGENT,
    WS_MODULE_ID_HTTP_SERVER,
    WS_MODULE_ID_STATUS,

    WS_MODULE_ID_PLATFORM = 0x400,
    WS_MODULE_ID_RECFILE_MANAGE,
    WS_MODULE_ID_RECFILE_RW,
    WS_MODULE_ID_DISK_MANAGE,
    WS_MODULE_ID_UTILITY,
    WS_MODULE_ID_PTZ, 

    WS_MODULE_ID_SQLITE = 0x500,
    WS_MODULE_ID_SQLTASKM = 0x501,
    WS_MODULE_ID_UTL_DEMO = 0x9527,
    WS_MODULE_ID_INVALID = -1,
} ws_module_id;

typedef enum
{
    WS_PURPOSE_UNKNOW = 0,
    WS_PURPOSE_STORE_IPC_INFO = 0x500,

    WS_PURPOSE_READ_PRIVATE_FILE_IDX_NODE = 0x1000, 

    WS_PROBE_REMOTE_DEV_INFO = 0x2201,

    WS_REMOTE_AGENT_LIST =0x2301,
    WS_REMOTE_UPGRADE_IPC = 0x2302,

    WS_PURPOSE_RECF_MANAGE_DATE_NODE = 0x3000,  
    WS_PURPOSE_RECF_MANAGE_PART_NODE = 0x3001, 
    WS_PURPOSE_RECF_MANAGE_INQUIRE = 0x3002,  

    WS_PURPOSE_RECORD_HOLIDAY_NODE = 0x3100,  
    WS_PURPOSE_RECORD_SAVE_PRE_REC = 0x3101,  

    WS_PURPOSE_LOG_BUF_CONTENT = 0x3200, 	 
    WS_PURPOSE_LOG_BUF_INQUIRE_IDX = 0x3201, 	
    WS_PURPOSE_LOG_BUF_INQUIRE_RESULT = 0x3202,  

    WS_PURPOSE_USR_MANAGE = 0x3300,	

    WS_PURPOSE_MODEL_RMT_CONNECT = 0x3400,	

    WS_PURPOSE_GUI_WIND = 0x3500,	
    WS_PURPOSE_GUI_FAC_PIC = 0x3501,	
    WS_PURPOSE_GUI_BACKUP_DOUBLE_FILE_LIST = 0x3502,
    WS_PURPOSE_GUI_COMM_SETTING_GROUP = 0x3503,

    WS_PURPOSE_PLAY_BACK_READ_FILE = 0x3600,	
    WS_PURPOSE_LOGO_READ_FILE = 0x3601,	

    WS_PURPOSE_HTTP_SERVER_CREATE_SENDBUF = 0x3700,

    WS_PURPOSE_NET_SERVER_NEWHIS_DATABUF = 0x3701,

    WS_PURPOSE_BACKUP_LIST_NODE = 0x3750,
    WS_PURPOSE_BACKUP_READ_FRAME = 0x3751,
    WS_PURPOSE_BACKUP_REC_RESULT = 0x3752,
    WS_PURPOSE_BACKUP_SNAP_RESULT = 0x3753,
    WS_AVI_FORMAT_CONVERTER_FILE = 0x3760,	
	
    WS_PURPOSE_DST_MANAGE = 0x3800,   

    WS_PURPOSE_EMAIL_NODE = 0x3900,	
    WS_PURPOSE_DHCP_NODE = 0x4000,		//DHCP

    WS_PURPOSE_SQLITE = 0x9400,

    WS_PURPOSE_SQLTASKM = 0x9401,

    WS_PURPOSE_SQLTASKM_DATE = 0x9402,

    WS_PURPOSE_SQLITE_SAMPLE = 0x9412,
	
    WS_UTILITY_PUSH_EVENT = 0x9526, 
    WS_UTILITY_THREAD_POOL_DIAGNOSE = 0x9527,
    WS_UTILITY_DIAGNOSE_TOOL = 0x9528,	
    WS_UTILITY_TIMER = 0x9529,	
    WS_UTILITY_WATCH_DOG = 0x9530, 

    WS_PURPOSE_REMOTE_CACHE_BUF = 0x9531, 
    WS_PURPOSE_REMOTE_PTZ_CMD_NODE = 0x9532,
    WS_PURPOSE_REMOTE_SNAP_TASK_NODE = 0x9533,

    WS_PURPOSE_PTZ_CMD_NODE = 0x9534,	
    WS_PURPOSE_PTZ_CRUISE_NODE = 0x9535, 
    WS_PURPOSE_REMOTE_TASK_NODE = 0x9536, //add by qqy, at 2016-07-25 20:01:44
    WS_PURPOSE_MODEL_TASK_NODE = 0x9537,  //add by qqy, at 2016-08-17 14:24:24
    WS_PURPOSE_GUI_CHAN_STATUS = 0x9538,  //add by qqy, at 2016-08-19 17:24:24
    
    WS_PURPOSE_PLATFORM_FRAME_STORE = 0x9600,
    WS_PURPOSE_PLATFOMR_STORE_BIT_MAP = 0x9601,
    WS_PURPOSE_TUTK_INQUARY_LOG = 0x9602,	
    WS_PURPOSE_PLATFOMR_MONITOR = 0x9651,
    WS_PURPOSE_GUI_SEARCH_LOG = 0x9652,       
    WS_PURPOSE_RECF_MANAGE_LIST = 0x9653,    
    WS_PURPOSE_PLATFORM_GET_FRAME = 0x9654,	

    WS_PURPOSE_PLATFORM_PCIV_STREAM_CACHE = 0x9658,
    WS_GUI_PLAYBACK_TASK_NODE = 0x9661,

    WS_RECFILE_PART_TASK_NODE = 0x9662,

    WS_PURPOSE_UPDATE_BUF = 0x9700,

    WS_PURPOSE_QR_PIC = 0x9800,

    WS_PURPOSE_RECF_RW_TMP_BUF = 0x9900,

    WS_TUTK_INQUARY_LOG = 0x9999,	
    WS_PURPOSE_PROC_TEST = 0x10000,	

    WS_PURPOSE_DISK_TEST = 0x10001,
    WS_PLAYBACK_SEL_CH_OPS = 0x10002,

    WS_PLAYBACK_INQUIRY_FILE = 0x10003,
    WS_GUI_BAR_ROOL_NODE= 0x10010,  
    WS_PURPOSE_REMOTE_SEND_EMAIL_TASK_NODE=0x10012,  
    WS_PURPOSE_DISK_FMT_NODE = 0x10020, 
    WS_PURPOSE_PLATFORM_SNAP_PIC = 0x10022,	
} ws_memmory_purpose;

typedef enum
{
    WS_PLAT_PURPOSE_UNKNOW = 0,
    WS_PLAT_PURPOSE_RECF_RW_TMP_BUF = 0x100,
    WS_PLAT_PURPOSE_GET_FRAME = 0x200,
    WS_PLAT_PURPOSE_TEST_MAX_PLATFORM_MMZ = 0x9528,
}ws_platform_memmory_purpose;

typedef enum
{
    WS_LANG_SIM_CHINESE = 0,
    WS_LANG_ENGLISH,
    WS_LANG_CUR = -1,
} ws_language_type;

typedef enum 
{
    WS_CRADLE_TYPE_UNKNOWN=0,	
    WS_CRADLE_TYPE_OPINT,		
    WS_CRADLE_TYPE_CRUISE,     
    WS_CRADLE_TYPE_TRA,		
}ws_cradle_cmd_type;


typedef struct
{
    ws_cradle_cmd_type		enCraType;	
    WS_U32					u32Idx;	
} ws_cradle_cmd_info;

typedef struct
{
    WS_U32	              ch_idx;				
    ws_cradle_cmd_info  cmd_info;	
} ws_linkage_cradle_info;

typedef enum
{
    ProtocolBegin = -1,    
    ProtocolHYPrivate,     
    ProtocolTideMobile,    
    ProtocolMegaEyes,     
    ProtocolRTSP,          
    ProtocolONVIF,
    ProtocolHTTP,
    ProtocolDiscovery,
    ProtocolRTMP,         
    ProtocolIPDetection, 
    ProtocolEnd,        
}login_protocol_type;

typedef struct
{
    char username[WS_NVR_MAX_USR_NAME_LEN];
    char userIpAddr[WS_NVR_IPV6_STRING_LEN];
    char userMacAddr[WS_NVR_MAC_STRING_LEN];
    login_protocol_type protocol_type;
    WS_USR_HAND handle;
}ws_user_info;

// change by linhh 20160617 
#define TST_MUL_CH(ch_idx, ch_mask_add)  ( (1<< ((ch_idx) %32)) & (ch_mask_add[(ch_idx)/32])) 	        

#define	MAIN_MAX_BITRATE 	(1000*1000*10)
#define	MAIN_MIN_BITRATE	(1000*1000)
#define	SUB1_MAX_BITRATE	(4000*1000)
#define	SUB1_MIN_BITRATE	(64 * 1000)
#define	SUB2_MAX_BITRATE	(1000*1000)
#define	SUB2_MIN_BITRATE	(30 * 1000)

#ifdef __cplusplus
}//namespace ws_utility 
}//extern "C" {
#endif

#endif  //#ifndef _WS_COMMON_H_


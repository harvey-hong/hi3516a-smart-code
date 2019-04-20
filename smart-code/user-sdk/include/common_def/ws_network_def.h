#ifndef _WS_NETWORK_DEF_H_
#define _WS_NETWORK_DEF_H_

#include "ws_common.h"
#include "ws_comm_sys.h"

/* add by zhangmq 20180527 start*/
//---------------------------------------- 网络配置参数 -------------------------------------
#define WS_CFG_NET_INFO         "Net_Info"              //网络信息
#define WS_CFG_NET_INFO_NVR     "Net_Info_Nvr"          //NVR网络信息
#define WS_CFG_NET_INFO_IPC     "Net_Info_Ipc"          //IPC网络信息

#define WS_CFG_NET_INFO_IP_VERSION  "Ip_Version"        //ip版本

#define WS_CFG_NET_IP_STATUS        "Ip_Status"         //网络连接模式
#define WS_CFG_NET_IP_ADDR      "Ip_Addr"               //ip地址
#define WS_CFG_NET_NETMASK      "Ip_Netmask"            //子网掩码
#define WS_CFG_NET_GETWAY           "Ip_Getway"         //网关
#define WS_CFG_NET_DNS1         "Ip_Dns1"               //首选DNS
#define WS_CFG_NET_DNS2         "Ip_Dns2"               //辅选DNS
#define WS_CFG_NET_INFO_IP_VERSION  "Ip_Version"        //ip版本

#define WS_CFG_NET_PORT_MEDIA       "Port_Media"        //媒体端口
#define WS_CFG_NET_PORT_HTTP        "Port_Http"         //HTTP端口
#define WS_CFG_NET_PORT_CMD     "Port_Cmd"              //信令端口
#define WS_CFG_NET_PORT_MOBILE  "Port_Mobile"           //手机服务监听端口
#define WS_CFG_NET_FTP_PORT     "Port_Ftp"              //FTP端口
#define WS_CFG_NET_RTSP_PORT    "Port_Rtsp"             //RTSP 端口
#define WS_CFG_NET_ALARM_PORT    "Port_Alarm"		//AlarmServer端口

#define WS_CFG_CHA_INFO             "Cha_Info"              //通道信息
#define WS_CFG_CHA_NUM              "Cha_Num"           //通道号
#define WS_CFG_CHA_NAME         "Cha_Name"              //用户名
#define WS_CFG_CHA_PASS         "Cha_Pass"              //密码
#define WS_CFG_CHA_CON_PROTOCOL "Cha_Con_PROTOCOL"//私有协议或者是其他协议
#define WS_CFG_CHA_IP_ADDR          "Cha_Ip_Addr"           //ip地址
#define WS_CFG_CHA_CONNECT_TYPE "Cha_Connect_Type"  //连接类型，手动连接还是自动连接
#define WS_CFG_CHA_CMD_PORT     "Cha_CmdPort"           //信令端口
#define WS_CFG_CHA_MEDIA_PORT       "Cha_MediaPort"     //媒体端口
#define WS_CFG_CHA_HTTP_PORT        "Cha_HttpPort"      //HTTP通信端口
#define WS_CFG_CHA_ENABLE        "Cha_Enable"          //启用或者禁用状态  add by khs 2017.3.23
#define WS_CFG_CHA_VERSION        "Cha_Version"          //版本 add by khs  2017.3.24


//------------------------------------------wifi----------------------------------
#define WS_CFG_WIFI                 "wifi"              //WIFI
#define WS_CFG_WIFI_ENABLE          "wifi_enable"       //wifi是否使能
#define WS_CFG_WIFI_CONNECT_MODE    "wifi_conncet_mode"     //WIFI连接模式
#define WS_CFG_WIFI_IP_ADDRESS      "wifi_ip_address"       //IP地址
#define WS_CFG_WIFI_SUBNET_MASK     "wifi_subnet_mask"      //子网掩码
#define WS_CFG_WIFI_GATEWAY         "wifi_gate_way"         //网关
#define WS_CFG_WIFI_DNS1            "wifi_dns1"             //DNS1
#define WS_CFG_WIFI_DNS2            "wifi_dns2"             //DNS2
#define WS_CFG_WIFI_AP_SSID         "wifi_ap_ssid"          //WIFI热点名
#define WS_CFG_WIFI_AP_MAC         "wifi_ap_mac"            //WIFI mac
#define WS_CFG_WIFI_AUTHENTICATION  "wifi_authentication"   //WIFI认证方式
#define WS_CFG_WIFI_ENCRYPTION      "wifi_encryption"       //WIFI加密算法
#define WS_CFG_WIFI_FORMAT          "wifi_format"           //WIFI网络类型
#define WS_CFG_WIFI_VALUE           "wifi_value"            //密码value
#define WS_CFG_WIFI_NUMBER_VALUE    "wifi_number_value"     //密码序列号
#define WS_CFG_WIFI_PASSWORD        "wifi_password"         //密码项
#define WS_CFG_WIFI_KEY             "wifi_key"              //具体密码参数
#define WS_CFG_WIFI_VALID_KEY       "wifi_valid_key"


//----------------ntp 使能所需-------------------------
#define WS_CFG_NTP_SET              "Ntp_Set"               //NTP
#define WS_CFG_NTP_STATUS           "Ntp_Status"            //NTP使能
#define WS_CFG_TIMEZONE_HOUR        "Ntp_Time_Hour"         //NTP时区时间小时
#define WS_CFG_TIMEZONE_MIN     "Ntp_Time_Min"              //NTP时区时间分钟
#define WS_CFG_NTP_SERVER_1     "Ntp_Server_1"              //NTP服务器1
#define WS_CFG_NTP_SERVER_2     "Ntp_Server_2"              //NTP服务器2

#define WS_CFG_TIME_SET  "Time_Set"                      //时间设置
#define WS_CFG_TIME_TYPE  "Time_Type"                    //时间类型
#define WS_CFG_TIME_STANDARD "Time_Standard"             //时间制式
 
#define WS_CFG_TIME_DST   			"Time_Dst"
#define WS_CFG_TIME_DST_ENABLE 		"Time_Dst_Enable"
#define ws_CFG_TIME_DST_MODEL   	"Time_Dst_Model"
#define WS_CFG_TIME_DST_DIFFERENCE  "Time_Dst_Difference"
#define WS_CFG_TIME_DST_START   	"Time_Dst_Start"
#define WS_CFG_TIME_DST_END         "Time_Dst_End"
#define WS_CFG_TIME_DST_MONTH   	"Time_Dst_Month"
#define WS_CFG_TIME_DST_DAY     	"Time_Dst_Day"
#define WS_CFG_TIME_DST_WDAY_IDX 	"Time_Dst_Wday_Idx"
#define WS_CFG_TIME_DST_WDAY     	"Time_Dst_Wday"
#define WS_CFG_TIME_DST_HOUR     	"Time_Dst_Hour"
#define WS_CFG_TIME_DST_MIN      	"Time_Dst_Min"

//---------------pppoe 使能所需--------------------------
#define WS_CFG_PPPOE_SET                "Pppoe_Set"         //PPPoE
#define WS_CFG_PPPOE_ENABLE         "Pppoe_Status"          //PPPoE使能
#define WS_CFG_PPPOE_USRNAME            "Pppoe_Name"        //PPPoE用户名
#define WS_CFG_PPPOE_PASSWORD           "Pppoe_Pass"        //PPPoE密码
#define WS_CFG_PPPOE_STATUS             "Pppoe_Status"      //连接状态
#define WS_CFG_PPPOE_IP                 "Pppoe_Ip"         //PPPoE IP      
#define WS_CFG_PPPOE_GATEWAY            "Pppoe_gateway"     //PPPoE gateway  

//---------------私有域名 使能所需--------------------------
#define WS_CFG_PRI_DNS                  "Pri_Dns_Set"       //DDNS
#define WS_CFG_PDNS_ENABLE          "Pri_Dns_Status"        //DDNS使能
#define WS_CFG_PDNS_USER_DOMAIN     "Pri_Dns_User_Domain"   //DDNS用户域名
#define WS_CFG_PDNS_SER_DOMAIN      "Pri_Dns_Ser_Domain"    //可能是接收方域名吧  完全没注释 看不懂 猜的
#define WS_CFG_PDNS_PORT                "Pri_Dns_Port"      //DDNS端口?  不知道什么东西
#define WS_CFG_PDNS_TIMEVAL         "Pri_Dns_TimeVal"       

//-----------------smtp 使能所需----------------------------
#define WS_CFG_SMTP                 "Smtp_Set"              //smtp
#define WS_CFG_SMTP_ENABLE          "Smtp_Enable"           //SMTP使能
#define WS_CFG_SMTP_SSL_ENABLE          "Smtp_Ssl_Enable"           //SMTP使能
#define WS_CFG_SMTP_PORT                "Smtp_Port"         //smtp端口
#define WS_CFG_SMTP_SERVER          "Smtp_Server"           //SMTP服务器地址
#define WS_CFG_SMTP_SEND_NAME           "Smtp_Sender_Name"  //SMTP发送方名称
#define WS_CFG_SMTP_SEND_PASS           "Smtp_Sender_Pass"  //SNTO发送方密码
#define WS_CFG_SMTP_SEND_PASS_NEW           "Smtp_Sender_Pass_New"          
#define WS_CFG_SMTP_RECIVER_NAME        "Smtp_Reciver_Name" //SMTP接收地址
#define WS_CFG_SMTP_RECIVER_COUNT   "Smtp_Reciver_Count"    //SMTP接收地址数目(小于等于4)

//----------------时区 -------------------------------------
#define WS_CFG_TIME                 "time"                  //时间
#define WS_CFG_TIME_ZONE                    "zone"          //时区
#define WS_CFG_DST_ENABLE           "dst_enable"            //是否使能DST

//----------------ipc同步时间----------------------------------------------------
#define WS_CFG_SYNC_IPC_TIME        "SYNC_IPC_TIME"
/* add by zhangmq 20180527 end*/

using namespace ws_utility;

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

#define DEFAULT_DEVICE "eth0"
#define ETH_NAME    "eth0"

#define ETH_HW_ADDR_LEN 6
#define IP_ADDR_LEN 4
#define ARP_FRAME_TYPE 0x0806
#define ETHER_HW_TYPE 0x1
#define IP_PROTO_TYPE 0x0800

#define OP_ARP_REQUEST 2
#define OP_ARP_QUEST 1

struct arp_packet
{
    //eth head
    WS_UCHAR targ_hw_addr[ETH_HW_ADDR_LEN];//all 0xff broadcast
    WS_UCHAR src_hw_addr[ETH_HW_ADDR_LEN];//local mac
    WS_U16 frame_type;

    //arp head
    WS_U16 hw_type;
    WS_U16 prot_type;
    WS_UCHAR hw_addr_size;
    WS_UCHAR prot_addr_size;

    WS_U16 op;//operation
    WS_UCHAR sndr_hw_addr[ETH_HW_ADDR_LEN];//no mean
    WS_UCHAR sndr_ip_addr[IP_ADDR_LEN];//sender
    WS_UCHAR rcpt_hw_addr[ETH_HW_ADDR_LEN];//target
    WS_UCHAR rcpt_ip_addr[IP_ADDR_LEN];//target
    WS_UCHAR padding[6]; /* zhangzl 20140809 DVR-IPC IP conflict need 2 bytes padding start end */
    WS_U32  stime;
} __attribute__((packed));

struct use_ip
{
    int flag;
};

typedef struct
{
    WS_BOOL is_auto;
    char new_ip[ws_utility::WS_NVR_IPV4_STRING_LEN];
    WS_BOOL is_dhcp;
    WS_BOOL is_ip_conflict;
} ip_state;

//本地连接配置
typedef struct
{
    WS_BOOL auto_get_ip;

    WS_CHAR ip[ws_utility::WS_NVR_IPV4_STRING_LEN];             // 静态IP地址
    WS_CHAR sub_mask[ws_utility::WS_MAX_NETMASK_LEN];       // 子网掩码
    WS_CHAR gate_way[ws_utility::WS_MAX_GETWAY_LEN];        // 网关

    WS_CHAR dns1[ws_utility::WS_MAX_DNS_LEN];               // 主DNS
    WS_CHAR dns2[ws_utility::WS_MAX_DNS_LEN];               // 次DNS
    WS_CHAR ip_version[16];                     //IP版本
} ws_local_connect_cfg;

typedef struct
{
    WS_BOOL auto_get_ip;

    WS_CHAR ip[ws_utility::WS_NVR_IPV4_STRING_LEN];         // 静态IP地址
    WS_CHAR sub_mask[ws_utility::WS_MAX_NETMASK_LEN];       // 子网掩码
    WS_CHAR gate_way[ws_utility::WS_MAX_GETWAY_LEN];        // 网关
} ws_wlan_connect_cfg;

typedef struct
{
    WS_S32  http_port;               // WEB服务器监听端口(默认80)
    WS_S32  cmd_port;                // 网络服务信令监听端口
    WS_S32  data_port;               // 网络服务媒体数据监听端口
    WS_S32  mobile_port;             // 手机服务监听端口
    WS_S32  ftp_port;
    WS_S32  rtsp_port;  //RTSP 端口 added by dzh
    WS_S32  alarm_port;	//alarmserver port added by Liujl 20160922
} ws_net_port_cfg;

//pppoe配置
typedef struct
{
    WS_BOOL enable;             // 是否启动PPPOE拔号
    WS_CHAR user_name[ws_utility::WS_NVR_MAX_USR_NAME_LEN + 1];     // 用户名
    WS_CHAR password[ws_utility::WS_NVR_MAX_USR_PASSWD_LEN + 1];    // 密码
} ws_pppoe_config;

// PPPOE连接信息
typedef struct
{
    WS_BOOL connect_ok;             // 是否连接上
    char ip[ws_utility::WS_NVR_IPV4_STRING_LEN];
    char geteway[ws_utility::WS_MAX_GETWAY_LEN];
} ws_pppoe_state;

typedef enum
{
    pppoe_UNKNOW=0,
    PPPOE_NOT_CONNECT,
    PPPOE_CONNECT_OK,
    PPPOE_IS_CONNECT,
}show_pppoe_state;

typedef struct
{
    show_pppoe_state connect_ok;
    char ip[ws_utility::WS_NVR_IPV4_STRING_LEN];
    char geteway[ws_utility::WS_MAX_GETWAY_LEN];
}show_pppoe_status;

typedef enum{
	UNKNOW=0,
	PPPOE_DIS_CONNECT,
	PPPOE_ON_CONNECT,
	PPPOE_CONNECT_SUCCESS,
	PPPOE_CONNECT_FAIL,
	PHASE1,
	PHASE2,
	PHASE3,
	PHASE4,
}pppoe_connect_state;

typedef enum
{
    WS_NET_NOT_LINK = 0,
    WS_NET_LINK,

    WS_NET_LINK_UNKNOW = 0xff,
} ws_net_link_state;

typedef enum
{
    GIFADDR = 0,
    GIFBRDADDR,
    GIFNETMASK,
    GIFHWADDR,



    GIFUNKNOW = 100,
} net_info_get;

/* connect_status deleted by yxl 2014.10.09 */

typedef enum
{
    WS_EMAIL_TLS,
    WS_EMAIL_SSL,
} ws_email_protocol;

//邮件配置
typedef struct
{
    WS_BOOL enable;         // 是否支持邮件功能

    WS_BOOL ssl_enable;     // TLS/SSL
    WS_S32  port;           // 邮件服务器端口
    WS_CHAR server[ws_utility::WS_MAX_SERVER_NAME_LEN + 1];     // 服务器地址
    WS_CHAR user_name[ws_utility::WS_NVR_MAX_ADDR_LEN + 1]; // 发送邮箱用户名
    WS_CHAR pass_word[ws_utility::WS_NVR_MAX_USR_PASSWD_LEN + 1];   // 发送邮箱密码

    WS_BOOL need_snap;      // 是否要求有截图作为附件发送告警邮件
} ws_email_sender_cfg;

typedef struct
{
    char addr[ws_utility::WS_NVR_MAX_ADDR_LEN + 1];
} ws_reciver_add;

typedef struct
{
    ws_reciver_add addr[ws_utility::RECIVER_MAS_NUM];
} ws_reciver_all;

typedef struct
{
    char filename[ws_utility::WS_MAX_EMAIL_ATTACHMENT][ws_utility::WS_MAX_FILE_NAME_LEN];
    int total_num;
} ws_email_attachment;  //邮件附件包  最多支持1此发送64个附件


//ntp添加修改
typedef struct
{
    WS_BOOL enable;                         // enable or disable internet time sync.(0,1)
    WS_S32 timezone_hour;                   // timezone(-12~13)
    WS_S32 timezone_min;                    // minute (0-59)

    // 12.10.191.251 windows对时ip地址
    WS_CHAR server1[ws_utility::WS_NTP_SERVER_NAME_LEN + 1];                   // timer server(域名或IP地址均可)  
    WS_CHAR server2[ws_utility::WS_NTP_SERVER_NAME_LEN + 1];                   // timer server(域名或IP地址均可)  
    WS_S32 resevered[64];                   // 保留字段
} ws_ntpc_config;

typedef enum
{
    YYYY_MM_DD,
    YYYY_MM_DD_W,
    MM_DD_YYYY,
    MM_DD_YYYY_W,
}ws_gui_show_time_type;


typedef enum
{
    TWELVE_STANDARD,
    TWENTY_FOUR_STANDARD,
}ws_gui_time_standard;

typedef struct
{
	ws_gui_show_time_type    show_time_type;
	ws_gui_time_standard     time_standard;
}ws_time_type_and_standard;

typedef struct
{
    WS_BOOL enable;
    WS_CHAR user_domain[65]; 
    WS_CHAR ser_domain[64];

    WS_U32 port;
    WS_U32 time_val;
    WS_CHAR using_domain[65];				/* 正在使用中的域名以方便UI显示 */
} ws_pri_dns_config;

typedef void (*set_sys_new_time)(const ws_utility::ws_time_struct *time);

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_MODEL_DEF_H_



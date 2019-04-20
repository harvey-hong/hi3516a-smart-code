#ifndef _WS_NETWORK_DEF_H_
#define _WS_NETWORK_DEF_H_

#include "ws_common.h"
#include "ws_comm_sys.h"

/* add by zhangmq 20180527 start*/
//---------------------------------------- �������ò��� -------------------------------------
#define WS_CFG_NET_INFO         "Net_Info"              //������Ϣ
#define WS_CFG_NET_INFO_NVR     "Net_Info_Nvr"          //NVR������Ϣ
#define WS_CFG_NET_INFO_IPC     "Net_Info_Ipc"          //IPC������Ϣ

#define WS_CFG_NET_INFO_IP_VERSION  "Ip_Version"        //ip�汾

#define WS_CFG_NET_IP_STATUS        "Ip_Status"         //��������ģʽ
#define WS_CFG_NET_IP_ADDR      "Ip_Addr"               //ip��ַ
#define WS_CFG_NET_NETMASK      "Ip_Netmask"            //��������
#define WS_CFG_NET_GETWAY           "Ip_Getway"         //����
#define WS_CFG_NET_DNS1         "Ip_Dns1"               //��ѡDNS
#define WS_CFG_NET_DNS2         "Ip_Dns2"               //��ѡDNS
#define WS_CFG_NET_INFO_IP_VERSION  "Ip_Version"        //ip�汾

#define WS_CFG_NET_PORT_MEDIA       "Port_Media"        //ý��˿�
#define WS_CFG_NET_PORT_HTTP        "Port_Http"         //HTTP�˿�
#define WS_CFG_NET_PORT_CMD     "Port_Cmd"              //����˿�
#define WS_CFG_NET_PORT_MOBILE  "Port_Mobile"           //�ֻ���������˿�
#define WS_CFG_NET_FTP_PORT     "Port_Ftp"              //FTP�˿�
#define WS_CFG_NET_RTSP_PORT    "Port_Rtsp"             //RTSP �˿�
#define WS_CFG_NET_ALARM_PORT    "Port_Alarm"		//AlarmServer�˿�

#define WS_CFG_CHA_INFO             "Cha_Info"              //ͨ����Ϣ
#define WS_CFG_CHA_NUM              "Cha_Num"           //ͨ����
#define WS_CFG_CHA_NAME         "Cha_Name"              //�û���
#define WS_CFG_CHA_PASS         "Cha_Pass"              //����
#define WS_CFG_CHA_CON_PROTOCOL "Cha_Con_PROTOCOL"//˽��Э�����������Э��
#define WS_CFG_CHA_IP_ADDR          "Cha_Ip_Addr"           //ip��ַ
#define WS_CFG_CHA_CONNECT_TYPE "Cha_Connect_Type"  //�������ͣ��ֶ����ӻ����Զ�����
#define WS_CFG_CHA_CMD_PORT     "Cha_CmdPort"           //����˿�
#define WS_CFG_CHA_MEDIA_PORT       "Cha_MediaPort"     //ý��˿�
#define WS_CFG_CHA_HTTP_PORT        "Cha_HttpPort"      //HTTPͨ�Ŷ˿�
#define WS_CFG_CHA_ENABLE        "Cha_Enable"          //���û��߽���״̬  add by khs 2017.3.23
#define WS_CFG_CHA_VERSION        "Cha_Version"          //�汾 add by khs  2017.3.24


//------------------------------------------wifi----------------------------------
#define WS_CFG_WIFI                 "wifi"              //WIFI
#define WS_CFG_WIFI_ENABLE          "wifi_enable"       //wifi�Ƿ�ʹ��
#define WS_CFG_WIFI_CONNECT_MODE    "wifi_conncet_mode"     //WIFI����ģʽ
#define WS_CFG_WIFI_IP_ADDRESS      "wifi_ip_address"       //IP��ַ
#define WS_CFG_WIFI_SUBNET_MASK     "wifi_subnet_mask"      //��������
#define WS_CFG_WIFI_GATEWAY         "wifi_gate_way"         //����
#define WS_CFG_WIFI_DNS1            "wifi_dns1"             //DNS1
#define WS_CFG_WIFI_DNS2            "wifi_dns2"             //DNS2
#define WS_CFG_WIFI_AP_SSID         "wifi_ap_ssid"          //WIFI�ȵ���
#define WS_CFG_WIFI_AP_MAC         "wifi_ap_mac"            //WIFI mac
#define WS_CFG_WIFI_AUTHENTICATION  "wifi_authentication"   //WIFI��֤��ʽ
#define WS_CFG_WIFI_ENCRYPTION      "wifi_encryption"       //WIFI�����㷨
#define WS_CFG_WIFI_FORMAT          "wifi_format"           //WIFI��������
#define WS_CFG_WIFI_VALUE           "wifi_value"            //����value
#define WS_CFG_WIFI_NUMBER_VALUE    "wifi_number_value"     //�������к�
#define WS_CFG_WIFI_PASSWORD        "wifi_password"         //������
#define WS_CFG_WIFI_KEY             "wifi_key"              //�����������
#define WS_CFG_WIFI_VALID_KEY       "wifi_valid_key"


//----------------ntp ʹ������-------------------------
#define WS_CFG_NTP_SET              "Ntp_Set"               //NTP
#define WS_CFG_NTP_STATUS           "Ntp_Status"            //NTPʹ��
#define WS_CFG_TIMEZONE_HOUR        "Ntp_Time_Hour"         //NTPʱ��ʱ��Сʱ
#define WS_CFG_TIMEZONE_MIN     "Ntp_Time_Min"              //NTPʱ��ʱ�����
#define WS_CFG_NTP_SERVER_1     "Ntp_Server_1"              //NTP������1
#define WS_CFG_NTP_SERVER_2     "Ntp_Server_2"              //NTP������2

#define WS_CFG_TIME_SET  "Time_Set"                      //ʱ������
#define WS_CFG_TIME_TYPE  "Time_Type"                    //ʱ������
#define WS_CFG_TIME_STANDARD "Time_Standard"             //ʱ����ʽ
 
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

//---------------pppoe ʹ������--------------------------
#define WS_CFG_PPPOE_SET                "Pppoe_Set"         //PPPoE
#define WS_CFG_PPPOE_ENABLE         "Pppoe_Status"          //PPPoEʹ��
#define WS_CFG_PPPOE_USRNAME            "Pppoe_Name"        //PPPoE�û���
#define WS_CFG_PPPOE_PASSWORD           "Pppoe_Pass"        //PPPoE����
#define WS_CFG_PPPOE_STATUS             "Pppoe_Status"      //����״̬
#define WS_CFG_PPPOE_IP                 "Pppoe_Ip"         //PPPoE IP      
#define WS_CFG_PPPOE_GATEWAY            "Pppoe_gateway"     //PPPoE gateway  

//---------------˽������ ʹ������--------------------------
#define WS_CFG_PRI_DNS                  "Pri_Dns_Set"       //DDNS
#define WS_CFG_PDNS_ENABLE          "Pri_Dns_Status"        //DDNSʹ��
#define WS_CFG_PDNS_USER_DOMAIN     "Pri_Dns_User_Domain"   //DDNS�û�����
#define WS_CFG_PDNS_SER_DOMAIN      "Pri_Dns_Ser_Domain"    //�����ǽ��շ�������  ��ȫûע�� ������ �µ�
#define WS_CFG_PDNS_PORT                "Pri_Dns_Port"      //DDNS�˿�?  ��֪��ʲô����
#define WS_CFG_PDNS_TIMEVAL         "Pri_Dns_TimeVal"       

//-----------------smtp ʹ������----------------------------
#define WS_CFG_SMTP                 "Smtp_Set"              //smtp
#define WS_CFG_SMTP_ENABLE          "Smtp_Enable"           //SMTPʹ��
#define WS_CFG_SMTP_SSL_ENABLE          "Smtp_Ssl_Enable"           //SMTPʹ��
#define WS_CFG_SMTP_PORT                "Smtp_Port"         //smtp�˿�
#define WS_CFG_SMTP_SERVER          "Smtp_Server"           //SMTP��������ַ
#define WS_CFG_SMTP_SEND_NAME           "Smtp_Sender_Name"  //SMTP���ͷ�����
#define WS_CFG_SMTP_SEND_PASS           "Smtp_Sender_Pass"  //SNTO���ͷ�����
#define WS_CFG_SMTP_SEND_PASS_NEW           "Smtp_Sender_Pass_New"          
#define WS_CFG_SMTP_RECIVER_NAME        "Smtp_Reciver_Name" //SMTP���յ�ַ
#define WS_CFG_SMTP_RECIVER_COUNT   "Smtp_Reciver_Count"    //SMTP���յ�ַ��Ŀ(С�ڵ���4)

//----------------ʱ�� -------------------------------------
#define WS_CFG_TIME                 "time"                  //ʱ��
#define WS_CFG_TIME_ZONE                    "zone"          //ʱ��
#define WS_CFG_DST_ENABLE           "dst_enable"            //�Ƿ�ʹ��DST

//----------------ipcͬ��ʱ��----------------------------------------------------
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

//������������
typedef struct
{
    WS_BOOL auto_get_ip;

    WS_CHAR ip[ws_utility::WS_NVR_IPV4_STRING_LEN];             // ��̬IP��ַ
    WS_CHAR sub_mask[ws_utility::WS_MAX_NETMASK_LEN];       // ��������
    WS_CHAR gate_way[ws_utility::WS_MAX_GETWAY_LEN];        // ����

    WS_CHAR dns1[ws_utility::WS_MAX_DNS_LEN];               // ��DNS
    WS_CHAR dns2[ws_utility::WS_MAX_DNS_LEN];               // ��DNS
    WS_CHAR ip_version[16];                     //IP�汾
} ws_local_connect_cfg;

typedef struct
{
    WS_BOOL auto_get_ip;

    WS_CHAR ip[ws_utility::WS_NVR_IPV4_STRING_LEN];         // ��̬IP��ַ
    WS_CHAR sub_mask[ws_utility::WS_MAX_NETMASK_LEN];       // ��������
    WS_CHAR gate_way[ws_utility::WS_MAX_GETWAY_LEN];        // ����
} ws_wlan_connect_cfg;

typedef struct
{
    WS_S32  http_port;               // WEB�����������˿�(Ĭ��80)
    WS_S32  cmd_port;                // ���������������˿�
    WS_S32  data_port;               // �������ý�����ݼ����˿�
    WS_S32  mobile_port;             // �ֻ���������˿�
    WS_S32  ftp_port;
    WS_S32  rtsp_port;  //RTSP �˿� added by dzh
    WS_S32  alarm_port;	//alarmserver port added by Liujl 20160922
} ws_net_port_cfg;

//pppoe����
typedef struct
{
    WS_BOOL enable;             // �Ƿ�����PPPOE�κ�
    WS_CHAR user_name[ws_utility::WS_NVR_MAX_USR_NAME_LEN + 1];     // �û���
    WS_CHAR password[ws_utility::WS_NVR_MAX_USR_PASSWD_LEN + 1];    // ����
} ws_pppoe_config;

// PPPOE������Ϣ
typedef struct
{
    WS_BOOL connect_ok;             // �Ƿ�������
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

//�ʼ�����
typedef struct
{
    WS_BOOL enable;         // �Ƿ�֧���ʼ�����

    WS_BOOL ssl_enable;     // TLS/SSL
    WS_S32  port;           // �ʼ��������˿�
    WS_CHAR server[ws_utility::WS_MAX_SERVER_NAME_LEN + 1];     // ��������ַ
    WS_CHAR user_name[ws_utility::WS_NVR_MAX_ADDR_LEN + 1]; // ���������û���
    WS_CHAR pass_word[ws_utility::WS_NVR_MAX_USR_PASSWD_LEN + 1];   // ������������

    WS_BOOL need_snap;      // �Ƿ�Ҫ���н�ͼ��Ϊ�������͸澯�ʼ�
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
} ws_email_attachment;  //�ʼ�������  ���֧��1�˷���64������


//ntp����޸�
typedef struct
{
    WS_BOOL enable;                         // enable or disable internet time sync.(0,1)
    WS_S32 timezone_hour;                   // timezone(-12~13)
    WS_S32 timezone_min;                    // minute (0-59)

    // 12.10.191.251 windows��ʱip��ַ
    WS_CHAR server1[ws_utility::WS_NTP_SERVER_NAME_LEN + 1];                   // timer server(������IP��ַ����)  
    WS_CHAR server2[ws_utility::WS_NTP_SERVER_NAME_LEN + 1];                   // timer server(������IP��ַ����)  
    WS_S32 resevered[64];                   // �����ֶ�
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
    WS_CHAR using_domain[65];				/* ����ʹ���е������Է���UI��ʾ */
} ws_pri_dns_config;

typedef void (*set_sys_new_time)(const ws_utility::ws_time_struct *time);

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_MODEL_DEF_H_



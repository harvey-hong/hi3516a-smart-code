#ifndef _TECOM_BASE_H_
#define _TECOM_BASE_H_

#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include<string.h>
#include<net/if.h>
#include<signal.h>
#include<sys/time.h>
#include<iostream>

#include "p2p_struct.h"

#include "ws_comm_av.h"
#include "ws_comm_data.h"


#include "ws_remote_agent_def.h"
#include "ws_wifi_def.h"
#include "ws_record_def.h"
#include "HieServer_Common.h"

/* ͳһ����ģ�����Ͷ��� ��HieServer_Cfg.h �� ws_status_def.h ��*/
#include "HieServer_Cfg.h"

using namespace ws_soft;
#define DEBUG_UNIT_TESTING

#ifdef __cplusplus
extern "C" {
#endif


//#define USE_OPENSSL 0			//2016-12-15 ronghl
#define REGISTER_DOMAIN     "ipcpddns.com"
#define REGISTER_SERVER_IP  "0.0.0.0"
#define REGISTER_SERVER_PORT            52003
 
#define     P2P_SERVER_CMD_PORT         52005
#define     P2P_SERVER_DATA_PORT        8050
#define     P2P_SERVER_CONFIG_UP_PORT  53000
#define     P2P_SERVER_CONFIG_DOWN_PORT  53001

#define     STREAM_SERVER_CMD_PORT      52007
#define     STREAM_SERVER_DATA_PORT     52008                           /* ���ѷ��������ϴ� */
#define     STREAM_SERVER_DATA_DOWN_PORT     52009                     /* ���ѷ����������� : ֻ��Ϊ�˴����ֲܷ����� */

#define SERVER_UUID_CONFIG_PATH "/usr/local/src/server.ini"
#define SERVER_BAND_INFO_PATH	"/usr/local/src/band.ini"
#define PUBLIC_KEY_CONFIG_PATH "/usr/local/src/public.key"
#define PRIVATE_KEY_CONFIG_PATH "/usr/local/src/private.key"
#define MAX_KEY_LEN 	(1024)		//֧��������Կ����
#define ABSTRACT_LEN	(32)		//����ժҪ�Ĵ�С

#define P2P_REBUILD_PORT 	(53001)
#define REG_REBUILD_PORT	(53000)
 
#define RELAY_SESSION_INIT_TIMEOUT    (10)   //�Ự���������յ�����Client Device�ĵ�һ��Relay�Ự���ĳ�ʱ���10��...
#define RELAY_TIMEOUT_INTERVAL            (10)   //Relay�Ự��,Client Device ���Եİ������ʱ10��...�κ�һ����ʱ��,ֱ����������Relay�Ự��ʱʧ��..

#define P2P_SESSION_TIMEOUT_INTERVAL (10) //P2P�������ϴ���P2P�Ự�󵽻Ự���ӳɹ��ĳ�ʱʱ��10��,
                                                                                  //P2P��������׼������Relay�Ự��ʼ,Relay�Ựÿһ���ļ����ʱ����10��.
#define MESSAGE_FORWARD_TIMEOUT_INTERVAL	(60 * 60) /// P2P�ȴ��ļ��ϴ�������ʱʱ��1Сʱ...

#define STREAM_SERVER_FILE_RECEIVE_TIMEOUT    (3600)        ///��ý��������Ͻ���Client�ϴ��ļ���1Сʱ��ʱʱ��...
#define STREAM_SERVER_FILE_CACHE_TIMEOUT       (48 * 3600) /// ��ý��������ϱ�����Ҫת�����ļ���48Сʱ��ʱʱ��...

#define CLIENT_2_P2P_HB_INTERVAL 	        (20)       //Client��P2P������֮���������20��..
#define DEVICE_2_P2P_HB_INTERVAL 	         (20)      //Device��P2P������֮���������20��..
#define DEVICE_2_P2P_HB_INTERVAL_MS 	(20000)  //Device��P2P������֮���������20��..

#define DEVICE_2_CLIENT_HB_INTERVAL_MS 	(500)  //Client ��Device֮��P2P�򶴽׶ΰ����������0.5��..
#define CLIENT_2_DEVICE_HB_KEEP_INTERVAL  (10)  //Client ��Device֮���ά�ֶ����������20��..
#define DEVICE_2_REGISTER_HB_INTERVAL_MS 	(20000)   //��Device   ��Register������֮���������20��..

#define DEVICE_2_REGISTER_HB_INTERVAL 	(20)   //��Device   ��Register������֮���������20��..
#define ALARM_2_REGISTER_HB_INTERVAL 	(15)   //Alarm Server��Register������֮���������15��..             
#define P2P_2_REGISTER_HB_INTERVAL 	        (15)   //P2P Server    ��Register������֮���������15��..       
#define STREAM_2_REGISTER_HB_INTERVAL    (15)   //Stream Server��Register������֮���������15��..           
#define REGISTER_CHECK_HB_TIMEOUT             (60)   //Register�������������4��������ʱ��ʱ��,3���������ʱ��.
#define REGISTER_CHECK_SERVER_HB_TIMEOUT             (45)   //Register��������������֮��������ʱ��ʱ��,3���������ʱ��.  

#define REGISTET_SERVER_REST_PASSWS_TIMEOUT (60)        //ע������� �һ�����RPC �ص���ʱʱ�� 1����

#define ONE_XML_PACKET_SIZE    1390
#define ONE_XML_PACKET_SIZE_SLICE    1000
#define DATA_SIZE_IN_ONE_XML_PACKET   1200
#define FRIEND_REMARK_LEN 256
// Command Token Defination
#define KKKK

/*
  Client�ĵ�¼�û����������ַ�������Ŀ�������󳤶ȶ���32�ֽڣ��ṹ�嶨��Ϊ 32 + 1�ֽڣ�
  Client�ı�ע�������32�ֽڣ��ṹ�嶨��32 + 1�ֽڣ�
  UID�ַ����ṹ�嶨�嶼��48�ֽڣ�ʵ�ʻ��ò�����ô����
  �����ַ��������󳤶� 128 �ֽڣ��ṹ�嶨�� 128 + 1�ֽڣ�

  Device�ĵ�¼�������룬���豸�ϵĶ���Ϊ׼�������������31�ֽڣ��ṹ�嶨�� 32 �ֽڣ�
  �豸���ƣ����豸�ϵĶ���Ϊ׼��ͨ������ʵ�ʿ��������32�ֽڣ��ṹ�嶨�� 32 + 1�ֽڣ�

  �豸��ע���ƣ�ͨ����ע������������32�ֽڣ��ṹ�嶨��32 + 1�ֽ�

*/

#define MAX_PACKET_SIZE 2048

//#define USER_NAME_LEN   (32+1)
//#define UID_LEN                 (48)
#define USER_NAME_LEN   (64+1)
#define UID_LEN   (64+1)
#define PASSWORD_LEN    (64 + 1)
#define DEVICE_PASSWORD_LEN    (32 + 1)

#define IP_STR_LEN           (16)
#define FILE_NAME_LEN    (128+1)
#define MACADDR_LEN      (64 + 1)

//#define PASSWORD_LEN    (32 + 1)
#define EMAIL_ADDR_LEN  (128 + 1)
#define DEVICE_NAME_LEN   (32+ 1)
#define CHANNLE_NAME_LEN (32+ 1)
#define WS_MAX_SSID_LEN   (128)
#define WS_WLAN_MAX_KEY_LEN (128)

#define KEY_LEN                     (16 + 1)
#define ENC_PASSWD_LEN      (32*2 +1)
#define ENC_USERNAME_LEN    (32*2 +1)
#define TRAN_PASSWD_LEN     (32*2 +8 +1)
#define TRAN_USERNAME_LEN     (32*2 +8 +1)

#define CLIENT_APP_ONLINE (0x0001)
#define CLIENT_POWER_ONLINE         (0x0002)
#define CLIENT_OFFLINE      (0x0003)


#define SESSION_RECIEVING   (0x0001)
#define SESSION_SENDING     (0x0002)
#define SESSION_CLOSED      (0x0003)
#define SESSION_RECIEVED    (0x0004)

#define RELAY_CREATED           (0x0001)
#define RELAY_HALF_CONNECTED    (0x0002)
#define RELAY_CONNECTED         (0x0003)
#define RELAY_FAILED            (0x0004)
#define RELAY_CLOSED            (0x0005)


#define OPT_RESULT_SUCCESS 			(0x0000)
#define OPT_RESULT_NAME_PWD_ERR		(0x0001)
#define OPT_RESULT_TIMEOUT			(0x0002)
#define OPT_RESULT_NOT_ONLINE		(0x0003)

#define DEVICE_STATUS_OFFLINE	(0x0000)
#define DEVICE_STATUS_ONLINE 	(0x0001)


/*����������״̬�궨��*/
#define SERVER_STATUS_OFFLINE	(0x0000)
#define SERVER_STATUS_ONLINE	(0x0001)

/*1003�������벻����״̬����*/
#define FILE_UNCOMPLETE			(0x0000)
#define FILE_COMPLETE 			(0x0001)

/******************/
//  Error code definition
/******************/
#define WS_P2P_SUCCESS                                                  (0x00000000)    //����ɹ�..

#define WS_P2P_NO_P2P_AVAILABLE                                 (0xC0000001)    //�޿��õ�P2P Server
#define WS_P2P_CLIENT_NAME_ONLINE_CONFLICT     		(0xC0000002)    //ͬһ���û����ѵ�¼..
#define WS_P2P_CLIENT_NAME_FORMAT_ERROR             (0xC0000003)    //�û�����ʽ����ȷ..
#define WS_P2P_CLIENT_NAME_EXIST_ERROR              (0xC0000004)    //�û����Ѿ���ע��..
#define WS_P2P_CLIENT_NAME_NOT_EXIST_ERROR       	(0xC0000005)    //�û���������...
#define WS_P2P_CLIENT_EMAIL_EXIST_ERROR             (0xC0000006)    //�û������Ѿ���ע��..
#define WS_P2P_CLIENT_EMAIL_FORMAT_ERROR            (0xC0000007)    //�û������ʽ����ȷ...
#define WS_P2P_CLIENT_EMAIL_NOT_MATCH_ERROR			(0xC0000008)	//����ע���������û�����ƥ��
#define WS_P2P_CLIENT_PASSWORD_ERROR				(0xC0000009)	//�û���¼�������
#define WS_P2P_CLIENT_NOT_ONLINE_ERROR				(0xC000000a)	//�û�δ��¼
#define WS_P2P_CLIENT_LOGIN_MODE_ERROR				(0xC000000b)	//�û���¼ģʽ�쳣
#define WS_P2P_CLIENT_PHONE_UUID_ERROR				(0xC000000c)	//�ն˵�¼����
#define WS_P2P_DEVICE_NOT_ONLINE_ERROR				(0xC000000d)	//�豸������
#define WS_P2P_CLIENT_USER_PASSWORD_NOT_MATCH_ERROR	(0xC000000e)	//�豸�û������벻ƥ��
#define WS_P2P_DEVICE_ADDED_TWICE_ERROR				(0xC000000f)	//�豸�������ظ����
#define WS_P2P_DEVICE_ALREADY_ADDED_ERROR			(0xC0000010)	//�豸����˽����
#define WS_P2P_CLIENT_NOT_PRIVATE_DEVICE_ERROR		(0xC0000011)	//�豸���û�֮�䲻����˽���߹�ϵ
#define WS_P2P_PROCESS_TIMEOUT_ERROR				(0xC0000012)	//��ǰ������ʱ,����������RPC���ֳ�ʱ,���ظ��ն˵Ĵ���.
#define WS_P2P_NOT_SHARE_RELATION_ERROR				(0xC0000013)	//�豸ͨ�����û�֮�䲻���ڷ���򱻷���Ĺ�ϵ
#define WS_P2P_P2PSER_STILL_ALIVE__ERROR			(0xC0000014)	//����P2P����������ԭP2P������������
#define WS_P2P_DEVICE_CLIENT_NO_RELATION_ERROR        (0xC0000015)	//�豸���û����κι�ϵ
#define WS_P2P_CHANNEL_NOT_EXIST_ERROR				(0xC0000016)	//ͨ��������
#define WS_P2P_P2P_OR_RELAY_SESSION_ERROR			(0xC0000017)   	//P2P����Relay�ỰID����
#define WS_P2P_CLIENT_NEED_RELOGIN			             (0xC0000018)   	//�Ѿ�ǿ���û�ǰ�ε�¼�˳�����Ҫ���µ�¼
#define WS_P2P_CLIENT_FRIEND_EXIST                                  (0xC0000019)        // ���ѹ�ϵ�Ѿ�����
#define WS_P2P_CLIENT_FRIEND_NOT_EXIST                          (0xC000001a)        // ���ѹ�ϵ������
#define WS_P2P_CLIENT_FRIEND_SAME_WITH_SELF                (0xC000001b)        // �����������Ϊ����
#define WS_P2P_CLIENT_OTHER_DEST_ONLINE                     (0xC000001C)        // �û��������ն˵�¼
#define WS_P2P_CLIENT_BINDUUID_NOT_MATCH_LOGINUUID_ERROR	(0xC000001D)

#define WS_P2P_GET_DEVICE_PARAM_ERROR                          (0xC2000001)   //��ȡ�豸��������
#define WS_P2P_SET_DEVICE_PARAM_ERROR                          (0xC2000002)   //�����豸��������
#define WS_P2P_DEVICE_CREATE_STREAM_ERROR                   (0xC2000003)//������ʧ��
#define WS_P2P_DEVICE_STOP_STREAM_ERROR                      (0xC2000004)//��ֹͣʧ��
#define WS_P2P_DEVICE_GET_STREAM_PARAM_ERROR            (0xC2000005)//��������ȡʧ��
#define WS_P2P_DEVICE_SET_STREAM_PARAM_ERROR            (0xC2000006)//����������ʧ��

#define WS_P2P_STRSER_OUT_OF_RESOURCE_ERROR			(0xC0001000)    //��ý���������Դ����

#define WS_P2P_DEVICE_PRIVATE_ERROR					(0xC1000001)	       // ֪ͨ �豸˽������Ϣ����
#define WS_P2P_DEVICE_NOT_EXIST                     (0xC1000002)        // �豸�����ڻ���˵�豸UID ����

#define WS_P2P_TRY_P2P_AGAIN_ERROR                                        (0xC4000001)            // û�г��Թ�P2P ������ֱ������Relay ���Ӵ���
#define WS_P2P_HAVE_P2P_CONNECT_ERROR                                    (0xC4000002)        // ����P2P ���ӳɹ�����ȥֱ������Relay ����
#define WS_P2P_HAVE_RELAY_CONNECT_ERROR                                    (0xC4000003)        // ����Relay ��������ȥֱ������P2P ���Ӵ���

#define WS_P2P_GROUP_MEMBER_ERROR                                    (0xc4000010)               /*����������ߴ���*/

#define WS_P2P_CONFIG_FILE_NOT_EXIST                                (0xc4000020)                /*�����ļ�������*/

#define WS_P2P_P2PSER_CREATE_CONFIG_UPLOAD_SESSION_ERROR			(0xC3000001)
#define WS_P2P_CLIENT_CONFIG_NOT_EXIST_ERROR						(0xC3000002)
#define WS_P2P_CLIENT_PASSWORD_RESET								(0xC3000003)				//�û����뱻����

// 0xC2 : Client ��Device �����Ĵ���
// 0xC3 : ע��������ϴ�����Ϣ
// 0xC4 : P2P �������ϴ�����Ϣ
// 0xC5 : ��ý��������ϴ�����Ϣ
// 0xC6 : �����������ϴ�����Ϣ
// 0xC7 : ϵͳ������Ϣ
#define WS_P2P_SYSTEM_NO_SPACE                                      (0xC7000001)        // ϵͳ�ռ䲻��

/******************/
//  CMD definition
/******************/

#define CMD_USER_REG_REQ_PKT         		(0x0001)
#define CMD_USER_REG_RESP_PKT         	(0x0002)
#define CMD_USER_LOGIN_REQ_PKT         	(0x0003)
#define CMD_USER_LOGIN_RESP_PKT         	(0x0004)
#define CLIENT_HB_REQ						(0x0005)
#define CLIENT_HB_RESP 					(0x0006)
#define CMD_USER_LOGOUT_NOTIFY_PKT		(0x0007)

#define CMD_REG_2_P2P_LOGIN_REQ_PKT                       	(0x0009)   //301
#define CMD_REG_2_P2P_LOGIN_RESP_PKT                      	(0x000a)   //302
#define CMD_REG_2_P2P_UUID_INVALID_NOTIFY_PKT    			(0x000b)   //304

#define CMD_P2P_2_REG_APP_STATUS_NOTIFY_PKT    			(0x000d)   //607

#define CMD_REG_2_P2P_FORCE_LOGOUT_REQ_PKT     				(0x0010)   //323
#define CMD_REG_2_P2P_FORCE_LOGOUT_RESP_PKT                (0x0011)   //324

#define CMD_P2P_2_CLI_FORCE_LOGOUT_REQ_PKT		            (0x0012)   //198
#define CMD_P2P_2_CLI_FORCE_LOGOUT_RESP_PKT		        (0x0013)   //199

#define CMD_USER_STATUS_NOTIFY_PKT 	                        (0x0016)   //311
#define CMD_CLI_P2P_MODIFY_PASSWORD_REQ_PKT (0x0100)
#define CMD_P2P_CLI_MODIFY_PASSWORD_RESP_PKT (0x0101)   //10

#define CMD_P2P_2_REG_MODIFY_PASSWD_REQ_PKT     (0x0102)   //603
#define CMD_P2P_2_REG_MODIFY_PASSWD_RESP_PKT     (0x0103)   //604

#define CMD_CLI_2_P2P_MODIFY_EMAIL_REQ_PKT     (0x0104)   // 11
#define CMD_CLI_2_P2P_MODIFY_EMAIL_RESP_PKT     (0x0105)   // 12

#define CMD_P2P_2_REG_MODIFY_MAIL_REQ_PKT     (0x0106)   //605
#define CMD_P2P_2_REG_MODIFY_MAIL_RESP_PKT    (0x0107)  //606
#define CMD_USER_RESET_PASSWD_REQ_PKT              (0x0108)   //13
#define CMD_USER_RESET_PASSWD_RESP_PKT             (0x0109)   //14

#define CMD_USER_BIND_PHONE_UUID_REQ_PKT              (0x010a)   //15
#define CMD_USER_BIND_PHONE_UUID_RESP_PKT             (0x010b)   //16

#define CMD_P2P_2_REG_BIND_UUID_REQ_PKT     (0x010c)   //637
#define CMD_P2P_2_REG_BIND_UUID_RESP_PKT     (0x010d)   //638

#define CMD_USER_ADD_FRIEND_REQ_PKT              (0x010e)   //31
#define CMD_USER_ADD_FRIEND_RESP_PKT             (0x010f)   //32

#define CMD_USER_REMOVE_FRIEND_REQ_PKT              (0x0110)   //33
#define CMD_USER_REMOVE_FRIEND_RESP_PKT             (0x0111)   //34

#define CMD_USER_FRIEND_OPERATION_NOTIFY_PKT     (0x0112)   //added  removed friend notify 117

#define CMD_REG_2_P2P_DEVICE_SHARE_ADD_REMOVE_NOTIFY_PKT    (0x0113)   //326  /* hzg 20161130 11:05:06  add CMD 0x0113 */

#define CMD_DEVICE_UPDATE_SHARE_NOTIFY_PKT    (0x0114)   //197

#define CMD_REG_P2P_RESET_USER_PASSWORD_NOTIFY_PKT	(0x0115)        // 306

#define CMD_P2P_2_REG_ADD_FRIEND_REQ_PKT         (0x0116)   //609
#define CMD_P2P_2_REG_ADD_FRIEND_RESP_PKT        (0x0117)   //610
#define CMD_P2P_2_REG_REMOVE_FRIEND_REQ_PKT   (0x0118)   //611
#define CMD_P2P_2_REG_REMOVE_FRIEND_RESP_PKT  (0x0119)   //612
/**2017-05-31: add by ronghl**/
#define CMD_P2P_STR_FRIEND_DELETE_NOTIFY_PKT		(0x011b)


#define CMD_USER_ADD_PRIVATE_DEVICE_REQ_PKT              (0x0120)   //35
#define CMD_USER_ADD_PRIVATE_DEVICE_RESP_PKT             (0x0122)   //36

#define CMD_USER_REMOVE_PRIVATE_DEVICE_REQ_PKT              (0x0123)   //37
#define CMD_USER_REMOVE_PRIVATE_DEVICE_RESP_PKT             (0x0124)   //38

#define CMD_P2P_2_REG_ADD_DEVICE_REQ_PKT           (0x0125)   //613
#define CMD_P2P_2_REG_ADD_DEVICE_RESP_PKT          (0x0126)   //614
#define CMD_P2P_2_REG_REMOVE_DEVICE_REQ_PKT     (0x0127)   //615
#define CMD_P2P_2_REG_REMOVE_DEVICE_RESP_PKT   (0x0128)   //616
#define CMD_REG_2_DEVICE_ADD_REQ_PKT                    (0x0129)   //68
#define CMD_REG_2_DEVICE_ADD_RESP_PKT                  (0x012a)   //69
#define CMD_DEVICE_DEL_PRIVATE_RELATION_NOTIFY_PKT  (0x012c)   //111


#define CMD_USER_GET_FRIEND_LIST_REQ_PKT              (0x0130)   //17
#define CMD_USER_GET_FRIEND_LIST_RESP_PKT             (0x0131)   //18

#define CMD_USER_GET_FRIENDS_ALIAS_REQ_PKT              (0x0132)   //23
#define CMD_USER_GET_FRIENDS_ALIAS_RESP_PKT             (0x0133)   //24

#define CMD_P2P_2_REG_GET_FRIEND_INFO_REQ_PKT           (0x0134)   //619
#define CMD_P2P_2_REG_GET_FRIEND_INFO_RESP_PKT           (0x0135)   //620

#define CMD_USER_MODIFY_FRIEND_ALIAS_REQ_PKT              (0x0136)   //27
#define CMD_USER_MODIFY_FRIEND_ALIAS_RESP_PKT             (0x0137)   //28

#define CMD_P2P_2_REG_MODIFY_FRIEND_ALIAS_REQ_PKT    (0x0138)   //633
#define CMD_P2P_2_REG_MODIFY_FRIEND_ALIAS_RESP_PKT    (0x0139)   //634

#define CMD_USER_GET_SHARED_CHANNELS_REQ_PKT              (0x013a)   //21
#define CMD_USER_GET_SHARED_CHANNELS_RESP_PKT             (0x013b)   //22

#define CMD_P2P_2_REG_GET_SHARED_CHAN_ALIAS_REQ_PKT    (0x013c)   //623
#define CMD_P2P_2_REG_GET_SHARED_CHAN_ALIAS_RESP_PKT    (0x013d)   //624

#define CMD_USER_GET_PRIVATE_DEVICES_REQ_PKT    (0x013e)   //19
#define CMD_USER_GET_PRIVATE_DEVICES_RESP_PKT    (0x013f)   //20

#define CMD_USER_GET_DEVICES_ALIAS_REQ_PKT    (0x0140)   //25
#define CMD_USER_GET_DEVICES_ALIAS_RESP_PKT    (0x0141)   //26

#define CMD_USER_GET_DEVICE_ALIAS_REQ_PKT       (0x011c)   //60
#define CMD_USER_GET_DEVICE_ALIAS_RESP_PKT      (0x011d)   //61

#define CMD_P2P_2_REG_GET_DEVICE_INFO_REQ_PKT    (0x0142)   //621
#define CMD_P2P_2_REG_GET_DEVICE_INFO_RESP_PKT    (0x0143)   //622

#define CMD_USER_MODIFY_DEVICE_ALIAS_REQ_PKT    (0x0144)   //29
#define CMD_USER_MODIFY_DEVICE_ALIAS_RESP_PKT    (0x0145)   //30

#define CMD_P2P_2_REG_MODIFY_DEVICE_ALIAS_REQ_PKT    (0x0146)   //631
#define CMD_P2P_2_REG_MODIFY_DEVICE_ALIAS_RESP_PKT    (0x0147)   //632

#define CMD_USER_GET_SHARING_CHANNELS_REQ_PKT    (0x0148)   //120
#define CMD_USER_GET_SHARING_CHANNELS_RESP_PKT    (0x0149)   //121

#define CMD_P2P_2_REG_GET_SHARING_CHAN_LIST_REQ_PKT    (0x014a)   //635
#define CMD_P2P_2_REG_GET_SHARING_CHAN_LIST_RESP_PKT    (0x014b)   //636

#define CMD_USER_GET_CONFIG_FILE_LIST_REQ_PKT		(0x014c)
#define CMD_USER_GET_CONFIG_FILE_LIST_RESP_PKT		(0x014d)
#define CMD_USER_UPLOAD_CONFIG_FILE_REQ_PKT			(0x014e)
#define CMD_USER_UPLOAD_CONFIG_FILE_RESP_PKT		(0x014f)
#define CMD_P2P_USER_UPLOAD_RESULT_NOTIFY_PKT		(0x0150)
#define CMD_USER_DOWNLOAD_CONFIG_REQ_PKT			(0x0152)
#define CMD_USER_DOWNLOAD_CONFIG_RESP_PKT			(0x0153)
#define CMD_USER_STARTUP_CONFIG_SEND_NOTIFY_PKT		(0x0154)
#define CMD_P2P_USER_CONFIG_SEND_DONE_NOTIFY_PKT	(0x0156)
#define CMD_USER_CONFIRM_DOWNLOAD_NOTIFY_PKT		(0x0158)
#define CMD_P2P_REG_CONFIG_FILE_INFO_REQ_PKT		(0x015a)
#define CMD_P2P_REG_CONFIG_FILE_INFO_RESP_PKT		(0x015b)
#define CMD_P2P_REG_CONFIG_UPLOAD_NOTIFY_PKT		(0x015c)

#define CMD_USR_CHANGE_DEVICE_PASSWORD_REQ_PKT     (0x015d)             // 242
#define CMD_USR_CHANGE_DEVICE_PASSWORD_RESP_PKT    (0x015e)             // 243
#define CMD_P2P_CHANGE_DEVICE_PASSWORD_REQ_PKT     (0x0160)             // 673
#define CMD_P2P_CHANGE_DEVICE_PASSWORD_RESP_PKT    (0x0161)             // 674


#define CMD_DEVICE_LOGIN_REQ_PKT    (0x0200)   //64
#define CMD_DEVICE_LOGIN_RESP_PKT    (0x0201)   //65

#define CMD_DEVICE_HEART_REQ_PKT    (0x0202)   //66
#define CMD_DEVICE_HEART_RESP_PKT    (0x0203)   //67

#define CMD_P2P_2_REG_DEVICE_IP_STATUS_NOTIFY_PKT     (0x0204)  //669

#define CMD_REG_2_P2P_DEVICE_ONLINE_NOTIFY_PKT     (0x0206)  //305

#define CMD_DEVICE_ONLINE_STATUS_NOTIFY_PKT     (0x0208)  //39  P2P --> Client
#define CMD_CLIENT_ONLINE_STATUS_NOTIFY_PKT		(0x0209)	//602 P2P-> Device
#define CMD_USER_START_P2P_REQ_PKT    (0x020a)   //74
#define CMD_USER_START_P2P_RESP_PKT    (0x020b)   //75

#define CMD_USER_START_RELAY_REQ_PKT    (0x020c)   //79
#define CMD_USER_START_RELAY_RESP_PKT    (0x020d)   //80

#define CMD_CLEINT_RELAY_REQ_PKT       (0x020e)  //82
#define CMD_CLIENT_RELAY_RESP_PKT   (0x020f)  //87

#define CMD_STOP_RELAY_NOTIFY_PKT     (0x0210)  //83  P2P --> Client

#define CMD_DEVICE_AND_CLIENT_REQ_PKT    (0x0212)   //76
#define CMD_DEVICE_AND_CLIENT_RESP_PKT    (0x0213)   //77

#define CMD_CLIENT_CONNECT_STATUS_NOTIFY_PKT    (0x0214)   //71
#define CMD_DEVICE_CONNECT_STATUS_NOTIFY_PKT    (0x0215)   //72

//#define CMD_DEVICE_START_CONNECT_NOTIFY_PKT (0x0216)   //70   /* 20171117 hzg ֪ͨ���޸�Ϊ����Ӧ����޸�Ϊ0x022a  0x022b */

#define CMD_DEVICE_GET_SHARE_REQ_PKT            (0x0217)   //85
#define CMD_DEVICE_GET_SHARE_RESP_PKT           (0x0218)   //86

#define CMD_DEVICE_LOGIN_NOTIFY_PKT             (0x0219)   //107

#define CMD_P2PSER_GET_RELAY_SERVER_REQ_PKT           (0x021c)  //641
#define CMD_P2PSER_GET_RELAY_SERVER_RESP_PKT         (0x021d)  //642

#define CMD_P2PSER_RELAY_REQ_PKT              (0x021e)  //643
#define CMD_P2PSER_RELAY_RESP_PKT           (0x021f)  //644

#define CMD_DEVICE_START_RELAY_CONNECT_NOTIFY_PKT   (0x0224)   //81

#define CMD_DEVICE_RELAY_REQ_PKT    (0x0226)  //84
#define CMD_DEVICE_RELAY_RESP_PKT   (0x0227)   //89

#define CMD_DEVICE_CLIENT_STOP_HEART_NOTIFY_PKT (0x0228)   //78

#define CMD_DEVICE_START_CONNECT_REQ_PKT (0x022a)   //70
#define CMD_DEVICE_START_CONNECT_RESP_PKT (0x022b)	//79

#define CMD_DEVICE_BANDWIDTH_FEEDBACK_REQ_PKT	(0x022c)	
#define CMD_DEVICE_BANDWIDTH_FEEDBACK_RESP_PKT	(0x022d)

#define CMD_USER_SET_PUSH_MSG_CONFIG_REQ_PKT    (0x0400)   //126
#define CMD_USER_SET_PUSH_MSG_CONFIG_RESP_PKT    (0x0401)   //127

#define CMD_USER_GSET_PUSH_MSG_CONFIG_REQ_PKT    (0x0402)   //124
#define CMD_USER_GET_PUSH_MSG_CONFIG_RESP_PKT    (0x0403)   //125

#define CMD_P2P_2_REG_MODIFY_PUSH_MSG_CONFIG_REQ_PKT         (0x0406)  //665
#define CMD_P2P_2_REG_MODIFY_PUSH_MSG_CONFIG_RESP_PKT       (0x0407)  //666
#define CMD_P2P_2_REG_GET_PUSH_MSG_CONFIG_REQ_PKT                (0x0408)  //667
#define CMD_P2P_2_REG_GET_PUSH_MSG_CONFIG_RESP_PKT               (0x0409)  //668


#define CMD_P2PSEND_ALARM_MSG_2_USER_NOTIFY_PKT      (0x0410)   //63

#define CMD_USER_CONFIG_NOTIFY_PKT      (0x0412)   //335

#define CMD_P2P_CONFIG_NOTIFY_PKT      (0x0413)   //343

#define CMD_STRSER_REGSER_HB_PKT        (0x0418)   //1001

#define CMD_REG_2_ALA_P2PONLINESTATECHANGE_NOTIFY_PKT  (0x041a)   //337


#define CMD_USER_SEND_SHARE_CHANNEL_REQ_PKT    (0x0500)   //41   Client A --> P2P
#define CMD_USER_SEND_SHARE_CHANNEL_RESP_PKT    (0x0501)   //42

#define CMD_USER_SHARE_CHANNEL_NOTIFY_PKT   (0x0502)   //137  P2P -->Client B


#define CMD_RECEIVED_USER_SHARE_CHANNEL_REQ_PKT    (0x0504)   //43   P2P --> Client B
#define CMD_RECEIVED_USER_SHARE_CHANNEL_RESP_PKT    (0x0505)   //44

#define CMD_USER_PROCESS_SHARING_CHANNEL_REQ_PKT    (0x0506)   //45   Client B --> P2P
#define CMD_USER_PROCESS_SHARING_CHANNEL_RESP_PKT    (0x0507)   //46

#define CMD_USER_REMOVE_SHARED_CHANNEL_REQ_PKT    (0x0508)   //48   Client B --> P2P    //�����߷���
#define CMD_USER_REMOVE_SHARED_CHANNEL_RESP_PKT    (0x0509)   //49


#define CMD_USER_CANCEL_SHARING_CHANNEL_REQ_PKT    (0x050a)   //50   Client A --> P2P   //���������߷���
#define CMD_USER_CANCEL_SHARING_CHANNEL_RESP_PKT    (0x050b)   //51

#define CMD_USER_CANCEL_SHARING_CHANNEL_NOTIFY_PKT          (0x050c)  //52   P2P --> Client B

#define CMD_USER_PROCESSED_SHARED_CHANNEL_RET_NOTIFY_PKT    (0x050e)  //47   P2P --> Client A


#define CMD_P2P_2_REG_SHARE_CHANNEL_NOTIFY_PKT          (0x0510)  //657

#define CMD_P2P_2_REG_CANCEL_SHARED_CHANNEL_NOTIFY_PKT  (0x0512)  //659             //������50����


#define CMD_P2P_2_REG_SHARE_ACCEPTOR_PROCESS_NOTIFY_PKT  (0x0514)  //661

#define CMD_REG_2_P2P_SHARING_CHANNEL_NOTIFY_PKT  (0x0516)  //319

#define CMD_REG_2_P2P_REMOVE_SGARING_CHANNEL_NOTIFY_PKT  (0x0518)  //331

#define CMD_REG_2_P2P_ACCEPTOR_PROCESSED_RET_NOTIFY_PKT  (0x051a)  //333

#define CMD_REG_2_P2P_CANCEL_SHARING_CHANNEL_NOTIFY_PKT  (0x051c)  //325

#define CMD_P2P_2_REG_ACCEPT_OR_REJECT_SHARING_CHANNEL_REQ_PKT    (0x051e)   //662 
#define CMD_P2P_2_REG_ACCEPT_OR_REJECT_SHARING_CHANNEL_RESP_PKT    (0x051f)   //663


#define CMD_USER_START_MESSAGE_SESSSION_REQ_PKT    (0x0530)   //128   Client A --> P2P  Message file transmission
#define CMD_USER_START_MESSAGE_SESSSION_RESP_PKT    (0x0531)   //129


#define CMD_CLIENT_MESSAGE_UPLOAD_NOTIFY_PKT     (0x0532)  //1003  Stream-Ser --> Client

#define CMD_CLIENT_MESSAGE_UPLOAD_DONE_NOTIFY_PKT     (0x0534)  //130   Client --> P2PServer-Ser

#define CMD_P2PSER_MESSAGE_REQ_PKT          (0x0536)  //649
#define CMD_P2PSER_MESSAGE_RESP_PKT (0x0537)  //650

#define CMD_P2P2C_PUSH_USER_MESSAGE_NOTIFY_PKT (0x0538)  //59  

#define CMD_P2P2C_USER_FILE_MESSAGE_NOTIFY_PKT (0x053a)  //57

#define CMD_CLIENT_MESSAGE_DOWNLOAD_NOTIFY_PKT     (0x053c)    //58
#define CMD_P2PSER_SESSION_FORWAR_NOTIFY_PKT     (0x0540)  //653

#define CMD_P2PSER_MESSAGE_DOWNLOAD_NOTIFY_PKT   (0x0542)    //1007

#define CMD_REG_2_P2P_STREAM_SERVER_INFO_NOTIFY_PKT   (0x0544)   //P2P�ϵ�,Stream Server�ϵ�ʱ.

#define CMD_USR_CREATE_GROUP_REQ_PKT                 (0x0546)         /*131 �û����󴴽������� */
#define CMD_USR_CREATE_GROUP_RESP_PKT                (0x0547)         /*132 �û����󴴽�������Ӧ�� */
#define CMD_USR_CHANGE_GROUP_MEMBER_REQ_PKT             (0x0548)         /*133 �û���������������Ա */
#define CMD_USR_CHANGE_GROUP_MEMBER_RESP_PKT           (0x0549)          /*134 �û���������������ԱӦ�� */


#define CMD_CLIENT_MESSAGE_DOWNLOAD_REQ_PKT         (0x054a)        /*�û�������������*/
#define CMD_CLIENT_MESSAGE_DOWNLOAD_RESP_PKT        (0x054b)        /*�û�������������Ӧ��*/

#define CMD_P2P2DEVICE_HW_RESET_NOTIFY_PKT   (0x0550)    //53

#define CMD_P2P2C_SHARING_CHANNEL_FAIL_NOTIFY_PKT   (0x0552)    //54

#define CMD_REG_2_P2P_DEVICE_RESET_NOTIFY_PKT   (0x0554)    //327

#define CMD_USER_GET_P2P_INFO_REQ_PKT    (0x0560)   //55   Client A --> Reg
#define CMD_USER_GET_P2P_INFO_RESP_PKT    (0x0562)   //56


#define CMD_DEVICE_INQUIRY_P2P_SERVER_REQ_PKT   (0x0564)   //122
#define CMD_DEVICE_INQUIRY_P2P_SERVER_RESP_PKT  (0x0565)   //123

#define CMD_P2P_2_REG_HEARTBEAT_NOTIFY_PKT   (0x0566)    //601

#define CMD_REG2STREAM_P2P_LIST_NOTIFY_PKT   (0x0568)    //341

#define CMD_USR_GET_GROUP_MEMBER_REQ_PKT        (0x0574)                /*245 �û���ȡ�������Ա*/
#define CMD_USR_GET_GROUP_MEMBER_RESP_PKT       (0x0575)                /*246 �û���ȡ�������ԱӦ��*/
//=====================device �������start==================================//

#define CMD_DEVICE_GET_RECORD_STATUS_REQ_PKT    (0x0300)   //145
#define CMD_DEVICE_GET_RECORD_STATUS_RESP_PKT   (0x0301)   //146

#define CMD_DEVICE_GET_NAME_REQ_PKT (0x0302)   //147
#define CMD_DEVICE_GET_NAME_RESP_PKT    (0x0303)   //148

#define CMD_DEVICE_SET_NAME_REQ_PKT (0x0304)   //149
#define CMD_DEVICE_SET_NAME_RESP_PKT    (0x0305)   //150

#define CMD_DEVICE_GET_CHANNLE_NAME_REQ_PKT (0x0306)   //151
#define CMD_DEVICE_GET_CHANNLE_NAME_RESP_PKT    (0x0307)   //152

#define CMD_DEVICE_SET_CHANNLE_NAME_REQ_PKT (0x0308)   //153
#define CMD_DEVICE_SET_CHANNLE_NAME_RESP_PKT    (0x0309)   //154

#define CMD_DEVICE_GET_ALARM_SCHEDULE_REQ_PKT   (0x030a)   //155
#define CMD_DEVICE_GET_ALARM_SCHEDULE_RESP_PKT  (0x030b)   //156

#define CMD_DEVICE_SET_ALARM_SCHEDULE_REQ_PKT   (0x030c)   //157
#define CMD_DEVICE_SET_ALARM_SCHEDULE_RESP_PKT  (0x030d)   //158

#define CMD_DEVICE_GET_CHANNEL_RECORD_STORAGE_TYPE_REQ_PKT  (0x030e)   //159
#define CMD_DEVICE_GET_CHANNEL_RECORD_STORAGE_TYPE_RESP_PKT (0x030f)   //160

#define CMD_DEVICE_SET_CHANNEL_RECORD_STORAGE_TYPE_REQ_PKT  (0x0310)   //161
#define CMD_DEVICE_SET_CHANNEL_RECORD_STORAGE_TYPE_RESP_PKT (0x0311)   //162

#define CMD_DEVICE_GET_CHANNEL_RECORD_SCHEDULE_REQ_PKT  (0x0312)   //163
#define CMD_DEVICE_GET_CHANNEL_RECORD_SCHEDULE_RESP_PKT (0x0313)   //164

#define CMD_DEVICE_SET_CHANNEL_RECORD_SCHEDULE_REQ_PKT  (0x0314)   //165
#define CMD_DEVICE_SET_CHANNEL_RECORD_SCHEDULE_RESP_PKT (0x0315)   //166

#define CMD_DEVICE_GET_ALARM_PUSH_CONFIG_REQ_PKT    (0x031c)   //170
#define CMD_DEVICE_GET_ALARM_PUSH_CONFIG_RESP_PKT   (0x031d)   //171

#define CMD_DEVICE_SET_ALARM_PUSH_CONFIG_REQ_PKT    (0x031e)   //172
#define CMD_DEVICE_SET_ALARM_PUSH_CONFIG_RESP_PKT   (0x031f)   //173

#define CMD_DEVICE_PTZ_NOTIFY_PKT   (0x0320)   //174

#define CMD_DEVICE_GET_IMAGE_PARA_REQ_PKT   (0x0322)   //175
#define CMD_DEVICE_GET_IMAGE_PARA_RESP_PKT  (0x0323)   //176

#define CMD_DEVICE_SET_IMAGE_PARA_REQ_PKT   (0x0324)   //177
#define CMD_DEVICE_SET_IMAGE_PARA_RESP_PKT  (0x0325)   //178

#define CMD_DEVICE_GET_VIDEO_QUALITY_REQ_PKT    (0x0326)   //179
#define CMD_DEVICE_GET_VIDEO_QUALITY_RESP_PKT   (0x0327)   //180

#define CMD_DEVICE_SET_VIDEO_QUALITY_REQ_PKT    (0x0328)   //181
#define CMD_DEVICE_SET_VIDEO_QUALITY_RESP_PKT   (0x0329)   //182

#define CMD_DEVICE_GET_DISK_WORK_CTRL_REQ_PKT   (0x032a)   //183
#define CMD_DEVICE_GET_DISK_WORK_CTRL_RESP_PKT  (0x032b)   //184

#define CMD_DEVICE_SET_DISK_WORK_CTRL_REQ_PKT   (0x032c)   //185
#define CMD_DEVICE_SET_DISK_WORK_CTRL_RESP_PKT  (0x032d)   //186

#define CMD_DEVICE_SET_PASSWD_REQ_PKT   (0x032e)   //187
#define CMD_DEVICE_SET_PASSWD_RESP_PKT  (0x032f)   //188

#define CMD_DEVICE_GET_WIFI_REQ_PKT (0x0330)   //191
#define CMD_DEVICE_GET_WIFI_RESP_PKT    (0x0331)   //192

#define CMD_DEVICE_SET_WIFI_REQ_PKT (0x0332)   //193
#define CMD_DEVICE_SET_WIFI_RESP_PKT    (0x0333)   //194

#define CMD_DEVICE_START_AUDIO_REQ_PKT  (0x0334)   //91
#define CMD_DEVICE_START_AUDIO_RESP_PKT (0x0335)   //92

#define CMD_DEVICE_STOP_AUDIO_REQ_PKT   (0x0336)   //93
#define CMD_DEVICE_STOP_AUDIO_RESP_PKT  (0x0337)   //94

#define CMD_DEVICE_START_CLIENT_AUDIO_REQ_PKT  (0x0338)   //95
#define CMD_DEVICE_START_CLIENT_AUDIO_RESP_PKT (0x0339)   //96

#define CMD_DEVICE_STOP_CLIENT_AUDIO_REQ_PKT   (0x033a)   //97
#define CMD_DEVICE_STOP_CLIENT_AUDIO_RESP_PKT  (0x033b)   //98

#define CMD_DEVICE_START_TALK_REQ_PKT   (0x033c)   //99
#define CMD_DEVICE_START_TALK_RESP_PKT  (0x033d)   //100

#define CMD_DEVICE_STOP_TALK_REQ_PKT    (0x033e)   //101
#define CMD_DEVICE_STOP_TALK_RESP_PKT   (0x033f)   //102

#define CMD_DEVICE_START_VIDEO_REQ_PKT  (0x0340)   //103
#define CMD_DEVICE_START_VIDEO_RESP_PKT (0x0341)   //104

#define CMD_DEVICE_STOP_VIDEO_REQ_PKT   (0x0342)   //105
#define CMD_DEVICE_STOP_VIDEO_RESP_PKT  (0x0343)   //106

#define CMD_DEVICE_START_DOWNLOAD_REQ_PKT (0x0344)   //109
#define CMD_DEVICE_START_DOWNLOAD_RESP_PKT    (0x0345)   //110

#define CMD_DEVICE_GET_DOWNLOAD_PROGRESS_REQ_PKT    (0x346)   //220
#define CMD_DEVICE_GET_DOWNLOAD_PROGRESS_RESP_PKT    (0x347)   //221

#define CMD_DEVICE_STOP_DOWNLOAD_REQ_PKT    (0x348)   //222
#define CMD_DEVICE_STOP_DOWNLOAD_RESP_PKT    (0x349)   //223

#define CMD_DEVICE_GET_ALL_PARAM_REQ_PKT     (0x034a)   //224
#define CMD_DEVICE_GET_ALL_PARAM_RESP_PKT    (0x034b)   //225

#define CMD_DEVICE_GET_CHANNEL_ALL_PARAM_REQ_PKT     (0x034c)   //226
#define CMD_DEVICE_GET_CHANNEL_ALL_PARAM_RESP_PKT    (0x034d)   //227

#define CMD_DEVICE_GET_CHANNEL_MD_REQ_PKT     (0x034e)   //228
#define CMD_DEVICE_GET_CHANNEL_MD_RESP_PKT    (0x034f)   //229

#define CMD_DEVICE_SET_CHANNEL_MD_REQ_PKT     (0x0350)   //230
#define CMD_DEVICE_SET_CHANNEL_MD_RESP_PKT    (0x0351)   //231
//add by qqy,end at 2016-12-15 16:49:18

#define CMD_DEVICE_GET_REPLAY_FILE_LIST_REQ_PKT    (0x0370)   //200
#define CMD_DEVICE_GET_REPLAY_FILE_LIST_RESP_PKT    (0x0371)   //201

#define CMD_DEVICE_START_REPLAY_REQ_PKT    (0x0372)   //202
#define CMD_DEVICE_START_REPLAY_RESP_PKT    (0x0373)   //203

#define CMD_DEVICE_GET_REPLAY_SPEED_REQ_PKT    (0x0374)   //204
#define CMD_DEVICE_GET_REPLAY_SPEED_RESP_PKT    (0x0375)   //205

#define CMD_DEVICE_SET_REPLAY_SPEED_REQ_PKT    (0x0376)   //206
#define CMD_DEVICE_SET_REPLAY_SPEED_RESP_PKT    (0x0377)   //207

#define CMD_DEVICE_GET_REPLAY_PROGRESS_REQ_PKT    (0x0378)   //208
#define CMD_DEVICE_GET_REPLAY_PROGRESS_RESP_PKT    (0x0379)   //209

#define CMD_DEVICE_SET_REPLAY_PROGRESS_REQ_PKT    (0x037a)   //210
#define CMD_DEVICE_SET_REPLAY_PROGRESS_RESP_PKT    (0x037b)   //211

#define CMD_DEVICE_SET_REPLAY_FILE_REQ_PKT    (0x037c)   //212
#define CMD_DEVICE_SET_REPLAY_FILE_RESP_PKT    (0x037d)   //213

#define CMD_DEVICE_SET_REPLAY_STATUS_REQ_PKT    (0x037e)   //214
#define CMD_DEVICE_SET_REPLAY_STATUS_RESP_PKT    (0x037f)   //215

#define CMD_DEVICE_STOP_REPLAY_REQ_PKT    (0x0380)   //216
#define CMD_DEVICE_STOP_REPLAY_RESP_PKT    (0x0381)   //217

#define CMD_DEVICE_REPLAY_END_NOTIFY_PKT    (0x0382)   //218

//liujl change start-end at 20171114
#define CMD_DEVICE_SET_WIFI_SWITCH_REQ_PKT		(0x0384)
#define CMD_DEVICE_SET_WIFI_SWITCH_RESP_PKT		(0x0385)


#define CMD_FRAME_DATA_PKT    			(0x0800)   		//ý��֡�ְ�
#define CMD_FILE_DATA_PKT    			(0x0801)       	//�ļ����ݷְ���
#define CMD_CONFIG_FILE_DATA_PKT		(0x0802)		//config file data cmd
//=====================device �������end==================================//

//==================add by ronghl 2017-01-14 start==========================// 
#define CMD_REG_STR_RELAY_INFO_REQ_PKT	        (0x0900)
#define CMD_REG_STR_RELAY_INFO_RESP_PKT       (0x0901)
#define CMD_REG_STR_MESSAGE_INFO_REQ_PKT    (0x0902)
#define CMD_REG_STR_MESSAGE_INFO_RESP_PKT  (0x0903)
#define CMD_REG_LOG_PAGE_REQ_PKT                     (0x0904)
#define CMD_REG_LOG_PAGE_RESP_PKT                   (0x0905)

/* hzg added User notify Server switch work node Notify */
#define CMD_USER_CHANGE_SERVER_WORK_MODE_NOTIFY_PKT   (0x0910)

//=====================add by ronghl 2017-01-14 end========================//
#define CMD_P2P_REG_REBUILD_USER_REQ		(0x0a01)
#define CMD_P2P_REG_REBUILD_USER_RESP		(0x0a02)
#define CMD_P2P_REG_REBUILD_DEVICE_REQ		(0x0a03)
#define CMD_P2P_REG_REBUILD_DEVICE_RESP		(0x0a04)
//20161213
typedef enum 
{
	UUID_TYPE_REGISTER_SERVER = 1,
	UUID_TYPE_P2P_SERVER,
	UUID_TYPE_STREAM_SERVER, 
	UUID_TYPE_ALARM_SERVER
}UUIDType;

// change by linhh 20161202 : P2P��¼���û�״̬���ܺ������������û�״̬��¼��ͻ
typedef enum
{
    P2P_OFFLINE = 0 ,
    P2P_BOOT_ONLINE=1,
    P2P_APP_ONLINE=2,
    P2P_BOOT_ONLINE_READY,
    P2P_APP_ONLINE_READY,
    P2P_FORCE_LOGOUT_PROCESSING,
    P2P_FORCE_LOGOUT
}P2POnlineStatus;

//User Status
typedef enum
{
    OFFLINE=0,
    BOOT_ONLINE,
    APP_ONLINE
}OnlineStatus;

//Device Type   add by ronghl 2017-01-06
typedef enum
{
	NORMAL_DEVICE = 0,
	PUBLIC_DEVICE = 1
}DeviceType;


typedef enum
{
    Friend_Operation_Remove = 0,
    Friend_Operation_Add
}FriendOperation;


typedef enum 
{
	P2P_DIRECT_CONNECTING,
	P2P_DIRECT_CONNECTED,
	P2P_DIRECT_FAILED,
	P2P_DIRECT_CLOSED,
	P2P_RELAY_CREATING,
	P2P_RELAY_CREATED,
	P2P_RELAY_CONNECTED,
	P2P_RELAY_CLOSED
}P2PConnectionStatus;

 //Modified by qqy,start at 2016-12-13 17:20:05
typedef enum   //device --> P2pSer  ֪ͨ����״̬CMD 71
{
	WS_P2P_CONNECT_STATUS_SUCCESS = 0,
	WS_P2P_CONNECT_STATUS_FAILED,
	WS_P2P_CONNECT_STATUS_UNKNOWN = -1,		//add by ronghl 2017-04-24: use only in p2pserver, not used in device or app
}ws_p2p_connect_status ;
 //Modified by qqy,end at 2016-12-13 17:20:08

/////////////////////////�����нṹ�嶨��//////////////////////////////////////
typedef enum
{
    WS_P2P_DATA_TYPE_UNKNOW,
    WS_P2P_DATA_TYPE_CMD,//�����
    WS_P2P_DATA_TYPE_FRAME,//ý��֡���ݰ�
    WS_P2P_DATA_TYPE_BIN,//�ļ����������ݰ�
} ws_p2p_data_type;


typedef struct _ReqCMDHeader
{
    int PacketType;
    int CMD;
    int SeqNo;
} ReqCMDHeader;

typedef struct _RespCMDHeader
{
    int PacketType;
    int CMD;
    int SeqNo;
    int Result;
} RespCMDHeader;

///////////���������ص�����ṹ�嶨��/////////////////////////////

typedef struct _UserRegistReqPkt   //0x0001
{
    ReqCMDHeader Header;
    char AppUsrName[USER_NAME_LEN];
    char AppLoginPasswd[PASSWORD_LEN];
    char MailAddress[EMAIL_ADDR_LEN];
} UserRegistReqPkt;

typedef struct _UserRegistRespPkt   //0x0002
{
    RespCMDHeader Header;
} UserRegistRespPkt;

typedef struct _UserLoginReqPkt   //0x0003
{
    ReqCMDHeader Header;
    char AppUsrName[USER_NAME_LEN];
    char AppLoginPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
    int LoginMode;
} UserLoginReqPkt;

typedef struct _UserLoginRespPkt   //0x0004
{
    RespCMDHeader Header;
    char   P2PServerIP[IP_STR_LEN];
    int     P2PServerPort;  
} UserLoginRespPkt;


typedef struct _cli_p2p_hb_req_pkt  //5 0x0005
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswrod[UID_LEN];
    char AppLanIP[IP_STR_LEN];
    int AppLanPort;
    char PhoneUUID[UID_LEN];
}cli_p2p_hb_req_pkt;

typedef struct _cli_p2p_hb_resp_pkt  //6 0x0005
{
    RespCMDHeader Header;
}cli_p2p_hb_resp_pkt;


typedef struct _UserLogoutNotifyPkt	//0x0007
{
    ReqCMDHeader Header;
    char AppUsrName[USER_NAME_LEN];
    char AppUsrPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
}UserLogoutNotifyPkt;

typedef struct _Reg2P2PLoginReqPkt   //(0x0009)   301
{
    ReqCMDHeader Header;
    char         AppUsrName[USER_NAME_LEN];
    char         AppLoginPasswd[PASSWORD_LEN];
    char         AppUID[UID_LEN];
    int          LoginMode;
    WS_BOOL      bBindPhone;                                /* ����ʹ�ã�P2P����������Ҫ�û��Ƿ�����ն�*/
    char         PhoneUID[UID_LEN];
    int          AlarmPushSwitch;		
    int          AlarmMDPush;	
    int          PushFriendMsg;                             /*add by linhh 20170828 : ���Ӻ�����Ϣ��������*/
    int          PushChanSharingMsg;
    int          PushFileMsg;
} Reg2P2PLoginReqPkt;

typedef struct _Reg2P2PLoginRespPkt   //(0x000a)   302
{
    RespCMDHeader Header;
} Reg2P2PLoginRespPkt;

typedef struct _Reg2P2PInvalidUUIDNotifyPkt   //(0x000b)   304
{
    ReqCMDHeader Header;
    char CommonUID[UID_LEN];
    int ClientType;
} Reg2P2PInvalidUUIDNotifyPkt;

typedef struct _P2P2RegAppIPStatusNotifyPkt   //(0x000d)   607
{
    ReqCMDHeader Header;
    char    P2PUID[UID_LEN];                                            // add by linhh 20161124 : ���P2P ��������UID ��Ϣ
    char AppUID[UID_LEN];
    int AppOnlineStatus;
    char AppWANIP[IP_STR_LEN];
    int     WANPort;                                                        // change by linhh 20161125 
    char AppLANIP[IP_STR_LEN];
    int     LANPort;                                                          // change by linhh 20161125 
    char PhoneUID[UID_LEN];                                           // change by liujl 20161129 : ��ӿͻ��˵�¼���ն�UID ��Ϣ
    char AppLoginTime[32];											//add by ronghl 2017-01-12 : �û���¼ʱ��
} P2P2RegAppIPStatusNotifyPkt;

typedef struct _Reg2P2PForceLogoutReqPkt   //(0x0010)   323
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
} Reg2P2PForceLogoutReqPkt;

typedef struct _Reg2P2PForceLogoutRespPkt   //(0x0011)   324
{
    RespCMDHeader Header;
} Reg2P2PForceLogoutRespPkt;



typedef struct _P2PCliForceLogoutReqPkt		//0x0012    198
{
	ReqCMDHeader Header;
	int LogoutReason;
}P2PCliForceLogoutReqPkt;


typedef struct _CliP2PForceLogoutRespPkt   //0x0013
{
	RespCMDHeader Header;
}CliP2PForceLogoutRespPkt;


typedef struct _CliP2PModifyPasswordReqPkt //9 0x0100
{
	ReqCMDHeader Header;
	char AppUsrName[USER_NAME_LEN];
	char AppOldPassword[PASSWORD_LEN];
	char AppNewPassword[PASSWORD_LEN];
	char PhoneUUID[UID_LEN];
	
}CliP2PModifyPasswordReqPkt;


typedef struct _P2PCliModifyPasswordRespPkt	//10 0x0101
{
	RespCMDHeader Header;
}P2PCliModifyPasswordRespPkt;

/*
    Packet:311
    ˵��:�����û�״̬֪ͨ��
    CMD:0x0016
*/
typedef struct _userStatusNotifyPkt
{
    ReqCMDHeader Header;
    char ClientName[USER_NAME_LEN];
    char ClientUID[UID_LEN];
    int ClientOnlineStatus;
    char P2PServerIP[IP_STR_LEN];
    int P2PServerPort;                                                  // change by linhh 20161125 
    char P2PServerUID[UID_LEN];
} UserStatusNotifyPkt;

typedef struct _P2P2RegModifyPasswdReqPkt   //(0x0102)   603
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppOldPasswd[PASSWORD_LEN];
    char AppNewPasswd[PASSWORD_LEN];
} P2P2RegModifyPasswdReqPkt;

typedef struct _P2P2RegModifyPasswdRespPkt   //(0x0103)   604
{
    RespCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppNewPasswd[PASSWORD_LEN];
} P2P2RegModifyPasswdRespPkt;

typedef struct _CliP2PModifyEmailReqPkt  // 0x0104  11
{
	ReqCMDHeader Header;
	char AppUsrName[USER_NAME_LEN];
	char AppUsrPassword[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
	char EmailAddr[EMAIL_ADDR_LEN];
}CliP2PModifyEmailReqPkt;


typedef struct _CliP2PModifyEmailRespPkt  // 0x0105  12
{
	RespCMDHeader Header;
}CliP2PModifyEmailRespPkt;



typedef struct _P2P2RegModifyMailReqPkt   //(0x0106)   605
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char EMailAddr[EMAIL_ADDR_LEN];
} P2P2RegModifyMailReqPkt;

typedef struct _P2P2RegModifyMailRespPkt   //(0x0107)   606
{
    RespCMDHeader Header;
    char AppName[USER_NAME_LEN];
} P2P2RegModifyMailRespPkt;

typedef struct _UserResetPasswdReqPkt   //(0x0108)   13
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char EMailAddr[EMAIL_ADDR_LEN];
} UserResetPasswdReqPkt;

typedef struct _UserResetPasswdRespPkt   //(0x0109)   14
{
    RespCMDHeader Header;
} UserResetPasswdRespPkt;

typedef struct _UserBindPhoneUUIDReqPkt   //(0x010a)   15
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
} UserBindPhoneUUIDReqPkt;

typedef struct _UserBindPhoneUUIDRespPkt   //(0x010b)   16
{
    RespCMDHeader Header;
}UserBindPhoneUUIDRespPkt;

typedef struct _P2P2RegBindUUIDReqPkt   //(0x010c)   637
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
} P2P2RegBindUUIDReqPkt;

typedef struct _P2P2RegBindUUIDRespPkt   //(0x010d)   638
{
    RespCMDHeader Header;
    char AppName[USER_NAME_LEN];
} P2P2RegBindUUIDRespPkt;

typedef struct _UserAddFriendReqPkt   //(0x010e)   31
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
    char FriendAppName[USER_NAME_LEN];
} UserAddFriendReqPkt;

typedef struct _UserAddFriendRespPkt   //(0x010f)  32
{
    RespCMDHeader Header;
    char FriendAppName[USER_NAME_LEN];
    int OnlineStatus;
}UserAddFriendRespPkt;

typedef struct _UserRemoveFriendReqPkt   //(0x0110)   33
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
    char FriendAppName[USER_NAME_LEN];
} UserRemoveFriendReqPkt;

typedef struct _UserRemoveFriendRespPkt   //(0x0111)  34
{
    RespCMDHeader Header;
}UserRemoveFriendRespPkt;

typedef struct _P2P2CLIFriendAddRemoveRetNotifyPkt  // 0x0112  117
{
    ReqCMDHeader Header;
    char ClientUsrName[USER_NAME_LEN];
    int FriendOpt;
} P2P2CLIFriendAddRemoveRetNotifyPkt;

typedef struct _DevShareOptList
{
    int DevChannel;
    int UsrOpt;
    char AppAcceptorName[USER_NAME_LEN];
    char AppAcceptorUID[UID_LEN];
    struct _DevShareOptList *Next;
}DevShareOptList;

typedef struct _REG2P2PDeviceShareAddRemoveNotifyPkt  // 0x0113  326
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    DevShareOptList *ShareChanList;
} REG2P2PDeviceShareAddRemoveNotifyPkt;

/*
    Packet:197
    ˵��:֪ͨ��: ֪ͨDevice��ͨ������ӷ�����߱�ɾ���˷��� (P2PSer -> Device ) 
    CMD:0x0114
 	����(����ӷ����Ǳ�ɾ������)
 	������������Ϣ(��ɾ������ʱ������Ϊ��)
 */
// change by linhh 20161122 : ɾ�� WS_SHARE_OPERATION_UNKNOW ��ƥ���ĵ� WS_SHARE_OPERATION_ADD = 0 
// �ϲ�ö��ShareOperateState ��ws_share_operation ��
typedef enum
{
    WS_SHARE_OPERATION_ADD = 0 ,                /*˽����������Ƶͨ������*/
    WS_SHARE_OPERATION_DEL,                     /*���������ɾ������*/  
    WS_SHARE_OPREATION_CAN,                     /*˽����ȡ����Ƶͨ������*/
    WS_SHARE_OPREATION_REFUSE,                  /*��������߾ܾ����ܷ���*/
    WS_SHARE_OPERATION_ACCEPT,                  /* ��������߽�����Ƶͨ������*/
    WS_SHARE_OPERATION_WAITING_ACCEPT,      	/*˽�������������ȴ����Ѵ���*/    
    WS_SHARE_OPERATION_DEVICE_RESET,      		/*�豸��λ*/      
    WS_SHARE_OPERATION_SERVER_REJECT,			/*������Ϣ���󣬷������ܾ�����add by ronghl 2017-03-30*/
    WS_SHARE_OPETATION_TIMEOUT = 0xC0000012 ,   /*���������ʱ*/
} ws_share_operation;

typedef struct _UpdateShareNotifyPkt            // CMD197 0x0114
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    DevShareOptList *ShareChanList;
} UpdateShareNotifyPkt;


typedef struct _P2P2RegAddFriendReqPkt   //(0x0116)   609
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char AppFriendName[USER_NAME_LEN];
} P2P2RegAddFriendReqPkt;

typedef struct _P2P2RegAddFriendRespPkt   //(0x0117)   610
{
    RespCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppFriendName[USER_NAME_LEN];
    int AppFriendOnline;
} P2P2RegAddFriendRespPkt;

typedef struct _P2P2RegRemoveFriendReqPkt   //(0x0118)   611
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char AppFriendName[USER_NAME_LEN];
} P2P2RegRemoveFriendReqPkt;

typedef struct _P2P2RegRemoveFriendRespPkt   //(0x0119)   612
{
    RespCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppFriendName[USER_NAME_LEN];
} P2P2RegRemoveFriendRespPkt;

typedef struct _UserAddDeviceReqPkt   //(0x0120)   35
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
    char DeviceUID[UID_LEN];
    char DeviceUserName[USER_NAME_LEN];
    char DevicePasswd[PASSWORD_LEN];
}UserAddDeviceReqPkt;

typedef struct _UserAddDeviceRespPkt   //(0x0122)  36
{
    RespCMDHeader Header;
    char          DeviceUID[UID_LEN];
    int           ChanCnt;                              /*add by linhh 20170828 : ����ͨ��������Ϣ */
}UserAddDeviceRespPkt;

typedef struct _UserRemoveDeviceReqPkt   //(0x0123)   37
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
    char DeviceUID[UID_LEN];
}UserRemoveDeviceReqPkt;

typedef struct _UserRemoveDeviceRespPkt   //(0x0124)  38
{
    RespCMDHeader Header;
}UserRemoveDeviceRespPkt;

typedef struct _P2P2RegAddDeviceReqPkt   //(0x0125)   613
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char DeviceUID[UID_LEN];
    char DeviceUserName[USER_NAME_LEN];
    char DevicePasswd[PASSWORD_LEN];
    /*add by linhh 20170831 : ע���������Ҫ֪���û���Ϣ�ſ������豸����������� */
    char P2PServerUID[UID_LEN];
    int  AlarmServerPort;
    char AppUID[UID_LEN];   
} P2P2RegAddDeviceReqPkt;

typedef struct _P2P2RegAddDeviceRespPkt   //(0x0126)   614
{
    RespCMDHeader Header;
    char          DeviceUID[UID_LEN];
    int           ChanCnt;                              /*add by linhh 20170828 : ����ͨ��������Ϣ */
} P2P2RegAddDeviceRespPkt;

typedef struct _P2P2RegRemoveDeviceReqPkt   //(0x0127)   615
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char DeviceUID[UID_LEN];
} P2P2RegRemoveDeviceReqPkt;

typedef struct _P2P2RegRemoveDeviceRespPkt   //(0x0128)   616
{
    RespCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char DeviceUID[UID_LEN];
} P2P2RegRemoveDeviceRespPkt;

typedef struct _Reg2DeviceAddReqPkt   //(0x0129)   68
{
    ReqCMDHeader Header;
    char DeviceUserName[USER_NAME_LEN];
    char DevicePasswd[PASSWORD_LEN];
    char AppName[USER_NAME_LEN];
    char AppUID[UID_LEN];
    char P2PServerUID[UID_LEN];
    char P2PServerIP[IP_STR_LEN];
    int P2PServerPort;                                              
    char AlarmServerIP[IP_STR_LEN];
    int     AlarmServerPort;                                        
} Reg2DeviceAddReqPkt;


typedef struct _Reg2DeviceAddRespPkt   //(0x012a)   69
{
    RespCMDHeader Header;
    char    DeviceUID[UID_LEN];
    char    AppUID[UID_LEN];
    int     DeviceChCnt;                            /* add by linhh 20170831 ������Ƶͨ������ */
} Reg2DeviceAddRespPkt;

typedef struct _UserGetFriendListReqPkt   //(0x0130)   17
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
}UserGetFriendListReqPkt;

typedef struct _FriendList
{
    char AppFriendName[USER_NAME_LEN];
    int onlineStatus;
    struct _FriendList *Next;                                   
}FriendList ;

typedef struct _UserGetFriendListRespPkt   //(0x0131)  18
{
    RespCMDHeader Header;
    FriendList *PtrFriendList;
}UserGetFriendListRespPkt;


typedef struct _FriendInfoList
{
    char FriendUsrName[USER_NAME_LEN];
    int FriendOnline;
    char FriendAliasName[USER_NAME_LEN];
    struct _FriendInfoList *Next;
} FriendInfoList;

typedef struct _UserGetFriendsAliasReqPkt   //(0x0132)   23
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
}UserGetFriendsAliasReqPkt;

typedef struct _UserGetFriendsAliasRespPkt   //(0x0133)  24
{
    RespCMDHeader Header;
	int PktCnt;
	int PktSeq;
    FriendInfoList *PtrFriendInfoList;
}UserGetFriendsAliasRespPkt;


typedef struct _P2P2RegGetFriendListReqPkt   //(0x0134)   619
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
} P2P2RegGetFriendListReqPkt;


typedef struct _DevChannelList
{
    int ChannelID;
    struct _DevChannelList *Next;               
}DevChannelList;

typedef struct _ClientAcceptor
{
    char    ClientUsrName[USER_NAME_LEN];
    // ����ý�������֪ͨP2P ʱ������P2P ����Ҫ���ĸ��û�����֪ͨ
    bool    bNeedStrSend;                                               
    bool    bClientReceived;  // ��¼�����Ƿ����������
   struct _ClientAcceptor *Next;
} ClientAcceptor;


typedef struct _P2P2RegGetFriendListRespPkt   //(0x0135)   620
{
    RespCMDHeader Header;
    int PktCnt;
    int PktSeq;
    char AppName[USER_NAME_LEN];
    FriendInfoList *PtrFriendInfo;
} P2P2RegGetFriendListRespPkt;

typedef struct _UserModifyFriendsAliasReqPkt   //(0x0136)   27
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
    char FriendUsrName[USER_NAME_LEN];
    char FriendAliasName[USER_NAME_LEN];
}UserModifyFriendsAliasReqPkt;

typedef struct _UserModifyFriendsAliasRespPkt   //(0x0137)  28
{
    RespCMDHeader Header;
}UserModifyFriendsAliasRespPkt;


typedef struct _P2P2ModifyFriendAliasNameReqPkt   //(0x0138)   633
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char FriendUserName[USER_NAME_LEN];
    char FriendAliasName[USER_NAME_LEN];
} P2P2RegModifyFriendAliasNameReqPkt;


typedef struct _P2P2RegModifyFriendAliasNameRespPkt   //(0x0139)   634
{
    RespCMDHeader Header;
    char FriendUserName[USER_NAME_LEN];
} P2P2RegModifyFriendAliasNameRespPkt;


typedef struct _UserGetSharedFriendsAliasReqPkt   //(0x013a)   21
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
}UserGetSharedFriendsAliasReqPkt;

typedef struct _SharedChanAliasInfoList
{
    char DeviceUID[UID_LEN];
    int DeviceChannel;
    int DeviceOnline;
    char DeviceUsrName[USER_NAME_LEN];
    char DevicePasswd[USER_NAME_LEN];
    char ShareSponsorName[USER_NAME_LEN];
    char ChanAliasName[USER_NAME_LEN];
    int		DeviceShareStatus;					/*��Ƶͨ������״̬*/
    struct _SharedChanAliasInfoList *Next;          
} SharedChanAliasInfoList;

typedef struct _UserGetSharedFriendsAliasRespPkt   //(0x013b)  22
{
    RespCMDHeader Header;
	int PktCnt;
	int PktSeq;
    SharedChanAliasInfoList *PtrSharedChanList;
}UserGetSharedFriendsAliasRespPkt;

typedef struct _P2P2RegGetSharedChanAliasReqPkt   //(0x013c)   623
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
} P2P2RegGetSharedChanAliasReqPkt;

typedef struct _P2P2RegGetSharedChanAliasRespPkt   //(0x013d)   624
{
    RespCMDHeader Header;
    int PktCnt;
    int PktSeq;
    SharedChanAliasInfoList *PtrChanList;
} P2P2RegGetSharedChanAliasRespPkt;

typedef struct _PrivareDeviceInfoList
{
    char DeviceUID[UID_LEN];
    int DeviceOnlineStatus;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPasswd[PASSWORD_LEN];
    int ChanCnt;
    struct _PrivareDeviceInfoList *Next;         
}PrivareDeviceInfoList;

typedef struct _DeviceInfoList
{
    char DeviceUID[UID_LEN];
    int DeviceOnline;
	char DeviceLoginName[USER_NAME_LEN];
	char DeviceLoginPasswd[PASSWORD_LEN];
    char DeviceAliasName[USER_NAME_LEN];
    int ChanCnt;
    struct _DeviceInfoList *Next;         
} DeviceInfoList;

typedef struct _UserGetPrivareDeviceListReqPkt		///0x013e  19
{
	ReqCMDHeader Header;
	char AppName[USER_NAME_LEN];
	char AppPasswd[PASSWORD_LEN];
	char PhonUUID[UID_LEN];
}UserGetPrivareDeviceListReqPkt;

typedef struct _UserGetPrivareDeviceListRespPkt   //(0x013f)   20
{
    RespCMDHeader Header;
    PrivareDeviceInfoList *PtrDevList;
} UserGetPrivareDeviceListRespPkt;


typedef struct _UserGetPrivareDevicesAliasReqPkt		///0x0140  25
{
	ReqCMDHeader Header;
	char AppName[USER_NAME_LEN];
	char AppPasswd[PASSWORD_LEN];
	char PhonUUID[UID_LEN];
}UserGetPrivareDevicesAliasReqPkt;


typedef struct _UserGetPrivareDevicesAliasRespPkt   //(0x0141)   26
{
    RespCMDHeader Header;
	int 			PktCnt;
	int				PktSeq;
    DeviceInfoList *PtrDevList;
}UserGetPrivareDevicesAliasRespPkt;

typedef struct _UserGetPrivareDeviceAliasReqPkt		///0x011c 60
{
	ReqCMDHeader Header;
	char AppName[USER_NAME_LEN];
	char AppPasswd[PASSWORD_LEN];
	char PhonUUID[UID_LEN];
    char DeviceUUID[UID_LEN];
}UserGetPrivareDeviceAliasReqPkt;

typedef struct _PrivateDeviceChInfoList
{
    int     ChanIndex ;
    char 	ChannelAliasName[USER_NAME_LEN];		                    /*�豸ͨ����ע��Ϣ*/
    struct _PrivateDeviceChInfoList *Next ;
}__attribute__((packed))PrivateDeviceChInfoList;

typedef struct _UserGetPrivareDeviceAliasRespPkt		///0x011d 61
{
	RespCMDHeader               Header;
	int							PktCnt;
	int							PktSeq;
    char                        DeviceUUID[UID_LEN];
    int                         ChanCnt;
    PrivateDeviceChInfoList     *pChanAlias;
}UserGetPrivareDeviceAliasRespPkt;

typedef struct _P2P2RegGetDeviceInfoListReqPkt   //(0x0142)   621
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
} P2P2RegGetDeviceInfoListReqPkt;


typedef struct _P2P2RegGetDeviceInfoListRespPkt   //(0x0143)   622
{
    RespCMDHeader Header;
    int PktCnt;
    int PktSeq;
    char AppName[USER_NAME_LEN];
    DeviceInfoList *PtrDeviceList;
} P2P2RegGetDeviceInfoListRespPkt;

/*˽�����޸��豸��ע�����������޸�ͨ����ע*/
typedef struct _UserModifyDeviceAliasReqPkt   //(0x0144)   29
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhonUUID[UID_LEN];
    char DeviceUID[UID_LEN];
    int DeviceChannel;
    char DevcieAliasName[USER_NAME_LEN];
} UserModifyDeviceAliasReqPkt;


typedef struct _UserModifyDeviceAliasRespPkt   //(0x0145)   30
{
    RespCMDHeader   Header;
} UserModifyDeviceAliasRespPkt;

typedef struct _P2P2RegModifyDeviceAliasNameReqPkt   //(0x0146)   631
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char DeviceUID[UID_LEN];
    int DeviceChannel;
    char DeviceAliasName[USER_NAME_LEN];
} P2P2RegModifyDeviceAliasNameReqPkt;


typedef struct _P2P2RegModifyDeviceAliasNameRespPkt   //(0x0147)   632
{
    RespCMDHeader Header;
    int DeviceChannel;
    char DeviceUID[UID_LEN];
} P2P2RegModifyDeviceAliasNameRespPkt;


typedef struct _SharingChanList
{
    char          DevUID[UID_LEN];
    WS_S32   chanIndex ;                                           // ������Ƶͨ����
    int      ChanOnline;                                         // �Ӵ������ 0 ��ʾ���ߣ� 1 ��ʾ����
    char    ChanAcceptorName[USER_NAME_LEN];
    int      ChanShareStatus;
    struct _SharingChanList *Next;                
} SharingChanList;


typedef struct _UserGetSharingChanListReqPkt   //(0x0148)   120
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
	char PhonUUID[UID_LEN];
} UserGetSharingChanListReqPkt;


typedef struct _UserGetSharingChanListRespPkt   //(0x0149)   121
{
    RespCMDHeader Header;
	int 	PktCnt;
	int 	PktSeq;
    SharingChanList *pShareChanList;
} UserGetSharingChanListRespPkt;


typedef struct _P2P2RegGetSharingChanListReqPkt   //(0x014a)   635
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
} P2P2RegGetSharingChanListReqPkt;


typedef struct _P2P2RegP2P2RegGetSharingChanListRespPkt   //(0x014b)   636
{
    RespCMDHeader Header;
    int PktCnt;
    int PktSeq;
    char AppUID[UID_LEN];
    SharingChanList *PtrChanList;
} P2P2RegP2P2RegGetSharingChanListRespPkt;

typedef struct _MissPacketList
{
	int PacketNo;
	struct _MissPacketList* Next;
}MissPacketList;

typedef struct _ConfigFileInfo
{
	int 	ConfigUploadTime;
	int 	ConfigFileSize;
	char 	ConfigFileName[FILE_NAME_LEN];
	struct _ConfigFileInfo* pNext;
}ConfigFileInfo;

typedef struct _UserConfigFileInfo
{
	int 	ConfigUploadTime;
	int 	ConfigFileSize;
	struct _UserConfigFileInfo* Next;
}UserConfigFileInfo;

//0x014c  232
typedef struct _UserGetConfigFileListReqPkt
{
	ReqCMDHeader 	Header;
	char 			AppUserName[USER_NAME_LEN];
	char			AppPassword[PASSWORD_LEN];
	char 			PhoneUUID[UID_LEN];
}UserGetConfigFileListReqPkt;

//0x014d	233
typedef struct _UserGetConfigFileListRespPkt
{
	RespCMDHeader 	Header;
	UserConfigFileInfo* pConfigFileList;
}UserGetConfigFileListRespPkt;

// 0x014e  234
typedef struct _UserConfigFileUploadReqPkt
{
	ReqCMDHeader 	Header;
	char 			AppUserName[USER_NAME_LEN];
	char 			AppPassword[PASSWORD_LEN];
	char 			PhoneUUID[UID_LEN];
	int 			ConfigFileSize;
}UserConfigFileUploadReqPkt;

//0x014f  235
typedef struct _UserConfigFileUploadRespPkt
{
	RespCMDHeader 	Header;
	char 			ConfigUploadServerIP[IP_STR_LEN];
	int 			ConfigUploadServerPort;
	int 			ConfigUploadSessionID;
}UserConfigFileUploadRespPkt;


//0x0150   	236
typedef struct _UserConfigUploadResultNotifyPkt
{
	ReqCMDHeader 	Header;
	int				PktCnt;		//add by ronghl 20170914
	int				PktSeq;
	int 			ConfigUploadSessionID;
	int 			ConfigUploadResult;
	MissPacketList* pMissConfigPacket;
}UserConfigUploadResultNotifyPkt;

//0x0152 237
typedef struct _UserDownLoadConfigReqPkt
{
	ReqCMDHeader 	Header;
	char 			AppUserName[USER_NAME_LEN];
	char 			AppPassword[PASSWORD_LEN];
	char 			PhoneUUID[UID_LEN];
	int 			ConfigUploadTime;
}UserDownloadConfigReqPkt;

//0x0153 237
typedef struct _UserDownLoadConfigRespPkt
{	
	RespCMDHeader		Header;
	char 				ConfigServerIP[IP_STR_LEN];
	int	 				ConfigServerPort;
	int					ConfigDownloadSessionID;
}UserDownLoadConfigRespPkt;

//0x0154 237
typedef struct _UserStartupConfigFileSendNotifyPkt
{
	ReqCMDHeader		Header;
	char 				AppUserName[USER_NAME_LEN];
	char 				AppPassword[PASSWORD_LEN];
	char				PhoneUUID[UID_LEN];
	int 				ConfigDownloadSessionID;
}UserStartupConfigFileSendNotifyPkt;

//0x0156 240
typedef struct _P2P2UserConfigSendDoneNotifyPkt
{
	RespCMDHeader		Header;
	int 				ConfigDownloadSessionID;
}P2PUserConfigSendDoneNotifyPkt;

//0x0158		241
typedef struct _User2P2PConfigDonwloadConfirmNotifyPkt
{
	ReqCMDHeader 			Header;
	int 					PktCnt;
	int 					PktSeq;
	char 					AppUserName[USER_NAME_LEN];
	char 					AppPassword[PASSWORD_LEN];
	char 					PhoneUUID[UID_LEN];
	int 					ConfigDownloadSessionID;
	int 					ConfigDownloadResult;
	MissPacketList*			pMissPacket;
}User2P2PConfigDonwloadConfirmNotifyPkt;

//0x015a	670
typedef struct _P2P2RegGetConfigFileListReqPkt
{
	ReqCMDHeader 	Header;
	char 			AppUserName[USER_NAME_LEN];
	char 			AppPassword[PASSWORD_LEN];
}P2P2RegGetConfigFileListReqPkt;


//0x015b  	671
typedef struct _P2P2RegGetConfigFileListRespPkt
{
	RespCMDHeader 	Header;
	int 			PktCnt;
	int 			PktSeq;
	char 			AppUserName[USER_NAME_LEN];
	ConfigFileInfo* pConfigFileList;
}P2P2RegGetConfigFileListRespPkt;

//0x015c	672
typedef struct _P2P2RegConfigUploadNotifyPkt
{
	ReqCMDHeader 	Header;
	char 			AppUserName[USER_NAME_LEN];
	char			AppPassword[PASSWORD_LEN];
	char			P2PServerIP[IP_STR_LEN];
	int 			P2PServerPort;
	char 			P2PServerUID[UID_LEN];
	char			ConfigFileName[FILE_NAME_LEN];
	int 			ConfigUploadTime;
	int 			ConfigFileSize;
}P2P2RegConfigUploadNotifyPkt;

/*0x015d �û��޸�˽���豸���� 242 */
typedef struct _UserChangeDevicePwdReqPkt
{
	ReqCMDHeader 	Header;
	char 			AppName[USER_NAME_LEN];
	char 			AppPasswd[PASSWORD_LEN];
	char 			PhoneUUID[UID_LEN];
    char            DeviceUUID[UID_LEN];
	char            DeviceLoginName[USER_NAME_LEN];
	char            DeviceNewLoginPasswd[PASSWORD_LEN];
}UserChangeDevicePwdReqPkt;

/*0x015e �û��޸�˽���豸����Ӧ�� 243 */
typedef struct _UserChangeDevicePwdRespPkt
{	
	RespCMDHeader		Header;
}UserChangeDevicePwdRespPkt;

/*0x0160 P2P�������޸�˽���豸���� 673 */
typedef struct _P2pChangeDevicePwdReqPkt
{
	ReqCMDHeader 	Header;
	char 			AppUserName[USER_NAME_LEN];
	char 			AppUID[UID_LEN];
    char            DeviceUUID[UID_LEN];
	char            DeviceLoginName[USER_NAME_LEN];
    char            DeviceOldLoginPasswd[PASSWORD_LEN];
	char            DeviceNewLoginPasswd[PASSWORD_LEN];
}P2pChangeDevicePwdReqPkt;

/*0x0161 P2P�������޸�˽���豸����Ӧ�� 674 */
typedef struct _P2pChangeDevicePwdRespPkt
{	
	RespCMDHeader		Header;
}P2pChangeDevicePwdRespPkt;

//************************************************************//
//add by ronghl 2017-02-22   end: add fro config file upload
//************************************************************//

//0x0115    
typedef struct _RegP2PUserResetPasswordNotify
{
	ReqCMDHeader 		Header;
	char 				AppUserName[USER_NAME_LEN];
	char 				AppUserUID[UID_LEN];
}RegP2PUserResetPasswordNotify;

//0x015e
typedef struct _StrSerFriendshipDeleteNotifyPkt
{
	ReqCMDHeader  			Header;
	char 					AppUserName[USER_NAME_LEN];
	char    				FriendUserName[USER_NAME_LEN];
}StrSerFriendshipDeleteNotifyPkt;

typedef struct _ChanShareAcceptorList
{
    char AppUID[UID_LEN];
    char AppUserName[USER_NAME_LEN];
    int DeviceChannelID;
    struct _ChanShareAcceptorList *Next;        
} ChanShareAcceptorList;

typedef struct _MDPushChanList
{
    int ChannelID;
    struct _MDPushChanList *Next;        
} MDPushChanList;


typedef struct _DeviceLoginReqPkt   //(0x0200)   64
{
    ReqCMDHeader Header;
    char DeviceUserName[TRAN_USERNAME_LEN];     
    char DevicePasswd[TRAN_PASSWD_LEN];     
    char DeviceUID[UID_LEN];
    char OwnerAppUID[UID_LEN];   /* ˽���ߵ�UID */
    int ChanCnt;    //�豸֧����Ƶͨ������
    int  DeviceResetFlag;	/* �豸��λ��־��0:��ʾû�и�λ��1:��ʾ������λ */
} __attribute__((packed))DeviceLoginReqPkt;                                     

typedef struct _DeviceLoginRespPkt   //(0x0201)   65        // 0x0218 86
{
    RespCMDHeader Header;   //'��¼Ӧ�����״̬��,�����ж��Ƿ���Ҫ���Ϊ���豸'..
    char P2PserverUID[UID_LEN];
    char P2PServerIP[IP_STR_LEN];
    int P2PServerPort;                               
    char AlarmServerIP[IP_STR_LEN];
    int     AlarmServerPort;
    char	PrivateUserName[USER_NAME_LEN];
    char	PrivateUserUUID[UID_LEN];
    ChanShareAcceptorList *PtrChanList;
} DeviceLoginRespPkt;

typedef struct _P2P2RegDeviceIPStatusNotifyPkt   //(0x0204)   669
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    int DeviceOnline;
    char DeviceWANIP[IP_STR_LEN];
    int DeviceWANPort;             
    char DeviceLANIP[IP_STR_LEN];				
	int DeviceLANPort;
} P2P2RegDeviceIPStatusNotifyPkt;

typedef struct _Reg2P2PDeviceStatusNotifyPkt   //(0x0206)   305
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    char PrivateAppUID[UID_LEN];
    int DeviceOnline;
    ChanShareAcceptorList *PtrChanList;
} Reg2P2PDeviceStatusNotifyPkt;

typedef struct _P2P2CLIDeviceLoginRetNotifyPkt  // 0x0208  39
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    int OnlineStatus;
}P2P2CLIDeviceLoginRetNotifyPkt;

/**0x0209 user online status change noify ,when user **/
typedef struct  _P2PDevUserOnlineStatusNotifyPkt
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
	char AppUserName[USER_NAME_LEN];
	char AppUserUID[UID_LEN];
 }P2PDevUserOnlineStatusNotifyPkt;

typedef struct _UserStartP2PConnectionReqPkt   //0x020a   74
{
	ReqCMDHeader Header;
	char AppName[USER_NAME_LEN];
	char AppPasswd[PASSWORD_LEN];
	char PhonUUID[UID_LEN];
	char LanIP[IP_STR_LEN];
	int LanPort;
	char DeviceUID[UID_LEN];
	char DeviceUserName[USER_NAME_LEN];
	char DevicePasswd[PASSWORD_LEN];
	char MAC[MACADDR_LEN];				/* App��MAC��ַ��Ϣ */
}UserStartP2PConnectionReqPkt;

typedef struct _UserStartP2PConnectionRespPkt   //(0x020b)   75
{
    RespCMDHeader Header;
    char DevWANIP[IP_STR_LEN];
    int DevWANPort;
    char DevLANIP[IP_STR_LEN];
    int DevLANPort;
    int P2PSessionID;
	char MAC[MACADDR_LEN];		/* �豸�˵�MAC��ַ��Ϣ */
} UserStartP2PConnectionRespPkt;

typedef struct _UserStartRelayConnectionReqPkt    //0x020c  79
{
    ReqCMDHeader Header;
    char AppUserName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhonUUID[UID_LEN];
    char DeviceUID[UID_LEN];
    char DeviceUserName[USER_NAME_LEN];
    char DevicePasswd[PASSWORD_LEN];
	char	MAC[MACADDR_LEN];
	char 	LocalIP[IP_STR_LEN];
}UserStartRelayConnectionReqPkt;

typedef struct _UserStartRelayConnectionRespPkt   //(0x020d)   80
{
    RespCMDHeader Header;
    int RelaySessionID;
    char RelayIP[IP_STR_LEN];
    int RelayPort;
} UserStartRelayConnectionRespPkt;

/*
    Packet:82
    ˵��:�ͻ���������Relay�Ự�������
    CMD:0x020e
*/
typedef struct _ClientRelayReqPkt
{
    ReqCMDHeader Header;
    char ClientName[USER_NAME_LEN];
    char ClientPassword[PASSWORD_LEN];
    int RelaySessionID;
    char DeviceUID[UID_LEN];
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
} ClientRelayReqPkt;


/*
    Packet:87
    ˵��:�ͻ���������Relay�Ự����Ӧ��
    CMD:0x020f
*/
typedef struct _ClientRelayRespPkt
{
    RespCMDHeader Header;
    int RelaySessionID;
} ClientRelayRespPkt;

typedef struct _P2P2ClientRelayStopNotifyPkt     // 0x0210   83
{
    ReqCMDHeader Header;
    int RelaySessionID;
    int ReasonStatus;
}P2P2ClientRelayStopNotifyPkt;

typedef struct _DeviceGetShareReqPkt   //(0x0217)   85
{
    ReqCMDHeader Header;
    char    DeviceUID[UID_LEN];
    char    OwnerAppUID[UID_LEN];   /* ˽���ߵ�UID */
}DeviceGetShareReqPkt;

typedef struct _DeviceLoginNotifyPkt     // 0x0219   107
{
    ReqCMDHeader Header;
    char    DeviceUID[UID_LEN];

    char    AppUID[UID_LEN];                                    /*˽����UID��˽�����û���*/
    char    AppUserName[USER_NAME_LEN];

    int     LoginMode ;                                         /*��¼ģʽ��0��ʾ��ȷ��¼��1��ʾ�쳣��¼*/
}DeviceLoginNotifyPkt;


/*
    Packet:641
    ˵��: Request get Relay Server IP port
    CMD:0x021c
*/
typedef struct _GetRelayServerReqPkt
{
    ReqCMDHeader Header;
    char P2PServerUID[UID_LEN];
} GetRelayServerReqPkt;

/*
    Packet:642
    ˵��: Get Relay Server IP port request's response
    CMD:0x021d
*/
typedef struct _GetRelayServerRespPkt
{
    RespCMDHeader Header;
    char P2PServerUID[UID_LEN];
    char StreamSerIP[IP_STR_LEN];
    int StreamSerPort;
} GetRelayServerRespPkt;


/*
    Packet:643
    ˵��:����Relay�Ự����
    CMD:0x021e
*/
typedef struct _RelaySessionReqPkt
{
    ReqCMDHeader Header;
    char ClientName[USER_NAME_LEN];
    char ClientUID[UID_LEN];                            /* �����û���UUID��Ϣ����V2.0ϵͳ����ý���������֪���û���UUID��Ϣ*/
    char ClientPassword[PASSWORD_LEN];
    char P2PServerUID[UID_LEN];
} RelaySessionReqPkt;


/*
    Packet:644
    ˵��:����Relay�Ự��Ӧ
    CMD:0x021f
*/
typedef struct _RelaySessionRespPkt
{
    RespCMDHeader Header;
    char P2PServerID[UID_LEN];
    int RelaySessionID;
    char RelayServerIP[IP_STR_LEN];
    int RelayServerPort;
} RelaySessionRespPkt;

/*0x054a INDEX = 135 �û�������ѷ�����������*/
typedef struct _MessageDownloadReqPkt
{
    ReqCMDHeader    Header;
    char            ClientName[USER_NAME_LEN];              /*�������û���*/
    char            GroupID[UID_LEN];
    int             SessionID;                              /* ��������ỰID*/
} MessageDownloadReqPkt;

/*0x054b INDEX=136 �û�������ѷ����������ص�Ӧ���*/
typedef struct _MessageDownloadRespPkt
{
    RespCMDHeader   Header;
    char            GroupID[UID_LEN];
    int             SessionID;                              /* ��������ỰID*/
    char            MessageServerIP[IP_STR_LEN];
    int             MessageServerPort;                     /* ��ý���������IP��˿���Ϣ */
} MessageDownloadRespPkt;


/*
    Packet:84
    ˵��:�豸��������Relay�Ự�������
    CMD:0x0226
*/
typedef struct _DeviceRelayReqPkt
{
    ReqCMDHeader Header;
    char ClientName[USER_NAME_LEN];     //�������ӵĿͻ��˵��û���
    char ClientUID[UID_LEN];        //  Client��UID
    char DeviceUID[UID_LEN];            //  �豸UID
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;            //P2P�ỰID����Relay�ỰID
} __attribute__((packed))DeviceRelayReqPkt;                             /*change by linhh 20170608 */


/*
    Packet:89
    ˵��:�豸��������Relay�Ự����Ӧ��
    CMD:0x0227
*/
typedef struct _DeviceRelayRespPkt
{
    RespCMDHeader Header;
    int RelaySessionID;
} DeviceRelayRespPkt;

typedef struct _UserSetMsgPushConfigReqPkt   //0x0400   126
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhoneUUID[UID_LEN];
    int PushAlarm;
    int MDAlarmPush;
    int PushFriendMsg;
    int PushChanSharingMsg;
    int PushFileMsg;
}UserSetMsgPushConfigReqPkt;

typedef struct _UserSetMsgPushConfigRespPkt    // 0x0401  127
{
    RespCMDHeader Header;
} UserSetMsgPushConfigRespPkt;

typedef struct _UserGetMsgPushConfigReqPkt   // 0x0402  124
{
	ReqCMDHeader Header;
	char AppName[USER_NAME_LEN];
	char AppPasswd[PASSWORD_LEN];
	char PhoneUUID[UID_LEN];
}UserGetMsgPushConfigReqPkt;

typedef struct _UserGetMsgPushConfigRespPkt    // 0x0403  125
{
    RespCMDHeader Header;
    int AlarmPushStatus;
    int MDAlarmPushStatus;
    int FriendMsgPushStatus;
    int ShareMsgPushStatus;
    int FileMsgPushStatus;
} UserGetMsgPushConfigRespPkt;


/*
    Packet: 665
    CMD:0x0406
*/
typedef struct _P2P2RegModifyAppPushMsgConfigReqPkt
{
    ReqCMDHeader Header;
    int PushAlarm;
    int MDAlarmPush;
    int PushFriendMsg;
    int PushChanSharingMsg;
    int PushFileMsg;
    char AppUserName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
} P2P2RegModifyAppPushMsgConfigReqPkt;


typedef struct _CliP2PRelayReqPkt
{
	ReqCMDHeader Header;
	char AppUserName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
	char PhonUUID[UID_LEN];
	char DeviceUID[UID_LEN];
	char DevcieUserName[USER_NAME_LEN];
	char DevicePasswd[PASSWORD_LEN];
}CliP2PRelayReqPkt;


/*
    Packet: 666
    CMD:0x0407
*/
typedef struct _P2P2RegModifyAppPushMsgConfigRespPkt
{
    RespCMDHeader Header;
    char AppUserName[USER_NAME_LEN];
} P2P2RegModifyAppPushMsgConfigRespPkt;

/*
    Packet: 667
    CMD:0x0408
*/
typedef struct _P2P2RegGetAppPushMsgConfigReqPkt
{
    ReqCMDHeader Header;
    char AppUserName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
} P2P2RegGetAppPushMsgConfigReqPkt;

/*
    Packet: 668
    CMD:0x0409
*/
typedef struct _P2P2RegGetAppPushMsgConfigRespPkt
{
    RespCMDHeader Header;
    char AppUserName[USER_NAME_LEN];
    int PushAlarm;
    int MDAlarmPush;
    int PushFriendMsg;
    int PushChanSharingMsg;
    int PushFileMsg;
} P2P2RegGetAppPushMsgConfigRespPkt;


struct SubscribeChange  //0x040a  339
{
    int PktType;
    int Cmd;
    int SeqNo;
    char AppName[48];
    int PushAlarm;
};


typedef struct _Alarm2P2PPushAlarmMsgNotifyPkt   //0x040a  339
{
    ReqCMDHeader Header;
    char  DevUID[UID_LEN];
    char  AppUID[UID_LEN];
    int AlarmType;
    int AlarmStatus;
    int AlarmTime;
    int AlarmChan;
    int AlarmCount;;
}Alarm2P2PPushAlarmMsgNotifyPkt;

typedef struct _UserConfig
{
    char ClientName[USER_NAME_LEN];
    char ClientUID[UID_LEN];
    int  ClientOnlineStatus;     //OFFLINE:����
    int  PowerMessagePushSwitch;
    char P2PServerUID[UID_LEN];
#if 0
    struct _UserConfig *Next;               // change by linhh 20161125 
#endif
} UserConfig;

typedef struct _P2PConfig
{
    char P2PServerUID[UID_LEN];
    char P2PServerIP[IP_STR_LEN];
    int P2PServerPort;                          // change by linhh 20161125 
    struct _P2PConfig *Next;
}P2PConfig;


typedef struct _P2P2ClientDeviceAlarmMsgNotifyPkt     // 0x0410   63
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    int DeviceChannelID;
    int AlarmType;
    int AlarmTime;
    int AlarmTotalCnt;
}P2P2ClientDeviceAlarmMsgNotifyPkt;


/*
    Packet:335
    ˵��:�״�����֪֪ͨͨ���������û�
    CMD : 0x0412
*/
typedef struct _userConfigNotifyPkt
{
    ReqCMDHeader Header;
    UserConfig *Configs;
} UserConfigNotifyPkt;

/*
    Packet:343
    ˵��:�״�����֪֪ͨͨ�������ߵ�P2PServer��Ϣ
    CMD : 0x0413
*/
typedef struct _p2pConfigNotifyPkt
{
    ReqCMDHeader Header;
    P2PConfig *Configs;
} P2PConfigNotifyPkt;


/*
    Packet:1001
    ˵��:��ע�������֮���������
    CMD:0x0418
*/
typedef struct _StrSerRegSerHBPkt
{
    ReqCMDHeader Header;
    char                StreamServerIP[IP_STR_LEN];
    int         StreamServerPort;                           // change by linhh 20161125 
    char                StreamServerUID[UID_LEN];
    int                  HBSeqNo;
	//add by ronghl 2017-01-13 start
	int 	UploadBand;
	int 	DownloadBand;
	char 	StreamServerTime[64];
	//add by ronghl 2017-01-13 end
} StrSerRegSerHBPkt;


struct P2PStatusChange  // 0x041a   337
{
    int PktType;
    int Cmd;
    int SeqNo;
    char P2PUID[48];
    int P2PStatus;
    char P2PIp[20];
    int P2PPort;
	//add by ronghl 2017-03-31 
	char OldP2PIP[IP_STR_LEN];
	int OldP2PPort;
};

typedef struct _UserStartShareChannelReqPkt            ///0x0500  41
{
    ReqCMDHeader Header;
    char AppName[USER_NAME_LEN];
    char AppPasswd[PASSWORD_LEN];
    char PhonUUID[UID_LEN];
    char DeviceUID[UID_LEN];
    int DeviceChannelID;
    char DeviceUserName[USER_NAME_LEN];
    char DevicePasswd[PASSWORD_LEN];
    char FriendAppName[USER_NAME_LEN];
}UserStartShareChannelReqPkt;

typedef struct _UserStartShareChannelRespPkt   //  0x0501  42
{
    RespCMDHeader Header;
} UserStartShareChannelRespPkt;


typedef struct _P2P2ClientSharingChannelNotifyPkt     // 0x0502   137
{
    ReqCMDHeader Header;
    char ClientUserName[USER_NAME_LEN];
    char DeviceUID[UID_LEN];
    int DeviceChannelID;
    char DevLoginUsrName[USER_NAME_LEN];
    char DevLoginPasswd[PASSWORD_LEN];
}P2P2ClientSharingChannelNotifyPkt;


typedef struct _P2P2ClientStartShareChannelReqPkt   //  0x0504  43
{
    ReqCMDHeader Header;
    char ClientUsrName[USER_NAME_LEN];
    char DeviceUID[UID_LEN];
    int DeviceChannelID;
    char DevLoginUsrName[USER_NAME_LEN];
    char DevLoginPasswd[PASSWORD_LEN];
} P2P2ClientStartShareChannelReqPkt;

typedef struct _P2P2ClientStartShareChannelRespPkt   //  0x0505  44
{
    RespCMDHeader Header;
} P2P2ClientStartShareChannelRespPkt;


/* �����������ӷ���ͨ�����߾ܾ�����ͨ�� */
typedef struct _UserProcessShareReqPkt  // 0x0506  45
{
	ReqCMDHeader Header;
	char AppName[USER_NAME_LEN];
	char AppPasswd[PASSWORD_LEN];
	char PhoneUUID[UID_LEN];
	char FriendAppName[USER_NAME_LEN];
	char DeviceUID[UID_LEN];
	int DeviceChannelID;
	int OperationType;
}UserProcessShareReqPkt;

typedef struct _UserProcessShareRespPkt   //  0x0507  46
{
    RespCMDHeader Header;
	char            DeviceUID[UID_LEN];
	int             DeviceChannelID;
    char            DevLoginUsrName[USER_NAME_LEN];
    char            DevLoginPasswd[PASSWORD_LEN];
    int             OnlineStatus;                           /*�豸������Ϣ: 0 ���ߣ� 1Ϊ����*/
} UserProcessShareRespPkt;


/* ���������ɾ���ѽ��ܵķ���ͨ�� */
typedef struct _UserRemoveSharedChanReqPkt  //0x0508  48
{
	ReqCMDHeader Header;
	char AppName[USER_NAME_LEN];
	char AppPasswd[PASSWORD_LEN];
	char PhoneUUID[UID_LEN];
	char FriendAppName[USER_NAME_LEN];
	char DeviceUID[UID_LEN];
	int DeviceChannelID;
}UserRemoveSharedChanReqPkt;

typedef struct _UserRemoveSharedChanRespPkt   //  0x0509  49
{
    RespCMDHeader Header;
} UserRemoveSharedChanRespPkt ;


/* ˽����ȡ������ͨ�� */
typedef struct _UserCancelSharingChanReqPkt    //0x050a  50
{
	ReqCMDHeader Header;
	char AppName[USER_NAME_LEN];
	char AppPasswd[PASSWORD_LEN];
	char PhoneUUID[UID_LEN];
	char DeviceUID[UID_LEN];
	int DeviceChannelID;
	char FriendAppName[USER_NAME_LEN];
}UserCancelSharingChanReqPkt;

typedef struct _UserCancelSharingChanResqPkt    //0x050b  51
{
	RespCMDHeader Header;
}UserCancelSharingChanRespPkt;

typedef struct _P2P2ClientShareCancelNotifyPkt     // 0x050c   52
{
    ReqCMDHeader Header;
    char ClientUserName[USER_NAME_LEN];
    char DeviceUID[UID_LEN];
    int DeviceChannelID;
}P2P2ClientShareCancelNotifyPkt;


typedef struct _P2P2ClientShareProcessedRetNotifyPkt     // 0x050e   47
{
    ReqCMDHeader Header;
    char ClientUserName[USER_NAME_LEN];
    char DeviceUID[UID_LEN];
    int DeviceChannelID;
    int ShareOptResult;
}P2P2ClientShareProcessedRetNotifyPkt;

/*
    Packet: 657
    CMD:0x0510
*/
typedef struct _P2P2RegShareChannelNotifyPkt
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    int DeviceChannel;
    char DeviceUserName[USER_NAME_LEN];
    char DevicePasswd[PASSWORD_LEN];
    char PrivateAppUserName[USER_NAME_LEN];
    char PrivateAppUID[UID_LEN];
    char AcceptorAppUserName[USER_NAME_LEN];
} P2P2RegShareChannelNotifyPkt;


/*
    Packet: 659
    CMD:0x0512
*/
typedef struct _P2P2RegCancelSharedChannelNotifyPkt
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    int DeviceChannel;
    char AcceptorAppUserName[USER_NAME_LEN];
    char PrivateAppUserName[USER_NAME_LEN];
    char PrivateAppUID[UID_LEN];
} P2P2RegCancelSharedChannelNotifyPkt;



/*
    Packet: 661
    CMD:0x0514
*/
typedef struct _P2P2RegProcessSharedChannelNotifyPkt
{
    ReqCMDHeader Header;
    char   DeviceUID[UID_LEN];
    int     DeviceChannel;
    char   AcceptorAppUserName[USER_NAME_LEN];
    char   PrivateAppUserName[USER_NAME_LEN];
    int     OperateStatus;
} P2P2RegProcessSharedChannelNotifyPkt;

/*
    Packet: 319
    CMD:0x0516
*/
typedef struct _Reg2P2PSharingChannelRequestNotifyPkt
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    char ShareSponsorName[USER_NAME_LEN];
    char ShareAcceptorName[USER_NAME_LEN];
    int DevChanID;
    char DevLoginUsrName[USER_NAME_LEN];
    char DevLoginPasswd[PASSWORD_LEN];
} Reg2P2PSharingChannelRequestNotifyPkt;

/*
    Packet: 331
    ��������ȡ��ͨ������--��RegSer����P2PSer��֪ͨ��
    CMD:0x0518
*/
typedef struct _Reg2P2PRemoveSharedChannelNotifyPkt
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    char ShareSponsorName[USER_NAME_LEN];
    char ShareAcceptorName[USER_NAME_LEN];
    int DevChanID;
} Reg2P2PRemoveSharedChannelNotifyPkt;

/*
    Packet: 333
    ��������ߵĲ������֪ͨ..
    CMD:0x051a
*/
typedef struct _Reg2P2PShareChanResultNotifyPkt
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    char ShareSponsorName[USER_NAME_LEN];
    char ShareAcceptorName[USER_NAME_LEN];
    int DevChanID;
    int ShareResult;
} Reg2P2PShareChanResultNotifyPkt;

typedef struct _SharedChanList
{
    char DeviceUID[UID_LEN];
    char ShareSponsorName[USER_NAME_LEN];
    char ShareAcceptorName[USER_NAME_LEN];
    int DevChanID;
    struct _SharedChanList *Next;               // change by linhh 20161125 
} SharedChanList;

/*
    Packet: 325
    ǿ��ȡ��ͨ������
    CMD:0x051c
*/
typedef struct _Reg2P2PCancelShareChansResultNotifyPkt
{
    ReqCMDHeader Header;
    SharedChanList *PChanList;
} Reg2P2PCancelShareChansResultNotifyPkt;

/*
    Packet: 662
    CMD:0x051e
*/
typedef struct _P2P2RegRefuseSharedChannelReqPkt
{  
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    int DeviceChannel;
    char AcceptorAppUserName[USER_NAME_LEN];
    char PrivateAppUserName[USER_NAME_LEN];
    int OperateStatus;       //����ģʽ  0��� 1 �ܾ�
} P2P2RegRefuseSharedChannelReqPkt;

typedef struct _P2P2RegRefuseSharedChannelRespPkt    //  663  0x051f
{  
    RespCMDHeader Header;
    char ShareSponsorName[USER_NAME_LEN];
    char ShareAcceptorName[USER_NAME_LEN];
    char DeviceUID[UID_LEN];
    int DeviceChannel;
} P2P2RegRefuseSharedChannelRespPkt;


/* Client�����ļ�/��Ϣ���͵ĻỰ */
typedef struct _UserShareFileMsgReqPkt   // 0x0530    128
{
	ReqCMDHeader Header;
	char AppName[USER_NAME_LEN];
	char AppPasswd[PASSWORD_LEN];
	char PhoneUUID[UID_LEN];
        
    char        GroupID[UID_LEN];
	int         FileType;
	int         FileSize;
	char        FileName[FILE_NAME_LEN];
}UserShareFileMsgReqPkt;

typedef struct _UserShareFileMsgRespPkt    //  0x0531  129
{  
    RespCMDHeader Header;
    char StreamServerIP[IP_STR_LEN];
    int  StreamServerPort;
    int  FileSessionID;
    char GroupID[UID_LEN];
} UserShareFileMsgRespPkt;


/*
    Packet:1003
    ˵��:֪ͨ���ݷ��Ͷ�Client�ļ����ܽ��
    CMD:0x0532
*/

typedef struct _MessageUploadConfirmNotifyPkt
{
    ReqCMDHeader Header;
    int MessageForwardSessionID;
    int CompleteFlag;				
    MissPacketList* MissPackets;
} MessageUploadConfirmNotifyPkt;

///0x0534    130
typedef struct _CliP2PMessageUploadDoneNotifyPkt
{
	ReqCMDHeader Header;
	char    AppName[USER_NAME_LEN];
	int     FileSessionID;
    char    GroupID[UID_LEN];
}CliP2PMessageUploadDoneNotifyPkt;

/*
    Packet:649
    ˵��:��������Ϣ�����
    CMD:0x0536
*/
typedef struct _MessageForwardReqPkt
{
    ReqCMDHeader Header;
    char P2PServerUID[UID_LEN];
    int P2PServerTaskID;
    char ClientName[USER_NAME_LEN];
    ClientAcceptor *PtrAcceptorList;
    char FileName[FILE_NAME_LEN];
    int FileSize;
    int FileType;
} MessageForwardReqPkt;

typedef struct _FileMsgList
{
    int FileType;
    int MsgCnt;
    struct _FileMsgList *Next;      // change by linhh 20161125 
} FileMsgList;


typedef struct _P2P2ClientFileMessageNotifyPkt    // 0x0538   59  ������Ϣ..
{
    ReqCMDHeader Header;
    char ClientName[USER_NAME_LEN];
    FileMsgList *PtrMsgList;
} P2P2ClientFileMessageNotifyPkt;

/*
    Packet:650
    ˵��:��������Ϣ�������Ӧ��
    CMD:0x0537
*/
typedef struct _MessageForwardRespPkt
{
    RespCMDHeader Header;
    char P2PServerUID[UID_LEN];
    int P2PServerTaskID;
    int StreamServerSessionID;
    int      FileUploadTime;    //change by liujl 20161208
    char StreamServerIP[IP_STR_LEN];
    int StreamServerPort;
} MessageForwardRespPkt;

typedef struct _P2P2OnlineClientsFileMessageNotifyPkt    // 0x053a   57  ������Ϣ..
{
    ReqCMDHeader Header;
    char StreamServerIP[IP_STR_LEN];
    int StreamServerPort;
    int FileMsgSessionID;
    char FileSponsorUsrName[USER_NAME_LEN];
    int FileType;
    time_t FileUploadTime;
    char FileName[128];
    int FileSize;
    char        GroupID[UID_LEN];
} P2P2OnlineClientsFileMessageNotifyPkt;

/*
    Packet:58
    ˵��:Client B���������Ϣ
    CMD:0x053c
*/
typedef struct _ClientRecieveMessageNotifyPkt
{
    ReqCMDHeader Header;
    int MessageForwardSessionID;
    char RecieverName[USER_NAME_LEN];
} ClientRecieveMessageNotifyPkt;

/*
    ������ʱ�ò���
    Packet:653
    ˵��:P2P Notify Stream Server recv client list
    CMD:0x0540
*/
typedef struct _MessageRecieverForwarNotifyPkt
{
    ReqCMDHeader Header;
    int FileSessionID;
    char SenderP2PServerUID[UID_LEN];
    char SenderClientName[USER_NAME_LEN];
    ClientAcceptor *PtrAcceptorList;				// change by linhh 20161109 : ά��֮ǰ�����ݽṹ����
} MessageRecieverForwardNofityfPkt;

/*
    Packet:1007
    ˵��:֪ͨ�ļ������߽����ļ�֪ͨ��Ϣ
    CMD:0x0542
*/
typedef struct _MessageRecieveNotifyPkt
{
    ReqCMDHeader Header;
    char    SendClientName[USER_NAME_LEN];
    int      MessageForwardSessionID;
    char    FileName[FILE_NAME_LEN];
    int      FileType;
    int      FileSize;
    int      FileUploadTime;    //change by liujl 20161208
    char    StreamServerIP[IP_STR_LEN];
    int      StreamServerPort;
    ClientAcceptor *PtrAcceptorList;
} MessageRecieveNotifyPkt;


typedef struct _Reg2P2PStreamServerInfoNotifyPkt   //0x0544
{
    ReqCMDHeader Header;
    char StreamServerUID[UID_LEN];
    char StreamServerIP[UID_LEN];
    int StreamServerPort;
} Reg2P2PStreamServerInfoNotifyPkt;

typedef struct _UserCreateGroupReqPkt                   /*0x0546 131*/
{
	ReqCMDHeader    Header;
	char            AppName[USER_NAME_LEN];
	char            AppPasswd[PASSWORD_LEN];
	char            PhoneUUID[UID_LEN];
    char            GroupMember[ (USER_NAME_LEN + 4) * 16 ];      /* �������Ա�����֧��16���û����û�����;����*/
}UserCreateGroupReqPkt;


typedef struct _UserCreateGroupRespPkt                  /*0x0547 132 */
{
    RespCMDHeader   Header;
    char            GroupID[UID_LEN];
} UserCreateGroupRespPkt;

typedef struct _UserGroupMebOperReqPkt                   /*0x0548 133 ��ӻ���ɾ���������Ա*/
{
	ReqCMDHeader    Header;
	char            AppName[USER_NAME_LEN];
	char            AppPasswd[PASSWORD_LEN];
	char            PhoneUUID[UID_LEN];
    char            GroupID[UID_LEN];
    char            GroupMember[ (USER_NAME_LEN + 4) * 16 ];      /* ����ӻ���ɾ�����������Ա�����֧��16���û����û�����;����*/
    int             FriendOpt;                                     /* 0 Ϊɾ���� 1Ϊ��� */
}UserGroupMebOperReqPkt;

typedef struct _UserGroupMebOperRespPkt                  /*0x0549 134 */
{
    RespCMDHeader   Header;
    char            GroupID[UID_LEN];
} UserGroupMebOperRespPkt;


typedef struct _P2P2CLIDeviceResetNotifyPkt   //0x0550 53
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
}P2P2CLIDeviceResetNotifyPkt;

typedef struct _P2P2CLIShareCancelNotifyPkt   //0x0552 54
{
    ReqCMDHeader Header;
	int			PktCnt;
	int 		PktSeq;
    char SponsorName[UID_LEN];
    char DeviceUID[UID_LEN];
    MDPushChanList *pChanList;
}P2P2CLIShareCancelNotifyPkt;

// change by linhh 20161128 : 0x554 ֻ����˽������Ϣ
typedef struct _Reg2P2PDeviceResetNotifyPkt   //0x0554 327
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];
    char PrivateAppUID[UID_LEN];
    // liujl change start at 20161220
    char ShareAcceptorUID[UID_LEN];
    MDPushChanList *pChanList;
    // liujl change end at 20161220
} Reg2P2PDeviceResetNotifyPkt;


typedef struct _UserGetP2PServerReqPkt   // 0x0560   55
{
	ReqCMDHeader Header;
	char AppName[USER_NAME_LEN];
	char AppPasswd[PASSWORD_LEN];
	char PhonUUID[UID_LEN];
} UserGetP2PServerReqPkt;

typedef struct _UserGetP2PServerRespPkt   // 0x0562   56
{
    RespCMDHeader Header;
    char P2PServerIP[IP_STR_LEN];
    int     P2PServerPort;           
} UserGetP2PServerRespPkt;


/*
    Packet:122
    ˵��:�����: Device����P2PSer  (Device ->RegSer)
������ͼ44��(P2PServer崻�ʱ��Device�������·���P2PServer)
    CMD:0x0564
*/

typedef struct _DeviceInquiryP2PSerReqPkt
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];            //  �豸UID
} __attribute__((packed))DeviceInquiryP2PSerReqPkt;                 /*change by linhh 20170608 */

/*
    Packet:123
    ˵��:Ӧ���: Device����P2PSer
    CMD:0x0565
*/
typedef struct _DeviceInquiryP2PSerRespPkt
{
    RespCMDHeader Header;
    char P2PServerIP[IP_STR_LEN];
    int P2PServerPort;                      
    char P2PServerUID[UID_LEN];
} DeviceInquiryP2PSerRespPkt;


typedef struct _P2P2RegHBPkt   //0x0566 601
{
    ReqCMDHeader Header;
    char P2PServerIP[IP_STR_LEN];
    int P2PServerPort;                        
    char P2PServerUID[UID_LEN];
    int HeartBeatCnt;
	//add by ronghl 2017-01-06 start
	char ServerTime[32];		//��������ǰ��ʱ���
	int UpBand;					//���д���
	int DownBand;				//���д���
	//add by ronghl 2017-01-06 end
} P2P2RegHBPkt;


typedef struct _Reg2StreamP2PInfoNotifyPkt   //0x0568  341
{
    ReqCMDHeader Header;
    char P2PServerUID[UID_LEN];
    char P2PServerIP[IP_STR_LEN];
    int P2PServerPort;
} Reg2StreamP2PInfoNotifyPkt;


typedef struct _UserGroupMebGetReqPkt                   /*0x0574 245 �û���ȡ�������Ա��Ϣ */
{
	ReqCMDHeader    Header;
	char            AppName[USER_NAME_LEN];
	char            AppPasswd[PASSWORD_LEN];
	char            PhoneUUID[UID_LEN];
    char            GroupID[UID_LEN];
}UserGroupMebGetReqPkt;

typedef struct _GroupFriendName
{
    char                        AppName[USER_NAME_LEN];
    struct _GroupFriendName    *Next ;
}GroupFriendName;

typedef struct _UserGroupMebGetRespPkt                 /*0x0575 246 �û���ȡ�������ԱӦ��� */
{
    RespCMDHeader       Header;
	int 				PktCnt;
	int 				PktSeq;
    char                GroupID[UID_LEN];
    GroupFriendName     *FriendList;
} UserGroupMebGetRespPkt;

/* add begin by ronghl, 2017-11-07, ��Ӻ��ѷ����豸��������Ϣ */

/* 0x0582 */
typedef struct _PhoneAddShareChannelReqPkt
{
	ReqCMDHeader		Header;
	char				AppName[USER_NAME_LEN];
	char				AppPasswd[PASSWORD_LEN];
	char				PhoneUUID[UID_LEN];
	char				DeviceUID[UID_LEN];
	int					DeviceChannelIndex;
	char				DeviceUserName[USER_NAME_LEN];
	char				DeviceUserPasswd[PASSWORD_LEN];
	char				DeviceChanAlias[USER_NAME_LEN];
}PhoneAddShareChannelReqPkt;


/* 0x0583 */
typedef struct _PhoneAddShareChannelRespPkt
{
	RespCMDHeader		Header;
	char				DeviceUID[UID_LEN];
	int					DeviceChannelIndex;
	int					DeviceOnlineStatus;
	char				DeviceChannelAlias[USER_NAME_LEN];
	char				DeviceSponsorName[USER_NAME_LEN];
}PhoneAddShareChannelRespPkt;

/* add end by ronghl, 2017-11-07 */


/////////////////////////////Relay�Ự��ص����������//////////////////////

/////////////////////////////Device��ص����������start//////////////////////
/* change by linhh 20170526 : ͳһ����ģ�����Ͷ��� ��HieServer_Cfg.h �� ws_status_def.h ��*/

typedef struct _ws_channel_name_info
{
    int     Channel;
    char    ChannelName[CHANNLE_NAME_LEN];
    struct _ws_channel_name_info *Next;
} ws_channel_name_info;

typedef struct _ws_alarm_push_info
{
    int channel;
    int    bPush;//0��ʾ�����ͣ�1��ʾ����
    struct _ws_alarm_push_info *Next;
} ws_alarm_push_info;

typedef enum
{
    WS_RECORD_STATUS_IDLE = 0,          //0 δ¼��
    WS_RECORD_STATUS_TIMER,             // 1 ��ʱ¼��
    WS_RECORD_STATUS_ALARM,            //  2 ����¼��
    WS_RECORD_STATUS_MANUAL,          /* 3 �ֶ�¼��*/
} ws_record_status;

typedef struct _ws_record_status_info
{
    int channel;
    ws_record_status    record_type;
    struct _ws_record_status_info *Next;
} ws_record_status_info;//0 δ¼�� �� 1 ��ʱ¼�� �� 2 ����¼��


typedef struct _ws_record_storage_type_info
{
    int channel;
    RECORD_MODE   record_storage_type;
    struct _ws_record_storage_type_info *Next;
} ws_record_storage_type_info;

typedef enum
{
    WS_VIDEO_QUALITY_AUTO = 0,  //����Ӧ
    WS_VIDEO_QUALITY_FLUENT,//������
    WS_VIDEO_QUALITY_DISTINCT,//��������
} ws_video_quality;

//=====================device ����ṹ��start==================================
/*
    Packet:66
    ˵��:�����: �豸����P2PSer����Device -> P2PSer��
    CMD:0x0202
*/
typedef struct _DeviceHeartReqPkt
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];            //  �豸UID
    char DeviceLANIP[IP_STR_LEN];       //�豸�ľ�����IP��ַ��Ϣ
    int  DeviceLANPort;
    char DeviceUserName[TRAN_USERNAME_LEN]; //�豸��¼��            
    char DevicePasswd[TRAN_PASSWD_LEN];        //�豸��¼����       
    char PrivateUserName[USER_NAME_LEN];	
    char PrivateUserUID[UID_LEN];
} __attribute__((packed))DeviceHeartReqPkt;                         /* change by linhh 20170608 */

/*
    Packet:67
    ˵��:67. Ӧ���: �豸����
    CMD:0x0203
*/
typedef struct _DeviceHeartRespPkt
{
    RespCMDHeader Header;
    char P2PServerUID[UID_LEN];	
    char AlarmDataIP[IP_STR_LEN];
    int  AlarmDataPort;
} DeviceHeartRespPkt;

/*
    Packet:70
    ˵��:֪ͨ��: ֪ͨDevice��������:��P2PSer -> Device����
    CMD:0x022a
*/
typedef struct _StartConnectDeviceReqPkt
{
    ReqCMDHeader Header;
    char ClientName[USER_NAME_LEN];     //�������ӵĿͻ��˵��û���
    char ClientUID[UID_LEN];            //�������ӵĿͻ��˵�UID
    char ClientWANIP[IP_STR_LEN];       //�ͻ��˵Ĺ���IP
    int ClientWANPort;             //�ͻ��˹����˿�
    char ClientLANIP[IP_STR_LEN];       //�ͻ��˾�����IP
    int ClientLANPort;             //�ͻ��˾������˿�
    int P2PSessionID;                   //P2P�ỰID
    char MAC[MACADDR_LEN];				//App�˵�MAC��ַ
} StartConnectDeviceReqPkt;

/*
    Packet:79
    ˵��:��Ӧ��: ֪ͨDevice��������:��P2PSer -> Device����
    CMD:0x022b
*/
typedef struct _StartConnectDeviceRespPkt
{
	RespCMDHeader Header;
	char 	ClientName[USER_NAME_LEN]; 	//�������ӵĿͻ��˵��û���
	char	DeviceUID[UID_LEN];			//�豸��Ӧ��
	int 	P2PSessionID;				//P2P�ỰID
	char	MAC[MACADDR_LEN];			//�豸�˵�MAC��ַ
} StartConnectDeviceRespPkt;


/*
    Packet:
    ˵��:�����: ֪ͨDevice��������:��P2PSer -> Device����
    CMD:0x022c
*/
typedef struct _BandwidthFeedbackReqPkt
{
	ReqCMDHeader	Header;
	char			AppUsrName[USER_NAME_LEN];
	char			DeviceUID[UID_LEN];
	int	    		P2POrRelaySessionID;
	int           	MediaSessionID;
	int				RecvPktCnt;
	int				LostPktCnt;
}BandwidthFeedbackReqPkt;


 
 /*
	 Packet:
	 ˵��:�����: ֪ͨDevice��������:��P2PSer -> Device����
	 CMD:0x022d
 */
 typedef struct _BandwidthFeedbackRespPkt
 {
 	RespCMDHeader	Header;
	int 			MediaSessionID;
	int				FeedbackInterval;
 }BandwidthFeedbackRespPkt;



 //Modified by qqy,start at 2017-04-27 10:19:16
/*
    Packet:71
    ˵��:֪ͨ��: Client֪ͨ����״̬��Client -> P2PSer��
    CMD:0x0214
*/
typedef struct _ClientConnectStatusNotifyPkt
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];            //  �豸UID
    char ClientName[USER_NAME_LEN];     //Client�û���
    int P2PorRelaySessionID;            //P2P�ỰID����Relay�ỰID
    int SessionConnectStatus;           //�Ự����״̬
} ClientConnectStatusNotifyPkt;

/*
    Packet:72
    ˵��:֪ͨ��: Device֪ͨ����״̬��Device -> P2PSer��
    CMD:0x0215
*/
typedef struct _DeviceConnectStatusNotifyPkt
{
    ReqCMDHeader Header;
    char DeviceUID[UID_LEN];            //  �豸UID
    char ClientName[USER_NAME_LEN];     //Client�û���
    int P2PorRelaySessionID;            //P2P�ỰID����Relay�ỰID
    int SessionConnectStatus;           //�Ự����״̬
} DeviceConnectStatusNotifyPkt;
 //Modified by qqy,end at 2017-04-27 10:19:19

/*
    Packet:73
    ˵��:֪ͨ��: �������������£���P2PServer -> Device��
    CMD:0x0416
*/


/*
    Packet:76
    ˵��:�����: Client��Device֮��������
    CMD:0x0212
*/
typedef struct _ClientAndDeviceHeartReqPkt
{
    ReqCMDHeader Header;
    char ClientName[USER_NAME_LEN];     //�������ӵĿͻ��˵��û���
    char DeviceUID[UID_LEN];            //  �豸UID
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;            //P2P�ỰID����Relay�ỰID	
    /**add by ronghl 2017-07-18: start**/
	int P2PUserStatus;		/* Ϊ1��ʾDevice���ѽ��յ�App���������Ӧ��� 0 : δ�յ�  1:�յ�  */
	int P2PDeviceStatus;	/* Ϊ1��ʾApp���ѽ��յ�Device���������Ӧ��� 0 : δ�յ�  1:�յ�*/
	/**add by ronghl 2017-07-18:   end**/
	int Capacity;			/* ʹ����Ϣ��APP��ʼ�շ���Ϊ0 */
} __attribute__((packed))ClientAndDeviceHeartReqPkt;                    /* change by linhh 20170608 */

/*
    Packet:77
    ˵��:Ӧ���: Client��Device֮������Ӧ��
    CMD:0x0213
*/
typedef struct _ClientAndDeviceHeartRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;            //P2P�ỰID����Relay�ỰID
    /**add by ronghl 2017-07-18: start**/
	int P2PUserStatus;					//�û��Ƿ��Ѿ����յ����豸�˵������������������Ӧ���� 0 : δ�յ�  1:�յ� 
	int P2PDeviceStatus;				//�豸�Ƿ��Ѿ����յ��û������������������������Ӧ���� 0 : δ�յ�  1:�յ�
	/**add by ronghl 2017-07-18:   end**/
	int Capacity;			/* �豸��ʹ����Ϣ,APP��ʼ�շ���0 */
} ClientAndDeviceHeartRespPkt;

/*
    Packet:78
    ˵��:֪ͨ��: Clientֹͣ����Device (Client -> Devcie):
    CMD:0x0228
*/
typedef struct _ClientStopHeartNotifyPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;            //P2P�ỰID����Relay�ỰID
} ClientStopHeartNotifyPkt;

/*
    Packet:81
    ˵��:֪ͨ��: ֪ͨDevice����Relay���� (P2PSer -> Device)
    CMD:0x0224
*/
typedef struct _StartRelayConnectNotifyPkt
{
    ReqCMDHeader Header;
    char AppUserName[USER_NAME_LEN];    //App�û���
    int RelaySessionID;                 //Relay�ỰID
    char RelayServerIP[IP_STR_LEN];     //Relay��IP
    int RelayServerPort;     //Relay��Port                      // change by linhh 20161125 
    char MAC[MACADDR_LEN];
	char LocalIP[IP_STR_LEN];
} StartRelayConnectNotifyPkt;


/*
    Packet:91
    ˵��:�����: �����豸��Ƶ��client -> Device , client -> StrSer����
    CMD:0x0334
*/
typedef struct _StartDeviceAudioReqPkt
{
    ReqCMDHeader Header;
    char AppUserName[USER_NAME_LEN];
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int DeviceChannel;          //�豸ͨ����    (ͨ���Ŵ�1��ʼ��ţ���ʾĳһ��ͨ����Ϊ0��ʾ�����豸����Ƶ)
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} StartDeviceAudioReqPkt;

/*
    Packet:92
    ˵��:Ӧ���: �����豸��Ƶ
    CMD:0x0335
*/
typedef struct _StartDeviceAudioRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StartDeviceAudioRespPkt;

/*
    Packet:93
    ˵��:�����: �ر��豸��Ƶ (client -> Device , Client -> StrSer)��
    CMD:0x0336
*/
typedef struct _StopDeviceAudioReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StopDeviceAudioReqPkt;

/*
    Packet:94
    ˵��:Ӧ���: �ر��豸��Ƶ
    CMD:0x0337
*/
typedef struct _StopDeviceAudioRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;            //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StopDeviceAudioRespPkt;

/*
   Packet:95
   ˵��:�����: ����Client��Ƶ (client -> Device , Client -> StrSer)��
   CMD:0x0338
*/
typedef struct _StartClientAudioReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} StartClientAudioReqPkt;

/*
    Packet:96
    ˵��:Ӧ���: ����Client��Ƶ
    CMD:0x0339
*/
typedef struct _StartClientAudioRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StartClientAudioRespPkt;

/*
    Packet:97
    ˵��:�����: �ر�Client��Ƶ (client -> Device , Client -> StrSer)
    CMD:0x033a
*/
typedef struct _StopClientAudioReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StopClientAudioReqPkt;

/*
    Packet:98
    ˵��:Ӧ���: �ر�Client��Ƶ
    CMD:0x033b
*/
typedef struct _StopClientAudioRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;            //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StopClientAudioRespPkt;

/*
    Packet:99
    ˵��:�����: ������Ƶ�Խ� (client -> Device , Client -> StrSer)��
    CMD:0x033c
*/
typedef struct _StartDeviceTalkReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} StartDeviceTalkReqPkt;

/*
    Packet:100
    ˵��:Ӧ���: ������Ƶ�Խ�
    CMD:0x033d
*/
typedef struct _StartDeviceTalkRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StartDeviceTalkRespPkt;

/*
    Packet:101
    ˵��:�����: �ر���Ƶ�Խ� (client -> Device , Client -> StrSer)��
    CMD:0x033e
*/
typedef struct _StopDeviceTalkReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StopDeviceTalkReqPkt;

/*
    Packet:102
    ˵��:Ӧ���: �ر���Ƶ�Խ�
    CMD:0x033f
*/
typedef struct _StopDeviceTalkRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StopDeviceTalkRespPkt;

/*
    Packet:103
    ˵��:�����: ������Ƶͨ����client -> Device , Client -> StrSer����
    CMD:0x0340
*/
typedef struct _StartDeviceVideoReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int DeviceChannel;          //�豸ͨ����    (ͨ���Ŵ�1��ʼ��ţ���ʾĳһ��ͨ����Ϊ0��ʾ�����豸����Ƶ)
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_video_quality   video_quality;//��Ƶ������
} StartDeviceVideoReqPkt;

/*
    Packet:104
    ˵��:Ӧ���: ������Ƶͨ��
    CMD:0x0341
*/
typedef struct _StartDeviceVideoRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StartDeviceVideoRespPkt;

/*
    Packet:105
    ˵��:�����: �ر���Ƶͨ�� (client -> Device , Client -> StrSer)��
    CMD:0x0342
*/
typedef struct _StopDeviceVideoReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StopDeviceVideoReqPkt;

/*
    Packet:106
    ˵��:Ӧ���: �ر���Ƶͨ��
    CMD:0x0343
*/
typedef struct _StopDeviceVideoRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} StopDeviceVideoRespPkt;

/*
    Packet:109
    ˵��:�����: ������Ƶ���� (client -> Device , Client -> StrSer)
    CMD:0x0344
*/
typedef struct _StartDeviceDownLoadReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    char FileName[FILE_NAME_LEN];//������ļ���
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} StartDeviceDownLoadReqPkt;

/*
ͼƬ����ʱ��Ӧ�����û����ʼ�����֡����Ϣ���ļ�����ʱ�����ļ��в�������Ƶ�����ݣ���Ӧ�����û����Ƶ��ʼ�����֡����Ϣ��
    Packet:110
    ˵��:Ӧ���: ������Ƶ����
    CMD:0x0345
*/
typedef struct _StartDeviceDownLoadRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�ļ�����ĻỰID
    int FirstVideoFrameNo;
    int LastVideoFrameNo;
    int FirstAudioFrameNo;
    int LastAudioFrameNo;
} StartDeviceDownLoadRespPkt;

/*
    Packet:111
    ˵��:֪ͨ��: ֪ͨDevice��ɾ��˽�й�ϵ (P2PSer -> Device)
    CMD:0x012c
*/
typedef struct _DeleteDevicePrivateRelationNotifyPkt
{
    ReqCMDHeader Header;
    char ClientName[USER_NAME_LEN];     //Client �û���
    char ClientUID[UID_LEN];            //Client�û�UID
    char DeviceUID[UID_LEN];            //  �豸UID
} DeleteDevicePrivateRelationNotifyPkt;


#if 0
/*
    Packet:114
    ˵��:֪ͨ��: �豸�������� (Device -> AlaSer)
    ����ID:0x040c
*/
typedef struct _DeviceAlarmNotifyPkt
{
    ReqCMDHeader Header;
    AlarmType alarmtype;    //��������
    int AlarmIndex;         //�������
    int channel;            //ͨ����Ϣ
    int IsOn;               //����״̬
    int time;               //�����¼���ʱ��
    char DeviceUID[UID_LEN];            //  �豸UID
    char ClientUID[UID_LEN];            //Client�û�UID
    int P2PSessionID;   //P2P�ỰID     //Device��¼��P2PSer��UID
} DeviceAlarmNotifyPkt;
#endif
/*
    Packet:145
    ˵��:�����: ��ȡDeviceͨ��¼��״̬ ( Client -> Device )
    CMD:0x0300
*/
typedef struct _GetDeviceRecordStatusReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    DevChannelList *PtrChanList;  //�豸ͨ����        : ֧��ͬʱ��ȡ���ͨ��¼��״̬..
} GetDeviceRecordStatusReqPkt;

/*
Packet:146
˵��:Ӧ���: ��ȡDeviceͨ��¼��״̬
   CMD:0x0301
*/
typedef struct _GetDeviceRecordStatusRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_record_status_info    *recordStatusInfo;   //¼��״̬��Ϣ
} GetDeviceRecordStatusRespPkt;

/*
    Packet:147
    ˵��:�����: ��ȡDevice�豸�� ( Client -> Device )
    CMD:0x0302
 */
typedef struct _GetDeviceNameReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} GetDeviceNameReqPkt;

/*
Packet:148
˵��:Ӧ���: ��ȡDevice�豸��
   CMD:0x0303
*/
typedef struct _GetDeviceNameRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    char DeviceName[DEVICE_NAME_LEN];
} GetDeviceNameRespPkt;

/*
    Packet:149
    ˵��:�����: ����Device�豸��  ( Client -> Device )
    CMD:0x0304
 */
typedef struct _SetDeviceNameReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    char DeviceName[DEVICE_NAME_LEN];
} SetDeviceNameReqPkt;

/*
    Packet:150
    ˵��:Ӧ���: ����Device�豸��
    CMD:0x0305
*/
typedef struct _SetDeviceNameRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetDeviceNameRespPkt;

/*
    Packet:151
    ˵��:�����: ��ȡDeviceͨ���� ( Client -> Device )
    CMD:0x0306
*/
typedef struct _GetDeviceChannelNameReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    DevChannelList *PtrChanList;//�豸ͨ����        : ֧��ͬʱ������ͨ����ͨ����
} GetDeviceChannelNameReqPkt;

/*
    Packet:152
    ˵��:Ӧ���: ��ȡDeviceͨ����
    CMD:0x0307
*/
typedef struct _GetDeviceChannelNameRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_channel_name_info *channel_name_info;
} GetDeviceChannelNameRespPkt;

/*
    Packet:153
    ˵��:�����: ����Deviceͨ���� ( Client -> Device )
    CMD:0x0308
 */
typedef struct _SetDeviceChannelNameReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_channel_name_info *channel_name_info;
} SetDeviceChannelNameReqPkt;

/*
    Packet:154
    ˵��:Ӧ���: ����Deviceͨ����
    CMD:0x0309
*/
typedef struct _SetDeviceChannelNameRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetDeviceChannelNameRespPkt;

/*����������ʱ������ÿ�ʼ�����ʱ��Ϊ0
    Packet:155
    ˵��:�����: ��ȡͨ���ƶ���Ⲽ��ʱ�� ( Client -> Device )
    CMD:0x030a
    */
typedef struct _GetChannelAlarmScheduleReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    DevChannelList *PtrChanList;//֧��ͬʱ��ȡ���ͨ�����ƶ���Ⲽ��ʱ��
} GetChannelAlarmScheduleReqPkt;

typedef struct _ChanRecordPlanList
{
    int Channel;
    ws_rec_schedule_per_day rec_schedule;
    struct _ChanRecordPlanList *Next;
} ChanRecordPlanList;

/*
    Packet:156
    ˵��:Ӧ���: ��ȡ�ƶ���Ⲽ��ʱ��
    CMD:0x030b
*/
typedef struct _GetChannelAlarmScheduleRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ChanRecordPlanList *PtrChanList;
} GetChannelAlarmScheduleRespPkt;

/*
    Packet:157
    ˵��:�����: �����ƶ���Ⲽ��ʱ�� ( Client -> Device )
    CMD:0x030c
    */
typedef struct _SetChannelAlarmScheduleReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ChanRecordPlanList *PtrChanList;
} SetChannelAlarmScheduleReqPkt;

/*
    Packet:158
    ˵��:Ӧ���: �����ƶ�������
    CMD:0x030d
*/
typedef struct _SetChannelAlarmScheduleRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetChannelAlarmScheduleRespPkt;

/*
¼��洢����Ϊ����¼���Ƕ�ʱ¼��
    Packet:159
    ˵��:�����: ��ȡDevice��Ƶͨ���洢���� ( Client -> Device )
    CMD:0x030e
 */
typedef struct _GetChannelRecordStorageTypeReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    DevChannelList *PtrChanList;
} GetChannelRecordStorageTypeReqPkt;

/*
Packet:160
˵��:Ӧ���: ��ȡDevice��Ƶͨ���洢����
   CMD:0x030f
*/
typedef struct _GetChannelRecordTypeStorageRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_record_storage_type_info   *storage_type_info;
} GetChannelRecordStorageTypeRespPkt;

/*
    Packet:161
    ˵��:�����: ����Device��Ƶͨ���洢���� ( Client -> Device )
    CMD:0x0310
 */
typedef struct _SetChannelRecordStorageTypeReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_record_storage_type_info   *storage_type_info;//֧��ͬʱ���ö����Ƶͨ���洢���Ͳ���]  : 1 : ��ʱ¼�� �� 2 : ����¼��
} SetChannelRecordStorageTypeReqPkt;

/*
    Packet:162
    ˵��:Ӧ���: ����Device��Ƶͨ���洢����
    CMD:0x0311
 */
typedef struct _SetChannelRecordStorageTypeRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetChannelRecordStorageTypeRespPkt;

/*
    Packet:163
    ˵��:�����: ��ȡ��ʱ¼����� ( Client -> Device )
    CMD:0x0312
 */
typedef struct _GetChannelRecordScheduleReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    DevChannelList *PtrChanList;//֧��ͬʱ��ȡ�����Ƶͨ��
} GetChannelRecordScheduleReqPkt;

/*
    Packet:164
    ˵��:Ӧ���: ��ȡ��ʱ¼�����
    CMD:0x0313
*/
typedef struct _GetChannelRecordScheduleRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ChanRecordPlanList *PtrChanList;
} GetChannelRecordScheduleRespPkt;

/*
    Packet:165
    ˵��:�����: ���ö�ʱ¼����� (Client -> Device )
    CMD:0x0314
 */
typedef struct _SetChannelRecordScheduleReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ChanRecordPlanList *PtrChanList;
} SetChannelRecordScheduleReqPkt;

/*
    Packet:166
    ˵��:Ӧ���: ���ö�ʱ¼�����
    CMD:0x0315
*/
typedef struct _SetChannelRecordScheduleRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetChannelRecordScheduleRespPkt;

/*
     Packet:200.
     ˵��:�����: Device¼���ļ���ѯ ( Client -> Device )
    CMD :0x0370
 */
typedef enum
{
    WS_FILE_TYPE_UNKNOW,
    WS_FILE_TYPE_PIC,
    WS_FILE_TYPE_VIDEO,
    WS_FILE_TYPE_ALL,
} ws_file_type;

typedef enum
{
    WS_FILE_INQUIRY_UNKNOW,
    WS_FILE_INQUIRY_COMM,
    WS_FILE_INQUIRY_ALARM,
    WS_FILE_INQUIRY_ALL,
} ws_file_inquiry_type;

typedef struct _GetReplayFileListReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int Channel;                //��ѯͨ����    : ¼���ļ����ܽ϶࣬һ������ֻ�ܻ�ȡһ��ͨ������Ƶ����
    ws_file_type file_type;      //�ļ����� (ͼƬ��¼���ļ���ȫ��)
    ws_file_inquiry_type alarm_type;     //�������� (�����ļ�����ͨ�ļ���ȫ��)
    time_t start_time;
    time_t stop_time;
} GetReplayFileListReqPkt;

typedef struct _PBFileList
{
    char FileName[FILE_NAME_LEN];//�ļ�����
    ws_file_type file_type;      //�ļ����� (ͼƬ��¼���ļ���ȫ��)
    ws_file_inquiry_type alarm_type;     //�������� (�����ļ�����ͨ�ļ���ȫ��)
    time_t start_time;
    time_t stop_time;
    int file_size;      //�ļ���С
    struct _PBFileList *Next;
}PBFileList;

/*
    Packet:201
    ˵��:Ӧ���: Device¼���ļ���ѯ
    CMD:0x0371
 */
typedef struct _GetReplayFileListRespPkt
{
    RespCMDHeader Header;
	/* add by ronghl 2017-09-27:   app need packet count and packet sequence */
	int 		  PktCnt;
	int			  PktSeq;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    PBFileList *PtrFileList;
} GetReplayFileListRespPkt;

/*
�ط��������: ���š���ͣ���ָ����š�ֹͣ����š����š����ò���ʱ����
    Packet:202
    ˵��:�����: ����Device �ط����� ( Client -> Device )
    CMD :0x0372
*/
typedef struct _StartReplayReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int Channel;                //�豸ͨ����        : �طŲ���ֻ֧�ֵ�ͨ������
    char FileName[FILE_NAME_LEN];//�ļ�����:�ļ����豸�ϵ�����·�� /dat��ʼ���ַ���
    time_t timepoint;           //��ʼ���ŵ�ʱ��  :  0 ��ʾ���ļ���ʼ���ţ�����ʱ��ֵ��ʾ���ļ�ָ����ʱ��㿪ʼ����
} StartReplayReqPkt;

/*
    Packet:203
    ˵��:Ӧ���: ����Device �ط�����
    CMD :0x0373
���ļ�����ΪͼƬʱ��APP���յ�����ͼƬ���ݰ���
��Device��ÿ��ͼƬ�����뷢������202���������203��
Device��������203���ӳ�300���뷢�������ݡ�
*/
typedef struct _StartReplayRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID        : Device���յ������ط������Ϊ�طŲ��������ỰID
    int magic;//��ЧMagic       : ��Ч��Magic��APP���յ����ݺ����Magic�ж��Ƿ���Ҫ������ʾ��
} StartReplayRespPkt;

/*
    Packet:204
    ˵��:�����: ��ȡ�����ٶ�(Client -> Device)��
    CMD:0x0374
 */
typedef struct _GetReplaySpeedReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
} GetReplaySpeedReqPkt;

/*
Packet:205
˵��:Ӧ�������ȡ�����ٶ�
   packet-type (1�������)
   CMD :0x0375
*/
typedef struct _GetReplaySpeedRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    eTaskSpeed speed;                 //�����ٶ�
} GetReplaySpeedRespPkt;

/*
    Packet:206
    ˵��:�����: ���ò����ٶ�(Client -> Device)��
    CMD :0x0376
 */
typedef struct _SetReplaySpeedReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    eTaskSpeed speed;                 //�����ٶ�
} SetReplaySpeedReqPkt;

/*
    Packet:207
    ˵��:Ӧ��������ò����ٶ�
    CMD :0x0377
�޸Ĳ����ٶȺ�,Device�����µ�Magic��APP��
APP�ɸ���Magic��Ϣ���������д�������ݰ���
*/
typedef struct _SetReplaySpeedRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    eTaskSpeed speed;                 //�����ٶ�
    int magic;//��ЧMagic   �޸Ĳ����ٶȺ�,Device�����µ�Magic��APP��APP�ɸ���Magic��Ϣ���������д�������ݰ���
} SetReplaySpeedRespPkt;

/*
    Packet:208
    ˵��:�����: ��ȡ���Ž��Ȱٷֱ�(Client -> Device)��
    CMD :0x0378
*/
typedef struct _GetReplayProgressReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
} GetReplayProgressReqPkt;

/*
Packet:209
˵��:Ӧ�������ȡ���Ž��Ȱٷֱ�
   CMD :0x0379
*/
typedef struct _GetReplayProgressRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    int progress;//���Ž��� :                           0 - 100��Χ
} GetReplayProgressRespPkt;

/*
    Packet:210
    ˵��:�����: ���ò��Ž��Ȱٷֱ�(Client -> Device)��
    CMD:0x037a
*/
typedef struct _SetReplayProgressReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    int progress;//���Ž��� :                           1 - 99 ��Χ
} SetReplayProgressReqPkt;

/*
Packet:211
˵��:Ӧ��������ò��Ž��Ȱٷֱ�
   CMD :0x037b
�޸Ĳ���ʱ����,Device�����µ�Magic��APP��
APP�ɸ���Magic��Ϣ���������д�������ݰ���
*/
typedef struct _SetReplayProgressRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    int progress;//���Ž��� :                           0 - 100��Χ
    int magic;//��ЧMagic
} SetReplayProgressRespPkt;

/*
    Packet:212
    ˵��:�����: �����µĲ����ļ�(Client -> Device)��
    CMD :0x037c
*/
typedef struct _SetReplayFileReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    char FileName[FILE_NAME_LEN];//�ļ�����:�ļ����豸�ϵ�����·�� /dat��ʼ���ַ���
} SetReplayFileReqPkt;

/*
Packet:213
˵��:Ӧ����������µĲ����ļ�
   CMD :0x037c
����һ���ļ�δ������ϵ�ʱ�򣬵�������212������һ���������ļ���
����ʵ�ֶ���ļ����������š�
*/
typedef struct _SetReplayFileRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
} SetReplayFileRespPkt;

/*
    Packet:214
    ˵��:�����: ��ͣ��ָ�����(Client -> Device)��
    CMD :0x037e
 */
typedef enum
{
    WS_REPAY_STATUS_CONTINUE,
    WS_REPAY_STATUS_PAUSE,
    WS_REPAY_STATUS_UNKNOW,
} ws_replay_status;

typedef struct _SetReplayStatusReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    ws_replay_status replay_status;//����״̬:              1 Ϊ��ͣ���ţ�0Ϊ��������
} SetReplayStatusReqPkt;

/*
    Packet:215
    ˵��:Ӧ�������ͣ��ָ�����(Client -> Device)��
    CMD :0x037f
*/
typedef struct _SetReplayStatusRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    ws_replay_status replay_status;//����״̬:              1 Ϊ��ͣ���ţ�0Ϊ��������
    int         Magic;
} SetReplayStatusRespPkt;

/*
    Packet:216
    ˵��:�����: ֹͣ����(Client -> Device)��
    CMD :0x0380
 */
typedef struct _StopReplayReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
} StopReplayReqPkt;

/*
    Packet:217
    ˵��:Ӧ�����ֹͣ����
    CMD :0x0381
�豸��һ���ļ�������Ϻ��豸��������֪ͨ����Client��
Client���յ�֪ͨ�����ֹͣ�طŲ�����������ʱ��ʧ���һ֡�������
*/
typedef struct _StopReplayRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
} StopReplayRespPkt;

/*
    Packet:218
    ˵��:֪ͨ��: �ط��ļ��е����ݶ�ȡ���� (Device -> Client)
    CMD :0x0382
ͨ������212ʵ�ֶ���ļ���������ʱ��
��ͨ������218��ȡ�����ļ��Ƿ񲥷������Ϣ��
���ļ�ΪͼƬ����ʱ��Device����������218��
*/
typedef struct _ReplayEndNotifyPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    char FileName[FILE_NAME_LEN];//�ļ�����:�ļ����豸�ϵ�����·�� /dat��ʼ���ַ���
    int EndStatus;              //���ݲ�����Ľ�� (0 ���ļ����������꣬1�����ŵ��ļ�������)
} ReplayEndNotifyPkt;
/*
    Packet:220
    ˵��:�����: ��ȡ���ؽ��Ȱٷֱ�(Client -> Device)��
    CMD :0x346
 */
typedef struct _GetDownloadProgressReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
} GetDownloadProgressReqPkt;

/*
Packet:221
˵��:Ӧ�������ȡ���ؽ��Ȱٷֱ�
   CMD :0x347
*/
typedef struct _GetDownloadProgressRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
    int progress;//���ؽ��� :                           0 - 100��Χ
} GetDownloadProgressRespPkt;

/*
    Packet:222
    ˵��:�����: ֹͣ�ļ�����(Client -> Device)��
    CMD:0x348
*/
typedef struct _StopDeviceDownloadReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
} StopDeviceDownloadReqPkt;

/*
Packet:223
˵��:Ӧ�����ֹͣ�ļ�����
   CMD:0x349
Client����ļ����غ�������222��Device�ر���������
*/
typedef struct _StopDeviceDownloadRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //ý��ỰID
} StopDeviceDownloadRespPkt;

//add by qqy,start at 2016-12-15 17:13:56
/*
Packet:224
˵��:�����: ��ȡ�豸���в���(Client -> Device)
   CMD:0x034a
*/
typedef struct _GetDeviceAllParamReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} GetDeviceAllParamReqPkt;

/*
Packet:225
˵��:Ӧ���: ��ȡ�豸���в���
   CMD:0x034b
*/
typedef struct _GetDeviceAllParamRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    char DeviceName[DEVICE_NAME_LEN];
    ws_hard_disk_work_ctl   disk_work_ctl;//¼�񸲸ǲ���: 0 Ϊ¼��ֹͣ��1 Ϊ����¼��
    /* liujl change start at 20171114 */
    int wifi_support;   //wifiģ��֧��
    int wifi_switch;    //wifi����ʹ��
    int wifi_status;    //wifi����״̬
    /* liujl change end at 20171114 */
    char   wifi_ssid_name[WS_MAX_SSID_LEN];
} GetDeviceAllParamRespPkt;

/*
Packet:226
˵��:�����: ��ȡ�豸ͨ�����в���(Client -> Device)
   CMD:0x034c
*/
typedef struct _GetChannelAllParamReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    DevChannelList *PtrChanList;////֧��ͬʱ��ȡ�����Ƶͨ���Ĳ���
} GetChannelAllParamReqPkt;

/*
Packet:227
˵��:Ӧ���: ��ȡ�豸ͨ�����в���
   CMD:0x034d

MTimeMerge[n]��TTimeMerge[n]����32���ص�DWORD�������ݡ�
Bit0-Bit7��ʾ����ʱ��ķ�����Ϣ��
Bit8-Bit15��ʾ����ʱ���Сʱ��Ϣ��
Bit16-Bit23��ʾ��ʼʱ��ķ�����Ϣ��
Bit24-Bit31��ʾ��ʼʱ���Сʱ��Ϣ��
*/

typedef struct _ws_channel_all_param
{
    int     Channel;
    char    ChannelName[CHANNLE_NAME_LEN];//    ͨ������
    ws_record_status    record_type; //¼��״̬��Ϣ
    RECORD_MODE   record_storage_type;//    �洢���Ͳ���
    int bAlarmAllArea;// 1��ʾȫ�����ƶ���Ⲽ�����,0���ر�����������ƶ���Ⲽ�����
    DWORD MTimeMerge[WS_NVR_MAX_SCHEDULE_PER_DAY];//  4���ƶ���Ⲽ��ʱ��
    DWORD TTimeMerge[WS_NVR_MAX_SCHEDULE_PER_DAY];//  4����ʱ¼�񲼷�ʱ��
    int    bAlarmPush;//0��ʾ�����ͣ�1��ʾ����
    struct _ws_channel_all_param *Next;
} ws_channel_all_param;

typedef struct _GetChannelAllParamRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_channel_all_param *PtrChanList;
} GetChannelAllParamRespPkt;

/*
Packet:228
˵��:�����: ��ȡ�豸ͨ���ƶ���������Ƿ񲼷�(Client -> Device)
   CMD:0x034e
*/
typedef struct _GetChannelMDReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    DevChannelList *PtrChanList;////֧��ͬʱ��ȡ�����Ƶͨ���Ĳ���
} GetChannelMDReqPkt;

/*
    Packet:229
    ˵��:Ӧ���:��ȡ�豸ͨ���ƶ���������Ƿ񲼷�
    CMD:0x034f
 */

typedef struct _ws_channel_md_info
{
    int channel;
    int bAlarmAllArea;// 1��ʾȫ�����ƶ���Ⲽ�����,0���ر�����������ƶ���Ⲽ�����
    struct _ws_channel_md_info *Next;
} ws_channel_md_info;

typedef struct _GetChannelMDRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_channel_md_info   *PtrChanList;
} GetChannelMDRespPkt;

/*
Packet:230
˵��:�����: �����豸ͨ���ƶ����ȫ���򲼷��򳷷�(Client -> Device)
   CMD:0x0350
*/
typedef struct _SetChannelMDReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_channel_md_info   *PtrChanList;
} SetChannelMDReqPkt;

/*
    Packet:231
    ˵��:Ӧ���:�����豸ͨ���ƶ����ȫ���򲼷��򳷷�
    CMD:0x0351
*/
typedef struct _SetChannelMDRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetChannelMDRespPkt;

//add by qqy,end at 2016-12-15 17:13:58
/*
    Packet:170
    ˵��:�����:��ȡDevice��ͨ���ı����������� ( Client -> Device )
    CMD:0x031c
 */
typedef struct _GetAlarmPushReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    DevChannelList *PtrChanList;////֧�����ͨ����Ϣ��ȡ��Ҳ֧�ֶ��ͨ����Ϣͬʱ��ȡ
} GetAlarmPushReqPkt;

/*
    Packet:171
    ˵��:Ӧ���:��ȡDevice��ͨ���ı�����������
    CMD:0x031d
 */
typedef struct _GetAlarmPushRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_alarm_push_info   *alarm_push_info;//�����������ͨ���������ض�Ӧ����ͨ���ı�������ͨ���ı������Ϳ��ز���
} GetAlarmPushRespPkt;

/*
    Packet:172
    ˵��:�����:����Device��ͨ���ı����������� ( Client -> Device )
    CMD:0x031e
 */
typedef struct _SetAlarmPushReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_alarm_push_info   *alarm_push_info;//֧�����ͨ�����ã�Ҳ֧�ֶ��ͨ��ͬʱ����ͨ��N�ı������Ϳ��ز���
} SetAlarmPushReqPkt;

/*
    Packet:173
    ˵��:Ӧ���:����Device��ͨ���ı�����������
    CMD:0x031f
*/
typedef struct _SetAlarmPushRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetAlarmPushRespPkt;

/*
    Packet:174
    ˵��:֪ͨ��: Device��PTZ�������� ( Client -> Device )
    CMD:0x0320
*/
typedef struct _PTZNotifyPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
    PTZ_CMD_ID ptz_cmd;
    int ptz_para;
    //�豸�յ�һ�����ת��һ��ʱ�䡢һ���ǶȾ��Զ�ֹͣ
} PTZNotifyPkt;




typedef struct _ImageISPCtlList
{
    int ParamName;       // "IIPara"   Isp Image ParamName
    int ParamValue;      // "IIValue"   Isp Image ParamValue
    struct _ImageISPCtlList *Next;
} ImageISPCtlList;// ��XML<DevChanX>������һ��Key "IMAGE1" "IMAGE2" "IMAGE3"

typedef struct _ChanISPList
{
    int DeviceChannel;   //"DevChanID"
    ImageISPCtlList *PtrISPList;//��ͨ�������в���
    struct _ChanISPList *Next;
} ChanISPList;

/*
ͼ������������ȡ��Աȶȡ����Ͷȡ�ɫ������ƽ���
    Packet:175
    ˵��:�����: Deviceͼ�������ȡ (Client -> Device)
    CMD:0x0322
 */
typedef struct _GetImageParaReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ChanISPList *PtrChanList; /* ��XML�в�����KEY "IMAGE"ʱ����ʾ��ȡ��ͨ��������ͼ����� */
} GetImageParaReqPkt;

/*
    Packet:176
    ˵��:Ӧ���: Deviceͼ�������ȡ
    CMD:0x0323
*/
typedef struct _GetImageParaRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;             //"SessionID"  //P2P�ỰID����Relay�ỰID
    ChanISPList *PtrChanList; ///��XML <body>��������һ��Key  "DevChan1" "DevChan2" "DevChan3"
} GetImageParaRespPkt;

/*
    Packet:177
    ˵��:�����: Deviceͼ��������� ( Client -> Device )
    CMD:0x0324
 */
typedef struct _SetImageParaReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];   //"DevUsrName"
    char DeviceLoginPwd[PASSWORD_LEN];     //"DevPasswd"
    int P2PorRelaySessionID;                         //"SessionID"  //P2P�ỰID����Relay�ỰID
    ChanISPList *PtrChanList;      ///��XML <body>��������һ��Key  "DevChan1" "DevChan2" "DevChan3"
} SetImageParaReqPkt;

/*
    Packet:178
    ˵��:Ӧ���: Deviceͼ���������
    CMD:0x0325
    */
typedef struct _SetImageParaRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetImageParaRespPkt;

/*
��ͬ����Ƶͨ����ͬ��P2P�Ự�����в�ͬ����Ƶ�����Ȳ�����
    Packet:179
    ˵��:�����: ��ȡDevice��Ƶ�����Ȳ��� ( Client -> Device )
    CMD:0x0326
*/
typedef struct _GetVideoQualityReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
} GetVideoQualityReqPkt;

/*
Packet:180
˵��:Ӧ���: ��ȡDevice��Ƶ�����Ȳ���
   CMD:0x0327
*/
typedef struct _GetVideoQualityRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
    ws_video_quality   video_quality;//���ڸ��ݻỰID��ȡ�����ԣ�����ֻ��һ������

} GetVideoQualityRespPkt;

/*
    Packet:181
    ˵��:�����: ����Device��Ƶ�����Ȳ��� ( Client -> Device )
    CMD:0x0328
    */
typedef struct _SetVideoQualityReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
    ws_video_quality   video_quality;
} SetVideoQualityReqPkt;

/*
    Packet:182
    ˵��:Ӧ���: ����Device��Ƶ�����Ȳ���
    CMD:0x0329
*/
typedef struct _SetVideoQualityRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 //�����ݻỰID
    ws_video_quality   video_quality;
} SetVideoQualityRespPkt;

/*
    Packet:183
    ˵��:�����: ��ȡDevice����¼������ģʽ ( Client -> Device )
    CMD:0x032a
*/
typedef struct _GetDiskWorkCtrlReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} GetDiskWorkCtrlReqPkt;

/*
    Packet:184
    ˵��:Ӧ���: ��ȡDevice����¼������ģʽ
    CMD:0x032b
 */
typedef struct _GetDiskWorkCtrlRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_hard_disk_work_ctl   disk_work_ctl;//¼�񸲸ǲ���: 0 Ϊ¼��ֹͣ��1 Ϊ����¼��
} GetDiskWorkCtrlRespPkt;

/*
    Packet:185
    ˵��:�����: ����Device����¼������ģʽ (Client -> Device)
    CMD:0x032c
*/
typedef struct _SetDiskWorkCtrlReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    ws_hard_disk_work_ctl   disk_work_ctl;//¼�񸲸ǲ���: 0 Ϊ¼��ֹͣ��1 Ϊ����¼��
} SetDiskWorkCtrlReqPkt;

/*
Packet:186
˵��:Ӧ���: ����Device����¼������ģʽ
CMD:0x032d
*/
typedef struct _SetDiskWorkCtrlRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetDiskWorkCtrlRespPkt;

/*
�豸���������������P2P���͵��������ͱ������µ�����
    Packet:187
    ˵��:�����: ����Device�������� (Client -> Device)
    CMD:0x032e
*/
typedef struct _SetPasswdReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    char NewDeviceLoginPwd[PASSWORD_LEN];//�豸��������
} SetPasswdReqPkt;

/*
    Packet:188
    ˵��:Ӧ���: ����Device��������
    CMD:0x032f
 */
typedef struct _SetPasswdRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetPasswdRespPkt;

/*
    Packet:191
    ˵��:�����: ��ȡDevice WiFi�������� (Client -> Device)
    CMD:0x0330
*/
typedef struct _GetDeviceWifiConfigReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} GetDeviceWifiConfigReqPkt;

/*
    Packet:192
    ˵��:Ӧ���: ��ȡDevice WiFi��������
    CMD:0x0331
*/

typedef struct _GetDeviceWifiConfigRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    char   wifi_ssid_name[WS_MAX_SSID_LEN];
    char   wifi_ssid_passwd[WS_WLAN_MAX_KEY_LEN];
} GetDeviceWifiConfigRespPkt;

/*
    Packet:193
    ˵��:�����: ����Device WiFi�������� (Client -> Device)
    CMD:0x0332
*/
typedef struct _SetDeviceWifiConfigReqPkt
{
    ReqCMDHeader Header;
    char DeviceLoginName[USER_NAME_LEN];
    char DeviceLoginPwd[PASSWORD_LEN];
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    char   wifi_ssid_name[WS_MAX_SSID_LEN];
    char   wifi_ssid_passwd[WS_WLAN_MAX_KEY_LEN];
} SetDeviceWifiConfigReqPkt;

/*
    Packet:194
    ˵��:Ӧ���: ����Device�� WiFi��������
    CMD:0x0333
*/
typedef struct _SetDeviceWifiConfigRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetDeviceWifiConfigRespPkt;


/*
    //Packet:194
    ˵��:�����: ����Device�� WiFi��������
    CMD:0x0384
*/
typedef struct _SetDeviceWifiSwitchReqPkt
{
    ReqCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
    int iSwitch;				//Wifi����
} SetDeviceWifiSwitchReqPkt;

/*
    //Packet:194
    ˵��:Ӧ���: ����Device�� WiFi��������
    CMD:0x0385
*/
typedef struct _SetDeviceWifiSwitchRespPkt
{
    RespCMDHeader Header;
    int P2PorRelaySessionID;    //P2P�ỰID����Relay�ỰID
} SetDeviceWifiSwitchRespPkt;

/////////////////////////////Device��ص����������end//////////////////////






/////////////////////////////////��Ϣת����ص������ֶ���//////////////////////



typedef enum
{
    WS_P2P_FRAME_TYPE_UNKNOW = 0,
    WS_P2P_FRAME_TYPE_I,
    WS_P2P_FRAME_TYPE_P,
    WS_P2P_FRAME_TYPE_B1,
    WS_P2P_FRAME_TYPE_B2,
    WS_P2P_FRAME_TYPE_AUDIO,
    WS_P2P_FRAME_TYPE_PIC,
} ws_p2p_frame_type;

typedef enum
{
    WS_P2P_FRAME_CODE_UNKNOW = 0,
    WS_P2P_FRAME_CODE_H264,
    WS_P2P_FRAME_CODE_H265,
    WS_P2P_FRAME_CODE_G726,
    WS_P2P_FRAME_CODE_G711,
    WS_P2P_FRAME_CODE_JPG,
} ws_p2p_frame_code;

typedef struct _FrameDataPacketHead
{
    int P2PorRelaySessionID;        	//P2P�ỰID����Relay�ỰID
    int MediaSessionID;                 	//ý��ỰID
    int PartSeq;                			//���Ự��ǰ����ķ�Ƭ��ţ���1��ʼ
    int MediaType;              			//0~15bit��ʾ֡�ı�������,16~31bit����֡����
    int FrameSec;               			//֡ʱ������ (1970�꿪ʼ������)
    int FrameMSec;          			//֡ʱ�������( ����1��Ĳ��ֵĺ�����)
    int Magic;						//�������Ż��߸���ʱ�䶨λʱ����������Ż�������ʱMagic�����仯
    int FrameNO;                			//����Ƶ֡�ţ���Ƶ����Ƶ������ַ����Ҫ����MediaType��������Ƶ֡�Ż�����Ƶ֡��
    int PktInfo;                			//0~15bit��ǰ�ְ��ڵ�ǰ֡�ڷְ���ţ���1��ʼ,16~31bit��ǰ֡���ְ�������
    int DataSize;               			//0~23bit�ְ���XML�������ý�����ݸ��ص��ֽ���,24~31bit��ʾ����DWORD����
#ifdef _APP_LIST_MANAGE_
    int Width;
    int Height;
    int TotalSize;
#endif
} __attribute__((packed))FrameDataPacketHead;

typedef struct _FrameDataPacket    ///0x0800
{
    FrameDataPacketHead	Header;
    char *DataBuf;              			//�����ֽ�+ ��ý�����ݸ���
} __attribute__((packed))FrameDataPacket;

typedef struct _FileDataPacket    ///0x0801
{
    int MediaSessionID;             //ý��ỰID
    int PktCnt;					//ý�����ݱ��ְ�������
    int PktSeq;					//���Ự��ǰ����ķ�Ƭ��ţ���1��ʼ
    int FileUpdateTime;			//�����ݻỰ�ϴ�ʱ��  1970�꿪ʼ����
    int FileTotalSize;			//���Ѵ������ݵ����ֽ���
    int DataSize;				//��3���ֽڱ�ʾ��ý�����ݸ���,���λ1���ֽڱ�ʾ����Word����
    char *DataBuf;				//��ý������ָ��
} FileDataPacket;



/////////////////////////����ṹ�嶨��/////////////////////////////////////////

typedef enum
{
    WS_CLIENT_2_DEVICE_ADD = 1 ,
    WS_CLIENT_2_DEVICE_DEL = 2 ,    
}WS_CLIENT_2_DEVICE;

struct DevicePrivateRelationChange   // 0x012e   317
{
    int PktType;
    int Cmd;
    int SeqNo;
    char  DevUID[UID_LEN];
    char AppName[USER_NAME_LEN];
    char AppUID[UID_LEN];
    int Operate;
};

struct ConfigInfo
{
    int PktType;
    int Cmd;
    int SeqNo;
    char AppName[USER_NAME_LEN];
    char AppUID[UID_LEN];
    int ClientStatus;
    int PushAlarm;
    char P2PUID[UID_LEN];
    char P2PIp[IP_STR_LEN];
    int P2PPort;
};

//app���˻���Ϣ�� 
typedef struct _APP_USER_INFO
{
    WS_CHAR USER_UID[UID_LEN];
    WS_CHAR USER_NAME[USER_NAME_LEN];
    WS_CHAR USER_PWD[PASSWORD_LEN];
    WS_CHAR BIND_EMAIL[EMAIL_ADDR_LEN];
    WS_CHAR BIND_UUID[UID_LEN];
    WS_S32  BIND_UUID_SWITCH;
    WS_CHAR LOGIN_UUID[UID_LEN];
    int  USER_STATUS;
    WS_CHAR P2PSER_IP[IP_STR_LEN];
    WS_S32  P2PSER_PORT;
    WS_CHAR P2PSER_UID[UID_LEN];
    WS_CHAR APP_WAN_IP[IP_STR_LEN];
    WS_S32  APP_WAN_PORT;
    WS_CHAR APP_LAN_IP[IP_STR_LEN];
    WS_S32  APP_LAN_PORT;
    WS_S32  alarm_msg_push ;
    WS_S32  md_msg_push ;
    WS_S32  friend_msg_push ;
    WS_S32  friend_share_push ;
    WS_S32  friend_file_push ;
    WS_CHAR APP_LOGIN_TIME[32]; 		//add by ronghl 2017-01-12:  �û���¼ʱ���
    struct _APP_USER_INFO* next;
}APP_USER_INFO;

//app��uid + "friend"  app�ĺ��ѱ�
typedef struct _friend_node
{
   WS_CHAR FRIEND_NAME[USER_NAME_LEN];
   WS_CHAR UsrUID[UID_LEN];		// UID ��Ϣ
   WS_CHAR FRIEND_REMARK[FRIEND_REMARK_LEN];
   struct _friend_node* next;
}friend_node;

//˽���豸��ͨ�� ����
typedef struct _dev_ch_remark_info
{
    WS_CHAR           DEVICE_UID[UID_LEN];
    WS_S32            chanIndex ;
    WS_CHAR           DEVICE_CH_REMARK[FRIEND_REMARK_LEN];
    struct _dev_ch_remark_info* next;
}dev_ch_remark_info;

//app�� ˽��device��
typedef struct _device_node
{
    WS_CHAR DEVICE_UID[UID_LEN];
    WS_CHAR DEVICE_NAME[USER_NAME_LEN];
    WS_CHAR DEVICE_PWD[PASSWORD_LEN];
    WS_CHAR DEVICE_REMARK[FRIEND_REMARK_LEN];
    int           ChanCnt ;                                                                 // �����豸֧�ֵ�ͨ������
	struct  _dev_ch_remark_info* DEVICE_CHANCNT_REMARK;  //˽���豸��ͨ���ı�ע��
    struct _device_node* next;
}device_node;

//�豸������ ������Ϣ��
typedef struct _dev_info
{
   WS_CHAR  DEVICE_UID[UID_LEN]; 
   int            ChanCnt;                                                                  // �豸֧�ֵ���Ƶͨ������  
   WS_CHAR  PRIVATE_USER_UID[UID_LEN];
   WS_CHAR  PRIVATE_USER_NAME[USER_NAME_LEN];
   WS_BOOL  DEVICE_STATUS;
   WS_CHAR  USER_P2PSER_IP[IP_STR_LEN];
   WS_CHAR  USER_P2PSER_UID[UID_LEN];
   WS_S32     USER_P2PSER_PORT;
   WS_CHAR  ALARM_SER_IP[IP_STR_LEN];
   WS_CHAR  ALARM_SER_UID[UID_LEN];
   WS_S32     ALARM_SER_PORT;
   WS_S32     NEW_DEVICE;
   WS_CHAR  DEVICE_PASSWORD[PASSWORD_LEN];
   WS_CHAR  DEVICE_USER_NAME[USER_NAME_LEN];
   WS_CHAR  DEVICE_WAN_IP[IP_STR_LEN];
   WS_S32    DEVICE_WAN_PORT;                                                                       // �ϲ��豸���߱����豸������Ϣ��
   //add by ronghl 2017-01-06 start
   	WS_CHAR DEVICE_LAN_IP[IP_STR_LEN];
   WS_CHAR DEVICE_LOGIN_TIME[32];
   WS_S32 	DEVICE_LAN_PORT;
   WS_S32	DEVICE_TYPE;
   //add by ronghl 2017-01-06 end
   struct _dev_ch_share_stat_info *pShare;      //�豸������Ϣ
   struct _dev_info* next;
}dev_info;

// ��¼�����û���Ϣ
typedef struct _private_dev_share
{
    WS_CHAR			        DevUID[UID_LEN];		        // �豸UID ��Ϣ
    WS_S32			        chanIndex ;
    WS_CHAR			        UsrOwnerUID[UID_LEN];	 // �豸˽������Ϣ
    WS_CHAR			        UsrSharedUID[UID_LEN];	 // �����������Ϣ
    WS_CHAR                        UsrSharedName[USER_NAME_LEN];                        // �����������
    WS_CHAR			        ChRemark[128];	        // ���ѷ���ͨ����ע��Ϣ
    WS_S32			        share_state;		 // ��ǰ�������״̬
    time_t					Start_time;		// ��������Ŀ�ʼʱ��
    WS_CHAR			        LoginName[48];	// �豸��¼�˻�
    WS_CHAR			        LoginPass[48];	// �豸��¼����
    struct _private_dev_share	*pNext ;
}private_dev_share;

// add by khs 2016.12.12
typedef struct _device_node_ex
{
    WS_CHAR DEVICE_UID[UID_LEN];
    int chanIndex ;
    WS_CHAR DEVICE_NAME[USER_NAME_LEN];
    WS_CHAR DEVICE_PWD[PASSWORD_LEN];
    WS_CHAR DEVICE_REMARK[FRIEND_REMARK_LEN];
    int           ChanCnt ;                                                                 // �����豸֧�ֵ�ͨ������
}device_node_ex;

//�豸��ͨ������״̬��
typedef struct _dev_ch_share_stat_info
{
    WS_S32            chanIndex ;
    WS_CHAR		UsrUID[UID_LEN];		// ���������UID ��Ϣ
    WS_CHAR         UsrName[USER_NAME_LEN];
    struct _dev_ch_share_stat_info* next;
}dev_ch_share_stat_info;

//add by khs 2016.12.8 UID������ӵ�������
typedef struct _UID_node
{
     WS_CHAR mid[UID_LEN];
     char  mid_type[USER_NAME_LEN];
     char  mid_info[USER_NAME_LEN];
     int NUMB; //uid���
     unsigned long mid_time;
}UID_node;
//add by khs 2016.12.8 end


// add by linhh 20161202 : �ܶ�Ӧ��������ݽṹ��һ���ģ���Ҫ���⴦��
typedef struct _CommonRespPkt   
{
    RespCMDHeader Header;
}CommonRespPkt;


//==================add by ronghl 2017-01-14 start==========================// 
typedef struct _RegStrRelayInfoReqPkt
{
	ReqCMDHeader Header;
	int PageIndex;				//�����ҳ��
	int PageSize;
}RegStrRelayInfoReqPkt;

typedef struct _RelayInfo
{
	char AppUserName[USER_NAME_LEN];
	char DeviceUID[UID_LEN];
	char RelayStartTime[32];
	int  AvgBitRate;
	struct _RelayInfo* pNext;
}RelayInfo;

typedef struct _RegStrRelayInfoRespPkt
{
	RespCMDHeader Header;
	int PktCnt;
    int PktSeq;
	int	PageIndex;
	int PageTotal;
	RelayInfo* pRelay;
}RegStrRelayInfoRespPkt;

typedef struct _RegStrMessageInfoReqPkt
{
	ReqCMDHeader Header;
	int PageIndex;
	int PageSize;
}RegStrMessageInfoReqPkt;

typedef struct _MessageInfo
{
	int MessageSessionID;
	char SponsorUserName[USER_NAME_LEN];
	ClientAcceptor* pAcceptor;
	char MessageStartTime[32];
	int FileSize;
	struct _MessageInfo* pNext;
}MessageInfo;

typedef struct _RegStrMessageInfoRespPkt
{
	RespCMDHeader Header;
	int PktCnt;
	int PktSeq;
	int PageIndex;
	int PageTotal;
	MessageInfo* pMessage;
}RegStrMessageInfoRespPkt;

typedef struct _LogMessage
{
	char LogTime[32];
	char Message[256];
	struct _LogMessage* Next;
}LogMessage;

typedef struct _RegLogPageReqPkt
{
	ReqCMDHeader Header;
	int pageIndex;
	int pageSize;
}RegLogPageReqPkt;

typedef struct _RegLogPageRespPkt
{
	RespCMDHeader Header;
	int pageIndex;
	int pageTotal;
	int PktCnt;
 	int PktSeq;
	LogMessage* pLog;
}RegLogPageRespPkt;
//=====================add by ronghl 2017-01-14 end========================//

typedef struct  _ClientOnlineStatus
{
	char AppUsrName[48];
	char AppPasswd[48];
	char AppUID[48];
	int AppStatus;    			//modify by ronghl 2017-04-13
	char WanIP[16];    			//���Client���ߺ�Ĺ���IP
	int  WanPort;    			//���Client���ߺ�Ĺ���Port
	char LanIP[16]; 		 	//���Client���ߺ�ľ�����IP
	int  LanPort;     			//���Client���ߺ�ľ�����Port
	char PhoneUUID[UID_LEN];  	//��Ϊ��ʱ��ʾ��Ҫ��֤�ֻ��ն�UUID,Ϊ��ʱ����֤..
	char LoginUID[UID_LEN];     //��¼��ǰ��¼���ն�UID
	int  AlarmPushSwitch;		//add by ronghl 2017-02-20
	int  AlarmMDPush;			//add by ronghl 2017-03-30
} ClientOnlineStatus;

typedef struct _Reg2P2PclientOnlineStatusReqPkt    /* 0x0a01 */
{
	ReqCMDHeader Header;
	int PktCnt;
	int PktSeq;
  	int UserNum;					//�÷�Ƭ���а������ٵ��û���Ϣ
    ClientOnlineStatus pOnlineUser[0];
} Reg2P2PclientOnlineStatusReqPkt;	//ÿ���û���Ϣ��СԼΪ356�ֽ����ϣ���������3-4����


typedef struct _Reg2P2PclientOnlineStatusRespPkt	 /* 0x0a02 */
{
	RespCMDHeader Header;
  	char P2PServerUID[UID_LEN];
	int  MissPktNum;
    int  MissPktSeq[256];
} Reg2P2PclientOnlineStatusRespPkt;


typedef struct _DeviceOnlineStatus
{
	char DevUID[UID_LEN];
	int  DevStatus;     		//��¼���ߡ��ػ�����
	/* delete by ronghl 2017-04-01 : not usable
	char P2PSerIP[IP_STR_LEN];  //���Device��¼��P2P Server IP
	int  P2PSerPort;     		//���Device��¼��P2P Server Port
	char P2PSerUID[UID_LEN]; 	//���Device��¼��P2P Server UID
	*/
	char WanIP[IP_STR_LEN];   	//���Device���ߺ�Ĺ���IP
	int  WanPort;    			//���Device���ߺ�Ĺ���Port
	char LanIP[IP_STR_LEN];  	//���Device���ߺ�ľ�����IP
	int  LanPort;     			//���Device���ߺ�ľ�����Port
	//ronghl 2017-03-30:  delete login time 
} DeviceOnlineStatus;

typedef  struct _Reg2P2PdeviceOnlineStatusReqPkt   /* 0x0a03 */
{
	ReqCMDHeader Header;
	int PktCnt;
	int PktSeq;
	int DeviceNum;
    DeviceOnlineStatus OnlineDevice[];
} Reg2P2PdeviceOnlineStatusReqPkt;

typedef  struct _Reg2P2PdeviceOnlineStatusRespPkt   /* 0x0a04 */
{
	RespCMDHeader Header;
	char P2PServerUID[UID_LEN];
	int MissPktNum;
    int MissPktSeq[256];
} Reg2P2PdeviceOnlineStatusRespPkt;

typedef struct _ConfigFileDataPkt				//0x0882
{
	 int MediaSessionID;			 //ý��ỰID
	 int PktCnt;				 //ý�����ݱ��ְ�������
	 int PktSeq;				 //���Ự��ǰ����ķ�Ƭ��ţ���1��ʼ
	 int DataSize;				 //��3���ֽڱ�ʾ��ý�����ݸ���,���λ1���ֽڱ�ʾ����Word����
	 char *DataBuf; 			 //��ý������ָ��	
}ConfigFileDataPkt;

/* hzg added User notify Server switch work node Notify */
typedef struct _ChangeServerWorkModeNotifyPkt	   //0x0910
{
    ReqCMDHeader 	Header;
    int   work_mode;        /* 0 ��Ԫ���Թ���ģʽ , 1 ���ɲ��Թ���ģʽ*/
}ChangeServerWorkModeNotifyPkt	;


/*add by ronghl 2017-04-01: start test user reliable reciever*/
#define CMD_BINARY_RESPONSE_PKT  	(0x0a07)
//delete by ronghl 2017-04-13: delete cmd CMD_BINARY_REQUEST_PKT, no use
typedef  struct 
{
	int 	CMD;		//���ݰ�����....
	int  	PktCnt;		//�ְ�����....
	int  	PktSeq;		//��ǰ�ְ����....
	int   	SeqNo;		//��ǰ�ְ������кţ������ڷ��Ͷ�Ψһ��ʶ���ͻỰ ....
	int 	PktSize;		//��ǰ�ְ������ݴ�С������������ͷBinaryReqHeader �����ݳ���...
}BinaryReqHeader;

typedef struct 
{
	int 		CMD;			//���ݰ�������.....
	int   		SeqNo;			//��Ӧ�ķ������ݶε����к�...
	int 		Result;			//���ս��...
	int   		DataSize;		//������BinaryRespHeader���ֵ����ݲ��ֳ���...
}BinaryRespHeader;

typedef WS_VOID (*DataHandler)(char* Data, int DataLen);
typedef struct _CmdFuncMap
{
	int 		cmd;
	DataHandler handler;
}CmdFuncMap;

/* WEB��ȡ���ߵķ�������Ϣ */
typedef struct _ServerInfo
{
    char    ServerUID[UID_LEN];
    int     ServerType;
    struct _ServerInfo* Next;
}ServerInfo;

typedef struct _deviceInfoPage
{
	char DEVICE_UID[UID_LEN];
	int  DEVICE_CHANNEL_COUNT;
	int  DEVICE_TYPE;
	char DEVICE_LAN_IP[IP_STR_LEN];
	int  DEVICE_LAN_PORT;
	char DEVICE_WAN_IP[IP_STR_LEN];
	int  DEVICE_WAN_PORT;
	int  DEVICE_STATUS;
	char P2PSER_UID[UID_LEN];
	char DEVICE_PRIVATOR[USER_NAME_LEN];
	struct _deviceInfoPage* NEXT;
}DeviceInfoPage;

typedef struct _UserInfoPage
{
	char UserName[USER_NAME_LEN];
	char UserLanIP[IP_STR_LEN];
	int UserLanPort;
	char UserWanIP[IP_STR_LEN];
	int UserWanPort;
	int UserStatus;
	char P2PSerUID[UID_LEN];
	struct _UserInfoPage* pNext;
}UserInfoPage;

typedef struct _userDevicePage
{
	char DEVICE_UID[UID_LEN];
	int  DEVICE_CHANNEL_INDEX;
	int  DEVICE_STATUS;
	char P2PSER_UID[UID_LEN];
	char DEVICE_PRIVATOR[UID_LEN];
	struct _userDevicePage* pNext;
}UserDevicePage;

typedef struct _P2PServerPageInfo
{
    char P2PSER_IP[IP_STR_LEN];
    char P2PSER_UID[UID_LEN]; //uid ��Ϣ
    int  P2PSER_UPBAND;	
	int P2PSER_DOWNBAND;
	char P2PSER_TIME[32];
	int ServiceUserNum;
	int ServerDeviceNum;
    struct _P2PServerPageInfo* pNext;//��������
}P2PServerPageInfo;

typedef struct _P2PSerServiceUserInfo
{
	char UID[UID_LEN];
	char LoginTime[64];
	char type[32];
	struct _P2PSerServiceUserInfo* pNext;
}P2PSerServiceUserInfo;

#ifdef __cplusplus
}//extern "C" {
#endif

#endif  /*#ifndef _TECOM_BASE_H_*/












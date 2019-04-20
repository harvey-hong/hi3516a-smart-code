#ifndef _WS_USR_MANAGE_DEF_H_
#define _WS_USR_MANAGE_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"

/* add by zhangmq 20180527 start */
//---------------------------------------- �û������� ------------------------------------
#define WS_CFG_GROUP_KEY1               "Group"
#define WS_CFG_GROUP_NUM                "Num"   //�û�������Ŀ

#define WS_CFG_GROUP_INFO               "Grp"   //ÿ���û�����Grp0��Grp1��Grp2�ȼ�¼
#define WS_CFG_GROUP_INFO_NAME          "Name"  //�û�����

#define WS_CFG_GROUP_AUTHOR_CH_PB       "ChPb"      //�ط�Ȩ��  
#define WS_CFG_GROUP_AUTHOR_CH_BACK     "ChBack"    //����Ȩ��  
#define WS_CFG_GROUP_AUTHOR_CH_LV       "ChLv"      //Ԥ��Ȩ��
#define WS_CFG_GROUP_AUTHOR_CH_CFG      "ChCfg"     //ͨ��Ȩ��

#define WS_CFG_GROUP_AUTHOR_INQUIRE     "Inquire"   //��ϢȨ��
#define WS_CFG_GROUP_AUTHOR_ALARM       "AlarmCtl"  //����Ȩ��
#define WS_CFG_GROUP_AUTHOR_NET         "NetCtl"    //����Ȩ��
#define WS_CFG_GROUP_AUTHOR_SYSTEM      "SysCtl"    //ϵͳȨ��

//---------------------------------------- �û����� ------------------------------------
#define WS_CFG_USR_KEY1             "User"
#define WS_CFG_USR_NUM              "Num"   //�û�����

#define WS_CFG_USR_INFO             "Usr"   //ÿ���û���Usr0��Usr1��Usr2�ȼ�¼
#define WS_CFG_USR_INFO_NAME        "Name"      //�û���
#define WS_CFG_USR_INFO_GRP_NAME    "GrpName"   //�����ĸ���
#define WS_CFG_USR_INFO_PASSWD      "Passwd"    //����
#define WS_CFG_USR_INFO_PASSWD_NEW  "Passwdnew_1.0"  //�¼��ܷ�ʽ���ܺ������        
#define WS_CFG_ATTRBUTE             "attribute"   //add by lmw 20170407



//add zmq �ڴ�XML�ļ��ڵ��ֶζ���[2018-05-11 11:31]
//һ���ڵ�
#define WS_GROUP_KEY_NAME   	 "Group"
#define WS_USR_KEY_NAME     	 "User" 
#define WS_USR_LOGIN_KEY_NAME  "UserLogin"

//�����ڵ�
#define WS_GROUP_NUM 		     	 "GroupNum"	
#define WS_USER_NUM 	      		 "UserNum"
#define WS_LOGIN_NUM 				 "LoginNum"
#define WS_CHILD_GROUP_KEY_PRE_NAME  "Cgrp"
#define WS_CHILD_USR_KEY_PRE_NAME    "Cusr"
#define WS_CHILD_LOGIN_KEY_PRE_NAME  "Clogin"

//�����ڵ�
#define WS_GROUP_INDEX      			"GroupIndex"
#define WS_GROUP_NAME		  			"GroupName"
#define WS_IS_SUPER_GROUP   			"IsSuperGroup"
#define WS_AUTHORITY_NVR_CH_PB_MASK  	"Nvr_ch_pb_mask"
#define WS_AUTHORITY_NVR_CH_MASK 		"Nvr_ch_back_mask"
#define WS_AUTHORITY_NVR_CH_LV_MASK  	"Nvr_ch_lv_mask"
#define WS_AUTHORITY_NVR_CH_CFG_MASK  	"Nvr_ch_cfg_mask"
#define WS_AUTHORITY_INQUIRE_INFO     	"Inquire_info"
#define WS_AUTHORITY_ALARM_CTL		 	"Alarm_ctl"
#define WS_AUTHORITY_NET_CTL           	"net_ctl"
#define WS_AUTHORITY_SYSTEM_CTL        	"system_ctl"
#define WS_IS_DELETED		  				"IsDeleted" //��,�û�,��¼��Ϣ�����д˽ڵ�

#define WS_USR_INDEX 		 	"UserIndex"
#define WS_USR_NAME         	"UserName"
#define WS_IS_SUPER_USR     	"IsSuperUser"
#define WS_PASSWORD			"PassWord"

#define WS_USR_HAND_NUM     	"UserHandNum"
#define WS_MAC 				 	"MAC"
#define WS_IP 				 	"IP"
#define WS_IS_LOCAL_LOGIN 		"IsLocalLogin"
#define WS_LOGIN_PROTOCAL     "LoginProtocol"
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef struct
{
    WS_S32  nvr_ch_pb_mask;         //�ط�ͨ��Ȩ��
    WS_S32  nvr_ch_back_mask;       //����Ȩ��
    WS_S32  nvr_ch_lv_mask;         //Ԥ������Ȩ��(����Ƶ)
    WS_S32  nvr_ch_cfg_mask;        //ͨ������Ȩ��(�������������¼��ƻ�����ɫ����)

    WS_S32 inquire_info;           //��Ϣ��ѯ
    WS_S32 alarm_ctl;
    WS_S32 net_ctl;
    WS_S32 system_ctl;             //�Ƿ���ϵͳ����Ȩ��
} ws_authority;

typedef struct
{
    WS_CHAR user_group_name[ws_utility::WS_NVR_MAX_GROUP_NAME_LEN];
    ws_authority authority;
} ws_user_group_info;

typedef struct
{
    WS_CHAR     user_name[ws_utility::WS_NVR_MAX_USR_NAME_LEN+1];
    WS_CHAR     user_group_name[ws_utility::WS_NVR_MAX_GROUP_NAME_LEN+1];
}ws_user_and_group_info;

typedef enum
{
    WS_AUTHOR_CHECK_UNKNOW,

    WS_AUTHOR_CHECK_NVR_CH_PB,      //nvrͨ���ط�Ȩ��
    WS_AUTHOR_CHECK_NVR_CH_BACK,    //nvrͨ���ļ�����Ȩ��
    WS_AUTHOR_CHECK_NVR_CH_LV,      //nvrͨ��Ԥ��Ȩ�ޣ������߼��豸��
    WS_AUTHOR_CHECK_NVR_CH_CFG,     //ͨ������: ����¼��ƻ���ͨ��������ͨ�����ã�ͨ��ͼ�����ã�ͨ��PTZ���ã�ͨ��PTZ���ƣ��ƶ����

    WS_AUTHOR_CHECK_INFO_CTL,       //��Ϣ��ѯ����: ����ͨ������״̬��ѯ��Ӳ�̲�ѯ����־��ѯ
    WS_AUTHOR_CHECK_ALARM_CTL,      //��������: ��������������棬�쳣�������
    WS_AUTHOR_CHECK_NET_CTL,        //�������: �����������ý��棬PPPoE���棬��̬�������棬SMTP���棬WIFI����
    WS_AUTHOR_CHECK_SYSTEM_CTL,     //ϵͳ���ƣ���ͨ���޹ص������������

    //ֻ�г����û��������ɾ���û����û���
    //�����û��ͳ����û��鱾���ܱ�ɾ��
    WS_AUTHOR_CHECK_ADD_DEL_USR = 0x80000000,   //���ɾ���û�
    WS_AUTHOR_CHECK_MODIFY_USR_PASSWD,          //�޸��û�����
    WS_AUTHOR_CHECK_MODIFY_USR_GRP,             //�޸��û���������

    WS_AUTHOR_CHECK_ADD_DEL_GROUP,              //���ɾ����
    WS_AUTHOR_CHECK_MODIFY_GROUP,               //�޸���Ȩ��
    WS_AUTHOR_CHECK_LOGIN_INVALID,              //����¼�Ƿ���Ч
} ws_authority_check_type;

typedef struct
{
    char group_name[ws_utility::WS_NVR_MAX_GROUP_NAME_LEN]; //�����ĸ���
    WS_S32 is_login;
} ws_usr_state_info;

typedef struct
{
    char name[ws_utility::WS_NVR_MAX_USR_NAME_LEN];
    char mac[ws_utility::WS_NVR_MAC_STRING_LEN];
    char ip[ws_utility::WS_NVR_IPV6_STRING_LEN];
    WS_S32 is_local_login;
} ws_usr_info_login;

typedef struct
{
    char name[ws_utility::WS_NVR_MAX_USR_NAME_LEN];
    char mac[ws_utility::WS_NVR_MAC_STRING_LEN];
    char ip[ws_utility::WS_NVR_IPV6_STRING_LEN];
    WS_BOOL is_local_login;
    time_t      login_time;
    ws_utility::login_protocol_type protocol_type;
} ws_usr_info_login_protocol;

struct ws_usr_node;
struct ws_group_node;
	
typedef struct ws_usr_login_info
{
    WS_USR_HAND  hand;
    time_t              login_time;
    WS_BOOL         is_local_login;
    char mac[ws_utility::WS_NVR_MAC_STRING_LEN];
    char ip[ws_utility::WS_NVR_IPV6_STRING_LEN];

    ws_usr_node     *usr;	
    ws_utility::login_protocol_type protocol_type;
    ws_usr_login_info *pre;
    ws_usr_login_info *next;
}ws_usr_login_info;

typedef struct ws_usr_node
{
    char name[ws_utility::WS_NVR_MAX_USR_NAME_LEN];
    char passwd[ws_utility::WS_NVR_MAX_USR_PASSWD_LEN];

    WS_BOOL is_supper_usr;
    WS_BOOL is_deleted; 

    ws_group_node *grp; 

    ws_usr_login_info *login_head;
    ws_usr_login_info *login_tail;

    ws_usr_node *pre;
    ws_usr_node *next;
} ws_usr_node;
	
	typedef struct ws_group_node
	{
		char name[ws_utility::WS_NVR_MAX_GROUP_NAME_LEN];
		ws_authority authority;
	
		WS_BOOL is_supper_group;
		WS_BOOL is_deleted; 
	
		ws_usr_node *usr_head;
		ws_usr_node *usr_tail;
	
		ws_group_node *pre;
		ws_group_node *next;
	} ws_group_node;

/* add by zhangmq 20180527 start */
//add zmq �ڴ�XML�ļ���Ӧ�Ľṹ[2018-05-11 16:10]
//add zmq ����Ϣ���ݽṹ
typedef struct
{
	WS_S32 groupIndex;
	char name[ws_utility::WS_NVR_MAX_GROUP_NAME_LEN];
	ws_soft::ws_authority authority;

	WS_S32 is_supper_group;
	WS_S32 is_deleted; 
} ws_ugm_group_cfg;

//add zmq �û���Ϣ���ݽṹ
typedef struct
{
	WS_S32 userIndex;
	char name[ws_utility::WS_NVR_MAX_USR_NAME_LEN];
	char grp_name[ws_utility::WS_NVR_MAX_GROUP_NAME_LEN];  //�����ĸ��û���
	char passwd[ws_utility::WS_NVR_MAX_USR_PASSWD_LEN];
	//�����û�����
	WS_S32 is_supper_usr;
    WS_S32 is_deleted; 
} ws_ugm_user_cfg;

typedef struct
{
	//������¼�û���½����
    WS_S32  hand;
	char usr_name[ws_utility::WS_NVR_MAX_USR_NAME_LEN];
	char grp_name[ws_utility::WS_NVR_MAX_GROUP_NAME_LEN];
	WS_S32 is_deleted; 
    char mac[ws_utility::WS_NVR_MAC_STRING_LEN];
    char ip[ws_utility::WS_NVR_IPV6_STRING_LEN];
	WS_S32      is_local_login;
	ws_utility::login_protocol_type protocol_type;
}ws_ugm_login_cfg;
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_NVR_MODEL_API_H_



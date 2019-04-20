#ifndef _WS_USR_MANAGE_DEF_H_
#define _WS_USR_MANAGE_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"

/* add by zhangmq 20180527 start */
//---------------------------------------- 用户组配置 ------------------------------------
#define WS_CFG_GROUP_KEY1               "Group"
#define WS_CFG_GROUP_NUM                "Num"   //用户组总数目

#define WS_CFG_GROUP_INFO               "Grp"   //每个用户组用Grp0，Grp1，Grp2等记录
#define WS_CFG_GROUP_INFO_NAME          "Name"  //用户组名

#define WS_CFG_GROUP_AUTHOR_CH_PB       "ChPb"      //回放权限  
#define WS_CFG_GROUP_AUTHOR_CH_BACK     "ChBack"    //备份权限  
#define WS_CFG_GROUP_AUTHOR_CH_LV       "ChLv"      //预览权限
#define WS_CFG_GROUP_AUTHOR_CH_CFG      "ChCfg"     //通道权限

#define WS_CFG_GROUP_AUTHOR_INQUIRE     "Inquire"   //信息权限
#define WS_CFG_GROUP_AUTHOR_ALARM       "AlarmCtl"  //报警权限
#define WS_CFG_GROUP_AUTHOR_NET         "NetCtl"    //网络权限
#define WS_CFG_GROUP_AUTHOR_SYSTEM      "SysCtl"    //系统权限

//---------------------------------------- 用户配置 ------------------------------------
#define WS_CFG_USR_KEY1             "User"
#define WS_CFG_USR_NUM              "Num"   //用户总数

#define WS_CFG_USR_INFO             "Usr"   //每个用户用Usr0，Usr1，Usr2等记录
#define WS_CFG_USR_INFO_NAME        "Name"      //用户名
#define WS_CFG_USR_INFO_GRP_NAME    "GrpName"   //属于哪个组
#define WS_CFG_USR_INFO_PASSWD      "Passwd"    //密码
#define WS_CFG_USR_INFO_PASSWD_NEW  "Passwdnew_1.0"  //新加密方式加密后的密码        
#define WS_CFG_ATTRBUTE             "attribute"   //add by lmw 20170407



//add zmq 内存XML文件节点字段定义[2018-05-11 11:31]
//一级节点
#define WS_GROUP_KEY_NAME   	 "Group"
#define WS_USR_KEY_NAME     	 "User" 
#define WS_USR_LOGIN_KEY_NAME  "UserLogin"

//二级节点
#define WS_GROUP_NUM 		     	 "GroupNum"	
#define WS_USER_NUM 	      		 "UserNum"
#define WS_LOGIN_NUM 				 "LoginNum"
#define WS_CHILD_GROUP_KEY_PRE_NAME  "Cgrp"
#define WS_CHILD_USR_KEY_PRE_NAME    "Cusr"
#define WS_CHILD_LOGIN_KEY_PRE_NAME  "Clogin"

//三级节点
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
#define WS_IS_DELETED		  				"IsDeleted" //组,用户,登录信息均会有此节点

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
    WS_S32  nvr_ch_pb_mask;         //回放通道权限
    WS_S32  nvr_ch_back_mask;       //备份权限
    WS_S32  nvr_ch_lv_mask;         //预览控制权限(音视频)
    WS_S32  nvr_ch_cfg_mask;        //通道配置权限(包括编码参数、录像计划、颜色配置)

    WS_S32 inquire_info;           //信息查询
    WS_S32 alarm_ctl;
    WS_S32 net_ctl;
    WS_S32 system_ctl;             //是否有系统控制权限
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

    WS_AUTHOR_CHECK_NVR_CH_PB,      //nvr通道回放权限
    WS_AUTHOR_CHECK_NVR_CH_BACK,    //nvr通道文件备份权限
    WS_AUTHOR_CHECK_NVR_CH_LV,      //nvr通道预览权限，后续高级设备用
    WS_AUTHOR_CHECK_NVR_CH_CFG,     //通道管理: 包括录像计划，通道搜索，通道配置，通道图像配置，通道PTZ配置，通道PTZ控制，移动侦测

    WS_AUTHOR_CHECK_INFO_CTL,       //信息查询管理: 包括通道连接状态查询，硬盘查询，日志查询
    WS_AUTHOR_CHECK_ALARM_CTL,      //报警管理: 包括报警管理界面，异常处理界面
    WS_AUTHOR_CHECK_NET_CTL,        //网络管理: 包括网络配置界面，PPPoE界面，动态域名界面，SMTP界面，WIFI界面
    WS_AUTHOR_CHECK_SYSTEM_CTL,     //系统控制，与通道无关的其他各项操作

    //只有超级用户才能添加删除用户和用户组
    //超级用户和超级用户组本身不能被删除
    WS_AUTHOR_CHECK_ADD_DEL_USR = 0x80000000,   //添加删除用户
    WS_AUTHOR_CHECK_MODIFY_USR_PASSWD,          //修改用户密码
    WS_AUTHOR_CHECK_MODIFY_USR_GRP,             //修改用户所属的组

    WS_AUTHOR_CHECK_ADD_DEL_GROUP,              //添加删除组
    WS_AUTHOR_CHECK_MODIFY_GROUP,               //修改组权限
    WS_AUTHOR_CHECK_LOGIN_INVALID,              //检测登录是否有效
} ws_authority_check_type;

typedef struct
{
    char group_name[ws_utility::WS_NVR_MAX_GROUP_NAME_LEN]; //隶属哪个组
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
//add zmq 内存XML文件对应的结构[2018-05-11 16:10]
//add zmq 组信息数据结构
typedef struct
{
	WS_S32 groupIndex;
	char name[ws_utility::WS_NVR_MAX_GROUP_NAME_LEN];
	ws_soft::ws_authority authority;

	WS_S32 is_supper_group;
	WS_S32 is_deleted; 
} ws_ugm_group_cfg;

//add zmq 用户信息数据结构
typedef struct
{
	WS_S32 userIndex;
	char name[ws_utility::WS_NVR_MAX_USR_NAME_LEN];
	char grp_name[ws_utility::WS_NVR_MAX_GROUP_NAME_LEN];  //属于哪个用户组
	char passwd[ws_utility::WS_NVR_MAX_USR_PASSWD_LEN];
	//新增用户属性
	WS_S32 is_supper_usr;
    WS_S32 is_deleted; 
} ws_ugm_user_cfg;

typedef struct
{
	//新增记录用户登陆属性
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



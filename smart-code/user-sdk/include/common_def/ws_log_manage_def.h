#ifndef _WS_LOG_MANAGE_H_
#define _WS_LOG_MANAGE_H_

#include "ws_comm_type.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

#define WS_LOG_DB_NAME			"/config/sys_log.db"
#define WS_LOG_DB_TABLE_NAME	      "sys_log_table"
#define WS_LOG_ROTATE_NUM		100
#define WS_LOG_MAX_NUM			5000 
#define MAX_LINE_NUM                        10 

typedef enum
{
    LOG_MAIN_UNKNOW = 0,
    LOG_MAIN_ALARM      = 0x01, //告警
    LOG_MAIN_MD            = 0x02, //移动侦测
    LOG_MAIN_OPERATION  = 0x04, //操作
    LOG_MAIN_GENERAL    = 0x08, //普通
    LOG_MAIN_EXCEPTION  = 0x80, //异常
    LOG_MAIN_ALL = 0xFFFFFFFF,
} ws_log_main_type;

typedef enum
{
    LOG_SUB_UNKNOW,

    //---------- 系统 -----------------
    LOG_SUB_LOCAL_USR_LOGIN = 0x1000,   //本地用户登录
    LOG_SUB_LOCAL_USR_LOGOUT,   //本地用户登出

    LOG_SUB_RMT_USR_LOGIN,  //远端用户登录
    LOG_SUB_RMT_USR_LOGOUT, //远端用户登出

    LOG_SUB_POWER_ON,   //开机
    LOG_SUB_POWER_OFF,  //关机
    LOG_SUB_REBOOT,     //重启

    //---------- MD -----------------
    LOG_SUB_MD = 0x2000,        //移动侦测
    //LOG_SUB_MD_DISAPPEAR, //(移动侦测消失取消，通过结束时间判断)

    //---------- AI -----------------
    LOG_SUB_AI = 0x3000,        //报警输入
    //LOG_SUB_AI_DISAPPEAR, //(报警输出消失取消，通过结束时间判断)

    //---------- 操作 -----------------
    LOG_SUB_MODIFY_TIME = 0x4000,   //修改系统时间
    LOG_SUB_DST_ON,                 //开启夏时制 
    LOG_SUB_DST_OFF,                //关闭夏时制 
    LOG_SUB_MODIFY_ALARM_LINK,      //修改报警联动	
    LOG_SUB_BACKUP_FILE,            //备份录像数据
    LOG_SUB_RESUME_DEFAULT,         //恢复默认
    LOG_SUB_RESUME_FACTORY,         //恢复出厂		
    LOG_SUB_RECMANUAL_ON,           //开启手动录像 
    LOG_SUB_RECMANUAL_OFF,          //关闭手动录像 
    LOG_SUB_UPGRADE,                //升级
    LOG_SUB_RESET_PASSWORD,         //密码复位
    LOG_SUB_CLR_ALARM,				//消除警报

    LOG_SUB_DISKMODE,				//硬盘控制模式
    LOG_SUB_RECPLAN,				//录像计划修改
	
    LOG_SUB_DISKFORMAT, 			//硬盘格式化
    LOG_SUB_AI_TYPECHANGE,			//修改报警输入类型
    LOG_SUB_MD_AREACHANGE,			//通道移动侦测区域修改
    LOG_SUB_MD_SENS,				//移动侦测灵敏度修改

    LOG_SUB_RECMANUAL,			// 录像模式修改，是对硬盘控制模式的补充，记录源模式和目标模式
    LOG_SUB_MODIFY_IO_LINK,		// 传感器报警联动，传感器报警联动项修改记录日志
    LOG_SUB_MOTION_LINK,			// 移动侦测报警联动，移动侦测报警联动项修改记录日志
    LOG_SUB_VIDEO_LOST_LINK,		// 视频丢失报警联动，视频丢失报警联动项修改记录日志
    LOG_SUB_VIDEO_COVER_LINK,	// 视频遮盖报警联动，视频遮盖报警联动项修改记录日志
    LOG_SUB_DELETE_DATA,			// 数据删除，硬盘数据主动删除记录日志


    //---------- 异常 -----------------
    LOG_SUB_ABNORMAL_SHUTDOWN = 0x5000, //异常关机

    LOG_SUB_ABNORMAL_NO_DISK,				//未接硬盘
    LOG_SUB_ABNORMAL_DISK_ERROR,			//硬盘访问异常
    LOG_SUB_ABNORMAL_DISK_LOST,			//硬盘丢失
    LOG_SUB_ABNORMAL_NO_SPACE,			//硬盘满
    LOG_SUB_ABNORMAL_NET_ERROR, 		//网络异常
    LOG_SUB_ABNORMAL_IP_CONFLICT,
    LOG_SUB_VIDEO_LOSS = 0x6000,		// 记录视频丢失时间，操作逻辑同移动侦测逻辑
    LOG_SUB_VIDEO_COVER,				// 记录视频遮盖时间，操作逻辑同移动侦测逻辑
} ws_log_sub_type;

typedef struct
{
    time_t start_time;  //日志起始时间
    time_t stop_time;   //日志结束时间

    ws_log_main_type type;  //查询类型
    WS_U32 ch_mask[ws_utility::WS_NVR_MAX_MASK_NUM];	//change by khs 2017.4.14
} ws_log_inquiry_ctl;

typedef struct
{
    time_t time;    //记录时间
    time_t end_time; //事件结束时间(不需要记录的置为-1)
    int ch_idx;     //通道

    ws_log_main_type main_type;
    ws_log_sub_type sub_type;

    //用户登录IP，本地用户为ip_v4和ip_v6全部为0
    WS_U32 ip_v4;
    WS_U32 ip_v6[4];

    WS_CHAR usr_name[32];

    WS_U32 node_idx;    //索引编号，日志文件内部使用
} ws_log_content;

typedef struct
{
    time_t time;        //记录时间
    time_t end_time; //事件结束时间(不需要记录的置为-1)

    int ch_idx;     //通道
    int ch_link_mask; // 联动通道mask		放弃，采用ch_link_mask_ex

    ws_log_main_type main_type;
    ws_log_sub_type sub_type;

    //用户登录IP，本地用户为ip_v4和ip_v6全部为0
    WS_U32  ip_v4;
    WS_U32  ip_v6[4];

    WS_CHAR disk_name[48];	 // 日志文件从旧版本到新版本中，新增项在日志文件中可能没有
    WS_CHAR usr_name[32];
    int 	ch_link_mask_ex[8];	 //以前版本的usr_name 裁剪出来一半用于保存联动条目
    WS_U32 node_idx;                //索引编号，日志文件内部使用
}ws_log_content_pro;

typedef struct ws_logm_cache_list
{
	ws_log_content_pro log_node;
	WS_U32 log_idx;	// 其他模块来做同步用的，避免发生时间变更导致日志同步和新增，刻舟求剑
	ws_logm_cache_list *pre;
	ws_logm_cache_list *next;
}ws_logm_cache_list;

typedef struct
{
    WS_CHAR num[32];
    WS_CHAR time[32];
    WS_CHAR event[32];
    WS_CHAR user[32];
} ws_log_title;

typedef struct
{
    int log_num;                    //日志数目
    ws_log_content *log_content;    //日志类容
} ws_log_inquiry_result;

typedef struct
{
    int log_num;                    //日志数目
    ws_log_content_pro *log_content;    //日志类容
} ws_log_inquiry_result_pro;

typedef struct
{
    ws_soft::ws_log_inquiry_result log_result;
    WS_BOOL *ws_log_have_file;
} ws_log_rec_result;

typedef struct
{
	ws_soft::ws_log_inquiry_result_pro log_result;
	WS_BOOL page_valid[WS_LOG_MAX_NUM / MAX_LINE_NUM + 1];
	WS_BOOL log_have_recfile[WS_LOG_MAX_NUM / MAX_LINE_NUM + 1][MAX_LINE_NUM];
} ws_log_rec_result_pro;

//将枚举类型翻译成实际类容之后传递给网络层，由网络层传递给IE客户端直接显示
typedef struct
{
    time_t time;    //记录时间
    WS_CHAR *content;
    WS_CHAR usr_name[32];
} ws_net_log_content;

typedef struct
{
    int         log_num;  
    ws_net_log_content *log_content;
} ws_net_log_inquiry_result;

typedef int (*log_content_trans)(const ws_log_content *src, ws_utility::ws_language_type language, char *content, size_t content_size); //
typedef int (*log_title_trans)(ws_utility::ws_language_type language, ws_log_title *title); //

typedef int (*log_content_trans_pro)(const ws_log_content_pro *src, ws_utility::ws_language_type language, char *content, size_t content_size);

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_LOG_MANAGE_H_


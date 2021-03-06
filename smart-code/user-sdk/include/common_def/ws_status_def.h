#ifndef _WS_STATUS_DEF_H_
#define _WS_STATUS_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"
#include "ws_comm_sys.h"
#include "ws_disk_manage_def.h"

using ws_utility::ws_event_serial_type;
using ws_utility::ws_time_struct;

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef enum{ 
	WS_EVENT_UNKNOW,
	WS_EVENT_HAPPEN,
	WS_EVENT_DISAPPEAR,
	WS_EVENT_CLEAR,	
}ws_event_state;

typedef enum
{
    WS_EVENT_TYPE_UNKNOW = 0,
    WS_EVENT_MD,        		
    WS_EVENT_AI,        		
    WS_EVENT_VLOST,     		
    WS_EVENT_R_LOF,   		
    WS_EVENT_COVER,
    WS_EVENT_NEED_RECORD,     
    WS_EVENT_LOGOUT,                    /* 强制用户登出 */
    WS_EVENT_AO,                 
    WS_EVNET_TOTAL_NUM,
} ws_event_type;

typedef enum
{
    EXCEPTION_UNKOWN = 0,
    EXCEPTION_DISK_CHECKING, 		
    EXCEPTION_NO_DISK,			
    EXCEPTION_DISK_ERROR,			
    EXCEPTION_NO_SPACE,      		
    EXCEPTION_NET_ERROR,			
    EXCEPTION_IP_CONFLICT,			
    EXCEPTION_ABNORMAL_SHUTDOWN,  	
    EXCEPTION_TOTAL_NUM,           
} exception_type;

typedef enum{
    WS_OPERATE_UNKONW = 0,
    WS_OPERATE_LOCK_SCREEN,      
    WS_OPERATE_IP_CHANGE,			
    WS_OPERATE_BACK_UP,				
    WS_OPERATE_IS_AUTO_IP_CONFIG,   
    WS_OPERATE_DISK_READY,                                              // 代表系统中磁盘已经检测完毕
    WS_OPERATE_DATABASE_READY,                                      // 代表系统中数据库已经建立完成
    WS_OPERATE_MOUSE_PANEL_OPT, 
    WS_OPERATE_NET_SERVER_INIT,
    WS_OPERATE_DISK_IS_FORMATING,
    WS_OPERATE_IS_AUTO_ROTATE,
    WS_OPERATE_TOTAL_NUM,
} ws_operate_type;

typedef enum
{
    WS_IP_CONFLICT = 0x01,    
    WS_IP_DHCP = 0x02,          
    WS_IP_AUTO = 0x04,      
} ws_exception_state;

typedef struct
{
    WS_BOOL is_enable;
    WS_BOOL is_email_linkage;
    WS_BOOL is_voice_alarm;
    WS_BOOL is_auto_ip;
    WS_BOOL is_linkage_rec;
    WS_BOOL is_alarm_out[4];
    WS_U32 ch_part[ws_utility::WS_NVR_MAX_MASK_NUM]; 	
} exception_control;

typedef struct
{
    exception_type type;
    exception_control ctl;
} exception_linkage;

typedef struct{
	ws_hard_disk_part_state 	part_state;
	WS_CHAR 							part_mount_dir[16];
}ws_status_manage_part_info;


typedef struct{
	ws_status_manage_part_info		part_info[ws_utility::WS_NVR_MAX_HDISK_PART_NUM];
	WS_CHAR part_mount_dir[ws_utility::WS_NVR_MAX_HDISK_PART_NUM][16];
	int available_node[ws_utility::WS_NVR_MAX_HDISK_PART_NUM];
	int valid_space_MB[ws_utility::WS_NVR_MAX_HDISK_PART_NUM]; //每个分区的可用空间
    int total_space_MB[ws_utility::WS_NVR_MAX_HDISK_PART_NUM]; //每个分区的总空间
    ws_time_struct 				start_time;//起始时间										
	ws_time_struct 				end_time;//结束时间
	WS_BOOL 	disk_get_time_range_flags;		//add by lmw 2016 10 20
	WS_U32      part_num;						//add by khs 2017.5.10 update part_num
}ws_status_manage_change_info_m;

typedef struct{
	ws_hard_disk_state 					disk_state;
	WS_U32 								part_num;
	time_t 								start_time;
	WS_CHAR  							serial_no[48];
}ws_hard_disk_state_info;

typedef struct{
    WS_CHAR vendor_name[16];            											//不变
    WS_CHAR product_name[48];           //产品名  								//不变
    WS_CHAR serial_no[48];                   //产品唯一编号 	                                        //不变
    WS_S32  scsi_bus_num;                   //表明是哪个插槽	        			//不变

    ws_hard_disk_state disk_state;											//要变
	
    int disk_space_MB; //硬盘总空间										//不变
    WS_U32 part_num;   //可用分区数										//不变
    
    WS_CHAR part_mount_dir[ws_utility::WS_NVR_MAX_HDISK_PART_NUM][16];  //分区挂载点
    int available_node[ws_utility::WS_NVR_MAX_HDISK_PART_NUM];//add by mjq 20151211 
	
    int valid_space_MB[ws_utility::WS_NVR_MAX_HDISK_PART_NUM]; //每个分区的可用空间
    int total_space_MB[ws_utility::WS_NVR_MAX_HDISK_PART_NUM]; //每个分区的总空间
    
    ws_status_manage_part_info		     part_info[ws_utility::WS_NVR_MAX_HDISK_PART_NUM];//可变
    ws_time_struct                                  start_time;                        //起始时间		//要变
    ws_time_struct                                  end_time;                          //结束时间		//要变
    WS_BOOL 			                          is_complete;	
}ws_status_manage_disk_info;

typedef struct
{
    ws_hard_disk_state                              disk_state_ex;										
    ws_time_struct                                  start_time_ex;  //起始时间
    ws_time_struct                                  end_time_ex;   //结束时间
    WS_CHAR serial_no[48];                   //产品唯一编号 	                                        //不变
}ws_status_disk_info_old;
//add by khs 2017.4.10

typedef struct
{
    time_t start_time;//保存到状态中心时的时间
    time_t end_time;
    time_t event_time;//设备上产生报警的时间 
}ws_event_info;

typedef struct excp_info
{
public:
    excp_info(time_t s_time,time_t e_time)
    {
        start_time = s_time;
        end_time = e_time;
    }
    excp_info(){}

    excp_info& operator=(const excp_info &value)
    {
        start_time = value.start_time;
        end_time = value.end_time;
        return *this;
    }
time_t start_time;
time_t end_time;
}ws_exception_info;



typedef struct{
	time_t start_time;
	time_t end_time;
}ws_operate_info;

typedef struct{
	ws_operate_type opt_type;
	WS_BOOL opt_state;
	ws_operate_info opt_info;
}ws_operate_state;




typedef struct
{
    ws_event_type     event_type;
    ws_event_state    state_event[_MAX_CHANNEL_NUM_];            
    ws_event_info      event_info[_MAX_CHANNEL_NUM_];
}ws_event_type_state;


typedef struct
{
    exception_type      type;
    WS_S32               state;  
    ws_event_state    state_event;    
    ws_exception_info excp_info;
} exception_state;

/* change by linhh 20170526 start : 统一报警模块类型定义 到HieServer_Cfg.h 与 ws_status_def.h 中*/
struct AlarmInfo
{
    ws_event_info     event_info;
    unsigned long	  m_AlarmCnt;//该报警的编号
};

typedef struct
{
    ws_event_info          event_info;
    ws_exception_info  exception_info;
}ws_alarm_info;

struct Device_Alarm_Info
{
    int			     m_use;
    ws_event_type     event_type;
    struct AlarmInfo     m_alarm[64];//目前给定64个通道
};
/* change by linhh 20170526 end: 统一报警模块类型定义 到HieServer_Cfg.h 与 ws_status_def.h 中*/

//add by khs 2017.7.14 start
typedef struct _file_state
{
    ws_time_struct time;//要操作的文件的日期
    WS_U32 ch;//要操作的文件的通道号
    WS_U32 operate_type;//备份还是回放模块
    _file_state* next;
}file_state;
//add by khs 2017.7.14 end

typedef int (*add_happen_event_node)(ws_event_serial_type evt, WS_U32 number, WS_U32 chan, time_t time);


#ifdef __cplusplus
}//namespace ws_soft
}//extern "C" {
#endif


#endif  //_WS_STATUS_DEF_H_  ?

#ifndef _WS_DISK_MANAGE_DEF_H_
#define _WS_DISK_MANAGE_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"
#include "ws_comm_sys.h" //add by lmw 2016 9 22
#define WS_ATA_DEVICE_PORT_INFO_PTAH "/sys/class/ata_port" 
#define WS_DATA_IMPORT_DISK_SERIAL_N0 "/config/date_import_" 

//using namespace ws_soft; //del by qqy, at 2017-01-10 18:57:25 解决IPC不能编译通过
using namespace ws_utility;//add by lmw 2016 9 22

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef enum
{
    WS_USB_DEV_UNKNOW,
    WS_USB_FLASH_DISK,  //U 盘
    WS_USB_CD_WRITER,   //刻录机
    WS_SATA_CD_WRITER,  //sata刻录机
} ws_usb_dev_type;

typedef struct
{
    WS_CHAR dev_name[16];       //设备名(usb disk 或者 DVD/CD)

    WS_CHAR vendor_name[16];    //生产厂商
    WS_CHAR product_name[48];   //产品名
    WS_CHAR scsi_name[16];
    ws_usb_dev_type type;

    WS_S32  part_num;       //分区数目
    WS_CHAR part_mount_dir[ws_utility::WS_NVR_MAX_USB_PART_NUM][16];    //分区挂载点
    WS_S32 valid_space_MB[ws_utility::WS_NVR_MAX_USB_PART_NUM]; //每个分区的可用空间
    WS_S32 total_space_MB[ws_utility::WS_NVR_MAX_USB_PART_NUM]; //每个分区的总空间
} ws_usb_disk_info;

// 非硬盘检测接口或格式化中 不得随便修改硬盘状态和分区状态
typedef enum
{
    WS_HARD_DISK_STATE_UNKNOW,			//
    WS_HARD_DISK_NEED_FORMAT,   		    // 硬盘格式化中出现了异常重启: 界面中使用 确认OK
    WS_HARD_DISK_ABNORMAL,      		    // 硬盘分区挂载失败时或者挂载的分区不见了设置: 确认OK
    WS_HARD_DISK_NORMAL,        		//正常
    WS_HARD_DISK_FORMATING,     		// 硬盘准备启动格式化或者格式化中设置该状态
    WS_HARD_DISK_FORMAT_FAILED,     		//格式化失败
    WS_HARD_DISK_VOLUME_ERROR,          //硬盘完成格式化后容量信息错误
    WS_HARD_DISK_ERROR,                             // 在硬盘分区错误或者硬盘有小分区或者硬盘有分区深度自检错误
    WS_HARD_DISK_CHECKING,				//检查中 为了在检查时，其他操作需要关闭检查
    WS_HARD_DISK_LOST,	         
    WS_HARD_DISK_PART_INFO_LOST,		//硬盘分区信息丢失
    WS_HARD_DISK_NO_SPACE,				// HDD no space
} ws_hard_disk_state;

typedef enum
{
    WS_HARD_DISK_PART_UNKNOW,			//
    WS_HARD_DISK_PART_NORMAL,			 //分区正常
    WS_HARD_DISK_PART_ERROR,			        // 分区设备节点不能正常访问或者有格式化中异常重启时设置: 确认OK 
    WS_HARD_DISK_PART_NEED_REPAIR,		 //分区挂载失败或者挂载的分区格式不正确确认OK
    WS_HARD_DISK_PART_NEED_CHECK,             // 分区修复失败情况下设置为深度自检，确认OK 
    WS_HARD_DISK_PART_READ_ONLY,		       //分区只读
    WS_HARD_DISK_PART_SMALL_MEMORY,		// 磁盘分区为小容量 确认OK
} ws_hard_disk_part_state;

typedef enum
{
    WS_HARD_DISK_TYPE_UNKNOW,	
    WS_HARD_DISK_TYPE_DISK,		        // 硬盘型号
    WS_HARD_DISK_TYPE_USB,			 //USB 型号
    WS_HARD_DISK_TYPE_USB_CDROM,		 //USB 刻录机
    WS_HARD_DISK_TYPE_SATA_CDROM,      //SATA 刻录机
    WS_HARD_DISK_TYPE_END,
} ws_hard_disk_type;

typedef struct
{
    WS_CHAR     serial_no[48];
}ws_disk_serial;

typedef struct
{
    WS_CHAR vendor_name[16];
    WS_CHAR product_name[48];   //产品名
    WS_CHAR serial_no[48];   //产品唯一编号 add by liuyu date 2014-12-18
    WS_S32 scsi_bus_num;    //表明是哪个插槽

    ws_hard_disk_state state;
	ws_time_struct start_time;//起始时间										//要变
	ws_time_struct end_time;//结束时间										//要变
    int disk_space_MB; //硬盘总空间
    int part_num;   //可用分区数

    WS_CHAR part_mount_dir[ws_utility::WS_NVR_MAX_HDISK_PART_NUM][16];  //分区挂载点
    int valid_space_MB[ws_utility::WS_NVR_MAX_HDISK_PART_NUM]; //每个分区的可用空间
    int total_space_MB[ws_utility::WS_NVR_MAX_HDISK_PART_NUM]; //每个分区的总空间
    int available_node[ws_utility::WS_NVR_MAX_HDISK_PART_NUM];//add by mjq 20151211 
    WS_BOOL 		is_complete;			// add by lmw 2016 10 20
} ws_hard_disk_info;

typedef struct
{
    WS_BOOL auto_rotate;    //是否自动轮转
} ws_hard_disk_work_ctl;


//此时只能获取到之前 的标记文件中的信息，并不能获取到磁盘的任何其它信息
typedef struct fmt_node
{
    WS_CHAR     serial_no[48];
    WS_U32	  part_idx;
    fmt_node    *next;
} ws_fmt_disk;

typedef struct format_info
{
    WS_CHAR serial_no[48];
    WS_U32 part_idx;
}ws_disk_format_info;


typedef struct
{
    WS_CHAR                 mount_dir[64];
    ws_usb_dev_type      dev_type;
    WS_CHAR                 scsi_name[16];
    int                           valid_space_MB;
    int                           total_space_MB;
} ws_dev_part_info;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_DISK_MANAGE_DEF_H_



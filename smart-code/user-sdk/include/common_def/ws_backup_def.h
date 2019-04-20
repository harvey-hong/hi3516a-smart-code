#ifndef _WS_BACKUP_DEF_H_
#define _WS_BACKUP_DEF_H_

#include "ws_comm_type.h"

#ifdef __cplusplus
extern "C" {
namespace ws_backup		
{
#endif

typedef enum
{
    WS_BACKUP_MODE_UNKNOW = 0,
    WS_BACKUP_BY_SELEST,    //按照选中文件备份
    WS_BACKUP_BY_TIME,      //按照设置的起始和结束时间备份
} ws_backup_work_mode;

typedef enum
{
    //录像文件备份格式
    WS_BACKUP_TO_H264,
    WS_BACKUP_TO_AVI,
    WS_BACKUP_TO_ASF,
    WS_BACKUP_TO_PRIVATE,

    //图片备份格式
    WS_BACKUP_TO_JPG = 100,
} ws_backup_file_type;

//mkisofs的压缩进度由percent导出
typedef struct
{
    double percent;
    int reserved[16];
} ws_mkisofs_shm_info_t;

//为了显示刻录进度，将刻录的大小采用共享内存导出
typedef struct
{
    long long  current_burn_size;
    long long total_size;
    int reserved[16];
} ws_cdrecord_shm_info_t;

#if defined (_SUPPORT_PRO_BACKUP_)
typedef enum
{
    WS_CD_DISK_STATUS_UNKNOW,
    WS_CD_DISK_STATUS_IN_ERASE,
    WS_CD_DISK_STATUS_HAS_ERASE,
} cd_disk_status_e;

typedef enum
{
	WS_BACKUP_STATUS_UNKNOW,
	WS_BACKUP_STATUS_CONVERT_REC,
	WS_BACKUP_STATUS_CONVERT_REC_FINISH,
	WS_BACKUP_STATUS_CONVERT_SNAP,
	WS_BACKUP_STATUS_CD_START,
	WS_BACKUP_STATUS_ERASE_CD,
	WS_BACKUP_STATUS_MAKE_ISO,
	WS_BACKUP_STATUS_BURN_ISO,	
	WS_BACKUP_STATUS_FINISH,
} ws_backup_job_status;
#endif

#ifdef __cplusplus
}//namespace ws_backup {
}//extern "C" {
#endif

#endif  //_WS_BACKUP_DEF_H_


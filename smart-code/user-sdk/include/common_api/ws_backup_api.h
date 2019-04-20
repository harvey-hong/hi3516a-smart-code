#if defined (_SUPPORT_PRO_BACKUP_)
#ifndef _WS_BACKUP_API_H_
#define _WS_BACKUP_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"

#include "ws_backup_def.h"
using namespace ws_soft;		

#ifdef __cplusplus
extern "C" {
namespace ws_backup
{
#endif
    WS_ERR backup_init();
    WS_ERR backup_add_rec_job(const ws_rec_file_inquiry_result *result);
    WS_ERR backup_add_snap_job(const ws_snap_file_inquiry_result *result);
    WS_ERR backup_file_size(WS_U64* total_size);
    WS_ERR backup_get_progress(WS_U32 *percent);
    WS_ERR backup_start(ws_dev_part_info *dev_info, WS_U32 dev_num, ws_backup_file_type file_type);
    WS_ERR backup_stop();
    WS_ERR backup_get_last_type(ws_usb_dev_type* m_dev_type);          

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif
#else
#ifndef _WS_BACKUP_API_H_
#define _WS_BACKUP_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_backup_def.h"

#define PERCENTAGE_OF_ERASE_IN_BURN (8)  //可擦写的光盘在擦除的时候占总进度的比例
#define PERCENTAGE_OF_CONVERT_IN_BURN (15) //刻录文件到光盘上进行格式转换占总进度的百分比,与擦除的比例相关，如果需要擦除则减去擦除的比例
#define PERCENTAGE_OF_MKISO_IN_BURN (18) //刻录文件到光盘上，制作iso文件系统占总进度的百分比
#define PERCENTAGE_OF_BURN_IN_BURN (67) //刻录文件到光盘上，真正刻录占总进度的百分比

#define WS_ERASE_TIME (10)  //擦除预估计时间

#ifdef __cplusplus
extern "C" {
namespace ws_backup 
{
#endif

    WS_ERR backup_init();
    WS_ERR backup_add_rec_job(const ws_rec_file_inquiry_result *result, ws_backup_work_mode mode, time_t start_time, time_t stop_time);
    WS_ERR backup_add_snap_job(const ws_snap_file_inquiry_result *result, ws_backup_work_mode mode, time_t start_time, time_t stop_time);
    WS_ERR backup_cnt_size(WS_U32 *size_MB);
    WS_ERR backup_file_size(WS_U64* total_size); 
    WS_ERR backup_start(const WS_CHAR* scsi_name, const WS_CHAR* part_mount_dir,ws_backup_file_type file_type, ws_usb_dev_type dev_type, const WS_CHAR* store_dir);
    WS_ERR backup_get_progress(WS_U32 *percent);    //percent为100表示完成
    WS_ERR backup_stop();
    WS_ERR backup_get_last_type(ws_usb_dev_type* m_dev_type);  

    WS_ERR get_cd_info(WS_BOOL *cd_can_write, WS_BOOL *cd_has_data_alreay, WS_BOOL *cd_burn_machine_exist, WS_BOOL *cd_disk_exist);
    WS_ERR parse_scsi_no(const char *scsi_name, int *no, size_t no_size);
    WS_ERR make_iso(const char *store_dir);
    WS_ERR burn_iso(const char *store_dir, const int *scsi_info);
    void backup_to_cd( const WS_CHAR *store_dir); 
    void backup_to_usb_flash(); 
    void *backup_thread(void *para);

    WS_ERR backup_to_cd_ex( const WS_CHAR *store_dir);
    WS_ERR backup_to_usb_flash_ex();
    WS_ERR backup_thread_ex(void *para);


#ifdef __cplusplus
}//namespace ws_backup {
}//extern "C" {
#endif

#endif  //_WS_REMOTE_AGENT_API_H_
#endif
// modefy by ljx 20160108 end
#ifndef _WS_RECFILE_MANAGE_API_H_
#define _WS_RECFILE_MANAGE_API_H_

#include "ws_comm_sys.h"
#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_flist.h"
#include "ws_comm_data.h"

#include "ws_recfile_manage_def.h"
#include "ws_sqltask_manage_def.h"

using ws_utility::WS_ERR;
using namespace ws_soft;

#ifdef __cplusplus
extern "C" {
namespace ws_recfm                
{
#endif

    WS_ERR recfm_init();
    WS_ERR recfm_get_range_time(const char *part_name[],WS_U32 part_num,ws_time_struct *rec_start_time, ws_time_struct *rec_end_time, ws_time_struct *snap_start_time, ws_time_struct *snap_end_time);
    int recfm_get_dbfile_open_num();

    WS_ERR recfm_refresh_list();    //刷新链表
    WS_ERR recfm_stop_recfile_work();
    WS_ERR recfm_start_recfile_work();
    WS_ERR recfm_record_lock(const char *file_path);
    WS_ERR recfm_record_unlock(const char *file_path);
    WS_BOOL recfm_part_is_full(const WS_CHAR *file_name); //检查录像文件所在分区是否写满
    WS_ERR recfm_get_rec_name(int nvr_ch, ws_utility::ws_rec_file_trig_type type, WS_CHAR *file_name, size_t name_size, const ws_frame_info *frame_info);    //申请录像文件名
    WS_ERR recfm_add_false_rec_info(int ch, ws_utility::ws_rec_file_trig_type type, WS_CHAR *file_name, size_t name_size);
    WS_ERR recfm_sync_rec_start(const WS_CHAR *file_name, time_t start_time);   //同步文件开始时间
    WS_ERR recfm_sync_rec_close(const WS_CHAR *file_name, time_t end_time, WS_U32 file_size);   //同步文件结束时间
    WS_ERR recfm_inquiry_rec_by_month(const ws_utility::ws_time_struct *time, WS_U32 *mask);            //查询指定月份哪些天有录像，bit0-bit30对应1号-31号，0表示没有录像，1表示有录像
    WS_ERR recfm_inquiry_rec_by_day(WS_U32 nvr_ch, const ws_utility::ws_time_struct *time, ws_rec_file_inquiry_type file_type, ws_rec_file_inquiry_result *result,int * real_num); //查询指定日期的录像 //change by lmw 20170509
    WS_ERR recfm_inquiry_rec_by_disk_num(int scsi_num, time_t *rec_start, time_t *rec_stop);//通过硬盘的sata口号查询该应该录像的起始时间和结束时间
    WS_ERR recfm_inquiry_rec_by_time(WS_U32 nvr_ch,
                    const ws_utility::ws_time_struct *start_time,
                    const ws_utility::ws_time_struct *stop_time,
                    ws_rec_file_inquiry_type file_type,
                    ws_rec_file_inquiry_result *result ,int * real_num);   //查询指定时间段的录像//change by lmw 20170509

    WS_ERR recfm_free_inquiry_rec_result(const ws_rec_file_inquiry_result *result); //释放查询结果
	WS_ERR recfm_save_inquiry_rec_result(ws_rec_file_inquiry_result *result);//add by lmw 20170509 保存查询
    WS_ERR recfm_get_snap_name(int* need_snap_ch, size_t ch_size , ws_utility::ws_snap_file_trig_type type, WS_CHAR *file_name, size_t name_size);
    WS_ERR recfm_add_snap_name(WS_U32 nvr_ch, ws_utility::ws_snap_file_trig_type type ,const WS_CHAR *file_name);

    WS_ERR recfm_inquiry_snap_by_month(const ws_utility::ws_time_struct *time, WS_U32 *mask);           //查询指定月份哪些天有录像，bit0-bit30对应1号-31号，0表示没有录像，1表示有录像
    WS_ERR recfm_inquiry_snap_by_day(WS_U32 nvr_ch, const ws_utility::ws_time_struct *time, ws_snap_file_inquiry_type file_type, ws_snap_file_inquiry_result *result);  //查询指定日期的录像
    WS_ERR recfm_inquiry_snap_by_time(WS_U32 nvr_ch,
                    const ws_utility::ws_time_struct * start_time,
                    const ws_utility::ws_time_struct * stop_time,
                    ws_snap_file_inquiry_type file_type,
                    ws_snap_file_inquiry_result * result);
    WS_ERR recfm_free_inquiry_snap_result(const ws_snap_file_inquiry_result *result);   //释放查询结果

    /*通知此时磁盘分区满*/
    WS_ERR recfm_notice_part_full(const WS_CHAR *file_name);
    void swap(ws_snap_file_inquiry_node  *node1, ws_snap_file_inquiry_node *node2);
    void Qsort(ws_snap_file_inquiry_node *current_node, int low, int high);
    void quickly_sort(ws_snap_file_inquiry_result *result, WS_U32 node_count);


    WS_ERR recfm_inquiry_recfile_by_day(WS_U32 nvr_ch, const ws_utility::ws_time_struct *time,const ws_rec_file_inquiry_type file_type,ws_rec_table_hand * rec_hld,WS_U32 * rec_num);
    WS_ERR recfm_inquiry_recfile_by_time(WS_U32 nvr_ch,const ws_utility::ws_time_struct * start_time,const ws_utility::ws_time_struct * stop_time,ws_soft::ws_rec_file_inquiry_type file_type,ws_rec_table_hand * rec_hand,WS_U32 * result_num);
    WS_ERR recfm_get_recfile_result_for_pb(WS_U32 nvr_ch,const ws_rec_table_hand rec_hdl,ws_pb_rec_file_inquiry_result * rec_result, time_t* min_time, time_t * max_time);
    WS_ERR recfm_get_recfile_result(WS_U32 nvr_ch,const ws_rec_table_hand rec_hdl, WS_U32 *start_num, WS_U32 *total_num, ws_rec_file_inquiry_node * rec_result, WS_BOOL is_playback);
    WS_ERR recfm_free_rec_result(ws_rec_table_hand * rec_hdl);

    WS_ERR recfm_inquiry_snapfile_by_day(WS_U32 nvr_ch,const ws_utility::ws_time_struct * time,const ws_snap_file_inquiry_type file_type,ws_snap_table_hand * snap_hdl,WS_U32 * snap_num);
    WS_ERR recfm_inquiry_snapfile_by_time(WS_U32 nvr_ch,const ws_utility::ws_time_struct * start_time,const ws_utility::ws_time_struct * stop_time,ws_soft::ws_snap_file_inquiry_type file_type, ws_snap_table_hand * snap_hand,WS_U32 * result_num);
    WS_ERR recfm_get_snapfile_result_for_pb(WS_U32 nvr_ch,const ws_snap_table_hand snap_hdl,ws_pb_snap_file_inquiry_result * snap_result, time_t* min_time, time_t * max_time);
    WS_ERR recfm_get_snapfile_result(WS_U32 nvr_ch,const ws_snap_table_hand snap_hdl, WS_U32 *start_num, WS_U32 *total_num, ws_snap_file_inquiry_node *snap_result);
    WS_ERR recfm_free_snap_result(ws_snap_table_hand * snap_hdl);

    WS_BOOL recfm_inquiry_have_recfile(WS_U32 nvr_ch,const ws_utility::ws_time_struct * start_time,const ws_utility::ws_time_struct * stop_time); 

#ifdef __cplusplus
}//namespace ws_recfm {
}//extern "C" {
#endif

#endif //#ifndef _WS_RECFILE_MANAGE_API_H_


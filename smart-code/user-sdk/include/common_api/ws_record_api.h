#ifndef _WS_RECORD_API_H_
#define _WS_RECORD_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_data.h"
#include "ws_record_def.h"
using ws_utility::WS_ERR;
using namespace ws_soft;
#ifdef __cplusplus
extern "C" {
namespace ws_record  
{ 
#endif

WS_ERR record_init(int rec_ch_num);

WS_ERR record_start_work();
WS_ERR record_stop_work();  //Ϊ��ʽ�����ػ���׼��
WS_ERR record_check_rec_status(WS_U32 rec_ch ,WS_BOOL* rec_status);


WS_ERR record_prepare_change_time(WS_U32 magic);

// �������ȡ��ǰͨ������ģʽ
WS_ERR record_set_record_mode(WS_U32 rec_ch, ws_soft::RECORD_MODE curMode);
WS_ERR record_get_record_mode(WS_U32 rec_ch, ws_soft::RECORD_MODE *curMode);

WS_ERR record_set_manual_rec_enable(WS_U32 rec_ch, WS_BOOL enable);//Ϊĳ��ͨ�����üƻ�
WS_ERR record_get_manual_rec_enable(WS_U32 rec_ch, WS_BOOL *enable);//��ȡĳ��ͨ���ƻ�

WS_ERR record_set_close_rec_enable(WS_U32 rec_ch, WS_BOOL enable);
WS_ERR record_get_close_rec_enable(WS_U32 rec_ch, WS_BOOL *enable);

WS_ERR record_set_schedule(WS_U32 rec_ch, ws_rec_schedule_day day, const ws_rec_schedule_per_day *schedule);
WS_ERR record_set_pre_rec_sec(WS_U32 rec_ch, int sec);      //����Ԥ¼ʱ��
WS_ERR record_get_pre_rec_sec(WS_U32 rec_ch, int *sec);
WS_ERR record_set_delay_rec_sec(WS_U32 rec_ch, int sec);    //�����ӳ�¼��ʱ��
WS_ERR record_get_delay_rec_sec(WS_U32 rec_ch, int *sec);

WS_ERR record_get_link_by_md(WS_U32 rec_ch, WS_U32 *md_link, WS_U32 mask_num);
WS_ERR record_get_link_by_ai(WS_U32 rec_ch, WS_U32 *ai_link, WS_U32 mask_num);

//add by qqy,start at 2017-02-22 16:54:24
WS_ERR record_set_link_by_md_ex(WS_U32 rec_ch, WS_U32 *md_link, WS_U32 mask_num);
WS_ERR record_set_link_by_ai_ex(WS_U32 rec_ch, WS_U32 *ai_link, WS_U32 mask_num);
//add by qqy,end at 2017-02-22 16:54:26

//Modified by qqy,start at 2017-03-10 09:57:02
ws_rec_file_trig_type record_get_ch_state(WS_U32 rec_ch);    //��ȡ¼��״̬
//Modified by qqy,end at 2017-03-10 09:57:05

WS_ERR record_set_enc_data_magic(WS_U32 magic);

/* add by zhangmq 20180527 start*/
//add zmq  ����cfg_manageģ����API���й�¼��Ľӿ�[2018-05-03 09:20]
WS_ERR cfg_manage_get_rec_holiday_enable(WS_U32 nvr_ch, WS_BOOL *enable);
WS_ERR cfg_fac_manage_get_rec_holiday_enable(WS_U32 nvr_ch, WS_BOOL *enable);
WS_ERR cfg_manage_set_rec_holiday_enable(WS_U32 nvr_ch, WS_BOOL enable);
//��ȡ¼��ƻ�
WS_ERR cfg_manage_get_rec_schedule(WS_U32 nvr_ch, ws_rec_schedule_day day, ws_rec_schedule_per_day *schedule);
WS_ERR cfg_fac_manage_get_rec_schedule(WS_U32 nvr_ch, ws_rec_schedule_day day, ws_rec_schedule_per_day *schedule);
//����¼��ƻ�
WS_ERR cfg_manage_set_rec_schedule(WS_U32 nvr_ch, ws_rec_schedule_day day, const ws_rec_schedule_per_day *schedule);
//��ѯָ���·���Щ���ǽڼ��գ�bit0-bit3��Ӧ1��-31�ţ�0��ʾ���ǣ�1��ʾ��.
WS_ERR cfg_manage_get_holiday(WS_U16 year, WS_U16 month, WS_U32 *mask);
WS_ERR cfg_fac_manage_get_holiday(WS_U16 year, WS_U16 month, WS_U32 *mask);
WS_ERR cfg_def_manage_get_holiday(WS_U16 year, WS_U16 month, WS_U32 *mask);
//����ָ���·���Щ���ǽڼ��գ�bit0-bit30��Ӧ1��-31�ţ�0��ʾ���ǣ�1��ʾ��.
WS_ERR cfg_manage_set_holiday(WS_U16 year, WS_U16 month, WS_U32 mask);

//add zmq �������õļ����ӿ�[2018-05-03 11:38]
WS_ERR resume_rec_shedule();
WS_ERR resume_timer_rec_cfg();
WS_ERR resume_holiday_cfg();
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
}
}//extern "C" {
#endif

#endif //#ifndef _WS_COMM_RECORD_H_


#ifndef _WS_TRIGGER_DEF_H_
#define _WS_TRIGGER_DEF_H_

#include "ws_comm_type.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef enum
{
    WS_TRIG_SRC_AI,
    WS_TRIG_SRC_VLOST,
    WS_TRIG_SRC_MD,
    WS_TRIG_SRC_NUM,                    //�����ʾ�ܹ��ж��ٸ��¼�
} ws_trig_source;

typedef enum
{
    WS_LANGE_AI,
    WS_LANGE_MD,
    WS_LANGE_VLOST,
    WS_LANGE_FROM,

    WS_LANGE_NO_DISK,
    WS_LANGE_DISK_CHECK,
    WS_LANGE_DISK_ERROR,
    WS_LANGE_NO_SPACE,
    WS_LANGE_NET_ERROR,
    WS_LANGE_IP_CONFLICT,
    WS_LANGE_NEW_IP,
    WS_LANGE_CHANNEL,//add by yxl 2014.08.11
    WS_LANGE_R_LOF,
} ws_trig_smtp;

typedef struct
{
    WS_U32  lv_ch_mask[ws_utility::WS_NVR_MAX_MASK_NUM];     //����Ԥ����ѵ��ͨ��mask[0], bit0-bit31�ֱ��Ӧͨ��0-ͨ��31��mask[1],bit0-bit31�ֱ��Ӧͨ��32-ͨ��63��1��ʾ������0��ʾ������
    WS_U32  rec_ch_mask[ws_utility::WS_NVR_MAX_MASK_NUM];    //����¼���ͨ��mask[0], bit0-bit31�ֱ��Ӧͨ��0-ͨ��31��mask[1],bit0-bit31�ֱ��Ӧͨ��32-ͨ��63��1��ʾ������0��ʾ������
    WS_U32  snap_ch_mask[ws_utility::WS_NVR_MAX_MASK_NUM];   //����ץͼ��ͨ��mask[0], bit0-bit31�ֱ��Ӧͨ��0-ͨ��31��mask[1],bit0-bit31�ֱ��Ӧͨ��32-ͨ��63��1��ʾ������0��ʾ������
    // �ֺ���: һ��Ҫע��: ��߶����AO ���������WS_NVR_MAX_MASK_NUM ������Ƕ��ʽϵͳ����֧�ֵ�AO ��С����Ƶͨ����������������쳣
    WS_U32  ao_ch_mask[ws_utility::WS_NVR_MAX_MASK_NUM];     //�������������mask������ͬ��
    
    WS_BOOL trig_buzzer;        //�Ƿ�����������
    WS_BOOL trig_email;          //�Ƿ������ʼ�
    WS_BOOL is_alarm_out[4];

#if defined(_SUPPORT_LINK_CLOUD_CRADLE_)
    ws_utility::ws_cradle_cmd_info trig_cradle_cmd[ws_utility::WS_NVR_MAX_CH_NUM];	
#endif
} ws_trig_operation;

typedef int (*ws_smpt_get_str_func)(ws_trig_smtp smtp, char *str, size_t str_size);
#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif //#ifndef _WS_COMM_TRIGGER_H_


#ifndef _WS_P2PLIVE_RESOURCE_H_
#define _WS_P2PLIVE_RESOURCE_H_

#include "ws_comm_data.h"
#include "ws_comm_display.h"
#include "ws_utility_class_def.h"

using ws_utility::WS_ERR; //changed by mjq 2014.11.24

namespace ws_p2plive
{

typedef struct
{
    WS_BOOL last_node_idx_ok;   //�Ƿ��ȡ����Ƶ����
    WS_U32 last_node_idx;

    WS_BOOL frame_ok;       //�Ƿ��ȡ����Ƶ���ݲ���û���ͷ�
    ws_soft::ws_frame_info frame_info;
    WS_UCHAR *frame_data;

    int fetch_num;
} ws_p2plive_ch_frame_info;

typedef struct
{
    // �Ƿ���Ҫ��ʾ
    WS_BOOL             need_dis;  
    
    // ����Ҫ��ʾ����������ʾ���ڵı��
    int                      Wndidx ;
    
    ws_utility::ws_abstract_rect    dis_rect;
    //ws_soft::ws_venc_str_type     venc_str_type;    //�����Ҫ��ʾ��ָ����ʾ����������

    ws_p2plive_ch_frame_info main_str; //��ȡ������֡��Ϣ
    ws_p2plive_ch_frame_info sub1_str; //��ȡ������֡��Ϣ

    WS_BOOL need_roi;                       //�Ƿ���Ҫ�ֲ��Ŵ�
    ws_utility::ws_abstract_rect roi_rect;     //�ֲ��Ŵ������
    ws_utility::ws_real_rect real_roi_rect;    //�ֲ��Ŵ��������ģ��1000*1000�е���ʵ����

    WS_BOOL have_auhority;  //�Ƿ���Ԥ��Ȩ�ޣ����û��Ȩ�ޣ�����ʾ����LOGO

    //ͳ��֡����Ϣ
    ws_utility::ws_rec_real_info dis_real_info;

    int         dec_pipe_idx;   //ƽ̨��Ľ���ܵ����
} ws_p2plive_ch_info;

typedef struct
{
    WS_BOOL             need_dis;   //�Ƿ���Ҫ��ʾ

    // ����Ҫ��ʾ����������ʾ���ڵı��
    int                      Wndidx ;
    
    ws_utility::ws_abstract_rect dis_rect;
    ws_utility::ws_logo_type logo_type;    //LOGO����

    int dec_pipe_idx;   //ƽ̨��Ľ���ܵ����
} ws_logo_wind_info;

class ws_p2plive_resource_manage : public ws_utility::ws_diagnose_client//change by xrg 2014.11.28
{
public:
    void construct_res(int nvr_ch_num); //ֻ�����ʼ����������һ��

    WS_ERR start_p2plive(const ws_utility::ws_display_screen_info *screen_info, const ws_utility::ws_wind_content *wind_content, size_t content_dim);
    WS_ERR stop_p2plive();
    
    WS_ERR start_audio(WS_U32 nvr_ch);
    WS_ERR stop_audio();

    WS_ERR set_roi(WS_S32 nvr_ch, const ws_utility::ws_abstract_rect *roi_rect);
    WS_ERR mouse_set_roi(WS_S32 nvr_ch, const ws_utility::ws_abstract_coordinate *roi_coor, WS_BOOL amplif);
    WS_ERR move_roi_rect(WS_S32 nvr_ch, const ws_utility::ws_abstract_coordinate *start, const ws_utility::ws_abstract_coordinate *stop);
     WS_ERR get_roi_rect(WS_S32 nvr_ch, WS_BOOL* has_roi,ws_utility::ws_real_rect *rect);			// md by lz 20160217;
    WS_ERR cancel_roi(WS_S32 nvr_ch);
    WS_ERR set_authority_mask(WS_U32 *mask, WS_U32 mask_num);		// change by liuy 20160322 start-end;
    WS_ERR set_enc_data_magic(WS_U32 magic);

    WS_BOOL work();

public:
    WS_VOID diagnose_dump(WS_U32 para, ws_utility::ws_diag_dump dump_fuc);

private:
    WS_BOOL is_valid_ch(int ch_idx);
    WS_ERR fetch_video_frame(int ch_idx, ws_p2plive_ch_frame_info *info);
    void rel_video_frame(int ch_idx, ws_p2plive_ch_frame_info *info);

    void rel_video_frame_all(int ch_idx);
    void proc_update_ch_state(int nvr_ch , ws_p2plive_ch_info *ch_info);
    void update_real_info(const ws_soft::ws_frame_info *frame_info, ws_utility::ws_rec_real_info *real_info, int ch);
    void dump_real_info(const ws_utility::ws_rec_real_info *real_info, int ch);

private:
    ws_utility::ws_lock    *m_lock;//change by xrg 2014.11.28

    int m_ch_num;
    ws_p2plive_ch_info m_ch_info[ws_utility::WS_NVR_MAX_CH_NUM];

    WS_U32 m_sys_time_magic;    //ϵͳ�޸�ʱ��֮��ͬ�����ݵ�����

    WS_BOOL m_need_start_audio;
    WS_U32 m_audio_ch;
    ws_p2plive_ch_frame_info m_audio_frame;

    pthread_t m_thr_hand;

    //��ʾ����logoʱ���
    WS_BOOL m_start_lose[ws_utility::WS_NVR_MAX_CH_NUM];
    WS_BOOL m_is_lose[ws_utility::WS_NVR_MAX_CH_NUM];
    time_t m_time[ws_utility::WS_NVR_MAX_CH_NUM];

public:
    static void *ws_p2plive_thread(void *para);  
    
public:
    ws_p2plive_resource_manage();
    ~ws_p2plive_resource_manage();
    const char *class_name()
    {
        return "ws_live_resource_manage";
    };
private:
    ws_p2plive_resource_manage(const ws_p2plive_resource_manage &other);
    ws_p2plive_resource_manage &operator=(const ws_p2plive_resource_manage &other);
};


ws_p2plive_resource_manage *get_resource();    //����������װ��Դ����������

}//namespace ws_live {
#endif  //#ifndef _WS_LIVE_RESOURCE_H_


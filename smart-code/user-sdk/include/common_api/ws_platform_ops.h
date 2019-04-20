#ifndef _WS_PLATFORM_OPS_H_
#define _WS_PLATFORM_OPS_H_

#include "ws_platform_def.h"
#include "ws_platform_hi.h"

#include "ws_comm_data.h"
#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_display.h"

#define HISI_PLAT_ALIGN (64)

#define HISI_VIDEO_IN_FORMAT       (WS_PIXEL_FORMAT_YUV_SEMIPLANAR_422)
#define HISI_PLAT_PIXEL_FORMAT     (WS_PIXEL_FORMAT_YUV_SEMIPLANAR_420)
#define HISI_LOGO_PIXEL_FORMAT     (WS_PIXEL_FORMAT_YUV_SEMIPLANAR_420)

#define HISI_3531_SH_DRIVER_ABSOLUTE_PATH		"/mnt/mtd/app/hi3531/ko/extdrv/sh4101.ko"
#define HISI_3521_SH_DRIVER_ABSOLUTE_PATH		"/mnt/mtd/app/hi3521/ko/extdrv/sh4101.ko"
#define HISI_3531_SEM_7704_DRV_ABSLUTE_PATH 	       "/mnt/mtd/app/hi3531/ko/extdrv/sem7704_drv.ko" 
#define HISI_3521_SEM_7704_DRV_ABSLUTE_PATH 	       "/mnt/mtd/app/hi3521/ko/extdrv/sem7704_drv.ko" 

#define HISI_3521A_SEM_7704_DRV_ABSLUTE_PATH 	"/mnt/mtd/app/hi3521a/ko/extdrv/sem7704_drv.ko" 

typedef	void*	WS_LIB_HANDLE;

typedef WS_S32 (*MPI_SYS_GET_RESOL)(hi_sdk_res_info** m_sys_resol, int* m_sys_num);
typedef WS_S32 (*MPI_SYS_INIT)(VB_CONF_S *pstVbConf);
typedef WS_S32 (*MPI_VI_2_VPSS)(WS_S32 ViDev, WS_S32 ViChn, WS_S32 VpssGrp);
typedef WS_S32 (*MPI_VI_N2_VPSS)(WS_S32 ViDev, WS_S32 ViChn, WS_S32 VpssGrp);
typedef WS_S32 (*MPI_VPSS_2_VPSS)(WS_S32 src_VpssGrp, WS_S32 src_VpssChn, WS_S32 dest_VpssGrp);
typedef WS_S32 (*MPI_VPSS_N2_VPSS)(WS_S32 src_VpssGrp, WS_S32 src_VpssChn, WS_S32 dest_VpssGrp);
typedef WS_S32 (*MPI_VPSS_2_VO)(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 VoDev, WS_S32 VoChn);
typedef WS_S32 (*MPI_VPSS_N2_VO)(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 VoDev, WS_S32 VoChn);
typedef WS_S32 (*MPI_VPSS_2_VENC)(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 GrpChn, WS_S32 VencChn);
typedef WS_S32 (*MPI_VPSS_N2_VENC)(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 GrpChn, WS_S32 VencChn);
typedef WS_S32 (*MPI_VPSS_2_VDA)(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 VdaChn);
typedef WS_S32 (*MPI_VPSS_N2_VDA)(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 VdaChn);
typedef WS_S32 (*MPI_PCIV_2_VO)(WS_S32 PcivCh, WS_S32 VoDev, WS_S32 VoChn);
typedef WS_S32 (*MPI_PCIV_N2_VO)(WS_S32 PcivCh, WS_S32 VoDev, WS_S32 VoChn);
typedef WS_S32 (*MPI_VDEC_2_VPSS)(WS_S32 VdChn, WS_S32 VpssGrp);
typedef WS_S32 (*MPI_VDEC_N2_VPSS)(WS_S32 VdChn, WS_S32 VpssGrp);
typedef WS_S32 (*MPI_AI_2_AENC)(WS_S32 AiDev, WS_S32 AiChn, WS_S32 AeChn);
typedef WS_S32 (*MPI_AI_N2_AENC)(WS_S32 AiDev, WS_S32 AiChn, WS_S32 AeChn);
typedef WS_S32 (*MPI_ADEC_2_AO)(WS_S32 AdChn, WS_S32 AoDev, WS_S32 AoChn);
typedef WS_S32 (*MPI_ADEC_N2_AO)(WS_S32 AdChn, WS_S32 AoDev, WS_S32 AoChn);
typedef WS_S32 (*MPI_AI_2_AO)(WS_S32 AiDev, WS_S32 AiChn, WS_S32 AoDev, WS_S32 AoChn);
typedef WS_S32 (*MPI_AI_N2_AO)(WS_S32 AiDev, WS_S32 AiChn, WS_S32 AoDev, WS_S32 AoChn);
typedef WS_S32 (*MPI_INIT_MPP_TIME)(WS_U64 u64PtsBase);
typedef WS_S32 (*MPI_SYNC_MPP_TIME)(WS_U64 u64PtsBase);
typedef WS_S32 (*MPI_GET_MPP_TIME)(WS_U64 *pu64CurPts);
typedef WS_S32 (*MPI_MMZ_ALLOC)(WS_U32 *pu32PhyAddr, WS_UCHAR **ppVirtAddr,  WS_U32 u32Len);
typedef WS_S32 (*MPI_VB_CREATE_LOGO)(WS_U32 , WS_U32 , WS_U32 , WS_U32 , WS_U32 , WS_U32 , hisilicon_logo_info*);
typedef WS_S32 (*MPI_VPSS_CREATE_GRP)(WS_S32 ViChn, WS_S32 VpssGrp, SIZE_S *pstSize, hi_vpss_src_type src_type);
typedef WS_S32 (*MPI_VPSS_DESTROY_GRP)(WS_S32 VpssGrp);
typedef WS_S32 (*MPI_VPSS_START_CH)(WS_S32 VpssGrp, WS_S32 VpssChn, int enable_gride);
typedef WS_S32 (*MPI_VPSS_STOP_CH)(WS_S32 VpssGrp, WS_S32 VpssChn);
typedef WS_S32 (*MPI_VPSS_SEND_FRAME)(WS_S32 VpssGrp, VIDEO_FRAME_INFO_S *frame);
typedef WS_S32 (*MPI_VPSS_SWITCH_USR)(WS_S32 VpssGrp, WS_S32 VpssChn, int dst_width, int dst_height);
typedef WS_S32 (*MPI_VPSS_CANCEL_USR)(WS_S32 VpssGrp, WS_S32 VpssChn);
typedef WS_S32 (*MPI_VPSS_SET_RECT_RITIO)(WS_S32 VpssGrp, RECT_S *rect);
typedef WS_S32 (*MPI_VPSS_SET_GRP_PARAM)(WS_S32 VpssGrp, const ws_vpss_param *vpss_param);
typedef WS_S32 (*MPI_VPSS_NR_CTL)(WS_S32 VpssGrp, WS_BOOL enable);
typedef WS_S32 (*MPI_VPSS_IE_CTL)(WS_S32 VpssGrp, WS_BOOL enable);
typedef WS_S32 (*MPI_VPSS_CH_SP_CTL)(WS_S32 VpssGrp, WS_S32 VpssChn, WS_BOOL enable);
typedef WS_S32 (*MPI_VPSS_GET_NR)(WS_S32 VpssGrp, WS_BOOL *enable);
typedef WS_S32 (*MPI_VPSS_GET_IE)(WS_S32 VpssGrp, WS_BOOL *enable);
typedef WS_S32 (*MPI_VPSS_CH_GET_SP)(WS_S32 VpssGrp, WS_S32 VpssChn, WS_BOOL *enable);
typedef WS_S32 (*MPI_VDEC_CREATE_CH)(WS_S32 vdec_ch, int width, int height, PAYLOAD_TYPE_E enType, int *hisi_buf_size);
typedef WS_S32 (*MPI_VDEC_DESTROY_CH)(WS_S32 vdec_ch);
typedef WS_S32 (*MPI_VDEC_GET_REMAIN)(WS_S32 vdec_ch);
typedef WS_S32 (*MPI_VDEC_SEND_FRAME)(WS_S32 vdec_ch, const char *data, int len, WS_U64 pts);
typedef WS_S32 (*MPI_VDEC_GET_IMAGE)(WS_S32 VdChn, VIDEO_FRAME_INFO_S *pstFrameInfo, WS_U32 u32BlockFlag);
typedef WS_S32 (*MPI_VDEC_REL_IMAGE)(WS_S32 VdChn, VIDEO_FRAME_INFO_S *pstFrameInfo);
typedef WS_S32 (*MPI_VO_GET_TIME)(WS_S32 VoDev, WS_S32 vo_wind, WS_U64 *pts);
typedef WS_S32 (*MPI_FB_ENABLE)(int fd);
typedef WS_S32 (*MPI_FB_DISABLE)(int fd);
typedef WS_S32 (*MPI_FB_SET_TRANS)(int fd, int percent);
typedef WS_S32 (*MPI_FB_INIT_COLOR)(int fd, int width, int height, HIFB_COLOR_FMT_E color_fmt, void **addr, int *max_size);
typedef WS_S32 (*MPI_FB_SWITCH_RESOL)(int fd, int width, int height);
typedef WS_S32 (*MPI_FB_GET_PHY)(int fd, WS_U32 *phy_addr, WS_U32 *phy_stride);
typedef WS_S32 (*MPI_VDEC_MEM_CFG)(int vdec_num);
typedef WS_S32 (*MPI_VPSS_MEM_CFG)(int vpss_num);
typedef WS_S32 (*MPI_VDA_MEM_CFG)(WS_U32 iNum);
typedef WS_S32 (*MPI_VDA_CREATE_CH)(WS_S32 VdaChn, WS_U32 ch_width, WS_U32 ch_height);
typedef WS_S32 (*MPI_VDA_START_CH)(WS_S32 VdaChn);
typedef WS_S32 (*MPI_VDA_STOP_CH)(WS_S32 VdaChn);
typedef WS_S32 (*MPI_VDA_DESTROY_CH)(WS_S32 VdaChn);
typedef WS_S32 (*MPI_VDA_GET_CH_DATA)(WS_S32 VdaChn, WS_S32 *check_blk_idx, WS_U32 check_blk_num, WS_U32 total_blk_num, WS_S32 sad_th, WS_S32 percent, WS_BOOL *md_state);
typedef WS_S32 (*MPI_VENC_MEM_CFG)(WS_S32 grp_num);
typedef WS_S32 (*MPI_VENC_START_CH)(WS_S32 VencGrp, WS_S32 VencChn, const hi_sdk_venc_ch_info *ctl, SIZE_S *enc_size);
typedef WS_S32 (*MPI_VENC_STOP_CH)(WS_S32 VencGrp, WS_S32 VencChn);
typedef WS_S32 (*MPI_VENC_RESTART_CH)(WS_S32 VencChn);
typedef WS_S32 (*MPI_VENC_ENABLE_CH)(WS_S32 VencChn);
typedef WS_S32 (*MPI_VENC_DISABLE_CH)(WS_S32 VencChn);
typedef WS_S32 (*MPI_VENC_GET_FD)(WS_S32 VencChn);
typedef WS_S32 (*MPI_VENC_GET_SNAP_DATA)(WS_S32 VencGrp, WS_S32 VencChn, time_t* CompareTime, const WS_CHAR *absolute_path, WS_CHAR *picture_cache, WS_S32 pic_size, WS_U32 *pic_length, time_t* frame_time,ws_snap_type snap_type);
typedef WS_S32 (*MPI_VENC_SET_RC)(WS_S32 ch, const hi_sdk_venc_ch_info *ctl);
typedef WS_S32 (*MPI_VENC_GET_DATA_ONE)(WS_S32 VencChn, ws_soft::ws_frame_info *frame_info, int* frame_packet_addr, int* frame_packet_len, int* frame_len, int* packet_num, WS_U32 buffer_size);
typedef WS_S32 (*MPI_VENC_REL_DATA_ONE)(WS_S32 VencChn);
typedef WS_S32 (*MPI_VENC_DISCARD_SNAP)(WS_S32 VencChn);
typedef WS_S32 (*MPI_REGION_MEM_CFG)(WS_U32 region_num);
typedef WS_S32 (*MPI_REGION_CREATE)(WS_U32 region_hand, hi_sdk_region_type region_type, WS_U32 width, WS_U32 height);
typedef WS_S32 (*MPI_REGION_DESTROY)(WS_U32 region_hand);
typedef WS_S32 (*MPI_REGION_OVERLAY_ATTACH)(WS_U32 RgnHandle, WS_S32 VencGrp, WS_S32 VencChn, RECT_S *rect);
typedef WS_S32 (*MPI_REGION_OVERLAY_DETACH)(WS_U32 RgnHandle, WS_S32 VencGrp, WS_S32 VencChn);
typedef WS_S32 (*MPI_REGION_COVER_ATTACH)(WS_U32 RgnHandle, WS_S32 ViDev, WS_S32 ViChn, WS_S32 VpssGrp, RECT_S *rect);
typedef WS_S32 (*MPI_REGION_COVER_DETACH)(WS_U32 RgnHandle, WS_S32 ViDev, WS_S32 ViChn, WS_S32 VpssGrp);
typedef WS_S32 (*MPI_REGION_OVERLAY_SET_BIT)(WS_U32 RgnHandle, WS_S16 *hi_bit, WS_U32 bit_w, WS_U32 bit_h);
typedef WS_S32 (*MPI_REGION_OVERLAY_CHANGE_POS)(WS_U32 RgnHandle, WS_S32 VencGrp, WS_S32 VencChn, WS_S32 x_pos, WS_S32 y_pos);
typedef WS_S32 (*MPI_REGION_COVER_CHANGE_POS)(WS_U32 RgnHandle, WS_S32 Vi_Dev, WS_S32 Vi_Chn, WS_S32 VpssGrp , WS_S32 x_pos, WS_S32 y_pos);
typedef WS_S32 (*MPI_PCIV_START_CH)(WS_S32 pciv_ch, PCIV_ATTR_S *pstPcivAttr);
typedef WS_S32 (*MPI_PCIV_STOP_CH)(WS_S32 pciv_ch);
typedef WS_S32 (*MPI_PCIV_MALLOC)(WS_U32 u32BlkSize, WS_U32 u32BlkCnt, WS_U32 u32PhyAddr[]);
typedef WS_S32 (*MPI_AI_START_DEV)(WS_S32 AudioDevId, WS_U32 MaxChn);
typedef WS_S32 (*MPI_AI_STOP_DEV)(WS_S32 AudioDevId);
typedef WS_S32 (*MPI_AI_START_CH)(WS_S32 AudioDevId, WS_S32 AiChn);
typedef WS_S32 (*MPI_AI_STOP_CH)(WS_S32 AudioDevId, WS_S32 AiChn);
typedef WS_S32 (*MPI_AO_START_DEV)(WS_S32 AudioDevId , WS_U32 MaxChn);
typedef WS_S32 (*MPI_AO_STOP_DEV)(WS_S32 AudioDevId);
typedef WS_S32 (*MPI_AO_START_CH)(WS_S32 AudioDevId, WS_S32 AoChn);
typedef WS_S32 (*MPI_AO_STOP_CH)(WS_S32 AudioDevId, WS_S32 AoChn);
typedef WS_S32 (*MPI_AENC_CREATE_CH)(WS_S32 AeChn, ws_soft::ws_frame_encode_type encode_type);
typedef WS_S32 (*MPI_AENC_DESTROY_CH)(WS_S32 AeChn);
typedef WS_S32 (*MPI_AENC_GET_STREAM)(WS_S32 AeChn, WS_BOOL bBlock, ws_soft::ws_frame_info *frame_info, WS_CHAR *data, WS_U32 buffer_length);
typedef WS_S32 (*MPI_ADEC_CREATE_CH)(WS_S32 AdChn, ws_frame_encode_type encode_type);
typedef WS_S32 (*MPI_ADEC_DESTROY_CH)(WS_S32 AdChn);
typedef WS_S32 (*MPI_ADEC_SEND_STREAM)(WS_S32 AdChn, const WS_CHAR* stream, WS_BOOL bBlock, WS_S32 nLen);
typedef WS_S32 (*MPI_TDE_ENABLE)();
typedef WS_S32 (*MPI_TDE_DISABLE)();
typedef WS_S32 (*MPI_TDE_BEGIN_JOB)();
typedef WS_S32 (*MPI_TDE_END_JOB)(WS_S32 s32Handle, WS_BOOL bSync, WS_BOOL bBlock, WS_U32 u32TimeOut);
typedef WS_S32 (*MPI_TDE_CANCEL_JOB)(WS_S32 s32Handle);
typedef WS_S32 (*MPI_TDE_QUICK_RESIZE)(WS_S32 , WS_U32 , WS_U32 , WS_U32 , WS_U32 , WS_U32 , WS_U32 , WS_U32 , WS_U32 , WS_U32 , WS_U32 , WS_U32  , WS_U32 );
typedef WS_S32 (*MPI_TDE_BEGIN_VIDEO_JOB)();
typedef WS_S32 (*MPI_VI_MEM_CFG)(WS_S32 ViChn, WS_U32 sdk_ch_idx);
typedef WS_S32 (*MPI_VI_SET_FPS)(WS_S32 ViChn, WS_S32 source_fps, WS_S32 target_fps);
typedef WS_S32 (*MPI_VI_START_DEV_CH)(WS_S32 ViDev , HI_VI_MODE m_localMode, WS_S32 ViChn, int x_ofset, int y_ofset, SIZE_S *pstSize, ws_soft::ws_video_std cur_std);
typedef WS_S32 (*MPI_VI_STOP_DEV_CH)(WS_S32 ViDev, WS_S32 ViChn);
typedef WS_S32 (*MPI_VI_STOP_CH)(WS_S32 ViChn);
typedef WS_S32 (*MPI_VO_START_HDMI)(ws_soft::ws_video_std m_std, const char *res_name);
typedef WS_S32 (*MPI_VO_STOP_HDMI)();
typedef WS_S32 (*MPI_VO_SET_OUT_PARAM)(WS_S32 VoDev, const ws_soft::ws_vo_output_param *vo_output_param);
typedef WS_S32 (*MPI_VO_GET_OUT_PARAM)(WS_S32 VoDev, ws_soft::ws_vo_output_param *vo_output_param);
typedef WS_S32 (*MPI_VO_SET_VGA_OUT_PARAM)(WS_S32 VoDev, const ws_soft::ws_vga_output_param *vga_output_param);
typedef WS_S32 (*MPI_VO_GET_VGA_OUT_PARAM)(WS_S32 VoDev, ws_soft::ws_vga_output_param *vga_output_param);
typedef WS_S32 (*MPI_VO_START_CVBS)(WS_S32 VoDev, ws_soft::ws_video_std m_std);
typedef WS_S32 (*MPI_VO_STOP_CVBS)(WS_S32 VoDev);
typedef WS_S32 (*MPI_VO_MEM_CFG)(int vo_dev_num);
typedef WS_S32 (*MPI_VO_CLR_DATA)(WS_S32 VoDev, int vo_wind, WS_BOOL clear_all);
typedef WS_S32 (*MPI_VO_START_WIND_DIS)(WS_S32 VoDev, int vo_wind, RECT_S *rect);
typedef WS_S32 (*MPI_VO_STOP_WIND_DIS)(WS_S32 VoDev, int vo_wind);
typedef WS_S32 (*MPI_VO_SET_WIND_FPS)(WS_S32 VoDev, int vo_wind, int fps);
typedef WS_S32 (*MPI_VO_SET_VGA_PARAM)(const HI_VGA_PARAM_S *pstVgaParam);
typedef WS_S32 (*MPI_VO_GET_VGA_PARAM)(HI_VGA_PARAM_S *pstVgaParam);

typedef struct hisi_ops_s
{
    MPI_SYS_GET_RESOL              mpi_sys_get_resol;
    MPI_SYS_INIT                        mpi_sys_init_f;
    MPI_VI_2_VPSS                      mpi_vi_2_vpss_f;
    MPI_VI_N2_VPSS                    mpi_vi_n2_vpss_f;
    MPI_VPSS_2_VPSS                  mpi_vpss_2_vpss_f;
    MPI_VPSS_N2_VPSS                mpi_vpss_n2_vpss_f;
    MPI_VPSS_2_VO                     mpi_vpss_2_vo_f;
    MPI_VPSS_N2_VO                   mpi_vpss_n2_vo_f;
    MPI_VPSS_2_VENC                  mpi_vpss_2_venc_f;
    MPI_VPSS_N2_VENC                mpi_vpss_n2_venc_f;
    MPI_VPSS_2_VDA                   mpi_vpss_2_vda_f;
    MPI_VPSS_N2_VDA                 mpi_vpss_n2_vda_f;
    MPI_PCIV_2_VO                     mpi_pciv_2_vo_f;
    MPI_PCIV_N2_VO                   mpi_pciv_n2_vo_f;
    MPI_VDEC_2_VPSS                  mpi_vdec_2_vpss_f;
    MPI_VDEC_N2_VPSS                mpi_vdec_n2_vpss_f;
    MPI_AI_2_AENC                     mpi_ai_2_aenc_f;
    MPI_AI_N2_AENC                   mpi_ai_n2_aenc_f;
    MPI_ADEC_2_AO                    mpi_adec_2_ao_f;
    MPI_ADEC_N2_AO                  mpi_adec_n2_ao_f;
    MPI_AI_2_AO                         mpi_ai_2_ao_f;
    MPI_AI_N2_AO                       mpi_ai_n2_ao_f;
    MPI_INIT_MPP_TIME               mpi_init_mpp_time_f;
    MPI_SYNC_MPP_TIME              mpi_sync_mpp_time_f;
    MPI_GET_MPP_TIME                mpi_get_mpp_time_f;
    MPI_MMZ_ALLOC                    mpi_mmz_alloc_f;
    MPI_VB_CREATE_LOGO           mpi_vb_create_logo_f;
    MPI_VPSS_CREATE_GRP          mpi_vpss_create_grp_f;
    MPI_VPSS_DESTROY_GRP        mpi_vpss_destroy_grp_f;
    MPI_VPSS_START_CH              mpi_vpss_start_ch_f;
    MPI_VPSS_STOP_CH               mpi_vpss_stop_ch_f;
    MPI_VPSS_SEND_FRAME          mpi_vpss_send_frame_f;
    MPI_VPSS_SWITCH_USR          mpi_vpss_switch_usr_f;
    MPI_VPSS_CANCEL_USR           mpi_vpss_cancel_usr_f;
    MPI_VPSS_SET_RECT_RITIO     mpi_vpss_set_rect_ritio_f;
    MPI_VPSS_SET_GRP_PARAM      mpi_vpss_set_grp_param_f;
    MPI_VPSS_NR_CTL                  mpi_vpss_nr_ctl_f;
    MPI_VPSS_IE_CTL                    mpi_vpss_ie_ctl_f;
    MPI_VPSS_CH_SP_CTL              mpi_vpss_ch_sp_ctl_f;
    MPI_VPSS_GET_NR                  mpi_vpss_get_nr_f;
    MPI_VPSS_GET_IE                     mpi_vpss_get_ie_f;
    MPI_VPSS_CH_GET_SP              mpi_vpss_ch_get_sp_f;
    MPI_VDEC_CREATE_CH             mpi_vdec_create_ch_f;
    MPI_VDEC_DESTROY_CH          mpi_vdec_destroy_ch_f;
    MPI_VDEC_GET_REMAIN           mpi_vdec_get_remain_f;
    MPI_VDEC_SEND_FRAME           mpi_vdec_send_frame_f;
    MPI_VDEC_GET_IMAGE             mpi_vdec_get_image_f;
    MPI_VDEC_REL_IMAGE             mpi_vdec_rel_image_f;
    MPI_VO_GET_TIME                  mpi_vo_get_time_f;
    MPI_FB_ENABLE                       mpi_fb_enable_f;
    MPI_FB_DISABLE                      mpi_fb_disable_f;
    MPI_FB_SET_TRANS                  mpi_fb_set_trans_f;
    MPI_FB_INIT_COLOR                mpi_fb_init_color_f;
    MPI_FB_SWITCH_RESOL            mpi_fb_switch_resol_f;
    MPI_FB_GET_PHY                     mpi_fb_get_phy_f;
    MPI_VDEC_MEM_CFG                mpi_vdec_mem_cfg_f;
    MPI_VPSS_MEM_CFG                mpi_vpss_mem_cfg_f;
    MPI_VDA_MEM_CFG                  mpi_vda_mem_cfg_f;
    MPI_VDA_CREATE_CH               mpi_vda_create_ch_f;
    MPI_VDA_START_CH                 mpi_vda_start_ch_f;
    MPI_VDA_STOP_CH                   mpi_vda_stop_ch_f;
    MPI_VDA_DESTROY_CH             mpi_vda_destroy_ch_f;
    MPI_VDA_GET_CH_DATA           mpi_vda_get_ch_data_f;
    MPI_VENC_MEM_CFG                 mpi_venc_mem_cfg_f;
    MPI_VENC_START_CH                mpi_venc_start_ch_f;
    MPI_VENC_STOP_CH                 mpi_venc_stop_ch_f;
    MPI_VENC_RESTART_CH            mpi_venc_restart_ch_f;
    MPI_VENC_ENABLE_CH              mpi_venc_enable_ch_f;
    MPI_VENC_DISABLE_CH            mpi_venc_disable_ch_f;
    MPI_VENC_GET_FD                   mpi_venc_get_fd_f;
    MPI_VENC_GET_SNAP_DATA      mpi_venc_get_snap_data_f;
    MPI_VENC_SET_RC                   mpi_venc_set_rc_f;
    MPI_VENC_GET_DATA_ONE       mpi_venc_get_data_one_f;
    MPI_VENC_REL_DATA_ONE        mpi_venc_rel_data_one_f;
    MPI_VENC_DISCARD_SNAP       mpi_venc_discard_snap_f;
    MPI_REGION_MEM_CFG             mpi_region_mem_cfg_f;
    MPI_REGION_CREATE                               mpi_region_create_f;
    MPI_REGION_DESTROY                             mpi_region_distroy_f;
    MPI_REGION_OVERLAY_ATTACH                 mpi_region_overlay_attach_f;
    MPI_REGION_OVERLAY_DETACH                 mpi_region_overlay_detach_f;
    MPI_REGION_COVER_ATTACH                    mpi_region_cover_attach_f;
    MPI_REGION_COVER_DETACH                    mpi_region_cover_deatch_f;
    MPI_REGION_OVERLAY_SET_BIT                mpi_region_overlay_set_bit_f;
    MPI_REGION_OVERLAY_CHANGE_POS         mpi_region_overlay_change_pos_f;
    MPI_REGION_COVER_CHANGE_POS             mpi_region_cover_change_pos;
    MPI_PCIV_START_CH                                mpi_pciv_start_ch_f;
    MPI_PCIV_STOP_CH                                  mpi_pciv_stop_ch_f;
    MPI_PCIV_MALLOC                                    mpi_pciv_malloc_f;
    MPI_AI_START_DEV                                   mpi_ai_start_dev_f;
    MPI_AI_STOP_DEV                                    mpi_ai_stop_dev_f;
    MPI_AI_START_CH                                     mpi_ai_start_ch_f;
    MPI_AI_STOP_CH                                      mpi_ai_stop_ch_f;
    MPI_AO_START_DEV                                  mpi_ao_start_dev_f;
    MPI_AO_STOP_DEV                                   mpi_ao_stop_dev_f;
    MPI_AO_START_CH                                   mpi_ao_start_ch_f;
    MPI_AO_STOP_CH                                     mpi_ao_stop_ch_f;
    MPI_AENC_CREATE_CH                              mpi_aenc_create_ch_f;
    MPI_AENC_DESTROY_CH                            mpi_aenc_destroy_ch_f;
    MPI_AENC_GET_STREAM                             mpi_aenc_get_stream_f;
    MPI_ADEC_CREATE_CH                              mpi_adec_create_ch_f;
    MPI_ADEC_DESTROY_CH                             mpi_adec_destroy_ch_f;
    MPI_ADEC_SEND_STREAM                            mpi_adec_send_stream_f;
    MPI_TDE_ENABLE                                       mpi_tde_enable_f;
    MPI_TDE_DISABLE                                     mpi_tde_disable_f;
    MPI_TDE_BEGIN_JOB                                   mpi_tde_begin_job_f;
    MPI_TDE_END_JOB                                     mpi_tde_end_job_f;
    MPI_TDE_CANCEL_JOB                                mpi_tde_cancel_job_f;
    MPI_TDE_QUICK_RESIZE                             mpi_tde_quick_resize_f;
    MPI_TDE_BEGIN_VIDEO_JOB                       mpi_tde_begin_video_job_f;
    MPI_VI_MEM_CFG                                      mpi_vi_mem_cfg_f;
    MPI_VI_SET_FPS                                          mpi_vi_set_fps_f;
    MPI_VI_START_DEV_CH                                 mpi_vi_start_dev_ch_f;
    MPI_VI_STOP_DEV_CH                                  mpi_vi_stop_dev_ch_f;
    MPI_VI_STOP_CH                                          mpi_vi_stop_ch_f;
    MPI_VO_START_HDMI                                   mpi_vo_start_hdmi_f;
    MPI_VO_STOP_HDMI                                    mpi_vo_stop_hdmi_f;
    MPI_VO_SET_OUT_PARAM                            mpi_vo_set_out_param_f;
    MPI_VO_GET_OUT_PARAM                            mpi_vo_get_out_param_f;
    MPI_VO_SET_VGA_OUT_PARAM                     mpi_vo_set_vga_out_param_f;
    MPI_VO_GET_VGA_OUT_PARAM                    mpi_vo_get_vga_out_param_f;
    MPI_VO_START_CVBS                                 mpi_vo_start_cvbs_f;
    MPI_VO_STOP_CVBS                                    mpi_vo_stop_cvbs_f;
    MPI_VO_MEM_CFG                                       mpi_vo_mem_cfg_f;
    MPI_VO_CLR_DATA                                      mpi_vo_clr_data_f;
    MPI_VO_START_WIND_DIS                           mpi_vo_start_wind_dis_f;
    MPI_VO_STOP_WIND_DIS                            mpi_vo_stop_wind_dis_f;
    MPI_VO_SET_WIND_FPS                               mpi_vo_set_wind_fps_f;
    MPI_VO_SET_VGA_PARAM                            mpi_vo_set_vga_param_f;
    MPI_VO_GET_VGA_PARAM                            mpi_vo_get_vga_param_f;
}WS_HISI_OPS_S;

namespace hi_sdk
{
    typedef enum
    {
        SDK_LV_IDENTITY_MAGIC  = 100,
        SDK_REC_USR_ID_MAGIC = 200,
        SDK_PB_USR_ID_MAGIC = 300,
        SDK_LV_LOGO_IDENTITY_MAGIC = 400,

        SDK_TIME_REGION_USR_ID_MAGIC = 1000,
        SDK_LV_MANAGE_IDENTITY_MAGIC  = 2000,

        SDK_VI_IDENTITY_MAGIC = 8000,
        SDK_VDEC_PIPE_IDENTITY_MAGIC = 8200,
    } sdk_identity_magic;

    typedef enum
    {
        VO_DEV_UNKNOW,
        VO_DEV_HD,
        VO_DEV_SD,
    } sdk_vo_dev_type_e;
    
    typedef enum
    {
        VO_VDEC_DIRECT = 0,
        VO_VDEC_BY_VPSS,
        VO_VDEC_UNKNOW = -1,
    } hi_vdec_vo_bind_type;						//2now all use VO_VDEC_BY_VPSS

    typedef enum
    {
        VDEC_SRC_VO = 0,
        LV_SRC_VO,
    }hi_vo_src_type;

    typedef enum
    {
        WS_PCIV_BIND_VO_DIRECT = 0x0,
        WS_PCIV_BIND_VPSS,
        WS_PCIV_BIND_UNKNOW = 0xFFFFFFFF,
    }ws_pciv_bind_type;

    typedef enum
    {
        HI_BIND_DST_VO = 0,
        HI_BIND_DST_VEVC,
        HI_BIND_DST_VPSS,
        HI_BIND_DST_VDA,
        HI_BIND_DST_UNKNOW = -1,
    } hi_bind_dst_type;

    typedef struct
    {
        int is_bind;
        hi_bind_dst_type bind_type;
        WS_S32 hi_vo_dev;
        WS_S32 hi_vo_win;

        int vpss_grp_idx;
        WS_S32 hi_vpss_grp;

        WS_S32 hi_venc_grp;
        WS_S32 hi_vda_ch;
        WS_S32 hi_venc_ch;
    } hi_bind_dst_info;

    typedef enum
    {
        VDA_UNKONW = 0,
        VDA_FOR_MD,
        VDA_FOR_OD,
    } hi_vda_type;

    typedef enum
    {
        VI_VENC_DIRECT = 0,
        VI_VENC_BY_VPSS,
        VI_VENC_UNKNOW = -1,
    } hi_vi_venc_bind_type;

    typedef enum
    {
        REGION_EX_UNKONW = 0,
        REGION_VI,
        REGION_VENC_MAIN,
        REGION_VENC_SUB1,
        REGION_VENC_SUB2,
        REGION_VENC_JPEG,
    } hi_sdk_region_type_ex;

    typedef enum
    {
        VDA_BIND_TYPE_UNKNOW,
        VI_VDA_DIRECT,
        VI_VPSS_VDA,
    } hi_vda_bind_type;

    typedef enum
    {
        HI_MPP_INIT = 0x0,
        HI_VI_BAND_VPSS = 0x1,
        HI_VPSS_BAND_VO = 0x2,
        HI_V0_BAND_WBC = 0x3,
        HI_VI_BAND_VO = 0x4,
        HI_VPSS_BAND_VENC = 0x5,
        HI_VPSS_BAND_VDA = 0x6,
        HI_VDEC_BAND_VPSS = 0x7,
        HI_VDEC_BAND_VO = 0x8,
        HI_AI_BAND_AENC = 0x9,
        HI_ADEC_BAND_AO = 0xa,
        HI_AI_BAND_AO = 0xb,
        HI_VPSS_GRP = 0xc,
        HI_VPSS_SWITCH_MODE = 0xd,
        HI_START_VPSS = 0xe,
        HI_VDEC_CREAT = 0xf,
        HI_VO_START = 0x10,
        HI_VO_WIND_DIS = 0x11,
        HI_VO_START_VIDEO_LAYER = 0x12,
        HI_VO_START_HDMI = 0x13,
        HI_VO_WBC = 0x14,
        HI_FB = 0x15,
        HI_VI_DEV = 0x16,
        HI_VI_CH = 0x17,
        HI_VDA_CH = 0x18,
        HI_VDA_VI_CH = 0x19,
        HI_VDA_DATA = 0x1a,
        HI_VENC_GRP = 0x1b,
        HI_VENC_CH = 0x1c,
        HI_AI_DEV = 0x1d,
        HI_AI_CH = 0x1e,
        HI_AO_DEV = 0x1f,
        HI_AO_CH = 0x20,
        HI_AENC_CH = 0x21,
        HI_ADEC_CH = 0x22,
        HI_TDA = 0x23,
        HI_VO_WIND_SHOW = 0x24,
        HI_AENC_STREAM = 0x25,
        HI_VPSS_BAND_VPSS = 0x26,
    } hi_mode_name;

    typedef struct
    {
        int idx1;           ///*监控模块编号属性 可以是通道号 设备号 组号等等 这里不限定类型*///
        int idx2;
        int idx3;
        int idx4;
        hi_mode_name mode;  ///*监控模块名称*///
        int mode_count;     ///*模块当前状态 由各模块自身控制*///
    } ws_platform_monitor_node;   ////*platform 监控节点记录*///

    typedef struct ws_platform_monitor
    {
        ws_platform_monitor_node node;
        ws_platform_monitor *pre;
        ws_platform_monitor *next;
    } ws_platform_monitor;

//---------------------------------------------
    WS_S32 ws_load_hi_func(WS_LIB_HANDLE handle);
    
//--------------------------------------------- mpi_sys ----------------------------------------
    void ws_platfor_ops_lock(const WS_CHAR * file_name, const WS_CHAR * func_name);
    void ws_platfor_ops_unlock(const WS_CHAR * file_name, const WS_CHAR * func_name);
    int ws_platform_ops_get_node(ws_platform_monitor_node *node);
    int ws_platform_ops_set_node(const ws_platform_monitor_node *node);
    WS_S32 ws_platform_ops_add_count(int idx1, int idx2, int idx3, int idx4, hi_mode_name mode);
    WS_S32 ws_platform_ops_del_count(int idx1, int idx2, int idx3, int idx4, hi_mode_name mode);
    int is_same_node(const ws_platform_monitor_node *node1,const ws_platform_monitor_node *node2);

    WS_S32 ws_platform_ops_check_add_count(int idx1, int idx2, int idx3, int idx4, hi_mode_name mode);
    WS_S32 ws_platform_ops_check_del_count(int idx1, int idx2, int idx3, int idx4, hi_mode_name mode);

    WS_S32 ws_hardware_mpi_get_support_resol(hi_sdk_res_info** m_sys_resol, int* m_sys_num);
    WS_S32 ws_hardware_mpi_sys_init(WS_VB_CONF_S *pstVbConf);
    WS_S32 ws_hardware_mpi_sys_vi_bind_vpss(WS_S32 ViDev, WS_S32 ViChn, WS_S32 VpssGrp);
    WS_S32 ws_hardware_mpi_sys_vi_unbind_vpss(WS_S32 ViDev, WS_S32 ViChn, WS_S32 VpssGrp);
    WS_S32 ws_hardware_mpi_sys_vpss_bind_vo(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 VoDev, WS_S32 VoChn);
    WS_S32 ws_hardware_mpi_sys_vpss_unbind_vo(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 VoDev, WS_S32 VoChn);

    WS_S32 ws_hardware_mpi_sys_vpss_bind_venc(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 GrpChn, WS_S32 VencChn);
    WS_S32 ws_hardware_mpi_sys_vpss_unbind_venc(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 GrpChn, WS_S32 VencChn);

    WS_S32 ws_hardware_mpi_sys_vpss_bind_vpss(WS_S32 src_VpssGrp, WS_S32 src_VpssChn, WS_S32 dest_VpssGrp);
    WS_S32 ws_hardware_mpi_sys_vpss_unbind_vpss(WS_S32 src_VpssGrp, WS_S32 src_VpssChn, WS_S32 dest_VpssGrp);

    WS_S32 ws_hardware_mpi_sys_vpss_bind_vda(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 VdaChn);
    WS_S32 ws_hardware_mpi_sys_vpss_unbind_vda(WS_S32 VpssGrp, WS_S32 VpssChn, WS_S32 VdaChn);

    WS_S32 ws_hardware_mpi_sys_pciv_bind_vo(WS_S32 PcivCh, WS_S32 VoDev, WS_S32 VoChn);
    WS_S32 ws_hardware_mpi_sys_pciv_unbind_vo(WS_S32 PcivCh, WS_S32 VoDev, WS_S32 VoChn);

    WS_S32 ws_hardware_mpi_sys_vdec_bind_vpss(WS_S32 VdChn, WS_S32 VpssGrp);
    WS_S32 ws_hardware_mpi_sys_vdec_unbind_vpss(WS_S32 VdChn, WS_S32 VpssGrp);

    WS_S32 ws_hardware_mpi_sys_ai_bind_aenc(WS_S32 AiDev, WS_S32 AiChn, WS_S32 AeChn);
    WS_S32 ws_hardware_mpi_sys_ai_unbind_aenc(WS_S32 AiDev, WS_S32 AiChn, WS_S32 AeChn);
    WS_S32 ws_hardware_mpi_sys_adec_bind_ao(WS_S32 AdChn, WS_S32 AoDev, WS_S32 AoChn);
    WS_S32 ws_hardware_mpi_sys_adec_unbind_ao(WS_S32 AdChn, WS_S32 AoDev, WS_S32 AoChn);
    WS_S32 ws_hardware_mpi_sys_ai_bind_ao(WS_S32 AiDev, WS_S32 AiChn, WS_S32 AoDev, WS_S32 AoChn);
    WS_S32 ws_hardware_mpi_sys_ai_unbind_ao(WS_S32 AiDev, WS_S32 AiChn, WS_S32 AoDev, WS_S32 AoChn);

    WS_S32 ws_software_mpi_sys_calc_vb_size(WS_VIDEO_NORM_E enNorm, WS_PIC_SIZE_E enPicSize, WS_PIXEL_FORMAT_E enPixFmt, WS_U32 u32AlignWidth, WS_U32 *blkSize);
    WS_S32 ws_hardware_mpi_init_mpp_time(WS_U64 u64PtsBase);
    WS_S32 ws_hardware_mpi_sync_mpp_time(WS_U64 u64PtsBase);
    WS_S32 ws_hardware_mpi_get_mpp_time(WS_U64 *pu64CurPts);

    WS_ERR ws_hardware_mpi_mmz_alloc(WS_U32 *pu32PhyAddr, WS_UCHAR **ppVirtAddr,  WS_U32 u32Len);
    //----------------------------------------------vb
    WS_ERR ws_hardware_vb_create_logo(WS_U32 u32BlkSize, WS_U32 u32BlkCnt, WS_U32 uvSize, WS_U32 u32Stride, WS_U32 u32Width , WS_U32 u32Height, hisilicon_logo_info *m_logo);

    //--------------------------------------------- vpss ----------------------------------------------
    WS_S32 ws_hardware_vpss_creat_grp(WS_S32 ViChn, WS_S32 VpssGrp, WS_SIZE_S *pstSize, hi_vpss_src_type src_type);
    WS_S32 ws_hardware_vpss_destroy_grp(WS_S32 VpssGrp);
    WS_S32 ws_hardware_vpss_start_ch(WS_S32 VpssGrp, WS_S32 VpssChn, int enable_gride);
    WS_S32 ws_hardware_vpss_stop_ch(WS_S32 VpssGrp, WS_S32 VpssChn);
    WS_S32 ws_hardware_vpss_send_frame(WS_S32 VpssGrp, WS_VIDEO_FRAME_INFO_S *frame);
    WS_S32 ws_hardware_vpss_switch_usr_mode(WS_S32 VpssGrp, WS_S32 VpssChn, int dst_width, int dst_height);
    WS_S32 ws_hardware_vpss_cancel_usr_mode(WS_S32 VpssGrp, WS_S32 VpssChn);
    WS_S32 ws_hardware_vpss_set_src_rect_ritio(WS_S32 VpssGrp, WS_RECT_S *rect);

    WS_S32 ws_hardware_vpss_set_grp_param(WS_S32 VpssGrp, const ws_soft::ws_vpss_param *vpss_param);
    WS_S32 ws_hardware_vpss_group_NR_ctl(WS_S32 VpssGrp, WS_BOOL enable);
    WS_S32 ws_hardware_vpss_group_IE_ctl(WS_S32 VpssGrp, WS_BOOL enable);
    WS_S32 ws_hardware_vpss_channel_SP_ctl(WS_S32 VpssGrp, WS_S32 VpssChn, WS_BOOL enable);

    WS_S32 ws_hardware_vpss_grp_get_NR_status(WS_S32 VpssGrp, WS_BOOL *enable);
    WS_S32 ws_hardware_vpss_grp_get_IE_status(WS_S32 VpssGrp, WS_BOOL *enable);
    WS_S32 ws_hardware_vpss_chn_get_SP_status(WS_S32 VpssGrp, WS_S32 VpssChn, WS_BOOL *enable);

    //--------------------------------------------- vdec ----------------------------------------------
    int ws_hardware_vdec_creat_ch(WS_S32 vdec_ch, int width, int height, WS_PAYLOAD_TYPE_E enType, int *hisi_buf_size);
    int ws_hardware_vdec_destroy_ch(WS_S32 vdec_ch);
    int ws_hardware_vdec_get_remain_num(WS_S32 vdec_ch);
    int ws_hardware_vdec_send_frame(WS_S32 vdec_ch, const char *data, int len, WS_U64 pts);
    int ws_hardware_vdec_get_image(WS_S32 VdChn, WS_VIDEO_FRAME_INFO_S *pstFrameInfo, WS_U32 u32BlockFlag);
    int ws_hardware_vdec_release_image(WS_S32 VdChn, WS_VIDEO_FRAME_INFO_S *pstFrameInfo);

    //--------------------------------------------- fb ----------------------------------------------
    WS_S32 ws_hardware_vdec_mem_cfg(int vdec_num);
    WS_S32 ws_hardware_vpss_mem_cfg(int vpss_num);

    //----------------------------------------------vda----------------------------------------------
    WS_S32 ws_hardware_vda_mem_cfg(WS_U32 iNum);
    WS_S32 ws_hardware_vda_create_ch(WS_S32 VdaChn, WS_U32 ch_width, WS_U32 ch_height);
    WS_S32 ws_hardware_vda_destroy_ch(WS_S32 VdaChn);
    WS_S32 ws_hardware_vda_start_ch(WS_S32 VdaChn);
    WS_S32 ws_hardware_vda_stop_ch(WS_S32 VdaChn);
    WS_ERR ws_hardware_vda_get_ch_data(WS_S32 VdaChn, WS_S32 *check_blk_idx, WS_U32 check_blk_num, WS_U32 total_blk_num, WS_S32 sad_th, WS_S32 percent, ws_soft::ws_md_state *md_state);

    //-----------------------------------------------venc----------------------------------------------
    WS_S32 ws_hardware_venc_mem_cfg(WS_S32 grp_num);
    WS_S32 ws_hardware_venc_start_ch(WS_S32 VencGrp, WS_S32 VencChn, const hi_sdk_venc_ch_info *ctl, WS_SIZE_S *enc_size);
    WS_S32 ws_hardware_venc_stop_ch(WS_S32 VencGrp, WS_S32 VencChn);
    WS_S32 ws_hardware_venc_restart_ch_recv(WS_S32 VencChn);
    WS_S32 ws_hardware_venc_get_fd(WS_S32 VencChn);
    WS_ERR ws_hardware_fetch_snap_data(WS_S32 VencGrp, WS_S32 VencChn, time_t* CompareTime, const WS_CHAR *absolute_path, WS_CHAR *picture_cache, WS_S32 pic_size, WS_U32 *pic_length, time_t* frame_time, ws_soft::ws_snap_type snap_type);
    WS_S32 ws_hardware_venc_enable_ch(WS_S32 VencChn);
    WS_S32 ws_hardware_venc_disable_ch(WS_S32 VencChn);
    WS_ERR ws_hardware_venc_discard_snap(WS_S32 VencChn);
    WS_S32 ws_hardware_venc_get_data_one(WS_S32 VencChn, ws_soft::ws_frame_info *frame_info, int* frame_packet_addr, int* frame_packet_len, int* frame_len, int* packet_num, WS_U32 buffer_size);    
    WS_S32 ws_hardware_venc_rel_data_one(WS_S32 VencChn);
    WS_S32 ws_hardware_venc_set_rc_para(WS_S32 ch, const hi_sdk_venc_ch_info *ctl);
    

    //-----------------------------------------------region---------------------------------------------
    WS_S32 ws_hardware_region_mem_cfg(WS_U32 region_num);
    WS_S32 ws_hardware_region_creat(WS_U32 region_hand, hi_sdk_region_type region_type, WS_U32 width, WS_U32 height);
    WS_S32 ws_hardware_region_destroy(WS_U32 region_hand);
    WS_S32 ws_hardware_region_overlay_attach(WS_U32 RgnHandle, WS_S32 VencGrp, WS_S32 VencChn, WS_RECT_S *rect);
    WS_S32 ws_hardware_region_overlay_detach(WS_U32 RgnHandle, WS_S32 VencGrp, WS_S32 VencChn);
    WS_S32 ws_hardware_region_cover_attach(WS_U32 RgnHandle, WS_S32 ViDev, WS_S32 ViChn, WS_S32 VpssGrp, WS_RECT_S *rect);
    WS_S32 ws_hardware_region_cover_detach(WS_U32 RgnHandle, WS_S32 ViDev, WS_S32 ViChn, WS_S32 VpssGrp);
    WS_S32 ws_hardware_region_overlay_set_bit(WS_U32 RgnHandle, WS_S16 *hi_bit, WS_U32 bit_w, WS_U32 bit_h);
    WS_S32 ws_hardware_region_overlay_change_pos(WS_U32 RgnHandle, WS_S32 VencGrp, WS_S32 VencChn, WS_S32 x_pos, WS_S32 y_pos);
    WS_S32 ws_hardware_region_cover_change_pos(WS_U32 RgnHandle, WS_S32 Vi_Dev, WS_S32 Vi_Chn, WS_S32 VpssGrp , WS_S32 x_pos, WS_S32 y_pos);

    //-----------------------------------------------pciv----------------------------------------------------
    WS_S32 ws_hardware_pciv_start_ch(WS_S32 pciv_ch, WS_PCIV_ATTR_S *pstPcivAttr);
    WS_S32 ws_hardware_pciv_stop_ch(WS_S32 pciv_ch);
    WS_S32 ws_hardware_pciv_malloc(WS_U32 u32BlkSize, WS_U32 u32BlkCnt, WS_U32 u32PhyAddr[]);

//------------------------------------------------ai----------------------------------------------
    WS_S32 ws_hardware_ai_start_dev(WS_S32 AudioDevId, WS_U32 MaxChn);
    WS_S32 ws_hardware_ai_stop_dev(WS_S32 AudioDevId);

    WS_S32 ws_hardware_ai_start_ch(WS_S32 AudioDevId, WS_S32 AiChn);
    WS_S32 ws_hardware_ai_stop_ch(WS_S32 AudioDevId, WS_S32 AiChn);
//-----------------------------------------------end---------------------------------------------

//----------------------------------------------- ao----------------------------------------------
    WS_S32 ws_hardware_ao_start_dev(WS_S32 AudioDevId , WS_U32 MaxChn);
    WS_S32 ws_hardware_ao_stop_dev(WS_S32 AudioDevId);

    WS_S32 ws_hardware_ao_start_ch(WS_S32 AudioDevId, WS_S32 AoChn);
    WS_S32 ws_hardware_ao_stop_ch(WS_S32 AudioDevId, WS_S32 AoChn);
//-----------------------------------------------end----------------------------------------------

//-----------------------------------------------aenc---------------------------------------------
    WS_S32 ws_hardware_aenc_create_ch(WS_S32 AeChn, ws_soft::ws_frame_encode_type encode_type);
    WS_S32 ws_hardware_aenc_destroy_ch(WS_S32 AeChn);
    WS_S32 ws_hardware_aenc_get_stream(WS_S32 AeChn, WS_BOOL bBlock, ws_soft::ws_frame_info *frame_info, WS_CHAR *data, WS_U32 buffer_length);
//-----------------------------------------------end----------------------------------------------

//-----------------------------------------------adec----------------------------------------------
    WS_S32 ws_hardware_adec_create_ch(WS_S32 AdChn, ws_soft::ws_frame_encode_type encode_type);
    WS_S32 ws_hardware_adec_destroy_ch(WS_S32 AeChn);
    WS_S32 ws_hardware_adec_send_stream(WS_S32 AdChn, const WS_CHAR* stream, WS_BOOL bBlock, WS_S32 nLen);
//-----------------------------------------------end-----------------------------------------------

//--------------------------------------------- tde ----------------------------------------------
    WS_S32 ws_hardware_tde_enable();
    void ws_hardware_tde_disable();
    WS_S32  ws_hardware_tde_begin_job();
    WS_S32  ws_hardware_tde_end_job(WS_S32 s32Handle, WS_BOOL bSync, WS_BOOL bBlock, WS_U32 u32TimeOut);
    WS_S32  ws_hardware_tde_cancel_job(WS_S32 s32Handle);
    WS_S32  ws_hardware_tde_quick_resize(WS_S32 s32Handle, 
        WS_U32 srcLeft, WS_U32 srcTop, WS_U32 srcWidth, WS_U32 srcHeight, WS_U32 srcAddr, WS_U32 srcStride, 
        WS_U32 dstLeft, WS_U32 dstTop, WS_U32 dstWidth, WS_U32 dstHeight, WS_U32 dstAddr , WS_U32 dstStride);
    WS_S32  ws_hardware_tde_begin_video_job();

    void clr_bind_dst(hi_bind_dst_info *bind_dst);
    void mylib_clear_roi(ws_utility::ws_abstract_rect *roi);

    unsigned char ws_software_convert_rgb_to_y(unsigned char r, unsigned char g, unsigned char b);
    unsigned char ws_software_convert_rgb_to_u(unsigned char r, unsigned char g, unsigned char b);
    unsigned char ws_software_convert_rgb_to_v(unsigned char r, unsigned char g, unsigned char b);

    typedef enum
    {
        WS_HI_VI_MODULE = 0x0,
        WS_HI_VPSS_MODULE,
        WS_HI_VENC_MODULE,
        WS_HI_VO_MODULE,
        WS_HI_OSD_MODULE,
        WS_HI_VDEC_MODULE,
        WS_HI_PCIV_MODULE,
    } ws_module_name;

    // 支持对外输出的接口函数--------------------------------------    

    WS_ERR ws_hardware_load_hisi_lib();
    
    WS_ERR ws_hardware_vi_mem_cfg(WS_S32 ViChn, WS_U32 sdk_ch_idx);
    WS_ERR ws_hardware_vi_set_fps(WS_S32 ViChn, WS_S32 source_fps, WS_S32 target_fps);
    WS_ERR ws_hardware_vi_start_dev_ch(WS_S32 ViDev , HI_VI_MODE m_localMode, WS_S32 ViChn, int x_ofset, int y_ofset, WS_SIZE_S *pstSize, ws_soft::ws_video_std cur_std);
    WS_ERR ws_hardware_vi_stop_dev_ch(WS_S32 ViDev, WS_S32 ViChn);    
    WS_ERR ws_hardware_vi_stop_ch(WS_S32 ViChn);

    WS_ERR ws_hardware_vo_mem_cfg(int vo_dev_num);
    WS_ERR ws_hardware_vo_start_hdmi(ws_soft::ws_video_std std, const char *res_name);
    WS_ERR ws_hardware_vo_stop_hdmi();
    WS_ERR ws_hardware_vo_set_output_param(WS_S32 VoDev, const ws_soft::ws_vo_output_param *vo_output_param);
    WS_ERR ws_hardware_vo_get_output_param(WS_S32 VoDev, ws_soft::ws_vo_output_param *vo_output_param);
    WS_ERR ws_hardware_vo_set_vga_output_param(WS_S32 VoDev, const ws_soft::ws_vga_output_param *vga_output_param);
    WS_ERR ws_hardware_vo_get_vga_output_param(WS_S32 VoDev, ws_soft::ws_vga_output_param *vga_output_param);
    WS_ERR ws_hardware_vo_start_cvbs(WS_S32 VoDev, ws_soft::ws_video_std std);
    WS_ERR ws_hardware_vo_stop_cvbs(WS_S32 VoDev);
    WS_ERR ws_hardware_vo_clear_data_buffer(WS_S32 VoDev, int vo_wind, WS_BOOL clear_all);
    WS_ERR ws_hardware_vo_start_wind_dis(WS_S32 VoDev, int vo_wind, WS_RECT_S *rect);
    WS_ERR ws_hardware_vo_stop_wind_dis(WS_S32 VoDev, int vo_wind);
    WS_ERR ws_hardware_vo_set_wind_fps(WS_S32 VoDev, int vo_wind, int fps);
    WS_ERR ws_hardware_vo_get_dis_pts(WS_S32 VoDev, WS_S32 vo_wind, WS_U64 *pts);
    // 调试使用，后续需要思考如何封装与合并
    WS_ERR ws_hardware_vo_set_vga_param(const HI_VGA_PARAM_S *pstVgaParam);
    WS_ERR ws_hardware_vo_get_vga_param(HI_VGA_PARAM_S *pstVgaParam);

    WS_S32 ws_hardware_fb_enable(int fd);
    WS_S32 ws_hardware_fb_disable(int fd);
    WS_S32 ws_hardware_fb_set_trans(int fd, int percent);
    WS_S32 ws_hardware_fb_init_color_fmt(int fd, int width, int height, WS_HIFB_COLOR_FMT_E color_fmt,void **addr, int *max_size);
    WS_S32 ws_hardware_fb_switch_resol(int fd, int width, int height);
    WS_S32 ws_hardware_fb_get_phy_addr(int fd, WS_U32 *phy_addr, WS_U32 *phy_stride);
} //namespace hi_sdk

#endif  //#ifndef _WS_PLATFORM_RESOURCE_MANAGE_H_

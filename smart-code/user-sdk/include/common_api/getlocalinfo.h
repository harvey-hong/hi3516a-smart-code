#ifndef GET_LOCAL_INFO_H
#define GET_LOCAL_INFO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "HieServer_Common.h"
#include "HieServer_Cfg.h"
#include "ws_comm_data.h"
#include "ws_comm_errno.h"
#include "ws_comm_debug.h"
#include "ws_IPdetection_API.h"	

#include "ws_comm_sys.h"
#include "ws_comm_type.h"
#include "ws_model_api.h"
#ifndef _WS_IPC_
#define PRIVATE_USER_CONFIG_FILE "/mnt/mtd/app/p2p_device.ini"
#else
#define PRIVATE_USER_CONFIG_FILE "/usr/local/etc/Edvr.cfg"
#include "ws_history_api.h"
#endif

using namespace ws_utility;

using namespace ws_soft;	

#define IN        	/* 输入参数，仅传入参数值 */
#define OUT      	/* 输出参数，使用指针来保存函数的结果参数，实现传出参数值 */
#define IN_OUT  	/* 输入输出参数，通过该指针传入具体的参数值，也通过该指针保存函数的结果参数，实现传出参数值 */

#if defined( __cplusplus)
#define HYPRIVATE_API  extern "C" __attribute__((visibility("default")))
#else
#define HYPRIVATE_API  __attribute__((visibility("default")))
#endif


namespace GETLOCALINFO
{

typedef struct
{
    int tcp_port;
    int rtp_port;
    int cmd_port;
    int rtsp_port;
    int reserve[4];
}Port_Info;

typedef struct
{
    unsigned int  base_version;
    unsigned int  minor_version;
    unsigned int  sub_version;
} snet_soft_version;

typedef struct
{
    int 	dev_type;
    char    product_name[32];   
    char    serial_no[36];    
    unsigned int  video_ch_num;   
    unsigned int  pb_ch_num;     

    unsigned int  alarm_in_num;  
    unsigned int  alarm_out_num; 

    bool 	support_speaking;  

    int     max_md_rect_num;    

    int     sata_slot_num;  
    snet_soft_version base_version;   
    snet_soft_version soft_version;   

    snet_soft_version hard_version;   
    char    date_buf[12];      
    char    description[48];        

    int dev_board_id;       

    int audio_ch_num;   

    int main_enc_size;  
    unsigned int main_max_bps;    
    unsigned int main_min_bps;    

    int sub_enc_size;
    unsigned int sub_max_bps;
    unsigned int sub_min_bps;

    unsigned int  audio_out_num;  

    bool 	dev_type_for_720p;      

    int 	rec_format;

    int	 rec_disk_format;
    bool	 support_wifi;
    bool	 is_slave_device;
    unsigned int	  pb_pic_ch_num;	 
	
    int reserverd[18];

} snet_device_capability;

HYPRIVATE_API int Get_QQDeviceType(IN DWORD dwUserID, OUT bool *bQQDeviceType);
HYPRIVATE_API int Get_DeviceType(IN DWORD dwUserID,OUT int *DeviceType);
HYPRIVATE_API int Login(IN const LPRemoteUserInfo pRemoteUserInfo, OUT DWORD *pUserID);
HYPRIVATE_API int Logout(IN DWORD pUserID);

HYPRIVATE_API WS_ERR localInfo_getNetPort2IP(DWORD dwUserID, int* cmd_port, int* http_port, char* local_ip, int nLen);
HYPRIVATE_API WS_ERR localInfo_getChan2AlarmNum(DWORD dwUserID, int* ChanCnt, int* AlarmCnt, char* local_uid, int nLen);
    
HYPRIVATE_API int Get_local_ip_info(DWORD dwUserID, DWORD dwMajorType, DWORD dwMinorType, BYTE *pBuffer, DWORD *dwBufLen);
HYPRIVATE_API int Get_local_port_info(DWORD dwUserID, DWORD dwMajorType, DWORD dwMinorType, BYTE *pBuffer, DWORD *dwBufLen);
HYPRIVATE_API int GetPassByName(IN const char *usr_name, OUT char *password,IN int passlen);
HYPRIVATE_API int Get_dev_capability(OUT snet_device_capability *device_capability);

HYPRIVATE_API WS_ERR general_get_local_connect_cfg(WS_USR_HAND hand, ws_local_connect_cfg *cfg);
HYPRIVATE_API WS_ERR general_get_usr_password_byname(const char *usr_name, WS_CHAR *password, size_t password_size);
HYPRIVATE_API const ws_device_capability* general_get_dev_capability();
HYPRIVATE_API WS_ERR general_remote_login(const WS_CHAR *usr_name, const char *password, const char *ip, const char *mac, WS_USR_HAND *hand);
HYPRIVATE_API WS_ERR general_auth_login_info(const WS_CHAR *usr_name, const char *password, const char *ip, const char *mac, WS_USR_HAND hand); /*hzg changed input param not use pointer 20170328 start end*/
HYPRIVATE_API WS_ERR general_remote_logout(WS_USR_HAND hand);

HYPRIVATE_API ws_rec_file_trig_type general_get_ch_rec_state(WS_U32 rec_ch);
HYPRIVATE_API WS_ERR general_get_dev_name(WS_USR_HAND hand, char *buf, size_t buf_size);
HYPRIVATE_API WS_ERR general_save_dev_name(WS_USR_HAND hand, const char *buf);
HYPRIVATE_API WS_ERR general_get_channel_name(WS_USR_HAND hand, WS_U32 ch, char *name_buf, size_t size);
HYPRIVATE_API WS_ERR general_set_channel_name_web(WS_USR_HAND hand, WS_U32 ch, const char *name_buf);
HYPRIVATE_API WS_ERR general_get_event_deployment_time(WS_USR_HAND hand ,ws_event_type type ,WS_U32 ch_idx,ws_channel_rec_schedule *schedule);
HYPRIVATE_API WS_ERR general_set_event_deployment_time(WS_USR_HAND hand ,ws_event_type type ,WS_U32 ch_idx,const ws_channel_rec_schedule *schedule);
HYPRIVATE_API WS_ERR general_get_record_mode(WS_USR_HAND hand, WS_U32 rec_ch, ws_soft::RECORD_MODE *curMode);
HYPRIVATE_API WS_ERR general_set_record_mode(WS_USR_HAND hand, WS_U32 rec_ch, ws_soft::RECORD_MODE curMode);
HYPRIVATE_API WS_ERR general_get_rec_schedule(WS_USR_HAND hand, WS_U32 nvr_ch, ws_rec_schedule_day day, ws_rec_schedule_per_day *schedule);
HYPRIVATE_API WS_ERR general_set_rec_schedule(WS_USR_HAND hand, WS_U32 nvr_ch, ws_rec_schedule_day day, const ws_rec_schedule_per_day *schedule);
HYPRIVATE_API WS_ERR general_ptz_cmd_control(WS_USR_HAND hand, WS_U32 rmt_ch, PTZ_CMD_ID cmd, WS_U32 para);
HYPRIVATE_API WS_ERR general_get_isp_info(WS_USR_HAND hand, WS_U32 rmt_ch, ws_isp_image *get_image, ws_isp_exposure *get_exposure);
HYPRIVATE_API WS_ERR general_set_isp_info(WS_USR_HAND hand, WS_U32 rmt_ch, ws_isp_type set_type, int set_val);
HYPRIVATE_API WS_ERR general_get_disk_work_ctl(WS_USR_HAND hand, ws_hard_disk_work_ctl *ctl);
HYPRIVATE_API WS_ERR general_set_disk_work_ctl(WS_USR_HAND hand, const ws_hard_disk_work_ctl *ctl);
HYPRIVATE_API WS_ERR general_set_usr_passwd(WS_USR_HAND hand, const char *login_password, const WS_CHAR *usr_name, const char *password);
HYPRIVATE_API WS_BOOL general_get_wifi_enable();
HYPRIVATE_API WS_ERR general_get_wifi_conn_status(WS_BOOL *status, char* ssid, char* mac);
HYPRIVATE_API WS_ERR general_get_wifi_ap_info(LPWLAN_CONNECTION ap_info);
HYPRIVATE_API WS_ERR general_get_wifi_ap_connect(WS_USR_HAND hand, ws_wifi_inquiry_result *result);
HYPRIVATE_API WS_ERR general_set_wifi_connect(WS_USR_HAND hand, const LPWLAN_CONNECTION connect);
HYPRIVATE_API WS_ERR general_get_wifi_ip_info(WS_USR_HAND hand, ws_local_connect_cfg *ip_info);
HYPRIVATE_API WS_ERR general_set_wifi_connect_mode(WS_USR_HAND hand, int mode);
HYPRIVATE_API WS_ERR general_set_wifi_enable(WS_USR_HAND hand, WS_BOOL is_enable);
HYPRIVATE_API WS_ERR general_set_wifi_ip_info(WS_USR_HAND hand, const ws_local_connect_cfg *ip_info);
HYPRIVATE_API WS_ERR general_set_wifi_ap_info(WS_USR_HAND hand, const LPWLAN_CONNECTION ap_info);

HYPRIVATE_API WS_ERR general_inquiry_rec_by_time(WS_USR_HAND hand,
        WS_U32 nvr_ch,
        const ws_time_struct *start_time,
        const ws_time_struct *stop_time,
        ws_rec_file_inquiry_type file_type,
        ws_rec_file_inquiry_result *result);

HYPRIVATE_API WS_ERR general_inquiry_snap_by_time(WS_USR_HAND hand,
	WS_U32 nvr_ch,
	const ws_time_struct * start_time,
	const ws_time_struct * stop_time,
	ws_snap_file_inquiry_type file_type,
	ws_snap_file_inquiry_result * result);      
HYPRIVATE_API WS_ERR general_free_inquiry_rec_result(WS_USR_HAND hand, const ws_rec_file_inquiry_result *result);
HYPRIVATE_API WS_ERR general_free_inquiry_snap_result(WS_USR_HAND hand, const ws_snap_file_inquiry_result *result);

//add by qqy,start at 2017-05-24 14:03:46
HYPRIVATE_API WS_ERR general_get_md_allalarm(WS_USR_HAND hand, WS_U32 rmt_ch, WS_U32* p_allalarm);
HYPRIVATE_API WS_ERR general_set_md_info(WS_USR_HAND hand, WS_U32 rmt_ch, const ws_md_arr *md_arr);
//add by qqy,end at 2017-05-24 14:03:48

/* hzg 20170411 Cmd control Private Protocol Server start stop  */
HYPRIVATE_API int VoiceStream_Create(DWORD dwUserId, DWORD dwChannel, eVoiceMode eMode);
HYPRIVATE_API int VoiceStream_Destroy(DWORD dwUserId, DWORD dwChannel);
HYPRIVATE_API int VoiceStream_Read(ws_frame_info *wsframe_info,char *pBuffer, DWORD dwBufLen);	/*cb change,2016-5-18 -- start*/
	
HYPRIVATE_API int set_local_ip(int a,void *msg);	
HYPRIVATE_API int general_get_live_stream_bitrate(int chan_idx, int stream_type);  /* hzg 20170914 added for TCP BWC */
}

HYPRIVATE_API int HYGetlocalinfo_UserActionIf( );

/* add begin by ronghl, 2017-12-20, 原因: 获取设备使能标志,目前没有实际代码，默认返回0xFFFFFFFFFF */
HYPRIVATE_API int Get_DeviceCapacityFlag(OUT DWORD * pCapacityFlag);
#endif

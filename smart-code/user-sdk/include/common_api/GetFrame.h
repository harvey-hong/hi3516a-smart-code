#ifndef GET_FRAME_H

#define GET_FRAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "HieServer_Common.h"

#if 0 //ndef _WS_IPC_
#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_common.h"
#include "ws_comm_av.h"
#include "ws_comm_data.h"
#include "ws_model_api.h"
#include "ws_utility_api.h"

#include "ws_model_api.h"
#include "ws_comm_data.h"
#include "ws_utility_api.h"  
using namespace ws_soft;
#else
#include "ws_history_api.h" 
#include "ws_recfile_rw_def.h"
#endif

#define IN        	/* 输入参数，仅传入参数值 */
#define OUT      	/* 输出参数，使用指针来保存函数的结果参数，实现传出参数值 */
#define IN_OUT  	/* 输入输出参数，通过该指针传入具体的参数值，也通过该指针保存函数的结果参数，实现传出参数值 */


#if defined( __cplusplus)
#define HYPRIVATE_API  extern "C" __attribute__((visibility("default")))
#else
#define HYPRIVATE_API  __attribute__((visibility("default")))
#endif

namespace GETFRAME
{
struct FrameInfo
{
	eStreamMediaType m_StreamType;
	unsigned int StreamMode;
	int last_node_idx;
	unsigned int iLastFrameNo;
	int iNeedIFrame;
	bool is_have_get;
	bool is_need_free;
		
	int iFrameType;		//!< 帧类型
	int frame_encode_type;	//!< 编码类型
	unsigned int tFrameTime;		//!< 帧时间
	unsigned int tFrameTimeUsec;	//!< 帧时间，单位微秒
	int iFrameLen;	//!< 帧长度
	unsigned int iFrameNo;	//!< 帧号
	unsigned int width;	//!< 帧的尺寸(宽)
	unsigned int height;	//!< 帧的尺寸(高)
	int magic;			//!< magic值
	int cur_node_idx;	//!< 节点编号
	int cur_m_node_idx;	//!< 主码流 节点编号
	int cur_s_node_idx;	//!< 子码流节点编号
	unsigned int frame_delta_time_ms;  //!< 保存当前帧与前一帧的时间差 > hzg 20170810  added start end
	unsigned int IFrameIdx;   /* I帧的序号,仅仅对一路流的I帧顺序编号 */
};

typedef struct
{
    int start_code;
    int file_id;
    unsigned short stream_type;
    unsigned char set_frame;
    int set_b;
    unsigned short wei;
    unsigned short hig;
} __attribute__((packed))head_info;


typedef struct data_head
{
    unsigned int  startcode;
    unsigned char fra_type;
    unsigned int fra_no;
    unsigned int show_time;
    unsigned char codec;
    unsigned int fra_len;
} __attribute__((packed))h_data;

#define NETSER_SYSHEAD_RESERVE  (80)
#define NETVOI_SYSHEAD_RESERVE  (76)

#define NETSER_SYSHEAD_LEN (sizeof(head_info)+NETSER_SYSHEAD_RESERVE)

#if 0 //ndef _WS_IPC_
typedef struct
{
    WS_U32              last_node_idx;
    WS_BOOL             is_have_send_sys;
    WS_BOOL             is_have_get;
    WS_BOOL             is_need_free;   //只有当获取后才会变成true，告知释放函数去进行释放
    ws_frame_info       cur_frame_info;
    ws_frame_info       last_frame_info;
    WS_UCHAR            sys_head[NETSER_SYSHEAD_LEN];
    WS_UCHAR            *frame_data;
} net_ser_usr_info;

typedef struct
{
    WS_BOOL             real_status;
    ws_venc_str_type  venc_str_type;//当前发送的码流类型
    net_ser_usr_info    main_usr_info;
    net_ser_usr_info    sub_usr_info;
} net_ser_cha_info;
#endif

#if 0 /* hzg 20190417 */
typedef struct
{
    /* 历史文件开始视频帧号与结束视频帧号*/
    unsigned int    iFileFirstFrameNo;     
    unsigned int    iFileLastFrameNo;
    /* 历史文件开始与结束视频的时间信息*/
    struct timeval  start_time;
    struct timeval  end_time;
    int                  iFileLen;                      /* 历史文件大小*/
}pb_file_info;
#endif

HYPRIVATE_API int RealStream_StartTaskId(OUT unsigned int *iTaskId, IN unsigned int iFrameMode);
HYPRIVATE_API int RealStream_GetOneFrame(IN unsigned int iTaskId, IN int rmt_ch, IN_OUT struct FrameInfo * frame_info, OUT char **frame_data);  
HYPRIVATE_API int RealStream_DelOneFrame(IN unsigned int iTaskId, IN int rmt_ch, struct FrameInfo * frame_info);
HYPRIVATE_API int RealStream_StopTaskId (IN unsigned int iTaskId);
HYPRIVATE_API int RealStream_GetSysHeader (IN unsigned int frame_width,IN unsigned int frame_height,OUT char **frame_data, OUT int *frame_len);
#if 0 /* hzg 20190417 */
HYPRIVATE_API int HisStream_NewTaskId(OUT unsigned int *iTaskId);
HYPRIVATE_API int HisStream_SetFile(IN unsigned int iTaskId , IN const char *file_name);
HYPRIVATE_API int HisStream_SetMode(IN unsigned int iTaskId , IN unsigned int Mode);
HYPRIVATE_API int HisStream_SetTime(IN unsigned int iTaskId , IN unsigned int time);
HYPRIVATE_API int HisStream_GetOneFrame(IN unsigned int iTaskId,  OUT char *buffer, IN int bufLen,OUT ws_frame_info *m_frame_info);
HYPRIVATE_API int HisStream_GetFileInfo(IN unsigned int iTaskId, OUT unsigned int * iFileFirstFrameNo, OUT unsigned int * iFileLastFrameNo, OUT struct timeval* start_time, OUT struct timeval* end_time, OUT int * iFileLen);
HYPRIVATE_API int HisStream_DelTaskId(IN unsigned int iTaskId);
HYPRIVATE_API int HisStream_GetPBFileInfo(IN const char *file_name, OUT pb_file_info *iFileInfo);

HYPRIVATE_API int VoiceStream_StartTaskId(OUT unsigned int *iTaskId);
HYPRIVATE_API int VoiceStream_StopTaskId(IN unsigned int iTaskId);
HYPRIVATE_API int VoiceStream_GetOneFrame(IN unsigned int iTaskId, OUT struct FrameInfo * frame_info, OUT char **frame_data);           /* change by linhh 20170612*/
HYPRIVATE_API int VoiceStream_DelOneFrame(IN unsigned int iTaskId, IN unsigned int last_node_idx);
HYPRIVATE_API int VoiceStream_AdpcmEncode(IN short inbuf[],OUT unsigned char outbuf[],IN int size);
#endif
}
#endif

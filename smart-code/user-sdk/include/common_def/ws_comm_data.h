#ifndef _WS_COMM_DATA_H_
#define _WS_COMM_DATA_H_

#include <sys/time.h>

#include "ws_common.h"
#include "ws_comm_sys.h"

#include "ws_comm_av.h"
#include "ws_comm_type.h"
#include "ws_status_def.h"  

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef enum
{
    CSC_MATRIX_IDENTITY = 0,
    CSC_MATRIX_BT601_TO_BT709,
    CSC_MATRIX_BT709_TO_BT601,
    CSC_MATRIX_BT601_TO_RGB_PC,
    CSC_MATRIX_BT709_TO_RGB_PC,
    CSC_MATRIX_BUTT,
} HI_CSC_MATRIX_E;

typedef struct
{
    HI_CSC_MATRIX_E enCscMatrix;
    WS_U32 u32Luma;         /* luminance: 0 ~ 100 default: 50 */
    WS_U32 u32Contrast;     /* contrast : 0 ~ 100 default: 50 */
    WS_U32 u32Hue;            /* hue : 0 ~ 100 default: 50 */
    WS_U32 u32Satuature;    /* satuature: 0 ~ 100 default: 50 */
    WS_U32 u32Gain;
} HI_VGA_PARAM_S;

typedef enum
{
    WS_IO_BLOCK_UNKONW,
    WS_IO_NO_BLOCK,
    WS_IO_BLOCK,
} ws_io_block_mode;

typedef enum
{
    WS_FRAME_ENCODE_TYPE_UNKNOW,
    //video
    WS_VIDEO_H264,
    WS_VIDEO_H264_A,
    WS_VIDEO_H265,//Add by qqy, at 2016-04-07 14:19:43
	
//audio
    WS_AUDIO_ADPCM_IMA = 0x9527,
    WS_AUDIO_G726,
    WS_AUDIO_G711_ALAW,
    WS_AUDIO_G711_ULAW,
    WS_AUDIO_G729,
    WS_AUDIO_G723_1,
    WS_AUDIO_MP3,
    WS_AUDIO_IMA,
    WS_AUDIO_DVI4,
    WS_AUDIO_AMR,
} ws_frame_encode_type;

typedef enum
{
    WS_FRAME_TYPE_UNKNOW,
    WS_VIDEO_FRAME_I,
    WS_VIDEO_FRAME_P,
    WS_AUDIO_FRAME = 0x9527,
} ws_frame_type;

typedef struct
{
    ws_frame_type frame_type;         //֡����
    ws_frame_encode_type encode_type; //��������
    WS_U32 frame_no;                  //֡��
    struct timeval frame_time;        //����ʱ���

    //�ߴ�(��Ƶ������Ч��Ϊ0)
    WS_U32 frame_width;
    WS_U32 frame_height;
    WS_U32 frame_len;   //֡����

    //�޸�ϵͳʱ��֮��magic��仯��recģ�������ж������Ƿ���Ч������ģ������طš����ݽ������ݵ�ʱ�������Ч
    WS_U32 magic;

    WS_U32 frame_delta_time_ms;  /* hzg 20170810 ���Ӳ������浱ǰ֡��ǰһ֡��ʱ��� start end */
    WS_U32 IFrame_Idx;          /* һ·����I֡�����TCP�ʹ��������Ҫ�õ� */
} ws_frame_info;

typedef struct
{
    WS_U32 pciv_stream_magic;
    WS_U32 dvr_ch;
    ws_venc_str_type stream_type;
    WS_U32 dma_length;
}ws_frame_info_ex;

typedef struct
{
    WS_U32 dvr_ch;
    WS_U32 frame_length;
    time_t frame_time;
    WS_U32 not_used[4];
}ws_snap_pic_info;

typedef struct
{
    WS_U32 dvr_ch;
    WS_U32 total_ch_mask;
    WS_U32  snap_ok_ch_mask;
    WS_U32   snap_fail_ch_mask;
    WS_U32 frame_length;
    time_t 	  frame_time;	
    WS_U32 not_used[4];
}ws_snap_pic_info_by_mask;

typedef enum
{
    WS_FRAME_PARSER_UNKNOW,
    WS_FRAME_PARSER_NEW,    //�µ�һ֡��ʼ
    WS_FRAME_PARSER_EXTEND_LAST,    //�����ϴ�δ���
} ws_frame_parser_type;

typedef struct
{
    ws_frame_type frame_type;         //֡����
    ws_frame_encode_type encode_type; //��������
    WS_U32 frame_no;                  //֡��
    struct timeval frame_time;      //����ʱ���

    //�ߴ�(��Ƶ������Ч��Ϊ0)
    WS_U32 frame_width;
    WS_U32 frame_height;
    WS_U32 frame_len;   //֡���ܳ���

    ws_frame_parser_type parser_type;
    WS_U32 cur_rd_len;      //���ζ�ȡ��֡��Ч���ݵĳ���
    WS_U32 remain_len;      //��֡��Ч���ݵ�ʣ�೤��
} ws_parser_frame;

typedef struct snap_task_node_t
{
    WS_U32 channel_index;
    ws_utility::ws_snap_file_trig_type trig_type;
    time_t		event_time; //�豸�˲���������ʱ��
    char file_name[ws_utility::WS_MAX_FILE_NAME_LEN];//����·����
    struct timeval task_get_time;//���յ������ʱ��
    WS_BOOL bRepeat; //add by qqy, at 2017-05-10 09:12:27
    struct snap_task_node_t *next;//ʹ��˫�������Լ����ʱ��
    struct snap_task_node_t *pre;
} snap_task_node_t;

typedef struct ws_snap_mask_task_node
{
    WS_U32 ch_mask[ws_utility::WS_NVR_MAX_MASK_NUM];
    WS_U32 re_snap_ch_mask[ws_utility::WS_NVR_MAX_MASK_NUM];
    ws_utility::ws_snap_file_trig_type trig_type;
    time_t		event_time[ws_utility::WS_NVR_MAX_CH_NUM]; //�豸�˲����¼���ʱ��//add by qqy, at 2016-08-31 10:16:11
    struct ws_snap_mask_task_node *next;//ʹ��˫�������Լ����ʱ��
    struct ws_snap_mask_task_node *pre;
} ws_snap_mask_task_node;

typedef struct send_email_task_node_t
{
	WS_U32 channel_index;
	WS_U32 check_count;//��ѯ���ݿ�ʧ�ܵĴ���
	time_t send_email_time;
	ws_soft::ws_event_type task_event_type;
	struct timeval task_get_time;
	struct send_email_task_node_t *next;
	struct send_email_task_node_t *pre;
}send_email_task_node_t;

typedef struct tag_recfile_requiry_snap_need_s
{
    WS_U32 channel_index;
    ws_time_struct send_email_time_start;
    ws_time_struct send_email_time_end;
}recfile_requiry_snap_need_s;

//����ֵ����Ϊ�̶��ֱ��� 704*576����Լ��������ֵ
typedef struct
{
    int x;
    int y;
    int w;
    int h;
} ws_md_rect;

typedef struct
{
    ws_md_rect md_rect[5];
    ws_md_sensitivity md_sen;

    int set_count;//�����Ǹ�֪ һ���м���
    int get_real_count;//��ȡmd����ʱ�� ipc�˸�֪�ľ������
} ws_md_arr;

//for rec file info
typedef struct
{
	struct timeval start_time;
	struct timeval end_time;
	WS_U32 file_size;
	WS_U32 video_width;
	WS_U32 video_height;
	WS_U32 first_frame_no;	
	WS_U32 last_frame_no;	
}ws_rec_file_info; 

typedef struct
{
    unsigned int head_start;
    unsigned char frame_type;
    unsigned int  num;
    unsigned int  n_time;
    unsigned char code;
    unsigned int  length;
} __attribute__((packed))hy_private_audio_head;

typedef struct
{
    unsigned int head_start;
    unsigned char frame_type;
    unsigned int  num;
    unsigned int  n_time;
    unsigned char code;
    unsigned int  length;
    unsigned int  s_time;
} __attribute__((packed))hy_private_video_head;

typedef struct
{
    unsigned int head_start;
    unsigned char frame_type;
    unsigned int  num;
    unsigned int  n_time;
    unsigned char code;
    unsigned int  length;
    short         dwWidth ;
    short         dwHeight;
} __attribute__((packed))hy_private_video_headEx;

/* �ļ�ͷ��Ϣ 19 bytes */
typedef struct tagMP4NewFileHeader
{
    int FileStartCode;           /* 4Bytes */
    int FileID;                      /* 4Bytes */
    short StreamType;         /* 2Bytes */
    char SetFrameRate;       /* 1Bytes */
    int SetBPS;                    /* 4Bytes */
    short   dwImageWidth;   /* 2Bytes */
    short   dwImageHight;    /* 2Bytes */
}__attribute__((packed)) MPEG4FILEHEADER;

/*��Ƶ֡ͷ��Ϣ22 bytes */
typedef struct tagDecoderFrameHeader
{
    unsigned int    dwDataPacketStartCode;   /* 4Bytes */
    unsigned char        bytFrameType;                   /* 1Bytes */
    unsigned int       dwFrameNo;                       /* 4Bytes */
    unsigned int    dwShowTime;                     /* 4Bytes */
    unsigned char  bytCodecType;                    /* 1Bytes */
    unsigned int    lDataLen;                            /* 4Bytes */
} __attribute__((packed)) DecoderFrameHeader, *PDecoderFrameHeader;


#if 1
// add by linhh 20160429 start - end 
/*��Ƶ֡ͷ��Ϣ22 bytes */
typedef struct tagDecoderFrameHeaderEx
{
    int    dwDataPacketStartCode;   /* 4Bytes */
    char  bytFrameType;                   /* 1Bytes */
    int    dwFrameNo;                       /* 4Bytes */
    int    dwShowTime;                     /* 4Bytes */
    char  bytCodecType;                    /* 1Bytes */
    int    lDataLen;                            /* 4Bytes */
    short dwWidth;                           /* 2Bytes */
    short dwHeight;                          /* 2Bytes */
} __attribute__((packed)) DecoderFrameHeaderEx, *PDecoderFrameHeaderEx;
#endif


//Add By ZhnagXinda Date:2014-08-28
typedef enum
{
    WS_SNAP_TYPE_UNKNOW = 0,
    WS_SNAP_FOR_STORE,
    WS_SNAP_FOR_CACHE,
    WS_SNAP_FOR_BOTH
}ws_snap_type;
//End By ZhangXinda Date:2014-08-28


typedef enum tagREMOTE_COMMAND
{
    WS_REMOTE_COMMAND_START,
    WS_REMOTE_COMMAND_GET_MAIN_ENC_PARAM,
    WS_REMOTE_COMMAND_GET_SUB1_ENC_PARAM,
    WS_REMOTE_COMMAND_GET_ALL_ENC_PARAM,
    WS_REMOTE_COMMAND_SET_MAIN_ENC_PARAM,
    WS_REMOTE_COMMAND_SET_SUB1_ENC_PARAM,
    WS_REMOTE_COMMAND_SET_ALL_ENC_PARAM,
    WS_REMOTE_COMMAND_SYNC_TIME,
    WS_REMOTE_COMMAND_GET_MOTION_PARAM,
    WS_REMOTE_COMMAND_SET_MOTION_PARAM,
 //add by qqy,start at 2016-07-12 17:11:34
    WS_REMOTE_COMMAND_SET_DEFAULT_ISP_PARAM,
    WS_REMOTE_COMMAND_SET_DEFAULT_EXPOSURE_PARAM,
 //add by qqy,end at 2016-07-12 17:11:36
    WS_REMOTE_COMMAND_END,        
}REMOTE_COMMAND;


typedef struct tagCMD_REMOTE
{
    WS_U32                          rmt_ch;
    REMOTE_COMMAND           rmt_cmd;
    struct tagCMD_REMOTE    *next;
}CMD_REMOTE, *pCMD_REMOTE;


typedef enum eStreamSpeed
{
	eStreamSpeedBegin		=0,	
	eStreamSpeedOneFifthIFrame,		/*!<���ĸ�I֡��һ��I֡*/
	eStreamSpeedQuarterIFrame,		/*!<������I֡��һ��I֡*/
	eStreamSpeedOneThirdIFrame,	/*!<������I֡��һ��I֡*/
	eStreamSpeedHalfIFrame,			/*!<��һ��I֡��һ��I֡*/
	eStreamSpeedIFrame,			/*!<ֻ��I֡ */
	eStreamSpeedIPFrame,			/*!<I֡P֡����*/
	eStreamSpeedEnd,
}STREAM_SPEED;
// add by linhh 20161008 end --

//liujl change start-end at 20170828, Synchronous branch SVN998 code
/* ¼���ļ����صı��� */
typedef enum eDownLoadFileSpeed
{
        eRecDownloadBeginSpeed = 0,
        eRecDownloadx16Speed,                  /* IP֡ȫ������,16���� */
        eRecDownloadx8Speed,                    /* IP֡ȫ������,8���� */
        eRecDownloadx4Speed,                    /* IP֡ȫ������,4���� */
        eRecDownloadx2Speed,                    /* IP֡ȫ������,2���� */
        eRecDownloadIPSpeed,                    /* IP֡ȫ������,�������� */
        eRecDownloadx1_2Speed,               /* IP֡ȫ������,1/2���� */
        eRecDownloadEndSpeed,
}DOWNLOADFILESPEED;

typedef enum eRecordMode
{
    eRecord_Mode_CLOSE = 0 ,            /* �ر�¼��*/
    eRecord_Mode_TIME,                     /* ��ʱ¼��ģʽ*/
    eRecord_Mode_ALARM,                  /* ����¼��ģʽ */
    eRecord_Mode_MANUAL,                /* �ֶ�¼��ģʽ*/
    eRecord_Mode_AUTO,                    /* �Զ�¼��ģʽ*/
    eRecord_Mode_END,
}RECORD_MODE;

/* sync by bandwidth */
/*!
*  @enum    eMediaStreamType
*  @brief   ��ý�����Ͷ���
*/
typedef enum tag_eMediaStreamType
{
    eMediaStreamTypeBegin                       = 0,                        //!< ��ʼֵ
    eMediaStreamReal,                                                   //!< ʵʱ��
    eMediaStreamVoice,                                                  //!< ������
    eMediaStreamHistory,                                                //!< ��ʷ��
    eMediaStreamHistoryQuery,                                           //!< ��ʷ��ѯ
    eMediaStreamLogQuery,                                               //!< ��־��ѯ
    eMediaFileUpload,                                                   //!< �ļ��ϴ�
    eMediaFileDownload,                                                 //!< �ļ�����
    eMediaTransparentChannel,                                           //!< ͸��ͨ��
    eMediaHistoryQuery,                                                 //!< ��ʷ��ѯ
    eMediaStreamTransfer,                                               //!< ��ת��
    eMediaLogoUpload,                                                   //!< Logo�ϴ�
    eMediaNewHisStream = 30,                                            //����ʷ��(���ڿͻ��˺ͷ��������м��в��ֻ�ܸ���̶�ֵ)
    eMediaStreamTypeEnd,                                                //!< ����ֵ
}eMediaStreamType;
 
#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_COMM_AV_H_


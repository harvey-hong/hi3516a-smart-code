#include "./GetFrame.h"
#include "ws_comm_data.h"

using namespace GETFRAME;
using namespace ws_soft ;

#if 0 //ndef hzg20190417 _WS_IPC_
#include "ws_comm_debug.h"
#include "ws_model_api.h"
#else
extern "C" int H264Node_NewTaskId(unsigned int *iTaskId, unsigned int iFrameMode);
extern "C" int H264Node_DelTaskId(unsigned int iTaskId);
/* hzg 20170810 获取帧接口增加参数返回了当前帧与前一帧的时间差 */
 /* hzg 20180312 获取帧链表中专门针对I帧编号的序号值 */
extern "C" int H264Node_GetOneFrameEx(unsigned int iTaskId, int *iFrameType, unsigned int *tFrameTime, unsigned int *tFrameTimeUsec, char **pFramePointer, int *iFrameLen, unsigned int *iFrameNo, unsigned int *width,unsigned int *height,unsigned int *last_node_idx, unsigned int *frame_delta_time_ms, unsigned int *IFrame_Idx);
extern "C" int H264Node_ReleaseOneFrameEx(unsigned int iTaskId, unsigned int iFrameNo, unsigned int node_idx);
#if 0 /*hzg 20190417 */
extern "C" int AUDIONode_NewTaskId(unsigned int *iTaskId);
extern "C" int AUDIO_DelTaskId(unsigned int iTaskId);
extern "C" int AUDIONode_GetOneFrameEx(unsigned int iTaskId, int *iFrameType, unsigned int *tFrameTime, unsigned int *tFrameTimeUsec, char **pFramePointer, unsigned int *iFrameLen, unsigned int *iFrameNo, char **pNodeP,unsigned int *last_node_idx);
extern "C" int AUDIONode_ReleaseOneFrameEx(unsigned int iTaskId, unsigned int last_node_idx);       /* change by linhh 20170612 */
extern "C" int AUDIO_AdpcmEncode(short inbuf[],unsigned char outbuf[],int size);
#endif
#endif

/* change by linhh 20170531 */
HYPRIVATE_API int GETFRAME::RealStream_StartTaskId(OUT unsigned int *iTaskId, IN unsigned int iFrameMode)
{
#if 0 //ndef hzg20190417 _WS_IPC_
    return 0;
#else
    return H264Node_NewTaskId(iTaskId, iFrameMode);
#endif
}

/* change by linhh 20170621 : DVR 也输出保护帧首部的地址, 调用者根据首部类型获取帧类型与偏移判断*/
HYPRIVATE_API int GETFRAME::RealStream_GetOneFrame(IN unsigned int iTaskId, IN int rmt_ch, IN_OUT struct FrameInfo * frame_info, OUT char **frame_data)
{
#if 0 //ndef hzg20190417 _WS_IPC_
    ws_venc_str_type        type = WS_ENC_STR_UNKNOW;
    switch( frame_info->m_StreamType )
    {
        case eMainVideoAndSound :
        case eMainVideo :
        case eMainSound :
            type = WS_ENC_STR_MAIN;
            break;

        default:
            type = WS_ENC_STR_SUB1;
            break;
    }

    if (frame_info->is_need_free == true)
        return -1;

    net_ser_usr_info info;
    if (frame_info->is_have_get == false)
    {
        if ((model_first_get_video_stream(rmt_ch, WS_MODULE_ID_NET_SERVER, type, &info.cur_frame_info, &info.frame_data, (WS_U32*)&frame_info->cur_node_idx)) == WS_SUCCESS)
        {
            frame_info->is_have_get = true;
            frame_info->last_node_idx = frame_info->cur_node_idx;
            frame_info->is_need_free = true;
            frame_info->magic = info.cur_frame_info.magic;      
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if ((model_get_video_stream(rmt_ch, WS_MODULE_ID_NET_SERVER, type, &info.cur_frame_info, &info.frame_data, frame_info->last_node_idx, (WS_U32*)&frame_info->cur_node_idx)) == WS_SUCCESS)
        {
            frame_info->last_node_idx = frame_info->cur_node_idx;
            frame_info->is_need_free = true;
            frame_info->magic = info.cur_frame_info.magic;            
        }
        else
        {
            return -1;
        }
    }

    frame_info->tFrameTime = info.cur_frame_info.frame_time.tv_sec;
    frame_info->tFrameTimeUsec = info.cur_frame_info.frame_time.tv_usec;
    frame_info->width = info.cur_frame_info.frame_width;
    frame_info->height = info.cur_frame_info.frame_height;
    frame_info->iFrameNo = info.cur_frame_info.frame_no;
    frame_info->iFrameType = info.cur_frame_info.frame_type;
    frame_info->iFrameLen = info.cur_frame_info.frame_len;
    frame_info->frame_delta_time_ms = info.cur_frame_info.frame_delta_time_ms;   /* hzg 20170810 返回当前帧与前一帧的时间差 */
    frame_info->IFrameIdx = info.cur_frame_info.IFrame_Idx;  /* hzg 20170815  提供I帧在这一路流中的序号 start end */
    (*frame_data) = (char*)info.frame_data;

    /* change by linhh 20170621 : 调整输出的指针位置，视频帧偏移22 字节，音频帧偏移18字节*/
    if (type == WS_ENC_STR_MAIN)
    {
        switch( frame_info->iFrameType )
        {
            case eFrameIFrames :
            case eFramePFrames :
                frame_info->iFrameLen = frame_info->iFrameLen + sizeof(hy_private_video_headEx);
                *frame_data = (char*)info.frame_data - sizeof(hy_private_video_headEx) ;
                break;
            case eFrameAudioFrames :
                frame_info->iFrameLen = frame_info->iFrameLen + sizeof(hy_private_audio_head);
                *frame_data = (char*)info.frame_data - sizeof(hy_private_audio_head) ;
                break;
            case eFrameSysHeader :
            default :
                break;
        }
    }
    else if (type == WS_ENC_STR_SUB1)
    {
        switch( frame_info->iFrameType )
        {
            case eFrameIFrames :
                frame_info->iFrameType = eFrameQCIFIFrames;
                frame_info->iFrameLen = frame_info->iFrameLen + sizeof(hy_private_video_headEx);
                *frame_data = (char*)info.frame_data - sizeof(hy_private_video_headEx) ;
                break;

            case eFrameQCIFIFrames :
                frame_info->iFrameLen = frame_info->iFrameLen + sizeof(hy_private_video_headEx);
                *frame_data = (char*)info.frame_data - sizeof(hy_private_video_headEx) ;
                break;
                
            case eFramePFrames :
                frame_info->iFrameType  = eFrameQCIFPFrames;
                frame_info->iFrameLen = frame_info->iFrameLen + sizeof(hy_private_video_headEx);
                *frame_data = (char*)info.frame_data - sizeof(hy_private_video_headEx) ;
                break;

            case eFrameQCIFPFrames :
                frame_info->iFrameLen = frame_info->iFrameLen + sizeof(hy_private_video_headEx);
                *frame_data = (char*)info.frame_data - sizeof(hy_private_video_headEx) ;
                break;
                
            case eFrameAudioFrames :
                frame_info->iFrameLen = frame_info->iFrameLen + sizeof(hy_private_audio_head);
                *frame_data = (char*)info.frame_data - sizeof(hy_private_audio_head) ;
                break;

            case eFrameSysHeader :
                frame_info->iFrameType  = eFramePktSysHeaderAux;                
                break;
                
            default :
                break;
        }
    }
    return 0;
#else
    if( 0xFFFF != iTaskId )
    {  
        /* hzg 20170810 返回当前帧与前一帧的时间差 */
         /* hzg 20180312 获取帧链表中专门针对I帧编号的序号值 */
        return H264Node_GetOneFrameEx(iTaskId, &(frame_info->iFrameType), &(frame_info->tFrameTime), &(frame_info->tFrameTimeUsec), (char**)frame_data, &(frame_info->iFrameLen), &(frame_info->iFrameNo), &(frame_info->width),&(frame_info->height),(unsigned int *)&frame_info->cur_node_idx, &frame_info->frame_delta_time_ms, &frame_info->IFrameIdx);
    }
    return -1 ;            
#endif
}

/* change by linhh 20170615 : 删除不需要的形参*/
HYPRIVATE_API int GETFRAME::RealStream_DelOneFrame(IN unsigned int iTaskId, IN int rmt_ch, struct FrameInfo *frame_info)
{
#if 0 //ndef hzg20190417 _WS_IPC_
    ws_venc_str_type        type = WS_ENC_STR_UNKNOW ;
#if 1
    switch( frame_info->m_StreamType )
    {
        case eMainVideoAndSound :
        case eMainVideo :
        case eMainSound :
            type = WS_ENC_STR_MAIN;
            break;

        default:
            type = WS_ENC_STR_SUB1;
            break;
    }
#else
    if (eMainVideoAndSound == frame_info->m_StreamType)
    {
        type = WS_ENC_STR_MAIN;
    }
    else if (eAssistVideo == frame_info->m_StreamType)
    {
        type = WS_ENC_STR_SUB1;
    }
#endif
    if (frame_info->is_need_free != true)
    {
        return -1;
    }

    WS_ERR ret = model_del_video_stream(rmt_ch, WS_MODULE_ID_NET_SERVER, type, frame_info->last_node_idx);
    if (ret != WS_SUCCESS)
        return -1;

    frame_info->is_need_free = false;
    return 0;
#else
    if( 0xFFFF != iTaskId )
        return H264Node_ReleaseOneFrameEx(iTaskId, frame_info->iFrameNo, frame_info->cur_node_idx);

    return -1 ;
#endif
}

HYPRIVATE_API int GETFRAME::RealStream_StopTaskId (IN unsigned int iTaskId)
{
#if 0 //ndef hzg20190417 _WS_IPC_
    return 0;
#else
    return H264Node_DelTaskId(iTaskId);
#endif
}

/* 根据宽度与高度信息产生文件首部结构*/
HYPRIVATE_API int GETFRAME::RealStream_GetSysHeader (IN unsigned int frame_width,IN unsigned int frame_height, OUT char **frame_data, OUT int *frame_len)
{
    head_info *tmp = (head_info *)((*frame_data) + NETSER_SYSHEAD_RESERVE);
    tmp->start_code = 0xC6010000 ;
    tmp->file_id = 0x3447504D;
    tmp->stream_type = 1;   
    tmp->set_frame = 30;
    tmp->set_b = 1024 * 4;
    tmp->wei = frame_width;
    tmp->hig = frame_height;
    *frame_len = sizeof(head_info);;
    return 0;
}

#if 0 /* hzg 20190417 */
HYPRIVATE_API int GETFRAME::HisStream_NewTaskId(OUT unsigned int *iTaskId)
{
#if 0 //ndef hzg20190417 _WS_IPC_
    return model_Pb_NewTaskId(iTaskId);
#else 
    return model_HisStream_NewTaskId(iTaskId);
#endif
}
 
HYPRIVATE_API int GETFRAME::HisStream_SetFile(IN unsigned int iTaskId , IN const char *file_name)
{
#if 0 //ndef hzg20190417 _WS_IPC_
	return model_Pb_SetFile(iTaskId , file_name);	
#else
	return model_HisStream_SetFile(iTaskId , file_name);
#endif
}

HYPRIVATE_API int GETFRAME::HisStream_SetMode(IN unsigned int iTaskId , IN unsigned int Mode)
{
#if 0 //ndef hzg20190417 _WS_IPC_
	return model_Pb_SetMode(iTaskId , Mode);	
#else 
	return model_HisStream_SetMode(iTaskId , Mode);
#endif
}

HYPRIVATE_API int GETFRAME::HisStream_SetTime(IN unsigned int iTaskId , IN unsigned int time)
{
#if 0 //ndef hzg20190417 _WS_IPC_
	return model_Pb_SetTime(iTaskId , time);
#else
	return model_HisStream_SetTime(iTaskId , time);
#endif
}

HYPRIVATE_API int GETFRAME::HisStream_GetOneFrame(IN unsigned int iTaskId,  OUT char *buffer, IN int bufLen,OUT ws_frame_info *m_frame_info)
{
#if 0 //ndef hzg20190417 _WS_IPC_
    return model_Pb_GetOneFrame(iTaskId, buffer, bufLen,(ws_frame_info*)m_frame_info);
#else
    return model_HisStream_GetOneFrame(iTaskId, buffer, bufLen,(ws_frame_info*)m_frame_info);
#endif
}

HYPRIVATE_API int GETFRAME::HisStream_GetFileInfo(IN unsigned int iTaskId, OUT unsigned int * iFileFirstFrameNo, OUT unsigned int * iFileLastFrameNo, OUT struct timeval* start_time, OUT struct timeval* end_time, OUT int * iFileLen)
{
#if 0 //ndef hzg20190417 _WS_IPC_
	return model_Pb_GetFileInfo(iTaskId, iFileFirstFrameNo, iFileLastFrameNo, start_time, end_time, iFileLen);
#else
	return model_HisStream_GetFileInfo(iTaskId, iFileFirstFrameNo, iFileLastFrameNo, start_time, end_time, iFileLen);
#endif
}

HYPRIVATE_API int GETFRAME::HisStream_GetPBFileInfo(IN const char *file_name, OUT pb_file_info *iFileInfo)
{
    unsigned int        iTaskId ;
#if 0 //ndef hzg20190417 _WS_IPC_
    if( WS_SUCCESS != model_Pb_NewTaskId(&iTaskId) )
        return -1 ;

    if( WS_SUCCESS != model_Pb_SetFile(iTaskId, file_name) )
    {
        model_Pb_DelTaskId(iTaskId);
        return -1 ;
    }

    if( WS_SUCCESS != model_Pb_GetFileInfo(iTaskId, &iFileInfo->iFileFirstFrameNo, &iFileInfo->iFileLastFrameNo, &iFileInfo->start_time, &iFileInfo->end_time, &iFileInfo->iFileLen) )
    {
        model_Pb_DelTaskId(iTaskId);
        return -1 ;
    }
    model_Pb_DelTaskId(iTaskId);
    
#else 
    if( 0 != model_HisStream_NewTaskId(&iTaskId) )
        return -1 ;
    
    if( 0 != model_HisStream_SetFile(iTaskId , file_name) )
    {
        model_HisStream_DelTaskId(iTaskId);
        return -1 ;
    }

    if( 0 != model_HisStream_GetFileInfo(iTaskId, &iFileInfo->iFileFirstFrameNo, &iFileInfo->iFileLastFrameNo, &iFileInfo->start_time, &iFileInfo->end_time, &iFileInfo->iFileLen) )
    {
        model_HisStream_DelTaskId(iTaskId);
        return -1 ;
    }

    model_HisStream_DelTaskId(iTaskId);
#endif
    return 0 ;    
}

HYPRIVATE_API int GETFRAME::HisStream_DelTaskId(IN unsigned int iTaskId)
{
#if 0 //ndef hzg20190417 _WS_IPC_
	return model_Pb_DelTaskId(iTaskId);
#else
	return model_HisStream_DelTaskId(iTaskId);
#endif
}

HYPRIVATE_API int GETFRAME::VoiceStream_StartTaskId(OUT unsigned int *iTaskId)
{
#if 0 //ndef hzg20190417 _WS_IPC_
    WS_ERR ret = model_start_talking();
    if (ret != WS_SUCCESS)
        return -1;
    return 0;
#else
    return AUDIONode_NewTaskId(iTaskId);
#endif
}
 
HYPRIVATE_API int GETFRAME::VoiceStream_StopTaskId(IN unsigned int iTaskId)
{
#if 0 //ndef hzg20190417 _WS_IPC_
	WS_ERR ret = model_stop_talking();
	 if (ret != WS_SUCCESS)
	 	return -1;
	 return 0;
#else
	return AUDIO_DelTaskId(iTaskId);
#endif
}

/* change by linhh 20170612 : 合并DVR 与IPC 在音频获取上控制，由上层分配空间，GetFrame模块中获取音频数据后做拷贝*/
HYPRIVATE_API int GETFRAME::VoiceStream_GetOneFrame(IN unsigned int iTaskId, OUT struct FrameInfo *frame_info, OUT char **frame_data) 
{
#if 0 //ndef hzg20190417 _WS_IPC_
    WS_USR_HAND         hand = -1;
    ws_frame_info          m_speak_info;
    WS_ERR  ret = model_get_talking_frame(hand, &m_speak_info, *frame_data + NETVOI_SYSHEAD_RESERVE, frame_info->iFrameLen - NETVOI_SYSHEAD_RESERVE);
    if (ret != WS_SUCCESS)
        return ret;

    frame_info->iFrameLen = m_speak_info.frame_len;
    frame_info->iFrameNo = m_speak_info.frame_no;
    frame_info->iFrameType = 0X0008;
    frame_info->m_StreamType = eMainSound;
    struct timeval      TimeNow;
    gettimeofday(&TimeNow, NULL);
    frame_info->tFrameTime = TimeNow.tv_sec;
    frame_info->tFrameTimeUsec = TimeNow.tv_usec;
    return 0;
#else
    char        *pFrameRelease = NULL;
    char        *pFramePointer = NULL;
    if( 0 != AUDIONode_GetOneFrameEx(iTaskId,&(frame_info->iFrameType),&(frame_info->tFrameTime), &(frame_info->tFrameTimeUsec),(char**)&pFramePointer,(unsigned int*)&(frame_info->iFrameLen),&(frame_info->iFrameNo),(char**)&pFrameRelease,(unsigned int*)&(frame_info->cur_node_idx)) )
        return -1 ;

    pFrameRelease = *frame_data + NETVOI_SYSHEAD_RESERVE ;
    memcpy(pFrameRelease, pFramePointer, frame_info->iFrameLen);
    return 0 ;
#endif
}

/* change by linhh 20170612 */
HYPRIVATE_API int GETFRAME::VoiceStream_DelOneFrame(IN unsigned int iTaskId, IN unsigned int last_node_idx)
{
#if 0 //ndef hzg20190417 _WS_IPC_
	return 0;
#else
	return AUDIONode_ReleaseOneFrameEx(iTaskId,last_node_idx);
#endif
}

HYPRIVATE_API int GETFRAME::VoiceStream_AdpcmEncode(IN short inbuf[],OUT unsigned char outbuf[],IN int size)
{
#if 0 //ndef hzg20190417 _WS_IPC_
	return 0;
#else
	return AUDIO_AdpcmEncode(inbuf, outbuf, size);
#endif
}
#endif

#include "../inc/RealStreamSender.h"
#include "../inc/Property.h"
#include "../inc/Utility.h"
#include "../inc/RealStream.h"

#include "ws_utility_api.h"
using namespace ws_utility;

using namespace GETFRAME;  

static void realsender_rsleep(unsigned int ntime)
{
    fd_set          rfds;
    struct timeval  tv;
    int             retval;                 /* Watch stdin  (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);               /* Wait up to five seconds. */
    tv.tv_sec   = ntime / 1000000;
    tv.tv_usec  = ntime % 1000000;
    retval = select(0, &rfds, NULL, NULL, &tv); /* Don't rely on the value of tv now! */
}

namespace   ApplicationLayer
{

CRealStreamSender::CRealStreamSender()
{
    Initialize();
}

CRealStreamSender::~CRealStreamSender()
{
    Destory();
}

// 通过TThread模板启动实时流发送器
int CRealStreamSender::Start(CRealStream *pSession, eMediaCodeType m_eCurCodeType)
{
    m_pSession = pSession;

    if (RET_CHECK_FAIL(m_cMutex.create()))
    {
        return RET_FAIL;
    }

    m_cMutex.lock();

    if (RET_CHECK_FAIL(m_cSendSignal.create()))
    {
        m_cMutex.unlock();
        m_cMutex.destroy();
        return RET_FAIL;
    }

    if (m_eCurCodeType == eMediaCodeMain)
    {
        m_stream_type = WS_ENC_STR_MAIN;
        pSession->GetChannel(m_channel_id);
        RealStream_StartTaskId(&m_iTaskId,0);
    }
    else
    {
        m_stream_type = WS_ENC_STR_SUB1;
        pSession->GetChannel(m_channel_id);
        RealStream_StartTaskId(&m_iTaskId,1);
    }

    m_dwState       = eTaskStatusStart;
    m_channel_id = m_channel_id - 1;

    if (RET_CHECK_FAIL(m_cSendThread.Start(this)))
    {
        m_cSendSignal.destroy();
        m_cMutex.unlock();
        m_cMutex.destroy();
        return RET_FAIL;
    }

    m_cMutex.unlock();
    return RET_SUCCESS;
}

//恢复实时流发送
int CRealStreamSender::Resume()
{
    m_dwState = eTaskStatusStart;
    return RET_SUCCESS;
}

//暂停实时流发送
int CRealStreamSender::Suspend()
{
    m_dwState = eTaskStatusStop;
    return RET_SUCCESS;
}

//停止实时流发送器
int CRealStreamSender::Stop()
{
    m_dwState = eTaskStatusStop;
    m_cSendSignal.signal();
    m_cSendThread.Stop();
    m_cMutex.lock();
    m_cSendSignal.destroy();
    m_pSession = NULL;
    if( m_iTaskId != 0xFFFF )
    {
        RealStream_StopTaskId(m_iTaskId);
    }
    RTSP_SER_PD("[CRealStreamSender::Stop()]停止发送\n"); 
    m_cMutex.unlock();
    m_cMutex.destroy();
    return RET_SUCCESS;
}

int CRealStreamSender::Send(CMediaPacketRealStreamDepict &depict, LPBuffer stream)
{
    if (eTaskStatusStart != m_dwState)
    {
        return RET_FAIL;
    }

    CGuard  guard(&m_cMutex);
    if (eTaskStatusStart != m_dwState)
    {
        return RET_FAIL;
    }

    if (CHECK_POINT_NULL(m_pSession))
    {
        return RET_FAIL;
    }

    m_cSendSignal.signal();
    return RET_SUCCESS;
}

// 实现数据发送
int CRealStreamSender::RunTaskSendData(char *pFramePointer , DWORD iFrameLen, ApplicationLayer::CRealStream *m_pSession)
{
    Buffer              cBuffer;
    cBuffer.pBuffer     = (BYTE *)pFramePointer;
    cBuffer.dwBufLen    = iFrameLen;
    m_pSession->Send(&cBuffer);
    return 0 ;
}

int CRealStreamSender::RunTask()
{
    DWORD           dwSendSerial = 10;
    int             nRet , iFrameType;
    unsigned int        tFrameTime , tFrameTimeUsec ;
    char           *pFramePointer ;
    int             iFrameLen ;
    int             nCnt = 0 ;
    int             ii , iNeedIFrame = 1;
    unsigned int        iLastFrameNo;
    struct FrameInfo  cur_frame_info;
    memset(&cur_frame_info,0,sizeof(cur_frame_info));
    cur_frame_info.is_need_free = false;
    cur_frame_info.is_have_get = false;
    if((ws_soft::ws_venc_str_type)m_stream_type == WS_ENC_STR_MAIN)
        cur_frame_info.m_StreamType = eMainVideoAndSound;
    else
        cur_frame_info.m_StreamType = eAssistVideo;
        
    while (1)
    {
        if (eTaskStatusStart != m_dwState)
        {
            break;
        }
        
        if (CHECK_POINT_NO_NULL(m_pSession))
        {
            nRet = RealStream_GetOneFrame(m_iTaskId,m_channel_id,&cur_frame_info,&pFramePointer);
            if( nRet >= 0 )
            {
                iFrameType = cur_frame_info.iFrameType;
                iFrameLen = cur_frame_info.iFrameLen;
                if( (iFrameType == 0x80) || (iFrameType == 0x81) )
                    iNeedIFrame = 1 ;

                /*add by linhh 20170703 : 暂不发送音频帧*/
                if( 0x08 == iFrameType )
                {
                    RealStream_DelOneFrame(m_iTaskId,m_channel_id,&cur_frame_info);
                    continue ;
                }
                
                if( iNeedIFrame > 0 )
                {
                    if( (iFrameType == 0x01) || (iFrameType == 0x10) )
                    {
                        /* change by linhh 20170621 : 合并DVR 与IPC 控制代码，在获取帧时都包含了帧头信息*/
                        RunTaskSendData((char *)pFramePointer, (DWORD)cur_frame_info.iFrameLen, m_pSession);
                        RealStream_DelOneFrame(m_iTaskId,m_channel_id,&cur_frame_info);
                    }
                    else
                    {
                        RealStream_DelOneFrame(m_iTaskId,m_channel_id,&cur_frame_info);
                    }
                        
                    if( (iFrameType == 0x01) || (iFrameType == 0x10) )
                    {
                        iNeedIFrame 	= 0 ;
                        iLastFrameNo	= cur_frame_info.iFrameNo ;
                    }
                }
                else
                {
                    if( (iFrameType == 0x01) || (iFrameType == 0x10) )
                    {
                        /* change by linhh 20170621 : 合并DVR 与IPC 控制代码，在获取帧时都包含了帧头信息*/
                        RunTaskSendData((char *)pFramePointer, (DWORD)cur_frame_info.iFrameLen, m_pSession);
                        RealStream_DelOneFrame(m_iTaskId,m_channel_id,&cur_frame_info);
                        iLastFrameNo	= cur_frame_info.iFrameNo;
                    }
                    /*change by linhh 20170703 : 音频与视频的帧号独立编号，不存在0x52000000的控制*/
                    else if( (cur_frame_info.iFrameNo == (iLastFrameNo + 1))  )
                    {
                        if( (iFrameType == 0x02) || (iFrameType == 0x40) )
                        {
                            /* change by linhh 20170621 : 合并DVR 与IPC 控制代码，在获取帧时都包含了帧头信息*/
                            RunTaskSendData((char *)pFramePointer, (DWORD)cur_frame_info.iFrameLen, m_pSession);
                        }
                        RealStream_DelOneFrame(m_iTaskId,m_channel_id,&cur_frame_info);
                        iLastFrameNo	= cur_frame_info.iFrameNo  ;							
                    }
                    else
                    {
                        RealStream_DelOneFrame(m_iTaskId,m_channel_id,&cur_frame_info);
                    }
                }
            }
            else
            {
                realsender_rsleep(10000);
            }
        }
        else
        {
            break;
        }
    }
    return RET_SUCCESS;
}

//初始化
int CRealStreamSender::Initialize()
{
    m_dwState   = eTaskStatusInitialize;
    m_pSession  = NULL;
    m_iTaskId   = 0xFFFF ;
    return RET_SUCCESS;
}

//销毁
int CRealStreamSender::Destory()
{
    return Initialize();
}
}

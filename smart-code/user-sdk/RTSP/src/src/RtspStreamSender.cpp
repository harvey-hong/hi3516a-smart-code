#include "../inc/RtspStreamSender.h"
#include "../inc/RtpRtsp.h"
#include "h265_decoder.h"/*cb change 2016.8.5 .添加h265的支持*/ 

// nal unit type
#define NAL_UNKNOWN       0
#define NAL_SLICE         1
#define NAL_SLICE_DPA     2
#define NAL_SLICE_DPB     3
#define NAL_SLICE_DPC     4
#define NAL_SLICE_IDR     5     /* ref_idc !  0 */
#define NAL_SEI           6     /* ref_idc    0 */
#define NAL_SPS           7
#define NAL_PPS           8
#define NAL_AUD           9
//设置最大时间戳极限值
#define MAX_TIME_STAMP                              (4015731839)

namespace ApplicationLayer
{
CRtspStreamSender::CRtspStreamSender()
{
    m_eStreamType = eRtspStreamTypeBegin;
    m_eCaptureStatus = eTaskStatusStop;
    memset(m_acSDPInfo, 0, MAX_SDP_LEN);
    m_nSDPInfoLen   = 0;
    m_nSpsFound     = 0;
    m_nPpsFound         = 0;
    m_nSessionId    = 0;
    m_pNaluPureData     = NULL;
    m_nNtpTimeStamp = 8000;
    m_dwLastTimeStamp = 0;
    m_eSendStatus   = eTaskStatusStop ;
    IsIFrameSend        = 1 ;
}

CRtspStreamSender::~CRtspStreamSender()
{
    Destroy();
}

//\\ 保存RTSP流发送器绑定的流类型与RTSP会话结构
int CRtspStreamSender::Initialize(int nSessionId, eRtspStreamType eStreamType)
{
    if (nSessionId <= 0 || eStreamType <= eRtspStreamTypeBegin || eStreamType >= eRtspStreamTypeEnd)
    {
        return RET_FAIL;
    }

    if (RET_CHECK_FAIL(m_cSDPSignal.create()))
    {
        return RET_FAIL;
    }

    if (RET_CHECK_FAIL(m_cCapStatusMutex.create()))
    {
        m_cSDPSignal.destroy();
        return RET_FAIL;
    }

    m_eStreamType   = eStreamType;
    m_nSessionId    = nSessionId;
    return RET_SUCCESS;
}

// 销毁
int CRtspStreamSender::Destroy()
{
    m_cSDPSignal.destroy();
    m_cCapStatusMutex.destroy();
    m_eStreamType   = eRtspStreamTypeBegin;
    m_eCaptureStatus = eTaskStatusStop;
    memset(m_acSDPInfo, 0, MAX_SDP_LEN);
    m_nSDPInfoLen   = 0;
    m_nSpsFound     = 0;
    m_nPpsFound         = 0;
    m_nSessionId    = 0;
    m_nNtpTimeStamp = 8000;  // 时间戳的初始值
    m_dwLastTimeStamp = 0;
    m_eSendStatus   = eTaskStatusStop ;
    IsIFrameSend        = 1 ;
    return RET_SUCCESS;
}

//\\ 检查在SPS与PPS已经获取的情况下发送帧数据
int CRtspStreamSender::Send(IN LPBuffer stream, void *pClientConn)
{
    if (NULL == stream || stream->dwBufLen <= 22)
    {
        return RET_FAIL;
    }

    int     nRet = RET_SUCCESS;

    if (0 == m_nSpsFound || 0 == m_nPpsFound)
    {
        nRet = GetSDPInfoFromFrame(stream);

        if (RET_CHECK_FAIL(nRet))
        {
            return RET_SUCCESS;
        }
    }

    m_cCapStatusMutex.lock();

    if (eTaskStatusStart != m_eCaptureStatus)
    {
        m_cCapStatusMutex.unlock();
        return RET_SUCCESS;
    }

    //\\ 还没有启动发送直接丢弃
    if (eTaskStatusStart != m_eSendStatus)
    {
        m_cCapStatusMutex.unlock();
        return RET_SUCCESS;
    }

    BYTE    *pBuffer = stream->pBuffer;
    int         nBufLen = stream->dwBufLen;
    unsigned char  nFrameType = *(pBuffer + 4);   //DVR encoded frames : Got Video I frame type 0x01 or p frame type 0x02, Audio frame type 0x08
    BYTE    nCodecType = *(pBuffer + 13);             //codec value: DVR encoded Audio  G726 0x00    G711_a 0x01  G711_u 0x02  G729 0x03, video H264 0x01 H264_A 0x03
    int Data_length = 0;
    memcpy(&Data_length, pBuffer, 4);                  // Got data length from WS private frame header, this (length -4) is true H264 or Audio data frome length

    // show frame data bytes :
    /*
    printf("data start: nBufLen=[0x%0.8x==%d] length=[0x%0.8x==%d]\n\r",nBufLen,nBufLen, Data_length, Data_length);
    for(int i = 0; i< 50; i++)
    {
    printf(" 0x%0.2x ", *(pBuffer + i));
    }
    printf("\n\r");
    */
        int CodecType = *(pBuffer + 13);/*cb change 2016.8.5 .添加h265的支持*/ 
    if (IsIFrameSend > 0)
    {
        if ((0x01 != nFrameType) && (0x10 != nFrameType) && (0x11 != nFrameType))
        {
            m_cCapStatusMutex.unlock();
            return RET_SUCCESS;
        }
        IsIFrameSend = 0 ;
    }

    if ((0x02 == nFrameType) || (0x01 == nFrameType) || (0x10 == nFrameType) || (0x11 == nFrameType) || (0x40 == nFrameType) || (0x41 != nFrameType))
    {
        int nTimeStamp  = 0;
        memcpy(&nTimeStamp, pBuffer + 9, 4);

        if ((0x01 == nCodecType)||(0x03 == nCodecType)||(0x04 == nCodecType)||(0x05 == nCodecType)||(0x06 == nCodecType))  // video frame
        {
            pBuffer += 22;
            nBufLen -= 22;
        }
        else // Other audio frame
        {
            pBuffer += 18;
            nBufLen -= 18;
        }
            nRet = SendH264DataFrame(pBuffer, nBufLen, nTimeStamp, pClientConn,CodecType);/*cb change 2016.8.5 .添加h265的支持*/ 
    }

    m_cCapStatusMutex.unlock();
    return nRet;
}

//\\ 等待同步信号，获取SDP信息.
int CRtspStreamSender::GetSDPInfo(char *pSDPInfo, INT32 &nSDPLen)
{
    if (NULL == pSDPInfo)
    {
        return RET_FAIL;
    }

    // change by luof 20160105 start - end 
    if(m_nSpsFound!=1||m_nPpsFound!=1)
    {
        m_cSDPSignal.wait();
    }

    if (m_nSDPInfoLen > nSDPLen)
    {
        return RET_FAIL;
    }

    nSDPLen     = m_nSDPInfoLen;
    memmove(pSDPInfo, m_acSDPInfo, nSDPLen);
    m_nSDPInfoLen = 0;
    return RET_SUCCESS;
}

//\\ 设置RTSP流发送器启动标志
int CRtspStreamSender::StartCapture()
{
    m_cCapStatusMutex.lock();

    if (eTaskStatusStart != m_eCaptureStatus)
    {
        m_eCaptureStatus = eTaskStatusStart;
    }

    m_cCapStatusMutex.unlock();
    return RET_SUCCESS;
}

//\\ 设置RTSP流发送器停止标志
int CRtspStreamSender::StopCapture()
{
    m_cCapStatusMutex.lock();

    if (eTaskStatusStop != m_eCaptureStatus)
    {
        m_eCaptureStatus = eTaskStatusStop;
    }

    m_eSendStatus   = eTaskStatusStop ;
    IsIFrameSend        = 1 ;
    m_cCapStatusMutex.unlock();
    return RET_SUCCESS;
}

int CRtspStreamSender::StartSend()
{
    m_cCapStatusMutex.lock();

    if (eTaskStatusStart != m_eSendStatus)
    {
        m_eSendStatus = eTaskStatusStart;
    }

    IsIFrameSend        = 1 ;
    m_cCapStatusMutex.unlock();
    return RET_SUCCESS;
}

int CRtspStreamSender::GetRtspClientHandle()
{
    return m_nSessionId;
}

// used to record H264 farme data file
#if 0
static FILE *H264_file = NULL;
static int g_file_size = 0;
#endif

/*cb change 2016.8.5 .添加h265的支持 start*/ 
//私有函数， 发送H264数据，但是NAL_SLICE与NAL_SLICE_IDR帧直接发送，而其它帧只发送NALU信息
    int CRtspStreamSender::SendH264DataFrame(BYTE *pData, int nDataLen, DWORD nTimeStamp, void *pClientConn,int nCodecType)
{
    int nRet = RET_SUCCESS;
    // 一帧数据缓冲区及其大小..
    BYTE    *pFrameBuf = pData;
    int     nRemainSz = nDataLen;
    int     nEndofFrameFlag = 0;

        //从前200字节中找到最后一个0x00 0x00 0x00 0x01..
        int find_count = 0;
        BYTE    *pFrameBuftmp = pFrameBuf;
        int     nRemainSztmp = nRemainSz;
        while (find_count < 200)
        {
            if(pFrameBuf[0] != 0 || pFrameBuf[1] != 0 || pFrameBuf[2] != 0 || pFrameBuf[3] != 1)
    {
        nRemainSz--;
        pFrameBuf++;
    }
            else
            {
                nRemainSztmp = nRemainSz--;
                pFrameBuftmp = pFrameBuf++;
            }
            find_count++;
        }
        nRemainSz = nRemainSztmp;
        pFrameBuf = pFrameBuftmp;

    //used to record H264 farme data file
#if 0
    if((NULL == H264_file)&&(g_file_size == 0))
    {
        H264_file = fopen("/root/h264.dat", "w");
        if(NULL == H264_file)
        {
            printf("\n Init creat file fail !\n\r");
            goto NOT_RECORD;
        }
        else
        {
            printf("\n Open file OK !\n\r");
        }
        g_file_size = 0;
    }

    fwrite(pFrameBuf, nRemainSz , 1, H264_file) ;
    g_file_size += nRemainSz;
    if(g_file_size >= 10*1024*1024)
    {
        fclose(H264_file);
        H264_file = NULL;
        printf("\n############### Record h264 file OK !##############\n\r");
    }

    NOT_RECORD:
    printf(" not record file\n\r");

#endif


    if (m_dwLastTimeStamp > 0)
    {
        DWORD nInterval = nTimeStamp - m_dwLastTimeStamp;
        if ((nInterval >= VIDEO_CLOCK_RATE) || (nInterval < 0))
        {
            nInterval = 3600;
        }

        m_nNtpTimeStamp += nInterval;
        if(m_nNtpTimeStamp >= MAX_TIME_STAMP )
        {
            m_nNtpTimeStamp = 8000;
            nTimeStamp = m_dwLastTimeStamp;
        }
    }
        m_dwLastTimeStamp = nTimeStamp;

        nRet = RTPSendH264Data(m_nSessionId, pFrameBuf,nRemainSz, NULL, 0, 0, m_nNtpTimeStamp, 0,nCodecType, NULL, pClientConn, 1);
        return RET_SUCCESS;
    }

    int CRtspStreamSender::GetFpsPps(LPBuffer pStream)
    {
        // 在该帧视频找搜索sps和pps
    BYTE    *pFrameBuf = pStream->pBuffer;
    int     nRemainSz = pStream->dwBufLen;
    BYTE    bytType;

    // 找到第一个00 00 00 01
    while (nRemainSz >= 4 && (pFrameBuf[0] != 0 || pFrameBuf[1] != 0 || pFrameBuf[2] != 0 || pFrameBuf[3] != 1))
    {
        nRemainSz--;
        pFrameBuf++;
    }

    // 从帧中分割出NALU
    int nSPSLen = 0 ;
    int nPPSLen = 0 ;
    int i = 0;

    while (nRemainSz > 4)
    {
        // 判断帧类型
        bytType = pFrameBuf[4] & 0x1F;

        if (NAL_SLICE == bytType)
        {
            break;
        }
        else if (NAL_SPS == bytType && (0 == m_nSpsFound))
        {
            // 寻找下一个00 00 00 01
            for (i = 4; i < nRemainSz - 3 ; i++)
            {
                if (pFrameBuf[i] == 0 && pFrameBuf[i + 1] == 0 && pFrameBuf[i + 2] == 0 && pFrameBuf[i + 3] == 1)
                {
                    memmove(m_acSDPInfo + m_nSDPInfoLen, pFrameBuf, i);
                    m_nSDPInfoLen += i;
                    m_nSpsFound = 1;
                    nSPSLen     = m_nSDPInfoLen ;
                    break;
                }
            }
        }
        else if (NAL_PPS == bytType && (0 == m_nPpsFound))
        {
            // 寻找下一个00 00 00 01
            for (i = 4; i < nRemainSz - 3 ; i++)
            {
                if (pFrameBuf[i] == 0 && pFrameBuf[i + 1] == 0 && pFrameBuf[i + 2] == 0 && pFrameBuf[i + 3] == 1)
                {
                    memmove(m_acSDPInfo + m_nSDPInfoLen, pFrameBuf, i);
                    m_nSDPInfoLen += i;
                    m_nPpsFound = 1;
                    nPPSLen         = m_nSDPInfoLen - nSPSLen ;
                    break;
                }
            }
        }

        if (1 == m_nPpsFound && 1 == m_nSpsFound)
        {
            // 通知sdp
#if 0
            {
                FILE    *fp ;
                fp = fopen("/dat/MobileSDP.dat", "ab+");
                fwrite(&m_nSDPInfoLen, sizeof(m_nSDPInfoLen), 1 , fp) ;
                fwrite(&nSPSLen, sizeof(nSPSLen), 1 , fp) ;
                fwrite(&nPPSLen, sizeof(nPPSLen), 1 , fp) ;
                fwrite(m_acSDPInfo, m_nSDPInfoLen, 1 , fp) ;
                fclose(fp) ;
                fp = NULL ;
            }
#endif
            m_cSDPSignal.signal();
            return RET_SUCCESS;
        }

        // 移动buffer指针
        nRemainSz -= i;
        pFrameBuf += i;
        }
        return RET_FAIL;
    }

    int CRtspStreamSender::GetVpsFpsPps(LPBuffer pStream)
    {
        // 在该帧视频找搜索sps和pps
        BYTE    *pFrameBuf = pStream->pBuffer;
        int     nRemainSz = pStream->dwBufLen;
        char    *temppt = NULL;
        int     tempSz = 0;
        BYTE    bytType;

        char tmp_buf[52];
        int tmp_len = 0;
        // 找到第一个00 00 00 01
        while (nRemainSz >= 4 && (pFrameBuf[0] != 0 || pFrameBuf[1] != 0 || pFrameBuf[2] != 0 || pFrameBuf[3] != 1))
        {
            nRemainSz--;
            pFrameBuf++;
        }
        temppt = (char *)pFrameBuf++;
        tempSz = nRemainSz--;

        // 找到第二个00 00 00 01
        while (nRemainSz >= 4 && (pFrameBuf[0] != 0 || pFrameBuf[1] != 0 || pFrameBuf[2] != 0 || pFrameBuf[3] != 1))
        {
            nRemainSz--;
            pFrameBuf++;
        }
        h265_unit_type type = get_nal_type(temppt,tempSz-nRemainSz,tmp_buf,&tmp_len);
        memmove(m_acSDPInfo + m_nSDPInfoLen, pFrameBuf, 4);
        m_nSDPInfoLen += 4;
        memmove(m_acSDPInfo + m_nSDPInfoLen, tmp_buf, tmp_len);
        m_nSDPInfoLen += tmp_len;
        temppt = (char *)pFrameBuf++;
        tempSz = nRemainSz--;

        // 找到第三个00 00 00 01
        while (nRemainSz >= 4 && (pFrameBuf[0] != 0 || pFrameBuf[1] != 0 || pFrameBuf[2] != 0 || pFrameBuf[3] != 1))
        {
            nRemainSz--;
            pFrameBuf++;
        }
        type = get_nal_type(temppt,tempSz-nRemainSz,tmp_buf,&tmp_len);
        memmove(m_acSDPInfo + m_nSDPInfoLen, pFrameBuf, 4);
        m_nSDPInfoLen += 4;
        memmove(m_acSDPInfo + m_nSDPInfoLen, tmp_buf, tmp_len);
        m_nSDPInfoLen += tmp_len;
        temppt = (char *)pFrameBuf++;
        tempSz = nRemainSz--;

        // 找到第四个00 00 00 01
        while (nRemainSz >= 4 && (pFrameBuf[0] != 0 || pFrameBuf[1] != 0 || pFrameBuf[2] != 0 || pFrameBuf[3] != 1))
        {
            nRemainSz--;
            pFrameBuf++;
        }
        type = get_nal_type(temppt,tempSz-nRemainSz,tmp_buf,&tmp_len);
        memmove(m_acSDPInfo + m_nSDPInfoLen, pFrameBuf, 4);
        m_nSDPInfoLen += 4;
        memmove(m_acSDPInfo + m_nSDPInfoLen, tmp_buf, tmp_len);
        m_nSDPInfoLen += tmp_len;

        m_nSpsFound = 1;
        m_nPpsFound = 1;
        m_cSDPSignal.signal();
        return RET_SUCCESS;
    }


//\\ 从视频帧中获取SDP信息
    int CRtspStreamSender::GetSDPInfoFromFrame(LPBuffer pStream)
    {
        //\\ 私有函数
        if (NULL == pStream)
        {
            return RET_FAIL;
        }

        int     nRet = RET_SUCCESS;
        //\\ 音频帧中没有SDP信息
        int nFrameType = *(pStream->pBuffer + 4);

        if (0x08 == nFrameType)
        {
            return RET_SUCCESS;
        }

        //\\ 判断是否为H264编码
        int nCodecType = *(pStream->pBuffer + 13);
        if(0x01 != nCodecType && 0x03 != nCodecType && 0x04 != nCodecType && 0x05 != nCodecType && 0x06 != nCodecType)  //hzg 20160510 新的 H264 codec值是6, H265 codec值是5 .
        {
            return RET_SUCCESS;
        }

        if(0x06 == nCodecType)
            return GetFpsPps(pStream);
        else
            return GetVpsFpsPps(pStream);
    }

}
/*cb change 2016.8.5 .添加h265的支持 end*/ 

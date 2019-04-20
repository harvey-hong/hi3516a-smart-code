
#ifndef HY_RTSP_COMMON_H

#define HY_RTSP_COMMON_H
#include "InternalCommon.h"

//////////////////////////////////////////////////////////////////////////
//宏定义
//////////////////////////////////////////////////////////////////////////

/** @brief URI最大长度                                                              */
#define MAX_RTSP_URI_LEN                            (128)

/** @brief 最大认证信息长度                                                             */
#define MAX_AUTHORIZE_INFO_LEN                      (512)

/** @brief response最大字符串长度                                                       */
#define MAX_RESPONSE_STRING_LEN                     (256)

/** @brief realm最大字符串长度                                                          */
#define MAX_REALM_STRING_LEN                        (128)

/** @brief nonce最大字符串长度                                                          */
#define MAX_NONCE_STRING_LEN                        (128)

// 最大会话名称长度
#define MAX_SESSION_NAME_LEN                        (64)

// 最大SDP长度
#define MAX_SDP_LEN                                 (1024)

// 每次调整码率的幅度
#define BITRATE_CONTROL_UNIT                        (32)  // kb

// I帧间隔，关系到码率的调节，在8x和9x的板子上要改变这个值
#define IFRAME_INTERVAL                             (1)

//////////////////////////////////////////////////////////////////////////

// 默认UDP MTU大小
#define UDP_MTU_SIZE                                (1450)

// 默认TCP MTU大小
#define TCP_MTU_SIZE                                (1452)

//默认最大帧间隔时间
#define MAX_FRAME_INTERVAL                          (1100)

//默认帧间隔时间
#define DEFAULT_FRAME_INTERVAL                      (40)

// 默认H.264和MJPEG流的时钟频率
#define VIDEO_CLOCK_RATE                            (90000)

// 默认G.711/G.726/G.729流的时钟频率
#define AUDIO_CLOCK_RATE                            (8000)

//////////////////////////////////////////////////////////////////////////
//枚举
//////////////////////////////////////////////////////////////////////////

/*!
*  @enum    eRtspStreamType
*  @brief   RTSP流类型
*/
enum eRtspStreamType
{
    eRtspStreamTypeBegin = -1,  // 流类型开始
    eRtspStreamReal,            // 实时流
    eRtspStreamHistory,         // 历史流
    eRtspStreamTypeEnd,         // 流类型结束
};

/*!
*  @enum    eRtspMediaCodeType
*  @brief   流媒体码流类型，按码流大小由高到低排列
*/
enum eRtspMediaCodeType
{
    eRtspMediaCodeTypeBegin = 0,    /*!< 起始值                                 */
    eRtspMediaCodeMain,             /*!< 主码流                                 */
    eRtspMediaCodeSub1,             /*!< 辅码流1                                */
    eRtspMediaCodeSub2,             /*!< 辅码流2                                */
    eRtspMediaCodeSub3,             /*!< 辅码流3                                */
    eRtspMediaCodeAdapt,            /*!< 自适应                                 */
    eRtspMediaCodeTypeEnd,          /*!< 结束值                                 */
};

/*!
*  @enum    eAuthenType
*  @brief   用户认证方式
*/
enum eAuthenType
{
    eAuthenBasic,               // 基本认证方式
    eAuthenDigest,              // 摘要认证方式
    eAuthenUnknown,             // 未知认证方式
};

/*!
*  @enum    eBitrateControl
*  @brief   码率控制类型
*/
enum eBitrateControl
{
    eBitRateCtrlBegin = 0,
    eBitrateCtrlUp,                 // 增大码率
    eBitrateCtrlDown,               // 降低码率
    eBitRateCtrlKeep,               // 保存原有码率
    eBitRateCtrlEnd,
};

/*!
*  @enum    eRtspVideoCodecType
*  @brief   RTSP视频编码类型
*/
enum eRtspVideoCodecType
{
    eRtspVideoCodecTypeBegin = 0,
    eRtspVideoCodecH264,            // H264
    eRtspVideoCodecH265,            // H265	/*cb change 2016.8.5 .添加h265的支持*/
    eRtspVideoCodecTypeEnd,
};

/*!
*  @enum    eRtspAudioCodecType
*  @brief   RTSP音频编码类型
*/
enum eRtspAudioCodecType
{
    eRtspAudioCodecTypeBegin = 0,
    eRtspAudioCodecG711A,           // G711A
    eRtspAudioCodecG711U,           // G711U
    eRtspAudioCodecG726_40,         // G726-40
    eRtspAudioCodecG726_32,         // G726-32
    eRtspAudioCodecG726_24,         // G726-24
    eRtspAudioCodecG726_16,         // G726-16
    eRtspAudioCodecG729,            // G729(merlin协议栈不支持)
    eRtspAudioCodecNone,            // 无音频
    eRtspAudioCodecTypeEnd,
};

//////////////////////////////////////////////////////////////////////////
//结构
//////////////////////////////////////////////////////////////////////////

/*!
*  @struct  tagAddSessionParam
*  @brief   添加会话参数
*/
typedef struct tagAddSessionParam
{
    int nChannel;                                       // 通道号
    eRtspStreamType eStreamType;                        // 流类型
    eRtspMediaCodeType eCodeType;                       // 实时流码流类型
    char acBeginTime[DATE_TIME_LEN];                    // 历史流起始时间
    char acEndTime[DATE_TIME_LEN];                      // 历史流结束时间
    char acSessionName[MAX_SESSION_NAME_LEN];           // 会话名称
} AddSessionParam, *LPAddSessionParam;

#endif

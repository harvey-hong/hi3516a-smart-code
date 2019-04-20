
#ifndef HY_RTSP_COMMON_H

#define HY_RTSP_COMMON_H
#include "InternalCommon.h"

//////////////////////////////////////////////////////////////////////////
//�궨��
//////////////////////////////////////////////////////////////////////////

/** @brief URI��󳤶�                                                              */
#define MAX_RTSP_URI_LEN                            (128)

/** @brief �����֤��Ϣ����                                                             */
#define MAX_AUTHORIZE_INFO_LEN                      (512)

/** @brief response����ַ�������                                                       */
#define MAX_RESPONSE_STRING_LEN                     (256)

/** @brief realm����ַ�������                                                          */
#define MAX_REALM_STRING_LEN                        (128)

/** @brief nonce����ַ�������                                                          */
#define MAX_NONCE_STRING_LEN                        (128)

// ���Ự���Ƴ���
#define MAX_SESSION_NAME_LEN                        (64)

// ���SDP����
#define MAX_SDP_LEN                                 (1024)

// ÿ�ε������ʵķ���
#define BITRATE_CONTROL_UNIT                        (32)  // kb

// I֡�������ϵ�����ʵĵ��ڣ���8x��9x�İ�����Ҫ�ı����ֵ
#define IFRAME_INTERVAL                             (1)

//////////////////////////////////////////////////////////////////////////

// Ĭ��UDP MTU��С
#define UDP_MTU_SIZE                                (1450)

// Ĭ��TCP MTU��С
#define TCP_MTU_SIZE                                (1452)

//Ĭ�����֡���ʱ��
#define MAX_FRAME_INTERVAL                          (1100)

//Ĭ��֡���ʱ��
#define DEFAULT_FRAME_INTERVAL                      (40)

// Ĭ��H.264��MJPEG����ʱ��Ƶ��
#define VIDEO_CLOCK_RATE                            (90000)

// Ĭ��G.711/G.726/G.729����ʱ��Ƶ��
#define AUDIO_CLOCK_RATE                            (8000)

//////////////////////////////////////////////////////////////////////////
//ö��
//////////////////////////////////////////////////////////////////////////

/*!
*  @enum    eRtspStreamType
*  @brief   RTSP������
*/
enum eRtspStreamType
{
    eRtspStreamTypeBegin = -1,  // �����Ϳ�ʼ
    eRtspStreamReal,            // ʵʱ��
    eRtspStreamHistory,         // ��ʷ��
    eRtspStreamTypeEnd,         // �����ͽ���
};

/*!
*  @enum    eRtspMediaCodeType
*  @brief   ��ý���������ͣ���������С�ɸߵ�������
*/
enum eRtspMediaCodeType
{
    eRtspMediaCodeTypeBegin = 0,    /*!< ��ʼֵ                                 */
    eRtspMediaCodeMain,             /*!< ������                                 */
    eRtspMediaCodeSub1,             /*!< ������1                                */
    eRtspMediaCodeSub2,             /*!< ������2                                */
    eRtspMediaCodeSub3,             /*!< ������3                                */
    eRtspMediaCodeAdapt,            /*!< ����Ӧ                                 */
    eRtspMediaCodeTypeEnd,          /*!< ����ֵ                                 */
};

/*!
*  @enum    eAuthenType
*  @brief   �û���֤��ʽ
*/
enum eAuthenType
{
    eAuthenBasic,               // ������֤��ʽ
    eAuthenDigest,              // ժҪ��֤��ʽ
    eAuthenUnknown,             // δ֪��֤��ʽ
};

/*!
*  @enum    eBitrateControl
*  @brief   ���ʿ�������
*/
enum eBitrateControl
{
    eBitRateCtrlBegin = 0,
    eBitrateCtrlUp,                 // ��������
    eBitrateCtrlDown,               // ��������
    eBitRateCtrlKeep,               // ����ԭ������
    eBitRateCtrlEnd,
};

/*!
*  @enum    eRtspVideoCodecType
*  @brief   RTSP��Ƶ��������
*/
enum eRtspVideoCodecType
{
    eRtspVideoCodecTypeBegin = 0,
    eRtspVideoCodecH264,            // H264
    eRtspVideoCodecH265,            // H265	/*cb change 2016.8.5 .���h265��֧��*/
    eRtspVideoCodecTypeEnd,
};

/*!
*  @enum    eRtspAudioCodecType
*  @brief   RTSP��Ƶ��������
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
    eRtspAudioCodecG729,            // G729(merlinЭ��ջ��֧��)
    eRtspAudioCodecNone,            // ����Ƶ
    eRtspAudioCodecTypeEnd,
};

//////////////////////////////////////////////////////////////////////////
//�ṹ
//////////////////////////////////////////////////////////////////////////

/*!
*  @struct  tagAddSessionParam
*  @brief   ��ӻỰ����
*/
typedef struct tagAddSessionParam
{
    int nChannel;                                       // ͨ����
    eRtspStreamType eStreamType;                        // ������
    eRtspMediaCodeType eCodeType;                       // ʵʱ����������
    char acBeginTime[DATE_TIME_LEN];                    // ��ʷ����ʼʱ��
    char acEndTime[DATE_TIME_LEN];                      // ��ʷ������ʱ��
    char acSessionName[MAX_SESSION_NAME_LEN];           // �Ự����
} AddSessionParam, *LPAddSessionParam;

#endif

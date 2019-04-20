#ifndef  _HISDK_H_
#define  _HISDK_H_

//----------------------------------------------------------------------------------------------------------
typedef enum 
{	
    	BOARD_SENSOR_NULL = 0, 
    	BOARD_SENSOR_NORM9960= 1, 
    	BOARD_SENSOR_OV2710 = 2, 
    	BOARD_SENSOR_IMX035 = 3, 
    	BOARD_SENSOR_MT9D131 = 4, 
    	BOARD_SENSOR_SONY = 5, 
    	BOARD_SENSOR_HITACHI = 6, 
    	BOARD_SENSOR_EFFIOE_E=7,
    	BOARD_SENSOR_HI9D131 =8,
    	BOARD_SENSOR_NORM5150 =9,
    	BOARD_SENSOR_IMAX122	=10,
    	BOARD_SENSOR_IMAX123=11,
    	BOARD_SENSOR_AP0130=12,
    	BOARD_SENSOR_OV9712=13,//add by yxl 2014.10.20
    	BOARD_SENSOR_OV5658=14,
    	BOARD_SENSOR_AR0330=15,
    	BOARD_SENSOR_OV4689=16,
    	BOARD_SENSOR_AR0237=17,
        BOARD_SENSOR_SC2135=18,
}BoardSensorType_t;

#define WB_MAX_REDGAIN 255
#define WB_MIN_REDGAIN 0
#define WB_MAX_BLUEGAIN 255
#define WB_MIN_BLUEGAIN 0
#define WB_MAX_GREENGAIN 255
#define WB_MIN_GREENGAIN 0

// define for Shutter Value
#define AE_MAX_SHUTTER 64
#define AE_MIN_SHUTTER 0

#define APP_AE_WINDOW_NUM 6

/* NXP8850 Image Sensor Processing配置信息: AE Window 设置*/
typedef struct tagAEWindow
{
	//开关(on /off)
	int bOpen;
	//X (0-4095) 需要识别到最大的宽度，如果是最大720p,就是1280
	int nX;
	//Y (0-4095) 需要识别最大有效像素高度
	int nY;
	//width (1-4095) 需要识别到最大的宽度
	int nWidth;
	//height(1-4095) 需要识别最大有效像素高度
	int nHeight;
	//Weighting (1X 到 8X可选) 参数0-7
	int nWeighting;

}AEWINDOW, *LP_AEWINDOW;

/* NXP8850 Image Sensor Processing配置信息: AE Window 设置*/
typedef struct tagAEWindowCFG
{
	AEWINDOW AEWindow[APP_AE_WINDOW_NUM];
#ifdef USE_NXPSDK45
	unsigned int dwMode; // 0:auto,1:backlight,2:customized, default mode is customized.
#endif
}AEWINDOW_CFG, *LP_AEWINDOW_CFG;

/* NXP8850 Image Sensor Processing配置信息: 曝光参数*/
typedef struct tagEXPOSALCFG
{
	//镜头光圈：(Lens Type)		0为 开启自动光圈  1-256为 手动光圈对应(0-255)
	int bLensType;
	//目标亮度  (Target Lumiance)	0-255
	int nTargetLumiance;
	//偏移 (Offset)	0-255
	int nOffset;
	//快门速度  (Shutter Speed)最小速度，0～1/2		最大速度，1/120～1	速度可选0,1/120,1/60,1/30,1/15,1/8,1/4,1/2,1 
	int nMinShutterSpeed;
	int nMaxShutterSpeed;
	//增益系数 (Gain)最小增益 1x ~ 16x 	最大增益 2x ~ 32x
	int nMinAutoGain;
	int nMaxAutoGain;
} EXPOSAL_CFG, *LP_EXPOSAL_CFG;

/* NXP8850 Image Sensor Processing配置信息: 白平衡 (White Balance)*/
typedef struct tagWHITEBALANCECFG
{
	//	0 自动	1 手动： 手动 需要修改 RED Gain (0-255),Blue Gain(0-255)	2 多云	3 太阳	4 阴天5 冷白荧光灯
	int bWorkMode;
	int nRedGain;
	int nBlueGain;
} WHITEBALANCE_CFG, *LP_WHITEBALANCE_CFG;

/* NXP8850 Image Sensor Processing配置信息: 数字降噪 （De-Noise）*/
typedef struct tagDENOISECFG
{
	//0为关闭1为开启： Y  Strength （0-255）  Cb strength (0-255)   Cr strength (0-255)
	int bWorkMode;
	int nYStrength;
	int nCbStrength;
	int nCrStrength;
} DENOISE_CFG, *LP_DENOISE_CFG;

/* NXP8850 Image Sensor Processing配置信息: 颜色校正*/
typedef struct tagCOLORCORRECTIONCFG
{
    float       flCoeff_RR;
    float       flCoeff_GR;
    float       flCoeff_BR;
    float       flCoeff_RG;
    float       flCoeff_GG;
    float       flCoeff_BG;
    float       flCoeff_RB;
    float       flCoeff_GB;
    float       flCoeff_BB;
    float       flOffset_R;
    float       flOffset_G;
    float       flOffset_B;
} COLORCORRECTION_CFG, *LP_COLORCORRECTION_CFG;

/* NXP8850 Image Sensor Processing配置信息: 图像颜色(0为黑白1为彩色)*/
typedef enum {
    VIDEO_COLOR_MONO = 0, //黑白
    VIDEO_COLOR_COLOR= 1, //彩色
}VideoColorType_t;

/* NXP8850 Image Sensor Processing配置信息: 图像方向(0为原始1为翻转2为镜像3为既翻转又镜像)*/
typedef enum {
    VIDEO_ORIENTATION_NORMAL = 0, //原始
    VIDEO_ORIENTATION_FLIP= 1, //翻转
    VIDEO_ORIENTATION_MIRROR  = 2, //镜像
    VIDEO_ORIENTATION_FLIP_MIRROR= 3, //翻转and 镜像
}VideoOrientationType_t;

typedef struct{
	unsigned int protocol;
	unsigned int addr;
	unsigned int band;
}PTZParam_t;
typedef enum
{
	VIDEO_FREQUENCY_50HZ = 0,	//50HZ
	VIDEO_FREQUENCY_60HZ = 1,	//60HZ
} VideoFrequencyType_t;
//编码电子PTZ
typedef enum {
    EPTZ_CLOSE     = 0, //关闭EPTZ
    EPTZ_OPEN      = 1, //开启EPTZ
    EPTZ_STOP      = 2, //停止EPTZ
    EPTZ_GETPOS    = 3,//获取坐标
    EPTZ_SETPOS    = 4, //设置坐标 
    EPTZ_UP        = 5, //上下左右
    EPTZ_DOWN      = 6, //
    EPTZ_LEFT      = 7, //
    EPTZ_RIGHT     = 8, //
}EPTZ_t;
//------------------------------------------------------------------------------------------------------
typedef enum 
{
    StandardNone    = 0x80000000,
    StandardNTSC    = 0x00000001,
    StandardPAL     = 0x00000002,
    StandardSECAM   = 0x00000004,
} VideoStandard_t;

typedef struct tag_FramsStatistics
{
    unsigned long   VideoFrames;
    unsigned long   AudioFrames;
    unsigned long   FramesLost;
    unsigned long   QueueOverflow;
}FRAMES_STATISTICS, *PFRAMES_STATISTICS;

typedef struct
{
    long    nWidth;
    long    nHeight;
    long    nStamp;
    long    nType;
    long    nFrameRate;
}FRAME_INFO;

typedef struct
{
    long    left;
    long    top;
    long    right;
    long    bottom;
} RECTH, *PRECTH, *LPRECTH;

typedef struct 
{
    long            nFrameNum;          
    unsigned int    nFrameTime;          
    long            nFilePos;            
}FRAME_POS ,*PFRAME_POS;

typedef struct tag_ChannelCapability
{
    unsigned char   bAudioPreview;
    unsigned char   bAlarmIO;
    unsigned char   bWatchDog;
}CHANNEL_CAPABILITY, *PCHANNEL_CAPABILITY;

#if 0
typedef enum 
{
    PktError            = 0x0000,	
    PktIFrames          = 0x0001,
    PktPFrames          = 0x0002,
    PktBPFrames         = 0x0020,
    PktBBPFrames        = 0x0004,
    PktAudioFrames      = 0x0008,
    PktQCIFIFrames      = 0x0010,
    PktQCIFPFrames      = 0x0040,
    PktBIFrames         = 0x0090,
    PktBBIFrames        = 0x00C0,
    PktSysHeader        = 0x0080,
    PktSFrames          = 0x0200,
    PktDspStatus        = 0x0100,
    PktAimDetection     = 0x0400,
    PktOrigImage        = 0x0800,
    PktMotionDetection  = 0x1000	
}FrameType_t;
#endif

typedef enum 
{	
    	PktError            = 0x0000,	
    PktIFrames          = 0x0001,
    PktPFrames          = 0x0002,
    PktBPFrames         = 0x0020,
    PktBBPFrames        = 0x0004,
    PktAudioFrames      = 0x0008,
    PktQCIFIFrames      = 0x0010,
	PktSQCIFIFrames 	= 0x0011,
    PktQCIFPFrames      = 0x0040,
	PktSQCIFPFrames 	= 0x0041,
    PktBIFrames         = 0x0090,
    PktBBIFrames        = 0x00C0,
    PktSysHeader        = 0x0080,
	PktSysHeaderAux 	= 0x0081,
	PktSysHeaderHDAux 	= 0x0082,
    PktSFrames          = 0x0200,
    PktDspStatus        = 0x0100,
    PktAimDetection     = 0x0400,
    PktOrigImage        = 0x0800,
    PktMotionDetection  = 0x1000	
}FrameType_t;

typedef struct tagVersion
{
    unsigned long   DspVersion,	DspBuildNum;
    unsigned long   DriverVersion,	DriverBuildNum;
    unsigned long   SDKVersion,	SDKBuildNum;
}VERSION_INFO, *PVERSION_INFO;

typedef enum 
{
    Mode_YYYY_MM_DD     = 0,
    Mode_MM_DD_YYYY     = 1,
} OSDTimeMode_t;

typedef struct	TimeOSDInfo_t
{
    int             FontWidth;              //字符宽度
    int             FontHeight;             //字符高度
    int             Start_X;                //起始X坐标
    int             Start_Y;                //起始Y坐标
    int             bTranslant;             //是否透明
    int             bHour24;                //是否24小时制
    int m_iTimePos ;
    OSDTimeMode_t   DisMod;                 //0,表示年月日, =1，表示月日年
    char            *pFontPixinfo;          //15个关键字的点阵信息：数字0-9,字母"A"，"P"，"M"，"："，"-"
}TimeOSDInfo_t;

typedef struct	TextOSDInfo_t
{
    int             TextNum;                //文本字符个数
    int             Start_X;                //起始X坐标
    int             Start_Y;                //起始Y坐标
    int		m_iTextPos;
    char            *pPixinfo;              //点阵信息(每个字符的宽、高各占一个字节)
}TextOSDInfo_t;
#if 0
typedef enum 
{
    ENC_CIF_FORMAT      = 0,
    ENC_QCIF_FORMAT     = 1,
    ENC_2CIF_FORMAT	    = 2,
    ENC_MD_FORMAT       = 3,
    ENC_D1_FORMAT       = 4,
    ENC_DCIF_FORMAT     = 5,
    ENC_SD1_FORMAT      = 6
}PictureFormat_t;
#else
typedef enum
{
	ENC_CIF_FORMAT 		= 0,
	ENC_QCIF_FORMAT 		= 1,
	ENC_2CIF_FORMAT 		= 2,
	ENC_MD_FORMAT 		= 3,
	ENC_D1_FORMAT 		= 4,
	ENC_DCIF_FORMAT 		= 5,
	ENC_SD1_FORMAT 		= 6,
	ENC_QVGA_FORMAT 		= 7,			//320*240
	ENC_VGA_FORMAT 		= 8,			//640*480
	ENC_SVGA_FORMAT 		= 9,			//800*600
	ENC_XVGA_FORMAT 		= 10,		//1024*768
	ENC_HD720_FORMAT 		= 11,		//1280*720
	ENC_QUADVGA_FORMAT 	= 12,		//1280*960
	ENC_SXGA_FORMAT 		= 13,		//1280*1024
	ENC_UXGA_FORMAT 		= 14,		//1600*1200
	ENC_HD1080_FORMAT 	= 15,		//1920*1080
	ENC_HD576_FORMAT 		= 16,     		//960*576
	ENC_QXGA_FORMAT		= 17,		//2048*1536
	ENC_5M_FORMAT		= 18,		//2592*1936
	ENC_4M_FORMAT		= 19,		//2592*1520
} PictureFormat_t;
#endif
//add by liuy date 2016-02-03 start
typedef enum
{
	WS_H264_FORMAT = 0,
	WS_H265_FORMAT = 1,
	WS_MPEG4_FORMAT = 2,
}EncFormat_t;
//add by liuy date 2016-02-03 end
typedef enum 
{
    TYPE_5150IPC  			= 45,
    TYPE_720IPC  				= 46,
    TYPE_650IPC		   	    	= 47,
    TYPE_HYCI785                  	= 48,	//0x70,
    TYPE_HY_7104_G			= 0x49,
}BoardFormat_t;

typedef struct CODEC_PARA_S_t
{
    PictureFormat_t PictureFormat;          //设置编码格式   
    int             BitRate;                //Bit率
    int             FrameRate;              //帧率
    int             PicQualityLever;        //编码图像质量，vbr有效
    int             bCbr;                   //码率控制类型：0为VBR，1为CBR
    int             KeyFrameInterval;       //关键帧间隔
//add by liuyu date 2015-02-02 start
	EncFormat_t		EncFormat;		//压缩格式
//add by liuyu date 2015-02-02 end     
}CODEC_PARA_S;

typedef struct tagCHANNEL_INFO
{
    PictureFormat_t PictureFormat;
    BoardFormat_t   BoardFormat;
    unsigned long   Reserved[4];
}CHANNEL_INFO,*PCHANNEL_INFO;

typedef struct tagMotionData
{
    PictureFormat_t PicFormat;
    unsigned long   HorizeBlocks;
    unsigned long   VerticalBlocks;
    unsigned long   Stride;
}MOTION_DATA_HEADER, *PMOTION_DATA_HEADER;

typedef int	(*STREAM_READ_CALLBACK )(unsigned long ChannelNumber);
typedef int	(*TALKING_READ_CALLBACK )(unsigned long HINumber);
typedef int (*SERIALDATA_READ_CALLBACK)(unsigned char* pSerailData,unsigned int uiLength);

#define STREAM_TYPE_VIDEO   1
#define STREAM_TYPE_AUDIO   2
#define STREAM_TYPE_AVSYNC  3

#define BITRATE_VBR     0
#define BITRATE_CBR     1
#define BITRATE_HBR     2

#define HI_SDK_SUCESS                   0               //成功
#if 0
#define ERR_NO                          0x00000000      //无错误
#define ERR_MALLOC_ERROR                0xc0000000      //内存分配失败
#define ERR_INVALID_HANDLE              0xc0000001      //句柄错误
#define ERR_WAIT_TIMEOUT                0xc0000002      //等待超时
#define ERR_INVALID_ARGUMENT            0xc0000003      //参数错误
#define ERR_NOT_SUPPORT                 0xc0000004      //不支持功能
#define ERR_SDK_INITFAIL                0xc0000005      //SDK初始化失败
#define ERR_FILE_READ_ERROR             0xC0000006      //文件读取失败
#define ERR_BUFFER_LEN_SHORT            0xC0000007      //内存大小不够
#define ERR_PACKET_NO_DATA              0xC0000008      //包里没有数据
#define ERR_SYS_BUSY                    0xC0000009      //系统忙
#define ERR_ENCODENOTSTART              0xC000000A      //未启动录像

#define ERR_SDK_NOINIT                  0xFFFFFFFF      //SDK没有初始化
#endif
#define ERR_NO                        	 	0x00000000	//无错误
#define ERR_MALLOC_ERROR                	0xc0000000	//内存分配失败
#define ERR_INVALID_HANDLE              	0xc0000001	//句柄错误
#define ERR_WAIT_TIMEOUT              	 	0xc0000002	//等待超时
#define ERR_INVALID_ARGUMENT          		0xc0000003	//参数错误
#define ERR_NOT_SUPPORT                 	0xc0000004	//不支持功能
#define ERR_SDK_INITFAIL                	0xc0000005	//SDK初始化失败
#define ERR_FILE_READ_ERROR             	0xC0000006	//文件读取失败
#define ERR_FILE_WRITE_ERROR							0xC0000007
#define ERR_BUFFER_LEN_SHORT           		0xC0000008	//内存大小不够
#define ERR_PACKET_NO_DATA              	0xC0000009	//包里没有数据
#define ERR_SYS_BUSY                    	0xC000000A	//系统忙
#define ERR_ENCODENOTSTART              	0xC000000B	//未启动录像
#define ERR_SEND_MESSAGE									0xC000000C
#define ERR_SDK_NOINIT                  	0xFFFFFFFF	//SDK没有初始化
#ifndef ERROR_MAX_THRDS_REACHED
#define ERROR_MAX_THRDS_REACHED         0x000000A4				//No more threads can be created in the system 
#endif

#ifdef __cplusplus
extern "C" {
#endif

int 	MP4Sys_InitDSPs( VideoStandard_t VideoStandard , int AudioInputPos, int AudioOutputPos, int TalkInputPos , int TalkOutputPos, PictureFormat_t PictureFormat, EncFormat_t EncFormat);		//add by liuy date 2016-01-25 start-end
int     MP4Sys_GetHiDevStatus(int *DevNum, char *DevStatus);
int     MP4Sys_GetSysStatus( );
int     MP4Sys_SetUserPassword(unsigned int iOldPassword, unsigned int iNewPassword);
int     MP4Sys_WriteBoardInfo(unsigned int iPassword, unsigned char *pInfoBuff, unsigned int iLen, unsigned int iRegIndex);
int     MP4Sys_ReadBoardInfo(unsigned int iPassword, unsigned char *pInfoBuff, unsigned int iLen, unsigned int iRegIndex);
int     MP4Sys_GetTotalEncChannels( );
int     MP4Sys_GetTotalDecChannels( );

void*   MP4Sys_EncChannelOpen(int ChannelNum);
int     MP4Sys_EncSetCurrentTime( );
int     MP4Sys_EncSetMute(int bMute);
int     MP4Sys_EncStartAudioPreview(void *hChannelHandle);
int     MP4Sys_EncStopAudioPreview();
int     MP4Sys_EncRegisterStreamReadCallback(STREAM_READ_CALLBACK StreamReadCallback);
int     MP4Sys_EncStartVideoCapture(void *hChannelHandle);
int     MP4Sys_EncStopVideoCapture(void *hChannelHandle);
int     MP4Sys_EncReadStreamData(void *hChannelHandle, char **pDataBuf, int *Length, int *FrameType, unsigned int *RealTime_Sec, unsigned int *RealTime_USec);
int     MP4Sys_EncGetFramesStatistics(void *hChannelHandle, PFRAMES_STATISTICS framesStatistics);
int     MP4Sys_EncGetBitRate(void *hChannelHandle, unsigned int *bitRate);
int     MP4Sys_EncCaptureIFrame(void *hChannelHandle);
int     MP4Sys_EncSetStreamType(void *hChannelHandle, unsigned short Type);
int     MP4Sys_EncSetCodecPara(void *hChannelHandle, int bAux, CODEC_PARA_S *pCodecPara);
int     MP4Sys_EncStartAuxCodec(void *hChannelHandle);
int     MP4Sys_EncStopAuxCodec(void *hChannelHandle);
int     MP4Sys_EncStartThirdCodec(void *hChannelHandle);
int     MP4Sys_EncStopThirdCodec(void *hChannelHandle);
int     MP4Sys_EncSetOsdText(void *hChannelHandle, TextOSDInfo_t *pOSDTextInfo);
int     MP4Sys_EncSetOsdTime(void *hChannelHandle, TimeOSDInfo_t *pOSDTimeInfo);
int     MP4Sys_EncSetOsd(void *hChannelHandle, int EnableTime, int EnableText);
// ghj 20121030
int		MP4Sys_EncSetOsdAll(char *strName);
int     MP4Sys_EncSetupMotionDetection( void *hChannelHandle, char *listOfAreas);
int     MP4Sys_EncStartMotionDetection(void *hChannelHandle);
int     MP4Sys_EncStopMotionDetection(void *hChannelHandle);
int     MP4Sys_EncAdjustMotionDetectPrecision(void *hChannelHandle, int iGrade, int iMotionDetectFps);
int     MP4Sys_EncMotionAnalyzer(void *hChannelHandle, char *MotionData, int *iResult);
int     MP4Sys_EncGetOriginalImage(void *hChannelHandle, char *ImageBuf, unsigned int *Size);

void*   MP4Sys_DecChannelOpen(int nDecCH);
int     MP4Sys_DecChannelClose(void *hChannelHandle);
int     MP4Sys_DecOpenFile(void *hChannelHandle, char *sFileName);
int     MP4Sys_DecCloseFile(void *hChannelHandle);
int     MP4Sys_DecOpenStream(void *hChannelHandle, int nBufPoolSize , int bFrameMode);
int     MP4Sys_DecCloseStream(void *hChannelHandle);
int     MP4Sys_DecSetPlayMode(int nPlayMode);
int     MP4Sys_DecPlay( );
int     MP4Sys_DecStop( );
int     MP4Sys_DecInputData(void *hChannelHandle, char *pBuf, int nSize );
int     MP4Sys_DecPause(int nPause);
int     MP4Sys_DecPlaySound(void *hChannelHandle);
int     MP4Sys_DecStopSound( );
int     MP4Sys_DecSetVolume(short nVolume);
short   MP4Sys_DecGetVolume();
int     MP4Sys_DecSetPlaySpeed(int nSpeed);
int     MP4Sys_DecOneByOne( );
int     MP4Sys_DecSetPlayPos(void *hChannelHandle , float fRelativePos);
int     MP4Sys_DecSetPlayedTime(void *hChannelHandle , int nTime);
int     MP4Sys_DecSetCurrentFrameNum(void *hChannelHandle , int nFrameNum);
int     MP4Sys_DecLocalZoom(void *hChannelHandle, int bLocalZoom, int Left, int Top, int Width, int Height);
int     MP4Sys_DecSetFileRefCallBack(void *hChannelHandle, void (*pFileRefDone)(int nPort, int nUser), int nUser);
int     MP4Sys_DecGetFileTime(void *hChannelHandle);
int     MP4Sys_DecGetFileTotalFrames(void *hChannelHandle);
int     MP4Sys_DecGetPictureSize(void *hChannelHandle, long *pWidth, long *pHeight);
int     MP4Sys_DecGetPlaySpeed( );
float   MP4Sys_DecGetPlayPos(void *hChannelHandle);
int     MP4Sys_DecGetPlayedTime(void *hChannelHandle);
int     MP4Sys_DecGetKeyFramePos(void *hChannelHandle, int nValue, int nType, PFRAME_POS pFramePos);
int     MP4Sys_DecGetNextKeyFramePos(void *hChannelHandle, int nValue, int nType, PFRAME_POS pFramePos);
int     MP4Sys_DecGetFileHead(void *hChannelHandle, char **pFileHead, int *FileHeadLenth);
int     MP4Sys_DecSnapShot(void *hChannelHandle, unsigned char *pBuf , unsigned int *realtime ,unsigned int *size);
int     MP4Sys_DecSetFillPic(char *sFileName);
int     MP4Sys_DecFillDisplayRegionPic(void *hChannelHandle, int bShow, RECTH*rect);
int     MP4Sys_DecFillDisplayRegionColor(void *hChannelHandle, int bShow, unsigned int RegionColor);
int     MP4Sys_DecGetSourceBufferRemain(void *hChannelHandle);
int     MP4Sys_DecResetSourceBuffer(void *hChannelHandle);
int     MP4Sys_DecSetSourceBufCallBack(void *hChannelHandle, int nThreShold, void (*SourceBufCallBack)(void *hChannelHandle, int nBufSize, int dwUser, void *pResvered), int dwUser, void *pReserved);
int     MP4Sys_DecResetSourceBufFlag(void *hChannelHandle);
int     MP4Sys_DecSetFileEndCallBack(void *hChannelHandle, void(* pFileEndCallBack)(int nPort, int nUser), int nUser);
unsigned int MP4Sys_DecGetVoShowTime(void *hChannelHandle);
int     MP4Sys_DecSetStreamBufferCount(int ncount);
int 	  MP4Sys_EncStartHDAuxCodec(void *hChannelHandle);
int      MP4Sys_EncStopHDAuxCodec(void *hChannelHandle);
int      MP4Sys_EncSetOsdTextOnSpot(void *hChannelHandle,TextOSDInfo_t *pOSDTextInfo);
int      MP4Sys_EncSetOsdTimeOnSpot(void *hChannelHandle,TimeOSDInfo_t *pOSDTimeInfo);
int     MP4Sys_DecClearBuffer(int bfillblack);

int     MP4Sys_SetMenuPreview(int bMenuShow);
int     MP4Sys_SetMixAlpha(unsigned int alphaIndex);
int     MP4Sys_UpdataOSGRegion(RECTH rect);
int     MP4Sys_SetSystemStandard(VideoStandard_t VideoStandard);
int     MP4Sys_GetSystemStandard(VideoStandard_t *VideoStandard);
int     MP4Sys_StartScreenSaving( );
int     MP4Sys_StopScreenSaving( );
int     MP4Sys_SetBuzzerTime(unsigned long nTime);
int     MP4Sys_SetTalkingMode(int Mode);
int     MP4Sys_SetTalkingEnable(int bEnable);
int     MP4Sys_SetTalkingData(char *DataBuf, unsigned long DataSize);

int  	SWSYS_SetISPSaturation(int bManualEnable, int target , int *stat, int statNum);

int 	SWSYS_SetVideoParam(int m_Brightness , int m_Contrast, int m_Saturation, int m_Hue, int m_nIndex) ;
#ifdef _HISI_V100_
int 	SWSYS_SetVideoSharpEx(int iSharpEnable, int iAutoSharp, int m_SharpTarget, int m_SharpMin, int Sharpaltd[], int altdNum, int SharpAltud[] , int altudNum ) ;
#endif
#ifdef _HISI_V300_
int 	SWSYS_SetVideoSharpEx(int iSharpEnable, int iAutoSharp, int m_SharpTarget, int m_SharpAltd, int m_SharpAltud, int Sharstrength[], int strengthNum, int Sharpaltd[], int altdNum, int SharpAltud[] , int altudNum );
#endif
int 	SWSYS_SetVideoXDREx(int iEnable, int iAuto , int iTarget, int iSlopMax , int iSlopMin, int Whitelevel, int blacklevel) ;
int	SWSYS_GetVideoGain(unsigned int *iAgain, unsigned int *iDgain, unsigned int *iAveLum);
int 	SWSYS_SetVideoDNREx( int i2D, int i3D, int chrome);
int    SWSYS_SetISPVideoDNR(int iEnable, int iManualEnable, int iTarget, int iMax , int *thresh, int threshNum);

int 	SWSYS_SetVideoFlip(int iFlip) ;
int SWSYS_SetVideoShadingEx(int iEnable, int ir_x, int ir_y , int ig_x , int ig_y , int ib_x , int ib_y , int *ir_array, int ir_len , int *ig_array, int ig_len , int *ib_array, int ib_len, int centerR, int centerG, int centerB , int DotNum);
int SWSYS_SetVideoBadDotEx(int iEnable, int iStaticEnable, int istartthresh, int ifinishthresh, int icountmax, int icountmin, int icount, int itigger_time, int islope, int ithresh);
int SWSYS_SetVideoDIS(int iEnable);
int SWSYS_SetVideoFOG(int iEnable);
#ifdef _HISI_V100_
int SWSYS_SetVideoEXPORTExEx(int iAuto, int iAutoMode, unsigned int iTime_Max, unsigned int iTime_Min, unsigned int iDGain_Max, unsigned int iDGain_Min, unsigned int iAGain_Max, unsigned int iAGain_Min, int iStep, int iTole, int iCompe, int *iWeight, int iRow, int iColumn, int iManualTimeEnalbe, int iManualTime, int iManualAGainEnable, int iManualAGain, int iManualDGainEnable, int iManualDGain, unsigned int  ISPMax, unsigned int SystemMax );
#endif
#ifdef _HISI_V300_
int SWSYS_SetVideoEXPORTExEx(int iAuto, int iAutoMode, unsigned int iTime_Max, unsigned int iTime_Min, unsigned int iDGain_Max, unsigned int iDGain_Min, unsigned int iAGain_Max, unsigned int iAGain_Min, int iStep, int iTole, int iCompe, int *iWeight, int iRow, int iColumn, int iManualTimeEnalbe, int iManualTime, int iManualAGainEnable, int iManualAGain, int iManualDGainEnable, int iManualDGain, unsigned int  ISPMax, unsigned int SystemMax , unsigned int  ISPMin, unsigned int SystemMin, unsigned int GainThreshold, unsigned int EVBias );
#endif
#ifdef _HISI_V100_
int SWSYS_SetVideoAI(int iAuto, int irisEnable, int irisCalEnable, int irisHoldValue, int irisStopValue, int irisCloseDriver, int irisTrigerTime, int irisintervia);
#endif
#ifdef _HISI_V300_
int SWSYS_SetVideoAI(int iAuto, int irisEnable, int irisCalEnable, int irisHoldValue, int irisStopValue, int irisCloseDriver, int irisTrigerTime, int irisintervia, int iriss32Kp, int iriss32Ki, int iriss32Kd, int irisMinPwm, int irisMaxPwm, int irisOpenPwm);
#endif
int SWSYS_GetVideoAI(int *irisHoldValue, int *irisStatus , int *irisTriggerStatus , int *irisStopValue, int *irisCloseDriver, int *irisTrigerTime, int *irisintervia);
#ifdef _HISI_V300_
int SWSYS_SetVideoWBALANCEEx(int iAuto, int iRGain, int iBGain, int iGRGain, int iGBGain, int iHighTemp, int iLowTemp, int iZoneSelect, int iSpeed, int *iWeight, int iRow, int iColumn, int whitelevel, int blacklevel, int cbmax, int cbmin, int crmax, int crmin, int grgain, int gbgain, int gsum);
#endif
#ifdef _HISI_V100_
int SWSYS_SetVideoWBALANCEEx(int iAuto, int iRGain, int iBGain, int iGGain, int iHighTemp, int iLowTemp, int iZoneSelect, int iSpeed , int *iWeight, int iRow, int iColumn, int whitelevel, int blacklevel, int cbmax, int cbmin, int crmax, int crmin, int grgain, int gbgain, int gsum);
#endif
int SWSYS_SetVideoGamma(int *iWeight, int nLen  , int fun, int iEnable);
int SWSYS_SetCCM(int highEnable, int* iHighValue, int MidEnable, int* iMidValue, int LowEnable, int* LowValue);
int SWSYS_SetCrossTalk(int iCROSSTALK_ENABLE, int iCROSSTALK_Strength, int iCROSSTALK_Sensitivity, int iCROSSTALK_Threshold, int iCROSSTALK_Slope);
int SWSYS_SetAntiFalseColor(int iTarget);
int SWSYS_SetBlackLevel(int *iLevel, int Num);
int SWSYS_SetVideoZoom(int nLarge);
int SWSYS_SetDemosaic(int ivhslope, int iaaslope, int ivaslope, int iuuslope, int ivhthresh, int iaathresh, int ivathresh, int iuuthresh, int idemosaicconfig);
int SWSYS_SetLDC(int iEnable , int xOffset, int yOffset, int ratio);
int	SWSYS_GetAEInfo( );

//add by liuy date 2016-01-22 start
int MP4Sys_SetResolution(PictureFormat_t m_PictureFormat, EncFormat_t m_EncFormat);
// 获取当前系统编码能力属性
int MP4Sys_GetEncCapacity(int *max_fps, int * cur_fps, int *frame_width, int *frame_height);
int MP4Sys_GetAuxEncCapacity(int *max_fps, int *frame_width, int *frame_height);
//add by liuy date 2016-01-22 end

int H264Enc_Start(int enc_type);
int H264Enc_Stop(int enc_type);
int AUDIO_Start();
int AUDIO_Stop();
    
#ifdef __cplusplus
}
#endif
#endif

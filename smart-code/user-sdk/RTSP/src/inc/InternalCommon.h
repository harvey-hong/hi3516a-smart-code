#ifndef INTERNAL_COMMON_H

#define INTERNAL_COMMON_H

//系统环境
#if defined(_WIN32)
#define SYSTEM_WIN32
#elif defined(_LINUX)
#define SYSTEM_LINUX
#else
#error "undefined system!"
#endif

//编译平台
//#define COMPILE_PLATFORM_VS6
//#define COMPILE_PLATFORM_VS7
//#define COMPILE_PLATFORM_VS8
//#define COMPILE_PLATFORM_VS9

#ifdef _HISI_ARM
	#define COMPILE_PLATFORM_HISI_ARM
#endif
//#define COMPILE_PLATFORM_GNU

#if defined(_MSC_VER)
#define COMPILE_PLATFORM_VS9
#elif defined(__GNUC__)
#define COMPILE_PLATFORM_GNU
#else
#error "undefined compile tool!"
#endif

#ifdef COMPILE_PLATFORM_VS9

//去除可忽略的警告
#pragma warning( disable : 4996 )
#pragma warning( disable : 4267 )

#elif defined(COMPILE_PLATFORM_GNU)

//用于检查编译器大小端
#include <endian.h>

#endif

#ifdef _POWERPC_8313
	//配置系统环境大小端
	#ifdef COMPILE_PLATFORM_VS9
		#define SYS_BIGDIAN
	#elif defined(SYSTEM_LINUX)
		#define SYS_LITDIAN
	#else
		#if defined(__i386__) || defined(__ia64__) || (defined(__alpha__) || defined(__alpha)) || defined(__arm__) || (defined(__mips__) && defined(__MIPSEL__)) || defined(__LITTLE_ENDIAN__) || (__BYTE_ORDER == __LITTLE_ENDIAN)
		#define SYS_LITDIAN		//小端字节序
		#else
		#define SYS_BIGDIAN		//大端字节序
		#endif
	#endif
#endif

//非常奇怪，不论是powerpc还是arm平台，Hxht必须用大端来编译
#ifdef _HISI_ARM
	#define SYS_BIGDIAN		//大端字节序
#endif

#ifdef SYS_LITDIAN

#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

#ifdef USE_SDP_PLATFORM
#include <sdp/sdpbase.h>
#include <sdp/os/sdpos.h>
#include <sdp/os/sdpfile.h>
#include <sdp/os/sdpevent.h>
#include <sdp/os/sdpmutex.h>
#include <sdp/os/sdpthread.h>
#include <sdp/net/sdpsocket.h>
#include <sdp/net/sdpnetbase.h>
#include <sdp/ose/sdpscheduler.h>
#include <sdp/net/sdpnetmanager.h>

#pragma comment(lib, "sdp.lib")

#endif

//XML
//#include "./xml/tinystr.h"
//#include "./xml/tinyxml.h"

//JRTP
#ifdef USE_JRTP_SUPPORT
#include <RTPErrors.h>
#include <RTPPacket.h>
#include <RTPSession.h>
#include <RTPSourceData.h>
#include <RTPIPv4Address.h>
#include <RTPSessionParams.h>
#include <RTPUDPv4Transmitter.h>
#endif

#ifdef SYSTEM_WIN32

#include <winsock2.h>
#include <Windows.h>
#include <Nb30.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "netapi32.lib")

#define IOC_VENDOR			0x18000000
#define _WSAIOW(x,y)		(IOC_IN|(x)|(y))
#define SIO_UDP_CONNRESET	_WSAIOW(IOC_VENDOR,12)

#define OUTC_SYSTEM_ERROR	OUTPUT_LOCAL("[NetSDK RTSP] %s %s %d Failed syserr:%d\n", __FILE__, __FUNCTION__, __LINE__, ::GetLastError());
#define OUTC_SYS_H_ERROR(x)	OUTPUT_LOCAL("[NetSDK RTSP] %s %s %d Failed:%d syserr:%d\n", __FILE__, __FUNCTION__, __LINE__, x, ::GetLastError());

#define STRCMP_CASE			strcmpi

#define NET_SOCKET			SOCKET

#elif defined(SYSTEM_LINUX)

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include "string.h"
#include "ws_comm_debug.h" //ht 2016.2.17
#define OUTC_SYSTEM_ERROR		OUTPUT_LOCAL("[NetSDK RTSP] %s %s %d Failed syserr:%d %s\n", __FILE__, __FUNCTION__, __LINE__, errno, strerror(errno));
#define OUTC_SYS_H_ERROR(x)	OUTPUT_LOCAL("[NetSDK RTSP] %s %s %d Failed:%d syserr:%d %s\n", __FILE__, __FUNCTION__, __LINE__, x, errno, strerror(errno));

#define SOCKET_ERROR		(-1)

#define STRCMP_CASE			strcasecmp

#define NET_SOCKET			int

#endif
#include "./OutputMessage.h"
#include "./BasicTypes.h"
#include "GetFrame.h"
/* CB 20160411 视频获取修改 end*/
//////////////////////////////////////////////////////////////////////////
///////							调试信息输出						//////
//////////////////////////////////////////////////////////////////////////

#if 0
/** @brief 调试信息输出方式																*/
#define OUTPUT				COutputMessage::OutputMessage

/** @brief 本地调试信息输出方式															*/
#define OUTPUT_LOCAL		COutputMessage::ControlMessage

/** @brief 调试信息输出(命令行RPC)														*/
//#define OUTC_COMMAND_RPC	COutputMessage::CommandRPCMessage
#else
/** @brief 调试信息输出方式																*/
#define OUTPUT				

/** @brief 本地调试信息输出方式															*/
#define OUTPUT_LOCAL		

#endif

/** @brief 调试信息输出(执行跟踪)														*/
#define OUTC_TRACK			OUTPUT

/** @brief 调试信息输出(警告信息)														*/
#define OUTC_WAR			OUTPUT

/** @brief 调试信息输出(失败信息)														*/
#define OUTC_FAIL			OUTPUT

/** @brief 调试信息输出(错误信息)														*/
#define OUTC_ERROR			OUTPUT

/** @brief 调试信息输出(异常信息)														*/
#define OUTC_EXCEPTION		OUTPUT

/** @brief 调试信息输出(执行跟踪)														*/
#define OUT_TRACK			OUTPUT

/** @brief 调试信息输出(警告信息)														*/
#define OUT_WAR				OUTPUT

/** @brief 调试信息输出(失败信息)														*/
#define OUT_FAIL			OUTPUT

/** @brief 调试信息输出(错误信息)														*/
#define OUT_ERROR			OUTPUT

/** @brief 调试信息输出(异常信息)														*/
#define OUT_EXCEPTION		OUTPUT

//////////////////////////////////////////////////////////////////////////
///////							调试信息实例						//////
//////////////////////////////////////////////////////////////////////////
#if 0
#define OUTC_SIMPLE_STRING(x)		OUTC_FAIL("[NetSDK RTSP] %s %s %d %s.\n", __FILE__, __FUNCTION__, __LINE__, x)
#define OUTC_SIMPLE_DWORD(x)		OUTC_FAIL("[NetSDK RTSP] %s %s %d %u.\n", __FILE__, __FUNCTION__, __LINE__, x)

#define OUTC_SIMPLE_FAILED			OUTC_SIMPLE_STRING("Failed")
#define OUTC_SIMPLE_TRACK			OUTC_SIMPLE_STRING("Track")
#define OUTC_SIMPLE_WAR			OUTC_SIMPLE_STRING("Warning")
#define OUT_SIMPLE_TRACK			OUTC_TRACK("[NetSDK RTSP] %s %s %d Track(%d).\n", __FILE__, __FUNCTION__, __LINE__, this)
#define OUT_SIMPLE_TIME			OUTC_TRACK("[NetSDK RTSP] %s %s %d Track(%d) %u.\n", __FILE__, __FUNCTION__, __LINE__, this, ApplicationLayer::CUtility::GetTickCount())
#define OUT_SIMPLE_EXPEND			OUTC_TRACK("[NetSDK RTSP] %s %s %d Track(%d) %u.\n", __FILE__, __FUNCTION__, __LINE__, this, cUtility.GetTickExpend())
#define OUTC_RTP_FAILED(x)			OUTC_TRACK("[NetSDK RTSP] %s %s %d Failed(%d) RTP[%d]:%s.\n", __FILE__, __FUNCTION__, __LINE__, this, x, RTPGetErrorString(x).c_str())
#else

#define OUTC_SIMPLE_STRING(x)		
#define OUTC_SIMPLE_DWORD(x)		

#define OUTC_SIMPLE_FAILED			
#define OUTC_SIMPLE_TRACK			
#define OUTC_SIMPLE_WAR			
#define OUT_SIMPLE_TRACK			
#define OUT_SIMPLE_TIME			
#define OUT_SIMPLE_EXPEND			
#define OUTC_RTP_FAILED(x)			
#endif

//////////////////////////////////////////////////////////////////////////
///////							接口返回值							//////
//////////////////////////////////////////////////////////////////////////
/** @brief 返回值(成功)																	*/
#define RET_SUCCESS				eErrorNone

/** @brief 返回值(失败)																	*/
#define RET_FAIL				eErrorFailed

/** @brief 无效句柄																		*/
#define HANDLE_INVALID			(void*)0xFFFFFFFF

/** @brief 无效值																		*/
#define VALUE_INVALID			0xFFFFFFFF

/** @brief 无等待锁																		*/
#define WAIT_PEEK				0x0

/** @brief 无限等待锁																	*/
#define WAIT_INFINITE			0xFFFFFFFF

/** @brief 无效媒体标识																	*/
#define MEDIA_FLAG_INVALID		(0)

/** @brief 检查返回值(成功)																*/
#define RET_CHECK_SUCCESS(x)	RET_SUCCESS == x

/** @brief 检查返回值(失败)																*/
#define RET_CHECK_FAIL(x)		RET_SUCCESS != x

//////////////////////////////////////////////////////////////////////////
///////							通用宏定义							//////
//////////////////////////////////////////////////////////////////////////
/** @brief 接口类型																		*/
#define Interface		struct

/** @brief 通用数据类型																	*/
typedef unsigned long long		ULONGLONG;
typedef unsigned long			DWORD;
typedef unsigned short			WORD;
typedef unsigned char			BYTE;

//////////////////////////////////////////////////////////////////////////
///////							通用功能定义						//////
//////////////////////////////////////////////////////////////////////////
/** @brief 无拷贝能力对象																*/
#define DISABLE_COPY_CAPABILITY_OBJECT(x)					\
	x(const x&){}											\
	virtual x& operator=(const x&){return (*this);}

/** @brief 检查并释放指针																*/
#define FREE_POINT_SAFE(x)									\
	{														\
		if (NULL != x)										\
		{													\
			delete x;										\
			x = NULL;										\
		}													\
	}

/** @brief 检查并释放数组																*/
#define FREE_ARRAY_SAFE(x)									\
	{														\
		if (NULL != x)										\
		{													\
			delete[] x;										\
			x = NULL;										\
		}													\
	}

/** @brief 获取数组元素个数																*/
#define ARRAY_ELEMENT_COUNT(x)	sizeof(x) / sizeof(x[0])

/** @brief 清空字符串数组元素															*/
#define CLEAN_ARRAY_ELEMENT(x)	memset(x, 0, sizeof(x))

/** @brief 检查指针是否为空																*/
#define CHECK_POINT_NULL(x)		NULL == x
/** @brief 检查指针是否为非空															*/
#define CHECK_POINT_NO_NULL(x)	NULL != x

/** @brief 检查句柄是否无效																*/
#define CHECK_HANDLE_INVALID(x)	HANDLE_INVALID == x
/** @brief 检查句柄是否有效																*/
#define CHECK_HANDLE_VALID(x)	HANDLE_INVALID != x

/** @brief 检查值是否无效																*/
#define CHECK_VALUE_INVALID(x)	VALUE_INVALID == x
/** @brief 检查值 是否有效																*/
#define CHECK_VALUE_VALID(x)	VALUE_INVALID != x

/** @brief 检查时间是否为无限															*/
#define CHECK_TIME_INFINITE(x)	WAIT_INFINITE == x
/** @brief 检查时间是否为有限															*/
#define CHECK_TIME_FINITE(x)	WAIT_INFINITE != x

/** @brief 检查值是否在范围内															*/
#define CHECK_VALUE_IN_AREA(x, s, b)	s < x && x < b
/** @brief 检查值是否在范围外															*/
#define CHECK_VALUE_OUT_AREA(x, s, b)	s >= x || x >= b

/** @brief 初始化元素																	*/
#define ZERO_ELEMENT(x)			::memset(x, 0, sizeof(x))

/** @brief 拷贝元素																		*/
#define COPY_ELEMENT_L(x, y)	::memcpy(x, y, sizeof(x))

/** @brief 拷贝元素																		*/
#define COPY_ELEMENT_R(x, y)	::memcpy(x, y, sizeof(y))

/** @brief 拷贝元素																		*/
#define COPY_ELEMENT(x, y)		COPY_ELEMENT_L(x, y)

inline WORD		HTONS_INLINE(WORD s)	{return (WORD)((s >> 8) | (s << 8));}
inline DWORD	HTONL_INLINE(DWORD l)	{return (l >> 24) | ((l >> 8) & 0xff00) | ((l << 8) & 0xff0000) | (l << 24);}
inline WORD		NTOHS_INLINE(WORD s)	{return (WORD)((s >> 8) | (s << 8));}
inline DWORD	NTOHL_INLINE(DWORD l)	{return (l >> 24) | ((l >> 8) & 0xff00) | ((l << 8) & 0xff0000) | (l << 24);}

//字节序处理
#ifdef SYS_BIGDIAN
//大端字节序
inline WORD		HTONS(WORD s)			{return s;}
inline DWORD	HTONL(DWORD l)			{return l;}
inline WORD		NTOHS(WORD s)			{return s;}
inline DWORD	NTOHL(DWORD l)			{return l;}

#else
//小端字节序
inline WORD		HTONS(WORD s)			{return HTONS_INLINE(s);}
inline DWORD	HTONL(DWORD l)			{return HTONL_INLINE(l);}
inline WORD		NTOHS(WORD s)			{return NTOHS_INLINE(s);}
inline DWORD	NTOHL(DWORD l)			{return NTOHL_INLINE(l);}

#endif

//是否为视频帧
#define CHECK_IS_VIDEO_FRAME(x)			(eFrameIFrames == x || eFramePFrames == x ||\
										eFrameBPFrames == x || eFrameBBPFrames == x ||\
										eFrameQCIFIFrames == x || eFramePktSQCIFIFrames == x ||\
										eFrameQCIFPFrames == x || eFramePktSQCIFPFrames == x ||\
										eFrameBIFrames == x || eFrameBBIFrames == x ||\
										eFrameSFrames == x)

//////////////////////////////////////////////////////////////////////////
///////							通用枚举值定义						//////
//////////////////////////////////////////////////////////////////////////
/*!
*  @enum	eBlockState
*  @brief	阻塞状态
*/
enum eBlockState
{
	eBlockStateBegin				= 0,	/*!< 起始值									*/
	eBlockUnlock,							/*!< 解锁									*/
	eBlockSignal,							/*!< 信号									*/
	eBlockTaskReturn,						/*!< 异步任务返回							*/
	eBlockSendReturn,						/*!< 发送返回								*/
	eBlockReceiveReturn,					/*!< 接收返回								*/
	eBlockNetWorkReturn,					/*!< 网络操作返回							*/
	eBlockLeaveApp,							/*!< 离开上层应用							*/
	eBlockWaitLock					= 100,	/*!< 等待锁定								*/
	eBlockLock						= 200,	/*!< 锁定									*/
	eBlockWaitSignal,						/*!< 等待信号								*/
	eBlockWaitTask,							/*!< 等待异步任务							*/
	eBlockSend,								/*!< 阻塞式发送								*/
	eBlockReceive,							/*!< 阻塞式接收								*/
	eBlockNetWorkIF,						/*!< 阻塞式网络操作							*/
	eBlockEnterApp,							/*!< 进入上层应用							*/
	eBlockStateEnd,							/*!< 结束值									*/
};


//////////////////////////////////////////////////////////////////////////
///////							通用结构体定义						//////
//////////////////////////////////////////////////////////////////////////

typedef struct tagMediaPacketRealStreamDepict
{
	DWORD					m_dwChannel;											/*!< 通道号							*/
	DWORD					m_dwSerial;												/*!< 包序号							*/
	eStreamMediaType			m_eType;												/*!< 流类型							*/
	DWORD					m_dwFrameType;										/*!< 帧类型							*/
	AbsoluteTime				m_cTime;	
	DWORD					m_dwReserve[DEF_RESERVE_NUM];							/*!< 保留								*/
}CMediaPacketRealStreamDepict, *PMediaPacketRealStreamDepict;

#endif



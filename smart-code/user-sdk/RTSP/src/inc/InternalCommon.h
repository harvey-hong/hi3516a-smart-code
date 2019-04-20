#ifndef INTERNAL_COMMON_H

#define INTERNAL_COMMON_H

//ϵͳ����
#if defined(_WIN32)
#define SYSTEM_WIN32
#elif defined(_LINUX)
#define SYSTEM_LINUX
#else
#error "undefined system!"
#endif

//����ƽ̨
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

//ȥ���ɺ��Եľ���
#pragma warning( disable : 4996 )
#pragma warning( disable : 4267 )

#elif defined(COMPILE_PLATFORM_GNU)

//���ڼ���������С��
#include <endian.h>

#endif

#ifdef _POWERPC_8313
	//����ϵͳ������С��
	#ifdef COMPILE_PLATFORM_VS9
		#define SYS_BIGDIAN
	#elif defined(SYSTEM_LINUX)
		#define SYS_LITDIAN
	#else
		#if defined(__i386__) || defined(__ia64__) || (defined(__alpha__) || defined(__alpha)) || defined(__arm__) || (defined(__mips__) && defined(__MIPSEL__)) || defined(__LITTLE_ENDIAN__) || (__BYTE_ORDER == __LITTLE_ENDIAN)
		#define SYS_LITDIAN		//С���ֽ���
		#else
		#define SYS_BIGDIAN		//����ֽ���
		#endif
	#endif
#endif

//�ǳ���֣�������powerpc����armƽ̨��Hxht�����ô��������
#ifdef _HISI_ARM
	#define SYS_BIGDIAN		//����ֽ���
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
/* CB 20160411 ��Ƶ��ȡ�޸� end*/
//////////////////////////////////////////////////////////////////////////
///////							������Ϣ���						//////
//////////////////////////////////////////////////////////////////////////

#if 0
/** @brief ������Ϣ�����ʽ																*/
#define OUTPUT				COutputMessage::OutputMessage

/** @brief ���ص�����Ϣ�����ʽ															*/
#define OUTPUT_LOCAL		COutputMessage::ControlMessage

/** @brief ������Ϣ���(������RPC)														*/
//#define OUTC_COMMAND_RPC	COutputMessage::CommandRPCMessage
#else
/** @brief ������Ϣ�����ʽ																*/
#define OUTPUT				

/** @brief ���ص�����Ϣ�����ʽ															*/
#define OUTPUT_LOCAL		

#endif

/** @brief ������Ϣ���(ִ�и���)														*/
#define OUTC_TRACK			OUTPUT

/** @brief ������Ϣ���(������Ϣ)														*/
#define OUTC_WAR			OUTPUT

/** @brief ������Ϣ���(ʧ����Ϣ)														*/
#define OUTC_FAIL			OUTPUT

/** @brief ������Ϣ���(������Ϣ)														*/
#define OUTC_ERROR			OUTPUT

/** @brief ������Ϣ���(�쳣��Ϣ)														*/
#define OUTC_EXCEPTION		OUTPUT

/** @brief ������Ϣ���(ִ�и���)														*/
#define OUT_TRACK			OUTPUT

/** @brief ������Ϣ���(������Ϣ)														*/
#define OUT_WAR				OUTPUT

/** @brief ������Ϣ���(ʧ����Ϣ)														*/
#define OUT_FAIL			OUTPUT

/** @brief ������Ϣ���(������Ϣ)														*/
#define OUT_ERROR			OUTPUT

/** @brief ������Ϣ���(�쳣��Ϣ)														*/
#define OUT_EXCEPTION		OUTPUT

//////////////////////////////////////////////////////////////////////////
///////							������Ϣʵ��						//////
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
///////							�ӿڷ���ֵ							//////
//////////////////////////////////////////////////////////////////////////
/** @brief ����ֵ(�ɹ�)																	*/
#define RET_SUCCESS				eErrorNone

/** @brief ����ֵ(ʧ��)																	*/
#define RET_FAIL				eErrorFailed

/** @brief ��Ч���																		*/
#define HANDLE_INVALID			(void*)0xFFFFFFFF

/** @brief ��Чֵ																		*/
#define VALUE_INVALID			0xFFFFFFFF

/** @brief �޵ȴ���																		*/
#define WAIT_PEEK				0x0

/** @brief ���޵ȴ���																	*/
#define WAIT_INFINITE			0xFFFFFFFF

/** @brief ��Чý���ʶ																	*/
#define MEDIA_FLAG_INVALID		(0)

/** @brief ��鷵��ֵ(�ɹ�)																*/
#define RET_CHECK_SUCCESS(x)	RET_SUCCESS == x

/** @brief ��鷵��ֵ(ʧ��)																*/
#define RET_CHECK_FAIL(x)		RET_SUCCESS != x

//////////////////////////////////////////////////////////////////////////
///////							ͨ�ú궨��							//////
//////////////////////////////////////////////////////////////////////////
/** @brief �ӿ�����																		*/
#define Interface		struct

/** @brief ͨ����������																	*/
typedef unsigned long long		ULONGLONG;
typedef unsigned long			DWORD;
typedef unsigned short			WORD;
typedef unsigned char			BYTE;

//////////////////////////////////////////////////////////////////////////
///////							ͨ�ù��ܶ���						//////
//////////////////////////////////////////////////////////////////////////
/** @brief �޿�����������																*/
#define DISABLE_COPY_CAPABILITY_OBJECT(x)					\
	x(const x&){}											\
	virtual x& operator=(const x&){return (*this);}

/** @brief ��鲢�ͷ�ָ��																*/
#define FREE_POINT_SAFE(x)									\
	{														\
		if (NULL != x)										\
		{													\
			delete x;										\
			x = NULL;										\
		}													\
	}

/** @brief ��鲢�ͷ�����																*/
#define FREE_ARRAY_SAFE(x)									\
	{														\
		if (NULL != x)										\
		{													\
			delete[] x;										\
			x = NULL;										\
		}													\
	}

/** @brief ��ȡ����Ԫ�ظ���																*/
#define ARRAY_ELEMENT_COUNT(x)	sizeof(x) / sizeof(x[0])

/** @brief ����ַ�������Ԫ��															*/
#define CLEAN_ARRAY_ELEMENT(x)	memset(x, 0, sizeof(x))

/** @brief ���ָ���Ƿ�Ϊ��																*/
#define CHECK_POINT_NULL(x)		NULL == x
/** @brief ���ָ���Ƿ�Ϊ�ǿ�															*/
#define CHECK_POINT_NO_NULL(x)	NULL != x

/** @brief ������Ƿ���Ч																*/
#define CHECK_HANDLE_INVALID(x)	HANDLE_INVALID == x
/** @brief ������Ƿ���Ч																*/
#define CHECK_HANDLE_VALID(x)	HANDLE_INVALID != x

/** @brief ���ֵ�Ƿ���Ч																*/
#define CHECK_VALUE_INVALID(x)	VALUE_INVALID == x
/** @brief ���ֵ �Ƿ���Ч																*/
#define CHECK_VALUE_VALID(x)	VALUE_INVALID != x

/** @brief ���ʱ���Ƿ�Ϊ����															*/
#define CHECK_TIME_INFINITE(x)	WAIT_INFINITE == x
/** @brief ���ʱ���Ƿ�Ϊ����															*/
#define CHECK_TIME_FINITE(x)	WAIT_INFINITE != x

/** @brief ���ֵ�Ƿ��ڷ�Χ��															*/
#define CHECK_VALUE_IN_AREA(x, s, b)	s < x && x < b
/** @brief ���ֵ�Ƿ��ڷ�Χ��															*/
#define CHECK_VALUE_OUT_AREA(x, s, b)	s >= x || x >= b

/** @brief ��ʼ��Ԫ��																	*/
#define ZERO_ELEMENT(x)			::memset(x, 0, sizeof(x))

/** @brief ����Ԫ��																		*/
#define COPY_ELEMENT_L(x, y)	::memcpy(x, y, sizeof(x))

/** @brief ����Ԫ��																		*/
#define COPY_ELEMENT_R(x, y)	::memcpy(x, y, sizeof(y))

/** @brief ����Ԫ��																		*/
#define COPY_ELEMENT(x, y)		COPY_ELEMENT_L(x, y)

inline WORD		HTONS_INLINE(WORD s)	{return (WORD)((s >> 8) | (s << 8));}
inline DWORD	HTONL_INLINE(DWORD l)	{return (l >> 24) | ((l >> 8) & 0xff00) | ((l << 8) & 0xff0000) | (l << 24);}
inline WORD		NTOHS_INLINE(WORD s)	{return (WORD)((s >> 8) | (s << 8));}
inline DWORD	NTOHL_INLINE(DWORD l)	{return (l >> 24) | ((l >> 8) & 0xff00) | ((l << 8) & 0xff0000) | (l << 24);}

//�ֽ�����
#ifdef SYS_BIGDIAN
//����ֽ���
inline WORD		HTONS(WORD s)			{return s;}
inline DWORD	HTONL(DWORD l)			{return l;}
inline WORD		NTOHS(WORD s)			{return s;}
inline DWORD	NTOHL(DWORD l)			{return l;}

#else
//С���ֽ���
inline WORD		HTONS(WORD s)			{return HTONS_INLINE(s);}
inline DWORD	HTONL(DWORD l)			{return HTONL_INLINE(l);}
inline WORD		NTOHS(WORD s)			{return NTOHS_INLINE(s);}
inline DWORD	NTOHL(DWORD l)			{return NTOHL_INLINE(l);}

#endif

//�Ƿ�Ϊ��Ƶ֡
#define CHECK_IS_VIDEO_FRAME(x)			(eFrameIFrames == x || eFramePFrames == x ||\
										eFrameBPFrames == x || eFrameBBPFrames == x ||\
										eFrameQCIFIFrames == x || eFramePktSQCIFIFrames == x ||\
										eFrameQCIFPFrames == x || eFramePktSQCIFPFrames == x ||\
										eFrameBIFrames == x || eFrameBBIFrames == x ||\
										eFrameSFrames == x)

//////////////////////////////////////////////////////////////////////////
///////							ͨ��ö��ֵ����						//////
//////////////////////////////////////////////////////////////////////////
/*!
*  @enum	eBlockState
*  @brief	����״̬
*/
enum eBlockState
{
	eBlockStateBegin				= 0,	/*!< ��ʼֵ									*/
	eBlockUnlock,							/*!< ����									*/
	eBlockSignal,							/*!< �ź�									*/
	eBlockTaskReturn,						/*!< �첽���񷵻�							*/
	eBlockSendReturn,						/*!< ���ͷ���								*/
	eBlockReceiveReturn,					/*!< ���շ���								*/
	eBlockNetWorkReturn,					/*!< �����������							*/
	eBlockLeaveApp,							/*!< �뿪�ϲ�Ӧ��							*/
	eBlockWaitLock					= 100,	/*!< �ȴ�����								*/
	eBlockLock						= 200,	/*!< ����									*/
	eBlockWaitSignal,						/*!< �ȴ��ź�								*/
	eBlockWaitTask,							/*!< �ȴ��첽����							*/
	eBlockSend,								/*!< ����ʽ����								*/
	eBlockReceive,							/*!< ����ʽ����								*/
	eBlockNetWorkIF,						/*!< ����ʽ�������							*/
	eBlockEnterApp,							/*!< �����ϲ�Ӧ��							*/
	eBlockStateEnd,							/*!< ����ֵ									*/
};


//////////////////////////////////////////////////////////////////////////
///////							ͨ�ýṹ�嶨��						//////
//////////////////////////////////////////////////////////////////////////

typedef struct tagMediaPacketRealStreamDepict
{
	DWORD					m_dwChannel;											/*!< ͨ����							*/
	DWORD					m_dwSerial;												/*!< �����							*/
	eStreamMediaType			m_eType;												/*!< ������							*/
	DWORD					m_dwFrameType;										/*!< ֡����							*/
	AbsoluteTime				m_cTime;	
	DWORD					m_dwReserve[DEF_RESERVE_NUM];							/*!< ����								*/
}CMediaPacketRealStreamDepict, *PMediaPacketRealStreamDepict;

#endif



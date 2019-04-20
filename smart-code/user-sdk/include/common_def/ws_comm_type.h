#ifndef _WS_COMM_TYPE_H_
#define _WS_COMM_TYPE_H_

typedef unsigned char           WS_U8;
typedef unsigned char           WS_UCHAR;
typedef unsigned short          WS_U16;
typedef unsigned int            WS_U32;

typedef signed char             WS_S8;
typedef short                   WS_S16;
typedef int                     WS_S32;

typedef unsigned long long      WS_U64;
typedef long long               WS_S64;

typedef char                    WS_CHAR;
typedef char                   *WS_PCHAR;

typedef float                   WS_FLOAT;
typedef double                  WS_DOUBLE;
typedef void                    WS_VOID;

typedef unsigned long           WS_SIZE_T;
typedef unsigned long           WS_LENGTH_T;

typedef enum
{
    WS_FALSE    = 0,
    WS_TRUE     = 1,
} WS_BOOL;

typedef unsigned int    WS_USR_HAND;        //登陆用户句柄
typedef unsigned int    WS_PARSER_ID;   //文件解析器的票
typedef unsigned int    WS_SQLITE_PARSER_ID;   //sqlite文件解析器的票  		
typedef unsigned int    ws_rec_table_hand; // add by longzhou 20150801		返回给调用者
typedef unsigned int    ws_snap_table_hand;// add by longzhou 20150801		返回给调用者
typedef unsigned int	ws_log_table_hand;	// add by ljx date 20151109 

typedef unsigned int    WS_IPV4_ADDR;
typedef unsigned int    WS_SUB_MASK;
typedef unsigned int    WS_GATE_WAY;

//liujl change start-end at 20170905
typedef enum
{
	eProtocolTypeP2p,
	eProtocolTypePrivate,
}WS_PROTOCOL;

#ifndef NULL
#define NULL             0L
#endif

#ifdef  _SUPPORT_SYSLOG_
typedef int     SyslogHander;
#endif

#endif //#ifndef _WS_NVR_TYPE_H_


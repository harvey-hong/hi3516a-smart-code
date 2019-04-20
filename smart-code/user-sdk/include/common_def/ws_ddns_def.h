#ifndef _WS_DDNS_DEF_H__
#define _WS_DDNS_DEF_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include "ws_common.h"
#include "ws_comm_type.h"

#define error_string strerror(errno)
#define BUFFER_SIZE (2*1024-1)
#define WS_DDNS_MAC_STRING_LEN sizeof("xx-xx-xx-xx-xx-xx")
#define WS_DDNS_SER_PORT   8086

typedef enum
{
    WS_DDNS_SUCCESS = 0,	//函数成功

    WS_ERR_GET_MAC = 				 0xdd000000,
    WS_ERR_MAC_INVALID = 			 0xdd000001,
    WS_ERR_GET_IP = 				 0xdd000002,
    WS_ERR_CREAT_SOCKET =			 0xdd000003,
    WS_ERR_CONNECT_SERVER =			 0xdd000004,
    WS_ERR_SEND_FAIL =               0xdd000005,
    WS_ERR_RECV_FAIL =               0xdd000006,
    WS_ERR_FIND_FAIL =               0xdd000007, 
    WS_ERR_CREATE_THREAD_FAIL =      0xdd000008,
    WS_ERR_DOMAIN_INVALID =			 0xdd000009,
    WS_ERR_ALLOC_LESS_SIZE =         0xdd00000a,
    WS_ERR_NOT_START_DDNS =          0xdd00000b,

    ADDNEW =                         0xdd010002,    //添加域名成功
    UPDATE_DNS =                         0xdd010003,    //更新域名成功  /* hzg enum name conflict with HTTP  */
    INVALIDNAME =                    0xdd010004,	//非法域名
    EXISTDNS =                       0xdd010004,	//域名冲突
    SYSFAIL =                        0xdd010006,	//服务器数据库异常
    CONNECT_BREAK =                  0xdd010007,	//连接断开
    STATUS_UNKNOWN = 0xffffffff,
}WS_DDNS_ERR;

typedef enum
{
	CONNECT_OK,
	CONNECT_ING,
	CONNECT_UNINIT,
    CONNECT_FAIL,     
	CONNECT_CONFLICT,
	INVALID_DOMAINNAME,
	SERVER_ERROR,
	CONNECT_STATUS_BREAk,
	CONNECT_STATUS_UNKNOW,
	
}connect_status;

typedef struct
{
	char sdomain[64];
	char sip[32];
}w_server_info;

typedef  int (*DDNSCallBack)(connect_status w_connect_status);

#endif

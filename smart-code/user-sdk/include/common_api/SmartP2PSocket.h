/**********************************************************************
Copyright (c) 2016 Wuhan branch of shenzhen wiseview technology co.ltd.
All Rights Reserved
No portions of this material may be reproduced in any form without the
written permission of:
Wuhan SmartTech Co., Ltd.
#09-1806, #62, GuangGu Road
Wuhan, PR China 430000
All information contained in this document is Wuhan SmartTech Co., Ltd.
company private, proprietary, and trade secret.
***********************************************************************
Filename: SmartP2PSocket.h
Author: hzg
Date: 2016-08-10
Description: 
 
Histroy: 
    1.  Modification: 
        Author: 
        Date: 
  
    2.  
***********************************************************************/
 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include<string.h>
#include<net/if.h>
#include<signal.h>
#include<sys/time.h>
#include<iostream>

#ifndef SMARTP2PSOCKET_H_
#define SMARTP2PSOCKET_H_

#ifdef __cplusplus
extern "C"{
#endif

#define FOX_DLL_EXPORT extern "C" __attribute__((visibility("default")))

typedef enum
{
    SP2P_SUCCESS = 0,

    // memory pointer operation error
    SP2P_MEM_NEW_ERR = 0x00001000,  /* new malloc failure */
    SP2P_MEM_POINTER_ERR = (SP2P_MEM_NEW_ERR + 1),  /* checked pointer is NULL  */
    SP2P_MEM_NOT_ENOUGH_ERR = (SP2P_MEM_NEW_ERR + 2),  /* buffer or memeory Not enough  */

    // socket operation error
    SP2P_SOCK_NEW_FAILURE = 0x00002000,   /* create socket failure  */
    SP2P_SOCK_SET_OPT_ERR = (SP2P_SOCK_NEW_FAILURE + 1),
    SP2P_SOCK_SEND_TIMEOUT_ERR = (SP2P_SOCK_NEW_FAILURE + 2),
    SP2P_SOCK_RECV_TIMEOUT_ERR = (SP2P_SOCK_NEW_FAILURE + 3),
    SP2P_SOCK_BIND_FAILURE = (SP2P_SOCK_NEW_FAILURE + 4),
    SP2P_SOCK_SEND_FAILURE = (SP2P_SOCK_NEW_FAILURE + 5),
    SP2P_SOCK_RECV_FAILURE = (SP2P_SOCK_NEW_FAILURE + 6),
    SP2P_SOCK_ACCEPT_FAILURE = (SP2P_SOCK_NEW_FAILURE + 7),
    SP2P_SOCK_CONNECT_FAILURE = (SP2P_SOCK_NEW_FAILURE + 8),
    SP2P_SOCK_ARP_REQUEST_FAILURE = (SP2P_SOCK_NEW_FAILURE + 9),

    SP2P_ERR_INVALID_ARGUMENT,
    SP2P_ERR_BUFFER_TO_SMALL, //add by qqy, at 2017-05-05 10:29:55
    SP2P_RET_UNKNOWN_ERR,
} SP2P_ERR;



#define DEFAULT_VALUE 0
#define INVALID_SOCKET -1
/*
*功能：		创建UDP客户端socket。..
*输入参数：	..
*输出参数：	client_socket:	保存创建好的客户端socket、，创建失败，则返回-1..
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码..
*/
SP2P_ERR _client_socket_(int &client_socket);

/*
*功能：		创建UDP客户端socket，并设置缓冲区。..
*输入参数：	snd_buf_size:发送缓冲区大小，若小于等于0，则不设置..
		rcv_buf_size:接受缓冲区大小，若小于等于0，则不设置..
*输出参数：	client_socket:	保存创建好的客户端socket、，创建失败，则返回-1..
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码..
*/
FOX_DLL_EXPORT SP2P_ERR client_socket_buf(int snd_buf_size,int rcv_buf_size,int &cli_socket);

/*
*功能：		创建UDP客户端socket，并设置超时时间。..
*输入参数：	ms_snd_timeout:发送超时时间，单位毫秒，若小于0，则不设置，等于0，则为无限等待..
		ms_rcv_timeout:接受超时时间，单位毫秒，若小于0，则不设置，等于0，则为无限等待..
*输出参数：	client_socket:	保存创建好的客户端socket、，创建失败，则返回-1..
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR client_socket_timeout(int ms_snd_timeout,int ms_rcv_timeout,int &cli_socket);


/*
*功能：		创建UDP客户端socket，并设置地址重用。...........
*输入参数：	breuse:是否重用地址，0值表示重用，非0为不重用...............
*输出参数：	client_socket:	保存创建好的客户端socket、，创建失败，则返回-1....
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码....
*/
FOX_DLL_EXPORT SP2P_ERR client_socket_reuseaddr(int breuse,int &cli_socket);

#ifdef SO_REUSEPORT
/*
*功能：		创建UDP客户端socket，并设置端口重用。.....
*输入参数：	breuse:是否重用地址，0值表示重用，非0为不重用...
*输出参数：	client_socket:	保存创建好的客户端socket、，创建失败，则返回-1...
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR client_socket_reuseport(int breuse,int &cli_socket);
#endif


/*
*功能：		创建UDP客户端socket，并设置缓冲区、超时、地址重用，端口重用以及阻塞标志。
*输入参数：	snd_buf_size:发送缓冲区大小，若小于等于0，则不设置..
		rcv_buf_size:接受缓冲区大小，若小于等于0，则不设置..
		ms_snd_timeout:发送超时时间，单位毫秒，若小于0，则不设置，等于0，则为无限等待
		ms_rcv_timeout:接受超时时间，单位毫秒，若小于0，则不设置，等于0，则为无限等待
		addr_reuse:是否重用地址，0值表示重用，非0为不重用..
		port_reuse:是否重用端口，0值表示重用，非0为不重用...
		nonblock:是否设置非阻塞模式，0值表示阻塞模式，非0为非阻塞模式..
*输出参数：	client_socket:	保存创建好的客户端socket、，创建失败，则返回-1..
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR client_socket(int snd_buf_size,int rcv_buf_size,int ms_snd_timeout,int ms_rcv_timeout,\
						 int addr_reuse,int port_reuse,int nonblock,int &cli_socket);


/*
*功能：		创建UDP服务短端socket，并绑定到给定端口..
*输入参数：	ip:		服务器ip地址，点分十进制字符串形式..
		port：		服务器端口..
*输出参数：	svr_socket:	保存创建好的客户端socket、，创建失败，则返回-1..
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
SP2P_ERR _server_socket_(const char * ip,short port,int &svr_socket);

/*
*功能：		创建UDP服务短端socket，绑定到给定地址，设置缓冲区大小...
*输入参数：	ip:		服务器ip地址，点分十进制字符串形式...
		port：		服务器端口...
		snd_buf_size:发送缓冲区大小，若小于等于0，则不设置...
		rcv_buf_size:接受缓冲区大小，若小于等于0，则不设置...
*输出参数：	svr_socket:	保存创建好的客户端socket，创建失败，则返回-1...
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR server_socket_buf(const char * ip,short port,int snd_buf_size,int rcv_buf_size,int &svr_socket);


/*
*功能：		创建UDP服务短端socket，绑定到给定地址，设置超时时间...
*输入参数：	ip:		服务器ip地址，点分十进制字符串形式...
		port：		服务器端口...
		ms_snd_timeout:发送超时时间，单位毫秒，若小于0，则不设置，等于0，则为无限等待...
		ms_rcv_timeout:接受超时时间，单位毫秒，若小于0，则不设置，等于0，则为无限等待...
*输出参数：	svr_socket:	保存创建好的客户端socket，创建失败，则返回-1...
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR server_socket_timeout(const char * ip,short port,int ms_snd_buf,int ms_rcv_timeout,int &svr_socket);


/*
*功能：		创建UDP服务短端socket，绑定到给定地址，设置地址重用...
*输入参数：	ip:		服务器ip地址，点分十进制字符串形式...
		port：		服务器端口...
		breuse:是否重用地址，0值表示重用，非0为不重用...
*输出参数：	svr_socket:	保存创建好的客户端socket，创建失败，则返回-1...
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR server_socket_reuseaddr(const char * ip,short port,int breuse,int &svr_socket);
#ifdef SO_REUSEPORT
/*
*功能：		创建UDP服务短端socket，绑定到给定地址，设置端口重用...
*输入参数：	ip:		服务器ip地址，点分十进制字符串形式...
		port：		服务器端口	...
		breuse:是否重用地址，0值表示重用，非0为不重用...
*输出参数：	svr_socket:	保存创建好的客户端socket，创建失败，则返回-1...
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR server_socket_reuseport(const char * ip,short port,int breuse,int &svr_socket);
#endif

/*
*功能：		创建UDP服务短端socket，绑定到给定地址，设置阻塞模式...
*输入参数：	ip:		服务器ip地址，点分十进制字符串形式...
		port：		服务器端口...
		nonblock:是否设置非阻塞模式，0值表示阻塞模式，非0为非阻塞模式...
*输出参数：	svr_socket:	保存创建好的客户端socket，创建失败，则返回-1...
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR server_socket_nonblock(const char * ip,short port,int nonblock,int &svr_socket);

/*
*功能：		创建UDP服务短端socket，绑定到给定地址，设置缓冲区、超时、阻塞、地址重用，端口重用等...
*输入参数：	ip:		服务器ip地址，点分十进制字符串形式...
		port：		服务器端口...
		snd_buf_size	发送缓冲区大小，若小于等于0，则不设置...
		rcv_buf_size:	接受缓冲区大小，若小于等于0，则不设置...
		ms_snd_timeout:	发送超时时间，单位毫秒，若小于0，则不设置，等于0，则为无限等待...
		ms_rcv_timeout:	接受超时时间，单位毫秒，若小于0，则不设置，等于0，则为无限等待...
		addr_reuse:	是否重用地址，0值表示重用，非0为不重用...
		port_reuse:	是否重用端口，0值表示重用，非0为不重用...
		nonblock:	是否设置非阻塞模式，0值表示阻塞模式，非0为非阻塞模式...
*输出参数：	svr_socket:	保存创建好的客户端socket，创建失败，则返回-1...
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR service_socket(const char * ip,short port,int snd_buf_size,int rcv_buf_size,int ms_snd_timeout,\
							int ms_rcv_timeout,	int addr_reuse,int port_reuse,int nonblock,int &svr_socket);


/*
*功能：		设置socket的缓冲区大小属性...
*输入参数：	sock:		需要设置属性的socket...
		snd_buf_size	发送缓冲区大小，若小于等于0，则不设置...
		rcv_buf_size:	接受缓冲区大小，若小于等于0，则不设置接受缓冲区大小，若小于等于0，则不设置...
*输出参数：	...
*输出参数：	
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR set_buf_size(int sock,int snd_buf_size,int rcv_buf_size);

/*
*功能：		获取socket的缓冲区大小属性...
*输入参数：	sock:		需要设置属性的socket...
*输出参数：	snd_buf_size	发送缓冲区大小......
		rcv_buf_size:	接受缓冲区大小...
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR get_buf_size(int sock,int* snd_buf_size,int* rcv_buf_size);


/*
*功能：		设置socket的缓冲区大小属性...
*输入参数：	sock:		需要设置属性的socket...
		ms_snd_timeout:	发送超时时间，单位毫秒，若小于0，则不设置，等于0，则为无限等待...
		ms_rcv_timeout:	接受超时时间，单位毫秒，若小于0，则不设置，等于0，则为无限等待置...
*输出参数：	
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR set_timeout(int sock,int ms_snd_timeout,int ms_rcv_timeout);


/*
*功能：		获取socket的超时属性...
*输入参数：	sock:		需要设置属性的socket...
*输出参数：	ms_snd_timeout:	发送超时时间，单位毫秒...
		ms_rcv_timeout:	接受超时时间，单位毫秒...
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR get_timeout(int sock,int* ms_snd_timeout,int* ms_rcv_timeout);


/*
*功能：		设置socket的地址重用属性...
*输入参数：	sock:		需要设置属性的socket...
		breuse:是否重用地址，0值表示重用，非0为不重用...
*输出参数：	
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR set_addr_reuse(int sock,int breuse);


/*
*功能：		获取socket的地址重用属性...
*输入参数：	sock:		需要设置属性的socket...
*输出参数：	breuse:是否重用地址...
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR get_addr_reuse(int sock,int* breuse);

#ifdef SO_REUSEPORT
/*
*功能：		设置socket的端口重用属性...
*输入参数：	sock:		需要设置属性的socket...
		breuse:是否重用地址，0值表示重用，非0为不重用...
*输出参数：	
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR set_port_reuse(int sock,int breuse);

/*
*功能：		获取socket的端口重用属性...
*输入参数：	sock:		需要设置属性的socket
*输出参数：	breuse:  	是否重用地址，0值表示重用，非0为不重用
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR get_port_reuse(int sock,int* breuse);
#endif


/*
*功能：		在socket上向制定地址发送数据
*输入参数：	sock:		需要设置属性的socket
		msg:		消息地址首指针
		msg_size:	消息的长度
		dstip:		目标ip地址
		dstport:	目标端口
*输出参数：	sent_size：	发送的消息长度
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR send_msg(int sock,const char * msg,int msg_size,const char * dstip, int dstport,int* sent_size);

FOX_DLL_EXPORT SP2P_ERR send_msgs(int sock,  iovec *iovec, int iovlen,const char *dstip, int  dstport, int *sent_size);
/*
*功能：		接受socket上的消息
*输入参数：	sock:		需要设置属性的socket
		buf_len:	接受缓冲区的大小
*输出参数：	buf：		接受缓冲区首指针
		rcv_szie:	接受的消息的长度
		srcip：		消息来源ip地址
		short:		消息源地址端口号
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR recv_msg(int sock,char * buf,int buf_len,int* rcv_size,char* srcip,int *srcport);


/*
*功能：		设置socket的非阻塞属性
*输入参数：	sock:		需要设置属性的socket
		nonblock:	是否设置非阻塞模式，0值表示阻塞模式，非0为非阻塞模式
*输出参数：	
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR set_nonblock(int sock,int nonblock);


/*
*功能：		获取socket的非阻塞属性
*输入参数：	sock:		需要设置属性的socket
*输出参数：	nonblock:	非阻塞模式标志，0值表示阻塞模式，非0为非阻塞模式
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR get_nonblock(int sock,int* nonblock);


/*
*功能：		关闭socket
*输入参数：	sock:		需要设置属性的socket
*输出参数：	
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR closesocket(int sock);


/*
*功能：		解析域名
*输入参数：	SerDomain:		需要解析的域名
                    len                        缓冲区长度
*输出参数：	Serip                   解析后保存的缓冲区
*返回值：	成功返回SP2P_SUCCESS,失败则返回相应的错误代码...
*/
FOX_DLL_EXPORT SP2P_ERR Domain_Resolution(char * SerDomain, char* Serip, int len);


/* hzg 20161123 added function for get local port start end*/
FOX_DLL_EXPORT SP2P_ERR get_local_listen_ip_port(int sockFd, char *local_IP, int *listen_port);


FOX_DLL_EXPORT SP2P_ERR TCPStartServerSocket(const char* pServerIP, int ListemPort, int &ServerSocketFd);

FOX_DLL_EXPORT SP2P_ERR TCPAcceptConnection(int ServerSocketFd, int TimeoutMS, int &SocketFd, char* pClientIP,  int &ClientPort);

FOX_DLL_EXPORT SP2P_ERR TCPConnect(const char* pServerIP, int ServerPort, int TimeoutMS, int &ClientSocketFD);

FOX_DLL_EXPORT SP2P_ERR TCPSendData(int SocketFd, const char* pBuff, const int BufLen, int TimeoutMS);

FOX_DLL_EXPORT SP2P_ERR TCPReceiveData(int SocketFd, char* pBuff, int &BufLen, int TimeoutMS);

FOX_DLL_EXPORT SP2P_ERR TCPPeekReceiveData(int SocketFd, char* pBuff, int &BufLen);

FOX_DLL_EXPORT SP2P_ERR TCPSetSocketNoDelay(int SocketFd);

//liujl change start-end at 20170904
FOX_DLL_EXPORT SP2P_ERR GetSocketAddress(int SocketFd, char *ip);

FOX_DLL_EXPORT SP2P_ERR GetPeerIpAndPort(int SocketFd, char* ip, int ipLen, int &port);

FOX_DLL_EXPORT SP2P_ERR GetPeerMac(int SocketFd,char *mac);
#ifdef __cplusplus
}
#endif

#endif /* SMARTP2PSOCKET_H_ */

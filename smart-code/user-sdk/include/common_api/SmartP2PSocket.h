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
*���ܣ�		����UDP�ͻ���socket��..
*���������	..
*���������	client_socket:	���洴���õĿͻ���socket��������ʧ�ܣ��򷵻�-1..
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������..
*/
SP2P_ERR _client_socket_(int &client_socket);

/*
*���ܣ�		����UDP�ͻ���socket�������û�������..
*���������	snd_buf_size:���ͻ�������С����С�ڵ���0��������..
		rcv_buf_size:���ܻ�������С����С�ڵ���0��������..
*���������	client_socket:	���洴���õĿͻ���socket��������ʧ�ܣ��򷵻�-1..
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������..
*/
FOX_DLL_EXPORT SP2P_ERR client_socket_buf(int snd_buf_size,int rcv_buf_size,int &cli_socket);

/*
*���ܣ�		����UDP�ͻ���socket�������ó�ʱʱ�䡣..
*���������	ms_snd_timeout:���ͳ�ʱʱ�䣬��λ���룬��С��0�������ã�����0����Ϊ���޵ȴ�..
		ms_rcv_timeout:���ܳ�ʱʱ�䣬��λ���룬��С��0�������ã�����0����Ϊ���޵ȴ�..
*���������	client_socket:	���洴���õĿͻ���socket��������ʧ�ܣ��򷵻�-1..
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR client_socket_timeout(int ms_snd_timeout,int ms_rcv_timeout,int &cli_socket);


/*
*���ܣ�		����UDP�ͻ���socket�������õ�ַ���á�...........
*���������	breuse:�Ƿ����õ�ַ��0ֵ��ʾ���ã���0Ϊ������...............
*���������	client_socket:	���洴���õĿͻ���socket��������ʧ�ܣ��򷵻�-1....
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������....
*/
FOX_DLL_EXPORT SP2P_ERR client_socket_reuseaddr(int breuse,int &cli_socket);

#ifdef SO_REUSEPORT
/*
*���ܣ�		����UDP�ͻ���socket�������ö˿����á�.....
*���������	breuse:�Ƿ����õ�ַ��0ֵ��ʾ���ã���0Ϊ������...
*���������	client_socket:	���洴���õĿͻ���socket��������ʧ�ܣ��򷵻�-1...
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR client_socket_reuseport(int breuse,int &cli_socket);
#endif


/*
*���ܣ�		����UDP�ͻ���socket�������û���������ʱ����ַ���ã��˿������Լ�������־��
*���������	snd_buf_size:���ͻ�������С����С�ڵ���0��������..
		rcv_buf_size:���ܻ�������С����С�ڵ���0��������..
		ms_snd_timeout:���ͳ�ʱʱ�䣬��λ���룬��С��0�������ã�����0����Ϊ���޵ȴ�
		ms_rcv_timeout:���ܳ�ʱʱ�䣬��λ���룬��С��0�������ã�����0����Ϊ���޵ȴ�
		addr_reuse:�Ƿ����õ�ַ��0ֵ��ʾ���ã���0Ϊ������..
		port_reuse:�Ƿ����ö˿ڣ�0ֵ��ʾ���ã���0Ϊ������...
		nonblock:�Ƿ����÷�����ģʽ��0ֵ��ʾ����ģʽ����0Ϊ������ģʽ..
*���������	client_socket:	���洴���õĿͻ���socket��������ʧ�ܣ��򷵻�-1..
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR client_socket(int snd_buf_size,int rcv_buf_size,int ms_snd_timeout,int ms_rcv_timeout,\
						 int addr_reuse,int port_reuse,int nonblock,int &cli_socket);


/*
*���ܣ�		����UDP����̶�socket�����󶨵������˿�..
*���������	ip:		������ip��ַ�����ʮ�����ַ�����ʽ..
		port��		�������˿�..
*���������	svr_socket:	���洴���õĿͻ���socket��������ʧ�ܣ��򷵻�-1..
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
SP2P_ERR _server_socket_(const char * ip,short port,int &svr_socket);

/*
*���ܣ�		����UDP����̶�socket���󶨵�������ַ�����û�������С...
*���������	ip:		������ip��ַ�����ʮ�����ַ�����ʽ...
		port��		�������˿�...
		snd_buf_size:���ͻ�������С����С�ڵ���0��������...
		rcv_buf_size:���ܻ�������С����С�ڵ���0��������...
*���������	svr_socket:	���洴���õĿͻ���socket������ʧ�ܣ��򷵻�-1...
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR server_socket_buf(const char * ip,short port,int snd_buf_size,int rcv_buf_size,int &svr_socket);


/*
*���ܣ�		����UDP����̶�socket���󶨵�������ַ�����ó�ʱʱ��...
*���������	ip:		������ip��ַ�����ʮ�����ַ�����ʽ...
		port��		�������˿�...
		ms_snd_timeout:���ͳ�ʱʱ�䣬��λ���룬��С��0�������ã�����0����Ϊ���޵ȴ�...
		ms_rcv_timeout:���ܳ�ʱʱ�䣬��λ���룬��С��0�������ã�����0����Ϊ���޵ȴ�...
*���������	svr_socket:	���洴���õĿͻ���socket������ʧ�ܣ��򷵻�-1...
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR server_socket_timeout(const char * ip,short port,int ms_snd_buf,int ms_rcv_timeout,int &svr_socket);


/*
*���ܣ�		����UDP����̶�socket���󶨵�������ַ�����õ�ַ����...
*���������	ip:		������ip��ַ�����ʮ�����ַ�����ʽ...
		port��		�������˿�...
		breuse:�Ƿ����õ�ַ��0ֵ��ʾ���ã���0Ϊ������...
*���������	svr_socket:	���洴���õĿͻ���socket������ʧ�ܣ��򷵻�-1...
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR server_socket_reuseaddr(const char * ip,short port,int breuse,int &svr_socket);
#ifdef SO_REUSEPORT
/*
*���ܣ�		����UDP����̶�socket���󶨵�������ַ�����ö˿�����...
*���������	ip:		������ip��ַ�����ʮ�����ַ�����ʽ...
		port��		�������˿�	...
		breuse:�Ƿ����õ�ַ��0ֵ��ʾ���ã���0Ϊ������...
*���������	svr_socket:	���洴���õĿͻ���socket������ʧ�ܣ��򷵻�-1...
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR server_socket_reuseport(const char * ip,short port,int breuse,int &svr_socket);
#endif

/*
*���ܣ�		����UDP����̶�socket���󶨵�������ַ����������ģʽ...
*���������	ip:		������ip��ַ�����ʮ�����ַ�����ʽ...
		port��		�������˿�...
		nonblock:�Ƿ����÷�����ģʽ��0ֵ��ʾ����ģʽ����0Ϊ������ģʽ...
*���������	svr_socket:	���洴���õĿͻ���socket������ʧ�ܣ��򷵻�-1...
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR server_socket_nonblock(const char * ip,short port,int nonblock,int &svr_socket);

/*
*���ܣ�		����UDP����̶�socket���󶨵�������ַ�����û���������ʱ����������ַ���ã��˿����õ�...
*���������	ip:		������ip��ַ�����ʮ�����ַ�����ʽ...
		port��		�������˿�...
		snd_buf_size	���ͻ�������С����С�ڵ���0��������...
		rcv_buf_size:	���ܻ�������С����С�ڵ���0��������...
		ms_snd_timeout:	���ͳ�ʱʱ�䣬��λ���룬��С��0�������ã�����0����Ϊ���޵ȴ�...
		ms_rcv_timeout:	���ܳ�ʱʱ�䣬��λ���룬��С��0�������ã�����0����Ϊ���޵ȴ�...
		addr_reuse:	�Ƿ����õ�ַ��0ֵ��ʾ���ã���0Ϊ������...
		port_reuse:	�Ƿ����ö˿ڣ�0ֵ��ʾ���ã���0Ϊ������...
		nonblock:	�Ƿ����÷�����ģʽ��0ֵ��ʾ����ģʽ����0Ϊ������ģʽ...
*���������	svr_socket:	���洴���õĿͻ���socket������ʧ�ܣ��򷵻�-1...
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR service_socket(const char * ip,short port,int snd_buf_size,int rcv_buf_size,int ms_snd_timeout,\
							int ms_rcv_timeout,	int addr_reuse,int port_reuse,int nonblock,int &svr_socket);


/*
*���ܣ�		����socket�Ļ�������С����...
*���������	sock:		��Ҫ�������Ե�socket...
		snd_buf_size	���ͻ�������С����С�ڵ���0��������...
		rcv_buf_size:	���ܻ�������С����С�ڵ���0�������ý��ܻ�������С����С�ڵ���0��������...
*���������	...
*���������	
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR set_buf_size(int sock,int snd_buf_size,int rcv_buf_size);

/*
*���ܣ�		��ȡsocket�Ļ�������С����...
*���������	sock:		��Ҫ�������Ե�socket...
*���������	snd_buf_size	���ͻ�������С......
		rcv_buf_size:	���ܻ�������С...
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR get_buf_size(int sock,int* snd_buf_size,int* rcv_buf_size);


/*
*���ܣ�		����socket�Ļ�������С����...
*���������	sock:		��Ҫ�������Ե�socket...
		ms_snd_timeout:	���ͳ�ʱʱ�䣬��λ���룬��С��0�������ã�����0����Ϊ���޵ȴ�...
		ms_rcv_timeout:	���ܳ�ʱʱ�䣬��λ���룬��С��0�������ã�����0����Ϊ���޵ȴ���...
*���������	
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR set_timeout(int sock,int ms_snd_timeout,int ms_rcv_timeout);


/*
*���ܣ�		��ȡsocket�ĳ�ʱ����...
*���������	sock:		��Ҫ�������Ե�socket...
*���������	ms_snd_timeout:	���ͳ�ʱʱ�䣬��λ����...
		ms_rcv_timeout:	���ܳ�ʱʱ�䣬��λ����...
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR get_timeout(int sock,int* ms_snd_timeout,int* ms_rcv_timeout);


/*
*���ܣ�		����socket�ĵ�ַ��������...
*���������	sock:		��Ҫ�������Ե�socket...
		breuse:�Ƿ����õ�ַ��0ֵ��ʾ���ã���0Ϊ������...
*���������	
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR set_addr_reuse(int sock,int breuse);


/*
*���ܣ�		��ȡsocket�ĵ�ַ��������...
*���������	sock:		��Ҫ�������Ե�socket...
*���������	breuse:�Ƿ����õ�ַ...
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR get_addr_reuse(int sock,int* breuse);

#ifdef SO_REUSEPORT
/*
*���ܣ�		����socket�Ķ˿���������...
*���������	sock:		��Ҫ�������Ե�socket...
		breuse:�Ƿ����õ�ַ��0ֵ��ʾ���ã���0Ϊ������...
*���������	
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR set_port_reuse(int sock,int breuse);

/*
*���ܣ�		��ȡsocket�Ķ˿���������...
*���������	sock:		��Ҫ�������Ե�socket
*���������	breuse:  	�Ƿ����õ�ַ��0ֵ��ʾ���ã���0Ϊ������
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR get_port_reuse(int sock,int* breuse);
#endif


/*
*���ܣ�		��socket�����ƶ���ַ��������
*���������	sock:		��Ҫ�������Ե�socket
		msg:		��Ϣ��ַ��ָ��
		msg_size:	��Ϣ�ĳ���
		dstip:		Ŀ��ip��ַ
		dstport:	Ŀ��˿�
*���������	sent_size��	���͵���Ϣ����
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR send_msg(int sock,const char * msg,int msg_size,const char * dstip, int dstport,int* sent_size);

FOX_DLL_EXPORT SP2P_ERR send_msgs(int sock,  iovec *iovec, int iovlen,const char *dstip, int  dstport, int *sent_size);
/*
*���ܣ�		����socket�ϵ���Ϣ
*���������	sock:		��Ҫ�������Ե�socket
		buf_len:	���ܻ������Ĵ�С
*���������	buf��		���ܻ�������ָ��
		rcv_szie:	���ܵ���Ϣ�ĳ���
		srcip��		��Ϣ��Դip��ַ
		short:		��ϢԴ��ַ�˿ں�
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR recv_msg(int sock,char * buf,int buf_len,int* rcv_size,char* srcip,int *srcport);


/*
*���ܣ�		����socket�ķ���������
*���������	sock:		��Ҫ�������Ե�socket
		nonblock:	�Ƿ����÷�����ģʽ��0ֵ��ʾ����ģʽ����0Ϊ������ģʽ
*���������	
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR set_nonblock(int sock,int nonblock);


/*
*���ܣ�		��ȡsocket�ķ���������
*���������	sock:		��Ҫ�������Ե�socket
*���������	nonblock:	������ģʽ��־��0ֵ��ʾ����ģʽ����0Ϊ������ģʽ
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR get_nonblock(int sock,int* nonblock);


/*
*���ܣ�		�ر�socket
*���������	sock:		��Ҫ�������Ե�socket
*���������	
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
*/
FOX_DLL_EXPORT SP2P_ERR closesocket(int sock);


/*
*���ܣ�		��������
*���������	SerDomain:		��Ҫ����������
                    len                        ����������
*���������	Serip                   �����󱣴�Ļ�����
*����ֵ��	�ɹ�����SP2P_SUCCESS,ʧ���򷵻���Ӧ�Ĵ������...
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

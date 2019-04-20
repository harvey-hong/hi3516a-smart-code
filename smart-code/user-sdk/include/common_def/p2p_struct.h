#ifndef _P2P_STRUCT_H_
#define _P2P_STRUCT_H_
#include <stdio.h>
#include <stdlib.h>
#include "ws_comm_type.h"

typedef struct _in_packet_node
{
	WS_CHAR 	*buf;					// 每个数据包分配1920个字节
	WS_S32 	bufLength;			    	// 缓冲区中实际有效数据长度
	char srcIP[16];
	unsigned int srcPort;	
	struct _in_packet_node * next;
} in_packet_node;

typedef struct _cmd_packet_node
{
    WS_S32     cmdValue;               // 发送命令值
    WS_VOID    *pStructData;           // 发送命令数据结构指针
    WS_S32     bufLength;              // 缓冲区长度
    WS_CHAR   destIP[16];              // 目标IP地址
    WS_S32     destPort;               // 目标设备端口
    struct _cmd_packet_node *next;
} cmd_packet_node;


/* Output packet's list */
typedef struct _OutputPacketNode
{
    int          Magic ;                                        /*add by linhh 20170601 : 在Deinit 中通过Magic 实现工作线程中命令的自动删除*/

    /* add by linhh 20170601 start: 添加流分片相关信息*/
    int          MediaSessionID;
    int          frameNo;
    int          frameType;
    int          PktCnt ;
    int          PktSeq;
    /* add by linhh 20170601 end: 添加流分片相关信息*/
    
    int         CmdValue;
    void       *PtrDataStruct;
    char        DestIP[16];
    int          DestPort;
    int          SockFd;
    _OutputPacketNode *Next;
} OutputPacketNode;

/* add by linhh 20170531 : 在流数据链表中添加Magic 判断是丢弃还是发送*/
typedef struct _OutputStreamNode
{
    int                             Magic ;
    OutputPacketNode       PacketNode;
    _OutputStreamNode     *Next ;
}OutputStreamNode;


/* change by linhh 20170526 : 统一报警模块类型定义 到HieServer_Cfg.h 与 ws_status_def.h 中*/
typedef WS_VOID(*fill_list)(in_packet_node *);

typedef struct
{
    WS_U32		iCmd;				// 命令Command
    fill_list	cmd_rev_func;		// 端口接收命令回调函数
    fill_list	cmd_timeout_func;	// 会话超时回调函数
    fill_list	cmd_ans_func;		// 端口命令解析出为会话应答包回调函数
} cmd_map_fun;


#endif







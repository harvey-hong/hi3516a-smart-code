#ifndef _P2P_STRUCT_H_
#define _P2P_STRUCT_H_
#include <stdio.h>
#include <stdlib.h>
#include "ws_comm_type.h"

typedef struct _in_packet_node
{
	WS_CHAR 	*buf;					// ÿ�����ݰ�����1920���ֽ�
	WS_S32 	bufLength;			    	// ��������ʵ����Ч���ݳ���
	char srcIP[16];
	unsigned int srcPort;	
	struct _in_packet_node * next;
} in_packet_node;

typedef struct _cmd_packet_node
{
    WS_S32     cmdValue;               // ��������ֵ
    WS_VOID    *pStructData;           // �����������ݽṹָ��
    WS_S32     bufLength;              // ����������
    WS_CHAR   destIP[16];              // Ŀ��IP��ַ
    WS_S32     destPort;               // Ŀ���豸�˿�
    struct _cmd_packet_node *next;
} cmd_packet_node;


/* Output packet's list */
typedef struct _OutputPacketNode
{
    int          Magic ;                                        /*add by linhh 20170601 : ��Deinit ��ͨ��Magic ʵ�ֹ����߳���������Զ�ɾ��*/

    /* add by linhh 20170601 start: �������Ƭ�����Ϣ*/
    int          MediaSessionID;
    int          frameNo;
    int          frameType;
    int          PktCnt ;
    int          PktSeq;
    /* add by linhh 20170601 end: �������Ƭ�����Ϣ*/
    
    int         CmdValue;
    void       *PtrDataStruct;
    char        DestIP[16];
    int          DestPort;
    int          SockFd;
    _OutputPacketNode *Next;
} OutputPacketNode;

/* add by linhh 20170531 : �����������������Magic �ж��Ƕ������Ƿ���*/
typedef struct _OutputStreamNode
{
    int                             Magic ;
    OutputPacketNode       PacketNode;
    _OutputStreamNode     *Next ;
}OutputStreamNode;


/* change by linhh 20170526 : ͳһ����ģ�����Ͷ��� ��HieServer_Cfg.h �� ws_status_def.h ��*/
typedef WS_VOID(*fill_list)(in_packet_node *);

typedef struct
{
    WS_U32		iCmd;				// ����Command
    fill_list	cmd_rev_func;		// �˿ڽ�������ص�����
    fill_list	cmd_timeout_func;	// �Ự��ʱ�ص�����
    fill_list	cmd_ans_func;		// �˿����������Ϊ�ỰӦ����ص�����
} cmd_map_fun;


#endif







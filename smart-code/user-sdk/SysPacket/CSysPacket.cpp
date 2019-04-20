#include <stdio.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "time.h"
#include <sys/select.h>
#include "hisdk.h"

#if 0 //def HI3518EV200_V001
const  int ITASKCNT				        = 2 ;
static int IFRAMEINCNT[ITASKCNT]	        = {100, 100};
static int IFRAMEINCNTSUB[ITASKCNT]     = {100, 100};
const  int IFRAMEHEADLEN			        = 512;
const  int IFRAMEBUFFLENGTH		        = 1024 * 1024 ; 
#else
const  int ITASKCNT				        = 3 ;
static int IFRAMEINCNT[ITASKCNT]	        = {100, 100, 100};
static int IFRAMEINCNTSUB[ITASKCNT]     = {100, 100, 100};
const  int IFRAMEHEADLEN			        = 512;
const  int IFRAMEBUFFLENGTH		        = 2 * 1024 * 1024 ;
#endif 
const   int IFRAMEBUFFPACKETLENGTH       = 4 * 1024;	                                            /*  循环缓冲区每片的大小  16K每片，也就是所循环缓冲区最多分为256片 */
const   int IFRAMEBUFFPACKETNUM	        = IFRAMEBUFFLENGTH / IFRAMEBUFFPACKETLENGTH;	    /*  循环缓冲区中分片数目 */
const   int INODECNT				        = 128;	                                                /*  任务节点最多只有分片个数 */
char  IFRAMEBUFFUSERECORD[ITASKCNT][IFRAMEBUFFPACKETNUM];		                            /*  循环缓冲区中对于每片的使用记录 */

#undef TEST_PLAYADUO

#define CSYSPACKET_FUNCTION_OUTPUT __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif
    CSYSPACKET_FUNCTION_OUTPUT int H264Node_Init( ) ;
    CSYSPACKET_FUNCTION_OUTPUT int H264Node_Add(int nBuffCnt, int pBuffData[10], int iBuffLen[10], int iFrameType, unsigned int tFrameTime, unsigned int tFrameTimeUsec, unsigned int width, unsigned int height, unsigned int iFrameNo) ;
    CSYSPACKET_FUNCTION_OUTPUT int H264Node_NewTaskId(unsigned int *iTaskId, unsigned int iFrameMode);
    CSYSPACKET_FUNCTION_OUTPUT int H264Node_DelTaskId(unsigned int iTaskId);
    /* hzg 20170810获取帧接口返回了当前帧与前一帧的时间差 */
     /* hzg 20180312 获取帧链表中专门针对I帧编号的序号值 */
    CSYSPACKET_FUNCTION_OUTPUT int H264Node_GetOneFrameEx(unsigned int iTaskId, int *iFrameType, unsigned int *tFrameTime, unsigned int *tFrameTimeUsec, char **pFramePointer, unsigned int *iFrameLen, unsigned int *iFrameNo, unsigned int *width, unsigned int *height, unsigned int *last_frame_idx, unsigned int *frame_delta_time, unsigned int *IFrameIdx);
    CSYSPACKET_FUNCTION_OUTPUT int H264Node_ReleaseOneFrameEx(unsigned int iTaskId, unsigned int iFrameNo, unsigned int node_idx);
    extern int H264Enc_Start(int enc_type);
    extern int H264Enc_Stop(int enc_type);
    extern int AUDIO_Start();
    extern int AUDIO_Stop();

    CSYSPACKET_FUNCTION_OUTPUT int AUDIONode_Add(int nBuffCnt, int pBuffData[10], int iBuffLen[10], int iFrameType, unsigned int tFrameTime, unsigned int tFrameTimeUsec) ;
    CSYSPACKET_FUNCTION_OUTPUT int AUDIONode_GetOneFrameEx(unsigned int iTaskId, int *iFrameType, unsigned int *tFrameTime, unsigned int *tFrameTimeUsec, char **pFramePointer, unsigned int *iFrameLen, unsigned int *iFrameNo, char **pNodeP, unsigned int *last_frame_idx);
    CSYSPACKET_FUNCTION_OUTPUT int AUDIONode_ReleaseOneFrameEx(unsigned int iTaskId, unsigned int node_idx);
    CSYSPACKET_FUNCTION_OUTPUT int AUDIONode_NewTaskId(unsigned int *iTaskId);
    CSYSPACKET_FUNCTION_OUTPUT int AUDIO_DelTaskId(unsigned int iTaskId);

#ifdef __cplusplus
}
#endif

typedef struct tagNODEINFO
{
	struct tagNODEINFO		*pNext;
	struct tagNODEINFO		*pPre;
	unsigned int				iFrameIndex;		// 当前帧号，文件头固定帧号为0x52001314
	char						*pFrameData;		// 数据在缓冲区中地址
	char						*pFrameBuff;		// 数据在缓冲区中偏移地址
	unsigned int				iFrameLen;			// 帧数据的长度包括偏移的256字节
	
	unsigned int				iFrameType;			// 当前帧类型	I帧数据，P帧数据或者音频帧数据
	unsigned int				iFrameLoadType;		// 负载类型，与解码库数据结构兼容
	unsigned int				iFrameTime;			// 帧数据时间戳
	unsigned int				iFrameTimeUsec;		// 帧数据的微秒时间
	unsigned int				iLocalFrameTime;	// 添加数据时获取
	unsigned int				iLocalFrameUsec;
	unsigned int				iLocalFrameWidth;
	unsigned int				iLocalFrameHeight;
	unsigned int				iFramePacketStart;//循环缓冲区使用分片的头分片的ID
	unsigned int				iFramePacketNum;//循环缓冲区使用分片的分片数目
	unsigned int				iFrameUseNum;	//用户使用计数
	unsigned int				iValid;				// 当前数据结构中帧信息是否有效
	unsigned int				node_idx;			//帧任务编号,用于取帧时候用

	unsigned int				frame_delta_time_ms; /* hzg 20170810 帧节点增加参数保存当前帧与前一帧的时间差 */
	unsigned int				IFrame_Idx;                   /* hzg 20180312 记录帧链表中专门针对I帧编号的序号值 */
}NodeInfo, *pNodeInfo ;

typedef struct tagTASKINFO
{
	struct tagTASKINFO		*pNext;
	struct tagTASKINFO		*pPre;
	unsigned int				iValid;				// 当前数据结构中信息是否有效
	unsigned int				iTaskId;			// 当前任务ID
	unsigned int				iFrameMode;			// 当前任务绑定的是主码流还是子码流信息: 0 标识主码流，1标识子码流
	unsigned int				iFrameCnt;			// 帧计数，当帧缓冲过多时候应该直接丢弃对应的帧，只存放I帧
    unsigned int                iNeedSysHeader;    /* hzg 启动任务时,需要发送系统头: 0x80表示主码流系统头,0x81表示子码流系统头 */	
	struct tagNODEINFO		*pNode;				// 当前任务使用的链表信息
	struct tagNODEINFO		*pNodeHead;			// 节点链表首指针
	struct tagNODEINFO		*pNodeTail;			// 节点链表尾指针	
	unsigned int				iNeedIFrame;		// 当前帧有不连续情况发生，下一帧必须是I帧
	char						*pFrameBuff;		// 开辟缓冲区，考虑采取拷贝方式实现
	unsigned int				iusr_num;
	char 					*pFramePacketRecord;//循环缓冲区使用分片的记录
	unsigned int				iLastIFrameidx;		//最后一个I帧的任务编号
        unsigned int                              i_IFrameIdx;          /* hzg 20180312 记录帧链表中专门针对I帧编号的序号值 */
	unsigned int				iFrameidx;		//最后一帧的任务编号
	pthread_mutex_t 			m_Capturelock;		// 任务访问的互斥锁，无论是填充数据或者发送数据
}TaskInfo, *pTaskInfo ;

// 存放任务链表首指针
static pTaskInfo				pTaskHead;

// 存放主码流与子码流文件首部的缓冲区
static unsigned char			m_NodeBuffMainHead[IFRAMEHEADLEN];			
static unsigned char			m_NodeBuffSubHead[IFRAMEHEADLEN];

static void syspacket_rsleep(unsigned int ntime)
{
	struct timespec 	ts;
	ts.tv_sec			= ntime / 1000000;
	ts.tv_nsec 			= (ntime % 1000000) * 1000L;
	nanosleep(&ts, NULL);
}

/* 数据链表初始化 */
CSYSPACKET_FUNCTION_OUTPUT int H264Node_Init( ) 
{
    /* 建立任务链表 */
    int			index , indexNode;
    pTaskInfo	pTaskTemp, pTaskTempPre, pTaskTempNext;
    pTaskHead	= (pTaskInfo)malloc( sizeof( TaskInfo ) * ITASKCNT );
    if( NULL == pTaskHead )
        return 0 ;
    memset((char*)pTaskHead, 0, sizeof( TaskInfo ) * ITASKCNT);
	
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        if( index == 0 )
            pTaskTempPre = NULL ;
        else
            pTaskTempPre = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * ( index - 1 ));
        if( index == ITASKCNT - 1 )
            pTaskTempNext = NULL ;
        else
            pTaskTempNext = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * ( index + 1 ));
        pTaskTemp->pNext		= pTaskTempNext ;
        pTaskTemp->pPre		= pTaskTempPre ;
        pTaskTemp->iValid		= 0 ;
        pTaskTemp->iFrameCnt	= 0 ;
        pTaskTemp->iusr_num     = 0 ;
        pTaskTemp->iTaskId		= index + 1;
    }

    // 为每个任务分配内部空间与节点索引
    pNodeInfo	pNodeTemp, pNodeTempPre, pNodeTempNext;
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        pTaskTemp->iFrameMode	= 0xFFFF ;
        pTaskTemp->iNeedIFrame	= 1 ;

        // 分配数据保存空间
        pTaskTemp->pFrameBuff	= (char*)malloc( IFRAMEBUFFLENGTH ) ;
        if( NULL == pTaskTemp->pFrameBuff )
        {
            printf("\n [FILE=%s][FUN=%s][LINE=%d] Task[%d] Malloc FrameBuff Error -- \n" , __FILE__ , __FUNCTION__ , __LINE__ , index);
            return 0 ;
        }
        memset((char*)pTaskTemp->pFrameBuff, 0, IFRAMEBUFFLENGTH );
        
        pTaskTemp->pFramePacketRecord = IFRAMEBUFFUSERECORD[index];
        memset(pTaskTemp->pFramePacketRecord,0,IFRAMEBUFFPACKETNUM);
        		
        // 分配数据索引节点空间
        pTaskTemp->pNode		= (pNodeInfo)malloc( sizeof( NodeInfo ) * INODECNT ) ;
        if( NULL == pTaskTemp->pNode )
        {
            printf("\n [FILE=%s][FUN=%s][LINE=%d] Task[%d] Malloc Node Error -- \n" , __FILE__ , __FUNCTION__ , __LINE__ , index);
            return 0 ;
        }
        memset((char*)pTaskTemp->pNode, 0, sizeof( NodeInfo ) * INODECNT );
		
        // 建立内部数据索引节点链表
        for( indexNode = 0 ; indexNode < INODECNT ; indexNode ++ )
        {
            pNodeTemp = (pNodeInfo)((char*)pTaskTemp->pNode + sizeof( NodeInfo ) * indexNode);
            if( 0 == indexNode )
                pNodeTempPre = (pNodeInfo)((char*)pTaskTemp->pNode + sizeof( NodeInfo ) * ( INODECNT - 1 ));
            else
                pNodeTempPre = (pNodeInfo)((char*)pTaskTemp->pNode + sizeof( NodeInfo ) * ( indexNode - 1 ));

            if( (INODECNT - 1) == indexNode )
                pNodeTempNext = (pNodeInfo)pTaskTemp->pNode ;
            else
                pNodeTempNext = (pNodeInfo)((char*)pTaskTemp->pNode + sizeof( NodeInfo ) * ( indexNode + 1 ));
            pNodeTemp->pNext		= pNodeTempNext ;
            pNodeTemp->pPre			= pNodeTempPre  ;
            pNodeTemp->pFrameData	= NULL ;
        }
        pTaskTemp->pNodeHead	= NULL ;
        pTaskTemp->pNodeTail	= NULL ;

        // 初始化任务访问的互斥锁
        pthread_mutex_init(&pTaskTemp->m_Capturelock, NULL);
    }
	
    memset(m_NodeBuffMainHead, 0, sizeof( m_NodeBuffMainHead ) );
    memset(m_NodeBuffSubHead, 0, sizeof( m_NodeBuffSubHead ) );

    return 0 ;
}

//计算需要的帧存储起始地址，返回1表示成功找到，0表示未找到
int stream_find_valid_space(const char *addr,const int addr_len,int need_space, int *start_addr)
{
    int find_packet_num = 0;
    int start_packet = -1;
    int is_find = 0;
    
    //从所有的内存分片记录中查找
    for(int i = 0; i < addr_len; i++)
    {
        // 查找连续可用的地址
        if(0 == addr[i])
        {
            if( -1 == start_packet)
            {
                start_packet = i;
            }
            find_packet_num ++;
        }
        else 
        {
            start_packet = -1;
            find_packet_num = 0;
        }

        //如果查找到的分片数目等同于需要查找的数目，对起始地址赋值后成功返回
        if(need_space == find_packet_num)
        {
            *start_addr = start_packet;
            is_find = 1;
            break;
        }
    }
    return is_find;
}

//释放当前链表中最早的
int del_old_frame(pTaskInfo task_node)
{
    struct tagNODEINFO	*cur = task_node->pNodeHead;
    struct tagNODEINFO	*stop = task_node->pNodeHead->pPre;
    struct tagNODEINFO	*pdelPre = task_node->pNodeHead->pPre;                                                  // control for delete 
    
    if( (cur->iValid == 1) && (cur->iFrameUseNum == 0) )
    {
        task_node->pNodeHead = task_node->pNodeHead->pNext;
        cur->iValid = 0;
        for( int k = 0 ; k < cur->iFramePacketNum ; k ++ )
            task_node->pFramePacketRecord[cur->iFramePacketStart + k] = 0 ;
        return 1 ;
    }

    int is_find = 0;
    while( cur->iValid == 1 )
    {
        if( cur->iFrameUseNum > 0 )
        {
            pdelPre = cur ;
            cur = cur->pNext;
            if( cur == stop )
                return is_find ;
            
            continue;
        }

        cur->iValid = 0;
        for( int k = 0 ; k < cur->iFramePacketNum ; k ++ )
            task_node->pFramePacketRecord[cur->iFramePacketStart + k] = 0 ;
        is_find = 1;

        pdelPre->pNext = cur->pNext ;
        cur->pNext->pPre = pdelPre ;
        cur->pNext = task_node->pNodeHead ;
        cur->pPre = task_node->pNodeHead->pPre ;
        task_node->pNodeHead->pPre->pNext = cur ;
        task_node->pNodeHead->pPre = cur ;

        break;
    }
    return  is_find ;   
}

//查找一个当前废弃的节点以使用，未找到则返回NULL
struct tagNODEINFO	*find_invalid_node(pTaskInfo task_node)
{
    struct tagNODEINFO	*cur = task_node->pNodeHead;
    struct tagNODEINFO	*stop = task_node->pNodeHead->pPre;

    while( cur != stop )
    {
        if(cur->iValid)
            cur = cur->pNext;
        else
            return cur ;
    }
    return NULL;
}

// 根据帧节点编号获取帧节点地址
struct tagNODEINFO	*find_node_by_idx(pTaskInfo task_node,unsigned int node_idx)
{
    struct tagNODEINFO *start = task_node->pNodeHead;
    struct tagNODEINFO	*stop = task_node->pNodeHead->pPre;

    do
    {
        if (start->node_idx == node_idx && start->iValid)
        {  
            return start;
        }
        start = start->pNext;
    }while (start != stop);
    return NULL;
}

struct tagNODEINFO	*find_next_i_node_by_idx(pTaskInfo task_node,unsigned int node_idx)
{
    struct tagNODEINFO *start = task_node->pNodeHead;
    struct tagNODEINFO	*stop = task_node->pNodeHead->pPre;
    
    do
    {
        if ((start->node_idx <= node_idx) || (!start->iValid) || ((start->iFrameType != 0x1) && (start->iFrameType != 0x10)))
        {
            start = start->pNext;
        }
        else
        {
            return start;
        }
    }while (start != stop);
    return NULL;
}

struct tagNODEINFO	*find_next_audio_node_by_idx(pTaskInfo task_node,unsigned int node_idx)
{
    struct tagNODEINFO *start = task_node->pNodeHead;
    struct tagNODEINFO	*stop = task_node->pNodeHead->pPre;
    
    do
    {
        if ((start->node_idx <= node_idx) || (!start->iValid) )
        {
            start = start->pNext;
        }
        else
            return start;
    }while (start != stop);
    return NULL;
}

int init_task(pTaskInfo task_node)
{
    struct tagNODEINFO *start = task_node->pNodeHead;
    struct tagNODEINFO	*stop = task_node->pNodeHead->pPre;
    if(start == NULL)
    {
        return -1;
    }

    do
    {
        start->iValid = 0;
        start = start->pNext;
    }while (start != stop);
}

// 底层音视频单元获取到数据后将数据添加到各任务链表中
CSYSPACKET_FUNCTION_OUTPUT int H264Node_Add(int nBuffCnt, int pBuffData[10], int iBuffLen[10], int iFrameType, unsigned int tFrameTime, unsigned int tFrameTimeUsec, unsigned int width, unsigned int height, unsigned int iFrameNo) 
{
    int			index , iTemp;
    int			m_SpaceNeed		= 0 ;
    pNodeInfo	    pNodeTemp ;
    pTaskInfo	    pTaskTemp ;

    int need_packet = 0;
    int start_packet = 0;
    int is_full = 0;
    
    struct timeval		tv ;
    gettimeofday(&tv, NULL);

    // 计算需要输入的总长度
    for( index = 0 ; index < nBuffCnt ; index ++ )
        m_SpaceNeed += iBuffLen[index] ;
    m_SpaceNeed += 256 ;

    /* 接收到文件首部直接拷贝到静态空间中保存 */
    if( 0x0080 == iFrameType )
    {
        /* hzg 20170525 09:01:03 把系统头数据写入静态缓冲区中,私有协议启动流时直接把这个缓冲区数据当做系统头帧发送 */
        memcpy((char*)m_NodeBuffMainHead + 256 , (char*)pBuffData[0], iBuffLen[0]);
        return 0 ;
    }

    if( 0x0081 == iFrameType )
    {
         /* hzg 20170525 09:01:03 把系统头数据写入静态缓冲区中,私有协议启动流时直接把这个缓冲区数据当做系统头帧发送 */
        memcpy((char*)m_NodeBuffSubHead + 256 , (char*)pBuffData[0], iBuffLen[0]);
        return 0 ;
    }

    /* 输入主码流数据保存处理逻辑 */
    if( (iFrameType == 1) || (iFrameType == 2) || (iFrameType == 8))
    {
        for( index = 0 ; index < ITASKCNT ; index ++ )
        {
            pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);

            // 判断任务是否有效，并且任务是否是主码流获取的任务: 网络协议用0 ，SD 卡用2
            if( (pTaskTemp->iValid != 0) && ((0 == pTaskTemp->iFrameMode) || (2 == pTaskTemp->iFrameMode)) ) 
            {
                // 前面有丢帧，必须等待到I帧才能保存
                if( ((pTaskTemp->iNeedIFrame > 0) && (iFrameType == 1)) || ( 0 == pTaskTemp->iNeedIFrame ) )
                {
                    // 有2秒的数据没有发送了，只保存I帧信息
                    // 目前所有客户端共用一个链表，无法判断是所有客户端访问慢还是个别客户端访问慢，不能添加控制了
                    need_packet = (m_SpaceNeed + IFRAMEBUFFPACKETLENGTH - 1) / IFRAMEBUFFPACKETLENGTH;
                    start_packet = 0 ;
                    is_full = 0 ;
                                
                    //没有找到可用帧的情况下，需要释放当前未被使用的帧
                    while(stream_find_valid_space(pTaskTemp->pFramePacketRecord,IFRAMEBUFFPACKETNUM,need_packet,&start_packet) == 0)
                    {
                        if(del_old_frame(pTaskTemp) == 0)
                        {
                            printf("[ LINHH MODEL [FILE=%s][FUN=%s][LINE=%d] there not enough mem to save frame\n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;
                            is_full = 1;
                            break;
                        }
                    }

                    if(is_full)
                    {
                        pTaskTemp->iNeedIFrame	= 1 ;
                        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                        continue ;
                    }

                    // 判断缓冲区索引是否已经不够使用
                    pNodeTemp = find_invalid_node(pTaskTemp);
                    while(pNodeTemp == NULL)
                    {
                        if(del_old_frame(pTaskTemp) == 0)
                        {
                            printf("[ LINHH MODEL [FILE=%s][FUN=%s][LINE=%d] there not enough mem to save frame\n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;
                            break;
                        }
                        pNodeTemp = find_invalid_node(pTaskTemp);
                    }

                    if(pNodeTemp == NULL)
                    {
                        pTaskTemp->iNeedIFrame	= 1 ;
                        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                        continue ;
                    }

                    // 将数据拷贝到循环缓冲区中
                    pNodeTemp->pFrameData = pTaskTemp->pFrameBuff + IFRAMEBUFFPACKETLENGTH*start_packet; 
                    char	*pDataPoint = pNodeTemp->pFrameData + 256;
                    m_SpaceNeed = 0 ;
                    for( iTemp = 0 ; iTemp < nBuffCnt ; iTemp ++ )
                    {
                        memcpy(pDataPoint + m_SpaceNeed, (char*)pBuffData[iTemp], iBuffLen[iTemp]);
                        m_SpaceNeed += iBuffLen[iTemp] ;
                    }
                    m_SpaceNeed += 256 ;

                    pNodeTemp->iFrameIndex        = iFrameNo;
                    pNodeTemp->iFrameLen		= m_SpaceNeed ;
                    pNodeTemp->iFrameType		= iFrameType ;
                    pNodeTemp->iFrameLoadType	= 3 ;
                    pNodeTemp->iFrameTime		= tFrameTime ;
                    pNodeTemp->iFrameTimeUsec	= tFrameTimeUsec ;
                    pNodeTemp->pFrameBuff		= pNodeTemp->pFrameData + 256;
                    pNodeTemp->iLocalFrameTime	= tv.tv_sec ;
                    pNodeTemp->iLocalFrameUsec	= tv.tv_usec;
                    pNodeTemp->iLocalFrameWidth = width;   
                    pNodeTemp->iLocalFrameHeight= height;
                    pNodeTemp->iFramePacketStart = start_packet;
                    pNodeTemp->iFramePacketNum = need_packet;
                    for( int k = 0 ; k < need_packet ; k++ )
                        pTaskTemp->pFramePacketRecord[start_packet+k] = 1 ;
                    pNodeTemp->iFrameUseNum = 0;
                    pNodeTemp->iValid = 1;
                    pTaskTemp->pNodeTail		= pNodeTemp ;
                    pTaskTemp->iNeedIFrame	= 0 ;
                    pTaskTemp->iFrameCnt       += 1 ;
                    pTaskTemp->iFrameidx	+= 1 ;
                    pNodeTemp->node_idx        = pTaskTemp->iFrameidx;
                    if(iFrameType == 1)
                    {
                        pTaskTemp->iLastIFrameidx = pNodeTemp->node_idx;
                        pNodeTemp->IFrame_Idx = pTaskTemp->i_IFrameIdx++;  /* hzg 20180312 获取帧链表中专门针对I帧编号的序号值 */
                    }

                    /* hzg 20170810 增加记录当前帧与前一帧的时间差 start */
                    pNodeTemp->frame_delta_time_ms = 30;
                    if((iFrameType == 0x01)||(iFrameType == 0x10)||(iFrameType == 0x02)||(iFrameType == 0x40) )
                    {
                        struct tagNODEINFO *prev_frame_node = NULL;
                        int SearchNodeIdx = pNodeTemp->node_idx;
                        for(int i = SearchNodeIdx - 1; i > 0; i--)
                        {
                            prev_frame_node = find_node_by_idx(pTaskTemp, i );   
                            if(prev_frame_node == NULL)
                            {
                                break;
                            }
                            else if((prev_frame_node->iFrameType == 0x01)||(prev_frame_node->iFrameType == 0x02)||(prev_frame_node->iFrameType == 0x10)||(prev_frame_node->iFrameType == 0x40) )
                            {
                                pNodeTemp->frame_delta_time_ms = ( (pNodeTemp->iFrameTime - prev_frame_node->iFrameTime)*1000 + (pNodeTemp->iFrameTimeUsec/1000 - prev_frame_node->iFrameTimeUsec/1000) );
                                break;
                            }
                        }
                    }
                    /* hzg 20170810 增加记录当前帧与前一帧的时间差 end */

                    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                }
                else			// if( ((pTaskTemp->iNeedIFrame > 0) && (iFrameType == 1)) || ( 0 == pTaskTemp->iNeedIFrame ) )
                {
                    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                }
            } 
            else				// if( (pTaskTemp->iValid != 0) && ((0 == pTaskTemp->iFrameMode) || (2 == pTaskTemp->iFrameMode)) ) 
            {
                pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
            }
        }
    }

    // 输入子码流数据保存处理逻辑
    if( (iFrameType == 0x10) || (iFrameType == 0x40) || (iFrameType == 8) )
    {
        for( index = 0 ; index < ITASKCNT ; index ++ )
        {
            pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);

            // 判断任务是否有效，并且任务是否是主码流获取的任务
            if( (pTaskTemp->iValid != 0) && ((1 == pTaskTemp->iFrameMode) || (3 == pTaskTemp->iFrameMode)) ) 
            {
                // 前面有丢帧，必须等待到I帧才能保存
                if( ((pTaskTemp->iNeedIFrame > 0) && (iFrameType == 0x10)) || ( 0 == pTaskTemp->iNeedIFrame ) )
                {
                    need_packet = (m_SpaceNeed + IFRAMEBUFFPACKETLENGTH - 1) / IFRAMEBUFFPACKETLENGTH;
                    start_packet = 0 ;
                    is_full = 0 ;
                    while(stream_find_valid_space(pTaskTemp->pFramePacketRecord,IFRAMEBUFFPACKETNUM,need_packet,&start_packet) == 0)
                    {
                        if(del_old_frame(pTaskTemp) == 0)
                        {
                            is_full = 1;
                            break;
                        }
                    }
					
                    if(is_full)
                    {
                        pTaskTemp->iNeedIFrame	= 1 ;
                        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                        continue ;
                    }

                    // 判断缓冲区索引是否已经不够使用
                    pNodeTemp = find_invalid_node(pTaskTemp);
                    while(pNodeTemp == NULL)
                    {
                        if(del_old_frame(pTaskTemp) == 0)
                        {
                            printf("[FILE=%s][FUN=%s][LINE=%d] there not enough mem to save frame\n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;
                            break;
                        }
                        pNodeTemp = find_invalid_node(pTaskTemp);
                    }

                    if(pNodeTemp == NULL)
                    {
                        pTaskTemp->iNeedIFrame	= 1 ;
                        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                        continue ;
                    }

                    // 将数据拷贝到循环缓冲区中
                    pNodeTemp->pFrameData = pTaskTemp->pFrameBuff + IFRAMEBUFFPACKETLENGTH*start_packet; 
                    char	*pDataPoint = pNodeTemp->pFrameData + 256;
                    m_SpaceNeed = 0 ;
                    for( iTemp = 0 ; iTemp < nBuffCnt ; iTemp ++ )
                    {
                        memcpy(pDataPoint + m_SpaceNeed, (char*)pBuffData[iTemp], iBuffLen[iTemp]);
                        m_SpaceNeed += iBuffLen[iTemp] ;
                    }
                    m_SpaceNeed += 256 ;

                    pNodeTemp->iFrameIndex      = iFrameNo;
                    pNodeTemp->iFrameLen		= m_SpaceNeed ;
                    pNodeTemp->iFrameType		= iFrameType ;
                    pNodeTemp->iFrameLoadType	= 3 ;
                    pNodeTemp->iFrameTime		= tFrameTime ;
                    pNodeTemp->iFrameTimeUsec	= tFrameTimeUsec ;
                    pNodeTemp->pFrameBuff		= pNodeTemp->pFrameData + 256;
                    pNodeTemp->iLocalFrameTime	= tv.tv_sec ;
                    pNodeTemp->iLocalFrameUsec	= tv.tv_usec;
                    pNodeTemp->iLocalFrameWidth = width;
                    pNodeTemp->iLocalFrameHeight= height;

                    pNodeTemp->iFramePacketStart = start_packet;
                    pNodeTemp->iFramePacketNum = need_packet;
                    for( int k = 0 ; k < need_packet ; k++ )
                        pTaskTemp->pFramePacketRecord[start_packet+k] = 1 ;
                    pNodeTemp->iFrameUseNum = 0;
                    pNodeTemp->iValid = 1;
                    pTaskTemp->pNodeTail		= pNodeTemp ;
                    pTaskTemp->iNeedIFrame		= 0 ;
                    pTaskTemp->iFrameCnt       += 1 ;
                    pTaskTemp->iFrameidx	   += 1 ;
                    pNodeTemp->node_idx         = pTaskTemp->iFrameidx;
                    if(iFrameType == 0x10)
                    {
                        pTaskTemp->iLastIFrameidx = pNodeTemp->node_idx;
                        pNodeTemp->IFrame_Idx = pTaskTemp->i_IFrameIdx++;  /* hzg 20180312 获取帧链表中专门针对I帧编号的序号值 */
                    }
                    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                }
                else			// if( ((pTaskTemp->iNeedIFrame > 0) && (iFrameType == 1)) || ( 0 == pTaskTemp->iNeedIFrame ) )
                {
                    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                }
            }
            else				// if( (pTaskTemp->iValid != 0) && ((0 == pTaskTemp->iFrameMode) || (2 == pTaskTemp->iFrameMode)) ) 
            {
                pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
            }
        }
    }
    return 0 ;
}

CSYSPACKET_FUNCTION_OUTPUT int H264Node_NewTaskId(unsigned int *iTaskId, unsigned int iFrameMode)
{
    int			index ;
    pTaskInfo	pTaskTemp ;

    struct timeval		tv ;
    gettimeofday(&tv, NULL);

    int     find_index = 0;
    int     is_find = 0;		/*1表示找到一个同需求任务，2表示找到一个空任务*/

	// 搜索是否存在可用的任务句柄
    if(iFrameMode == 0 || iFrameMode == 2)
    {
        iFrameMode = 0;
    }
    else if(iFrameMode == 1 || iFrameMode == 3)
    {
        iFrameMode = 1;
    }
	
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        pthread_mutex_lock(&pTaskTemp->m_Capturelock);
        //防止mode为初始化的0值时认为有用户使用，这里只有任务开启并且mode相同，则认为任务需求相同，返回同一个任务ID
        if( (pTaskTemp->iValid > 0) && (pTaskTemp->iFrameMode == iFrameMode))
        {
            is_find = 1;
            break;
        }
        /* 当前找到一个未使用的任务，先记录下来，如果后面没有找到同需求任务，则以这个任务号创建新任务 */
        else if(pTaskTemp->iValid == 0)
        {
            if(0 == is_find)
            {
                is_find     = 2;
                find_index  = index;
            }
        }
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
    }
    
    if( 0 == is_find )
        return -1 ;

    //找到相同需求任务，用户数加1返回
    if(is_find == 1)
    {
        pTaskTemp->iusr_num++ ;
        /* hzg 20170525 09:01:03 任务标记一下,私有协议会需要发送一次系统头帧 start  */
        if( (0 == iFrameMode) || (2 == iFrameMode) )
        {
            pTaskTemp->iNeedSysHeader = 0x0080;
        }
        else
        {
            pTaskTemp->iNeedSysHeader = 0x0081;
        }
        /* hzg 20170525 09:01:03 任务标记一下,私有协议会需要发送一次系统头帧 end  */
        
        *iTaskId	= pTaskTemp->iTaskId ;
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
        return 0;
    }

    pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * find_index) ;
    pthread_mutex_lock(&pTaskTemp->m_Capturelock);
    pTaskTemp->iValid			= 1 ;
    pTaskTemp->iFrameCnt		= 0 ;
    pTaskTemp->iFrameMode		= iFrameMode ;
    pTaskTemp->pNodeHead		= pTaskTemp->pNode ;
    pTaskTemp->pNodeTail		= pTaskTemp->pNode ;
    pTaskTemp->iNeedIFrame	    = 1 ;
    pTaskTemp->iusr_num		    = 1 ;
    pTaskTemp->iLastIFrameidx	= 0 ;
    pTaskTemp->i_IFrameIdx = 0;    /* hzg 20180312 获取帧链表中专门针对I帧编号的序号值 */
    pTaskTemp->iFrameidx		= 0 ;

    /* hzg 20170525 09:01:03 任务标记一下,私有协议会需要发送一次系统头帧 start  */
    if( (0 == iFrameMode) || (2 == iFrameMode) )
    {
        pTaskTemp->iNeedSysHeader = 0x0080;
    }
    else
    {
        pTaskTemp->iNeedSysHeader = 0x0081;
    }
    /* hzg 20170525 09:01:03 任务标记一下,私有协议会需要发送一次系统头帧 end */

    *iTaskId	= pTaskTemp->iTaskId ;
    H264Enc_Start(iFrameMode);

    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
    return 0 ;
}

CSYSPACKET_FUNCTION_OUTPUT int H264Node_DelTaskId(unsigned int iTaskId)
{
	int			index ;
	pTaskInfo	pTaskTemp ;

	// 判断任务信息是否正确
	for( index = 0 ; index < ITASKCNT ; index ++ )
	{
		pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
		if( pTaskTemp->iTaskId == iTaskId )
		{
			pthread_mutex_lock(&pTaskTemp->m_Capturelock);
			if( pTaskTemp->iValid <= 0 )
			{
				pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
				return -1 ;
			}
			break;
		}
	}
	if( index == ITASKCNT )
		return -1 ;
        
	if(pTaskTemp->iusr_num > 0)
		pTaskTemp->iusr_num--;
	else
		pTaskTemp->iusr_num = 0;

	if(pTaskTemp->iusr_num == 0)
	{
		H264Enc_Stop(pTaskTemp->iFrameMode);
		pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
		init_task(pTaskTemp);
		pTaskTemp->iValid			= 0 ;		
		pTaskTemp->pNodeTail		= NULL ;
		pTaskTemp->pNodeHead		= NULL ;
		pTaskTemp->iFrameMode		= 0xFFFF ;
                pTaskTemp->i_IFrameIdx = 0; /* hzg 20180312 获取帧链表中专门针对I帧编号的序号值 */
		pTaskTemp->iLastIFrameidx	= 0 ;
		pTaskTemp->iFrameidx		= 0 ;
		memset(pTaskTemp->pFramePacketRecord,0,IFRAMEBUFFPACKETNUM);
	}
	pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
	return 0 ;
}

// 先获取任务互斥锁，再获取缓冲区互斥锁
/* change by linhh 20170615 : 删除不需要的形参*/
/* hzg 20170810 获取帧接口增加参数返回了当前帧与前一帧的时间差 */
 /* hzg 20180312 获取帧链表中专门针对I帧编号的序号值 */
CSYSPACKET_FUNCTION_OUTPUT int H264Node_GetOneFrameEx(unsigned int iTaskId, int *iFrameType, unsigned int *tFrameTime, unsigned int *tFrameTimeUsec, char **pFramePointer, 
unsigned int *iFrameLen, unsigned int *iFrameNo, unsigned int *width, unsigned int *height, unsigned int *last_frame_idx, unsigned int *frame_delta_time, unsigned int *IFrameIdx)
{
    int				index ;
    pTaskInfo		pTaskTemp ;
    
    // 判断任务信息是否正确...
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        if( pTaskTemp->iTaskId == iTaskId )
        {
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);
            if( pTaskTemp->iValid <= 0 )
            {
                pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                return -1 ;
            }
            break;
        }
    }
    
    if( index == ITASKCNT )
    {
        return -1 ;
    }

    // 有锁在身，直接获取帧数据
    pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
    int need_i_frame = 0;
    int cur_frame_no = *last_frame_idx;
    if(last_frame_idx == NULL)
    {
        need_i_frame = 1;
    }
    else if(*last_frame_idx == 0xFFFFFFFF)
    {
        need_i_frame = 1;
    }
    /* hzg 20170525 09:01:03 这个帧号是获取到系统头帧后才会传下来释放的,直接置位需要I帧 start*/
    else if( *last_frame_idx  == 0x52001314 )
    {
        need_i_frame = 1;
    }
    /* hzg 20170525 09:01:03 这个帧号是获取到系统头帧后才会传下来释放的,直接置位I帧  end */
    else
    {
        cur_frame_no = cur_frame_no + 1;
    }

    /* hzg 20170525 09:01:03 任务中有标志并且是初次获取帧时,直接发送系统头帧 start*/
    if((0x80 == pTaskTemp->iNeedSysHeader)&&(0xFFFFFFFF == cur_frame_no) )
    {
        struct timeval		tmp_tv ;
        gettimeofday(&tmp_tv, NULL);

        *iFrameType		= 0x0080;
        *tFrameTime		= tmp_tv.tv_sec ;
        *tFrameTimeUsec	= tmp_tv.tv_usec ;
        *iFrameNo		= 0x52001314 ;
        *width			= 1920;
        *height			= 1080;
        *pFramePointer	= ((char *)m_NodeBuffMainHead + 256);
        *iFrameLen		= 19;
        *last_frame_idx     = 0;
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
        return 0 ;
    }
    else if( (0x81 == pTaskTemp->iNeedSysHeader)&&(0xFFFFFFFF == cur_frame_no) )
    {
        struct timeval		tmp_tv ;
        gettimeofday(&tmp_tv, NULL);

        *iFrameType		= 0x0081;
        *tFrameTime		= tmp_tv.tv_sec ;
        *tFrameTimeUsec	= tmp_tv.tv_usec ;
        *iFrameNo		= 0x52001314 ;
        *width			= 704;
        *height			= 576;
        *pFramePointer	= ((char *)m_NodeBuffSubHead + 256);
        *iFrameLen		= 19;
        *last_frame_idx     = 0;
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
        return 0 ;
    }
    /* hzg 20170525 09:01:03 任务中有标志并且是初次获取帧时,直接发送系统头帧 end*/

    struct tagNODEINFO *frame_node = NULL;
    if(need_i_frame)
    {
        frame_node = find_node_by_idx(pTaskTemp,pTaskTemp->iLastIFrameidx);
    }
    else
    {
        frame_node = find_node_by_idx(pTaskTemp,cur_frame_no);
        if(frame_node == NULL)
        {
            frame_node = find_next_i_node_by_idx(pTaskTemp,cur_frame_no-1);
        }
    }
    
    // 目前还没有数据可获取，直接退出..
    if(frame_node == NULL)
    {
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);				
        return -2 ;
    } 

    *iFrameType		= frame_node->iFrameType ;
    *tFrameTime		= frame_node->iFrameTime ;
    *tFrameTimeUsec	= frame_node->iFrameTimeUsec ;
    *iFrameNo		       = frame_node->iFrameIndex;
    *width			= frame_node->iLocalFrameWidth;
    *height			= frame_node->iLocalFrameHeight;

    // 提供偏移后的缓冲区，供私有协议使用
    *pFramePointer	= frame_node->pFrameBuff;
    *iFrameLen		= frame_node->iFrameLen - 256;
    frame_node->iFrameUseNum++;                                    
    *last_frame_idx     = frame_node->node_idx;
    *frame_delta_time = frame_node->frame_delta_time_ms;  /* hzg 20170810 获取帧时返回当前帧与前一帧的时间差 start end */
    *IFrameIdx = frame_node->IFrame_Idx;        /* hzg 20180312 获取帧链表中专门针对I帧编号的序号值 */

    if( pTaskTemp->iFrameCnt > 0 )
        pTaskTemp->iFrameCnt   -= 1 ;

    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);				
    return 0 ;					
}

/* change by linhh 20170615 : 删除不需要的形参*/
CSYSPACKET_FUNCTION_OUTPUT int H264Node_ReleaseOneFrameEx(unsigned int iTaskId, unsigned int iFrameNo, unsigned int node_idx)
{
    int				index ;
    pTaskInfo		pTaskTemp ;

    // 判断任务信息是否正确
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        if( pTaskTemp->iTaskId == iTaskId )
        {
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);
            if( pTaskTemp->iValid <= 0 )
            {
                pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                return -1 ;
            }
            break;
        }
    }
    if( index == ITASKCNT )
        return -1 ;

    // 有锁在身，直接获取帧数据
    pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;

    /* hzg 20170525 09:01:03 任务中有标志并且是释放系统头帧的特定帧号时,清除任务中的标志 start*/
    if( ( (0x80 == pTaskTemp->iNeedSysHeader)||(0x80 == pTaskTemp->iNeedSysHeader) )&&(0x52001314 == iFrameNo) )
    {
        pTaskTemp->iNeedSysHeader = 0;
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
        return 0 ;
    }
    /* hzg 20170525 09:01:03 任务中有标志并且是释放系统头帧的特定帧号时,清除任务中的标志 end*/

    struct tagNODEINFO *frame_node = find_node_by_idx(pTaskTemp,node_idx);
    if(frame_node != NULL)
    {
        if(frame_node->iFrameUseNum > 0)
            frame_node->iFrameUseNum--;
    }
    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
    return 0 ;
}
	
CSYSPACKET_FUNCTION_OUTPUT int AUDIONode_Add(int nBuffCnt, int pBuffData[10], int iBuffLen[10], int iFrameType, unsigned int tFrameTime, unsigned int tFrameTimeUsec) 
{
    int			index , iTemp;
    int			m_SpaceNeed		= 0 ;
    pNodeInfo	pNodeTemp ;
    pTaskInfo	pTaskTemp ;

    int need_packet = 0;
    int start_packet = 0;
    int is_full = 0;
	
    struct timeval		tv ;
    gettimeofday(&tv, NULL);
    
    // 计算需要输入的总长度
    for( index = 0 ; index < nBuffCnt ; index ++ )
        m_SpaceNeed += iBuffLen[index] ;
    m_SpaceNeed += 256 ;

    // 输入音频数据保存处理逻辑
    if( (iFrameType == 8) )
    {
        for( index = 0 ; index < ITASKCNT ; index ++ )
        {
            pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);

            // 判断任务是否有效，并且任务是否是主码流获取的任务
            if( (pTaskTemp->iValid != 0) && (8 == pTaskTemp->iFrameMode) ) 
            {
                // 保存音频帧 ， 接到直接存
                need_packet = (m_SpaceNeed + IFRAMEBUFFPACKETLENGTH - 1) / IFRAMEBUFFPACKETLENGTH;
                //没有找到可用帧的情况下，需要释放当前未被使用的帧
                while(stream_find_valid_space(pTaskTemp->pFramePacketRecord,IFRAMEBUFFPACKETNUM,need_packet,&start_packet) == 0)
                {
                    if(del_old_frame(pTaskTemp) == 0)
                    {
                        printf("[FILE=%s][FUN=%s][LINE=%d] there not enough mem to save frame\n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;
                        is_full = 1;
                        break;
                    }
                }

                if(is_full)
                {
                    pTaskTemp->iNeedIFrame	= 1 ;
                    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                    continue ;
                }

                // 判断缓冲区索引是否已经不够使用
                pNodeTemp = find_invalid_node(pTaskTemp);
                while(pNodeTemp == NULL)
                {
                    if(del_old_frame(pTaskTemp) == 0)
                    {
                        printf("[FILE=%s][FUN=%s][LINE=%d] there not enough mem to save frame\n" , __FILE__ , __FUNCTION__ , __LINE__ ) ;
                        break;
                    }
                    pNodeTemp = find_invalid_node(pTaskTemp);
                }

                // 将数据拷贝到循环缓冲区中
                pNodeTemp->pFrameData = pTaskTemp->pFrameBuff + IFRAMEBUFFPACKETLENGTH*start_packet; 
                char	*pDataPoint = pNodeTemp->pFrameData + 256;
                m_SpaceNeed = 0 ;
                for( iTemp = 0 ; iTemp < nBuffCnt ; iTemp ++ )
                {
                    memcpy(pDataPoint + m_SpaceNeed, (char*)pBuffData[iTemp], iBuffLen[iTemp]);
                    m_SpaceNeed += iBuffLen[iTemp] ;
                }
                m_SpaceNeed += 256 ;

                pNodeTemp->iFrameIndex	= IFRAMEINCNT[index] ++ ;
                if( IFRAMEINCNT[index] == 0x52000000 )
                    IFRAMEINCNT[index] = 1 ;
                pNodeTemp->iFrameLen		= m_SpaceNeed ;
                pNodeTemp->iFrameType		= iFrameType ;
                pNodeTemp->iFrameLoadType	= 3 ;
                pNodeTemp->iFrameTime		= tFrameTime ;
                pNodeTemp->iFrameTimeUsec	= tFrameTimeUsec ;
                pNodeTemp->pFrameBuff		= pNodeTemp->pFrameData + 256;
                pNodeTemp->iLocalFrameTime	= tv.tv_sec ;
                pNodeTemp->iLocalFrameUsec	= tv.tv_usec;
				
                pTaskTemp->pNodeTail		= pNodeTemp ;
                pTaskTemp->iNeedIFrame		= 0 ;
                pTaskTemp->iFrameCnt       += 1 ;
                pTaskTemp->iFrameidx	   += 1 ;
                pNodeTemp->node_idx         = pTaskTemp->iFrameidx;

                pNodeTemp->iFramePacketStart = start_packet;
                pNodeTemp->iFramePacketNum = need_packet;
                for( int k = 0 ; k < need_packet ; k ++ )
                    pTaskTemp->pFramePacketRecord[start_packet + k] = 1 ;
                pNodeTemp->iFrameUseNum = 0;
                pNodeTemp->iValid = 1;
                pTaskTemp->iLastIFrameidx = pNodeTemp->node_idx;
                pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
            } 
            else	
            {
                pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
            }
        }
    }
    return 0 ;
}

// 先获取任务互斥锁，再获取缓冲区互斥锁
CSYSPACKET_FUNCTION_OUTPUT int AUDIONode_GetOneFrameEx(unsigned int iTaskId, int *iFrameType, unsigned int *tFrameTime, unsigned int *tFrameTimeUsec, char **pFramePointer, unsigned int *iFrameLen, unsigned int *iFrameNo, char **pNodeP, unsigned int *last_frame_idx)
{
    int				index ;
    pTaskInfo		pTaskTemp ;

    // 判断任务信息是否正确
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        if( pTaskTemp->iTaskId == iTaskId )
        {
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);
            if( pTaskTemp->iValid <= 0 )
            {
                pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                return -1 ;
            }
            break;
        }
    }
    if( index == ITASKCNT )
        return -1 ;

    // 有锁在身，直接获取帧数据
    pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
    int need_i_frame = 0;
    int cur_frame_no = 0;
    if(last_frame_idx == NULL)
        need_i_frame = 1;
    else if(*last_frame_idx == 0xFFFFFFFF)
        need_i_frame = 1;
    else
        cur_frame_no = *last_frame_idx + 1;

    struct tagNODEINFO *frame_node = NULL;
    if(need_i_frame)
    {
        frame_node = find_node_by_idx(pTaskTemp,pTaskTemp->iLastIFrameidx);
    }
    else
    {
        frame_node = find_node_by_idx(pTaskTemp,cur_frame_no);
        if(frame_node == NULL)
            frame_node = find_next_audio_node_by_idx(pTaskTemp,pTaskTemp->iLastIFrameidx);
    }

    // 目前还没有数据可获取，直接退出...
    if(frame_node == NULL)
    {
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);				
        return -2 ;
    }

    *iFrameType		= frame_node->iFrameType ;
    *tFrameTime		= frame_node->iFrameTime ;
    *tFrameTimeUsec	= frame_node->iFrameTimeUsec ;
    *iFrameNo		= frame_node->iFrameIndex;
    *pNodeP			= (char*)frame_node;

    // 提供偏移后的缓冲区，供私有协议使用
    *pFramePointer	= frame_node->pFrameBuff;
    *iFrameLen		= frame_node->iFrameLen - 256;
    frame_node->iFrameUseNum++;
    *last_frame_idx = frame_node->node_idx;
	
    if( pTaskTemp->iFrameCnt > 0 )
        pTaskTemp->iFrameCnt   -= 1 ;

    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);				
    return 0 ;					
}

CSYSPACKET_FUNCTION_OUTPUT int AUDIONode_ReleaseOneFrameEx(unsigned int iTaskId, unsigned int node_idx)
{
    int				index ;
    pTaskInfo		pTaskTemp ;

    // 判断任务信息是否正确
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        if( pTaskTemp->iTaskId == iTaskId )
        {
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);
            if( pTaskTemp->iValid <= 0 )
            {
                pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                return -1 ;
            }
            break;
        }
    }
    if( index == ITASKCNT )
        return -1 ;

    // 有锁在身，直接获取帧数据
    pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
    struct tagNODEINFO *frame_node = find_node_by_idx(pTaskTemp,node_idx);
    if(frame_node != NULL)
    {
        if(frame_node->iFrameUseNum > 0)
            frame_node->iFrameUseNum--;
    }
    
    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
    return 0 ;
}

CSYSPACKET_FUNCTION_OUTPUT int AUDIONode_NewTaskId(unsigned int *iTaskId)
{
    unsigned int iFrameMode = 0x8;
    int			index ;
    pTaskInfo	pTaskTemp ;

    struct timeval		tv ;
    gettimeofday(&tv, NULL);
    int find_index = 0;
    int is_find = 0;		//1表示找到一个同需求任务，2表示找到一个空任务

    // 搜索是否存在可用的任务句柄
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        pthread_mutex_lock(&pTaskTemp->m_Capturelock);
        //防止mode为初始化的0值时认为有用户使用，这里只有任务开启并且mode相同，则认为任务需求相同，返回同一个任务ID
        if( (pTaskTemp->iValid > 0) && (pTaskTemp->iFrameMode == iFrameMode))
        {
            is_find = 1;
            break;
        }
        else if(pTaskTemp->iValid == 0)//当前找到一个未使用的任务，先记录下来，如果后面没有找到同需求任务，则以这个任务号创建新任务
        {
            // 获取到可用的任务句柄
            if(0 == is_find)
            {
                is_find = 2;
                find_index = index;
            }
        }
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
    }

    //未找到可用任务，返回失败
    if( 0 == is_find )
    {
        return -1 ;
    }

    //找到相同需求任务，用户数加1返回
    if(is_find == 1)
    {
        pTaskTemp->iusr_num++ ;
        *iTaskId	= pTaskTemp->iTaskId ;
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
        return 0;
    }

    //找到空任务，填充任务属性
    // 有锁在身，可以直接使用了
    pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * find_index) ;
    pthread_mutex_lock(&pTaskTemp->m_Capturelock);
    pTaskTemp->iValid			= 1 ;
    pTaskTemp->iFrameCnt		= 0 ;
    pTaskTemp->iFrameMode		= iFrameMode ;
    pTaskTemp->pNodeHead		= pTaskTemp->pNode ;
    pTaskTemp->pNodeTail		= pTaskTemp->pNode ;
    pTaskTemp->iNeedIFrame		= 1 ;
    pTaskTemp->iusr_num			= 1 ;
    pTaskTemp->iLastIFrameidx	= 0 ;
    pTaskTemp->iFrameidx		= 0 ;

    /* hzg 20170525 09:01:03 音频帧不需要系统头帧处理 */
    
    *iTaskId	= pTaskTemp->iTaskId ;
    AUDIO_Start();
    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
    return 0 ;
}

CSYSPACKET_FUNCTION_OUTPUT int AUDIO_DelTaskId(unsigned int iTaskId)
{
    int			index ;
    pTaskInfo	pTaskTemp ;

    // 判断任务信息是否正确
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        if( pTaskTemp->iTaskId == iTaskId )
        {
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);
            if( pTaskTemp->iValid <= 0 )
            {
                pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
                return -1 ;
            }
            break;
        }
    }
    if( index == ITASKCNT )
        return -1 ;
    
    if(pTaskTemp->iusr_num > 0)
        pTaskTemp->iusr_num--;
    else
        pTaskTemp->iusr_num = 0;

    if(pTaskTemp->iusr_num == 0)
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        init_task(pTaskTemp);
        pTaskTemp->iValid			= 0 ;		
        pTaskTemp->pNodeTail		= NULL ;
        pTaskTemp->pNodeHead		= NULL ;
        pTaskTemp->iFrameMode		= 0xFFFF ;
        pTaskTemp->iLastIFrameidx	= 0 ;
        pTaskTemp->iFrameidx		= 0 ;
        memset(pTaskTemp->pFramePacketRecord,0,IFRAMEBUFFPACKETNUM);
    }
    AUDIO_Stop();
    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
    return 0 ;
}
 



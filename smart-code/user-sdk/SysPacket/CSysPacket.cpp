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
const   int IFRAMEBUFFPACKETLENGTH       = 4 * 1024;	                                            /*  ѭ��������ÿƬ�Ĵ�С  16KÿƬ��Ҳ������ѭ������������Ϊ256Ƭ */
const   int IFRAMEBUFFPACKETNUM	        = IFRAMEBUFFLENGTH / IFRAMEBUFFPACKETLENGTH;	    /*  ѭ���������з�Ƭ��Ŀ */
const   int INODECNT				        = 128;	                                                /*  ����ڵ����ֻ�з�Ƭ���� */
char  IFRAMEBUFFUSERECORD[ITASKCNT][IFRAMEBUFFPACKETNUM];		                            /*  ѭ���������ж���ÿƬ��ʹ�ü�¼ */

#undef TEST_PLAYADUO

#define CSYSPACKET_FUNCTION_OUTPUT __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif
    CSYSPACKET_FUNCTION_OUTPUT int H264Node_Init( ) ;
    CSYSPACKET_FUNCTION_OUTPUT int H264Node_Add(int nBuffCnt, int pBuffData[10], int iBuffLen[10], int iFrameType, unsigned int tFrameTime, unsigned int tFrameTimeUsec, unsigned int width, unsigned int height, unsigned int iFrameNo) ;
    CSYSPACKET_FUNCTION_OUTPUT int H264Node_NewTaskId(unsigned int *iTaskId, unsigned int iFrameMode);
    CSYSPACKET_FUNCTION_OUTPUT int H264Node_DelTaskId(unsigned int iTaskId);
    /* hzg 20170810��ȡ֡�ӿڷ����˵�ǰ֡��ǰһ֡��ʱ��� */
     /* hzg 20180312 ��ȡ֡������ר�����I֡��ŵ����ֵ */
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
	unsigned int				iFrameIndex;		// ��ǰ֡�ţ��ļ�ͷ�̶�֡��Ϊ0x52001314
	char						*pFrameData;		// �����ڻ������е�ַ
	char						*pFrameBuff;		// �����ڻ�������ƫ�Ƶ�ַ
	unsigned int				iFrameLen;			// ֡���ݵĳ��Ȱ���ƫ�Ƶ�256�ֽ�
	
	unsigned int				iFrameType;			// ��ǰ֡����	I֡���ݣ�P֡���ݻ�����Ƶ֡����
	unsigned int				iFrameLoadType;		// �������ͣ����������ݽṹ����
	unsigned int				iFrameTime;			// ֡����ʱ���
	unsigned int				iFrameTimeUsec;		// ֡���ݵ�΢��ʱ��
	unsigned int				iLocalFrameTime;	// �������ʱ��ȡ
	unsigned int				iLocalFrameUsec;
	unsigned int				iLocalFrameWidth;
	unsigned int				iLocalFrameHeight;
	unsigned int				iFramePacketStart;//ѭ��������ʹ�÷�Ƭ��ͷ��Ƭ��ID
	unsigned int				iFramePacketNum;//ѭ��������ʹ�÷�Ƭ�ķ�Ƭ��Ŀ
	unsigned int				iFrameUseNum;	//�û�ʹ�ü���
	unsigned int				iValid;				// ��ǰ���ݽṹ��֡��Ϣ�Ƿ���Ч
	unsigned int				node_idx;			//֡������,����ȡ֡ʱ����

	unsigned int				frame_delta_time_ms; /* hzg 20170810 ֡�ڵ����Ӳ������浱ǰ֡��ǰһ֡��ʱ��� */
	unsigned int				IFrame_Idx;                   /* hzg 20180312 ��¼֡������ר�����I֡��ŵ����ֵ */
}NodeInfo, *pNodeInfo ;

typedef struct tagTASKINFO
{
	struct tagTASKINFO		*pNext;
	struct tagTASKINFO		*pPre;
	unsigned int				iValid;				// ��ǰ���ݽṹ����Ϣ�Ƿ���Ч
	unsigned int				iTaskId;			// ��ǰ����ID
	unsigned int				iFrameMode;			// ��ǰ����󶨵���������������������Ϣ: 0 ��ʶ��������1��ʶ������
	unsigned int				iFrameCnt;			// ֡��������֡�������ʱ��Ӧ��ֱ�Ӷ�����Ӧ��֡��ֻ���I֡
    unsigned int                iNeedSysHeader;    /* hzg ��������ʱ,��Ҫ����ϵͳͷ: 0x80��ʾ������ϵͳͷ,0x81��ʾ������ϵͳͷ */	
	struct tagNODEINFO		*pNode;				// ��ǰ����ʹ�õ�������Ϣ
	struct tagNODEINFO		*pNodeHead;			// �ڵ�������ָ��
	struct tagNODEINFO		*pNodeTail;			// �ڵ�����βָ��	
	unsigned int				iNeedIFrame;		// ��ǰ֡�в����������������һ֡������I֡
	char						*pFrameBuff;		// ���ٻ����������ǲ�ȡ������ʽʵ��
	unsigned int				iusr_num;
	char 					*pFramePacketRecord;//ѭ��������ʹ�÷�Ƭ�ļ�¼
	unsigned int				iLastIFrameidx;		//���һ��I֡��������
        unsigned int                              i_IFrameIdx;          /* hzg 20180312 ��¼֡������ר�����I֡��ŵ����ֵ */
	unsigned int				iFrameidx;		//���һ֡��������
	pthread_mutex_t 			m_Capturelock;		// ������ʵĻ�������������������ݻ��߷�������
}TaskInfo, *pTaskInfo ;

// �������������ָ��
static pTaskInfo				pTaskHead;

// ������������������ļ��ײ��Ļ�����
static unsigned char			m_NodeBuffMainHead[IFRAMEHEADLEN];			
static unsigned char			m_NodeBuffSubHead[IFRAMEHEADLEN];

static void syspacket_rsleep(unsigned int ntime)
{
	struct timespec 	ts;
	ts.tv_sec			= ntime / 1000000;
	ts.tv_nsec 			= (ntime % 1000000) * 1000L;
	nanosleep(&ts, NULL);
}

/* ���������ʼ�� */
CSYSPACKET_FUNCTION_OUTPUT int H264Node_Init( ) 
{
    /* ������������ */
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

    // Ϊÿ����������ڲ��ռ���ڵ�����
    pNodeInfo	pNodeTemp, pNodeTempPre, pNodeTempNext;
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        pTaskTemp->iFrameMode	= 0xFFFF ;
        pTaskTemp->iNeedIFrame	= 1 ;

        // �������ݱ���ռ�
        pTaskTemp->pFrameBuff	= (char*)malloc( IFRAMEBUFFLENGTH ) ;
        if( NULL == pTaskTemp->pFrameBuff )
        {
            printf("\n [FILE=%s][FUN=%s][LINE=%d] Task[%d] Malloc FrameBuff Error -- \n" , __FILE__ , __FUNCTION__ , __LINE__ , index);
            return 0 ;
        }
        memset((char*)pTaskTemp->pFrameBuff, 0, IFRAMEBUFFLENGTH );
        
        pTaskTemp->pFramePacketRecord = IFRAMEBUFFUSERECORD[index];
        memset(pTaskTemp->pFramePacketRecord,0,IFRAMEBUFFPACKETNUM);
        		
        // �������������ڵ�ռ�
        pTaskTemp->pNode		= (pNodeInfo)malloc( sizeof( NodeInfo ) * INODECNT ) ;
        if( NULL == pTaskTemp->pNode )
        {
            printf("\n [FILE=%s][FUN=%s][LINE=%d] Task[%d] Malloc Node Error -- \n" , __FILE__ , __FUNCTION__ , __LINE__ , index);
            return 0 ;
        }
        memset((char*)pTaskTemp->pNode, 0, sizeof( NodeInfo ) * INODECNT );
		
        // �����ڲ����������ڵ�����
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

        // ��ʼ��������ʵĻ�����
        pthread_mutex_init(&pTaskTemp->m_Capturelock, NULL);
    }
	
    memset(m_NodeBuffMainHead, 0, sizeof( m_NodeBuffMainHead ) );
    memset(m_NodeBuffSubHead, 0, sizeof( m_NodeBuffSubHead ) );

    return 0 ;
}

//������Ҫ��֡�洢��ʼ��ַ������1��ʾ�ɹ��ҵ���0��ʾδ�ҵ�
int stream_find_valid_space(const char *addr,const int addr_len,int need_space, int *start_addr)
{
    int find_packet_num = 0;
    int start_packet = -1;
    int is_find = 0;
    
    //�����е��ڴ��Ƭ��¼�в���
    for(int i = 0; i < addr_len; i++)
    {
        // �����������õĵ�ַ
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

        //������ҵ��ķ�Ƭ��Ŀ��ͬ����Ҫ���ҵ���Ŀ������ʼ��ַ��ֵ��ɹ�����
        if(need_space == find_packet_num)
        {
            *start_addr = start_packet;
            is_find = 1;
            break;
        }
    }
    return is_find;
}

//�ͷŵ�ǰ�����������
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

//����һ����ǰ�����Ľڵ���ʹ�ã�δ�ҵ��򷵻�NULL
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

// ����֡�ڵ��Ż�ȡ֡�ڵ��ַ
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

// �ײ�����Ƶ��Ԫ��ȡ�����ݺ�������ӵ�������������
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

    // ������Ҫ������ܳ���
    for( index = 0 ; index < nBuffCnt ; index ++ )
        m_SpaceNeed += iBuffLen[index] ;
    m_SpaceNeed += 256 ;

    /* ���յ��ļ��ײ�ֱ�ӿ�������̬�ռ��б��� */
    if( 0x0080 == iFrameType )
    {
        /* hzg 20170525 09:01:03 ��ϵͳͷ����д�뾲̬��������,˽��Э��������ʱֱ�Ӱ�������������ݵ���ϵͳͷ֡���� */
        memcpy((char*)m_NodeBuffMainHead + 256 , (char*)pBuffData[0], iBuffLen[0]);
        return 0 ;
    }

    if( 0x0081 == iFrameType )
    {
         /* hzg 20170525 09:01:03 ��ϵͳͷ����д�뾲̬��������,˽��Э��������ʱֱ�Ӱ�������������ݵ���ϵͳͷ֡���� */
        memcpy((char*)m_NodeBuffSubHead + 256 , (char*)pBuffData[0], iBuffLen[0]);
        return 0 ;
    }

    /* �������������ݱ��洦���߼� */
    if( (iFrameType == 1) || (iFrameType == 2) || (iFrameType == 8))
    {
        for( index = 0 ; index < ITASKCNT ; index ++ )
        {
            pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);

            // �ж������Ƿ���Ч�����������Ƿ�����������ȡ������: ����Э����0 ��SD ����2
            if( (pTaskTemp->iValid != 0) && ((0 == pTaskTemp->iFrameMode) || (2 == pTaskTemp->iFrameMode)) ) 
            {
                // ǰ���ж�֡������ȴ���I֡���ܱ���
                if( ((pTaskTemp->iNeedIFrame > 0) && (iFrameType == 1)) || ( 0 == pTaskTemp->iNeedIFrame ) )
                {
                    // ��2�������û�з����ˣ�ֻ����I֡��Ϣ
                    // Ŀǰ���пͻ��˹���һ�������޷��ж������пͻ��˷��������Ǹ���ͻ��˷�������������ӿ�����
                    need_packet = (m_SpaceNeed + IFRAMEBUFFPACKETLENGTH - 1) / IFRAMEBUFFPACKETLENGTH;
                    start_packet = 0 ;
                    is_full = 0 ;
                                
                    //û���ҵ�����֡������£���Ҫ�ͷŵ�ǰδ��ʹ�õ�֡
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

                    // �жϻ����������Ƿ��Ѿ�����ʹ��
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

                    // �����ݿ�����ѭ����������
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
                        pNodeTemp->IFrame_Idx = pTaskTemp->i_IFrameIdx++;  /* hzg 20180312 ��ȡ֡������ר�����I֡��ŵ����ֵ */
                    }

                    /* hzg 20170810 ���Ӽ�¼��ǰ֡��ǰһ֡��ʱ��� start */
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
                    /* hzg 20170810 ���Ӽ�¼��ǰ֡��ǰһ֡��ʱ��� end */

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

    // �������������ݱ��洦���߼�
    if( (iFrameType == 0x10) || (iFrameType == 0x40) || (iFrameType == 8) )
    {
        for( index = 0 ; index < ITASKCNT ; index ++ )
        {
            pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);

            // �ж������Ƿ���Ч�����������Ƿ�����������ȡ������
            if( (pTaskTemp->iValid != 0) && ((1 == pTaskTemp->iFrameMode) || (3 == pTaskTemp->iFrameMode)) ) 
            {
                // ǰ���ж�֡������ȴ���I֡���ܱ���
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

                    // �жϻ����������Ƿ��Ѿ�����ʹ��
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

                    // �����ݿ�����ѭ����������
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
                        pNodeTemp->IFrame_Idx = pTaskTemp->i_IFrameIdx++;  /* hzg 20180312 ��ȡ֡������ר�����I֡��ŵ����ֵ */
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
    int     is_find = 0;		/*1��ʾ�ҵ�һ��ͬ��������2��ʾ�ҵ�һ��������*/

	// �����Ƿ���ڿ��õ�������
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
        //��ֹmodeΪ��ʼ����0ֵʱ��Ϊ���û�ʹ�ã�����ֻ������������mode��ͬ������Ϊ����������ͬ������ͬһ������ID
        if( (pTaskTemp->iValid > 0) && (pTaskTemp->iFrameMode == iFrameMode))
        {
            is_find = 1;
            break;
        }
        /* ��ǰ�ҵ�һ��δʹ�õ������ȼ�¼�������������û���ҵ�ͬ�������������������Ŵ��������� */
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

    //�ҵ���ͬ���������û�����1����
    if(is_find == 1)
    {
        pTaskTemp->iusr_num++ ;
        /* hzg 20170525 09:01:03 ������һ��,˽��Э�����Ҫ����һ��ϵͳͷ֡ start  */
        if( (0 == iFrameMode) || (2 == iFrameMode) )
        {
            pTaskTemp->iNeedSysHeader = 0x0080;
        }
        else
        {
            pTaskTemp->iNeedSysHeader = 0x0081;
        }
        /* hzg 20170525 09:01:03 ������һ��,˽��Э�����Ҫ����һ��ϵͳͷ֡ end  */
        
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
    pTaskTemp->i_IFrameIdx = 0;    /* hzg 20180312 ��ȡ֡������ר�����I֡��ŵ����ֵ */
    pTaskTemp->iFrameidx		= 0 ;

    /* hzg 20170525 09:01:03 ������һ��,˽��Э�����Ҫ����һ��ϵͳͷ֡ start  */
    if( (0 == iFrameMode) || (2 == iFrameMode) )
    {
        pTaskTemp->iNeedSysHeader = 0x0080;
    }
    else
    {
        pTaskTemp->iNeedSysHeader = 0x0081;
    }
    /* hzg 20170525 09:01:03 ������һ��,˽��Э�����Ҫ����һ��ϵͳͷ֡ end */

    *iTaskId	= pTaskTemp->iTaskId ;
    H264Enc_Start(iFrameMode);

    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
    return 0 ;
}

CSYSPACKET_FUNCTION_OUTPUT int H264Node_DelTaskId(unsigned int iTaskId)
{
	int			index ;
	pTaskInfo	pTaskTemp ;

	// �ж�������Ϣ�Ƿ���ȷ
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
                pTaskTemp->i_IFrameIdx = 0; /* hzg 20180312 ��ȡ֡������ר�����I֡��ŵ����ֵ */
		pTaskTemp->iLastIFrameidx	= 0 ;
		pTaskTemp->iFrameidx		= 0 ;
		memset(pTaskTemp->pFramePacketRecord,0,IFRAMEBUFFPACKETNUM);
	}
	pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
	return 0 ;
}

// �Ȼ�ȡ���񻥳������ٻ�ȡ������������
/* change by linhh 20170615 : ɾ������Ҫ���β�*/
/* hzg 20170810 ��ȡ֡�ӿ����Ӳ��������˵�ǰ֡��ǰһ֡��ʱ��� */
 /* hzg 20180312 ��ȡ֡������ר�����I֡��ŵ����ֵ */
CSYSPACKET_FUNCTION_OUTPUT int H264Node_GetOneFrameEx(unsigned int iTaskId, int *iFrameType, unsigned int *tFrameTime, unsigned int *tFrameTimeUsec, char **pFramePointer, 
unsigned int *iFrameLen, unsigned int *iFrameNo, unsigned int *width, unsigned int *height, unsigned int *last_frame_idx, unsigned int *frame_delta_time, unsigned int *IFrameIdx)
{
    int				index ;
    pTaskInfo		pTaskTemp ;
    
    // �ж�������Ϣ�Ƿ���ȷ...
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

    // ��������ֱ�ӻ�ȡ֡����
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
    /* hzg 20170525 09:01:03 ���֡���ǻ�ȡ��ϵͳͷ֡��Żᴫ�����ͷŵ�,ֱ����λ��ҪI֡ start*/
    else if( *last_frame_idx  == 0x52001314 )
    {
        need_i_frame = 1;
    }
    /* hzg 20170525 09:01:03 ���֡���ǻ�ȡ��ϵͳͷ֡��Żᴫ�����ͷŵ�,ֱ����λI֡  end */
    else
    {
        cur_frame_no = cur_frame_no + 1;
    }

    /* hzg 20170525 09:01:03 �������б�־�����ǳ��λ�ȡ֡ʱ,ֱ�ӷ���ϵͳͷ֡ start*/
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
    /* hzg 20170525 09:01:03 �������б�־�����ǳ��λ�ȡ֡ʱ,ֱ�ӷ���ϵͳͷ֡ end*/

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
    
    // Ŀǰ��û�����ݿɻ�ȡ��ֱ���˳�..
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

    // �ṩƫ�ƺ�Ļ���������˽��Э��ʹ��
    *pFramePointer	= frame_node->pFrameBuff;
    *iFrameLen		= frame_node->iFrameLen - 256;
    frame_node->iFrameUseNum++;                                    
    *last_frame_idx     = frame_node->node_idx;
    *frame_delta_time = frame_node->frame_delta_time_ms;  /* hzg 20170810 ��ȡ֡ʱ���ص�ǰ֡��ǰһ֡��ʱ��� start end */
    *IFrameIdx = frame_node->IFrame_Idx;        /* hzg 20180312 ��ȡ֡������ר�����I֡��ŵ����ֵ */

    if( pTaskTemp->iFrameCnt > 0 )
        pTaskTemp->iFrameCnt   -= 1 ;

    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);				
    return 0 ;					
}

/* change by linhh 20170615 : ɾ������Ҫ���β�*/
CSYSPACKET_FUNCTION_OUTPUT int H264Node_ReleaseOneFrameEx(unsigned int iTaskId, unsigned int iFrameNo, unsigned int node_idx)
{
    int				index ;
    pTaskInfo		pTaskTemp ;

    // �ж�������Ϣ�Ƿ���ȷ
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

    // ��������ֱ�ӻ�ȡ֡����
    pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;

    /* hzg 20170525 09:01:03 �������б�־�������ͷ�ϵͳͷ֡���ض�֡��ʱ,��������еı�־ start*/
    if( ( (0x80 == pTaskTemp->iNeedSysHeader)||(0x80 == pTaskTemp->iNeedSysHeader) )&&(0x52001314 == iFrameNo) )
    {
        pTaskTemp->iNeedSysHeader = 0;
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
        return 0 ;
    }
    /* hzg 20170525 09:01:03 �������б�־�������ͷ�ϵͳͷ֡���ض�֡��ʱ,��������еı�־ end*/

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
    
    // ������Ҫ������ܳ���
    for( index = 0 ; index < nBuffCnt ; index ++ )
        m_SpaceNeed += iBuffLen[index] ;
    m_SpaceNeed += 256 ;

    // ������Ƶ���ݱ��洦���߼�
    if( (iFrameType == 8) )
    {
        for( index = 0 ; index < ITASKCNT ; index ++ )
        {
            pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
            pthread_mutex_lock(&pTaskTemp->m_Capturelock);

            // �ж������Ƿ���Ч�����������Ƿ�����������ȡ������
            if( (pTaskTemp->iValid != 0) && (8 == pTaskTemp->iFrameMode) ) 
            {
                // ������Ƶ֡ �� �ӵ�ֱ�Ӵ�
                need_packet = (m_SpaceNeed + IFRAMEBUFFPACKETLENGTH - 1) / IFRAMEBUFFPACKETLENGTH;
                //û���ҵ�����֡������£���Ҫ�ͷŵ�ǰδ��ʹ�õ�֡
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

                // �жϻ����������Ƿ��Ѿ�����ʹ��
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

                // �����ݿ�����ѭ����������
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

// �Ȼ�ȡ���񻥳������ٻ�ȡ������������
CSYSPACKET_FUNCTION_OUTPUT int AUDIONode_GetOneFrameEx(unsigned int iTaskId, int *iFrameType, unsigned int *tFrameTime, unsigned int *tFrameTimeUsec, char **pFramePointer, unsigned int *iFrameLen, unsigned int *iFrameNo, char **pNodeP, unsigned int *last_frame_idx)
{
    int				index ;
    pTaskInfo		pTaskTemp ;

    // �ж�������Ϣ�Ƿ���ȷ
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

    // ��������ֱ�ӻ�ȡ֡����
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

    // Ŀǰ��û�����ݿɻ�ȡ��ֱ���˳�...
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

    // �ṩƫ�ƺ�Ļ���������˽��Э��ʹ��
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

    // �ж�������Ϣ�Ƿ���ȷ
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

    // ��������ֱ�ӻ�ȡ֡����
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
    int is_find = 0;		//1��ʾ�ҵ�һ��ͬ��������2��ʾ�ҵ�һ��������

    // �����Ƿ���ڿ��õ�������
    for( index = 0 ; index < ITASKCNT ; index ++ )
    {
        pTaskTemp = (pTaskInfo)((char*)pTaskHead + sizeof( TaskInfo ) * index) ;
        pthread_mutex_lock(&pTaskTemp->m_Capturelock);
        //��ֹmodeΪ��ʼ����0ֵʱ��Ϊ���û�ʹ�ã�����ֻ������������mode��ͬ������Ϊ����������ͬ������ͬһ������ID
        if( (pTaskTemp->iValid > 0) && (pTaskTemp->iFrameMode == iFrameMode))
        {
            is_find = 1;
            break;
        }
        else if(pTaskTemp->iValid == 0)//��ǰ�ҵ�һ��δʹ�õ������ȼ�¼�������������û���ҵ�ͬ�������������������Ŵ���������
        {
            // ��ȡ�����õ�������
            if(0 == is_find)
            {
                is_find = 2;
                find_index = index;
            }
        }
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
    }

    //δ�ҵ��������񣬷���ʧ��
    if( 0 == is_find )
    {
        return -1 ;
    }

    //�ҵ���ͬ���������û�����1����
    if(is_find == 1)
    {
        pTaskTemp->iusr_num++ ;
        *iTaskId	= pTaskTemp->iTaskId ;
        pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
        return 0;
    }

    //�ҵ������������������
    // ������������ֱ��ʹ����
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

    /* hzg 20170525 09:01:03 ��Ƶ֡����Ҫϵͳͷ֡���� */
    
    *iTaskId	= pTaskTemp->iTaskId ;
    AUDIO_Start();
    pthread_mutex_unlock(&pTaskTemp->m_Capturelock);
    return 0 ;
}

CSYSPACKET_FUNCTION_OUTPUT int AUDIO_DelTaskId(unsigned int iTaskId)
{
    int			index ;
    pTaskInfo	pTaskTemp ;

    // �ж�������Ϣ�Ƿ���ȷ
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
 



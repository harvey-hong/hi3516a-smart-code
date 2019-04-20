#ifndef _LIST_MANAGE_H__
#define _LIST_MANAGE_H__

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_remote_agent_def.h"
#include "ws_comm_data.h"
#include "ws_utility_api.h"
#include "ws_common.h"

using ws_soft::ws_frame_info;
using ws_utility::WS_ERR; 
using ws_utility::ws_module_id;

namespace ws_listnode_manage	
{
typedef struct
{
    ws_module_id usr_id;
    int usr_num;
} ws_list_node_usr;

typedef struct list_node
{
    WS_U32              node_idx;          
    WS_UCHAR          *buffadd;      
    WS_UCHAR          *buff_naked_frame;
    
    ws_frame_info   	frame_info;  
    list_node           *pre;
    list_node           *next;

    int                     usr_cnt ;
    int                     bUsed ;                //标记节点占用
    int                     iFirstBufIndex ;    //保存这个节点记录的缓冲区的起始位置与首地址偏移了多少个分片
    int                     iBufLen ;//记录这个缓冲区要占用多少个分片
    WS_BOOL          		bHaveData;// 标记这个节点是否有数据从Client上传;
    WS_BOOL          		bClear;// 通道断开时，置为清除标志，使之下次不能被获取;
} list_node;

class ws_agent_list
{
public:
    WS_ERR set_new_magic(WS_U32 pmagic);            
    WS_ERR get_recv_pos(int len,WS_UCHAR ** frame_data);
    WS_ERR delete_node(list_node *node);
    WS_ERR delete_all_node();
    WS_ERR push_data(const ws_frame_info *frame_info, WS_UCHAR *buffadd);
    WS_ERR push_data_one(const ws_frame_info *frame_info, int *part_addr, int *part_len, int PartNum , int FrameLen);
    WS_ERR first_get_list_data(ws_module_id mode, ws_frame_info *frame_info, WS_UCHAR **frame_data, WS_U32 *node_idx); 
    WS_ERR get_list_data(ws_module_id mode, ws_frame_info *frame_info, WS_UCHAR **frame_data, WS_U32 last_node_idx, WS_U32 *cur_node_idx);
    WS_ERR rel_node(ws_module_id usr_id, WS_U32 node_idx);
    void change_local_pts();

    WS_ERR get_bit_rate(ws_soft::STREAM_SPEED speed, WS_U32 *get_kb);

    WS_BOOL get_connect_status();
    
private:
    list_node *find_node_by_idx(WS_U32 node_idx);
    list_node *find_next_i_node_by_idx(WS_U32 node_idx);

    WS_ERR add_new_node(const ws_frame_info *frame_info, int *part_addr, int *part_len, int PartNum , int FrameLen, int iFirstSlice);
    WS_ERR has_enough_slice(int iNeed, int *iFirst);
    WS_ERR has_enough_space(int iNeed, int *iFirst);
    
    //同步时间
    void change_node_pts(list_node *node, struct timeval* cur_time, struct timeval* ipc_delta_time);
    void update_real_info(const ws_frame_info *frame_info, ws_utility::ws_rec_real_info *real_info);

private:
    WS_CHAR m_list_name[32];

    WS_U32      m_node_idx;

    const WS_U32 m_max_node_num;
    WS_U32      m_node_num;//当前Client层请求占用的节点数

    WS_U32      m_last_frame_no;//最后一帧的帧号

    WS_U32      m_last_i_nod_idx;//最后一个i帧的节点号

    WS_U32      m_last_i_frame_no;   /*仅仅 记录I帧的序号 */

    list_node   *m_head;//所有需要添加的数据都往后面添加
    list_node   *m_tail;//上一帧的信息 用于判断

    ws_utility::ws_lock     *m_push_lock;

    struct timeval  			m_last_frame_time_ipc;
    struct timeval			m_last_frame_time_nvr;

    WS_BOOL                  	m_bFirstFrame; //为真代表新的连接第一次接收到帧

	ws_utility::ws_rec_real_info    m_real_info;
    list_node                   *pList ;
    WS_UCHAR                *pBufAddr;
    int                             *iBufStatus;

    int                             iBufTotalLen ;//分配的缓冲区总的分片数
    int 				m_iLen;		//记录上一次保存的记录个数 
    int                         m_magic;

    /* 统计比特率相关信息*/
    WS_U32                  m_main_total_size;
    time_t                     m_main_start_time;
    WS_U32                  m_main_bps;
    WS_U32                  m_main_I_bps;
    WS_U32                  m_main_total_I_size;

    WS_BOOL                m_stream_connect_ok;             /*for digit channel */
public:
    ws_agent_list(const char *list_name, WS_U32 max_node_num);
    ws_agent_list(const char *list_name, WS_U32 max_node_num, int Mode);   
    ~ws_agent_list();
    const char *class_name()
    {
        return m_list_name;
    };

};

}



#endif


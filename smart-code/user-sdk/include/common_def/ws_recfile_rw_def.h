#ifndef _WS_RECFILE_RW_DEF_H_
#define _WS_RECFILE_RW_DEF_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_data.h"
#include "ws_comm_flist.h"

using ws_utility::WS_ERR;

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef enum
{
    WS_SEEK_TO_PRE,
    WS_SEEK_TO_NEXT,
} ws_seek_pos_mode;

class ws_recfile_writer
{
public:
    virtual WS_ERR open(const WS_CHAR *file_name, WS_BOOL is_save_i_pos = WS_FALSE,WS_CHAR *idx_name = NULL) = 0;   
    virtual WS_ERR write(const ws_frame_info *frame_info, const void *frame_data, int *cur_file_size, WS_BOOL check_enc_size = WS_TRUE) = 0;
    virtual WS_VOID  insert_empty_frame(ws_frame_info *last_frame_info) =0; 
    virtual WS_ERR close() = 0;

public:
    virtual ~ws_recfile_writer() {};
};

class ws_recfile_reader
{
public:
    virtual WS_ERR open(const WS_CHAR *file_name) = 0;
    virtual WS_ERR close() = 0;
    virtual WS_ERR get_file_info(ws_soft::ws_rec_file_info *file_info) = 0;

    //读取完整的一帧，如果buf_size不够，丢掉该帧，直到下一帧成功，如果到了文件尾返回失败
    virtual WS_ERR read_full(ws_parser_read_mode read_mode, ws_frame_info *frame_info, void *data_buf, size_t buf_size) = 0;

    virtual WS_ERR seek_by_time(const struct timeval *time, ws_seek_pos_mode seek_mode) = 0;

    virtual WS_ERR seek_to_next_i() = 0;
    virtual WS_ERR seek_to_pre_i() = 0;
    virtual WS_ERR seek_to_first_i()= 0;
    virtual WS_ERR seek_to_last_i() = 0;

public:
    virtual ~ws_recfile_reader() {};
};
    
class ws_recfile_converter		
{
public:
    virtual WS_ERR recfile_type_convert(const WS_CHAR *read_name,const WS_CHAR *write_path)=0;
    virtual WS_ERR  recfile_type_convert(const WS_CHAR *read_name,const WS_CHAR *write_path,int channel_num)=0;
    virtual WS_U32  get_file_convert_process()=0; 
    virtual WS_VOID file_rw_stop()=0;
public:
    virtual ~ws_recfile_converter() {};
};						

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif //#ifndef _WS_RECFILE_MANAGE_API_H_



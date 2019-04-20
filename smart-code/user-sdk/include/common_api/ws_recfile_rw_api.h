#ifndef _WS_RECFILE_RW_API_H_
#define _WS_RECFILE_RW_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_sys.h" 

#include "ws_recfile_rw_def.h"

using ws_utility::WS_ERR;
using ws_utility::ws_recfile_format;
using namespace ws_soft;   


#ifdef __cplusplus
extern "C" {
namespace ws_rfrw  
{
#endif

    WS_ERR recfrw_init();
    ws_recfile_writer *recfrw_new_file_writer(ws_utility::ws_recfile_format format);    //指明存储格式
    //对于需要读取视频数据的解析器，将load_i_node置为WS_TRUE，在开文件的时候会自动导入私有索引信息，
    //对于不需要读取视频数据的解析器(回放音频通道)，将load_i_node置为WS_FALSE，在开文件的时候不会导入私有索引信息，
    ws_recfile_reader *recfrw_new_file_reader(WS_BOOL load_i_node); //自适应支持的格式
    ws_recfile_converter *recfrw_new_file_converter(ws_recfile_format input_format ,ws_recfile_format output_format);   

    //change by khs 2017.3.30 start
    WS_ERR parser_manage_malloc_file_parser(WS_PARSER_ID *parser_id);
    WS_ERR parser_manage_free_file_pareser(WS_PARSER_ID parser_id);
    WS_ERR parser_manage_set_parser_file(WS_PARSER_ID parser_id, const char *file_name);
    WS_ERR parser_manage_seek_parser_time(WS_PARSER_ID parser_id, time_t time);
    WS_ERR parser_manage_set_parser_read_mode(WS_PARSER_ID parser_id, WS_U32 mode);
    WS_ERR parser_manage_parser_frame(WS_PARSER_ID parser_id, char *rd_buf, size_t buf_size, ws_soft::ws_frame_info *frame_info);
    WS_ERR parser_manage_parser_get_file_info(WS_PARSER_ID parser_id, ws_soft::ws_rec_file_info *file_info);
    WS_ERR parser_manage_close_parser_file(WS_PARSER_ID parser_id);
    //change by khs 2017.3.30 end

#ifdef __cplusplus
}//namespace ws_rfrw {
}//extern "C" {
#endif

#endif //#ifndef _WS_RECFILE_MANAGE_API_H_


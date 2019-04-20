#ifndef _WS_HISTORY_API_H_
#define _WS_HISTORY_API_H_

// add by lhh 20151109 start : sync to SVN
    
#include <sys/time.h>
#include "ws_comm_sys.h"
#include "ws_recfile_rw_def.h"
//#include "../AVL/CChannelManager.h"

#ifdef __cplusplus
extern "C" {
using namespace ws_soft;
using namespace ws_utility;
#endif

 //Modified by qqy,start at 2017-03-07 19:08:45
//==================================²éÑ¯Â¼Ïñ=============================
int avl_inquiry_rec_by_month(int nCh,const ws_time_struct *time, WS_U32 *mask);
int avl_inquiry_rec_by_day(int nCh,const ws_time_struct *time, ws_rec_file_inquiry_type file_type, ws_rec_file_inquiry_result *result);
int avl_free_inquiry_rec_result(int nCh,const ws_rec_file_inquiry_result *result);
int avl_inquiry_rec_by_time(int nCh,const ws_time_struct *start_time,const ws_time_struct *end_time, ws_rec_file_inquiry_type file_type, ws_rec_file_inquiry_result *result);

//==================================²éÑ¯½ØÍ¼=============================
int avl_inquiry_snap_by_month(int nCh,const ws_time_struct *time, WS_U32 *mask);
int avl_inquiry_snap_by_day(int nCh,const ws_time_struct *time, ws_snap_file_inquiry_type file_type, ws_snap_file_inquiry_result *result);
int avl_free_inquiry_snap_result(int nCh,const ws_snap_file_inquiry_result *result);
int avl_inquiry_snap_by_time(int nCh,const ws_time_struct *start_time,const ws_time_struct *end_time, ws_snap_file_inquiry_type file_type, ws_snap_file_inquiry_result *result);
 //Modified by qqy,end at 2017-03-07 19:08:46

int model_HisStream_NewTaskId(unsigned int *iTaskId);
int model_HisStream_SetFile(unsigned int iTaskId ,  const char *file_name);
int model_HisStream_SetMode( unsigned int iTaskId ,  unsigned int Mode);
int model_HisStream_SetTime(unsigned int iTaskId , unsigned int time);
int model_HisStream_GetOneFrame( unsigned int iTaskId,   char *buffer,  int bufLen, ws_frame_info *m_frame_info);
int model_HisStream_GetFileInfo( unsigned int iTaskId,  unsigned int * iFileFirstFrameNo,  unsigned int * iFileLastFrameNo,  struct timeval* start_time,  struct timeval* end_time,  int * iFileLen);
int model_HisStream_DelTaskId( unsigned int iTaskId);

#ifdef __cplusplus
}//extern "C" {
#endif

// add by lhh 20151109 end : sync to SVN

#endif  

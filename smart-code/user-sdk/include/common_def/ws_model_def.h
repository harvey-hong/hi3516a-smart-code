#ifndef _WS_MODEL_DEF_H_
#define _WS_MODEL_DEF_H_

#include "ws_comm_type.h"

using ws_utility::WS_ERR;


#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef WS_ERR(*set_hyp_server_restart)();
typedef int (*set_language)(const char *language);
typedef WS_ERR (*set_chn_name)(WS_USR_HAND hand, WS_U32 ch, const char *name_buf);

typedef int (*reset_admin)();	
typedef WS_ERR (*repair_database)(void *usr_para);

typedef int (*get_support_language_num)(int *num);
typedef int (*get_support_language_name)(int idx, char *name, size_t name_size);
typedef const char* (*get_time_zone_name)(WS_USR_HAND hand, int idx);

// change by linhh 20170316 : 采取数组进行保存与调用
#if defined (_V_3_1_5_ZGF_FORCE_TO_QUIT_)
typedef WS_ERR (* set_protocal_stop)(WS_USR_HAND usr_hand);
#endif

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_MODEL_DEF_H_



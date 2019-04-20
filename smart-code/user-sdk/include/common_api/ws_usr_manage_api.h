#ifndef _WS_USR_MANAGE_API_H_
#define _WS_USR_MANAGE_API_H_

#include "ws_common.h"        
#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_usr_manage_def.h"

using ws_utility::WS_ERR;
using ws_soft::ws_authority;	
#ifdef __cplusplus
extern "C" {
namespace ws_usrm
{
#endif

WS_ERR usrm_init(int max_group_num, int max_usr_num);
WS_ERR usrm_get_group_num(WS_U32 *group_num);   
WS_ERR usrm_get_group_name(WS_U32 group_idx, WS_CHAR *group_name, size_t name_size);   
WS_ERR usrm_add_group(WS_USR_HAND hand, const WS_CHAR *group_name, const ws_soft::ws_authority *authority);
WS_ERR usrm_del_group(WS_USR_HAND hand, const WS_CHAR *group_name);
WS_ERR usrm_get_group_authority(const WS_CHAR *group_name, ws_authority *authority);
WS_ERR usrm_set_group_authority(WS_USR_HAND hand, const WS_CHAR *group_name, const ws_soft::ws_authority *authority);
WS_ERR usrm_get_usr_num(WS_U32 *usr_num);   
WS_ERR usrm_get_usr_name(WS_U32 usr_idx, WS_CHAR *usr_name, size_t name_size, WS_CHAR *passwd = NULL, size_t passwd_size = 0);  
WS_ERR usrm_local_login(const WS_CHAR *usr_name, const char *password, WS_USR_HAND *hand);  
WS_ERR usrm_remote_login_protocol(const WS_CHAR *usr_name,const char *password,const char* ip,const char *mac,ws_utility::login_protocol_type protocol_type,WS_USR_HAND *hand);
/* hzg 20170329 input param NOT use pointer type start */
WS_ERR usrm_check_login(const WS_CHAR *usr_name, const char *password, const char *ip, const char *mac, WS_USR_HAND hand);
/* hzg 20170329 input param NOT use pointer type end */

WS_ERR usrm_logout(WS_USR_HAND hand);   
WS_BOOL usrm_is_supper_user(WS_USR_HAND hand);
WS_BOOL usrm_is_supper_user_for_name(const char *name);
#if defined (_V_3_1_5_ZGF_FORCE_TO_QUIT_)
WS_ERR  usrm_find_all_usr(WS_USR_HAND usr_hand, ws_utility::ws_user_info *usr_node,WS_U32 *count);
WS_ERR usr_get_login_num(WS_USR_HAND usr_hand,WS_U32 *count);
WS_ERR find_match_login_usr(WS_USR_HAND usr_hand);
#endif 
WS_BOOL usrm_is_local_login(WS_USR_HAND hand);
WS_ERR usrm_get_login_grp_name(WS_USR_HAND hand, WS_CHAR *grp_name, int name_length);
WS_ERR usrm_get_login_usr_info(WS_USR_HAND hand, ws_soft::ws_usr_info_login *usr_info);
WS_ERR usrm_get_login_usr_info_protocol(WS_USR_HAND hand, ws_soft::ws_usr_info_login_protocol *usr_info);
WS_ERR usrm_add_usr(WS_USR_HAND hand, const WS_CHAR *usr_name, const char *password, const char *group_name);  
WS_ERR usrm_del_usr(WS_USR_HAND hand, const WS_CHAR *usr_name);

WS_ERR usrm_set_usr_passwd(WS_USR_HAND hand, const char *login_password, const WS_CHAR *usr_name, const char *new_passwd);
WS_ERR usrm_change_usr_group(WS_USR_HAND hand, const WS_CHAR *usr_name, const char *group_name);   
WS_ERR usrm_get_usr_state(const WS_CHAR *usr_name, ws_soft::ws_usr_state_info *info);    
WS_ERR usrm_get_usr_password(WS_USR_HAND hand, WS_CHAR *password, size_t password_size); 
WS_ERR usrm_get_usr_password_byname(const char *usr_name, WS_CHAR *password, size_t password_size); 

WS_ERR usr_reset_admin();

WS_ERR usrm_check_authority(WS_USR_HAND hand, ws_soft::ws_authority_check_type type, WS_U32 sub_ch);

WS_ERR usrm_load_grp(const WS_CHAR *group_name, const ws_authority *authority);
WS_ERR usrm_load_usr(const WS_CHAR *usr_name, const char *password, const char *group_name);

/* add by zhangmq 20180527 start*/
//add zmq 添加分离cfg_manage模块中有关用户管理的接口[2018-05-02 12:22]
WS_ERR cfg_manage_get_grp_num(WS_U32 *num);
WS_ERR cfg_manage_save_grp_num(WS_U32 num);

WS_ERR cfg_manage_get_grp_info(WS_U32 grp_idx, char *name, size_t name_size, ws_authority *authority);
WS_ERR cfg_manage_save_grp_info(WS_U32 grp_idx, const char *name, const ws_authority *authority);

WS_ERR cfg_manage_get_usr_num(WS_U32 *num);
WS_ERR cfg_manage_save_usr_num(WS_U32 num);

WS_ERR cfg_manage_get_usr_info(WS_U32 usr_idx,char *usr_name, size_t usr_name_size,
         char *passwd, size_t passwd_size, char *grp_name, size_t grp_name_size);
WS_ERR cfg_manage_save_usr_info(WS_U32 usr_idx, const char *usr_name, const char *passwd, const char *grp_name);

//add zmq 添加重置admin的接口[2018-05-02 17:28]
WS_ERR cfg_manage_reset_admin();

//add zmq 从model层移入usr manage 模块的API层,由于有效数是有问题的
void save_group_cfg();
void save_usr_cfg();

//add zmq 增加获取有效用户组数的接口,仅为兼容user manage模块中的内存文件方式
WS_ERR usrm_get_valid_group_num(WS_U32 *group_num);
WS_ERR usrm_get_valid_usr_num(WS_U32 *usr_num);
/* add by zhangmq 20180527 end*/

#ifdef __cplusplus
}//namespace ws_usrm{
}//extern "C" {
#endif

#endif  //_WS_USR_MANAGE_API_H_



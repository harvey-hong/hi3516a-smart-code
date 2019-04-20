#ifndef _WS_DEV_PROBE_DEF_H_
#define _WS_DEV_PROBE_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"
#include "ws_comm_sys.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

typedef struct ip_node_info
{
    WS_CHAR 			ipv4[ws_utility::WS_NVR_IPV4_STRING_LEN];
    struct ip_node_info 	*next;
} ws_ip_node_info;

typedef struct
{
    ws_utility::ws_device_type dev_type;        //设备类型
    ws_utility::ws_connet_protocol protocol;    //连接的协议类型

    char ipv4[ws_utility::WS_NVR_IPV4_STRING_LEN];
    char ipv6[ws_utility::WS_NVR_IPV6_STRING_LEN];
    char mac[ws_utility::WS_NVR_MAC_STRING_LEN];

    //------------------------ ws设备有效，其他厂家设备用默认值或者固定值 ---------------
    ws_utility::ws_soft_version base_version;   //基础版本
    ws_utility::ws_soft_version soft_version;   //软件版本
    char    soft_version_str[32];   //以字符串的形式填充版本信息和日期

    char    product_name[ws_utility::WS_MAX_DEV_NAME_LENTH+17];   //产品名称   
    char    serial_no[36];  //序列号
    int     video_ch_num;   //视频通道数目

    unsigned short cmd_port;
    unsigned short media_port;
    unsigned short http_port;   //预留着
} ws_remote_dev_info;

//针对不同的协议，返回的应答信息可能不同，有的全有的缺，专门声明一个带标志位的结构体，用来兼容不同的协议返回的信息，
//如果标志位为FALSE，表示该项信息无法获取，设备探测的时候不修改该项信息
typedef struct
{
    ws_utility::ws_device_type dev_type;        //设备类型
    WS_BOOL dev_type_sta;

    ws_utility::ws_connet_protocol protocol;    //连接的协议类型
    WS_BOOL protocol_sta;

    char ipv4[ws_utility::WS_NVR_IPV4_STRING_LEN];
    WS_BOOL ipv4_sta;

    char ipv6[ws_utility::WS_NVR_IPV6_STRING_LEN];
    WS_BOOL ipv6_sta;

    char mac[ws_utility::WS_NVR_MAC_STRING_LEN];
    WS_BOOL mac_sta;

    //------------------------ ws设备有效，其他厂家设备用默认值或者固定值 ---------------
    ws_utility::ws_soft_version base_version;   //基础版本
    WS_BOOL base_version_sta;

    ws_utility::ws_soft_version soft_version;   //软件版本
    WS_BOOL soft_version_sta;

    char    product_name[32];   //产品名称
    WS_BOOL product_name_sta;

    char    serial_no[36];  //序列号
    WS_BOOL serial_no_sta;

    int     video_ch_num;   //视频通道数目
    WS_BOOL video_ch_num_sta;

    unsigned short cmd_port;
    WS_BOOL cmd_port_sta;

    unsigned short media_port;
    WS_BOOL media_port_sta;

    unsigned short http_port;   //预留着
    WS_BOOL http_port_sta;

    char    soft_version_str[32];   //以字符串的形式填充版本信息和日期
    WS_BOOL soft_version_str_sta;
} ws_remote_dev_info_sta;


#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_MODEL_DEF_H_



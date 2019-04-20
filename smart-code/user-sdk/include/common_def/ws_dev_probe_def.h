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
    ws_utility::ws_device_type dev_type;        //�豸����
    ws_utility::ws_connet_protocol protocol;    //���ӵ�Э������

    char ipv4[ws_utility::WS_NVR_IPV4_STRING_LEN];
    char ipv6[ws_utility::WS_NVR_IPV6_STRING_LEN];
    char mac[ws_utility::WS_NVR_MAC_STRING_LEN];

    //------------------------ ws�豸��Ч�����������豸��Ĭ��ֵ���߹̶�ֵ ---------------
    ws_utility::ws_soft_version base_version;   //�����汾
    ws_utility::ws_soft_version soft_version;   //����汾
    char    soft_version_str[32];   //���ַ�������ʽ���汾��Ϣ������

    char    product_name[ws_utility::WS_MAX_DEV_NAME_LENTH+17];   //��Ʒ����   
    char    serial_no[36];  //���к�
    int     video_ch_num;   //��Ƶͨ����Ŀ

    unsigned short cmd_port;
    unsigned short media_port;
    unsigned short http_port;   //Ԥ����
} ws_remote_dev_info;

//��Բ�ͬ��Э�飬���ص�Ӧ����Ϣ���ܲ�ͬ���е�ȫ�е�ȱ��ר������һ������־λ�Ľṹ�壬�������ݲ�ͬ��Э�鷵�ص���Ϣ��
//�����־λΪFALSE����ʾ������Ϣ�޷���ȡ���豸̽���ʱ���޸ĸ�����Ϣ
typedef struct
{
    ws_utility::ws_device_type dev_type;        //�豸����
    WS_BOOL dev_type_sta;

    ws_utility::ws_connet_protocol protocol;    //���ӵ�Э������
    WS_BOOL protocol_sta;

    char ipv4[ws_utility::WS_NVR_IPV4_STRING_LEN];
    WS_BOOL ipv4_sta;

    char ipv6[ws_utility::WS_NVR_IPV6_STRING_LEN];
    WS_BOOL ipv6_sta;

    char mac[ws_utility::WS_NVR_MAC_STRING_LEN];
    WS_BOOL mac_sta;

    //------------------------ ws�豸��Ч�����������豸��Ĭ��ֵ���߹̶�ֵ ---------------
    ws_utility::ws_soft_version base_version;   //�����汾
    WS_BOOL base_version_sta;

    ws_utility::ws_soft_version soft_version;   //����汾
    WS_BOOL soft_version_sta;

    char    product_name[32];   //��Ʒ����
    WS_BOOL product_name_sta;

    char    serial_no[36];  //���к�
    WS_BOOL serial_no_sta;

    int     video_ch_num;   //��Ƶͨ����Ŀ
    WS_BOOL video_ch_num_sta;

    unsigned short cmd_port;
    WS_BOOL cmd_port_sta;

    unsigned short media_port;
    WS_BOOL media_port_sta;

    unsigned short http_port;   //Ԥ����
    WS_BOOL http_port_sta;

    char    soft_version_str[32];   //���ַ�������ʽ���汾��Ϣ������
    WS_BOOL soft_version_str_sta;
} ws_remote_dev_info_sta;


#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_MODEL_DEF_H_



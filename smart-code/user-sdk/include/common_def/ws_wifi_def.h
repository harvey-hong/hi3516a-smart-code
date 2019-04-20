#ifndef _WS_WIFI_DEF_H_
#define _WS_WIFI_DEF_H_

#include "ws_common.h"
#include "ws_comm_type.h"
#include "ws_network_def.h"

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

// 0-OPEN,1-SHARED,2-WPAPSK,3-WPA2PSK,4-WPANONE,5-WPA,6-WPA2
typedef enum
{
    AM_OPEN = 0,
    AM_SHARED,
    AM_WPAPSK,
    AM_WPA2PSK,
    AM_WPANONE,
    AM_WPA,
    AM_WPA2
} wifi_authentication;      //��֤��ʽ

// �����㷨 0-NONE,1-WEP,2-TKIP,3-AES
typedef enum
{
    ET_NONE = 0,
    ET_WEP,
    ET_TKIP,
    ET_AES
} wifi_encryption;          //���ܷ�ʽ


//!\brief �ȵ�֧�ֵĹ淶
// 1: legacy 11B only
// 2: legacy 11A only
// 3: legacy 11a/b/g mixed
// 4: legacy 11G only
// 5: 11ABGN mixed
// 6: 11N only
// 7: 11GN mixed
// 8: 11AN mixed
// 9: 11BGN mixed

typedef enum
{
    legacy_11_B_only = 0,
    legacy_11_A_only,
    legacy_11_a_b_g_mixed,
    legacy_11_g_only,
    ABGN_11_mixed,
    N_11_only,
    GN_11_mixed,
    AN_11_mixed,
    BGN_11_mixed,

} wifi_transmission_standard;

typedef enum
{
    key_1 = 0,
    key_2,
    key_3,
    key_4,
} wifi_password_value;


typedef struct
{
    char ip_address[ws_utility::WS_MAX_NETMASK_LEN];
    char subnet_mask[ws_utility::WS_MAX_NETMASK_LEN];
    char gateway[ws_utility::WS_MAX_GETWAY_LEN];
    char DNS_1[ws_utility::WS_MAX_DNS_LEN];
    char DNS_2[ws_utility::WS_MAX_DNS_LEN];
} ws_wifi_ip_info;

/*�������Ǹ�����ṹ�����ļ�����Ҫ������ֻ����һ�����룬��������೤���������ϲ㴦����ȷ���ٴ���*/
typedef struct
{
    char ssid[ws_utility::WS_MAX_SSID_LEN];
    //!\brief �ȵ�MAC��ַ
    char MacAddress[ws_utility::WS_NVR_MAC_STRING_LEN];
    wifi_authentication authentication;
    wifi_encryption encryption;                                 //�ȵ�����㷨
    wifi_password_value number_value;           //WEP ����(�ṹ��)���������ֵ  �Ժ�����������ܷ�ʽҲ��Ҫ���ƵĶ��� ����д�Ժ�Ķ�Ӧ�÷���Щ
    char password[ws_utility::WS_MAX_SSID_LEN];

} ws_wifi_ap_info;

typedef struct
{
    wifi_password_value wep_value;
    char wep_password[ws_utility::WS_MAX_WEP_LEN];
} ws_wep_password;

typedef struct
{
    char ssid[ws_utility::WS_MAX_SSID_LEN];
    wifi_authentication authentication;                             //�ȵ����֤�㷨
    wifi_encryption encryption;                                 //�ȵ�����㷨
    ws_wep_password wep_password;                   //wep����
    char wpa_password[ws_utility::WS_MAX_WPA_LEN];              //wap����
} ws_wifi_connect;

typedef struct
{
    char ssid[ws_utility::WS_MAX_SSID_LEN];
    char ap_mac_address[ws_utility::WS_NVR_MAC_STRING_LEN];     //MAC��ַ
    wifi_authentication authentication;                             //�ȵ����֤�㷨
    wifi_encryption encryption;                                 //�ȵ�����㷨
    int signal_quality;                             //�ź�����
    wifi_transmission_standard Signal_transmission_standard;                //�źŴ����׼
} ws_wifi_ap;                       //���������ȵ���Ϣ


typedef struct
{
    WS_BOOL work_status;
    WS_BOOL ip_mode;
    char        connect_ssid_name[ws_utility::WS_MAX_SSID_LEN];
    //ws_wifi_ip_info net_info;
    ws_local_connect_cfg net_info;
} ws_wifi_right_now_info;

typedef struct
{
    int bValid;

    // ����
    char szKey[ws_utility::WS_WLAN_MAX_KEY_LEN];
} WIFI_KEY;



typedef struct
{
    int bValid;
    int nDefKeyID;
    WIFI_KEY Key1;
    WIFI_KEY Key2;
    WIFI_KEY Key3;
    WIFI_KEY Key4;
    WIFI_KEY WPAKey;
} WIFI_KEY_CFG, *LPWIFI_KEY_CFG;

typedef enum
{
    AUTO,
    AD_HOC,
    MANAGED,//һ��Ӧ��Ϊ��ģʽ
    MASTER,
    REPERTER,
    SECONDARY,
    MONITOR,
    UNKNOWN_BUG,
} ws_wifi_net_format;

typedef struct
{
    //!\brief �Ƿ�����
    WS_BOOL bConnect;

    // !\brief �ȵ�����
    char szSSID[ws_utility::WS_MAX_SSID_LEN];

    //!\brief �ȵ�MAC��ַ
    char szMacAddress[ws_utility::WS_NVR_MAC_STRING_LEN];

    // ��������
    // 0 "Auto",
    // 1 "Ad-Hoc",
    // 2 "Managed", һ��Ӧ��Ϊ��ģʽ
    // 3 "Master",
    // 4 "Repeater",
    // 5 "Secondary",
    // 6 "Monitor",
    // 7 "Unknown/bug"
    ws_wifi_net_format nNetworkType;

    // ��֤ģʽ
    // 0-OPEN,1-SHARED,2-WPAPSK,3-WPA2PSK,4-WPANONE,5-WPA,6-WPA2
    wifi_authentication nAuthMode;

    // �����㷨 0-NONE,1-WEP,2-TKIP,3-AES
    wifi_encryption nEncrypType;

    // ��������
    WIFI_KEY_CFG struKeyCfg;
} WLAN_CONNECTION, *LPWLAN_CONNECTION;


typedef struct
{
    // !\brief �ȵ�����
    char szSSID[ws_utility::WS_MAX_SSID_LEN];

    //!\brief �ȵ�MAC��ַ
    char szMacAddress[ws_utility::WS_NVR_MAC_STRING_LEN];

    //!\brief �ȵ��ź�ǿ��
    int nQuality;

    //!0��ʾOpen,1��ʾShared,2��ʾWPAPSK, 3��ʾWPA2PSK, 4��ʾWPANONE(ad-hocģʽ),5��ʾWPA,6��ʾWPA2
    wifi_authentication nAuthentication;

    //! 0��ʾNONE 1��ʾWEP 2��ʾTKIP 3��ʾAES
    wifi_encryption nEncrypType;

    //!\brief �ȵ�֧�ֵĹ淶
    // 1: legacy 11B only
    // 2: legacy 11A only
    // 3: legacy 11a/b/g mixed
    // 4: legacy 11G only
    // 5: 11ABGN mixed
    // 6: 11N only
    // 7: 11GN mixed
    // 8: 11AN mixed
    // 9: 11BGN mixed
    wifi_transmission_standard nWirelessMode;
} WLAN_ACCESSPOINT, *LPWLAN_ACCESSPOINT;

typedef struct
{
    int total_ap_num;               //��ȡ�������ȵ���Ŀ
    WLAN_ACCESSPOINT wifi_ap[ws_utility::WS_MAX_AP_NUM];          //һ������ܻ�ȡ��ô����ȵ���Ϣ
} ws_wifi_inquiry_result;

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_WIFI_DEF_H_
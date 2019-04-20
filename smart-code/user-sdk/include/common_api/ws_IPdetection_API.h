#ifndef _WS_ARP_API_SERVER_H__
#define _WS_ARP_API_SERVER_H__

typedef struct 
{
    bool ip_status;
    bool ip_enable;
}get_ip_enable_status;

typedef struct
{
	char old_ip[16];
	char new_ip[16];
	bool ip_is_conflict;
}ip_conflict_event;

typedef void (*IPDetectionCallBack)(int a,void *Msg);

#ifdef __cplusplus
extern "C" {
#endif

    int IPDetection_Server_Start(get_ip_enable_status *GetIpMsg);
    int ipdetection_stop(void);
    int IPDetection_Server_Stop(void);
    int set_arp_ip(const char *ip);
    int set_arp_dhcp(bool status);
    int set_arp_ip_enable(bool enable);
    int Set_IPDetection_CallBackAPI(IPDetectionCallBack pFun);

#ifdef __cplusplus
}
#endif

#endif
 

 

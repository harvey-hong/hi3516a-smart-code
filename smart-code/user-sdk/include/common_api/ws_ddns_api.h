#ifndef _WS_DDNS_API_H_
#define _WS_DDNS_API_H_

#include <stdio.h>
#include "ws_network_def.h"
#include "ws_ddns_def.h"
#include "HieServer_Common.h"	

using namespace ws_soft;
#ifdef __cplusplus
extern "C" {
namespace ws_ddnsName{
#endif
		
const char* ws_ddns_lib_version();	//ªÒ»°∞Ê±æ∫≈
WS_DDNS_ERR ws_InitDDNS(ws_pri_dns_config *pri_dns);
WS_DDNS_ERR ws_startDDNS();
WS_DDNS_ERR ws_stopDDNS();
WS_DDNS_ERR ws_setUserDomain(const char *domain);
WS_DDNS_ERR ws_getUserDomain(char *domain,size_t domain_size);
WS_DDNS_ERR ws_getDefaultDomain(char *domain, size_t domain_size);
WS_DDNS_ERR ws_getServerDomain(char *domain, size_t domain_size);
WS_DDNS_ERR ws_setUpdateTime(int count);
WS_DDNS_ERR ws_getUpdateTime(int* count);
//WS_DDNS_ERR ws_DDNSCallBackAPI(DDNSCallBack pfun);                // del by linhh 20170418
connect_status ws_getDDNSConnectStatus();

#ifdef __cplusplus
}//end ws_ddnsName
}//extern "C" {
#endif

#endif

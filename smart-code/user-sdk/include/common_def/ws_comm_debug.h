#ifndef _WS_COMM_DEBUG_H_
#define _WS_COMM_DEBUG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 

#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif

#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif



#ifdef __cplusplus
extern "C" {
#endif

static void ws_print_local_time()
{
    time_t now;
    struct tm  *timenow;	
    char local_time[64];
    memset(local_time, 0, sizeof(local_time));
    time(&now);						
    timenow = localtime(&now);	
    snprintf(local_time, sizeof(local_time),"%04d-%02d-%02d %02d:%02d:%02d", 
        timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday,
        timenow->tm_hour, timenow->tm_min, timenow->tm_sec);
    printf("[%s]", local_time);
    return;
}

#define WS_PRINT_LOCAL_TIME ws_print_local_time();

#define WS_DUMP_RED printf("\033[0;32;31m")
#define WS_DUMP_YELLOW printf("\033[1;33m")
#define WS_DUMP_GREEN printf("\033[0;32;32m")
#define WS_DUMP_NONE printf("\033[m")

//通用信息，用白色输出，通过在makefile中指定是否支持..
#if defined (_SUPPORT_PRINT_NOTICE_)
#define GUI_PN(msg, args...)                do{WS_PRINT_LOCAL_TIME;printf("[GUI] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define GUI_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[GUI] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DEC_BOX_PN(msg, args...)            do{WS_PRINT_LOCAL_TIME;printf("[DEC_BOX] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DEC_BOX_CLASS_PN(msg, args...)  do{WS_PRINT_LOCAL_TIME;printf("[DEC_BOX] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define UPDATE_PN(msg, args...)             do{WS_PRINT_LOCAL_TIME;printf("[UPDATE] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define UPDATE_CLASS_PN(msg, args...)       do{WS_PRINT_LOCAL_TIME;printf("[UPDATE] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define BACKUP_PN(msg, args...)             do{WS_PRINT_LOCAL_TIME;printf("[BACKUP] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define BACKUP_CLASS_PN(msg, args...)       do{WS_PRINT_LOCAL_TIME;printf("[BACKUP] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define NSER_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[NSER] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define NSER_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[NSER] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define MODEL_PN(msg, args...)          do{WS_PRINT_LOCAL_TIME;printf("[MODEL] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define MODEL_CLASS_PN(msg, args...)    do{WS_PRINT_LOCAL_TIME;printf("[MODEL] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define LIVE_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[LIVE] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define LIVE_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[LIVE] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define REC_PN(msg, args...)            do{WS_PRINT_LOCAL_TIME;printf("[REC] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define REC_CLASS_PN(msg, args...)      do{WS_PRINT_LOCAL_TIME;printf("[REC] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PLAY_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[PLAY] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define PLAY_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[PLAY] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PLAT_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[PLAT] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define PLAT_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[PLAT] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define UTL_PN(msg, args...)            do{WS_PRINT_LOCAL_TIME;printf("[UTL] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define UTL_CLASS_PN(msg, args...)      do{WS_PRINT_LOCAL_TIME;printf("[UTL] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DISKM_PN(msg, args...)          do{WS_PRINT_LOCAL_TIME;printf("[DISKM] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define DISKM_CLASS_PN(msg, args...)    do{WS_PRINT_LOCAL_TIME;printf("[DISKM] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define RFRW_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[RFRW] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define RFRW_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[RFRW] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PROBE_PN(msg, args...)      do{WS_PRINT_LOCAL_TIME;printf("[PROBE] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define PROBE_CLASS_PN(msg, args...)    do{WS_PRINT_LOCAL_TIME;printf("[PROBE] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define RECFM_PN(msg, args...)          do{WS_PRINT_LOCAL_TIME;printf("[RECFM] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define RECFM_CLASS_PN(msg, args...)    do{WS_PRINT_LOCAL_TIME;printf("[RECFM] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define REMOTE_PN(msg, args...)         do{WS_PRINT_LOCAL_TIME;printf("[REMOTE] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define REMOTE_CLASS_PN(msg, args...)   do{WS_PRINT_LOCAL_TIME;printf("[REMOTE] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define LOGM_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[LOGM] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define LOGM_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[LOGM] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define USRM_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[USRM] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define USRM_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[USRM] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define NETWORK_PN(msg, args...)        do{WS_PRINT_LOCAL_TIME;printf("[NETWORK] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define NETWORK_CLASS_PN(msg, args...)  do{WS_PRINT_LOCAL_TIME;printf("[NETWORK] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define CFGM_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[CFGM] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define CFGM_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[CFGM] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SNET_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[SER_NET] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define SNET_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[SER_NET] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DST_PN(msg, args...)            do{WS_PRINT_LOCAL_TIME;printf("[DST] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define DST_CLASS_PN(msg, args...)  do{WS_PRINT_LOCAL_TIME;printf("[DST] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define HTTP_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[HTTP] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define HTTP_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[HTTP] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define HTTP_ALARM_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[HTTP_Alarm] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define HTTP_ALARM_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[HTTP_Alarm] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PTZ_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[PTZ] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define PTZ_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[PTZ] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SQLITE_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[SQLITE] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define SQLITE_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[SQLITE] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SQLTASKM_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[SQLTASKM] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define SQLTASKM_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[SQLTASKM] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define STATUS_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[STATUS] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define STATUS_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[STATUS] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)


#define THMA_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[THMA] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)											//add by yujun start 2015/10/14
#define THMA_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[THMA] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)     //add by yujun end 2015/10/14        

#define RTSP_SER_PN(msg, args...)       do{WS_PRINT_LOCAL_TIME;printf("[RTSP Server] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define TUTK_PN(msg, args...)           do{printf("[TUTK_P2P] %s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define P2P_PN(msg, args...)         do{WS_PRINT_LOCAL_TIME;printf("[WS_P2P] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define DANA_PN(msg,args...)           do{printf("[DANA_P2P] %s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)

#define GPIO_PN(msg, args...)           do{WS_PRINT_LOCAL_TIME;printf("[GPIO] %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define GPIO_CLASS_PN(msg, args...)     do{WS_PRINT_LOCAL_TIME;printf("[GPIO] %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

/*同步IPC上代码 linhh 20170511*/
#define TX_PN(msg,args...)           do{printf("[TENG_XUN] %s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)

#else //#if defined (_SUPPORT_PRINT_NOTICE_)
#define GUI_PN(msg, args...)
#define GUI_CLASS_PN(msg, args...)

#define DEC_BOX_PN(msg, args...)
#define DEC_BOX_CLASS_PN(msg, args...)

#define UPDATE_PN(msg, args...)
#define UPDATE_CLASS_PN(msg, args...)

#define BACKUP_PN(msg, args...)
#define BACKUP_CLASS_PN(msg, args...)

#define NSER_PN(msg, args...)
#define NSER_CLASS_PN(msg, args...)

#define MODEL_PN(msg, args...)
#define MODEL_CLASS_PN(msg, args...)

#define LIVE_PN(msg, args...)
#define LIVE_CLASS_PN(msg, args...)

#define REC_PN(msg, args...)
#define REC_CLASS_PN(msg, args...)

#define PLAY_PN(msg, args...)
#define PLAY_CLASS_PN(msg, args...)

#define PLAT_PN(msg, args...)
#define PLAT_CLASS_PN(msg, args...)

#define UTL_PN(msg, args...)
#define UTL_CLASS_PN(msg, args...)

#define DISKM_PN(msg, args...)
#define DISKM_CLASS_PN(msg, args...)

#define RFRW_PN(msg, args...)
#define RFRW_CLASS_PN(msg, args...)

#define PROBE_PN(msg, args...)
#define PROBE_CLASS_PN(msg, args...)

#define RECFM_PN(msg, args...)
#define RECFM_CLASS_PN(msg, args...)

#define REMOTE_PN(msg, args...)
#define REMOTE_CLASS_PN(msg, args...)

#define LOGM_PN(msg, args...)
#define LOGM_CLASS_PN(msg, args...)

#define USRM_PN(msg, args...)
#define USRM_CLASS_PN(msg, args...)

#define NETWORK_PN(msg, args...)
#define NETWORK_CLASS_PN(msg, args...)

#define CFGM_PN(msg, args...)
#define CFGM_CLASS_PN(msg, args...)

#define SNET_PN(msg, args...)
#define SNET_CLASS_PN(msg, args...)

#define DST_PN(msg, args...)
#define DST_CLASS_PN(msg, args...)

#define HTTP_PN(msg, args...)
#define HTTP_CLASS_PN(msg, args...)

#define HTTP_ALARM_PN(msg, args...)
#define HTTP_ALARM_CLASS_PN(msg, args...)

#define PTZ_PN(msg, args...)
#define PTZ_CLASS_PN(msg, args...)

#define SQLITE_PN(msg, args...)
#define SQLITE_CLASS_PN(msg, args...)

#define SQLTASKM_PN(msg, args...)
#define SQLTASKM_CLASS_PN(msg, args...)
//add  by mjq 201500807 start 

#define STATUS_PN(msg, args...)
#define STATUS_CLASS_PN(msg, args...)


//add  by mjq 201500807 end

#define THMA_PN(msg, args...)        	//add by yujun start 2015/10/14
#define THMA_CLASS_PN(msg, args...)     //add by yujun end 2015/10/14        
//ht 2016.2.16 start
#define RTSP_SER_PN(msg, args...)  
#define TUTK_PN(msg, args...)
#define P2P_PN(msg, args...)
#define DANA_PN(msg,args...)
/*同步IPC上代码 linhh 20170511*/
#define TX_PN(msg,args...) 
//ht 2016.2.16 end


//add  by mjq 20160323 start 
#define GPIO_PN(msg,args...)
#define GPIO_CLASS_PN(msg, args...)
//add  by mjq 20160323 end 



#endif //#if defined (_SUPPORT_PRINT_NOTICE_)

//警告信息，用黄色输出，通过在makefile中指定是否支持
#if defined (_SUPPORT_PRINT_WARNING_)
#define GUI_PW(msg, args...)        do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[GUI] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define GUI_CLASS_PW(msg, args...)  do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[GUI] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DEC_BOX_PW(msg, args...)        do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[DEC_BOX] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DEC_BOX_CLASS_PW(msg, args...)  do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[DEC_BOX] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define UPDATE_PW(msg, args...)         do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[UPDATE] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define UPDATE_CLASS_PW(msg, args...)   do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[UPDATE] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define BACKUP_PW(msg, args...)     do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[BACKUP] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define BACKUP_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[BACKUP] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define NSER_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[SER] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define NSER_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[SER] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define MODEL_PW(msg, args...)      do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[MODEL] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define MODEL_CLASS_PW(msg, args...)do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[MODEL] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define LIVE_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[LIVE] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define LIVE_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[LIVE] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define REC_PW(msg, args...)        do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[REC] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define REC_CLASS_PW(msg, args...)  do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[REC] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PLAY_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[PLAY] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PLAY_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[PLAY] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PLAT_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[PLAT] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PLAT_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[PLAT] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define UTL_PW(msg, args...)        do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[UTL] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define UTL_CLASS_PW(msg, args...)  do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[UTL] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DISKM_PW(msg, args...)      do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[DISKM] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DISKM_CLASS_PW(msg, args...)do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[DISKM] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define RFRW_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[RFRW] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define RFRW_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[RFRW] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PROBE_PW(msg, args...)      do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[PROBE] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PROBE_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[PROBE] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define RECFM_PW(msg, args...)      do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[RECFM] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define RECFM_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[RECFM] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define REMOTE_PW(msg, args...)         do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[REMOTE] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define REMOTE_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[REMOTE] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define LOGM_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[LOGM] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define LOGM_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[LOGM] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define USRM_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[USRM] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define USRM_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[USRM] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define NETWORK_PW(msg, args...)        do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[NETWORK] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define NETWORK_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[NETWORK] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define CFGM_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[CFGM] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define CFGM_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[CFGM] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SNET_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[SNET] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define SNET_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[SNET] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DST_PW(msg, args...)        do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[DST] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DST_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[DST] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define HTTP_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[HTTP] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define HTTP_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[HTTP] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define HTTP_ALARM_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[HTTP_Alarm] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define HTTP_ALARM_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[HTTP_Alarm] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PTZ_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[PTZ] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PTZ_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[PTZ] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SQLITE_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[SQLITE] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define SQLITE_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[SQLITE] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SQLTASKM_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[SQLTASKM] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define SQLTASKM_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[SQLTASKM] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define STATUS_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[STATUS] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define STATUS_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[STATUS] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define THMA_PW(msg, args...)         do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[THMA] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)							  //add by yujun start 2015/10/14
#define THMA_CLASS_PW(msg, args...)   do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[THMA] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)     //add by yujun end 2015/10/14        

#define RTSP_SER_PW(msg, args...)      do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[RTSP Server] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define TUTK_PW(msg, args...)           do{WS_DUMP_YELLOW;printf("[TUTK_P2P] WARNING!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define P2P_PW(msg, args...)         do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[WS_P2P] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DANA_PW(msg, args...)         do{WS_DUMP_YELLOW;printf("[DANA_P2P] WARNING!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DDNS_PW(msg, args...) 		do{printf("[DDNS] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define DDNS_CLASS_PW(msg, args...) do{printf("[DDNS] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)

#define GPIO_PW(msg, args...) 		do{WS_DUMP_YELLOW;printf("[GPIO] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define GPIO_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW;printf("[GPIO] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)

/*同步IPC上代码 linhh 20170511*/
#define TX_PW(msg, args...)         do{printf("[TENG_XUN] WARNING!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define BW_PW(msg, args...)       do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[BW] WARNING! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define BW_CLASS_PW(msg, args...) do{WS_DUMP_YELLOW; WS_PRINT_LOCAL_TIME;printf("[BW] WARNING! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#else

#define GUI_PW(msg, args...)
#define GUI_CLASS_PW(msg, args...)

#define DEC_BOX_PW(msg, args...)
#define DEC_BOX_CLASS_PW(msg, args...)

#define UPDATE_PW(msg, args...)
#define UPDATE_CLASS_PW(msg, args...)

#define BACKUP_PW(msg, args...)
#define BACKUP_CLASS_PW(msg, args...)

#define NSER_PW(msg, args...)
#define NSER_CLASS_PW(msg, args...)

#define MODEL_PW(msg, args...)
#define MODEL_CLASS_PW(msg, args...)

#define LIVE_PW(msg, args...)
#define LIVE_CLASS_PW(msg, args...)

#define REC_PW(msg, args...)
#define REC_CLASS_PW(msg, args...)

#define PLAY_PW(msg, args...)
#define PLAY_CLASS_PW(msg, args...)

#define PLAT_PW(msg, args...)
#define PLAT_CLASS_PW(msg, args...)

#define UTL_PW(msg, args...)
#define UTL_CLASS_PW(msg, args...)

#define DISKM_PW(msg, args...)
#define DISKM_CLASS_PW(msg, args...)

#define RFRW_PW(msg, args...)
#define RFRW_CLASS_PW(msg, args...)

#define PROBE_PW(msg, args...)
#define PROBE_CLASS_PW(msg, args...)

#define RECFM_PW(msg, args...)
#define RECFM_CLASS_PW(msg, args...)

#define REMOTE_PW(msg, args...)
#define REMOTE_CLASS_PW(msg, args...)

#define LOGM_PW(msg, args...)
#define LOGM_CLASS_PW(msg, args...)

#define USRM_PW(msg, args...)
#define USRM_CLASS_PW(msg, args...)

#define NETWORK_PW(msg, args...)
#define NETWORK_CLASS_PW(msg, args...)

#define CFGM_PW(msg, args...)
#define CFGM_CLASS_PW(msg, args...)

#define SNET_PW(msg, args...)
#define SNET_CLASS_PW(msg, args...)

#define DST_PW(msg, args...)
#define DST_CLASS_PW(msg, args...)

#define HTTP_PW(msg, args...)
#define HTTP_CLASS_PW(msg, args...)

#define HTTP_ALARM_PW(msg, args...)
#define HTTP_ALARM_CLASS_PW(msg, args...)

#define PTZ_PW(msg, args...)
#define PTZ_CLASS_PW(msg, args...)

#define SQLITE_PW(msg, args...)
#define SQLITE_CLASS_PW(msg, args...)

#define SQLTASKM_PW(msg, args...)
#define SQLTASKM_CLASS_PW(msg, args...)
//add  by mjq 201500807 start 
#define STATUS_PW(msg, args...)
#define STATUS_CLASS_PW(msg, args...)

//add  by mjq 201500807 end

#define THMA_PW(msg, args...)        	//add by yujun start 2015/10/14
#define THMA_CLASS_PW(msg, args...)     //add by yujun end 2015/10/14       
//ht 2016.2.16 start 
#define RTSP_SER_PW(msg, args...) 
#define TUTK_PW(msg, args...)
#define P2P_PW(msg, args...)
#define DANA_PW(msg, args...)

#define DDNS_PW(msg, args...)
#define DDNS_CLASS_PW(msg, args...)

/*同步IPC上代码 linhh 20170511*/
#define TX_PW(msg, args...) 
//ht 2016.2.16 end 

#define GPIO_PW(msg, args...)
#define GPIO_CLASS_PW(msg, args...)

#define BW_PW(msg, args...)       
#define BW_CLASS_PW(msg, args...) 

#endif //#if defined (_SUPPORT_PRINT_WARNING_)

//错误信息，用红色输出，通过在makefile中指定是否支持
#if defined (_SUPPORT_PRINT_ERROR_)
#define GUI_PE(msg, args...)        do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[GUI] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define GUI_CLASS_PE(msg, args...)  do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[GUI] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DEC_BOX_PE(msg, args...)        do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[DEC_BOX] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DEC_BOX_CLASS_PE(msg, args...)  do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[DEC_BOX] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define UPDATE_PE(msg, args...)         do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[UPDATE] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define UPDATE_CLASS_PE(msg, args...)   do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[UPDATE] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)


#define BACKUP_PE(msg, args...)         do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[BACKUP] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define BACKUP_CLASS_PE(msg, args...)   do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[BACKUP] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define NSER_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[NSER] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define NSER_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[NSER] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define MODEL_PE(msg, args...)      do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[MODEL] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define MODEL_CLASS_PE(msg, args...)do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[MODEL] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define LIVE_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[LIVE] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define LIVE_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[LIVE] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define REC_PE(msg, args...)        do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[REC] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define REC_CLASS_PE(msg, args...)  do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[REC] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PLAY_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[PLAY] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PLAY_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[PLAY] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PLAT_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[PLAT] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PLAT_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[PLAT] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define UTL_PE(msg, args...)        do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[UTL] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define UTL_CLASS_PE(msg, args...)  do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[UTL] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DISKM_PE(msg, args...)      do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[DISKM] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DISKM_CLASS_PE(msg, args...)do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[DISKM] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define RFRW_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[RFRW] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define RFRW_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[RFRW] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PROBE_PE(msg, args...)      do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[PROBE] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PROBE_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[PROBE] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define RECFM_PE(msg, args...)      do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[RECFM] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define RECFM_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[RECFM] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define REMOTE_PE(msg, args...)         do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[REMOTE] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define REMOTE_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[REMOTE] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define LOGM_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[LOGM] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define LOGM_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[LOGM] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define USRM_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[USRM] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define USRM_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[USRM] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define NETWORK_PE(msg, args...)        do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[NETWORK] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define NETWORK_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[NETWORK] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define CFGM_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[CFGM] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define CFGM_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[CFGM] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SNET_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[SNET] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define SNET_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[SNET] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DST_PE(msg, args...)        do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[DST] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DST_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[DST] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define HTTP_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[HTTP] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define HTTP_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[HTTP] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define HTTP_ALARM_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[HTTP_Alarm] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define HTTP_ALARM_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[HTTP_Alarm] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PTZ_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[PTZ] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PTZ_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[PTZ] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SQLITE_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[SQLITE] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define SQLITE_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[SQLITE] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SQLTASKM_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[SQLTASKM] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define SQLTASKM_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[SQLTASKM] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define STATUS_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[STATUS] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define STATUS_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[STATUS] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define THMA_PE(msg, args...)         do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[THMA] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)						 	   //add by yujun start 2015/10/14
#define THMA_CLASS_PE(msg, args...)   do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[THMA] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)     //add by yujun end 2015/10/14        

//ht 2016.2.16 start
#define CLIENT_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[CLIENT] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define RTSP_SER_PE(msg, args...)        do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[RTSP Server] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define TUTK_PE(msg, args...)           do{WS_DUMP_RED;printf("[TUTK_P2P] ERROR!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define P2P_PE(msg, args...)         do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[WS_P2P] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DANA_PE(msg,args...)          do{WS_DUMP_RED;printf("[DANA_P2P] ERROR!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DDNS_PE(msg, args...) 		do{printf("[DDNS] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define DDNS_CLASS_PE(msg, args...) do{printf("[DDNS] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)

/*同步IPC上代码 linhh 20170511 start*/
#define TX_PE(msg,args...)          do{printf("[TENG_XUN] ERROR!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define ONVIF_PE(msg,args...)          do{printf("[ONVIF] ERROR!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define UPNP_PE(msg,args...)          do{printf("[UPNP] ERROR!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define RTMP_PE(msg,args...)          do{printf("[RTMP] ERROR!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)

#define IPDetection_PE(msg,args...)   do{printf("[IPDetection] ERROR!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define CMSDiscovery_PE(msg,args...)   do{printf("[CMSDiscovery] ERROR!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
/*同步IPC上代码 linhh 20170511 end*/


#define GPIO_PE(msg, args...) 		do{WS_DUMP_RED;printf("[GPIO] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define GPIO_CLASS_PE(msg, args...) do{WS_DUMP_RED;printf("[GPIO] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)

#define BW_PE(msg, args...)       do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[BW] ERROR! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define BW_CLASS_PE(msg, args...) do{WS_DUMP_RED; WS_PRINT_LOCAL_TIME;printf("[BW] ERROR! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#else

#define GUI_PE(msg, args...)
#define GUI_CLASS_PE(msg, args...)

#define DEC_BOX_PE(msg, args...)
#define DEC_BOX_CLASS_PE(msg, args...)

#define UPDATE_PE(msg, args...)
#define UPDATE_CLASS_PE(msg, args...)

#define BACKUP_PE(msg, args...)
#define BACKUP_CLASS_PE(msg, args...)

#define NSER_PE(msg, args...)
#define NSER_CLASS_PE(msg, args...)

#define MODEL_PE(msg, args...)
#define MODEL_CLASS_PE(msg, args...)

#define LIVE_PE(msg, args...)
#define LIVE_CLASS_PE(msg, args...)

#define REC_PE(msg, args...)
#define REC_CLASS_PE(msg, args...)

#define PLAY_PE(msg, args...)
#define PLAY_CLASS_PE(msg, args...)

#define PLAT_PE(msg, args...)
#define PLAT_CLASS_PE(msg, args...)

#define UTL_PE(msg, args...)
#define UTL_CLASS_PE(msg, args...)

#define DISKM_PE(msg, args...)
#define DISKM_CLASS_PE(msg, args...)

#define RFRW_PE(msg, args...)
#define RFRW_CLASS_PE(msg, args...)

#define PROBE_PE(msg, args...)
#define PROBE_CLASS_PE(msg, args...)

#define RECFM_PE(msg, args...)
#define RECFM_CLASS_PE(msg, args...)

#define REMOTE_PE(msg, args...)
#define REMOTE_CLASS_PE(msg, args...)

#define LOGM_PE(msg, args...)
#define LOGM_CLASS_PE(msg, args...)

#define USRM_PE(msg, args...)
#define USRM_CLASS_PE(msg, args...)

#define NETWORK_PE(msg, args...)
#define NETWORK_CLASS_PE(msg, args...)

#define CFGM_PE(msg, args...)
#define CFGM_CLASS_PE(msg, args...)

#define SNET_PE(msg, args...)
#define SNET_CLASS_PE(msg, args...)

#define DST_PE(msg, args...)
#define DST_CLASS_PE(msg, args...)

#define HTTP_PE(msg, args...)
#define HTTP_CLASS_PE(msg, args...)

#define HTTP_ALARM_PE(msg, args...)
#define HTTP_ALARM_CLASS_PE(msg, args...)

#define PTZ_PE(msg, args...)
#define PTZ_CLASS_PE(msg, args...)

#define SQLITE_PE(msg, args...)
#define SQLITE_CLASS_PE(msg, args...)

#define SQLTASKM_PE(msg, args...)
#define SQLTASKM_CLASS_PE(msg, args...)
//add  by mjq 201500807 start 

#define STATUS_PE(msg, args...)
#define STATUS_CLASS_PE(msg, args...)


//add  by mjq 201500807 end

#define THMA_PE(msg, args...)        	//add by yujun start 2015/10/14
#define THMA_CLASS_PE(msg, args...)     //add by yujun end 2015/10/14       

//ht 2016.2.16 start
#define CLIENT_PE(msg, args...)
#define RTSP_SER_PE(msg, args...)  
#define TUTK_PE(msg, args...) 
#define P2P_PE(msg, args...) 
#define DANA_PE(msg,args...)

#define DDNS_PE(msg, args...) 
#define DDNS_CLASS_PE(msg, args...)

/*同步IPC上代码 linhh 20170511 start*/
#define TX_PE(msg,args...)
#define ONVIF_PE(msg,args...) 
#define UPNP_PE(msg,args...)
#define RTMP_PE(msg,args...) 
#define IPDetection_PE(msg,args...) 
#define CMSDiscovery_PE(msg,args...)
/*同步IPC上代码 linhh 20170511 end*/


#define GPIO_PE(msg, args...) 
#define GPIO_CLASS_PE(msg, args...)

#define BW_PE(msg, args...)     
#define BW_CLASS_PE(msg, args...) 

#endif //#if defined (_SUPPORT_PRINT_ERROR_)

//诊断型的调试信息，用绿色输出，通过在makefile中指定是否支持
#if defined (_SUPPORT_PRINT_DEBUG_)
//#define GUI_PD(msg, args...)        do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[GUI] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define GUI_PD(msg, args...)        do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[GUI] DEBUG! FILE=%s, FUN=%s, LINE=%d: ", __FILE__ , __FUNCTION__ , __LINE__ );printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define GUI_CLASS_PD(msg, args...)  do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[GUI] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DEC_BOX_PD(msg, args...)        do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[DEC_BOX] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DEC_BOX_CLASS_PD(msg, args...)  do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[DEC_BOX] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define UPDATE_PD(msg, args...)         do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[UPDATE] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define UPDATE_CLASS_PD(msg, args...)   do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[UPDATE] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)


#define BACKUP_PD(msg, args...)         do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[BACKUP] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define BACKUP_CLASS_PD(msg, args...)   do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[BACKUP] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define NSER_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[NSER] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define NSER_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[NSER] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define MODEL_PD(msg, args...)      do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[MODEL] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define MODEL_CLASS_PD(msg, args...)do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[MODEL] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define LIVE_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[LIVE] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define LIVE_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[LIVE] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define REC_PD(msg, args...)        do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[REC] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define REC_CLASS_PD(msg, args...)  do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[REC] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PLAY_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[PLAY] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PLAY_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[PLAY] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PLAT_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[PLAT] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PLAT_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[PLAT] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define UTL_PD(msg, args...)        do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[UTL] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define UTL_CLASS_PD(msg, args...)  do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[UTL] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DISKM_PD(msg, args...)      do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[DISKM] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DISKM_CLASS_PD(msg, args...)do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[DISKM] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define RFRW_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[RFRW] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define RFRW_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[RFRW] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PROBE_PD(msg, args...)      do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[PROBE] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PROBE_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[PROBE] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define RECFM_PD(msg, args...)      do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[RECFM] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define RECFM_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[RECFM] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define REMOTE_PD(msg, args...)         do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[REMOTE] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define REMOTE_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[REMOTE] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define LOGM_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[LOGM] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define LOGM_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[LOGM] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define USRM_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[USRM] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define USRM_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[USRM] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define NETWORK_PD(msg, args...)        do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[NETWORK] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define NETWORK_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[NETWORK] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define CFGM_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[CFGM] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define CFGM_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[CFGM] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SNET_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[SNET] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define SNET_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[SNET] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DST_PD(msg, args...)        do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[DST] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DST_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[DST] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define HTTP_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[HTTP] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define HTTP_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[HTTP] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define HTTP_ALARM_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[HTTP_Alarm] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define HTTP_ALARM_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[HTTP_Alarm] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define PTZ_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[PTZ] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define PTZ_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[PTZ] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SQLITE_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[SQLITE] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define SQLITE_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[SQLITE] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define SQLTASKM_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[SQLTASKM] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define SQLTASKM_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[SQLTASKM] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
//add  by mjq 201500807 start 

#define STATUS_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[STATUS] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define STATUS_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[STATUS] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

//add  by mjq 201500807 end

//add by yujun start 2015/10/14
#define THMA_PD(msg, args...)         do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[THMA] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)						 	   //add by yujun start 2015/10/14
#define THMA_CLASS_PD(msg, args...)   do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[THMA] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)     //add by yujun end 2015/10/14        
//add by yujun end 2015/10/14
//ht 2016.2.16 start
#define CLIENT_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[CLIENT] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define RTSP_SER_PD(msg, args...)        do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[RTSP Server] DEBUG! %s:%d ", __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define TUTK_PD(msg, args...)           do{WS_DUMP_GREEN;printf("[TUTK_P2P] DEBUG!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define P2P_PD(msg, args...)         do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[WS_P2P] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define DANA_PD(msg, args...)         do{WS_DUMP_GREEN;printf("[DANA_P2P] DEBUG!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)

#define DDNS_PD(msg, args...) 		do{printf("[DDNS] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define DDNS_CLASS_PD(msg, args...) do{printf("[DDNS] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)

/*同步IPC上代码 linhh 20170511 start*/
#define TX_PD(msg, args...)         do{printf("[TENG_XUN] DEBUG!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define ONVIF_PD(msg,args...)          do{printf("[ONVIF] DEBUG!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define UPNP_PD(msg,args...)          do{printf("[UPNP] DEBUG!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define RTMP_PD(msg,args...)          do{printf("[RTMP] DEBUG!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define IPDetection_PD(msg,args...)          do{printf("[IPDetection] DEBUG!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define CMSDiscovery_PD(msg,args...)          do{printf("[CMSDiscovery] DEBUG!%s %s() line-%d: ",__FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
/*同步IPC上代码 linhh 20170511 end*/



#define GPIO_PD(msg, args...) 		do{WS_DUMP_GREEN;printf("[GPIO] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)
#define GPIO_CLASS_PD(msg, args...) do{WS_DUMP_GREEN;printf("[GPIO] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);}while(0)


#define BW_PD(msg, args...)       do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[BW] DEBUG! %s::%s::%d: ", __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
#define BW_CLASS_PD(msg, args...) do{WS_DUMP_GREEN; WS_PRINT_LOCAL_TIME;printf("[BW] DEBUG! %s::%s::%s::%d: ", this->class_name(), __FILE__, __FUNCTION__, __LINE__);printf(msg, ##args);WS_DUMP_NONE;}while(0)
 //add by qqy,end at 2016-10-14 11:27:17
#else
#define GUI_PD(msg, args...)
#define GUI_CLASS_PD(msg, args...)

#define DEC_BOX_PD(msg, args...)
#define DEC_BOX_CLASS_PD(msg, args...)

#define UPDATE_PD(msg, args...)
#define UPDATE_CLASS_PD(msg, args...)

#define BACKUP_PD(msg, args...)
#define BACKUP_CLASS_PD(msg, args...)

#define NSER_PD(msg, args...)
#define NSER_CLASS_PD(msg, args...)

#define MODEL_PD(msg, args...)
#define MODEL_CLASS_PD(msg, args...)

#define LIVE_PD(msg, args...)
#define LIVE_CLASS_PD(msg, args...)

#define REC_PD(msg, args...)
#define REC_CLASS_PD(msg, args...)

#define PLAY_PD(msg, args...)
#define PLAY_CLASS_PD(msg, args...)

#define PLAT_PD(msg, args...)
#define PLAT_CLASS_PD(msg, args...)

#define UTL_PD(msg, args...)
#define UTL_CLASS_PD(msg, args...)

#define DISKM_PD(msg, args...)
#define DISKM_CLASS_PD(msg, args...)

#define RFRW_PD(msg, args...)
#define RFRW_CLASS_PD(msg, args...)

#define PROBE_PD(msg, args...)
#define PROBE_CLASS_PD(msg, args...)

#define RECFM_PD(msg, args...)
#define RECFM_CLASS_PD(msg, args...)

#define REMOTE_PD(msg, args...)
#define REMOTE_CLASS_PD(msg, args...)

#define LOGM_PD(msg, args...)
#define LOGM_CLASS_PD(msg, args...)

#define USRM_PD(msg, args...)
#define USRM_CLASS_PD(msg, args...)

#define NETWORK_PD(msg, args...)
#define NETWORK_CLASS_PD(msg, args...)

#define CFGM_PD(msg, args...)
#define CFGM_CLASS_PD(msg, args...)

#define SNET_PD(msg, args...)
#define SNET_CLASS_PD(msg, args...)

#define DST_PD(msg, args...)
#define DST_CLASS_PD(msg, args...)

#define HTTP_PD(msg, args...)
#define HTTP_CLASS_PD(msg, args...)

#define HTTP_ALARM_PD(msg, args...)
#define HTTP_ALARM_CLASS_PD(msg, args...)

#define PTZ_PD(msg, args...)
#define PTZ_CLASS_PD(msg, args...)

#define SQLITE_PD(msg, args...)
#define SQLITE_CLASS_PD(msg, args...)

#define SQLTASKM_PD(msg, args...)
#define SQLTASKM_CLASS_PD(msg, args...)
//add  by mjq 201500807 start 
#define STATUS_PD(msg, args...)
#define STATUS_CLASS_PD(msg, args...)
//add  by mjq 201500807 end

#define THMA_PD(msg, args...)        	//add by yujun start 2015/10/14
#define THMA_CLASS_PD(msg, args...)     //add by yujun end 2015/10/14       
//ht 2016.2.16 start
#define CLIENT_PD(msg, args...)
#define RTSP_SER_PD(msg, args...)
#define TUTK_PD(msg, args...)
#define P2P_PD(msg, args...)
#define DANA_PD(msg, args...) 

#define DDNS_PD(msg, args...)
#define DDNS_CLASS_PD(msg, args...)

/*同步IPC上代码 linhh 20170511 start*/
#define TX_PD(msg, args...) 
#define ONVIF_PD(msg,args...)
#define UPNP_PD(msg,args...)
#define RTMP_PD(msg,args...)
#define IPDetection_PD(msg,args...) 
#define CMSDiscovery_PD(msg,args...) 
/*同步IPC上代码 linhh 20170511 end*/
//ht 2016.2.16 end

#define GPIO_PD(msg, args...)
#define GPIO_CLASS_PD(msg, args...)

#define BW_PD(msg, args...)
#define BW_CLASS_PD(msg, args...)

#endif //#if defined (_SUPPORT_PRINT_DEBUG_)

#if defined (_SUPPORT_ASSERT_)
#define WS_ASSERT(expr)     \
    do{                         \
        if (!(expr)) {          \
            WS_DUMP_RED;        \
            WS_PRINT_LOCAL_TIME;printf("ASSERT!\n >File name: %s\n >Function: %s\n >Line No: %d\n >Condition: %s\n", \
                   __FILE__,__FUNCTION__, __LINE__, #expr);\
            WS_DUMP_NONE;       \
            exit(-1);\
        } \
    }while(0)
#else
#define WS_ASSERT(expr)
#endif


#ifdef __cplusplus
}//extern "C" {
#endif

#endif //#ifndef _WS_COMM_DEBUG_H_


#include "../inc/HYRtsp.h"
#include "../inc/GlobalObject.h"
#include "../inc/HYRtspCallBackFunc.h"
#include "ws_utility_api.h"
#include "ws_model_api.h"
#include "ws_rtsp_server.h"
#include "../inc/RtpRtspCommon.h"
#include "getlocalinfo.h"

using namespace GETLOCALINFO;
using namespace ws_utility; 

static WS_BOOL rtsp_api_init = WS_FALSE;
static pthread_mutex_t  rtsp_api_init_lock = PTHREAD_MUTEX_INITIALIZER;
static  pthread_t g_rtsp_pid = -1;


static  pthread_mutex_t     Rtspmask = PTHREAD_MUTEX_INITIALIZER ;
static  int  Rtspmask_state = 0;


void *HYRtsp_Start(void *para)
{
    int last_rtsp_port = 0;

    pthread_mutex_lock(&Rtspmask);
    if(1 == Rtspmask_state)
    {
        pthread_mutex_unlock(&Rtspmask);
        return NULL;
    }

    Rtspmask_state = 1;
    if (RET_CHECK_FAIL(TSingletons<CGlobalObject>::Instance().PrivateService().Start()))
    {
        Rtspmask_state = 0 ;
        pthread_mutex_unlock(&Rtspmask);
        return NULL;
    }

    pthread_mutex_unlock(&Rtspmask);

    while(1)
    {
    	int rtsp_port;
        int DeviceType;
        int ret = Get_DeviceType((DWORD)VALUE_INVALID,&DeviceType);
        if(0 != ret)
        {
            return NULL;
        }
        if(1 == DeviceType)
        {
            HY_DVR_LISTENPORT_CONF  cNetWorkConfig;
            memset(&cNetWorkConfig, 0, sizeof(cNetWorkConfig));
            DWORD dwBufferLen = sizeof(cNetWorkConfig);
            int ret = Get_local_port_info((DWORD)VALUE_INVALID, HY_DVR_GET_NETCFG, NETCFG_LISTENPORT_CONF, (BYTE *)&cNetWorkConfig, &dwBufferLen);
            if(0 != ret)
            {
                return NULL;
            }
            if(sizeof(cNetWorkConfig) != dwBufferLen)
            {
                return NULL;
            }

            rtsp_port = cNetWorkConfig.wRtpPort;
        }
        else
        {
            Port_Info m_dwport_info;
            memset(&m_dwport_info, 0, sizeof(m_dwport_info));
            DWORD dwBufferLen = sizeof(m_dwport_info);
            int ret = Get_local_port_info((DWORD)VALUE_INVALID, 0, 0, (BYTE *)&m_dwport_info, &dwBufferLen);
            if(0 != ret)
            {
                return NULL;
            }

            rtsp_port = m_dwport_info.rtsp_port;
        }

	 if(0 == last_rtsp_port)
        {
            last_rtsp_port = rtsp_port;
        }

        if(rtsp_port != last_rtsp_port)  // now detected port changed, need restart RTSP service
        {
            RTSP_SER_PD(" %s line-%d get new rtsp_port=[%d], old rtsp_port=[%d], need restart RTSP service !\n\r", __FILE__, __LINE__,rtsp_port, last_rtsp_port);
            pthread_mutex_lock(&Rtspmask);
            RTSPServer *pRtspServer = (RTSPServer *)TSingletons<CGlobalObject>::Instance().RtspServerHandle();
            if(NULL == pRtspServer)
            {
                pthread_mutex_unlock(&Rtspmask);
                RTSP_SER_PE("RtspServerHandle() is NULL, continue !! \n");
                usleep(1000*1000);
                continue;
            }

            shutdown(pRtspServer->ServerSocket, SHUT_RDWR);
            close(pRtspServer->ServerSocket);
            pRtspServer->ServerSocket = CreateRTSPServerListenPort(rtsp_port);

            last_rtsp_port = rtsp_port;
            pthread_mutex_unlock(&Rtspmask);
        }
        usleep(500*1000);
    }

    return NULL;
}

HYRTSP_API int HYRtsp_Stop()
{
    return RET_SUCCESS;
}

#define MODULEVERSION       "2015-12-18-SVN454"
HYRTSP_API int HYRtsp_GetLocalModuleVersion(char *ModuleVersion)
{
    memcpy(ModuleVersion,MODULEVERSION,sizeof(MODULEVERSION));
    return RET_SUCCESS;
}
#undef  MODULEVERSION

static int rtsp_start(void)
{
    int ret = pthread_create(&g_rtsp_pid, NULL, HYRtsp_Start, NULL);
    if (ret != 0)
    {
        RTSP_SER_PE(" [%s]pthread_create err!ret=[%d]\n\r", __FUNCTION__, ret);
        return ret;
    }

    return ret;
}

HYRTSP_API int rtsp_init(void)
{
    if (rtsp_api_init == WS_FALSE)
    {
        pthread_mutex_lock(&rtsp_api_init_lock);
        if (rtsp_api_init == WS_FALSE)
        {
            rtsp_start();
            rtsp_api_init = WS_TRUE;
        }

        pthread_mutex_unlock(&rtsp_api_init_lock);
    }

    return WS_SUCCESS;
}


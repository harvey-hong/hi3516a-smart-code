/*******************************************************************************
 * Copyright (c) 2007 eInfochips - All rights reserved.
 *
 * This software is authored by eInfochips and is eInfochips' intellectual
 * property, including the copyrights in all countries in the world.
 * This software is provided under a license to use only with all other rights,
 * including ownership rights, being retained by eInfochips.
 *
 * This file may not be distributed, copied, or reproduced in any manner,
 * electronic or otherwise, without the written consent of eInfochips.
 ******************************************************************************/

/*******************************************************************************
 *
 * File Name    :   RtpRtspInclude.h
 *
 * Description  :   This file includes header files as per the platform
 *
 * History:
 *  JUN/22/2007, UBV,   Created the file
 *  JAN/16/2008, ARJ,   Included process.h for windows
 *
 ******************************************************************************/

#ifndef _INCLUDE_RTPRTSP_INCLUDE_H
#define _INCLUDE_RTPRTSP_INCLUDE_H

/*********************
 * Include Files
 *********************/
#ifdef LINUX            /* Include files for linux platform                   */

#include <sys/types.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <netdb.h>
#include <sys/signal.h>
#include <sys/errno.h>

#ifdef __cplusplus
#define RTP_RTSPLIB_API extern "C"
#else
#define RTP_RTSPLIB_API
#endif

#endif

#ifdef WIN32            /* Include files for windows platform                 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>
#include <sys/timeb.h>
#include <process.h>
#include <time.h>
#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>

#ifdef RTP_RTSPLIB_EXPORTS
#define RTP_RTSPLIB_API __declspec(dllexport)
#else
#define RTP_RTSPLIB_API __declspec(dllimport)
#endif

#endif

#ifdef DSP              /* Include files for DSP platform                     */

#include <stdio.h>
#include <stdlib.h>
#include <netmain.h>
#include <log.h>
#include <sem.h>
#include <lck.h>

#endif

#endif  /* _INCLUDE_RTPRTSP_INCLUDE_H */

/*******************************************************************************
 * Copyright (c) 2007 eInfochips - All rights reserved.
 *
 * This software is authored by eInfochips and is eInfochips' intellectual
 * property, including the copyrights in all countries in the world.
 * This software is provided under a license to use only with all other rights,
 * including ownership rights, being retained by eInfochips.
 *
 * This file may not be distributed, copied, or reproduced in any manner,
 * electronic or otherwise, without the written consent of eInfochips.
 ******************************************************************************/

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
 * File Name    :   BasicTypes.h
 *
 * Description  :   This file contains definitions for basic data types.
 *
 * History:
 *  JUN/22/2007, UBV,   Created the file
 *
 ******************************************************************************/

#ifndef _INCLUDE_BASIC_TYPES_H
#define _INCLUDE_BASIC_TYPES_H

/*********************
 * Include Files
 *********************/
#ifdef LINUX
#include <pthread.h>
#endif

/*********************
 * Defines and Macros
 *********************/

/* Generic function return values                                             */
#define RET_OK          (0)
#define RET_ERROR       (-1)

/*********************
 * Typedefs and Enums
 *********************/

#ifndef WIN32
//typedef unsigned char           BYTE;
//typedef short                   WORD;
//typedef int                     DWORD;
typedef unsigned long           ULONG;
typedef long long               INT64;
typedef unsigned long long      UINT64;
typedef double                  FLOAT;
#endif

typedef char                    INT8;
typedef short                   INT16;
typedef int                     INT32;

typedef unsigned char           UINT8;
typedef unsigned short          UINT16;
typedef unsigned int            UINT32;

typedef unsigned char           UCHAR;
typedef unsigned short          USHORT;
typedef unsigned int            UINT;

typedef struct sockaddr_in      SOCKETADDR_IN;

#ifdef LINUX
typedef int                     SOCKET;
typedef pthread_t               THREAD_HANDLE;
typedef pthread_mutex_t         LOCK_HANDLE;
typedef __timer_t               RTP_RTSP_TIMERID;
typedef INT32                   RTP_RTSP_TIMER_HANDLE;
//typedef INT32                   HANDLE;

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#endif

#ifdef WIN32
typedef HANDLE                  THREAD_HANDLE;
typedef CRITICAL_SECTION        LOCK_HANDLE;
typedef HANDLE                  RTP_RTSP_TIMERID;
typedef INT32                   RTP_RTSP_TIMER_HANDLE;
#endif

#endif /* _INCLUDE_BASIC_TYPES_H */

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

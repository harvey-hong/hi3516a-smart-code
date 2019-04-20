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
 * File Name    :   DbgPrint.h
 *
 * Description  :   This file contains definition and implementation of print
 *                  for different type of messages like debug/error/warning.
 *
 * History:
 *  JUN/02/2007, UBV,   Created the file
 *
 ******************************************************************************/

#ifndef _INCLUDE_DBG_PRINT_H
#define _INCLUDE_DBG_PRINT_H

/*********************
 * Include Files
 *********************/
#include "RtpRtspInclude.h"
#include "ws_comm_debug.h" //ht 2016.2.16




/*********************
 * Defines and Macros
 *********************/

/* Debug levels supported */
/* Level 1 : Input and Output Arguments of RTSP Server APIs.
   Level 2 : Input and Output Arguments of RTSP and RTP Server APIs.
   Level 3 : Input and Output Arguments of RTSP, RTP Server APIs and Internal Functions.
   Level 4 : Input and Output Arguments of RTSP and RTP Server APIs and Internals,
             Also Inner Debug prints of RTSP and RTP APIs.
   Level 5 : Input and Output Arguments of RTSP and RTP Server APIs and Internals,
             Also Inner Debug prints of RTSP, RTP APIs and Internal Functions.
*/

#define DBG_LEVEL_1     1   /* Lowest debug level */
#define DBG_LEVEL_2     2
#define DBG_LEVEL_3     3
#define DBG_LEVEL_4     4
#define DBG_LEVEL_5     5   /* Highest debug level, Enabling this enables all
                                lower debug levels from _LEVEL_4 to _LEVEL_1  */

#define MAX_PRINT_SIZE  1024 /* Max. Debug/info/error print msg size          */

/* Function for Debug Print                                                   */
void RtpRtspDebugPrint(INT32 level, INT8 *format, ...);

/* Function for Error Print                                                   */
void RtpRtspErrorPrint(INT8 *format, ...);

#endif  /* _INCLUDE_DBG_PRINT_H */

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

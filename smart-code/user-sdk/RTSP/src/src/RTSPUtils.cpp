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
 * File Name    :   RTSPUtils.c
 *
 * Description  :   This file contain the Linux OS specific utility function
 *                   required by RTSP/RTP files.
 *
 * History:
 *  JUL/13/2007, UBV,   Created the file.
 *
 ******************************************************************************/

/****************
 * Include Files
 ****************/
#include "../inc/RtspServer.h"
#include "../inc/RtpRtspInclude.h"
#include "../inc/DbgPrint.h"

/****************
 * Function
 * Declaration
 ****************/
/*******************************************************************************
 * Function   : ThreadCreate
 *
 * Description: Creates the thread
 *
 * Parameters :
 *      [IN]  THREAD_HANDLE *ThreadHandle   - Pointer to thread handle.
 *      [IN]  THREAD_FUNC   ThreadFunction  - Thread Routine
 *      [IN]  void          *ThreadArg      - Thread Argument
 *
 * Return Value:
 *      INT32 : RET_OK      , On Success
 *            : RET_ERROR   , On Failure
 ******************************************************************************/
INT32 ThreadCreate(THREAD_HANDLE *ThreadHandle, THREAD_FUNC ThreadFunction,
                   void *ThreadArg)
{
    INT32         threadRetVal;                 /* Store return value of function call    */
    threadRetVal = pthread_create(
                       ThreadHandle,               /* Thread ID                  */
                       NULL,                           /* No Attributes required     */
                       /*(void*)*/ThreadFunction, /* Thread Function         */
                       (INT32 *)ThreadArg          /* Argument to Thread Function*/
                   );

    if (threadRetVal != 0)
    {
        return RET_ERROR;
    }
    else
    {
        return RET_OK;
    }
}

/*******************************************************************************
 * Function   : ThreadExit
 *
 * Description: Destroys the thread
 *
 * Parameters :
 *  [IN] THREAD_HANDLE ThreadHandle - Handle of thread to terminated.
 *
 * Return Value:
 *      INT32 : RET_OK      , On Success
 *            : RET_ERROR   , On Failure
 ******************************************************************************/
INT32 ThreadExit(THREAD_HANDLE ThreadHandle)
{
    INT32 retVal;                       /* Return value                       */
    /* Call function to exit the calling thread                               */
    pthread_exit((void *)&retVal);
    return RET_OK;
}

/*******************************************************************************
 * Function   : ThreadDetach
 *
 * Description: Detaches the thread
 *
 * Parameters :
 *  [IN] THREAD_HANDLE ThreadHandle - Handle of thread to detached.
 *
 * Return Value:
 *      INT32 : RET_OK      , On Success
 *            : RET_ERROR   , On Failure
 ******************************************************************************/

INT32 ThreadDetach(THREAD_HANDLE ThreadHandle)
{
    /* Call function to detach the calling thread                             */
    if (pthread_detach(ThreadHandle))
    {
        return RET_ERROR;
    }

    return RET_OK;
}



/*******************************************************************************
 * Function   : WaitForThreadCompletion
 *
 * Description: This osal function wait until given thread is not terminated
 *
 * Parameters :
 *  [IN] THREAD_HANDLE ThreadHandle - Handle of thread to terminated.
 *
 * Return Value:
 *      INT32 : RET_OK      , On Success
 *            : RET_ERROR   , On Failure
 ******************************************************************************/
INT32 WaitForThreadCompletion(THREAD_HANDLE ThreadHandle)
{
    /* Call function to wait for termination of thread                        */
    if (pthread_join(ThreadHandle, NULL))
    {
        return RET_ERROR;
    }
    else
    {
        return RET_OK;
    }
}

/*******************************************************************************
 * Function   : HandleSignal
 *
 * Description: This osal function ignores the SIGPIPE in case of attempting to
 *              send message to a closed destination socket.
 *
 * Parameters :     NONE
 *
 * Return Value:    NONE
 ******************************************************************************/
void HandleSignal(void)
{
    signal(SIGPIPE, SIG_IGN);
    return;
}

/*******************************************************************************
 * Function   : GetTimeValue
 *
 * Description: This function return the system time value
 *
 * Parameters : None
 *
 * Return Value:
 *      INT64   - system time
 ******************************************************************************/
DWORD GetTimeValue()
{
    struct  timeval tvDate;
    gettimeofday(&tvDate, NULL);
    return ((WS_U64) tvDate.tv_sec * (WS_U64)1000 + (WS_U64)tvDate.tv_usec / (WS_U64)1000);                   // change by linhh 20160525
}

/*******************************************************************************
 * Function   : GetPresentTimeInSec
 *
 * Description: This Function gets current time in seconds and micro seconds.
 *
 * Parameters :
 *  [IN] UINT32* Sec        -   Return pointer for second value
 *  [IN] UINT32* Microsec   -   Return pointer for micro second value
 *
 * Return Value:
 *      INT32 : RET_OK
 ******************************************************************************/
INT32 GetPresentTimeInSec(UINT32 *Sec, UINT32 *Microsec)
{
    struct timeval  systemTime;                 /* System time structure      */

    /* Get system time                                                        */
    if (gettimeofday(&systemTime, NULL) == -1)
    {
        return RET_ERROR;
    }

    *Sec        = systemTime.tv_sec;
    *Microsec   = systemTime.tv_usec;
    return RET_OK;
}

/*******************************************************************************
 * Function   : CloseServerSock
 *
 * Description: This function close server socket
 *
 * Parameters :
 *      [IN]  SOCKET ServerSock   - Pointer of thread function
 *
 * Return Value:
 *      None
 ******************************************************************************/
void CloseServerSock(SOCKET ServerSock)
{
    if (ServerSock != INVALID_SOCKET)
    {
        shutdown(ServerSock, SHUT_RDWR);
        close(ServerSock);
    }
}

/*******************************************************************************
 * Function   : MutexInit
 *
 * Description: This function initialize the mutex.
 *
 * Parameters :
 *      [IN]  LOCK_HANDLE *CriticalSection  -   Handle of Lock
 *
 * Return Value:
 *      INT32 : RET_OK, On Success,
 *              RET_ERROR, On Failure
 ******************************************************************************/
INT32 MutexInit(LOCK_HANDLE *CriticalSection)
{
    pthread_mutexattr_t mattr;
    pthread_mutexattr_init(&mattr);

    if (pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_ADAPTIVE_NP))
    {
        perror("Err in pthread_mutexattr_settype: ");
    }

    if (pthread_mutex_init(CriticalSection, &mattr))
    {
        perror("Err in pthread_mutex_init: ");
        return RTP_RTSP_ERROR;
    }
    else
    {
        return RTP_RTSP_OK;
    }
}

/*******************************************************************************
 * Function   : MutexLock
 *
 * Description: This function Lock the critical section.
 *
 * Parameters :
 *      [IN]  LOCK_HANDLE *CriticalSection  -   Handle of Lock
 *
 * Return Value:
 *      INT32 : RET_OK, On Success,
 *              RET_ERROR, On Failure
 ******************************************************************************/
INT32 MutexLock(LOCK_HANDLE *CriticalSection)
{
    if (pthread_mutex_lock(CriticalSection))
    {
        return RET_ERROR;
    }
    else
    {
        return RET_OK;
    }
}

/*******************************************************************************
 * Function   : MutexUnlock
 *
 * Description: This function Unlocks the critical section.
 *
 * Parameters :
 *      [IN]  LOCK_HANDLE *CriticalSection  -   Handle of Lock
 *
 * Return Value:
 *      INT32 : RET_OK, On Success,
 *              RET_ERROR, On Failure
 ******************************************************************************/
INT32 MutexUnlock(LOCK_HANDLE *CriticalSection)
{
    if (pthread_mutex_unlock(CriticalSection))
    {
        return RET_ERROR;
    }
    else
    {
        return RET_OK;
    }
}

/*******************************************************************************
 * Function   : MutexDestroy
 *
 * Description: This function destroys the mutex.
 *
 * Parameters :
 *      [IN]  LOCK_HANDLE *CriticalSection  -   Handle of Lock
 *
 * Return Value:
 *      INT32 : RET_OK, On Success,
 *              RET_ERROR, On Failure
 ******************************************************************************/
INT32 MutexDestroy(LOCK_HANDLE *CriticalSection)
{
    if (pthread_mutex_destroy(CriticalSection))
    {
        return RET_ERROR;
    }
    else
    {
        return RET_OK;
    }
}

/*******************************************************************************
 * Function   : MSecDelay
 *
 * Description: Delay function in milliseconds.
 *
 * Parameters : INT32  DelayTime  - MilliSecond delay
 *
 * Return Value:
 *      None
 ******************************************************************************/
void MSecDelay(INT32  DelayTime)
{
    usleep(DelayTime * 1000);
}

/*******************************************************************************
 * Function   : RtpRtspDebugPrint
 *
 * Description: Function for printing debug information.
 *
 * Parameters : INT32 Level     - Debug Level
 *              BYTE *Format    - Pointer to arguments
 *
 * Return Value:
 *      None
 ******************************************************************************/
void RtpRtspDebugPrint(INT32 Level, INT8 *Format, ...)
{
#ifdef ENABLE_DBG_LEVEL
    INT8                messagebuf[MAX_PRINT_SIZE]; /* Store message string   */
    va_list             va;                         /* Argument list          */
    //    if ( Level <= ENABLE_DBG_LEVEL )
    {
        memset(messagebuf, 0x00, MAX_PRINT_SIZE);
        /* Format the string                                                  */
        va_start(va, Format);
        vsnprintf(messagebuf, MAX_PRINT_SIZE, Format, va);
        va_end(va);
    }
#endif
}

/*******************************************************************************
 * Function   : RtpRtspErrorPrint
 *
 * Description: Function for printing Error messages
 *
 * Parameters : BYTE *Format    - Pointer to arguments
 *
 *
 * Return Value:
 *      None
 ******************************************************************************/
void RtpRtspErrorPrint(INT8 *Format, ...)
{
    INT8                messagebuf[MAX_PRINT_SIZE]; /* Store message string   */
    va_list             va;                         /* Argument list          */
    memset(messagebuf, 0x00, MAX_PRINT_SIZE);
    /* Format the string                                                      */
    va_start(va, Format);
    vsnprintf(messagebuf, MAX_PRINT_SIZE, Format, va);
    va_end(va);
}


/******************************************************************************
 *  Function    :   RtpRtspStopTimer
 *
 *  Description :   This function stop the timer and unregister its handle function
 *
 *  Parameters  :   RTP_RTSP_TIMER_HANDLE timerHandle   -   Timer handle to stop
 *
 *  Return Value:
 *              INT32 : RET_OK      , On Success
 *                    : RET_ERROR   , On Failure
 *
 ******************************************************************************/
INT32 RtpRtspStopTimer(RTP_RTSP_TIMER_HANDLE timerHandle)
{
    TimerStruct *timerObj;              /* Local timer ojbect pointer         */

    if (!timerHandle)
    {
        RtpRtspErrorPrint("Invalid timer handle passed \n");
        return RET_ERROR;
    }

    /* Delete the timer queue and related timers                              */
    timerObj = (TimerStruct *)timerHandle;

    if (timer_delete(timerObj->hTimer))
    {
        return RET_ERROR;
    }

    free(timerObj);
    return RET_OK;
}

/*******************************************************************************
 * Function   : RtpRtspUDPSockRecv
 *
 * Description: This function receive data from given UDP socket
 *
 * Parameters :
 *      [IN]  SOCKET        sockHandle    - Pointer of thread function
 *      [IN]  BYTE          *dataBuff     - Pointer of data buffer
 *      [IN]  INT32         dataSize      - Size of data to read
 *      [IN]  SOCKETADDR_IN sockAddr      - Pointer of sockaddr structure
 *      [IN]  INT32         *sockAddrSize - Sock Addr Struct size
 *
 * Return Value:
 *      None
 ******************************************************************************/
INT32 RtpRtspUDPSockRecv(SOCKET        sockHandle, BYTE  *dataBuff,    INT32 dataSize,
                         SOCKETADDR_IN *sockAddr,   INT32 *sockAddrSize)
{
    INT32   retValue;           /* Store the return value                     */

    /* Read the data from the given socket and check the error code           */
    do
    {
        retValue = recvfrom(sockHandle, dataBuff, dataSize, MSG_TRUNC,
                            (struct sockaddr *)sockAddr, (socklen_t *)sockAddrSize);

        if (retValue < 0)
        {
            if ((errno == EINTR) || (errno == 29))
            {
                RTSP_SER_PD("UDP recv function error in linux: errno :%d Retval: %d \n", errno, retValue);
            }
            else
            {
                break;
            }
        }
    }
    while (retValue < 0);

    return retValue;
}

/******************************************************************************
 * Copyright (c) 2007 eInfochips - All rights reserved.
 *
 * This software is authored by eInfochips and is eInfochips' intellectual
 * property, including the copyrights in all countries in the world.
 * This software is provided under a license to use only with all other rights,
 * including ownership rights, being retained by eInfochips.
 *
 * This file may not be distributed, copied, or reproduced in any manner,
 * electronic or otherwise, without the written consent of eInfochips.
 *****************************************************************************/


#ifndef _WS_BW_CONTROL_API_H_
#define _WS_BW_CONTROL_API_H_

#include "HieServer_Common.h"
#include "ws_bw_control_def.h"
#include <sys/time.h>

#if 0
#if defined( __cplusplus)
#define BW_CONTROL_API  extern "C" __attribute__((visibility("default")))
#else
#define BW_CONTROL_API  __attribute__((visibility("default")))
#endif
#endif

#define BW_CONTROL_API __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif

BW_CONTROL_API int BWContorlStart(const char* deviceUID);

BW_CONTROL_API int BWContorlStop();

BW_CONTROL_API int createBWTaskID(DWORD &taskId, StreamInfo info);

BW_CONTROL_API int releaseBWTaskID(DWORD SessionID);

BW_CONTROL_API bool judgeSend(DWORD SessionID, int iFrameType, int iFrameLen, struct timeval& frameTime, int iFrameNo);

BW_CONTROL_API int setFeedback(BWLostInfo lostInfo,int* interval);

BW_CONTROL_API int adjustMaxSpeed(DWORD sessionID, DWORD dwSpeed);

BW_CONTROL_API bool getInterval(DWORD SessionID, int& speed_ms);
#ifdef __cplusplus
}
#endif

#endif  /*#ifndef _WS_BW_CONTROL_API_H_*/

#ifndef _WS_BW_CONTROL_API_H_
#define _WS_BW_CONTROL_API_H_

#include "HieServer_Common.h"
#include "ws_p2p_bw_control_def.h"
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

BW_CONTROL_API int P2PBWContorlStart();

BW_CONTROL_API int P2PBWContorlStop();

BW_CONTROL_API int createP2PBWTaskID(DWORD &taskId, StreamInfo& info);

BW_CONTROL_API int releaseP2PBWTaskID(DWORD taskId);

BW_CONTROL_API int getP2PBWTaskSpeed(DWORD taskId, eBWStreamSpeed& eSpeed);

BW_CONTROL_API int setP2PFeedback(DWORD taskId, BWLostInfo& lostInfo,int* interval);

BW_CONTROL_API int adjustP2PBaseSpeed(DWORD taskId, DWORD dwSpeed);

BW_CONTROL_API bool judgeStreamBitRate(DWORD taskId, DWORD frameType, DWORD dwDataLen, DWORD dwIFrameIdx);
#ifdef __cplusplus
}
#endif

#endif  /*#ifndef _WS_BW_CONTROL_API_H_*/

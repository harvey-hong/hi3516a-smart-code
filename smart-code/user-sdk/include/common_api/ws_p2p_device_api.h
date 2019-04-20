#ifndef _WS_P2P_DEVICE_API_H_
#define _WS_P2P_DEVICE_API_H_
    

#if defined( __cplusplus)
#define P2P_DEVICE_API  extern "C" __attribute__((visibility("default")))
#else
#define P2P_DEVICE_API  __attribute__((visibility("default")))
#endif

P2P_DEVICE_API int p2p_device_init(void);

P2P_DEVICE_API int p2p_device_privator_hw_reset(void);  /* hzg 20180315 added DVR support hardware reset privator  */

#endif  /*#ifndef _TECOM_WS_P2P_DEVICE_API_H_*/

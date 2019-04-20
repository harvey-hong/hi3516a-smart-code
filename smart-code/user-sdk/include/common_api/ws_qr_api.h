#ifndef _WS_QR_API_H_
#define _WS_QR_API_H_

#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_common.h"



#ifdef __cplusplus
extern "C" {
namespace QR_Encode
{
#endif

//QRÂëÉú³É
WS_S32 utility_qr_manager(int nLevel, int nVersion , char *lpsSource, int sourcelen, char *QR_m_data, size_t QR_m_data_size);

#ifdef __cplusplus
}//namespace QR_Encode {
}//extern "C" {
#endif

#endif  //_WS_QR_API_H_

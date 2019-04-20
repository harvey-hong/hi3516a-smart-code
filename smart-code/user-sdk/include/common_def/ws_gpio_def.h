#ifndef _WS_GPIO_DEF_H_
#define _WS_GPIO_DEF_H_

#include "ws_comm_type.h"
#include "ws_common.h"


#ifdef __cplusplus
extern "C" {
namespace ws_soft
{
#endif


typedef enum
{
    GPIO_ALARM_OUT_OPEN,
    GPIO_ALARM_OUT_CLOSE,
} gpio_alarm_out_ctl;


#ifdef __cplusplus
}//namespace ws_soft {
}//extern "C" {
#endif

#endif  //_WS_GPIO_DEF_H_


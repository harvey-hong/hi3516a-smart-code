#ifndef _WS_GPIO_API_H_
#define _WS_GPIO_API_H_

#include "ws_comm_sys.h"
#include "ws_comm_type.h"
#include "ws_comm_errno.h"
#include "ws_comm_data.h"
#include "ws_comm_av.h"
#include "ws_gpio_def.h"
#include <termios.h>


namespace ws_soft
{
WS_ERR gpio_init();
WS_ERR gpio_buzzer_on(void);
WS_ERR gpio_buzzer_off(void);
WS_ERR gpio_buzzer_ms(WS_U32 msecs);
WS_ERR gpio_support_alarm_in_out(WS_BOOL* is_have);
WS_ERR gpio_check_alarm_in(const WS_U32 pin, WS_BOOL *is_vaild);
WS_ERR gpio_set_alarm_out_control(const WS_U32 pin, ws_soft::gpio_alarm_out_ctl ctl);
WS_ERR gpio_set_alarm_out(const WS_U32 ao_mask);
WS_ERR gpio_require_password_reset_pin_state(WS_BOOL *is_vaild);
WS_ERR gpio_set_alarm_in_check_type(const WS_U32 pin, ws_utility::ws_ai_check_type type);     
WS_ERR gpio_422_send_message(WS_U32 port_idx,const char* send_buf, size_t send_size, speed_t baudrate);
WS_ERR gpio_422_receive_message(WS_U32 port_idx, char* receive_buf, size_t recv_size, speed_t baudrate);
WS_ERR gpio_485_send_message(WS_U32 port_idx,const char* send_buf, size_t send_size, speed_t baudrate);
WS_ERR gpio_485_receive_message(WS_U32 port_idx, char* receive_buf, size_t recv_size, speed_t baudrate);
WS_ERR gpio_power_off_gpio();
}
#endif

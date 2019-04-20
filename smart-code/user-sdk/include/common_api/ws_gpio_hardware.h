#ifndef __WS_GPIO_HARDWARE_H__
#define __WS_GPIO_HARDWARE_H__

#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <termios.h>	

#include "ws_common.h"
#include "ws_comm_errno.h"
#include "ws_comm_debug.h"
#include "ws_comm_sys.h"

using namespace ws_utility;

#define HI_GPIO_HIGH_LEVEL (0x1)  //高低电平
#define HI_GPIO_LOW_LEVEL  (0x0)
#define HI_GPIO_DIR_IN        0
#define HI_GPIO_DIR_OUT     1

typedef struct
{
    //结构体中包含哪个GPIO组，组中的哪个引脚以及该引脚对应的寄存器中的值
    unsigned int grp;
    unsigned int pin;
    unsigned int value; //value的值不定，有可能是方向寄存器的，也有可能是状态寄存器的
} hsx_gpio_ctl;

namespace ws_hardware_gpio
{
    WS_ERR ws_gpio_set_regist_mask(unsigned int base,unsigned int offset,unsigned int value);
    WS_ERR ws_gpio_clr_regist_mask(unsigned int base,unsigned int offset,unsigned int value);
    WS_ERR ws_gpio_set_state(int gpioGrp, int gpioPin, WS_U32 gpioValue);
    WS_ERR ws_gpio_get_state(int gpioGrp, int gpioPin, WS_U32 *gpioValue);
    WS_ERR ws_gpio_set_pin_dir(int gpioGrp, int gpioPin, WS_U32 gpioValue);
    WS_ERR ws_gpio_alarm_out(int gpioGrp0, int gpioPin0,int gpioGrp1, int gpioPin1, WS_U32 gpioValue);
}


#endif

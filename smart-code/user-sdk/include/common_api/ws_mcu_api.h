#ifndef __WS_MCU_API_H__
#define __WS_MCU_API_H__

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



#include "ws_utility_api.h"
#include "ws_utility_class_def.h"

using ws_utility::WS_ERR;
namespace ws_mcu
{
    WS_ERR send_al_dark_to_mcu();
    WS_ERR send_al_light_to_mcu();
    WS_ERR send_al_ficker_to_mcu();
    WS_ERR send_rec_dark_to_mcu();
    WS_ERR send_rec_light_to_mcu();
    WS_ERR send_rec_ficker_to_mcu();
    WS_ERR send_cancel_shutdown_to_mcu();
}
#endif


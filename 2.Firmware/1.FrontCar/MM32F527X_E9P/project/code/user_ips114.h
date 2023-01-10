/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef _USER_IPS114_H
#define _USER_IPS114_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"
#include "zf_device_ips114.h"

void IPS114_DrawRBox(int16_t x, int16_t y, uint16_t width, uint16_t height);
void IPS114_ClearRBox(int16_t x, int16_t y, uint16_t width, uint16_t height);

#ifdef __cplusplus
}
#endif

#endif

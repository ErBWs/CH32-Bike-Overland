/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef MM32F527X_E9P_USER_FLASH_H
#define MM32F527X_E9P_USER_FLASH_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "zf_driver_flash.h"

void DoubleToInt(double val, uint32_t *arr);
void IntToDouble(double *val, const uint32_t *arr);

#ifdef __cplusplus
}
#endif

#endif

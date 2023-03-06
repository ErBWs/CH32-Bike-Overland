/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef MM32F527X_E9P_VOFA_H
#define MM32F527X_E9P_VOFA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "zf_driver_uart.h"

#define CHANNEL_NUM     3

extern float vofaData[CHANNEL_NUM];

void VofaLittleEndianSendFrame();
void VofaBigEndianSendFrame();

#ifdef __cplusplus
}
#endif

#endif

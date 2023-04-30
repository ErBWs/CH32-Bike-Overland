/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef VOFA_H
#define VOFA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "zf_driver_uart.h"

#define CHANNEL_NUM     6

extern float vofaData[CHANNEL_NUM];

void VofaLittleEndianSendFrame();
void VofaBigEndianSendFrame();

#ifdef __cplusplus
}
#endif

#endif

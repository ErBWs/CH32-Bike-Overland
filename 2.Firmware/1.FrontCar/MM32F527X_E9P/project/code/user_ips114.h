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
#include <stdlib.h>
#include <stdbool.h>
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"
#include "zf_device_ips114.h"

extern uint16_t IPS114_penColor;
extern uint16_t IPS114_backgroundColor;

typedef enum
{
    NORMAL = 1,
    XOR
} IPS114_ColorMode_e;

void IPS114_SendBuffer();
void IPS114_ClearBuffer();

void IPS114_SetDrawColor(IPS114_ColorMode_e mode);
void IPS114_DrawPoint (int16 x, int16 y, uint16 color);
void IPS114_DrawLine (int16 x_start, int16 y_start, int16 x_end, int16 y_end, uint16 color);
void IPS114_ShowChar(int16 x, int16 y, char dat);
void IPS114_ShowStr (int16 x, int16 y, const char dat[]);
void IPS114_ShowInt(int16 x, int16 y, int32 dat, uint8 num);
void IPS114_ShowUint(int16 x, int16 y, uint32 dat, uint8 num);
void IPS114_ShowFloat(int16 x, int16 y, float dat, uint8 num, uint8 pointnum);

extern bool reversedColor;
void IPS114_ModifyColor();

void IPS114_DrawFrame(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color);
void IPS114_DrawBox(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color);
void IPS114_DrawRFrame(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color);
void IPS114_DrawRBox(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color);
void IPS114_DrawRBoxWithBlur(int16_t x, int16_t y, uint16_t width, uint16_t height);
void IPS114_DrawCheckbox(int16_t x, int16_t y, uint16_t size, uint8_t offset, bool boolValue);

void IPS114_ShowBMP(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint8_t *pic);

#ifdef __cplusplus
}
#endif

#endif

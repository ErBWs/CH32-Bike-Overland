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
#include <math.h>
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

#define CIRCLE_UPPER_RIGHT      0x01
#define CIRCLE_UPPER_LEFT       0x02
#define CIRCLE_LOWER_LEFT       0x04
#define CIRCLE_LOWER_RIGHT      0x08
#define CIRCLE_DRAW_ALL         (CIRCLE_UPPER_RIGHT | CIRCLE_UPPER_LEFT | CIRCLE_LOWER_LEFT | CIRCLE_LOWER_RIGHT)

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

void IPS114_DrawCircle(int16_t x, int16_t y, uint16_t r, uint16_t color, uint8_t section);
void IPS114_DrawDisc(int16_t x, int16_t y, uint16_t r, uint16_t color, uint8_t section);
void IPS114_DrawFrame(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color);
void IPS114_DrawBox(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color);
void IPS114_DrawRFrame(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color, uint8_t r);
void IPS114_DrawRBox(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color, uint8_t r);
void IPS114_DrawRBoxWithBlur(int16_t x, int16_t y, uint16_t width, uint16_t height);

void IPS114_ShowBMP(int16_t x, int16_t y, uint16_t width, uint16_t height, const uint8_t *pic);
void IPS114_ShowGrayImage(uint16_t x, uint16_t y, const uint8_t *image, uint16_t width, uint16_t height, uint16_t dis_width,
                          uint16_t dis_height, uint8_t threshold);

#ifdef __cplusplus
}
#endif

#endif

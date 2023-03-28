/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH        the first version
 */
#ifndef DRV_ES8388_H__
#define DRV_ES8388_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>



/* ES8388 register space */
#define ES8388_CONTROL1         0x00
#define ES8388_CONTROL2         0x01
#define ES8388_CHIPPOWER        0x02
#define ES8388_ADCPOWER         0x03
#define ES8388_DACPOWER         0x04
#define ES8388_CHIPLOPOW1       0x05
#define ES8388_CHIPLOPOW2       0x06
#define ES8388_ANAVOLMANAG      0x07
#define ES8388_MASTERMODE       0x08
#define ES8388_ADCCONTROL1      0x09
#define ES8388_ADCCONTROL2      0x0a
#define ES8388_ADCCONTROL3      0x0b
#define ES8388_ADCCONTROL4      0x0c
#define ES8388_ADCCONTROL5      0x0d
#define ES8388_ADCCONTROL6      0x0e
#define ES8388_ADCCONTROL7      0x0f
#define ES8388_ADCCONTROL8      0x10
#define ES8388_ADCCONTROL9      0x11
#define ES8388_ADCCONTROL10     0x12
#define ES8388_ADCCONTROL11     0x13
#define ES8388_ADCCONTROL12     0x14
#define ES8388_ADCCONTROL13     0x15
#define ES8388_ADCCONTROL14     0x16

#define ES8388_DACCONTROL1      0x17
#define ES8388_DACCONTROL2      0x18
#define ES8388_DACCONTROL3      0x19
#define ES8388_DACCONTROL4      0x1a
#define ES8388_DACCONTROL5      0x1b
#define ES8388_DACCONTROL6      0x1c
#define ES8388_DACCONTROL7      0x1d
#define ES8388_DACCONTROL8      0x1e
#define ES8388_DACCONTROL9      0x1f
#define ES8388_DACCONTROL10     0x20
#define ES8388_DACCONTROL11     0x21
#define ES8388_DACCONTROL12     0x22
#define ES8388_DACCONTROL13     0x23
#define ES8388_DACCONTROL14     0x24
#define ES8388_DACCONTROL15     0x25
#define ES8388_DACCONTROL16     0x26
#define ES8388_DACCONTROL17     0x27
#define ES8388_DACCONTROL18     0x28
#define ES8388_DACCONTROL19     0x29
#define ES8388_DACCONTROL20     0x2a
#define ES8388_DACCONTROL21     0x2b
#define ES8388_DACCONTROL22     0x2c
#define ES8388_DACCONTROL23     0x2d
#define ES8388_DACCONTROL24     0x2e
#define ES8388_DACCONTROL25     0x2f
#define ES8388_DACCONTROL26     0x30
#define ES8388_DACCONTROL27     0x31
#define ES8388_DACCONTROL28     0x32
#define ES8388_DACCONTROL29     0x33
#define ES8388_DACCONTROL30     0x34




rt_err_t ES8388_Init(const char *i2c_name, rt_uint16_t pin);
void ES8388_I2S_Cfg(rt_uint8_t fmt, rt_uint8_t len);
void ES8388_Set_Volume(rt_uint8_t volume);
void ES8388_ADDA_Cfg(rt_uint8_t dacen,rt_uint8_t adcen);
void ES8388_Output_Cfg(rt_uint8_t out);
void ES8388_Input_Cfg(rt_uint8_t in);



#endif

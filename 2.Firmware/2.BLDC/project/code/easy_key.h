/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan
 */

#ifndef _easy_key_h_
#define _easy_key_h_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "zf_driver_gpio.h"
#include "zf_driver_delay.h"

#define FILTER_TIME_US          100     // Dithering elimination
#define HOLD_THRESHOLD_MS       100     // Time longer than this is considered as "hold"
#define INTERVAL_THRESHOLD_MS   80      // Trigger time interval less than this is considered as "multiclick"

typedef struct EasyKey_typedef
{
    // Internal call
    uint8_t value, preVal;      // Press:0  Not press:1
    uint16_t id;
    uint32_t intervalTime;
    struct EasyKey_typedef *next;
    gpio_pin_enum pin;
    uint32_t holdTime;
    uint32_t clickCnt;
    enum
    {
        release,
        dither,
        preClick,
        inClick,
        press,
        hold,
        multiClick
    } state;

    // User call
    bool isPressed;
    bool isHold;
    bool isMultiClick;
} EasyKey_t;

extern bool multiClickSwitch;

void DebounceFilter(uint8_t timeUs);
void EasyKeyInit(EasyKey_t *key, gpio_pin_enum _pin);
void EasyKeyHandler(uint8_t timer);

void PressCallback(EasyKey_t *key);
void HoldCallback(EasyKey_t *key);
void MultiClickCallback(EasyKey_t *key);
void ReleaseCallback(EasyKey_t *key);

extern EasyKey_t keyL, keyC, keyR;
#endif

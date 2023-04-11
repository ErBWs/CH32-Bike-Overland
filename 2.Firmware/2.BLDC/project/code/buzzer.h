/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef _BUZZER_H_
#define _BUZZER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "easy_ui.h"
#include "zf_driver_gpio.h"
#include "zf_driver_pwm.h"

#define BUZZER_PIN                  TIM8_PWM_MAP1_CH4_C13
#define BUZZER_TRIGGER_TIME_MS      10

extern paramType buzzerVolume;
extern int16_t beepTime;

typedef enum
{
    C_4 = 262,
    C_4_SHARP = 277,
    
} MusicScale_e;

void BuzzerInit();
void Beep();

#ifdef __cplusplus
}
#endif

#endif

/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef MM32F527X_E9P_BUZZER_H
#define MM32F527X_E9P_BUZZER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "easy_ui.h"
#include "zf_driver_gpio.h"
#include "zf_driver_pwm.h"

#define BUZZER_PIN      TIM2_PWM_CH4_B11
extern paramType buzzerVolume;

void BuzzerInit();
void Beep();
void StopBeep();

#ifdef __cplusplus
}
#endif

#endif

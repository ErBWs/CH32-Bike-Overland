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
    C_4 = 262,        C_4_SHARP = 277,  D_4 = 294,        D_4_SHARP = 311,  E_4 = 330,        F_4 = 349,
    F_4_SHARP = 370,  G_4 = 392,        G_4_SHARP = 415,  A_4 = 440,        A_4_SHARP = 466,  B_4 = 494,

    C_5 = 523,        C_5_SHARP = 554,  D_5 = 587,        D_5_SHARP = 622,  E_5 = 659,        F_5 = 698,
    F_5_SHARP = 740,  G_5 = 784,        G_5_SHARP = 831,  A_5 = 880,        A_5_SHARP = 932,  B_5 = 988,

    C_6 = 1047,       C_6_SHARP = 1109, D_6 = 1175,       D_6_SHARP = 1245, E_6 = 1319,       F_6 = 1397,
    F_6_SHARP = 1480, G_6 = 1568,       G_6_SHARP = 1661, A_6 = 1760,       A_6_SHARP = 1865, B_6 = 1976,
} MusicScale_e;

void BuzzerInit();
void Beep();

#ifdef __cplusplus
}
#endif

#endif

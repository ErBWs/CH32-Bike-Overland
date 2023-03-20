#ifndef __BSP_ENCODER_H
#define __BSP_ENCODER_H

#include "zf_common_headfile.h"

#define ENCODER_FLY_WHEEL_SPD_PIN       TIM2_ENCOEDER_MAP0_CH2_A1            // Encoder speed input
#define ENCODER_FLY_WHEEL_DIR_PIN       TIM2_ENCOEDER_MAP0_CH1_A0            // Encoder direction input
#define ENCODER_FLY_WHEEL_TIM           TIM2_ENCOEDER                        // Timer of encoder
#define ENCODER_BACK_WHEEL_SPD_PIN      TIM4_ENCOEDER_MAP0_CH1_B6            // Encoder speed input
#define ENCODER_BACK_WHEEL_DIR_PIN      TIM4_ENCOEDER_MAP0_CH2_B7            // Encoder direction input
#define ENCODER_BACK_WHEEL_TIM          TIM4_ENCOEDER                   // Timer of encoder

void encoderInit(void);
void GetDistance();
#endif

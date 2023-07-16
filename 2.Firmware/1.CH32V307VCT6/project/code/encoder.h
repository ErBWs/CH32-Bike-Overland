#ifndef __BSP_ENCODER_H
#define __BSP_ENCODER_H

#include "zf_common_headfile.h"

#define ENCODER_FLY_WHEEL_SPD_PIN       TIM9_ENCOEDER_MAP3_CH2_D11            // Encoder speed input
#define ENCODER_FLY_WHEEL_DIR_PIN       TIM9_ENCOEDER_MAP3_CH1_D9            // Encoder direction input
#define ENCODER_FLY_WHEEL_TIM           TIM9_ENCOEDER                        // Timer of encoder
#define ENCODER_BACK_WHEEL_SPD_PIN      TIM10_ENCOEDER_MAP3_CH2_D3            // Encoder speed input
#define ENCODER_BACK_WHEEL_DIR_PIN      TIM10_ENCOEDER_MAP3_CH1_D1            // Encoder direction input
#define ENCODER_BACK_WHEEL_TIM          TIM10_ENCOEDER                   // Timer of encoder

void encoderInit(void);
#endif

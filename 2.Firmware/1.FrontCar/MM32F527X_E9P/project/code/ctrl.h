/*
 * @file    ctrl.h
 * @author  Baohan
 * @date    2022/05/02
 */

#ifndef _ctrl_h_
#define _ctrl_h_

#include <stdint.h>
#include <string.h>
#include "pid.h"
#include "vofa.h"
#include "zf_driver_flash.h"
#include "zf_driver_gpio.h"
#include "zf_driver_pwm.h"
#include "zf_driver_delay.h"
#include "zf_driver_encoder.h"
#include "zf_driver_pit.h"
#include "zf_common_interrupt.h"

#define SERVO_FREQ          50                                  // Servo frequency(50-300)
/* 
 * Calculate servo PWM duty from turning angle.
 * 
 * Servo often receive a period of 0.5ms to 2.5ms high level pulse,
 * which correspond 0 to 180-degree turning angle.
 * 
 * To make calculate easier, I change the angle to [-90, 90],
 * if you want to use [0, 180], change the "1.5" in equation to "0.5".
 * 
 * Below is the angle to duty equation,
 * "freq" refers to "PWM frequency"
 * 
 *         10000 * (1.5 + x / 90)
 * duty = ------------------------   (-90 <= x <= 90)
 *              1000 / freq
 * 
 */
#define GetServoDuty(x)    ((float)(PWM_DUTY_MAX * (1.48 + (float)x / 90.0)) / (1000.0 / (float)SERVO_FREQ))

#define SERVO_MID           GetServoDuty(0)                     // Middle duty of servo motor
#define SERVO_DUTY_MAX      (GetServoDuty(14) - SERVO_MID)      // Maximum turning angle of servo motor
#define SERVO_PIN           TIM2_PWM_CH1_A15                    // Servo pwm output pin
#define MOTOR_FREQ          13000                               // Motor frequency
#define MOTOR_L_PIN         TIM2_PWM_CH2_A1                     // Left motor pwm output pin
#define MOTOR_L_DIR_PIN     A0                                  // Left motor direction output pin
#define MOTOR_R_PIN         TIM2_PWM_CH4_A3                     // Right motor pwm output pin
#define MOTOR_R_DIR_PIN     A2                                  // Right motor direction output pin


#define ENCODER_L_SPD_PIN       TIM3_ENCODER_CH1_B4            // Encoder speed input
#define ENCODER_L_DIR_PIN       TIM3_ENCODER_CH2_B5            // Encoder direction input
#define ENCODER_R_SPD_PIN       TIM4_ENCODER_CH1_D12            // Encoder speed input
#define ENCODER_R_DIR_PIN       TIM4_ENCODER_CH2_D13            // Encoder direction input
#define ENCODER_L_TIM           TIM3_ENCODER                   // Timer of encoder
#define ENCODER_R_TIM           TIM4_ENCODER                   // Timer of encoder

extern PidParam_t spdParam;
extern PidParam_t dirParam;
extern bool preset1, preset2, preset3;

void MotorInit(void);
int16_t GetDirError(uint8_t status);
void ServoControl(float dirError);
void SpeedControl(void);

#endif
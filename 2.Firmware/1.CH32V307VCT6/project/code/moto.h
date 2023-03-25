#ifndef __BSP_MOTO_H
#define __BSP_MOTO_H

#include "zf_common_headfile.h"

#define SERVO_FREQ          50                                  // Servo frequency(50-300)
/* 
 * Caculate servo PWM duty from turning angle.
 * 
 * Servo often receive a period of 0.5ms to 2.5ms high level pulse,
 * which correspond 0 to 180 degree turning angle.
 * 
 * To make caculate easier, I change the angle to [-90, 90],
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
#define GetServoDuty(x)    ((float)(PWM_DUTY_MAX * (1.45 + (float)x / 90.0)) / (1000.0 / (float)SERVO_FREQ))

#define SERVO_MID           GetServoDuty(0)                     // Middle duty of servo motor
#define SERVO_DUTY_MAX      (GetServoDuty(14) - SERVO_MID)      // Maximum turning angle of servo motor
#define SERVO_PIN           TIM10_PWM_MAP3_CH1_D1                    // Servo pwm output pin

#define MOTOR_FREQ            10000                               // Motor frequency
#define MOTOR_BACK_PIN        TIM5_PWM_MAP0_CH4_A3                     // Left motor pwm output pin
#define MOTOR_BACK_DIR_PIN    C7                                  // Left motor direction output pin
#define MOTOR_FLY_PIN         TIM5_PWM_MAP0_CH3_A2                     // Right motor pwm output pin
#define MOTOR_FLY_DIR_PIN     C6                                  // Right motor direction output pin

void motoInit(void);
void motoDutySet(pwm_channel_enum pin,int32_t duty);
#define myABS(x) (x>0?x:-x)

#endif

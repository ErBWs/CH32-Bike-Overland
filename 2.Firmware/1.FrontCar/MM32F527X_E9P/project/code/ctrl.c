/*
 * @file    ctrl.c
 * @author  Baohan
 * @date    2022/05/02
 */

#include "ctrl.h"

// PID parameter array: *Param[5] = {kp, ki, kd, target_value, limitation}
//float spdParam[5] = {80, 0, 15, 37.3, PWM_DUTY_MAX - 1000};
//float dirParam[5] = {0.6, 0, 0, 0, SERVO_DUTY_MAX};       // PD control for direction, ki should be 0

// PID struct define
PidParam_t spdParam =
        {
                80,
                0,
                -10,
                300,
                PWM_DUTY_MAX - SERVO_DUTY_MAX,
                3000,
                900,
                300,
        };
PidParam_t dirParam =
        {
                10,
                0,
                -10,
                0,
                SERVO_DUTY_MAX,
                3000,
                900,
                300,
        };

/*!
 * @brief       Motor control init, including encoder init
 *
 * @return      None
 */
void MotorInit(void)
{
    // Servo motor init
    pwm_init(SERVO_PIN, SERVO_FREQ, SERVO_MID);

    // Motor and encoder init
    pwm_init(MOTOR_L_PIN, MOTOR_FREQ, 0);
    pwm_init(MOTOR_R_PIN, MOTOR_FREQ, 0);

    gpio_init(MOTOR_L_DIR_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(MOTOR_R_DIR_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    encoder_dir_init(ENCODER_L_TIM, ENCODER_L_SPD_PIN, ENCODER_L_DIR_PIN);
    encoder_dir_init(ENCODER_R_TIM, ENCODER_R_SPD_PIN, ENCODER_R_DIR_PIN);

    // Interrupt init
    interrupt_set_priority(TIM7_IRQn, 1);    // Set priority to 1
}


/*!
 * @brief       Get direction error
 * 
 * @param       None
 * @return      dirError        Direction error
 */
int16_t GetDirError(uint8_t status)
{

}


/*!
 * @brief       Servo PID control
 *
 * @param       dirError        Direction error
 * @return      None
 */
void ServoControl(const float dirError)
{
    static int32_t servoOut = 0;

    // Servo pid
    servoOut = PidPosControl(&dirParam, dirError);

    // Servo output
    pwm_set_duty(SERVO_PIN, (SERVO_MID + servoOut));
}


/*!
 * @brief       Speed PID control
 *
 * @param       None
 * @return      None
 */
void SpeedControl(void)
{
    static int32_t leftSpeed = 0, rightSpeed = 0, speedInput = 0;
    static int32_t averageSpdOut = 0, leftSpdOut = 0, rightSpdOut = 0;


    // Get encoder speed data
    leftSpeed = encoder_get_count(ENCODER_L_TIM);
    encoder_clear_count(ENCODER_L_TIM);
    rightSpeed = -encoder_get_count(ENCODER_R_TIM);
    encoder_clear_count(ENCODER_R_TIM);
    speedInput = (leftSpeed + rightSpeed) / 2;

    // PID calculate
    averageSpdOut = PidIncControl(&spdParam, speedInput);
    leftSpdOut = averageSpdOut + (int32_t) spdParam.out;
    rightSpdOut = averageSpdOut - (int32_t) spdParam.out;


    if (leftSpdOut >= 0)
    {
        pwm_set_duty(MOTOR_L_PIN, leftSpdOut);
        gpio_set_level(MOTOR_L_DIR_PIN, 0);
    } else
    {
        pwm_set_duty(MOTOR_L_PIN, -leftSpdOut);
        gpio_set_level(MOTOR_L_DIR_PIN, 1);
    }
    if (rightSpdOut >= 0)
    {
        pwm_set_duty(MOTOR_R_PIN, rightSpdOut);
        gpio_set_level(MOTOR_R_DIR_PIN, 0);
    } else
    {
        pwm_set_duty(MOTOR_R_PIN, -rightSpdOut);
        gpio_set_level(MOTOR_R_DIR_PIN, 1);
    }
}
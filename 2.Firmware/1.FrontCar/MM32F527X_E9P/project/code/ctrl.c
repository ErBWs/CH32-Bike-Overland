/*
 * @file    ctrl.c
 * @author  Baohan
 * @date    2022/05/02
 */

#include "ctrl.h"

// PID struct define
PidParam_t spdParam =
        {
                10,
                0,
                0,
                50,
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

bool preset1 = false, preset2 = false, preset3 = false;

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
    pwm_init(MOTOR_L_PIN, MOTOR_FREQ, 2000);
    pwm_init(MOTOR_R_PIN, MOTOR_FREQ, 2000);

    gpio_init(MOTOR_L_DIR_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(MOTOR_R_DIR_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);

    encoder_dir_init(ENCODER_L_TIM, ENCODER_L_SPD_PIN, ENCODER_L_DIR_PIN);
    encoder_dir_init(ENCODER_R_TIM, ENCODER_R_SPD_PIN, ENCODER_R_DIR_PIN);
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
    static uint8_t time = 0;

    // Get encoder speed data
    if (time == 19)
    {
        leftSpeed = encoder_get_count(ENCODER_L_TIM);
        encoder_clear_count(ENCODER_L_TIM);
        rightSpeed = -encoder_get_count(ENCODER_R_TIM);
        encoder_clear_count(ENCODER_R_TIM);
        speedInput = (leftSpeed + rightSpeed) / 2;
        vofaData[0] = speedInput;
        // PID calculate
        averageSpdOut = PidIncControl(&spdParam, speedInput);
        leftSpdOut += averageSpdOut + (int32_t) spdParam.out;
        rightSpdOut += averageSpdOut - (int32_t) spdParam.out;
        time = 0;
    } else
    {
        time += 1;
    }

    leftSpdOut = Limitation(leftSpdOut, -10000, 10000);
    vofaData[1] = leftSpdOut;
    rightSpdOut = Limitation(rightSpdOut, -10000, 10000);
    vofaData[2] = rightSpdOut;


//    if (leftSpdOut >= 0)
//    {
//        pwm_set_duty(MOTOR_L_PIN, leftSpdOut);
//        gpio_set_level(MOTOR_L_DIR_PIN, 0);
//    } else
//    {
//        pwm_set_duty(MOTOR_L_PIN, -leftSpdOut);
//        gpio_set_level(MOTOR_L_DIR_PIN, 1);
//    }
//    if (rightSpdOut >= 0)
//    {
//        pwm_set_duty(MOTOR_R_PIN, rightSpdOut);
//        gpio_set_level(MOTOR_R_DIR_PIN, 1);
//    } else
//    {
//        pwm_set_duty(MOTOR_R_PIN, -rightSpdOut);
//        gpio_set_level(MOTOR_R_DIR_PIN, 0);
//    }
}
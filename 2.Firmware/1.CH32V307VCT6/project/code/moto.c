#include "encoder.h"
#include "moto.h"
#include "pid.h"

// PID parameter array: *Param[5] = {kp, ki, kd, target_value, limitation}


void motoInit(void)
{
    pwm_init(SERVO_PIN, SERVO_FREQ, SERVO_MID);
    pwm_init(MOTOR_FLY_PIN, 1000, 0);
    gpio_init(MOTOR_FLY_DIR_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
    pwm_init(MOTOR_BACK_PIN, 1000, 0);
    gpio_init(MOTOR_BACK_DIR_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
}



void motoDutySet(pwm_channel_enum pin,int32_t duty)
{
    if(pin==MOTOR_BACK_PIN)
    {
        if(duty<0)
        {
            duty =-duty;
            gpio_set_level(MOTOR_BACK_DIR_PIN,GPIO_HIGH);
        }
        else if(duty>0)
		gpio_set_level(MOTOR_BACK_DIR_PIN,GPIO_LOW);
        pwm_set_duty(MOTOR_BACK_PIN,duty>PWM_DUTY_MAX?PWM_DUTY_MAX:duty);
    }
    else if(pin==MOTOR_FLY_PIN)
    {
        if(duty<0)
        {
            duty =-duty;
            gpio_set_level(MOTOR_FLY_DIR_PIN,GPIO_HIGH);
        }
        else if(duty>0)
        gpio_set_level(MOTOR_FLY_DIR_PIN,GPIO_LOW);
        pwm_set_duty(MOTOR_FLY_PIN,duty>PWM_DUTY_MAX?PWM_DUTY_MAX:duty);
    }
}

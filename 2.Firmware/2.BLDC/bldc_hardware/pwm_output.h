#ifndef _pwm_output_h_
#define _pwm_output_h_


#include "zf_common_typedef.h"
#include "bldc_config.h"
#include "hall.h"

typedef struct
{
    TIM_TypeDef *tim_ch;        // 使用的定时器
    vuint8  pwm_channel;        // PWM输出通道
    vuint16 pwm_duty_value;     // PWM占空比值

}pwm_output_struct;

extern pwm_output_struct motor1_pwm_output;
extern pwm_output_struct motor2_pwm_output;


void pwm_complementary_control(pwm_output_struct *pwm_output, uint8 status);
void pwm_complementary_set_duty(pwm_output_struct *pwm_output, hall_struct *hall, uint16 duty);
void pwm_complementary_brake(pwm_output_struct *pwm_output);
void pwm_a_bn_output(pwm_output_struct *pwm_output);
void pwm_a_cn_output(pwm_output_struct *pwm_output);
void pwm_b_cn_output(pwm_output_struct *pwm_output);
void pwm_b_an_output(pwm_output_struct *pwm_output);
void pwm_c_an_output(pwm_output_struct *pwm_output);
void pwm_c_bn_output(pwm_output_struct *pwm_output);
void pwm_complementary_init(motor_index_enum motor_index, pwm_output_struct *pwm_output);

#endif

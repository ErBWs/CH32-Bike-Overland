#ifndef _pwm_input_h_
#define _pwm_input_h_


#include "ch32v30x.h"
#include "ch32v30x_tim.h"
#include "ch32v30x_rcc.h"

#include "zf_common_typedef.h"
#include "bldc_config.h"



typedef enum
{
    FORWARD,    // 正转
    REVERSE,    // 反转
}MOTOR_DIR_enum;

typedef struct
{
    uint16 pwm_pin;             // 输入信号脉冲引脚
    uint16 dir_pin;             // 输入信号方向引脚
    TIM_TypeDef *tim_ch;        // 使用的定时器
    uint16 period;              // 输入信号的周期数值
    uint16 low;                 // 输入信号的低电平数值
    uint16 high;                // 输入信号的高电平数值
    uint16 freq;
    float  cycle;               // 输入信号的高电平百分比 数据范围0-1
    MOTOR_DIR_enum direction;   // 输入信号的方向 0：正转 1：反转
}pwm_input_struct;

extern pwm_input_struct motor1_pwm_input_value;

extern pwm_input_struct motor2_pwm_input_value;

void pwm_input_trigger_callback(pwm_input_struct *pwm_input);
void pwm_input_timeout_callback(pwm_input_struct *pwm_input);
void pwm_input_init(motor_index_enum motor_index, pwm_input_struct *pwm_input);

















#endif

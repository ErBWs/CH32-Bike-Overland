#ifndef _encoder_h_
#define _encoder_h_

#include "zf_common_typedef.h"
#include "bldc_config.h"



typedef struct
{
    uint32 pwm_pin;             // 输出信号脉冲引脚
    uint16 dir_pin;             // 输出信号方向引脚

}encoder_out_struct;


extern encoder_out_struct motor1_encoder_out;
extern encoder_out_struct motor2_encoder_out;


void encoder_out_speed(encoder_out_struct *encoder_out, int32 speed);
void encoder_init(motor_index_enum motor_index, encoder_out_struct *encoder_out);

#endif

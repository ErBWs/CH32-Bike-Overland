


#include "bldc_config.h"
#include "encoder.h"

#include "zf_common_headfile.h"

encoder_out_struct motor1_encoder_out;
encoder_out_struct motor2_encoder_out;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      输出电机方向信息
//  @param      *encoder_out  编码器输出结构体
//  @param      direction     输出方向引脚
//  @return     void
//  @since      内部调用，用户无需关心
//-------------------------------------------------------------------------------------------------------------------
void encoder_direction_out(encoder_out_struct *encoder_out, uint8 direction)
{
    gpio_set_level(encoder_out->dir_pin, direction);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      输出电机频率信息
//  @param      *encoder_out  编码器输出结构体
//  @param      frequency     输出频率
//  @return     void
//  @since      内部调用，用户无需关心
//-------------------------------------------------------------------------------------------------------------------
void tim_pwm_frequency(encoder_out_struct *encoder_out, uint16 frequency)
{
    if(frequency <= 6)
    {
        pwm_set_duty(encoder_out->pwm_pin,  0); // 频率过小的时候，将占空比设置为0即可

    }
    else
    {

        pwm_set_freq(encoder_out->pwm_pin, frequency, 5000);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      输出电机转速以及方向信息
//  @param      void 
//  @return     void					
//  @since      每次换相的时候翻转IO，外部控制器用编码器接口直接采集即可
//              速度引脚连接外部控制器编码器接口的A通道 方向引脚连接B通道
//-------------------------------------------------------------------------------------------------------------------
void encoder_out_speed(encoder_out_struct *encoder_out, int32 speed)
{
    uint32 speed_out;
    uint8  direction;

    speed_out = func_abs(speed);
    direction = speed >= 0 ? 1 : 0;

    // 输出电机转动方向
    encoder_direction_out(encoder_out, direction);

    // 输出电机转速
    tim_pwm_frequency(encoder_out, speed_out);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      编码器功能初始化
//  @param      motor_index     电机索引
//  @param      *encoder_out    使能开关结构体指针
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void encoder_init(motor_index_enum motor_index, encoder_out_struct *encoder_out)
{
    if(motor_index == MOTOR_1)
    {
        encoder_out->pwm_pin = TIM5_PWM_MAP0_CH1_A0;
        encoder_out->dir_pin = E2;
    }
    else if(motor_index == MOTOR_2)
    {
        encoder_out->pwm_pin = TIM8_PWM_MAP0_CH4_C9;
        encoder_out->dir_pin = E4;
    }

    pwm_init(encoder_out->pwm_pin, 1000, 0);
    gpio_init(encoder_out->dir_pin, GPO, 0, GPO_PUSH_PULL); // 初始化引脚
}

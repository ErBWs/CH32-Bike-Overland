#include "led.h"
#include "zf_common_headfile.h"
#include "motor.h"
#include "battery_adc.h"
#include "pwm_output.h"

led_struct motor1_led;
led_struct motor2_led;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      运行LED控制
//  @param      *led            led结构体指针
//  @param      status          打开或者关闭
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void led_run_control(led_struct *led, LED_STATUS_enum status)
{
    vofaData[led->run_pin] = status;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      错误LED控制
//  @param      *led            led结构体指针
//  @param      status          打开或者关闭
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void led_error_control(led_struct *led, LED_STATUS_enum status)
{
    vofaData[led->err_pin] = status;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      使能LED控制
//  @param      *led            led结构体指针
//  @param      status          打开或者关闭
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void led_enable_control(led_struct *led, LED_STATUS_enum status)
{
    vofaData[led->en_pin] = status;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      LED控制
//  @param      *led            led结构体指针
//  @param      *motor          电机结构体指针
//  @param      *pwm_output     PWM互补输出结构体指针
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void led_control(led_struct *led, motor_struct *motor, pwm_output_struct * pwm_output)
{
    // 电机已关闭
    if(MOTOR_DISABLE == motor->enable_status)
    {
        led_enable_control(led, LED_OFF);
        led_error_control(led, LED_OFF);
        led_run_control(led, LED_OFF);
    }
    // 电机已使能
    else
    {
        // 检查刹车信号是否有效
        if(TIM_GetFlagStatus(pwm_output->tim_ch, TIM_IT_Break) != RESET)
        {
            TIM_ClearITPendingBit(pwm_output->tim_ch, TIM_IT_Break);

            // 当刹车信号有效的时候会运行这里的代码
            // 例如点亮一个LED灯来指示
            led_error_control(led, LED_ON);
        }
        else
        {
            led_error_control(led, LED_OFF);
        }
    }

    // 检测是否在运转
    if(motor->speed_now)
    {
        led_run_control(led, LED_ON);
    }
    else
    {
        led_run_control(led, LED_OFF);
    }

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      LED灯初始化
//  @param      motor_index 电机索引
//  @param      *led       led结构体指针
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void led_init(motor_index_enum motor_index, led_struct *led)
{
    if(motor_index == MOTOR_1)
    {
        led->en_pin = 4;
        led->run_pin = 5;
        led->err_pin = 6;
    }
    else if(motor_index == MOTOR_2)
    {
        led->en_pin = 7;
        led->run_pin = 8;
        led->err_pin = 9;
    }
}


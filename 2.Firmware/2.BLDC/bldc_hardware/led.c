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
    gpio_set_level(led->run_pin ,status);
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
    gpio_set_level(led->err_pin, status);
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
    gpio_set_level(led->en_pin, status);
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
        // 电源电压低于设置的阈值 LED闪烁
        if(1 == battery_information.type)
        {
            static uint16 delay_time;
            static uint8  led_en_state;
            delay_time++;

            if(0 == (delay_time%100))
            {
                if(0 == led_en_state)
                {
                    led_enable_control(led, LED_ON);
                    led_en_state = 1;
                }
                else
                {
                    led_enable_control(led, LED_OFF);
                    led_en_state = 0;
                }
            }
        }
        // 电源电压正常，LED常亮
        else
        {
            led_enable_control(led, LED_ON);
        }

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
        led->en_pin = E10;
        led->run_pin = E11;
        led->err_pin = E12;
    }
    else if(motor_index == MOTOR_2)
    {
        led->en_pin = D4;
        led->run_pin = D5;
        led->err_pin = D6;
    }


    gpio_init(led->en_pin,  GPO, 1, GPO_PUSH_PULL);
    gpio_init(led->err_pin, GPO, 1, GPO_PUSH_PULL);
    gpio_init(led->run_pin, GPO, 1, GPO_PUSH_PULL);
}


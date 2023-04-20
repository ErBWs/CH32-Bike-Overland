#include "led.h"
#include "zf_common_headfile.h"
#include "motor.h"
#include "battery_adc.h"
#include "pwm_output.h"

led_struct motor1_led;
led_struct motor2_led;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����LED����
//  @param      *led            led�ṹ��ָ��
//  @param      status          �򿪻��߹ر�
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void led_run_control(led_struct *led, LED_STATUS_enum status)
{
    gpio_set_level(led->run_pin ,status);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����LED����
//  @param      *led            led�ṹ��ָ��
//  @param      status          �򿪻��߹ر�
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void led_error_control(led_struct *led, LED_STATUS_enum status)
{
    gpio_set_level(led->err_pin, status);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʹ��LED����
//  @param      *led            led�ṹ��ָ��
//  @param      status          �򿪻��߹ر�
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void led_enable_control(led_struct *led, LED_STATUS_enum status)
{
    gpio_set_level(led->en_pin, status);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      LED����
//  @param      *led            led�ṹ��ָ��
//  @param      *motor          ����ṹ��ָ��
//  @param      *pwm_output     PWM��������ṹ��ָ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void led_control(led_struct *led, motor_struct *motor, pwm_output_struct * pwm_output)
{
    // ����ѹر�
    if(MOTOR_DISABLE == motor->enable_status)
    {
        led_enable_control(led, LED_OFF);
        led_error_control(led, LED_OFF);
        led_run_control(led, LED_OFF);
    }
    // �����ʹ��
    else
    {
        // ��Դ��ѹ�������õ���ֵ LED��˸
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
        // ��Դ��ѹ������LED����
        else
        {
            led_enable_control(led, LED_ON);
        }

        // ���ɲ���ź��Ƿ���Ч
        if(TIM_GetFlagStatus(pwm_output->tim_ch, TIM_IT_Break) != RESET)
        {
            TIM_ClearITPendingBit(pwm_output->tim_ch, TIM_IT_Break);

            // ��ɲ���ź���Ч��ʱ�����������Ĵ���
            // �������һ��LED����ָʾ
            led_error_control(led, LED_ON);
        }
        else
        {
            led_error_control(led, LED_OFF);
        }
    }

    // ����Ƿ�����ת
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
//  @brief      LED�Ƴ�ʼ��
//  @param      motor_index �������
//  @param      *led       led�ṹ��ָ��
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


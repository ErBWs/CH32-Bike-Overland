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
    vofaData[led->run_pin] = status;
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
    vofaData[led->err_pin] = status;
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
    vofaData[led->en_pin] = status;
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


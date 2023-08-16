


#include "bldc_config.h"
#include "encoder.h"

#include "zf_common_headfile.h"

encoder_out_struct motor1_encoder_out;
encoder_out_struct motor2_encoder_out;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������������Ϣ
//  @param      *encoder_out  ����������ṹ��
//  @param      direction     �����������
//  @return     void
//  @since      �ڲ����ã��û��������
//-------------------------------------------------------------------------------------------------------------------
void encoder_direction_out(encoder_out_struct *encoder_out, uint8 direction)
{
    gpio_set_level(encoder_out->dir_pin, direction);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������Ƶ����Ϣ
//  @param      *encoder_out  ����������ṹ��
//  @param      frequency     ���Ƶ��
//  @return     void
//  @since      �ڲ����ã��û��������
//-------------------------------------------------------------------------------------------------------------------
void tim_pwm_frequency(encoder_out_struct *encoder_out, uint16 frequency)
{
    if(frequency <= 6)
    {
        pwm_set_duty(encoder_out->pwm_pin,  0); // Ƶ�ʹ�С��ʱ�򣬽�ռ�ձ�����Ϊ0����

    }
    else
    {

        pwm_set_freq(encoder_out->pwm_pin, frequency, 5000);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ת���Լ�������Ϣ
//  @param      void 
//  @return     void					
//  @since      ÿ�λ����ʱ��תIO���ⲿ�������ñ������ӿ�ֱ�Ӳɼ�����
//              �ٶ����������ⲿ�������������ӿڵ�Aͨ�� ������������Bͨ��
//-------------------------------------------------------------------------------------------------------------------
void encoder_out_speed(encoder_out_struct *encoder_out, int32 speed)
{
    uint32 speed_out;
    uint8  direction;

    speed_out = func_abs(speed);
    direction = speed >= 0 ? 1 : 0;

    // ������ת������
    encoder_direction_out(encoder_out, direction);

    // ������ת��
    tim_pwm_frequency(encoder_out, speed_out);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������ܳ�ʼ��
//  @param      motor_index     �������
//  @param      *encoder_out    ʹ�ܿ��ؽṹ��ָ��
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
    gpio_init(encoder_out->dir_pin, GPO, 0, GPO_PUSH_PULL); // ��ʼ������
}

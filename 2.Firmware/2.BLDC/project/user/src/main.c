/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2023-03-31        ��W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "user_header.h"

#include "hall.h"
#include "pwm_output.h"
#include "pwm_input.h"
#include "led.h"
#include "operational_amplifier.h"
#include "comparator.h"
#include "motor.h"
#include "en_switch.h"
#include "encoder.h"
#include "move_filter.h"
#include "battery_adc.h"
#include "virtual_oscilloscope.h"




int main (void)
{
    // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
    clock_init(SYSTEM_CLOCK_144M);
    // ��ʼ��Ĭ�� Debug UART
    debug_init();

    //------------------------���1��ʼ��-------------------------//
    // ��ʼ��LED����
    led_init(MOTOR_1, &motor1_led);

    // ��ʼ���˷ţ�����������ĵ�ѹ���зŴ�Ȼ�󴫵ݸ��Ƚ���
    operational_amplifier_init(MOTOR_1);

    // ��ʼ���Ƚ���������ʵ�ֶ�ת�������Ƚ�������ʱ�Զ��ر�PWM�������������ֶ��ر�
    comparator_init(MOTOR_1);

    // �����˲���ʼ��
    move_filter_init(&motor1_speed_filter);

    // ������ʼ��
    hall_init(MOTOR_1, &motor1_hall);

    // pi�ջ���ʼ��
    closed_loop_pi_init(&motor1_closed_loop);

    // �ٶ����߳�ʼ��
    motor_speed_curve_init(&motor1_control, &motor1_speed_filter);

    // ��ʼ������ٶ��뷽����Ϣ������
    encoder_init(MOTOR_1, &motor1_encoder_out);

    // �����źŲ����ʼ��
    pwm_input_init(MOTOR_1, &motor1_pwm_input_value);

    // ʹ�ܿ��س�ʼ��
    switch_init(MOTOR_1, &motor1_enable_switch);

    // ���adc���ų�ʼ��
    motor_init(MOTOR_1, &motor1_control);

    // ���õ��1ΪN�����ֵ��
    motor_set_type(&motor1_control, BLDC_MOTOR_MOMENTUM);

    // N�����ּ�����Ϊ7
    motor_set_polepairs(&motor1_control, 7);

    // ���õ����ǰ�Ƕȣ�60��
    motor_set_commutation_angle(&motor1_control, 60);

    // ��ʼ����ʱ��1�������������PWM
    pwm_complementary_init(MOTOR_1, &motor1_pwm_output);

    //------------------------���1��ʼ��-------------------------//

    //------------------------���2��ʼ��-------------------------//
    // ��ʼ��LED����
    led_init(MOTOR_2, &motor2_led);

    // ��ʼ���˷ţ�����������ĵ�ѹ���зŴ�Ȼ�󴫵ݸ��Ƚ���
    operational_amplifier_init(MOTOR_2);

    // ��ʼ���Ƚ���������ʵ�ֶ�ת�������Ƚ�������ʱ�Զ��ر�PWM�������������ֶ��ر�
    comparator_init(MOTOR_2);

    // �����˲���ʼ��
    move_filter_init(&motor2_speed_filter);

    // ������ʼ��
    hall_init(MOTOR_2, &motor2_hall);

    // pi�ջ���ʼ��
    closed_loop_pi_init(&motor2_closed_loop);

    // �ٶ����߳�ʼ��
    motor_speed_curve_init(&motor2_control, &motor2_speed_filter);

    // ��ʼ������ٶ��뷽����Ϣ������
    encoder_init(MOTOR_2, &motor2_encoder_out);

    // �����źŲ����ʼ��
    pwm_input_init(MOTOR_2, &motor2_pwm_input_value);

    // ʹ�ܿ��س�ʼ��
    switch_init(MOTOR_2, &motor2_enable_switch);

    // ���adc���ų�ʼ��
    motor_init(MOTOR_2, &motor2_control);

    // ���õ��2ΪN�����ֵ��
    motor_set_type(&motor2_control, BLDC_MOTOR_MOMENTUM);

    // N�����ּ�����Ϊ7
    motor_set_polepairs(&motor2_control, 7);

    // ���õ����ǰ�Ƕȣ�60��
    motor_set_commutation_angle(&motor2_control, 60);

    // ��ʼ����ʱ��9�������������PWM
    pwm_complementary_init(MOTOR_2, &motor2_pwm_output);
    //------------------------���2��ʼ��-------------------------//

//    // ��ʼ��adcͨ����adc���ڲɼ���Դ��ѹ
//    battery_adc_init();

    // ��ʼ����ʱ��6������PI�ջ�����
    pit_ms_init(TIM6_PIT, 1);

    while(1)
    {

//        // �������ݵ�����ʾ���� ����ʾ������������ https://pan.baidu.com/s/198CMXTZsbI3HAEqNXDngBw
//        virtual_oscilloscope_data_conversion(motor1_control.speed_now/10, motor1_pwm_input_value.cycle*1000,
//                                             motor2_control.speed_now/10, motor2_pwm_input_value.cycle*1000);
//        uart_write_buffer(DEBUG_UART_INDEX, virtual_oscilloscope_data, sizeof(virtual_oscilloscope_data));

        vofaData[0] = motor1_control.speed_now/10;          // Motor1 speed
        vofaData[1] = motor1_pwm_input_value.cycle*1000;    // Motor1 speed input
        vofaData[2] = motor2_control.speed_now/10;          // Motor2 speed
        vofaData[3] = motor2_pwm_input_value.cycle*1000;    // Motor2 speed input

        // �����״̬Ȼ����ƶ�Ӧ��LED�Ƶ�����Ϩ��
        led_control(&motor1_led, &motor1_control, &motor1_pwm_output);
        led_control(&motor2_led, &motor2_control, &motor2_pwm_output);

//        VofaLittleEndianSendFrame();
    }
}
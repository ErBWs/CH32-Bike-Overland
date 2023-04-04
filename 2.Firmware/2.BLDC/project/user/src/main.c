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
* 2022-09-15        ��W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "easy_key.h"
#include "ips096.h"
#include "vofa.h"

int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART

    // �˴���д�û����� ���������ʼ�������
    EasyKeyInit(&keyL, E2);
    EasyKeyInit(&keyC, E3);
    EasyKeyInit(&keyR, E4);
//    printf("uart3 success\n");
    ips096_init();
//    ips096_full(RGB565_CYAN);
//    imu660ra_init();
    pit_init(TIM1_PIT, 1);
//    pwm_init(TIM8_PWM_MAP1_CH4_C13, 1000, 5000);  // Buzzer
//    pwm_init(TIM2_PWM_MAP1_CH1_A15, 50, 800);     // Servo
    timer_init(TIM_2, TIMER_US);
    // �˴���д�û����� ���������ʼ�������

    while(1)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
//        timer_start(TIM_2);
//        timer_stop(TIM_2);
//        ips114_show_int(0, 0, timer_get(TIM_2), 5);
//        timer_clear(TIM_2);
//        imu660ra_get_gyro();
//        vofaData[0] = imu660ra_gyro_x;
//        vofaData[1] = imu660ra_gyro_y;
//        vofaData[2] = imu660ra_gyro_z;
//        VofaLittleEndianSendFrame();
//        system_delay_ms(10);
//        ips114_show_int(0, 0, count++, 5);
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}


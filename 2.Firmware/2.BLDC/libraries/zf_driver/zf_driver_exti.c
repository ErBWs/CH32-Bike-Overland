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
* �ļ�����          zf_driver_exti
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

#include "zf_common_interrupt.h"

#include "zf_driver_exti.h"
#include "zf_driver_gpio.h"

//-------------------------------------------------------------------------------------------------------------------
// �������     EXTI �ж�ʹ��
// ����˵��     pin              ѡ�� EXTI ���� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     exti_enable(A0);
//-------------------------------------------------------------------------------------------------------------------
void exti_enable (gpio_pin_enum pin)
{
    EXTI->INTENR |= (0x00000001 << (pin&0x1F));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     EXTI �ж�ʧ��
// ����˵��     pin             ѡ�� EXTI ���� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     exti_disable(A0);
//-------------------------------------------------------------------------------------------------------------------
void exti_disable (gpio_pin_enum pin)
{
    EXTI->INTENR &= ~(0x00000001 << (pin&0x1F));
}


//-------------------------------------------------------------------------------------------------------------------
// �������     EXTI �жϳ�ʼ�� <ͬһ�±�����Ų���ͬʱ��ʼ��Ϊ�ⲿ�ж����� ���� A0 �� B0 ����ͬʱ��ʼ��Ϊ�ⲿ�ж�����>
// ����˵��     pin             ѡ�� EXTI ���� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ����˵��     trigger         ѡ�񴥷����źŷ�ʽ [EXTI_TRIGGER_RISING/EXTI_TRIGGER_FALLING/EXTI_TRIGGER_BOTH]
// ���ز���     void
// ʹ��ʾ��     exti_init(A0, EXTI_TRIGGER_RISING);
//-------------------------------------------------------------------------------------------------------------------
void exti_init (gpio_pin_enum pin, exti_trigger_enum trigger)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                         // ����ʱ��ʹ��
    gpio_init(pin, GPI, GPIO_HIGH, GPI_PULL_UP);                                // ��ʼ��ѡ�е�����
    GPIO_EXTILineConfig(pin >> 5, pin & 0x1F);                                  // ѡ����һ��GPIO���ж�

    EXTI_InitTypeDef EXTI_InitStructure = {0};
    EXTI_InitStructure.EXTI_Line = 1 << (pin & 0x1F);                           // ���ź�����
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                         // ����ģʽ
    EXTI_InitStructure.EXTI_Trigger = trigger;                                  // ������ʽ
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                                   // ʹ�ܻ���ʧ��
    EXTI_Init(&EXTI_InitStructure);

    if((pin&0x1F) < 1)
       interrupt_enable(EXTI0_IRQn);                                             // ʹ�� Line0 ���ж���Ӧ
    else if((pin&0x1F) < 2)
       interrupt_enable(EXTI1_IRQn);                                             // ʹ�� Line1 ���ж���Ӧ
    else if((pin&0x1F) < 3)
       interrupt_enable(EXTI2_IRQn);                                             // ʹ�� Line2 ���ж���Ӧ
    else if((pin&0x1F) < 4)
       interrupt_enable(EXTI3_IRQn);                                             // ʹ�� Line3 ���ж���Ӧ
    else if((pin&0x1F) < 5)
       interrupt_enable(EXTI4_IRQn);                                             // ʹ�� Line4 ���ж���Ӧ
    else if((pin&0x1F) < 10)
       interrupt_enable(EXTI9_5_IRQn);                                           // ʹ�� Line5-9 ���ж���Ӧ
    else
       interrupt_enable(EXTI15_10_IRQn);                                         // ʹ�� Line10-15 ���ж���Ӧ
}


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
* �ļ�����          zf_driver_pit
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


#include "ch32v30x_rcc.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_timer.h"

#include "zf_driver_pit.h"

//-------------------------------------------------------------------------------------------------------------------
// �������      PIT �ж�ʹ��
// ����˵��     pit_n           PIT ����ģ���
// ���ز���     void
// ʹ��ʾ��     pit_enable(TIM1_PIT);
//-------------------------------------------------------------------------------------------------------------------
void pit_enable (pit_index_enum pit_n)
{
    const uint32 irq_index[] =
    {
        TIM1_UP_IRQn,
        TIM2_IRQn,
        TIM3_IRQn,
        TIM4_IRQn,
        TIM5_IRQn,
        TIM6_IRQn,
        TIM7_IRQn,
        TIM8_UP_IRQn,
        TIM9_UP_IRQn,
        TIM10_UP_IRQn
    };
    interrupt_enable(irq_index[pit_n]);                                // ʹ���ж�
}

//-------------------------------------------------------------------------------------------------------------------
// �������      PIT �жϽ�ֹ
// ����˵��     pit_n           PIT ����ģ���
// ���ز���     void
// ʹ��ʾ��     pit_disable(TIM1_PIT);
//-------------------------------------------------------------------------------------------------------------------
void pit_disable (pit_index_enum pit_n)
{
    const uint32 irq_index[] =
    {
        TIM1_UP_IRQn,
        TIM2_IRQn,
        TIM3_IRQn,
        TIM4_IRQn,
        TIM5_IRQn,
        TIM6_IRQn,
        TIM7_IRQn,
        TIM8_UP_IRQn,
        TIM9_UP_IRQn,
        TIM10_UP_IRQn
    };

    interrupt_disable(irq_index[pit_n]);                                // ʧ���ж�

}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʱ�������ж�
// ����˵��     timer_ch      ��ʱ��ͨ��
// ����˵��     us          ��ʱ����(1-65535)
// ���ز���     void
// ��ע��Ϣ           pit_init(TIMER_1, 5); ʹ�ö�ʱ��1��Ϊ5msһ�ε������ж�
//-------------------------------------------------------------------------------------------------------------------
void pit_init (pit_index_enum pit_n, uint32 period)
{

    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
    // �����Ǽ���Ƿ����ظ�ʹ�ö�ʱ��
    // �����ʼ���� TIM1_PWM Ȼ���ֳ�ʼ���� TIM1_PIT �����÷��ǲ������
    zf_assert(timer_funciton_check((timer_index_enum)pit_n, TIMER_FUNCTION_TIMER));
    // �������һ�б��� ���Ҿ͵�������Ϊʲô����д���� 0
    zf_assert(period!=0);

    uint16 freq_div = (period >> 15);                                           // ����Ԥ��Ƶ
    uint16 period_temp = (period / (freq_div+1));                               // �����Զ���װ��ֵ

    timer_clock_enable(pit_n);                                                  // ʹ��ʱ��


    TIM_TypeDef *tim_index = TIM1;
    switch(pit_n)
    {
        case TIM_1:  tim_index = ((TIM_TypeDef *)TIM1_BASE);    break;
        case TIM_2:  tim_index = ((TIM_TypeDef *)TIM2_BASE);    break;
        case TIM_3:  tim_index = ((TIM_TypeDef *)TIM3_BASE);    break;
        case TIM_4:  tim_index = ((TIM_TypeDef *)TIM4_BASE);    break;
        case TIM_5:  tim_index = ((TIM_TypeDef *)TIM5_BASE);    break;
        case TIM_6:  tim_index = ((TIM_TypeDef *)TIM6_BASE);    break;
        case TIM_7:  tim_index = ((TIM_TypeDef *)TIM7_BASE);    break;
        case TIM_8:  tim_index = ((TIM_TypeDef *)TIM8_BASE);    break;
        case TIM_9:  tim_index = ((TIM_TypeDef *)TIM9_BASE);    break;
        case TIM_10: tim_index = ((TIM_TypeDef *)TIM10_BASE);   break;
    }


    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
    TIM_TimeBaseStructure.TIM_Period = period_temp;
    TIM_TimeBaseStructure.TIM_Prescaler = freq_div;                             // ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     // ����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 // TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                            // �ظ�����������Ϊ0
    TIM_TimeBaseInit(tim_index, &TIM_TimeBaseStructure);                        // ����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    TIM_ITConfig(tim_index,TIM_IT_Update,ENABLE );                              // ʹ��ָ����TIM�ж�,��������ж�
    TIM_ClearITPendingBit(tim_index, TIM_IT_Update);

    const uint32  irq_index[10] =
    {
        TIM1_UP_IRQn,
        TIM2_IRQn,
        TIM3_IRQn,
        TIM4_IRQn,
        TIM5_IRQn,
        TIM6_IRQn,
        TIM7_IRQn,
        TIM8_UP_IRQn,
        TIM9_UP_IRQn,
        TIM10_UP_IRQn
    };

    interrupt_set_priority((IRQn_Type)irq_index[(uint8)pit_n], 0x03);           // �����ж����ȼ�
    interrupt_enable((IRQn_Type)irq_index[pit_n]);                              // ʹ���ж�

    TIM_Cmd(tim_index, ENABLE);                                                 // ʹ�ܶ�ʱ��
}

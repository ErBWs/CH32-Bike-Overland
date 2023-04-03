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
* �ļ�����          zf_driver_timer
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

#include "zf_driver_gpio.h"
#include "zf_driver_timer.h"


// �������ֹ�޸ģ��ڲ�ʹ��,�û��������
static timer_function_enum timer_function_state[10] =
{
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT
};

// �������ֹ�޸ģ��ڲ�ʹ��,�û��������
static timer_mode_enum timer_mode_state[10] =
{
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK
};

//-------------------------------------------------------------------------------------------------------------------
// �������      TIMER ����ȷ�Ϲ���״̬ ���ڲ�����
// ����˵��     index           TIMER ����ģ���
// ����˵��     mode            ��Ҫȷ�Ĺ���ģ��
// ���ز���     uint8           1-����ʹ�� 0-������ʹ��
// ʹ��ʾ��     zf_assert(timer_funciton_check(TIM_1, TIMER_FUNCTION_PWM);
//-------------------------------------------------------------------------------------------------------------------
uint8 timer_funciton_check (timer_index_enum index, timer_function_enum mode)
{
    uint8 return_state = 1;
    if(TIMER_FUNCTION_INIT == timer_function_state[index])
    {
        timer_function_state[index] = mode;
    }
    else if(timer_function_state[index] == mode)
    {
        return_state = 1;
    }
    else
    {
        return_state = 0;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʱ��ʱ�����߳�ʼ��
// ����˵��     timer_ch      ��ʱ��ͨ��
// ���ز���     void
// ��ע��Ϣ          �ڲ�ʹ�ã��û��������
//-------------------------------------------------------------------------------------------------------------------
void timer_clock_enable(timer_index_enum index)
{
    if(TIM_1 == index)        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//ʹ�ܶ�ʱ��1��ʱ��
    else  if(TIM_2 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܶ�ʱ��2��ʱ��
    else  if(TIM_3 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ʹ�ܶ�ʱ��3��ʱ��
    else  if(TIM_4 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
    else  if(TIM_5 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//ʹ�ܶ�ʱ��5��ʱ��
    else  if(TIM_6 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);//ʹ�ܶ�ʱ��6��ʱ��
    else  if(TIM_7 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);//ʹ�ܶ�ʱ��7��ʱ��
    else  if(TIM_8 == index)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//ʹ�ܶ�ʱ��8��ʱ��
    else  if(TIM_9 == index)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);//ʹ�ܶ�ʱ��9��ʱ��
    else  if(TIM_10== index)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);//ʹ�ܶ�ʱ��10��ʱ��
}



//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʱ����ʼ
// ����˵��     timer_ch      ѡ��ģ���ͨ�� (ѡ��Χ ��TIMERN_enumö��ֵ������ȷ��)
// ���ز���     void
// ʹ��ʾ��     timer_start(TIM_1, TIMER_US);  //��ʱ��1 ��ʼ������ÿһus����һ��
//-------------------------------------------------------------------------------------------------------------------
void timer_start(timer_index_enum index)
{
    TIM_TypeDef *tim_index = TIM1;
    switch(index)
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
    TIM_Cmd(tim_index, ENABLE);                                          // ʹ��TIMx
}


//-------------------------------------------------------------------------------------------------------------------
// �������     �رռ�ʱ��
// ����˵��     timer_ch      ѡ��ģ���ͨ�� (ѡ��Χ ��TIMERN_enumö��ֵ������ȷ��)
// ���ز���     void
// ��ע��Ϣ             �رն�ʱ���������־λ
//-------------------------------------------------------------------------------------------------------------------
void timer_stop(timer_index_enum index)
{
    TIM_TypeDef *tim_index = TIM1;

    switch(index)
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

    TIM_Cmd(tim_index, DISABLE);  //ʧ��TIM
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ��ʱ��ֵ
// ����˵��     timer_ch      ѡ��ģ���ͨ�� (ѡ��Χ ��TIMERN_enumö��ֵ������ȷ��)
// ���ز���     uint32      ����ֵ
// ʹ��ʾ��     timer_get(TIM_1)  //��ȡ��ʱ��1�ļ�ʱʱ��
//-------------------------------------------------------------------------------------------------------------------
uint16 timer_get(timer_index_enum index)
{
    TIM_TypeDef *tim_index = TIM1;
    uint16 return_value = 0;

    switch(index)
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


    if(timer_mode_state[index] == TIMER_MS)
    {
        return_value = tim_index->CNT/3;
    }
    else
    {
        return_value = tim_index->CNT;
    }
    return return_value;
}



//-------------------------------------------------------------------------------------------------------------------
// �������     TIMER �����ʱ������
// ����˵��     index           TIMER ����ģ���
// ���ز���     void
// ʹ��ʾ��     timer_clear(TIM_1);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void timer_clear (timer_index_enum index)
{
    TIM_TypeDef *tim_index = TIM1;

    switch(index)
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
    tim_index->CNT = 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TIMER ��ʱ����ʼ��
// ����˵��     index           TIMER ����ģ���
// ����˵��     mode            ��ʱ��ʽ
// ���ز���     void
// ʹ��ʾ��     timer_init(TIM_1, TIMER_US);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void timer_init(timer_index_enum index, timer_mode_enum mode)
{

    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
    // �����Ǽ���Ƿ����ظ�ʹ�ö�ʱ��
    // �����ʼ���� TIM1_PWM Ȼ���ֳ�ʼ���� TIM_1 �����÷��ǲ������
    zf_assert(timer_funciton_check(index, TIMER_FUNCTION_TIMER));
    timer_function_state[index] = TIMER_FUNCTION_TIMER;

    TIM_TypeDef *tim_index = TIM1;
    switch(index)
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



    timer_clock_enable(index);                                                  // ����ʱ������

    timer_mode_state[index] = mode;

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
    if(mode == TIMER_US)
    {
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                              // װ���Զ���װ��ֵ
        TIM_TimeBaseStructure.TIM_Prescaler = (system_clock/1000000)-1;         // װ��Ԥ��Ƶ
    }
    else if(mode == TIMER_MS)
    {
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                              // װ���Զ���װ��ֵ
        TIM_TimeBaseStructure.TIM_Prescaler = (system_clock/1000)/3-1;          // װ��Ԥ��Ƶ
    }
    else
    {
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                              // װ���Զ���װ��ֵ
        TIM_TimeBaseStructure.TIM_Prescaler = 0;                                // װ��Ԥ��Ƶ
    }
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     // ����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 // TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                            // �ظ�����������Ϊ0
    TIM_TimeBaseInit(tim_index, &TIM_TimeBaseStructure);                        // ����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_Cmd(tim_index, ENABLE);                                                 // ʹ��TIMx
}


#include "hall.h"
#include "bldc_config.h"

#include "zf_common_headfile.h"

hall_struct motor1_hall;
hall_struct motor2_hall;


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ��ǰ����ֵ
//  @param      *hall   �����ṹ��ָ��
//  @return     uint8   ����ֵ
//  @since      
//-------------------------------------------------------------------------------------------------------------------
uint8 hall_value_read(hall_struct *hall)
{
    uint8 hall_a;
    uint8 hall_b;
    uint8 hall_c;

    hall_a = gpio_get_level(hall->hall_a_pin);
    hall_b = gpio_get_level(hall->hall_b_pin);
    hall_c = gpio_get_level(hall->hall_c_pin);
    return (hall_a*4 + hall_b*2 + hall_c);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����ʱ��
//  @param      *hall   �����ṹ��ָ��
//  @return     uint16  ����ʱ��
//  @since      
//-------------------------------------------------------------------------------------------------------------------
uint16 hall_interval_time(hall_struct *hall)
{
    return TIM_GetCapture1(hall->tim_ch);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ʱ����ʱ��
//  @param      *hall       �����ṹ��ָ��
//  @param      delay_time  ���õ�ʱ��
//  @return     void
//  @since      
//-------------------------------------------------------------------------------------------------------------------
void hall_delay_set(hall_struct *hall, uint32 delay_time)
{
    //����Ӧ���жϣ�������õ�ʱ��С�ڼ���ֵ��ֱ�Ӵ����ж�
    if((hall->tim_ch->CNT+5) < (delay_time))
    {
        TIM_SetCompare2(hall->tim_ch, delay_time);
    }
    else
    {
        // ��ʱ��ʱ���붨ʱ���ļ���ֵ���ڽӽ���ֱ�Ӵ����ж�
        hall->tim_ch->INTFR = TIM_FLAG_CC2;
    }
    
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʹ�ܻ�ʧ���ӳٻ���
//  @param      *hall       �����ṹ��ָ��
//  @param      state       ʹ�ܻ�ʧ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void hall_delay_state_set(hall_struct *hall, uint8 state)
{
    TIM_ClearFlag(hall->tim_ch, TIM_FLAG_CC2);
    TIM_ITConfig(hall->tim_ch, TIM_IT_CC2, (FunctionalState)state);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����ɼ���ʼ��
//  @param      motor_index �������
//  @param      *hall       �����ṹ��ָ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void hall_init(motor_index_enum motor_index, hall_struct *hall)
{
    if(motor_index == MOTOR_1)
    {
        hall->hall_a_pin = C6;
        hall->hall_b_pin = C7;
        hall->hall_c_pin = C8;
        hall->tim_ch = TIM3;
        hall->irqn = TIM3_IRQn;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);            // ʹ��AFIO���ù���ģ��ʱ��
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);               // ��ȫ��ӳ��

        interrupt_enable(hall->irqn);                                    // ʹ���ж�
        interrupt_set_priority(hall->irqn, 0<<5|0);                      // ��ռ���ȼ�0�������ȼ�0
    }
    else if(motor_index == MOTOR_2)
    {
        hall->hall_a_pin = B6;
        hall->hall_b_pin = B7;
        hall->hall_c_pin = B8;
        hall->tim_ch = TIM4;
        hall->irqn = TIM4_IRQn;

        interrupt_enable(hall->irqn);                                    // ʹ���ж�
        interrupt_set_priority(hall->irqn, 0<<5|0);                      // ��ռ���ȼ�0�������ȼ�0
    }

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};           // ʱ����ʼ���ṹ��
    TIM_ICInitTypeDef       TIM_ICInitStruct = {0};                 // ���벶���ʼ���ṹ��
    TIM_OCInitTypeDef       TIM_OCInitStructure = {0};

    if(hall->tim_ch == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }
    else if(hall->tim_ch == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }
    else if(hall->tim_ch == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }
    else if(hall->tim_ch == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    }
    else if(hall->tim_ch == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    }
    else if(hall->tim_ch == TIM6)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    }
    else if(hall->tim_ch == TIM7)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    }
    else if(hall->tim_ch == TIM8)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    }
    else if(hall->tim_ch == TIM9)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    }
    else if(hall->tim_ch == TIM10)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    }
    else
    {
        zf_assert(0);
    }

    gpio_init(hall->hall_a_pin, GPI, 0, GPI_PULL_UP);
    gpio_init(hall->hall_b_pin, GPI, 0, GPI_PULL_UP);
    gpio_init(hall->hall_c_pin, GPI, 0, GPI_PULL_UP);


    //ʱ����������
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;                    // ʱ�ӷָTDTS = TCK_INT ������Ƶ��=144M
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_CenterAligned1;    // ���Ķ���ģʽ
    TIM_TimeBaseInitStruct.TIM_Period = 50*1000 - 1;                            // ���ó�ʱʱ��Ϊ60ms
    TIM_TimeBaseInitStruct.TIM_Prescaler = SYSTEM_CLOCK/1000000;                // ��Ƶ��ʱ����Ƶ��Ϊ1000KHZ
    //ʱ����ʼ��
    TIM_TimeBaseInit(hall->tim_ch,&TIM_TimeBaseInitStruct);


    //ʹ��Timx�����������ӿڣ�ʵ���Ͼ�����ɽ�CH1��CH2��CH3�������
    TIM_SelectHallSensor(hall->tim_ch, ENABLE);

    // hall->tim_ch����ͨ��1��ʼ�������벶��ͨ��1����
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;                   // ͨ��1
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_BothEdge;      // �����غ��½���
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;              // ���������źŷ�Ƶ������Ƶ
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_TRC;         // ��IC1ӳ�䵽 TRC��
    TIM_ICInitStruct.TIM_ICFilter = 15;                             // �˲����ȣ�15
    TIM_ICInit(hall->tim_ch,&TIM_ICInitStruct);                     // ���벶���ʼ��

    TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;                   // ͨ��2
    TIM_ICInit(hall->tim_ch,&TIM_ICInitStruct);                     // ���벶���ʼ��

    TIM_ICInitStruct.TIM_Channel = TIM_Channel_3;                   // ͨ��3
    TIM_ICInit(hall->tim_ch,&TIM_ICInitStruct);                     // ���벶���ʼ��


    // hall->tim_ch���ͨ��2��ʼ������ʱ����
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1000;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(hall->tim_ch, &TIM_OCInitStructure);
    TIM_CCxCmd(hall->tim_ch, TIM_Channel_2, TIM_CCx_Disable);

    // hall->tim_ch���ͨ��3��ʼ�������ڼ�ⳬʱ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;               // TIM���ͨ����ʼ��
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseInitStruct.TIM_Period - 1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(hall->tim_ch, &TIM_OCInitStructure);
    TIM_CCxCmd(hall->tim_ch, TIM_Channel_3, TIM_CCx_Disable);
//    TIM_OC3PreloadConfig(hall->tim_ch, TIM_OCPreload_Enable);                      // ��ʱ��Ԥװ������
//    TIM_OC3FastConfig(hall->tim_ch, TIM_OC3FE);                                    // �Ƚϲ���ͨ������ʹ��


    TIM_SelectInputTrigger(hall->tim_ch, TIM_TS_TI1F_ED);                   // ���봥��Դѡ��ѡ��TI1F_ED
    TIM_SelectSlaveMode(hall->tim_ch, TIM_SlaveMode_Reset);                 // ��ģʽѡ�񣬸�λģʽ
//    TIM_SelectOutputTrigger(hall->tim_ch, TIM_TRGOSource_OC2Ref);         // ѡ���������ģʽ(TRGO��)
    TIM_SelectMasterSlaveMode(hall->tim_ch, TIM_MasterSlaveMode_Enable);    // ����ģʽѡ��


    TIM_ClearFlag(hall->tim_ch, TIM_FLAG_CC1);
    TIM_ClearFlag(hall->tim_ch, TIM_FLAG_CC3);

    TIM_ITConfig(hall->tim_ch, TIM_IT_CC1, ENABLE);
    TIM_ITConfig(hall->tim_ch, TIM_IT_CC3, ENABLE);

    TIM_Cmd(hall->tim_ch, ENABLE);

}

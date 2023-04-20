#include "pwm_input.h"
#include "zf_common_headfile.h"

pwm_input_struct motor1_pwm_input_value;
pwm_input_struct motor2_pwm_input_value;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM���벶�񴥷��жϻص�����
//  @param      *pwm_input     PWM���벶��ṹ��ָ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void pwm_input_trigger_callback(pwm_input_struct *pwm_input)
{
    float duty;
    pwm_input->high   = TIM_GetCapture1(pwm_input->tim_ch) + 1 ;    // ��ȡ�ߵ�ƽʱ��
    pwm_input->period = TIM_GetCapture2(pwm_input->tim_ch) + 1;     // ��ȡ����ֵ
    pwm_input->low    = pwm_input->period - pwm_input->high;        // ��ȡ�͵�ƽ
    pwm_input->freq   = (SYSTEM_CLOCK)/(SYSTEM_CLOCK/1000000) / pwm_input->period;

    duty = (float)pwm_input->high/pwm_input->period;

    duty = func_limit_ab(duty, 0.05, 0.95) - 0.05;
    // �������õķ������ռ�ձ�
    if(REVERSE == gpio_get_level(pwm_input->dir_pin))
    {
        duty = -duty;
    }

    pwm_input->cycle = duty;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM���벶��ʱ�жϻص�����
//  @param      *pwm_input     PWM���벶��ṹ��ָ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void pwm_input_timeout_callback(pwm_input_struct *pwm_input)
{
    pwm_input->high = 0;
    pwm_input->low = 0;
    pwm_input->period = 3000;       // ��ȡ����ֵ
    pwm_input->freq   = 0;
    pwm_input->cycle  = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���벶���ʼ��
//  @param      motor_index    �������
//  @param      *pwm_input     PWM���벶��ṹ��ָ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void pwm_input_init(motor_index_enum motor_index, pwm_input_struct *pwm_input)
{
    if(motor_index == MOTOR_1)
    {
        pwm_input->tim_ch = TIM2;
        pwm_input->dir_pin = E3;
        pwm_input->pwm_pin = B3;

        interrupt_enable(TIM2_IRQn);                                    // ʹ���ж�
        interrupt_set_priority(TIM2_IRQn, 1<<5|1);                      // ��ռ���ȼ�1�������ȼ�1

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);            // ʹ��AFIO���ù���ģ��ʱ��
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);               // ��ȫ��ӳ��
    }
    else if(motor_index == MOTOR_2)
    {
        pwm_input->tim_ch = TIM10;
        pwm_input->dir_pin = E5;
        pwm_input->pwm_pin = D3;


        interrupt_enable(TIM10_CC_IRQn);                                // ʹ���ж�
        interrupt_set_priority(TIM10_CC_IRQn, 1<<5|1);                  // ��ռ���ȼ�1�������ȼ�1

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);            // ʹ��AFIO���ù���ģ��ʱ��
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM10, ENABLE);              // ��ȫ��ӳ��
    }

    TIM_ICInitTypeDef       TIM_ICInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    if(pwm_input->tim_ch == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }
    else if(pwm_input->tim_ch == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }
    else if(pwm_input->tim_ch == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }
    else if(pwm_input->tim_ch == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    }
    else if(pwm_input->tim_ch == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    }
    else if(pwm_input->tim_ch == TIM6)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    }
    else if(pwm_input->tim_ch == TIM7)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    }
    else if(pwm_input->tim_ch == TIM8)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    }
    else if(pwm_input->tim_ch == TIM9)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    }
    else if(pwm_input->tim_ch == TIM10)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    }
    else
    {
        zf_assert(0);
    }

    gpio_init(pwm_input->dir_pin, GPI, 0, GPI_PULL_UP);
    gpio_init(pwm_input->pwm_pin, GPI, 0, GPI_PULL_UP);

    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
    TIM_TimeBaseInitStructure.TIM_Period = 0xffff;
    TIM_TimeBaseInitStructure.TIM_Prescaler = SYSTEM_CLOCK / 1000000 - 1; // ֧�ֵķ�Χ50hz-2Khz
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(pwm_input->tim_ch, &TIM_TimeBaseInitStructure);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;        // �½��ز������ߵ�ƽֵ
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
    TIM_ICInitStructure.TIM_ICFilter = 15;
    TIM_ICInit(pwm_input->tim_ch, &TIM_ICInitStructure);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;         // �����ز���������ֵ
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICFilter = 15;
    TIM_ICInit(pwm_input->tim_ch, &TIM_ICInitStructure);

    TIM_SelectInputTrigger(pwm_input->tim_ch, TIM_TS_TI2FP2);
    TIM_SelectSlaveMode(pwm_input->tim_ch, TIM_SlaveMode_Reset);
    TIM_SelectMasterSlaveMode(pwm_input->tim_ch, TIM_MasterSlaveMode_Enable);

    TIM_OCInitTypeDef       TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                       // PWMģʽ1����ʱ������ֵС�ڱȽ�ֵ��ʱ�����������Ч��ƽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;           // CHxͨ��ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;         //
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;               // CHx  ��Ч��ƽΪ�ߵ�ƽ ��Ч��ƽΪ�͵�ƽ
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;             // CHxN ��Ч��ƽΪ�ߵ�ƽ ��Ч��ƽΪ�͵�ƽ
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;            // CHx  ����״̬����͵�ƽ
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;          // CHxN ����״̬����͵�ƽ

    TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseInitStructure.TIM_Period - 1;   // ����ͨ��4�Ƚ�ֵ
    TIM_OC4Init(pwm_input->tim_ch, &TIM_OCInitStructure);                       // CC4�����жϳ�ʱ

    TIM_ITConfig(pwm_input->tim_ch, TIM_IT_CC2, ENABLE);                        // ʹ�ܴ����ж�
    TIM_ITConfig(pwm_input->tim_ch, TIM_IT_CC4, ENABLE);                        // ʹ��ͨ��4 �жϳ�ʱ
    TIM_ClearITPendingBit(pwm_input->tim_ch, TIM_IT_CC2);
    TIM_ClearITPendingBit(pwm_input->tim_ch, TIM_IT_CC4);

    TIM_Cmd(pwm_input->tim_ch, ENABLE);
}












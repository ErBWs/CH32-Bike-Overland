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
* �ļ�����          zf_driver_pwm
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
#include "zf_driver_pwm.h"


//-------------------------------------------------------------------------------------------------------------------
// �������     PWMռ�ձ��趨
// ����˵��     pwmch           PWMͨ���ż�����
// ����˵��     duty            PWMռ�ձ�
// ���ز���     void
// ʹ��ʾ��     pwm_set_duty(TIM10_PWM_CH4_C15, 5000);   //��ʱ��10 ͨ��4 ʹ������C15 ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//                              PWM_DUTY_MAX��zf_pwm.h�ļ��� Ĭ��Ϊ10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_duty(pwm_channel_enum pin, uint32 duty)
{
    // �������һ�б��� �����ȥ�������ռ�ձ����޶��Ķ��� ռ�ձ�д�����
    zf_assert(PWM_DUTY_MAX >= duty);                            // ռ�ձ�д�����



    TIM_TypeDef *tim_index = TIM1;
    switch((pin & 0xF0000) >> 16)                               // ��ȡTIM���
    {
        case 0: tim_index = TIM1;    break;
        case 1: tim_index = TIM2;    break;
        case 2: tim_index = TIM3;    break;
        case 3: tim_index = TIM4;    break;
        case 4: tim_index = TIM5;    break;
        case 7: tim_index = TIM8;    break;
        case 8: tim_index = TIM9;    break;
        case 9: tim_index = TIM10;   break;
    }


    uint16 match_temp;
    uint16 period_temp;

    period_temp = tim_index->ATRLR;                             // ��ȡ��ʱ��������ֵ
    match_temp = period_temp * duty / PWM_DUTY_MAX;             // ռ�ձ�



    if(((pin>>8) & 0x03) == 0x00)                               // ͨ��ѡ��
    {
        tim_index->CH1CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x01)                          // ͨ��ѡ��
    {
        tim_index->CH2CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x02)                          // ͨ��ѡ��
    {
        tim_index->CH3CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x03)                          // ͨ��ѡ��
    {
        tim_index->CH4CVR = match_temp;
    }

}

//-------------------------------------------------------------------------------------------------------------------
// �������     PWMƵ���趨
// ����˵��     pwmch           PWMͨ���ż�����
// ����˵��     freq            PWMƵ��
// ����˵��     duty            PWMռ�ձ�
// ���ز���     void
// ʹ��ʾ��     pwm_set_freq(PWM1_CH1_A8, 60, 5000);   //ʹ������A8  ���PWMƵ��60HZ   ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//                              PWM_DUTY_MAX��zf_pwm.h�ļ��� Ĭ��Ϊ10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_freq(pwm_channel_enum pin, uint32 freq, uint32 duty)
{
    uint16 period_temp = 0;                                     // ����ֵ
    uint16 freq_div = 0;                                        // ��Ƶֵ
    uint16 match_temp;

    freq_div = (uint16)((system_clock / freq) >> 16);           // ������ٷ�Ƶ
    period_temp = (uint16)(system_clock/(freq*(freq_div + 1))); // ��������

    // ��ȡTIM���
    TIM_TypeDef *tim_index = TIM1;
    switch((pin & 0xF0000) >> 16)
    {
        case 0: tim_index = TIM1;    break;
        case 1: tim_index = TIM2;    break;
        case 2: tim_index = TIM3;    break;
        case 3: tim_index = TIM4;    break;
        case 4: tim_index = TIM5;    break;
        case 7: tim_index = TIM8;    break;
        case 8: tim_index = TIM9;    break;
        case 9: tim_index = TIM10;   break;
    }



    tim_index->ATRLR = period_temp - 1 ;
    tim_index->PSC = freq_div;
    match_temp = period_temp * duty / PWM_DUTY_MAX;             // ռ�ձ�


    if(((pin>>8) & 0x03) == 0x00)                               // ͨ��ѡ��
    {
        tim_index->CH1CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x01)                          // ͨ��ѡ��
    {
        tim_index->CH2CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x02)                          // ͨ��ѡ��
    {
        tim_index->CH3CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x03)                          // ͨ��ѡ��
    {
        tim_index->CH4CVR = match_temp;
    }

}


//-------------------------------------------------------------------------------------------------------------------
// �������     PWM��ʼ��
// ����˵��     pwmch           PWMͨ���ż�����
// ����˵��     freq            PWMƵ��
// ����˵��     duty            PWMռ�ձ�
// ���ز���     void
// ʹ��ʾ��     pwm_init(PWM1_CH1_A8, 50, 5000);   //��ʼ��PWM1 ͨ��1 ʹ������A8  ���PWMƵ��50HZ   ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//                              PWM_DUTY_MAX��zf_pwm.h�ļ��� Ĭ��Ϊ10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(pwm_channel_enum pin, uint32 freq, uint32 duty)
{

    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
    // �����Ǽ���Ƿ����ظ�ʹ�ö�ʱ��
    // �����ʼ���� TIM1_PIT Ȼ���ֳ�ʼ���� TIM1_PWM �����÷��ǲ������
    zf_assert(timer_funciton_check((timer_index_enum)(pin>>16), TIMER_FUNCTION_PWM));
    // �������һ�б��� �����ȥ�������ռ�ձ����޶��Ķ��� ռ�ձ�д�����
    zf_assert(PWM_DUTY_MAX >= duty);

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
    TIM_OCInitTypeDef  TIM_OCInitStructure = {0};
    uint16 match_temp;                                                              // ռ�ձ�ֵ
    uint16 period_temp;                                                             // ����ֵ
    uint16 freq_div = 0;                                                            // ��Ƶֵ

    timer_clock_enable((pin & 0xF0000) >> 16);                                      // ��ʱ��ʱ��ʹ��

    gpio_init((gpio_pin_enum)(pin & 0xFF), GPO, 0, GPO_AF_PUSH_PULL | SPEED_50MHZ); // ��ʼ������

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                            // ʹ��AFIO���ù���ģ��ʱ��

    // ��ȡTIM���
    TIM_TypeDef *tim_index = TIM1;
    switch((pin & 0xF0000) >> 16)
    {
        case 0: tim_index = TIM1;    break;
        case 1: tim_index = TIM2;    break;
        case 2: tim_index = TIM3;    break;
        case 3: tim_index = TIM4;    break;
        case 4: tim_index = TIM5;    break;
        case 7: tim_index = TIM8;    break;
        case 8: tim_index = TIM9;    break;
        case 9: tim_index = TIM10;   break;
    }

    // �������ù���
    if((pin >> 12) == 0x03)      GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,        ENABLE);

    else if((pin >> 12) == 0x11) GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,    ENABLE);
    else if((pin >> 12) == 0x12) GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,    ENABLE);
    else if((pin >> 12) == 0x13) GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,        ENABLE);

    else if((pin >> 12) == 0x22) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,     ENABLE);
    else if((pin >> 12) == 0x23) GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,        ENABLE);
    else if((pin >> 12) == 0x31) GPIO_PinRemapConfig(GPIO_Remap_TIM4,            ENABLE);
    else if((pin >> 12) == 0x71) GPIO_PinRemapConfig(GPIO_Remap_TIM8,            ENABLE);
    else if((pin >> 12) == 0x83) GPIO_PinRemapConfig(GPIO_FullRemap_TIM9,        ENABLE);
    else if((pin >> 12) == 0x91) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM10,    ENABLE);
    else if((pin >> 12) == 0x93) GPIO_PinRemapConfig(GPIO_FullRemap_TIM10,       ENABLE);

    freq_div = (uint16)((system_clock / freq) >> 16);                               // ���ٷ�Ƶ
    period_temp = (uint16)(system_clock/(freq*(freq_div + 1)));                     // ����
    match_temp = period_temp * duty / PWM_DUTY_MAX;                                 // ռ�ձ�

    TIM_TimeBaseStructure.TIM_Period = period_temp - 1;                             // ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = freq_div;                                 // ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                         // ����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                     // TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(tim_index, &TIM_TimeBaseStructure);                            // ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                               // ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                   // �Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_Pulse = match_temp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                        // �������:TIM����Ƚϼ��Ե�
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_Low;                       // �������:TIM����Ƚϼ��Ե�
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

    if(((pin>>8) & 0x03) == 0x00)                                                   // ͨ��ѡ��
    {
        TIM_OC1Init(tim_index, &TIM_OCInitStructure );                              // ��ʱ��ͨ��1��ʼ��
        TIM_OC1PreloadConfig(tim_index, TIM_OCPreload_Enable);                      // ��ʱ��Ԥװ������
        TIM_OC1FastConfig(tim_index, TIM_OC1FE);                                    // �Ƚϲ���ͨ������ʹ��
    }
    else if(((pin>>8) & 0x03) == 0x01)
    {
        TIM_OC2Init(tim_index, &TIM_OCInitStructure );
        TIM_OC2PreloadConfig(tim_index, TIM_OCPreload_Enable);
        TIM_OC2FastConfig(tim_index, TIM_OC2FE);
    }
    else if(((pin>>8) & 0x03) == 0x02)
    {
        TIM_OC3Init(tim_index, &TIM_OCInitStructure );
        TIM_OC3PreloadConfig(tim_index, TIM_OCPreload_Enable);
        TIM_OC3FastConfig(tim_index, TIM_OC3FE);
    }
    else if(((pin>>8) & 0x03) == 0x03)
    {
        TIM_OC4Init(tim_index, &TIM_OCInitStructure );
        TIM_OC4PreloadConfig(tim_index, TIM_OCPreload_Enable);
        TIM_OC4FastConfig(tim_index, TIM_OC4FE);
    }
    TIM_CtrlPWMOutputs(tim_index, ENABLE );                                         // ͨ��PWM���ʹ��
    TIM_Cmd(tim_index, ENABLE);                                                     // ��ʱ��ʹ��
    //TIM_ARRPreloadConfig( TIM1, ENABLE );
}


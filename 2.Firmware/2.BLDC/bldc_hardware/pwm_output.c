
#include "pwm_output.h"
#include "bldc_config.h"
#include "zf_common_headfile.h"

pwm_output_struct motor1_pwm_output;
pwm_output_struct motor2_pwm_output;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʹ�ܻ�ʹ��PWM�������
//  @param      *pwm_output     PWM��������ṹ��ָ��
//  @param      status          ʹ�ܻ�ʧ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void pwm_complementary_control(pwm_output_struct *pwm_output, uint8 status)
{
    if(status)
    {
        TIM_CtrlPWMOutputs(pwm_output->tim_ch, ENABLE);
    }
    else
    {
        TIM_CtrlPWMOutputs(pwm_output->tim_ch, DISABLE);
        TIM_SetCompare1(pwm_output->tim_ch, 0);
        TIM_SetCompare2(pwm_output->tim_ch, 0);
        TIM_SetCompare3(pwm_output->tim_ch, 0);

        pwm_output->pwm_channel = 0;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ռ�ձ�
//  @param      *pwm_output     PWM��������ṹ��ָ��
//  @param      *hall           �����ṹ��ָ��
//  @param      duty            ռ�ձ�
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void pwm_complementary_set_duty(pwm_output_struct *pwm_output, hall_struct *hall, uint16 duty)
{
//    // ʧ��HALL�ж�
//    interrupt_disable(hall->irqn);

    pwm_output->pwm_duty_value = duty;
    switch(pwm_output->pwm_channel)
    {
        case 1:
        {
            TIM_SetCompare1(pwm_output->tim_ch, pwm_output->pwm_duty_value);
        }break;

        case 2:
        {
            TIM_SetCompare1(pwm_output->tim_ch, pwm_output->pwm_duty_value);
        }break;

        case 3:
        {
            TIM_SetCompare2(pwm_output->tim_ch, pwm_output->pwm_duty_value);
        }break;

        case 4:
        {
            TIM_SetCompare2(pwm_output->tim_ch, pwm_output->pwm_duty_value);
        }break;

        case 5:
        {
            TIM_SetCompare3(pwm_output->tim_ch, pwm_output->pwm_duty_value);
        }break;

        case 6:
        {
            TIM_SetCompare3(pwm_output->tim_ch, pwm_output->pwm_duty_value);
        }break;
    }

//    // ʹ��HALL�ж�
//    interrupt_enable(hall->irqn);
}

void pwm_a_bn_output(pwm_output_struct *pwm_output)
{

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_3, TIM_CCx_Disable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_3, TIM_CCxN_Disable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_1, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_1, TIM_CCxN_Enable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_2, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_2, TIM_CCxN_Enable);

    pwm_output->pwm_channel = 1;
    TIM_SetCompare1(pwm_output->tim_ch, pwm_output->pwm_duty_value);
    TIM_SetCompare2(pwm_output->tim_ch, 0);
}

void pwm_a_cn_output(pwm_output_struct *pwm_output)
{
    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_2, TIM_CCx_Disable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_2, TIM_CCxN_Disable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_1, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_1, TIM_CCxN_Enable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_3, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_3, TIM_CCxN_Enable);

    pwm_output->pwm_channel = 2;
    TIM_SetCompare1(pwm_output->tim_ch, pwm_output->pwm_duty_value);
    TIM_SetCompare3(pwm_output->tim_ch, 0);
}

void pwm_b_cn_output(pwm_output_struct *pwm_output)
{
    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_1, TIM_CCx_Disable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_1, TIM_CCxN_Disable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_2, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_2, TIM_CCxN_Enable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_3, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_3, TIM_CCxN_Enable);

    pwm_output->pwm_channel = 3;
    TIM_SetCompare2(pwm_output->tim_ch, pwm_output->pwm_duty_value);
    TIM_SetCompare3(pwm_output->tim_ch, 0);
}

void pwm_b_an_output(pwm_output_struct *pwm_output)
{
    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_3, TIM_CCx_Disable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_3, TIM_CCxN_Disable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_1, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_1, TIM_CCxN_Enable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_2, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_2, TIM_CCxN_Enable);

    pwm_output->pwm_channel = 4;
    TIM_SetCompare2(pwm_output->tim_ch, pwm_output->pwm_duty_value);
    TIM_SetCompare1(pwm_output->tim_ch, 0);
}

void pwm_c_an_output(pwm_output_struct *pwm_output)
{
    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_2, TIM_CCx_Disable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_2, TIM_CCxN_Disable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_1, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_1, TIM_CCxN_Enable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_3, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_3, TIM_CCxN_Enable);

    pwm_output->pwm_channel = 5;
    TIM_SetCompare3(pwm_output->tim_ch, pwm_output->pwm_duty_value);
    TIM_SetCompare1(pwm_output->tim_ch, 0);
}

void pwm_c_bn_output(pwm_output_struct *pwm_output)
{
    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_1, TIM_CCx_Disable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_1, TIM_CCxN_Disable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_2, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_2, TIM_CCxN_Enable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_3, TIM_CCx_Enable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_3, TIM_CCxN_Enable);

    pwm_output->pwm_channel = 6;
    TIM_SetCompare3(pwm_output->tim_ch, pwm_output->pwm_duty_value);
    TIM_SetCompare2(pwm_output->tim_ch, 0);
}

void pwm_an_bn_cn_output(pwm_output_struct *pwm_output)
{
    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_1, TIM_CCx_Disable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_1, TIM_CCxN_Enable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_2, TIM_CCx_Disable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_2, TIM_CCxN_Enable);

    TIM_CCxCmd (pwm_output->tim_ch, TIM_Channel_3, TIM_CCx_Disable);
    TIM_CCxNCmd(pwm_output->tim_ch, TIM_Channel_3, TIM_CCxN_Enable);

    pwm_output->pwm_channel = 0;
    TIM_SetCompare1(pwm_output->tim_ch, BLDC_BRAKE_DUTY);
    TIM_SetCompare2(pwm_output->tim_ch, BLDC_BRAKE_DUTY);
    TIM_SetCompare3(pwm_output->tim_ch, BLDC_BRAKE_DUTY);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ɲ��
//  @param      *pwm_output    PWM��������ṹ��ָ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void pwm_complementary_brake(pwm_output_struct *pwm_output)
{
    pwm_an_bn_cn_output(pwm_output);
    pwm_output->pwm_duty_value = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM���������ʼ��
//  @param      motor_index    �������
//  @param      *pwm_output    PWM��������ṹ��ָ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void pwm_complementary_init(motor_index_enum motor_index, pwm_output_struct *pwm_output)
{
    if(motor_index == MOTOR_1)
    {
        pwm_output->tim_ch = TIM1;

        gpio_init(A8, GPO, 0, GPO_AF_PUSH_PULL);                        // ��ʼ��CH1����
        gpio_init(A9, GPO, 0, GPO_AF_PUSH_PULL);                        // ��ʼ��CH2����
        gpio_init(A10, GPO, 0, GPO_AF_PUSH_PULL);                       // ��ʼ��CH3����

        gpio_init(A7, GPO, 0, GPO_AF_PUSH_PULL);                        // ��ʼ��CH1N����
        gpio_init(B0, GPO, 0, GPO_AF_PUSH_PULL);                        // ��ʼ��CH2N����
        gpio_init(B1, GPO, 0, GPO_AF_PUSH_PULL);                        // ��ʼ��CH3N����

        gpio_init(A6, GPO, 0, GPI_PULL_DOWN);                           // ��ʼ��BKIN����

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);            // ʹ��AFIO���ù���ģ��ʱ��
        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);            // ��ӳ��
    }
    else if(motor_index == MOTOR_2)
    {
        pwm_output->tim_ch = TIM9;

        gpio_init(D9,  GPO, 0, GPO_AF_PUSH_PULL);                       // ��ʼ��CH1����
        gpio_init(D11, GPO, 0, GPO_AF_PUSH_PULL);                       // ��ʼ��CH2����
        gpio_init(D13, GPO, 0, GPO_AF_PUSH_PULL);                       // ��ʼ��CH3����

        gpio_init(D8,  GPO, 0, GPO_AF_PUSH_PULL);                       // ��ʼ��CH1N����
        gpio_init(D10, GPO, 0, GPO_AF_PUSH_PULL);                       // ��ʼ��CH2N����
        gpio_init(D12, GPO, 0, GPO_AF_PUSH_PULL);                       // ��ʼ��CH3N����

        gpio_init(D14, GPO, 0, GPI_PULL_DOWN);                          // ��ʼ��BKIN����

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);            // ʹ��AFIO���ù���ģ��ʱ��
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM9, ENABLE);               // ��ӳ��
    }


    TIM_OCInitTypeDef       TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    TIM_BDTRInitTypeDef     TIM_BDTRInitStructure = {0};

    if(pwm_output->tim_ch == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }
    else if(pwm_output->tim_ch == TIM8)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    }
    else if(pwm_output->tim_ch == TIM9)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    }
    else if(pwm_output->tim_ch == TIM10)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    }
    else
    {
        zf_assert(0);
    }

    TIM_DeInit(pwm_output->tim_ch);

    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
    TIM_TimeBaseInitStructure.TIM_Period = PWM_PERIOD;                          // ���ö�ʱ������ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;                                // ��ʱ��ʱ�Ӳ���Ƶ
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 // ����Ƶ
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; // ���Ķ���ģʽ  PWMƵ��=��ʱ������ʱ��Ƶ��/(2*����ֵ)
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;                        // ռ�ձȵĸ���Ƶ��=��ʱ������ʱ��Ƶ��/((TIM_RepetitionCounter+1)*����ֵ)
    TIM_TimeBaseInit(pwm_output->tim_ch, &TIM_TimeBaseInitStructure);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           // PWMģʽ1����ʱ������ֵС�ڱȽ�ֵ��ʱ�����������Ч��ƽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;               // CHxͨ��ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;             //
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                   // CHx  ��Ч��ƽΪ�ߵ�ƽ ��Ч��ƽΪ�͵�ƽ
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;                 // CHxN ��Ч��ƽΪ�ߵ�ƽ ��Ч��ƽΪ�͵�ƽ
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;                // CHx  ����״̬����͵�ƽ
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;              // CHxN ����״̬����͵�ƽ

    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC1Init(pwm_output->tim_ch, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC2Init(pwm_output->tim_ch, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC3Init(pwm_output->tim_ch, &TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_Pulse = 1;
    TIM_OC4Init(pwm_output->tim_ch, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(pwm_output->tim_ch,TIM_OCPreload_Disable);
    TIM_OC2PreloadConfig(pwm_output->tim_ch,TIM_OCPreload_Disable);
    TIM_OC3PreloadConfig(pwm_output->tim_ch,TIM_OCPreload_Disable);
    TIM_OC4PreloadConfig(pwm_output->tim_ch,TIM_OCPreload_Disable);

    TIM_BDTRStructInit(&TIM_BDTRInitStructure);
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_DeadTime = PWM_DEADTIME;                          // PWM����ʱ��

    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;                         // ɲ��ʹ��
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;           // ɲ������Ϊ�ߣ��ߵ�ƽ��ʱ��ɲ��
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;     // ��ɲ���ź���Ч��ʱ���Զ��������
    TIM_BDTRConfig(pwm_output->tim_ch, &TIM_BDTRInitStructure);

    TIM_ARRPreloadConfig(pwm_output->tim_ch, ENABLE);                           // ʹ���Զ���װ��Ԥװ��ʹ��

    TIM_ITConfig(pwm_output->tim_ch,TIM_IT_Break,DISABLE);                      // �ر�ɲ���ж�
    TIM_ITConfig(pwm_output->tim_ch,TIM_IT_Update, DISABLE);                    // �رո����ж�
    TIM_ITConfig(pwm_output->tim_ch, TIM_IT_Trigger, DISABLE);                  // ����ʱ�������ж�
    TIM_ITConfig(pwm_output->tim_ch, TIM_IT_COM, DISABLE);

    TIM_CtrlPWMOutputs(pwm_output->tim_ch, ENABLE);

    TIM_Cmd(pwm_output->tim_ch, ENABLE);
}


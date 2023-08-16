
#include "pwm_output.h"
#include "bldc_config.h"
#include "zf_common_headfile.h"

pwm_output_struct motor1_pwm_output;
pwm_output_struct motor2_pwm_output;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      使能或使能PWM互补输出
//  @param      *pwm_output     PWM互补输出结构体指针
//  @param      status          使能或失能
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
//  @brief      更新占空比
//  @param      *pwm_output     PWM互补输出结构体指针
//  @param      *hall           霍尔结构体指针
//  @param      duty            占空比
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void pwm_complementary_set_duty(pwm_output_struct *pwm_output, hall_struct *hall, uint16 duty)
{
//    // 失能HALL中断
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

//    // 使能HALL中断
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
//  @brief      刹车
//  @param      *pwm_output    PWM互补输出结构体指针
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void pwm_complementary_brake(pwm_output_struct *pwm_output)
{
    pwm_an_bn_cn_output(pwm_output);
    pwm_output->pwm_duty_value = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM互补输出初始化
//  @param      motor_index    电机索引
//  @param      *pwm_output    PWM互补输出结构体指针
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void pwm_complementary_init(motor_index_enum motor_index, pwm_output_struct *pwm_output)
{
    if(motor_index == MOTOR_1)
    {
        pwm_output->tim_ch = TIM1;

        gpio_init(A8, GPO, 0, GPO_AF_PUSH_PULL);                        // 初始化CH1引脚
        gpio_init(A9, GPO, 0, GPO_AF_PUSH_PULL);                        // 初始化CH2引脚
        gpio_init(A10, GPO, 0, GPO_AF_PUSH_PULL);                       // 初始化CH3引脚

        gpio_init(A7, GPO, 0, GPO_AF_PUSH_PULL);                        // 初始化CH1N引脚
        gpio_init(B0, GPO, 0, GPO_AF_PUSH_PULL);                        // 初始化CH2N引脚
        gpio_init(B1, GPO, 0, GPO_AF_PUSH_PULL);                        // 初始化CH3N引脚

        gpio_init(A6, GPO, 0, GPI_PULL_DOWN);                           // 初始化BKIN引脚

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);            // 使能AFIO复用功能模块时钟
        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);            // 重映射
    }
    else if(motor_index == MOTOR_2)
    {
        pwm_output->tim_ch = TIM9;

        gpio_init(D9,  GPO, 0, GPO_AF_PUSH_PULL);                       // 初始化CH1引脚
        gpio_init(D11, GPO, 0, GPO_AF_PUSH_PULL);                       // 初始化CH2引脚
        gpio_init(D13, GPO, 0, GPO_AF_PUSH_PULL);                       // 初始化CH3引脚

        gpio_init(D8,  GPO, 0, GPO_AF_PUSH_PULL);                       // 初始化CH1N引脚
        gpio_init(D10, GPO, 0, GPO_AF_PUSH_PULL);                       // 初始化CH2N引脚
        gpio_init(D12, GPO, 0, GPO_AF_PUSH_PULL);                       // 初始化CH3N引脚

        gpio_init(D14, GPO, 0, GPI_PULL_DOWN);                          // 初始化BKIN引脚

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);            // 使能AFIO复用功能模块时钟
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM9, ENABLE);               // 重映射
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
    TIM_TimeBaseInitStructure.TIM_Period = PWM_PERIOD;                          // 设置定时器周期值
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;                                // 定时器时钟不分频
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 // 不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; // 中心对齐模式  PWM频率=定时器输入时钟频率/(2*周期值)
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;                        // 占空比的更新频率=定时器输入时钟频率/((TIM_RepetitionCounter+1)*周期值)
    TIM_TimeBaseInit(pwm_output->tim_ch, &TIM_TimeBaseInitStructure);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           // PWM模式1，定时器计数值小于比较值的时候，引脚输出有效电平
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;               // CHx通道使能
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;             //
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                   // CHx  有效电平为高电平 无效电平为低电平
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;                 // CHxN 有效电平为高电平 无效电平为低电平
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;                // CHx  空闲状态输出低电平
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;              // CHxN 空闲状态输出低电平

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
    TIM_BDTRInitStructure.TIM_DeadTime = PWM_DEADTIME;                          // PWM死区时间

    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;                         // 刹车使能
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;           // 刹车极性为高，高电平的时候刹车
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;     // 当刹车信号无效的时候自动开启输出
    TIM_BDTRConfig(pwm_output->tim_ch, &TIM_BDTRInitStructure);

    TIM_ARRPreloadConfig(pwm_output->tim_ch, ENABLE);                           // 使能自动重装载预装载使能

    TIM_ITConfig(pwm_output->tim_ch,TIM_IT_Break,DISABLE);                      // 关闭刹车中断
    TIM_ITConfig(pwm_output->tim_ch,TIM_IT_Update, DISABLE);                    // 关闭更新中断
    TIM_ITConfig(pwm_output->tim_ch, TIM_IT_Trigger, DISABLE);                  // 允许定时器更新中断
    TIM_ITConfig(pwm_output->tim_ch, TIM_IT_COM, DISABLE);

    TIM_CtrlPWMOutputs(pwm_output->tim_ch, ENABLE);

    TIM_Cmd(pwm_output->tim_ch, ENABLE);
}


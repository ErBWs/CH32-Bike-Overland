/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          zf_driver_pwm
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2022-09-15        大W            first version
********************************************************************************************************************/


#include "zf_driver_gpio.h"
#include "zf_driver_timer.h"
#include "zf_driver_pwm.h"


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PWM占空比设定
// 参数说明     pwmch           PWM通道号及引脚
// 参数说明     duty            PWM占空比
// 返回参数     void
// 使用示例     pwm_set_duty(TIM10_PWM_CH4_C15, 5000);   //定时器10 通道4 使用引脚C15 占空比为百分之 5000/PWM_DUTY_MAX*100
//                              PWM_DUTY_MAX在zf_pwm.h文件中 默认为10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_duty(pwm_channel_enum pin, uint32 duty)
{
    // 如果是这一行报错 那你得去看看最大占空比是限定的多少 占空比写入错误
    zf_assert(PWM_DUTY_MAX >= duty);                            // 占空比写入错误



    TIM_TypeDef *tim_index = TIM1;
    switch((pin & 0xF0000) >> 16)                               // 获取TIM编号
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

    period_temp = tim_index->ATRLR;                             // 获取定时器的周期值
    match_temp = period_temp * duty / PWM_DUTY_MAX;             // 占空比



    if(((pin>>8) & 0x03) == 0x00)                               // 通道选择
    {
        tim_index->CH1CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x01)                          // 通道选择
    {
        tim_index->CH2CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x02)                          // 通道选择
    {
        tim_index->CH3CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x03)                          // 通道选择
    {
        tim_index->CH4CVR = match_temp;
    }

}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PWM频率设定
// 参数说明     pwmch           PWM通道号及引脚
// 参数说明     freq            PWM频率
// 参数说明     duty            PWM占空比
// 返回参数     void
// 使用示例     pwm_set_freq(PWM1_CH1_A8, 60, 5000);   //使用引脚A8  输出PWM频率60HZ   占空比为百分之 5000/PWM_DUTY_MAX*100
//                              PWM_DUTY_MAX在zf_pwm.h文件中 默认为10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_freq(pwm_channel_enum pin, uint32 freq, uint32 duty)
{
    uint16 period_temp = 0;                                     // 周期值
    uint16 freq_div = 0;                                        // 分频值
    uint16 match_temp;

    freq_div = (uint16)((system_clock / freq) >> 16);           // 计算多少分频
    period_temp = (uint16)(system_clock/(freq*(freq_div + 1))); // 计算周期

    // 获取TIM编号
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
    match_temp = period_temp * duty / PWM_DUTY_MAX;             // 占空比


    if(((pin>>8) & 0x03) == 0x00)                               // 通道选择
    {
        tim_index->CH1CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x01)                          // 通道选择
    {
        tim_index->CH2CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x02)                          // 通道选择
    {
        tim_index->CH3CVR = match_temp;
    }
    else if(((pin>>8) & 0x03) == 0x03)                          // 通道选择
    {
        tim_index->CH4CVR = match_temp;
    }

}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PWM初始化
// 参数说明     pwmch           PWM通道号及引脚
// 参数说明     freq            PWM频率
// 参数说明     duty            PWM占空比
// 返回参数     void
// 使用示例     pwm_init(PWM1_CH1_A8, 50, 5000);   //初始化PWM1 通道1 使用引脚A8  输出PWM频率50HZ   占空比为百分之 5000/PWM_DUTY_MAX*100
//                              PWM_DUTY_MAX在zf_pwm.h文件中 默认为10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(pwm_channel_enum pin, uint32 freq, uint32 duty)
{

    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PIT 然后又初始化成 TIM1_PWM 这种用法是不允许的
    zf_assert(timer_funciton_check((timer_index_enum)(pin>>16), TIMER_FUNCTION_PWM));
    // 如果是这一行报错 那你得去看看最大占空比是限定的多少 占空比写入错误
    zf_assert(PWM_DUTY_MAX >= duty);

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
    TIM_OCInitTypeDef  TIM_OCInitStructure = {0};
    uint16 match_temp;                                                              // 占空比值
    uint16 period_temp;                                                             // 周期值
    uint16 freq_div = 0;                                                            // 分频值

    timer_clock_enable((pin & 0xF0000) >> 16);                                      // 定时器时钟使能

    gpio_init((gpio_pin_enum)(pin & 0xFF), GPO, 0, GPO_AF_PUSH_PULL | SPEED_50MHZ); // 初始化引脚

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                            // 使能AFIO复用功能模块时钟

    // 获取TIM编号
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

    // 开启复用功能
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

    freq_div = (uint16)((system_clock / freq) >> 16);                               // 多少分频
    period_temp = (uint16)(system_clock/(freq*(freq_div + 1)));                     // 周期
    match_temp = period_temp * duty / PWM_DUTY_MAX;                                 // 占空比

    TIM_TimeBaseStructure.TIM_Period = period_temp - 1;                             // 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = freq_div;                                 // 设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                         // 设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                     // TIM向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(tim_index, &TIM_TimeBaseStructure);                            // 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                               // 选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                   // 比较输出使能
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_Pulse = match_temp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                        // 输出极性:TIM输出比较极性低
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_Low;                       // 输出极性:TIM输出比较极性低
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

    if(((pin>>8) & 0x03) == 0x00)                                                   // 通道选择
    {
        TIM_OC1Init(tim_index, &TIM_OCInitStructure );                              // 定时器通道1初始化
        TIM_OC1PreloadConfig(tim_index, TIM_OCPreload_Enable);                      // 定时器预装载配置
        TIM_OC1FastConfig(tim_index, TIM_OC1FE);                                    // 比较捕获通道快速使能
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
    TIM_CtrlPWMOutputs(tim_index, ENABLE );                                         // 通道PWM输出使能
    TIM_Cmd(tim_index, ENABLE);                                                     // 定时器使能
    //TIM_ARRPreloadConfig( TIM1, ENABLE );
}


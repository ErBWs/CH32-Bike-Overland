/*********************************************************************************************************************
* MM32F527X-E9P Opensourec Library 即（MM32F527X-E9P 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 MM32F527X-E9P 开源库的一部分
* 
* MM32F527X-E9P 开源库 是免费软件
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
* 开发环境          MDK 5.37
* 适用平台          MM32F527X_E9P
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "zf_driver_timer.h"

#include "zf_driver_pwm.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PWM 更新占空比
// 参数说明     pin             选择 PWM 引脚
// 参数说明     duty            设置占空比
// 返回参数     void
// 使用示例     pwm_set_duty(TIM5_PWMCH1_A0, PWM_DUTY_MAX / 4);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_duty (pwm_channel_enum pin, const uint32 duty)
{
    // 如果是这一行报错 那你得去看看最大占空比是限定的多少 占空比写入错误
    zf_assert(PWM_DUTY_MAX >= duty);                                            // 占空比写入错误

    TIM_Type *tim_index;
    switch(pin & 0x0F)
    {
        case 0: tim_index = (TIM_Type *) TIM1;   break;
        case 1: tim_index = (TIM_Type *) TIM2;   break;
        case 2: tim_index = (TIM_Type *) TIM3;   break;
        case 3: tim_index = (TIM_Type *) TIM4;   break;
        case 4: tim_index = (TIM_Type *) TIM5;   break;
        case 7: tim_index = (TIM_Type *) TIM8;   break;
    }
    uint16 period_temp = tim_index->ARR;                                        // 获取自动重装载值
    uint16 match_temp = (uint16)(period_temp * ((float)duty / PWM_DUTY_MAX));   // 计算占空比
    if(match_temp == period_temp)
    {
        match_temp +=1;
    }
    switch(pin & 0xF0)
    {
        case 0x10:
        case 0x50:  TIM_PutChannelValue(tim_index, TIM_CHN_1, match_temp);    break;
        case 0x20:
        case 0x60:  TIM_PutChannelValue(tim_index, TIM_CHN_2, match_temp);    break;
        case 0x30:
        case 0x70:  TIM_PutChannelValue(tim_index, TIM_CHN_3, match_temp);    break;
        case 0x40:
        case 0x80:  TIM_PutChannelValue(tim_index, TIM_CHN_4, match_temp);    break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PWM 初始化
// 参数说明     pin             选择 PWM 引脚
// 参数说明     freq            设置频率 同个模块只有最后一次设置生效
// 参数说明     duty            设置占空比
// 返回参数     void
// 使用示例     pwm_init(TIM5_PWMCH1_A0, 17000, PWM_DUTY_MAX / 2);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pwm_init (pwm_channel_enum pin, const uint32 freq, const uint32 duty)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PIT 然后又初始化成 TIM1_PWM 这种用法是不允许的
    zf_assert(timer_funciton_check((timer_index_enum)(pin & 0x0F), TIMER_FUNCTION_PWM));
    // 如果是这一行报错 那你得去看看最大占空比是限定的多少 占空比写入错误
    zf_assert(PWM_DUTY_MAX >= duty);

    uint16 freq_div = ((bus_clock / freq) >> 15);                               // 计算预分频
    uint16 period_temp = (bus_clock / freq / (freq_div + 1));                   // 计算自动重装载值

    timer_clock_enable((timer_index_enum)(pin & 0x0F));
    afio_init((gpio_pin_enum)((pin & 0xFFF000) >> 12), GPO, (gpio_af_enum)((pin & 0xF00) >> 8), GPO_AF_PUSH_PULL);  // 初始化引脚

    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = bus_clock;
    tim_init.StepFreqHz = bus_clock / (((bus_clock / freq) >> 15) + 1);
    tim_init.Period = period_temp;
    tim_init.EnablePreloadPeriod = false;
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing;

    TIM_OutputCompareConf_Type tim_outcomp_conf;
    tim_outcomp_conf.ChannelValue = 0u;
    tim_outcomp_conf.EnableFastOutput = false;
    tim_outcomp_conf.EnablePreLoadChannelValue = false;
    tim_outcomp_conf.RefOutMode = TIM_OutputCompareRefOut_FallingEdgeOnMatch;
    tim_outcomp_conf.ClearRefOutOnExtTrigger = false;
    tim_outcomp_conf.PinPolarity = TIM_PinPolarity_Rising;

    TIM_Type *tim_index;
    switch(pin & 0x0F)
    {
        case 0: tim_index = (TIM_Type *) TIM1;   break;
        case 1: tim_index = (TIM_Type *) TIM2;   break;
        case 2: tim_index = (TIM_Type *) TIM3;   break;
        case 3: tim_index = (TIM_Type *) TIM4;   break;
        case 4: tim_index = (TIM_Type *) TIM5;   break;
        case 7: tim_index = (TIM_Type *) TIM8;   break;
    }
    switch(pin & 0xF0)
    {
        case 0x10:
        {
            TIM_Init(tim_index, &tim_init);
            TIM_EnableOutputCompare(tim_index, TIM_CHN_1, &tim_outcomp_conf);
            TIM_EnableOutputCompareSwitch(tim_index, true);
        }break;
        case 0x20:
        {
            TIM_Init(tim_index, &tim_init);
            TIM_EnableOutputCompare(tim_index, TIM_CHN_2, &tim_outcomp_conf);
            TIM_EnableOutputCompareSwitch(tim_index, true);
        }break;
        case 0x30:
        {
            TIM_Init(tim_index, &tim_init);
            TIM_EnableOutputCompare(tim_index, TIM_CHN_3, &tim_outcomp_conf);
            TIM_EnableOutputCompareSwitch(tim_index, true);
        }break;
        case 0x40:
        {
            TIM_Init(tim_index, &tim_init);
            TIM_EnableOutputCompare(tim_index, TIM_CHN_4, &tim_outcomp_conf);
            TIM_EnableOutputCompareSwitch(tim_index, true);
        }break;
        case 0x50:
        {
            TIM_Init(tim_index, &tim_init);
            TIM_EnableOutputCompare(tim_index, TIM_CHN_1, &tim_outcomp_conf);
            TIM_EnableCompOutput(tim_index, TIM_CHN_1, true);
            TIM_EnableOutputCompareSwitch(tim_index, true);
        }break;
        case 0x60:
        {
            TIM_Init(tim_index, &tim_init);
            TIM_EnableOutputCompare(tim_index, TIM_CHN_2, &tim_outcomp_conf);
            TIM_EnableCompOutput(tim_index, TIM_CHN_2, true);
            TIM_EnableOutputCompareSwitch(tim_index, true);
        }break;
        case 0x70:
        {
            TIM_Init(tim_index, &tim_init);
            TIM_EnableOutputCompare(tim_index, TIM_CHN_3, &tim_outcomp_conf);
            TIM_EnableCompOutput(tim_index, TIM_CHN_3, true);
            TIM_EnableOutputCompareSwitch(tim_index, true);
        }break;
        case 0x80:
        {
            TIM_Init(tim_index, &tim_init);
            TIM_EnableOutputCompare(tim_index, TIM_CHN_4, &tim_outcomp_conf);
            TIM_EnableCompOutput(tim_index, TIM_CHN_4, true);
            TIM_EnableOutputCompareSwitch(tim_index, true);
        }break;
    }
    pwm_set_duty(pin, duty);
    TIM_Start(tim_index);
}

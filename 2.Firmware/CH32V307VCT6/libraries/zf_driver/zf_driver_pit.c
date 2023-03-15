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
* 文件名称          zf_driver_pit
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


#include "ch32v30x_rcc.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_timer.h"

#include "zf_driver_pit.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      PIT 中断使能
// 参数说明     pit_n           PIT 外设模块号
// 返回参数     void
// 使用示例     pit_enable(TIM1_PIT);
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
    interrupt_enable(irq_index[pit_n]);                                // 使能中断
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      PIT 中断禁止
// 参数说明     pit_n           PIT 外设模块号
// 返回参数     void
// 使用示例     pit_disable(TIM1_PIT);
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

    interrupt_disable(irq_index[pit_n]);                                // 失能中断

}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     定时器周期中断
// 参数说明     timer_ch      定时器通道
// 参数说明     us          定时周期(1-65535)
// 返回参数     void
// 备注信息           pit_init(TIMER_1, 5); 使用定时器1作为5ms一次的周期中断
//-------------------------------------------------------------------------------------------------------------------
void pit_init (pit_index_enum pit_n, uint32 period)
{

    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PWM 然后又初始化成 TIM1_PIT 这种用法是不允许的
    zf_assert(timer_funciton_check((timer_index_enum)pit_n, TIMER_FUNCTION_TIMER));
    // 如果是这一行报错 那我就得问问你为什么周期写的是 0
    zf_assert(period!=0);

    uint16 freq_div = (period >> 15);                                           // 计算预分频
    uint16 period_temp = (period / (freq_div+1));                               // 计算自动重装载值

    timer_clock_enable(pit_n);                                                  // 使能时钟


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
    TIM_TimeBaseStructure.TIM_Prescaler = freq_div;                             // 分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     // 设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 // TIM向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                            // 重复计数器设置为0
    TIM_TimeBaseInit(tim_index, &TIM_TimeBaseStructure);                        // 根据指定的参数初始化TIMx的时间基数单位
    TIM_ITConfig(tim_index,TIM_IT_Update,ENABLE );                              // 使能指定的TIM中断,允许更新中断
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

    interrupt_set_priority((IRQn_Type)irq_index[(uint8)pit_n], 0x03);           // 设置中断优先级
    interrupt_enable((IRQn_Type)irq_index[pit_n]);                              // 使能中断

    TIM_Cmd(tim_index, ENABLE);                                                 // 使能定时器
}

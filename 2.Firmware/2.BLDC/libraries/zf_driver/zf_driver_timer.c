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
* 文件名称          zf_driver_timer
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


// 该数组禁止修改，内部使用,用户无需关心
static timer_function_enum timer_function_state[10] =
{
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT
};

// 该数组禁止修改，内部使用,用户无需关心
static timer_mode_enum timer_mode_state[10] =
{
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK
};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      TIMER 外设确认功能状态 库内部调用
// 参数说明     index           TIMER 外设模块号
// 参数说明     mode            需要确的功能模块
// 返回参数     uint8           1-可以使用 0-不可以使用
// 使用示例     zf_assert(timer_funciton_check(TIM_1, TIMER_FUNCTION_PWM);
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
// 函数简介     定时器时钟总线初始化
// 参数说明     timer_ch      定时器通道
// 返回参数     void
// 备注信息          内部使用，用户无需关心
//-------------------------------------------------------------------------------------------------------------------
void timer_clock_enable(timer_index_enum index)
{
    if(TIM_1 == index)        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//使能定时器1的时钟
    else  if(TIM_2 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器2的时钟
    else  if(TIM_3 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能定时器3的时钟
    else  if(TIM_4 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4的时钟
    else  if(TIM_5 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//使能定时器5的时钟
    else  if(TIM_6 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);//使能定时器6的时钟
    else  if(TIM_7 == index)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);//使能定时器7的时钟
    else  if(TIM_8 == index)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//使能定时器8的时钟
    else  if(TIM_9 == index)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);//使能定时器9的时钟
    else  if(TIM_10== index)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);//使能定时器10的时钟
}



//-------------------------------------------------------------------------------------------------------------------
// 函数简介     计时器开始
// 参数说明     timer_ch      选择模块的通道 (选择范围 由TIMERN_enum枚举值的内容确定)
// 返回参数     void
// 使用示例     timer_start(TIM_1, TIMER_US);  //定时器1 开始计数，每一us计数一次
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
    TIM_Cmd(tim_index, ENABLE);                                          // 使能TIMx
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     关闭计时器
// 参数说明     timer_ch      选择模块的通道 (选择范围 由TIMERN_enum枚举值的内容确定)
// 返回参数     void
// 备注信息             关闭定时器并清除标志位
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

    TIM_Cmd(tim_index, DISABLE);  //失能TIM
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取计时器值
// 参数说明     timer_ch      选择模块的通道 (选择范围 由TIMERN_enum枚举值的内容确定)
// 返回参数     uint32      计数值
// 使用示例     timer_get(TIM_1)  //获取定时器1的计时时间
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
// 函数简介     TIMER 清除计时器计数
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_clear(TIM_1);
// 备注信息
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
// 函数简介     TIMER 计时器初始化
// 参数说明     index           TIMER 外设模块号
// 参数说明     mode            计时方式
// 返回参数     void
// 使用示例     timer_init(TIM_1, TIMER_US);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void timer_init(timer_index_enum index, timer_mode_enum mode)
{

    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PWM 然后又初始化成 TIM_1 这种用法是不允许的
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



    timer_clock_enable(index);                                                  // 开启时钟总线

    timer_mode_state[index] = mode;

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
    if(mode == TIMER_US)
    {
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                              // 装载自动重装载值
        TIM_TimeBaseStructure.TIM_Prescaler = (system_clock/1000000)-1;         // 装载预分频
    }
    else if(mode == TIMER_MS)
    {
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                              // 装载自动重装载值
        TIM_TimeBaseStructure.TIM_Prescaler = (system_clock/1000)/3-1;          // 装载预分频
    }
    else
    {
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                              // 装载自动重装载值
        TIM_TimeBaseStructure.TIM_Prescaler = 0;                                // 装载预分频
    }
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     // 设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 // TIM向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                            // 重复计数器设置为0
    TIM_TimeBaseInit(tim_index, &TIM_TimeBaseStructure);                        // 根据指定的参数初始化TIMx的时间基数单位

    TIM_Cmd(tim_index, ENABLE);                                                 // 使能TIMx
}


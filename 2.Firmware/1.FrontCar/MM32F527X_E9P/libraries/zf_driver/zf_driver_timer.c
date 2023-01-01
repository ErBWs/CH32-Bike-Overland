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
* 文件名称          zf_driver_timer
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

#include "hal_rcc.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

#include "zf_driver_timer.h"

timer_function_enum timer_function_state[8] = 
{
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT,
    TIMER_FUNCTION_INIT, TIMER_FUNCTION_INIT
};

static timer_mode_enum timer_mode_state[8] = 
{
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK,
    TIMER_SYSTEM_CLOCK, TIMER_SYSTEM_CLOCK
};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 外设确认功能状态 库内部调用
// 参数说明     index           TIMER 外设模块号
// 参数说明     mode            需要确的功能模块
// 返回参数     uint8           1-可以使用 0-不可以使用
// 使用示例     zf_assert(timer_funciton_check(TIM_1, TIMER_FUNCTION_PWM);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 timer_funciton_check (timer_index_enum index,timer_function_enum mode)
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
// 函数简介     TIMER 时钟使能 库内部调用
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_clock_enable(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_clock_enable (timer_index_enum index)
{
    switch(index)
    {
        case TIM_1: RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_TIM1, ZF_ENABLE);    break;
        case TIM_2: RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_TIM2, ZF_ENABLE);    break;
        case TIM_3: RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_TIM3, ZF_ENABLE);    break;
        case TIM_4: RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_TIM4, ZF_ENABLE);    break;
        case TIM_5: RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_TIM5, ZF_ENABLE);    break;
        case TIM_6: RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_TIM6, ZF_ENABLE);    break;
        case TIM_7: RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_TIM7, ZF_ENABLE);    break;
        case TIM_8: RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_TIM8, ZF_ENABLE);    break;
        default:    break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 开始计时
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_start(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_start (timer_index_enum index)
{
    switch(index)
    {
        case TIM_1: TIM_Start((TIM_Type *) TIM1);   break;
        case TIM_2: TIM_Start((TIM_Type *) TIM2);   break;
        case TIM_3: TIM_Start((TIM_Type *) TIM3);   break;
        case TIM_4: TIM_Start((TIM_Type *) TIM4);   break;
        case TIM_5: TIM_Start((TIM_Type *) TIM5);   break;
        case TIM_6: TIM_Start((TIM_Type *) TIM6);   break;
        case TIM_7: TIM_Start((TIM_Type *) TIM7);   break;
        case TIM_8: TIM_Start((TIM_Type *) TIM8);   break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 停止计时
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_stop(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_stop (timer_index_enum index)
{
    switch(index)
    {
        case TIM_1: TIM_Stop((TIM_Type *) TIM1);   break;
        case TIM_2: TIM_Stop((TIM_Type *) TIM2);   break;
        case TIM_3: TIM_Stop((TIM_Type *) TIM3);   break;
        case TIM_4: TIM_Stop((TIM_Type *) TIM4);   break;
        case TIM_5: TIM_Stop((TIM_Type *) TIM5);   break;
        case TIM_6: TIM_Stop((TIM_Type *) TIM6);   break;
        case TIM_7: TIM_Stop((TIM_Type *) TIM7);   break;
        case TIM_8: TIM_Stop((TIM_Type *) TIM8);   break;
    }
    timer_function_state[index] = TIMER_FUNCTION_INIT;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 获取计时器计数
// 参数说明     index           TIMER 外设模块号
// 返回参数     uint16          计数值
// 使用示例     timer_get(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 timer_get (timer_index_enum index)
{
    uint16 return_value = 0;
    switch(index)
    {
        case TIM_1: return_value = TIM_GetCounterValue((TIM_Type *) TIM1);   break;
        case TIM_2: return_value = TIM_GetCounterValue((TIM_Type *) TIM2);   break;
        case TIM_3: return_value = TIM_GetCounterValue((TIM_Type *) TIM3);   break;
        case TIM_4: return_value = TIM_GetCounterValue((TIM_Type *) TIM4);   break;
        case TIM_5: return_value = TIM_GetCounterValue((TIM_Type *) TIM5);   break;
        case TIM_6: return_value = TIM_GetCounterValue((TIM_Type *) TIM6);   break;
        case TIM_7: return_value = TIM_GetCounterValue((TIM_Type *) TIM7);   break;
        case TIM_8: return_value = TIM_GetCounterValue((TIM_Type *) TIM8);   break;
    }
    if(TIMER_MS == timer_mode_state[index])
    {
        return_value = return_value / 2;
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
    switch(index)
    {
        case TIM_1: TIM_DoSwTrigger((TIM_Type *) TIM1, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM_2: TIM_DoSwTrigger((TIM_Type *) TIM2, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM_3: TIM_DoSwTrigger((TIM_Type *) TIM3, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM_4: TIM_DoSwTrigger((TIM_Type *) TIM4, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM_5: TIM_DoSwTrigger((TIM_Type *) TIM5, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM_6: TIM_DoSwTrigger((TIM_Type *) TIM6, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM_7: TIM_DoSwTrigger((TIM_Type *) TIM7, TIM_SWTRG_UPDATE_PERIOD);  break;
        case TIM_8: TIM_DoSwTrigger((TIM_Type *) TIM8, TIM_SWTRG_UPDATE_PERIOD);  break;
        default:    break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 计时器初始化
// 参数说明     index           TIMER 外设模块号
// 参数说明     mode            计时方式
// 返回参数     void
// 使用示例     timer_init(TIM_1, TIMER_US);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_init (timer_index_enum index, timer_mode_enum mode)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PWM 然后又初始化成 TIM_1 这种用法是不允许的
    zf_assert(timer_funciton_check(index, TIMER_FUNCTION_TIMER));

    timer_clock_enable(index);                                                  // 使能时钟
    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = bus_clock;
    switch(mode)
    {
        case TIMER_US:
            tim_init.StepFreqHz = 1000000;
            break;
        case TIMER_MS:
            tim_init.StepFreqHz = 2000;
            break;
        default:
            tim_init.StepFreqHz = bus_clock;
            break;
    }
    tim_init.Period = 0x0000FFFF;
    tim_init.EnablePreloadPeriod = false;
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing;
    timer_mode_state[index] = mode;
    switch(index)
    {
        case TIM_1: TIM_Init((TIM_Type *) TIM1, &tim_init); break;
        case TIM_2: TIM_Init((TIM_Type *) TIM2, &tim_init); break;
        case TIM_3: TIM_Init((TIM_Type *) TIM3, &tim_init); break;
        case TIM_4: TIM_Init((TIM_Type *) TIM4, &tim_init); break;
        case TIM_5: TIM_Init((TIM_Type *) TIM5, &tim_init); break;
        case TIM_6: TIM_Init((TIM_Type *) TIM6, &tim_init); break;
        case TIM_7: TIM_Init((TIM_Type *) TIM7, &tim_init); break;
        case TIM_8: TIM_Init((TIM_Type *) TIM8, &tim_init); break;
        default:    break;
    }
    timer_stop(index);
    timer_clear(index);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER ETR 外部时钟输入功能初始化 32类单片机用于驱动摄像头 库内部调用
// 参数说明     pin             ETR 引脚
// 参数说明     sign            信号类型 上升沿或者下降沿
// 返回参数     void
// 使用示例     timer_etr_init(OV7725_PCLK_PIN, TIM_ETR_FALLING);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_etr_init (timer_etr_pin_emun pin, timer_etr_mode_emun sign)
{
    timer_index_enum index = (timer_index_enum)(pin & 0x0F);

    zf_assert(timer_funciton_check(index, TIMER_FUNCTION_CAMERA));
    timer_clock_enable(index);

    afio_init((gpio_pin_enum)((pin & 0xFFF000) >> 12), GPI, (gpio_af_enum)((pin & 0xF00) >> 8), GPI_FLOATING_IN);  // 提取对应IO索引 AF功能编码

    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = bus_clock;
    tim_init.StepFreqHz = bus_clock;
    tim_init.Period = 0x0000FFFF;
    tim_init.EnablePreloadPeriod = false;
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing;

    TIM_SlaveModeConf_Type tim_slave;
    if(0x50 == (pin & 0xF0))
        tim_slave.In = TIM_SlaveIn_Alt7;
    else
        tim_slave.In = TIM_SlaveIn_Alt5;
    tim_slave.Resp = TIM_SlaveResp_Alt4;

    TIM_ExtTriggerInConf_Type tim_trigger;
    tim_trigger.InDiv = TIM_ExtTriggerInDiv_OnEach1Capture;
    tim_trigger.InFilter = TIM_ExtTriggerInFilter_Alt0;
    if(TIM_ETR_FALLING == sign)
        tim_trigger.PinPolarity = TIM_ExtTriggerPinPolarity_Falling;
    else
        tim_trigger.PinPolarity = TIM_ExtTriggerPinPolarity_Rising;

    switch(index)
    {
        case TIM_1:
            TIM_Init((TIM_Type *) TIM1, &tim_init);
            timer_stop(index);
            timer_clear(index);
            TIM_EnableSlaveMode((TIM_Type *) TIM1, &tim_slave);
            TIM_EnableExtTriggerIn((TIM_Type *) TIM1, &tim_trigger);
            TIM_EnableDMA((TIM_Type *) TIM1, TIM_DMA_TRGOUT_EVENT, ZF_ENABLE);
            break;
        case TIM_2:
            break;
        case TIM_3:
            TIM_Init((TIM_Type *) TIM3, &tim_init);
            timer_stop(index);
            timer_clear(index);
            TIM_EnableSlaveMode((TIM_Type *) TIM3, &tim_slave);
            TIM_EnableExtTriggerIn((TIM_Type *) TIM3, &tim_trigger);
            TIM_EnableDMA((TIM_Type *) TIM3, TIM_DMA_TRGOUT_EVENT, ZF_ENABLE);
            break;
        case TIM_4:
            break;
        case TIM_5:
            TIM_Init((TIM_Type *) TIM5, &tim_init);
            timer_stop(index);
            timer_clear(index);
            TIM_EnableSlaveMode((TIM_Type *) TIM5, &tim_slave);
            TIM_EnableExtTriggerIn((TIM_Type *) TIM5, &tim_trigger);
            TIM_EnableDMA((TIM_Type *) TIM5, TIM_DMA_TRGOUT_EVENT, ZF_ENABLE);
            break;
        case TIM_6:
            break;
        case TIM_7:
            break;
        case TIM_8:
            TIM_Init((TIM_Type *) TIM8, &tim_init);
            timer_stop(index);
            timer_clear(index);
            TIM_EnableSlaveMode((TIM_Type *) TIM8, &tim_slave);
            TIM_EnableExtTriggerIn((TIM_Type *) TIM8, &tim_trigger);
            TIM_EnableDMA((TIM_Type *) TIM8, TIM_DMA_TRGOUT_EVENT, ZF_ENABLE);
            break;
        default:
            break;
    }
    timer_start(index);
}


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
* 文件名称          zf_driver_encoder
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
#include "zf_driver_encoder.h"


static volatile uint8 encoder_dir_pin[10] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     定时器编码器解码取值
// 参数说明     timer_ch      定时器枚举体
// 返回参数     void
// 备注信息
// 使用示例    encoder_get_count(TIM2_ENCOEDER)  // 获取定时器2的采集到的编码器数据
//-------------------------------------------------------------------------------------------------------------------
int16 encoder_get_count(encoder_index_enum encoder_n)
{
    int16 result = 0;
    int16 return_value = 0;
    switch(encoder_n)
    {
        case TIM1_ENCOEDER:  result = TIM1->CNT;   break;
        case TIM2_ENCOEDER:  result = TIM2->CNT;   break;
        case TIM3_ENCOEDER:  result = TIM3->CNT;   break;
        case TIM4_ENCOEDER:  result = TIM4->CNT;   break;
        case TIM5_ENCOEDER:  result = TIM5->CNT;   break;
        case TIM8_ENCOEDER:  result = TIM8->CNT;   break;
        case TIM9_ENCOEDER:  result = TIM9->CNT;   break;
        case TIM10_ENCOEDER: result = TIM10->CNT;  break;
        default:             result = 0;                 break;
    }
    if(0xFF == encoder_dir_pin[encoder_n])
    {
        return_value = result;
    }
    else
    {
        if(!gpio_get_level((gpio_pin_enum)encoder_dir_pin[encoder_n]))
        {
            return_value = -result;
        }
		else
		{
			return_value = result;
		}
    }

    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     定时器的计数器清空
// 参数说明     timer_ch      定时器枚举体
// 返回参数     void
// 备注信息
// 使用示例    encoder_clear_count(TIM1_ENCOEDER)  //清除定时器1采集到的编码器数据
//-------------------------------------------------------------------------------------------------------------------
void encoder_clear_count(encoder_index_enum encoder_n)
{
    switch(encoder_n)
    {
        case TIM1_ENCOEDER:  TIM1->CNT  = 0;  break;
        case TIM2_ENCOEDER:  TIM2->CNT  = 0;  break;
        case TIM3_ENCOEDER:  TIM3->CNT  = 0;  break;
        case TIM4_ENCOEDER:  TIM4->CNT  = 0;  break;
        case TIM5_ENCOEDER:  TIM5->CNT  = 0;  break;
        case TIM8_ENCOEDER:  TIM8->CNT  = 0;  break;
        case TIM9_ENCOEDER:  TIM9->CNT  = 0;  break;
        case TIM10_ENCOEDER: TIM10->CNT = 0;  break;
        default:  break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     编码器解码初始化
// 参数说明     timer_ch      定时器枚举体
// 参数说明     phaseA      通道A以及引脚
// 参数说明     phaseB      通道B以及引脚
// 返回参数     void
// 备注信息    推荐使用正交解码编码器。
// 使用示例    encoder_init_quad(TIM1_ENCOEDER, TIM1_CH1_ENCOEDER_E9, TIM1_CH2_ENCOEDER_E11)
//          // 使用定时器1 做正交编码器解码， 通道1引脚号E9，通道2引脚号E11
//-------------------------------------------------------------------------------------------------------------------
void encoder_quad_init(encoder_index_enum encoder_n, encoder_channel_enum ch1_pin, encoder_channel_enum ch2_pin)
{
    uint32 register_temp = 0;
    TIM_TypeDef *tim_index;

    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PWM 然后又初始化成 TIM1_ENCODER 这种用法是不允许的
    zf_assert(timer_funciton_check((timer_index_enum)encoder_n, TIMER_FUNCTION_ENCODER));
    zf_assert((ch1_pin >> 12) == (encoder_n));                                  // ch1_pin 与 ch2_pin 必须与 encoder_n 匹配
    zf_assert((ch2_pin >> 12) == (encoder_n));                                  // ch1_pin 与 ch2_pin 必须与 encoder_n 匹配

    timer_clock_enable(encoder_n);                                              // 定时器时钟使能

    gpio_init((gpio_pin_enum)(ch1_pin & 0xFF), GPI, 0, GPI_PULL_UP);            // 初始化引脚
    gpio_init((gpio_pin_enum)(ch2_pin & 0xFF), GPI, 0, GPI_PULL_UP);            // 初始化引脚

    //encoder_dir_pin[encoder_n] = (ch1_pin &0xFF);                               // 将方向引脚号存入数组中

    switch(encoder_n)
    {
        case TIM1_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM1_BASE);   break;
        case TIM2_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM2_BASE);   break;
        case TIM3_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM3_BASE);   break;
        case TIM4_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM4_BASE);   break;
        case TIM5_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM5_BASE);   break;
        case TIM8_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM8_BASE);   break;
        case TIM9_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM9_BASE);   break;
        case TIM10_ENCOEDER: tim_index = ((TIM_TypeDef *)TIM10_BASE);  break;
        default: register_temp = 1;
    }

    // 开启复用功能
    if((ch1_pin >> 8) == 0x03)      GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,        ENABLE);
    else if((ch1_pin >> 8) == 0x11) GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,    ENABLE);
    else if((ch1_pin >> 8) == 0x22) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,     ENABLE);
    else if((ch1_pin >> 8) == 0x23) GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,        ENABLE);
    else if((ch1_pin >> 8) == 0x31) GPIO_PinRemapConfig(GPIO_Remap_TIM4,            ENABLE);
    else if((ch1_pin >> 8) == 0x71) GPIO_PinRemapConfig(GPIO_Remap_TIM8,            ENABLE);
    else if((ch1_pin >> 8) == 0x83) GPIO_PinRemapConfig(GPIO_FullRemap_TIM9,        ENABLE);
    else if((ch1_pin >> 8) == 0x91) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM10,    ENABLE);
    else if((ch1_pin >> 8) == 0x93) GPIO_PinRemapConfig(GPIO_FullRemap_TIM10,       ENABLE);

    if(!register_temp)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                // 使能AFIO复用功能模块时钟
        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
        TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
        TIM_TimeBaseStructure.TIM_Prescaler = 0;                            // 预分频器
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                          // 设定计数器自动重装值
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             // 选择时钟分频：不分频
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         // TIM向上计数
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                    // 重复计数器
        TIM_TimeBaseInit(tim_index, &TIM_TimeBaseStructure);                // 初始化结构体
        TIM_ITRxExternalClockConfig(tim_index, TIM_TS_TI2FP2);              // 配置外部触发，否则不会计数
        TIM_Cmd(tim_index, ENABLE);                                         // 定时器使能

        TIM_EncoderInterfaceConfig(
                tim_index,
                TIM_EncoderMode_TI2 ,
                TIM_ICPolarity_Rising,
                TIM_ICPolarity_Rising);                                     // 使用编码器模式, T2计数 ,T1判断方向, 上升沿计数

        TIM_Cmd(tim_index, ENABLE);                                         // 定时器使能

    }

}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     编码器解码初始化
// 参数说明     timer_ch        定时器枚举体
// 参数说明     phaseA          通道A以及引脚
// 参数说明     phaseB          通道B以及引脚
// 返回参数     void
//          推荐使用正交解码编码器。
// 使用示例      encoder_init_dir(TIM1_ENCOEDER, TIM1_CH1_ENCOEDER_E9, TIM1_CH2_ENCOEDER_E11)
//                              // 使用定时器1 做带方向的编码器解码， 通道1方向信号引脚E9，通道2脉冲信号引脚E11
//-------------------------------------------------------------------------------------------------------------------
void encoder_dir_init(encoder_index_enum encoder_n, encoder_channel_enum ch1_pin, encoder_channel_enum ch2_pin)
{
    uint32 register_temp = 0;
    TIM_TypeDef *tim_index;

    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 就去查看你在什么地方调用这个函数 检查你的传入参数
    // 这里是检查是否有重复使用定时器
    // 比如初始化了 TIM1_PWM 然后又初始化成 TIM1_ENCODER 这种用法是不允许的
    zf_assert(timer_funciton_check((timer_index_enum)encoder_n, TIMER_FUNCTION_ENCODER));
    zf_assert((ch1_pin & (encoder_n << 12)) == (encoder_n << 12));              // ch1_pin 与 ch2_pin 必须与 encoder_n 匹配
    zf_assert((ch2_pin & (encoder_n << 12)) == (encoder_n << 12));              // ch1_pin 与 ch2_pin 必须与 encoder_n 匹配

    timer_clock_enable(encoder_n);                                              // 定时器时钟使能

    gpio_init((gpio_pin_enum)(ch1_pin & 0xFF), GPI, 0, GPI_PULL_UP);            // 初始化引脚
    gpio_init((gpio_pin_enum)(ch2_pin & 0xFF), GPI, 0, GPI_PULL_UP);            // 初始化引脚

    encoder_dir_pin[encoder_n] = (ch1_pin &0xFF);                               // 将方向引脚号存入数组中

    switch(encoder_n)
    {
        case TIM1_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM1_BASE);   break;
        case TIM2_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM2_BASE);   break;
        case TIM3_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM3_BASE);   break;
        case TIM4_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM4_BASE);   break;
        case TIM5_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM5_BASE);   break;
        case TIM8_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM8_BASE);   break;
        case TIM9_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM9_BASE);   break;
        case TIM10_ENCOEDER: tim_index = ((TIM_TypeDef *)TIM10_BASE);  break;
        default: register_temp = 1;
    }

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                // 使能AFIO复用功能模块时钟

    // 开启复用功能
    if((ch1_pin >> 8) == 0x03)      GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,        ENABLE);
    else if((ch1_pin >> 8) == 0x11) GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,    ENABLE);
    else if((ch1_pin >> 8) == 0x22) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,     ENABLE);
    else if((ch1_pin >> 8) == 0x23) GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,        ENABLE);
    else if((ch1_pin >> 8) == 0x31) GPIO_PinRemapConfig(GPIO_Remap_TIM4,            ENABLE);
    else if((ch1_pin >> 8) == 0x71) GPIO_PinRemapConfig(GPIO_Remap_TIM8,            ENABLE);
    else if((ch1_pin >> 8) == 0x83) GPIO_PinRemapConfig(GPIO_FullRemap_TIM9,        ENABLE);
    else if((ch1_pin >> 8) == 0x91) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM10,    ENABLE);
    else if((ch1_pin >> 8) == 0x93) GPIO_PinRemapConfig(GPIO_FullRemap_TIM10,       ENABLE);

    if(!register_temp)
    {

        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
        TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
        TIM_TimeBaseStructure.TIM_Prescaler = 0;                            // 预分频器
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                          // 设定计数器自动重装值
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             // 选择时钟分频：不分频
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         // TIM向上计数
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                    // 重复计数器
        TIM_TimeBaseInit(tim_index, &TIM_TimeBaseStructure);                // 初始化结构体
        TIM_ITRxExternalClockConfig(tim_index, TIM_TS_TI2FP2);              // 配置外部触发，否则不会计数
        TIM_Cmd(tim_index, ENABLE);                                         // 定时器使能
    }
}


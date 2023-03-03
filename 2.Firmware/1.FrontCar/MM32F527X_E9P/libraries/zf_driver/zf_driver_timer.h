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

#ifndef _zf_driver_timer_h_
#define _zf_driver_timer_h_

#include "hal_tim.h"

#include "zf_common_typedef.h"

typedef enum
{
    TIM_1,
    TIM_2,
    TIM_3,
    TIM_4,
    TIM_5,
    TIM_6,
    TIM_7,
    TIM_8,
}timer_index_enum;

typedef enum
{
    TIMER_SYSTEM_CLOCK,                                                         // 系统频率计时 最大 0xFFFF
    TIMER_US,                                                                   // 微秒计时 最大 0xFFFF
    TIMER_MS,                                                                   // 毫秒计时 最大 0xFFFF/2
}timer_mode_enum;

typedef enum
{
    TIMER_FUNCTION_INIT = 0,                                                    // 功能未初始化
    TIMER_FUNCTION_TIMER,                                                       // 用作 TIMER 计时
    TIMER_FUNCTION_PIT,                                                         // 用作 PIT
    TIMER_FUNCTION_PWM,                                                         // 用作 PWM
    TIMER_FUNCTION_ENCODER,                                                     // 用作 ENCODER
    TIMER_FUNCTION_CAMERA,                                                      // 用作 CAMERA
}timer_function_enum;

// 需要特别注意的是 只有 TIM1/8/5/3 四个定时器支持 TRGI 触发 DMA
// 也就是说 只能用这四个定时器的对应 ETR 通道来采集摄像头 PCLK 信号
typedef enum                                                                    // 枚举 TIM_ETR 通道    此枚举定义不允许用户修改
{
    // Advanced Timer 16 bits TIM1
    TIM1_ETR_A12            = 0x00C150,                                         // 0x 00C[A12] 1[AF1] 5[ETR] 0[TIM1]
    TIM1_ETR_E7             = 0x087150,                                         // 0x 087[E7]  1[AF1] 5[ETR] 0[TIM1]
    TIM1_ETR_H2             = 0x0E2150,                                         // 0x 0E2[H2]  1[AF1] 5[ETR] 0[TIM1]

    // Advanced Timer 16 bits TIM8
    TIM8_ETR_A0             = 0x000357,                                         // 0x 000[A0]  3[AF3] 5[ETR] 7[TIM8]
    TIM8_ETR_H2             = 0x0E2357,                                         // 0x 0E2[H2]  3[AF3] 5[ETR] 7[TIM8]
    TIM8_ETR_I1             = 0x101357,                                         // 0x 101[I1]  3[AF3] 5[ETR] 7[TIM8]

    // General Timer 32 bits TIM2
//    TIM2_ETR_A0             = 0x000151,                                         // 0x 000[A0]  1[AF1] 5[ETR] 1[TIM2]
//    TIM2_ETR_A5             = 0x005151,                                         // 0x 005[A5]  1[AF1] 5[ETR] 1[TIM2]
//    TIM2_ETR_A15            = 0x00F151,                                         // 0x 00F[A15] 1[AF1] 5[ETR] 1[TIM2]
//    TIM2_ETR_I1             = 0x101151,                                         // 0x 101[I1]  1[AF1] 5[ETR] 1[TIM2]

    // General Timer 32 bits TIM5
    TIM5_ETR_A4             = 0x004254,                                         // 0x 004[A4]  2[AF2] 5[ETR] 4[TIM5]
    TIM5_ETR_B12            = 0x02C254,                                         // 0x 02C[B12] 2[AF2] 5[ETR] 4[TIM5]
    TIM5_ETR_F6             = 0x0A6254,                                         // 0x 02C[B12] 2[AF2] 5[ETR] 4[TIM5]
    TIM5_ETR_I1             = 0x101254,                                         // 0x 101[I1]  2[AF2] 5[ETR] 4[TIM5]

    // General Timer 16 bits TIM3
    TIM3_ETR_A5             = 0x005252,                                         // 0x 005[A5]  2[AF2] 5[ETR] 2[TIM3]
    TIM3_ETR_A8             = 0x008252,                                         // 0x 008[A8]  2[AF2] 5[ETR] 2[TIM3]
    TIM3_ETR_D2             = 0x062252,                                         // 0x 062[D2]  2[AF2] 5[ETR] 2[TIM3]

    // General Timer 16 bits TIM4
//    TIM4_ETR_B3             = 0x023253,                                         // 0x 023[B3]  2[AF2] 5[ETR] 3[TIM4]
//    TIM4_ETR_D11            = 0x06B253,                                         // 0x 06B[D11  2[AF2] 5[ETR] 3[TIM4]
//    TIM4_ETR_E0             = 0x080253,                                         // 0x 080[E0]  2[AF2] 5[ETR] 3[TIM4]
}timer_etr_pin_emun;

typedef enum
{
    TIM_ETR_RISING,
    TIM_ETR_FALLING,
}timer_etr_mode_emun;

uint8       timer_funciton_check        (timer_index_enum index, timer_function_enum mode);
void        timer_clock_enable          (timer_index_enum index);

void        timer_start                 (timer_index_enum index);
void        timer_stop                  (timer_index_enum index);
uint16      timer_get                   (timer_index_enum index);
void        timer_clear                 (timer_index_enum index);

void        timer_init                  (timer_index_enum index, timer_mode_enum mode);
void        timer_etr_init              (timer_etr_pin_emun pin, timer_etr_mode_emun sign);

#endif

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

#ifndef _zf_driver_timer_h
#define _zf_driver_timer_h

#include "ch32v30x_rcc.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x_tim.h"

#include "zf_common_debug.h"
#include "zf_common_clock.h"

//此枚举定义不允许用户修改
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
    TIM_9,
    TIM_10,
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


uint8       timer_funciton_check    (timer_index_enum index, timer_function_enum mode);
void        timer_clock_enable      (timer_index_enum index);

void        timer_start             (timer_index_enum index);
void        timer_stop              (timer_index_enum index);
uint16      timer_get               (timer_index_enum index);
void        timer_clear             (timer_index_enum index);

void        timer_init              (timer_index_enum index, timer_mode_enum mode);





#endif

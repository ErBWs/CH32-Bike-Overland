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
* 文件名称          zf_common_clock
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

#ifndef _zf_common_clock_h_
#define _zf_common_clock_h_

#include "zf_common_typedef.h"

#define BOARD_XTAL_FREQ         ( 8000000 )                                    // 晶振频率 如果自己用的不是这个频率就修改这里 UM 定义范围为 4-24Mhz
#define XTAL_STARTUP_TIMEOUT    ( 0x0F00 )                                      // 晶振就绪等待超时时长

// 推荐最高使用到 120MHz
// 虽然内核超频过 120MHz
// 但总线最多只到 120MHz
// 当内核超频超过 120MHz 时总线必须为内核二分频
// 所以推荐最高使用到 120MHz 就好
typedef enum
{
    SYSTEM_CLOCK_XTAL       = BOARD_XTAL_FREQ,                                  // 使用晶振频率作为时钟频率
    SYSTEM_CLOCK_24M        = 24000000,                                         // 24Mhz
    SYSTEM_CLOCK_48M        = 48000000,                                         // 48Mhz
    SYSTEM_CLOCK_72M        = 72000000,                                         // 72Mhz
    SYSTEM_CLOCK_96M        = 96000000,                                         // 96Mhz
    SYSTEM_CLOCK_120M       = 120000000,                                        // 120Mhz
}system_clock_enum;

extern uint32 system_clock;                                                     // 全局变量 系统时钟信息 SYSTICK AHB
extern uint32 bus_clock;                                                        // 全局变量 总线时钟信息 APB1 APB2

void clock_init (uint32 clock);                                                 // 核心时钟初始化

#endif

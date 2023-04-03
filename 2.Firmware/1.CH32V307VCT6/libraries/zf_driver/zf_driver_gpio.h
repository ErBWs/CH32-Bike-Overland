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
* 文件名称          zf_driver_gpio
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

 
#ifndef _zf_driver_gpio_h
#define _zf_driver_gpio_h

#include "ch32v30x_rcc.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x_exti.h"
#include "zf_common_typedef.h"

typedef enum                                                                    // 枚举 GPIO 引脚  此枚举定义不允许用户修改
{
    A0 = 0x00,  A1 ,    A2 ,    A3 ,    A4 ,    A5 ,    A6 ,    A7 ,
    A8 ,        A9 ,    A10,    A11,    A12,    A13,    A14,    A15,

    B0 = 0x20,  B1 ,    B2 ,    B3 ,    B4 ,    B5 ,    B6 ,    B7 ,
    B8 ,        B9 ,    B10,    B11,    B12,    B13,    B14,    B15,

    C0 = 0x40,  C1 ,    C2 ,    C3 ,    C4 ,    C5 ,    C6 ,    C7 ,
    C8 ,        C9 ,    C10,    C11,    C12,    C13,    C14,    C15,

    D0 = 0x60,  D1 ,    D2 ,    D3 ,    D4 ,    D5 ,    D6 ,    D7 ,
    D8 ,        D9 ,    D10,    D11,    D12,    D13,    D14,    D15,

    E0 = 0x80,  E1 ,    E2 ,    E3 ,    E4 ,    E5 ,    E6 ,    E7 ,
    E8 ,        E9 ,    E10,    E11,    E12,    E13,    E14,    E15,

    PIN_NULL = 0xFF
}gpio_pin_enum;

typedef enum
{
    GPI = 0,        //  定义管脚输入方向
    GPO = 1,        //  定义管脚输出方向
}gpio_dir_enum;

typedef enum
{
    // 输入
    GPI_ANAOG_IN        = 0x00,         //  模拟输入模式
    GPI_FLOATING_IN     = 0x04,         //  浮空输入模式
    GPI_PULL_DOWN       = 0x28,         //  下拉输入
    GPI_PULL_UP         = 0x48,         //  上拉输入

    // 输出
    GPO_PUSH_PULL       = 0x10,         //  通用推挽输出模式
    GPO_OPEN_DTAIN      = 0x14,         //  通用开漏输出模式
    GPO_AF_PUSH_PULL    = 0x18,         //  复用功能推挽输出模式
    GPO_AF_OPEN_DTAIN   = 0x1C,         //  复用功能开漏输出模式
}gpio_mode_enum;

//  宏定义GPIO引脚的默认配置，便于初始化GPIO时快速填写参数，如果需要其他参数可自行修改
#define GPIO_PIN_CONFIG (SPEED_50MHZ | GPO_PUSH_PULL)
//  宏定义GPIO中断和输入引脚的默认配置，便于初始化GPIO中断时快速填写参数，如果需要其他参数可自行修改
#define GPIO_INT_CONFIG (GPI_PULL_UP)

typedef enum
{
    SPEED_10MHZ = (0x01 << 8),
    SPEED_2MHZ  = (0x02 << 8),
    SPEED_50MHZ = (0x03 << 8)
}gpio_speed_enum;

typedef enum
{
    GPIO_LOW  = 0,  //  低电平
    GPIO_HIGH = 1,  //  高电平
}gpio_level_enum;

extern  GPIO_TypeDef *gpio_group[5];



//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取对应 IO 的输入数据地址
// 参数说明     x           选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     uint32      32bit 地址
// 使用示例     gpio_idr_addr(D5);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define     gpio_idr_addr(x)            (0x40040008 + (((x) & 0xFE0) >> 5) * 0x400 + (((x) & 0x1F) / 8))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取对应 IO 的输出数据地址
// 参数说明     x           选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     uint32      32bit 地址
// 使用示例     gpio_odr_addr(D5);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define     gpio_odr_addr(x)            (0x4004000C + (((x) & 0xFE0) >> 5) * 0x400 + (((x) & 0x1F) / 8))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取对应 IO 的置位寄存器地址
// 参数说明     x           选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     uint32      32bit 地址
// 使用示例     gpio_bsrr_addr(D5);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define     gpio_bsrr_addr(x)           (0x40040010 + (((x) & 0xFE0) >> 5) * 0x400 + (((x) & 0x1F) / 8))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取对应 IO 的复位寄存器地址
// 参数说明     x           选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     uint32      32bit 地址
// 使用示例     gpio_brr_addr(D5);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define     gpio_brr_addr(x)            (0x40040014 + (((x) & 0xFE0) >> 5) * 0x400 + (((x) & 0x1F) / 8))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     对应 IO 复位为低电平
// 参数说明     x           选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_low(D5);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define gpio_low(x)             ((GPIO_TypeDef*)gpio_group[(x>>5)])->BCR   = (uint16)(1 << (x & 0x0F))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     对应 IO 置位为高电平
// 参数说明     x           选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_high(D5);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define gpio_high(x)            ((GPIO_TypeDef*)gpio_group[(x>>5)])->BSHR  = (uint16)(1 << (x & 0x0F))

void    gpio_set_level          (gpio_pin_enum pin, uint8 dat);
uint8   gpio_get_level          (gpio_pin_enum pin);
void    gpio_toggle_level       (gpio_pin_enum pin);
void    gpio_init               (gpio_pin_enum pin, gpio_dir_enum dir, const uint8 dat, gpio_mode_enum mode);


#ifdef      COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称
#define     gpio_set(pin, dat)          (gpio_set_level((pin), (dat)))
#define     gpio_get(pin)               (gpio_get_level((pin)))
#define     gpio_dir(pin, dir, mode)    (gpio_set_dir((pin), (dir), (mode)))
#define     gpio_toggle(pin)            (gpio_toggle_level((pin)))
#endif



#endif

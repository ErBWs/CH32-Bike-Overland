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
* 文件名称          zf_driver_gpio
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

#ifndef _zf_driver_gpio_h_
#define _zf_driver_gpio_h_

#include "hal_gpio.h"

#include "zf_common_typedef.h"

typedef enum                                                                    // 枚举 GPIO 引脚  此枚举定义不允许用户修改
{
    A0 = 32* 0, A1 ,    A2 ,    A3 ,    A4 ,    A5 ,    A6 ,    A7 ,
    A8 ,        A9 ,    A10,    A11,    A12,    A13,    A14,    A15,

    B0 = 32* 1, B1 ,    B2 ,    B3 ,    B4 ,    B5 ,    B6 ,    B7 ,
    B8 ,        B9 ,    B10,    B11,    B12,    B13,    B14,    B15,

    C0 = 32* 2, C1 ,    C2 ,    C3 ,    C4 ,    C5 ,    C6 ,    C7 ,
    C8 ,        C9 ,    C10,    C11,    C12,    C13,    C14,    C15,

    D0 = 32* 3, D1 ,    D2 ,    D3 ,    D4 ,    D5 ,    D6 ,    D7 ,
    D8 ,        D9 ,    D10,    D11,    D12,    D13,    D14,    D15,

    E0 = 32* 4, E1 ,    E2 ,    E3 ,    E4 ,    E5 ,    E6 ,    E7 ,
    E8 ,        E9 ,    E10,    E11,    E12,    E13,    E14,    E15,

    F0 = 32* 5, F1 ,    F2 ,    F3 ,    F4 ,    F5 ,    F6 ,    F7 ,
    F8 ,        F9 ,    F10,    F11,    F12,    F13,    F14,    F15,

    G0 = 32* 6, G1 ,    G2 ,    G3 ,    G4 ,    G5 ,    G6 ,    G7 ,
    G8 ,        G9 ,    G10,    G11,    G12,    G13,    G14,    G15,

    H0 = 32* 7, H1 ,    H2 ,    H3 ,

    I0 = 32* 8, I1 ,
}gpio_pin_enum;

typedef enum                                                                    // 枚举端口方向   此枚举定义不允许用户修改
{
    GPI = 0x00,                                                                 // 定义管脚输入
    GPO = 0x10,                                                                 // 定义管脚输出
}gpio_dir_enum;

typedef enum                                                                    // 枚举端口模式   此枚举定义不允许用户修改
{
    GPI_ANAOG_IN        = GPIO_PinMode_In_Analog,                               // [输入] [定义管脚模拟输入]
    GPI_FLOATING_IN     = GPIO_PinMode_In_Floating,                             // [输入] [定义管脚浮空输入]
    GPI_PULL_DOWN       = GPIO_PinMode_In_PullDown,                             // [输入] [定义管脚下拉输入]
    GPI_PULL_UP         = GPIO_PinMode_In_PullUp,                               // [输入] [定义管脚上拉输入]

    GPO_PUSH_PULL       = GPIO_PinMode_Out_PushPull,                            // [输出] [定义管脚推挽输出]
    GPO_OPEN_DTAIN      = GPIO_PinMode_Out_OpenDrain,                           // [输出] [定义管脚开漏输出]
    GPO_AF_PUSH_PULL    = GPIO_PinMode_AF_PushPull,                             // [输出] [定义管脚复用推挽输出]
    GPO_AF_OPEN_DTAIN   = GPIO_PinMode_AF_OpenDrain,                            // [输出] [定义管脚复用开漏输出]
}gpio_mode_enum;

typedef enum                                                                    // 枚举端口复用   此枚举定义不允许用户修改
{
    GPIO_AF0            = GPIO_AF_0 ,                                           // 引脚复用功能选项  0
    GPIO_AF1            = GPIO_AF_1 ,                                           // 引脚复用功能选项  1
    GPIO_AF2            = GPIO_AF_2 ,                                           // 引脚复用功能选项  2
    GPIO_AF3            = GPIO_AF_3 ,                                           // 引脚复用功能选项  3
    GPIO_AF4            = GPIO_AF_4 ,                                           // 引脚复用功能选项  4
    GPIO_AF5            = GPIO_AF_5 ,                                           // 引脚复用功能选项  5
    GPIO_AF6            = GPIO_AF_6 ,                                           // 引脚复用功能选项  6
    GPIO_AF7            = GPIO_AF_7 ,                                           // 引脚复用功能选项  7
    GPIO_AF8            = GPIO_AF_8 ,                                           // 引脚复用功能选项  8
    GPIO_AF9            = GPIO_AF_9 ,                                           // 引脚复用功能选项  9
    GPIO_AF10           = GPIO_AF_10,                                           // 引脚复用功能选项 10
    GPIO_AF11           = GPIO_AF_11,                                           // 引脚复用功能选项 11
    GPIO_AF12           = GPIO_AF_12,                                           // 引脚复用功能选项 12
    GPIO_AF13           = GPIO_AF_13,                                           // 引脚复用功能选项 13
    GPIO_AF14           = GPIO_AF_14,                                           // 引脚复用功能选项 14
    GPIO_AF15           = GPIO_AF_15,                                           // 引脚复用功能选项 15
}gpio_af_enum;

typedef enum                                                                    // 枚举端口电平   此枚举定义不允许用户修改
{
    GPIO_LOW            = 0x00,                                                 // 定义管脚初始化电平为低
    GPIO_HIGH           = 0x01,                                                 // 定义管脚初始化电平为高
}gpio_level_enum;

extern GPIO_Type *gpio_group[9];

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
#define     gpio_low(x)                 (gpio_group[((x) >> 5)]->BRR    |= ((uint16)0x0001 << ((x) & 0x1F)))    // GPIO复位

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     对应 IO 置位为高电平
// 参数说明     x           选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_high(D5);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
#define     gpio_high(x)                (gpio_group[((x) >> 5)]->BSRR   |= ((uint16)0x0001 << ((x) & 0x1F)))    // GPIO置位

void        gpio_set_level              (gpio_pin_enum pin, const uint8 dat);
uint8       gpio_get_level              (gpio_pin_enum pin);
void        gpio_toggle_level           (gpio_pin_enum pin);
void        gpio_set_dir                (gpio_pin_enum pin, gpio_dir_enum dir, gpio_mode_enum mode);

void        gpio_init                   (gpio_pin_enum pin, gpio_dir_enum dir, const uint8 dat, gpio_mode_enum mode);
void        afio_init                   (gpio_pin_enum pin, gpio_dir_enum dir, gpio_af_enum af, gpio_mode_enum mode);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称
#define     gpio_set(pin, dat)          (gpio_set_level((pin), (dat)))
#define     gpio_get(pin)               (gpio_get_level((pin)))
#define     gpio_dir(pin, dir, mode)    (gpio_set_dir((pin), (dir), (mode)))
#define     gpio_toggle(pin)            (gpio_toggle_level((pin)))
#endif

#endif

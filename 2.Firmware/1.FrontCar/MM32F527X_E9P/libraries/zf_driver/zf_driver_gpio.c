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

#include "hal_rcc.h"
#include "zf_common_debug.h"

#include "zf_driver_gpio.h"

GPIO_Type *gpio_group[9] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 输出设置
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     dat         0：低电平 1：高电平
// 返回参数     void
// 使用示例     gpio_set_level(D5, 1);                                          // D5 输出高电平
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_level (gpio_pin_enum pin, const uint8 dat)
{
    (   (dat) ?
        (gpio_group[((pin) >> 5)]->BSRR |= ((uint16)0x0001 << ((pin) & 0x1F))) :
        (gpio_group[((pin) >> 5)]->BRR  |= ((uint16)0x0001 << ((pin) & 0x1F))));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 电平获取
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     uint8       引脚当前电平
// 使用示例     uint8 status = gpio_get_level(D5);                              // 获取 D5 引脚电平
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get_level (gpio_pin_enum pin)
{
    return ((gpio_group[(pin >> 5)]->IDR & (GPIO_PIN_0 << (pin & 0x1F))) ? (1) : (0));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 翻转电平
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_toggle_level(D5);                                          // 翻转 D5 电平
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle_level (gpio_pin_enum pin)
{
    if((gpio_group[(pin >> 5)]->IDR & (GPIO_PIN_0 << (pin & 0x1F))))
    {
        (gpio_group[((pin) >> 5)]->BRR  |= ((uint16)0x0001 << ((pin) & 0x1F)));
    }
    else
    {
        (gpio_group[((pin) >> 5)]->BSRR |= ((uint16)0x0001 << ((pin) & 0x1F)));
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 方向设置
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     dir         引脚的方向   输出：GPO   输入：GPI
// 参数说明     mode        引脚的模式 (可选择范围由 zf_driver_gpio.h 内 gpio_mode_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_set_dir(D5, GPI, GPI_PULL_UP);                             // 设置 D5 为上拉输入
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_dir (gpio_pin_enum pin, gpio_dir_enum dir, gpio_mode_enum mode)
{
    zf_assert(((GPO == dir) && (GPO == (dir & mode))) || ((GPI == dir) && (GPO != (dir & mode))));

    GPIO_Init_Type gpio_init;
    uint8 io_group = ((pin & 0xFE0) >> 5);                                      // 提取IO分组
    uint8 io_pin = (pin & 0x1F);                                                // 提取IO引脚下标

    gpio_init.Pins  = (GPIO_PIN_0 << io_pin);
    gpio_init.PinMode = (GPIO_PinMode_Type)mode;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(gpio_group[io_group], &gpio_init);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 初始化
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     mode        引脚的方向 [GPI/GPIO]
// 参数说明     dat         引脚初始化时设置的电平状态，输出时有效 0：低电平 1：高电平 仅在设置为输出模式时有效
// 参数说明     mode        引脚的模式 (可选择范围由 zf_driver_gpio.h 内 gpio_mode_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_init(D1, GPI, GPIO_HIGH, GPI_PULL_UP);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void gpio_init (gpio_pin_enum pin, gpio_dir_enum dir, const uint8 dat, gpio_mode_enum mode)
{
    zf_assert(((GPO == dir) && (GPO == (dir & mode))) || ((GPI == dir) && (GPO != (dir & mode))));

    GPIO_Init_Type gpio_init;
    uint8 io_group = (pin >> 5);                                                // 提取IO分组
    uint8 io_pin = (pin & 0x1F);                                                // 提取IO引脚下标

    switch(io_group)
    {
        case 0x00:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOA, true); break;
        case 0x01:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOB, true); break;
        case 0x02:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOC, true); break;
        case 0x03:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOD, true); break;
        case 0x04:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOE, true); break;
        case 0x05:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOF, true); break;
        case 0x06:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOG, true); break;
        case 0x07:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOH, true); break;
        case 0x08:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOI, true); break;
    }

    gpio_init.Pins  = (GPIO_PIN_0 << io_pin);
    gpio_init.PinMode = (GPIO_PinMode_Type)mode;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(gpio_group[io_group], &gpio_init);
    GPIO_PinAFConf(gpio_group[io_group], gpio_init.Pins, GPIO_AF_14);

    if(GPO == dir)
    {
        gpio_set_level(pin, dat);                                               // 初始化电平设置
    }
    if(GPI_PULL_DOWN == mode)
    {
        gpio_set_level(pin, GPIO_LOW);
    }
    if(GPI_PULL_UP == mode)
    {
        gpio_set_level(pin, GPIO_HIGH);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     gpio 复用功能初始化 一般是内部调用
// 参数说明     pin         选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     mode        引脚的方向 [GPI/GPIO]
// 参数说明     af          引脚的功能选择 (可选择范围由 zf_driver_gpio.h 内 gpio_af_enum 枚举值确定)
// 参数说明     mode        引脚的模式 (可选择范围由 zf_driver_gpio.h 内 gpio_mode_enum 枚举值确定)
// 返回参数     void
// 使用示例     afio_init(D5, GPO, GPIO_AF0, GPO_AF_PUSH_PULL);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void afio_init (gpio_pin_enum pin, gpio_dir_enum dir, gpio_af_enum af, gpio_mode_enum mode)
{
    zf_assert(((GPO == dir) && (GPO == (dir & mode))) || ((GPI == dir) && (GPO != (dir & mode))));

    GPIO_Init_Type gpio_init;
    uint8 io_group = (pin >> 5);                                                // 提取IO分组
    uint8 io_pin = (pin & 0x1F);                                                // 提取IO引脚下标

    switch(io_group)
    {
        case 0x00:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOA, true); break;
        case 0x01:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOB, true); break;
        case 0x02:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOC, true); break;
        case 0x03:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOD, true); break;
        case 0x04:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOE, true); break;
        case 0x05:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOF, true); break;
        case 0x06:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOG, true); break;
        case 0x07:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOH, true); break;
        case 0x08:  RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOI, true); break;
    }

    gpio_init.Pins  = (GPIO_PIN_0 << io_pin);
    gpio_init.PinMode = (GPIO_PinMode_Type)mode;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(gpio_group[io_group], &gpio_init);
    GPIO_PinAFConf(gpio_group[io_group], gpio_init.Pins, af);
}

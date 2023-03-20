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


#include "zf_driver_gpio.h"


GPIO_TypeDef *gpio_group[5] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     GPIO输出设置
// 参数说明     pin         引脚号选择的引脚 (可选择范围由 common.h 内GPIO_PIN_enum枚举值确定)
// 参数说明     dat         引脚的电平状态，输出时有效 0：低电平 1：高电平
// 返回参数     void
// 使用示例     gpio_set_level(D0, 0);//D0输出低电平
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_level(gpio_pin_enum pin, uint8 dat)
{
    if(dat)
    {
        gpio_high(pin);                                                         // 输出高电平
    }
    else
    {
        gpio_low(pin);                                                          // 输出低电平
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     GPIO状态获取
// 参数说明     pin         选择的引脚 (可选择范围由 common.h 内GPIO_PIN_enum枚举值确定)
// 返回参数     uint8       0：低电平 1：高电平
// 使用示例     uint8 status = gpio_get_level(D0);//获取D0引脚电平
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get_level(gpio_pin_enum pin)
{
    return ((gpio_group[(pin & 0xE0) >> 5]->INDR & (((uint16)0x0001) << (pin & 0x1F))) ? 1 : 0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     GPIO 翻转
// 参数说明     pin         选择的引脚 (可选择范围由 common.h 内GPIO_PIN_enum枚举值确定)
// 返回参数     void        
// 使用示例     gpio_toggle_level(D5);//D5引脚电平翻转
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle_level(gpio_pin_enum pin)
{
    uint8 io_group = (pin & 0xE0) >> 5;
    uint8 io_pin = pin & 0x1F;

    ((gpio_group[io_group]))->OUTDR ^= (uint16)(1 << io_pin);
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
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    uint8 io_group = (pin & 0xE0) >> 5;
    uint8 io_pin = pin & 0x1F;

    // 设置引脚号
    GPIO_InitStructure.GPIO_Pin = (uint16)(1 << io_pin);

    // 只有输出需要设置速度
    if(GPO == dir)
    {
        if((uint16)mode >> 8 == 0) GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)(GPIO_Speed_50MHz);    // 防止没有填写这个参数,默认设置50Mhz
        else GPIO_InitStructure.GPIO_Speed = (gpio_speed_enum)((uint16)mode >> 8);                           // 已经填写了该参数。根据值来设置
    }

    // 设置模式
    GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)((uint16)mode & 0xFF);
    GPIO_Init(gpio_group[io_group], &GPIO_InitStructure);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     GPIO初始化
// 参数说明     pin         选择的引脚 (可选择范围由 common.h 内GPIO_PIN_enum枚举值确定)
// 参数说明     dir         引脚的方向   输出：GPO   输入：GPI
// 参数说明     dat         引脚初始化时设置的电平状态，输出时有效 0：低电平 1：高电平
// 参数说明     pinconf     引脚配置（可设置参数由zf_gpio.h文件内GPIOSPEED_enum与GPIOMODE_enum枚举值确定，多个条件使用 | 相或）
// 返回参数     void
// 使用示例     gpio_init(D0, GPO, 1, GPIO_PIN_CONFIG);//D0初始化为GPIO功能、输出模式、输出高电平、速度100MHZ 推挽输出
//-------------------------------------------------------------------------------------------------------------------
void gpio_init (gpio_pin_enum pin, gpio_dir_enum dir, const uint8 dat, gpio_mode_enum mode)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    uint8 io_group = (pin & 0xE0) >> 5;
    uint8 io_pin = pin & 0x1F;

    // GPIO总线使能
    if(0 == io_group)      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if(1 == io_group) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    else if(2 == io_group) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    else if(3 == io_group) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    else if(4 == io_group) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    // 设置引脚号
    GPIO_InitStructure.GPIO_Pin = (uint16)(1 << io_pin);

    // 只有输出需要设置速度
    if(GPO == dir)
    {
        if((uint16)mode >> 8 == 0) GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)(GPIO_Speed_50MHz);    // 防止没有填写这个参数,默认设置50Mhz
        else GPIO_InitStructure.GPIO_Speed = (gpio_speed_enum)((uint16)mode >> 8);                           // 已经填写了该参数。根据值来设置
    }

    // 设置模式
    GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)((uint16)mode & 0xFF);
    GPIO_Init(gpio_group[io_group], &GPIO_InitStructure);

    // 只有输出需要设置引脚状态
    if(GPO == dir)
    {
        GPIO_WriteBit(gpio_group[io_group], (uint16)(1 << io_pin), dat);
    }
}


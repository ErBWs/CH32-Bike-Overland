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
* 文件名称          zf_driver_exti
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
#include "hal_syscfg.h"
#include "zf_common_interrupt.h"

#include "zf_driver_exti.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     EXTI 中断使能
// 参数说明     pin             选择 EXTI 引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     exti_enable(A0);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void exti_enable (gpio_pin_enum pin)
{
    EXTI_EnableLineInterrupt(EXTI, (0x00000001 << (pin & 0x1F)), ZF_ENABLE);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     EXTI 中断失能
// 参数说明     pin             选择 EXTI 引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     exti_disable(A0);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void exti_disable (gpio_pin_enum pin)
{
    EXTI_EnableLineInterrupt(EXTI, (0x00000001 << (pin & 0x1F)), ZF_DISABLE);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     EXTI 中断初始化
// 参数说明     pin             选择 EXTI 引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     trigger         选择触发的信号方式 [EXTI_TRIGGER_RISING/EXTI_TRIGGER_FALLING/EXTI_TRIGGER_BOTH]
// 返回参数     void
// 使用示例     exti_init(A0, EXTI_TRIGGER_RISING);
// 备注信息     同一下标的引脚不能同时初始化为外部中断输入 例如 A0 和 B0 不能同时初始化为外部中断输入
//-------------------------------------------------------------------------------------------------------------------
void exti_init (gpio_pin_enum pin, exti_trigger_enum trigger)
{
    uint32 register_temp = 0;
    gpio_init(pin, GPI, GPIO_HIGH, GPI_PULL_UP);                                // 初始化选中的引脚

    RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_SYSCFG, true);
    SYSCFG_SetExtIntMux((SYSCFG_EXTIPort_Type)((pin & 0xFE) >> 5), (pin & 0x01f));
    EXTI_SetTriggerIn(EXTI, (0x00000001 << (pin & 0x01f)), (EXTI_TriggerIn_Type)trigger);
    EXTI_EnableLineInterrupt(EXTI, (0x00000001 << (pin & 0x01f)), true);

   if(1 > (pin & 0x1F))
   {
       interrupt_enable(EXTI0_IRQn);                                            // 使能 Line0 的中断响应
   }
   else if(2 > (pin & 0x1F))
   {
       interrupt_enable(EXTI1_IRQn);                                            // 使能 Line1 的中断响应
   }
   else if(3 > (pin & 0x1F))
   {
       interrupt_enable(EXTI2_IRQn);                                            // 使能 Line2 的中断响应
   }
   else if(4 > (pin & 0x1F))
   {
       interrupt_enable(EXTI3_IRQn);                                            // 使能 Line3 的中断响应
   }
   else if(5 > (pin & 0x1F))
   {
       interrupt_enable(EXTI4_IRQn);                                            // 使能 Line4 的中断响应
   }
   else if(10 > (pin & 0x1F))
   {
       interrupt_enable(EXTI9_5_IRQn);                                          // 使能 Line5-9 的中断响应
   }
   else
   {
       interrupt_enable(EXTI15_10_IRQn);                                        // 使能 Line10-15 的中断响应
   }
}

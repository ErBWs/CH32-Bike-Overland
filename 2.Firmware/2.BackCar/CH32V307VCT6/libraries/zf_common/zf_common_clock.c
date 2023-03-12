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
 * 文件名称          zf_common_clock
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

#include "ch32v30x.h"
#include "zf_common_function.h"
#include "zf_common_interrupt.h"

#include "zf_common_clock.h"

uint32 system_clock = SYSTEM_CLOCK_144M;                               // 系统时钟信息

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      核心时钟恢复初始设置 内部调用
// 参数说明     void
// 返回参数     void
//-------------------------------------------------------------------------------------------------------------------
static void clock_reset(void)
{
    RCC->CTLR  |= (uint32) 0x00000001;      //使能HSI振荡器
    RCC->CFGR0 &= (uint32) 0xF8FF0000;
    RCC->CTLR  &= (uint32) 0xFEF6FFFF;
    RCC->CTLR  &= (uint32) 0xFFFBFFFF;
    RCC->CFGR0 &= (uint32) 0xFF80FFFF;
    RCC->INTR   = (uint32) 0x009F0000;      // 禁用所有中断并清除挂起位
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      核心时钟设置
// 参数说明     clock           时钟频率 推荐使用 zf_common_clock.h 中 system_clock_enum 定义的选项
// 返回参数     void
//-------------------------------------------------------------------------------------------------------------------
static void clock_set_freq(uint32 clock)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    RCC->CTLR |= ((uint32_t) RCC_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->CTLR & RCC_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CTLR & RCC_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t) 0x01;
    }
    else
    {
        HSEStatus = (uint32_t) 0x00;
    }

    if (HSEStatus == (uint32_t) 0x01)
    {

//        /* Enable Prefetch Buffer */
//        FLASH->ACTLR |= FLASH_ACTLR_PRFTBE; ((uint8_t)0x10)
//
//        /* Flash 2 wait state */
//        FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);   ((uint8_t)0x03)
//        FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_2;              ((uint8_t)0x02)

        /* HCLK = SYSCLK */
        RCC->CFGR0 |= (uint32_t) RCC_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR0 |= (uint32_t) RCC_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR0 |= (uint32_t) RCC_PPRE1_DIV1;

        /*  PLL configuration: PLLCLK = HSE * ? = ? MHz */
        RCC->CFGR0 &= (uint32) ((uint32) ~(RCC_PLLSRC | RCC_PLLXTPRE
                | RCC_PLLMULL));

        if (clock == SYSTEM_CLOCK_144M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL18_EXTEN);
        else if (clock == SYSTEM_CLOCK_120M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL15_EXTEN);
        else if (clock == SYSTEM_CLOCK_96M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL12_EXTEN);
        else if (clock == SYSTEM_CLOCK_72M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL9_EXTEN);
        else if (clock == SYSTEM_CLOCK_48M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL6_EXTEN);
        else if (clock == SYSTEM_CLOCK_24M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL3_EXTEN);

        /* Enable PLL */
        RCC->CTLR |= RCC_PLLON;
        /* Wait till PLL is ready */
        while((RCC->CTLR & RCC_PLLRDY) == 0)
        {
        }
        /* Select PLL as system clock source */
        RCC->CFGR0 &= (uint32_t) ((uint32_t) ~(RCC_SW));
        RCC->CFGR0 |= (uint32_t) RCC_SW_PLL;
        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08)
        {
        }
    }
    else
    {
        while(1);
        // 外部晶振不稳定或缺失 时钟设置失败
        /*
         * If HSE fails to start-up, the application will have wrong clock
         * configuration. User can add here some code to deal with this error
         */
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      核心时钟初始化
// 参数说明     clock           时钟频率 推荐使用 zf_common_clock.h 中 system_clock_enum 定义的选项
// 返回参数     void
// 使用示例     clock_init(SYSTEM_CLOCK_144M);                   // 初始化核心时钟为 144MHz
//-------------------------------------------------------------------------------------------------------------------
void clock_init(uint32 clock)
{

    system_clock = clock;                                            // 记录核心时钟频率
    clock_reset();
    clock_set_freq(clock);

    interrupt_init();


}

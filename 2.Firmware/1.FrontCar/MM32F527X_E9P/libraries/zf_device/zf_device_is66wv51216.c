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
* 文件名称          zf_device_is66wv51216
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
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   CS1#                G10
*                   WE#                 D5
*                   LB#                 E0
*                   UB#                 E1
*                   OE#                 D4
*                   A0                  F0
*                   A1                  F1
*                   A2                  F2
*                   A3                  F3
*                   A4                  F4
*                   A5                  F5
*                   A6                  F12
*                   A7                  F13
*                   A8                  F14
*                   A9                  F15
*                   A10                 G0
*                   A11                 G1
*                   A12                 G2
*                   A13                 G3
*                   A14                 G4
*                   A15                 G5
*                   A16                 D11
*                   A17                 D12
*                   A18                 D13
*                   IO0                 D14
*                   IO1                 D15
*                   IO2                 D0
*                   IO3                 D1
*                   IO4                 E7
*                   IO5                 E8
*                   IO6                 E9
*                   IO7                 E10
*                   IO8                 E11
*                   IO9                 E12
*                   IO10                E13
*                   IO11                E14
*                   IO12                E15
*                   IO13                D8
*                   IO14                D9
*                   IO15                D10
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "zf_driver_fsmc.h"

#include "zf_device_is66wv51216.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief       初始化 SRAM
// @param       void
// @return      uint8           1-初始化失败 0-初始化成功
// Sample usage:                is66wv51216_init();
//-------------------------------------------------------------------------------------------------------------------
uint8 is66wv51216_init (void)
{
    afio_init(G10, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_NE3     SRAM_CS1#
    afio_init(D5 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_NWE     SRAM_WE#
    afio_init(E0 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_NBL0    SRAM_LB#
    afio_init(E1 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_NBL1    SRAM_UB#
    afio_init(D4 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_NOE     SRAM_OE#

    afio_init(F0 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A0      SRAM_A0
    afio_init(F1 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A1      SRAM_A1
    afio_init(F2 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A2      SRAM_A2
    afio_init(F3 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A3      SRAM_A3
    afio_init(F4 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A4      SRAM_A4
    afio_init(F5 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A5      SRAM_A5
    afio_init(F12, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A6      SRAM_A6
    afio_init(F13, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A7      SRAM_A7
    afio_init(F14, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A8      SRAM_A8 
    afio_init(F15, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A9      SRAM_A9 
    afio_init(G0 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A10     SRAM_A10
    afio_init(G1 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A11     SRAM_A11
    afio_init(G2 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A12     SRAM_A12
    afio_init(G3 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A13     SRAM_A13
    afio_init(G4 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A14     SRAM_A14
    afio_init(G5 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A15     SRAM_A15
    afio_init(D11, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A14     SRAM_A16
    afio_init(D12, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A15     SRAM_A17
    afio_init(D13, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_A15     SRAM_A18

    afio_init(D14, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D0      SRAM_D0  & IPS350_D0
    afio_init(D15, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D1      SRAM_D1  & IPS350_D1
    afio_init(D0 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D2      SRAM_D2  & IPS350_D2
    afio_init(D1 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D3      SRAM_D3  & IPS350_D3
    afio_init(E7 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D4      SRAM_D4  & IPS350_D4
    afio_init(E8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D5      SRAM_D5  & IPS350_D5
    afio_init(E9 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D6      SRAM_D6  & IPS350_D6
    afio_init(E10, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D7      SRAM_D7  & IPS350_D7
    afio_init(E11, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D8      SRAM_D8  & IPS350_D8 
    afio_init(E12, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D9      SRAM_D9  & IPS350_D9
    afio_init(E13, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D10     SRAM_D10 & IPS350_D10
    afio_init(E14, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D11     SRAM_D11 & IPS350_D11
    afio_init(E15, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D12     SRAM_D12 & IPS350_D12
    afio_init(D8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D13     SRAM_D13 & IPS350_D13
    afio_init(D9 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D14     SRAM_D14 & IPS350_D14
    afio_init(D10, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // FSMC_D15     SRAM_D15 & IPS350_D15

    fsmc_is66wv51216_init();

    return 0;
}

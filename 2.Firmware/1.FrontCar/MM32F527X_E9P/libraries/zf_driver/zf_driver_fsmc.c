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
* 文件名称          zf_driver_fsmc
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
#include "zf_driver_gpio.h"

#include "zf_driver_fsmc.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 屏幕的 FSMC 外设初始化
// 参数说明     void
// 返回参数     void
// 使用示例     fsmc_ips200_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void fsmc_ips200_init (void)
{
    RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_FSMC, ZF_ENABLE);

    FSMC_Conf_Type fsmc_config;
//    fsmc_config.ReadPeriod = 1;
//    fsmc_config.AddrSetTime = 2;
//    fsmc_config.WriteHoldTime = 3;
//    fsmc_config.WritePeriod = 3;
    fsmc_config.ReadPeriod = 1;
    fsmc_config.AddrSetTime = 3;
    fsmc_config.WriteHoldTime = 0;
    fsmc_config.WritePeriod = 0;
    fsmc_config.ReadySignal = FSMC_ReadySignal_Internal;
    fsmc_config.SMReadPipe = 0;
    fsmc_config.BusWidth = FSMC_BusWidth_16b;
    FSMC_SetConf(FSMC, 0, &fsmc_config);

    FSMC_Init_Type fsmc_init;
    fsmc_init.MemType = FSMC_MemType_SRAM;
    fsmc_init.MemSize = FSMC_MemSize_64MB;
    FSMC_Init(FSMC, 3, &fsmc_init);
    FSMC_EnableConf(FSMC, 3, 0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 屏幕的 FSMC 外设初始化
// 参数说明     void
// 返回参数     void
// 使用示例     fsmc_ips350_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void fsmc_ips350_init (void)
{
    RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_FSMC, ZF_ENABLE);

    FSMC_Conf_Type fsmc_config;
//    fsmc_config.ReadPeriod = 1;
//    fsmc_config.AddrSetTime = 3;
//    fsmc_config.WriteHoldTime = 3;
//    fsmc_config.WritePeriod = 3;
    fsmc_config.ReadPeriod = 0;
    fsmc_config.AddrSetTime = 3;
    fsmc_config.WriteHoldTime = 3;
    fsmc_config.WritePeriod = 31;
    fsmc_config.ReadySignal = FSMC_ReadySignal_Internal;
    fsmc_config.SMReadPipe = 0;
    fsmc_config.BusWidth = FSMC_BusWidth_16b;
    FSMC_SetConf(FSMC, 0, &fsmc_config);

    FSMC_Init_Type fsmc_init;
    fsmc_init.MemType = FSMC_MemType_SRAM;
    fsmc_init.MemSize = FSMC_MemSize_64MB;
    FSMC_Init(FSMC, 3, &fsmc_init);
    FSMC_EnableConf(FSMC, 3, 0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ISSI IS66WV51216 SRAM 的 FSMC 外设初始化
// 参数说明     void
// 返回参数     void
// 使用示例     fsmc_is66wv51216_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void fsmc_is66wv51216_init (void)
{
    RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_FSMC, ZF_ENABLE);

    FSMC_Conf_Type fsmc_config;
    fsmc_config.ReadPeriod = 23;
    fsmc_config.AddrSetTime = 3;
    fsmc_config.WriteHoldTime = 3;
    fsmc_config.WritePeriod = 7;
    fsmc_config.ReadySignal = FSMC_ReadySignal_Internal;
    fsmc_config.SMReadPipe = 0;
    fsmc_config.BusWidth = FSMC_BusWidth_16b;
    FSMC_SetConf(FSMC, 1, &fsmc_config);

    FSMC_Init_Type fsmc_init;
    fsmc_init.MemType = FSMC_MemType_SRAM;
    fsmc_init.MemSize = FSMC_MemSize_1MB;
    FSMC_Init(FSMC, 2, &fsmc_init);
    FSMC_EnableConf(FSMC, 2, 1);
}


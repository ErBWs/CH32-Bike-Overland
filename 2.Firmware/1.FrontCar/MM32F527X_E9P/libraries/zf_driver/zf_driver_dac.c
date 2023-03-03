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
* 文件名称          zf_driver_dac
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
#include "zf_common_clock.h"
#include "zf_driver_gpio.h"

#include "zf_driver_dac.h"

static  dac_resolution_enum dac_resolution[2] = {DAC_12BIT, DAC_12BIT};         // 精度数据备份

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DAC 更新输出数据
// 参数说明     ch              选择 DAC 通道 (详见 zf_driver_dac.h 中枚举 dac_channel_enum 定义)
// 参数说明     data            输出的 dac 值
// 返回参数     void
// 使用示例     dac_output(DAC_OUT1_A4, 1024);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void dac_output (dac_channel_enum ch, uint16 data)
{
    DAC_PutData(DAC, (0x000F & ch), data, (DAC_Align_Type)dac_resolution[(0x000F & ch)]);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     DAC 初始化
// 参数说明     ch              选择 DAC 通道 (详见 zf_driver_dac.h 中枚举 dac_channel_enum 定义)
// 参数说明     resolution      DAC 使用的精度位数
// 返回参数     void
// 使用示例     dac_init(DAC_OUT1_A4, DAC_12BIT);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void dac_init (dac_channel_enum ch, dac_resolution_enum resolution)
{
    gpio_init((gpio_pin_enum)((ch & 0xFFF0) >> 4), GPI, GPIO_LOW, GPI_ANAOG_IN);

    dac_resolution[(0x000F & ch)] = resolution;
    RCC_EnableAPB1Periphs(RCC_APB1_PERIPH_DAC, true);

    DAC_Init_Type dac_init;
    dac_init.EnableOutBuf = false;
    dac_init.EnableTrigger = false;

    DAC_Init(DAC, (0x000F & ch), &dac_init);
    DAC_Enable(DAC, (0x000F & ch), true);
    DAC_EnableChannelOutput(DAC, (0x000F & ch), true);
}




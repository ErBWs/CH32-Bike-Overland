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

#ifndef _zf_driver_dac_h_
#define _zf_driver_dac_h_

#include "hal_dac.h"

#include "zf_common_typedef.h"

typedef enum                                                                    // 枚举 ADC 引脚通道  此枚举定义不允许用户修改
{
    DAC_OUT1_A4         = 0x0040,                                               // 0x 000[A0 ] 0[OUT1]
    DAC_OUT2_A5         = 0x0051,                                               // 0x 005[A5 ] 1[OUT2]
}dac_channel_enum;

typedef enum                                                                    // 枚举 ADC 引脚通道  此枚举定义不允许用户修改
{
    DAC_8BIT            = DAC_Align_8b_Right,
    DAC_12BIT           = DAC_Align_12b_Right,
}dac_resolution_enum;

void        dac_output              (dac_channel_enum ch, uint16 data);
void        dac_init                (dac_channel_enum ch, dac_resolution_enum resolution);

#endif

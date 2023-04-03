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
* 文件名称          zf_driver_adc
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

#ifndef _zf_driver_adc_h
#define _zf_driver_adc_h

#include "zf_driver_gpio.h"
#include "zf_common_typedef.h"
//CH32V307只有一个ADC，可以分时复用在很多个通道上面


//此枚举定义不允许用户修改
typedef enum    // 枚举ADC通道
{
    ADC1_IN0_A0  = 0x0000,    // 0x 0[ADC1] 0[CH00] 00[A0]
    ADC1_IN1_A1  = 0x0101,    // 0x 0[ADC1] 1[CH00] 01[A1]
    ADC1_IN2_A2  = 0x0202,    // 0x 0[ADC1] 2[CH00] 02[A2]
    ADC1_IN3_A3  = 0x0303,    // 0x 0[ADC1] 3[CH00] 03[A3]
    ADC1_IN4_A4  = 0x0404,    // 0x 0[ADC1] 4[CH00] 04[A4]
    ADC1_IN5_A5  = 0x0505,    // 0x 0[ADC1] 5[CH00] 05[A5]
    ADC1_IN6_A6  = 0x0606,    // 0x 0[ADC1] 6[CH00] 06[A6]
    ADC1_IN7_A7  = 0x0707,    // 0x 0[ADC1] 7[CH00] 07[A7]
    ADC1_IN8_B0  = 0x0820,    // 0x 0[ADC1] 8[CH00] 20[B0]
    ADC1_IN9_B1  = 0x0921,    // 0x 0[ADC1] 9[CH00] 21[B1]
    ADC1_IN10_C0 = 0x0A40,    // 0x 0[ADC1] A[CH00] 40[C0]
    ADC1_IN11_C1 = 0x0B41,    // 0x 0[ADC1] B[CH00] 41[C1]
    ADC1_IN12_C2 = 0x0C42,    // 0x 0[ADC1] C[CH00] 42[C2]
    ADC1_IN13_C3 = 0x0D43,    // 0x 0[ADC1] D[CH00] 43[C3]
    ADC1_IN14_C4 = 0x0E44,    // 0x 0[ADC1] E[CH00] 44[C4]
    ADC1_IN15_C5 = 0x0F45,    // 0x 0[ADC1] F[CH00] 45[C5]


    ADC2_IN0_A0  = 0x1000,    // 0x 1[ADC2] 0[CH00] 00[A0]
    ADC2_IN1_A1  = 0x1101,    // 0x 1[ADC2] 1[CH00] 01[A1]
    ADC2_IN2_A2  = 0x1202,    // 0x 1[ADC2] 2[CH00] 02[A2]
    ADC2_IN3_A3  = 0x1303,    // 0x 1[ADC2] 3[CH00] 03[A3]
    ADC2_IN4_A4  = 0x1404,    // 0x 1[ADC2] 4[CH00] 04[A4]
    ADC2_IN5_A5  = 0x1505,    // 0x 1[ADC2] 5[CH00] 05[A5]
    ADC2_IN6_A6  = 0x1606,    // 0x 1[ADC2] 6[CH00] 06[A6]
    ADC2_IN7_A7  = 0x1707,    // 0x 1[ADC2] 7[CH00] 07[A7]
    ADC2_IN8_B0  = 0x1820,    // 0x 1[ADC2] 8[CH00] 20[B0]
    ADC2_IN9_B1  = 0x1921,    // 0x 1[ADC2] 9[CH00] 21[B1]
    ADC2_IN10_C0 = 0x1A40,    // 0x 1[ADC2] A[CH00] 40[C0]
    ADC2_IN11_C1 = 0x1B41,    // 0x 1[ADC2] B[CH00] 41[C1]
    ADC2_IN12_C2 = 0x1C42,    // 0x 1[ADC2] C[CH00] 42[C2]
    ADC2_IN13_C3 = 0x1D43,    // 0x 1[ADC2] D[CH00] 43[C3]
    ADC2_IN14_C4 = 0x1E44,    // 0x 1[ADC2] E[CH00] 44[C4]
    ADC2_IN15_C5 = 0x1F45,    // 0x 1[ADC2] F[CH00] 45[C5]
}adc_channel_enum;


//此枚举定义不允许用户修改
typedef enum            // 枚举ADC通道
{
    ADC_8BIT  = 4,      //8位分辨率
    ADC_9BIT  = 3,      //9位分辨率
    ADC_10BIT = 2,      //10位分辨率
    ADC_11BIT = 1,      //11位分辨率
    ADC_12BIT = 0,      //12位分辨率
}adc_resolution_enum;




uint16  adc_convert             (adc_channel_enum ch);
uint16  adc_mean_filter_convert (adc_channel_enum ch, const uint8 count);
void    adc_init                (adc_channel_enum ch, adc_resolution_enum resolution);


#endif

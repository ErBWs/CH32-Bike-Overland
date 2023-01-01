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
* 文件名称          zf_driver_encoder
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

#ifndef _zf_driver_encoder_h_
#define _zf_driver_encoder_h_

#include "zf_common_typedef.h"

typedef enum                                                                    // 枚举 TIM_ENCOEDER 通道    此枚举定义不允许用户修改
{
    // Advanced Timer 16 bits TIM1
    TIM1_ENCOEDER_CH1_A8          = 0x008110,                                   // 0x 008[A8]  1[AF1] 1[CH1] 0[TIM1]
    TIM1_ENCOEDER_CH1_E9          = 0x089110,                                   // 0x 089[E9]  1[AF1] 1[CH1] 0[TIM1]

    // General Timer 32 bits TIM2
    TIM2_ENCOEDER_CH1_A0          = 0x000111,                                   // 0x 000[A0]  1[AF1] 1[CH1] 1[TIM2]
    TIM2_ENCOEDER_CH1_A5          = 0x005111,                                   // 0x 005[A5]  1[AF1] 1[CH1] 1[TIM2]
    TIM2_ENCOEDER_CH1_A15         = 0x00F111,                                   // 0x 00F[A15] 1[AF1] 1[CH1] 1[TIM2]

    // General Timer 16 bits TIM3
    TIM3_ENCOEDER_CH1_A6          = 0x006212,                                   // 0x 006[A6]  2[AF2] 1[CH1] 2[TIM3]
    TIM3_ENCOEDER_CH1_B4          = 0x024212,                                   // 0x 024[B4]  2[AF2] 1[CH1] 2[TIM3]
    TIM3_ENCOEDER_CH1_C6          = 0x046212,                                   // 0x 046[C6]  2[AF2] 1[CH1] 2[TIM3]
    TIM3_ENCOEDER_CH1_E2          = 0x082212,                                   // 0x 082[E2]  2[AF2] 1[CH1] 2[TIM3]

    // General Timer 16 bits TIM4
    TIM4_ENCOEDER_CH1_B6          = 0x026213,                                   // 0x 026[B6]  2[AF2] 1[CH1] 2[TIM3]
    TIM4_ENCOEDER_CH1_D12         = 0x06C213,                                   // 0x 06C[D12] 2[AF2] 1[CH1] 2[TIM3]

    // General Timer 32 bits TIM5
    TIM5_ENCOEDER_CH1_A0          = 0x000214,                                   // 0x 000[A0]  2[AF2] 1[CH1] 4[TIM5]
    TIM5_ENCOEDER_CH1_F6          = 0x0A6214,                                   // 0x 0A6[F6]  2[AF2] 1[CH1] 4[TIM5]

    // Advanced Timer 16 bits TIM8
    TIM8_ENCOEDER_CH1_C6          = 0x046317,                                   // 0x 046[C6]  3[AF3] 1[CH1] 7[TIM8]
    TIM8_ENCOEDER_CH1_C13         = 0x04D317,                                   // 0x 04D[C13] 3[AF3] 1[CH1] 7[TIM8]
}encoder_channel1_enum;

typedef enum                                                                    // 枚举 TIM_ENCOEDER 通道    此枚举定义不允许用户修改
{
    // Advanced Timer 16 bits TIM1
    TIM1_ENCOEDER_CH2_A9          = 0x009120,                                   // 0x 009[A9]  1[AF1] 2[CH2] 0[TIM1]
    TIM1_ENCOEDER_CH2_E11         = 0x08B120,                                   // 0x 08B[E11] 1[AF1] 2[CH2] 0[TIM1]

    // General Timer 32 bits TIM2
    TIM2_ENCOEDER_CH2_A1          = 0x001121,                                   // 0x 001[A1]  1[AF1] 2[CH2] 1[TIM2]
    TIM2_ENCOEDER_CH2_B3          = 0x023121,                                   // 0x 023[B3]  1[AF1] 2[CH2] 1[TIM2]

    // General Timer 16 bits TIM3
    TIM3_ENCOEDER_CH2_A7          = 0x007222,                                   // 0x 007[A7]  2[AF2] 2[CH2] 2[TIM3]
    TIM3_ENCOEDER_CH2_B5          = 0x025222,                                   // 0x 025[B5]  2[AF2] 2[CH2] 2[TIM3]
    TIM3_ENCOEDER_CH2_C7          = 0x047222,                                   // 0x 047[C7]  2[AF2] 2[CH2] 2[TIM3]
    TIM3_ENCOEDER_CH2_E3          = 0x083222,                                   // 0x 083[E3]  2[AF2] 2[CH2] 2[TIM3]

    // General Timer 16 bits TIM4
    TIM4_ENCOEDER_CH2_B7          = 0x027223,                                   // 0x 027[B7]  2[AF2] 2[CH2] 2[TIM3]
    TIM4_ENCOEDER_CH2_D13         = 0x06D223,                                   // 0x 06D[D13] 2[AF2] 2[CH2] 2[TIM3]

    // General Timer 32 bits TIM5
    TIM5_ENCOEDER_CH2_A1          = 0x001224,                                   // 0x 001[A1]  2[AF2] 2[CH2] 4[TIM5]
    TIM5_ENCOEDER_CH2_F7          = 0x0A7224,                                   // 0x 0A7[F7]  2[AF2] 2[CH2] 4[TIM5]

    // Advanced Timer 16 bits TIM8
    TIM8_ENCOEDER_CH2_C7          = 0x047327,                                   // 0x 047[C7]  3[AF3] 2[CH2] 7[TIM8]
    TIM8_ENCOEDER_CH2_C14         = 0x04E327,                                   // 0x 04E[C14] 3[AF3] 2[CH2] 7[TIM8]
}encoder_channel2_enum;

typedef enum                                                                    // 枚举 TIM_ENCOEDER 模块    此枚举定义不允许用户修改
{
    TIM1_ENCOEDER = 0,
    TIM2_ENCOEDER,
    TIM3_ENCOEDER,
    TIM4_ENCOEDER,
    TIM5_ENCOEDER,
    TIM8_ENCOEDER = 7,
}encoder_index_enum;

int16   encoder_get_count       (encoder_index_enum encoder_n);
void    encoder_clear_count     (encoder_index_enum encoder_n);

void    encoder_quad_init       (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin);
void    encoder_dir_init        (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin);

#endif

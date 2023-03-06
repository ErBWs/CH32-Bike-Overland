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
* 文件名称          zf_driver_pwm
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

#ifndef _zf_driver_pwm_h_
#define _zf_driver_pwm_h_

#include "zf_common_typedef.h"

#define PWM_DUTY_MAX        (10000)

typedef enum                                                                    // 枚举 PWM 通道    此枚举定义不允许用户修改
{
    // Advanced Timer 16 bits TIM1 positive-channel 正向通道
    TIM1_PWM_CH1_A8          = 0x008110,                                        // 0x 008[A8]  1[AF1] 1[CH1] 0[TIM1]
    TIM1_PWM_CH1_E9          = 0x089110,                                        // 0x 089[E9]  1[AF1] 1[CH1] 0[TIM1]

    TIM1_PWM_CH2_A9          = 0x009120,                                        // 0x 009[A9]  1[AF1] 2[CH2] 0[TIM1]
    TIM1_PWM_CH2_E11         = 0x08B120,                                        // 0x 08B[E11] 1[AF1] 2[CH2] 0[TIM1]

    TIM1_PWM_CH3_A10         = 0x00A130,                                        // 0x 00A[A10] 1[AF1] 3[CH3] 0[TIM1]
    TIM1_PWM_CH3_E13         = 0x08D130,                                        // 0x 08D[E13] 1[AF1] 3[CH2] 0[TIM1]

    TIM1_PWM_CH4_A11         = 0x00B140,                                        // 0x 00B[A11] 1[AF1] 4[CH4] 0[TIM1]
    TIM1_PWM_CH4_E14         = 0x08E140,                                        // 0x 08E[E14] 1[AF1] 4[CH4] 0[TIM1]

    // Advanced Timer 16 bits TIM1 inversion-channel 反向通道
    TIM1_PWM_CH1N_A7         = 0x007150,                                        // 0x 007[A7]  1[AF1] 5[CH1] 0[TIM1]
    TIM1_PWM_CH1N_B13        = 0x02D150,                                        // 0x 02D[B13] 1[AF1] 5[CH1] 0[TIM1]
    TIM1_PWM_CH1N_E8         = 0x088150,                                        // 0x 088[E8]  1[AF1] 5[CH1] 0[TIM1]

    TIM1_PWM_CH2N_B0         = 0x020160,                                        // 0x 020[B0]  1[AF1] 6[CH2] 0[TIM1]
    TIM1_PWM_CH2N_B14        = 0x02E160,                                        // 0x 02E[B14] 1[AF1] 6[CH2] 0[TIM1]
    TIM1_PWM_CH2N_E10        = 0x08A160,                                        // 0x 0A8[E10] 1[AF1] 6[CH2] 0[TIM1]

    TIM1_PWM_CH3N_B1         = 0x021170,                                        // 0x 021[B1]  1[AF1] 7[CH3] 0[TIM1]
    TIM1_PWM_CH3N_B15        = 0x02F170,                                        // 0x 02F[B15] 1[AF1] 7[CH3] 0[TIM1]
    TIM1_PWM_CH3N_E12        = 0x08C170,                                        // 0x 08C[E12] 1[AF1] 7[CH3] 0[TIM1]

    TIM1_PWM_CH4N_B2         = 0x022180,                                        // 0x 022[B2]  1[AF1] 8[CH4] 0[TIM1]
    TIM1_PWM_CH4N_I0         = 0x100180,                                        // 0x 100[I0]  1[AF1] 8[CH4] 0[TIM1]

    // Advanced Timer 16 bits TIM8 positive-channel 正向通道
    TIM8_PWM_CH1_C6          = 0x046317,                                        // 0x 046[C6]  3[AF3] 1[CH1] 7[TIM8]
    TIM8_PWM_CH1_C13         = 0x04D317,                                        // 0x 04D[C13] 3[AF3] 1[CH1] 7[TIM8]

    TIM8_PWM_CH2_C7          = 0x047327,                                        // 0x 047[C7]  3[AF3] 2[CH2] 7[TIM8]
    TIM8_PWM_CH2_C14         = 0x04E327,                                        // 0x 04E[C14] 3[AF3] 2[CH2] 7[TIM8]

    TIM8_PWM_CH3_C8          = 0x048337,                                        // 0x 048[C8]  3[AF3] 3[CH3] 7[TIM8]
    TIM8_PWM_CH3_C15         = 0x04F337,                                        // 0x 04F[C15] 3[AF3] 3[CH3] 7[TIM8]

    TIM8_PWM_CH4_C9          = 0x049347,                                        // 0x 049[C9]  3[AF3] 4[CH4] 7[TIM8]
    TIM8_PWM_CH4_I0          = 0x100347,                                        // 0x 100[I0]  3[AF3] 4[CH4] 7[TIM8]

    // Advanced Timer 16 bits TIM8 inversion-channel 反向通道
    TIM8_PWM_CH1N_A5         = 0x005357,                                        // 0x 005[A5]  3[AF3] 5[CH1] 7[TIM8]
    TIM8_PWM_CH1N_A7         = 0x007357,                                        // 0x 007[A7]  3[AF3] 5[CH1] 7[TIM8]
    TIM8_PWM_CH1N_B8         = 0x028357,                                        // 0x 028[B8]  3[AF3] 5[CH1] 7[TIM8]
    TIM8_PWM_CH1N_B13        = 0x02D357,                                        // 0x 02D[B13] 3[AF3] 5[CH1] 7[TIM8]

    TIM8_PWM_CH2N_B0         = 0x020367,                                        // 0x 020[B0]  3[AF3] 6[CH2] 7[TIM8]
    TIM8_PWM_CH2N_B9         = 0x029367,                                        // 0x 029[B9]  3[AF3] 6[CH2] 7[TIM8]
    TIM8_PWM_CH2N_B14        = 0x02E367,                                        // 0x 02E[B14] 3[AF3] 6[CH2] 7[TIM8]

    TIM8_PWM_CH3N_B1         = 0x021377,                                        // 0x 021[B1]  3[AF3] 7[CH3] 7[TIM8]
    TIM8_PWM_CH3N_B5         = 0x025377,                                        // 0x 025[B5]  3[AF3] 7[CH3] 7[TIM8]
    TIM8_PWM_CH3N_B15        = 0x02F377,                                        // 0x 02F[B15] 3[AF3] 7[CH3] 7[TIM8]

    TIM8_PWM_CH4N_B2         = 0x022387,                                        // 0x 022[B2]  3[AF3] 8[CH4] 7[TIM8]
    TIM8_PWM_CH4N_B6         = 0x026387,                                        // 0x 026[B6]  3[AF3] 8[CH4] 7[TIM8]

    // General Timer 32 bits TIM2 positive-channel 正向通道
    TIM2_PWM_CH1_A0          = 0x000111,                                        // 0x 000[A0]  1[AF1] 1[CH1] 1[TIM2]
    TIM2_PWM_CH1_A5          = 0x005111,                                        // 0x 005[A5]  1[AF1] 1[CH1] 1[TIM2]
    TIM2_PWM_CH1_A15         = 0x00F111,                                        // 0x 00F[A15] 1[AF1] 1[CH1] 1[TIM2]

    TIM2_PWM_CH2_A1          = 0x001121,                                        // 0x 001[A1]  1[AF1] 2[CH2] 1[TIM2]
    TIM2_PWM_CH2_B3          = 0x023121,                                        // 0x 023[B3]  1[AF1] 2[CH2] 1[TIM2]

    TIM2_PWM_CH3_A2          = 0x002131,                                        // 0x 002[A2]  1[AF1] 3[CH3] 1[TIM2]
    TIM2_PWM_CH3_B10         = 0x02A131,                                        // 0x 02A[B10] 1[AF1] 3[CH3] 1[TIM2]

    TIM2_PWM_CH4_A3          = 0x003141,                                        // 0x 003[A3]  1[AF1] 4[CH4] 1[TIM2]
    TIM2_PWM_CH4_B11         = 0x02B141,                                        // 0x 02B[B11] 1[AF1] 4[CH4] 1[TIM2]

    // General Timer 32 bits TIM5 positive-channel 正向通道
    TIM5_PWM_CH1_A0          = 0x000214,                                        // 0x 000[A0]  2[AF2] 1[CH1] 4[TIM5]
    TIM5_PWM_CH1_F6          = 0x0A6214,                                        // 0x 0A6[F6]  2[AF2] 1[CH1] 4[TIM5]

    TIM5_PWM_CH2_A1          = 0x001224,                                        // 0x 001[A1]  2[AF2] 2[CH2] 4[TIM5]
    TIM5_PWM_CH2_F7          = 0x0A7224,                                        // 0x 0A7[F7]  2[AF2] 2[CH2] 4[TIM5]

    TIM5_PWM_CH3_A2          = 0x002234,                                        // 0x 002[A2]  2[AF2] 3[CH3] 4[TIM5]
    TIM5_PWM_CH3_F8          = 0x0A8234,                                        // 0x 0A8[F8]  2[AF2] 3[CH3] 4[TIM5]

    TIM5_PWM_CH4_A3          = 0x003244,                                        // 0x 003[A3]  2[AF2] 4[CH4] 4[TIM5]
    TIM5_PWM_CH4_F9          = 0x0A9244,                                        // 0x 0A9[F9]  2[AF2] 4[CH4] 4[TIM5]

    // General Timer 16 bits TIM3 positive-channel 正向通道
    TIM3_PWM_CH1_A6          = 0x006212,                                        // 0x 006[A6]  2[AF2] 1[CH1] 2[TIM3]
    TIM3_PWM_CH1_B4          = 0x024212,                                        // 0x 024[B4]  2[AF2] 1[CH1] 2[TIM3]
    TIM3_PWM_CH1_C6          = 0x046212,                                        // 0x 046[C6]  2[AF2] 1[CH1] 2[TIM3]
    TIM3_PWM_CH1_E2          = 0x082212,                                        // 0x 082[E2]  2[AF2] 1[CH1] 2[TIM3]

    TIM3_PWM_CH2_A7          = 0x007222,                                        // 0x 007[A7]  2[AF2] 2[CH2] 2[TIM3]
    TIM3_PWM_CH2_B5          = 0x025222,                                        // 0x 025[B5]  2[AF2] 2[CH2] 2[TIM3]
    TIM3_PWM_CH2_C7          = 0x047222,                                        // 0x 047[C7]  2[AF2] 2[CH2] 2[TIM3]
    TIM3_PWM_CH2_E3          = 0x083222,                                        // 0x 083[E3]  2[AF2] 2[CH2] 2[TIM3]

    TIM3_PWM_CH3_B0          = 0x020232,                                        // 0x 020[B0]  2[AF2] 3[CH3] 2[TIM3]
    TIM3_PWM_CH3_C8          = 0x048232,                                        // 0x 048[C8]  2[AF2] 3[CH3] 2[TIM3]
    TIM3_PWM_CH3_E4          = 0x084232,                                        // 0x 084[E4]  2[AF2] 3[CH3] 2[TIM3]
    TIM3_PWM_CH3_E6          = 0x086232,                                        // 0x 086[E6]  2[AF2] 3[CH3] 2[TIM3]

    TIM3_PWM_CH4_B1          = 0x021242,                                        // 0x 021[B1]  2[AF2] 4[CH4] 2[TIM3]
    TIM3_PWM_CH4_C9          = 0x049242,                                        // 0x 049[C9]  2[AF2] 4[CH4] 2[TIM3]
    TIM3_PWM_CH4_E5          = 0x085242,                                        // 0x 085[E5]  2[AF2] 4[CH4] 2[TIM3]

    // General Timer 16 bits TIM4 positive-channel 正向通道
    TIM4_PWM_CH1_B6          = 0x026213,                                        // 0x 026[B6]  2[AF2] 1[CH1] 2[TIM3]
    TIM4_PWM_CH1_D12         = 0x06C213,                                        // 0x 06C[D12] 2[AF2] 1[CH1] 2[TIM3]

    TIM4_PWM_CH2_B7          = 0x027223,                                        // 0x 027[B7]  2[AF2] 2[CH2] 2[TIM3]
    TIM4_PWM_CH2_D13         = 0x06D223,                                        // 0x 06D[D13] 2[AF2] 2[CH2] 2[TIM3]

    TIM4_PWM_CH3_B8          = 0x028233,                                        // 0x 028[B8]  2[AF2] 3[CH3] 2[TIM3]
    TIM4_PWM_CH3_D14         = 0x06E233,                                        // 0x 06E[D14] 2[AF2] 3[CH3] 2[TIM3]

    TIM4_PWM_CH4_B9          = 0x029243,                                        // 0x 029[B9]  2[AF2] 4[CH4] 2[TIM3]
    TIM4_PWM_CH4_D15         = 0x06F243,                                        // 0x 06F[D15] 2[AF2] 4[CH4] 2[TIM3]
}pwm_channel_enum;

void    pwm_set_duty    (pwm_channel_enum pin, const uint32 duty);
void    pwm_init        (pwm_channel_enum pin, const uint32 freq, const uint32 duty);

#endif

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
* 文件名称          zf_driver_PWM_MAP
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

#ifndef _zf_driver_PWM_MAP_h
#define _zf_driver_PWM_MAP_h

#include "ch32v30x_rcc.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x_tim.h"
#include "zf_common_debug.h"

typedef enum
{
    // MAP0  默认映射
    // MAP1  重映射
    // MAP2  部分映射
    // MAP3  完全映射

    // 同一个PWMP模块不同通道只能输出相同频率的PWM，占空比可设置不同
    // 例如PWM1_PWM_MAP_CH1_PA8与PWM1_PWM_MAP_CH3_PA10属于同一个模块，频率只能一样，但是占空比可以不一样

    //----------------定时器1----------------
    // 例如：PWM1_PWM_MAP_CH2_PA9与PWM1_PWM_MAP_CH1N_PB13不能一起使用。
    // 只允许TIM1_PWM_MAP0_CH1_A8 和  TIM1_PWM_MAP0_CH2_A9和 TIM1_PWM_MAP0_CH3_A10 和  TIM1_PWM_MAP0_CH4_A11 同组映射引脚一起使用

    // 以下为TIM1的PWM的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    TIM1_PWM_MAP0_CH1_A8  = 0x00000 | A8 ,				// 0x 0[TIM1] 0[MAP0] 0[CH1] 08[A8 ]
    TIM1_PWM_MAP0_CH2_A9  = 0x00100 | A9 ,				// 0x 0[TIM1] 0[MAP0] 1[CH2] 09[A9 ]
    TIM1_PWM_MAP0_CH3_A10 = 0x00200 | A10,				// 0x 0[TIM1] 0[MAP0] 2[CH3] 0A[A10]
    TIM1_PWM_MAP0_CH4_A11 = 0x00300 | A11,				// 0x 0[TIM1] 0[MAP0] 3[CH4] 0B[A11]

    // 以下为TIM1的PWM的一组映射引脚，不允许映射引脚混用。
    // 完全映射
    TIM1_PWM_MAP3_CH1_E9  = 0x03000 | E9 ,				// 0x 0[TIM1] 3[MAP3] 0[CH1] 69[E9 ]
    TIM1_PWM_MAP3_CH2_E11 = 0x03100 | E11,              // 0x 0[TIM1] 3[MAP3] 1[CH2] 6B[E11]
    TIM1_PWM_MAP3_CH3_E13 = 0x03200 | E13,              // 0x 0[TIM1] 3[MAP3] 2[CH3] 6D[E13]
    TIM1_PWM_MAP3_CH4_E14 = 0x03300 | E14,              // 0x 0[TIM1] 3[MAP3] 3[CH4] 6E[E14]

    //----------------定时器2----------------

    // 以下为TIM2的PWM的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    TIM2_PWM_MAP0_CH1_A0  = 0x10000 | A0,
    TIM2_PWM_MAP0_CH2_A1  = 0x10100 | A1,
    TIM2_PWM_MAP0_CH3_A2  = 0x10200 | A2,
    TIM2_PWM_MAP0_CH4_A3  = 0x10300 | A3,

    // 以下为TIM2的PWM的一组映射引脚，不允许映射引脚混用。
    // 重映射
    TIM2_PWM_MAP1_CH1_A15 = 0x11000 | A15,
    TIM2_PWM_MAP1_CH2_B3  = 0x11100 | B3 ,
    TIM2_PWM_MAP1_CH3_A2  = 0x11200 | A2 ,
    TIM2_PWM_MAP1_CH4_A3  = 0x11300 | A3 ,

    // 以下为TIM2的PWM的一组映射引脚，不允许映射引脚混用。
    // 部分映射
    TIM2_PWM_MAP2_CH1_A0  = 0x12000 | A0 ,
    TIM2_PWM_MAP2_CH2_A1  = 0x12100 | A1 ,
    TIM2_PWM_MAP2_CH3_B10 = 0x12200 | B10,              // 下载器默认串口，如果需要使用，则需要屏蔽默认串口初始化
    TIM2_PWM_MAP2_CH4_B11 = 0x12300 | B11,              // 下载器默认串口，如果需要使用，则需要屏蔽默认串口初始化

    // 以下为TIM2的PWM的一组映射引脚，不允许映射引脚混用。
    // 完全映射
    TIM2_PWM_MAP3_CH1_A15 = 0x13000 | A15,
    TIM2_PWM_MAP3_CH2_B3  = 0x13100 | B3 ,
    TIM2_PWM_MAP3_CH3_B10 = 0x13200 | B10,              // 下载器默认串口，如果需要使用，则需要屏蔽默认串口初始化
    TIM2_PWM_MAP3_CH4_B11 = 0x13300 | B11,              // 下载器默认串口，如果需要使用，则需要屏蔽默认串口初始化

    //----------------定时器3----------------

    // 以下为TIM3的PWM的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    TIM3_PWM_MAP0_CH1_A6  = 0x20000 | A6,
    TIM3_PWM_MAP0_CH2_A7  = 0x20100 | A7,
    TIM3_PWM_MAP0_CH3_B0  = 0x20200 | B0,
    TIM3_PWM_MAP0_CH4_B1  = 0x20300 | B1,

    // 以下为TIM3的PWM的一组映射引脚，不允许映射引脚混用。
    // 部分映射
    TIM3_PWM_MAP2_CH1_B4  = 0x22000 | B4,
    TIM3_PWM_MAP2_CH2_B5  = 0x22100 | B5,
    TIM3_PWM_MAP2_CH3_B0  = 0x22200 | B0,
    TIM3_PWM_MAP2_CH4_B1  = 0x22300 | B1,

    // 以下为TIM3的PWM的一组映射引脚，不允许映射引脚混用。
    // 完全映射
    TIM3_PWM_MAP3_CH1_C6  = 0x23000 | C6,
    TIM3_PWM_MAP3_CH2_C7  = 0x23100 | C7,
    TIM3_PWM_MAP3_CH3_C8  = 0x23200 | C8,
    TIM3_PWM_MAP3_CH4_C9  = 0x23300 | C9,

    //----------------定时器4----------------

    // 以下为TIM4的PWM的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    TIM4_PWM_MAP0_CH1_B6  = 0x30000 | B6,
    TIM4_PWM_MAP0_CH2_B7  = 0x30100 | B7,
    TIM4_PWM_MAP0_CH3_B8  = 0x30200 | B8,
    TIM4_PWM_MAP0_CH4_B9  = 0x30300 | B9,

    // 以下为TIM4的PWM的一组映射引脚，不允许映射引脚混用。
    //重映射
    TIM4_PWM_MAP1_CH1_D12 = 0x31000 | D12,
    TIM4_PWM_MAP1_CH2_D13 = 0x31100 | D13,
    TIM4_PWM_MAP1_CH3_D14 = 0x31200 | D14,
    TIM4_PWM_MAP1_CH4_D15 = 0x31300 | D15,

    //----------------定时器5----------------

    // 以下为TIM5的PWM的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    TIM5_PWM_MAP0_CH1_A0  = 0x40000 | A0,
    TIM5_PWM_MAP0_CH2_A1  = 0x40100 | A1,
    TIM5_PWM_MAP0_CH3_A2  = 0x40200 | A2,
    TIM5_PWM_MAP0_CH4_A3  = 0x40300 | A3,
						  
    //----------------定时器8----------------

    // 以下为TIM8的PWM的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    TIM8_PWM_MAP0_CH1_C6  = 0x70000 | C6,
    TIM8_PWM_MAP0_CH2_C7  = 0x70100 | C7,
    TIM8_PWM_MAP0_CH3_C8  = 0x70200 | C8,
    TIM8_PWM_MAP0_CH4_C9  = 0x70300 | C9,

    // 以下为TIM8的PWM的一组映射引脚，不允许映射引脚混用。
    //重映射
    TIM8_PWM_MAP1_CH1_B6  = 0x71000 | B6 ,
    TIM8_PWM_MAP1_CH2_B7  = 0x71100 | B7 ,
    TIM8_PWM_MAP1_CH3_B8  = 0x71200 | B8 ,
    TIM8_PWM_MAP1_CH4_C13 = 0x71300 | C13,

    //----------------定时器9----------------

    // 以下为TIM9的PWM的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    TIM9_PWM_MAP0_CH1_A2  = 0x80000 | A2,
    TIM9_PWM_MAP0_CH2_A3  = 0x80100 | A3,
    TIM9_PWM_MAP0_CH3_A4  = 0x80200 | A4,
    TIM9_PWM_MAP0_CH4_C4  = 0x80300 | C4,

    // 以下为TIM9的PWM的一组映射引脚，不允许映射引脚混用。
    // 完全映射
    TIM9_PWM_MAP3_CH1_D9  = 0x83000 | D9 ,
    TIM9_PWM_MAP3_CH2_D11 = 0x83100 | D11,
    TIM9_PWM_MAP3_CH3_D13 = 0x83200 | D13,
    TIM9_PWM_MAP3_CH4_D15 = 0x83300 | D15,

    //----------------定时器10----------------

    // 以下为TIM10的PWM的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    TIM10_PWM_MAP0_CH1_B8 = 0x90000 | B8 ,
    TIM10_PWM_MAP0_CH2_B9 = 0x90100 | B9 ,
    TIM10_PWM_MAP0_CH3_C3 = 0x90200 | C3 ,
    TIM10_PWM_MAP0_CH4_C11= 0x90300 | C11,

    // 以下为TIM10的PWM的一组映射引脚，不允许映射引脚混用。
    //部分映射
    TIM10_PWM_MAP1_CH1_B3 = 0x91000 | B3 ,
    TIM10_PWM_MAP1_CH2_B4 = 0x91100 | B4 ,
    TIM10_PWM_MAP1_CH3_B5 = 0x91200 | B5 ,
    TIM10_PWM_MAP1_CH4_C15= 0x91300 | C15,
	
    // 以下为TIM10的PWM的一组映射引脚，不允许映射引脚混用。
	//完全映射
    TIM10_PWM_MAP3_CH1_D1 = 0x93000 | D1,
    TIM10_PWM_MAP3_CH2_D3 = 0x93100 | D3,
    TIM10_PWM_MAP3_CH3_D5 = 0x93200 | D5,
    TIM10_PWM_MAP3_CH4_D7 = 0x93300 | D7,

}pwm_channel_enum;

#define PWM_DUTY_MAX 10000

void    pwm_set_duty    (pwm_channel_enum pin, uint32 duty);
void    pwm_set_freq    (pwm_channel_enum pin, uint32 freq, uint32 duty);
void    pwm_init        (pwm_channel_enum pin, uint32 freq, uint32 duty);

#endif

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
* 文件名称          zf_driver_encoder
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

#ifndef _zf_driver_encoder_h
#define _zf_driver_encoder_h

#include "ch32v30x_rcc.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x_tim.h"

#include "zf_common_debug.h"
#include "zf_common_typedef.h"

typedef enum    // TIMER引脚枚举
{
    // MAP0  默认映射
    // MAP1  重映射
    // MAP2  部分映射
    // MAP3  完全映射

    //----------定时器1----------
    // 以下为TIM1编码器的一组通道，不允许映射引脚混用。
    // 例如：TIM1_ENCOEDER_MAP_CH1_A8与TIM1_ENCOEDER_MAP_CH2_E11不能一起使用。
    // 只能是TIM1_ENCOEDER_MAP_CH1_A8与TIM1_ENCOEDER_MAP_CH2_A9 同组映射引脚一起使用，
    // 或者TIM1_ENCOEDER_MAP_CH1_E9与TIM1_ENCOEDER_MAP_CH2_E11  同组映射引脚一起使用
    // 默认映射
    TIM1_ENCOEDER_MAP0_CH1_A8  = 0x0000 | A8,        	// 0x 0[TIM1] 0[MAP0] 08[A8 ]
    TIM1_ENCOEDER_MAP0_CH2_A9  = 0x0000 | A9,        	// 0x 0[TIM1] 0[MAP0] 09[A9 ]

    // 以下为TIM1编码器的一组通道，不允许映射引脚混用。
    // 完全映射                                    	                
    TIM1_ENCOEDER_MAP3_CH1_E9  = 0x0300 | E9,        	// 0x 0[TIM1] 3[MAP3] 89[E9 ]
    TIM1_ENCOEDER_MAP3_CH2_E11 = 0x0300 | E11,       	// 0x 0[TIM1] 3[MAP3] 8B[E11]
																	
    //----------定时器2----------

    // 以下为TIM2编码器的一组通道，不允许映射引脚混用。
    // 默认映射	
    TIM2_ENCOEDER_MAP0_CH1_A0  = 0x1000 | A0,        	// 0x 1[TIM2] 0[MAP0] 00[A0 ]
    TIM2_ENCOEDER_MAP0_CH2_A1  = 0x1000 | A1,        	// 0x 1[TIM2] 0[MAP0] 01[A1 ]

    // 以下为TIM2编码器的一组通道，不允许映射引脚混用。
    // 重映射                                      	                
    TIM2_ENCOEDER_MAP1_CH1_A15 = 0x1100 | A15,       	// 0x 1[TIM2] 1[MAP1] 0F[A15]
    TIM2_ENCOEDER_MAP1_CH2_B3  = 0x1100 | B3,        	// 0x 1[TIM2] 1[MAP1] 23[B3 ]

    //----------定时器3----------

    // 以下为TIM3编码器的一组通道，不允许映射引脚混用。
    // 默认映射	
    TIM3_ENCOEDER_MAP0_CH1_A6  = 0x2000 | A6,        	// 0x 2[TIM3] 0[MAP0] 06[A6 ]
    TIM3_ENCOEDER_MAP0_CH2_A7  = 0x2000 | A7,        	// 0x 2[TIM3] 0[MAP0] 07[A7 ]

    // 以下为TIM3编码器的一组通道，不允许映射引脚混用。
    // 部分映射                                    	                
    TIM3_ENCOEDER_MAP2_CH1_B4  = 0x2200 | B4,        	// 0x 2[TIM3] 2[MAP2] 24[B4 ]
    TIM3_ENCOEDER_MAP2_CH2_B5  = 0x2200 | B5,        	// 0x 2[TIM3] 2[MAP2] 25[B5 ]

    // 以下为TIM3编码器的一组通道，不允许映射引脚混用。
    // 完全映射                                    	                
    TIM3_ENCOEDER_MAP3_CH1_C6  = 0x2300 | C6,        	// 0x 2[TIM3] 3[MAP3] 46[C6 ]
    TIM3_ENCOEDER_MAP3_CH2_C7  = 0x2300 | C7,        	// 0x 2[TIM3] 3[MAP3] 47[C7 ]

    //----------定时器4----------	

    // 以下为TIM4编码器的一组通道，不允许映射引脚混用。
    // 默认映射	
    TIM4_ENCOEDER_MAP0_CH1_B6  = 0x3000 | B6,        	// 0x 3[TIM4] 0[MAP0] 26[B6 ]
    TIM4_ENCOEDER_MAP0_CH2_B7  = 0x3000 | B7,        	// 0x 3[TIM4] 0[MAP0] 27[B7 ]

    // 以下为TIM4编码器的一组通道，不允许映射引脚混用。
    // 重定向                                      	                
    TIM4_ENCOEDER_MAP1_CH1_D12 = 0x3100 | D12,       	// 0x 3[TIM4] 1[MAP1] 6C[D12]
    TIM4_ENCOEDER_MAP1_CH2_D13 = 0x3100 | D13,       	// 0x 3[TIM4] 1[MAP1] 6D[D13]

    //----------定时器5----------

    // 以下为TIM5编码器的一组通道，不允许映射引脚混用。
    // 默认映射	
    TIM5_ENCOEDER_MAP0_CH1_A0  = 0x4000 | A0,        	// 0x 4[TIM5] 0[MAP0] 00[A0 ]
    TIM5_ENCOEDER_MAP0_CH2_A1  = 0x4000 | A1,        	// 0x 4[TIM5] 0[MAP0] 01[A1 ]
																	
    //----------定时器8----------

    // 以下为TIM8编码器的一组通道，不允许映射引脚混用。
    // 默认映射	
    TIM8_ENCOEDER_MAP0_CH1_C6  = 0x7000 | C6,        	// 0x 7[TIM8] 0[MAP0] 46[C6 ]
    TIM8_ENCOEDER_MAP0_CH2_C7  = 0x7000 | C7,        	// 0x 7[TIM8] 0[MAP0] 47[C7 ]

    // 以下为TIM8编码器的一组通道，不允许映射引脚混用。
    // 重映射                                      	                
    TIM8_ENCOEDER_MAP1_CH1_B6  = 0x7100 | B6,        	// 0x 7[TIM8] 1[MAP1] 26[B6 ]
    TIM8_ENCOEDER_MAP1_CH2_B7  = 0x7100 | B7,        	// 0x 7[TIM8] 1[MAP1] 27[B7 ]
																	
    //----------定时器9----------

    // 以下为TIM9编码器的一组通道，不允许映射引脚混用。
    // 默认映射	
    TIM9_ENCOEDER_MAP0_CH1_A2  = 0x8000 | A2,        	// 0x 8[TIM9] 0[MAP0] 02[A2 ]
    TIM9_ENCOEDER_MAP0_CH2_A3  = 0x8000 | A3,        	// 0x 8[TIM9] 0[MAP0] 03[A3 ]

    // 以下为TIM9编码器的一组通道，不允许映射引脚混用。
    // 完全映射                                    	                
    TIM9_ENCOEDER_MAP3_CH1_D9  = 0x8300 | D9,        	// 0x 8[TIM9] 3[MAP3] 69[D9 ]
    TIM9_ENCOEDER_MAP3_CH2_D11 = 0x8300 | D11,       	// 0x 8[TIM9] 3[MAP3] 6B[D11]
												
    //----------定时器10----------

    // 以下为TIM10编码器的一组通道，不允许映射引脚混用。
    // 默认映射	
    TIM10_ENCOEDER_MAP0_CH1_B8 = 0x9000 | B8,        	// 0x 9[TIM10] 0[MAP0] 28[B8]
    TIM10_ENCOEDER_MAP0_CH2_B9 = 0x9000 | B9,        	// 0x 9[TIM10] 0[MAP0] 29[B9]

    // 以下为TIM10编码器的一组通道，不允许映射引脚混用。
    // 部分映射
    TIM10_ENCOEDER_MAP1_CH1_B3 = 0x9100 | B3,           // 0x 9[TIM10] 1[MAP1] 23[B3]
    TIM10_ENCOEDER_MAP1_CH2_B4 = 0x9100 | B4,           // 0x 9[TIM10] 1[MAP1] 24[B4]

    // 以下为TIM10编码器的一组通道，不允许映射引脚混用。
    // 完全映射
    TIM10_ENCOEDER_MAP3_CH1_D1 = 0x9300 | D1,           // 0x 9[TIM10] 3[MAP3] 41[D1]
    TIM10_ENCOEDER_MAP3_CH2_D3 = 0x9300 | D3,           // 0x 9[TIM10] 3[MAP3] 43[D3]

}encoder_channel_enum;


typedef enum
{
    TIM1_ENCOEDER = 0,
    TIM2_ENCOEDER,
    TIM3_ENCOEDER,
    TIM4_ENCOEDER,
    TIM5_ENCOEDER,
    TIM8_ENCOEDER = 7,
    TIM9_ENCOEDER,
    TIM10_ENCOEDER,
}encoder_index_enum;

int16   encoder_get_count   (encoder_index_enum encoder_n);
void    encoder_clear_count (encoder_index_enum encoder_n);
void    encoder_quad_init   (encoder_index_enum encoder_n, encoder_channel_enum ch1_pin, encoder_channel_enum ch2_pin);
void    encoder_dir_init    (encoder_index_enum encoder_n, encoder_channel_enum ch1_pin, encoder_channel_enum ch2_pin);

#endif

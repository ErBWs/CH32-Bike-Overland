/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          zf_driver_encoder
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-09-15        ��W            first version
********************************************************************************************************************/

#ifndef _zf_driver_encoder_h
#define _zf_driver_encoder_h

#include "ch32v30x_rcc.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x_tim.h"

#include "zf_common_debug.h"
#include "zf_common_typedef.h"

typedef enum    // TIMER����ö��
{
    // MAP0  Ĭ��ӳ��
    // MAP1  ��ӳ��
    // MAP2  ����ӳ��
    // MAP3  ��ȫӳ��

    //----------��ʱ��1----------
    // ����ΪTIM1��������һ��ͨ����������ӳ�����Ż��á�
    // ���磺TIM1_ENCOEDER_MAP_CH1_A8��TIM1_ENCOEDER_MAP_CH2_E11����һ��ʹ�á�
    // ֻ����TIM1_ENCOEDER_MAP_CH1_A8��TIM1_ENCOEDER_MAP_CH2_A9 ͬ��ӳ������һ��ʹ�ã�
    // ����TIM1_ENCOEDER_MAP_CH1_E9��TIM1_ENCOEDER_MAP_CH2_E11  ͬ��ӳ������һ��ʹ��
    // Ĭ��ӳ��
    TIM1_ENCOEDER_MAP0_CH1_A8  = 0x0000 | A8,        	// 0x 0[TIM1] 0[MAP0] 08[A8 ]
    TIM1_ENCOEDER_MAP0_CH2_A9  = 0x0000 | A9,        	// 0x 0[TIM1] 0[MAP0] 09[A9 ]

    // ����ΪTIM1��������һ��ͨ����������ӳ�����Ż��á�
    // ��ȫӳ��                                    	                
    TIM1_ENCOEDER_MAP3_CH1_E9  = 0x0300 | E9,        	// 0x 0[TIM1] 3[MAP3] 89[E9 ]
    TIM1_ENCOEDER_MAP3_CH2_E11 = 0x0300 | E11,       	// 0x 0[TIM1] 3[MAP3] 8B[E11]
																	
    //----------��ʱ��2----------

    // ����ΪTIM2��������һ��ͨ����������ӳ�����Ż��á�
    // Ĭ��ӳ��	
    TIM2_ENCOEDER_MAP0_CH1_A0  = 0x1000 | A0,        	// 0x 1[TIM2] 0[MAP0] 00[A0 ]
    TIM2_ENCOEDER_MAP0_CH2_A1  = 0x1000 | A1,        	// 0x 1[TIM2] 0[MAP0] 01[A1 ]

    // ����ΪTIM2��������һ��ͨ����������ӳ�����Ż��á�
    // ��ӳ��                                      	                
    TIM2_ENCOEDER_MAP1_CH1_A15 = 0x1100 | A15,       	// 0x 1[TIM2] 1[MAP1] 0F[A15]
    TIM2_ENCOEDER_MAP1_CH2_B3  = 0x1100 | B3,        	// 0x 1[TIM2] 1[MAP1] 23[B3 ]

    //----------��ʱ��3----------

    // ����ΪTIM3��������һ��ͨ����������ӳ�����Ż��á�
    // Ĭ��ӳ��	
    TIM3_ENCOEDER_MAP0_CH1_A6  = 0x2000 | A6,        	// 0x 2[TIM3] 0[MAP0] 06[A6 ]
    TIM3_ENCOEDER_MAP0_CH2_A7  = 0x2000 | A7,        	// 0x 2[TIM3] 0[MAP0] 07[A7 ]

    // ����ΪTIM3��������һ��ͨ����������ӳ�����Ż��á�
    // ����ӳ��                                    	                
    TIM3_ENCOEDER_MAP2_CH1_B4  = 0x2200 | B4,        	// 0x 2[TIM3] 2[MAP2] 24[B4 ]
    TIM3_ENCOEDER_MAP2_CH2_B5  = 0x2200 | B5,        	// 0x 2[TIM3] 2[MAP2] 25[B5 ]

    // ����ΪTIM3��������һ��ͨ����������ӳ�����Ż��á�
    // ��ȫӳ��                                    	                
    TIM3_ENCOEDER_MAP3_CH1_C6  = 0x2300 | C6,        	// 0x 2[TIM3] 3[MAP3] 46[C6 ]
    TIM3_ENCOEDER_MAP3_CH2_C7  = 0x2300 | C7,        	// 0x 2[TIM3] 3[MAP3] 47[C7 ]

    //----------��ʱ��4----------	

    // ����ΪTIM4��������һ��ͨ����������ӳ�����Ż��á�
    // Ĭ��ӳ��	
    TIM4_ENCOEDER_MAP0_CH1_B6  = 0x3000 | B6,        	// 0x 3[TIM4] 0[MAP0] 26[B6 ]
    TIM4_ENCOEDER_MAP0_CH2_B7  = 0x3000 | B7,        	// 0x 3[TIM4] 0[MAP0] 27[B7 ]

    // ����ΪTIM4��������һ��ͨ����������ӳ�����Ż��á�
    // �ض���                                      	                
    TIM4_ENCOEDER_MAP1_CH1_D12 = 0x3100 | D12,       	// 0x 3[TIM4] 1[MAP1] 6C[D12]
    TIM4_ENCOEDER_MAP1_CH2_D13 = 0x3100 | D13,       	// 0x 3[TIM4] 1[MAP1] 6D[D13]

    //----------��ʱ��5----------

    // ����ΪTIM5��������һ��ͨ����������ӳ�����Ż��á�
    // Ĭ��ӳ��	
    TIM5_ENCOEDER_MAP0_CH1_A0  = 0x4000 | A0,        	// 0x 4[TIM5] 0[MAP0] 00[A0 ]
    TIM5_ENCOEDER_MAP0_CH2_A1  = 0x4000 | A1,        	// 0x 4[TIM5] 0[MAP0] 01[A1 ]
																	
    //----------��ʱ��8----------

    // ����ΪTIM8��������һ��ͨ����������ӳ�����Ż��á�
    // Ĭ��ӳ��	
    TIM8_ENCOEDER_MAP0_CH1_C6  = 0x7000 | C6,        	// 0x 7[TIM8] 0[MAP0] 46[C6 ]
    TIM8_ENCOEDER_MAP0_CH2_C7  = 0x7000 | C7,        	// 0x 7[TIM8] 0[MAP0] 47[C7 ]

    // ����ΪTIM8��������һ��ͨ����������ӳ�����Ż��á�
    // ��ӳ��                                      	                
    TIM8_ENCOEDER_MAP1_CH1_B6  = 0x7100 | B6,        	// 0x 7[TIM8] 1[MAP1] 26[B6 ]
    TIM8_ENCOEDER_MAP1_CH2_B7  = 0x7100 | B7,        	// 0x 7[TIM8] 1[MAP1] 27[B7 ]
																	
    //----------��ʱ��9----------

    // ����ΪTIM9��������һ��ͨ����������ӳ�����Ż��á�
    // Ĭ��ӳ��	
    TIM9_ENCOEDER_MAP0_CH1_A2  = 0x8000 | A2,        	// 0x 8[TIM9] 0[MAP0] 02[A2 ]
    TIM9_ENCOEDER_MAP0_CH2_A3  = 0x8000 | A3,        	// 0x 8[TIM9] 0[MAP0] 03[A3 ]

    // ����ΪTIM9��������һ��ͨ����������ӳ�����Ż��á�
    // ��ȫӳ��                                    	                
    TIM9_ENCOEDER_MAP3_CH1_D9  = 0x8300 | D9,        	// 0x 8[TIM9] 3[MAP3] 69[D9 ]
    TIM9_ENCOEDER_MAP3_CH2_D11 = 0x8300 | D11,       	// 0x 8[TIM9] 3[MAP3] 6B[D11]
												
    //----------��ʱ��10----------

    // ����ΪTIM10��������һ��ͨ����������ӳ�����Ż��á�
    // Ĭ��ӳ��	
    TIM10_ENCOEDER_MAP0_CH1_B8 = 0x9000 | B8,        	// 0x 9[TIM10] 0[MAP0] 28[B8]
    TIM10_ENCOEDER_MAP0_CH2_B9 = 0x9000 | B9,        	// 0x 9[TIM10] 0[MAP0] 29[B9]

    // ����ΪTIM10��������һ��ͨ����������ӳ�����Ż��á�
    // ����ӳ��
    TIM10_ENCOEDER_MAP1_CH1_B3 = 0x9100 | B3,           // 0x 9[TIM10] 1[MAP1] 23[B3]
    TIM10_ENCOEDER_MAP1_CH2_B4 = 0x9100 | B4,           // 0x 9[TIM10] 1[MAP1] 24[B4]

    // ����ΪTIM10��������һ��ͨ����������ӳ�����Ż��á�
    // ��ȫӳ��
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

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
* �ļ�����          zf_driver_PWM_MAP
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

#ifndef _zf_driver_PWM_MAP_h
#define _zf_driver_PWM_MAP_h

#include "ch32v30x_rcc.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x_tim.h"
#include "zf_common_debug.h"

typedef enum
{
    // MAP0  Ĭ��ӳ��
    // MAP1  ��ӳ��
    // MAP2  ����ӳ��
    // MAP3  ��ȫӳ��

    // ͬһ��PWMPģ�鲻ͬͨ��ֻ�������ͬƵ�ʵ�PWM��ռ�ձȿ����ò�ͬ
    // ����PWM1_PWM_MAP_CH1_PA8��PWM1_PWM_MAP_CH3_PA10����ͬһ��ģ�飬Ƶ��ֻ��һ��������ռ�ձȿ��Բ�һ��

    //----------------��ʱ��1----------------
    // ���磺PWM1_PWM_MAP_CH2_PA9��PWM1_PWM_MAP_CH1N_PB13����һ��ʹ�á�
    // ֻ����TIM1_PWM_MAP0_CH1_A8 ��  TIM1_PWM_MAP0_CH2_A9�� TIM1_PWM_MAP0_CH3_A10 ��  TIM1_PWM_MAP0_CH4_A11 ͬ��ӳ������һ��ʹ��

    // ����ΪTIM1��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    TIM1_PWM_MAP0_CH1_A8  = 0x00000 | A8 ,				// 0x 0[TIM1] 0[MAP0] 0[CH1] 08[A8 ]
    TIM1_PWM_MAP0_CH2_A9  = 0x00100 | A9 ,				// 0x 0[TIM1] 0[MAP0] 1[CH2] 09[A9 ]
    TIM1_PWM_MAP0_CH3_A10 = 0x00200 | A10,				// 0x 0[TIM1] 0[MAP0] 2[CH3] 0A[A10]
    TIM1_PWM_MAP0_CH4_A11 = 0x00300 | A11,				// 0x 0[TIM1] 0[MAP0] 3[CH4] 0B[A11]

    // ����ΪTIM1��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��
    TIM1_PWM_MAP3_CH1_E9  = 0x03000 | E9 ,				// 0x 0[TIM1] 3[MAP3] 0[CH1] 69[E9 ]
    TIM1_PWM_MAP3_CH2_E11 = 0x03100 | E11,              // 0x 0[TIM1] 3[MAP3] 1[CH2] 6B[E11]
    TIM1_PWM_MAP3_CH3_E13 = 0x03200 | E13,              // 0x 0[TIM1] 3[MAP3] 2[CH3] 6D[E13]
    TIM1_PWM_MAP3_CH4_E14 = 0x03300 | E14,              // 0x 0[TIM1] 3[MAP3] 3[CH4] 6E[E14]

    //----------------��ʱ��2----------------

    // ����ΪTIM2��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    TIM2_PWM_MAP0_CH1_A0  = 0x10000 | A0,
    TIM2_PWM_MAP0_CH2_A1  = 0x10100 | A1,
    TIM2_PWM_MAP0_CH3_A2  = 0x10200 | A2,
    TIM2_PWM_MAP0_CH4_A3  = 0x10300 | A3,

    // ����ΪTIM2��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ӳ��
    TIM2_PWM_MAP1_CH1_A15 = 0x11000 | A15,
    TIM2_PWM_MAP1_CH2_B3  = 0x11100 | B3 ,
    TIM2_PWM_MAP1_CH3_A2  = 0x11200 | A2 ,
    TIM2_PWM_MAP1_CH4_A3  = 0x11300 | A3 ,

    // ����ΪTIM2��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ����ӳ��
    TIM2_PWM_MAP2_CH1_A0  = 0x12000 | A0 ,
    TIM2_PWM_MAP2_CH2_A1  = 0x12100 | A1 ,
    TIM2_PWM_MAP2_CH3_B10 = 0x12200 | B10,              // ������Ĭ�ϴ��ڣ������Ҫʹ�ã�����Ҫ����Ĭ�ϴ��ڳ�ʼ��
    TIM2_PWM_MAP2_CH4_B11 = 0x12300 | B11,              // ������Ĭ�ϴ��ڣ������Ҫʹ�ã�����Ҫ����Ĭ�ϴ��ڳ�ʼ��

    // ����ΪTIM2��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��
    TIM2_PWM_MAP3_CH1_A15 = 0x13000 | A15,
    TIM2_PWM_MAP3_CH2_B3  = 0x13100 | B3 ,
    TIM2_PWM_MAP3_CH3_B10 = 0x13200 | B10,              // ������Ĭ�ϴ��ڣ������Ҫʹ�ã�����Ҫ����Ĭ�ϴ��ڳ�ʼ��
    TIM2_PWM_MAP3_CH4_B11 = 0x13300 | B11,              // ������Ĭ�ϴ��ڣ������Ҫʹ�ã�����Ҫ����Ĭ�ϴ��ڳ�ʼ��

    //----------------��ʱ��3----------------

    // ����ΪTIM3��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    TIM3_PWM_MAP0_CH1_A6  = 0x20000 | A6,
    TIM3_PWM_MAP0_CH2_A7  = 0x20100 | A7,
    TIM3_PWM_MAP0_CH3_B0  = 0x20200 | B0,
    TIM3_PWM_MAP0_CH4_B1  = 0x20300 | B1,

    // ����ΪTIM3��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ����ӳ��
    TIM3_PWM_MAP2_CH1_B4  = 0x22000 | B4,
    TIM3_PWM_MAP2_CH2_B5  = 0x22100 | B5,
    TIM3_PWM_MAP2_CH3_B0  = 0x22200 | B0,
    TIM3_PWM_MAP2_CH4_B1  = 0x22300 | B1,

    // ����ΪTIM3��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��
    TIM3_PWM_MAP3_CH1_C6  = 0x23000 | C6,
    TIM3_PWM_MAP3_CH2_C7  = 0x23100 | C7,
    TIM3_PWM_MAP3_CH3_C8  = 0x23200 | C8,
    TIM3_PWM_MAP3_CH4_C9  = 0x23300 | C9,

    //----------------��ʱ��4----------------

    // ����ΪTIM4��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    TIM4_PWM_MAP0_CH1_B6  = 0x30000 | B6,
    TIM4_PWM_MAP0_CH2_B7  = 0x30100 | B7,
    TIM4_PWM_MAP0_CH3_B8  = 0x30200 | B8,
    TIM4_PWM_MAP0_CH4_B9  = 0x30300 | B9,

    // ����ΪTIM4��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    //��ӳ��
    TIM4_PWM_MAP1_CH1_D12 = 0x31000 | D12,
    TIM4_PWM_MAP1_CH2_D13 = 0x31100 | D13,
    TIM4_PWM_MAP1_CH3_D14 = 0x31200 | D14,
    TIM4_PWM_MAP1_CH4_D15 = 0x31300 | D15,

    //----------------��ʱ��5----------------

    // ����ΪTIM5��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    TIM5_PWM_MAP0_CH1_A0  = 0x40000 | A0,
    TIM5_PWM_MAP0_CH2_A1  = 0x40100 | A1,
    TIM5_PWM_MAP0_CH3_A2  = 0x40200 | A2,
    TIM5_PWM_MAP0_CH4_A3  = 0x40300 | A3,
						  
    //----------------��ʱ��8----------------

    // ����ΪTIM8��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    TIM8_PWM_MAP0_CH1_C6  = 0x70000 | C6,
    TIM8_PWM_MAP0_CH2_C7  = 0x70100 | C7,
    TIM8_PWM_MAP0_CH3_C8  = 0x70200 | C8,
    TIM8_PWM_MAP0_CH4_C9  = 0x70300 | C9,

    // ����ΪTIM8��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    //��ӳ��
    TIM8_PWM_MAP1_CH1_B6  = 0x71000 | B6 ,
    TIM8_PWM_MAP1_CH2_B7  = 0x71100 | B7 ,
    TIM8_PWM_MAP1_CH3_B8  = 0x71200 | B8 ,
    TIM8_PWM_MAP1_CH4_C13 = 0x71300 | C13,

    //----------------��ʱ��9----------------

    // ����ΪTIM9��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    TIM9_PWM_MAP0_CH1_A2  = 0x80000 | A2,
    TIM9_PWM_MAP0_CH2_A3  = 0x80100 | A3,
    TIM9_PWM_MAP0_CH3_A4  = 0x80200 | A4,
    TIM9_PWM_MAP0_CH4_C4  = 0x80300 | C4,

    // ����ΪTIM9��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // ��ȫӳ��
    TIM9_PWM_MAP3_CH1_D9  = 0x83000 | D9 ,
    TIM9_PWM_MAP3_CH2_D11 = 0x83100 | D11,
    TIM9_PWM_MAP3_CH3_D13 = 0x83200 | D13,
    TIM9_PWM_MAP3_CH4_D15 = 0x83300 | D15,

    //----------------��ʱ��10----------------

    // ����ΪTIM10��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    // Ĭ��ӳ��
    TIM10_PWM_MAP0_CH1_B8 = 0x90000 | B8 ,
    TIM10_PWM_MAP0_CH2_B9 = 0x90100 | B9 ,
    TIM10_PWM_MAP0_CH3_C3 = 0x90200 | C3 ,
    TIM10_PWM_MAP0_CH4_C11= 0x90300 | C11,

    // ����ΪTIM10��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
    //����ӳ��
    TIM10_PWM_MAP1_CH1_B3 = 0x91000 | B3 ,
    TIM10_PWM_MAP1_CH2_B4 = 0x91100 | B4 ,
    TIM10_PWM_MAP1_CH3_B5 = 0x91200 | B5 ,
    TIM10_PWM_MAP1_CH4_C15= 0x91300 | C15,
	
    // ����ΪTIM10��PWM��һ��ӳ�����ţ�������ӳ�����Ż��á�
	//��ȫӳ��
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

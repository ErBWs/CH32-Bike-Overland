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
* �ļ�����          zf_driver_adc
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

#ifndef _zf_driver_adc_h
#define _zf_driver_adc_h

#include "zf_driver_gpio.h"
#include "zf_common_typedef.h"
//CH32V307ֻ��һ��ADC�����Է�ʱ�����ںܶ��ͨ������


//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
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


//��ö�ٶ��岻�����û��޸�
typedef enum            // ö��ADCͨ��
{
    ADC_8BIT  = 4,      //8λ�ֱ���
    ADC_9BIT  = 3,      //9λ�ֱ���
    ADC_10BIT = 2,      //10λ�ֱ���
    ADC_11BIT = 1,      //11λ�ֱ���
    ADC_12BIT = 0,      //12λ�ֱ���
}adc_resolution_enum;




uint16  adc_convert             (adc_channel_enum ch);
uint16  adc_mean_filter_convert (adc_channel_enum ch, const uint8 count);
void    adc_init                (adc_channel_enum ch, adc_resolution_enum resolution);


#endif

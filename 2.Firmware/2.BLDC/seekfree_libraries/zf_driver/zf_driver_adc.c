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

#include "ch32v30x.h"
#include "ch32v30x_adc.h"

#include "zf_driver_adc.h"
#include "zf_driver_gpio.h"

#include "zf_common_debug.h"


static  ADC_TypeDef    *adc_index[2]        = {ADC1, ADC2};
static  uint8           adc_resolution[2]   = {ADC_12BIT, ADC_12BIT};


//-------------------------------------------------------------------------------------------------------------------
// �������     ADCת��һ��
// ����˵��     ch              ѡ��ADCͨ��
// ����˵��     resolution      �ֱ���(8λ 10λ 12λ)
// ���ز���     void
// ʹ��ʾ��     adc_convert(ADC_IN0_A0, ADC_8BIT);  //�ɼ�A0�˿ڷ���8λ�ֱ��ʵ�ADֵ
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_convert (adc_channel_enum ch)
{
    uint8 adc = ((ch & 0xF000) >> 12);
    uint8 adc_ch = (uint8)(ch >> 8) & 0xF;

    ADC_RegularChannelConfig(adc_index[adc], adc_ch, 1, ADC_SampleTime_41Cycles5);  // ʹ�ܶ�Ӧͨ��
    ADC_SoftwareStartConvCmd(adc_index[adc], ENABLE);                               // ��ʼ����ת��
    while(!ADC_GetFlagStatus(adc_index[adc], ADC_FLAG_EOC ));                       // �ȴ�����ת�����
    return ((adc_index[adc]->RDATAR) >> adc_resolution[adc]);                       // ��ȡ����
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ADCת��N�Σ�ƽ��ֵ�˲�
// ����˵��     ch              ѡ��ADCͨ��
// ����˵��     resolution      �ֱ���(8λ 10λ 12λ)
// ����˵��     count           ת������
// ���ز���     void
// ʹ��ʾ��     adc_mean_filter(ADC_IN0_A0, ADC_8BIT,5);  //�ɼ�A0�˿ڷ���8λ�ֱ��ʵ�ADֵ���ɼ����ȡƽ��ֵ
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_mean_filter_convert (adc_channel_enum ch, const uint8 count)
{
    uint8 i;
    uint32 sum;

    zf_assert(count);//���Դ�������Ϊ0

    sum = 0;
    for(i=0; i<count; i++)
    {
        sum += adc_convert(ch);
    }

    sum = sum/count;
    return sum;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ADC��ʼ��
// ����˵��     adc_ch      adc_chͨ��(��ѡ��Χ��zf_adc.h��ADC_CH_enumö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��    adc_init(ADC_IN0_A0);//��ʼ��A0����ΪADC����
//-------------------------------------------------------------------------------------------------------------------
void adc_init (adc_channel_enum ch, adc_resolution_enum resolution)
{
    ADC_InitTypeDef ADC_InitStructure = {0};

    uint8 adc = ((ch & 0xF000) >> 12);
    gpio_init(ch&0xFF, GPI, 0, GPI_ANAOG_IN);                           // GPIO��ʼ��

    if(adc == 0)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE );          // ʹ��ADC1ͨ��ʱ��
    }
    else if(adc == 1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 , ENABLE );          // ʹ��ADC2ͨ��ʱ��
    }

    RCC_ADCCLKConfig(RCC_PCLK2_Div2);


//    if(system_clock > 84000000)  RCC_ADCCLKConfig(RCC_PCLK2_Div8);    // ����ADC��Ƶ���ӣ�ADC������ʲ��ܳ���14M
//    else RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(adc_index[adc]);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  // ADC����ģʽ:ADC1�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       // ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                 // ģ��ת�������ڵ���ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // ת��������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              // ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;                             // ˳����й���ת����ADCͨ������Ŀ
    ADC_Init(adc_index[adc], &ADC_InitStructure);                       // ����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

    ADC_Cmd(adc_index[adc], ENABLE);                                    // ʹ��ָ����ADC1
    ADC_BufferCmd(adc_index[adc], DISABLE);                             // disable buffer

    ADC_ResetCalibration(adc_index[adc]);                               // ʹ�ܸ�λУ׼
    while(ADC_GetResetCalibrationStatus(adc_index[adc]));               // �ȴ���λУ׼����
    ADC_StartCalibration(adc_index[adc]);                               // ����ADУ׼
    while(ADC_GetCalibrationStatus(adc_index[adc]));                    // �ȴ�У׼����
    //ADC_BufferCmd(ADC1, ENABLE);                                      // enable buffer

    adc_resolution[adc] = resolution;                                   // ��¼ADC���� ���ڲɼ�ʱʹ��
}

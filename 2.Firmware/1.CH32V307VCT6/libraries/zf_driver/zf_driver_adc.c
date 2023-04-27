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

#include "ch32v30x.h"
#include "ch32v30x_adc.h"

#include "zf_driver_adc.h"
#include "zf_driver_gpio.h"

#include "zf_common_debug.h"


static  ADC_TypeDef    *adc_index[2]        = {ADC1, ADC2};
static  uint8           adc_resolution[2]   = {ADC_12BIT, ADC_12BIT};


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ADC转换一次
// 参数说明     ch              选择ADC通道
// 参数说明     resolution      分辨率(8位 10位 12位)
// 返回参数     void
// 使用示例     adc_convert(ADC_IN0_A0, ADC_8BIT);  //采集A0端口返回8位分辨率的AD值
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_convert (adc_channel_enum ch)
{
    uint8 adc = ((ch & 0xF000) >> 12);
    uint8 adc_ch = (uint8)(ch >> 8) & 0xF;

    ADC_RegularChannelConfig(adc_index[adc], adc_ch, 1, ADC_SampleTime_41Cycles5);  // 使能对应通道
    ADC_SoftwareStartConvCmd(adc_index[adc], ENABLE);                               // 开始数据转换
    while(!ADC_GetFlagStatus(adc_index[adc], ADC_FLAG_EOC ));                       // 等待数据转换完成
    return ((adc_index[adc]->RDATAR) >> adc_resolution[adc]);                       // 读取数据
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ADC转换N次，平均值滤波
// 参数说明     ch              选择ADC通道
// 参数说明     resolution      分辨率(8位 10位 12位)
// 参数说明     count           转换次数
// 返回参数     void
// 使用示例     adc_mean_filter(ADC_IN0_A0, ADC_8BIT,5);  //采集A0端口返回8位分辨率的AD值，采集五次取平均值
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_mean_filter_convert (adc_channel_enum ch, const uint8 count)
{
    uint8 i;
    uint32 sum;

    zf_assert(count);//断言次数不能为0

    sum = 0;
    for(i=0; i<count; i++)
    {
        sum += adc_convert(ch);
    }

    sum = sum/count;
    return sum;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ADC初始化
// 参数说明     adc_ch      adc_ch通道(可选择范围由zf_adc.h内ADC_CH_enum枚举值确定)
// 返回参数     void
// 使用示例    adc_init(ADC_IN0_A0);//初始化A0引脚为ADC功能
//-------------------------------------------------------------------------------------------------------------------
void adc_init (adc_channel_enum ch, adc_resolution_enum resolution)
{
    ADC_InitTypeDef ADC_InitStructure = {0};

    uint8 adc = ((ch & 0xF000) >> 12);
    gpio_init(ch&0xFF, GPI, 0, GPI_ANAOG_IN);                           // GPIO初始化

    if(adc == 0)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE );          // 使能ADC1通道时钟
    }
    else if(adc == 1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 , ENABLE );          // 使能ADC2通道时钟
    }

    RCC_ADCCLKConfig(RCC_PCLK2_Div8);


//    if(system_clock > 84000000)  RCC_ADCCLKConfig(RCC_PCLK2_Div8);    // 设置ADC分频因子，ADC最大速率不能超过14M
//    else RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    ADC_DeInit(adc_index[adc]);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  // ADC工作模式:ADC1工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       // 模数转换工作在单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                 // 模数转换工作在单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              // ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;                             // 顺序进行规则转换的ADC通道的数目
    ADC_Init(adc_index[adc], &ADC_InitStructure);                       // 根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

    ADC_Cmd(adc_index[adc], ENABLE);                                    // 使能指定的ADC1
    ADC_BufferCmd(adc_index[adc], DISABLE);                             // disable buffer

    ADC_ResetCalibration(adc_index[adc]);                               // 使能复位校准
    while(ADC_GetResetCalibrationStatus(adc_index[adc]));               // 等待复位校准结束
    ADC_StartCalibration(adc_index[adc]);                               // 开启AD校准
    while(ADC_GetCalibrationStatus(adc_index[adc]));                    // 等待校准结束
    //ADC_BufferCmd(ADC1, ENABLE);                                      // enable buffer

    adc_resolution[adc] = resolution;                                   // 记录ADC精度 将在采集时使用
}

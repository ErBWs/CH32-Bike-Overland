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
* 文件名称          zf_driver_adc
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

#include "hal_rcc.h"
#include "zf_common_clock.h"
#include "zf_driver_gpio.h"

#include "zf_driver_adc.h"

static  ADC_Type    *adc_index[2]       = {ADC1, ADC2};                         // 模块索引数组
static  uint8       adc_resolution[2]   = {ADC_12BIT, ADC_12BIT};               // 精度数据备份

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     adc 转换数据
// 参数说明     ch              选择 adc 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 返回参数     uint16          转换的 adc 值
// 使用示例     adc_convert(ADC1_CH0_A0);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_convert (adc_channel_enum ch)
{
    uint32_t flag = ((ch & 0xFF0) >> 4);                                        // 不要问为什么新建变量
    uint32_t data = 0;                                                          // 读取数据缓冲区

    ADC_EnableSeqSlot(adc_index[(ch & 0x0F)], 0, flag);
    ADC_DoSwTrigger(adc_index[(ch & 0x0F)], true);                              // 启动转换
    while((ADC_STATUS_CONV_SLOT_DONE | ADC_STATUS_CONV_SAMPLE_DONE) !=
        (ADC_GetStatus(adc_index[(ch & 0x0F)]) & (ADC_STATUS_CONV_SLOT_DONE | ADC_STATUS_CONV_SAMPLE_DONE)));
    ADC_ClearStatus(adc_index[(ch & 0x0F)], (ADC_STATUS_CONV_SLOT_DONE | ADC_STATUS_CONV_SAMPLE_DONE));
    data = ADC_GetSlotConvResult(adc_index[(ch & 0x0F)], 0, &flag);             // 显而易见 这是读取结果
    return (data >> adc_resolution[(ch & 0x0F)]);                               // 根据精度输出对应位数数据
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     adc 均值滤波转换
// 参数说明     ch              选择 adc 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 参数说明     count           均值滤波次数
// 返回参数     uint16          转换的 adc 值
// 使用示例     adc_mean_filter_convert(ADC1_CH0_A0, 5);                        // 采集5次 然后返回平均值
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_mean_filter_convert (adc_channel_enum ch, const uint8 count)
{
    uint8 i = 0;
    uint32 sum = 0;

    for(i = 0; i < count; i ++)
    {
        sum += adc_convert(ch);
    }

    return sum / count;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     adc 初始化
// 参数说明     ch              选择 adc 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 参数说明     resolution      选择选择通道分辨率(如果同一个 adc 模块初始化时设置了不同的分辨率 则最后一个初始化的分辨率生效)
// 返回参数     void
// 使用示例     adc_init(ADC1_CH0_A0, ADC_8BIT);                                // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void adc_init (adc_channel_enum ch, adc_resolution_enum resolution)
{
    if(ADC2_CH17_TEMP != ch && ADC2_CH18_VS != ch)                              // 确认是引脚通道
    {
        gpio_init((gpio_pin_enum)((ch & 0xFFF000) >> 12), GPI, GPIO_LOW, GPI_ANAOG_IN);
    }

    if(0x00 == (ch & 0x0F))
    {
        RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_ADC1, true);                      // 使能 ADC1 时钟
    }
    else
    {
        RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_ADC2, true);                      // 使能 ADC2 时钟
    }

    ADC_Init_Type adc_init;
    adc_resolution[(ch & 0x0F)] = resolution;                                   // 先备份精度
    adc_init.Resolution = (ADC_Resolution_Type)resolution;                      // 精度设定
    adc_init.ConvMode = ADC_ConvMode_SingleSlot;                                // 单次转换
    adc_init.Align = ADC_Align_Right;                                           // 数据右对齐
    ADC_Init(adc_index[(ch & 0x0F)], &adc_init);                                // 按照上述配置初始化 ADC

    if(ADC2_CH17_TEMP == ch)
    {
        ADC_EnableTempSensor(adc_index[(ch & 0x0F)], true);                     // 温度传感器使能
    }
    if(ADC2_CH18_VS == ch)
    {
        ADC_EnableVoltSensor(adc_index[(ch & 0x0F)], true);                     // 内部参考电压使能
    }

    ADC_Enable(adc_index[(ch & 0x0F)], true);                                   // 使能 ADC
    ADC_DoAutoCalib(adc_index[(ch & 0x0F)]);                                    // 进行 ADC 硬件自校准
}

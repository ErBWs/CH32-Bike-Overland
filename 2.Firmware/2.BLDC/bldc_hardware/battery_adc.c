#include "bldc_config.h"
#include "battery_adc.h"
#include "zf_common_headfile.h"


battery_struct battery_information;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取电池ADC信息
//  @param      void
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void battery_adc_read(void)
{
    static uint16 low_voltage_num;
    static uint16 adc_time;
    uint16 battery_adc_value;
    adc_time++;

    // 读取电池ADC值
    battery_adc_value = adc_convert(battery_information.adc_pin);
    // 转换为电池电压，12位的ADC，5.7倍的放大倍数
    battery_information.voltage = (uint16) ((float)battery_adc_value / 4095 * 3300 * 5.7);

    // 电池类型无效时 则进行判断
    if((BATTERY_INVALID == battery_information.type) && (1000 < adc_time))
    {
        if(9000 > battery_information.voltage)
        {
            battery_information.type = BATTERY_2S;
        }
        else if(13000 > battery_information.voltage)
        {
            battery_information.type = BATTERY_3S;
        }
        else
        {
            battery_information.type = BATTERY_4S;
        }
    }

    // 持续检查电压是否过低
    if(BATTERY_LOW != battery_information.type)
    {
        if((battery_information.type * BLDC_LOW_VOLTAGE * 1000) > battery_information.voltage)
        {
            low_voltage_num++;
        }
        else
        {
            low_voltage_num = 0;
        }

        // 低压超过3秒，则认为电池电压过低
        if(3000 < low_voltage_num)
        {
            battery_information.type = BATTERY_LOW;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      电池ADC初始化
//  @param      void
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void battery_adc_init(void)
{
    battery_information.adc_pin = ADC1_IN10_C0;
    // 初始化电池电压ADC引脚
    adc_init(battery_information.adc_pin, ADC_12BIT);
}

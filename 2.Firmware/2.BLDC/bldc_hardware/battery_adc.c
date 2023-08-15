#include "bldc_config.h"
#include "battery_adc.h"
#include "zf_common_headfile.h"


battery_struct battery_information;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ���ADC��Ϣ
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

    // ��ȡ���ADCֵ
    battery_adc_value = adc_convert(battery_information.adc_pin);
    // ת��Ϊ��ص�ѹ��12λ��ADC��5.7���ķŴ���
    battery_information.voltage = (uint16) ((float)battery_adc_value / 4095 * 3300 * 5.7);

    // ���������Чʱ ������ж�
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

    // ��������ѹ�Ƿ����
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

        // ��ѹ����3�룬����Ϊ��ص�ѹ����
        if(3000 < low_voltage_num)
        {
            battery_information.type = BATTERY_LOW;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ADC��ʼ��
//  @param      void
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void battery_adc_init(void)
{
    battery_information.adc_pin = ADC1_IN10_C0;
    // ��ʼ����ص�ѹADC����
    adc_init(battery_information.adc_pin, ADC_12BIT);
}

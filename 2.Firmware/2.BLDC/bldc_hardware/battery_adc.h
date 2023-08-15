#ifndef _battery_adc_h_
#define _battery_adc_h_

#include "zf_common_typedef.h"
#include "zf_driver_adc.h"


typedef enum
{
    BATTERY_INVALID,    // ��Ч
    BATTERY_LOW,        // �͵�ѹ
    BATTERY_2S,         // 2S﮵��
    BATTERY_3S,         // 3S﮵��
    BATTERY_4S,         // 4S﮵��
}battery_type_enum;

typedef struct
{
    adc_channel_enum adc_pin;   // ��ص�ѹADC����
	uint16 voltage;             // ��ص�ѹ
    battery_type_enum  type;    // ������� 0����Ч  1����ѹ�����뼰ʱ������� 2��2S���  3��3S���  4��4S���
}battery_struct;


extern battery_struct battery_information;



void battery_adc_read(void);
void battery_adc_init(void);
#endif

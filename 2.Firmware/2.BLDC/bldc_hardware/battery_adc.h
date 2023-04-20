#ifndef _battery_adc_h_
#define _battery_adc_h_

#include "zf_common_typedef.h"
#include "zf_driver_adc.h"


typedef enum
{
    BATTERY_INVALID,    // 无效
    BATTERY_LOW,        // 低电压
    BATTERY_2S,         // 2S锂电池
    BATTERY_3S,         // 3S锂电池
    BATTERY_4S,         // 4S锂电池
}battery_type_enum;

typedef struct
{
    adc_channel_enum adc_pin;   // 电池电压ADC引脚
	uint16 voltage;             // 电池电压
    battery_type_enum  type;    // 电池类型 0：无效  1：电压过低请及时更换电池 2：2S电池  3：3S电池  4：4S电池
}battery_struct;


extern battery_struct battery_information;



void battery_adc_read(void);
void battery_adc_init(void);
#endif

#ifndef _enable_switch_h_
#define _enable_switch_h_


#include "zf_common_typedef.h"
#include "bldc_config.h"





typedef struct
{
    uint16 switch_en_pin;
    uint16 switch_1_pin;
}enable_switch_struct;


extern enable_switch_struct motor1_enable_switch;
extern enable_switch_struct motor2_enable_switch;

uint8 switch_check(enable_switch_struct *enable_switch);
void switch_init(motor_index_enum motor_index, enable_switch_struct *enable_switch);







#endif

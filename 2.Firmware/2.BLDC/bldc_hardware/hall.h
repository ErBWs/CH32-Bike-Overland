
#ifndef _hall_h_
#define _hall_h_



#include "vofa.h"
#include "zf_common_typedef.h"
#include "bldc_config.h"


typedef struct
{
    uint16 hall_a_pin;      // 霍尔A引脚
    uint16 hall_b_pin;      // 霍尔B引脚
    uint16 hall_c_pin;      // 霍尔C引脚
    uint16 hall_a_vofa;      // 霍尔A引脚
    uint16 hall_b_vofa;      // 霍尔B引脚
    uint16 hall_c_vofa;      // 霍尔C引脚
    uint16 hall_all_vofa;      // 霍尔C引脚
    TIM_TypeDef *tim_ch;    // 使用的定时器
    IRQn_Type irqn;         // 使用的定时器中断号
}hall_struct;

extern hall_struct motor1_hall;
extern hall_struct motor2_hall;


uint8   hall_value_read(hall_struct *hall);
uint16  hall_interval_time(hall_struct *hall);
void    hall_delay_set(hall_struct *hall, uint32 delay_time);
void    hall_delay_state_set(hall_struct *hall, uint8 state);
void    hall_init(motor_index_enum motor_index, hall_struct *hall);
#endif

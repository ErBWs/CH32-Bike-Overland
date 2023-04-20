
#ifndef _led_h_
#define _led_h_




#include "zf_common_typedef.h"
#include "bldc_config.h"

#include "motor.h"
#include "pwm_output.h"


typedef enum
{
    LED_ON,
    LED_OFF,
}LED_STATUS_enum;



typedef struct
{
    uint16 en_pin;
    uint16 run_pin;
    uint16 err_pin;
}led_struct;

extern led_struct motor1_led;
extern led_struct motor2_led;





void led_control(led_struct *led, motor_struct *motor, pwm_output_struct * pwm_output);

void led_init(motor_index_enum motor_index, led_struct *led);




#endif

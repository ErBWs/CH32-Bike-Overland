#ifndef _pwm_input_h_
#define _pwm_input_h_


#include "ch32v30x.h"
#include "ch32v30x_tim.h"
#include "ch32v30x_rcc.h"

#include "zf_common_typedef.h"
#include "bldc_config.h"



typedef enum
{
    FORWARD,    // ��ת
    REVERSE,    // ��ת
}MOTOR_DIR_enum;

typedef struct
{
    uint16 pwm_pin;             // �����ź���������
    uint16 dir_pin;             // �����źŷ�������
    TIM_TypeDef *tim_ch;        // ʹ�õĶ�ʱ��
    uint16 period;              // �����źŵ�������ֵ
    uint16 low;                 // �����źŵĵ͵�ƽ��ֵ
    uint16 high;                // �����źŵĸߵ�ƽ��ֵ
    uint16 freq;
    float  cycle;               // �����źŵĸߵ�ƽ�ٷֱ� ���ݷ�Χ0-1
    MOTOR_DIR_enum direction;   // �����źŵķ��� 0����ת 1����ת
}pwm_input_struct;

extern pwm_input_struct motor1_pwm_input_value;

extern pwm_input_struct motor2_pwm_input_value;

void pwm_input_trigger_callback(pwm_input_struct *pwm_input);
void pwm_input_timeout_callback(pwm_input_struct *pwm_input);
void pwm_input_init(motor_index_enum motor_index, pwm_input_struct *pwm_input);

















#endif

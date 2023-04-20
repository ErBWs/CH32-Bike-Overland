#ifndef _motor_h_
#define _motor_h_


#include "zf_common_typedef.h"
#include "zf_driver_adc.h"

#include "bldc_config.h"
#include "pid.h"
#include "en_switch.h"
#include "encoder.h"
#include "move_filter.h"
#include "hall.h"
#include "pwm_input.h"
#include "pwm_output.h"

typedef enum
{
    MOTOR_DISABLE,  // 驱动关闭
    MOTOR_ENABLE,   // 驱动使能
}MOTOR_EN_STATUS_enum;


typedef enum                    // 定义电机型号
{
    BLDC_MOTOR_3650      = 1,   // 1：黑色3650一对极无刷电机
    BLDC_MOTOR_MOMENTUM  = 2,   // 2：N车飞轮无刷电机
    BLDC_MOTOR_TRAVELING = 3,   // 3：N车行进无刷电机
}BLDC_MOTOR_TYPE_enum;

typedef struct
{
    uint8 bldc_motor_type;              // 电机类型
    MOTOR_EN_STATUS_enum enable_status; // 指示电机使能状态
//    MOTOR_DIR_enum  direction;          // 电机旋转方向 FORWARD：正转  REVERSE：反转
    MOTOR_DIR_enum  direction_now;      // 电机旋转方向 FORWARD：正转  REVERSE：反转
    uint8  brake_flag;                  // 指示当前刹车是否有效    1：启用刹车  0：不启用刹车   
    int32  speed_set;                   // 设置的速度
    int32  speed_now;                   // 当前速度  单位 r/min
    int32  speed_max;                   // 速度最大值
    int32  speed_min;                   // 速度最小值
    uint8  hall_last_value;             // 当前霍尔的值
    uint8  hall_now_value;              // 当前霍尔的值
    uint8  hall_except_value;           // 期望的下一次霍尔值
    int16  increase_step;               // 速度增加的步进值  加速的时候，值越大speed_set的值就会越快逼近except_speed
//    uint16 commutation_time_single[6];  // 单次换相时间，记录最近6次换相时间    单位us
//    uint32 commutation_time_sum;        // 转一圈的时间   单位us
    uint8  commutation_index;           // 统计换相次数
    uint8  commutation_timeout_num;     // 换相超时次数
    int16  commutation_angle;           // 换相角度 单位 °
    uint8  stop_flag;                   // 电机停止标志位
    uint8  hall_sequence[8];            // 记录霍尔顺序，0用于占位
    uint8  hall_sequence_index[8];      // 记录霍尔值在hall_sequence数组中的下标
    uint8  polepairs;                   // 电机极对数
    uint16 adc_bus_filter;              // 总线滤波后ADC值
    uint16 voltage_bus_filter;          // 总线滤波的总线电压值,单位MA
    adc_channel_enum adc_pin;           // 总线电压ADC引脚
}motor_struct;



extern motor_struct motor1_control;
extern motor_struct motor2_control;


void motor_commutation_finished_callback(
        hall_struct *hall,
        motor_struct *motor,
        pwm_input_struct *pwm_input,
        pwm_output_struct *pwm_output,
        closed_loop_struct *closed_loop,
        enable_switch_struct *enable_switch,
        move_filter_struct *speed_filter
        );
void motor_pit_control_callback(
        hall_struct *hall,
        motor_struct *motor,
        pwm_input_struct *pwm_input,
        pwm_output_struct *pwm_output,
        closed_loop_struct *closed_loop,
        enable_switch_struct *enable_switch,
        encoder_out_struct *encoder_out
);

void motor_commutation_timeout_callback(motor_struct *motor,move_filter_struct *speed_filter);
void motor_commutation_callback(motor_struct *motor, pwm_output_struct *pwm_output, hall_struct *hall);
void motor_set_commutation_angle(motor_struct *motor, uint8 commutation_angle);
void motor_set_polepairs(motor_struct *motor, uint8 num);
void motor_set_type(motor_struct *motor, BLDC_MOTOR_TYPE_enum bldc_motor_type);
void motor_speed_curve_init(motor_struct *motor, move_filter_struct *speed_filter);
void motor_init(motor_index_enum motor_index, motor_struct *motor);

#endif

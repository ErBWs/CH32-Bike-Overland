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
    MOTOR_DISABLE,  // �����ر�
    MOTOR_ENABLE,   // ����ʹ��
}MOTOR_EN_STATUS_enum;


typedef enum                    // �������ͺ�
{
    BLDC_MOTOR_3650      = 1,   // 1����ɫ3650һ�Լ���ˢ���
    BLDC_MOTOR_MOMENTUM  = 2,   // 2��N��������ˢ���
    BLDC_MOTOR_TRAVELING = 3,   // 3��N���н���ˢ���
}BLDC_MOTOR_TYPE_enum;

typedef struct
{
    uint8 bldc_motor_type;              // �������
    MOTOR_EN_STATUS_enum enable_status; // ָʾ���ʹ��״̬
//    MOTOR_DIR_enum  direction;          // �����ת���� FORWARD����ת  REVERSE����ת
    MOTOR_DIR_enum  direction_now;      // �����ת���� FORWARD����ת  REVERSE����ת
    uint8  brake_flag;                  // ָʾ��ǰɲ���Ƿ���Ч    1������ɲ��  0��������ɲ��   
    int32  speed_set;                   // ���õ��ٶ�
    int32  speed_now;                   // ��ǰ�ٶ�  ��λ r/min
    int32  speed_max;                   // �ٶ����ֵ
    int32  speed_min;                   // �ٶ���Сֵ
    uint8  hall_last_value;             // ��ǰ������ֵ
    uint8  hall_now_value;              // ��ǰ������ֵ
    uint8  hall_except_value;           // ��������һ�λ���ֵ
    int16  increase_step;               // �ٶ����ӵĲ���ֵ  ���ٵ�ʱ��ֵԽ��speed_set��ֵ�ͻ�Խ��ƽ�except_speed
//    uint16 commutation_time_single[6];  // ���λ���ʱ�䣬��¼���6�λ���ʱ��    ��λus
//    uint32 commutation_time_sum;        // תһȦ��ʱ��   ��λus
    uint8  commutation_index;           // ͳ�ƻ������
    uint8  commutation_timeout_num;     // ���೬ʱ����
    int16  commutation_angle;           // ����Ƕ� ��λ ��
    uint8  stop_flag;                   // ���ֹͣ��־λ
    uint8  hall_sequence[8];            // ��¼����˳��0����ռλ
    uint8  hall_sequence_index[8];      // ��¼����ֵ��hall_sequence�����е��±�
    uint8  polepairs;                   // ���������
    uint16 adc_bus_filter;              // �����˲���ADCֵ
    uint16 voltage_bus_filter;          // �����˲������ߵ�ѹֵ,��λMA
    adc_channel_enum adc_pin;           // ���ߵ�ѹADC����
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

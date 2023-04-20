
#include "hall.h"
#include "battery_adc.h"
#include "move_filter.h"
#include "bldc_config.h"
#include "pwm_output.h"
#include "en_switch.h"
#include "motor.h"
#include "pwm_input.h"
#include "pwm_output.h"
#include "encoder.h"
#include "move_filter.h"
#include "zf_common_function.h"


motor_struct motor1_control;
motor_struct motor2_control;



//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ٶ����߼��㺯��
//  @param      *motor              ����ṹ��ָ��
//  @param      *closed_loop        �ջ��ṹ��ָ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void motor_speed_curve(motor_struct *motor, closed_loop_struct *closed_loop)
{
    static int32 speed_set_last;

    // ���Ʊ仯����
    closed_loop->target_speed = func_limit_ab(motor->speed_set, speed_set_last - motor->increase_step, speed_set_last + motor->increase_step);

    // ���汾��Ŀ���ٶ�
    closed_loop->speed_set_last = closed_loop->target_speed;

    // �޷�
    closed_loop->target_speed = func_limit_ab(closed_loop->target_speed, motor->speed_min, motor->speed_max);
}

//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      ���ݲ��񵽵�ռ�ձ���Ϣ���õ�������ƽ
////  @param      *motor          ����ṹ��ָ��
////  @param      *pwm_input      PWM���벶��ṹ��ָ��
////  @return     void
////  @since
////-------------------------------------------------------------------------------------------------------------------
//void motor_set_dir(motor_struct *motor, pwm_input_struct *pwm_input)
//{
//    if(0 <= pwm_input->cycle)
//    {
//        motor->direction = FORWARD;
//    }
//    else
//    {
//        motor->direction = REVERSE;
//    }
//}


uint8 motor_hall_read(motor_struct *motor, hall_struct *hall)
{
    uint8 hall_value;
    
    // ��ȡ��ǰ����
    hall_value = hall_value_read(hall);

    
    // �Ի�����ֵ��������
    hall_value = motor->hall_sequence_index[hall_value];
    
    return hall_value;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ��һ�������Ļ���ֵ
//  @param      *motor              ����ṹ��ָ��
//  @param      *closed_loop        �ջ��ṹ��ָ��
//  @param      hall_value          ��ǰ����ֵ
//  @param      commutation_angle   ��ǰ�Ƕ�
//  @return     void
//  @since      
//-------------------------------------------------------------------------------------------------------------------
uint8 motor_next_hall(motor_struct *motor, closed_loop_struct *closed_loop, int8 hall_value, int16 commutation_angle)
{
    int8 hall_next;
    int8 commutation_phase_num;
    
    // ������Ҫ��һ�εĻ������뱾�λ����ļ��
    commutation_phase_num = commutation_angle / 60 + (0 < (commutation_angle%60));
    
    // ���ݵ����ת�����Լ���ǰ�� ������һ�������Ļ���ֵ
    if(0 < closed_loop->out)
    {
        hall_next = hall_value + commutation_phase_num;

        if(6 < hall_next)
        {
            hall_next -= 6;
        }
    }
    else
    {
        if(motor->bldc_motor_type == BLDC_MOTOR_MOMENTUM)
        {
            hall_next = hall_value - commutation_phase_num - 1;
        }
        else
        {
            hall_next = hall_value - commutation_phase_num;
        }

        
        if(1 > hall_next)  
        {
            hall_next += 6;
        }
    }
    
    return hall_next;
}

void motor_stop(motor_struct *motor, pwm_output_struct *pwm_output)
{
    if(motor->brake_flag)
    {
        pwm_complementary_brake(pwm_output);
    }
    else
    {
        pwm_complementary_control(pwm_output, DISABLE);
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����Ƿ���Ҫֹͣ
//  @param      *motor          ����ṹ��ָ��
//  @param      *closed_loop    �ջ��ṹ��ָ��
//  @return     void
//  @since      
//-------------------------------------------------------------------------------------------------------------------
uint8 motor_check_stop(motor_struct *motor, closed_loop_struct *closed_loop)
{
    uint8 temp = 0;

    if(0 == closed_loop->target_speed)                                   // �����ٶ�Ϊ0
    {
        temp = 1;
    }
    else if(MOTOR_DISABLE == motor->enable_status)               // �����ѹر�
    {
        temp = 1;
    }

    #if (1 == BLDC_LOW_VOLTAGE_BRAKE)
    else if(BATTERY_LOW == battery_information.type)                // ��ص�ѹ����
    {
        temp = 1;
    }
    #endif

    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ִ�е������
//  @param      *motor              ����ṹ��ָ��
//  @param      *pwm_output         PWM��������ṹ��ָ��
//  @param      hall_except_value   ��һ�������Ļ���ֵ
//  @return     void
//  @since      
//-------------------------------------------------------------------------------------------------------------------
void motor_commutation_execute(motor_struct *motor, pwm_output_struct *pwm_output, uint8 hall_except_value)
{
    if(0 == motor->stop_flag)
    {
        switch(hall_except_value)
        {
            case 1:
            {
                pwm_a_bn_output(pwm_output);
            }break;
                
            case 2:
            {
                pwm_a_cn_output(pwm_output);
            }break;
            
            case 3:
            {
                pwm_b_cn_output(pwm_output);
            }break;
            
            case 4:
            {
                pwm_b_an_output(pwm_output);
            }break;
            
            case 5:
            {
                pwm_c_an_output(pwm_output);
            }break;
            
            case 6:
            {
                pwm_c_bn_output(pwm_output);
            }break;
        }
    }
}

void motor_start(closed_loop_struct *closed_loop, pwm_output_struct *pwm_output, motor_struct *motor, hall_struct *hall)
{
    motor->commutation_timeout_num = 0;
    
    // ��ȡ��ǰ����
    motor->hall_now_value = motor_hall_read(motor, hall);
    
    // ������һ�λ���������ֵ
    motor->hall_except_value = motor_next_hall(motor, closed_loop, motor->hall_now_value, motor->commutation_angle);
    
    // ���л���
    motor_commutation_execute(motor, pwm_output, motor->hall_except_value);
}

//uint16 motor_commutation_time_min(motor_struct *motor)
//{
//    uint16 i;
//    uint16 min = 0xffff;
//    for(i=0; i<6; i++)
//    {
//        if(min > motor->commutation_time_single[i])
//        {
//            min = motor->commutation_time_single[i];
//        }
//    }
//    return min*19/20; // ����Сֵ����һ�����Ŵ�����������������ʱ��������ʱ��
//}

void motor_commutation_time_clear(motor_struct *motor, move_filter_struct *speed_filter)
{
    // �������ǰ�ٶ�����Ϊ0
    motor->speed_now = 0;
    move_filter_init(speed_filter);

//    // ���ת��һȦ��ʱ������Ϊ���ֵ
//    motor->commutation_time_sum = BLDC_COMMUTATION_TIME_MAX * 6;
//
//    // ������ʱ������Ϊ���
//    uint8 i;
//    for(i=0; i<6; i++)
//    {
//        motor->commutation_time_single[i] = BLDC_COMMUTATION_TIME_MAX;
//    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ʵ�����з���
//  @param      *motor          ����ṹ��ָ��
//  @return     void
//  @since      
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void motor_direction_calculate(motor_struct *motor)
{
    int8 temp;
    
    temp = (int8)motor->hall_now_value - (int8)motor->hall_last_value;
    
    if(func_abs(temp) > 3)
    {
        if(temp>3)
        {
            temp -= 6;
        }
        else
        {
            temp += 6;
        }
    }

    motor->direction_now = temp>0?FORWARD:REVERSE;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����Ѿ���ɻ���
//  @param      *hall           �����ṹ��ָ��
//  @param      *motor          ����ṹ��ָ��
//  @param      *pwm_input      PWM���벶��ṹ��ָ��
//  @param      *pwm_output     PWM��������ṹ��ָ��
//  @param      *closed_loop    �ջ��ṹ��ָ��
//  @param      *enable_switch  ʹ�ܿ��ؽṹ��ָ��
//  @param      *speed_filter   �ٶ��˲��ṹ��ָ��
//  @return     void
//  @since      
//  @note       ������isr.c�б�����
//-------------------------------------------------------------------------------------------------------------------
void motor_commutation_finished_callback(
        hall_struct *hall,
        motor_struct *motor,
        pwm_input_struct *pwm_input,
        pwm_output_struct *pwm_output,
        closed_loop_struct *closed_loop,
        enable_switch_struct *enable_switch,
        move_filter_struct *speed_filter
        )
{
    int32  speed_now_temp;
    uint8  hall_temp;
    uint16 time_temp;
//    uint16 commutation_delay_time;

    // ��ȡ���λ�������ʱ��
    time_temp = hall_interval_time(hall);

    // ��ȡ��ǰ����
    while(1)
    {
        hall_temp = motor_hall_read(motor, hall);
        
        if(0 != hall_temp && 7 != hall_temp)
        {
            break;
        }
    }
    motor->hall_last_value = motor->hall_now_value;
    motor->hall_now_value = hall_temp;
    
    motor_direction_calculate(motor);
    
    // ����ط���Ҫ�޸�Ϊʵ��ת��
    
    speed_now_temp = 60*1000*1000 / (time_temp * 6) / motor->polepairs;
    
    // �����ת��ȡ��
    if(REVERSE == motor->direction_now)
    {
        speed_now_temp = -speed_now_temp;
    }

    // ���ٶ���ƽ���˲�
    move_filter_calculate(speed_filter, speed_now_temp);

    motor->speed_now = speed_filter->data_average;


    if(closed_loop->out)
    {
        // ����Ƕȹ�С ֱ�ӻ���
        motor->hall_except_value = motor_next_hall(motor, closed_loop, motor->hall_now_value, 60);
        motor_commutation_execute(motor, pwm_output, motor->hall_except_value);
//
//        if(60 >= motor->commutation_angle)
//        {
//            // ����Ƕȹ�С ֱ�ӻ���
//            motor->hall_except_value = motor_next_hall(motor, closed_loop, motor->hall_now_value, 60);
//            motor_commutation_execute(motor, pwm_output, motor->hall_except_value);
//        }
//        else
//        {
//            // ����ֱ�ӻ���
//            if(100 > func_abs(motor->speed_now))
//            {
//                // ������һ�λ���������ֵ
//                motor->hall_except_value = motor_next_hall(motor, closed_loop, motor->hall_now_value, 60);
//                motor_commutation_execute(motor, pwm_output, motor->hall_except_value);
//            }
//            else
//            {
//                // ������һ�λ���������ֵ
//                motor->hall_except_value = motor_next_hall(motor, closed_loop, motor->hall_now_value, motor->commutation_angle);
//                commutation_delay_time = (uint32)(((float)60 - (motor->commutation_angle%60)) / 60 * motor_commutation_time_min(motor));
//
//                // ������ʱ����
//                hall_delay_set(hall, commutation_delay_time);
//                // ������ʱ
//                hall_delay_state_set(hall, ENABLE);
//            }
//        }
    }

    motor->commutation_timeout_num = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ຯ��
//  @param      *motor          ����ṹ��ָ��
//  @param      *pwm_output     PWM��������ṹ��ָ��
//  @param      *hall           �����ṹ��ָ��
//  @return     void
//  @since      
//  @note       ������isr.c�б�����
//-------------------------------------------------------------------------------------------------------------------
//void motor_commutation_callback(motor_struct *motor, pwm_output_struct *pwm_output, hall_struct *hall)
//{
//    motor_commutation_execute(motor, pwm_output, motor->hall_except_value);
//
//    hall_delay_state_set(hall, DISABLE);
//}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������೬ʱ����
//  @param      *motor          ����ṹ��ָ��
//  @param      *speed_filter   �ٶ��˲��ṹ��ָ��
//  @return     void
//  @since      
//  @note       ������isr.c�б�����
//-------------------------------------------------------------------------------------------------------------------
void motor_commutation_timeout_callback(motor_struct *motor,move_filter_struct *speed_filter)
{
    // ���ʹ���ѿ���
    if(MOTOR_ENABLE == motor->enable_status)
    {
        motor->commutation_timeout_num++;
        motor->commutation_timeout_num = func_limit_ab(motor->commutation_timeout_num, 1, 100);
        if(1 <= motor->commutation_timeout_num)
        {
            move_filter_calculate(speed_filter, 0);
            motor->speed_now = speed_filter->data_average;
//            motor_commutation_time_clear(motor, speed_filter);
        }
    }
    // ���ʹ���ѹر�
    else
    {
        motor->commutation_timeout_num = 0;
        motor_commutation_time_clear(motor, speed_filter);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����ʱ�������жϻص�����
//  @param      *hall           �����ṹ��ָ��
//  @param      *motor          ����ṹ��ָ��
//  @param      *pwm_input      PWM���벶��ṹ��ָ��
//  @param      *pwm_output     PWM��������ṹ��ָ��
//  @param      *closed_loop    �ջ��ṹ��ָ��
//  @param      *enable_switch  ʹ�ܿ��ؽṹ��ָ��
//  @param      *encoder_out    ����������ṹ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void motor_pit_control_callback(
        hall_struct *hall,
        motor_struct *motor,
        pwm_input_struct *pwm_input,
        pwm_output_struct *pwm_output,
        closed_loop_struct *closed_loop,
        enable_switch_struct *enable_switch,
        encoder_out_struct *encoder_out
)
{
    // ��ȡ���ߵ�ѹֵ
    motor->adc_bus_filter = adc_convert(motor->adc_pin);

    // ͨ����ʽת���ɵ���ֵ����λma
    motor->voltage_bus_filter = (float)motor->adc_bus_filter / 4095 * 3300 / 5.7 / 50 * 1000;

    // ���ʹ�ܿ���״̬
    motor->enable_status = (MOTOR_EN_STATUS_enum)switch_check(enable_switch);

    if(MOTOR_DISABLE == motor->enable_status)
    {
        // ��ʹ�ܿ��عر�ʱĿ���ٶ�����Ϊ0
        motor->speed_set = 0;
    }
    else
    {
        // ���������ٶ�
        motor->speed_set = (int32)(motor->speed_max * pwm_input->cycle);
    }

#if BLDC_SPEED_CURVE_ENABLE==1
    // ����������� ͨ�����ò������Ե��ڼ��ٵ���Ӧ�ٶ�
    motor_speed_curve(motor, closed_loop);
#else
    closed_loop->target_speed = motor->speed_set;
#endif

//    motor_set_dir(motor, pwm_input);

#if BLDC_CLOSE_LOOP_ENABLE==1
    // ����PI�ջ�����
    closed_loop_pi_calc(closed_loop, motor->enable_status, motor->speed_max, motor->speed_now);
#else
    closed_loop->out = closed_loop->target_speed;
#endif

    // ��־λ��һ���������
    if(closed_loop->out && (1 <= motor->commutation_timeout_num))
    {
        motor_start(closed_loop, pwm_output, motor, hall);
    }
    
    
    // ����Ƿ���Ҫͣת���
    motor->stop_flag = motor_check_stop(motor, closed_loop);

    if(0 == motor->stop_flag)
    {
        // �������
        pwm_complementary_set_duty(pwm_output, hall, func_abs(closed_loop->out));
    }
    else
    {
        motor_stop(motor, pwm_output);
    }
    
    // ����ٶ��뷽����Ϣ
    encoder_out_speed(encoder_out, motor->speed_now);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���õ����ǰ�Ƕ�
//  @param      *motor                  ����ṹ��ָ��
//  @param      commutation_angle       ��ǰ�Ƕ�, �����÷�Χ60-120 Ĭ������Ϊ60
//  @return     void
//  @since
//              ��ǰ�Ƕ�, �����÷�Χ60-120 Ĭ������Ϊ60
//-------------------------------------------------------------------------------------------------------------------
void motor_set_commutation_angle(motor_struct *motor, uint8 commutation_angle)
{
    motor->commutation_angle = commutation_angle;
    motor->commutation_angle = func_limit_ab(motor->commutation_angle, 60, 120);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���õ��������
//  @param      *motor          ����ṹ��ָ��
//  @param      num             ������
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void motor_set_polepairs(motor_struct *motor, uint8 num)
{
    motor->polepairs = num;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���õ������
//  @param      *motor          ����ṹ��ָ��
//  @param      bldc_motor_type �������
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void motor_set_type(motor_struct *motor, BLDC_MOTOR_TYPE_enum bldc_motor_type)
{
    uint8 i;
    uint8 temp_hall_sequence[] = {0, 2, 3, 1, 5, 4, 6, 0};

    motor->bldc_motor_type = bldc_motor_type;

    for(i=0; i<8; i++)
    {
        motor->hall_sequence[i] = temp_hall_sequence[i];
    }

    // ����ÿ������ֵ��hall_sequence�����е��±�
    for(i=1; i<=6; i++)
    {
        motor->hall_sequence_index[motor->hall_sequence[i]] = i;
    }
    motor->hall_sequence_index[0] = 0;
    motor->hall_sequence_index[7] = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ٶ����߳�ʼ��
//  @param      *motor          ����ṹ��ָ��
//  @param      *speed_filter   �ٶ��˲��ṹ��ָ��
//  @return     void
//  @since      
//-------------------------------------------------------------------------------------------------------------------
void motor_speed_curve_init(motor_struct *motor, move_filter_struct *speed_filter)
{
#if BLDC_BRAKE_ENABLE==1
    motor->brake_flag = 1;                               // ɲ��ʹ��
#else           
    motor->brake_flag = 0;                               // ɲ���ر�
#endif          
//    motor->direction = FORWARD;                          // ����Ĭ�ϵķ���


    
    motor->speed_set = 0;
    
#if BLDC_CLOSE_LOOP_ENABLE==1
    motor->speed_max = BLDC_MAX_SPEED;                   // ���������ת�ٶ�
    motor->speed_min = -BLDC_MAX_SPEED;                  // �������ת�ٶ�
    motor->increase_step = BLDC_STEP_SPEED;              // ���ü���ʱ�Ĳ���ֵ
#else                                                              
    motor->speed_max = PWM_PERIOD;                       // ���������ת�ٶ�
    motor->speed_min = -PWM_PERIOD;                      // �������ת�ٶ�
    motor->increase_step = BLDC_STEP_SPEED;              // ���ü���ʱ�Ĳ���ֵ
#endif

    motor_commutation_time_clear(motor, speed_filter);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���adc���ų�ʼ��
//  @param      motor_index �������
//  @param      *motor      ����ṹ��ָ��
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void motor_init(motor_index_enum motor_index, motor_struct *motor)
{
    if(motor_index == MOTOR_1)
    {
        motor->adc_pin = ADC2_IN11_C1;

    }
    else if(motor_index == MOTOR_2)
    {
        motor->adc_pin = ADC2_IN4_A4;
    }

    adc_init(motor->adc_pin, ADC_12BIT);    // ����ADC���ų�ʼ����ʹ��12λADC
}

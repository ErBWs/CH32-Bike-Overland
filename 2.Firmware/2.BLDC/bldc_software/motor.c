
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
//  @brief      速度曲线计算函数
//  @param      *motor              电机结构体指针
//  @param      *closed_loop        闭环结构体指针
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void motor_speed_curve(motor_struct *motor, closed_loop_struct *closed_loop)
{
    static int32 speed_set_last;

    // 限制变化速率
    closed_loop->target_speed = func_limit_ab(motor->speed_set, speed_set_last - motor->increase_step, speed_set_last + motor->increase_step);

    // 保存本次目标速度
    closed_loop->speed_set_last = closed_loop->target_speed;

    // 限幅
    closed_loop->target_speed = func_limit_ab(closed_loop->target_speed, motor->speed_min, motor->speed_max);
}

//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      根据捕获到的占空比信息设置电机输出电平
////  @param      *motor          电机结构体指针
////  @param      *pwm_input      PWM输入捕获结构体指针
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
    
    // 读取当前霍尔
    hall_value = hall_value_read(hall);

    
    // 对霍尔的值重新排序
    hall_value = motor->hall_sequence_index[hall_value];
    
    return hall_value;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取下一次期望的霍尔值
//  @param      *motor              电机结构体指针
//  @param      *closed_loop        闭环结构体指针
//  @param      hall_value          当前霍尔值
//  @param      commutation_angle   超前角度
//  @return     void
//  @since      
//-------------------------------------------------------------------------------------------------------------------
uint8 motor_next_hall(motor_struct *motor, closed_loop_struct *closed_loop, int8 hall_value, int16 commutation_angle)
{
    int8 hall_next;
    int8 commutation_phase_num;
    
    // 计算需要下一次的霍尔距离本次霍尔的间距
    commutation_phase_num = commutation_angle / 60 + (0 < (commutation_angle%60));
    
    // 根据电机旋转方向以及超前角 计算下一次期望的霍尔值
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
//  @brief      检查是否需要停止
//  @param      *motor          电机结构体指针
//  @param      *closed_loop    闭环结构体指针
//  @return     void
//  @since      
//-------------------------------------------------------------------------------------------------------------------
uint8 motor_check_stop(motor_struct *motor, closed_loop_struct *closed_loop)
{
    uint8 temp = 0;

    if(0 == closed_loop->target_speed)                                   // 期望速度为0
    {
        temp = 1;
    }
    else if(MOTOR_DISABLE == motor->enable_status)               // 驱动已关闭
    {
        temp = 1;
    }

    #if (1 == BLDC_LOW_VOLTAGE_BRAKE)
    else if(BATTERY_LOW == battery_information.type)                // 电池电压过低
    {
        temp = 1;
    }
    #endif

    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      执行电机换相
//  @param      *motor              电机结构体指针
//  @param      *pwm_output         PWM互补输出结构体指针
//  @param      hall_except_value   下一次期望的霍尔值
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
    
    // 读取当前霍尔
    motor->hall_now_value = motor_hall_read(motor, hall);
    
    // 计算下一次霍尔的期望值
    motor->hall_except_value = motor_next_hall(motor, closed_loop, motor->hall_now_value, motor->commutation_angle);
    
    // 进行换相
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
//    return min*19/20; // 对最小值在做一个缩放处理，避免计算出来的延时超过换相时长
//}

void motor_commutation_time_clear(motor_struct *motor, move_filter_struct *speed_filter)
{
    // 将电机当前速度设置为0
    motor->speed_now = 0;
    move_filter_init(speed_filter);

//    // 电机转动一圈的时间设置为最大值
//    motor->commutation_time_sum = BLDC_COMMUTATION_TIME_MAX * 6;
//
//    // 将换相时间设置为最大
//    uint8 i;
//    for(i=0; i<6; i++)
//    {
//        motor->commutation_time_single[i] = BLDC_COMMUTATION_TIME_MAX;
//    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      计算电机实际运行方向
//  @param      *motor          电机结构体指针
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
//  @brief      电机已经完成换相
//  @param      *hall           霍尔结构体指针
//  @param      *motor          电机结构体指针
//  @param      *pwm_input      PWM输入捕获结构体指针
//  @param      *pwm_output     PWM互补输出结构体指针
//  @param      *closed_loop    闭环结构体指针
//  @param      *enable_switch  使能开关结构体指针
//  @param      *speed_filter   速度滤波结构体指针
//  @return     void
//  @since      
//  @note       函数在isr.c中被调用
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

    // 获取本次换相所用时间
    time_temp = hall_interval_time(hall);

    // 读取当前霍尔
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
    
    // 这个地方需要修改为实际转速
    
    speed_now_temp = 60*1000*1000 / (time_temp * 6) / motor->polepairs;
    
    // 如果反转则取负
    if(REVERSE == motor->direction_now)
    {
        speed_now_temp = -speed_now_temp;
    }

    // 对速度做平滑滤波
    move_filter_calculate(speed_filter, speed_now_temp);

    motor->speed_now = speed_filter->data_average;


    if(closed_loop->out)
    {
        // 换相角度过小 直接换相
        motor->hall_except_value = motor_next_hall(motor, closed_loop, motor->hall_now_value, 60);
        motor_commutation_execute(motor, pwm_output, motor->hall_except_value);
//
//        if(60 >= motor->commutation_angle)
//        {
//            // 换相角度过小 直接换相
//            motor->hall_except_value = motor_next_hall(motor, closed_loop, motor->hall_now_value, 60);
//            motor_commutation_execute(motor, pwm_output, motor->hall_except_value);
//        }
//        else
//        {
//            // 低速直接换相
//            if(100 > func_abs(motor->speed_now))
//            {
//                // 计算下一次霍尔的期望值
//                motor->hall_except_value = motor_next_hall(motor, closed_loop, motor->hall_now_value, 60);
//                motor_commutation_execute(motor, pwm_output, motor->hall_except_value);
//            }
//            else
//            {
//                // 计算下一次霍尔的期望值
//                motor->hall_except_value = motor_next_hall(motor, closed_loop, motor->hall_now_value, motor->commutation_angle);
//                commutation_delay_time = (uint32)(((float)60 - (motor->commutation_angle%60)) / 60 * motor_commutation_time_min(motor));
//
//                // 设置延时换相
//                hall_delay_set(hall, commutation_delay_time);
//                // 开启延时
//                hall_delay_state_set(hall, ENABLE);
//            }
//        }
    }

    motor->commutation_timeout_num = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机换相函数
//  @param      *motor          电机结构体指针
//  @param      *pwm_output     PWM互补输出结构体指针
//  @param      *hall           霍尔结构体指针
//  @return     void
//  @since      
//  @note       函数在isr.c中被调用
//-------------------------------------------------------------------------------------------------------------------
//void motor_commutation_callback(motor_struct *motor, pwm_output_struct *pwm_output, hall_struct *hall)
//{
//    motor_commutation_execute(motor, pwm_output, motor->hall_except_value);
//
//    hall_delay_state_set(hall, DISABLE);
//}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机换相超时函数
//  @param      *motor          电机结构体指针
//  @param      *speed_filter   速度滤波结构体指针
//  @return     void
//  @since      
//  @note       函数在isr.c中被调用
//-------------------------------------------------------------------------------------------------------------------
void motor_commutation_timeout_callback(motor_struct *motor,move_filter_struct *speed_filter)
{
    // 电机使能已开启
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
    // 电机使能已关闭
    else
    {
        motor->commutation_timeout_num = 0;
        motor_commutation_time_clear(motor, speed_filter);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机定时器周期中断回调函数
//  @param      *hall           霍尔结构体指针
//  @param      *motor          电机结构体指针
//  @param      *pwm_input      PWM输入捕获结构体指针
//  @param      *pwm_output     PWM互补输出结构体指针
//  @param      *closed_loop    闭环结构体指针
//  @param      *enable_switch  使能开关结构体指针
//  @param      *encoder_out    编码器输出结构体
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
    // 读取总线电压值
    motor->adc_bus_filter = adc_convert(motor->adc_pin);

    // 通过公式转换成电流值，单位ma
    motor->voltage_bus_filter = (float)motor->adc_bus_filter / 4095 * 3300 / 5.7 / 50 * 1000;

    // 检查使能开关状态
    motor->enable_status = (MOTOR_EN_STATUS_enum)switch_check(enable_switch);

    if(MOTOR_DISABLE == motor->enable_status)
    {
        // 当使能开关关闭时目标速度设置为0
        motor->speed_set = 0;
    }
    else
    {
        // 计算期望速度
        motor->speed_set = (int32)(motor->speed_max * pwm_input->cycle);
    }

#if BLDC_SPEED_CURVE_ENABLE==1
    // 计算加速曲线 通过设置参数可以调节加速的响应速度
    motor_speed_curve(motor, closed_loop);
#else
    closed_loop->target_speed = motor->speed_set;
#endif

//    motor_set_dir(motor, pwm_input);

#if BLDC_CLOSE_LOOP_ENABLE==1
    // 进行PI闭环计算
    closed_loop_pi_calc(closed_loop, motor->enable_status, motor->speed_max, motor->speed_now);
#else
    closed_loop->out = closed_loop->target_speed;
#endif

    // 标志位置一则启动电机
    if(closed_loop->out && (1 <= motor->commutation_timeout_num))
    {
        motor_start(closed_loop, pwm_output, motor, hall);
    }
    
    
    // 检查是否需要停转电机
    motor->stop_flag = motor_check_stop(motor, closed_loop);

    if(0 == motor->stop_flag)
    {
        // 输出动力
        pwm_complementary_set_duty(pwm_output, hall, func_abs(closed_loop->out));
    }
    else
    {
        motor_stop(motor, pwm_output);
    }
    
    // 输出速度与方向信息
    encoder_out_speed(encoder_out, motor->speed_now);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      设置电机超前角度
//  @param      *motor                  电机结构体指针
//  @param      commutation_angle       超前角度, 可设置范围60-120 默认设置为60
//  @return     void
//  @since
//              超前角度, 可设置范围60-120 默认设置为60
//-------------------------------------------------------------------------------------------------------------------
void motor_set_commutation_angle(motor_struct *motor, uint8 commutation_angle)
{
    motor->commutation_angle = commutation_angle;
    motor->commutation_angle = func_limit_ab(motor->commutation_angle, 60, 120);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      设置电机极对数
//  @param      *motor          电机结构体指针
//  @param      num             极对数
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void motor_set_polepairs(motor_struct *motor, uint8 num)
{
    motor->polepairs = num;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      设置电机类型
//  @param      *motor          电机结构体指针
//  @param      bldc_motor_type 电机类型
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

    // 计算每个霍尔值在hall_sequence数组中的下标
    for(i=1; i<=6; i++)
    {
        motor->hall_sequence_index[motor->hall_sequence[i]] = i;
    }
    motor->hall_sequence_index[0] = 0;
    motor->hall_sequence_index[7] = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机速度曲线初始化
//  @param      *motor          电机结构体指针
//  @param      *speed_filter   速度滤波结构体指针
//  @return     void
//  @since      
//-------------------------------------------------------------------------------------------------------------------
void motor_speed_curve_init(motor_struct *motor, move_filter_struct *speed_filter)
{
#if BLDC_BRAKE_ENABLE==1
    motor->brake_flag = 1;                               // 刹车使能
#else           
    motor->brake_flag = 0;                               // 刹车关闭
#endif          
//    motor->direction = FORWARD;                          // 设置默认的方向


    
    motor->speed_set = 0;
    
#if BLDC_CLOSE_LOOP_ENABLE==1
    motor->speed_max = BLDC_MAX_SPEED;                   // 设置最大正转速度
    motor->speed_min = -BLDC_MAX_SPEED;                  // 设置最大反转速度
    motor->increase_step = BLDC_STEP_SPEED;              // 设置加速时的步进值
#else                                                              
    motor->speed_max = PWM_PERIOD;                       // 设置最大正转速度
    motor->speed_min = -PWM_PERIOD;                      // 设置最大反转速度
    motor->increase_step = BLDC_STEP_SPEED;              // 设置加速时的步进值
#endif

    motor_commutation_time_clear(motor, speed_filter);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机adc引脚初始化
//  @param      motor_index 电机索引
//  @param      *motor      电机结构体指针
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

    adc_init(motor->adc_pin, ADC_12BIT);    // 总线ADC引脚初始化，使用12位ADC
}

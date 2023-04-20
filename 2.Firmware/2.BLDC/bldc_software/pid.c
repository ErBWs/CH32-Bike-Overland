
#include "bldc_config.h"
#include "motor.h"
#include "pid.h"
#include "pwm_output.h"
#include "zf_common_function.h"


closed_loop_struct motor1_closed_loop;
closed_loop_struct motor2_closed_loop;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PI闭环计算
//  @param      read_speed  当前速度 
//  @return     void					
//  @since      
//-------------------------------------------------------------------------------------------------------------------
void closed_loop_pi_calc(closed_loop_struct *closed_loop, uint8 enable_status, uint32 speed_max, int32 read_speed)
{
    closed_loop->real_speed = read_speed;
    
    closed_loop->error = closed_loop->target_speed - closed_loop->real_speed;

    closed_loop->pout = (int32)(closed_loop->error * closed_loop->kp);
    
    closed_loop->iout += closed_loop->error * closed_loop->ki;
    
    //积分限幅
    closed_loop->iout = func_limit_ab(closed_loop->iout, -closed_loop->out_max, closed_loop->out_max);

    //如果目标速度为0或者电机被关闭则清除积分
    if((0 == closed_loop->target_speed )|| (MOTOR_DISABLE == enable_status))
    {
        closed_loop->iout = 0;
    }
    
    //正转的时候对积分进行限幅
    if(0 < closed_loop->target_speed)
    {
        closed_loop->iout = func_limit_ab(closed_loop->iout, (float)closed_loop->target_speed/speed_max*closed_loop->out_max/2, closed_loop->out_max);
    }
    //反转的时候对积分进行限幅
    else if(0 > closed_loop->target_speed)
    {
        closed_loop->iout = func_limit_ab(closed_loop->iout, -closed_loop->out_max, (float)closed_loop->target_speed/speed_max*closed_loop->out_max/2);
    }

    closed_loop->out = (int32)closed_loop->iout + closed_loop->pout;
    
    //输出限幅
    closed_loop->out = func_limit_ab(closed_loop->out, -closed_loop->out_max, closed_loop->out_max);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      PI闭环计算初始化
//  @param      *closed_loop   闭环结构体指针
//  @return     void					
//  @since      
//-------------------------------------------------------------------------------------------------------------------
void closed_loop_pi_init(closed_loop_struct *closed_loop)
{
    closed_loop->out_max = PWM_PERIOD;
    closed_loop->kp = 0.003;
    closed_loop->ki = 0.001;
    closed_loop->out = 0;
    closed_loop->real_speed = 0;
}

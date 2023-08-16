#ifndef _pid_h_
#define _pid_h_

#include "zf_common_typedef.h"
#include "bldc_config.h"

typedef struct 
{
    float kp;           //PI闭环的比例参数
    float ki;           //PI闭环的积分参数
    int32 target_speed; //闭环的目标速度 不要直接修改这个变量
    int32 real_speed;   //当前电机转速
    int32 error;        //目标速度与实际速度误差
    int32 out_max;      //闭环最大输出
    int32 pout;         //闭环比例输出值
    float iout;         //闭环积分输出值
    int32 out;          //闭环输出值
    int32 speed_set_last;//上一次速度设置值
}closed_loop_struct;



extern closed_loop_struct motor1_closed_loop;
extern closed_loop_struct motor2_closed_loop;
void closed_loop_pi_init(closed_loop_struct *closed_loop); //PI初始化程序
void closed_loop_pi_calc(closed_loop_struct *closed_loop, uint8 enable_status, uint32 speed_max, int32 read_speed);

#endif

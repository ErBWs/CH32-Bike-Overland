/**
 ***************************************(C) COPYRIGHT 2021 DIODE***************************************
 * @file       pid.c
 * @brief     
 * @note
 * @Version    V1.0.0
 * @Date       2021.5
 ***************************************(C) COPYRIGHT 2021 DIODE***************************************
 */
#include "moto.h"
#include "pid.h"
#include "math.h"

bool preset1 = false, preset2 = false, preset3 = false;
// PID struct define
PID_TypeDef flySpdPid;
PID_TypeDef flyAnglePid;
PID_TypeDef flyAngleSpdPid;
PID_TypeDef backSpdPid;
PID_TypeDef dirPid;
PID_TypeDef dirDisPid;
void PID_Reset(PID_TypeDef	*pid, float kp, float ki, float kd)
{
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
}
/**
  * @brief  初始化PID结构体
  * @param  PID结构体指针
		@param	PID模式
		@param  总输出最大值
		@param  积分最大值
    @param  比例系数
		@param  积分系数
		@param  微分系数


  * @retval None
  */
void PID_Init(
    PID_TypeDef*	pid,
    uint32_t 			mode,
    float 			maxout,
    float 			intergral_limit,
    float 				kp,
    float 				ki,
    float 				kd)
{
    pid->IntegralLimit = intergral_limit;
    pid->MaxOutput = maxout;
    pid->pid_mode = mode;

    pid->target[0]=0;
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;

}
static void abs_limit(float *num, float Limit)
{
    if (*num > Limit)
    {
        *num = Limit;
    }
    else if (*num < -Limit)
    {
        *num = -Limit;
    }
}
float PID_Calculate(PID_TypeDef *pid, float target, float feedback)
{
    pid->feedback[NOW] = feedback;
    pid->target[NOW] = target;
    pid->err[NOW] = target - feedback;

    if (pid->max_err != 0 && ABS(pid->err[NOW]) >  pid->max_err  )
        return 0;
    if (pid->deadband != 0 && ABS(pid->err[NOW]) < pid->deadband)
        return 0;

    if(pid->pid_mode == POSITION_PID)					 //位置式PID
    {
        pid->pout = pid->Kp * pid->err[NOW];
        pid->iout += pid->Ki * pid->err[NOW];
//			  if(pid->pout*pid->iout<0) pid->iout/=3.0f;
        pid->dout = pid->Kd * (pid->err[NOW] - pid->err[LAST] );
				
				
        abs_limit(&(pid->iout), pid->IntegralLimit);				//限制积分输出
        pid->pos_out = pid->pout + pid->iout + pid->dout;		// 计算总输出
        abs_limit(&(pid->pos_out), pid->MaxOutput);					// 限制总输出
        pid->last_pos_out = pid->pos_out;										//更新上一次总输出
    }
    else if(pid->pid_mode == DELTA_PID)					//增量式PID
    {
        pid->pout = pid->Kp * (pid->err[NOW] - pid->err[LAST]);
        pid->iout = pid->Ki * pid->err[NOW];
        pid->dout = pid->Kd * (pid->err[NOW] - 2*pid->err[LAST] + pid->err[LLAST]);

        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->delta_u = pid->pout + pid->iout + pid->dout;
        pid->delta_out = pid->last_delta_out + pid->delta_u;
        abs_limit(&(pid->delta_out), pid->MaxOutput);
        pid->last_delta_out = pid->delta_out;	//update last time
    }

    pid->err[LLAST] = pid->err[LAST];
    pid->err[LAST] = pid->err[NOW];
    pid->feedback[LLAST] = pid->feedback[LAST];
    pid->feedback[LAST] = pid->feedback[NOW];
    pid->target[LLAST] = pid->target[LAST];
    pid->target[LAST] = pid->target[NOW];

//    return pid->pid_mode==POSITION_PID ? (fabs(target)<=0.1? 0 : pid->pos_out) : pid->delta_out;
	return pid->pid_mode==POSITION_PID ?  pid->pos_out : pid->delta_out;
}
void pidClear(PID_TypeDef *pid)
{
    pid->err[NOW] = 0;
    pid->err[LAST] = 0;
    pid->err[LLAST] = 0;
    pid->last_delta_out = 0;
    pid->delta_u = 0;
    pid->dout = 0;
    pid->iout = 0;
    pid->pout = 0;
    pid->last_pos_out = 0;
    pid->pos_out = 0;
}
void setSmoothKp(PID_TypeDef *pid, float targetKp ,float ms){
    pid->smoothTargetKp = targetKp;
    pid->sport_kp_step = (targetKp - pid->Kp) / ((float) ms / SMOOTH_KP_PER_TICK_MS);
    pid->is_sporting = true;
}
void dynamicKpHandler(PID_TypeDef *pid){
    if(pid->is_sporting==false)return;
    float kp_target, y_target;
    kp_target = pid->smoothTargetKp;
    if ((pid->sport_kp_step > 0 && pid->Kp < pid->smoothTargetKp) ||
        (pid->sport_kp_step < 0 && pid->Kp > pid->smoothTargetKp))
        kp_target = pid->Kp + pid->sport_kp_step;
    if ((pid->sport_kp_step > 0 && pid->Kp >= pid->smoothTargetKp) ||(pid->sport_kp_step < 0 && pid->Kp <= pid->smoothTargetKp) ||
        pid->sport_kp_step == 0) {
        kp_target = pid->smoothTargetKp;
        pid->is_sporting = false;
    }
    pid->Kp = kp_target;
}
void pidAllInit(void)
{
	/**
  * @brief  初始化PID结构体
  * @param  PID结构体指针
    @param	PID模式
    @param  总输出最大值
    @param  积分最大值
    @param  比例系数
    @param  积分系数
    @param  微分系数
	
  * @retval None
  */

	PID_Init(&dirPid,POSITION_PID,SERVO_MAX_ANGLE,0,-0.045f,0,0);//舵机PD
//    PID_Init(&flySpdPid,POSITION_PID,PWM_DUTY_MAX-20,0,-0.4f,0,0);//飞轮速度环纯P
//    PID_Init(&flyAnglePid,POSITION_PID,PWM_DUTY_MAX-20,0,11.0f,0,0);//飞轮角度环PD
//    PID_Init(&flyAngleSpdPid,POSITION_PID,PWM_DUTY_MAX-20,PWM_DUTY_MAX-20,45.0f,0.8f,0);//飞轮角速度环PI
    PID_Init(&flySpdPid,POSITION_PID,PWM_DUTY_MAX-20,0,-0.35f,0,0);//飞轮速度环纯P
    PID_Init(&flyAnglePid,POSITION_PID,PWM_DUTY_MAX-20,0,10.5f,0,0);//飞轮角度环PD
    PID_Init(&flyAngleSpdPid,POSITION_PID,PWM_DUTY_MAX-20,PWM_DUTY_MAX-20,45.0f,0.6f,0);//飞轮角速度环PI

    PID_Init(&backSpdPid,POSITION_PID,PWM_DUTY_MAX-10,5000,60,2.5f,0.0f);//后轮速度环纯P

//    PID_Init(&dirPid,POSITION_PID,SERVO_MAX_ANGLE,0,-1.0f,0,0);//舵机PD
//    PID_Init(&flySpdPid,POSITION_PID,PWM_DUTY_MAX-10,8000,0.8f,0.005f,-0.0f);//飞轮速度环纯P
//    PID_Init(&flyAnglePid,POSITION_PID,PWM_DUTY_MAX-10,0,23,0,0);//飞轮角度环PD
//    PID_Init(&flyAngleSpdPid,POSITION_PID,PWM_DUTY_MAX-10,PWM_DUTY_MAX-10,-45,0.0f,0);//飞轮角速度环PI
//    PID_Init(&backSpdPid,POSITION_PID,PWM_DUTY_MAX-10,4000,150,1.2f,-0.2f);//后轮速度环纯P

}

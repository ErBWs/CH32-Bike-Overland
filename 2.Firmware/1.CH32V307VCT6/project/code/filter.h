/*
 * filter.h
 *
 *  Created on: 2023Äê2ÔÂ7ÈÕ
 *      Author: sorrymaker
 */

#ifndef CODE_FILTER_H_
#define CODE_FILTER_H_

#include "zf_common_headfile.h"
#include "inc_all.h"

#define M_PI_F 3.141592653589793f
#define LPF_1_(hz,t,in,out) ((out) += ( 1 / ( 1 + 1 / ( (hz) *6.28f *(t) ) ) ) *( (in) - (out) ))

extern float angle, angle_dot;
void Kalman_Filter(float Accel,float Gyro);
typedef struct
{
 float Input_Butter[3];
 float Output_Butter[3];
}Butter_BufferData;

typedef struct
{
  float a[3];
  float b[3];
}Butter_Parameter;


extern Butter_BufferData Butter_5HZ_Buffer_Acce[3];
extern float Acce_Control[3],Acce_Control_Feedback[3];
float set_lpf_alpha(int16 cutoff_frequency, float time_step);
void Acce_Control_Filter(void);
float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter);
float set_lpf_alpha(int16 cutoff_frequency, float time_step);
void set_cutoff_frequency(float sample_frequent, float cutoff_frequent,Butter_Parameter *LPF);
void Butterworth_Parameter_Init(void);
typedef struct
{
    float in_est_d;   //Estimator
    float in_obs;    //Observation

    float fix_kp;
    float e_limit;

    float e;

    float out;
}_fix_inte_filter_st;

void fix_inte_filter(float dT,_fix_inte_filter_st *data);

typedef struct
{
    float lpf_1;

    float out;
}_lf_t;
void limit_filter(float T,float hz,_lf_t *data,float in);


typedef struct
{
    uint8 cnt;

    int32 lst_pow_sum;

    int32 now_out;
    int32 lst_out;
    int32 now_velocity_xdt;
} _steepest_st;
void steepest_descend(int32 arr[],uint8 len,_steepest_st *steepest,uint8 step_num,int32 in);
 void Moving_Average(float moavarray[],uint16 len ,uint16 *fil_cnt,float in,float *out);



#endif /* CODE_FILTER_H_ */

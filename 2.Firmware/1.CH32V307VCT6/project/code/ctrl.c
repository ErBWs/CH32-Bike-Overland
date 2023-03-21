#include "ctrl.h"

#define MAIN_PIT   TIM3_PIT
#define IMU_PIT    TIM1_PIT
void taskTimAllInit(void)
{
    pit_ms_init(MAIN_PIT, 5);
    pit_ms_init(IMU_PIT,5);
    //interrupt_set_priority(TIM6_IRQn, 1);
}
void IMUGetCalFun(void)
{
    IMU_Getdata(&gyro,&acc);
    Data_steepest();
    IMU_update(0.005, &sensor.Gyro_deg, &sensor.Acc_mmss, &imu_data);
}
void ServoControl(void)
{
    PID_Calculate(&dirPid,0,imu_data.rol);//纯P
    pwm_set_duty(SERVO_PIN,GetServoDuty(dirPid.pos_out));
    //printf("A%f\r\n",imu_data.rol);
}
uint32_t back_inter_distance=0;
void BackMotoControl(void)
{
    int16_t back_wheel_encode=0;

    back_wheel_encode = encoder_get_count(ENCODER_BACK_WHEEL_TIM);
    printf("A%d\r\n",back_wheel_encode);
    encoder_clear_count(ENCODER_BACK_WHEEL_TIM);
    back_inter_distance += myABS(back_wheel_encode);

    PID_Calculate(&backSpdPid,backSpdPid.target[NOW],back_wheel_encode);//速度环P
    motoDutySet(MOTOR_BACK_PIN,backSpdPid.pos_out);
}
void FlyWheelControl(void)
{
    extern Butter_Parameter Butter_10HZ_Parameter_Acce;
    extern Butter_BufferData Butter_Buffer;
    int16_t fly_wheel_encode=0;
    float temp_x;
    temp_x = LPButterworth(sensor.Gyro_deg.x,&Butter_Buffer,&Butter_10HZ_Parameter_Acce);
    fly_wheel_encode = encoder_get_count(ENCODER_FLY_WHEEL_TIM);
//    printf("A%d\r\n",fly_wheel_encode);
    encoder_clear_count(ENCODER_FLY_WHEEL_TIM);
    PID_Calculate(&flySpdPid,0,fly_wheel_encode);//速度环P

    PID_Calculate(&flyAnglePid,flySpdPid.pos_out+2.5,imu_data.rol);//角度环PD
    printf("A%f\r\n",imu_data.rol);
//    printf("B%f\r\n",temp_x);
    PID_Calculate(&flyAngleSpdPid,flyAnglePid.pos_out,temp_x);//角速度环PI

    motoDutySet(MOTOR_FLY_PIN,(int32_t)flyAngleSpdPid.pos_out);
}

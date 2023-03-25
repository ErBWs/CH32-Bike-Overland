#include "ctrl.h"
#define ANGLE_STATIC_BIAS 4
#define MAIN_PIT   TIM3_PIT
#define GPS_PIT    TIM1_PIT
float dynamic_zero = 0;
void taskTimAllInit(void)
{
    pit_ms_init(MAIN_PIT, 2);
    pit_ms_init(GPS_PIT,100);
//    interrupt_set_priority(TIM6_IRQn, 1);
}
void IMUGetCalFun(void)
{
    IMU_Getdata(&gyro,&acc);
    Data_steepest();
    IMU_update(0.005, &sensor.Gyro_deg, &sensor.Acc_mmss, &imu_data);
}
void ServoControl(void)
{
//    PID_Calculate(&dirPid,0,imu_data.rol);//纯P
//    pwm_set_duty(SERVO_PIN,GetServoDuty(dirPid.pos_out));
    pwm_set_duty(SERVO_PIN,GetServoDuty(dirPid.target[NOW]));
    //printf("A%f\r\n",imu_data.rol);
}
uint32_t back_inter_distance=0;
void BackMotoControl(void)
{
    static uint8 counts=0;
    if(++counts<5)return;
    counts=0;

    int16_t back_wheel_encode=0;

    back_wheel_encode = encoder_get_count(ENCODER_BACK_WHEEL_TIM);
    encoder_clear_count(ENCODER_BACK_WHEEL_TIM);
    back_inter_distance += myABS(back_wheel_encode);

    PID_Calculate(&backSpdPid,backSpdPid.target[NOW],back_wheel_encode);//速度环P
    motoDutySet(MOTOR_BACK_PIN,backSpdPid.pos_out);
}
uint8 stagger_flag=1;
void FlyWheelControl(void)
{
    extern Butter_Parameter Butter_10HZ_Parameter_Acce;
    extern Butter_BufferData Butter_Buffer;
    int16_t fly_wheel_encode=0;
    static uint8 counts=0;

    static uint16 imu_update_counts=0;
    if(imu_update_counts<1500)
        imu_update_counts++;
//    static uint8 delay_2ms=0;
    float temp_x;
    temp_x = LPButterworth(sensor.Gyro_deg.x,&Butter_Buffer,&Butter_10HZ_Parameter_Acce);
    if(++counts>2)
    {
        fly_wheel_encode = encoder_get_count(ENCODER_FLY_WHEEL_TIM);//    printf("A%d\r\n",fly_wheel_encode);
        encoder_clear_count(ENCODER_FLY_WHEEL_TIM);
        PID_Calculate(&flySpdPid,0,fly_wheel_encode);//速度环P
        counts=0;
    }
    PID_Calculate(&flyAnglePid,flySpdPid.pos_out+ANGLE_STATIC_BIAS+dynamic_zero*0,imu_data.rol);//角度环PD    printf("A%f\r\n",imu_data.rol);
    PID_Calculate(&flyAngleSpdPid,flyAnglePid.pos_out,temp_x);//角速度环PI//    printf("B%f\r\n",temp_x);
//    if(++delay_2ms>5)
//    {
//        //printf("A%f\r\n",flyAnglePid.pos_out);
//        printf("A%f\r\n",flyAngleSpdPid.pos_out);
//        delay_2ms=0;
//    }
    if(abs(imu_data.rol)>40)
    {
        stagger_flag=1;
        motoDutySet(MOTOR_FLY_PIN,0);
        flyAngleSpdPid.iout=0;
        return;
    }
    if(stagger_flag==1&&abs(imu_data.rol)<2&&imu_update_counts==1500)
    {
        stagger_flag=0;
        flyAngleSpdPid.iout=0;
    }
    if(stagger_flag==0)
        motoDutySet(MOTOR_FLY_PIN,(int32_t)flyAngleSpdPid.pos_out);
}
void UpdateControl(void)
{
    if(BlueToothData.VelocityVal>10)
    {
        backSpdPid.target[NOW]=5;
    }
    else {
        backSpdPid.target[NOW]=0;
    }
    dirPid.target[NOW]=BlueToothData.TurnVal/1.2;
//    static float last_zero=0;
//    float now_zero;
//    now_zero = 0.7*last_zero+0.3*dirPid.target[NOW];
//    last_zero = now_zero;
//    dynamic_zero = Limitation(dirPid.target[NOW],-5,5);
}

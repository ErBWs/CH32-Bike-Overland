#include "ctrl.h"
#define ANGLE_STATIC_BIAS 4.5

//2,9,10,5,1
#define MAIN_PIT   TIM3_PIT
#define IMU_PIT    TIM4_PIT
uint16 imu_update_counts=0;
float dynamic_zero = 0;
void taskTimAllInit(void)
{
    pit_ms_init(MAIN_PIT, 2);
    pit_ms_init(IMU_PIT,2);
    interrupt_set_priority(TIM3_IRQn, (2<<5) | 2);
    interrupt_set_priority(TIM4_IRQn, (2<<5) | 1);
}
void IMUGetCalFun(void)
{
    if(imu_update_counts<1500)
            imu_update_counts++;
    IMU_Getdata(&gyro,&acc, IMU_ICM);
//    imuGetMagData(&mag_data);
    Data_steepest();
    IMU_update(0.002, &sensor.Gyro_deg, &sensor.Acc_mmss, &imu_data);
//    Inclination_compensation(&mag_data, ICO);
//    Cal_YawAngle(sensor.Gyro_deg.z, &imu_data.mag_yaw);
}
void ServoControl(void)
{
//    PID_Calculate(&dirPid,0,gps_use.delta);//纯P
//    pwm_set_duty(SERVO_PIN,GetServoDuty(dirPid.pos_out));
    pwm_set_duty(SERVO_PIN,GetServoDuty(dirPid.target[NOW]));
//    printf("A%f\r\n",imu_data.rol);
//    dynamic_zero = dirPid.pos_out/15;
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
//    uint8 delay_2ms=0;
    if(imu_update_counts!=1500)return;
//    if(++delay_2ms>5)
//    {
////            printf("A%f\r\n",imu_data.mag_yaw);
//        printf("A%f\r\n",flyAngleSpdPid.delta_out);
//        delay_2ms=0;
//    }

    counts++;
    float temp_x;
    temp_x = LPButterworth(sensor.Gyro_deg.x,&Butter_Buffer,&Butter_10HZ_Parameter_Acce);
    if(counts>=5)
    {
        fly_wheel_encode = encoder_get_count(ENCODER_FLY_WHEEL_TIM);//    printf("A%d\r\n",fly_wheel_encode);
        encoder_clear_count(ENCODER_FLY_WHEEL_TIM);
        PID_Calculate(&flySpdPid,0,fly_wheel_encode);//速度环P
        counts=0;
    }
    else if(counts==2)
    {
        PID_Calculate(&flyAnglePid,flySpdPid.pos_out+ANGLE_STATIC_BIAS+dynamic_zero,imu_data.rol);//角度环PD    printf("A%f\r\n",imu_data.rol);
    }
        PID_Calculate(&flyAngleSpdPid,flyAnglePid.pos_out,temp_x);//角速度环PI//    printf("B%f\r\n",temp_x);


    if(abs(imu_data.rol)>25)
    {
        stagger_flag=1;
        motoDutySet(MOTOR_FLY_PIN,0);
        Bike_Start = 0;//倒下以后停止循迹，需要再次按发车按钮
        return;
    }
    if(stagger_flag==1&&abs(imu_data.rol)<1)
    {
        pidClear(&flySpdPid);
        pidClear(&flyAngleSpdPid);
        stagger_flag=0;
        counts=0;
    }
    if(stagger_flag==0)
    {
        motoDutySet(MOTOR_FLY_PIN,(int32_t)flyAngleSpdPid.pos_out);
    }
}
void UpdateControl(void)
{
    if(BlueToothData.VelocityVal>10&&BlueToothData.VelocityVal<=15)
    {
        backSpdPid.target[NOW]=10;
    }
    else if(BlueToothData.VelocityVal>15)
    {
        backSpdPid.target[NOW]=10;
    }
    else {
        backSpdPid.target[NOW]=0;
    }
    dynamic_zero = BlueToothData.TurnVal/17;
    dirPid.target[NOW]=BlueToothData.TurnVal/1;
//    static float last_zero=0;
//    float now_zero;
//    now_zero = 0.7*last_zero+0.3*dirPid.target[NOW];
//    last_zero = now_zero;
//    dynamic_zero = Limitation(dirPid.target[NOW],-5,5);
}

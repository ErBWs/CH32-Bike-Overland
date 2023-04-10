#include "ctrl.h"
#define ANGLE_STATIC_BIAS 0


#define MAIN_PIT           TIM1_PIT
#define BEEP_AND_KEY_PIT   TIM3_PIT
uint16 imu_update_counts=0;
float dynamic_zero = 0;
void taskTimAllInit(void)
{
    pit_ms_init(MAIN_PIT, 2);
    pit_ms_init(BEEP_AND_KEY_PIT, 10);
    interrupt_set_priority(TIM1_UP_IRQn, (1<<5) | 2);
    interrupt_set_priority(TIM3_IRQn, (2<<5) | 2);
}
float num_float[8];
void IMUGetCalFun(void)
{
    if(imu_update_counts<1500)
            imu_update_counts++;
    IMU_Getdata(&gyro,&acc, IMU_ALL);
    imuGetMagData(&mag_data);
    Data_steepest();
    IMU_update(0.002, &sensor.Gyro_deg, &sensor.Acc_mmss, &imu_data);
    Inclination_compensation(&mag_data, NO_ICO);
    Cal_YawAngle(sensor.Gyro_deg.z, &imu_data.mag_yaw);
//    gpsFusionyaw(gps_tau1201.direction, &imu_data.mag_yaw);

}
#define USE_BLUE_TOOTH 0
void ServoControl(void)
{
#if USE_BLUE_TOOTH==1
    pwm_set_duty(SERVO_PIN,GetServoDuty(dirPid.target[NOW]));
#else
//    static float servo_feedback;
//    servo_feedback = 0.8*servo_feedback+0.2*gps_use.delta;
    static uint8 counts=0;
    if(++counts!=25)return;
    counts=0;
    if(pile_state==1)
    {
        if(pile_update_flag!=1)return;//若绕桩模式下参数没有更新则提前退出
        pile_update_flag=0;
        PID_Calculate(&dirDisPid,dirDisPid.target[NOW],(float)gps_use.points_distance);
    }
    PID_Calculate(&dirPid,dirDisPid.pos_out,(float)gps_use.delta);//纯P
    BlueToothPrintf("servo_input_delta:%f\n",gps_use.delta);
    BlueToothPrintf("servo_out:%f\n",dirPid.pos_out);
    dynamic_zero = dirPid.pos_out/17;
    pwm_set_duty(SERVO_PIN,GetServoDuty(dirPid.pos_out));
#endif
//    printf("A%f\r\n",imu_data.rol);
//    dynamic_zero = dirPid.pos_out/15;
}
uint32_t back_inter_distance=0;
uint8 back_maintain_flag=1;
void BackMotoControl(void)
{
    static uint8 beg_state=0,pitch_state=0;
    static uint8 counts=0;
    if(++counts<5)return;
    counts=0;
    if(stagger_flag==1||Bike_Start==0)
    {
        motoDutySet(MOTOR_BACK_PIN,0);
        return;
    }
    int16_t back_wheel_encode=0;

    back_wheel_encode = encoder_get_count(ENCODER_BACK_WHEEL_TIM);
//    printf("A%d\r\n",-back_wheel_encode);
    encoder_clear_count(ENCODER_BACK_WHEEL_TIM);
    back_inter_distance += myABS(back_wheel_encode);

    PID_Calculate(&backSpdPid,backSpdPid.target[NOW],-back_wheel_encode);//速度环PID
    switch (beg_state) {
        case 0:
            if(back_maintain_flag==1)
            {
                back_inter_distance=0;
                beg_state=1;
            }
        break;
        case 1:
            backSpdPid.pos_out=1500;
            if(back_inter_distance>200)
            {
                pidClear(&backSpdPid);
                back_maintain_flag=0;
                beg_state=0;
            }
        break;
    }
    switch (pitch_state) {
        case 0:
            if(imu_data.pit>15)
            {
                pitch_state=1;
                beep_time = 20;
            }
            break;
        case 1:
            if(imu_data.pit<0)
            {
                backSpdPid.pos_out -= backSpdPid.iout;//消除积分作用
                backSpdPid.iout = 0;
                beep_time = 20;
                pitch_state=0;
            }
            break;
    }
    motoDutySet(MOTOR_BACK_PIN,backSpdPid.pos_out);
}
uint8 stagger_flag=1;
void FlyWheelControl(void)
{
    extern Butter_Parameter Butter_10HZ_Parameter_Acce;
    extern Butter_BufferData Butter_Buffer;
    int16_t fly_wheel_encode=0;
    static uint8 counts=0;

    if(imu_update_counts!=1500)return;
//    uint8 delay_2ms=0;
//    if(++delay_2ms>5)
//    {
////            printf("A%f\r\n",imu_data.mag_yaw);
//        printf("A%f\r\n",flyAngleSpdPid.delta_out);
//        delay_2ms=0;
//    }

    counts++;
    float temp_x;
    temp_x = LPButterworth(sensor.Gyro_deg.x,&Butter_Buffer,&Butter_10HZ_Parameter_Acce);
    if(counts%5 == 0)
    {
        fly_wheel_encode = encoder_get_count(ENCODER_FLY_WHEEL_TIM);//    printf("A%d\r\n",fly_wheel_encode);
//        fly_wheel_encode = fly_wheel_encode*0.8 + last_fly_wheel_encode * 0.2;//速度低通滤波
//        last_fly_wheel_encode = fly_wheel_encode;
        encoder_clear_count(ENCODER_FLY_WHEEL_TIM);
        PID_Calculate(&flySpdPid,0,fly_wheel_encode);//速度环P
//        Fhan_ADRC(&ADRC_SPEED_Controller,flySpdPid.pos_out); //对速度环的输出量进行TD
        counts=0;
    }
    if(counts%2 == 0)
    {
        PID_Calculate(&flyAnglePid, (flySpdPid.pos_out<0?-sqrtf(-flySpdPid.pos_out):sqrtf(flySpdPid.pos_out))+ANGLE_STATIC_BIAS+dynamic_zero,imu_data.rol);//角度环PD    printf("A%f\r\n",imu_data.rol);
    }
        PID_Calculate(&flyAngleSpdPid,flyAnglePid.pos_out,temp_x);//角速度环PI//    printf("B%f\r\n",temp_x);

    if(abs(imu_data.rol)>25)
    {
        stagger_flag=1;
        motoDutySet(MOTOR_FLY_PIN,0);
        return;
    }
    if(stagger_flag==1&&abs(imu_data.rol)<1)
    {
        pidClear(&flySpdPid);
        pidClear(&flyAngleSpdPid);
        stagger_flag=0;
        back_maintain_flag=1;
        counts=0;
    }
    if(stagger_flag==0)
    {
        motoDutySet(MOTOR_FLY_PIN,(int32_t)flyAngleSpdPid.pos_out);
    }
}
void UpdateControl(void)
{
#if USE_BLUE_TOOTH==1
    if(BlueToothData.VelocityVal>10&&BlueToothData.VelocityVal<=15)
    {
        backSpdPid.target[NOW]=10;
    }
    else if(BlueToothData.VelocityVal>15)
    {
        backSpdPid.target[NOW]=15;
    }
    else {
        backSpdPid.target[NOW]=0;
    }
    dynamic_zero = BlueToothData.TurnVal/17;
    dirPid.target[NOW]=BlueToothData.TurnVal/1;
#endif
}

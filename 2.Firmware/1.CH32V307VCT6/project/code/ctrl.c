#include "ctrl.h"
#include "easy_ui.h"

paramType ANGLE_STATIC_BIAS=0.2;


#define MAIN_PIT           TIM1_PIT
#define BEEP_AND_KEY_PIT   TIM3_PIT

uint32_t myTimeStamp = 0;

uint16 imu_update_counts=0;
float dynamic_zero = 0;
extern double X0,Y0;

void taskTimAllInit(void)
{
    pit_ms_init(MAIN_PIT, 2);
    pit_ms_init(BEEP_AND_KEY_PIT, 10);
    interrupt_set_priority(TIM1_UP_IRQn, (1<<5) | 1);
    interrupt_set_priority(TIM3_IRQn, (2<<5) | 2);
}
void IMUGetCalFun(void)
{
    static uint8_t count = 0;
    count++;
    if(imu_update_counts<1500)
            imu_update_counts++;
    static float temp,tempUseFlag = 0;
    IMU_Getdata(&gyro,&acc, IMU_ALL);
    imuGetMagData(&mag_data);
    Data_steepest();
    IMU_update(0.002, &sensor.Gyro_deg, &sensor.Acc_mmss,&mag_data, &imu_data);
    if (Bike_Start == 1)
    {
        INS_U.IMU.acc_x = (float)-imu660ra_acc_x / 4096 * 9.8f;
        INS_U.IMU.acc_y = (float)-imu660ra_acc_y / 4096 * 9.8f;
        INS_U.IMU.acc_z = (float)imu660ra_acc_z / 4096 * 9.8f;
        INS_U.IMU.gyr_x = ANGLE_TO_RAD((float)-imu660ra_gyro_x / 16.4f);
        INS_U.IMU.gyr_y = ANGLE_TO_RAD((float)-imu660ra_gyro_y / 16.4f);
        INS_U.IMU.gyr_z = ANGLE_TO_RAD((float)imu660ra_gyro_z / 16.4f);
        INS_U.IMU.timestamp = myTimeStamp;
        INS_U.MAG.mag_x = (float)imu963ra_mag_x / 3000;
        INS_U.MAG.mag_y = (float)-imu963ra_mag_y / 3000;
        INS_U.MAG.mag_z = (float)-imu963ra_mag_z / 3000;
        INS_U.MAG.timestamp = myTimeStamp;
        myTimeStamp+=2;
        INS_step();
//        BlueToothPrintf("%f\n", Degree_To_360(RAD_TO_ANGLE(INS_Y.INS_Out.psi)) );
    }
    if (gps_tau1201_flag == 1 && Bike_Start==1)
    {
        uint8 state = gps_data_parse();
        if (state == 0)
        {
            int dir = gpio_get_level(D1);
            INS_U.GPS_uBlox.lat = gps_tau1201.latitude * 1e7;
            INS_U.GPS_uBlox.lon = gps_tau1201.longitude * 1e7;
            INS_U.GPS_uBlox.velN = gps_tau1201.speed * 0.51444f * 1e3 * cosf(INS_Y.INS_Out.psi);
            INS_U.GPS_uBlox.velE = gps_tau1201.speed  * 0.51444f * 1e3 * sinf(INS_Y.INS_Out.psi);
            if (dir)
            {
                INS_U.GPS_uBlox.velN *= -1;
                INS_U.GPS_uBlox.velE *= -1;
            }
            INS_U.GPS_uBlox.fixType = 3;
            INS_U.GPS_uBlox.hAcc = gps_tau1201.hdop * 1e3;
            INS_U.GPS_uBlox.vAcc = 0 * 1e3;
            INS_U.GPS_uBlox.sAcc = 0 * 1e3;
            INS_U.GPS_uBlox.numSV = gps_tau1201.satellite_used;
            INS_U.GPS_uBlox.timestamp = myTimeStamp;
            Global_v_now = 0.1f;//gps_tau1201.speed * 0.51444f;
            Global_yaw = (float)Pi_To_2Pi(INS_Y.INS_Out.psi);
            Global_current_node.X =  X0+ INS_Y.INS_Out.x_R;
            Global_current_node.Y =  Y0+ INS_Y.INS_Out.y_R;
        }
        gps_tau1201_flag = 0;
    }
//    if (Bike_Start == 0)
//    {
//        imuGetMagData(&mag_data);
//        Inclination_compensation(&mag_data, NO_ICO);
//        temp = imu_data.mag_yaw;
//    }
//    else if (Bike_Start == 1 && tempUseFlag == 0)
//    {
//        carBodyState.yaw = temp;
//        tempUseFlag = 1;
//    }
//    if (Bike_Start == 1 && tempUseFlag == 1)
//    {
//        Cal_YawAngle(sensor.Gyro_deg.z, &carBodyState.yaw);
//    }
//    if (Bike_Start == 1 && count % 5 == 0 && tempUseFlag == 1)
//    {
//        kalmanVelocityUpdata(&carBodyState,&kalmanVelocity,0.01);
//    }
//    if (Bike_Start == 1 && count % 50 == 0 && tempUseFlag == 1)
//    {
//        if (gps_tau1201_flag == 1)
//        {
//            kalmanDistanceUpdata(&carBodyState,&kalmanDistanceX,&kalmanDistanceY,0.1);
//            gps_tau1201_flag = 0;
//        }
//        count = 0;
//    }
}
#define USE_BLUE_TOOTH 0
void ServoControl(void)
{
#if USE_BLUE_TOOTH==1
    pwm_set_duty(SERVO_PIN,GetServoDuty(dirPid.target[NOW]));
#else
    static uint8 counts=0;
    if(++counts!=20||stagger_flag==1)return;
    counts=0;
    PID_Calculate(&dirPid,dirDisPid.pos_out,(float)gps_use.delta);//纯P
//    dynamic_zero = dirPid.pos_out*4/12;
    uint16 duty_input=GetServoDuty(dirPid.pos_out);
    if(servo_sport_update_flag==0)
    {
        servo_current_duty = duty_input;//记得在缓动不起效果时更新当前duty值
    }
    ServoSportHandler(&duty_input);
    pwm_set_duty(SERVO_PIN,duty_input);
#endif
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
float temp_x;
int16_t fly_wheel_encode=0;
void FlyWheelControl(void)
{
    extern Butter_Parameter Butter_10HZ_Parameter_Acce;
    extern Butter_Parameter Butter_80HZ_Parameter_Acce;
    extern Butter_BufferData Butter_Buffer;

    static uint8 counts=0;

    if(imu_update_counts!=1500)return;
    counts++;

    temp_x = LPButterworth(sensor.Gyro_deg.x,&Butter_Buffer,&Butter_10HZ_Parameter_Acce);
    if(counts%5 == 0)
    {
        fly_wheel_encode = encoder_get_count(ENCODER_FLY_WHEEL_TIM);
        encoder_clear_count(ENCODER_FLY_WHEEL_TIM);
        PID_Calculate(&flySpdPid,0,fly_wheel_encode);//速度环P
        counts=0;
    }
    if(counts%2 == 0)
    {
//        ANGLE_STATIC_BIAS -= fly_wheel_encode * 0.00001f;
//        if (my_abs(ANGLE_STATIC_BIAS)>6)
//        {
//            ANGLE_STATIC_BIAS = ANGLE_STATIC_BIAS<0?-6:6;
//        }
        PID_Calculate(&flyAnglePid, (flySpdPid.pos_out<0?-sqrtf(-flySpdPid.pos_out):sqrtf(flySpdPid.pos_out))+ANGLE_STATIC_BIAS,imu_data.rol);//角度环PD    printf("A%f\r\n",imu_data.rol);
    }
        PID_Calculate(&flyAngleSpdPid,flyAnglePid.pos_out,temp_x);//角速度环PI//    printf("B%f\r\n",temp_x);

    if(abs(imu_data.rol)>20)
    {
        stagger_flag=1;
        ANGLE_STATIC_BIAS = 0.2;
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

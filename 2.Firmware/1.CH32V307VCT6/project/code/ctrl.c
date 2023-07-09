#include "ctrl.h"
#include "easy_ui.h"

paramType ANGLE_STATIC_BIAS=1.2f;


#define MAIN_PIT           TIM1_PIT
#define BEEP_AND_KEY_PIT   TIM3_PIT

uint32_t myTimeStamp = 0;

uint16 imu_update_counts=0;
float dynamic_zero = 0;
extern double X0,Y0;
gps_report_t gpsReport;

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
    IMU_Getdata(&gyro,&acc, IMU_ALL);
    Compass_Read();
    Data_steepest();
    IMU_update(0.002f, &sensor.Gyro_deg, &sensor.Acc_mmss, &imu_data);
    if (gps_read(&gpsReport))
    {
        if(Bike_Start !=0)
        {
            INS_U.GPS_uBlox.lat = gpsReport.lat;
            INS_U.GPS_uBlox.lon = gpsReport.lon;
            INS_U.GPS_uBlox.velN = gpsReport.vel_n_m_s * 1e3;
            INS_U.GPS_uBlox.velE = gpsReport.vel_e_m_s * 1e3;
            INS_U.GPS_uBlox.velD = gpsReport.vel_d_m_s * 1e3;
            INS_U.GPS_uBlox.fixType = gpsReport.fix_type;
            INS_U.GPS_uBlox.hAcc = gpsReport.eph * 1e3;
            INS_U.GPS_uBlox.vAcc = gpsReport.epv * 1e3;
            INS_U.GPS_uBlox.sAcc = gpsReport.s_variance_m_s * 1e3;
            INS_U.GPS_uBlox.numSV = gpsReport.satellites_used;
            INS_U.GPS_uBlox.timestamp = myTimeStamp;
            Global_current_node.X =  X0+ INS_Y.INS_Out.x_R - moveArray.offsetX;
            Global_current_node.Y =  Y0+ INS_Y.INS_Out.y_R - moveArray.offsetY;
            Global_v_now = gpsReport.vel_m_s;
        }
        if(Bike_Start == 2 && stagger_flag == 0)
        {
            moveFilter(&moveArray,INS_Y.INS_Out.x_R,INS_Y.INS_Out.y_R);
        }
    }
    if (Bike_Start !=0)
    {
        INS_U.IMU.acc_x = (float)-imu660ra_acc_x / 4096 * 9.8f;
        INS_U.IMU.acc_y = (float)-imu660ra_acc_y / 4096 * 9.8f;
        INS_U.IMU.acc_z = (float)imu660ra_acc_z / 4096 * 9.8f;
        INS_U.IMU.gyr_x = ANGLE_TO_RAD((float)-imu660ra_gyro_x / 16.4f);
        INS_U.IMU.gyr_y = ANGLE_TO_RAD((float)-imu660ra_gyro_y / 16.4f);
        INS_U.IMU.gyr_z = ANGLE_TO_RAD((float)imu660ra_gyro_z / 16.4f);
        INS_U.IMU.timestamp = myTimeStamp;
        INS_U.MAG.mag_x = Mag_Raw.x;
        INS_U.MAG.mag_y = Mag_Raw.y;
        INS_U.MAG.mag_z = Mag_Raw.z;
        INS_U.MAG.timestamp = myTimeStamp;
        INS_step();

        Global_yaw = (float)Pi_To_2Pi(INS_Y.INS_Out.psi);
    }
    Global_Raw_Yaw = (float)Pi_To_2Pi(atan2f(-Mag_Raw.y,Mag_Raw.x))- (float)ANGLE_TO_RAD(yaw_angle_bias);
    myTimeStamp+=2;
}

#define USE_BLUE_TOOTH 0
void ServoControl(void)
{
    static uint16 input_duty = 0;
    static uint8 counts=0;
    static bool turn_flag=false;
    counts++;
#if USE_BLUE_TOOTH==1
    pwm_set_duty(SERVO_PIN,GetServoDuty(dirPid.target[NOW]));
#else

    if(stagger_flag==1)return;
//    gps_use.delta = gps_use.delta * 0.3 + last_angle * 0.7;
    PID_Calculate(&dirPid,0,(float)gps_use.delta);//纯P

    dynamic_zero = (float)(input_duty- SERVO_MID)*0.008f;

    uint16 duty_temp=GetServoDuty(dirPid.pos_out);
    if(abs(duty_temp-input_duty)> GetServoDuty(2))
        turn_flag = true;
    if(turn_flag ==true)
    {
        if(abs(duty_temp-input_duty)> GetServoDuty(2) && counts%3==0)
        {
            if(duty_temp>input_duty)
                input_duty++;
            else if(duty_temp<input_duty)
                input_duty--;
        }
        else
            turn_flag=false;
    }
    else
    {
        input_duty = duty_temp;
    }


//    if(servo_sport_update_flag==0)
//    {
//        servo_current_duty = input_duty;//记得在缓动不起效果时更新当前duty值
//    }
//    ServoSportHandler(&input_duty);
    pwm_set_duty(SERVO_PIN,input_duty);
#endif
}
uint32_t back_inter_distance=0;
uint8 back_maintain_flag=1;
int16_t back_wheel_encode=0;

void BackMotoControl(void)
{
    static uint8 beg_state=0,pitch_state=0;
    static uint8 counts=0;
    if(++counts<20)return;
    counts=0;
    if(stagger_flag==1||Bike_Start!=1)
    {
        pidClear(&backSpdPid);
        motoDutySet(MOTOR_BACK_PIN,0);
        return;
    }

    back_wheel_encode = encoder_get_count(ENCODER_BACK_WHEEL_TIM);
    encoder_clear_count(ENCODER_BACK_WHEEL_TIM);
    back_inter_distance += myABS(back_wheel_encode);

    PID_Calculate(&backSpdPid,backSpdPid.target[NOW],-(float)back_wheel_encode);//速度环PID
//    switch (beg_state) {
//        case 0:
//            if(back_maintain_flag==1)
//            {
//                back_inter_distance=0;
//                beg_state=1;
//            }
//        break;
//        case 1:
//            backSpdPid.pos_out=2000;
//            if(back_inter_distance>100)
//            {
//                pidClear(&backSpdPid);
//                back_maintain_flag=0;
//                beg_state=0;
//            }
//        break;
//    }
    switch (pitch_state) {
        case 0:
            if(imu_data.pit>15)
            {
//                backSpdPid.target[NOW]=7;
                pitch_state=1;
                beepTime = 400;
            }
            break;
        case 1:
            if(imu_data.pit<1)
            {
//                backSpdPid.target[NOW]=7;

                backSpdPid.pos_out -= backSpdPid.iout;//消除积分作用
                backSpdPid.iout = 0;
                beepTime = 400;
                pitch_state=0;
            }
            break;
    }
    motoDutySet(MOTOR_BACK_PIN,-(int32)backSpdPid.pos_out);
}
uint8 stagger_flag=1;
float temp_x;
int16_t fly_wheel_encode=0;
void FlyWheelControl(void)
{
    extern Butter_Parameter Butter_10HZ_Parameter_Acce;
//    extern Butter_Parameter Butter_80HZ_Parameter_Acce;
    extern Butter_BufferData Butter_Buffer;

    static uint8 counts=0;

    if(imu_update_counts!=1500)return;
    counts++;

    temp_x = LPButterworth(sensor.Gyro_deg.x,&Butter_Buffer,&Butter_10HZ_Parameter_Acce);
    if(counts%3 == 0)//16
    {
        fly_wheel_encode = encoder_get_count(ENCODER_FLY_WHEEL_TIM);
        encoder_clear_count(ENCODER_FLY_WHEEL_TIM);
        PID_Calculate(&flySpdPid,0,fly_wheel_encode);//速度环P
        counts=0;
    }
    if(counts%2 == 0)//4
    {
//        ANGLE_STATIC_BIAS -= fly_wheel_encode * 0.00001f;
//        if (my_abs(ANGLE_STATIC_BIAS)>6)
//        {
//            ANGLE_STATIC_BIAS = ANGLE_STATIC_BIAS<0?-6:6;
//        }
        PID_Calculate(&flyAnglePid, (flySpdPid.pos_out<0?-sqrtf(-flySpdPid.pos_out):sqrtf(flySpdPid.pos_out))+ANGLE_STATIC_BIAS+dynamic_zero,imu_data.rol);//角度环PD    printf("A%f\r\n",imu_data.rol);
    }
        PID_Calculate(&flyAngleSpdPid,flyAnglePid.pos_out,temp_x);//角速度环PI//    printf("B%f\r\n",temp_x);

    if(abs(imu_data.rol)>40)
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

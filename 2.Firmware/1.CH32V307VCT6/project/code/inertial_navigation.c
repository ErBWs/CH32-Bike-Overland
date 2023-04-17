/*
 * inertial_navigation.c
 *
 *  Created on: Mar 24, 2023
 *      Author: sorrymaker
 */

#include "inertial_navigation.h"


_gps_st gps_data_array[GPS_MAX_POINT] = {0};
_gps_st gps_data = {0};
_gps_use_st gps_use = {0};

EasyKey_t key_read, key_write;
uint8 write_key_flag=0;
uint8 read_key_flag=0;
uint8 main_key_flag=0;
uint8 Bike_Start = 0;
void GPS_init(void)
{
    gps_init();
}
void gps_handler(uint8_t pointStatus) {
    uint8 state = gps_data_parse();
    
    if (opnEnter)
    {
        opnEnter = false;
        flash_buffer_clear();
        if (state == 0 && (gps_tau1201.hdop < 1)) {
            EasyUIDrawMsgBox("Saving...");
            beep_time = 20;
            gps_data_array[gps_use.point_count].latitude = gps_tau1201.latitude;
            gps_data_array[gps_use.point_count].longitude = gps_tau1201.longitude;
            gps_data_array[gps_use.point_count].type = pointStatus;
            gps_use.point_count++;
        }
        else
        {
            EasyUIDrawMsgBox("Error!");
        }
    }
    if (opnForward)
    {

    }
    if (opnExit)
    {
    }
}

void gpsStateCheck(void)
{
    pointsStatusCheck();
    switch (gps_data.type)
    {
        case COMMON:
        {
            normalHandler();
            break;
        }
        case PILE:
        {
            pileHandler();
            break;
        }
        case OTHER:
        {
            
            break;
        }
        case STOP:
        {
//            stagger_flag=1;
//            motoDutySet(MOTOR_FLY_PIN,0);
            functionIsRunning = false;
            beep_time = 70;
            Bike_Start = 0;
            break;
        }
    }
}

void normalHandler(void)
{
    if(gps_tau1201_flag==1)
    {
        uint8 gps_state = gps_data_parse();
        if(gps_state==0)//&&gps_tau1201.hdop<0.8
        {
            GetPoint(gps_tau1201.latitude, gps_tau1201.longitude,&gps_data);
            gps_use.delta = yaw_gps_delta(gps_use.points_azimuth, imu_data.mag_yaw);

        }
        gps_tau1201_flag=0;
    }
//    else
//    {
//        gps_use.delta = yaw_gps_delta(gps_use.points_azimuth, imu_data.mag_yaw);
//    }
}

void pileHandler(void)
{
    static uint8 state=0;
    switch(state)
    {
        case 0:
            beep_time = 20;
            gps_use.z_angle=0;
            gps_use.delta = -160;
            state = 1;
        break;
        case 1:
            if (gps_use.z_angle >= 360)
            {
                beep_time = 40;
                gps_data = gps_data_array[gps_use.use_point_count];
                gps_use.use_point_count++;
                state = 0;
            }
        break;
    }
}

void pointsStatusCheck(void)
{
//    if (gps_data_array[gps_use.point_count].type == PILE)
//    {
//        gps_data.type = PILE;
//    }
//    if (gps_data_array[gps_use.point_count].type == OTHER)
//    {
//        gps_data.type = OTHER;
//    }
    if(gps_use.use_point_count>gps_use.point_count)
    {
        gps_data.type = STOP;
    }
}

void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data,_gps_two_point_st *gps_result)
{
    double gps_distance,gps_azimuth;
    //更新当前的位置姿态
    gps_distance = get_two_points_distance(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);
    gps_azimuth = get_two_points_azimuth(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);

    gps_result->points_distance = gps_distance;
    gps_result->points_azimuth = gps_azimuth;
}

float yaw_gps_delta( float azimuth, float yaw)
{
    float delta;
    //0<azimut<90
    if(azimuth>=0&&azimuth<90)
    {
        if (yaw>=0&&yaw<azimuth)
        {
            delta = azimuth - yaw;
            return delta;
        }
        else if (yaw>=(azimuth+180)&&yaw<360)
        {
            delta = 360 - yaw + azimuth;
            return delta;
        }
        else
        {
            delta = yaw - azimuth;
            return -delta;
        }
    }
    //90<azimut<180
    if (azimuth>=90&&azimuth<180)
    {
       if (yaw>=0 && yaw<azimuth)
       {
           delta = azimuth - yaw;
           return delta;
       }
       else if(yaw>=(azimuth+180)&&yaw<360)
       {
           delta = 360-yaw+azimuth;
           return delta;
       }
       else
       {
           delta = yaw - azimuth;
           return -delta;
       }
    }
    //180<azimut<270
    if (azimuth>=180&&azimuth<270)
    {
        if (yaw>=(azimuth-180)&&yaw<azimuth)
        {
            delta = azimuth - yaw;
            return delta;
        }
        else if (yaw>=0 && yaw<(azimuth-180))
        {
            delta = 360 - azimuth + yaw;
            return -delta;
        }
        else if(yaw>=azimuth && yaw<360)
        {
            delta = yaw - azimuth;
            return -delta;
        }
    }
    //270<azimut<360
    if (azimuth>=270&&azimuth<=360)
    {
        if (yaw>=(azimuth-180)&&yaw<azimuth)
        {
            delta = azimuth - yaw;
            return delta;
        }
        else if (yaw>=azimuth&&yaw<360)
        {
            delta = yaw - azimuth;
            return -delta;
        }
        else
        {
            delta = 360 - azimuth + yaw;
            return -delta;
        }
    }
}

uint8 GetPointAdvance(double latitude_now, double longitude_now,_gps_st *gpsData)//只能在解析完数据后才能调用此函数
{
    double min_distance;
    double min_azimuth = 0;
    uint8 state = 0;
    uint8 i,k;
    uint8 min_index = gps_use.use_point_count-1;//假设以当前的目标点作为最小点
    int16 forecase_depth = EXTRA_FORECAST_POINT;
    _gps_two_point_st gps_result;

    while(1)
    {
        if(gps_use.use_point_count>gps_use.point_count)
        {
            state = 1;
            break;
        }
        two_points_message(latitude_now,longitude_now,&gps_data_array[min_index],&gps_result);
        min_distance = gps_result.points_distance;//以当前目标点作为缺省点
        min_azimuth = gps_result.points_azimuth;
        if(gps_use.use_point_count+forecase_depth>=gps_use.point_count)
        {
            forecase_depth = (gps_use.point_count-1)-gps_use.use_point_count;//动态深度更新
            forecase_depth = forecase_depth<-1?-1:forecase_depth;
        }
        for(i=gps_use.use_point_count;i<=gps_use.use_point_count+forecase_depth;i++)//筛选出指顶前瞻区间内的距离最短且满足给定距离的导航点
        {
            two_points_message(latitude_now,longitude_now,&gps_data_array[i],&gps_result);
            if(gps_result.points_distance<min_distance)
            {
                min_index = i;
                min_distance = gps_result.points_distance;
                min_azimuth = gps_result.points_azimuth;
            }
        }
        if(min_distance<DISTANCE_LIMITATION)
        {
            for(k=min_index;k>=gps_use.use_point_count;k--)//禁用下一个目标点以及前面可能已经略过的导航节点
            {
                gps_data_array[k].is_used = 1;
                gps_use.use_point_count++;
            }
            if(min_index+1 < gps_use.point_count)
            {
                *gpsData = gps_data_array[min_index + 1];//赋予新的目标点
                gps_use.use_point_count++;
                printf("CHANGE-POINT\n");
            }
            else {
                printf("OVER-OF-POINTS\n");
                gps_use.use_point_count++;//已经到达终点
            }
        }
        else
        {
            printf("distance last=%f\n",gps_result.points_distance);
        }
        break;
    }
    return state;
}

void GetPoint(double latitude_now, double longitude_now,_gps_st *gps_data)
{
    _gps_two_point_st gps_result;
        if(gps_use.use_point_count>gps_use.point_count)
        {

        }
        two_points_message(latitude_now, longitude_now, gps_data, &gps_result);
        if(gps_result.points_distance<DISTANCE_LIMITATION)
        {
            *gps_data = gps_data_array[gps_use.use_point_count];
            gps_data->is_used = 1;
            gps_use.use_point_count++;
//            printf("CHANGE-POINT\n");
            beep_time=20;
        }
        else
        {
//            printf("distance last=%f\n",gps_result.points_distance);
//            BlueToothPrintf("distance last=%f\n",gps_result.points_distance);
        }
    gps_use.points_distance = gps_result.points_distance;
    gps_use.points_azimuth = gps_result.points_azimuth;
}
uint8 navigate_forbid = 0;
uint8 pile_update_flag=0;
uint8 circle_fitting_flag=0;
void pileProcess(double latitude_now, double longitude_now,_gps_st *gpsData)
{
    static uint8 state =0;
    static float last_yaw;
    static float beg_yaw;
    static uint8 dir;
    static uint8 dir_change_flag=0;
    _gps_two_point_st gps_result;
    switch(state)
    {
        case 0:
            if(gpsData->type == 1)//如果是绕桩点
            {
                dir = gps_use.delta<0?0:1;//判断绕行方向，0为逆时针，1为顺时针
                last_yaw = beg_yaw = imu_data.mag_yaw;
                dirDisPid.target[NOW] = 2;//距离环设定为2米，即绕桩半径为2m
                navigate_forbid = 1;
                state=1;
            }
        break;
        case 1:
            two_points_message(latitude_now, longitude_now, gpsData, &gps_result);
            gps_use.delta+=gps_use.delta>=0?-90:90;
            gps_use.points_distance = gps_result.points_distance;
            pile_update_flag=1;//置位更新标志位
            if(dir==0)
            {
                if(yaw_gps_delta(last_yaw,imu_data.mag_yaw)>0)//逆时针转有效
                    last_yaw = imu_data.mag_yaw;
                if(dir_change_flag==0&&yaw_gps_delta(last_yaw,beg_yaw)<0)
                {
                    TONE_PLAY(SO,10);
                    TONE_PLAY(DO,10);
                    dir_change_flag=1;
                }
                else if(dir_change_flag==0&&yaw_gps_delta(last_yaw,beg_yaw)>0)
                {
                    dir_change_flag=0;
                    state = 2;
                }
            }
            else if(dir==1)
            {
                if(yaw_gps_delta(last_yaw,imu_data.mag_yaw)<0)//顺时针转有效
                    last_yaw = imu_data.mag_yaw;
                if(dir_change_flag==0&&yaw_gps_delta(last_yaw,beg_yaw)>0)
                {
                    TONE_PLAY(SO,10);
                    TONE_PLAY(DO,10);
                    dir_change_flag=1;
                }
                else if(dir_change_flag==1&&yaw_gps_delta(last_yaw,beg_yaw)<0)
                {
                    dir_change_flag=0;
                    state = 2;
                }
            }
        break;
        case 2:
            dirDisPid.target[NOW] = 0;
            TONE_PLAY(DO,10);
            TONE_PLAY(SO,10);
            *gpsData = gps_data_array[gps_use.use_point_count];
            gpsData->is_used = 1;
            gps_use.use_point_count++;
            printf("CHANGE-POINT\n");
            navigate_forbid = 0;
            state=0;
        break;
        default:
            printf("logical error!\n");
        break;
    }
}
void pileProcess2(_gps_st *gpsData)
{
    static uint8 state =0;
    static _gps_st beg_point;
    _gps_two_point_st gps_result;
    double bias=0;
    static uint8 dir=255;
    switch(state)
    {
        case 0:
            if(gpsData->type == 1)//如果是绕桩起点
            {
                beg_point = *gpsData;//存储开始的导航点
                state=1;
            }
        break;
        case 1:
            if(gpsData->type == 2)//若转换到了桩的中心点
            {
                printf("Begin Pile\n");
                beep_feq = SO;
                beep_time=30;
                navigate_forbid = 1;//禁用换点函数，但仍然解析当前与目标点（即桩的中心点）
                circle_fitting_flag = 1;//取消原本角度解算方法，改用state=2里的方法,但导航目标点的解算仍然进行
                state = 2;
            }
        break;
        case 2:
            bias = yaw_gps_delta(gps_use.points_azimuth, imu_data.mag_yaw);
            if(dir==255)
                dir = bias<0?0:1;//0:逆时针，1:顺时针
            bias += bias>=0?-90:90;
            gps_use.delta = bias;
            if(fabs(bias)<ANGLE_BIAS_THRESHOLD)//满足偏差条件，开始绕弯并进行角度积分
            {
                if(dir==0)
                    ServoSportSet(GetServoDuty(-10),20);
                else
                    ServoSportSet(GetServoDuty(10),20);
                beep_feq = DO;
                beep_time = 30;
                gps_use.z_angle = 0;
                gps_data = beg_point;//将初始的点变为导航的目标点
                state=3;
            }
        break;
        case 3:
            if(gps_use.points_distance<DISTANCE_LIMITATION)
            {
                state = 4;
            }
        break;
        case 4:
            if((gps_use.z_angle<-360&&dir==0)||(gps_use.z_angle>360&&dir==1))
            {
                ServoSportSet(GetServoDuty(0),30);
                beep_feq = DO1;
                beep_time = 70;
                circle_fitting_flag = 0;//恢复正常的delta解算方法
                navigate_forbid = 0;//恢复导航
                dir=255;
                state = 0;
            }
        break;
        default:
            printf("error");
        break;
    }
}
static uint16_t duty_target=0;
static int32_t servo_step_duty;
static int32_t duty_err;
uint8 servo_sport_update_flag = 0;//若该标志位置1，则外部不能有强行修改servo_current_duty的行为；
uint16 servo_current_duty = GetServoDuty(0);
void ServoSportSet(uint16_t duty_value,int32_t ticks)
{
    duty_target = duty_value;
    duty_err = duty_value- servo_current_duty;
    servo_step_duty = duty_err/ticks;
    servo_step_duty = servo_step_duty!=0?servo_step_duty:duty_err>0?1:-1;
    servo_sport_update_flag = 1;
}
void ServoSportHandler(uint16 *duty_input)
{
    static uint32 last_ticks=1LL << 31;
    uint16 input_pwm_duty=servo_current_duty;//(TIM2->CH1CVR*PWM_DUTY_MAX)/TIM2->ATRLR;
    if(now_tick>last_ticks&&servo_sport_update_flag==1)
    {
        last_ticks = now_tick;
        duty_err-=servo_step_duty;
        if((servo_step_duty<0&&duty_err>=0)||(servo_step_duty>0&&duty_err<=0))
        {
            servo_sport_update_flag = 0;
            duty_err = 0;
            input_pwm_duty = duty_target;
        }
        else{
            input_pwm_duty += servo_step_duty;
            input_pwm_duty = input_pwm_duty<0?0:input_pwm_duty>=PWM_DUTY_MAX?PWM_DUTY_MAX-1:input_pwm_duty;
        }
    }
    *duty_input = input_pwm_duty;
    servo_current_duty = input_pwm_duty;
}


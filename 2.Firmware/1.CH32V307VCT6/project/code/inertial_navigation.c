/*
 * inertial_navigation.c
 *
 *  Created on: Mar 24, 2023
 *      Author: sorrymaker
 */

#include "inertial_navigation.h"


_gps_st gps_data_array[GPS_MAX_POINT] = {0};
_gps_st gps_data;
_gps_use_st gps_use;
double first_point_latitude, first_point_longitude, second_point_latitude, second_point_longitude;

EasyKey_t key_read, key_write;
uint8 write_key_flag=0;
uint8 read_key_flag=0;
uint8 main_key_flag=0;
uint8 Bike_Start = 0;
void GPS_init(void)
{
    gps_init();
    exti_init(B0,EXTI_TRIGGER_BOTH);//r
    exti_init(D8,EXTI_TRIGGER_BOTH);//w
}
void gps_handler(void)
{
    uint8 state = gps_data_parse();
    static uint8_t writeStatus = 0;
    
    if (opnEnter)
    {
        if(writeStatus==0)
        {
            writeStatus=1;
            EasyUIDrawMsgBox("EnterSavingMode");
            flash_buffer_clear();
            memset(gps_data_array,0,sizeof(_gps_st)*GPS_MAX_POINT);//清空数组准备录入新的数据
            memset(&gps_use,0,sizeof(_gps_use_st));//清空记录信息准备录入新的数据
        }
        opnEnter = false;
        flash_buffer_clear();
        if (state == 0 && (gps_tau1201.hdop < 1.0))
        {
            EasyUIDrawMsgBox("Saving...");
            beep_time=20;
            gps_data_array[gps_use.point_count].latitude = gps_tau1201.latitude;
            gps_data_array[gps_use.point_count].longitude = gps_tau1201.longitude;
            gps_use.point_count++;
        }
        else
        {
            EasyUIDrawMsgBox("Error!");
        }
    }
    if (opnForward)
    {
        opnForward = false;
        if(writeStatus == 0)
        {
            flash_buffer_clear();
            memset(gps_data_array, 0, sizeof(_gps_st) * GPS_MAX_POINT);//清空数组准备录入新的数据
            memset(&gps_use, 0, sizeof(_gps_use_st));//清空记录信息准备录入新的数据
            double count;
            GPSReadFlashWithConversion(&count);//写完点后取消读点模式，以便下一次随时进入写点模式。
            gps_use.point_count = (uint8) count;
            for (uint8 k = 0; k < gps_use.point_count; k++) {
                GPSReadFlashWithConversion(&gps_data_array[k].latitude);
                GPSReadFlashWithConversion(&gps_data_array[k].longitude);
            }
            gps_data_array[0].is_used = 1;//设为已用状态
            gps_data = gps_data_array[0];//获得第一个目标点
            gps_use.use_point_count = 1;
        }
    }
    if (opnExit)
    {
        EasyUIDrawMsgBox("Saving to Flash...");
//        EasyUIBackgroundBlur();
        writeStatus = 0;
        if(gps_use.point_count!=0)
        {
            double count = gps_use.point_count;
            GPSSaveToFlashWithConversion(&count);
            for(uint32 k=0;k<gps_use.point_count;k++)
            {
                GPSSaveToFlashWithConversion(&gps_data_array[k].latitude);
                GPSSaveToFlashWithConversion(&gps_data_array[k].longitude);
            }
            gps_data_array[0].is_used = 1;//设为已用状态
            gps_data = gps_data_array[0];//获得第一个目标点
            gps_use.use_point_count=1;
            GPSFlashOperationEnd();
        }
//        opnExit = false;//bug!!!
    }
}

/*
void gps_handler(void)
{
    static uint8 write_keep_flag=0;
    if(key_write.isPressed)
    {
        printf("sat:%d\n",gps_tau1201.satellite_used);
    }
    if(write_keep_flag==0&&write_key_flag==2)
    {
        
        flashBufIndex = 0;
        flashSecIndex = 63;
        flashPageIndex = 3;

        flash_buffer_clear();
        memset(gps_data_array,0,sizeof(_gps_st)*GPS_MAX_POINT);//清空数组准备录入新的数据
        memset(&gps_use,0,sizeof(_gps_use_st));//清空记录信息准备录入新的数据
        write_keep_flag = 1;
        write_key_flag = 0;
    }
    while(gps_use.point_count < GPS_MAX_POINT&&write_keep_flag==1)
    {
        if(gps_tau1201_flag==1) {
            uint8 state = gps_data_parse();
            if (state == 0) {
                if (write_key_flag == 2) {
                    write_key_flag = 0;
                    write_keep_flag = 0;//写完点后取消读点模式，以便下一次随时进入写点模式。
                    double count = gps_use.point_count;
                    SaveToFlashWithConversion(&count);
                    for (uint8 k = 0; k < gps_use.point_count; k++) {
                        SaveToFlashWithConversion(&gps_data_array[k].latitude);
                        SaveToFlashWithConversion(&gps_data_array[k].longitude);
                    }
                    FlashOperationEnd();
                    gps_data_array[0].is_used = 1;//设为已用状态
                    gps_data = gps_data_array[0];//获得第一个目标点
                    gps_use.use_point_count = 1;
                    break;
                }
                if ((write_key_flag == 1 || read_key_flag == 3) && write_keep_flag == 1) {
                    if (gps_tau1201.state && (gps_tau1201.satellite_used >= 4) && gps_tau1201.hpdo < 0.75) {
                        printf("gps_state:%d\r\n", gps_tau1201.state);
                        printf("gps_satellite:%d\r\n", gps_tau1201.satellite_used);
                        printf("save successful\r\n");
                        printf("gps_point : %d\r\n", gps_use.point_count);
                        printf("latitude:%.9f\r\n", gps_tau1201.latitude);
                        printf("longitude:%.9f\r\n", gps_tau1201.longitude);
                        BlueToothPrintf("\ngps_satellite:%d\r\n", gps_tau1201.satellite_used);
                        BlueToothPrintf("gps_point : %d\r\n", gps_use.point_count);
                        BlueToothPrintf("latitude:%.9f\r\n", gps_tau1201.latitude);
                        BlueToothPrintf("longitude:%.9f\r\n", gps_tau1201.longitude);
                        gps_data_array[gps_use.point_count].latitude = gps_tau1201.latitude;
                        gps_data_array[gps_use.point_count].longitude = gps_tau1201.longitude;
                        if(read_key_flag == 3)
                        {
                            TONE_PLAY(DO,10);
                            TONE_PLAY(RE,10);
                            TONE_PLAY(MI,10);
                            gps_data_array[gps_use.point_count].type = 1;
                            read_key_flag = 0;
                        }
                        gps_use.point_count++;
                        ips114_show_int(10, 32, gps_use.point_count, 2);
                    } else {
                        printf("satellite-couts:%d", gps_tau1201.satellite_used);
                    }
                    write_key_flag = 0;
                }
            }
            gps_tau1201_flag = 0;
        }
     }
    if(write_keep_flag == 1&&gps_use.point_count==GPS_MAX_POINT)//当读点达到上限的时候清除读点模式并写入Flash
    {
        write_keep_flag = 0;
        double count = gps_use.point_count;
        SaveToFlashWithConversion(&count);
        for(uint32 k=0;k<gps_use.point_count;k++)
        {
             SaveToFlashWithConversion(&gps_data_array[k].latitude);
             SaveToFlashWithConversion(&gps_data_array[k].longitude);
        }
        FlashOperationEnd();
        gps_data_array[0].is_used = 1;//设为已用状态
        gps_data = gps_data_array[0];//获得第一个目标点
        gps_use.use_point_count=1;
    }
    if(read_key_flag==1)//从Flash读点，通常在不写点的时候起作用。写点完成后无须read。
    {
        flashBufIndex = 0;
        flashSecIndex = 63;
        flashPageIndex = 3;
        flash_buffer_clear();
        memset(gps_data_array,0,sizeof(_gps_st)*GPS_MAX_POINT);//清空数组准备录入新的数据
        memset(&gps_use,0,sizeof(_gps_use_st));//清空记录信息准备录入新的数据
        double count;
        ReadFlashWithConversion(&count);//写完点后取消读点模式，以便下一次随时进入写点模式。
        gps_use.point_count=(uint8)count;
        for(uint8 k=0;k<gps_use.point_count;k++)
        {
            ReadFlashWithConversion(&gps_data_array[k].latitude);
            ReadFlashWithConversion(&gps_data_array[k].longitude);
        }
        gps_data_array[0].is_used = 1;//设为已用状态
        gps_data = gps_data_array[0];//获得第一个目标点
        gps_use.use_point_count=1;
        read_key_flag = 0;
        printf("total:%d\n",gps_use.point_count);
        for(uint16 k=0;k<gps_use.point_count;k++)
        {
            printf("the %d point's comformation:\nlatitude:%f\nlongitude:%f\n",k,gps_data_array[k].latitude,gps_data_array[k].longitude);
        }
    }

    if (main_key_flag==1) {//发车
        if(gps_use.point_count!=0)
        {
            TONE_PLAY(DO,100);
            TONE_PLAY(DO1,20);
            Bike_Start = 1;
        }
        main_key_flag = 0;
    }
}
*/

void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data,_gps_two_point_st *gps_result)
{
    double gps_distance,gps_azimuth;
    //更新当前的位置姿态
    gps_distance = get_two_points_distance(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);
    gps_azimuth = get_two_points_azimuth(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);

    gps_result->points_distance = gps_distance;
    gps_result->points_azimuth = gps_azimuth;
//        printf("%f\n",gps_data->latitude);
//        printf("%f\n",gps_data->longitude);
//        printf("%.9f\n",gps_result->points_distance);
//        printf("%.9f\n",gps_result->points_azimuth);

}

double yaw_gps_delta( float azimuth, float yaw)
{
    double delta;
    //0<azimut<90
    if(azimuth>0&&azimuth<90)
    {
        if (yaw>0&&yaw<azimuth)
        {
            delta = azimuth - yaw;
            return delta;
        }
        else if (yaw>(azimuth+180)&&yaw<360)
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
    if (azimuth>90&&azimuth<180)
    {
       if (yaw>0 && yaw<azimuth)
       {
           delta = azimuth - yaw;
           return delta;
       }
       else if(yaw>(azimuth+180)&&yaw<360)
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
    if (azimuth>180&&azimuth<270)
    {
        if (yaw>(azimuth-180)&&yaw<azimuth)
        {
            delta = azimuth - yaw;
            return delta;
        }
        else if (yaw>0 && yaw<(azimuth-180))
        {
            delta = 360 - azimuth + yaw;
            return -delta;
        }
        else if(yaw>azimuth && yaw<360)
        {
            delta = yaw - azimuth;
            return -delta;
        }
    }
    //270<azimut<360
    if (azimuth>270&&azimuth<360)
    {
        if (yaw>(azimuth-180)&&yaw<azimuth)
        {
            delta = azimuth - yaw;
            return delta;
        }
        else if (yaw>azimuth&&yaw<360)
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


#define EXTRA_FORECAST_POINT 0
#define DISTANCE_LIMITATION 1
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

uint8 GetPoint(double latitude_now, double longitude_now,_gps_st *gpsData)
{
    uint8 state=0;
    _gps_two_point_st gps_result;
    while(1)
    {
        if(gps_use.use_point_count>gps_use.point_count)
        {
            state=1;
            break;
        }
        two_points_message(latitude_now, longitude_now, gpsData, &gps_result);
        if(gps_result.points_distance<DISTANCE_LIMITATION)
        {
            *gpsData = gps_data_array[gps_use.use_point_count];
            gpsData->is_used = 1;
            gps_use.use_point_count++;
            printf("CHANGE-POINT\n");
            beep_time=20;
        }
        else
        {
            printf("distance last=%f\n",gps_result.points_distance);
            BlueToothPrintf("distance last=%f\n",gps_result.points_distance);
        }
        break;
    }
    return state;
}
uint8 pile_state = 0;
uint8 pile_update_flag=0;
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
                pile_state = 1;
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
            dirDisPid.target[NOW] = 0;//距离环设定为2米，即绕桩半径为2m
            TONE_PLAY(DO,10);
            TONE_PLAY(SO,10);
            *gpsData = gps_data_array[gps_use.use_point_count];
            gpsData->is_used = 1;
            gps_use.use_point_count++;
            printf("CHANGE-POINT\n");
            pile_state = 0;
            state=0;
        break;
        default:
            printf("logical error!\n");
        break;
    }
}


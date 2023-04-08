/*
 * inertial_navigation.c
 *
 *  Created on: Mar 24, 2023
 *      Author: sorrymaker
 */

#include "inertial_navigation.h"


_gps_st gps_data_array[GPS_MAX_POINT];
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
    static uint8 write_keep_flag=0;
    if(key_write.isPressed)
    {
        printf("sat:%d\n",gps_tau1201.satellite_used);
    }
    if(write_keep_flag==0&&write_key_flag==2)
    {
        /*初始化buff指针*/
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
        if(gps_tau1201_flag==1)
        {
            uint8 state = gps_data_parse();
            if(state==0)
            {
                if(write_key_flag==2)
                {
                    write_key_flag = 0;
                    write_keep_flag = 0;//写完点后取消读点模式，以便下一次随时进入写点模式。
                    double count = gps_use.point_count;
                    SaveToFlashWithConversion(&count);
                    for(uint8 k=0;k<gps_use.point_count;k++)
                    {
                         SaveToFlashWithConversion(&gps_data_array[k].latitude);
                         SaveToFlashWithConversion(&gps_data_array[k].longitude);
                    }
                    FlashOperationEnd();
                    gps_data_array[0].is_used = 1;//设为已用状态
                    gps_data = gps_data_array[0];//获得第一个目标点
                    gps_use.use_point_count=1;
                    break;
                }
                if(write_key_flag==1&&write_keep_flag==1)
                {
                     if (gps_tau1201.state && (gps_tau1201.satellite_used >= 4))
                     {
                         printf("gps_state:%d\r\n",gps_tau1201.state);
                         printf("gps_satellite:%d\r\n",gps_tau1201.satellite_used);
                         printf("save successful\r\n");
                         printf("gps_point : %d\r\n",gps_use.point_count);
                         printf("latitude:%.9f\r\n",gps_tau1201.latitude);
                         printf("longitude:%.9f\r\n",gps_tau1201.longitude);
                         BlueToothPrintf("\ngps_satellite:%d\r\n",gps_tau1201.satellite_used);
                         BlueToothPrintf("gps_point : %d\r\n",gps_use.point_count);
                         BlueToothPrintf("latitude:%.9f\r\n",gps_tau1201.latitude);
                         BlueToothPrintf("longitude:%.9f\r\n",gps_tau1201.longitude);
                         gps_data_array[gps_use.point_count].latitude = gps_tau1201.latitude;
                         gps_data_array[gps_use.point_count].longitude = gps_tau1201.longitude;
                         gps_use.point_count++;
                         ips114_show_int(10, 32, gps_use.point_count, 2);
                     }
                     else
                     {
                         printf("satellite-couts:%d",gps_tau1201.satellite_used);
                     }
                     write_key_flag = 0;
                }
            }
            gps_tau1201_flag=0;
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
        /*初始化buff指针*/
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
            Bike_Start = 1;
        }
        main_key_flag = 0;
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
//        printf("%f\n",gps_data->latitude);
//        printf("%f\n",gps_data->longitude);
//        printf("%.9f\n",gps_result->points_distance);
//        printf("%.9f\n",gps_result->points_azimuth);

}

float yaw_gps_delta( float azimuth, float yaw)
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
uint8 GetPointAdvance(double latitude_now, double longitude_now,_gps_st *gps_data)//只能在解析完数据后才能调用此函数
{
    double min_distance;
    double min_azimuth;
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
                *gps_data = gps_data_array[min_index+1];//赋予新的目标点
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

uint8 GetPoint(double latitude_now, double longitude_now,_gps_st *gps_data)
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
        two_points_message(latitude_now,longitude_now,gps_data,&gps_result);
        if(gps_result.points_distance<DISTANCE_LIMITATION)
        {
            *gps_data = gps_data_array[gps_use.use_point_count];
            gps_data->is_used = 1;
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
    gps_use.points_distance=gps_result.points_distance;
    gps_use.points_azimuth=gps_result.points_azimuth;
    return state;
}




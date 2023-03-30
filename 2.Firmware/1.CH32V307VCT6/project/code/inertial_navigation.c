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
uint8 Bike_Start = 0;
void GPS_init(void)
{
    gps_init();
//    EasyKeyInit(&key_read, B0);
//    EasyKeyInit(&key_write, B12);
    exti_init(B0,EXTI_TRIGGER_FALLING);//r
    exti_init(D8,EXTI_TRIGGER_BOTH);//w
//    while(1)
//   {
//        if(read_key_flag==1)
//        {
//            read_key_flag = 0;
//        }
//        if(write_key_flag==1)
//        {
//            write_key_flag = 0;
//        }
//   }
    gps_handler();
}

void gps_handler(void)
{
    static uint8 write_keep_flag=0;
    if(write_key_flag==2&&write_keep_flag==0)
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
                     for(uint32 k=0;k<gps_use.point_count;k++)
                     {
                         SaveToFlashWithConversion(&gps_data_array[k].latitude);
                         SaveToFlashWithConversion(&gps_data_array[k].longitude);
                     }
                     FlashOperationEnd();
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
                         gps_data_array[gps_use.point_count] = gps_data;
                         gps_use.point_count++;
                     }
                     else
                     {
                         printf("gps_state error");
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
        ReadFlashWithConversion(&count);//获取原先的点数
        gps_use.point_count=count;
        for(uint16 k=0;k<gps_use.point_count;k++)
        {
            ReadFlashWithConversion(&gps_data_array[k].latitude);
            ReadFlashWithConversion(&gps_data_array[k].longitude);
        }
        gps_data = gps_data_array[0];//获得第一个目标点
        read_key_flag = 0;
    }
    else if (read_key_flag==2) {//发车
        if(gps_use.point_count!=0)
        {
            Bike_Start = 1;
        }
    }
}


void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data)
{
    double gps_distance,gps_azimuth;
    if (gps_use.use_point_count > GPS_MAX_POINT)
    {
        printf("no_other_gps_points\r\n");
    }
    else
    {
        //更新当前的位置姿态
        gps_distance = get_two_points_distance(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);
        gps_azimuth = get_two_points_azimuth(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);

        gps_use.points_distance = gps_distance;
        gps_use.points_azimuth = gps_azimuth;
//        printf("%f\n",gps_data->latitude);
//        printf("%f\n",gps_data->longitude);
        printf("%.9f\n",gps_use.points_distance);
        printf("%.9f\n",gps_use.points_azimuth);
    }
}

double yaw_gps_delta( double azimuth, double yaw)
{
    double delta;
    if (azimuth <= (yaw + 180))
    {
        delta = azimuth - yaw;
    }
    else if (azimuth > (yaw + 180))
    {
        delta = -(-azimuth + yaw + 360);
    }
    return delta;
}

void change_point(void)
{
    if (gps_use.points_distance < 2)
    {
        //更新下一个目标点
//        ReadFlashWithConversion(&gps_data->latitude);
//        ReadFlashWithConversion(&gps_data->longitude);
        printf("CHANGE-POINT\n");
        gps_use.use_point_count++;
    }
}




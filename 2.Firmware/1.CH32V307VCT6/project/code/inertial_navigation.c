/*
 * inertial_navigation.c
 *
 *  Created on: Mar 24, 2023
 *      Author: sorrymaker
 */

#include "inertial_navigation.h"


uint8 first_point = 1;


_gps_st gps_data;
_gps_use_st gps_use;
double first_point_latitude, first_point_longitude, second_point_latitude, second_point_longitude;

static EasyKey_t key_read, key_write;
void GPS_init(void)
{
    gps_init();

    EasyKeyInit(&key_read, B0);
    EasyKeyInit(&key_write, B12);
    gps_get_point();
}

void gps_get_point(void)
{
    while(gps_data.point_count < GPS_MAX_POINT)
    {
        if(gps_tau1201_flag==1)
        {
            uint8 state = gps_data_parse();
            if(state==0)
            {
                if(key_write.isPressed)
                {
                     if (gps_tau1201.state && (gps_tau1201.satellite_used >= 4))
                     {
                         printf("gps_state:%d\r\n",gps_tau1201.state);
                         printf("gps_satellite:%d\r\n",gps_tau1201.satellite_used);
                         printf("save successful\r\n");
                         printf("gps_point : %d\r\n",gps_data.point_count);
                         SaveToFlashWithConversion(&gps_tau1201.latitude);
                         SaveToFlashWithConversion(&gps_tau1201.longitude);
                         gps_data.point_count++;
                     }
                     else
                     {
                         printf("gps_state error");
                     }
                }
            }
            gps_tau1201_flag=0;
        }
     }
     if(gps_data.point_count == GPS_MAX_POINT)
     {
        //读出第一个目标点
        ReadFlashWithConversion(&gps_data.latitude);
        ReadFlashWithConversion(&gps_data.longitude);
     }
}


void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data)
{
    double gps_distance,gps_azimuth;
    if (gps_data->use_point_count > GPS_MAX_POINT)
    {
        printf("no_other_gps_points\r\n");
    }
    else
    {
        //更新当前的位置姿态
        gps_distance = get_two_points_distance(latitude_now, gps_data->latitude, longitude_now, gps_data->longitude);
        gps_azimuth = get_two_points_azimuth(latitude_now, gps_data->latitude, longitude_now, gps_data->longitude);

        gps_data->points_distance = gps_distance;
        gps_data->points_azimuth = gps_azimuth;
        printf("%f\n",gps_data->points_distance);
        printf("%f\n",gps_data->points_azimuth);
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

void change_point(_gps_st gps_data)
{
    if (gps_data.points_distance < 2)
    {
        //更新下一个目标点
        ReadFlashWithConversion(&gps_data.latitude);
        ReadFlashWithConversion(&gps_data.longitude);
        gps_data.use_point_count++;
    }
}




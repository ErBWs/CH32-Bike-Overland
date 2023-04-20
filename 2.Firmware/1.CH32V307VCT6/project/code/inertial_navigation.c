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

uint8 Bike_Start = 0;
void GPS_init(void)
{
    gps_init();
}
void gps_handler(gpsState pointStatus) {

    if (opnEnter) {
        opnEnter = false;
        beep_time = 20;
        if (gps_use.point_count > GPS_MAX_POINT) {
            EasyUIDrawMsgBox("Gps_Buff Not Enough!");
            return;
        }
        if(gps_tau1201_flag)
        {
            uint8 state = gps_data_parse();
            gps_tau1201_flag = 0;
            if (state == 0 && (gps_tau1201.hdop < 1) && (gps_tau1201.hdop > 0.5)) {
                switch (pointStatus) {
                    case COMMON:
                    case PILE:
                        EasyUIDrawMsgBox("Saving...");
                        beep_time = 20;
                        gps_data_array[gps_use.point_count].latitude = gps_tau1201.latitude;
                        gps_data_array[gps_use.point_count].longitude = gps_tau1201.longitude;
                        gps_data_array[gps_use.point_count].type = pointStatus;
                        gps_use.point_count++;
                        break;
                    case BASE:
                        GlobalBase_GPS_data.latitude = gps_tau1201.latitude;
                        GlobalBase_GPS_data.longitude = gps_tau1201.longitude;
                        EasyUIDrawMsgBox("Saving...");
                        beep_time = 50;
                        break;
                    default:;
                }
            }
        } else {
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

void gpsTest(void)
{
    if (gps_tau1201_flag == 1)
    {
        uint8 state = gps_data_parse();
        if (state == 0)
        {
            printf("%f,%f,%f,%f\n",carBodyState.velocity,gps_tau1201.speed * 0.5144f, carBodyState.gpsvelocity,imu_data.w_acc.x/1000.0);
            system_delay_ms(50);
        }
    }
}



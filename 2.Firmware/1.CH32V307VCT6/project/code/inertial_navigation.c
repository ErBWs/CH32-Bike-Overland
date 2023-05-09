/*
 * inertial_navigation.c
 *
 *  Created on: Mar 24, 2023
 *      Author: sorrymaker
 */

#include "inertial_navigation.h"
extern gps_report_t gpsReport;

#if GPS_MAX_POINT != B_REFER_POINT_COUNTS_MAX
#error "Too Much Point!"
#endif

float ref_rad=0;
_gps_st gps_data_array[GPS_MAX_POINT] = {0};
_gps_use_st gps_use = {0};
float normalXArray[GPS_MAX_POINT]={0},normalYArray[GPS_MAX_POINT]={0};
uint8 Bike_Start = 0;

void gps_handler(gpsState pointStatus) {
    uint16 temp=4000;
    while(1)
    {
        if (--temp==0)
        {
            IPS096_ClearBuffer();
            IPS096_ShowStr(0, 2, "current_X:");
            IPS096_ShowStr(0, 14, "current_Y:");
            IPS096_ShowFloat(70, 2, (float)Global_current_node.X,3,3);
            IPS096_ShowFloat(70, 14, (float)Global_current_node.Y,3,3);
            IPS096_SendBuffer();
//                BlueToothPrintf("%f,%f\n",moveArray.offsetX,moveArray.offsetY);
            temp = 4000;
        }
        if (opnEnter)
        {
            opnEnter = false;
            if (gps_use.point_count > GPS_MAX_POINT) {
                EasyUIDrawMsgBox("Gps_Buff Not Enough!");
                return;
            }
            if ((gpsReport.eph < 3) && (gpsReport.eph > 0.1))
            {
                beepTime = 400;
                gps_use.point_count++;
                normalXArray[gps_use.point_count] = (float)Global_current_node.X;
                normalYArray[gps_use.point_count] = (float)Global_current_node.Y;
            }
        }
        if (opnExit)
        {
            Bike_Start = 0;
            break;
        }
    }
    if (opnForward)
    {

    }

}


//void pileHandler(void)
//{
//    static uint8 state=0;
//    switch(state)
//    {
//        case 0:
//            beep_time = 20;
//            gps_use.z_angle=0;
//            gps_use.delta = -160;
//            state = 1;
//        break;
//        case 1:
//            if (gps_use.z_angle >= 360)
//            {
//                beep_time = 40;
//                gps_data = gps_data_array[gps_use.use_point_count];
//                gps_use.use_point_count++;
//                state = 0;
//            }
//        break;
//    }
//}


//void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data,_gps_two_point_st *gps_result)
//{
//    double gps_distance,gps_azimuth;
//    //更新当前的位置姿态
//    gps_distance = get_two_points_distance(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);
//    gps_azimuth = get_two_points_azimuth(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);
//
//    gps_result->points_distance = gps_distance;
//    gps_result->points_azimuth = gps_azimuth;
//}

//float yaw_gps_delta( float azimuth, float yaw)
//{
//    float delta;
//    //0<azimut<90
//    if(azimuth>=0&&azimuth<90)
//    {
//        if (yaw>=0&&yaw<azimuth)
//        {
//            delta = azimuth - yaw;
//            return delta;
//        }
//        else if (yaw>=(azimuth+180)&&yaw<360)
//        {
//            delta = 360 - yaw + azimuth;
//            return delta;
//        }
//        else
//        {
//            delta = yaw - azimuth;
//            return -delta;
//        }
//    }
//    //90<azimut<180
//    if (azimuth>=90&&azimuth<180)
//    {
//       if (yaw>=0 && yaw<azimuth)
//       {
//           delta = azimuth - yaw;
//           return delta;
//       }
//       else if(yaw>=(azimuth+180)&&yaw<360)
//       {
//           delta = 360-yaw+azimuth;
//           return delta;
//       }
//       else
//       {
//           delta = yaw - azimuth;
//           return -delta;
//       }
//    }
//    //180<azimut<270
//    if (azimuth>=180&&azimuth<270)
//    {
//        if (yaw>=(azimuth-180)&&yaw<azimuth)
//        {
//            delta = azimuth - yaw;
//            return delta;
//        }
//        else if (yaw>=0 && yaw<(azimuth-180))
//        {
//            delta = 360 - azimuth + yaw;
//            return -delta;
//        }
//        else if(yaw>=azimuth && yaw<360)
//        {
//            delta = yaw - azimuth;
//            return -delta;
//        }
//    }
//    //270<azimut<360
//    if (azimuth>=270&&azimuth<=360)
//    {
//        if (yaw>=(azimuth-180)&&yaw<azimuth)
//        {
//            delta = azimuth - yaw;
//            return delta;
//        }
//        else if (yaw>=azimuth&&yaw<360)
//        {
//            delta = yaw - azimuth;
//            return -delta;
//        }
//        else
//        {
//            delta = 360 - azimuth + yaw;
//            return -delta;
//        }
//    }
//}

void gpsTest(void)
{
    BlueToothPrintf("%f,%f,%f,%f,%f,%d\n",INS_Y.INS_Out.vn,INS_Y.INS_Out.ve,INS_Y.INS_Out.x_R,INS_Y.INS_Out.y_R,
                    Degree_To_360(RAD_TO_ANGLE(INS_Y.INS_Out.psi)),gpio_get_level(D1));
    system_delay_ms(50);
}

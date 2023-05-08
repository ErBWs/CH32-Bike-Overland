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

float distance_step=1;
float multiple_counts=1;
float constant_yaw=0;
bool constant_yaw_flag=0;
float ref_rad=0;

float points_index=0;
_gps_st gps_data_array[GPS_MAX_POINT] = {0};
float Dx_zero=0,Dy_zero=0;
_gps_use_st gps_use = {0};
float normalXArray[GPS_MAX_POINT]={0},normalYArray[GPS_MAX_POINT]={0};
uint8 Bike_Start = 0;

void gps_handler(gpsState pointStatus) {
    static float x_bias=0,y_bias=0;
        if (opnEnter) {
            opnEnter = false;
            if (gps_use.point_count > GPS_MAX_POINT) {
                EasyUIDrawMsgBox("Gps_Buff Not Enough!");
                return;
            }
#if USE_DISTANCE_STEP==0
            if ((gpsReport.eph < 1.5) && (gpsReport.eph > 0.1))
            {
#endif
                switch (pointStatus)
                {
                    case COMMON:
                    case PILE:
                        if(gps_use.point_count != (int16)points_index) {
                            for(int i=0;i<gps_use.point_count -(int16)points_index;i++)
                            {
                                Dx_zero -= normalXArray[(int16)points_index+i];
                                Dy_zero -= normalYArray[(int16)points_index+i];
                                normalXArray[(int16)points_index+i] = normalYArray[(int16)points_index+i]=0;
                                x_bias = y_bias=0;
                            }
                            gps_use.point_count = (int16)points_index;
                        }
#if USE_DISTANCE_STEP
                        EasyUIDrawMsgBox("Saving...");
                        beepTime = 400;

                        for(uint16 i=0;i<multiple_counts;i++)
                        {
                            if(gps_use.point_count==0)
                            {
                                gps_data_array[0].latitude = gpsReport.lat * 1e-7;
                                gps_data_array[0].longitude = gpsReport.lon * 1e-7;
                                gps_data_array[gps_use.point_count].type = pointStatus;
                                ref_rad = Global_yaw;
                            }
                            else
                            {
                                float x_det,y_det;
                                x_det = normalXArray[gps_use.point_count-1]-x_bias;
                                y_det = normalYArray[gps_use.point_count-1]-y_bias;
                                if(constant_yaw_flag==0) {
                                    x_bias = normalXArray[gps_use.point_count] = distance_step * cosf(Global_yaw);
                                    y_bias = normalYArray[gps_use.point_count] = distance_step * sinf(Global_yaw);
                                }
                                else {
                                    x_bias = normalXArray[gps_use.point_count] = distance_step * cosf(ANGLE_TO_RAD(constant_yaw));
                                    y_bias = normalYArray[gps_use.point_count] = distance_step * sinf(ANGLE_TO_RAD(constant_yaw));
                                }
                                normalXArray[gps_use.point_count] += x_det;
                                normalYArray[gps_use.point_count] += y_det;
                                extern EasyUIItem_t itemCNX,itemCNY;
                                itemCNX.param = &normalXArray[gps_use.point_count];
                                itemCNY.param = &normalYArray[gps_use.point_count];
                                Dx_zero += normalXArray[gps_use.point_count];
                                Dy_zero += normalYArray[gps_use.point_count];
                            }
                            gps_use.point_count++;
                        }
#else
                        EasyUIDrawMsgBox("Saving...");
                        beepTime = 400;
                        gps_data_array[gps_use.point_count].latitude = gpsReport.lat * 1e-7;
                        gps_data_array[gps_use.point_count].longitude = gpsReport.lon * 1e-7;
                        gps_data_array[gps_use.point_count].type = pointStatus;
                        if(gps_use.point_count!=0)
                        {
                            float x_det,y_det;
                            x_det = normalXArray[gps_use.point_count-1]-x_bias;
                            y_det = normalYArray[gps_use.point_count-1]-y_bias;
                            double dx_lat,dy_lon;
                            latlonTodxdy(gps_data_array[gps_use.point_count-1].latitude,&dx_lat,&dy_lon);
                            x_bias = normalXArray[gps_use.point_count] = ANGLE_TO_RAD(gps_data_array[gps_use.point_count].latitude - gps_data_array[gps_use.point_count-1].latitude)*dx_lat;
                            y_bias = normalYArray[gps_use.point_count] = ANGLE_TO_RAD(gps_data_array[gps_use.point_count].longitude - gps_data_array[gps_use.point_count-1].longitude)*dy_lon;
                            normalXArray[gps_use.point_count] += x_det;
                            normalYArray[gps_use.point_count] += y_det;
                            extern EasyUIItem_t itemCNX,itemCNY;
                            itemCNX.param = &normalXArray[gps_use.point_count];
                            itemCNY.param = &normalYArray[gps_use.point_count];
                            Dx_zero += normalXArray[gps_use.point_count];
                            Dy_zero += normalYArray[gps_use.point_count];
                        }
                        gps_use.point_count++;
#endif
                        points_index = gps_use.point_count;
                        break;
                    case BASE:
                        memset(&gps_use,0,sizeof(_gps_use_st));
                        memset(gps_data_array,0, sizeof(_gps_st)*GPS_MAX_POINT);
                        Dx_zero = Dy_zero = x_bias = y_bias = points_index=0;
                        GlobalBase_GPS_data.latitude = gpsReport.lat * 1e-7;
                        GlobalBase_GPS_data.longitude = gpsReport.lon * 1e-7;
                        EasyUIDrawMsgBox("Saving...");
                        beepTime = 800;
                        break;
                    default:;
                }
#if USE_DISTANCE_STEP==0
            }
#endif
    }
    if (opnForward)
    {

    }
    if (opnExit)
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

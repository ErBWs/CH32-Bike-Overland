/*
 * inertial_navigation.c
 *
 *  Created on: Mar 24, 2023
 *      Author: sorrymaker
 */

#include "inertial_navigation.h"

extern gps_report_t gpsReport;

#if GPS_MAX_POINT != B_REFER_POINT_COUNTS_MAX
#error "Not correspond to 'B_REFER_POINT_COUNTS_MAX'!"
#endif
//=========Normal=========
bool constant_angle_flag = false;
float constant_angle = 0;
float distance_step = 1;
float multiple_counts = 1;
float ref_angle = 0;
//==========Cone==========
bool cone_print_dir = false;    //false:left, true:right.
float cone_total_counts = 4;
float cone_total_distance = 6;
float cone_horizon_distance = 0.707f;
//==========Pile==========
bool pile_print_dir = false;    //false:left, true:right.
float pile_radius = 1;


gps_use_st gps_use = {0};
gps_st gps_data_array[GPS_MAX_POINT] = {0};
float normalXArray[GPS_MAX_POINT] = {0}, normalYArray[GPS_MAX_POINT] = {0};
float Dx_zero = 0, Dy_zero = 0;
float points_index = 0;

uint8 Bike_Start = 0;
bool generate_update_flag=true;
extern EasyUIItem_t itemCNX, itemCNY;
void gps_handler(gpsState pointStatus) {
    if (opnEnter) {
        opnEnter = false;
        if (gps_use.point_count > GPS_MAX_POINT) {
            EasyUIDrawMsgBox("Gps_Buff Not Enough!");
            return;
        }
        switch (pointStatus)
        {
            case COMMON:
                EasyUIDrawMsgBox("Saving...");
                beepTime = 400;
                if (gps_use.point_count != (int16) points_index) {
                    for (int i = 0; i < gps_use.point_count - (int16) points_index; i++) {
                        Dx_zero -= normalXArray[(int16) points_index + i];
                        Dy_zero -= normalYArray[(int16) points_index + i];
                        normalXArray[(int16) points_index + i] = normalYArray[(int16) points_index + i] = 0;
                    }
                    gps_use.point_count = (int16) points_index;
                }

                for (uint16 i = 0; i < multiple_counts; i++) {
                    if (gps_use.point_count == 0) {
                        gps_data_array[0].latitude = gpsReport.lat * 1e-7;
                        gps_data_array[0].longitude = gpsReport.lon * 1e-7;
                    } else {
                        if (constant_angle_flag == false) {
                            normalXArray[gps_use.point_count] = distance_step * cosf(Global_yaw - (float) ANGLE_TO_RAD(ref_angle));
                            normalYArray[gps_use.point_count] = distance_step * sinf(Global_yaw - (float) ANGLE_TO_RAD(ref_angle));
                        } else {
                            normalXArray[gps_use.point_count] = distance_step * cosf(ANGLE_TO_RAD(constant_angle - ref_angle));
                            normalYArray[gps_use.point_count] = distance_step * sinf(ANGLE_TO_RAD(constant_angle - ref_angle));
                        }
                        itemCNX.param = &normalXArray[gps_use.point_count];
                        itemCNY.param = &normalYArray[gps_use.point_count];
                        Dx_zero += normalXArray[gps_use.point_count];
                        Dy_zero += normalYArray[gps_use.point_count];
                    }
                    gps_use.point_count++;
                }
                points_index = gps_use.point_count;
                generate_update_flag = true;
                break;
            case CONE:
            {
                if(gps_use.point_count==0)
                {
                    EasyUIDrawMsgBox("There no point before!");
                    break;
                }
                float step_dis = cone_total_distance / (2 * (cone_total_counts - 1));
                float side_bias = sqrtf(powf(step_dis, 2) - powf(cone_horizon_distance, 2));
                float side_dis = sqrtf(powf(step_dis - side_bias, 2) + powf(cone_horizon_distance, 2));
                float side_rad = atanf(cone_horizon_distance / (step_dis - side_bias));
                if (cone_horizon_distance > step_dis || cone_horizon_distance <= 0) {
                    EasyUIDrawMsgBox("Horizon Error!");
                    break;
                }
                beepTime = 400;
                uint8 flag=0;float counts=cone_total_counts;
                uint8 point_start = gps_use.point_count;
                if(cone_print_dir==true)
                {
                    flag=1;
                    counts++;
                }
                for (uint8 i=flag; i < counts; i++) {
                    if (i % 2 == 0) {
                        if (constant_angle_flag == false) {
                            normalXArray[gps_use.point_count] = side_dis * cosf(Global_yaw -(float) (ANGLE_TO_RAD(ref_angle) -side_rad));
                            normalYArray[gps_use.point_count++] = side_dis * sinf(Global_yaw -(float) (ANGLE_TO_RAD(ref_angle) -side_rad ));
                            normalXArray[gps_use.point_count] = 2 * side_bias * cosf(Global_yaw - (float) ANGLE_TO_RAD(ref_angle));
                            normalYArray[gps_use.point_count++] = 2 * side_bias * sinf(Global_yaw - (float) ANGLE_TO_RAD(ref_angle));
                            normalXArray[gps_use.point_count] = side_dis * cosf(Global_yaw - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                            normalYArray[gps_use.point_count++] = side_dis * sinf(Global_yaw - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                        }else
                        {
                            normalXArray[gps_use.point_count] = side_dis * cosf(ANGLE_TO_RAD(constant_angle) -(float) (ANGLE_TO_RAD(ref_angle) -side_rad));
                            normalYArray[gps_use.point_count++] = side_dis * sinf(ANGLE_TO_RAD(constant_angle) -(float) (ANGLE_TO_RAD(ref_angle) -side_rad));
                            normalXArray[gps_use.point_count] = 2 * side_bias * cosf(ANGLE_TO_RAD(constant_angle) - (float) ANGLE_TO_RAD(ref_angle));
                            normalYArray[gps_use.point_count++] = 2 * side_bias * sinf(ANGLE_TO_RAD(constant_angle) - (float) ANGLE_TO_RAD(ref_angle));
                            normalXArray[gps_use.point_count] = side_dis * cosf(ANGLE_TO_RAD(constant_angle) - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                            normalYArray[gps_use.point_count++] = side_dis * sinf(ANGLE_TO_RAD(constant_angle) - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                        }
                    } else {
                        if (constant_angle_flag == false) {
                            normalXArray[gps_use.point_count] =side_dis * cosf(Global_yaw - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                            normalYArray[gps_use.point_count++] =side_dis * sinf(Global_yaw - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                            normalXArray[gps_use.point_count] =2 * side_bias * cosf(Global_yaw - (float) ANGLE_TO_RAD(ref_angle));
                            normalYArray[gps_use.point_count++] =2 * side_bias * sinf(Global_yaw - (float) ANGLE_TO_RAD(ref_angle));
                            normalXArray[gps_use.point_count] =side_dis * cosf(Global_yaw - (float) (ANGLE_TO_RAD(ref_angle) - side_rad));
                            normalYArray[gps_use.point_count++] =side_dis * sinf(Global_yaw - (float) (ANGLE_TO_RAD(ref_angle) - side_rad));
                        }
                        else
                        {
                            normalXArray[gps_use.point_count] =side_dis * cosf(ANGLE_TO_RAD(constant_angle) - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                            normalYArray[gps_use.point_count++] =side_dis * sinf(ANGLE_TO_RAD(constant_angle) - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                            normalXArray[gps_use.point_count] =2 * side_bias * cosf(ANGLE_TO_RAD(constant_angle) - (float) ANGLE_TO_RAD(ref_angle));
                            normalYArray[gps_use.point_count++] =2 * side_bias * sinf(ANGLE_TO_RAD(constant_angle) - (float) ANGLE_TO_RAD(ref_angle));
                            normalXArray[gps_use.point_count] =side_dis * cosf(ANGLE_TO_RAD(constant_angle) - (float) (ANGLE_TO_RAD(ref_angle) - side_rad));
                            normalYArray[gps_use.point_count++] =side_dis * sinf(ANGLE_TO_RAD(constant_angle) - (float) (ANGLE_TO_RAD(ref_angle) - side_rad));
                        }
                    }
                }
                for(uint8 k=point_start;k<gps_use.point_count;k++)
                {
                    Dx_zero += normalXArray[k];
                    Dy_zero += normalYArray[k];
                }
                itemCNX.param = &normalXArray[gps_use.point_count-1];
                itemCNY.param = &normalYArray[gps_use.point_count-1];
                points_index = gps_use.point_count;
                generate_update_flag = true;
                break;
            }
            case PILE:
            {
                if(gps_use.point_count==0)
                {
                    EasyUIDrawMsgBox("There no point before!");
                    break;
                }
                beepTime = 400;
                float dir=-1;uint8 point_start = gps_use.point_count;
                if(pile_print_dir==true)
                    dir=1;
                for(int16 i=-1;i<8;i++)
                {
                    if (constant_angle_flag == false)
                    {
                        normalXArray[gps_use.point_count] =pile_radius * cosf(Global_yaw - (float) ANGLE_TO_RAD(ref_angle+i*dir*60));
                        normalYArray[gps_use.point_count++] =pile_radius * sinf(Global_yaw - (float) ANGLE_TO_RAD(ref_angle+i*dir*60));
                    }
                    else
                    {
                        normalXArray[gps_use.point_count] =pile_radius * cosf(ANGLE_TO_RAD(constant_angle) - (float) ANGLE_TO_RAD(ref_angle+i*dir*60));
                        normalYArray[gps_use.point_count++] =pile_radius * sinf(ANGLE_TO_RAD(constant_angle) - (float) ANGLE_TO_RAD(ref_angle+i*dir*60));
                    }
                }
                for(uint8 k=point_start;k<gps_use.point_count;k++)
                {
                    Dx_zero += normalXArray[k];
                    Dy_zero += normalYArray[k];
                }
                itemCNX.param = &normalXArray[gps_use.point_count-1];
                itemCNY.param = &normalYArray[gps_use.point_count-1];
                points_index = gps_use.point_count;
                generate_update_flag = true;
                break;
            }
            case BASE:
                memset(&gps_use, 0, sizeof(gps_use_st));
                memset(gps_data_array, 0, sizeof(gps_st) * GPS_MAX_POINT);
                Dx_zero = Dy_zero = points_index = 0;
                GlobalBase_GPS_data.latitude = gpsReport.lat * 1e-7;
                GlobalBase_GPS_data.longitude = gpsReport.lon * 1e-7;
                EasyUIDrawMsgBox("Saving...");
                beepTime = 800;
                break;
            default:;
        }
    }
    if (opnForward) {

    }
    if (opnExit) {
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

void gpsTest(void) {
    BlueToothPrintf("%f,%f,%f,%f,%f,%d\n", INS_Y.INS_Out.vn, INS_Y.INS_Out.ve, INS_Y.INS_Out.x_R, INS_Y.INS_Out.y_R,
    Degree_To_360(RAD_TO_ANGLE(INS_Y.INS_Out.psi)), gpio_get_level(D1));
    system_delay_ms(50);
}

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
bool normal_gps_enable = true;
float constant_angle = 0;
float distance_step = 1;
float multiple_counts = 1;
float ref_angle = 0;
uint8 normal_gps_index[GPS_MAX_POINT] = {0};
//==========Cone==========
bool cone_print_dir = false;    //false:left, true:right.
float cone_total_counts = 5;
float cone_total_distance = 8;
float cone_horizon_distance = 0.3f;
float slow_velocity = 12.0f;
float fast_velocity = 30.0f;
float turn_velocity = 14.0f;
float ramp_velocity = 22.0f;
float slow_servo_kp = -0.13f;
float fast_servo_kp = -0.026f;//-0.045f;
float turn_servo_kp = -0.1f;
uint8 cone_index[9] = {0};
uint8 cone_count = 0;
uint8 cone_handler_index = 0;
bool cone_handler_flag = false;
//==========Pile==========
bool pile_print_dir = false;    //false:left, true:right.
float pile_radius = 1;
uint8 pile_index[2] = {0};


gps_use_st gps_use = {0};
gps_st gps_data_array[GPS_MAX_POINT] = {0};
float normalXArray[GPS_MAX_POINT] = {0}, normalYArray[GPS_MAX_POINT] = {0};
float Dx_zero = 0, Dy_zero = 0;
float points_index = 0;
float yaw_angle_bias = 0;
float Global_Raw_Yaw = 0;
float Global_k_gain = 0.25f;

float Global_encode1 = 800;
float Global_encode2 = 650;


uint8 Bike_Start = 0;
bool generate_update_flag = true;
extern EasyUIItem_t itemCNX, itemCNY;

void gps_handler(gpsState pointStatus) {
    if (opnEnter) {
        opnEnter = false;
        if (gps_use.point_count > GPS_MAX_POINT) {
            EasyUIDrawMsgBox("Gps_Buff Not Enough!");
            return;
        }
        if (normal_gps_enable == true) {
            switch (pointStatus) {
                case COMMON:;
                    break;
                case CONE:
                    if (gps_use.point_count != 0) {
                        cone_index[cone_count++] = gps_use.point_count;
                    } else {
                        EasyUIDrawMsgBox("There no point before!");
                        return;
                    }
                    break;
                case PILE:
                    if (gps_use.point_count != 0) {
                        if (pile_index[0] == 0)
                            pile_index[0] = gps_use.point_count;
                        else
                            pile_index[1] = gps_use.point_count;
                    } else {
                        EasyUIDrawMsgBox("There no point before!");
                        return;
                    }
                    break;
                default:;
            }
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
            gps_data_array[gps_use.point_count].latitude = gpsReport.lat * 1e-7;
            gps_data_array[gps_use.point_count].longitude = gpsReport.lon * 1e-7;
            if (gps_use.point_count == 0) {
                GlobalBase_GPS_data.latitude = gps_data_array[0].latitude;
                GlobalBase_GPS_data.longitude = gps_data_array[0].longitude;
            }
            for (uint16 i = 0; i < multiple_counts; i++) {
                if (gps_use.point_count == 0) {
                    gps_use.point_count++;
                    points_index = gps_use.point_count;
                    continue;
                }
                double dx_lat, dy_lon;
                float DX, DY;
                latlonTodxdy(GlobalBase_GPS_data.latitude, &dx_lat, &dy_lon);
                normalXArray[gps_use.point_count] = DX =
                        ANGLE_TO_RAD(gps_data_array[gps_use.point_count].latitude - GlobalBase_GPS_data.latitude) *
                        dx_lat;
                normalYArray[gps_use.point_count] = DY =
                        ANGLE_TO_RAD(gps_data_array[gps_use.point_count].longitude - GlobalBase_GPS_data.longitude) *
                        dy_lon;
                Dx_zero = DX * cosf(ANGLE_TO_RAD(ref_angle)) + DY * sinf(ANGLE_TO_RAD(ref_angle));
                Dy_zero = -DX * sinf(ANGLE_TO_RAD(ref_angle)) + DY * cosf(ANGLE_TO_RAD(ref_angle));
                normal_gps_index[gps_use.point_count] = 1;

                itemCNX.param = &normalXArray[gps_use.point_count];
                itemCNY.param = &normalYArray[gps_use.point_count];
                gps_use.point_count++;
                points_index = gps_use.point_count;
                generate_update_flag = true;
            }
        }
    }
//    if (opnForward) {
//
//    }
//    if (opnExit) {
//    }
}

void gpsConeHandler(void) {
    double dx_lat, dy_lon;
    float DX, DY;
    latlonTodxdy(gps_data_array[cone_index[cone_handler_index]].latitude, &dx_lat, &dy_lon);
    DX = ANGLE_TO_RAD(gpsReport.lat * 1e-7 - gps_data_array[cone_index[cone_handler_index]].latitude) * dx_lat;
    DY = ANGLE_TO_RAD(gpsReport.lon * 1e-7 - gps_data_array[cone_index[cone_handler_index]].longitude) * dy_lon;
    if (cone_index[0] != 0) {
        switch (cone_handler_index) {
            case 0 :{
                if (sqrtf(DX * DX + DY * DY) < 1.7) {
                    beepTime = 1200;
                    backSpdPid.target[NOW] = ramp_velocity;
                    cone_handler_index = 1;
                }
                break;
            }
            case 1 :{
                if (sqrtf(DX * DX + DY * DY) < 1.7) {
                    beepTime = 1200;
                    backSpdPid.target[NOW] = fast_velocity;
                    cone_handler_index = 2;
                }
                break;
            }
            case 2: {
                if (cone_handler_flag == false) {
                    if (sqrtf(DX * DX + DY * DY) < 2) {
                        beepTime = 1200;
                        backSpdPid.target[NOW] = turn_velocity;
                        back_inter_distance = 0;
                        cone_handler_flag = true;
                    }
                }
                else if(back_inter_distance > Global_encode1) {
                    beepTime = 1200;
                    setSmoothKp(&dirPid,turn_servo_kp,800);
                    dynamic_gain = turn_dynamic_gain;
                    anti_dither_flag = false;
                    cone_handler_flag = false;
                    cone_handler_index = 3;
                }
                break;
            }
            case 3: {
                if (sqrtf(DX * DX + DY * DY) < 2) {
                    beepTime = 1200;
                    setSmoothKp(&dirPid,fast_servo_kp,2000);
//                    dirPid.Kp = fast_servo_kp;
                    dynamic_gain = normal_dynamic_gain;
                    backSpdPid.target[NOW] = fast_velocity-1;
                    anti_dither_flag = true;
                    cone_handler_index = 4;
                }
                break;
            }
            case 4: {
                if (cone_handler_flag == false) {
                    if (sqrtf(DX * DX + DY * DY) < 2) {
                        beepTime = 1200;
                        backSpdPid.target[NOW] = slow_velocity;
                        back_inter_distance = 0;
                        cone_handler_flag = true;
                    }
                }
                else if(back_inter_distance > Global_encode2) {
                    beepTime = 1200;
                    dirPid.Kp = slow_servo_kp;
                    dynamic_gain = turn_dynamic_gain;
                    cone_handler_flag = false;
                    cone_handler_index = 5;
                }
                break;
            }
            case 5: {
                if (sqrtf(DX * DX + DY * DY) < 2) {
                    beepTime = 1200;
                    backSpdPid.target[NOW] = fast_velocity;
                    dynamic_gain = normal_dynamic_gain;
                    dirPid.Kp = fast_servo_kp;
                    anti_dither_flag = true;
                    cone_handler_index = 6;
                }
                break;
            }
            case 6: {
                if (sqrtf(DX * DX + DY * DY) < 2) {
                    beepTime = 1200;
                    backSpdPid.target[NOW] = slow_velocity;
                    dirPid.Kp = slow_servo_kp;
                    cone_handler_index = 7;
                }
                break;
            }
            case 7: {
                if (sqrtf(DX * DX + DY * DY) < 2) {
                    beepTime = 1200;
                    backSpdPid.target[NOW] = fast_velocity;
                    dirPid.Kp = fast_servo_kp;
                    anti_dither_flag = true;
                    cone_handler_index = 0;
                }
                break;
            }
            default:;
        }
    }
}

void gpsTest(void) {
    BlueToothPrintf("%f,%f,%f,%f,%f,%d\n", INS_Y.INS_Out.vn, INS_Y.INS_Out.ve, INS_Y.INS_Out.x_R, INS_Y.INS_Out.y_R,
                    Degree_To_360(RAD_TO_ANGLE(INS_Y.INS_Out.psi)), gpio_get_level(D1));
    system_delay_ms(50);
}

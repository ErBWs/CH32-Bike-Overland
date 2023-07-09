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
uint8 cone_index[2] = {0};
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
        if(normal_gps_enable == true)
        {
            switch(pointStatus)
            {
                case COMMON:
                    ;
                    break;
                case CONE:
                    if(gps_use.point_count!=0)
                    {
                        if(cone_index[0]==0)
                            cone_index[0] = gps_use.point_count;
                        else
                            cone_index[1] = gps_use.point_count;
                    }
                    else
                    {
                        EasyUIDrawMsgBox("There no point before!");
                        return;
                    }
                    break;
                case PILE:
                    if(gps_use.point_count!=0)
                    {
                        if(pile_index[0]==0)
                            pile_index[0] = gps_use.point_count;
                        else
                            pile_index[1] = gps_use.point_count;
                    }
                    else
                    {
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
            if(gps_use.point_count==0)
            {
                GlobalBase_GPS_data.latitude =  gps_data_array[0].latitude;
                GlobalBase_GPS_data.longitude =  gps_data_array[0].longitude;
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
                normalXArray[gps_use.point_count] = DX =ANGLE_TO_RAD(gps_data_array[gps_use.point_count].latitude - GlobalBase_GPS_data.latitude) * dx_lat;
                normalYArray[gps_use.point_count] = DY = ANGLE_TO_RAD(gps_data_array[gps_use.point_count].longitude - GlobalBase_GPS_data.longitude) * dy_lon;
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
        else
        {
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
                    if(gps_use.point_count==0)
                    {
                        gps_data_array[gps_use.point_count].latitude = gpsReport.lat * 1e-7;
                        gps_data_array[gps_use.point_count].longitude = gpsReport.lon * 1e-7;
                        GlobalBase_GPS_data.latitude =  gps_data_array[0].latitude;
                        GlobalBase_GPS_data.longitude =  gps_data_array[0].longitude;
                    }
                    for (uint16 i = 0; i < multiple_counts; i++) {
                        if(gps_use.point_count==0)
                        {
                            gps_use.point_count++;
                            continue;
                        }
                        if (constant_angle_flag == false) {
                            normalXArray[gps_use.point_count] = distance_step * cosf(Global_Raw_Yaw - (float) ANGLE_TO_RAD(ref_angle));
                            normalYArray[gps_use.point_count] = distance_step * sinf(Global_Raw_Yaw - (float) ANGLE_TO_RAD(ref_angle));
                        } else {
                            normalXArray[gps_use.point_count] = distance_step * cosf(ANGLE_TO_RAD(constant_angle - ref_angle));
                            normalYArray[gps_use.point_count] = distance_step * sinf(ANGLE_TO_RAD(constant_angle - ref_angle));
                        }
                        Dx_zero += normalXArray[gps_use.point_count];
                        Dy_zero += normalYArray[gps_use.point_count];
                        itemCNX.param = &normalXArray[gps_use.point_count];
                        itemCNY.param = &normalYArray[gps_use.point_count];
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
                                normalXArray[gps_use.point_count] = side_dis * cosf(Global_Raw_Yaw -(float) (ANGLE_TO_RAD(ref_angle) -side_rad));
                                normalYArray[gps_use.point_count++] = side_dis * sinf(Global_Raw_Yaw -(float) (ANGLE_TO_RAD(ref_angle) -side_rad ));
                                normalXArray[gps_use.point_count] = 2 * side_bias * cosf(Global_Raw_Yaw - (float) ANGLE_TO_RAD(ref_angle));
                                normalYArray[gps_use.point_count++] = 2 * side_bias * sinf(Global_Raw_Yaw - (float) ANGLE_TO_RAD(ref_angle));
                                normalXArray[gps_use.point_count] = side_dis * cosf(Global_Raw_Yaw - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                                normalYArray[gps_use.point_count++] = side_dis * sinf(Global_Raw_Yaw - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
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
                                normalXArray[gps_use.point_count] =side_dis * cosf(Global_Raw_Yaw - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                                normalYArray[gps_use.point_count++] =side_dis * sinf(Global_Raw_Yaw - (float) (ANGLE_TO_RAD(ref_angle) + side_rad));
                                normalXArray[gps_use.point_count] =2 * side_bias * cosf(Global_Raw_Yaw - (float) ANGLE_TO_RAD(ref_angle));
                                normalYArray[gps_use.point_count++] =2 * side_bias * sinf(Global_Raw_Yaw - (float) ANGLE_TO_RAD(ref_angle));
                                normalXArray[gps_use.point_count] =side_dis * cosf(Global_Raw_Yaw - (float) (ANGLE_TO_RAD(ref_angle) - side_rad));
                                normalYArray[gps_use.point_count++] =side_dis * sinf(Global_Raw_Yaw - (float) (ANGLE_TO_RAD(ref_angle) - side_rad));
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
                            normalXArray[gps_use.point_count] =pile_radius * cosf(Global_Raw_Yaw - (float) ANGLE_TO_RAD(ref_angle+i*dir*60));
                            normalYArray[gps_use.point_count++] =pile_radius * sinf(Global_Raw_Yaw - (float) ANGLE_TO_RAD(ref_angle+i*dir*60));
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
                    memset(normalXArray, 0 ,sizeof(float) * GPS_MAX_POINT);
                    memset(normalYArray, 0 ,sizeof(float) * GPS_MAX_POINT);
                    memset(normal_gps_index, 0 , sizeof(uint8) * GPS_MAX_POINT);
                    memset(cone_index, 0 , sizeof(uint8) *2);
                    memset(pile_index, 0 , sizeof(uint8) *2);
                    Dx_zero = Dy_zero = points_index = 0;
                    EasyUIDrawMsgBox("Reset OK!");
                    beepTime = 800;
                    break;
                default:;
            }
        }

    }
//    if (opnForward) {
//
//    }
//    if (opnExit) {
//    }
}
void gpsConeHandler(void)
{
    static uint8 index=0;
    double dx_lat, dy_lon;
    float DX, DY;
    latlonTodxdy(gps_data_array[cone_index[index]].latitude, &dx_lat, &dy_lon);
    DX =ANGLE_TO_RAD(gpsReport.lat * 1e-7 - gps_data_array[cone_index[index]].latitude) * dx_lat;
    DY = ANGLE_TO_RAD(gpsReport.lon * 1e-7 - gps_data_array[cone_index[index]].longitude) * dy_lon;
    if(sqrtf(DX*DX+DY*DY)<1&&index<2)
    {
        beepTime = 800;
        if(index==0)
        {
            backSpdPid.target[NOW]=7;
        }
        else if (index==1)
        {
            backSpdPid.target[NOW]=15;
        }
        index++;

    }
    if(index >=2)index=0;
}
void gpsPileHandler(void)
{

}
void gpsTest(void) {
    BlueToothPrintf("%f,%f,%f,%f,%f,%d\n", INS_Y.INS_Out.vn, INS_Y.INS_Out.ve, INS_Y.INS_Out.x_R, INS_Y.INS_Out.y_R,
    Degree_To_360(RAD_TO_ANGLE(INS_Y.INS_Out.psi)), gpio_get_level(D1));
    system_delay_ms(50);
}

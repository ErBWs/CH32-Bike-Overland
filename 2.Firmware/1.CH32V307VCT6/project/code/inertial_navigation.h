/*
 * inertial_navigation.h
 *
 *  Created on: Mar 24, 2023
 *      Author: sorrymaker
 */

#ifndef INERTIAL_NAVIGATION_H_
#define INERTIAL_NAVIGATION_H_

#include "zf_common_headfile.h"
#include "inc_all.h"


#define GPS_MAX_POINT   70

#define USE_DISTANCE_STEP 1


typedef enum
{
    COMMON = 0,
    PILE,
    BASE,
    STOP
}gpsState;

typedef struct
{
    double      latitude;                                                       // 当前目标点经度
    double      longitude;                                                      // 当前目标点纬度
    uint8       type;                                                           //该结点的类型
}_gps_st;

typedef struct
{
    uint8       point_count;                                                   //采点数
    uint8       use_point_count;                                                //已用点数
    float       z_angle;                                                        //z轴陀螺仪积分
    float       delta;
}_gps_use_st;

typedef struct
{
    double      points_azimuth ;                                               //两个点之间的方位角
    double      points_distance;                                               //两点之间的距离
}_gps_two_point_st;




extern _gps_st gps_data_array[GPS_MAX_POINT];
extern _gps_st gps_data;
extern _gps_use_st gps_use;

extern uint8 Bike_Start;
extern float normalXArray[GPS_MAX_POINT],normalYArray[GPS_MAX_POINT];
extern float Dx_zero,Dy_zero;
extern float distance_step;
extern float multiple_counts;

extern bool constant_yaw_flag;
extern float constant_yaw;
extern float points_index;

extern float ref_rad;

void GPS_init(void);
void gps_handler(gpsState pointStatus);
void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data,_gps_two_point_st *gps_result);
float yaw_gps_delta( float azimuth, float yaw);
void pileHandler(void);

void gpsTest(void);

#endif /* INERTIAL_NAVIGATION_H_ */

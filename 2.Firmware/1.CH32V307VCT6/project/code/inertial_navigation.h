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
//#include "imu.h"

#define GPS_MAX_POINT   2



typedef struct
{
    uint8       state;                                                          // 有效状态  1：定位有效  0：定位无效

    uint16      latitude_degree;                                                // 度
    uint16      latitude_cent;                                                  // 分
    uint16      latitude_second;                                                // 秒
    uint16      longitude_degree;                                               // 度
    uint16      longitude_cent;                                                 // 分
    uint16      longitude_second;                                               // 秒

    double      latitude;                                                       // 当前经度
    double      longitude;                                                      // 当前纬度

    float       speed;                                                          // 速度（公里/每小时）
    float       body_speed;                                                     //机体坐标下的速度

    double      points_azimuth ;                                               //两个点之间的方位角
    double      points_distance;                                               //两点之间的距离

    uint8       point_count;                                                   //采点数
    uint8       use_point_count;                                                //已用点数
}_gps_st;

typedef struct
{
    double delta;


}_gps_use_st;

extern _gps_st gps_data;
extern _gps_use_st gps_use;

void GPS_init(void);
void gps_get_point(void);
void two_points_message(double latitude_1, double longitude_1, _gps_st *gps_data);
double yaw_gps_delta( double azimuth, double yaw);
void change_point(_gps_st gps_data);
//double yaw_gps_delta( _gps_st gps_data, _imu_st imu_data);

#endif /* INERTIAL_NAVIGATION_H_ */

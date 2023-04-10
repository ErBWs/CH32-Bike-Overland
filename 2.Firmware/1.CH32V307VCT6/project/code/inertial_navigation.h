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

#define GPS_MAX_POINT   5



typedef struct
{
    double      latitude;                                                       // 当前目标点经度
    double      longitude;                                                      // 当前目标点纬度
    uint8       is_used;                                                        //该结点已用状态标志
    uint8       type;                                                           //该结点的类型
}_gps_st;

typedef struct
{
    double      delta;
    double      points_azimuth ;                                               //两个点之间的方位角
    double      points_distance;                                               //两点之间的距离
    uint8       point_count;                                                   //采点数
    uint8       use_point_count;                                                //已用点数
}_gps_use_st;
typedef struct
{
    double      points_azimuth ;                                               //两个点之间的方位角
    double      points_distance;                                               //两点之间的距离
}_gps_two_point_st;

extern _gps_st gps_data_array[GPS_MAX_POINT];
extern _gps_st gps_data;
extern _gps_use_st gps_use;
extern uint8 write_key_flag;
extern uint8 read_key_flag;
extern uint8 main_key_flag;
extern uint8 Bike_Start;

extern uint8 pile_state;
extern uint8 pile_update_flag;
void GPS_init(void);
void gps_handler(void);
void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data,_gps_two_point_st *gps_result);
double yaw_gps_delta( float azimuth, float yaw);
uint8 GetPointAdvance(double latitude_now, double longitude_now,_gps_st *gpsData);
uint8 GetPoint(double latitude_now, double longitude_now,_gps_st *gpsData);
void pileProcess(double latitude_now, double longitude_now,_gps_st *gpsData);
//double yaw_gps_delta( _gps_st gps_data, _imu_st imu_data);

#endif /* INERTIAL_NAVIGATION_H_ */

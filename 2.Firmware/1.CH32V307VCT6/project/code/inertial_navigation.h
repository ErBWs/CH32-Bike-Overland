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

#define GPS_MAX_POINT   80

#define EXTRA_FORECAST_POINT 0
#define DISTANCE_LIMITATION 1.5
#define ANGLE_BIAS_THRESHOLD 20

typedef enum
{
    COMMON = 0,
    PILE,
    BASE,
    STOP
}gpsState;

typedef struct
{
    double      latitude;                                                       // ��ǰĿ��㾭��
    double      longitude;                                                      // ��ǰĿ���γ��
    uint8       type;                                                           //�ý�������
}_gps_st;

typedef struct
{
    uint8       point_count;                                                   //�ɵ���
    uint8       use_point_count;                                                //���õ���
    float       z_angle;                                                        //z�������ǻ���
    float       delta;
}_gps_use_st;

typedef struct
{
    double      points_azimuth ;                                               //������֮��ķ�λ��
    double      points_distance;                                               //����֮��ľ���
}_gps_two_point_st;




extern _gps_st gps_data_array[GPS_MAX_POINT];
extern _gps_st gps_data;
extern _gps_use_st gps_use;

extern uint8 Bike_Start;





void GPS_init(void);
void gps_handler(gpsState pointStatus);
void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data,_gps_two_point_st *gps_result);
float yaw_gps_delta( float azimuth, float yaw);
void pileHandler(void);

void gpsTest(void);

#endif /* INERTIAL_NAVIGATION_H_ */

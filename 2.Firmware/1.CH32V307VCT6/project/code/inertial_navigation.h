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


#define GPS_MAX_POINT   120

typedef enum
{
    COMMON = 0,
    CONE,
    PILE,
    BASE,
    STOP
}gpsState;

typedef struct
{
    double      latitude;                                                       // ��ǰĿ��㾭��
    double      longitude;                                                      // ��ǰĿ���γ��
}gps_st;

typedef struct
{
    uint8       point_count;                                                   //�ɵ���
    uint8       use_point_count;                                                //���õ���
    float       z_angle;                                                        //z�������ǻ���
    float       delta;
}gps_use_st;

typedef struct
{
    double      points_azimuth ;                                               //������֮��ķ�λ��
    double      points_distance;                                               //����֮��ľ���
}gps_two_point_st;



extern gps_use_st gps_use;
extern gps_st gps_data_array[GPS_MAX_POINT];
extern float normalXArray[GPS_MAX_POINT],normalYArray[GPS_MAX_POINT];
extern float Dx_zero,Dy_zero;
extern float points_index;
extern uint8 Bike_Start;
extern bool generate_update_flag;

//=========Normal=========
extern bool constant_angle_flag;
extern float constant_angle;
extern float distance_step;
extern float multiple_counts;
extern float ref_angle;

//==========Cone==========
extern bool cone_print_dir;
extern float cone_total_counts;
extern float cone_total_distance;
extern float cone_horizon_distance;

//==========Pile==========
extern bool pile_print_dir;
extern float pile_radius;
extern float yaw_angle_bias;
extern float Global_Raw_Yaw;


void GPS_init(void);
void gps_handler(gpsState pointStatus);
void two_points_message(double latitude_now, double longitude_now, gps_st *gps_data,gps_two_point_st *gps_result);
float yaw_gps_delta( float azimuth, float yaw);
void pileHandler(void);

void gpsTest(void);

#endif /* INERTIAL_NAVIGATION_H_ */

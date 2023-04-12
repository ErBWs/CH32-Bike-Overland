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

#define GPS_MAX_POINT   40

#define EXTRA_FORECAST_POINT 0
#define DISTANCE_LIMITATION 1
#define ANGLE_BIAS_THRESHOLD 20

typedef enum
{
    COMMON = 1,
    PILE,
    OTHER,
    STOP
}gpsState;

typedef struct
{
    double      latitude;                                                       // ��ǰĿ��㾭��
    double      longitude;                                                      // ��ǰĿ���γ��
    uint8       is_used;                                                        //�ý������״̬��־
    uint8       type;                                                           //�ý�������
}_gps_st;

typedef struct
{
    double      delta;
    double      points_azimuth ;                                               //������֮��ķ�λ��
    double      points_distance;                                               //����֮��ľ���
    uint8       point_count;                                                   //�ɵ���
    uint8       use_point_count;                                                //���õ���
    float       z_angle;                                                        //z�������ǻ���
}_gps_use_st;

typedef struct
{
    double      points_azimuth ;                                               //������֮��ķ�λ��
    double      points_distance;                                               //����֮��ľ���
}_gps_two_point_st;




extern _gps_st gps_data_array[GPS_MAX_POINT];
extern _gps_st gps_data;
extern _gps_use_st gps_use;
extern uint8 write_key_flag;
extern uint8 read_key_flag;
extern uint8 main_key_flag;
extern uint8 Bike_Start;

extern uint8 navigate_forbid;
extern uint8 pile_update_flag;
extern uint8 circle_fitting_flag;
extern uint16 servo_current_duty;
void GPS_init(void);
void gps_handler(uint8_t pointStatus);
void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data,_gps_two_point_st *gps_result);
float yaw_gps_delta( float azimuth, float yaw);
uint8 GetPointAdvance(double latitude_now, double longitude_now,_gps_st *gps_data);
void GetPoint(double latitude_now, double longitude_now,_gps_st *gps_data);
void gpsStateCheck(void);
void normalHandler(void);
void pileHandler(void);
void pointsStatusCheck(void);
//double yaw_gps_delta( _gps_st gps_data, _imu_st imu_data);
void pileProcess(double latitude_now, double longitude_now,_gps_st *gpsData);
void pileProcess2(_gps_st *gpsData);
void ServoSportSet(uint16_t duty_value,int32_t ticks);
void ServoSportHandler(uint16 *duty_input);

#endif /* INERTIAL_NAVIGATION_H_ */

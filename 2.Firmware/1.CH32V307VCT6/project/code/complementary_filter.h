/*
 * complementary_filter.h
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

#ifndef COMPLEMENTARY_FILTER_H_
#define COMPLEMENTARY_FILTER_H_

#include "inc_all.h"
#include "zf_common_headfile.h"
//#include "imu.h"
//#include "ellipsoid_fitting_process.h"

//typedef struct
//{
//    float mx;
//    float my;
//    float mz;
//} _xyz_mag_s16_st;
//
//typedef struct
//{
//    float w;//q0;
//    float x;//q1;
//    float y;//q2;
//    float z;//q3;
//
//    _xyz_f_st x_vec;
//    _xyz_f_st y_vec;
//    _xyz_f_st z_vec;
//
//    _xyz_f_st a_acc;
//    _xyz_f_st w_acc;
//
//    float rol;
//    float pit;
//    float yaw;
//
//    float inter_rol;
//    float inter_pit;
//    float inter_yaw;
//    float mag_yaw;
//} _imu_st ;

#define  VAL  57.2957795f;
#define  INVVAL  0.0174533f

double Cal_Angle(int16 gyro_x, int16 acc_y, int16 acc_z, int16 offset);
void Cal_YawAngle(float mag_gyro_z, float *yaw);
void gpsFusionyaw(float gpsangle, float *yaw);
#endif /* COMPLEMENTARY_FILTER_H_ */

/*
 * imu.h
 *
 *  Created on: 2023Äê2ÔÂ5ÈÕ
 *      Author: sorrymaker
 */

#ifndef CODE_IMU_H_
#define CODE_IMU_H_

#include "inc_all.h"
#include "zf_common_headfile.h"

typedef struct
{
    float x;
    float y;
    float z;
} _xyz_f_st;

typedef struct
{
    short int x;
    short int y;
    short int z;
} _xyz_s16_st;

typedef struct
{
    int32 x;
    int32 y;
    int32 z;
} _xyz_s32_st;

typedef struct
{
    float w;//q0;
    float x;//q1;
    float y;//q2;
    float z;//q3;

    _xyz_f_st x_vec;
    _xyz_f_st y_vec;
    _xyz_f_st z_vec;

    _xyz_f_st a_acc;
    _xyz_f_st w_acc;

    float rol;
    float pit;
    float yaw;

    float inter_rol;
    float inter_pit;
    float inter_yaw;
    float mag_yaw;
} _imu_st ;

extern _imu_st imu_data;
extern _xyz_s16_st gyro, gyro_offset, gyro_last;
extern _xyz_s16_st acc, acc_offset, acc_last;
extern char Offset_OK;
typedef struct
{
    uint8 acc_CALIBRATE;
    uint8 gyr_CALIBRATE;
    uint8 vec3d_CALIBRATE;

    _xyz_s16_st Acc_I16;
    _xyz_s16_st Gyro_I16;

    _xyz_f_st Acc;
    _xyz_f_st Acc_mmss;
    _xyz_f_st Gyro;
    _xyz_f_st Gyro_deg;

}_sensor_st;//__attribute__((packed))

extern _sensor_st sensor;
extern void Data_steepest(void);
extern void IMU_Offset(void);
extern void IMU_update(float dT,_xyz_f_st *gyr, _xyz_f_st *acc,_imu_st *imu);
extern void IMU_Getdata(_xyz_s16_st *gyro, _xyz_s16_st *acc);
extern void imuinit(void);
#endif /* CODE_IMU_H_ */

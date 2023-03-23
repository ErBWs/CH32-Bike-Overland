/*
 * imu.c
 *
 *  Created on: 2023年2月5日
 *      Author: sorrymaker
 */

#include "imu.h"


//*********************IMU_updata's param************************//
_imu_st imu_data =  {1,0,0,0,
                    {0,0,0},
                    {0,0,0},
                    {0,0,0},
                    {0,0,0},
                    {0,0,0},
                     0,0,0};

_lf_t err_lf_x;
_lf_t err_lf_y;
_lf_t err_lf_z;

_xyz_f_st vec_err_i;
_xyz_f_st x_vec;
_xyz_f_st y_vec;
_xyz_f_st z_vec;
_xyz_f_st a_acc;
_xyz_f_st w_acc;
//*********************IMU_updata's param************************//

//*********************IMU_Getdata's param************************//
char Offset_OK = 0;
_xyz_s16_st gyro, gyro_offset, gyro_last;
_xyz_s16_st acc, acc_offset, acc_last;
//*********************IMU_Getdata's param************************//

//*********************Data_steepest's param************************//
#define MPU_WINDOW_NUM 5
#define MPU_STEEPEST_NUM 5

#define MPU_WINDOW_NUM_ACC 15
#define MPU_STEEPEST_NUM_ACC 15

_steepest_st steepest_ax;
_steepest_st steepest_ay;
_steepest_st steepest_az;
_steepest_st steepest_gx;
_steepest_st steepest_gy;
_steepest_st steepest_gz;

int32 steepest_ax_arr[MPU_WINDOW_NUM_ACC ];
int32 steepest_ay_arr[MPU_WINDOW_NUM_ACC ];
int32 steepest_az_arr[MPU_WINDOW_NUM_ACC ];
int32 steepest_gx_arr[MPU_WINDOW_NUM ];
int32 steepest_gy_arr[MPU_WINDOW_NUM ];
int32 steepest_gz_arr[MPU_WINDOW_NUM ];
_sensor_st sensor;
//*********************Data_steepest's param************************//
char imumode;
//获取陀螺仪数据
void IMU_Getdata(_xyz_s16_st *gyro, _xyz_s16_st *acc, char imumode)
{
    if (imumode == IMU_ALL)
    {
        imu660ra_get_acc();
        imu660ra_get_gyro();
        if (Offset_OK)
        {
            acc->x = imu660ra_acc_x;  //获取加速度原始数据
            acc->y = imu660ra_acc_y;
            acc->z = imu660ra_acc_z;

            gyro->x = imu660ra_gyro_x - gyro_offset.x;  // 获取陀螺仪原始数据并减去零偏
            gyro->y = imu660ra_gyro_y - gyro_offset.y;
            gyro->z = imu660ra_gyro_z - gyro_offset.z;
        }
        else
        {
            acc->x = imu660ra_acc_x;  //获取加速度计原始数据
            acc->y = imu660ra_acc_y;
            acc->z = imu660ra_acc_z;

            gyro->x = imu660ra_gyro_x;  //获取陀螺仪原始数据
            gyro->y = imu660ra_gyro_y;
            gyro->z = imu660ra_gyro_z;
        }


    }
    else if (imumode == IMU_963RA)
    {
        imu963ra_get_acc();
        imu963ra_get_gyro();
        if (Offset_OK)
        {
            acc->x = imu963ra_acc_x;  //获取加速度原始数据
            acc->y = imu963ra_acc_y;
            acc->z = imu963ra_acc_z;

            gyro->x = imu963ra_gyro_x - gyro_offset.x;  // 获取陀螺仪原始数据并减去零偏
            gyro->y = imu963ra_gyro_y - gyro_offset.y;
            gyro->z = imu963ra_gyro_z - gyro_offset.z;
        }
        else
        {
            acc->x = imu963ra_acc_x;  //获取加速度计原始数据
            acc->y = imu963ra_acc_y;
            acc->z = imu963ra_acc_z;

            gyro->x = imu963ra_gyro_x;  //获取陀螺仪原始数据
            gyro->y = imu963ra_gyro_y;
            gyro->z = imu963ra_gyro_z;
        }
    }
    else if (imumode == IMU_ICM)
    {
        icm20602_get_acc();
        icm20602_get_gyro();
        if (Offset_OK)
        {
            acc->x = icm20602_acc_x;  //获取加速度原始数据
            acc->y = icm20602_acc_y;
            acc->z = icm20602_acc_z;

            gyro->x = icm20602_gyro_x - gyro_offset.x;  // 获取陀螺仪原始数据并减去零偏
            gyro->y = icm20602_gyro_y - gyro_offset.y;
            gyro->z = icm20602_gyro_z - gyro_offset.z;
        }
        else
        {
            acc->x = icm20602_acc_x;  //获取加速度计原始数据
            acc->y = icm20602_acc_y;
            acc->z = icm20602_acc_z;

            gyro->x = icm20602_gyro_x;  //获取陀螺仪原始数据
            gyro->y = icm20602_gyro_y;
            gyro->z = icm20602_gyro_z;
        }
    }


}

//计算陀螺仪零偏
void IMU_Offset(char imumode)
{
    uint8 i, Count = 100;
    int64 temp[6] = {0};

    acc_offset.x = 0;
    acc_offset.y = 0;
    acc_offset.z = 0;
    gyro_offset.x = 0;
    gyro_offset.y = 0;
    gyro_offset.z = 0;

    for (i = 0; i < Count; i++)
    {
        IMU_Getdata(&gyro, &acc, imumode);   //读取陀螺仪数据
        system_delay_ms(2);

        temp[0] += acc.x;
        temp[1] += acc.y;
        temp[2] += acc.z;

        temp[3] += gyro.x;
        temp[4] += gyro.y;
        temp[5] += gyro.z;
    }
    acc_offset.x = (int16)(temp[0] / Count);
    acc_offset.y = (int16)(temp[1] / Count);
    acc_offset.z = (int16)(temp[2] / Count);

    gyro_offset.x = (int16)(temp[3] / Count);
    gyro_offset.y = (int16)(temp[4] / Count);
    gyro_offset.z = (int16)(temp[5] / Count);

    Offset_OK = 1;
}

//数据滤波
void Data_steepest(void)
{
    steepest_descend(steepest_ax_arr ,MPU_WINDOW_NUM_ACC ,&steepest_ax ,MPU_STEEPEST_NUM_ACC,(int32) acc.x);
    steepest_descend(steepest_ay_arr ,MPU_WINDOW_NUM_ACC ,&steepest_ay ,MPU_STEEPEST_NUM_ACC,(int32) acc.y);
    steepest_descend(steepest_az_arr ,MPU_WINDOW_NUM_ACC ,&steepest_az ,MPU_STEEPEST_NUM_ACC,(int32) acc.z);
    steepest_descend(steepest_gx_arr ,MPU_WINDOW_NUM ,&steepest_gx ,MPU_STEEPEST_NUM,(int32) gyro.x);
    steepest_descend(steepest_gy_arr ,MPU_WINDOW_NUM ,&steepest_gy ,MPU_STEEPEST_NUM,(int32) gyro.y);
    steepest_descend(steepest_gz_arr ,MPU_WINDOW_NUM ,&steepest_gz ,MPU_STEEPEST_NUM,(int32) gyro.z);

    sensor.Gyro_deg.x = steepest_gx.now_out *0.0610f;
    sensor.Gyro_deg.y = steepest_gy.now_out *0.0610f;
    sensor.Gyro_deg.z = steepest_gz.now_out *0.0610f;
    sensor.Acc_mmss.x = steepest_ax.now_out *2.3926f;
    sensor.Acc_mmss.y = steepest_ay.now_out *2.3926f;
    sensor.Acc_mmss.z = steepest_az.now_out *2.3926f;
}

//角度解算
void IMU_update(float dT,_xyz_f_st *gyr, _xyz_f_st *acc,_imu_st *imu)
{
    //PI补偿器 KP是对于加速度计的信任程度，KP越大，对加速度计信任程度越高，表现为：收敛速度快，但是毛刺变多。
    //KI用于消除稳态误差，经过零偏矫正的角速度测量，KI取值很小。KI越大，表现为：收敛时出现震荡。
    float kp = 3.5,ki = 0.001;

    float q0q1,q0q2,q1q1,q1q3,q2q2,q2q3,q3q3,q1q2,q0q3;
    float w_q,x_q,y_q,z_q;
    float acc_length,q_length;
    _xyz_f_st acc_norm;
    _xyz_f_st vec_err;
    _xyz_f_st d_angle;


    w_q = imu->w;
    x_q = imu->x;
    y_q = imu->y;
    z_q = imu->z;

//  q0q0 = w_q * w_q;
    q0q1 = w_q * x_q;
    q0q2 = w_q * y_q;
    q1q1 = x_q * x_q;
    q1q3 = x_q * z_q;
    q2q2 = y_q * y_q;
    q2q3 = y_q * z_q;
    q3q3 = z_q * z_q;
    q1q2 = x_q * y_q;
    q0q3 = w_q * z_q;
//

    // 加速度计的读数，单位化
    acc_length = my_sqrt(my_pow(acc->x) + my_pow(acc->y) + my_pow(acc->z));
    acc_norm.x = acc->x / acc_length;
    acc_norm.y = acc->y / acc_length;
    acc_norm.z = acc->z / acc_length;


    // 载体坐标下的x方向向量，单位化
    imu->x_vec.x = 1 - (2*q2q2 + 2*q3q3);
    imu->x_vec.y = 2*q1q2 - 2*q0q3;
    imu->x_vec.z = 2*q1q3 + 2*q0q2;

    // 载体坐标下的y方向向量，单位化
    imu->y_vec.x = 2*q1q2 + 2*q0q3;
    imu->y_vec.y = 1 - (2*q1q1 + 2*q3q3);
    imu->y_vec.z = 2*q2q3 - 2*q0q1;

    // 载体坐标下的z方向向量(等效重力向量、重力加速度向量)，单位化
    imu->z_vec.x = 2*q1q3 - 2*q0q2;
    imu->z_vec.y = 2*q2q3 + 2*q0q1;
    imu->z_vec.z = 1 - (2*q1q1 + 2*q2q2);

    // 计算载体坐标下的运动加速度。（与姿态解算无关）
    imu->a_acc.x = acc->x - 9800 *imu->z_vec.x;
    imu->a_acc.y = acc->y - 9800 *imu->z_vec.y;
    imu->a_acc.z = acc->z - 9800 *imu->z_vec.z;

    // 计算世界坐标下的运动加速度。（与姿态解算无关）
    imu->w_acc.x = imu->x_vec.x *imu->a_acc.x + imu->x_vec.y *imu->a_acc.y + imu->x_vec.z *imu->a_acc.z;
    imu->w_acc.y = imu->y_vec.x *imu->a_acc.x + imu->y_vec.y *imu->a_acc.y + imu->y_vec.z *imu->a_acc.z;
    imu->w_acc.z = imu->z_vec.x *imu->a_acc.x + imu->z_vec.y *imu->a_acc.y + imu->z_vec.z *imu->a_acc.z;
    // 测量值与等效重力向量的叉积（计算向量误差）
    vec_err.x =  (acc_norm.y * imu->z_vec.z - imu->z_vec.y * acc_norm.z);
    vec_err.y = -(acc_norm.x * imu->z_vec.z - imu->z_vec.x * acc_norm.z);
    vec_err.z = -(acc_norm.y * imu->z_vec.x - imu->z_vec.y * acc_norm.x);

    //截止频率1Hz的低通限幅滤波
    limit_filter(dT,0.2f,&err_lf_x,vec_err.x);
    limit_filter(dT,0.2f,&err_lf_y,vec_err.y);
    limit_filter(dT,0.2f,&err_lf_z,vec_err.z);

    //误差积分
    vec_err_i.x += err_lf_x.out *dT *ki;
    vec_err_i.y += err_lf_y.out *dT *ki;
    vec_err_i.z += err_lf_z.out *dT *ki;

    // 构造增量旋转（含融合矫正）
    d_angle.x = (gyr->x *RAD_PER_DEG + (err_lf_x.out + vec_err_i.x) * kp) * dT / 2 ;
    d_angle.y = (gyr->y *RAD_PER_DEG + (err_lf_y.out + vec_err_i.y) * kp) * dT / 2 ;
    d_angle.z = (gyr->z *RAD_PER_DEG + (err_lf_z.out + vec_err_i.z) * kp) * dT / 2 ;

    // 计算姿态
    imu->w = w_q           - x_q*d_angle.x - y_q*d_angle.y - z_q*d_angle.z;
    imu->x = w_q*d_angle.x + x_q           + y_q*d_angle.z - z_q*d_angle.y;
    imu->y = w_q*d_angle.y - x_q*d_angle.z + y_q           + z_q*d_angle.x;
    imu->z = w_q*d_angle.z + x_q*d_angle.y - y_q*d_angle.x + z_q;

    q_length = my_sqrt(imu->w*imu->w + imu->x*imu->x + imu->y*imu->y + imu->z*imu->z);
    imu->w /= q_length;
    imu->x /= q_length;
    imu->y /= q_length;
    imu->z /= q_length;
    //四元数转欧拉角
    imu->pit = asin(2*q1q3 - 2*q0q2)*57.30f;
    imu->rol = fast_atan2(2*q2q3 + 2*q0q1, -2*q1q1-2*q2q2 + 1)*57.30f;
    imu->yaw = -fast_atan2(2*q1q2 + 2*q0q3, -2*q2q2-2*q3q3 + 1)*57.30f;
}
//extern float num_float[8];

void imuinit(char imumode)
{
    if (imumode == IMU_ALL)
    {
        imu963ra_init();
        icm20602_init();
        IMU_Offset(imumode);
//        num_float[5] = (float)Offset_OK;
//        vcan_sendware(num_float, sizeof(num_float));
        system_delay_ms(2000);
//        num_float[5] = 0;
        imuMagOffset();
        Ellipsoid_fitting_Process(&mag_origin_data);
    }
    if (imumode == IMU_ICM)
    {
        icm20602_init();
        IMU_Offset(imumode);
    }
    if (imumode == IMU_963RA)
    {
        imu963ra_init();
        IMU_Offset(imumode);
        system_delay_ms(2000);
        imuMagOffset();
        Ellipsoid_fitting_Process(&mag_origin_data);
    }


}

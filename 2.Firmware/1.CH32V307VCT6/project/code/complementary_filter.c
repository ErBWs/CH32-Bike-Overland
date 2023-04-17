/*
 * complementary_filter.c
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

#include "complementary_filter.h"


/*
 * 一阶互补滤波
 * gyro_x,acc_y, acc_z：x轴陀螺仪采集数据, y、z轴加速度采集数据
 * offset：x轴的零飘
 * weight：权重
 * dt：计算周期（s）
 * return：滤波后角度
 */
double Cal_Angle(int16 gyro_x, int16 acc_y, int16 acc_z, int16 offset)
{
    static double angle_rol;
    float weight_acc=0.05, weight_gyro = 0.95, dt = 0.00012195f;//dt=0.005s / 16.4，将前括号内数字量转化为真实物理角度量
    float acc_angle;
    float d_gyro_angle;
    //加速度解算
    acc_angle = atan2((double)(acc_y), (double)acc_z) * VAL;
    //陀螺仪积分
    d_gyro_angle = ((double)gyro_x - offset) * dt;
   //一阶互补滤波
    angle_rol = weight_acc * acc_angle + weight_gyro * (angle_rol + d_gyro_angle);
    return angle_rol;
}

/*
 * 一阶互补滤波
 * mag_gyro_z,yaw：x轴陀螺仪采集数据, 偏航角解算
 * weight：权重
 * dt：计算周期（s）
 * return：滤波后角度
 */
void Cal_YawAngle(float mag_gyro_z, float *yaw )
{
    float weight_mag=0.05, weight_gyro = 0.95, dt = 0.0023f;
    static float d_gyro_angle = 0,yaw_last = 0;
    //陀螺仪积分

    d_gyro_angle = ((double)mag_gyro_z) * dt;
    //如果检测到绕桩

    gps_use.z_angle += d_gyro_angle;
    
   //一阶互补滤波
    (*yaw) = weight_mag * (*yaw) + weight_gyro * (yaw_last + d_gyro_angle);
    yaw_last = (*yaw);
}

void gpsFusionyaw(float gpsangle, float *yaw)
{
    //运动时相信gps航向角
    float weight_gps = 0.8f, weight_yaw = 0.2f;
    float last_speed;
    //当车体速度稳定且行进方向稳定时，进行融合  之后改为当运动到第三个点时开始相信gps，初始运用偏航角循迹
    if (gps_tau1201.speed>1.5&&(gps_tau1201.speed - last_speed) < 0.5)     //when(count>=3 and reach third_point) begin fusion
    {
        (*yaw) = weight_gps * gpsangle + weight_yaw * (*yaw);
        return;
    }
    
    last_speed = gps_tau1201.speed;
}

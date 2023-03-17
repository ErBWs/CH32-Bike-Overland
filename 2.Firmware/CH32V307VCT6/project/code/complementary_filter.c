/*
 * complementary_filter.c
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

#include "complementary_filter.h"

#define  VAL  57.2957795f;
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
    d_gyro_angle = ((double)gyro_x + offset) * dt;
   //一阶互补滤波
    angle_rol = weight_acc * acc_angle + weight_gyro * (angle_rol + d_gyro_angle);
    return angle_rol;
}

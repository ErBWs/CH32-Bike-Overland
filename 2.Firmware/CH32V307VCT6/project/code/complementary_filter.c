/*
 * complementary_filter.c
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

#include "complementary_filter.h"

double VAL = 57.2957795f;
double atheta_x;
double atheta_y;
double atheta_z;


/*
 * 计算陀螺仪加速度角θ = arctan(x/z)
 * return：atheta角度值
 */
//void Cal_Gyro_Atheta(void)
//{
//    //获取 ICM20602 加速度计数据
//    icm20602_get_acc();
//    //解算
//    atheta_y = atan2((double)(icm20602_acc_y), (double)icm20602_acc_z) * VAL;
//}

/*
 * 计算陀螺仪积分角θ=∫ω(t)dt
 * return：theta
 */
//double Cal_Gyro_Theta(void)
//{
//    static double theta=0;
//
//    //获取 ICM20602 陀螺仪数据
//    icm20602_get_gyro();
//    //积分
//    theta += ((double)icm20602_gyro_x + 1) / 16.4f * 0.005;
//    return theta;
//}
extern float num_float[8];
/*
 * 一阶互补滤波
 * mode：使用
 * gyro_m：某个轴陀螺仪采集数据
 * error：对应轴的零飘
 * weight：权重
 * dt：计算周期（s）
 * return：滤波后角度
 */
double Cal_Angle(int16 gyro_x, int16 acc_y, int16 acc_z, int16 offset)
{
    static double angle_rol;
    float weight_acc=0.05, weight_gyro = 0.95, dt = 0.00012195f;//dt=0.005s，另外除以16.4，将前括号内数字量转化为真实物理角度量
    float acc_angle;
    float d_gyro_angle;
    //加速度解算
    acc_angle = atan2((double)(acc_y), (double)acc_z) * VAL;
    num_float[1] = acc_angle;
//    num_float[0] = (float)acc_z;
//    num_float[1] = acc_y;
//    num_float[2] = acc_angle;
    //陀螺仪积分
    d_gyro_angle = ((double)gyro_x + offset) * dt;
//    num_float[3] += d_gyro_angle;
   //一阶互补滤波
    angle_rol = weight_acc * acc_angle + weight_gyro * (angle_rol + d_gyro_angle);
//    num_float[4] = angle_rol;
    return angle_rol;
}

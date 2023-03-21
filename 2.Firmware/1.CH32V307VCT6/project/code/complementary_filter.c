/*
 * complementary_filter.c
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

#include "complementary_filter.h"


/*
 * һ�׻����˲�
 * gyro_x,acc_y, acc_z��x�������ǲɼ�����, y��z����ٶȲɼ�����
 * offset��x�����Ʈ
 * weight��Ȩ��
 * dt���������ڣ�s��
 * return���˲���Ƕ�
 */
double Cal_Angle(int16 gyro_x, int16 acc_y, int16 acc_z, int16 offset)
{
    static double angle_rol;
    float weight_acc=0.05, weight_gyro = 0.95, dt = 0.00012195f;//dt=0.005s / 16.4����ǰ������������ת��Ϊ��ʵ����Ƕ���
    float acc_angle;
    float d_gyro_angle;
    //���ٶȽ���
    acc_angle = atan2((double)(acc_y), (double)acc_z) * VAL;
    //�����ǻ���
    d_gyro_angle = ((double)gyro_x - offset) * dt;
   //һ�׻����˲�
    angle_rol = weight_acc * acc_angle + weight_gyro * (angle_rol + d_gyro_angle);
    return angle_rol;
}

/*
 * һ�׻����˲�
 * gyro_x,acc_y, acc_z��x�������ǲɼ�����, y��z����ٶȲɼ�����
 * offset��x�����Ʈ
 * weight��Ȩ��
 * dt���������ڣ�s��
 * return���˲���Ƕ�
 */
extern float num_float[8];
void Cal_YawAngle(float mag_gyro_z, float *yaw )
{
//    static double angle_yaw;
    float weight_mag=0.2, weight_gyro = 0.8, dt = 0.00022;//0.00012195f;//dt=0.002s / 16.4����ǰ������������ת��Ϊ��ʵ����Ƕ���
//    float yaw_angle;
    num_float[1] = (*yaw);
    static float d_gyro_angle = 0;
//    //���ٶȽ���
//    acc_angle = atan2((double)(acc_y), (double)acc_z) * VAL;
//    Inclination_compensation(mag_gyro_z, ICO);
    //�����ǻ���
    num_float[3] = mag_gyro_z;
//    mag_gyro_z = mag_gyro_z * 10;
    d_gyro_angle += ((double)mag_gyro_z) * dt;
    num_float[2] = d_gyro_angle;
   //һ�׻����˲�
    (*yaw) = weight_mag * (*yaw) + weight_gyro * ((*yaw) + d_gyro_angle);

}

/*
 * complementary_filter.c
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

#include "complementary_filter.h"

#define  VAL  57.2957795f;
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
    d_gyro_angle = ((double)gyro_x + offset) * dt;
   //һ�׻����˲�
    angle_rol = weight_acc * acc_angle + weight_gyro * (angle_rol + d_gyro_angle);
    return angle_rol;
}

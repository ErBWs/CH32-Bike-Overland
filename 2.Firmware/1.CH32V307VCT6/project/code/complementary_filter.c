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
 * mag_gyro_z,yaw��x�������ǲɼ�����, ƫ���ǽ���
 * weight��Ȩ��
 * dt���������ڣ�s��
 * return���˲���Ƕ�
 */
void Cal_YawAngle(float mag_gyro_z, float *yaw )
{
    float weight_mag=0.05, weight_gyro = 0.95, dt = 0.0023f;
    static float d_gyro_angle = 0,yaw_last = 0;
    //�����ǻ���
    d_gyro_angle = ((double)mag_gyro_z) * dt;

   //һ�׻����˲�
    (*yaw) = weight_mag * (*yaw) + weight_gyro * (yaw_last + d_gyro_angle);
    yaw_last = (*yaw);
}

void gpsFusionyaw(float gpsangle, float *yaw)
{
    //�˶�ʱ����gps�����
    float weight_gps = 0.8, weight_yaw = 0.2;
    static char count = 0;
    count++;
    //�Ƕ������������任�����Ŵ�ƫ��
    if (Abs(*yaw) < 5)
    {
        count = 0;
    }
    //�������ٶ��ȶ����н������ȶ�ʱ�������ں�  ֮���Ϊ���˶�����������ʱ��ʼ����gps����ʼ����ƫ����ѭ��
    else if ((count >= 3) && (gps_tau1201.speed > 4.3))//when(count>=3 and reach third_point) begin fusion
    {
        (*yaw) = weight_gps * gpsangle + weight_yaw * (*yaw);
        count = 3;
    }
    //������߳������ݲ��ȶ�ʱ�����Ŵ����Ʒ����
    else
    {
        *yaw = atan2f(mag_data.my,mag_data.mx) * VAL;
        if (*yaw < 0)
        {
            *yaw += 360;
        }
    }
}

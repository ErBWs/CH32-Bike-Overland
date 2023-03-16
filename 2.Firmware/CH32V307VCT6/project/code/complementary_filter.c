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
 * ���������Ǽ��ٶȽǦ� = arctan(x/z)
 * return��atheta�Ƕ�ֵ
 */
//void Cal_Gyro_Atheta(void)
//{
//    //��ȡ ICM20602 ���ٶȼ�����
//    icm20602_get_acc();
//    //����
//    atheta_y = atan2((double)(icm20602_acc_y), (double)icm20602_acc_z) * VAL;
//}

/*
 * ���������ǻ��ֽǦ�=�Ҧ�(t)dt
 * return��theta
 */
//double Cal_Gyro_Theta(void)
//{
//    static double theta=0;
//
//    //��ȡ ICM20602 ����������
//    icm20602_get_gyro();
//    //����
//    theta += ((double)icm20602_gyro_x + 1) / 16.4f * 0.005;
//    return theta;
//}
extern float num_float[8];
/*
 * һ�׻����˲�
 * mode��ʹ��
 * gyro_m��ĳ���������ǲɼ�����
 * error����Ӧ�����Ʈ
 * weight��Ȩ��
 * dt���������ڣ�s��
 * return���˲���Ƕ�
 */
double Cal_Angle(int16 gyro_x, int16 acc_y, int16 acc_z, int16 offset)
{
    static double angle_rol;
    float weight_acc=0.05, weight_gyro = 0.95, dt = 0.00012195f;//dt=0.005s���������16.4����ǰ������������ת��Ϊ��ʵ����Ƕ���
    float acc_angle;
    float d_gyro_angle;
    //���ٶȽ���
    acc_angle = atan2((double)(acc_y), (double)acc_z) * VAL;
    num_float[1] = acc_angle;
//    num_float[0] = (float)acc_z;
//    num_float[1] = acc_y;
//    num_float[2] = acc_angle;
    //�����ǻ���
    d_gyro_angle = ((double)gyro_x + offset) * dt;
//    num_float[3] += d_gyro_angle;
   //һ�׻����˲�
    angle_rol = weight_acc * acc_angle + weight_gyro * (angle_rol + d_gyro_angle);
//    num_float[4] = angle_rol;
    return angle_rol;
}

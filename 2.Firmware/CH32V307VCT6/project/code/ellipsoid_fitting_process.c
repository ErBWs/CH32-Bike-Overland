/*
 * ellipsoid_fitting_process.c
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

//����У׼
//��С���˵��������
//((x-x0)/A)^2 + ((y-y0)/B)^2 + ((z-z0)/C)^2 = 1 �Ŀռ��������򷽳�ʽ
//x^2 + a*y^2 + b*z^2 + c*x + d*y + e*z + f = 0  �򻯺�ķ���
//����ת��Ϊ��a,b,c,d,e,f,�����x0��y0��z0 �Լ� A,B,C
//���ߣ�Ԭ���
//֪��ID��Ԭ���  ת����ע������ �����Ͷ��߳ɹ�

#include "ellipsoid_fitting_process.h"


#define MATRIX_SIZE 6
float m_matrix[MATRIX_SIZE][MATRIX_SIZE + 1];//ϵ������
float solve[MATRIX_SIZE] = { 0 };//������Ľ��Ӧ��С������������еģ�a��b��c��d��e��f

float m_result[MATRIX_SIZE];
int N = 0;//�����ۼƵĲ����������

_xyz_mag_f_st mag_Offset;
_xyz_mag_s16_ary_st mag_origin_data;
_xyz_mag_s16_st mag_data;

//��������
//_xyz_mag_s16_ary_st mag_origin_data_test = {{87, 301, 274, 312, -3805, 4389, 261, 327, -1963, 3024},
//                                       {-52, -45, 4088, -4109, -24, 6, 2106, -2047, -13, 18},
//                                       {-4454, 3859, -303, -305, -390, -228, -3848, -3880, -3797, -3449}
//                                        };


char Offset_Mag_OK = 0;

//��ȡ����������
void imuGetMagData(_xyz_mag_s16_st *mag_data)
{
    imu963ra_get_mag();
    if (Offset_Mag_OK)
        {
        mag_data->mx = (imu963ra_mag_x - mag_Offset.X0) / mag_Offset.A;  //��ȡ�������������
        mag_data->my = (imu963ra_mag_y - mag_Offset.Y0) / mag_Offset.B;
        mag_data->mz = (imu963ra_mag_z - mag_Offset.Z0) / mag_Offset.C;
        }
     else
        {
         mag_data->mx = imu963ra_mag_x;  //��ȡ������ԭʼ����
         mag_data->my = imu963ra_mag_y;
         mag_data->mz = imu963ra_mag_z;
        }
}

void imuMagOffset()
{
    int i;
    for (i = 0; i < MAG_SAMPLE; ++i)
    {
        imuGetMagData(&mag_data);
        system_delay_ms(10);
        if ((mag_data.mx != 0) || (mag_data.my != 0) || (mag_data.mz != 0) )
        {
            mag_origin_data.mx_o[i] = mag_data.mx;
            mag_origin_data.my_o[i] = mag_data.my;
            mag_origin_data.mz_o[i] = mag_data.mz;
        }

    }
    Offset_Mag_OK = 1;
}

//ȡ����ֵ
float Abs(float a)
{
    return a < 0 ? -a : a;
}

//�Ѿ���ϵ��ȫ�����Ϊ0
void ResetMatrix(void)
{
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    {
        for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
            m_matrix[row][column] = 0.0f;
    }
}

//����������������ɾ����Ԫ�ص��ܺ�
void CalcData_Input(int16 x, int16 y, int16 z)//ԭ����float
{
    float V[MATRIX_SIZE + 1];
    N++;
    V[0] = y*y;
    V[1] = z*z;
    V[2] = x;
    V[3] = y;
    V[4] = z;
    V[5] = 1.0;
    V[6] = -x*x;
    //����ϵ�����󣬲������ۼ�
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    {
        for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        {
            m_matrix[row][column] += V[row] * V[column];
        }
    }
    //b������m_matrix[row][6]
}

//�����е����������ɾ����Ԫ�ص��ܺ�
void CalcData_Input_sum(_xyz_mag_s16_ary_st *mag_origin_data)
{
    int i, count = 0;
    for (i = 0; i < MAG_SAMPLE; ++i)
    {
        if ((mag_origin_data->mx_o[i] != 0) || (mag_origin_data->my_o[i] != 0) || (mag_origin_data->mz_o[i] != 0) )
        {
            CalcData_Input(mag_origin_data->mx_o[i - count], mag_origin_data->my_o[i - count], mag_origin_data->mz_o[i - count]);
        }
        else //�п�������
        {
            count++;
        }

    }

}

//����ϵ�����󣬰ѳ���N����
void CalcData_Input_average()
{
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        m_matrix[row][column] /= N;
    //b������m_matrix[row][6]
}

//��ʾ����ϵ��������������[A|b]
void DispMatrix(void)
{
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    {
        for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        {
            printf("%23f ", m_matrix[row][column]);
            if (column == MATRIX_SIZE - 1)
                printf("|");
        }
        printf("\r\n");
    }
    printf("\r\n\r\n");
}

//��������Ԫ��λ��
void Row2_swop_Row1(int row1, int row2)
{
    float tmp = 0;
    for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
    {
        tmp = m_matrix[row1][column];
        m_matrix[row1][column] = m_matrix[row2][column];
        m_matrix[row2][column] = tmp;
    }
}

//�ð�row�е�Ԫ�س���һ��ϵ��k
void k_muiltply_Row(float k, int row)
{
    for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        m_matrix[row][column] *= k;
}

//��һ��������row1�мӵ�row2����ȥ
void Row2_add_kRow1(float k, int row1, int row2)
{
    for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        m_matrix[row2][column] += k*m_matrix[row1][column];
}


//����Ԫ����k����Ԫ֮ǰ����k�е�MATRIX_SIZE�������н���ð���ų���������������k�е�Ԫ�صĴ�С
void MoveBiggestElement_to_Top(int k)
{
    int row = 0;//, column = 0;

    for (row = k + 1; row < MATRIX_SIZE; row++)
    {
        if (Abs(m_matrix[k][k]) < Abs(m_matrix[row][k]))
        {
            Row2_swop_Row1(k, row);
        }
    }
}

//��˹��Ԫ�������н����;���
uint8 Matrix_GaussElimination(void)
{
    float k = 0;
    for (uint8 cnt = 0; cnt < MATRIX_SIZE; cnt++)//���е�k�ε����㣬��Ҫ�����k�����µ�������k�е�Ԫ�ض����0
    {
        //��k������k�е�Ԫ�ش�С����������
        MoveBiggestElement_to_Top(cnt);
        if (m_matrix[cnt][cnt] == 0)
            return(1);//����ֵ��ʾ����
        //��k���������Ԫ��ȫ������0�����б仯
        for (uint8 row = cnt + 1; row < MATRIX_SIZE; row++)
        {
            k = -m_matrix[row][cnt] / m_matrix[cnt][cnt];
            Row2_add_kRow1(k, cnt, row);
        }
    }
    return 0;
}

//��������;��󣬼��ѶԽ��ߵ�Ԫ��ȫ������1
void Matrix_RowSimplify(void)
{
    float k = 0;
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    {
        k = 1 / m_matrix[row][row];
        k_muiltply_Row(k, row);
    }
}

//���������Է�����Ľ�
void Matrix_Solve(float* solve)
{
    for (short row = MATRIX_SIZE - 1; row >= 0; row--)
    {
        solve[row] = m_matrix[row][MATRIX_SIZE];
        for (uint8 column = MATRIX_SIZE - 1; column >= row + 1; column--)
            solve[row] -= m_matrix[row][column] * solve[column];
    }
}

//��������У׼�Ĺ���
void Ellipsoid_fitting_Process(_xyz_mag_s16_ary_st *mag_origin_data)
{

    ResetMatrix();
    //�����������������ٶȲ����������������Ͼ��ȷֲ�
    CalcData_Input_sum(mag_origin_data);//�����﷨�д���ȶ//��֤û������
    CalcData_Input_average();//����������ݵ�����Ԫ�ؽ��й�һ��
//    DispMatrix();//��ʾԭʼ���������
    if (Matrix_GaussElimination())  //����н����ξ���
        printf("the marix could not be solved\r\n");
    else
    {
        Matrix_RowSimplify();//���������̬
        Matrix_Solve(solve);//���a,b,c,d,e,f

        mag_Offset.X0 = -solve[2] / 2;
        mag_Offset.Y0 = -solve[3] / (2 * solve[0]);
        mag_Offset.Z0 = -solve[4] / (2 * solve[1]);
        mag_Offset.A = sqrt(mag_Offset.X0*mag_Offset.X0 + solve[0]*mag_Offset.Y0*mag_Offset.Y0 + solve[1]*mag_Offset.Z0*mag_Offset.Z0 - solve[5]);
        mag_Offset.B = mag_Offset.A / sqrt(solve[0]);
        mag_Offset.C = mag_Offset.A / sqrt(solve[1]);
//        printf("  ((x - x0) / A) ^ 2 + ((y - y0) / B) ^ 2 + ((z - z0) / C) ^ 2 = 1 Ellipsoid result as below��\r\n");
//        printf("\r\n");
     }
    //���ڴ��ڸ�������
//    int32 i = 0;
//    for (i = 0; i < N; ++i) {
//        printf("%d %d %d\t\n",mag_origin_data->mx_o[i],mag_origin_data->my_o[i],mag_origin_data->mz_o[i]);
//        if (i % 500 == 0  )
//        {
//            system_delay_ms(10000);
//        }
//    }
    printf("  X0 = %f| Y0 = %f| Z0 = %f| A = %f| B = %f| C = %f \r\n", mag_Offset.X0, mag_Offset.Y0, mag_Offset.Z0, mag_Offset.A, mag_Offset.B, mag_Offset.C);
}

//��ǲ��� + ƫ���ǽ���
void Inclination_compensation(_xyz_mag_s16_st *mag_data)
{
    float Hx = 0,Hy = 0;
    Hx = mag_data->mx * cosf(imu_data.rol * INVVAL) + mag_data->mz * sinf(imu_data.rol * INVVAL);
    Hy = mag_data->mx * sinf(imu_data.pit * INVVAL) * sinf(imu_data.rol * INVVAL) + mag_data->my * cosf(imu_data.pit * INVVAL) - mag_data->mz * sinf(imu_data.pit * INVVAL) * cosf(imu_data.rol * INVVAL);
    imu_data.mag_yaw = atan2f(Hx,Hy) * VAL;

    if (imu_data.mag_yaw < 0)
    {
        imu_data.mag_yaw += 360;
    }
}


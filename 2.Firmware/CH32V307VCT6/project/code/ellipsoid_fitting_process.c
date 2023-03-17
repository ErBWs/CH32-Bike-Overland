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

_xyz_mag_s16_ary_st mag_origin_data_test = {{87, 301, 274, 312, -3805, 4389, 261, 327, -1963, 3024},
                                       {-52, -45, 4088, -4109, -24, 6, 2106, -2047, -13, 18},
                                       {-4454, 3859, -303, -305, -390, -228, -3848, -3880, -3797, -3449}
                                        };


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
        system_delay_ms(2);
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
    int i;
    for (i = 0; i < MAG_SAMPLE; ++i)
    {
        if ((mag_origin_data->mx_o[i] != 0) || (mag_origin_data->my_o[i] != 0) || (mag_origin_data->mz_o[i] != 0) )
        {
            CalcData_Input(mag_origin_data->mx_o[i], mag_origin_data->my_o[i], mag_origin_data->mz_o[i]);
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
        DispMatrix();
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
    DispMatrix();
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
    printf("  a = %f| b = %f| c = %f| d = %f| e = %f| f = %f ", solve[0], solve[1], solve[2], solve[3], solve[4], solve[5]);
    printf("\r\n");
    printf("\r\n");
}

//��������У׼�Ĺ���
void Ellipsoid_fitting_Process(void)
{
    ResetMatrix();

    //�����������������ٶȲ����������������Ͼ��ȷֲ�
//    CalcData_Input(87, -52, -4454);
//    CalcData_Input(301, -45, 3859);
//    CalcData_Input(274, 4088, -303);
//    CalcData_Input(312, -4109, -305);
//    CalcData_Input(-3805, -24, -390);
//    CalcData_Input(4389, 6, -228);
//    CalcData_Input(261, 2106, -3848);
//    CalcData_Input(327, -2047, -3880);
//    CalcData_Input(-1963, -13, -3797);
//    CalcData_Input(3024, 18, -3449);
    CalcData_Input_sum(&mag_origin_data_test);
    CalcData_Input_average();//����������ݵ�����Ԫ�ؽ��й�һ��
//    DispMatrix();//��ʾԭʼ���������
    if (Matrix_GaussElimination())  //����н����ξ���
        printf("the marix could not be solved\r\n");
    else
    {
        Matrix_RowSimplify();//���������̬
        Matrix_Solve(solve);//���a,b,c,d,e,f

//        float a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
//        a = solve[0];
//        b = solve[1];
//        c = solve[2];
//        d = solve[3];
//        e = solve[4];
//        f = solve[5];

//        float X0 = 0, Y0 = 0, Z0 = 0, A = 0, B = 0, C = 0;
        mag_Offset.X0 = -solve[2] / 2;
        mag_Offset.Y0 = -solve[3] / (2 * solve[0]);
        mag_Offset.Z0 = -solve[4] / (2 * solve[1]);
        mag_Offset.A = sqrt(mag_Offset.X0*mag_Offset.X0 + solve[0]*mag_Offset.Y0*mag_Offset.Y0 + solve[1]*mag_Offset.Z0*mag_Offset.Z0 - solve[5]);
        mag_Offset.B = mag_Offset.A / sqrt(solve[0]);
        mag_Offset.C = mag_Offset.A / sqrt(solve[1]);
        printf("  ((x - x0) / A) ^ 2 + ((y - y0) / B) ^ 2 + ((z - z0) / C) ^ 2 = 1 Ellipsoid result as below��\r\n");
        printf("\r\n");
        printf("  X0 = %f| Y0 = %f| Z0 = %f| A = %f| B = %f| C = %f \r\n", mag_Offset.X0, mag_Offset.Y0, mag_Offset.Z0, mag_Offset.A, mag_Offset.B, mag_Offset.C);
    }
    while (1);
}

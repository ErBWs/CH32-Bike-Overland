/*
 * ellipsoid_fitting_process.c
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

//椭球校准
//最小二乘的椭球拟合
//((x-x0)/A)^2 + ((y-y0)/B)^2 + ((z-z0)/C)^2 = 1 的空间任意椭球方程式
//x^2 + a*y^2 + b*z^2 + c*x + d*y + e*z + f = 0  简化后的方程
//问题转换为由a,b,c,d,e,f,来求解x0，y0，z0 以及 A,B,C
//作者：袁玉斌
//知乎ID：袁玉斌  转载请注明出处 尊重劳动者成果

#include "ellipsoid_fitting_process.h"


#define MATRIX_SIZE 6
float m_matrix[MATRIX_SIZE][MATRIX_SIZE + 1];//系数矩阵
float solve[MATRIX_SIZE] = { 0 };//方程组的解对应最小二乘椭球拟合中的，a，b，c，d，e，f

float m_result[MATRIX_SIZE];
int N = 0;//计算累计的采样点次数的

_xyz_mag_f_st mag_Offset;
_xyz_mag_s16_ary_st mag_origin_data;
_xyz_mag_s16_st mag_data;


_lf_t magmx = {1,0};
_lf_t magmy = {1,0};
_lf_t magmz = {1,0};

//测试数组
//_xyz_mag_s16_ary_st mag_origin_data_test = {{87, 301, 274, 312, -3805, 4389, 261, 327, -1963, 3024},
//                                       {-52, -45, 4088, -4109, -24, 6, 2106, -2047, -13, 18},
//                                       {-4454, 3859, -303, -305, -390, -228, -3848, -3880, -3797, -3449}
//                                        };


char Offset_Mag_OK = 0;

//读取磁力计数据
void imuGetMagData(_xyz_mag_s16_st *mag_data)
{
    static _xyz_mag_s16_st last_mag = {0};
    imu963ra_get_mag();
    if (Offset_Mag_OK)
        {
//        imu963ra_mag_x = imu963ra_mag_x * cosf(ANGLE_TO_RAD(imu_data.pit)) - imu963ra_mag_y * sinf(ANGLE_TO_RAD(imu_data.pit)) * sinf(ANGLE_TO_RAD(imu_data.rol)) - imu963ra_mag_z * cosf(ANGLE_TO_RAD(imu_data.rol)) * sinf(ANGLE_TO_RAD(imu_data.pit));
//        imu963ra_mag_y = imu963ra_mag_y * cosf(ANGLE_TO_RAD(imu_data.rol)) - imu963ra_mag_z * sinf(ANGLE_TO_RAD(imu_data.rol));
        mag_data->mx = ((float)imu963ra_mag_x - (float)mag_Offset.X0) / (float)mag_Offset.A;  //获取磁力计拟合数据
        mag_data->my = ((float)imu963ra_mag_y - (float)mag_Offset.Y0) / (float)mag_Offset.B;
        mag_data->mz = ((float)imu963ra_mag_z - (float)mag_Offset.Z0) / (float)mag_Offset.C;
        
        mag_data->mx = mag_data->mx * 0.8 + last_mag.mx * 0.2;//低通滤波
        mag_data->my = mag_data->my * 0.8 + last_mag.my * 0.2;
        mag_data->mz = mag_data->mz * 0.8 + last_mag.mz * 0.2;
        
        last_mag.mx = mag_data->mx;
        last_mag.my = mag_data->my;
        last_mag.mz = mag_data->mz;
        }
     else
        {
         mag_data->mx = imu963ra_mag_x;  //获取磁力计原始数据
         mag_data->my = imu963ra_mag_y;
         mag_data->mz = imu963ra_mag_z;
        }
}

void imuMagOffset(void)
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

//取绝对值
float Abs(float a)
{
    return a < 0 ? -a : a;
}

//把矩阵系数全部清除为0
void ResetMatrix(void)
{
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    {
        for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
            m_matrix[row][column] = 0.0f;
    }
}

//把输入的数据先生成矩阵的元素的总和
void CalcData_Input(int16 x, int16 y, int16 z)//原来是float
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
    //构建系数矩阵，并进行累加
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    {
        for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        {
            m_matrix[row][column] += V[row] * V[column];
        }
    }
    //b向量是m_matrix[row][6]
}

//把所有的数据先生成矩阵的元素的总和
void CalcData_Input_sum(_xyz_mag_s16_ary_st *mag_origin_data)
{
    int i, count = 0;
    for (i = 0; i < MAG_SAMPLE; ++i)
    {
        if ((mag_origin_data->mx_o[i] != 0) || (mag_origin_data->my_o[i] != 0) || (mag_origin_data->mz_o[i] != 0) )
        {
            CalcData_Input(mag_origin_data->mx_o[i - count], mag_origin_data->my_o[i - count], mag_origin_data->mz_o[i - count]);
        }
        else //有空余数据
        {
            count++;
        }

    }

}

//化简系数矩阵，把除以N带上
void CalcData_Input_average()
{
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
        for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
            m_matrix[row][column] /= N;
    //b向量是m_matrix[row][6]
}

//显示出来系数矩阵和增广矩阵[A|b]
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

//交换两行元素位置
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

//用把row行的元素乘以一个系数k
void k_muiltply_Row(float k, int row)
{
    for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        m_matrix[row][column] *= k;
}

//用一个数乘以row1行加到row2行上去
void Row2_add_kRow1(float k, int row1, int row2)
{
    for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        m_matrix[row2][column] += k*m_matrix[row1][column];
}


//列主元，第k次消元之前，把k行到MATRIX_SIZE的所有行进行冒泡排出最大，排序的依据是k列的元素的大小
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

//高斯消元法，求行阶梯型矩阵
uint8 Matrix_GaussElimination(void)
{
    float k = 0;
    for (uint8 cnt = 0; cnt < MATRIX_SIZE; cnt++)//进行第k次的运算，主要是针对k行以下的行数把k列的元素都变成0
    {
        //把k行依据k列的元素大小，进行排序
        MoveBiggestElement_to_Top(cnt);
        if (m_matrix[cnt][cnt] == 0)
            return(1);//返回值表示错误
        //把k行下面的行元素全部消成0，整行变化
        for (uint8 row = cnt + 1; row < MATRIX_SIZE; row++)
        {
            k = -m_matrix[row][cnt] / m_matrix[cnt][cnt];
            Row2_add_kRow1(k, cnt, row);
        }
    }
    return 0;
}

//求行最简型矩阵，即把对角线的元素全部化成1
void Matrix_RowSimplify(void)
{
    float k = 0;
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    {
        k = 1 / m_matrix[row][row];
        k_muiltply_Row(k, row);
    }
}

//求非齐次线性方程组的解
void Matrix_Solve(float* solve)
{
    for (short row = MATRIX_SIZE - 1; row >= 0; row--)
    {
        solve[row] = m_matrix[row][MATRIX_SIZE];
        for (uint8 column = MATRIX_SIZE - 1; column >= row + 1; column--)
            solve[row] -= m_matrix[row][column] * solve[column];
    }
}

//整个椭球校准的过程
void Ellipsoid_fitting_Process(_xyz_mag_s16_ary_st *mag_origin_data)
{

    ResetMatrix();
    //这里输入任意个点加速度参数，尽量在球面上均匀分布
    CalcData_Input_sum(mag_origin_data);//这里语法有待商榷//验证没有问题
    CalcData_Input_average();//对输入的数据到矩阵元素进行归一化
//    DispMatrix();//显示原始的增广矩阵
    if (Matrix_GaussElimination())  //求得行阶梯形矩阵
        printf("the marix could not be solved\r\n");
    else
    {
        Matrix_RowSimplify();//化行最简形态
        Matrix_Solve(solve);//求解a,b,c,d,e,f

        mag_Offset.X0 = -solve[2] / 2;
        mag_Offset.Y0 = -solve[3] / (2 * solve[0]);
        mag_Offset.Z0 = -solve[4] / (2 * solve[1]);
        mag_Offset.A = sqrt(mag_Offset.X0*mag_Offset.X0 + solve[0]*mag_Offset.Y0*mag_Offset.Y0 + solve[1]*mag_Offset.Z0*mag_Offset.Z0 - solve[5]);
        mag_Offset.B = mag_Offset.A / sqrt(solve[0]);
        mag_Offset.C = mag_Offset.A / sqrt(solve[1]);
     }
    //用于串口复制数据
//    int32 i = 0;
//    for (i = 0; i < N; ++i) {
//        printf("%d %d %d\t\n",mag_origin_data->mx_o[i],mag_origin_data->my_o[i],mag_origin_data->mz_o[i]);
//        if (i % 500 == 0  )
//        {
//            system_delay_ms(10000);
//        }
//    }
//    printf("  X0 = %f| Y0 = %f| Z0 = %f| A = %d| B = %d| C = %d \r\n", mag_Offset.X0, mag_Offset.Y0, mag_Offset.Z0, mag_Offset.A, mag_Offset.B, mag_Offset.C);
}
//extern float num_float[8];
//倾角补偿 + 偏航角解算
void Inclination_compensation(_xyz_mag_s16_st *mag_data, char mode)
{
//    imu_data.pit; y   ??
//    imu_data.rol; x   ??
    float Hx = 0,Hy = 0;
//    float temp;
    if (mode == ICO)
    {
//        temp = atan2f(mag_data->mx,mag_data->my) * VAL;

//       printf("%f,",Hx);
//       printf("%f,",Hy);
//       printf("%f,",mag_data->mx);
//       printf("%f,",mag_data->my);
//       printf("%f\n",mag_data->mz);

       imu_data.mag_yaw = atan2f(-Hy,Hx) * VAL;
//       printf("%f,",imu_data.mag_yaw);
//       printf("%f\n",temp);
    }
    if(mode == NO_ICO)
    {
        imu_data.mag_yaw = atan2f(mag_data->my,mag_data->mx) * VAL;
    }
    if (imu_data.mag_yaw < 0)
    {
        imu_data.mag_yaw += 360;
    }
}


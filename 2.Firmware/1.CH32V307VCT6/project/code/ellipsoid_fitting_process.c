/*
 * ellipsoid_fitting_process.c
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

//ÍÖÇòÐ£×¼
//×îÐ¡¶þ³ËµÄÍÖÇòÄâºÏ
//((x-x0)/A)^2 + ((y-y0)/B)^2 + ((z-z0)/C)^2 = 1 µÄ¿Õ¼äÈÎÒâÍÖÇò·½³ÌÊ½
//x^2 + a*y^2 + b*z^2 + c*x + d*y + e*z + f = 0  ¼ò»¯ºóµÄ·½³Ì
//ÎÊÌâ×ª»»ÎªÓÉa,b,c,d,e,f,À´Çó½âx0£¬y0£¬z0 ÒÔ¼° A,B,C
//×÷Õß£ºÔ¬Óñ±ó
//ÖªºõID£ºÔ¬Óñ±ó  ×ªÔØÇë×¢Ã÷³ö´¦ ×ðÖØÀÍ¶¯Õß³É¹û

#include "ellipsoid_fitting_process.h"


#define MATRIX_SIZE 6
float m_matrix[MATRIX_SIZE][MATRIX_SIZE + 1];//ÏµÊý¾ØÕó
float solve[MATRIX_SIZE] = { 0 };//·½³Ì×éµÄ½â¶ÔÓ¦×îÐ¡¶þ³ËÍÖÇòÄâºÏÖÐµÄ£¬a£¬b£¬c£¬d£¬e£¬f

float m_result[MATRIX_SIZE];
int N = 0;//¼ÆËãÀÛ¼ÆµÄ²ÉÑùµã´ÎÊýµÄ

_xyz_mag_f_st mag_Offset;
_xyz_mag_s16_ary_st mag_origin_data;
_xyz_mag_s16_st mag_data;


_lf_t magmx = {1,0};
_lf_t magmy = {1,0};
_lf_t magmz = {1,0};

//²âÊÔÊý×é
//_xyz_mag_s16_ary_st mag_origin_data_test = {{87, 301, 274, 312, -3805, 4389, 261, 327, -1963, 3024},
//                                       {-52, -45, 4088, -4109, -24, 6, 2106, -2047, -13, 18},
//                                       {-4454, 3859, -303, -305, -390, -228, -3848, -3880, -3797, -3449}
//                                        };


char Offset_Mag_OK = 0;

//¶ÁÈ¡´ÅÁ¦¼ÆÊý¾Ý
void imuGetMagData(_xyz_mag_s16_st *mag_data)
{
    imu963ra_get_mag();
    if (0)
        {
        mag_data->mx = ((float)imu963ra_mag_x - (float)mag_Offset.X0) / (float)mag_Offset.A;  //»ñÈ¡´ÅÁ¦¼ÆÄâºÏÊý¾Ý
        mag_data->my = ((float)imu963ra_mag_y - (float)mag_Offset.Y0) / (float)mag_Offset.B;
        mag_data->mz = ((float)imu963ra_mag_z - (float)mag_Offset.Z0) / (float)mag_Offset.C;
//        magmx.out = mag_data->mx;
//        magmy.out = mag_data->my;
//        magmz.out = mag_data->mz;
//        limit_filter(0.002, 500, &magmx, mag_data->mx);
//        limit_filter(0.002, 500, &magmy, mag_data->my);
//        limit_filter(0.002, 500, &magmz, mag_data->mz);
//        mag_data->mx = magmx.out;
//        mag_data->my = magmy.out;
//        mag_data->mz = magmz.out;
        }
     else
        {
         mag_data->mx = imu963ra_mag_x;  //»ñÈ¡´ÅÁ¦¼ÆÔ­Ê¼Êý¾Ý
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
        system_delay_ms(1);
        if ((mag_data.mx != 0) || (mag_data.my != 0) || (mag_data.mz != 0) )
        {
            mag_origin_data.mx_o[i] = mag_data.mx;
            mag_origin_data.my_o[i] = mag_data.my;
            mag_origin_data.mz_o[i] = mag_data.mz;
        }

    }
    Offset_Mag_OK = 1;
}

//È¡¾ø¶ÔÖµ
float Abs(float a)
{
    return a < 0 ? -a : a;
}

//°Ñ¾ØÕóÏµÊýÈ«²¿Çå³ýÎª0
void ResetMatrix(void)
{
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    {
        for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
            m_matrix[row][column] = 0.0f;
    }
}

//°ÑÊäÈëµÄÊý¾ÝÏÈÉú³É¾ØÕóµÄÔªËØµÄ×ÜºÍ
void CalcData_Input(int16 x, int16 y, int16 z)//Ô­À´ÊÇfloat
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
    //¹¹½¨ÏµÊý¾ØÕó£¬²¢½øÐÐÀÛ¼Ó
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    {
        for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        {
            m_matrix[row][column] += V[row] * V[column];
        }
    }
    //bÏòÁ¿ÊÇm_matrix[row][6]
}

//°ÑËùÓÐµÄÊý¾ÝÏÈÉú³É¾ØÕóµÄÔªËØµÄ×ÜºÍ
void CalcData_Input_sum(_xyz_mag_s16_ary_st *mag_origin_data)
{
    int i, count = 0;
    for (i = 0; i < MAG_SAMPLE; ++i)
    {
        if ((mag_origin_data->mx_o[i] != 0) || (mag_origin_data->my_o[i] != 0) || (mag_origin_data->mz_o[i] != 0) )
        {
            CalcData_Input(mag_origin_data->mx_o[i - count], mag_origin_data->my_o[i - count], mag_origin_data->mz_o[i - count]);
        }
        else //ÓÐ¿ÕÓàÊý¾Ý
        {
            count++;
        }

    }

}

//»¯¼òÏµÊý¾ØÕó£¬°Ñ³ýÒÔN´øÉÏ
void CalcData_Input_average()
{
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        m_matrix[row][column] /= N;
    //bÏòÁ¿ÊÇm_matrix[row][6]
}

//ÏÔÊ¾³öÀ´ÏµÊý¾ØÕóºÍÔö¹ã¾ØÕó[A|b]
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

//½»»»Á½ÐÐÔªËØÎ»ÖÃ
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

//ÓÃ°ÑrowÐÐµÄÔªËØ³ËÒÔÒ»¸öÏµÊýk
void k_muiltply_Row(float k, int row)
{
    for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        m_matrix[row][column] *= k;
}

//ÓÃÒ»¸öÊý³ËÒÔrow1ÐÐ¼Óµ½row2ÐÐÉÏÈ¥
void Row2_add_kRow1(float k, int row1, int row2)
{
    for (uint8 column = 0; column < MATRIX_SIZE + 1; column++)
        m_matrix[row2][column] += k*m_matrix[row1][column];
}


//ÁÐÖ÷Ôª£¬µÚk´ÎÏûÔªÖ®Ç°£¬°ÑkÐÐµ½MATRIX_SIZEµÄËùÓÐÐÐ½øÐÐÃ°ÅÝÅÅ³ö×î´ó£¬ÅÅÐòµÄÒÀ¾ÝÊÇkÁÐµÄÔªËØµÄ´óÐ¡
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

//¸ßË¹ÏûÔª·¨£¬ÇóÐÐ½×ÌÝÐÍ¾ØÕó
uint8 Matrix_GaussElimination(void)
{
    float k = 0;
    for (uint8 cnt = 0; cnt < MATRIX_SIZE; cnt++)//½øÐÐµÚk´ÎµÄÔËËã£¬Ö÷ÒªÊÇÕë¶ÔkÐÐÒÔÏÂµÄÐÐÊý°ÑkÁÐµÄÔªËØ¶¼±ä³É0
    {
        //°ÑkÐÐÒÀ¾ÝkÁÐµÄÔªËØ´óÐ¡£¬½øÐÐÅÅÐò
        MoveBiggestElement_to_Top(cnt);
        if (m_matrix[cnt][cnt] == 0)
            return(1);//·µ»ØÖµ±íÊ¾´íÎó
        //°ÑkÐÐÏÂÃæµÄÐÐÔªËØÈ«²¿Ïû³É0£¬ÕûÐÐ±ä»¯
        for (uint8 row = cnt + 1; row < MATRIX_SIZE; row++)
        {
            k = -m_matrix[row][cnt] / m_matrix[cnt][cnt];
            Row2_add_kRow1(k, cnt, row);
        }
    }
    return 0;
}

//ÇóÐÐ×î¼òÐÍ¾ØÕó£¬¼´°Ñ¶Ô½ÇÏßµÄÔªËØÈ«²¿»¯³É1
void Matrix_RowSimplify(void)
{
    float k = 0;
    for (uint8 row = 0; row < MATRIX_SIZE; row++)
    {
        k = 1 / m_matrix[row][row];
        k_muiltply_Row(k, row);
    }
}

//Çó·ÇÆë´ÎÏßÐÔ·½³Ì×éµÄ½â
void Matrix_Solve(float* solve)
{
    for (short row = MATRIX_SIZE - 1; row >= 0; row--)
    {
        solve[row] = m_matrix[row][MATRIX_SIZE];
        for (uint8 column = MATRIX_SIZE - 1; column >= row + 1; column--)
            solve[row] -= m_matrix[row][column] * solve[column];
    }
}

//Õû¸öÍÖÇòÐ£×¼µÄ¹ý³Ì
void Ellipsoid_fitting_Process(_xyz_mag_s16_ary_st *mag_origin_data)
{

    ResetMatrix();
    //ÕâÀïÊäÈëÈÎÒâ¸öµã¼ÓËÙ¶È²ÎÊý£¬¾¡Á¿ÔÚÇòÃæÉÏ¾ùÔÈ·Ö²¼
    CalcData_Input_sum(mag_origin_data);//ÕâÀïÓï·¨ÓÐ´ýÉÌÈ¶//ÑéÖ¤Ã»ÓÐÎÊÌâ
    CalcData_Input_average();//¶ÔÊäÈëµÄÊý¾Ýµ½¾ØÕóÔªËØ½øÐÐ¹éÒ»»¯
//    DispMatrix();//ÏÔÊ¾Ô­Ê¼µÄÔö¹ã¾ØÕó
    if (Matrix_GaussElimination())  //ÇóµÃÐÐ½×ÌÝÐÎ¾ØÕó
        printf("the marix could not be solved\r\n");
    else
    {
        Matrix_RowSimplify();//»¯ÐÐ×î¼òÐÎÌ¬
        Matrix_Solve(solve);//Çó½âa,b,c,d,e,f

        mag_Offset.X0 = -solve[2] / 2;
        mag_Offset.Y0 = -solve[3] / (2 * solve[0]);
        mag_Offset.Z0 = -solve[4] / (2 * solve[1]);
        mag_Offset.A = sqrt(mag_Offset.X0*mag_Offset.X0 + solve[0]*mag_Offset.Y0*mag_Offset.Y0 + solve[1]*mag_Offset.Z0*mag_Offset.Z0 - solve[5]);
        mag_Offset.B = mag_Offset.A / sqrt(solve[0]);
        mag_Offset.C = mag_Offset.A / sqrt(solve[1]);
     }
    //ÓÃÓÚ´®¿Ú¸´ÖÆÊý¾Ý
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
extern float num_float[8];
//Çã½Ç²¹³¥ + Æ«º½½Ç½âËã
void Inclination_compensation(_xyz_mag_s16_st *mag_data, char mode)
{
//    imu_data.pit; y   ¦È
//    imu_data.rol; x   ¦µ
    float Hx = 0,Hy = 0;
    float temp;
    if (mode == ICO)
    {
//        temp = atan2f(mag_data->mx,mag_data->my) * VAL;
       Hx = mag_data->mx * cosf(ANGLE_TO_RAD(imu_data.pit)) - mag_data->my * sinf(ANGLE_TO_RAD(imu_data.pit)) * sinf(ANGLE_TO_RAD(imu_data.rol)) - mag_data->mz * cosf(ANGLE_TO_RAD(imu_data.rol)) * sinf(ANGLE_TO_RAD(imu_data.pit));
       Hy = mag_data->my * cosf(ANGLE_TO_RAD(imu_data.rol)) - mag_data->mz * sinf(ANGLE_TO_RAD(imu_data.rol));
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
        imu_data.mag_yaw = atan2f(mag_data->mx,mag_data->my) * VAL;
    }
    if (imu_data.mag_yaw < 0)
    {
        imu_data.mag_yaw += 360;
    }
}


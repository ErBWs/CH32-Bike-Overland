/*
 * ellipsoid_fitting_process.h
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */
#ifndef CODE_ELLIPSOID_FITTING_PROCESS_H_
#define CODE_ELLIPSOID_FITTING_PROCESS_H_

#include "zf_common_headfile.h"
#include "inc_all.h"

#define MAG_SAMPLE 50

typedef struct
{
    float X0;
    float Y0;
    float Z0;
    float A;
    float B;
    float C;
} _xyz_mag_f_st;

typedef struct
{
    int16 mx;
    int16 my;
    int16 mz;
} _xyz_mag_s16_st;

typedef struct
{
    int16 mx_o[MAG_SAMPLE];
    int16 my_o[MAG_SAMPLE];
    int16 mz_o[MAG_SAMPLE];
}_xyz_mag_s16_ary_st;


extern float Abs(float a);
extern void ResetMatrix(void);
extern void CalcData_Input(int16 x, int16 y, int16 z);
extern void CalcData_Input_average();
extern void DispMatrix(void);
extern void Row2_swop_Row1(int row1, int row2);
extern void k_muiltply_Row(float k, int row);
extern void Row2_add_kRow1(float k, int row1, int row2);
extern void MoveBiggestElement_to_Top(int k);
extern uint8 Matrix_GaussElimination(void);
extern void Matrix_RowSimplify(void);
extern void Matrix_Solve(float* solve);


extern void ImuGetMagData(_xyz_mag_s16_ary_st *mag_origin_data, _xyz_mag_s16_st *mag_real_data);
extern void imuMagOffset();
extern void imuGetMagData(_xyz_mag_s16_st *mag_data);
extern void CalcData_Input_sum(_xyz_mag_s16_ary_st *mag_origin_data);
extern void Ellipsoid_fitting_Process(void);

#endif

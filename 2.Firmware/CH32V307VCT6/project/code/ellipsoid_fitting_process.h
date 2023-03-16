/*
 * ellipsoid_fitting_process.h
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */
#ifndef CODE_ELLIPSOID_FITTING_PROCESS_H_
#define CODE_ELLIPSOID_FITTING_PROCESS_H_

#include "inc_all.h"
#include "zf_common_headfile.h"

extern float Abs(float a);
extern void ResetMatrix(void);
extern void CalcData_Input(float x, float y, float z);
extern void CalcData_Input_average();
extern void DispMatrix(void);
extern void Row2_swop_Row1(int row1, int row2);
extern void k_muiltply_Row(float k, int row);
extern void Row2_add_kRow1(float k, int row1, int row2);
extern void MoveBiggestElement_to_Top(int k);
extern uint8 Matrix_GaussElimination(void);
extern void Matrix_RowSimplify(void);
extern void Matrix_Solve(float* solve);
extern void Ellipsoid_fitting_Process(void);




#endif

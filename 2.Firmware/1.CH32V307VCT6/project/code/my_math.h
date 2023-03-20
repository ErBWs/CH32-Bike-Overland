/*
 * my_math.h
 *
 *  Created on: 2023��2��7��
 *      Author: sorrymaker
 */

#ifndef CODE_MY_MATH_H_
#define CODE_MY_MATH_H_

#include "zf_common_headfile.h"
#include "inc_all.h"


#define REAL   float
#define TAN_MAP_RES     0.003921569f     /* (smallest non-zero value in table) */
#define RAD_PER_DEG     0.017453293f
#define TAN_MAP_SIZE    256
#define MY_PPPIII   3.14159f
#define MY_PPPIII_HALF   1.570796f

#define my_3_norm(x,y,z) (my_sqrt(my_pow((x)) + my_pow((y)) + my_pow((z))))
#define my_2_norm(x,y) (my_sqrt(my_pow((x)) + my_pow((y))))

#define my_pow(a) ((a)*(a))
#define safe_div(numerator,denominator,safe_value) ( (denominator == 0) ? (safe_value) : ((numerator)/(denominator)) )
//#define ABS(x) ( (x)>0?(x):-(x) )//????
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define _MIN(a, b) ((a) < (b) ? (a) : (b))
#define _MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define my_pow_2_curve(in,a,max) (((1.0f - (a)) + (a) *ABS((in) / (max))) * in)

float my_abs(float f);
REAL fast_atan2(REAL y, REAL x);
//float my_pow(float a);
float my_sqrt(float number);
double mx_sin(double rad);
double my_sin(double rad);
float my_cos(double rad);
float my_deadzone(float x,float ,float zoom);
float my_deadzone_2(float x,float ,float zoom);
float invSqrt(float x);
float my_deadzone_p(float x,float zone);
float my_deadzone_n(float x,float zone);

float To_180_degrees(float x);
double To_180_degrees_db(double x);
//float my_pow_2_curve(float in,float a,float max);
//float safe_div(float numerator ,float denominator,float sv);
float linear_interpolation_5(float range[5],float interpolation[5],float in);//range ??????


#endif /* CODE_MY_MATH_H_ */

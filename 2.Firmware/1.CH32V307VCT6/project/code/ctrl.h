#ifndef _CTRL_H_
#define _CTRL_H_
#include "zf_common_headfile.h"
#include "inc_all.h"
#include "gps_ubx.h"



extern uint32_t back_inter_distance;
extern uint8 stagger_flag;
extern float dynamic_gain;
extern bool servo_forbid;
extern uint16 servo_input_duty;
extern paramType ANGLE_STATIC_BIAS;
extern float temp_x;
extern int16_t fly_wheel_encode;
extern uint32_t myTimeStamp;
void IMUGetCalFun(void);
void ServoControl(void);
void taskTimAllInit(void);
void BackMotoControl(void);
void FlyWheelControl(void);
void UpdateControl(void);
#endif

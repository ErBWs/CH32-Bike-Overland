#ifndef _CTRL_H_
#define _CTRL_H_
#include "zf_common_headfile.h"
#include "inc_all.h"

extern uint32_t back_inter_distance;
extern uint8 stagger_flag;
void IMUGetCalFun(void);
void ServoControl(void);
void taskTimAllInit(void);
void BackMotoControl(void);
void FlyWheelControl(void);
void UpdateControl(void);
#endif

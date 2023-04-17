/*
 * inc_all.h
 *
 *  Created on: Mar 16, 2023
 *      Author: sorrymaker
 *
 */

#ifndef INC_ALL_H_
#define INC_ALL_H_

#define USE_GPS 1

#include "complementary_filter.h"
#include "math.h"
#include "filter.h"
#include "imu.h"
#include "my_math.h"
#include "sendware.h"
#include "vofa.h"
#include "ellipsoid_fitting_process.h"
#include "inertial_navigation.h"
#include "user_flash.h"
#include "easy_key.h"
#include "ips096.h"
#include "moto.h"
#include "encoder.h"
#include "pid.h"
#include "ctrl.h"
#include "jdy34.h"
#include "easy_ui.h"
#include "easy_ui_user_app.h"
#include "profile_photo_erbws.h"
#include "graph_mapping.h"

//#include "ADRC.h"
extern uint32 now_tick;
extern uint16 beep_time;
extern uint16 beep_feq;
#define BEEP_PWM_PIN TIM8_PWM_MAP1_CH4_C13

typedef enum tone_frq
{
    NONE=0,
    DO=500,
    RE=550,
    MI=590,
    FA=640,
    SO=710,
    LA=760,
    TI=830,
    DO1=880,
    RE1=950
};
#define TONE_PLAY(frq,time) beep_feq=frq;       \
                            beep_time = time;   \
                            while(beep_time!=0);\
                            beep_feq=1000;
#endif /* INC_ALL_H_ */

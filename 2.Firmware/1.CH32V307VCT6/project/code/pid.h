#ifndef _PID_H
#define _PID_H
#include <stdint.h>
#include <stdbool.h>
#include "easy_ui.h"
#define ABS(x)		(((x)>0)? (x): -(x))
#define pi 3.14159265358979

#define SERVO_MAX_ANGLE 40.0

#define Limitation(x, low, high) ((x) < (low) ? (low) : ((x) > (high) ? (high) : (x)))
#define SMOOTH_KP_PER_TICK_MS       10

enum {
    LLAST	= 0,
    LAST 	= 1,
    NOW 	= 2,

    POSITION_PID,
    DELTA_PID,
};
extern uint8_t motionflag;
typedef struct _PID_Typedef
{
    paramType Kp;
    paramType Ki;
    paramType Kd;

    float target[3];					//Ŀ��ֵ,����NOW�� LAST�� LLAST���ϴ�
    float feedback[3];					//����ֵ
    float err[3];							//���

    float pout;								//p���
    float iout;								//i���
    float dout;								//d���

    float pos_out;						//����λ��ʽ���
    float last_pos_out;					//�ϴ�λ��ʽ���
    float pos_out0;						//λ��ʽ�����Сֵ

    float delta_u;						//��������ֵ
    float last_delta_out;				//�ϴ�����ʽ���
    float delta_out;					//��������ʽ��� = last_delta_out + delta_u

    float max_err;
    float deadband;						//err < deadband return

    uint32_t pid_mode;
    float MaxOutput;				//����޷�
    float IntegralLimit;		    //�����޷�

    float smoothTargetKp;
    float sport_kp_step;
    bool is_sporting;
} PID_TypeDef;

// PID struct define
extern PID_TypeDef flySpdPid;
extern PID_TypeDef flyAnglePid;
extern PID_TypeDef flyAngleSpdPid;
extern PID_TypeDef backSpdPid;
extern PID_TypeDef dirPid;
extern PID_TypeDef dirDisPid;
extern bool preset1, preset2, preset3;

void PID_Init(
    PID_TypeDef*	pid,
    uint32_t 			mode,
    float 			maxout,
    float 			intergral_limit,
    float 				kp,
    float 				ki,
    float 				kd
);
void PID_Reset(PID_TypeDef	*pid, float kp, float ki, float kd);
float PID_Calculate(PID_TypeDef *pid, float target, float feedback);
void pidAllInit(void);
void pidClear(PID_TypeDef *pid);
void setSmoothKp(PID_TypeDef *pid, float targetKp ,float ms);
void dynamicKpHandler(PID_TypeDef *pid);
#endif




#ifndef _pid_h_
#define _pid_h_

#include "zf_common_typedef.h"
#include "bldc_config.h"

typedef struct 
{
    float kp;           //PI�ջ��ı�������
    float ki;           //PI�ջ��Ļ��ֲ���
    int32 target_speed; //�ջ���Ŀ���ٶ� ��Ҫֱ���޸��������
    int32 real_speed;   //��ǰ���ת��
    int32 error;        //Ŀ���ٶ���ʵ���ٶ����
    int32 out_max;      //�ջ�������
    int32 pout;         //�ջ��������ֵ
    float iout;         //�ջ��������ֵ
    int32 out;          //�ջ����ֵ
    int32 speed_set_last;//��һ���ٶ�����ֵ
}closed_loop_struct;



extern closed_loop_struct motor1_closed_loop;
extern closed_loop_struct motor2_closed_loop;
void closed_loop_pi_init(closed_loop_struct *closed_loop); //PI��ʼ������
void closed_loop_pi_calc(closed_loop_struct *closed_loop, uint8 enable_status, uint32 speed_max, int32 read_speed);

#endif

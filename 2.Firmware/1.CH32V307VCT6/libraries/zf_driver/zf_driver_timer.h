/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          zf_driver_timer
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-09-15        ��W            first version
********************************************************************************************************************/

#ifndef _zf_driver_timer_h
#define _zf_driver_timer_h

#include "ch32v30x_rcc.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x_tim.h"

#include "zf_common_debug.h"
#include "zf_common_clock.h"

//��ö�ٶ��岻�����û��޸�
typedef enum
{
    TIM_1,
    TIM_2,
    TIM_3,
    TIM_4,
    TIM_5,
    TIM_6,
    TIM_7,
    TIM_8,
    TIM_9,
    TIM_10,
}timer_index_enum;

typedef enum
{
    TIMER_SYSTEM_CLOCK,                                                         // ϵͳƵ�ʼ�ʱ ��� 0xFFFF
    TIMER_US,                                                                   // ΢���ʱ ��� 0xFFFF
    TIMER_MS,                                                                   // �����ʱ ��� 0xFFFF/2
}timer_mode_enum;

typedef enum
{
    TIMER_FUNCTION_INIT = 0,                                                    // ����δ��ʼ��
    TIMER_FUNCTION_TIMER,                                                       // ���� TIMER ��ʱ
    TIMER_FUNCTION_PIT,                                                         // ���� PIT
    TIMER_FUNCTION_PWM,                                                         // ���� PWM
    TIMER_FUNCTION_ENCODER,                                                     // ���� ENCODER
    TIMER_FUNCTION_CAMERA,                                                      // ���� CAMERA
}timer_function_enum;


uint8       timer_funciton_check    (timer_index_enum index, timer_function_enum mode);
void        timer_clock_enable      (timer_index_enum index);

void        timer_start             (timer_index_enum index);
void        timer_stop              (timer_index_enum index);
uint16      timer_get               (timer_index_enum index);
void        timer_clear             (timer_index_enum index);

void        timer_init              (timer_index_enum index, timer_mode_enum mode);





#endif

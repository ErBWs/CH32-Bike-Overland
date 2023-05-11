#ifndef _bldc_config_h_
#define _bldc_config_h_


typedef enum
{
    MOTOR_1 = 0,
    MOTOR_2 = 1
}motor_index_enum;


// ϵͳʱ�ӣ����ɸ���
#define SYSTEM_CLOCK                ((uint32)144000000)

// ����PWMƵ��
#define PWM_FREQUENCY               ((uint16)40000)

// PWM����ֵ
#define PWM_PERIOD                  (uint16)(SYSTEM_CLOCK / PWM_FREQUENCY / 2) 

// PWM��������
#define PWM_DEADTIME                (0x1)

// ɲ��ʱռ�ձ� ���ɸ���
#define BLDC_BRAKE_DUTY             (PWM_PERIOD / 100 * BLDC_BRAKE_PERCENT)

//0��������ɲ������     1������
#define BLDC_BRAKE_ENABLE           (1)

// ���ڵ�ص�ѹ������ֵ����λ��������������3.4ʱʹ��3S�����򵱵�ѹС��3*3.4=10.2V��ʱ��ʼ����, ���÷�Χ3.0-3.6
#define BLDC_LOW_VOLTAGE            (3.4f)

// ��ѹ����ʱ�Զ�ɲ�� 0�����Զ�ɲ�� 1���Զ�ɲ��  
#define BLDC_LOW_VOLTAGE_BRAKE      (0)

// ���������ʱ�� һ�㲻���޸�
#define BLDC_COMMUTATION_TIME_MAX   (10000)

//0���������ٶȱջ�     1������  һ�㲻��Ҫ�����ջ�
#define BLDC_CLOSE_LOOP_ENABLE      (0)       

// ���������Ӽ��ٹ���
#define BLDC_SPEED_CURVE_ENABLE     (0)

// �������ת��
#define BLDC_MAX_SPEED              (6000)


// ɲ���������ã���Χ0-100����ֵԽ��ɲ������Խ��
#define BLDC_BRAKE_PERCENT          (50)

#if BLDC_CLOSE_LOOP_ENABLE==1

    // �ջ������Ӽ���ϵ��
    // BLDC_STEP_SPEED������ʹ�õ���������٣�������ֵ�������ģ�ֵԽС�������Խ��
    // �������Ҫ����ͨ����BLDC_SPEED_CURVE_ENABLE����Ϊ0�����ر��������
    #define BLDC_STEP_SPEED         (100)
#else
    // ���������Ӽ���ϵ��
    #define BLDC_STEP_SPEED         (1000)
#endif

    
#endif











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
* �ļ�����          main
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
#include "zf_common_headfile.h"
#include "inc_all.h"
/*
 * TIM2 Servo
 * TIM4 FLY_WHEEL AND BACK WHELL
 * TIM9 FLY_ENCODER
 * TIM10 BACK_MOTO_ENCODER
 *
 * TIM8 BEEP_PWM
 * TIM3 BEEP_AND_KEY_PIT
 *
 */
extern uint8 gps_state;


void play_song(void)
{
    TONE_PLAY(MI,20);
    TONE_PLAY(SO,20);
    TONE_PLAY(LA,20);
    TONE_PLAY(NONE,5);
    TONE_PLAY(LA,30);
    TONE_PLAY(NONE,5);
    TONE_PLAY(LA,20);
    TONE_PLAY(TI,20);
    TONE_PLAY(DO1,20);
    TONE_PLAY(NONE,5);
    TONE_PLAY(DO1,30);
    TONE_PLAY(NONE,5);
    TONE_PLAY(DO1,20);
    TONE_PLAY(RE1,20);
    TONE_PLAY(TI,20);
    TONE_PLAY(NONE,5);
    TONE_PLAY(TI,30);
    TONE_PLAY(NONE,5);
    TONE_PLAY(LA,20);
    TONE_PLAY(SO,20);
    TONE_PLAY(NONE,5);
    TONE_PLAY(SO,10);
    TONE_PLAY(LA,20);
    TONE_PLAY(NONE,100);
    TONE_PLAY(DO,50);
    TONE_PLAY(DO1,50);
}
#define USE_GPS 1
//extern double flashBuf[2000];
int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART
    // �˴���д�û����� ���������ʼ�������
    EasyKeyInit(&keyL,E2);
    EasyKeyInit(&keyC,E3);
    EasyKeyInit(&keyR,E4);
    ips096_init();
//    timer_init(TIM_7,TIMER_US);

////    adc_init(ADC1_IN9_B1,ADC_12BIT);
////    double temp=101.22;
////    SaveToFlashWithConversion(&temp);
////    double count;
////    FlashOperationEnd();
////    ReadFlashWithConversion(&count);
////    printf("%f",count);
//
////    while(1)
////    {
////        system_delay_ms(100);
//////        printf("%d\n", adc_convert(ADC2_IN9_B1));
////        ips096_show_int(0,0,adc_convert(ADC1_IN9_B1),4);
////    }
    encoderInit();
    motoInit();
    imuinit(IMU_ALL);
//    ADRC_Init(&ADRC_GYRO_Controller,&ADRC_SPEED_Controller,&ADRC_SPEED_MIN_Controller);//�Կ��ſ�������ʼ��
    pidAllInit();
    BlueToothInit();

    Butterworth_Parameter_Init();
    backSpdPid.target[NOW]=2;

//    pwm_set_duty(MOTOR_BACK_PIN,5000);
//    system_delay_ms(1000);
//    pwm_set_duty(SERVO_PIN, GetServoDuty(-20));
//    system_delay_ms(1000);
//    pwm_set_duty(SERVO_PIN, GetServoDuty(20));
//    system_delay_ms(1000);
//    pwm_set_duty(SERVO_PIN, GetServoDuty(0));
//while(1);
#if USE_GPS==1
    GPS_init();
#endif
    // �˴���д�û����� ���������ʼ�������
    taskTimAllInit();

    while(1)
    {
#if USE_GPS==1
        if(gps_tau1201_flag==1&&Bike_Start==1)
        {
            uint8 gps_state = gps_data_parse();
            if(gps_state==0)
            {
                uint8 is_finish=0;
                if(gps_tau1201.hpdo<0.75&&pile_state==0)//����׮ģʽ�£���pile_state==1��ȡ���Զ������߼�
                {
                    is_finish = GetPoint(gps_tau1201.latitude, gps_tau1201.longitude,&gps_data);
                    gps_use.delta = yaw_gps_delta(gps_use.points_azimuth, imu_data.mag_yaw);
                }
                pileProcess(gps_tau1201.latitude, gps_tau1201.longitude,&gps_data);
                BlueToothPrintf("\ndelta:%f\n",gps_use.delta);
                BlueToothPrintf("yaw:%f\n",imu_data.mag_yaw);
                BlueToothPrintf("azimuth:%f\n",gps_use.points_azimuth);
//                ips096_show_float(0,0,gps_use.delta,3,3);
//                ips096_show_float(0,8,imu_data.mag_yaw,3,3);
//                printf("dis:%f\n",gps_use.points_distance);
                if(is_finish)
                {
                    stagger_flag=1;
                    motoDutySet(MOTOR_FLY_PIN,0);
                    Bike_Start = 0;
                    play_song();
                    while(1)
                    {
                        printf("Complete!!\n");
                        system_delay_ms(500);
                    }
                    //........//
                }
            }
            gps_tau1201_flag=0;
        }
        if(Bike_Start==0)
        {
            gps_handler();
        }
#endif
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}


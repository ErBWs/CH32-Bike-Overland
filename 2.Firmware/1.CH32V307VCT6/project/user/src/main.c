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
}

int main (void)
{
    clock_init(SYSTEM_CLOCK_120M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART
    pidAllInit();
    MenuInit();
    EasyUIInit(1);
    encoderInit();
    motoInit();
    BlueToothInit();
    imuinit(IMU_ALL);
    Butterworth_Parameter_Init();
#if USE_GPS==1
    GPS_init();
#endif
    EasyUITransitionAnim();
    backSpdPid.target[NOW]=2;
    taskTimAllInit();
//    pit_disable(TIM1_PIT);
    while(1)
    {
        EasyUI(20);
//        printf("A%f\r\n",imu_data.rol);
//        printf("B%f\r\n", atan2f(acc.y,acc.z)*57.29f);
//        BlueToothPrintf("rol:%f\n",imu_data.rol);
//        BlueToothPrintf("yaw:%f\n",imu_data.mag_yaw);
//        BlueToothPrintf("imu_data.inter_pit:%f\n",imu_data.inter_pit);
//        if (imu_data.yaw<0)imu_data.yaw += 360;
//        BlueToothPrintf("yaw:%f\n",imu_data.yaw);
//        BlueToothPrintf("yaw:%f\n",imu_data.mag_yaw);
//        BlueToothPrintf();
//        BlueToothPrintf("yaw:%f\n",0);
//        system_delay_ms(50);

    }
}


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
 * TIM8 BEEP_PWM
 * TIM3 BEEP_AND_KEY_PIT
 *
 */

void systemInit();
float num[8] = {0};
int main (void)
{
    clock_init(SYSTEM_CLOCK_120M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART
    systemInit();
    while(1)
    {
        EasyUI(20);
//        num[0] = flyAnglePid.pos_out;
//        num[1] = temp_x*0.0610f;
//
//        num[2] = (flySpdPid.pos_out<0?-sqrtf(-flySpdPid.pos_out):sqrtf(flySpdPid.pos_out))+0.5;
//        num[3] = imu_data.rol;
//
//        num[4] = 0;
//        num[5] = fly_wheel_encode;
//
//        num[6] = flyAngleSpdPid.pos_out;
//        vcan_sendware(num,sizeof(num));
//        system_delay_ms(10);
//        motoDutySet(MOTOR_BACK_PIN,3000);
//        BlueToothPrintf("speed:%f\n",gps_tau1201.speed);
//        BlueToothPrintf("type:%d\n",gps_data.type);
//        BlueToothPrintf("gpsyaw:%f\n",gps_use.points_azimuth);
//        BlueToothPrintf("yaw:%f\n",imu_data.mag_yaw);
//        BlueToothPrintf("delta:%f\n",gps_use.delta);
//        BlueToothPrintf("distance:%f\n",gps_use.points_distance);
//        if (gps_use.point_count != 0)
//        {
//            BlueToothPrintf("lai:%.9f\n",gps_data_array[gps_use.point_count-1].latitude);
//            BlueToothPrintf("log:%.9f\n",gps_data_array[gps_use.point_count-1].longitude);
//            BlueToothPrintf("type:%d\n",gps_data_array[gps_use.point_count-1].type );
//        }
//        else
//        {
//            BlueToothPrintf("lai:%.9f\n",gps_data_array[gps_use.point_count].latitude);
//            BlueToothPrintf("log:%.9f\n",gps_data_array[gps_use.point_count].longitude);
//            BlueToothPrintf("type:%d\n",gps_data_array[gps_use.point_count].type );
//        }
//
//        system_delay_ms(50);
    }
}




void systemInit(void)
{
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
    backSpdPid.target[NOW] = 2;
    taskTimAllInit();
}


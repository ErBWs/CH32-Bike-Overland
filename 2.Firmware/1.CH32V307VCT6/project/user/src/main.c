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

<<<<<<< Updated upstream
#define USE_GPS 1
=======
extern uint8 gps_state;
#define USE_GPS 0
>>>>>>> Stashed changes
//extern double flashBuf[2000];
int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART
    // �˴���д�û����� ���������ʼ�������
    ips114_init();
//    ips114_show_string(0, 0, "he");
    encoderInit();
//    printf("OK\r\n");
    motoInit();
<<<<<<< Updated upstream
    pit_ms_init(TIM1_PIT,10);
    gpio_init(C13, GPO, 0, GPO_PUSH_PULL);//BEEP
    imuinit(IMU_ALL);
=======
//    pwm_set_duty(MOTOR_FLY_PIN,8000);
//    while(1)
//    {
//        system_delay_ms(50);
//        printf("A%d\r\n", encoder_get_count(ENCODER_BACK_WHEEL_TIM));
//        encoder_clear_count(ENCODER_BACK_WHEEL_TIM);
//    }
//    pit_ms_init(TIM1_PIT,10);
//    gpio_init(C13, GPO, 0, GPO_PUSH_PULL);//BEEP
    imuinit(IMU_660RA);
    while(1)
    {
//        imu963ra_get_mag();
        imu660ra_get_acc();
        system_delay_ms(50);
        printf("A%d\r\n",imu660ra_acc_z);
    }
//    pidAllInit();
//    BlueToothInit();
//    Butterworth_Parameter_Init();

>>>>>>> Stashed changes
#if USE_GPS==1
    GPS_init();
#endif
    pidAllInit();
    BlueToothInit();
    Butterworth_Parameter_Init();


    // �˴���д�û����� ���������ʼ�������
    taskTimAllInit();

    while(1)
    {

//        imu660ra_get_gyro();
//        ips114_show_int(0, 16, imu660ra_gyro_x, 5);
//        vcan_sendware(num_float, sizeof(num_float));
//        system_delay_ms(20);
#if USE_GPS==1
        if(gps_tau1201_flag==1&&Bike_Start==1)
        {
            uint8 gps_state = gps_data_parse();
            if(gps_state==0)
            {
                uint8 is_finish;
                is_finish = get_point(gps_tau1201.latitude, gps_tau1201.longitude,&gps_data);
                two_points_message(gps_tau1201.latitude, gps_tau1201.longitude, &gps_data,&gps_use);//���ݵ�ǰ��γ�Լ��õ���Ŀ�����㣬�ŵ�gps_use��
                gps_use.delta = yaw_gps_delta(gps_use.points_azimuth, imu_data.mag_yaw);
                printf("delta:%f\n",gps_use.delta);
                printf("dis:%f\n",gps_use.points_distance);
                if(is_finish)
                {
                    while(1)
                    {
                        printf("Complete!!\n");
                        system_delay_ms(500);
                    }
                    //........//
                }
            }
//            gps_state=1;
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


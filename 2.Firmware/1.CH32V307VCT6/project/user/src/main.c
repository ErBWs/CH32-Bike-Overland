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

//extern float num_float[8];
#define USE_GPS 1
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
    pit_ms_init(TIM1_PIT,10);
    gpio_init(C13, GPO, 0, GPO_PUSH_PULL);//BEEP
    imuinit(IMU_ALL);
#if USE_GPS==1
    GPS_init();
#endif
    pidAllInit();
    BlueToothInit();
    Butterworth_Parameter_Init();


    // �˴���д�û����� ���������ʼ�������
    taskTimAllInit();

    static uint8 toggle=0;
    while(1)
    {

//        imu660ra_get_gyro();
//        ips114_show_int(0, 16, imu660ra_gyro_x, 5);
//        vcan_sendware(num_float, sizeof(num_float));
//        system_delay_ms(20);
#if USE_GPS==1
//        if(read_key_flag==1)
//        {
//            toggle ^=toggle;
//            if(toggle==0)
//            {
//                FlashOperationEnd();
//            }
//            read_key_flag = 0;
//        }
        if(gps_tau1201_flag==1)//&&toggle==1
        {
            uint8 state = gps_data_parse();
            if(state==0)
            {
                 two_points_message(gps_tau1201.latitude, gps_tau1201.longitude, &gps_data_array[gps_use.use_point_count]);
                 gps_use.delta = yaw_gps_delta(gps_use.points_azimuth, imu_data.mag_yaw);
                 change_point(&gps_data);
                 ips114_show_float(10, 0, gps_use.delta, 3, 6);
                 ips114_show_float(10, 16, gps_use.points_distance, 3, 6);
                 ips114_show_float(10, 32, imu_data.mag_yaw, 3, 6);

//                 printf("delta:%f\n",gps_use.delta);
            }
            gps_tau1201_flag=0;
        }
#endif
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}


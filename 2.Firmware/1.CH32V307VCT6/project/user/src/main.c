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

int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART
    // �˴���д�û����� ���������ʼ�������
    encoderInit();
    motoInit();

    icm20602_init();
    IMU_Offset();
    pidAllInit();
    BlueToothInit();
//    gps_init();
    Butterworth_Parameter_Init();
//    motoDutySet(MOTOR_FLY_PIN,2000);

    // �˴���д�û����� ���������ʼ�������
    taskTimAllInit();

//    backSpdPid.target[NOW]=5;
//    int16_t fly_wheel_encode=0;
    while(1)
    {
        IMUGetCalFun();
//        if(gps_tau1201_flag==1)
//        {
//            uint8 state = gps_data_parse();
//            if(state==0)
//            {
//                printf("A%.8f\r\n\rB%.8f\r\n",gps_tau1201.longitude,gps_tau1201.latitude);
//            }
//            gps_tau1201_flag=0;
//        }
        // �˴���д��Ҫѭ��ִ�еĴ���
//        system_delay_ms(100);
//        printf("%f",imu_data.rol);
//        printf("A%d\r\n",encoder_get_count(ENCODER_BACK_WHEEL_TIM));
//        fly_wheel_encode = encoder_get_count(ENCODER_FLY_WHEEL_TIM);
//        printf("A%d\r\n",fly_wheel_encode);
    }
}


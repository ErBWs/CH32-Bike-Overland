/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2022-09-15        大W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "inc_all.h"

//extern float num_float[8];
#define USE_GPS 1
//extern double flashBuf[2000];
int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 144MHz
    debug_init();                                                               // 初始化默认 Debug UART
    // 此处编写用户代码 例如外设初始化代码等
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


    // 此处编写用户代码 例如外设初始化代码等
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
        // 此处编写需要循环执行的代码
    }
}


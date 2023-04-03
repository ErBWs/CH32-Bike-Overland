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
* 文件名称          zf_device_imu660ra
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
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   // 硬件 SPI 引脚
*                   SCL/SPC           查看 zf_device_imu660ra.h 中 IMU660RA_SPC_PIN 宏定义
*                   SDA/DSI           查看 zf_device_imu660ra.h 中 IMU660RA_SDI_PIN 宏定义
*                   SA0/SDO           查看 zf_device_imu660ra.h 中 IMU660RA_SDO_PIN 宏定义
*                   CS                查看 zf_device_imu660ra.h 中 IMU660RA_CS_PIN 宏定义
*                   VCC               3.3V电源
*                   GND               电源地
*                   其余引脚悬空
*
*                   // 软件 IIC 引脚
*                   SCL/SPC           查看 zf_device_imu660ra.h 中 IMU660RA_SCL_PIN 宏定义
*                   SDA/DSI           查看 zf_device_imu660ra.h 中 IMU660RA_SDA_PIN 宏定义
*                   VCC               3.3V电源
*                   GND               电源地
*                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/
#ifndef _zf_device_imu660ra_h_
#define _zf_device_imu660ra_h_

#include "zf_common_typedef.h"

#define IMU660RA_USE_SOFT_IIC       (0)                                         // 默认使用硬件 SPI 方式驱动
#if IMU660RA_USE_SOFT_IIC                                                       // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 IIC 驱动====================================================
#define IMU660RA_SOFT_IIC_DELAY     (10 )                                       // 软件 IIC 的时钟延时周期 数值越小 IIC 通信速率越快
#define IMU660RA_SCL_PIN            (B13)                                       // 软件 IIC SCL 引脚 连接 IMU660RA 的 SCL 引脚
#define IMU660RA_SDA_PIN            (B15)                                       // 软件 IIC SDA 引脚 连接 IMU660RA 的 SDA 引脚
//====================================================软件 IIC 驱动====================================================
#else

//====================================================硬件 SPI 驱动====================================================
#define IMU660RA_SPI_SPEED          (10*1000*1000)                              // 硬件 SPI 速率
#define IMU660RA_SPI                SPI_3                                       // 硬件 SPI 号
#define IMU660RA_SPC_PIN            SPI3_MAP0_SCK_B3                            // 硬件 SPI SCK 引脚
#define IMU660RA_SDI_PIN            SPI3_MAP0_MOSI_B5                           // 硬件 SPI MOSI 引脚
#define IMU660RA_SDO_PIN            SPI3_MAP0_MISO_B4                           // 硬件 SPI MISO 引脚

//====================================================硬件 SPI 驱动====================================================
#endif
#define IMU660RA_CS_PIN             (C10)                                       // CS 片选引脚
#define IMU660RA_CS(x)              ((x) ? (gpio_high(IMU660RA_CS_PIN)) : (gpio_low(IMU660RA_CS_PIN)))

#define IMU660RA_TIMEOUT_COUNT      (0x00FF)                                    // IMU660RA 超时计数

#define IMU660RA_DEV_ADDR           (0x69)                                      // SA0接地：0x68 SA0上拉：0x69 模块默认上拉
#define IMU660RA_SPI_W              (0x00)
#define IMU660RA_SPI_R              (0x80)

#define IMU660RA_CHIP_ID            (0x00)
#define IMU660RA_PWR_CONF           (0x7C)
#define IMU660RA_PWR_CTRL           (0x7D)
#define IMU660RA_INIT_CTRL          (0x59)
#define IMU660RA_INIT_DATA          (0x5E)
#define IMU660RA_INT_STA            (0x21)
#define IMU660RA_ACC_ADDRESS        (0x0C)
#define IMU660RA_GYRO_ADDRESS       (0x12)
#define IMU660RA_ACC_CONF           (0x40)
#define IMU660RA_ACC_RANGE          (0x41)

#define IMU660RA_GYR_CONF           (0x42)
#define IMU660RA_GYR_RANGE          (0x43)

#define IMU660RA_ACC_SAMPLE         (0x02)                                      // 加速度计量程
// 设置为:0x00 加速度计量程为:±2g         获取到的加速度计数据 除以 16384   可以转化为带物理单位的数据 单位：g(m/s^2)
// 设置为:0x01 加速度计量程为:±4g         获取到的加速度计数据 除以 8192    可以转化为带物理单位的数据 单位：g(m/s^2)
// 设置为:0x02 加速度计量程为:±8g         获取到的加速度计数据 除以 4096    可以转化为带物理单位的数据 单位：g(m/s^2)
// 设置为:0x03 加速度计量程为:±16g        获取到的加速度计数据 除以 2048    可以转化为带物理单位的数据 单位：g(m/s^2)


#define IMU660RA_GYR_SAMPLE         (0x00)                                      // 陀螺仪量程
// 设置为:0x00 陀螺仪量程为:±2000dps     获取到的陀螺仪数据 除以 16.4       可以转化为带物理单位的数据 单位为：°/s
// 设置为:0x01 陀螺仪量程为:±1000dps     获取到的陀螺仪数据 除以 32.8       可以转化为带物理单位的数据 单位为：°/s
// 设置为:0x02 陀螺仪量程为:±500 dps     获取到的陀螺仪数据 除以 65.6       可以转化为带物理单位的数据 单位为：°/s
// 设置为:0x03 陀螺仪量程为:±250 dps     获取到的陀螺仪数据 除以 131.2      可以转化为带物理单位的数据 单位为：°/s
// 设置为:0x04 陀螺仪量程为:±125 dps     获取到的陀螺仪数据 除以 262.4      可以转化为带物理单位的数据 单位为：°/s



extern int16 imu660ra_gyro_x, imu660ra_gyro_y, imu660ra_gyro_z;                 // 三轴陀螺仪数据      gyro (陀螺仪)
extern int16 imu660ra_acc_x, imu660ra_acc_y, imu660ra_acc_z;                    // 三轴加速度计数据     acc (accelerometer 加速度计)


void  imu660ra_get_acc              (void);                                     // 获取 IMU660RA 加速度计数据
void  imu660ra_get_gyro             (void);                                     // 获取 IMU660RA 陀螺仪数据
float imu660ra_acc_transition       (int16 acc_value);                          // 将 IMU660RA 加速度计数据转换为实际物理数据
float imu660ra_gyro_transition      (int16 gyro_value);                         // 将 IMU660RA 陀螺仪数据转换为实际物理数据
uint8 imu660ra_init                 (void);                                     // 初始化 IMU660RA

#endif


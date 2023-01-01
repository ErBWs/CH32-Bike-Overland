/*********************************************************************************************************************
* MM32F527X-E9P Opensourec Library 即（MM32F527X-E9P 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 MM32F527X-E9P 开源库的一部分
* 
* MM32F527X-E9P 开源库 是免费软件
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
* 文件名称          zf_device_icm20602
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK 5.37
* 适用平台          MM32F527X_E9P
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   // 硬件 SPI 引脚
*                   SCL/SPC             查看 zf_device_icm20602.h 中 ICM20602_SPC_PIN 宏定义
*                   SDA/DSI             查看 zf_device_icm20602.h 中 ICM20602_SDI_PIN 宏定义
*                   SA0/SDO             查看 zf_device_icm20602.h 中 ICM20602_SDO_PIN 宏定义
*                   CS                  查看 zf_device_icm20602.h 中 ICM20602_CS_PIN 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*
*                   // 软件 IIC 引脚
*                   SCL/SPC             查看 zf_device_icm20602.h 中 ICM20602_SCL_PIN 宏定义
*                   SDA/DSI             查看 zf_device_icm20602.h 中 ICM20602_SDA_PIN 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_icm20602_h_
#define _zf_device_icm20602_h_

#include "zf_common_typedef.h"

#define ICM20602_USE_SOFT_IIC       (0)                                         // 默认使用硬件 SPI 方式驱动
#if ICM20602_USE_SOFT_IIC                                                       // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 IIC 驱动====================================================
#define ICM20602_SOFT_IIC_DELAY     (10 )                                       // 软件 IIC 的时钟延时周期 数值越小 IIC 通信速率越快
#define ICM20602_SCL_PIN            (B13)                                       // 软件 IIC SCL 引脚 连接 ICM20602 的 SCL 引脚
#define ICM20602_SDA_PIN            (B15)                                       // 软件 IIC SDA 引脚 连接 ICM20602 的 SDA 引脚
//====================================================软件 IIC 驱动====================================================
#else
//====================================================硬件 SPI 驱动====================================================
#define ICM20602_SPI_SPEED          (10 * 1000 * 1000)                          // 硬件 SPI 速率
#define ICM20602_SPI                (SPI_2)                                     // 硬件 SPI 号
#define ICM20602_SPC_PIN            (SPI2_SCK_B13)                              // 硬件 SPI SCK 引脚
#define ICM20602_SDI_PIN            (SPI2_MOSI_B15)                             // 硬件 SPI MOSI 引脚
#define ICM20602_SDO_PIN            (SPI2_MISO_B14)                             // 硬件 SPI MISO 引脚
//====================================================硬件 SPI 驱动====================================================
#endif
#define ICM20602_CS_PIN             (B12)                                       // CS 片选引脚
#define ICM20602_CS(x)              ((x) ? (gpio_high(ICM20602_CS_PIN)) : (gpio_low(ICM20602_CS_PIN)))

#define ICM20602_TIMEOUT_COUNT      (0x00FF)                                    // ICM20602 超时计数

//================================================定义 ICM20602 内部地址================================================
#define ICM20602_DEV_ADDR           (0x69)                                      // SA0接地：0x68 SA0上拉：0x69 模块默认上拉
#define ICM20602_SPI_W              (0x00)
#define ICM20602_SPI_R              (0x80)

#define ICM20602_XG_OFFS_TC_H       (0x04)
#define ICM20602_XG_OFFS_TC_L       (0x05)
#define ICM20602_YG_OFFS_TC_H       (0x07)
#define ICM20602_YG_OFFS_TC_L       (0x08)
#define ICM20602_ZG_OFFS_TC_H       (0x0A)
#define ICM20602_ZG_OFFS_TC_L       (0x0B)
#define ICM20602_SELF_TEST_X_ACCEL  (0x0D)
#define ICM20602_SELF_TEST_Y_ACCEL  (0x0E)
#define ICM20602_SELF_TEST_Z_ACCEL  (0x0F)
#define ICM20602_XG_OFFS_USRH       (0x13)
#define ICM20602_XG_OFFS_USRL       (0x14)
#define ICM20602_YG_OFFS_USRH       (0x15)
#define ICM20602_YG_OFFS_USRL       (0x16)
#define ICM20602_ZG_OFFS_USRH       (0x17)
#define ICM20602_ZG_OFFS_USRL       (0x18)
#define ICM20602_SMPLRT_DIV         (0x19)
#define ICM20602_CONFIG             (0x1A)
#define ICM20602_GYRO_CONFIG        (0x1B)
#define ICM20602_ACCEL_CONFIG       (0x1C)
#define ICM20602_ACCEL_CONFIG_2     (0x1D)
#define ICM20602_LP_MODE_CFG        (0x1E)
#define ICM20602_ACCEL_WOM_X_THR    (0x20)
#define ICM20602_ACCEL_WOM_Y_THR    (0x21)
#define ICM20602_ACCEL_WOM_Z_THR    (0x22)
#define ICM20602_FIFO_EN            (0x23)
#define ICM20602_FSYNC_INT          (0x36)
#define ICM20602_INT_PIN_CFG        (0x37)
#define ICM20602_INT_ENABLE         (0x38)
#define ICM20602_FIFO_WM_INT_STATUS (0x39)
#define ICM20602_INT_STATUS         (0x3A)
#define ICM20602_ACCEL_XOUT_H       (0x3B)
#define ICM20602_ACCEL_XOUT_L       (0x3C)
#define ICM20602_ACCEL_YOUT_H       (0x3D)
#define ICM20602_ACCEL_YOUT_L       (0x3E)
#define ICM20602_ACCEL_ZOUT_H       (0x3F)
#define ICM20602_ACCEL_ZOUT_L       (0x40)
#define ICM20602_TEMP_OUT_H         (0x41)
#define ICM20602_TEMP_OUT_L         (0x42)
#define ICM20602_GYRO_XOUT_H        (0x43)
#define ICM20602_GYRO_XOUT_L        (0x44)
#define ICM20602_GYRO_YOUT_H        (0x45)
#define ICM20602_GYRO_YOUT_L        (0x46)
#define ICM20602_GYRO_ZOUT_H        (0x47)
#define ICM20602_GYRO_ZOUT_L        (0x48)
#define ICM20602_SELF_TEST_X_GYRO   (0x50)
#define ICM20602_SELF_TEST_Y_GYRO   (0x51)
#define ICM20602_SELF_TEST_Z_GYRO   (0x52)
#define ICM20602_FIFO_WM_TH1        (0x60)
#define ICM20602_FIFO_WM_TH2        (0x61)
#define ICM20602_SIGNAL_PATH_RESET  (0x68)
#define ICM20602_ACCEL_INTEL_CTRL   (0x69)
#define ICM20602_USER_CTRL          (0x6A)
#define ICM20602_PWR_MGMT_1         (0x6B)
#define ICM20602_PWR_MGMT_2         (0x6C)
#define ICM20602_I2C_IF             (0x70)
#define ICM20602_FIFO_COUNTH        (0x72)
#define ICM20602_FIFO_COUNTL        (0x73)
#define ICM20602_FIFO_R_W           (0x74)
#define ICM20602_WHO_AM_I           (0x75)
#define ICM20602_XA_OFFSET_H        (0x77)
#define ICM20602_XA_OFFSET_L        (0x78)
#define ICM20602_YA_OFFSET_H        (0x7A)
#define ICM20602_YA_OFFSET_L        (0x7B)
#define ICM20602_ZA_OFFSET_H        (0x7D)
#define ICM20602_ZA_OFFSET_L        (0x7E)

#define ICM20602_ACC_SAMPLE         (0x10)                                      // 加速度计量程
// 设置为:0x00 加速度计量程为:±2g          获取到的加速度计数据 除以16384      可以转化为带物理单位的数据，单位：g(m/s^2)
// 设置为:0x08 加速度计量程为:±4g          获取到的加速度计数据 除以8192       可以转化为带物理单位的数据，单位：g(m/s^2)
// 设置为:0x10 加速度计量程为:±8g          获取到的加速度计数据 除以4096       可以转化为带物理单位的数据，单位：g(m/s^2)
// 设置为:0x18 加速度计量程为:±16g         获取到的加速度计数据 除以2048       可以转化为带物理单位的数据，单位：g(m/s^2)

#define ICM20602_GYR_SAMPLE         (0x18)                                      // 陀螺仪量程
// 设置为:0x00 陀螺仪量程为:±250 dps     获取到的陀螺仪数据除以131           可以转化为带物理单位的数据，单位为：°/s
// 设置为:0x08 陀螺仪量程为:±500 dps     获取到的陀螺仪数据除以65.5          可以转化为带物理单位的数据，单位为：°/s
// 设置为:0x10 陀螺仪量程为:±1000dps     获取到的陀螺仪数据除以32.8          可以转化为带物理单位的数据，单位为：°/s
// 设置为:0x18 陀螺仪量程为:±2000dps     获取到的陀螺仪数据除以16.4          可以转化为带物理单位的数据，单位为：°/s

//================================================定义 ICM20602 内部地址================================================

extern int16 icm20602_gyro_x, icm20602_gyro_y, icm20602_gyro_z;                 // 三轴陀螺仪数据
extern int16 icm20602_acc_x, icm20602_acc_y, icm20602_acc_z;                    // 三轴加速度计数据

void    icm20602_get_acc            (void);
void    icm20602_get_gyro           (void);
float   icm20602_acc_transition     (int16 acc_value);                          // 将 ICM20602 加速度计数据转换为实际物理数据
float   icm20602_gyro_transition    (int16 gyro_value);                         // 将 ICM20602 陀螺仪数据转换为实际物理数据
uint8   icm20602_init               (void);

#endif


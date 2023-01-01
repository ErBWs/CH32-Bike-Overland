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
* 文件名称          zf_device_mpu6050
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
*                   软件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_mpu6050.h 中 MPU6050_SOFT_IIC_SCL 宏定义
*                   SDA                 查看 zf_device_mpu6050.h 中 MPU6050_SOFT_IIC_SDA 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*
*                   硬件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_mpu6050.h 中 MPU6050_IIC_SCL 宏定义
*                   SDA                 查看 zf_device_mpu6050.h 中 MPU6050_IIC_SDA 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_mpu6050_h_
#define _zf_device_mpu6050_h_

#include "zf_common_typedef.h"

#define MPU6050_USE_SOFT_IIC        (1)                                         // 默认使用软件 IIC 方式驱动 建议使用软件 IIC 方式
#if MPU6050_USE_SOFT_IIC                                                        // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 IIC 驱动====================================================
#define MPU6050_SOFT_IIC_DELAY      (10 )                                       // 软件 IIC 的时钟延时周期 数值越小 IIC 通信速率越快
#define MPU6050_SCL_PIN             (B13)                                       // 软件 IIC SCL 引脚 连接 MPU6050 的 SCL 引脚
#define MPU6050_SDA_PIN             (B15)                                       // 软件 IIC SDA 引脚 连接 MPU6050 的 SDA 引脚
//====================================================软件 IIC 驱动====================================================
#else
//====================================================硬件 IIC 驱动====================================================
#define MPU6050_IIC_SPEED           (400000     )                               // 硬件 IIC 通信速率 最高 400KHz 不建议低于 40KHz
#define MPU6050_IIC                 (IIC_1      )                               // 硬件 IIC SCL 引脚 连接 MPU6050 的 SCL 引脚
#define MPU6050_SCL_PIN             (IIC1_SCL_C6)                               // 硬件 IIC SCL 引脚 连接 MPU6050 的 SCL 引脚
#define MPU6050_SDA_PIN             (IIC1_SDA_C7)                               // 硬件 IIC SDA 引脚 连接 MPU6050 的 SDA 引脚
//====================================================硬件 IIC 驱动====================================================
#endif

#define MPU6050_TIMEOUT_COUNT       (0x00FF)                                    // MPU6050 超时计数

//================================================定义 MPU6050 内部地址================================================
#define MPU6050_DEV_ADDR            (0xD0>>1)                                   // IIC写入时的地址字节数据，+1为读取

#define MPU6050_SMPLRT_DIV          (0x19)                                      // 陀螺仪采样率，典型值：0x07(125Hz)
#define MPU6050_CONFIG              (0x1A)                                      // 低通滤波频率，典型值：0x06(5Hz)
#define MPU6050_GYRO_CONFIG         (0x1B)                                      // 陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define MPU6050_ACCEL_CONFIG        (0x1C)                                      // 加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define MPU6050_INT_PIN_CFG         (0x37)                                      // 设置6050辅助I2C为直通模式寄存器
#define MPU6050_ACCEL_XOUT_H        (0x3B)
#define MPU6050_ACCEL_XOUT_L        (0x3C)
#define MPU6050_ACCEL_YOUT_H        (0x3D)
#define MPU6050_ACCEL_YOUT_L        (0x3E)
#define MPU6050_ACCEL_ZOUT_H        (0x3F)
#define MPU6050_ACCEL_ZOUT_L        (0x40)
#define MPU6050_GYRO_XOUT_H         (0x43)
#define MPU6050_GYRO_XOUT_L         (0x44)
#define MPU6050_GYRO_YOUT_H         (0x45)
#define MPU6050_GYRO_YOUT_L         (0x46)
#define MPU6050_GYRO_ZOUT_H         (0x47)
#define MPU6050_GYRO_ZOUT_L         (0x48)
#define MPU6050_USER_CONTROL        (0x6A)                                      // 关闭6050对辅助I2C设备的控制
#define MPU6050_PWR_MGMT_1          (0x6B)                                      // 电源管理，典型值：0x00(正常启用)
#define MPU6050_WHO_AM_I            (0x75)                                      // IIC地址寄存器(默认数值0x68，只读)

#define MPU6050_ACC_SAMPLE          (0x10)                                      // 加速度计量程
// 设置为:0x00 陀螺仪量程为:±250 dps     获取到的陀螺仪数据除以131.2         可以转化为带物理单位的数据，单位为：°/s
// 设置为:0x08 陀螺仪量程为:±500 dps     获取到的陀螺仪数据除以65.6          可以转化为带物理单位的数据，单位为：°/s
// 设置为:0x10 陀螺仪量程为:±1000dps     获取到的陀螺仪数据除以32.8          可以转化为带物理单位的数据，单位为：°/s
// 设置为:0x18 陀螺仪量程为:±2000dps     获取到的陀螺仪数据除以16.4          可以转化为带物理单位的数据，单位为：°/s

#define MPU6050_GYR_SAMPLE          (0x18)                                      // 陀螺仪量程
// 设置为:0x00 陀螺仪量程为:±250 dps     获取到的陀螺仪数据除以131.2         可以转化为带物理单位的数据，单位为：°/s
// 设置为:0x08 陀螺仪量程为:±500 dps     获取到的陀螺仪数据除以65.6          可以转化为带物理单位的数据，单位为：°/s
// 设置为:0x10 陀螺仪量程为:±1000dps     获取到的陀螺仪数据除以32.8          可以转化为带物理单位的数据，单位为：°/s
// 设置为:0x18 陀螺仪量程为:±2000dps     获取到的陀螺仪数据除以16.4          可以转化为带物理单位的数据，单位为：°/s

//================================================定义 MPU6050 内部地址================================================

extern int16 mpu6050_gyro_x, mpu6050_gyro_y, mpu6050_gyro_z;                    // 三轴陀螺仪数据      gyro (陀螺仪)
extern int16 mpu6050_acc_x, mpu6050_acc_y, mpu6050_acc_z;                       // 三轴加速度计数据    acc (accelerometer 加速度计)

void    mpu6050_get_acc             (void);
void    mpu6050_get_gyro            (void);
float   mpu6050_acc_transition      (int16 acc_value);                          // 将 MPU6050 加速度计数据转换为实际物理数据
float   mpu6050_gyro_transition     (int16 gyro_value);                         // 将 MPU6050 陀螺仪数据转换为实际物理数据
uint8   mpu6050_init                (void);

#endif

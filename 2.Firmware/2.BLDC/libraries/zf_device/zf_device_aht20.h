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
* 文件名称          zf_device_aht20
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
* 接线定义:
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   软件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_aht20.h 中 AHT20_SOFT_IIC_SCL 宏定义
*                   SDA                 查看 zf_device_aht20.h 中 AHT20_SOFT_IIC_SDA 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*
*                   硬件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_aht20.h 中 AHT20_IIC_SCL 宏定义
*                   SDA                 查看 zf_device_aht20.h 中 AHT20_IIC_SDA 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_aht20_h_
#define _zf_device_aht20_h_

#include "zf_common_clock.h"
#include "zf_common_debug.h"

#include "zf_driver_delay.h"

#include "zf_driver_soft_iic.h"

#define AHT20_USE_SOFT_IIC          (1)                                         // 默认使用软件 IIC 方式驱动 建议使用软件 IIC 方式
#if AHT20_USE_SOFT_IIC                                                          // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 IIC 驱动====================================================
#define AHT20_SOFT_IIC_DELAY        (10 )                                       // 软件 IIC 的时钟延时周期 数值越小 IIC 通信速率越快
#define AHT20_SCL_PIN               (B10)                                       // 软件 IIC SCL 引脚 连接 MPU6050 的 SCL 引脚
#define AHT20_SDA_PIN               (B11)                                       // 软件 IIC SDA 引脚 连接 MPU6050 的 SDA 引脚
//====================================================软件 IIC 驱动====================================================
#else
//====================================================硬件 IIC 驱动====================================================
#define AHT20_IIC_SPEED             (400000     )                               // 硬件 IIC 通信速率 最高 400KHz 不建议低于 40KHz
#define AHT20_IIC                   (IIC_2      )                               // 硬件 IIC SCL 引脚 连接 MPU6050 的 SCL 引脚
#define AHT20_SCL_PIN               (IIC2_SCL_B10)                              // 硬件 IIC SCL 引脚 连接 MPU6050 的 SCL 引脚
#define AHT20_SDA_PIN               (IIC2_SDA_B11)                              // 硬件 IIC SDA 引脚 连接 MPU6050 的 SDA 引脚
//====================================================硬件 IIC 驱动====================================================
#endif

#define AHT20_TIMEOUT_COUNT         (0x001F)                                    // MPU6050 超时计数

//================================================定义 AHT20 内部地址================================================
#define	AHT20_DEV_ADDR              (0x38)

#define	AHT20_READ_STATE            (0x71)
#define	AHT20_CAL_ENABLE            (0x08)
#define	AHT20_STATE_BUSY            (0x80)

#define	AHT20_MEASURE_CMD           (0xAC)

#define	AHT20_SELF_INIT             (0xBE)
//================================================定义 AHT20 内部地址================================================

extern float aht_temperature, aht_humidity;

void    aht20_read_data     (void);
uint8   aht20_init          (void);

#endif

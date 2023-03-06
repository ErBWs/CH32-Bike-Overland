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
* 文件名称          zf_device_gt911
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
*                   SCL                 查看 zf_device_gt911.h 中 GT911_SOFT_IIC_SCL_PIN 宏定义
*                   SDA                 查看 zf_device_gt911.h 中 GT911_SOFT_IIC_SDA_PIN 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   硬件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_gt911.h 中 GT911_IIC_SCL_PIN 宏定义
*                   SDA                 查看 zf_device_gt911.h 中 GT911_IIC_SDA_PIN 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_gt911_h_
#define _zf_device_gt911_h_

#include "zf_common_typedef.h"

#define GT911_USE_SOFT_IIC          ( 1 )                                       // 默认使用软件 IIC 方式驱动 建议使用软件 IIC 方式
#if GT911_USE_SOFT_IIC                                                          // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 IIC 驱动====================================================
#define GT911_SOFT_IIC_DELAY        ( 10 )                                      // 软件 IIC 的时钟延时周期 数值越小 IIC 通信速率越快
#define GT911_SCL_PIN               ( C2 )                                      // 软件 IIC SCL 引脚 连接 GT911 的 SCL 引脚
#define GT911_SDA_PIN               ( C3 )                                      // 软件 IIC SDA 引脚 连接 GT911 的 SDA 引脚
//====================================================软件 IIC 驱动====================================================
#else
//====================================================硬件 IIC 驱动====================================================
#define GT911_IIC_SPEED             ( 400 * 1000  )                             // 硬件 IIC 通信速率 最高 400KHz 不建议低于 40KHz
#define GT911_IIC                   ( IIC_2       )                             // 硬件 IIC
#define GT911_SCL_PIN               ( IIC2_SCL_C2 )                             // 硬件 IIC SCL 引脚 连接 GT911 的 SCL 引脚
#define GT911_SDA_PIN               ( IIC2_SDA_C3 )                             // 硬件 IIC SDA 引脚 连接 GT911 的 SDA 引脚
//====================================================硬件 IIC 驱动====================================================
#endif

#define GT911_RST_PIN               ( F11 )                                     // GT911 复位引脚
#define GT911_INT_PIN               ( D6  )                                     // GT911 中断引脚

#define GT911_RST(x)                ((x) ? (gpio_high(GT911_RST_PIN)) : (gpio_low(GT911_RST_PIN)))
#define GT911_INT(x)                ((x) ? (gpio_high(GT911_INT_PIN)) : (gpio_low(GT911_INT_PIN)))

#define IPS350_DEFAULT_DIR          ( GT911_PORTAIT )                           // 默认的方向
#define GT911_TIMEOUT_COUNT         ( 0x000F )                                  // GT911 超时计数

#define GT911_IIC_ADDR              ( 0x5D )                                    // 0x5D or 0x14
#define GT911_READ_ADDR             ( 0x814E )                                  // touch point information
#define GT911_ID_ADDR               ( 0x8140 )                                  // ID of touch IC
#define GT911_TOUCH_DATA_ADDR       ( 0x8150 )

typedef enum
{
    GT911_PORTAIT                   = 0,                                        // 竖屏模式
    GT911_PORTAIT_180               = 1,                                        // 竖屏模式  旋转180
    GT911_CROSSWISE                 = 2,                                        // 横屏模式
    GT911_CROSSWISE_180             = 3,                                        // 横屏模式  旋转180
}gt911_dir_enum;

typedef struct
{
    uint16                      x_axis;
    uint16                      y_axis;
}gt911_data_struct;

extern gt911_data_struct gt911_contact_state[5];

void    gt911_set_dir   (gt911_dir_enum dir);
uint8   gt911_scanner   (void);

uint8   gt911_init      (void);

#endif

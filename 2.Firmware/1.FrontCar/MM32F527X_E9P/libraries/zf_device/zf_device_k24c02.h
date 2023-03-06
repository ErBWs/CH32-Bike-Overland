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
* 文件名称          zf_device_k24c02
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
*                   SCL                 查看 zf_device_k24c02.h 中 K24C02_SOFT_IIC_SCL_PIN 宏定义
*                   SDA                 查看 zf_device_k24c02.h 中 K24C02_SOFT_IIC_SDA_PIN 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   硬件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_k24c02.h 中 K24C02_IIC_SCL_PIN 宏定义
*                   SDA                 查看 zf_device_k24c02.h 中 K24C02_IIC_SDA_PIN 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_k24c02_h_
#define _zf_device_k24c02_h_

#include "zf_common_typedef.h"

#define K24C02_USE_SOFT_IIC         ( 0 )                                       // 默认使用软件 IIC 方式驱动 建议使用软件 IIC 方式
#if K24C02_USE_SOFT_IIC                                                         // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 IIC 驱动====================================================
#define K24C02_SOFT_IIC_DELAY       ( 10 )                                      // 软件 IIC 的时钟延时周期 数值越小 IIC 通信速率越快
#define K24C02_SCL_PIN              ( C6 )                                      // 软件 IIC SCL 引脚 连接 K24C02 的 SCL 引脚
#define K24C02_SDA_PIN              ( C7 )                                      // 软件 IIC SDA 引脚 连接 K24C02 的 SDA 引脚
//====================================================软件 IIC 驱动====================================================
#else
//====================================================硬件 IIC 驱动====================================================
#define K24C02_IIC_SPEED            ( 400 * 1000  )                             // 硬件 IIC 通信速率 最高 400KHz 不建议低于 40KHz
#define K24C02_IIC                  ( IIC_1       )                             // 硬件 IIC
#define K24C02_SCL_PIN              ( IIC1_SCL_C6 )                             // 硬件 IIC SCL 引脚 连接 K24C02 的 SCL 引脚
#define K24C02_SDA_PIN              ( IIC1_SDA_C7 )                             // 硬件 IIC SDA 引脚 连接 K24C02 的 SDA 引脚
//====================================================硬件 IIC 驱动====================================================
#endif

#define K24C02_TIMEOUT_COUNT        ( 0x00FF )                                  // K24C02 超时计数

//================================================定义 K24C02 内部地址================================================
#define K24C02_DEV_ADDR             ( 0xA0 >> 1 )                               // IIC写入时的地址字节数据 +1为读取
//================================================定义 K24C02 内部地址================================================

#define K24C02_SIZE                 ( 256 )                                     // 256 byte
#define K24C02_PAGE_SIZE            ( 8 )                                       // 8 byte
#define K24C02_DATA_BUFFER_SIZE     (K24C02_PAGE_SIZE / sizeof(k24c02_data_union))// 自动计算每个页能够存下多少个数据

typedef enum                                                                    // 枚举 K24C02 页索引 此枚举定义不允许用户修改
{
    K24C02_PAGE_0 , K24C02_PAGE_1 , K24C02_PAGE_2 , K24C02_PAGE_3 ,
    K24C02_PAGE_4 , K24C02_PAGE_5 , K24C02_PAGE_6 , K24C02_PAGE_7 ,
    K24C02_PAGE_8 , K24C02_PAGE_9 , K24C02_PAGE_10, K24C02_PAGE_11,
    K24C02_PAGE_12, K24C02_PAGE_13, K24C02_PAGE_14, K24C02_PAGE_15,
    K24C02_PAGE_16, K24C02_PAGE_17, K24C02_PAGE_18, K24C02_PAGE_19,
    K24C02_PAGE_20, K24C02_PAGE_21, K24C02_PAGE_22, K24C02_PAGE_23,
    K24C02_PAGE_24, K24C02_PAGE_25, K24C02_PAGE_26, K24C02_PAGE_27,
    K24C02_PAGE_28, K24C02_PAGE_29, K24C02_PAGE_30, K24C02_PAGE_31,
}k24c02_page_enum;

typedef union                                                                   // 固定的数据缓冲单元格式
{
    float   float_type;                                                         // float  类型
    uint32  uint32_type;                                                        // uint32 类型
    int32   int32_type;                                                         // int32  类型
    uint16  uint16_type;                                                        // uint16 类型
    int16   int16_type;                                                         // int16  类型
    uint8   uint8_type;                                                         // uint8  类型
    int8    int8_type;                                                          // int8   类型
}k24c02_data_union;                                                             // 所有类型数据共用同一个 32bit 地址

extern k24c02_data_union k24c02_union_buffer[K24C02_DATA_BUFFER_SIZE];

void    k24c02_read_page                (k24c02_page_enum page_num, uint8 *buf, uint8 len);
uint8   k24c02_write_page               (k24c02_page_enum page_num, const uint8 *buf, uint8 len);

void    k24c02_read_page_to_buffer      (k24c02_page_enum page_num);
uint8   k24c02_write_page_from_buffer   (k24c02_page_enum page_num);

uint8   k24c02_init                     (void);

#endif

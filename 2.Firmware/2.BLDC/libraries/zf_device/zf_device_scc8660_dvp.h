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
* 文件名称          zf_device_scc8660_dvp
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
*接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   TXD                 查看 zf_device_scc8660.h 中 SCC8660_COF_UART_TX_DVP        宏定义
*                   RXD                 查看 zf_device_scc8660.h 中 SCC8660_COF_UART_RX_DVP        宏定义
*                   D0                  查看 zf_device_scc8660.h 中 SCC8660_D0_PIN_DVP             宏定义
*                   D1                  查看 zf_device_scc8660.h 中 SCC8660_D1_PIN_DVP             宏定义
*                   D2                  查看 zf_device_scc8660.h 中 SCC8660_D2_PIN_DVP             宏定义
*                   D3                  查看 zf_device_scc8660.h 中 SCC8660_D3_PIN_DVP             宏定义
*                   D4                  查看 zf_device_scc8660.h 中 SCC8660_D4_PIN_DVP             宏定义
*                   D5                  查看 zf_device_scc8660.h 中 SCC8660_D5_PIN_DVP             宏定义
*                   D6                  查看 zf_device_scc8660.h 中 SCC8660_D6_PIN_DVP             宏定义
*                   D7                  查看 zf_device_scc8660.h 中 SCC8660_D7_PIN_DVP             宏定义
*                   PCLK                查看 zf_device_scc8660.h 中 SCC8660_PCLK_PIN_DVP           宏定义
*                   VSYNC               查看 zf_device_scc8660.h 中 SCC8660_VSY_PIN_DVP            宏定义
*                   HSYNC               查看 zf_device_scc8660.h 中 SCC8660_HERF_PIN_DVP           宏定义
*                   ------------------------------------
********************************************************************************************************************/


#ifndef _zf_device_scc8660_h_
#define _zf_device_scc8660_h_

#include "zf_common_typedef.h"

//--------------------------------------------------------------------------------------------------
// 引脚配置
//--------------------------------------------------------------------------------------------------
#define SCC8660_COF_UART        UART_5                                          // 配置摄像头所使用到的串口
#define SCC8660_COF_BAUR        9600                                            // 配置摄像头用的串口波特率 禁止修改
#define SCC8660_COF_UART_RX     UART5_MAP0_TX_C12                               // 摄像头的  UART-RX 引脚 要接在单片机 TX 上
#define SCC8660_COF_UART_TX     UART5_MAP0_RX_D2                                // 摄像头的  UART-TX 引脚 要接在单片机 RX 上

#define SCC8660_D0_PIN          (A9 )
#define SCC8660_D1_PIN          (A10)
#define SCC8660_D2_PIN          (C8 )
#define SCC8660_D3_PIN          (C9 )
#define SCC8660_D4_PIN          (C11)
#define SCC8660_D5_PIN          (B6 )
#define SCC8660_D6_PIN          (B8 )
#define SCC8660_D7_PIN          (B9 )

#define SCC8660_PCLK_PIN        (A6 )
#define SCC8660_VSY_PIN         (A5 )
#define SCC8660_HERF_PIN        (A4 )
#define SCC8660_INIT_TIMEOUT    (0x0080)                                        // 默认的摄像头初始化超时时间 毫秒为单位

//--------------------------------------------------------------------------------------------------
// 摄像头默认参数配置 在此修改摄像头配置
//--------------------------------------------------------------------------------------------------
#define SCC8660_W               (160)                                           // 实际图像分辨率宽度 可选参数为：160 180
#define SCC8660_H               (120)                                           // 实际图像分辨率高度 可选参数为：120 160
#define SCC8660_IMAGE_SIZE      (SCC8660_W * 2 * SCC8660_H)                     // 整体图像大小 SCC8660_W*2*SCC8660_H 不能超过 65535

#define SCC8660_AUTO_EXP_DEF    (0  )                                           // 自动曝光     默认不开启自动曝光设置  范围 [0-1] 0为关闭
#define SCC8660_BRIGHT_DEF      (300)                                           // 亮度设置     手动曝光默认：300   手动曝光时：参数范围0-65535   自动曝光推荐值：100 自动曝光时参数设置范围0-255
#define SCC8660_FPS_DEF         (60 )                                           // 图像帧率     默认：60        可选参数为：60 50 30 25。 实际帧率还需要看SCC8660_PCLK_DIV参数的设置
#define SCC8660_PCLK_DIV_DEF    (0  )                                           // PCLK分频系数 默认：0         可选参数为：<0:1/1> <1:2/3> <2:1/2> <3:1/3> <4:1/4> <5:1/8>
                                                                                //              分频系数越大，PCLK频率越低，降低PCLK可以减轻DVP接口的干扰，但降低PCLK频率则会影响帧率。若无特殊需求请保持默认。
                                                                                //              例如设置FPS为50帧，但是pclk分频系数选择的为5，则摄像头输出的帧率为50*（1/8）=6.25帧
                                                                                //              其他参数不变的情况下，SCC8660_PCLK_DIV参数越大图像会越亮
#define SCC8660_PCLK_MODE_DEF   (1  )                                           // PCLK模式     默认：0         可选参数为：[0,1] 0：不输出消隐信号 1：输出消隐信号 <通常都设置为0，如果使用STM32的DCMI接口采集需要设置为1>
#define SCC8660_COLOR_MODE_DEF  (0  )                                           // 图像色彩模式 默认：0         可选参数为：[0,1] 0：正常彩色模式   1：鲜艳模式（色彩饱和度提高）
#define SCC8660_DATA_FORMAT_DEF (0  )                                           // 输出数据格式 默认：0         可选参数为：[0-3] 0：RGB565 1：RGB565(字节交换) 2：YUV422(YUYV) 3：YUV422(UYVY)
#define SCC8660_MANUAL_WB_DEF   (0  )                                           // 手动白平衡   默认：0         可选参数为：[0,0x65-0xa0] 0：关闭手动白平衡，启用自动白平衡    其他：手动白平衡 手动白平衡时 参数范围0x65-0xa0

// 摄像头命令枚举
typedef enum
{
    SCC8660_INIT                = 0x00,                                         // 摄像头初始化命令
    SCC8660_AUTO_EXP,                                                           // 自动曝光命令
    SCC8660_BRIGHT,                                                             // 亮度命令
    SCC8660_FPS,                                                                // 摄像头帧率命令
    SCC8660_SET_COL,                                                            // 图像列命令
    SCC8660_SET_ROW,                                                            // 图像行命令
    SCC8660_PCLK_DIV,                                                           // 像素时钟分频命令
    SCC8660_PCLK_MODE,                                                          // 像素时钟模式命令
    SCC8660_COLOR_MODE,                                                         // 色彩模式命令
    SCC8660_DATA_FORMAT,                                                        // 数据格式命令
    SCC8660_MANUAL_WB,                                                          // 手动白平衡命令
    SCC8660_CONFIG_FINISH,                                                      // 非命令位，主要用来占位计数

    SCC8660_GET_WHO_AM_I        = 0xEF,                                         // 我是谁命令，用于判断摄像头型号
    SCC8660_SET_BRIGHT          = 0xF0,                                         // 单独设置亮度
    SCC8660_GET_STATUS          = 0XF1,                                         // 获取摄像头配置命令
    SCC8660_GET_VERSION         = 0xF2,                                         // 固件版本号
    SCC8660_SET_MANUAL_WB       = 0xF3,                                         // 单独设置手动白平衡

    SCC8660_SET_REG_ADDR        = 0xFE,
    SCC8660_SET_REG_DATA        = 0xFF,
}scc8660_cmd_enum;

extern vuint8       scc8660_finish_flag;                                        // 一场图像采集完成标志位
extern uint16       scc8660_image[SCC8660_H][SCC8660_W];

uint16      scc8660_get_id              (void);
uint16      scc8660_get_parameter       (uint16 config);
uint16      scc8660_get_version         (void);
uint8       scc8660_set_bright          (uint16 data);
uint8       scc8660_set_white_balance   (uint16 data);
uint8       scc8660_set_reg             (uint8 addr, uint16 data);

uint8       scc8660_init                (void);

#endif

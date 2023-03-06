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
* 文件名称          zf_device_mt9v03x
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
*                   TXD                 查看 zf_device_mt9v03x.h 中 MT9V03X_COF_UART_TX 宏定义
*                   RXD                 查看 zf_device_mt9v03x.h 中 MT9V03X_COF_UART_RX 宏定义
*                   PCLK                查看 zf_device_mt9v03x.h 中 MT9V03X_PCLK_PIN 宏定义
*                   VSY                 查看 zf_device_mt9v03x.h 中 MT9V03X_VSYNC_PIN 宏定义
*                   D0-D7               查看 zf_device_mt9v03x.h 中 MT9V03X_DATA_PIN 宏定义 从该定义开始的连续八个引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_mt9v03x_h_
#define _zf_device_mt9v03x_h_

#include "zf_common_typedef.h"

//--------------------------------------------------------------------------------------------------
// 引脚配置
//--------------------------------------------------------------------------------------------------
#define MT9V03X_COF_UART        ( UART_5       )                                // 配置摄像头所使用到的串口
#define MT9V03X_COF_BAUR        ( 9600         )                                // 总钻风配置串口波特率
#define MT9V03X_COF_UART_TX     ( UART5_RX_D2  )                                // 总钻风 UART-TX 引脚 要接在单片机 RX 上
#define MT9V03X_COF_UART_RX     ( UART5_TX_C12 )                                // 总钻风 UART-RX 引脚 要接在单片机 TX 上

#define MT9V03X_COF_IIC_DELAY   ( 150 )                                         // 总钻风 IIC 延时
#define MT9V03X_COF_IIC_SCL     ( D2  )                                         // 总钻风 IIC-SCL 引脚
#define MT9V03X_COF_IIC_SDA     ( C12 )                                         // 总钻风 IIC-SDA 引脚

#define MT9V03X_DMA_CH          ( DMA1_CHANNEL4 )
#define MT9V03X_DMA_IRQN        ( DMA1_CH4_IRQn )

#define MT9V03X_PCLK_PIN        ( TIM1_ETR_E7 )                                 // PCLK 触发信号 TIM_ETR 引脚禁止随意修改

#define MT9V03X_VSYNC_PIN       ( E8           )                                // 场中断引脚
#define MT9V03X_VSYNC_IRQN      ( EXTI9_5_IRQn )                                // 中断号

#define MT9V03X_DATA_PIN        ( G0 )                                          // 数据引脚 这里是 只能是 GPIOx0 或者 GPIOx8 开始 连续八个引脚例如 F0-F7
#define MT9V03X_DATA_ADD        (gpio_idr_addr(MT9V03X_DATA_PIN))

#define MT9V03X_INIT_TIMEOUT    ( 0x0080 )                                      // 默认的摄像头初始化超时时间 毫秒为单位

//--------------------------------------------------------------------------------------------------
// 摄像头默认参数配置 在此修改摄像头配置
//--------------------------------------------------------------------------------------------------
#define MT9V03X_W               ( 188 )                                         // 图像宽度     范围 [1-752]
#define MT9V03X_H               ( 120 )                                         // 图像高度     范围 [1-480]
#define MT9V03X_IMAGE_SIZE      ( MT9V03X_W * MT9V03X_H )                       // 整体图像大小不能超过 65535

#define MT9V03X_AUTO_EXP_DEF    ( 0   )                                         // 自动曝光设置     默认不开启自动曝光设置  范围 [0-63] 0为关闭
                                                                                //                  如果自动曝光开启  EXP_TIME命令设置自动曝光时间的上限
                                                                                //                  一般情况是不需要开启自动曝光设置 如果遇到光线非常不均匀的情况可以尝试设置自动曝光，增加图像稳定性
#define MT9V03X_EXP_TIME_DEF    ( 300 )                                         // 曝光时间         摄像头收到后会自动计算出最大曝光时间，如果设置过大则设置为计算出来的最大曝光值
#define MT9V03X_FPS_DEF         ( 50  )                                         // 图像帧率         摄像头收到后会自动计算出最大FPS，如果过大则设置为计算出来的最大FPS
#define MT9V03X_LR_OFFSET_DEF   ( 0   )                                         // 图像左右偏移量   正值 右偏移   负值 左偏移  列为188 376 752时无法设置偏移
                                                                                //                  摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
#define MT9V03X_UD_OFFSET_DEF   ( 0   )                                         // 图像上下偏移量   正值 上偏移   负值 下偏移  行为120 240 480时无法设置偏移
                                                                                //                  摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
#define MT9V03X_GAIN_DEF        ( 32  )                                         // 图像增益         范围 [16-64]  增益可以在曝光时间固定的情况下改变图像亮暗程度
#define MT9V03X_PCLK_MODE_DEF   ( 0   )                                         // 像素时钟模式     范围 [0-1]    默认：0 可选参数为：[0：不输出消隐信号,1：输出消隐信号]
                                                                                //                  通常都设置为0，如果使用CH32V307的DVP接口或STM32的DCMI接口采集需要设置为1
                                                                                //                  仅总钻风 MT9V034 V1.5 以及以上版本支持该命令

// 摄像头命令枚举
typedef enum
{
    MT9V03X_INIT = 0,                                                           // 摄像头初始化命令
    MT9V03X_AUTO_EXP,                                                           // 自动曝光命令
    MT9V03X_EXP_TIME,                                                           // 曝光时间命令
    MT9V03X_FPS,                                                                // 摄像头帧率命令
    MT9V03X_SET_COL,                                                            // 图像列命令
    MT9V03X_SET_ROW,                                                            // 图像行命令
    MT9V03X_LR_OFFSET,                                                          // 图像左右偏移命令
    MT9V03X_UD_OFFSET,                                                          // 图像上下偏移命令
    MT9V03X_GAIN,                                                               // 图像偏移命令
    MT9V03X_PCLK_MODE,                                                          // 像素时钟模式命令(仅总钻风MT9V034 V1.5以及以上版本支持该命令)
    MT9V03X_CONFIG_FINISH,                                                      // 非命令位，主要用来占位计数

    MT9V03X_COLOR_GET_WHO_AM_I = 0xEF,
    MT9V03X_SET_EXP_TIME = 0XF0,                                                // 单独设置曝光时间命令
    MT9V03X_GET_STATUS,                                                         // 获取摄像头配置命令
    MT9V03X_GET_VERSION,                                                        // 固件版本号命令

    MT9V03X_SET_ADDR = 0XFE,                                                    // 寄存器地址命令
    MT9V03X_SET_DATA                                                            // 寄存器数据命令
}m9v03x_cmd_enum;

// 摄像头接口类型枚举
typedef enum
{
    MT9V03X_UART,
    MT9V03X_SCCB,
}m9v03x_type_enum;

extern vuint8   mt9v03x_finish_flag;                                            // 一场图像采集完成标志位
extern uint8    mt9v03x_image[MT9V03X_H][MT9V03X_W];

uint16      mt9v03x_get_version         (void);
uint8       mt9v03x_set_exposure_time   (uint16 light);
uint8       mt9v03x_set_reg             (uint8 addr, uint16 data);

uint8       mt9v03x_init                (void);

#endif

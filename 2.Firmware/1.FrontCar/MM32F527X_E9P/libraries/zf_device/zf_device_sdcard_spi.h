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
* 文件名称          zf_device_sdcard_spi
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
*                   硬件SPI通信
*                   SPC                 查看 SDCARD_SCK_PIN       宏定义
*                   SDI                 查看 SDCARD_MOSI_PIN  宏定义
*                   SDO                 查看 SDCARD_MISO_PIN  宏定义
*                   CS                  查看 SDCARD_CS_PIN        宏定义
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_sdcard_spi_h_
#define _zf_device_sdcard_spi_h_

#include "zf_common_typedef.h"

//-----------------引脚定义------------------------------
#define SDCARD_USER_SOFT_SPI        (0)
#if SDCARD_USER_SOFT_SPI
#define SDCARD_SCK_PIN      (C12)                                               // 接模块 SPC
#define SDCARD_MOSI_PIN     (D2 )                                               // 接模块 SDI
#define SDCARD_MISO_PIN     (C8 )                                               // 接模块 SDO
#define SDCARD_CS_PIN       (C11)                                               // 接模块 CS
#else
#define SDCARD_SPI          (SPI_3)
#define SDCARD_BAUDRATE     (30000000)
#define SDCARD_SCK_PIN      (SPI3_SCK_C10 )                                     // 接模块 SPC
#define SDCARD_MOSI_PIN     (SPI3_MOSI_C12)                                     // 接模块 SDI
#define SDCARD_MISO_PIN     (SPI3_MOSI_C11)                                     // 接模块 SDO
#define SDCARD_CS_PIN       (A15          )                                     // 接模块 CS
#endif

#define SDCARD_CS(x)        (x? (gpio_high(SDCARD_CS_PIN)): (gpio_low(SDCARD_CS_PIN)))
//-----------------引脚定义------------------------------

// Definitions for MMC/SDC command
#define CMD0                (0x40 + 0)                                          // GO_IDLE_STATE
#define CMD1                (0x40 + 1)                                          // SEND_OP_COND
#define CMD8                (0x40 + 8)                                          // SEND_IF_COND
#define CMD9                (0x40 + 9)                                          // SEND_CSD
#define CMD10               (0x40 + 10)                                         // SEND_CID
#define CMD12               (0x40 + 12)                                         // STOP_TRANSMISSION
#define CMD16               (0x40 + 16)                                         // SET_BLOCKLEN
#define CMD17               (0x40 + 17)                                         // READ_SINGLE_BLOCK
#define CMD18               (0x40 + 18)                                         // READ_MULTIPLE_BLOCK
#define CMD23               (0x40 + 23)                                         // SET_BLOCK_COUNT
#define CMD24               (0x40 + 24)                                         // WRITE_BLOCK
#define CMD25               (0x40 + 25)                                         // WRITE_MULTIPLE_BLOCK
#define CMD41               (0x40 + 41)                                         // SEND_OP_COND (ACMD)
#define CMD55               (0x40 + 55)                                         // APP_CMD
#define CMD58               (0x40 + 58)                                         // READ_OCR

// MMC card type flags (MMC_GET_TYPE)
#define CT_MMC              (0x01)                                              // MMC ver 3
#define CT_SD1              (0x02)                                              // SD ver 1
#define CT_SD2              (0x04)                                              // SD ver 2
#define CT_SDC              (0x06)                                              // SD
#define CT_BLOCK            (0x08)                                              // Block addressing

// Disk Status Bits         (DSTATUS)
#define STA_NOINIT          (0x01)                                              // Drive not initialized
#define STA_NODISK          (0x02)                                              // No medium in the drive
#define STA_PROTECT         (0x04)                                              // Write protected



uint8 sdcard_spi_init (void);

#endif

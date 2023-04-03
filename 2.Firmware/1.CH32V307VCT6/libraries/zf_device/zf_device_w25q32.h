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
* 文件名称          zf_device_w25q32
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
*                   模块管脚                                  单片机管脚
*                   //------------------硬件 SPI 引脚------------------//
*                   SPC                 查看 zf_device_w25q32.h 中 W25Q32_SPC_PIN 宏定义
*                   SDI                 查看 zf_device_w25q32.h 中 W25Q32_SDI_PIN 宏定义
*                   SDO                 查看 zf_device_w25q32.h 中 W25Q32_SDO_PIN 宏定义
*                   CS                  查看 zf_device_w25q32.h 中 W25Q32_CS_PIN 宏定义
*                   //------------------硬件 SPI 引脚------------------//
*                   电源引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_w25q32_h_
#define _zf_device_w25q32_h_

#include "zf_common_clock.h"
#include "zf_common_debug.h"

#include "zf_driver_delay.h"
#include "zf_driver_spi.h"
#include "zf_driver_soft_iic.h"


#define W25Q32_BASE_ADDR             (0x00000000)                   // W25Q32FALSH首地址
#define W25Q32_PAGE_SIZE             (0x00000100)                   // 256 byte
#define W25Q32_SECTION_SIZE          (W25Q32_PAGE_SIZE      *16)    // 4K byte
#define W25Q32_BLOCK_SIZE            (W25Q32_SECTION_SIZE   *16)    // 64K byte

//W25Q32有64个块儿，共64*65536 = 4194304 Byte；4194304/1024/1024 = 4MB,寻址空间：0x000000~0x3FFFFF；

//所有W25QXX系列FLASH相同点
//不同型号的flash有不同数量的块儿，W25Q16有32块儿，W25Q32有64块儿，以此类推；详细见本文“
//3.2、W25QXX系列FLASH芯片不同型号的相同点和区别是啥？”
//1块儿 = 16扇区
//1块儿 = 16 * 16 * 256字节（Byte）= 65536Byte = 64KB（65536Byte/1024=64KB）
//1扇区 = 16页
//1扇区 = 16 * 256（Byte）= 4096Byte = 4KB
//1页 = 256字节


// 枚举 Flash 块区  此枚举定义不允许用户修改
typedef enum
{
    W25Q32_BLOCK_00,
    W25Q32_BLOCK_01,
    W25Q32_BLOCK_02,
    W25Q32_BLOCK_03,
    W25Q32_BLOCK_04,
    W25Q32_BLOCK_05,
    W25Q32_BLOCK_06,
    W25Q32_BLOCK_07,
    W25Q32_BLOCK_08,
    W25Q32_BLOCK_09,
    W25Q32_BLOCK_10,
    W25Q32_BLOCK_11,
    W25Q32_BLOCK_12,
    W25Q32_BLOCK_13,
    W25Q32_BLOCK_14,
    W25Q32_BLOCK_15,
    W25Q32_BLOCK_16,
    W25Q32_BLOCK_17,
    W25Q32_BLOCK_18,
    W25Q32_BLOCK_19,
    W25Q32_BLOCK_20,
    W25Q32_BLOCK_21,
    W25Q32_BLOCK_22,
    W25Q32_BLOCK_23,
    W25Q32_BLOCK_24,
    W25Q32_BLOCK_25,
    W25Q32_BLOCK_26,
    W25Q32_BLOCK_27,
    W25Q32_BLOCK_28,
    W25Q32_BLOCK_29,
    W25Q32_BLOCK_30,
    W25Q32_BLOCK_31,
    W25Q32_BLOCK_32,
    W25Q32_BLOCK_33,
    W25Q32_BLOCK_34,
    W25Q32_BLOCK_35,
    W25Q32_BLOCK_36,
    W25Q32_BLOCK_37,
    W25Q32_BLOCK_38,
    W25Q32_BLOCK_39,
    W25Q32_BLOCK_40,
    W25Q32_BLOCK_41,
    W25Q32_BLOCK_42,
    W25Q32_BLOCK_43,
    W25Q32_BLOCK_44,
    W25Q32_BLOCK_45,
    W25Q32_BLOCK_46,
    W25Q32_BLOCK_47,
    W25Q32_BLOCK_48,
    W25Q32_BLOCK_49,
    W25Q32_BLOCK_50,
    W25Q32_BLOCK_51,
    W25Q32_BLOCK_52,
    W25Q32_BLOCK_53,
    W25Q32_BLOCK_54,
    W25Q32_BLOCK_55,
    W25Q32_BLOCK_56,
    W25Q32_BLOCK_57,
    W25Q32_BLOCK_58,
    W25Q32_BLOCK_59,
    W25Q32_BLOCK_60,
    W25Q32_BLOCK_61,
    W25Q32_BLOCK_62,
    W25Q32_BLOCK_63
}w25q32_block_enum;

// 枚举 Flash 扇区  此枚举定义不允许用户修改
typedef enum
{
    W25Q32_SECTION_00,
    W25Q32_SECTION_01,
    W25Q32_SECTION_02,
    W25Q32_SECTION_03,
    W25Q32_SECTION_04,
    W25Q32_SECTION_05,
    W25Q32_SECTION_06,
    W25Q32_SECTION_07,
    W25Q32_SECTION_08,
    W25Q32_SECTION_09,
    W25Q32_SECTION_10,
    W25Q32_SECTION_11,
    W25Q32_SECTION_12,
    W25Q32_SECTION_13,
    W25Q32_SECTION_14,
    W25Q32_SECTION_15,
}w25q32_section_enum;

// 枚举 Flash 页索引 此枚举定义不允许用户修改
typedef enum
{
    W25Q32_PAGE_00,
    W25Q32_PAGE_01,
    W25Q32_PAGE_02,
    W25Q32_PAGE_03,
    W25Q32_PAGE_04,
    W25Q32_PAGE_05,
    W25Q32_PAGE_06,
    W25Q32_PAGE_07,
    W25Q32_PAGE_08,
    W25Q32_PAGE_09,
    W25Q32_PAGE_10,
    W25Q32_PAGE_11,
    W25Q32_PAGE_12,
    W25Q32_PAGE_13,
    W25Q32_PAGE_14,
    W25Q32_PAGE_15,
}w25q32_page_enum;

//====================================================硬件 SPI 驱动====================================================
#define W25Q32_SPI_SPEED          system_clock/8                              // 硬件 SPI 速率
#define W25Q32_SPI                SPI_3                                       // 硬件 SPI 号
#define W25Q32_SPC_PIN            SPI1_MAP1_SCK_B3                                 // 硬件 SPI SCK 引脚
#define W25Q32_SDI_PIN            SPI1_MAP1_MISO_B4                                // 硬件 SPI MOSI 引脚
#define W25Q32_SDO_PIN            SPI1_MAP1_MOSI_B5                                // 硬件 SPI MISO 引脚
//====================================================硬件 SPI 驱动====================================================
#define W25Q32_CS_PIN             A15                                         // CS 片选引脚
#define W25Q32_CS(x)              (x? (gpio_high(W25Q32_CS_PIN)): (gpio_low(W25Q32_CS_PIN)))

#define W25Q32_TIMEOUT_COUNT      0x00FF

//================================================定义 ICM20602 内部地址================================================
#define W25Q32_WRITE_ENABLE             0x06
#define W25Q32_WRITE_DISABLE            0x04

#define W25Q32_READ_STATUS_REG_1        0x05
#define W25Q32_READ_STATUS_REG_2        0x35
#define W25Q32_READ_STATUS_REG_3        0x15
#define W25Q32_WRITE_STATUS_REG_1       0x01
#define W25Q32_WRITE_STATUS_REG_2       0x31
#define W25Q32_WRITE_STATUS_REG_3       0x11
#define W25Q32_PAGE_PROGRAM             0x02
#define W25Q32_READ_DATA                0x03
#define W25Q32_FAST_READ                0x0B
#define W25Q32_SECTOR_ERASE             0x20
#define W25Q32_32KB_BLOCK_ERASE         0x52
#define W25Q32_64KB_BLOCK_ERASE         0xD8
#define W25Q32_CHIP_ERASE               0xC7
#define W25Q32_SUSPEND                  0x75
#define W25Q32_RESUME                   0x7A
#define W25Q32_READ_UID                 0x4B
#define W25Q32_JEDEC_ID                 0x9F    // W25Q32 返回0xEF40
#define W25Q32_DEVICE_ID                0x90    // W25Q32 返回0xEF15
#define W25Q32_RESET_ENABLE             0x66
#define W25Q32_RESET_DEVICE             0x99
//================================================定义 ICM20602 内部地址================================================


void  w25q32_erase_chip(void);
uint8 w25q32_check          (w25q32_block_enum block_num, w25q32_section_enum sector_num, w25q32_page_enum page_num);
uint8 w25q32_erase_sector   (w25q32_block_enum block_num, w25q32_section_enum sector_num);

void  w25q32_read_page      (w25q32_block_enum block_num, w25q32_section_enum sector_num, w25q32_page_enum page_num,
        uint8 *buf, uint16 len);

void  w25q32_write_page     (w25q32_block_enum block_num, w25q32_section_enum sector_num, w25q32_page_enum page_num,
        uint8 *buf, uint16 len);
uint8 w25q32_init();

//SPI_FLASH写使能

#endif

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
* 文件名称          zf_driver_spi
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

#ifndef _zf_driver_spi_h
#define _zf_driver_spi_h

#include "ch32v30x_spi.h"
#include "ch32v30x_rcc.h"
#include "ch32v30x_gpio.h"

#include "zf_common_debug.h"
#include "zf_common_clock.h"

#include "zf_driver_gpio.h"

#define SPI_SPEED_PRIORITY                                                      // SPI 通信速度优先

// 此枚举定义不允许用户修改
typedef enum // 枚举串口号
{
    SPI_1 = 0x00,
    SPI_2 = 0x01,
    SPI_3 = 0x02
}spi_index_enum;

// 此枚举定义不允许用户修改
typedef enum // 枚举串口号
{
    //----------SPI1----------
    // 以下为SPI1的一组映射引脚，不允许映射引脚混用。
    // 例如：SPI1_MAP0_MAP_SCK_A5与SPI1_MAP1_MAP_MISO_B4不能一起使用。
    // 只允许SPI1_MAP0_MAP_SCK_A5 和  SPI1_MAP0_MAP_MISO_A6和 SPI1_MAP0_MAP_MOSI_A7 同组映射引脚一起使用
    // 默认映射
    SPI1_MAP0_SCK_A5   = 0x0000 | A5,
    SPI1_MAP0_MISO_A6  = 0x0000 | A6,
    SPI1_MAP0_MOSI_A7  = 0x0000 | A7,

    // 以下为SPI1的一组映射引脚，不允许映射引脚混用。
    // 重映射          
    SPI1_MAP1_SCK_B3   = 0x0100 | B3,
    SPI1_MAP1_MISO_B4  = 0x0100 | B4,
    SPI1_MAP1_MOSI_B5  = 0x0100 | B5,
					   
    //----------SPI2-- --------

    // 以下为SPI2的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    SPI2_MAP0_SCK_B13  = 0x1000 | B13,
    SPI2_MAP0_MISO_B14 = 0x1000 | B14,
    SPI2_MAP0_MOSI_B15 = 0x1000 | B15,
					   
    //----------SPI3-- --------

    // 以下为SPI3的一组映射引脚，不允许映射引脚混用。
    // 默认映射
    SPI3_MAP0_SCK_B3   = 0x2000 | B3,
    SPI3_MAP0_MISO_B4  = 0x2000 | B4,
    SPI3_MAP0_MOSI_B5  = 0x2000 | B5,

    // 以下为SPI3的一组映射引脚，不允许映射引脚混用。
    // 重映射          
    SPI3_MAP1_SCK_C10  = 0x2100 | C10,
    SPI3_MAP1_MISO_C11 = 0x2100 | C11,
    SPI3_MAP1_MOSI_C12 = 0x2100 | C12,

    // 不需要MISO引脚就用此定义
    SPI_MISO_NULL = 0xFFFE,

    // 不需要CS引脚就用此定义
    SPI_CS_NULL = 0xFF,
}spi_pin_enum;


typedef enum                                                                    // 枚举 SPI 模式 此枚举定义不允许用户修改
{
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3,
}spi_mode_enum;



void        spi_write_8bit                  (spi_index_enum spi_n, const uint8 data);
void        spi_write_8bit_array            (spi_index_enum spi_n, const uint8 *data, uint32 len);

void        spi_write_16bit                 (spi_index_enum spi_n, const uint16 data);
void        spi_write_16bit_array           (spi_index_enum spi_n, const uint16 *data, uint32 len);

void        spi_write_8bit_register         (spi_index_enum spi_n, const uint8 register_name, const uint8 data);
void        spi_write_8bit_registers        (spi_index_enum spi_n, const uint8 register_name, const uint8 *data, uint32 len);

void        spi_write_16bit_register        (spi_index_enum spi_n, const uint16 register_name, const uint16 data);
void        spi_write_16bit_registers       (spi_index_enum spi_n, const uint16 register_name, const uint16 *data, uint32 len);

uint8       spi_read_8bit                   (spi_index_enum spi_n);
void        spi_read_8bit_array             (spi_index_enum spi_n, uint8 *data, uint32 len);

uint16      spi_read_16bit                  (spi_index_enum spi_n);
void        spi_read_16bit_array            (spi_index_enum spi_n, uint16 *data, uint32 len);

uint8       spi_read_8bit_register          (spi_index_enum spi_n, const uint8 register_name);
void        spi_read_8bit_registers         (spi_index_enum spi_n, const uint8 register_name, uint8 *data, uint32 len);

uint16      spi_read_16bit_register         (spi_index_enum spi_n, const uint16 register_name);
void        spi_read_16bit_registers        (spi_index_enum spi_n, const uint16 register_name, uint16 *data, uint32 len);

void        spi_transfer_8bit               (spi_index_enum spi_n, const uint8 *write_buffer, uint8 *read_buffer, uint32 len);
void        spi_transfer_16bit              (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 len);

void        spi_init                        (spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_pin_enum sck_pin, spi_pin_enum mosi_pin, spi_pin_enum miso_pin, gpio_pin_enum cs_pin);

#endif

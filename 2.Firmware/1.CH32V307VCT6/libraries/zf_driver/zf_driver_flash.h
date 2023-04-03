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
* 文件名称          zf_driver_delay
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

#ifndef _zf_driver_flash_h
#define _zf_driver_flash_h

#include "ch32v30x.h"
#include "ch32v30x_flash.h"
#include "zf_common_typedef.h"

#define FLASH_BASE_ADDR             (0x08000000)                // FALSH首地址
#define FLASH_MAX_PAGE_INDEX        (3)
#define FLASH_MAX_SECTION_INDEX     (63)
#define FLASH_PAGE_SIZE             (0x00000400)                // 1K byte
#define FLASH_SECTION_SIZE          (FLASH_PAGE_SIZE*4)         // 4K byte
#define FLASH_OPERATION_TIME_OUT    0x0FFF

#define FLASH_DATA_BUFFER_SIZE      (FLASH_PAGE_SIZE/sizeof(flash_data_union))  // 自动计算每个页能够存下多少个数据

typedef union                                                                   // 固定的数据缓冲单元格式
{
    float   float_type;                                                       // float  类型
    uint32  uint32_type;                                                      // uint32 类型
    int32   int32_type;                                                       // int32  类型
    uint16  uint16_type;                                                      // uint16 类型
    int16   int16_type;                                                       // int16  类型
    uint8   uint8_type;                                                       // uint8  类型
    int8    int8_type;                                                        // int8   类型
}flash_data_union;                                                              // 所有类型数据共用同一个 32bit 地址


/*
     本开源库使用的是64K RAM+ 256KFLASH
  flash部分 一共64个扇区，一个扇区4K。
*/


extern flash_data_union flash_union_buffer[FLASH_DATA_BUFFER_SIZE];

uint8   flash_check                         (uint32 sector_num, uint32 page_num);
uint8   flash_erase_sector                  (uint32 sector_num, uint32 page_num);
void    flash_read_page                     (uint32 sector_num, uint32 page_num, uint32 *buf, uint16 len);
uint8   flash_write_page                    (uint32 sector_num, uint32 page_num, const uint32 *buf, uint16 len);

void    flash_read_page_to_buffer           (uint32 sector_num, uint32 page_num);
uint8   flash_write_page_from_buffer        (uint32 sector_num, uint32 page_num);
void    flash_buffer_clear                  (void);

#endif

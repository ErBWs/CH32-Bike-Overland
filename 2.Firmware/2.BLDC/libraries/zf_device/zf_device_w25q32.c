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
*                   模块管脚                                        单片机管脚
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

#include "zf_device_w25q32.h"


static uint8 w25q32_read_dat()
{
    //    W25Q32_CS(0);
    uint8 dat = spi_read_8bit(W25Q32_SPI);
    //    W25Q32_CS(1);
    return dat;
}

static void w25q32_read_dats(uint8 *dat, uint32 len)
{
    //    W25Q32_CS(0);
    spi_read_8bit_array(W25Q32_SPI, dat, len);
    //    W25Q32_CS(1);
}

static void w25q32_write_dat(uint8 dat)
{
    //    W25Q32_CS(0);
    spi_write_8bit(W25Q32_SPI, dat);
    //    W25Q32_CS(1);
}


static void w25q32_write_dats(uint8 *dat, uint32 len)
{
    //    W25Q32_CS(0);
    spi_write_8bit_array(W25Q32_SPI, dat, len);
    //    W25Q32_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      写使能 内部调用
// 参数说明     void
// 返回参数     void
//-------------------------------------------------------------------------------------------------------------------
static void w25q32_write_enable(void)
{
    W25Q32_CS(0);
    w25q32_write_dat(W25Q32_WRITE_ENABLE);   //发送写使能
    W25Q32_CS(1);
}

////-------------------------------------------------------------------------------------------------------------------
//// @brief       写失能 内部调用
//// @param       void
//// @return      void
////-------------------------------------------------------------------------------------------------------------------
//static void w25q32_write_disable(void)
//{
//    W25Q32_CS(0);
//    w25q32_write_dat(W25Q32_WRITE_DISABLE);  //发送写禁止指令
//    W25Q32_CS(1);
//}



//-------------------------------------------------------------------------------------------------------------------
// 函数简介      读取状态 内部调用
// 参数说明     void
// 返回参数     uint8   寄存器状态值
//              BIT7  6   5   4   3   2   1   0
//              SPR   RV  TB BP2 BP1 BP0 WEL BUSY
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
static uint8 w25q32_read_state(void)
{
    uint8 byte=0;
    W25Q32_CS(0);
    //发送读取状态寄存器命令
    //读取一个字节
    w25q32_write_dat(W25Q32_READ_STATUS_REG_1);  // 发送读取命令
    byte = w25q32_read_dat();                    // 读取一个字节
    W25Q32_CS(1);
    return byte;
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介      等待不忙 内部调用
// 参数说明     void
// 返回参数     void
//-------------------------------------------------------------------------------------------------------------------
static void w25q32_wait_busy(void)
{
    while ((w25q32_read_state()&0x01)==0x01);   // 等待BUSY复位
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介      读芯片id 内部调用
// 参数说明     void
// 返回参数     uint16   ID值
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
static uint16 w25q32_read_device_id(void)
{
    uint8 send_dat[4] = {W25Q32_DEVICE_ID, 0x00, 0x00, 0x00};
    uint8 read_dat[2] = {0};
    W25Q32_CS(0);
    w25q32_write_dats(send_dat, 4);
    w25q32_read_dats(read_dat, 2);
    W25Q32_CS(1);

    return read_dat[0] << 8 | read_dat[1];
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      擦除W25Q32所有区域(需要等待20秒)
// 参数说明     void
// 返回参数     void
//-------------------------------------------------------------------------------------------------------------------
void w25q32_erase_chip(void)
{
    w25q32_wait_busy();
    W25Q32_CS(0);                               //使能器件
    w25q32_write_dat(W25Q32_CHIP_ERASE);        //发送片擦除命令
    W25Q32_CS(1);                               //取消片选
    w25q32_wait_busy();                         //等待芯片擦除结束
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取一个字节 内部调用
// 参数说明     uint32        读取地址24bit
// 返回参数     uint8           读取到的值
//  @since      v1.0
// 使用示例     w25q32_read_byte(0x000001);
//-------------------------------------------------------------------------------------------------------------------
static uint8 w25q32_read_byte(uint32 addr)
{
    uint8 temp;
    W25Q32_CS(0);

    w25q32_write_dat(W25Q32_READ_DATA);       // 发送读取命令
    w25q32_write_dat((uint8)((addr)>>16));    // 发送24bit地址
    w25q32_write_dat((uint8)((addr)>>8));
    w25q32_write_dat((uint8)addr);
    temp = w25q32_read_dat();                 // 读取一个字节

    W25Q32_CS(1);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     校验w25q32是否有数据
// 参数说明     block_num       需要写入的扇区编号   参数范围 W25Q32_BLOCK_00   - W25Q32_BLOCK_63
// 参数说明     sector_num      需要写入的扇区编号   参数范围 W25Q32_SECTION_00 - W25Q32_SECTION_15
// 参数说明     page_num        当前扇区页的编号       参数范围 W25Q32_PAGE_00    - W25Q32_PAGE_15
// 返回参数     返回1有数据，返回0没有数据，如果需要对有数据的区域写入新的数据则应该对所在扇区进行擦除操作
//  @since      v1.0
// 使用示例     w25q32_check(W25Q32_BLOCK_63, W25Q32_SECTION_15, W25Q32_PAGE_00);
//-------------------------------------------------------------------------------------------------------------------
uint8 w25q32_check (w25q32_block_enum block_num, w25q32_section_enum sector_num, w25q32_page_enum page_num)
{
    uint16 temp_loop;
    uint32 addr = (W25Q32_BASE_ADDR         +
            W25Q32_BLOCK_SIZE*block_num     +
            W25Q32_SECTION_SIZE*sector_num  +
            W25Q32_PAGE_SIZE*page_num);     // 提取当前地址

    for(temp_loop = 0; temp_loop < W25Q32_PAGE_SIZE; temp_loop++)       // 循环读取 Flash 的值
    {
        if( w25q32_read_byte(addr + temp_loop) != 0xff )                // 如果不是 0xff 那就是有值
            return 1;
    }
    return 0;
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     擦除一个扇区
// 参数说明     block_num       需要写入的扇区编号   参数范围 W25Q32_BLOCK_00   - W25Q32_BLOCK_63
// 参数说明     sector_num      需要写入的扇区编号   参数范围 W25Q32_SECTION_00 - W25Q32_SECTION_15
// 返回参数     
//  @since      v1.0
// 使用示例     w25q32_erase_sector(W25Q32_BLOCK_63, W25Q32_SECTION_15);
//-------------------------------------------------------------------------------------------------------------------
uint8 w25q32_erase_sector(w25q32_block_enum block_num, w25q32_section_enum sector_num)
{
    uint32 addr = (W25Q32_BASE_ADDR  +
            W25Q32_BLOCK_SIZE*block_num    +
            W25Q32_SECTION_SIZE*sector_num +
            W25Q32_PAGE_SIZE*0);                    // 提取当前地址

    W25Q32_CS(0);

    w25q32_write_dat(W25Q32_SECTOR_ERASE);          // 发送擦除扇区命令
    w25q32_write_dat((uint8)((addr)>>16));          // 发送24bit地址
    w25q32_write_dat((uint8)((addr)>>8));
    w25q32_write_dat((uint8)addr);

    W25Q32_CS(1);
    w25q32_wait_busy();                             // 等待擦除完成
    return 0;
}




//-------------------------------------------------------------------------------------------------------------------
// 函数简介     从该地址开始读取数据 内部使用
// 参数说明     addr            开始读取的地址24bit
// 参数说明     buff            数据存储区
// 参数说明     len             要读取的长度(最大65535)
// 返回参数     
//  @since      v1.0
// 使用示例     w25q32_erase_sector(0x000001, buf, 16);
//-------------------------------------------------------------------------------------------------------------------
static void w25q32_read_addr_dats(uint32 addr, uint8 *buff, uint16 len)
{
    W25Q32_CS(0);
    w25q32_write_dat(W25Q32_FAST_READ);             // 发送读取命令
    w25q32_write_dat((uint8)((addr)>>16));          // 发送24bit地址
    w25q32_write_dat((uint8)((addr)>>8));
    w25q32_write_dat((uint8)addr);
    w25q32_read_dat();                              // 快速读取要求第一个字节为空字节。
    w25q32_read_dats(buff, len);

    W25Q32_CS(1);//取消片选
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     从该地址开始写入数据 内部使用
// 参数说明     addr            开始写入的地址24bit
// 参数说明     buff            数据存储区
// 参数说明     len             要写入的长度(最大256,且len不能超过该页剩余的字节数)
// 返回参数     
//  @since      v1.0
// 使用示例     w25q32_write_addr_dats(0x000001, buf, 16);
//-------------------------------------------------------------------------------------------------------------------
static void w25q32_write_addr_dats(uint32 addr, uint8 *buff, uint16 len)
{

    W25Q32_CS(0);

    w25q32_write_dat(W25Q32_PAGE_PROGRAM);          // 发送写页命令
    w25q32_write_dat((uint8)((addr)>>16));          // 发送24bit地址
    w25q32_write_dat((uint8)((addr)>>8));
    w25q32_write_dat((uint8)addr);
    w25q32_write_dats(buff, len);
    W25Q32_CS(1);
    w25q32_wait_busy();                             // 等待写入结束
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取一页
// 参数说明     block_num       需要读取的扇区编号   参数范围 W25Q32_BLOCK_00   - W25Q32_BLOCK_63
// 参数说明     sector_num      需要读取的扇区编号   参数范围 W25Q32_SECTION_00 - W25Q32_SECTION_15
// 参数说明     page_num        需要读取的页编号       参数范围 W25Q32_PAGE_00    - W25Q32_PAGE_15
// 参数说明     buf             需要读取的数据地址   传入的数组类型必须为uint8 *
// 参数说明     len             需要读取的数据长度   参数范围 1-256
// 返回参数     NULL
//  @since      v1.0
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void w25q32_read_page(w25q32_block_enum block_num, w25q32_section_enum sector_num, w25q32_page_enum page_num,
        uint8 *buf, uint16 len)
{
    uint32  addr = (W25Q32_BASE_ADDR  +
            W25Q32_BLOCK_SIZE*block_num    +
            W25Q32_SECTION_SIZE*sector_num +
            W25Q32_PAGE_SIZE*page_num);     // 提取当前 Flash 地址

    w25q32_read_addr_dats(addr, buf, len);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     写入一页
// 参数说明     block_num       需要读取的扇区编号   参数范围 W25Q32_BLOCK_00   - W25Q32_BLOCK_63
// 参数说明     sector_num      需要读取的扇区编号   参数范围 W25Q32_SECTION_00 - W25Q32_SECTION_15
// 参数说明     page_num        需要读取的页编号       参数范围 W25Q32_PAGE_00    - W25Q32_PAGE_15
// 参数说明     buf             需要读取的数据地址   传入的数组类型必须为uint8 *
// 参数说明     len             需要读取的数据长度   参数范围 1-256
// 返回参数     NULL
//  @since      v1.0
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void w25q32_write_page(w25q32_block_enum block_num, w25q32_section_enum sector_num, w25q32_page_enum page_num,
        uint8 *buf, uint16 len)
{
    uint32 flash_addr = (W25Q32_BASE_ADDR  +
            W25Q32_BLOCK_SIZE*block_num    +
            W25Q32_SECTION_SIZE*sector_num +
            W25Q32_PAGE_SIZE*page_num);     // 提取当前 Flash 地址

    w25q32_write_addr_dats(flash_addr, buf, len);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介      自检 内部调用
// 参数说明     void
// 返回参数     void
//-------------------------------------------------------------------------------------------------------------------
static uint8 w25q32_self_check(void)
{
    uint8 ret = 0;
    uint16 dat = 0;
    volatile int16 timeout_count = W25Q32_TIMEOUT_COUNT;

///* Winbond SPIFalsh ID */
//#define W25Q80                   0XEF13
//#define W25Q16                   0XEF14
//#define W25Q32                   0XEF15
//#define W25Q64                   0XEF16
//#define W25Q128                  0XEF17

    while(((dat & 0xEF10) != 0xEF10) && timeout_count)                                         // 判断 ID 是否正确
    {
       timeout_count--;

       dat = w25q32_read_device_id();

       system_delay_ms(1);
    }

    if(timeout_count < 0)
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介      初始化 W25Q32
// 参数说明     void
// 返回参数     uint8         1-初始化失败 0-初始化成功
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 w25q32_init(void)
{
    spi_init(W25Q32_SPI, SPI_MODE0, W25Q32_SPI_SPEED, W25Q32_SPC_PIN, W25Q32_SDI_PIN, W25Q32_SDO_PIN, W25Q32_CS_PIN);

    if( w25q32_self_check() )
    {
        zf_log(0, "W25Q32 self check error.");
        return 1;
    }

    w25q32_write_enable();                    // 写使能
    return 0;
}

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
* 文件名称          zf_device_ips350
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
*                   RD                  查看 zf_device_ips350.h 中 IPS350_RD_PIN_PARALLEL8     宏定义
*                   WR                  查看 zf_device_ips350.h 中 IPS350_WR_PIN_PARALLEL8     宏定义
*                   RS                  查看 zf_device_ips350.h 中 IPS350_RS_PIN_PARALLEL8     宏定义
*                   RST                 查看 zf_device_ips350.h 中 IPS350_RST_PIN_PARALLEL8    宏定义
*                   CS                  查看 zf_device_ips350.h 中 IPS350_CS_PIN_PARALLEL8     宏定义
*                   BL                  查看 zf_device_ips350.h 中 IPS350_BL_PIN_PARALLEL8     宏定义
*                   D0-D7               查看 zf_device_ips350.h 中 IPS350_Dx_PIN_PARALLEL8     宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   最大分辨率 320 * 240
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_ips350_h_
#define _zf_device_ips350_h_

#include "zf_common_typedef.h"

// 如果使用的是双排排针的两寸屏幕 并口驱动控制引脚 可以修改
#define IPS350_RST_PIN_PARALLEL8        ( G11 )
#define IPS350_BL_PIN_PARALLEL8         ( E3  )

// 如果使用的是双排排针的两寸屏幕 并口驱动控制引脚 FSMC固定引脚 不可更改
#define IPS350_RD_PIN_PARALLEL8         ( D4  )
#define IPS350_WR_PIN_PARALLEL8         ( D5  )
#define IPS350_RS_PIN_PARALLEL8         ( E2  ) 
#define IPS350_CS_PIN_PARALLEL8         ( G12 )

// 如果使用的是双排排针的两寸屏幕 并口驱动数据引脚 FSMC固定引脚 不可更改
#define IPS350_D0_PIN_PARALLEL8         ( D14 )
#define IPS350_D1_PIN_PARALLEL8         ( D15 )
#define IPS350_D2_PIN_PARALLEL8         ( D0  )
#define IPS350_D3_PIN_PARALLEL8         ( D1  )
#define IPS350_D4_PIN_PARALLEL8         ( E7  )
#define IPS350_D5_PIN_PARALLEL8         ( E8  )
#define IPS350_D6_PIN_PARALLEL8         ( E9  )
#define IPS350_D7_PIN_PARALLEL8         ( E10 )
#define IPS350_D8_PIN_PARALLEL8         ( E11 )
#define IPS350_D9_PIN_PARALLEL8         ( E12 )
#define IPS350_D10_PIN_PARALLEL8        ( E13 )
#define IPS350_D11_PIN_PARALLEL8        ( E14 )
#define IPS350_D12_PIN_PARALLEL8        ( E15 )
#define IPS350_D13_PIN_PARALLEL8        ( D8  )
#define IPS350_D14_PIN_PARALLEL8        ( D9  )
#define IPS350_D15_PIN_PARALLEL8        ( D10 )

#define IPS350_DEFAULT_DISPLAY_DIR      ( IPS350_PORTAIT   )                    // 默认的显示方向
#define IPS350_DEFAULT_PENCOLOR         ( RGB565_RED       )                    // 默认的画笔颜色
#define IPS350_DEFAULT_BGCOLOR          ( RGB565_WHITE     )                    // 默认的背景颜色
#define IPS350_DEFAULT_DISPLAY_FONT     ( IPS350_8X16_FONT )                    // 默认的字体模式

// 数据对应地址 不可更改
#define IPS350_DATA_ADD                 ( 0x6D000000 )
#define IPS350_CMD_ADD                  ( 0x6C000000 )

// 控制语句
#define IPS350_RD(x)        ((x) ? (gpio_high(IPS350_RD_PIN_PARALLEL8)) : (gpio_low(IPS350_RD_PIN_PARALLEL8)))
#define IPS350_WR(x)        ((x) ? (gpio_high(IPS350_WR_PIN_PARALLEL8)) : (gpio_low(IPS350_WR_PIN_PARALLEL8)))
#define IPS350_RST(x)       ((x) ? (gpio_high(IPS350_RST_PIN_PARALLEL8)) : (gpio_low(IPS350_RST_PIN_PARALLEL8)))
#define IPS350_BL(x)        ((x) ? (gpio_high(IPS350_BL_PIN_PARALLEL8)) : (gpio_low(IPS350_BL_PIN_PARALLEL8)))

typedef enum
{
    IPS350_PORTAIT                      = 0,                                    // 竖屏模式
    IPS350_PORTAIT_180                  = 1,                                    // 竖屏模式  旋转180
    IPS350_CROSSWISE                    = 2,                                    // 横屏模式
    IPS350_CROSSWISE_180                = 3,                                    // 横屏模式  旋转180
}ips350_dir_enum;

typedef enum
{
    IPS350_6X8_FONT                     = 0,                                    // 6x8      字体
    IPS350_8X16_FONT                    = 1,                                    // 8x16     字体
    IPS350_16X16_FONT                   = 2,                                    // 16x16    字体 目前不支持
}ips350_font_size_enum;

void    ips350_clear                    (void);
void    ips350_full                     (const uint16 color);
void    ips350_set_dir                  (ips350_dir_enum dir);
void    ips350_set_font                 (ips350_font_size_enum font);
void    ips350_set_color                (const uint16 pen, const uint16 bgcolor);
void    ips350_draw_point               (uint16 x, uint16 y, const uint16 color);
void    ips350_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);

void    ips350_show_char                (uint16 x, uint16 y, const char dat);
void    ips350_show_string              (uint16 x, uint16 y, const char dat[]);
void    ips350_show_int                 (uint16 x, uint16 y, const int32 dat, uint8 num);
void    ips350_show_uint                (uint16 x, uint16 y, const uint32 dat, uint8 num);
void    ips350_show_float               (uint16 x, uint16 y, const float dat, uint8 num, uint8 pointnum);

void    ips350_show_binary_image        (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void    ips350_show_gray_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);
void    ips350_show_rgb565_image        (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode);

void    ips350_show_wave                (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);
void    ips350_show_chinese             (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color);

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示小钻风图像
// 参数说明     p               图像数组
// 参数说明     width           显示宽度
// 参数说明     height          显示高度
// 返回参数     void
// 使用示例     ips350_displayimage7725(ov7725_image_binary[0], 80, 60);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
#define ips350_displayimage7725(p, width, height)       (ips350_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, (width), (height)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示总钻风图像 不带二值化 显示灰度图像
// 参数说明     p               图像数组
// 参数说明     width           显示宽度
// 参数说明     height          显示高度
// 返回参数     void
// 使用示例     ips350_displayimage03x(mt9v03x_image[0], 94, 60);
// 备注信息     如果要显示二值化图像就去调用 ips350_show_gray_image 函数
//-------------------------------------------------------------------------------------------------------------------
#define ips350_displayimage03x(p, width, height)        (ips350_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, (width), (height), 0))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS350 显示凌瞳图像
// 参数说明     p               图像数组
// 参数说明     width           显示宽度
// 参数说明     height          显示高度
// 返回参数     void
// 使用示例     ips350_displayimage8660(scc8660_image[0], 80, 60);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
#define ips350_displayimage8660(p, width, height)       (ips350_show_rgb565_image(0, 0, (p), SCC8660_W, SCC8660_H, (width), (height), 1))

void    ips350_init                     (void);

#endif

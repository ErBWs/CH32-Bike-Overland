/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef IPS096_H
#define IPS096_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "zf_driver_gpio.h"
#include "zf_driver_spi.h"
#include "zf_common_font.h"
#include "zf_driver_delay.h"
#include "zf_common_function.h"

#define IPS096_SPI_SPEED                (72 * 1000 * 1000)                      // 这里设置为系统时钟二分频
#define IPS096_SPI                      (SPI_2)
#define IPS096_SCL_PIN                  (SPI2_MAP0_SCK_B13)
#define IPS096_SDA_PIN                  (SPI2_MAP0_MOSI_B15)
#define IPS096_RST_PIN                  (B7 )
#define IPS096_DC_PIN                   (D7 )
#define IPS096_CS_PIN                   (D4 )
#define IPS096_BLK_PIN                  (D0 )

#define IPS096_DEFAULT_DISPLAY_DIR      (IPS096_CROSSWISE_180)                  // 默认的显示方向
#define IPS096_DEFAULT_PENCOLOR         (RGB565_RED)                            // 默认的画笔颜色
#define IPS096_DEFAULT_BGCOLOR          (RGB565_WHITE)                          // 默认的背景颜色
#define IPS096_DEFAULT_DISPLAY_FONT     (IPS096_8X16_FONT)                      // 默认的字体模式

#define IPS096_DC(x)                    ((x) ? (gpio_high(IPS096_DC_PIN)) : (gpio_low(IPS096_DC_PIN)))
#define IPS096_RST(x)                   ((x) ? (gpio_high(IPS096_RST_PIN)) : (gpio_low(IPS096_RST_PIN)))
#define IPS096_CS(x)                    ((x) ? (gpio_high(IPS096_CS_PIN)) : (gpio_low(IPS096_CS_PIN)))
#define IPS096_BLK(x)                   ((x) ? (gpio_high(IPS096_BLK_PIN)) : (gpio_low(IPS096_BLK_PIN)))

typedef enum
{
    IPS096_PORTRAIT = 0,                                        // 竖屏模式
    IPS096_PORTRAIT_180 = 1,                                    // 竖屏模式  旋转180
    IPS096_CROSSWISE = 2,                                       // 横屏模式
    IPS096_CROSSWISE_180 = 3,                                   // 横屏模式  旋转180
} ips096_dir_enum;

typedef enum
{
    IPS096_6X8_FONT = 0,                                        // 6x8      字体
    IPS096_8X16_FONT = 1,                                       // 8x16     字体
} ips096_font_size_enum;

void ips096_init (void);
void ips096_clear(void);
void ips096_full(const uint16_t color);
void ips096_set_dir(ips096_dir_enum dir);
void ips096_set_font(ips096_font_size_enum font);
void ips096_set_color(const uint16_t pen, const uint16_t bgcolor);
void ips096_draw_point(uint16_t x, uint16_t y, const uint16_t color);
void ips096_draw_line(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, const uint16_t color);

void ips096_show_char(uint16_t x, uint16_t y, const char dat);
void ips096_show_string(uint16_t x, uint16_t y, const char dat[]);
void ips096_show_int(uint16_t x, uint16_t y, const int32_t dat, uint8_t num);
void ips096_show_uint(uint16_t x, uint16_t y, const uint32_t dat, uint8_t num);
void ips096_show_float(uint16_t x, uint16_t y, const float dat, uint8_t num, uint8_t pointnum);

void ips096_show_binary_image(uint16_t x, uint16_t y, const uint8_t *image, uint16_t width, uint16_t height,
                              uint16_t dis_width, uint16_t dis_height);
void ips096_show_gray_image(uint16_t x, uint16_t y, const uint8_t *image, uint16_t width, uint16_t height,
                            uint16_t dis_width, uint16_t dis_height, uint8_t threshold);

void
ips096_show_wave(uint16_t x, uint16_t y, const uint16_t *wave, uint16_t width, uint16_t value_max, uint16_t dis_width,
                 uint16_t dis_value_max);


#ifdef __cplusplus
}
#endif

#endif

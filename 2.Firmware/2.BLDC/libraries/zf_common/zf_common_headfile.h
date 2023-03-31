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
* 文件名称          zf_common_headfile
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

#ifndef __HEADFILE_H
#define __HEADFILE_H




#include "stdio.h"
#include "stdint.h"
#include "string.h"



//===================================================芯片 SDK 底层===================================================
#include "ch32v30x_adc.h"
#include "ch32v30x_bkp.h"
#include "ch32v30x_can.h"
#include "ch32v30x_crc.h"
#include "ch32v30x_dac.h"
#include "ch32v30x_dbgmcu.h"
#include "ch32v30x_dma.h"
#include "ch32v30x_exti.h"
#include "ch32v30x_flash.h"
#include "ch32v30x_fsmc.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x_i2c.h"
#include "ch32v30x_iwdg.h"
#include "ch32v30x_pwr.h"
#include "ch32v30x_rcc.h"
#include "ch32v30x_rtc.h"
#include "ch32v30x_sdio.h"
#include "ch32v30x_spi.h"
#include "ch32v30x_tim.h"
#include "ch32v30x_usart.h"
#include "ch32v30x_wwdg.h"


//===================================================芯片 SDK 底层===================================================

//====================================================开源库公共层====================================================
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_common_interrupt.h"
#include "zf_common_fifo.h"
#include "zf_common_typedef.h"
//====================================================开源库公共层====================================================

//===================================================芯片外设驱动层===================================================
#include "zf_driver_adc.h"
#include "zf_driver_delay.h"
#include "zf_driver_dvp.h"
#include "zf_driver_encoder.h"
#include "zf_driver_exti.h"
#include "zf_driver_flash.h"
#include "zf_driver_gpio.h"
//#include "zf_driver_iic.h"
#include "zf_driver_pit.h"
#include "zf_driver_pwm.h"
//#include "zf_driver_soft_iic.h"
//#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"
#include "zf_driver_timer.h"
#include "zf_driver_uart.h"
#include "zf_driver_usb_cdc.h"

//===================================================芯片外设驱动层===================================================

//===================================================外接设备驱动层===================================================
#include "zf_device_camera.h"
#include "zf_device_icm20602.h"
#include "zf_device_ips114.h"
#include "zf_device_tft180.h"
#include "zf_device_ips200.h"
#include "zf_device_mt9v03x_dvp.h"
#include "zf_device_mpu6050.h"
#include "zf_device_type.h"
#include "zf_device_wireless_uart.h"
#include "zf_device_oled.h"
#include "zf_device_scc8660_dvp.h"
#include "zf_device_bluetooth_ch9141.h"
#include "zf_device_wireless_ch573.h"
#include "zf_device_wireless_uart.h"
#include "zf_device_virtual_oscilloscope.h"
#include "zf_device_w25q32.h"
#include "zf_device_k24c02.h"
#include "zf_device_aht20.h"
#include "zf_device_wifi_uart.h"
#include "zf_device_imu660ra.h"
#include "zf_device_imu963ra.h"
#include "zf_device_key.h"
#include "zf_device_gps_tau1201.h"
#include "zf_device_dl1a.h"
#include "zf_device_dm1xa.h"
//===================================================外接设备驱动层===================================================


//===================================================应用组件层===================================================

//===================================================应用组件层===================================================

//===================================================用户自定义文件===================================================

//===================================================用户自定义文件===================================================

#endif


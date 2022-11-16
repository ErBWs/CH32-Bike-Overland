/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             main
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ3184284598)
* @version          查看doc内version文件 版本说明
* @Software         IAR 8.32.4 or MDK 5.28
* @Target core      MM32F327X_G9P
* @Taobao           https://seekfree.taobao.com/
* @date             2022-04-11
********************************************************************************************************************/

#include "zf_common_headfile.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// 本例程是开源库移植用空工程

// **************************** 代码区域 ****************************
int main (void)
{
    clock_init(SYSTEM_CLOCK_120M);                                              // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                                                               // 初始化默认 Debug UART

    // 此处编写用户代码 例如外设初始化代码等
    // Coreboard led init(For test usage)
	gpio_init(H2, GPO, GPIO_HIGH, GPO_PUSH_PULL);
	gpio_init(B13, GPO, GPIO_HIGH, GPO_PUSH_PULL);

	// BLDC and servo motor init
	tft180_show_string(0, 1 * 16, "motor: ==== [done]");

	// Switch init
    system_delay_ms(100);
	tft180_show_string(0, 2 * 16, "menu: ===== [done]");
	pit_ms_init(TIM8_PIT, 10);
	interrupt_set_priority(TIM8_UP_IRQn, 2);

	// Camera init
	mt9v03x_init();
    system_delay_ms(100);
	tft180_show_string(0, 3 * 16, "camera: === [done]");

	tft180_show_string(0, 7 * 16, "all completed!");
    system_delay_ms(100);

	// Clear screen(If the screen is cleared means all the inits were done)
	tft180_clear();
    // 此处编写用户代码 例如外设初始化代码等

    while(1)
    {
        // 此处编写需要循环执行的代码
        // Test code
		gpio_set_level(B13,1);
		gpio_set_level(H2,0);
		system_delay_ms(500);
		gpio_set_level(B13,0);
		gpio_set_level(H2,1);
		system_delay_ms(500);

		// tft180_show_uint(0, 0, !GPIO_ReadInDataBit(GPIOG,GPIO_PIN_3), 6);
    	tft180_displayimage032_zoom((const uint8_t *)mt9v03x_image, 188, 120, 160, 128);
        // 此处编写需要循环执行的代码
    }
}
// **************************** 代码区域 ****************************

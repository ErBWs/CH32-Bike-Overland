/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-09-09     WCH        the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_SRAM
#include "drv_sram.h"

#define DRV_DEBUG
#define LOG_TAG             "drv.sram"
#include <drv_log.h>

#define Bank1_SRAM1_ADDR    ((u32)(0x68000000))
#define EX_SRAM_SIZE        (512*1024)

#ifdef RT_USING_MEMHEAP_AS_HEAP

static struct rt_memheap system_heap;

#endif


static int sram_fmsc_init(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure={0};
    FSMC_NORSRAMTimingInitTypeDef  readWriteTiming={0};
    GPIO_InitTypeDef  GPIO_InitStructure={0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);

    /* FSMC_NADV */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOD, GPIO_Pin_13);

    readWriteTiming.FSMC_AddressSetupTime = 0x03;
    readWriteTiming.FSMC_AddressHoldTime = 0x06;
    readWriteTiming.FSMC_DataSetupTime = 0x06;
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_CLKDivision = 0x00;
    readWriteTiming.FSMC_DataLatency = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Enable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);

#ifdef RT_USING_MEMHEAP_AS_HEAP
        /* If RT_USING_MEMHEAP_AS_HEAP is enabled, external SRAM is initialized to the heap */
        rt_memheap_init(&system_heap, "exsram", (void *)Bank1_SRAM1_ADDR, EX_SRAM_SIZE);
#endif
    return RT_EOK;
}
INIT_BOARD_EXPORT(sram_fmsc_init);




#ifdef FINSH_USING_MSH
#define SDRAM_DATA_WIDTH 16
int sdram_test(void)
{
    int i = 0;
    uint32_t start_time = 0, time_cast = 0;
    char data_width = 2;
    uint16_t data = 0;

    /* write data */
    rt_kprintf("Writing the %ld bytes data, waiting....", EX_SRAM_SIZE);
    start_time = rt_tick_get();
    for (i = 0; i < EX_SRAM_SIZE / data_width; i++)
    {
        *(__IO uint16_t *)(Bank1_SRAM1_ADDR + i * data_width) = (uint32_t)0x5555;
    }

    time_cast = rt_tick_get() - start_time;
    rt_kprintf("Write data success, total time: %d.%03dS.", time_cast / RT_TICK_PER_SECOND,
          time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));

    /* read data */
    rt_kprintf("start Reading and verifying data, waiting....");
    for (i = 0; i < EX_SRAM_SIZE / data_width; i++)
    {

        data = *(__IO uint16_t *)(Bank1_SRAM1_ADDR + i * data_width);


        rt_kprintf("data=%x\r\n",data);

        if (data != 0x5555)
        {
            rt_kprintf("SRAM test failed!");
//            break;
        }
        if(i>16) break;
    }
    if (i >= Bank1_SRAM1_ADDR / data_width)
    {
        rt_kprintf("SRAM test success!");
    }
    return RT_EOK;
}
MSH_CMD_EXPORT(sdram_test, sdram test)
#endif /* FINSH_USING_MSH */


#endif /* RT_USING_SRAM */

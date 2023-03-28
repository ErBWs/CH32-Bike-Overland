/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH        the first version
 */

#include <rtthread.h>
#include "spi_flash.h"
#include "spi_flash_sfud.h"
#include "drv_spi.h"

#if defined(BSP_USING_SPI_FLASH)

/* if BSP_USING_SPI1 then BSP_USING_SPI_FLASH will be enable  */
static int rt_hw_spi_flash_init(void)
{
    /* PA4--->CS */
    rt_hw_spi_device_attach("spi3", "spi30", GPIOA, GPIO_Pin_15);
    if (RT_NULL == rt_sfud_flash_probe("W25Q128", "spi30"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);

#endif

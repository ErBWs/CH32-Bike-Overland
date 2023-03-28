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

#ifdef RT_USING_WDT
#include "drv_wdt.h"

#define DRV_DEBUG
#define LOG_TAG             "drv.wdt"
#include <drv_log.h>

static struct ch32_wdt_obj ch32_wdt;
static struct rt_watchdog_ops ops;

static rt_err_t IWDG_Reload(IWDG_HandleTypeDef *hiwdg)
{
    hiwdg->Instance->CTLR=KEY_Reload;
    return RT_EOK;
}

static rt_err_t IWDG_Init(IWDG_HandleTypeDef *hiwdg)
{
    hiwdg->Instance->CTLR=IWDG_WriteAccess_Enable;
    hiwdg->Instance->PSCR = hiwdg->Init.Prescaler;
    hiwdg->Instance->RLDR = hiwdg->Init.Reload;

    hiwdg->Instance->CTLR = KEY_Reload;
    hiwdg->Instance->CTLR = KEY_Enable;
    return RT_EOK;
}

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
        /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        if(IWDG_Reload(&ch32_wdt.hiwdg) != RT_EOK)
        {
            LOG_E("watch dog keepalive fail.");
        }
        break;
        /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
#if defined(LSI_VALUE)
        if(LSI_VALUE)
        {
            ch32_wdt.hiwdg.Init.Reload = (*((rt_uint32_t*)arg)) * LSI_VALUE / 256 ;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
        if(ch32_wdt.hiwdg.Init.Reload > 0xFFF)
        {
            LOG_E("wdg set timeout parameter too large, please less than %ds",0xFFF * 256 / LSI_VALUE);
            return -RT_EINVAL;
        }
#else
  #error "Please define the value of LSI_VALUE!"
#endif
        if(ch32_wdt.is_start)
        {
            if (IWDG_Init(&ch32_wdt.hiwdg) != RT_EOK)
            {
                LOG_E("wdg set timeout failed.");
                return -RT_ERROR;
            }
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
#if defined(LSI_VALUE)
        if(LSI_VALUE)
        {
            (*((rt_uint32_t*)arg)) = ch32_wdt.hiwdg.Init.Reload * 256 / LSI_VALUE;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
#else
  #error "Please define the value of LSI_VALUE!"
#endif
        break;
    case RT_DEVICE_CTRL_WDT_START:
        if (IWDG_Init(&ch32_wdt.hiwdg) != RT_EOK)
        {
            LOG_E("wdt start failed.");
            return -RT_ERROR;
        }
        ch32_wdt.is_start = 1;
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_wdt_init(void)
{
    ch32_wdt.hiwdg.Instance = IWDG;
    ch32_wdt.hiwdg.Init.Prescaler = IWDG_Prescaler_256;
    ch32_wdt.hiwdg.Init.Reload = 0x00000FFF;
    ch32_wdt.is_start = 0;
    ops.init = &wdt_init;
    ops.control = &wdt_control;
    ch32_wdt.watchdog.ops = &ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&ch32_wdt.watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#endif /* RT_USING_WDT */

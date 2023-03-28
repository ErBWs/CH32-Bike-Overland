/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH        the first version
 */
#ifndef DRV_WDT_H__
#define DRV_WDT_H__


#define LSI_VALUE 40000
#define KEY_Reload    ((uint16_t)0xAAAA)
#define KEY_Enable    ((uint16_t)0xCCCC)

typedef struct
{
  uint32_t Prescaler;
  uint32_t Reload;
} IWDG_InitTypeDef;

typedef struct
{
  IWDG_TypeDef                 *Instance;
  IWDG_InitTypeDef             Init;
} IWDG_HandleTypeDef;

struct ch32_wdt_obj
{
    rt_watchdog_t      watchdog;
    IWDG_HandleTypeDef hiwdg ;
    rt_uint16_t        is_start;
};


#endif /* RT_USING_WDT */

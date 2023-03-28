/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH        the first version
 */
#ifndef DRV_DAC_H__
#define DRV_DAC_H__
typedef struct
{
    DAC_TypeDef                   *Instance;
    DAC_InitTypeDef                Init;
    rt_uint32_t                    Channel;
}DAC_HandleTypeDef;




#endif

/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH        the first version
 */

#ifndef __DRV_DMA_H_
#define __DRV_DMA_H_

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DMA_INSTANCE_TYPE              DMA_Channel_TypeDef

struct dma_config {
    DMA_INSTANCE_TYPE *Instance;
    rt_uint32_t dma_rcc;
    IRQn_Type dma_irq;
};


typedef struct _DMA_HandleTypeDef{
    DMA_INSTANCE_TYPE    *Instance;
    DMA_InitTypeDef       Init;
}DMA_HandleTypeDef;


#ifdef __cplusplus
}
#endif

#endif /*__DRV_DMA_H_ */

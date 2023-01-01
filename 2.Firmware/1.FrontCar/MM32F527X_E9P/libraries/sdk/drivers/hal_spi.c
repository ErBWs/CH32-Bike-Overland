/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_spi.h"

void SPI_SetBaudrate(SPI_Type * SPIx, uint32_t src_clk, uint32_t baudrate)
{
    uint32_t div = src_clk / baudrate;
    if (div < 2u)
    {
        /* div = 0, 1 is not allowed. */
        div = 2u;
    }
    SPIx->SPBRG = div;
    if (div <= 4)
    {
        /* to support high speed mode. */
        SPIx->CCTL |= (SPI_I2S_CCTL_TXEDGE_MASK | SPI_I2S_CCTL_RXEDGE_MASK);
    }
    else
    {
        SPIx->CCTL &= ~(SPI_I2S_CCTL_TXEDGE_MASK | SPI_I2S_CCTL_RXEDGE_MASK);
    }
}

/* SPI peripheral is disabled just after the initialization.
 * user needs to call SPI_Enable() before using the module.
 */
void SPI_InitMaster(SPI_Type * SPIx, SPI_Master_Init_Type * init)
{
    uint32_t gctl = SPIx->GCTL &~ ( SPI_I2S_GCTL_MODE_MASK
                                  | SPI_I2S_GCTL_RXEN_MASK
                                  | SPI_I2S_GCTL_TXEN_MASK
                                  | SPI_I2S_GCTL_NSS_MASK
                                  | SPI_I2S_GCTL_INTEN_MASK
                                  | SPI_I2S_GCTL_DW832_MASK
                                  );
    uint32_t extctl = 0u;

    uint32_t cctl = SPIx->CCTL &~ ( SPI_I2S_CCTL_CPHA_MASK
                                  | SPI_I2S_CCTL_CPOL_MASK
                                  | SPI_I2S_CCTL_LSBFE_MASK
                                  | SPI_I2S_CCTL_SPILEN_MASK
                                  );

    /* Master. */
    gctl |= SPI_I2S_GCTL_MODE_MASK; /* master mode, disable spi, and reset the other bits in CCTL. */

    /* XferMode. */
    switch (init->XferMode)
    {
        case SPI_XferMode_RxOnly:
            gctl |= SPI_I2S_GCTL_RXEN_MASK;
            break;

        case SPI_XferMode_TxRx:
            gctl |= (SPI_I2S_GCTL_RXEN_MASK | SPI_I2S_GCTL_TXEN_MASK);
            break;

        default:
            break;
    }

    /* AutoCS. */
    if (init->AutoCS)
    {
        gctl |= SPI_I2S_GCTL_NSS_MASK;
    }

    /* Interrupts. Always enable the global interrupt. The specific events are controlled by each bits in INTEN register. */
    gctl |= SPI_I2S_GCTL_INTEN_MASK;

    /* DataWidth. */
    if (init->DataWidth == SPI_DataWidth_7b)
    {
    }
    else if (init->DataWidth == SPI_DataWidth_8b)
    {
        cctl |= SPI_I2S_CCTL_SPILEN_MASK;
    }
    else
    {
        gctl |= SPI_I2S_GCTL_DW832_MASK;
        extctl = SPI_I2S_EXTCTL_EXTLEN(init->DataWidth);
    }

    /* CPOL & CPHA. */
    cctl |= ( (SPI_I2S_CCTL_CPHA_MASK | SPI_I2S_CCTL_CPOL_MASK)
            & ((init->PolPha) << SPI_I2S_CCTL_CPHA_SHIFT)
            );

    /* MSB. */
    if (init->LSB)
    {
        cctl |= SPI_I2S_CCTL_LSBFE_MASK;
    }

    SPIx->GCTL = gctl;
    SPIx->CCTL = cctl;
    SPIx->EXTCTL = extctl;

    /* BaudRate. */
    SPI_SetBaudrate(SPIx, init->ClockFreqHz, init->BaudRate);
}

void SPI_InitSlave(SPI_Type * SPIx, SPI_Slave_Init_Type * init)
{
    uint32_t gctl = SPIx->GCTL &~ ( SPI_I2S_GCTL_MODE_MASK
                                  | SPI_I2S_GCTL_RXEN_MASK
                                  | SPI_I2S_GCTL_TXEN_MASK
                                  | SPI_I2S_GCTL_NSS_MASK
                                  | SPI_I2S_GCTL_INTEN_MASK
                                  | SPI_I2S_GCTL_DW832_MASK
                                  );
    uint32_t cctl = SPIx->CCTL &~ ( SPI_I2S_CCTL_CPHA_MASK
                                  | SPI_I2S_CCTL_CPOL_MASK
                                  | SPI_I2S_CCTL_LSBFE_MASK
                                  | SPI_I2S_CCTL_SPILEN_MASK
                                  );
    uint32_t extctl = 0u;

    /* XferMode. */
    switch (init->XferMode)
    {
        case SPI_XferMode_RxOnly:
            gctl |= SPI_I2S_GCTL_RXEN_MASK;
            break;

        case SPI_XferMode_TxRx:
            gctl |= (SPI_I2S_GCTL_RXEN_MASK | SPI_I2S_GCTL_TXEN_MASK);
            break;

        default:
            break;
    }

    /* AutoCS. */
    if (init->AutoCS)
    {
        gctl |= SPI_I2S_GCTL_NSS_MASK;
    }

    /* Interrupts. Always enable the global interrupt. The specific events are controlled by each bits in INTEN register. */
    gctl |= SPI_I2S_GCTL_INTEN_MASK;

    /* DataWidth. */
    if (init->DataWidth == SPI_DataWidth_7b)
    {
    }
    else if (init->DataWidth == SPI_DataWidth_8b)
    {
        cctl |= SPI_I2S_CCTL_SPILEN_MASK;
    }
    else
    {
        gctl |= SPI_I2S_GCTL_DW832_MASK;
        extctl = SPI_I2S_EXTCTL_EXTLEN(init->DataWidth);
    }

    /* CPOL & CPHA. */
    cctl |= ( (SPI_I2S_CCTL_CPHA_MASK | SPI_I2S_CCTL_CPOL_MASK)
            & ((init->PolPha) << SPI_I2S_CCTL_CPHA_SHIFT)
            );

    /* MSB. */
    if (init->LSB)
    {
        cctl |= SPI_I2S_CCTL_LSBFE_MASK;
    }

    SPIx->GCTL = gctl;
    SPIx->CCTL = cctl;
    SPIx->EXTCTL = extctl;
}

void SPI_Enable(SPI_Type * SPIx, bool enable)
{
    if (enable)
    {
        SPIx->GCTL |= SPI_I2S_GCTL_SPIEN_MASK;
    }
    else
    {
        SPIx->GCTL &= ~SPI_I2S_GCTL_SPIEN_MASK;
    }
}

uint32_t SPI_GetStatus(SPI_Type * SPIx)
{
    return SPIx->CSTAT;
}

void SPI_EnableInterrupts(SPI_Type * SPIx, uint32_t interrupts, bool enable)
{
    if (enable)
    {
        SPIx->INTEN |= interrupts;
    }
    else
    {
        SPIx->INTEN &= ~interrupts;
    }
}

uint32_t SPI_GetInterruptStatus(SPI_Type * SPIx)
{
    return SPIx->INTSTAT;
}

void SPI_ClearInterruptStatus(SPI_Type * SPIx, uint32_t interrupts)
{
    SPIx->INTCLR = interrupts;
}

void SPI_PutData(SPI_Type * SPIx, uint32_t data)
{
    SPIx->TXREG = data;
}

uint32_t SPI_GetData(SPI_Type * SPIx)
{
    return SPIx->RXREG;
}

void SPI_EnableDMA(SPI_Type * SPIx, bool enable)
{
    if (enable)
    {
        SPIx->GCTL |= SPI_I2S_GCTL_DMAMODE_MASK;
    }
    else
    {
        SPIx->GCTL &= ~SPI_I2S_GCTL_DMAMODE_MASK;
    }
}

uint32_t SPI_GetEnabledInterrupts(SPI_Type * SPIx)
{
    return SPIx->INTEN;
}

uint32_t SPI_GetRxDataRegAddr(SPI_Type * SPIx)
{
    return (uint32_t)(&(SPIx->RXREG));
}

uint32_t SPI_GetTxDataRegAddr(SPI_Type * SPIx)
{
    return (uint32_t)(&(SPIx->TXREG));
}

void SPI_EnableCS(SPI_Type * SPIx, uint32_t cs_mask)
{
    SPIx->NSSR = ~(cs_mask);
}

void SPI_SetRxDataNum(SPI_Type * SPIx, uint16_t number)
{
    SPIx->RXDNR = number;
}


void SPI_SetPadMux(SPI_Type * SPIx, SPI_PadMux_Type opt)
{
    SPIx->GCTL = ( (SPIx->GCTL &~ SPI_I2S_GCTL_PADSEL_MASK)
                 | SPI_I2S_GCTL_PADSEL(opt)
                 );
}
/* EOF. */

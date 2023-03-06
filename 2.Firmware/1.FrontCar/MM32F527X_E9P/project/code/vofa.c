/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "vofa.h"

float vofaData[CHANNEL_NUM] = {0};

void VofaBigEndianSendFrame()
{
    unsigned char vofaTail[4] = {0x00, 0x00, 0x80, 0x7F};

    uart_write_buffer(UART_1, (uint8_t *)vofaData, CHANNEL_NUM * sizeof(float));
    uart_write_buffer(UART_1, (uint8_t *)vofaTail, 4);
}

void VofaLittleEndianSendFrame()
{
    unsigned char vofaTail[4] = {0x00, 0x00, 0x80, 0x7F};

    uart_write_buffer(UART_1, (uint8_t *)vofaData, CHANNEL_NUM * sizeof(float));
    uart_write_buffer(UART_1, (uint8_t *)vofaTail, 4);
}
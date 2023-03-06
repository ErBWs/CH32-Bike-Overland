/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "vofa.h"

float vofaData[CHANNEL_NUM] = {0};

/*!
 * @brief   Vofa send data using JustFloat
 *
 * @param   void
 * @return  void
 *
 * @note    Big-Endian is for C51, normally Little-Endian is used.
 */
void VofaLittleEndianSendFrame()
{
    unsigned char vofaTail[4] = {0x00, 0x00, 0x80, 0x7F};

    uart_write_buffer(UART_1, (uint8_t *) vofaData, CHANNEL_NUM * sizeof(float));
    uart_write_buffer(UART_1, (uint8_t *) vofaTail, 4);
}

void VofaBigEndianSendFrame()
{
    unsigned char vofaTail[4] = {0x7F, 0x80, 0x00, 0x00};
    float temp;

    for (int i = 0; i < CHANNEL_NUM * sizeof(float); i += 2)
    {
        temp = ((uint8 *) vofaData)[i];
        ((uint8 *) vofaData)[i] = ((uint8 *) vofaData)[i + 1];
        ((uint8 *) vofaData)[i + 1] = (uint8_t) temp;
    }

    uart_write_buffer(UART_1, (uint8_t *) vofaTail, 4);
    uart_write_buffer(UART_1, (uint8_t *) vofaData, CHANNEL_NUM * sizeof(float));
}
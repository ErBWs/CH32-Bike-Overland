/*
 * sendware.c
 *
 *  Created on: 2021年12月4日
 *      Author: Lenovo and sormaker
 */

#include "sendware.h"

uint8 DataSend[100];

void vcan_sendware(void *wareaddr, uint32 waresize)
{
#define VCAN_PORT UART_3
#define CMD_WARE     3

    uint8 cmdf[2] = {CMD_WARE, ~CMD_WARE};
    uint8 cmdr[2] = {~CMD_WARE, CMD_WARE};

    uart_write_buffer(VCAN_PORT, cmdf, sizeof(cmdf));
    uart_write_buffer(VCAN_PORT, (uint8 *) wareaddr, waresize);
    uart_write_buffer(VCAN_PORT, cmdr, sizeof(cmdr));
}

//匿名姿态角函数
void ano_sendware(int16 roll, int16 pitch, int16 yaw, uint8 fu)
{
    #define VCAN_PORT UART_3


    uint8 _cnt = 0;
    DataSend[_cnt++] = 0xAA;
    DataSend[_cnt++] = 0xFF;
    DataSend[_cnt++] = 0x03;
    DataSend[_cnt++] = 7;

    DataSend[_cnt++] = BYTE0(roll);
    DataSend[_cnt++] = BYTE1(roll);

    DataSend[_cnt++] = BYTE0(pitch);
    DataSend[_cnt++] = BYTE1(pitch);

    DataSend[_cnt++] = BYTE0(yaw);
    DataSend[_cnt++] = BYTE1(yaw);

    DataSend[_cnt++] = BYTE0(fu);

    uint8 sumcheck = 0;
    uint8 addcheck = 0;
    for(uint8 i = 0; i < (DataSend[3]+4); i++)
    {
        sumcheck += DataSend[i];
        addcheck += sumcheck;
    }

    DataSend[_cnt++] = sumcheck;
    DataSend[_cnt++] = addcheck;

    uart_write_buffer(VCAN_PORT,DataSend,_cnt);


}

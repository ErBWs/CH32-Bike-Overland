#ifndef _JDY34_H_
#define _JDY34_H_

#include "zf_common_headfile.h"
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#define BLUE_TOOTH_JDY34_BAUD       115200
#define BLUE_TOOTH_JDY34_TX_PIN     UART7_MAP3_TX_E12
#define BLUE_TOOTH_JDY34_RX_PIN     UART7_MAP3_RX_E13
#define BLUE_TOOTH_JDY34_UART       UART_7


#define DATA_STREAM_LEN  3 //61
#define RX_DATA_BUFFER_LEN 100
#define NAMEMAXLEN  20
#define PASSWORDLEN 5

#define GET_ELE(buff,offset,type) (*(type *)BuffDataIndex(buff,&offset,sizeof(type)))

typedef struct USER_DATA
{
    char CustomName[NAMEMAXLEN];
    char PassWord[PASSWORDLEN];
    uint8_t Baudrate;
    signed char VelocityVal;
    signed char TurnVal;//编译器特性！！char和unsigned char 都是无符号，要有符号就要加signed！！
}UserDataTypedef;
extern uint8 receive_complete;
extern UserDataTypedef BlueToothData;
void BlueToothInit(void);
void BlueToothUpdate(void);
void BlueToothInterupt_Handler(void);
#endif

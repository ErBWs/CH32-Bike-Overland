#include "jdy34.h"
#include "inc_all.h"
UserDataTypedef BlueToothData = {"Balance_Bike","1234",8,0,0};
static uint8 blue_tooth_buffer[RX_DATA_BUFFER_LEN];
static uint8 blue_tooth_data;
uint8 receive_complete=0;
/*
波特率选择
4：9600
5：19200
6：38400
7：57600
8：115200
9：128000
*/


static void* BuffDataIndex(void* buff,uint16 *offset,uint8_t size)
{
    void *p = buff+*offset;
    *offset += size;
    return p;
}
static void BlueToothPrintf(char *formatString,...)
{
    char TXBuffer[RX_DATA_BUFFER_LEN];
    uint16_t length;
    va_list args;
    va_start(args,formatString);
    length = vsnprintf(TXBuffer,RX_DATA_BUFFER_LEN,formatString,args);
    uart_write_buffer(BLUE_TOOTH_JDY34_UART,(uint8*)TXBuffer,length);
    va_end(args);
}
void BlueToothUpdate(void)
{
    BlueToothPrintf("AT+NAME%s\r\n",BlueToothData.CustomName);
    system_delay_ms(100);
    BlueToothPrintf("AT+PIN%s\r\n",BlueToothData.PassWord);
    system_delay_ms(100);
    BlueToothPrintf("AT+BAUD%d\r\n",BlueToothData.Baudrate);
    system_delay_ms(100);
    BlueToothPrintf("AT+RESET\r\n");
    system_delay_ms(100);
}
void BlueToothInit(void)
{
    uart_init(BLUE_TOOTH_JDY34_UART,BLUE_TOOTH_JDY34_BAUD,BLUE_TOOTH_JDY34_TX_PIN,BLUE_TOOTH_JDY34_RX_PIN);
    uart_rx_interrupt(BLUE_TOOTH_JDY34_UART, 1);
    interrupt_set_priority(UART7_IRQn,(1<<5) | 1);
//    BlueToothUpdate();
}
static void DataResolve(void)
{
    uint16 offset = 0;
    uint8 ValidFactorFlag = 0;
    uint8 BreakDownFlag = 0;
    BlueToothData.VelocityVal = GET_ELE(blue_tooth_buffer,offset,char);
    BlueToothData.TurnVal = GET_ELE(blue_tooth_buffer,offset,char);
//    BreakDownFlag = GET_ELE(blue_tooth_buffer,offset,char);
//    ValidFactorFlag = GET_ELE(blue_tooth_buffer,offset,char);
//    if(ValidFactorFlag)
//    {
//        flySpdPid.Kp = GET_ELE(blue_tooth_buffer,offset,float);
//        flySpdPid.Ki = GET_ELE(blue_tooth_buffer,offset,float);
//        flySpdPid.Kd = GET_ELE(blue_tooth_buffer,offset,float);
//        flyAnglePid.Kp = GET_ELE(blue_tooth_buffer,offset,float);
//        flyAnglePid.Ki = GET_ELE(blue_tooth_buffer,offset,float);
//        flyAnglePid.Kd = GET_ELE(blue_tooth_buffer,offset,float);
//        flyAngleSpdPid.Kp = GET_ELE(blue_tooth_buffer,offset,float);
//        flyAngleSpdPid.Ki = GET_ELE(blue_tooth_buffer,offset,float);
//        flyAngleSpdPid.Kd = GET_ELE(blue_tooth_buffer,offset,float);
//        backSpdPid.Kp = GET_ELE(blue_tooth_buffer,offset,float);
//        backSpdPid.Ki = GET_ELE(blue_tooth_buffer,offset,float);
//        backSpdPid.Kd = GET_ELE(blue_tooth_buffer,offset,float);
//        dirPid.Kp = GET_ELE(blue_tooth_buffer,offset,float);
//        dirPid.Kd = GET_ELE(blue_tooth_buffer,offset,float);
//    }
//    if(BreakDownFlag)
//    {
//        stagger_flag=1;
//        motoDutySet(MOTOR_FLY_PIN,0);//使单车失去控制直接倒下
//        flyAngleSpdPid.iout=0;
//    }

}
void BlueToothInterupt_Handler(void)
{
    static uint16 buffer_cursor=0;
    static uint8 flag=0;
    uart_query_byte(BLUE_TOOTH_JDY34_UART,&blue_tooth_data);
    switch(flag)
    {
        case 0:
            if(blue_tooth_data==0xA5)
            {
                memset(blue_tooth_buffer,0,DATA_STREAM_LEN);
                buffer_cursor=0;
                flag=1;
            }
        break;
        case 1:
            blue_tooth_buffer[buffer_cursor]=blue_tooth_data;
            if(buffer_cursor==DATA_STREAM_LEN-1)
                flag=2;
            buffer_cursor++;
        break;
        case 2:
            if(blue_tooth_data==0x5A)
            {
                uint8 sum=0;
                uint16 i;
                for(i=0;i<DATA_STREAM_LEN-1;i++)
                    sum+=blue_tooth_buffer[i];
                if(sum==blue_tooth_buffer[i])
                    DataResolve();
                flag=0;
            }
            else {
                flag=0;
            }
        break;
    }
}

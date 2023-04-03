/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          zf_driver_uart
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-09-15        ��W            first version
********************************************************************************************************************/
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"

// �������ֹ�޸ģ��ڲ�ʹ���û��������
const uint8 uart_irq[] = {USART1_IRQn, USART2_IRQn, USART3_IRQn, UART4_IRQn, UART5_IRQn, UART6_IRQn, UART7_IRQn, UART8_IRQn};
const uint32 uart_index[] = {USART1_BASE, USART2_BASE, USART3_BASE, UART4_BASE, UART5_BASE, UART6_BASE, UART7_BASE, UART8_BASE};

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ���һ���ֽ�
// ����˵��     uartn       ����ͨ��
// ����˵��     dat         ��������
// ���ز���     void
// ʹ��ʾ��     uart_write_byte(UART_1, 0x43);        //����1����0x43��
//-------------------------------------------------------------------------------------------------------------------
void uart_write_byte(uart_index_enum uartn, const uint8 dat)
{
    while((((USART_TypeDef*)uart_index[uartn])->STATR & USART_FLAG_TXE)==0);
    ((USART_TypeDef*)uart_index[uartn])->DATAR = dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ�������
// ����˵��     uartn       ����ͨ��
// ����˵��     buff        Ҫ���͵������ַ
// ����˵��     len         ���ݳ���
// ���ز���     void
// ʹ��ʾ��     uart_write_buffer(UART_1, buff, 10);     //����1����10��buff���顣
//-------------------------------------------------------------------------------------------------------------------
void uart_write_buffer(uart_index_enum uartn, const uint8 *buff, uint32 len)
{
    zf_assert(buff != NULL);
    while(len--)
        uart_write_byte(uartn, *buff++);
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ����ַ���
// ����˵��     uartn       ����ͨ��
// ����˵��     str         �ַ����׵�ַ
// ���ز���     void
// ʹ��ʾ��     uart_putstr(UART_1, (uint8 *)"12345")   //����1����12345����ַ���
//-------------------------------------------------------------------------------------------------------------------
void uart_write_string(uart_index_enum uartn, const char *str)
{
    zf_assert(str != NULL);
    while(*str)                                                                 // һֱѭ������β
    {
        uart_write_byte(uartn, *str++);
    }
}



//-------------------------------------------------------------------------------------------------------------------
// �������     �򿪴��ڽ����ж�
// ����˵��     uartn       ����ͨ��
// ����˵��     status      ʹ�ܻ���ʧ��
// ���ز���     void
// ʹ��ʾ��     uart_rx_irq(UART_1, ENABLE);        //�򿪴���1�����ж�
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_interrupt(uart_index_enum uartn, uint8 status)
{
    USART_ITConfig(((USART_TypeDef*)uart_index[uartn]), USART_IT_RXNE, status);

    // �����ж����ȼ�
    interrupt_set_priority((uint32)((IRQn_Type)uart_irq[uartn]), 0);

    if(status)  interrupt_enable((IRQn_Type)uart_irq[uartn]);
    else        interrupt_disable((IRQn_Type)uart_irq[uartn]);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �򿪴��ڷ����ж�
// ����˵��     uartn       ����ͨ��
// ����˵��     status      ʹ�ܻ���ʧ��
// ���ز���     void
// ʹ��ʾ��     uart_tx_irq(UART_1, DISABLE);       //�رմ���1���� �ж�
//-------------------------------------------------------------------------------------------------------------------
void uart_tx_interrupt(uart_index_enum uartn, uint8 status)
{
    USART_ITConfig(((USART_TypeDef*)uart_index[uartn]), USART_IT_TXE, status);

    // �����ж����ȼ�
    interrupt_set_priority((uint32)((IRQn_Type)uart_irq[uartn]), 0);

    if(status)  interrupt_enable((IRQn_Type)uart_irq[uartn]);
    else        interrupt_disable((IRQn_Type)uart_irq[uartn]);
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ���ڽ��յ����ݣ�whlie�ȴ���
// ����˵��     uartn           ����ģ���(UART_1 - UART_8)
// ����˵��     *dat            �������ݵĵ�ַ
// ���ز���     void
// ʹ��ʾ��     uint8 dat; uart_read_byte(USART_1,&dat);       // ���մ���1����  ������dat������
//-------------------------------------------------------------------------------------------------------------------
void uart_read_byte(uart_index_enum uartn, uint8 *dat)
{
    while((((USART_TypeDef*)uart_index[uartn])->STATR & USART_FLAG_RXNE) == 0);
    *dat = (uint16)(((USART_TypeDef*)uart_index[uartn])->DATAR & (uint16)0xFF);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ���ڽ��յ����ݣ���ѯ���գ�
// ����˵��     uartn           ����ģ���(UART_1 - UART_8)
// ����˵��     *dat            �������ݵĵ�ַ
// ���ز���     uint8           1�����ճɹ�   0��δ���յ�����
// ʹ��ʾ��     uint8 dat; uart_query_byte(USART_1,&dat);       // ���մ���1����  ������dat������
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_query_byte(uart_index_enum uartn, uint8 *dat)
{
    if((((USART_TypeDef*)uart_index[uartn])->STATR & USART_FLAG_RXNE) != 0)
    {
        *dat = (((USART_TypeDef*)uart_index[uartn])->DATAR & 0xFF);
        return 1;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڳ�ʼ��
// ����˵��     uartn       ����ͨ��
// ����˵��     baud        ������
// ����˵��     tx_pin      ���ڷ������ź�
// ����˵��     rx_pin      ���ڽ������ź�
// ���ز���     void
// ʹ��ʾ��     uart_init(UART_1, 115200, UART1_TX_A9, UART1_RX_A10); //����1��ʼ�����ź�,TXΪA9,RXΪA10
//-------------------------------------------------------------------------------------------------------------------
void uart_init(uart_index_enum uart_n, uint32 baud, uart_pin_enum tx_pin, uart_pin_enum rx_pin)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
    // RX��TX������Ҫ����ͬһ��ӳ�����ţ������ͬ�ͻ������
    zf_assert((tx_pin & (uart_n << 12)) == (rx_pin & (uart_n << 12)));      // tx_pin �� rx_pin ������ uart_n ƥ��
    zf_assert((tx_pin >> 8) == (rx_pin >> 8));                              // tx_pin �� rx_pin ������鴫��

    gpio_init(tx_pin & 0xFF, GPO, 0, GPO_AF_PUSH_PULL);
    gpio_init(rx_pin & 0xFF, GPI, 0, GPI_PULL_UP);

    // AFIO���߿���
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    switch(tx_pin & 0xFFFF)
    {
        case UART1_MAP1_TX_B6:
           AFIO->PCFR2 &= ~(0x01<<26);
           AFIO->PCFR1 &= ~(0x01<<2);
           AFIO->PCFR1 |=  (0x01<<2);
           break;
        case UART1_MAP2_TX_B15:
            AFIO->PCFR2 &= ~(0x01<<26);
            AFIO->PCFR2 |=  (0x01<<26);
            AFIO->PCFR1 &= ~(0x01<<2);
           break;
        case UART1_MAP3_TX_A6:
            AFIO->PCFR2 &= ~(0x01<<26);
            AFIO->PCFR2 |=  (0x01<<26);
            AFIO->PCFR1 &= ~(0x01<<2);
            AFIO->PCFR1 |=  (0x01<<2);
           break;

        case UART2_MAP1_TX_D5:
            AFIO->PCFR1 &= ~(0x01<<3);
            AFIO->PCFR1 |=  (0x01<<3);
           break;

        case UART3_MAP1_TX_C10:
            AFIO->PCFR1 &= ~(0x03<<3);
            AFIO->PCFR1 |=  (0x01<<3);
           break;

        case UART3_MAP2_TX_D8:
            AFIO->PCFR1 &= ~(0x03<<3);
            AFIO->PCFR1 |=  (0x03<<3);
           break;

        case UART4_MAP1_TX_B0:
            AFIO->PCFR2 &= ~(0x03<<16);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 16);
           break;

        case UART4_MAP3_TX_E0:
            AFIO->PCFR2 &= ~(0x03<<16);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 16);
           break;

        case UART5_MAP1_TX_B4:
            AFIO->PCFR2 &= ~(0x03<<18);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 18);
           break;

        case UART5_MAP3_TX_E8:
            AFIO->PCFR2 &= ~(0x03<<18);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 18);
           break;

        case UART6_MAP1_TX_B8:
            AFIO->PCFR2 &= ~(0x03<<20);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 20);
           break;

        case UART6_MAP3_TX_E10:
            AFIO->PCFR2 &= ~(0x03<<20);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 20);
           break;

        case UART7_MAP1_TX_A6:
            AFIO->PCFR2 &= ~(0x03<<22);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 22);
           break;

        case UART7_MAP3_TX_E12:
            AFIO->PCFR2 &= ~(0x03<<22);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 22);
           break;

        case UART8_MAP1_TX_A14:
            AFIO->PCFR2 &= ~(0x03<<24);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 24);
           break;

        case UART8_MAP3_TX_E14:
            AFIO->PCFR2 &= ~(0x03<<24);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 24);
           break;
    }


    // ��������ʹ��
    if(UART_1 == uart_n)        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    else if(UART_2 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    else if(UART_3 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    else if(UART_4 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,  ENABLE);
    else if(UART_5 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,  ENABLE);
    else if(UART_6 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART6,  ENABLE);
    else if(UART_7 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7,  ENABLE);
    else if(UART_8 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8,  ENABLE);

    // ���ڲ�������
    USART_InitTypeDef USART_InitStructure = {0};
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    // ʹ�ܴ���
    USART_Init((USART_TypeDef*)uart_index[uart_n], &USART_InitStructure);
    USART_Cmd((USART_TypeDef*)uart_index[uart_n], ENABLE);

}





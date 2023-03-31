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
* �ļ�����          zf_common_debug
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


#include "zf_driver_uart.h"
#include "zf_common_interrupt.h"
#include "zf_common_fifo.h"

#include "zf_common_debug.h"

#if DEBUG_UART_USE_INTERRUPT                                                    // ������� debug uart �����ж�
uint8                       debug_uart_buffer[DEBUG_RING_BUFFER_LEN];           // ���ݴ������
uint8                       debug_uart_data;
fifo_struct                 debug_uart_fifo;
#endif

static debug_output_struct  debug_output_info;
static volatile uint8       zf_debug_init_flag = 0;
static volatile uint8       zf_debug_assert_enable = 1;

//-------------------------------------------------------------------------------------------------------------------
// �������      debug ����ʱ���� �� 120MHz ����һ����ʱ�� ����Ƭ����Ҫ���ݸ���ʱ������
// ����˵��     pass        �ж��Ƿ񴥷�����
// ����˵��     *file       �ļ���
// ����˵��     line        Ŀ������
// ���ز���     void
//-------------------------------------------------------------------------------------------------------------------
static void debug_delay (void)
{
    vuint32 loop_1 = 0, loop_2 = 0;
    for(loop_1 = 0; loop_1 <= 0xFF; loop_1 ++)
        for(loop_2 = 0; loop_2 <= 0xFFFF; loop_2 ++)
            __NOP();
}


//-------------------------------------------------------------------------------------------------------------------
// �������     debug �������� ��Ҫ�Ƿ�ֹ���Ժ�����ź�ά�ֶ�����Ӳ��ʧ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_protective_handler();
// ��ע��Ϣ     ���������ļ��ڲ����� �û����ù�ע Ҳ�����޸�
//-------------------------------------------------------------------------------------------------------------------
static void debug_protective_handler (void)
{
   // ��δ����
}

//-------------------------------------------------------------------------------------------------------------------
// �������      debug ��������ӿ� �˲��ֲ������û�����
// ����˵��     *str        ��Ҫ������ַ���
// ���ز���     void
// ʹ��ʾ��     debug_uart_str_output("Log message");
// ��ע��Ϣ     ���������ļ��ڲ����� �û����ù�ע Ҳ�����޸�
//-------------------------------------------------------------------------------------------------------------------
static void debug_uart_str_output (const char *str)
{
    uart_write_string(DEBUG_UART_INDEX, str);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     debug ����ӿ�
// ����˵��     *type       log ����
// ����˵��     *file       �ļ���
// ����˵��     line        Ŀ������
// ����˵��     *str        ��Ϣ
// ���ز���     void
// ʹ��ʾ��     debug_output("Log message", file, line, str);
// ��ע��Ϣ     ���������ļ��ڲ����� �û����ù�ע Ҳ�����޸�
//-------------------------------------------------------------------------------------------------------------------
static void debug_output (char *type, char *file, int line, char *str)
{
    char *file_str;
    vuint16 i = 0, j = 0;
    vint16 len_origin = 0;
    vint16 show_len = 0;
    vint16 show_line_index = 0;
    len_origin = strlen(file);

    char output_buffer[256];
    char file_path_buffer[64];

    if(debug_output_info.type_index)
    {
        debug_output_info.output_screen_clear();
    }

    if(zf_debug_init_flag)
    {
        if(debug_output_info.type_index)
        {
            // ��Ҫ���н��ļ���·�����������
            // <���������·�� ֻ���һ��Ŀ¼ ���� src/main.c>
            // ��� line : xxxx
            debug_output_info.output_screen(0, show_line_index ++, type);

            file_str = file;
            len_origin = strlen(file);
            show_len = (debug_output_info.display_x_max / debug_output_info.font_x_size);

            while(*file_str++ != '\0');

            // ֻȡһ��Ŀ¼ ����ļ������̷���Ŀ¼ ���� MDK �Ĺ��̸�Ŀ¼ �ͻ�ֱ�������ǰĿ¼
            for(j = 0; (j < 2) && (len_origin >= 0); len_origin --)             // �������� '/'
            {
                file_str --;
                if((*file_str == '/') || (*file_str == 0x5C))
                {
                    j ++;
                }
            }

            // �ļ�·�����浽������
            if(len_origin >= 0)
            {
                file_str ++;
                sprintf(output_buffer, "file: %s", file_str);
            }
            else
            {
                if(0 == j)
                {
                    sprintf(output_buffer, "file: mdk/%s", file_str);
                }
                else
                {
                    sprintf(output_buffer, "file: %s", file_str);
                }
            }

            // ��Ļ��ʾ·��
            for(i = 0; i < ((strlen(output_buffer) / show_len) + 1); i ++)
            {
                for(j = 0; j < show_len; j ++)
                {
                    if(strlen(output_buffer) < (j + i * show_len))
                    {
                        break;
                    }
                    file_path_buffer[j] = output_buffer[j + i * show_len];
                }

                file_path_buffer[j] = '\0';                                     // ĩβ���\0

                debug_output_info.output_screen(0, debug_output_info.font_y_size * show_line_index ++, file_path_buffer);
            }

            // ��Ļ��ʾ�к�
            sprintf(output_buffer, "line: %d", line);
            debug_output_info.output_screen(0, debug_output_info.font_y_size * show_line_index ++, output_buffer);

            // ��Ļ��ʾ Log ����еĻ�
            if(NULL != str)
            {
                for(i = 0; i < ((strlen(str) / show_len) + 1); i ++)
                {
                    for(j = 0; j < show_len; j ++)
                    {
                        if(strlen(str) < (j + i * show_len))
                        {
                            break;
                        }
                        file_path_buffer[j] = str[j + i * show_len];
                    }

                    file_path_buffer[j] = '\0';                                 // ĩβ���\0

                    debug_output_info.output_screen(0, debug_output_info.font_y_size * show_line_index ++, file_path_buffer);
                }
            }
        }
        else
        {
            char output_buffer[256];
            memset(output_buffer, 0, 256);
            debug_output_info.output_uart(type);
            if(NULL != str)
            {
                sprintf(output_buffer, "\r\nfile %s line %d: %s.\r\n", file, line, str);
            }
            else
            {
                sprintf(output_buffer, "\r\nfile %s line %d.\r\n", file, line);
            }
            debug_output_info.output_uart(output_buffer);
        }
    }
}

#if DEBUG_UART_USE_INTERRUPT                                                    // �������� ֻ�������ô����жϲű���

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ debug ���λ���������
// ����˵��     *data       �������ݴ�ŵ�����ָ��
// ���ز���     uint32      �������ݵ�ʵ�ʳ���
// ʹ��ʾ��     uint8 data[64]; uint32 len = debug_read_ring_buffer(data);
// ��ע��Ϣ     ��������Ҫ���� DEBUG_UART_USE_INTERRUPT �궨��ſ�ʹ��
//-------------------------------------------------------------------------------------------------------------------
uint32 debug_read_ring_buffer (uint8 *data)
{
    uint32 data_len = sizeof(data);
    fifo_read_buffer(&debug_uart_fifo, data, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     debug �����жϴ����� isr.c �ж�Ӧ�����жϷ���������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_interrupr_handler();
// ��ע��Ϣ     ��������Ҫ���� DEBUG_UART_USE_INTERRUPT �궨��ſ�ʹ��
//              ���ұ�����Ĭ�Ϸ����� UART1 �Ĵ��ڽ����жϴ���
//-------------------------------------------------------------------------------------------------------------------
void debug_interrupr_handler (void)
{
    if(zf_debug_init_flag)
    {
        uart_query_byte(DEBUG_UART_INDEX, &debug_uart_data);                    // ��ȡ��������
        fifo_write_buffer(&debug_uart_fifo, &debug_uart_data, 1);               // ���� FIFO
    }
}

#endif

//-------------------------------------------------------------------------     // printf �ض��� �˲��ֲ������û�����
//-------------------------------------------------------------------------------------------------------------------
// �������     printf�ض���
// ����˵��     void
// ���ز���     void
//  @since      v1.0
// ��ע��Ϣ              �ض���printf��DEBUG������
//-------------------------------------------------------------------------------------------------------------------
#if (1 == PRINTF_ENABLE)
int _write(int fd, char *buf, int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        while (USART_GetFlagStatus((USART_TypeDef*)uart_index[DEBUG_UART_INDEX], USART_FLAG_TC) == RESET);
        USART_SendData((USART_TypeDef*)uart_index[DEBUG_UART_INDEX], *buf++);
    }
    return size;
}
#endif
//-------------------------------------------------------------------------     // printf �ض��� �˲��ֲ������û�����

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ö���
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_assert_enable();
// ��ע��Ϣ     ����Ĭ�Ͽ��� ���鿪������
//-------------------------------------------------------------------------------------------------------------------
void debug_assert_enable (void)
{
    zf_debug_assert_enable = 1;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      ���ö���
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_assert_disable();
// ��ע��Ϣ     ����Ĭ�Ͽ��� ��������ö���
//-------------------------------------------------------------------------------------------------------------------
void debug_assert_disable (void)
{
    zf_debug_assert_enable = 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      debug ���Դ����� �˲��ֲ������û�����
// ����˵��     pass        �ж��Ƿ񴥷�����
// ����˵��     *file       �ļ���
// ����˵��     line        Ŀ������
// ���ز���     void
// ʹ��ʾ��     zf_assert(0);
// ��ע��Ϣ     �����������ֱ�ӵ��õ� �˲��ֲ������û�����
//              ʹ�� zf_commmon_debug.h �е� zf_assert(x) �ӿ�
//-------------------------------------------------------------------------------------------------------------------
void debug_assert_handler (uint8 pass, char *file, int line)
{
    do
    {
       if(pass || !zf_debug_assert_enable)
       {
           break;
       }

       static uint8 assert_nest_index = 0;

       if(0 != assert_nest_index)
       {
           while(1);
       }
       assert_nest_index ++;

       interrupt_global_disable();
       debug_protective_handler();

       while(1)
       {
           // ���������ת������ͣס��
           // һ����ĺ����������ݳ�����
           // �������Լ����õ� zf_assert(x) �ӿڴ�������

           // ��������� debug_init ��ʼ���� log ���
           // ���ڶ�Ӧ�������ȥ�鿴���ĸ��ļ�����һ�б���

           // ���û�г�ʼ�� debug
           // �ǾͿ������ file ���ַ���ֵ�� line ������
           // �Ǵ�������ļ�·�����ƺͶ�Ӧ��������

           // ��ȥ���Կ�����Ϊʲô��������

           debug_output("Assert error", file, line, NULL);
           debug_delay();
       }
   }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������      debug ������Ϣ������ �˲��ֲ������û�����
// ����˵��     bool        �ж��Ƿ񴥷�����
// ����˵��     *str        Ҫ����ĵ�����Ϣ
// ����˵��     *file       �ļ���
// ����˵��     line        Ŀ������
// ���ز���     void
// ʹ��ʾ��     zf_log(0, "Log Message");
// ��ע��Ϣ     �����������ֱ�ӵ��õ� �˲��ֲ������û�����
//              ʹ�� zf_commmon_debug.h �е� zf_log(x, str) �ӿ�
//-------------------------------------------------------------------------------------------------------------------
void debug_log_handler (uint8 pass, char *str, char *file, int line)
{
    do
    {
        if(pass)
        {
            break;
        }
        if(zf_debug_init_flag)
        {
            debug_output("Log message", file, line, str);
//            printf("Log message from %s line %d :\"%s\".\r\n", file, line, str);
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������      debug �������Ϣ��ʼ�� �˲��ֲ������û�����
// ����˵��     *info       debug �������Ϣ�ṹ��
// ���ز���     void
// Sample usage:            debug_output_struct_init(info);
//-------------------------------------------------------------------------------------------------------------------
void debug_output_struct_init (debug_output_struct *info)
{
    info->type_index            = 0;

    info->display_x_max         = 0xFFFF;
    info->display_y_max         = 0xFFFF;

    info->font_x_size           = 0xFF;
    info->font_y_size           = 0xFF;

    info->output_uart           = NULL;
    info->output_screen         = NULL;
    info->output_screen_clear   = NULL;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      debug ����󶨳�ʼ�� �˲��ֲ������û�����
// ����˵��     *info       debug �������Ϣ�ṹ��
// ���ز���     void
// ʹ��ʾ��     debug_output_init(info);
// ��ע��Ϣ     �������һ�㲻���û�����
//-------------------------------------------------------------------------------------------------------------------
void debug_output_init (debug_output_struct *info)
{
    debug_output_info.type_index            = info->type_index;

    debug_output_info.display_x_max         = info->display_x_max;
    debug_output_info.display_y_max         = info->display_y_max;

    debug_output_info.font_x_size           = info->font_x_size;
    debug_output_info.font_y_size           = info->font_y_size;

    debug_output_info.output_uart           = info->output_uart;
    debug_output_info.output_screen         = info->output_screen;
    debug_output_info.output_screen_clear   = info->output_screen_clear;

    zf_debug_init_flag = 1;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      debug ���ڳ�ʼ�� �˲��ֲ������û�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_init();
// ��ע��Ϣ     ��Դ��ʾ��Ĭ�ϵ��� ��Ĭ�Ͻ����жϽ���
//-------------------------------------------------------------------------------------------------------------------
void debug_init (void)
{
    debug_output_struct info;
    debug_output_struct_init(&info);
    info.output_uart = debug_uart_str_output;
    debug_output_init(&info);

    uart_init(
        DEBUG_UART_INDEX,                                                       // �� zf_common_debug.h �в鿴��Ӧֵ
        DEBUG_UART_BAUDRATE,                                                    // �� zf_common_debug.h �в鿴��Ӧֵ
        DEBUG_UART_TX_PIN,                                                      // �� zf_common_debug.h �в鿴��Ӧֵ
        DEBUG_UART_RX_PIN);                                                     // �� zf_common_debug.h �в鿴��Ӧֵ

#if DEBUG_UART_USE_INTERRUPT                                                    // �������� ֻ�������ô����жϲű���
    fifo_init(&debug_uart_fifo, FIFO_DATA_8BIT, debug_uart_buffer, DEBUG_RING_BUFFER_LEN);
    uart_rx_interrupt(DEBUG_UART_INDEX, 1);                                     // ʹ�ܶ�Ӧ���ڽ����ж�
#endif
}





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
* �ļ�����          zf_common_clock
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


#ifndef _zf_common_clock_h_
#define _zf_common_clock_h_

#include "ch32v30x.h"
#include "zf_common_typedef.h"

#define BOARD_XTAL_FREQ         8000000                                         // ����Ƶ�� ����Լ��õĲ������Ƶ�ʾ��޸����� UM ���巶ΧΪ 4-24Mhz
//#define XTAL_STARTUP_TIMEOUT    0x0800                                          // ��������ȴ���ʱʱ��

typedef enum
{
    SYSTEM_CLOCK_XTAL       = BOARD_XTAL_FREQ,                                  // ʹ�þ���Ƶ����Ϊʱ��Ƶ��
    SYSTEM_CLOCK_24M        = 24000000,                                         // 24Mhz
    SYSTEM_CLOCK_48M        = 48000000,                                         // 48Mhz
    SYSTEM_CLOCK_72M        = 72000000,                                         // 72Mhz
    SYSTEM_CLOCK_96M        = 96000000,                                         // 96Mhz
    SYSTEM_CLOCK_120M       = 120000000,                                        // 120Mhz
    SYSTEM_CLOCK_144M       = 144000000,                                        // 144Mhz
}system_clock_enum;

extern uint32 system_clock;                                                   // ȫ�ֱ��� ϵͳʱ����Ϣ

void clock_init (uint32 clock);                                               // ����ʱ�ӳ�ʼ��

#endif

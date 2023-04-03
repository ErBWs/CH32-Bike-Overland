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
* �ļ�����          zf_driver_delay
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

#ifndef _zf_driver_flash_h
#define _zf_driver_flash_h

#include "ch32v30x.h"
#include "ch32v30x_flash.h"
#include "zf_common_typedef.h"

#define FLASH_BASE_ADDR             (0x08000000)                // FALSH�׵�ַ
#define FLASH_MAX_PAGE_INDEX        (3)
#define FLASH_MAX_SECTION_INDEX     (63)
#define FLASH_PAGE_SIZE             (0x00000400)                // 1K byte
#define FLASH_SECTION_SIZE          (FLASH_PAGE_SIZE*4)         // 4K byte
#define FLASH_OPERATION_TIME_OUT    0x0FFF

#define FLASH_DATA_BUFFER_SIZE      (FLASH_PAGE_SIZE/sizeof(flash_data_union))  // �Զ�����ÿ��ҳ�ܹ����¶��ٸ�����

typedef union                                                                   // �̶������ݻ��嵥Ԫ��ʽ
{
    float   float_type;                                                       // float  ����
    uint32  uint32_type;                                                      // uint32 ����
    int32   int32_type;                                                       // int32  ����
    uint16  uint16_type;                                                      // uint16 ����
    int16   int16_type;                                                       // int16  ����
    uint8   uint8_type;                                                       // uint8  ����
    int8    int8_type;                                                        // int8   ����
}flash_data_union;                                                              // �����������ݹ���ͬһ�� 32bit ��ַ


/*
     ����Դ��ʹ�õ���64K RAM+ 256KFLASH
  flash���� һ��64��������һ������4K��
*/


extern flash_data_union flash_union_buffer[FLASH_DATA_BUFFER_SIZE];

uint8   flash_check                         (uint32 sector_num, uint32 page_num);
uint8   flash_erase_sector                  (uint32 sector_num, uint32 page_num);
void    flash_read_page                     (uint32 sector_num, uint32 page_num, uint32 *buf, uint16 len);
uint8   flash_write_page                    (uint32 sector_num, uint32 page_num, const uint32 *buf, uint16 len);

void    flash_read_page_to_buffer           (uint32 sector_num, uint32 page_num);
uint8   flash_write_page_from_buffer        (uint32 sector_num, uint32 page_num);
void    flash_buffer_clear                  (void);

#endif

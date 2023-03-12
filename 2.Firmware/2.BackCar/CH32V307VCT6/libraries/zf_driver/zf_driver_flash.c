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
* �ļ�����          zf_driver_flash
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



#include "zf_common_debug.h"
#include "zf_common_interrupt.h"

#include "zf_driver_flash.h"

flash_data_union flash_union_buffer[FLASH_DATA_BUFFER_SIZE];               // FLASH ���������ݻ�����

//-------------------------------------------------------------------------------------------------------------------
// �������     У�� FLASH �Ƿ�������
// ����˵��     sector_num      ��Ҫд���������� ������Χ <0 - 63>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <0 - 3>
// ���ز���     uint8           1-������ 0-û������ �����Ҫ�������ݵ�����д���µ�������Ӧ�ö������������в�������
// ʹ��ʾ��     flash_check(63, 3);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_check (uint32 sector_num, uint32 page_num)
{
    zf_assert(sector_num <= FLASH_MAX_SECTION_INDEX);                                                   // ������Χ 0-63
    zf_assert(page_num <= FLASH_MAX_PAGE_INDEX);                                                        // ������Χ 0-3

    uint8 return_state = 0;
    uint16 temp_loop;
    uint32 flash_addr = ((FLASH_BASE_ADDR+FLASH_SECTION_SIZE*sector_num+FLASH_PAGE_SIZE*page_num));     // ��ȡ��ǰ Flash ��ַ

    for(temp_loop = 0; temp_loop < FLASH_PAGE_SIZE; temp_loop+=4)                                       // ѭ����ȡ Flash ��ֵ
    {
        if( (*(__IO u32*) (flash_addr+temp_loop)) != 0x39E339E3 )                                       // �õ�Ƭ��������������� 0x39E339E3 �Ǿ�����ֵ
        {
            return_state = 1;
            break;
        }
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������
// ����˵��     sector_num      ��Ҫд���������� ������Χ <0 - 63>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <0 - 3>
// ���ز���     uint8           1-��ʾʧ�� 0-��ʾ�ɹ�
// ʹ��ʾ��     flash_erase_page(63, 3);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_erase_page (uint32 sector_num, uint32 page_num)
{
    zf_assert(sector_num <= FLASH_MAX_SECTION_INDEX);                                                   // ������Χ 0-63
    zf_assert(page_num <= FLASH_MAX_PAGE_INDEX);                                                        // ������Χ 0-3

    uint8 return_state = 0;

    static volatile FLASH_Status gFlashStatus = FLASH_COMPLETE;
    uint32 flash_addr = ((FLASH_BASE_ADDR+FLASH_SECTION_SIZE*sector_num+FLASH_PAGE_SIZE*page_num));     // ��ȡ��ǰ Flash ��ַ

    FLASH_Unlock();                                                                                     // ���� Flash
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);                           // ���������־
    gFlashStatus = FLASH_ErasePage(flash_addr);                                                         // ����
    FLASH_ClearFlag(FLASH_FLAG_EOP );                                                                   // ���������־
    FLASH_Lock();                                                                                       // ���� Flash
    if(gFlashStatus != FLASH_COMPLETE)          // �жϲ����Ƿ�ɹ�
    {
        return_state = 1;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡһҳ
// ����˵��     sector_num      ��Ҫд���������� ������Χ <0 - 63>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <0 - 3>
// ����˵��     buf             ��Ҫ��ȡ�����ݵ�ַ   ������������ͱ���Ϊuint32
// ����˵��     len             ��Ҫд������ݳ���   ������Χ 1-256
// ���ز���     void
// ʹ��ʾ��     flash_read_page(63, 3, data_buffer, 256);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void flash_read_page (uint32 sector_num, uint32 page_num, uint32 *buf, uint16 len)
{
    zf_assert(sector_num <= FLASH_MAX_SECTION_INDEX);                                                   // ������Χ 0-63
    zf_assert(page_num <= FLASH_MAX_PAGE_INDEX);                                                        // ������Χ 0-3
    zf_assert(len <= FLASH_DATA_BUFFER_SIZE);

    uint16 temp_loop = 0;
    uint32 flash_addr = 0;
    flash_addr = ((FLASH_BASE_ADDR+FLASH_SECTION_SIZE*sector_num+FLASH_PAGE_SIZE*page_num));            // ��ȡ��ǰ Flash ��ַ

    for(temp_loop = 0; temp_loop < len; temp_loop++)                                                    // ����ָ�����ȶ�ȡ
    {
        *buf++ = *(__IO uint32*)(flash_addr+temp_loop*4);                                               // ѭ����ȡ Flash ��ֵ
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���һҳ
// ����˵��     sector_num      ��Ҫд���������� ������Χ <0 - 63>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <0 - 3>
// ����˵��     buf             ��Ҫд������ݵ�ַ   ������������ͱ���Ϊ uint32
// ����˵��     len             ��Ҫд������ݳ���   ������Χ 1-256
// ���ز���     uint8           1-��ʾʧ�� 0-��ʾ�ɹ�
// ʹ��ʾ��     flash_write_page(63, 3, data_buffer, 256);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_write_page (uint32 sector_num, uint32 page_num, const uint32 *buf, uint16 len)
{
    zf_assert(sector_num <= FLASH_MAX_SECTION_INDEX);                                                   // ������Χ 0-63
    zf_assert(page_num <= FLASH_MAX_PAGE_INDEX);                                                        // ������Χ 0-3
    zf_assert(len <= FLASH_DATA_BUFFER_SIZE);
    uint8 return_state = 0;
    static volatile FLASH_Status gFlashStatus = FLASH_COMPLETE;
    uint32 flash_addr = 0;
    flash_addr = ((FLASH_BASE_ADDR+FLASH_SECTION_SIZE*sector_num+FLASH_PAGE_SIZE*page_num));            // ��ȡ��ǰ Flash ��ַ

    if(flash_check(sector_num, page_num))                                                               // �ж��Ƿ������� ����������ı��� ��ֹ����û������д��
    {
        flash_erase_page(sector_num, page_num);                                                         // ������һҳ
    }

    uint32 primask = interrupt_global_disable();
    FLASH_Unlock();                                                                                     // ���� Flash
    while(len--)                                                                                        // ���ݳ���
    {
        gFlashStatus = FLASH_ProgramWord(flash_addr, *buf++);                                           // ���� 32bit д������
        if(gFlashStatus != FLASH_COMPLETE)                                                              // ����ȷ�ϲ����Ƿ�ɹ�
        {
            return_state = 1;
            break;
        }
        flash_addr += 4;                                                                                // ��ַ����
    }
    FLASH_Lock();                                                                                       // ���� Flash
    interrupt_global_enable(primask);

    return return_state;
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��ָ�� FLASH ��������ָ��ҳ���ȡ���ݵ�������
// ����˵��     sector_num      ��Ҫд���������� ������Χ <0 - 63>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <0 - 3>
// ���ز���     void
// ʹ��ʾ��     flash_read_page_to_buffer(63, 3);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void flash_read_page_to_buffer (uint32 sector_num, uint32 page_num)
{
    zf_assert(sector_num <= FLASH_MAX_SECTION_INDEX);                                                   // ������Χ 0-63
    zf_assert(page_num <= FLASH_MAX_PAGE_INDEX);                                                        // ������Χ 0-3
    uint16 temp_loop;
    uint32 flash_addr = ((FLASH_BASE_ADDR + FLASH_SECTION_SIZE*sector_num + FLASH_PAGE_SIZE*page_num)); // ��ȡ��ǰ Flash ��ַ

    for(temp_loop = 0; temp_loop < FLASH_DATA_BUFFER_SIZE; temp_loop++)                                 // ����ָ�����ȶ�ȡ
    {
        flash_union_buffer[temp_loop].uint32_type = *(__IO uint32*)(flash_addr+temp_loop*4);       // ѭ����ȡ Flash ��ֵ
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ָ�� FLASH ��������ָ��ҳ��д�뻺����������
// ����˵��     sector_num      ��Ҫд���������� ������Χ <0 - 63>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <0 - 3>
// ���ز���     uint8           1-��ʾʧ�� 0-��ʾ�ɹ�
// ʹ��ʾ��     flash_write_page_from_buffer(63, 3);
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_write_page_from_buffer (uint32 sector_num, uint32 page_num)
{
    zf_assert(sector_num <= FLASH_MAX_SECTION_INDEX);                                                   // ������Χ 0-63
    zf_assert(page_num <= FLASH_MAX_PAGE_INDEX);                                                        // ������Χ 0-3
    uint8 return_state = 0;

    static volatile FLASH_Status gFlashStatus = FLASH_COMPLETE;
    uint32 flash_addr = 0;
    uint16 len = 0;
    flash_addr = ((FLASH_BASE_ADDR+FLASH_SECTION_SIZE*sector_num+FLASH_PAGE_SIZE*page_num));            // ��ȡ��ǰ Flash ��ַ

    if(flash_check(sector_num, page_num))                                                               // �ж��Ƿ������� ����������ı��� ��ֹ����û������д��
        flash_erase_page(sector_num, page_num);                                                         // ������һҳ

    FLASH_Unlock();                                                                                     // ���� Flash
    while(len < FLASH_DATA_BUFFER_SIZE)                                                                 // ���ݳ���
    {
        gFlashStatus = FLASH_ProgramWord(flash_addr, flash_union_buffer[len].uint32_type);         // ���� 32bit д������
        if(gFlashStatus != FLASH_COMPLETE)                                                              // ����ȷ�ϲ����Ƿ�ɹ�
        {
            return_state = 1;
            break;
        }

        len++;                                                                                          // ��������
        flash_addr += 4;                                                                                // ��ַ����
    }
    FLASH_Lock();                                                                                       // ���� Flash
    return return_state;
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ������ݻ�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     flash_buffer_clear();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void flash_buffer_clear (void)
{
    memset(flash_union_buffer, 0xFF, FLASH_PAGE_SIZE);
}


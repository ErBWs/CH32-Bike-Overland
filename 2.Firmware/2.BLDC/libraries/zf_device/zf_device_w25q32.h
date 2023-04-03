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
* �ļ�����          zf_device_w25q32
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
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�                                  ��Ƭ���ܽ�
*                   //------------------Ӳ�� SPI ����------------------//
*                   SPC                 �鿴 zf_device_w25q32.h �� W25Q32_SPC_PIN �궨��
*                   SDI                 �鿴 zf_device_w25q32.h �� W25Q32_SDI_PIN �궨��
*                   SDO                 �鿴 zf_device_w25q32.h �� W25Q32_SDO_PIN �궨��
*                   CS                  �鿴 zf_device_w25q32.h �� W25Q32_CS_PIN �궨��
*                   //------------------Ӳ�� SPI ����------------------//
*                   ��Դ����
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_w25q32_h_
#define _zf_device_w25q32_h_

#include "zf_common_clock.h"
#include "zf_common_debug.h"

#include "zf_driver_delay.h"
#include "zf_driver_spi.h"
#include "zf_driver_soft_iic.h"


#define W25Q32_BASE_ADDR             (0x00000000)                   // W25Q32FALSH�׵�ַ
#define W25Q32_PAGE_SIZE             (0x00000100)                   // 256 byte
#define W25Q32_SECTION_SIZE          (W25Q32_PAGE_SIZE      *16)    // 4K byte
#define W25Q32_BLOCK_SIZE            (W25Q32_SECTION_SIZE   *16)    // 64K byte

//W25Q32��64���������64*65536 = 4194304 Byte��4194304/1024/1024 = 4MB,Ѱַ�ռ䣺0x000000~0x3FFFFF��

//����W25QXXϵ��FLASH��ͬ��
//��ͬ�ͺŵ�flash�в�ͬ�����Ŀ����W25Q16��32�����W25Q32��64������Դ����ƣ���ϸ�����ġ�
//3.2��W25QXXϵ��FLASHоƬ��ͬ�ͺŵ���ͬ���������ɶ����
//1��� = 16����
//1��� = 16 * 16 * 256�ֽڣ�Byte��= 65536Byte = 64KB��65536Byte/1024=64KB��
//1���� = 16ҳ
//1���� = 16 * 256��Byte��= 4096Byte = 4KB
//1ҳ = 256�ֽ�


// ö�� Flash ����  ��ö�ٶ��岻�����û��޸�
typedef enum
{
    W25Q32_BLOCK_00,
    W25Q32_BLOCK_01,
    W25Q32_BLOCK_02,
    W25Q32_BLOCK_03,
    W25Q32_BLOCK_04,
    W25Q32_BLOCK_05,
    W25Q32_BLOCK_06,
    W25Q32_BLOCK_07,
    W25Q32_BLOCK_08,
    W25Q32_BLOCK_09,
    W25Q32_BLOCK_10,
    W25Q32_BLOCK_11,
    W25Q32_BLOCK_12,
    W25Q32_BLOCK_13,
    W25Q32_BLOCK_14,
    W25Q32_BLOCK_15,
    W25Q32_BLOCK_16,
    W25Q32_BLOCK_17,
    W25Q32_BLOCK_18,
    W25Q32_BLOCK_19,
    W25Q32_BLOCK_20,
    W25Q32_BLOCK_21,
    W25Q32_BLOCK_22,
    W25Q32_BLOCK_23,
    W25Q32_BLOCK_24,
    W25Q32_BLOCK_25,
    W25Q32_BLOCK_26,
    W25Q32_BLOCK_27,
    W25Q32_BLOCK_28,
    W25Q32_BLOCK_29,
    W25Q32_BLOCK_30,
    W25Q32_BLOCK_31,
    W25Q32_BLOCK_32,
    W25Q32_BLOCK_33,
    W25Q32_BLOCK_34,
    W25Q32_BLOCK_35,
    W25Q32_BLOCK_36,
    W25Q32_BLOCK_37,
    W25Q32_BLOCK_38,
    W25Q32_BLOCK_39,
    W25Q32_BLOCK_40,
    W25Q32_BLOCK_41,
    W25Q32_BLOCK_42,
    W25Q32_BLOCK_43,
    W25Q32_BLOCK_44,
    W25Q32_BLOCK_45,
    W25Q32_BLOCK_46,
    W25Q32_BLOCK_47,
    W25Q32_BLOCK_48,
    W25Q32_BLOCK_49,
    W25Q32_BLOCK_50,
    W25Q32_BLOCK_51,
    W25Q32_BLOCK_52,
    W25Q32_BLOCK_53,
    W25Q32_BLOCK_54,
    W25Q32_BLOCK_55,
    W25Q32_BLOCK_56,
    W25Q32_BLOCK_57,
    W25Q32_BLOCK_58,
    W25Q32_BLOCK_59,
    W25Q32_BLOCK_60,
    W25Q32_BLOCK_61,
    W25Q32_BLOCK_62,
    W25Q32_BLOCK_63
}w25q32_block_enum;

// ö�� Flash ����  ��ö�ٶ��岻�����û��޸�
typedef enum
{
    W25Q32_SECTION_00,
    W25Q32_SECTION_01,
    W25Q32_SECTION_02,
    W25Q32_SECTION_03,
    W25Q32_SECTION_04,
    W25Q32_SECTION_05,
    W25Q32_SECTION_06,
    W25Q32_SECTION_07,
    W25Q32_SECTION_08,
    W25Q32_SECTION_09,
    W25Q32_SECTION_10,
    W25Q32_SECTION_11,
    W25Q32_SECTION_12,
    W25Q32_SECTION_13,
    W25Q32_SECTION_14,
    W25Q32_SECTION_15,
}w25q32_section_enum;

// ö�� Flash ҳ���� ��ö�ٶ��岻�����û��޸�
typedef enum
{
    W25Q32_PAGE_00,
    W25Q32_PAGE_01,
    W25Q32_PAGE_02,
    W25Q32_PAGE_03,
    W25Q32_PAGE_04,
    W25Q32_PAGE_05,
    W25Q32_PAGE_06,
    W25Q32_PAGE_07,
    W25Q32_PAGE_08,
    W25Q32_PAGE_09,
    W25Q32_PAGE_10,
    W25Q32_PAGE_11,
    W25Q32_PAGE_12,
    W25Q32_PAGE_13,
    W25Q32_PAGE_14,
    W25Q32_PAGE_15,
}w25q32_page_enum;

//====================================================Ӳ�� SPI ����====================================================
#define W25Q32_SPI_SPEED          system_clock/8                              // Ӳ�� SPI ����
#define W25Q32_SPI                SPI_3                                       // Ӳ�� SPI ��
#define W25Q32_SPC_PIN            SPI1_MAP1_SCK_B3                                 // Ӳ�� SPI SCK ����
#define W25Q32_SDI_PIN            SPI1_MAP1_MISO_B4                                // Ӳ�� SPI MOSI ����
#define W25Q32_SDO_PIN            SPI1_MAP1_MOSI_B5                                // Ӳ�� SPI MISO ����
//====================================================Ӳ�� SPI ����====================================================
#define W25Q32_CS_PIN             A15                                         // CS Ƭѡ����
#define W25Q32_CS(x)              (x? (gpio_high(W25Q32_CS_PIN)): (gpio_low(W25Q32_CS_PIN)))

#define W25Q32_TIMEOUT_COUNT      0x00FF

//================================================���� ICM20602 �ڲ���ַ================================================
#define W25Q32_WRITE_ENABLE             0x06
#define W25Q32_WRITE_DISABLE            0x04

#define W25Q32_READ_STATUS_REG_1        0x05
#define W25Q32_READ_STATUS_REG_2        0x35
#define W25Q32_READ_STATUS_REG_3        0x15
#define W25Q32_WRITE_STATUS_REG_1       0x01
#define W25Q32_WRITE_STATUS_REG_2       0x31
#define W25Q32_WRITE_STATUS_REG_3       0x11
#define W25Q32_PAGE_PROGRAM             0x02
#define W25Q32_READ_DATA                0x03
#define W25Q32_FAST_READ                0x0B
#define W25Q32_SECTOR_ERASE             0x20
#define W25Q32_32KB_BLOCK_ERASE         0x52
#define W25Q32_64KB_BLOCK_ERASE         0xD8
#define W25Q32_CHIP_ERASE               0xC7
#define W25Q32_SUSPEND                  0x75
#define W25Q32_RESUME                   0x7A
#define W25Q32_READ_UID                 0x4B
#define W25Q32_JEDEC_ID                 0x9F    // W25Q32 ����0xEF40
#define W25Q32_DEVICE_ID                0x90    // W25Q32 ����0xEF15
#define W25Q32_RESET_ENABLE             0x66
#define W25Q32_RESET_DEVICE             0x99
//================================================���� ICM20602 �ڲ���ַ================================================


void  w25q32_erase_chip(void);
uint8 w25q32_check          (w25q32_block_enum block_num, w25q32_section_enum sector_num, w25q32_page_enum page_num);
uint8 w25q32_erase_sector   (w25q32_block_enum block_num, w25q32_section_enum sector_num);

void  w25q32_read_page      (w25q32_block_enum block_num, w25q32_section_enum sector_num, w25q32_page_enum page_num,
        uint8 *buf, uint16 len);

void  w25q32_write_page     (w25q32_block_enum block_num, w25q32_section_enum sector_num, w25q32_page_enum page_num,
        uint8 *buf, uint16 len);
uint8 w25q32_init();

//SPI_FLASHдʹ��

#endif

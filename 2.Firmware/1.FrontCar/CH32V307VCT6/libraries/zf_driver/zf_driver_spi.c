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
* �ļ�����          zf_driver_spi
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
#include "zf_driver_spi.h"

const uint32 spi_index[3] = {SPI1_BASE, SPI2_BASE, SPI3_BASE};

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ�д 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     spi_write_8bit(SPI_1,0x11);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit (spi_index_enum spi_n, const uint8 dat)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = dat;                                   // ��������
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);    // ����Ϊ��
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ�д 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_write_8bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_array (spi_index_enum spi_n, const uint8 *dat, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = *(dat++);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ�д 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     spi_write_16bit(SPI_1,0x1101);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit (spi_index_enum spi_n, const uint16 dat)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((dat & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(dat & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ�д 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_write_16bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_array (spi_index_enum spi_n, const uint16 *dat, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((*dat & 0xFF00)>>8);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(*dat++ & 0x00FF);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ��򴫸����ļĴ���д 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     spi_write_8bit_register(SPI_1,0x11,0x01);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_register (spi_index_enum spi_n, const uint8 register_name, const uint8 dat)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = register_name;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = dat;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ��򴫸����ļĴ���д 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_write_8bit_registers(SPI_1,0x11,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_registers (spi_index_enum spi_n, const uint8 register_name, const uint8 *dat, uint32 len)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = register_name;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = *dat++;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ��򴫸����ļĴ���д 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     spi_write_16bit_register(SPI_1,0x1011,0x0101);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_register (spi_index_enum spi_n, const uint16 register_name, const uint16 dat)
{

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((register_name & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(register_name & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((dat & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(dat & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿ��򴫸����ļĴ���д 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_write_16bit_registers(SPI_1,0x1011,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_registers (spi_index_enum spi_n, const uint16 register_name, const uint16 *dat, uint32 len)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((register_name & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(register_name & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((*dat & 0xFF00)>>8);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(*dat++ & 0x00FF);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    }

}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڶ� 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ���ز���     uint8         ����
// ʹ��ʾ��     spi_read_8bit(SPI_1);
//-------------------------------------------------------------------------------------------------------------------
uint8 spi_read_8bit (spi_index_enum spi_n)
{
    uint8 dat = 0;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
    dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڶ� 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ���ͻ���������
// ���ز���     void
// ʹ��ʾ��     spi_read_8bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_8bit_array (spi_index_enum spi_n, uint8 *dat, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
        *dat++ = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڶ� 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ���ز���     uint16        ����
// ʹ��ʾ��     spi_read_16bit(SPI_1);
//-------------------------------------------------------------------------------------------------------------------
uint16 spi_read_16bit (spi_index_enum spi_n)
{
    uint16 dat = 0;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    dat = ((dat << 8)| ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR);

    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڶ� 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ���ͻ���������
// ���ز���     void
// ʹ��ʾ��     spi_read_16bit_array(SPI_1,data,64);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_16bit_array (spi_index_enum spi_n, uint16 *dat, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
        *dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
        *dat = ((*dat << 8)| ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR);
        dat++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڴӴ������ļĴ����� 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ���ز���     uint8         ����
// ʹ��ʾ��     spi_read_8bit_register(SPI_1,0x11);
 //-------------------------------------------------------------------------------------------------------------------
uint8 spi_read_8bit_register (spi_index_enum spi_n, const uint8 register_name)
{
    uint8 dat;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = register_name;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 2;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
    dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;


    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڴӴ������ļĴ����� 8bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ���ͻ���������
// ���ز���     void
// ʹ��ʾ��     spi_read_8bit_registers(SPI_1,0x11,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_8bit_registers (spi_index_enum spi_n, const uint8 register_name, uint8 *dat, uint32 len)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = register_name;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY));
        *dat++ = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڴӴ������ļĴ����� 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ���ز���     uint16        ����
// ʹ��ʾ��     spi_read_16bit_register(SPI_1,0x1011);
//-------------------------------------------------------------------------------------------------------------------
uint16 spi_read_16bit_register (spi_index_enum spi_n, const uint16 register_name)
{

    uint16 dat = 0;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((register_name & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(register_name & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
    //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
    dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
     while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
     //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
     dat = ((dat << 8)|  ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR);

     return dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڴӴ������ļĴ����� 16bit ����
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     register_name   �Ĵ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ���ͻ���������
// ���ز���     void
// ʹ��ʾ��     spi_read_16bit_registers(SPI_1,0x1101,data,32);
//-------------------------------------------------------------------------------------------------------------------
void spi_read_16bit_registers (spi_index_enum spi_n, const uint16 register_name, uint16 *dat, uint32 len)
{
    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)((register_name & 0xFF00)>>8);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (uint8)(register_name & 0x00FF);
    while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);

    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
        *dat = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;

        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = 0;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
        *dat = ((*dat << 8)|  ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR);
        dat++;
    }

}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI 8bit ���ݴ��� ���������������ͬʱ���е�
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     write_buffer    ���͵����ݻ�������ַ
// ����˵��     read_buffer     ��������ʱ���յ������ݵĴ洢��ַ(����Ҫ������ NULL)
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_transfer_8bit(SPI_1,buf,buf,1);
//-------------------------------------------------------------------------------------------------------------------
void spi_transfer_8bit (spi_index_enum spi_n,const uint8 *write_buffer, uint8 *read_buffer, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = *(write_buffer++);
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        if(read_buffer != NULL)
        {
            //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
            *read_buffer++ = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI 16bit ���ݴ��� ���������������ͬʱ���е�
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     write_buffer    ���͵����ݻ�������ַ
// ����˵��     read_buffer     ��������ʱ���յ������ݵĴ洢��ַ(����Ҫ������ NULL)
// ����˵��     len             ����������
// ���ز���     void
// ʹ��ʾ��     spi_transfer_16bit(SPI_1,buf,buf,1);
//-------------------------------------------------------------------------------------------------------------------
void spi_transfer_16bit (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 len)
{
    while(len--)
    {
        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (*write_buffer&0xFF00)>>8;
        while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
        if(read_buffer != NULL)
        {
            //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
            *read_buffer++ = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
        }

        ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR = (*write_buffer&0x00FF);
         while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_BSY) != RESET);
         if(read_buffer != NULL)
         {
             //while((((SPI_TypeDef *)(spi_index[spi_n]))->STATR & SPI_I2S_FLAG_RXNE) == RESET);
             *read_buffer = ((SPI_TypeDef *)(spi_index[spi_n]))->DATAR;
         }
         write_buffer++;
         read_buffer++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      SPI �ӿڳ�ʼ��
// ����˵��     spi_n           SPI ģ��� ���� zf_driver_spi.h �� spi_index_enum ö���嶨��
// ����˵��     mode            SPI ģʽ ���� zf_driver_spi.h �� spi_mode_enum ö���嶨��
// ����˵��     baud            ���� SPI �Ĳ����� ������ϵͳʱ�ӵ�һ�� �������ʻᱻ��������������
// ����˵��     sck_pin         ѡ�� SCK ���� ���� zf_driver_spi.h �� spi_pin_enum ö���嶨��
// ����˵��     mosi_pin        ѡ�� MOSI ���� ���� zf_driver_spi.h �� spi_pin_enum ö���嶨��
// ����˵��     miso_pin        ѡ�� MISO ���� ���� zf_driver_spi.h �� spi_pin_enum ö���嶨��
// ����˵��     cs_pin          ѡ�� CS ���� ���� zf_driver_gpio.h �� gpio_pin_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     spi_init(SPI_1, 0, 1*1000*1000, SPI1_SCK_A5, SPI1_MOSI_A7, SPI1_MISO_A6, A4);  //Ӳ��SPI��ʼ��  ģʽ0 ������Ϊ1Mhz
//-------------------------------------------------------------------------------------------------------------------
void spi_init(spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_pin_enum sck_pin, spi_pin_enum mosi_pin, spi_pin_enum miso_pin, gpio_pin_enum cs_pin)
{
    SPI_I2S_DeInit((SPI_TypeDef *)(spi_index[spi_n]));

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                                           // ��������ʹ��

    if(sck_pin == SPI1_MAP1_SCK_B3 && miso_pin == SPI1_MAP1_MISO_B4 && mosi_pin == SPI1_MAP1_MOSI_B5)
    {
        GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);
    }
    else if(sck_pin == SPI3_MAP1_SCK_C10 && miso_pin == SPI3_MAP1_MISO_C11 && mosi_pin == SPI3_MAP1_MOSI_C12)
    {
        GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);
    }

         if(SPI_1 == spi_n)   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);                // SPI1ʱ��ʹ��
    else if(SPI_2 == spi_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);                // SPI2ʱ��ʹ��
    else if(SPI_3 == spi_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);                // SPI3ʱ��ʹ��

    gpio_init(sck_pin  & 0xFF,  GPO, 1, SPEED_50MHZ|GPO_AF_PUSH_PULL);
    gpio_init(mosi_pin & 0xFF,  GPO, 1, SPEED_50MHZ|GPO_AF_PUSH_PULL);
    if(miso_pin != SPI_MISO_NULL)
    {
        gpio_init(miso_pin & 0xFF,  GPI, 1, SPEED_50MHZ|GPI_PULL_UP);
    }
    if(cs_pin != PIN_NULL)
    {
        gpio_init(cs_pin & 0xFF,  GPO, 0, SPEED_50MHZ|GPO_PUSH_PULL);
    }

    SPI_InitTypeDef  SPI_InitStructure = {0};
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;      // SPI����Ϊ˫��˫��ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                           // ����SPI����ģʽ:����Ϊ��SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                       // ����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ

    switch(mode)
    {
        case SPI_MODE0:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                      // ����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                    // ����ͬ��ʱ�ӵĵ�һ�������أ��������½������ݱ�����
        }break;
        case SPI_MODE1:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                      // ����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                    // ����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
        }break;
        case SPI_MODE2:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                     // ����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                    // ����ͬ��ʱ�ӵĵ�һ�������أ��������½������ݱ�����
        }break;
        case SPI_MODE3:
        {
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                     // ����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                    // ����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
        }break;
    }

    uint16 psc = 0;
    psc = system_clock / baud;                                              // �����Ƶֵ
    if((system_clock % baud)== 0)
    {
        psc = psc - 1;
    }
         if(psc >= 128) psc = SPI_BaudRatePrescaler_256;                    // CLK_0.5625M
    else if(psc >= 64)  psc = SPI_BaudRatePrescaler_128;                    // CLK_1.125M
    else if(psc >= 32)  psc = SPI_BaudRatePrescaler_64;                     // CLK_2.25M
    else if(psc >= 16)  psc = SPI_BaudRatePrescaler_32;                     // CLK_4.5M
    else if(psc >= 8)   psc = SPI_BaudRatePrescaler_16;                     // CLK_9M
    else if(psc >= 4)   psc = SPI_BaudRatePrescaler_8;                      // CLK_18M
    else if(psc >= 2)   psc = SPI_BaudRatePrescaler_4;                      // CLK_36M
    else if(psc >= 1)   psc = SPI_BaudRatePrescaler_2;                      // CLK_72M
    else zf_assert(0);

    SPI_InitStructure.SPI_BaudRatePrescaler = psc;                          // ���岨����Ԥ��Ƶ��ֵ
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                               // ����ģʽ��ʹ���������NSS����
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                      // ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI_InitStructure.SPI_CRCPolynomial = 7;                                // CRCֵ����Ķ���ʽ
    SPI_Init((SPI_TypeDef *)(spi_index[spi_n]), &SPI_InitStructure);        // ����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���

    SPI_Cmd(((SPI_TypeDef *)(spi_index[spi_n])), ENABLE);                   // ʹ��SPI����
}

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
* �ļ�����          zf_device_virtual_oscilloscope
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

#include "zf_device_virtual_oscilloscope.h"

uint8_t virtual_oscilloscope_data[10];

//-------------------------------------------------------------------------------------------------------------------
// @brief		CRC У�� �ڲ�ʹ�� �û��������
// @param		buff            ��Ҫ���� CRC ��������ݵ�ַ
// @param		crc_cnt			��Ҫ���� CRC ��������ݸ���
// @return		uint16          CRC У����
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
static uint16 crc_check (uint8 *buff, uint8 crc_cnt)
{
	uint16 crc_temp;
	uint8 i,j;
	crc_temp = 0xffff;

	for (i=0;i<crc_cnt; i++)
	{
		crc_temp ^= buff[i];
		for (j=0;j<8;j++)
		{
			if (crc_temp & 0x01)
				crc_temp = (crc_temp >>1) ^ 0xa001;
			else
				crc_temp = crc_temp >> 1;
		}
	}
	return(crc_temp);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		����ʾ��������ת������
// @param		data1			Ҫ���͵ĵ�һ������
// @param		data2			Ҫ���͵ĵڶ�������
// @param		data3			Ҫ���͵ĵ���������
// @param		data4			Ҫ���͵ĵ��ĸ�����
// @param		*dat			ת��֮�������ݵĵ�ַ
// @return		void
// ʹ��ʾ��     uint8_t data_buffer[10];
//                              virtual_oscilloscope_data_conversion(100,200,300,400, data_buffer);
//                              wireless_uart_send_buff(data_buffer, 10);
//-------------------------------------------------------------------------------------------------------------------
void virtual_oscilloscope_data_conversion (const int16 data1, const int16 data2, const int16 data3, const int16 data4)
{
	uint16 crc_16 = 0;

	virtual_oscilloscope_data[0] = (uint8)((uint16)data1&0xff);
	virtual_oscilloscope_data[1] = (uint8)((uint16)data1>>8);

	virtual_oscilloscope_data[2] = (uint8)((uint16)data2&0xff);
	virtual_oscilloscope_data[3] = (uint8)((uint16)data2>>8);

	virtual_oscilloscope_data[4] = (uint8)((uint16)data3&0xff);
	virtual_oscilloscope_data[5] = (uint8)((uint16)data3>>8);

	virtual_oscilloscope_data[6] = (uint8)((uint16)data4&0xff);
	virtual_oscilloscope_data[7] = (uint8)((uint16)data4>>8);

	crc_16  = crc_check(virtual_oscilloscope_data,8);
	virtual_oscilloscope_data[8] = (uint8)(crc_16&0xff);
	virtual_oscilloscope_data[9] = (uint8)(crc_16>>8);
}

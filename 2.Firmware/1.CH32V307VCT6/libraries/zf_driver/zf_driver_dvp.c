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
* �ļ�����          zf_driver_dvp
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

#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_dvp.h"

//vuint32 frame_cnt = 0;
//vuint32 addr_cnt = 0;
//vuint32 href_cnt = 0;

//-------------------------------------------------------------------------------------------------------------------
// �������     dvp�ӿ����ų�ʼ��
// ����˵��     dvp_d0��dvp_d0       ����ͷD0-D7����
// ����˵��     dvp_pclk            ����ͷPCLK����
// ����˵��     dvp_vsync           ����ͷvysnc����
// ����˵��     dvp_herf            ����ͷherf����
// ���ز���     void
// ʹ��ʾ��         �ڲ�ʹ�ã��û��������
//-------------------------------------------------------------------------------------------------------------------
void dvp_gpio_init(
        uint8 dvp_d0,uint8 dvp_d1,uint8 dvp_d2,uint8 dvp_d3,
        uint8 dvp_d4,uint8 dvp_d5,uint8 dvp_d6,uint8 dvp_d7,
        uint8 dvp_pclk,uint8 dvp_vsync,uint8 dvp_hsync)
{
    //DVP_D0 �� DVP_ D7
    gpio_init(dvp_d0, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d1, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d2, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d3, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d4, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d5, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d6, GPI, 0, GPI_PULL_UP);
    gpio_init(dvp_d7, GPI, 0, GPI_PULL_UP);
    //DVP_VSYNC
    gpio_init(dvp_vsync, GPI, 0, GPI_PULL_UP);
    //DVP_PCLK
    gpio_init(dvp_pclk,  GPI, 0, GPI_PULL_UP);
    //DVP_HSYNC
    gpio_init(dvp_hsync, GPI, 0, GPI_PULL_UP);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     dvp�ӿڳ�ʼ��
// ����˵��     *image0                ����buff0�ĵ�ַ
// ����˵��     *image1                ����buff1�ĵ�ַ
// ����˵��     col_len                �г���
// ����˵��     row_len                �г���
// ���ز���     void
// ʹ��ʾ��            �ڲ�ʹ�ã��û��������
//-------------------------------------------------------------------------------------------------------------------
void dvp_camera_init(uint32 *image0_addr, uint32 *image1_addr, uint16 col_len, uint16 row_len)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DVP, ENABLE);

    DVP->CR0 &= ~RB_DVP_MSK_DAT_MOD;

    /* VSYNC��HSYNC:High level active */
    DVP->CR0 |= RB_DVP_D8_MOD | RB_DVP_JPEG | RB_DVP_V_POLAR ;
    DVP->CR1 &= ~((RB_DVP_ALL_CLR)| RB_DVP_RCV_CLR);
    DVP->ROW_NUM = row_len;                    // rows����
    DVP->COL_NUM = col_len;                    // cols����

    DVP->DMA_BUF0 = (uint32)image0_addr;               //DMA addr0
    DVP->DMA_BUF1 = (uint32)image1_addr;               //DMA addr1


    /* Set frame capture rate */
    DVP->CR1 &= ~RB_DVP_FCRC;
    DVP->CR1 |= DVP_RATE_100P;  //100%

    // ����Ϊѭ���ɼ�ģʽ
    // DVP->CR1 |= RB_DVP_CM;



    //Interupt Enable
//    DVP->IER |= RB_DVP_IE_STR_FRM;
//    DVP->IER |= RB_DVP_IE_ROW_DONE;
    DVP->IER |= RB_DVP_IE_FRM_DONE;
//    DVP->IER |= RB_DVP_IE_FIFO_OV;
//    DVP->IER |= RB_DVP_IE_STP_FRM;


    DVP->CR1 |= RB_DVP_DMA_EN;  //enable DMA
    DVP->CR0 |= RB_DVP_ENABLE;  //enable DVP

    interrupt_set_priority(DVP_IRQn, 0x03);
    interrupt_enable(DVP_IRQn);

}


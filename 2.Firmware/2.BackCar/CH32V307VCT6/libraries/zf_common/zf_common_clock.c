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

#include "ch32v30x.h"
#include "zf_common_function.h"
#include "zf_common_interrupt.h"

#include "zf_common_clock.h"

uint32 system_clock = SYSTEM_CLOCK_144M;                               // ϵͳʱ����Ϣ

//-------------------------------------------------------------------------------------------------------------------
// �������      ����ʱ�ӻָ���ʼ���� �ڲ�����
// ����˵��     void
// ���ز���     void
//-------------------------------------------------------------------------------------------------------------------
static void clock_reset(void)
{
    RCC->CTLR  |= (uint32) 0x00000001;      //ʹ��HSI����
    RCC->CFGR0 &= (uint32) 0xF8FF0000;
    RCC->CTLR  &= (uint32) 0xFEF6FFFF;
    RCC->CTLR  &= (uint32) 0xFFFBFFFF;
    RCC->CFGR0 &= (uint32) 0xFF80FFFF;
    RCC->INTR   = (uint32) 0x009F0000;      // ���������жϲ��������λ
}

//-------------------------------------------------------------------------------------------------------------------
// �������      ����ʱ������
// ����˵��     clock           ʱ��Ƶ�� �Ƽ�ʹ�� zf_common_clock.h �� system_clock_enum �����ѡ��
// ���ز���     void
//-------------------------------------------------------------------------------------------------------------------
static void clock_set_freq(uint32 clock)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    RCC->CTLR |= ((uint32_t) RCC_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->CTLR & RCC_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CTLR & RCC_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t) 0x01;
    }
    else
    {
        HSEStatus = (uint32_t) 0x00;
    }

    if (HSEStatus == (uint32_t) 0x01)
    {

//        /* Enable Prefetch Buffer */
//        FLASH->ACTLR |= FLASH_ACTLR_PRFTBE; ((uint8_t)0x10)
//
//        /* Flash 2 wait state */
//        FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);   ((uint8_t)0x03)
//        FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_2;              ((uint8_t)0x02)

        /* HCLK = SYSCLK */
        RCC->CFGR0 |= (uint32_t) RCC_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR0 |= (uint32_t) RCC_PPRE2_DIV1;
        /* PCLK1 = HCLK */
        RCC->CFGR0 |= (uint32_t) RCC_PPRE1_DIV1;

        /*  PLL configuration: PLLCLK = HSE * ? = ? MHz */
        RCC->CFGR0 &= (uint32) ((uint32) ~(RCC_PLLSRC | RCC_PLLXTPRE
                | RCC_PLLMULL));

        if (clock == SYSTEM_CLOCK_144M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL18_EXTEN);
        else if (clock == SYSTEM_CLOCK_120M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL15_EXTEN);
        else if (clock == SYSTEM_CLOCK_96M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL12_EXTEN);
        else if (clock == SYSTEM_CLOCK_72M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL9_EXTEN);
        else if (clock == SYSTEM_CLOCK_48M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL6_EXTEN);
        else if (clock == SYSTEM_CLOCK_24M)
            RCC->CFGR0 |= (uint32) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE
                    | RCC_PLLMULL3_EXTEN);

        /* Enable PLL */
        RCC->CTLR |= RCC_PLLON;
        /* Wait till PLL is ready */
        while((RCC->CTLR & RCC_PLLRDY) == 0)
        {
        }
        /* Select PLL as system clock source */
        RCC->CFGR0 &= (uint32_t) ((uint32_t) ~(RCC_SW));
        RCC->CFGR0 |= (uint32_t) RCC_SW_PLL;
        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08)
        {
        }
    }
    else
    {
        while(1);
        // �ⲿ�����ȶ���ȱʧ ʱ������ʧ��
        /*
         * If HSE fails to start-up, the application will have wrong clock
         * configuration. User can add here some code to deal with this error
         */
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������      ����ʱ�ӳ�ʼ��
// ����˵��     clock           ʱ��Ƶ�� �Ƽ�ʹ�� zf_common_clock.h �� system_clock_enum �����ѡ��
// ���ز���     void
// ʹ��ʾ��     clock_init(SYSTEM_CLOCK_144M);                   // ��ʼ������ʱ��Ϊ 144MHz
//-------------------------------------------------------------------------------------------------------------------
void clock_init(uint32 clock)
{

    system_clock = clock;                                            // ��¼����ʱ��Ƶ��
    clock_reset();
    clock_set_freq(clock);

    interrupt_init();


}

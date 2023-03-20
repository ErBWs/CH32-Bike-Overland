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
* �ļ�����          zf_driver_gpio
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


GPIO_TypeDef *gpio_group[5] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};

//-------------------------------------------------------------------------------------------------------------------
// �������     GPIO�������
// ����˵��     pin         ���ź�ѡ������� (��ѡ��Χ�� common.h ��GPIO_PIN_enumö��ֵȷ��)
// ����˵��     dat         ���ŵĵ�ƽ״̬�����ʱ��Ч 0���͵�ƽ 1���ߵ�ƽ
// ���ز���     void
// ʹ��ʾ��     gpio_set_level(D0, 0);//D0����͵�ƽ
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_level(gpio_pin_enum pin, uint8 dat)
{
    if(dat)
    {
        gpio_high(pin);                                                         // ����ߵ�ƽ
    }
    else
    {
        gpio_low(pin);                                                          // ����͵�ƽ
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     GPIO״̬��ȡ
// ����˵��     pin         ѡ������� (��ѡ��Χ�� common.h ��GPIO_PIN_enumö��ֵȷ��)
// ���ز���     uint8       0���͵�ƽ 1���ߵ�ƽ
// ʹ��ʾ��     uint8 status = gpio_get_level(D0);//��ȡD0���ŵ�ƽ
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get_level(gpio_pin_enum pin)
{
    return ((gpio_group[(pin & 0xE0) >> 5]->INDR & (((uint16)0x0001) << (pin & 0x1F))) ? 1 : 0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     GPIO ��ת
// ����˵��     pin         ѡ������� (��ѡ��Χ�� common.h ��GPIO_PIN_enumö��ֵȷ��)
// ���ز���     void        
// ʹ��ʾ��     gpio_toggle_level(D5);//D5���ŵ�ƽ��ת
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle_level(gpio_pin_enum pin)
{
    uint8 io_group = (pin & 0xE0) >> 5;
    uint8 io_pin = pin & 0x1F;

    ((gpio_group[io_group]))->OUTDR ^= (uint16)(1 << io_pin);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     gpio ��������
// ����˵��     pin         ѡ������� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ����˵��     dir         ���ŵķ���   �����GPO   ���룺GPI
// ����˵��     mode        ���ŵ�ģʽ (��ѡ��Χ�� zf_driver_gpio.h �� gpio_mode_enum ö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     gpio_set_dir(D5, GPI, GPI_PULL_UP);                             // ���� D5 Ϊ��������
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_dir (gpio_pin_enum pin, gpio_dir_enum dir, gpio_mode_enum mode)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    uint8 io_group = (pin & 0xE0) >> 5;
    uint8 io_pin = pin & 0x1F;

    // �������ź�
    GPIO_InitStructure.GPIO_Pin = (uint16)(1 << io_pin);

    // ֻ�������Ҫ�����ٶ�
    if(GPO == dir)
    {
        if((uint16)mode >> 8 == 0) GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)(GPIO_Speed_50MHz);    // ��ֹû����д�������,Ĭ������50Mhz
        else GPIO_InitStructure.GPIO_Speed = (gpio_speed_enum)((uint16)mode >> 8);                           // �Ѿ���д�˸ò���������ֵ������
    }

    // ����ģʽ
    GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)((uint16)mode & 0xFF);
    GPIO_Init(gpio_group[io_group], &GPIO_InitStructure);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     GPIO��ʼ��
// ����˵��     pin         ѡ������� (��ѡ��Χ�� common.h ��GPIO_PIN_enumö��ֵȷ��)
// ����˵��     dir         ���ŵķ���   �����GPO   ���룺GPI
// ����˵��     dat         ���ų�ʼ��ʱ���õĵ�ƽ״̬�����ʱ��Ч 0���͵�ƽ 1���ߵ�ƽ
// ����˵��     pinconf     �������ã������ò�����zf_gpio.h�ļ���GPIOSPEED_enum��GPIOMODE_enumö��ֵȷ�����������ʹ�� | ���
// ���ز���     void
// ʹ��ʾ��     gpio_init(D0, GPO, 1, GPIO_PIN_CONFIG);//D0��ʼ��ΪGPIO���ܡ����ģʽ������ߵ�ƽ���ٶ�100MHZ �������
//-------------------------------------------------------------------------------------------------------------------
void gpio_init (gpio_pin_enum pin, gpio_dir_enum dir, const uint8 dat, gpio_mode_enum mode)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    uint8 io_group = (pin & 0xE0) >> 5;
    uint8 io_pin = pin & 0x1F;

    // GPIO����ʹ��
    if(0 == io_group)      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if(1 == io_group) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    else if(2 == io_group) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    else if(3 == io_group) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    else if(4 == io_group) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    // �������ź�
    GPIO_InitStructure.GPIO_Pin = (uint16)(1 << io_pin);

    // ֻ�������Ҫ�����ٶ�
    if(GPO == dir)
    {
        if((uint16)mode >> 8 == 0) GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)(GPIO_Speed_50MHz);    // ��ֹû����д�������,Ĭ������50Mhz
        else GPIO_InitStructure.GPIO_Speed = (gpio_speed_enum)((uint16)mode >> 8);                           // �Ѿ���д�˸ò���������ֵ������
    }

    // ����ģʽ
    GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)((uint16)mode & 0xFF);
    GPIO_Init(gpio_group[io_group], &GPIO_InitStructure);

    // ֻ�������Ҫ��������״̬
    if(GPO == dir)
    {
        GPIO_WriteBit(gpio_group[io_group], (uint16)(1 << io_pin), dat);
    }
}


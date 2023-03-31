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
* �ļ�����          zf_driver_encoder
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
#include "zf_driver_timer.h"
#include "zf_driver_encoder.h"


static volatile uint8 encoder_dir_pin[10] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʱ������������ȡֵ
// ����˵��     timer_ch      ��ʱ��ö����
// ���ز���     void
// ��ע��Ϣ
// ʹ��ʾ��    encoder_get_count(TIM2_ENCOEDER)  // ��ȡ��ʱ��2�Ĳɼ����ı���������
//-------------------------------------------------------------------------------------------------------------------
int16 encoder_get_count(encoder_index_enum encoder_n)
{
    int16 result = 0;
    int16 return_value = 0;
    switch(encoder_n)
    {
        case TIM1_ENCOEDER:  result = TIM1->CNT;   break;
        case TIM2_ENCOEDER:  result = TIM2->CNT;   break;
        case TIM3_ENCOEDER:  result = TIM3->CNT;   break;
        case TIM4_ENCOEDER:  result = TIM4->CNT;   break;
        case TIM5_ENCOEDER:  result = TIM5->CNT;   break;
        case TIM8_ENCOEDER:  result = TIM8->CNT;   break;
        case TIM9_ENCOEDER:  result = TIM9->CNT;   break;
        case TIM10_ENCOEDER: result = TIM10->CNT;  break;
        default:             result = 0;                 break;
    }
    if(0xFF == encoder_dir_pin[encoder_n])
    {
        return_value = result;
    }
    else
    {
        if(!gpio_get_level((gpio_pin_enum)encoder_dir_pin[encoder_n]))
        {
            return_value = -result;
        }
		else
		{
			return_value = result;
		}
    }

    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʱ���ļ��������
// ����˵��     timer_ch      ��ʱ��ö����
// ���ز���     void
// ��ע��Ϣ
// ʹ��ʾ��    encoder_clear_count(TIM1_ENCOEDER)  //�����ʱ��1�ɼ����ı���������
//-------------------------------------------------------------------------------------------------------------------
void encoder_clear_count(encoder_index_enum encoder_n)
{
    switch(encoder_n)
    {
        case TIM1_ENCOEDER:  TIM1->CNT  = 0;  break;
        case TIM2_ENCOEDER:  TIM2->CNT  = 0;  break;
        case TIM3_ENCOEDER:  TIM3->CNT  = 0;  break;
        case TIM4_ENCOEDER:  TIM4->CNT  = 0;  break;
        case TIM5_ENCOEDER:  TIM5->CNT  = 0;  break;
        case TIM8_ENCOEDER:  TIM8->CNT  = 0;  break;
        case TIM9_ENCOEDER:  TIM9->CNT  = 0;  break;
        case TIM10_ENCOEDER: TIM10->CNT = 0;  break;
        default:  break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �����������ʼ��
// ����˵��     timer_ch      ��ʱ��ö����
// ����˵��     phaseA      ͨ��A�Լ�����
// ����˵��     phaseB      ͨ��B�Լ�����
// ���ز���     void
// ��ע��Ϣ    �Ƽ�ʹ�����������������
// ʹ��ʾ��    encoder_init_quad(TIM1_ENCOEDER, TIM1_CH1_ENCOEDER_E9, TIM1_CH2_ENCOEDER_E11)
//          // ʹ�ö�ʱ��1 ���������������룬 ͨ��1���ź�E9��ͨ��2���ź�E11
//-------------------------------------------------------------------------------------------------------------------
void encoder_quad_init(encoder_index_enum encoder_n, encoder_channel_enum ch1_pin, encoder_channel_enum ch2_pin)
{
    uint32 register_temp = 0;
    TIM_TypeDef *tim_index;

    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
    // �����Ǽ���Ƿ����ظ�ʹ�ö�ʱ��
    // �����ʼ���� TIM1_PWM Ȼ���ֳ�ʼ���� TIM1_ENCODER �����÷��ǲ������
    zf_assert(timer_funciton_check((timer_index_enum)encoder_n, TIMER_FUNCTION_ENCODER));
    zf_assert((ch1_pin >> 12) == (encoder_n));                                  // ch1_pin �� ch2_pin ������ encoder_n ƥ��
    zf_assert((ch2_pin >> 12) == (encoder_n));                                  // ch1_pin �� ch2_pin ������ encoder_n ƥ��

    timer_clock_enable(encoder_n);                                              // ��ʱ��ʱ��ʹ��

    gpio_init((gpio_pin_enum)(ch1_pin & 0xFF), GPI, 0, GPI_PULL_UP);            // ��ʼ������
    gpio_init((gpio_pin_enum)(ch2_pin & 0xFF), GPI, 0, GPI_PULL_UP);            // ��ʼ������

    //encoder_dir_pin[encoder_n] = (ch1_pin &0xFF);                               // ���������źŴ���������

    switch(encoder_n)
    {
        case TIM1_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM1_BASE);   break;
        case TIM2_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM2_BASE);   break;
        case TIM3_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM3_BASE);   break;
        case TIM4_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM4_BASE);   break;
        case TIM5_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM5_BASE);   break;
        case TIM8_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM8_BASE);   break;
        case TIM9_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM9_BASE);   break;
        case TIM10_ENCOEDER: tim_index = ((TIM_TypeDef *)TIM10_BASE);  break;
        default: register_temp = 1;
    }

    // �������ù���
    if((ch1_pin >> 8) == 0x03)      GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,        ENABLE);
    else if((ch1_pin >> 8) == 0x11) GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,    ENABLE);
    else if((ch1_pin >> 8) == 0x22) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,     ENABLE);
    else if((ch1_pin >> 8) == 0x23) GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,        ENABLE);
    else if((ch1_pin >> 8) == 0x31) GPIO_PinRemapConfig(GPIO_Remap_TIM4,            ENABLE);
    else if((ch1_pin >> 8) == 0x71) GPIO_PinRemapConfig(GPIO_Remap_TIM8,            ENABLE);
    else if((ch1_pin >> 8) == 0x83) GPIO_PinRemapConfig(GPIO_FullRemap_TIM9,        ENABLE);
    else if((ch1_pin >> 8) == 0x91) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM10,    ENABLE);
    else if((ch1_pin >> 8) == 0x93) GPIO_PinRemapConfig(GPIO_FullRemap_TIM10,       ENABLE);

    if(!register_temp)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                // ʹ��AFIO���ù���ģ��ʱ��
        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
        TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
        TIM_TimeBaseStructure.TIM_Prescaler = 0;                            // Ԥ��Ƶ��
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                          // �趨�������Զ���װֵ
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             // ѡ��ʱ�ӷ�Ƶ������Ƶ
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         // TIM���ϼ���
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                    // �ظ�������
        TIM_TimeBaseInit(tim_index, &TIM_TimeBaseStructure);                // ��ʼ���ṹ��
        TIM_ITRxExternalClockConfig(tim_index, TIM_TS_TI2FP2);              // �����ⲿ���������򲻻����
        TIM_Cmd(tim_index, ENABLE);                                         // ��ʱ��ʹ��

        TIM_EncoderInterfaceConfig(
                tim_index,
                TIM_EncoderMode_TI2 ,
                TIM_ICPolarity_Rising,
                TIM_ICPolarity_Rising);                                     // ʹ�ñ�����ģʽ, T2���� ,T1�жϷ���, �����ؼ���

        TIM_Cmd(tim_index, ENABLE);                                         // ��ʱ��ʹ��

    }

}


//-------------------------------------------------------------------------------------------------------------------
// �������     �����������ʼ��
// ����˵��     timer_ch        ��ʱ��ö����
// ����˵��     phaseA          ͨ��A�Լ�����
// ����˵��     phaseB          ͨ��B�Լ�����
// ���ز���     void
//          �Ƽ�ʹ�����������������
// ʹ��ʾ��      encoder_init_dir(TIM1_ENCOEDER, TIM1_CH1_ENCOEDER_E9, TIM1_CH2_ENCOEDER_E11)
//                              // ʹ�ö�ʱ��1 ��������ı��������룬 ͨ��1�����ź�����E9��ͨ��2�����ź�����E11
//-------------------------------------------------------------------------------------------------------------------
void encoder_dir_init(encoder_index_enum encoder_n, encoder_channel_enum ch1_pin, encoder_channel_enum ch2_pin)
{
    uint32 register_temp = 0;
    TIM_TypeDef *tim_index;

    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
    // �����Ǽ���Ƿ����ظ�ʹ�ö�ʱ��
    // �����ʼ���� TIM1_PWM Ȼ���ֳ�ʼ���� TIM1_ENCODER �����÷��ǲ������
    zf_assert(timer_funciton_check((timer_index_enum)encoder_n, TIMER_FUNCTION_ENCODER));
    zf_assert((ch1_pin & (encoder_n << 12)) == (encoder_n << 12));              // ch1_pin �� ch2_pin ������ encoder_n ƥ��
    zf_assert((ch2_pin & (encoder_n << 12)) == (encoder_n << 12));              // ch1_pin �� ch2_pin ������ encoder_n ƥ��

    timer_clock_enable(encoder_n);                                              // ��ʱ��ʱ��ʹ��

    gpio_init((gpio_pin_enum)(ch1_pin & 0xFF), GPI, 0, GPI_PULL_UP);            // ��ʼ������
    gpio_init((gpio_pin_enum)(ch2_pin & 0xFF), GPI, 0, GPI_PULL_UP);            // ��ʼ������

    encoder_dir_pin[encoder_n] = (ch1_pin &0xFF);                               // ���������źŴ���������

    switch(encoder_n)
    {
        case TIM1_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM1_BASE);   break;
        case TIM2_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM2_BASE);   break;
        case TIM3_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM3_BASE);   break;
        case TIM4_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM4_BASE);   break;
        case TIM5_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM5_BASE);   break;
        case TIM8_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM8_BASE);   break;
        case TIM9_ENCOEDER:  tim_index = ((TIM_TypeDef *)TIM9_BASE);   break;
        case TIM10_ENCOEDER: tim_index = ((TIM_TypeDef *)TIM10_BASE);  break;
        default: register_temp = 1;
    }

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                // ʹ��AFIO���ù���ģ��ʱ��

    // �������ù���
    if((ch1_pin >> 8) == 0x03)      GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,        ENABLE);
    else if((ch1_pin >> 8) == 0x11) GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,    ENABLE);
    else if((ch1_pin >> 8) == 0x22) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,     ENABLE);
    else if((ch1_pin >> 8) == 0x23) GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,        ENABLE);
    else if((ch1_pin >> 8) == 0x31) GPIO_PinRemapConfig(GPIO_Remap_TIM4,            ENABLE);
    else if((ch1_pin >> 8) == 0x71) GPIO_PinRemapConfig(GPIO_Remap_TIM8,            ENABLE);
    else if((ch1_pin >> 8) == 0x83) GPIO_PinRemapConfig(GPIO_FullRemap_TIM9,        ENABLE);
    else if((ch1_pin >> 8) == 0x91) GPIO_PinRemapConfig(GPIO_PartialRemap_TIM10,    ENABLE);
    else if((ch1_pin >> 8) == 0x93) GPIO_PinRemapConfig(GPIO_FullRemap_TIM10,       ENABLE);

    if(!register_temp)
    {

        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
        TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
        TIM_TimeBaseStructure.TIM_Prescaler = 0;                            // Ԥ��Ƶ��
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                          // �趨�������Զ���װֵ
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             // ѡ��ʱ�ӷ�Ƶ������Ƶ
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         // TIM���ϼ���
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                    // �ظ�������
        TIM_TimeBaseInit(tim_index, &TIM_TimeBaseStructure);                // ��ʼ���ṹ��
        TIM_ITRxExternalClockConfig(tim_index, TIM_TS_TI2FP2);              // �����ⲿ���������򲻻����
        TIM_Cmd(tim_index, ENABLE);                                         // ��ʱ��ʹ��
    }
}


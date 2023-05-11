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
* �ļ�����          isr
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

#include "zf_common_headfile.h"

#include "hall.h"
#include "pwm_output.h"
#include "pwm_input.h"
#include "led.h"
#include "operational_amplifier.h"
#include "comparator.h"
#include "motor.h"
#include "en_switch.h"
#include "encoder.h"
#include "move_filter.h"
#include "battery_adc.h"

void NMI_Handler(void)       __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

//void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void UART4_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void UART5_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void UART6_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void UART7_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void UART8_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void DVP_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM1_BRK_IRQHandler        (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM1_UP_IRQHandler         (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM1_TRG_COM_IRQHandler    (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM1_CC_IRQHandler         (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler            (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM3_IRQHandler            (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM4_IRQHandler            (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM5_IRQHandler            (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM6_IRQHandler            (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM7_IRQHandler            (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM8_BRK_IRQHandler        (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM8_UP_IRQHandler         (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM8_TRG_COM_IRQHandler    (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM8_CC_IRQHandler         (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM9_BRK_IRQHandler        (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM9_UP_IRQHandler         (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM9_TRG_COM_IRQHandler    (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM9_CC_IRQHandler         (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM10_BRK_IRQHandler       (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM10_UP_IRQHandler        (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
//void TIM10_TRG_COM_IRQHandler   (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM10_CC_IRQHandler        (void)  __attribute__((interrupt("WCH-Interrupt-fast")));

//void EXTI0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void EXTI1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void EXTI2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void EXTI3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void EXTI4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void EXTI9_5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void EXTI15_10_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));


void TIM2_IRQHandler(void)
{
    if (RESET != TIM_GetITStatus(TIM2, TIM_FLAG_CC2))
    {
        TIM_ClearFlag(TIM2, TIM_FLAG_CC2);
        pwm_input_trigger_callback(&motor1_pwm_input_value);

    }
    if (RESET != TIM_GetITStatus(TIM2, TIM_FLAG_CC4))
    {
        TIM_ClearFlag(TIM2, TIM_FLAG_CC4);
        pwm_input_timeout_callback(&motor1_pwm_input_value);
    }
}

void TIM3_IRQHandler(void)
{
    TIM3->CNT = 0;
    if (RESET != TIM_GetITStatus(TIM3, TIM_IT_Update))
    {
        TIM_ClearFlag(TIM3, TIM_IT_Update);
    }

    if (RESET != TIM_GetITStatus(TIM3, TIM_IT_CC1))
    {
        TIM_ClearFlag(TIM3, TIM_FLAG_CC1);


        // �����µĻ���ֵ
        motor_commutation_finished_callback(
                &motor2_hall,
                &motor2_control,
                &motor2_pwm_input_value,
                &motor2_pwm_output,
                &motor2_closed_loop,
                &motor2_enable_switch,
                &motor2_speed_filter
        );
    }

    if (RESET != TIM_GetITStatus(TIM3, TIM_IT_CC2))
    {
        TIM_ClearFlag(TIM3, TIM_FLAG_CC2);
//        // ����ʱ�䵽
//        motor_commutation_callback(&motor1_control, &motor1_pwm_output, &motor1_hall);
    }

    if (RESET != TIM_GetITStatus(TIM3, TIM_IT_CC3))
    {
        TIM_ClearFlag(TIM3, TIM_FLAG_CC3);
        // ���೬ʱ
        motor_commutation_timeout_callback(&motor2_control, &motor2_speed_filter);

    }
}

void TIM4_IRQHandler(void)
{
    TIM4->CNT = 0;

    if (RESET != TIM_GetITStatus(TIM4, TIM_IT_CC1))
    {
        TIM_ClearFlag(TIM4, TIM_FLAG_CC1);
        // �����µĻ���ֵ
        motor_commutation_finished_callback(
                &motor1_hall,
                &motor1_control,
                &motor1_pwm_input_value,
                &motor1_pwm_output,
                &motor1_closed_loop,
                &motor1_enable_switch,
                &motor1_speed_filter
        );
    }

    if (RESET != TIM_GetITStatus(TIM4, TIM_IT_CC2))
    {
        TIM_ClearFlag(TIM4, TIM_FLAG_CC2);
//        // ����ʱ�䵽
//        motor_commutation_callback(&motor2_control, &motor2_pwm_output, &motor2_hall);
    }

    if (RESET != TIM_GetITStatus(TIM4, TIM_IT_CC3))
    {
        TIM_ClearFlag(TIM4, TIM_FLAG_CC3);
        // ���೬ʱ
        motor_commutation_timeout_callback(&motor1_control, &motor1_speed_filter);
    }
}


void TIM6_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
       TIM_ClearITPendingBit(TIM6, TIM_IT_Update );

       motor_pit_control_callback(
                &motor1_hall,
                &motor1_control,
                &motor1_pwm_input_value,
                &motor1_pwm_output,
                &motor1_closed_loop,
                &motor1_enable_switch,
                &motor1_encoder_out
       );

       motor_pit_control_callback(
                &motor2_hall,
                &motor2_control,
                &motor2_pwm_input_value,
                &motor2_pwm_output,
                &motor2_closed_loop,
                &motor2_enable_switch,
                &motor2_encoder_out
       );

//       battery_adc_read();
    }
}


void TIM10_CC_IRQHandler(void)
{
    if (RESET != TIM_GetITStatus(TIM10, TIM_FLAG_CC1))
    {
        TIM_ClearFlag(TIM10, TIM_FLAG_CC1);
    }

    if (RESET != TIM_GetITStatus(TIM10, TIM_FLAG_CC2))
    {
        TIM_ClearFlag(TIM10, TIM_FLAG_CC2);
        pwm_input_trigger_callback(&motor2_pwm_input_value);
    }

    if (RESET != TIM_GetITStatus(TIM10, TIM_FLAG_CC3))
    {
        TIM_ClearFlag(TIM10, TIM_FLAG_CC3);
    }
    if (RESET != TIM_GetITStatus(TIM10, TIM_FLAG_CC4))
    {
        TIM_ClearFlag(TIM10, TIM_FLAG_CC4);
        pwm_input_timeout_callback(&motor2_pwm_input_value);
    }
}

//.section    .text.vector_handler, "ax", @progbits

//   .weak   EXTI0_IRQHandler           /* EXTI Line 0 */
//   .weak   EXTI1_IRQHandler           /* EXTI Line 1 */
//   .weak   EXTI2_IRQHandler           /* EXTI Line 2 */
//   .weak   EXTI3_IRQHandler           /* EXTI Line 3 */
//   .weak   EXTI4_IRQHandler           /* EXTI Line 4 */
//   .weak   DMA1_Channel1_IRQHandler   /* DMA1 Channel 1 */
//   .weak   DMA1_Channel2_IRQHandler   /* DMA1 Channel 2 */
//   .weak   DMA1_Channel3_IRQHandler   /* DMA1 Channel 3 */
//   .weak   DMA1_Channel4_IRQHandler   /* DMA1 Channel 4 */
//   .weak   DMA1_Channel5_IRQHandler   /* DMA1 Channel 5 */
//   .weak   DMA1_Channel6_IRQHandler   /* DMA1 Channel 6 */
//   .weak   DMA1_Channel7_IRQHandler   /* DMA1 Channel 7 */
//   .weak   ADC1_2_IRQHandler          /* ADC1_2 */
//   .weak   USB_HP_CAN1_TX_IRQHandler  /* USB HP and CAN1 TX */
//   .weak   USB_LP_CAN1_RX0_IRQHandler /* USB LP and CAN1RX0 */
//   .weak   CAN1_RX1_IRQHandler        /* CAN1 RX1 */
//   .weak   CAN1_SCE_IRQHandler        /* CAN1 SCE */
//   .weak   EXTI9_5_IRQHandler         /* EXTI Line 9..5 */
//   .weak   TIM1_BRK_IRQHandler        /* TIM1 Break */
//   .weak   TIM1_UP_IRQHandler         /* TIM1 Update */
//   .weak   TIM1_TRG_COM_IRQHandler    /* TIM1 Trigger and Commutation */
//   .weak   TIM1_CC_IRQHandler         /* TIM1 Capture Compare */
//   .weak   TIM2_IRQHandler            /* TIM2 */
//   .weak   TIM3_IRQHandler            /* TIM3 */
//   .weak   TIM4_IRQHandler            /* TIM4 */
//   .weak   I2C1_EV_IRQHandler         /* I2C1 Event */
//   .weak   I2C1_ER_IRQHandler         /* I2C1 Error */
//   .weak   I2C2_EV_IRQHandler         /* I2C2 Event */
//   .weak   I2C2_ER_IRQHandler         /* I2C2 Error */
//   .weak   SPI1_IRQHandler            /* SPI1 */
//   .weak   SPI2_IRQHandler            /* SPI2 */
//   .weak   USART1_IRQHandler          /* USART1 */
//   .weak   USART2_IRQHandler          /* USART2 */
//   .weak   USART3_IRQHandler          /* USART3 */
//   .weak   EXTI15_10_IRQHandler       /* EXTI Line 15..10 */
//   .weak   RTCAlarm_IRQHandler        /* RTC Alarm through EXTI Line */
//   .weak   USBWakeUp_IRQHandler       /* USB Wakeup from suspend */
//   .weak   TIM8_BRK_IRQHandler        /* TIM8 Break */
//   .weak   TIM8_UP_IRQHandler         /* TIM8 Update */
//   .weak   TIM8_TRG_COM_IRQHandler    /* TIM8 Trigger and Commutation */
//   .weak   TIM8_CC_IRQHandler         /* TIM8 Capture Compare */
//   .weak   RNG_IRQHandler             /* RNG */
//   .weak   FSMC_IRQHandler            /* FSMC */
//   .weak   SDIO_IRQHandler            /* SDIO */
//   .weak   TIM5_IRQHandler            /* TIM5 */
//   .weak   SPI3_IRQHandler            /* SPI3 */
//   .weak   UART4_IRQHandler           /* UART4 */
//   .weak   UART5_IRQHandler           /* UART5 */
//   .weak   TIM6_IRQHandler            /* TIM6 */
//   .weak   TIM7_IRQHandler            /* TIM7 */
//   .weak   DMA2_Channel1_IRQHandler   /* DMA2 Channel 1 */
//   .weak   DMA2_Channel2_IRQHandler   /* DMA2 Channel 2 */
//   .weak   DMA2_Channel3_IRQHandler   /* DMA2 Channel 3 */
//   .weak   DMA2_Channel4_IRQHandler   /* DMA2 Channel 4 */
//   .weak   DMA2_Channel5_IRQHandler   /* DMA2 Channel 5 */
//   .weak   ETH_IRQHandler             /* ETH */
//   .weak   ETH_WKUP_IRQHandler        /* ETH WakeUp */
//   .weak   CAN2_TX_IRQHandler         /* CAN2 TX */
//   .weak   CAN2_RX0_IRQHandler        /* CAN2 RX0 */
//   .weak   CAN2_RX1_IRQHandler        /* CAN2 RX1 */
//   .weak   CAN2_SCE_IRQHandler        /* CAN2 SCE */
//   .weak   OTG_FS_IRQHandler          /* OTGFS */
//   .weak   USBHSWakeup_IRQHandler     /* USBHS Wakeup */
//   .weak   USBHS_IRQHandler           /* USBHS */
//   .weak   DVP_IRQHandler             /* DVP */
//   .weak   UART6_IRQHandler           /* UART6 */
//   .weak   UART7_IRQHandler           /* UART7 */
//   .weak   UART8_IRQHandler           /* UART8 */
//   .weak   TIM9_BRK_IRQHandler        /* TIM9 Break */
//   .weak   TIM9_UP_IRQHandler         /* TIM9 Update */
//   .weak   TIM9_TRG_COM_IRQHandler    /* TIM9 Trigger and Commutation */
//   .weak   TIM9_CC_IRQHandler         /* TIM9 Capture Compare */
//   .weak   TIM10_BRK_IRQHandler       /* TIM10 Break */
//   .weak   TIM10_UP_IRQHandler        /* TIM10 Update */
//   .weak   TIM10_TRG_COM_IRQHandler   /* TIM10 Trigger and Commutation */
//   .weak   TIM10_CC_IRQHandler        /* TIM10 Capture Compare */
//   .weak   DMA2_Channel6_IRQHandler   /* DMA2 Channel 6 */
//   .weak   DMA2_Channel7_IRQHandler   /* DMA2 Channel 7 */
//   .weak   DMA2_Channel8_IRQHandler   /* DMA2 Channel 8 */
//   .weak   DMA2_Channel9_IRQHandler   /* DMA2 Channel 9 */
//   .weak   DMA2_Channel10_IRQHandler  /* DMA2 Channel 10 */
//   .weak   DMA2_Channel11_IRQHandler  /* DMA2 Channel 11 */

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  while (1)
  {
  }
}



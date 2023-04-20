################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_adc.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_delay.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_dvp.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_encoder.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_exti.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_flash.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_gpio.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_iic.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_pit.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_pwm.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_soft_iic.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_soft_spi.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_spi.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_timer.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_uart.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_usb_cdc.c 

OBJS += \
./zf_driver/zf_driver_adc.o \
./zf_driver/zf_driver_delay.o \
./zf_driver/zf_driver_dvp.o \
./zf_driver/zf_driver_encoder.o \
./zf_driver/zf_driver_exti.o \
./zf_driver/zf_driver_flash.o \
./zf_driver/zf_driver_gpio.o \
./zf_driver/zf_driver_iic.o \
./zf_driver/zf_driver_pit.o \
./zf_driver/zf_driver_pwm.o \
./zf_driver/zf_driver_soft_iic.o \
./zf_driver/zf_driver_soft_spi.o \
./zf_driver/zf_driver_spi.o \
./zf_driver/zf_driver_timer.o \
./zf_driver/zf_driver_uart.o \
./zf_driver/zf_driver_usb_cdc.o 

C_DEPS += \
./zf_driver/zf_driver_adc.d \
./zf_driver/zf_driver_delay.d \
./zf_driver/zf_driver_dvp.d \
./zf_driver/zf_driver_encoder.d \
./zf_driver/zf_driver_exti.d \
./zf_driver/zf_driver_flash.d \
./zf_driver/zf_driver_gpio.d \
./zf_driver/zf_driver_iic.d \
./zf_driver/zf_driver_pit.d \
./zf_driver/zf_driver_pwm.d \
./zf_driver/zf_driver_soft_iic.d \
./zf_driver/zf_driver_soft_spi.d \
./zf_driver/zf_driver_spi.d \
./zf_driver/zf_driver_timer.d \
./zf_driver/zf_driver_uart.d \
./zf_driver/zf_driver_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
zf_driver/zf_driver_adc.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_delay.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_delay.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_dvp.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_encoder.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_exti.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_flash.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_gpio.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_iic.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pit.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pwm.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_iic.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_soft_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_spi.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_soft_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_spi.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_timer.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_uart.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_usb_cdc.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/libraries/zf_driver/zf_driver_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


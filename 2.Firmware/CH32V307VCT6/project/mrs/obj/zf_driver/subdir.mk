################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_adc.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_delay.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_dvp.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_encoder.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_exti.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_flash.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_gpio.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_iic.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_pit.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_pwm.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_soft_iic.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_soft_spi.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_spi.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_timer.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_uart.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_usb_cdc.c 

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
zf_driver/zf_driver_adc.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_delay.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_delay.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_dvp.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_encoder.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_exti.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_flash.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_gpio.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_iic.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pit.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pwm.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_iic.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_soft_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_spi.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_soft_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_spi.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_timer.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_uart.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_usb_cdc.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/CH32V307VCT6/libraries/zf_driver/zf_driver_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


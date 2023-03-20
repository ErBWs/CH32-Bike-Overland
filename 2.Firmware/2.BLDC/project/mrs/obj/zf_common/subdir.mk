################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_clock.c \
Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_debug.c \
Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_fifo.c \
Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_font.c \
Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_function.c \
Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_interrupt.c 

OBJS += \
./zf_common/zf_common_clock.o \
./zf_common/zf_common_debug.o \
./zf_common/zf_common_fifo.o \
./zf_common/zf_common_font.o \
./zf_common/zf_common_function.o \
./zf_common/zf_common_interrupt.o 

C_DEPS += \
./zf_common/zf_common_clock.d \
./zf_common/zf_common_debug.d \
./zf_common/zf_common_fifo.d \
./zf_common/zf_common_font.d \
./zf_common/zf_common_function.d \
./zf_common/zf_common_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
zf_common/zf_common_clock.o: Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\Libraries\doc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Core" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Ld" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Peripheral" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Startup" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\user\inc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_common" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_device" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\code" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\Libraries\doc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Core" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Ld" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Peripheral" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Startup" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\user\inc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_common" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_device" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\code" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\Libraries\doc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Core" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Ld" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Peripheral" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Startup" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\user\inc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_common" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_device" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\code" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\Libraries\doc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Core" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Ld" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Peripheral" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Startup" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\user\inc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_common" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_device" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\code" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\Libraries\doc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Core" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Ld" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Peripheral" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Startup" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\user\inc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_common" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_device" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\code" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: Z:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\Libraries\doc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Core" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Ld" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Peripheral" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\sdk\Startup" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\user\inc" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_common" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_device" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\project\code" -I"Z:\Users\baohan\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\2.BLDC\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


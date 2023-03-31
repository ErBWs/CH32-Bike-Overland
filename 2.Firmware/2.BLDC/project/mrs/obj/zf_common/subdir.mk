################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_clock.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_debug.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_fifo.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_font.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_function.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_interrupt.c

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
zf_common/zf_common_clock.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core/core_riscv.c

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


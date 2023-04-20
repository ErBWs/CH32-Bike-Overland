################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/seekfree_libraries/sdk/Startup/startup_ch32v30x_D8C.S

OBJS += \
./seekfree_libraries/sdk/Startup/startup_ch32v30x_D8C.o 

S_UPPER_DEPS += \
./seekfree_libraries/sdk/Startup/startup_ch32v30x_D8C.d 


# Each subdirectory must supply rules for building sources it contributes
seekfree_libraries/sdk/Startup/startup_ch32v30x_D8C.o: /Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/seekfree_libraries/sdk/Startup/startup_ch32v30x_D8C.S
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -pedantic -Wunused -Wuninitialized -Wall  -g -x assembler -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/seekfree_libraries/sdk/Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


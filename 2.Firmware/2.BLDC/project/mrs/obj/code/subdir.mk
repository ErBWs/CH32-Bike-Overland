################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/easy_key.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/ips096.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/ips096_dma.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/user_flash.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/user_spi.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/vofa.c

OBJS += \
./code/easy_key.o \
./code/ips096.o \
./code/ips096_dma.o \
./code/user_flash.o \
./code/user_spi.o \
./code/vofa.o 

C_DEPS += \
./code/easy_key.d \
./code/ips096.d \
./code/ips096_dma.d \
./code/user_flash.d \
./code/user_spi.d \
./code/vofa.d 


# Each subdirectory must supply rules for building sources it contributes
code/easy_key.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/easy_key.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/ips096.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/ips096.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/ips096_dma.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/ips096_dma.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/user_flash.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/user_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/user_spi.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/user_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/vofa.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/vofa.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


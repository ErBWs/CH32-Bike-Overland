################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/user/src/isr.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/user/src/main.c 

OBJS += \
./user_c/isr.o \
./user_c/main.o 

C_DEPS += \
./user_c/isr.d \
./user_c/main.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/isr.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


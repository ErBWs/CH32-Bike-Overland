################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/INS/INS.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/INS/insapi.c 

OBJS += \
./code/INS/INS.o \
./code/INS/insapi.o 

C_DEPS += \
./code/INS/INS.d \
./code/INS/insapi.d 


# Each subdirectory must supply rules for building sources it contributes
code/INS/INS.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/INS/INS.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/INS/insapi.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/INS/insapi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


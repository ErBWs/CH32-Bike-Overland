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
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/vofa.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/easing_function.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/easy_ui.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/easy_ui_user_app.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/profile_photo_erbws.c \
/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/nmea0183.c

OBJS += \
./code/easy_key.o \
./code/ips096.o \
./code/ips096_dma.o \
./code/user_flash.o \
./code/user_spi.o \
./code/vofa.o \
./code/easing_function.o \
./code/easy_ui.o \
./code/easy_ui_user_app.o \
./code/profile_photo_erbws.o \
./code/nmea0183.o

C_DEPS += \
./code/easy_key.d \
./code/ips096.d \
./code/ips096_dma.d \
./code/user_flash.d \
./code/user_spi.d \
./code/vofa.d \
./code/easing_function.d \
./code/easy_ui.d \
./code/easy_ui_user_app.d \
./code/profile_photo_erbws.d \
./code/nmea0183.d


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
code/easing_function.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/easing_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/easy_ui.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/easy_ui.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/easy_ui_user_app.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/easy_ui_user_app.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/profile_photo_erbws.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/profile_photo_erbws.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/nmea0183.o:/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code/nmea0183.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/Libraries/doc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Core" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Ld" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Peripheral" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/sdk/Startup" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/user/inc" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_common" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_device" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/project/code" -I"/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/libraries/zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
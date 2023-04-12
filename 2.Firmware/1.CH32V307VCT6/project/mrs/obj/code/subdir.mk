################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/buzzer.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/complementary_filter.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ctrl.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/easy_key.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/easy_ui.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/easy_ui_user_app.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ellipsoid_fitting_process.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/encoder.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/filter.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/imu.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/inertial_navigation.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ips096.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/jdy34.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/moto.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/my_math.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/pid.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/profile_photo_erbws.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/sendware.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/user_flash.c \
S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/vofa.c 

OBJS += \
./code/buzzer.o \
./code/complementary_filter.o \
./code/ctrl.o \
./code/easy_key.o \
./code/easy_ui.o \
./code/easy_ui_user_app.o \
./code/ellipsoid_fitting_process.o \
./code/encoder.o \
./code/filter.o \
./code/imu.o \
./code/inertial_navigation.o \
./code/ips096.o \
./code/jdy34.o \
./code/moto.o \
./code/my_math.o \
./code/pid.o \
./code/profile_photo_erbws.o \
./code/sendware.o \
./code/user_flash.o \
./code/vofa.o 

C_DEPS += \
./code/buzzer.d \
./code/complementary_filter.d \
./code/ctrl.d \
./code/easy_key.d \
./code/easy_ui.d \
./code/easy_ui_user_app.d \
./code/ellipsoid_fitting_process.d \
./code/encoder.d \
./code/filter.d \
./code/imu.d \
./code/inertial_navigation.d \
./code/ips096.d \
./code/jdy34.d \
./code/moto.d \
./code/my_math.d \
./code/pid.d \
./code/profile_photo_erbws.d \
./code/sendware.d \
./code/user_flash.d \
./code/vofa.d 


# Each subdirectory must supply rules for building sources it contributes
code/buzzer.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/buzzer.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/complementary_filter.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/complementary_filter.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/ctrl.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ctrl.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/easy_key.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/easy_key.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/easy_ui.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/easy_ui.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/easy_ui_user_app.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/easy_ui_user_app.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/ellipsoid_fitting_process.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ellipsoid_fitting_process.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/encoder.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/filter.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/filter.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/imu.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/imu.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/inertial_navigation.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/inertial_navigation.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/ips096.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ips096.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/jdy34.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/jdy34.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/moto.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/moto.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/my_math.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/my_math.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/pid.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/pid.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/profile_photo_erbws.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/profile_photo_erbws.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/sendware.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/sendware.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/user_flash.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/user_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/vofa.o: S:/WorkSpace/bicycle\ motocross/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/vofa.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"S:\WorkSpace\bicycle motocross\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


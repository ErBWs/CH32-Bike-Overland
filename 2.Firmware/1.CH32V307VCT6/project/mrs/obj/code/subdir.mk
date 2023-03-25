################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/complementary_filter.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ctrl.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ellipsoid_fitting_process.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/encoder.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/filter.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/imu.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/jdy34.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/moto.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/my_math.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/pid.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/sendware.c \
F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/vofa.c 

OBJS += \
./code/complementary_filter.o \
./code/ctrl.o \
./code/ellipsoid_fitting_process.o \
./code/encoder.o \
./code/filter.o \
./code/imu.o \
./code/jdy34.o \
./code/moto.o \
./code/my_math.o \
./code/pid.o \
./code/sendware.o \
./code/vofa.o 

C_DEPS += \
./code/complementary_filter.d \
./code/ctrl.d \
./code/ellipsoid_fitting_process.d \
./code/encoder.d \
./code/filter.d \
./code/imu.d \
./code/jdy34.d \
./code/moto.d \
./code/my_math.d \
./code/pid.d \
./code/sendware.d \
./code/vofa.d 


# Each subdirectory must supply rules for building sources it contributes
code/complementary_filter.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/complementary_filter.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/ctrl.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ctrl.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/ellipsoid_fitting_process.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ellipsoid_fitting_process.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/encoder.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/filter.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/filter.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/imu.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/imu.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/jdy34.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/jdy34.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/moto.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/moto.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/my_math.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/my_math.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/pid.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/pid.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/sendware.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/sendware.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/vofa.o: F:/bike/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/vofa.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"F:\bike\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/complementary_filter.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ctrl.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ellipsoid_fitting_process.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/encoder.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/filter.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/imu.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/moto.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/my_math.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/pid.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/sendware.c \
Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/vofa.c 

OBJS += \
./code/complementary_filter.o \
./code/ctrl.o \
./code/ellipsoid_fitting_process.o \
./code/encoder.o \
./code/filter.o \
./code/imu.o \
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
./code/moto.d \
./code/my_math.d \
./code/pid.d \
./code/sendware.d \
./code/vofa.d 


# Each subdirectory must supply rules for building sources it contributes
code/complementary_filter.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/complementary_filter.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/ctrl.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ctrl.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/ellipsoid_fitting_process.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/ellipsoid_fitting_process.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/encoder.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/filter.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/filter.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/imu.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/imu.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/moto.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/moto.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/my_math.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/my_math.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/pid.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/pid.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/sendware.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/sendware.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/vofa.o: Y:/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/1.CH32V307VCT6/project/code/vofa.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\Libraries\doc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Core" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Ld" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Peripheral" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\sdk\Startup" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\user\inc" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_common" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_device" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\project\code" -I"Y:\ErBW_s\Projects\CH32-Bike-Overland\2.Firmware\1.CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


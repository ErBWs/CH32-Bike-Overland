################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include user_c/subdir.mk
-include seekfree_libraries/zf_driver/subdir.mk
-include seekfree_libraries/zf_common/subdir.mk
-include seekfree_libraries/sdk/Startup/subdir.mk
-include seekfree_libraries/sdk/Peripheral/subdir.mk
-include seekfree_libraries/sdk/Core/subdir.mk
-include code/subdir.mk
-include bldc_software/subdir.mk
-include bldc_hardware/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
SEEKFREE_CH32V307_DOUBLE_BLDC.hex \

SECONDARY_LIST += \
SEEKFREE_CH32V307_DOUBLE_BLDC.lst \

SECONDARY_SIZE += \
SEEKFREE_CH32V307_DOUBLE_BLDC.siz \


# All Target
all: SEEKFREE_CH32V307_DOUBLE_BLDC.elf secondary-outputs

# Tool invocations
SEEKFREE_CH32V307_DOUBLE_BLDC.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -pedantic -Wunused -Wuninitialized -Wall  -g -T "/Users/baohan/ErBW_s/Projects/CH32-Bike-Overland/2.Firmware/2.BLDC/seekfree_libraries/sdk/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -Wl,-Map,"SEEKFREE_CH32V307_DOUBLE_BLDC.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -Wl,--print-memory-usage -o "SEEKFREE_CH32V307_DOUBLE_BLDC.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
SEEKFREE_CH32V307_DOUBLE_BLDC.hex: SEEKFREE_CH32V307_DOUBLE_BLDC.elf
	@	riscv-none-embed-objcopy -O ihex "SEEKFREE_CH32V307_DOUBLE_BLDC.elf"  "SEEKFREE_CH32V307_DOUBLE_BLDC.hex"
	@	@
SEEKFREE_CH32V307_DOUBLE_BLDC.lst: SEEKFREE_CH32V307_DOUBLE_BLDC.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "SEEKFREE_CH32V307_DOUBLE_BLDC.elf" > "SEEKFREE_CH32V307_DOUBLE_BLDC.lst"
	@	@
SEEKFREE_CH32V307_DOUBLE_BLDC.siz: SEEKFREE_CH32V307_DOUBLE_BLDC.elf
	@	riscv-none-embed-size --format=berkeley "SEEKFREE_CH32V307_DOUBLE_BLDC.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) SEEKFREE_CH32V307_DOUBLE_BLDC.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets

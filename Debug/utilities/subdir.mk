################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c 

S_UPPER_SRCS += \
../utilities/fsl_memcpy.S 

C_DEPS += \
./utilities/fsl_assert.d 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_memcpy.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DMCUXPRESSO_SDK -DCPU_MCXN947VDF_cm33_core0 -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Workspaces_NXP\Audio\digital_led\drivers" -I"C:\Workspaces_NXP\Audio\digital_led\CMSIS" -I"C:\Workspaces_NXP\Audio\digital_led\CMSIS\m-profile" -I"C:\Workspaces_NXP\Audio\digital_led\device" -I"C:\Workspaces_NXP\Audio\digital_led\device\periph" -I"C:\Workspaces_NXP\Audio\digital_led\utilities" -I"C:\Workspaces_NXP\Audio\digital_led\utilities\str" -I"C:\Workspaces_NXP\Audio\digital_led\utilities\debug_console_lite" -I"C:\Workspaces_NXP\Audio\digital_led\component\uart" -I"C:\Workspaces_NXP\Audio\digital_led\source" -I"C:\Workspaces_NXP\Audio\digital_led\board" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -fno-builtin -imacros "C:\Workspaces_NXP\Audio\digital_led\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utilities/%.o: ../utilities/%.S utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -I"C:\Workspaces_NXP\Audio\digital_led\drivers" -I"C:\Workspaces_NXP\Audio\digital_led\CMSIS" -I"C:\Workspaces_NXP\Audio\digital_led\CMSIS\m-profile" -I"C:\Workspaces_NXP\Audio\digital_led\device" -I"C:\Workspaces_NXP\Audio\digital_led\device\periph" -I"C:\Workspaces_NXP\Audio\digital_led\utilities" -I"C:\Workspaces_NXP\Audio\digital_led\utilities\str" -I"C:\Workspaces_NXP\Audio\digital_led\utilities\debug_console_lite" -I"C:\Workspaces_NXP\Audio\digital_led\component\uart" -I"C:\Workspaces_NXP\Audio\digital_led\source" -g3 -gdwarf-4 -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o ./utilities/fsl_memcpy.o

.PHONY: clean-utilities


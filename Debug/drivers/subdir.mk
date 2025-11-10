################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_ctimer.c \
../drivers/fsl_edma.c \
../drivers/fsl_edma_soc.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpflexcomm.c \
../drivers/fsl_lptmr.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_reset.c \
../drivers/fsl_spc.c 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_ctimer.d \
./drivers/fsl_edma.d \
./drivers/fsl_edma_soc.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpflexcomm.d \
./drivers/fsl_lptmr.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_reset.d \
./drivers/fsl_spc.d 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_ctimer.o \
./drivers/fsl_edma.o \
./drivers/fsl_edma_soc.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpflexcomm.o \
./drivers/fsl_lptmr.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_reset.o \
./drivers/fsl_spc.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DMCUXPRESSO_SDK -DCPU_MCXN947VDF_cm33_core0 -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Workspaces_NXP\Audio\digital_led\drivers" -I"C:\Workspaces_NXP\Audio\digital_led\CMSIS" -I"C:\Workspaces_NXP\Audio\digital_led\CMSIS\m-profile" -I"C:\Workspaces_NXP\Audio\digital_led\device" -I"C:\Workspaces_NXP\Audio\digital_led\device\periph" -I"C:\Workspaces_NXP\Audio\digital_led\utilities" -I"C:\Workspaces_NXP\Audio\digital_led\utilities\str" -I"C:\Workspaces_NXP\Audio\digital_led\utilities\debug_console_lite" -I"C:\Workspaces_NXP\Audio\digital_led\component\uart" -I"C:\Workspaces_NXP\Audio\digital_led\source" -I"C:\Workspaces_NXP\Audio\digital_led\board" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -fno-builtin -imacros "C:\Workspaces_NXP\Audio\digital_led\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_ctimer.d ./drivers/fsl_ctimer.o ./drivers/fsl_edma.d ./drivers/fsl_edma.o ./drivers/fsl_edma_soc.d ./drivers/fsl_edma_soc.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpflexcomm.d ./drivers/fsl_lpflexcomm.o ./drivers/fsl_lptmr.d ./drivers/fsl_lptmr.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_reset.d ./drivers/fsl_reset.o ./drivers/fsl_spc.d ./drivers/fsl_spc.o

.PHONY: clean-drivers


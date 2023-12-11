################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/I2C.c \
../source/QMC_588L_MAG.c \
../source/Systick.c \
../source/mag_readings.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/tpm.c 

C_DEPS += \
./source/I2C.d \
./source/QMC_588L_MAG.d \
./source/Systick.d \
./source/mag_readings.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/tpm.d 

OBJS += \
./source/I2C.o \
./source/QMC_588L_MAG.o \
./source/Systick.o \
./source/mag_readings.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/tpm.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\MSI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\KL25Z-DMA-DAC-ADC\QMC_588L_MAG\board" -I"C:\Users\MSI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\KL25Z-DMA-DAC-ADC\QMC_588L_MAG\source" -I"C:\Users\MSI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\KL25Z-DMA-DAC-ADC\QMC_588L_MAG" -I"C:\Users\MSI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\KL25Z-DMA-DAC-ADC\QMC_588L_MAG\drivers" -I"C:\Users\MSI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\KL25Z-DMA-DAC-ADC\QMC_588L_MAG\CMSIS" -I"C:\Users\MSI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\KL25Z-DMA-DAC-ADC\QMC_588L_MAG\utilities" -I"C:\Users\MSI\Documents\MCUXpressoIDE_11.8.0_1165\workspace\KL25Z-DMA-DAC-ADC\QMC_588L_MAG\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/I2C.d ./source/I2C.o ./source/QMC_588L_MAG.d ./source/QMC_588L_MAG.o ./source/Systick.d ./source/Systick.o ./source/mag_readings.d ./source/mag_readings.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/tpm.d ./source/tpm.o

.PHONY: clean-source


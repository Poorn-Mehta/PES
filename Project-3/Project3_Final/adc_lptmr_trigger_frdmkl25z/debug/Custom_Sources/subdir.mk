################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Custom_Sources/Custom_ASCII_Counter.c \
../Custom_Sources/Custom_Circular_Buffer.c \
../Custom_Sources/Custom_UART.c \
../Custom_Sources/project_3.c 

OBJS += \
./Custom_Sources/Custom_ASCII_Counter.o \
./Custom_Sources/Custom_Circular_Buffer.o \
./Custom_Sources/Custom_UART.o \
./Custom_Sources/project_3.o 

C_DEPS += \
./Custom_Sources/Custom_ASCII_Counter.d \
./Custom_Sources/Custom_Circular_Buffer.d \
./Custom_Sources/Custom_UART.d \
./Custom_Sources/project_3.d 


# Each subdirectory must supply rules for building sources it contributes
Custom_Sources/%.o: ../Custom_Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DCPU_MKL25Z128VLK4 -DFRDM_KL25Z -DFREEDOM -I../../../../../../../platform/osa/inc -I../../../../../../../platform/utilities/inc -I../../../../../../../platform/CMSIS/Include -I../../../../../../../platform/devices -I../../../../../../../platform/devices/MKL25Z4/include -I../../../../../../../platform/devices/MKL25Z4/startup -I../../../../../../../platform/hal/inc -I../../../../../../../platform/drivers/inc -I../../../../../../../platform/system/inc -I../../../../.. -I"C:\Freescale\KSDK_1.3.0\examples\frdmkl25z\demo_apps\adc_hw_trigger\lptmr\kds\Custom_Includes" -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



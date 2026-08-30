################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DC_MOTOR.c \
../DIO_program.c \
../SWITCH.c \
../main.c 

OBJS += \
./DC_MOTOR.o \
./DIO_program.o \
./SWITCH.o \
./main.o 

C_DEPS += \
./DC_MOTOR.d \
./DIO_program.d \
./SWITCH.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\HAL\DC_MOTOR" -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\LIB" -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\MCAL\DIO" -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\HAL\SWITCH" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



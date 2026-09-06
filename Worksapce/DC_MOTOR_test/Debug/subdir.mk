################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../DC_MOTOR.c \
../DIO_program.c \
../SWITCH.c \
../TIMER_program.c \
../main.c 

OBJS += \
./ADC_program.o \
./DC_MOTOR.o \
./DIO_program.o \
./SWITCH.o \
./TIMER_program.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./DC_MOTOR.d \
./DIO_program.d \
./SWITCH.d \
./TIMER_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\HAL\DC_MOTOR" -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\MCAL\ADC" -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\MCAL\DIO" -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\MCAL\GIE" -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\MCAL\TIMER" -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\LIB" -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\MCAL\DIO" -I"D:\Microcontroller-Architecture-and-Interfacing-with-AVR\CTOS\ATmega32\HAL\SWITCH" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



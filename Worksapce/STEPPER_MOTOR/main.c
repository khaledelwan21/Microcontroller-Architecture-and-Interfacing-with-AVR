/*
 * main.c - Simple Security
 * Author: Khaled Ahmed Elwan
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "KEYPAD_interface.h"
#include "STEPPER_MOTOR_Interface.h"

int main(void)
{

	LCD_Init() ;
	LCD_Send_String((u8 *)"Start ") ;
	STEPPER_voidInit() ;
	STEPPER_voidOn(STEPPER_FULL_STEP, STEPPER_CLOCK_WISE, 5, 90);
	LCD_Set_Position(1,1) ;
	LCD_Send_String((u8 *)"RPM=") ;
	LCD_Send_Number((1000.0/2046.0)*60.0/5.0)
		while(1) ;
    return 0;
}



/****************************************************************/
/******* Author    : Khaled Ahmed Elwan         *****************/
/******* Date      : 23 Aug 2026                *****************/
/******* Version   : 1.0                        *****************/
/******* File Name : LED.c           *****************/
/****************************************************************/


#include "LED.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

void  LED_Init( led_type led )
{
	DIO_SetPinDirection(led.port, led.pin, DIO_OUTPUT) ;
}

void LED_ON (led_type led )
{
	DIO_SetPinValue(led.port , led.pin , DIO_HIGH) ;
}

void LED_OFF (led_type led)
{
	DIO_SetPinValue(led.port , led.pin , DIO_LOW );
}

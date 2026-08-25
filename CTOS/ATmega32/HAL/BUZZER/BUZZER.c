
/****************************************************************/
/******* Author    : Khaled Ahmed Elwan         *****************/
/******* Date      : 23 Aug 2026                *****************/
/******* Version   : 1.0                        *****************/
/******* File Name : BUZZRR.c            *****************/
/****************************************************************/


#include "BUZZER.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

void  BUZZER_Init( buzzer_type buzzer )
{
	DIO_SetPinDirection(buzzer.port, buzzer.pin, DIO_OUTPUT) ;
}

void BUZZER_ON (buzzer_type buzzer )
{
	DIO_SetPinValue(buzzer.port , buzzer.pin , DIO_HIGH) ;
}

void BUZZER_OFF (buzzer_type buzzer)
{
	DIO_SetPinValue(buzzer.port , buzzer.pin , DIO_LOW );
}

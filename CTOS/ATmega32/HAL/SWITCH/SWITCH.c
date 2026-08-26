/*
 *  file Name : SWITCH.c
 *  Author    : Khaled Ahmed Elwan
 *  Description :
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "SWITCH.h"

void SW_Init(sw_type sw)
{
	DIO_SetPinDirection(sw.port, sw.pin, DIO_INPUT);

	if (sw.type == PIN_INTERNAL_PULL_UP)
	{
		DIO_SetPin_PullUp(sw.port, sw.pin, PullUp);
	}
}

u8 SW_Getpressed(sw_type sw)
{
	u8 _u8local = 0;

	if (sw.type == PIN_PULL_UP)
	{
		DIO_SetPinValue(sw.port,sw.pin,DIO_LOW) ;
		DIO_GetPinValue(sw.port, sw.pin, &_u8local);
		return !_u8local;
	}
	else if (sw.type == PIN_PULL_DOWN)
	{
		DIO_SetPinValue(sw.port,sw.pin,DIO_LOW) ;
		DIO_GetPinValue(sw.port, sw.pin, &_u8local);
		return _u8local;
	}
	else if (sw.type == PIN_INTERNAL_PULL_UP)
	{
		DIO_SetPinValue(sw.port,sw.pin,DIO_HIGH) ;
		DIO_GetPinValue(sw.port, sw.pin, &_u8local);
		return !_u8local;
	}

	return _u8local;
}

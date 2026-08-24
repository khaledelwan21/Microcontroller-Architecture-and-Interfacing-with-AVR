/****************************************************************/
/******* Author    : Khaled Ahned Elwan         *****************/
/******* Date      : 23 Aug 2026                *****************/
/******* Version   : 1.0                        *****************/
/******* File Name : DIO_prrogram.c              *****************/
/****************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"



Std_ReturnType DIO_SetPinDirection(u8 Copy_PortId, u8 Copy_PinId,u8 Copy_PinDirection)
{
	Std_ReturnType Local_FunctionStatus = E_OK;

	if(((Copy_PortId < 4) && (Copy_PinId < 8)) && ((Copy_PinDirection == DIO_OUTPUT) || (Copy_PinDirection == DIO_INPUT)))
	{
		switch (Copy_PortId)
		{
			case PORTA:
				switch (Copy_PinDirection)
				{
					case DIO_OUTPUT: SET_BIT(DIO_DDRA, Copy_PinId);break;
					case DIO_INPUT : CLR_BIT(DIO_DDRA, Copy_PinId);break;
					default : Local_FunctionStatus = E_NOT_OK;
				}
				break;
			case PORTB:
				switch (Copy_PinDirection)
				{
					case DIO_OUTPUT:SET_BIT(DIO_DDRB, Copy_PinId);break;
					case DIO_INPUT :CLR_BIT(DIO_DDRB, Copy_PinId);break;
					default : Local_FunctionStatus = E_NOT_OK;
				}
				break;
			case PORTC:
				switch (Copy_PinDirection)
				{
					case DIO_OUTPUT:SET_BIT(DIO_DDRC, Copy_PinId);break;
					case DIO_INPUT :CLR_BIT(DIO_DDRC, Copy_PinId);break;
					Local_FunctionStatus = E_NOT_OK;
				}
				break;
			case PORTD:
				switch (Copy_PinDirection)
				{
					case DIO_OUTPUT:SET_BIT(DIO_DDRD, Copy_PinId);break;
					case DIO_INPUT :CLR_BIT(DIO_DDRD, Copy_PinId);break;
					Local_FunctionStatus = E_NOT_OK;
				}
				break;
		}
	}
	else
	{
		Local_FunctionStatus = E_NOT_OK;
	}

	return Local_FunctionStatus;

}


Std_ReturnType DIO_SetPinValue(u8 Copy_PortId, u8 Copy_PinId, u8 Copy_PinValue)
{
	Std_ReturnType Local_FunctionStatus = E_OK;

		if(((Copy_PortId < 4) && (Copy_PinId < 8)) && ((Copy_PinValue == DIO_HIGH) || (Copy_PinValue == DIO_LOW)))
		{
			switch (Copy_PortId)
			{
				case PORTA:
					switch (Copy_PinValue)
					{
						case DIO_LOW  : CLR_BIT(DIO_PORTA, Copy_PinId);break;
						case DIO_HIGH : SET_BIT(DIO_PORTA, Copy_PinId);break;
						default : Local_FunctionStatus = E_NOT_OK;
					}
					break;
				case PORTB:
					switch (Copy_PinValue)
					{
				     	case DIO_LOW  : CLR_BIT(DIO_PORTB, Copy_PinId);break;
						case DIO_HIGH : SET_BIT(DIO_PORTB, Copy_PinId);break;
						default : Local_FunctionStatus = E_NOT_OK;
					}
					break;
				case PORTC:
					switch (Copy_PinValue)
					{
					    case DIO_LOW  : CLR_BIT(DIO_PORTC, Copy_PinId);break;
						case DIO_HIGH : SET_BIT(DIO_PORTC, Copy_PinId);break;
						Local_FunctionStatus = E_NOT_OK;
					}
					break;
				case PORTD:
					switch (Copy_PinValue)
					{
					    case DIO_LOW  : CLR_BIT(DIO_PORTD, Copy_PinId);break;
						case DIO_HIGH : SET_BIT(DIO_PORTD, Copy_PinId);break;
						Local_FunctionStatus = E_NOT_OK;
					}
					break;
			}
		}
		else
		{
			Local_FunctionStatus = E_NOT_OK;
		}

		return Local_FunctionStatus;

}

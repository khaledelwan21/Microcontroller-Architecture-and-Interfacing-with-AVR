/*
 * main.c
 * Motor Speed & Direction Control via Potentiometer (ADC)
 */
#include <util/delay.h>
#include <avr/interrupt.h>
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "CLCD_interface.h"
#include "TIMER_interface.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define F_CPU			8000000UL

u8 edge=0 ;
u16 rising_edge1,rising_edge2;
u16 time_period=0 ;
f32 frequency ;
void getFrequency(void)
{
	if (edge == 0)
	{
		rising_edge1=TIMER_u16GetICR();
		edge =1 ;
	}
	else
	{
		rising_edge2=TIMER_u16GetICR();
		TIMER_voidICUDisableInterrupt() ;
		edge=2 ;
	}

}


/*----------------------------------------------------------------*/

int main()
{
	/*Direction Pins*/
	DIO_SetPinDirection(PORTD , DIO_PIN6 , DIO_INPUT) ;

	DIO_SetPinDirection(PORTD , DIO_PIN5 , DIO_OUTPUT) ;
	LCD_Init() ;
	LCD_Send_String((u8 *)"Frequency=");
	TIMER1_voidInit() ;
	TIMER_u8SetCallBack( getFrequency ,TIMER1_ICU_VECTOR_ID) ;


	sei() ;

	while(1)
	{
		if(edge ==2)
		{
			time_period=rising_edge2-rising_edge1;
			frequency=1000000.0/time_period ;
			LCD_Send_Number(frequency) ;
		}
	}

	return 0 ;
}

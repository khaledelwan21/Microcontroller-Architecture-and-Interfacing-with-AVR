/*
 * main.c
 *
 *  Created on: Aug 31, 2026
 *      Author: khaled
 */
#include <util/delay.h>
#include <avr/interrupt.h>
#include "DIO_interface.h"
#include "DIO_private.h"
#include "LED.h"
#include "ADC_interface.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define F_CPU	8000000UL

led_type LED[8] = {
     { .port = PORTB, .pin = DIO_PIN0 },
     { .port = PORTB, .pin = DIO_PIN1 },
     { .port = PORTB, .pin = DIO_PIN2 },
     { .port = PORTB, .pin = DIO_PIN3 },
     { .port = PORTB, .pin = DIO_PIN4 },
     { .port = PORTB, .pin = DIO_PIN5 },
     { .port = PORTB, .pin = DIO_PIN6 },
     { .port = PORTB, .pin = DIO_PIN7 }
 };

u16 result = 0 ;

void LED_Edge(void)
{
	if (result >= 0)    LED_ON(LED[0]) ; else LED_OFF(LED[0]) ;
	if (result >= 128)  LED_ON(LED[1]) ; else LED_OFF(LED[1]) ;
	if (result >= 256)  LED_ON(LED[2]) ; else LED_OFF(LED[2]) ;
	if (result >= 384)  LED_ON(LED[3]) ; else LED_OFF(LED[3]) ;
	if (result >= 512)  LED_ON(LED[4]) ; else LED_OFF(LED[4]) ;
	if (result >= 640)  LED_ON(LED[5]) ; else LED_OFF(LED[5]) ;
	if (result >= 768)  LED_ON(LED[6]) ; else LED_OFF(LED[6]) ;
	if (result >= 896)  LED_ON(LED[7]) ; else LED_OFF(LED[7]) ;
}
int main()
{
	DIO_SetPinDirection(PORTA, DIO_PIN0, DIO_INPUT) ;

	for (u8 i = 0; i < 8; i++)
	{
		LED_Init(LED[i]) ;
	}

	ADC_voidInit() ;
	ADC_u8SetPrescaler(ADC_PRE_2) ;
	ADC_u8StartFreeRunningAsynch(ADC_CHANNEL0, &result, LED_Edge) ;

	sei() ;   /*لازم بعد كل الـ Init، يفتح الـ Global Interrupt*/

	while(1)
	{
		_delay_ms(50) ;
	}

	return 0;
}

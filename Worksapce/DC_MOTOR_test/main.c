/*
 * main.c
 *
 *  Created on: Aug 27, 2026
 *      Author: khaled
 */


#include <util/delay.h>
#include "DIO_interface.h"
#include "DC_MOTOR.h"
#include "SWITCH.h"
#include "STD_TYPES.h"
#define F_CPU	8000000UL


u8 button1_status ,button2_status  ;

sw_type sw1 ={
		.port =PORTD,
		.pin=DIO_PIN7,
		.type= PIN_INTERNAL_PULL_UP
};
sw_type sw2 ={
		.port =PORTD,
		.pin=DIO_PIN6,
		.type= PIN_INTERNAL_PULL_UP
};
motor_type motor1={
		.port =PORTB,
		.pin1=DIO_PIN0,
		.pin2=DIO_PIN1
};
int main()
{
	SW_Init(sw1);
	SW_Init(sw2);

	while(1)
	{
		    button1_status=SW_Getpressed(sw1) ;
			button2_status=SW_Getpressed(sw2) ;
			if (button1_status == 1 && button2_status == 0)
			{
				DC_MOTOR_ON_CW(motor1) ;
			}
			if (button2_status == 1 && button1_status == 0)
			{
				DC_MOTOR_ON_CCW(motor1) ;
			}


	}

	return 0 ;
}

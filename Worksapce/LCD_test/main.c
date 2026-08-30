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

const u8 password[4] = {'1', '2', '3', '4'};
u8 get_pass[4] ;
u8 i =1 ;
u8 counter=0 ;
int main(void)
{
while(counter!=4)
{
	LCD_Init() ;
	u8 KeyPressed;
	KPD_Init();

		LCD_Send_String((u8 *)"Enter Your Pass:") ;


		while(i !=5)
		{
		    KeyPressed = KPD_u8GetPressed();

		    if(KeyPressed != NOTPRESSED)
		    {
				LCD_Set_Position(2,i) ;
				get_pass[i-1]=KeyPressed ;
		    	i++ ;
		        LCD_Send_Data(KeyPressed);
		        while(KPD_u8GetPressed() != NOTPRESSED);
		    }
		}
		LCD_Clear_Screen() ;
		for(int i=0 ;i<4 ;i++)
		{
			if(password[i]==get_pass[i]) counter++ ;
		}
		if (counter==4)
		{
			LCD_Set_Position(1,4) ;
			LCD_Send_String((u8 *)"Correct Pass") ;
		}
		else
		{
			LCD_Set_Position(1,4) ;
			LCD_Send_String((u8 *)"Wrong Pass") ;
			i=1;
			counter=0 ;
			_delay_ms(100) ;
		}
}
		while(1) ;
    return 0;
}


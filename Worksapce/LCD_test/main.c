/*
 * main.c
 *
 * Author: khaled
 */
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "STD_TYPES.h"

int main(void)
{
	LCD_Init();
	LCD_Set_Position(CLCD_ROW_1, 1);
	LCD_Send_String((u8*)"Khaled Elwan");

	while(1)
	{
	}
	return 0;
}

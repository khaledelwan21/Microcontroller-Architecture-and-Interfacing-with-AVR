/*
 *  file Name : KEYPAD_program.c
 *  Author    : Khaled Ahmed Elwan
 *  Date : 27/8/2026
 *  Version : 1.0
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"
#include "KEYPAD_config.h"


#include "util/delay.h"

static u8 KPD_u8Buttons [4][4] = {
		{'7', '8', '9', '/'}, /* ROW 0 */
		{'4', '5', '6', '*'}, /* ROW 1 */
		{'1', '2', '3', '-'}, /* ROW 2 */
		{'?', '0', '=', '+'}  /* ROW 3 */
};
void KPD_Init(void)
{
	    DIO_SetPinDirection(KPD_PORT, DIO_PIN0, DIO_INPUT);
	    DIO_SetPinDirection(KPD_PORT, DIO_PIN1, DIO_INPUT);
	    DIO_SetPinDirection(KPD_PORT, DIO_PIN2, DIO_INPUT);
	    DIO_SetPinDirection(KPD_PORT, DIO_PIN3, DIO_INPUT);

	    DIO_SetPinDirection(KPD_PORT, DIO_PIN4, DIO_OUTPUT);
	    DIO_SetPinDirection(KPD_PORT, DIO_PIN5, DIO_OUTPUT);
	    DIO_SetPinDirection(KPD_PORT, DIO_PIN6, DIO_OUTPUT);
	    DIO_SetPinDirection(KPD_PORT, DIO_PIN7, DIO_OUTPUT);

	    DIO_SetPortValue(KPD_PORT, 0xFF);
}


u8 KPD_u8GetPressed(void){
	u8 ReturnData = NOTPRESSED;
	u8 GetPressed;

	/* Iterators */
	u8 Row;
	u8 Col;

	for(Col = 0 + KPD_COL_INIT; Col < KPD_COL_END + 1; Col++)
	{
		DIO_SetPinValue(KPD_PORT, Col, DIO_LOW); // low on current column

		/* check rows for current columns */
		for(Row = 0 + KPD_ROW_INIT; Row < KPD_ROW_END + 1; Row++)
		{
			// check the current row: get its value (in GetPressed variable)
			DIO_GetPinValue(KPD_PORT, Row, &GetPressed);
			/* GetPressed = DIO_GetPinValue(KPD_PORT, Row); */

			if(GetPressed == 0)
			{
			    _delay_ms(10); // Debouncing Delay
			    DIO_GetPinValue(KPD_PORT, Row, &GetPressed);
			    if(GetPressed == 0)
			    {

			        ReturnData = KPD_u8Buttons[Row - KPD_ROW_INIT][Col - KPD_COL_INIT];
			    }
			}
		}

		// return the column high
		DIO_SetPinValue(KPD_PORT, Col, DIO_HIGH);

	}
	return ReturnData;
}

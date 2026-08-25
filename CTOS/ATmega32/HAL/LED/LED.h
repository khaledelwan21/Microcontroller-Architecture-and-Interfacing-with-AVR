
/****************************************************************/
/******* Author    : Khaled Ahmed Elwan         *****************/
/******* Date      : 23 Aug 2026                *****************/
/******* Version   : 1.0                        *****************/
/******* File Name : LED.h            *****************/
/****************************************************************/


#ifndef LED_H_
#define LED_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

typedef struct {

	u8 port ;
	u8 pin  ;

}led_type ;


void LED_Init( led_type) ;

void LED_ON (led_type) ;

void LED_OFF (led_type) ;




#endif

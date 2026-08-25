
/****************************************************************/
/******* Author    : Khaled Ahmed Elwan         *****************/
/******* Date      : 23 Aug 2026                *****************/
/******* Version   : 1.0                        *****************/
/******* File Name : BUZZER.h            *****************/
/****************************************************************/


#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

typedef struct {

	u8 port ;
	u8 pin  ;

}buzzer_type ;


void BUZZER_Init( buzzer_type) ;

void BUZZER_ON (buzzer_type) ;

void BUZZER_OFF (buzzer_type) ;




#endif

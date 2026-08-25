
/****************************************************************/
/******* Author    : Khaled Ahmed Elwan         *****************/
/******* Date      : 23 Aug 2026                *****************/
/******* Version   : 1.0                        *****************/
/******* File Name : 7SEGMENT.h            *****************/
/****************************************************************/


#ifndef _7SEGMENT_H_
#define _7SEGMENT_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#define COMMON_CATHOUDE 0
#define COMMON_ANODE 1

typedef struct {

	u8 port ;
	u8 type ;
}seg_type ;


void SEG_Init( seg_type) ;

void SEG_Display (seg_type ,u8) ;






#endif

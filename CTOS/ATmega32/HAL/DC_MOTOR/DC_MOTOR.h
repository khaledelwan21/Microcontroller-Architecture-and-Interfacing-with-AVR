/*
 *  file Name : DC_MOTOR.h
 *  Author    : Khaled Ahmed Elwan
 *  Date : 27/8/2026
 *  Version : 1.0
 */


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "STD_TYPES.h"
typedef struct
{

    u8 port ;
    u8 pin1 ;
    u8 pin2 ;
}motor_type ;


void DC_MOTOR_Init(motor_type motor) ;
void DC_MOTOR_ON_CW(motor_type motor) ;
void DC_MOTOR_ON_CCW(motor_type motor) ;
void DC_MOTOR_OFF(motor_type motor) ;















#endif /* DC_MOTOR_H_ */

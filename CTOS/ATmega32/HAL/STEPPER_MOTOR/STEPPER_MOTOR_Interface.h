/*
 *  file Name : Stepper_Motor_Interface.h
 *  Created on: 30/8/2026
 *  Author    : Khaled Ahmed Elwan
 *  Description : 
 */

#ifndef HAL_STEPPER_MOTOR_STEPPER_MOTOR_INTERFACE_H_
#define HAL_STEPPER_MOTOR_STEPPER_MOTOR_INTERFACE_H_

#include "BIT_MATH.h"
#include "STD_Types.h"


#define STEPPER_FULL_STEP    1
#define STEPPER_HALF_STEP    0

#define STEPPER_CLOCK_WISE       1
#define STEPPER_ANTI_CLOCK_WISE  0

#define ANGLE_45	0
#define ANGLE_90	1
#define ANGLE_135	2
#define ANGLE_180	3
#define ANGLE_225	4
#define ANGLE_270	5
#define ANGLE_315	6
#define ANGLE_360	7

void STEPPER_voidInit( void );
void STEPPER_voidOff ( void );
void STEPPER_voidOn  ( u8 Copy_u8StepType , u8 Copy_u8Direction , u8 Copy_u8Speed , u16 Copy_u16Degree );

#endif /* HAL_STEPPER_MOTOR_STEPPER_MOTOR_INTERFACE_H_ */

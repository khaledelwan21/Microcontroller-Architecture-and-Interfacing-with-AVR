/*
 *  file Name : KEYPAD_config.h
 *  Author    : Khaled Ahmed Elwan
 *  Date : 27/8/2026
 *  Version : 1.0
 */

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_


#include"DIO_interface.h"


#include "DIO_interface.h"


#define KPD_PORT        PORTA

#define KPD_ROW_INIT    0
#define KPD_ROW_END     3

#define KPD_COL_INIT    4
#define KPD_COL_END     7

#define KPD_R0 DIO_PIN0
#define KPD_R1 DIO_PIN1
#define KPD_R2 DIO_PIN2
#define KPD_R3 DIO_PIN3

#define KPD_C0 DIO_PIN4
#define KPD_C1 DIO_PIN5
#define KPD_C2 DIO_PIN6
#define KPD_C3 DIO_PIN7

#endif

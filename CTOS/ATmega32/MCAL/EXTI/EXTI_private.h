/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXTI_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Khaled Ahmed Elwan
 *  Layer  : MCAL
 *  SWC    : EXTI
 *
 */
#ifndef _EXTI_PRIVATE_H_
#define _EXTI_PRIVATE_H_

#define MCUCR_REG   *((volatile u8 *)0x55)
#define MCUCSR_REG  *((volatile u8 *)0x54)
#define GICR_REG    *((volatile u8 *)0x5B)
#define GIFR_REG    *((volatile u8 *)0x5A)



#define DISABLE 0
#define ENABLE 1












#endif   /**end _EXTI_PRIVATE_H_**/

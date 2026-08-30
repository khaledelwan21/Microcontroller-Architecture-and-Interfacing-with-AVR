/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXTI_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Khaled Ahmed Elwan
 *  Layer  : MCAL
 *  SWC    : EXTI
 *
 */#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

static EXTI_CallbackFunc_t EXTI_CallBack[EXTI_LINES_Count] = {NULL};

void EXTI_voidInit(void)
{
	#if EXTI_SENSE0_MODE == EXTI_LOW_LEVEL
		CLR_BIT(MCUCR_REG, 0); CLR_BIT(MCUCR_REG, 1);
	#elif EXTI_SENSE0_MODE == EXTI_ON_CHANGE
		SET_BIT(MCUCR_REG, 0); CLR_BIT(MCUCR_REG, 1);
	#elif EXTI_SENSE0_MODE == EXTI_FALLING_EDGE
		CLR_BIT(MCUCR_REG, 0); SET_BIT(MCUCR_REG, 1);
	#elif EXTI_SENSE0_MODE == EXTI_RISING_EDGE
		SET_BIT(MCUCR_REG, 0); SET_BIT(MCUCR_REG, 1);
	#endif

	#if EXTI_SENSE1_MODE == EXTI_LOW_LEVEL
		CLR_BIT(MCUCR_REG, 2); CLR_BIT(MCUCR_REG, 3);
	#elif EXTI_SENSE1_MODE == EXTI_ON_CHANGE
		SET_BIT(MCUCR_REG, 2); CLR_BIT(MCUCR_REG, 3);
	#elif EXTI_SENSE1_MODE == EXTI_FALLING_EDGE
		CLR_BIT(MCUCR_REG, 2); SET_BIT(MCUCR_REG, 3);
	#elif EXTI_SENSE1_MODE == EXTI_RISING_EDGE
		SET_BIT(MCUCR_REG, 2); SET_BIT(MCUCR_REG, 3);
	#endif

	#if EXTI_SENSE2_MODE == EXTI_FALLING_EDGE
		CLR_BIT(MCUCSR_REG, 6);
	#elif EXTI_SENSE2_MODE == EXTI_RISING_EDGE
		SET_BIT(MCUCSR_REG, 6);
	#endif
}

u8 EXTI_voidDisableInterrupt(u8 Copy_u8Line)
{
	u8 Local_u8ErrorState = E_OK;
	if (Copy_u8Line == EXTI_LINE0 || Copy_u8Line == EXTI_LINE1 || Copy_u8Line == EXTI_LINE2)
	{
		CLR_BIT(GICR_REG, Copy_u8Line);
	}
	else
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	return Local_u8ErrorState;
}

u8 EXTI_voidEnableInterrupt(u8 Copy_u8Line)
{
	u8 Local_u8ErrorState = E_OK;
	if (Copy_u8Line == EXTI_LINE0 || Copy_u8Line == EXTI_LINE1 || Copy_u8Line == EXTI_LINE2)
	{
		SET_BIT(GICR_REG, Copy_u8Line);
	}
	else
	{
		Local_u8ErrorState = E_NOT_OK;
	}
	return Local_u8ErrorState;
}

void EXTI_voidClearFlag(u8 Copy_u8Line)
{
	SET_BIT(GIFR_REG, Copy_u8Line);
}

u8 EXTI_u8GetFlag(u8 Copy_u8Line)
{
	return GET_BIT(GIFR_REG, Copy_u8Line);
}

void EXTI_voidSetCallBack(u8 Copy_u8EXTILine, void(*Copy_pvoidCallBack)(void))
{
	u8 LOC_u8Index;

	if (Copy_u8EXTILine == EXTI_LINE0) LOC_u8Index = 0;
	else if (Copy_u8EXTILine == EXTI_LINE1) LOC_u8Index = 1;
	else LOC_u8Index = 2;

	if (Copy_pvoidCallBack != NULL)
	{
		EXTI_CallBack[LOC_u8Index] = Copy_pvoidCallBack;
	}
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if (EXTI_CallBack[0] != NULL)
	{
		EXTI_CallBack[0]();
	}
	EXTI_voidClearFlag(EXTI_LINE0);
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if (EXTI_CallBack[1] != NULL)
	{
		EXTI_CallBack[1]();
	}
	EXTI_voidClearFlag(EXTI_LINE1);
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if (EXTI_CallBack[2] != NULL)
	{
		EXTI_CallBack[2]();
	}
	EXTI_voidClearFlag(EXTI_LINE2);
}

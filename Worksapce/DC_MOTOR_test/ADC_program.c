/*
 *  file Name : ADC_program.c
 *  Created on: 30/8/2026
 *  Author    : Khaled Ahmed Elwan
 *  Description : 
 */


 /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     LIB     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     MCAL     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
#include "ADC_interface.h" 
#include "ADC_private.h"
#include "ADC_config.h"



//=================================================================================================================================================================
/*Global pointer to carry the conversion result in the Asynchronous execution*/
static u16 * ADC_pu16AsynchConversionResult = NULL;

/*Global pointer to function to carry the notification function called by ISR*/
static void (* ADC_pvNotificationFunc)(void)= NULL;

/*Global flag for the ADC ISR State*/
static u8 ADC_u8ISRState ;

/*Global pointer to carry the chain Channel*/
static u8 * ADC_pu8ChainChannel ;

/*Global variable to carry the chain size*/
static u8 ADC_u8ChainSize ;

/*Global variable to indicate for the current ADC Chain*/
static u8 ADC_u8Index ;

/*Global flag for the ADC Busy State*/
static u8 ADC_u8State= IDLE ;

//=================================================================================================================================================================
void ADC_voidInit(void)
{
	/*Select the voltage reference*/
	#if ADC_VREF == AREF
		CLR_BIT(ADMUX , ADMUX_REFS0) ;
		CLR_BIT(ADMUX , ADMUX_REFS1) ;

	#elif ADC_VREF == AVCC
		SET_BIT(ADMUX , ADMUX_REFS0) ;
		CLR_BIT(ADMUX , ADMUX_REFS1) ;

	#elif ADC_VREF == INTERNAL_2_56
		SET_BIT(ADMUX , ADMUX_REFS0) ;
		SET_BIT(ADMUX , ADMUX_REFS1) ;

	#else
		#error "Wrong ADC_VREF config"

	#endif


	/*Set Left Adjust Result*/
	#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
			CLR_BIT(ADMUX , ADMUX_ADLAR) ;

	#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
			SET_BIT(ADMUX , ADMUX_ADLAR) ;

	#else
		#error "Wrong ADC_ADJUSTMENT config"
	
	#endif 

	/*Set Prescaler Value*/
	ADSAR &= ADC_PRE_MASK ;
	ADSAR |= ADC_PRESCALLER ;

	/* ENABLE The Peripheral & Interrupt  */
	
	/*Enable ADC Peripheral*/
	#if ADC_STATUS == ADC_DISABLE
		CLR_BIT(ADSAR , ADSAR_ADEN) ;
	#elif ADC_STATUS == ADC_ENABLE
		SET_BIT(ADSAR , ADSAR_ADEN) ;
	#else
	#error "Wrong ADC_STATUS config"
	#endif 

	/*Enable ADC Interrupt*/
	#if INT_STATUS == INT_DISABLE
		CLR_BIT(ADSAR , ADSAR_ADIE) ;
	#elif INT_STATUS == INT_ENABLE
		SET_BIT(ADSAR , ADSAR_ADIE) ;
	#else
	#error "Wrong INT_STATUS config"
	#endif 

}



//----------------------------------------------------------------------------------------------------------------------------------------------------

void ADC_voidEnable (void)
{
	SET_BIT(ADSAR , ADSAR_ADEN) ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void ADC_voidDisable (void)
{
	CLR_BIT(ADSAR , ADSAR_ADEN) ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void ADC_voidInterruptEnable (void)
{
	SET_BIT(ADSAR , ADSAR_ADIE) ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void ADC_voidInterruptDisable (void)
{
	CLR_BIT(ADSAR , ADSAR_ADIE) ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC_u8SetPrescaler (u8 Copy_u8Prescaler)
{
	u8 Local_u8ErrorState = E_OK ;

	if (Copy_u8Prescaler < 8)
	{
		/*Set Prescaler Value*/
		ADSAR &= ADC_PRE_MASK ;
		ADSAR |= Copy_u8Prescaler ;
	}
    else
    {
        Local_u8ErrorState = E_NOT_OK;
    }

	return Local_u8ErrorState ;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC_u8SetTriggerSource (u8 Copy_u8TriggerSource)
{
	u8 Local_u8ErrorState = E_OK ;

	if (Copy_u8TriggerSource <= ADC_TRIGGER_TIMER1_CAPT)
	{
		/*Clear the ADTS bits first*/
		SFIOR &= ADTS_MASK ;          /* ADTS_MASK = 0b00011111 */

		/*Set the required trigger source*/
		SFIOR |= (Copy_u8TriggerSource << ADTS0) ;
	}
	else
	{
		Local_u8ErrorState = E_NOT_OK; ;
	}

	return Local_u8ErrorState ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC_u8EnableAutoTrigger (void)
{
	SET_BIT(ADSAR , ADSAR_ADATE) ;
	return OK ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC_u8DisableAutoTrigger (void)
{
	CLR_BIT(ADSAR , ADSAR_ADATE) ;
	return OK ;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC_u8GetResultSync (u8 Copy_u8Channel , u16 * Copy_pu16Result)
{
	u8 Local_u8ErrorState = E_OK ;
	u32 Local_u32TimeoutCounter = 0 ;
	if (Copy_pu16Result != NULL)
	{
		if (ADC_u8State == IDLE)
		{
			/*ADC is now Busy*/
			ADC_u8State = BUSY ;

			/*Set required channel*/
			ADMUX &= ADC_CH_MASK ;
			ADMUX |= Copy_u8Channel ;

			/*Start Conversion*/
			SET_BIT(ADSAR , ADSAR_ADSC) ;

			/*Waiting until the conversion is complete*/
			while (((GET_BIT(ADSAR , ADSAR_ADIF)) == 0) && (Local_u32TimeoutCounter < ADC_TIMEOUT))
			{
				Local_u32TimeoutCounter++ ;
			}
			if (Local_u32TimeoutCounter == ADC_TIMEOUT)
			{
				Local_u8ErrorState = TIMEOUT_STATE ;
			}
			else
			{
				/*Clear the interrupt flag*/
				SET_BIT(ADSAR , ADSAR_ADIF) ;

				/*Return Conversion Result*/
				#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
					*Copy_pu16Result = (ADCL|(ADCH << 8))  ;

				#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
					*Copy_pu16Result = ADCH ;
				#else
					#error "Wrong ADC_ADJUSTMENT config"

				#endif
			}

			/*ADC is IDLE*/
			ADC_u8State = IDLE ;
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE ;
		}


	}
	else
	{
		Local_u8ErrorState = NULL_POINTER ;
	}
	return Local_u8ErrorState ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
u8 ADC_u8StartConversionAsynch (u8 Copy_u8Channel , u16 * Copy_pu16Result , void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState =E_OK ;

	if ((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		if (ADC_u8State == IDLE)
		{
			/*ADC is now Busy*/
			ADC_u8State = BUSY ;

			/*Set ISR State*/
			ADC_u8ISRState = SINGLE_CHANNEL_ASYNCH ;

			/*Initialize the global result pointer*/
			ADC_pu16AsynchConversionResult = Copy_pu16Result;

			/*Initialize the global notification function pointer*/
			ADC_pvNotificationFunc= Copy_pvNotificationFunc;

			/*Set required channel*/
			ADMUX &= ADC_CH_MASK ;
			ADMUX |= Copy_u8Channel ;

			/*Start Conversion*/
			SET_BIT(ADSAR , ADSAR_ADSC) ;

			/*ADC Conversion Complete Interrupt Enable*/
			SET_BIT(ADSAR , ADSAR_ADIE) ;
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE ;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER ;
	}

	return Local_u8ErrorState ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC_u8StartChainAsynch (Chain_t * Copy_Chain)
{
	u8 Local_u8ErrorState = E_OK ;

	if ((Copy_Chain != NULL) && (Copy_Chain->Channel != NULL) && (Copy_Chain->NotificationFunc != NULL) && (Copy_Chain->Result))
	{
		if (ADC_u8State == IDLE)
		{
			/*ADC is now Busy*/
			ADC_u8State = BUSY ;

			/*Set ISR State*/
			ADC_u8ISRState = CHAIN_CHANNEL_ASYNCH ;

			/*Assign the ADC data globally*/
			ADC_pu16AsynchConversionResult = Copy_Chain->Result ;
			ADC_pu8ChainChannel = Copy_Chain->Channel ;
			ADC_u8ChainSize = Copy_Chain->Size ;
			ADC_pvNotificationFunc = Copy_Chain->NotificationFunc ;

			/*Set Index to first element*/
			ADC_u8Index = 0 ;

			/*Set required channel*/
			ADMUX &= ADC_CH_MASK ;
			ADMUX |= ADC_pu8ChainChannel[ADC_u8Index] ;

			/*Start Conversion*/
			SET_BIT(ADSAR , ADSAR_ADSC) ;

			/*ADC Conversion Complete Interrupt Enable*/
			SET_BIT(ADSAR , ADSAR_ADIE) ;
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE ;
		}

	}
	else
	{
		Local_u8ErrorState = NULL_POINTER ;
	}
	return Local_u8ErrorState ;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC_u8StartFreeRunningAsynch (u8 Copy_u8Channel , u16 * Copy_pu16Result , void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState = E_OK ;

	if ((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		if (ADC_u8State == IDLE)
		{
			/*ADC is now Busy*/
			ADC_u8State = BUSY ;

			/*Set ISR State*/
			ADC_u8ISRState = FREE_RUNNING_ASYNCH ;

			/*Initialize the global result pointer*/
			ADC_pu16AsynchConversionResult = Copy_pu16Result;

			/*Initialize the global notification function pointer*/
			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			/*Set required channel*/
			ADMUX &= ADC_CH_MASK ;
			ADMUX |= Copy_u8Channel ;

			/*Select Free Running as the trigger source*/
			SFIOR &= ADTS_MASK ;
			SFIOR |= (ADC_TRIGGER_FREE_RUNNING << ADTS0) ;

			/*Enable Auto Trigger*/
			SET_BIT(ADSAR , ADSAR_ADATE) ;

			/*ADC Conversion Complete Interrupt Enable*/
			SET_BIT(ADSAR , ADSAR_ADIE) ;

			/*Start first conversion, the rest triggers automatically by hardware*/
			SET_BIT(ADSAR , ADSAR_ADSC) ;
		}
		else
		{
			Local_u8ErrorState = BUSY_STATE ;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER ;
	}

	return Local_u8ErrorState ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

u8 ADC_u8StopFreeRunning (void)
{
    u8 Local_u8ErrorState = E_OK ;

	if (ADC_u8State == BUSY)
	{
		/*Disable Auto Trigger - stops the self-retriggering loop*/
		CLR_BIT(ADSAR , ADSAR_ADATE) ;

		/*Disable the Conversion Complete Interrupt*/
		CLR_BIT(ADSAR , ADSAR_ADIE) ;

		/*ADC is IDLE again*/
		ADC_u8State = IDLE ;
    }
    else
    {
        Local_u8ErrorState = E_NOT_OK;
	}

	return Local_u8ErrorState ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------

void __vector_16 (void)  __attribute__((signal)) ;
void __vector_16 (void)
{
	if (ADC_u8ISRState == SINGLE_CHANNEL_ASYNCH)
	{
		/*Return Conversion Result*/
		#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
			*ADC_pu16AsynchConversionResult = (ADCL|(ADCH << 8)) ;
		#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
			*ADC_pu16AsynchConversionResult = ADCH ;
		#else
			#error "Wrong ADC_ADJUSTMENT config"
		#endif

		/*ADC is IDLE*/
		ADC_u8State = IDLE ;

		/*Call Notification Function*/
		ADC_pvNotificationFunc() ;

		/*Disable the Conversion Complete Interrupt*/
		CLR_BIT(ADSAR , ADSAR_ADIE) ;
	}
	else if (ADC_u8ISRState == FREE_RUNNING_ASYNCH)
	{
		/*Return Conversion Result*/
		#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
			*ADC_pu16AsynchConversionResult = (ADCL|(ADCH << 8)) ;
		#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
			*ADC_pu16AsynchConversionResult = ADCH ;
		#else
			#error "Wrong ADC_ADJUSTMENT config"
		#endif

		/*Call Notification Function - triggered on every new sample*/
		ADC_pvNotificationFunc() ;

		/*No ADC_u8State = IDLE and no CLR_BIT(ADIE) here,
		  because the hardware (ADATE) keeps re-triggering conversions
		  automatically, so we don't stop anything*/
	}
	else   /*CHAIN_CHANNEL_ASYNCH*/
	{
		/*Return Conversion Result*/
		#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
			ADC_pu16AsynchConversionResult[ADC_u8Index] = (ADCL|(ADCH << 8)) ;
		#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
			ADC_pu16AsynchConversionResult[ADC_u8Index] = ADCH ;
		#else
			#error "Wrong ADC_ADJUSTMENT config"
		#endif

		/*Increment Data index of the chain*/
		ADC_u8Index++ ;

		if (ADC_u8Index == ADC_u8ChainSize)
		{
			/*ADC is IDLE*/
			ADC_u8State = IDLE ;

			/*Call Notification Function*/
			ADC_pvNotificationFunc() ;

			/*Disable the Conversion Complete Interrupt*/
			CLR_BIT(ADSAR , ADSAR_ADIE) ;
		}
		else
		{
			/*Set required channel*/
			ADMUX &= ADC_CH_MASK ;
			ADMUX |= ADC_pu8ChainChannel[ADC_u8Index] ;

			/*Start Conversion*/
			SET_BIT(ADSAR , ADSAR_ADSC) ;
		}
	}
}

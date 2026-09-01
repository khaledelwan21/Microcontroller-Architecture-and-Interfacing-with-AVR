/*
 *  file Name : ADC_interface.h
 *  Created on: 3/8/2026
 *  Author    : Khaled Ahmed Elwan
 *  Description : 
 */
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


#define ADC_DISABLE             0
#define ADC_ENABLE              1

#define INT_DISABLE             0
#define INT_ENABLE              1

#define AREF                    0
#define AVCC                    1
#define INTERNAL_2_56           3


#define RIGHT_ADJUSTMENT        0
#define LEFT_ADJUSTMENT         1

//Channel
#define ADC_CHANNEL0            0
#define ADC_CHANNEL1            1
#define ADC_CHANNEL2            2
#define ADC_CHANNEL3            3
#define ADC_CHANNEL4            4
#define ADC_CHANNEL5            5
#define ADC_CHANNEL6            6
#define ADC_CHANNEL7            7

//Trigger Source
#define ADC_TRIGGER_FREE_RUNNING          0b000
#define ADC_TRIGGER_ANALOG_COMPARATOR     0b001
#define ADC_TRIGGER_EXT_INT0              0b010
#define ADC_TRIGGER_TIMER0_COMPA          0b011
#define ADC_TRIGGER_TIMER0_OVF            0b100
#define ADC_TRIGGER_TIMER1_COMPB          0b101
#define ADC_TRIGGER_TIMER1_OVF            0b110
#define ADC_TRIGGER_TIMER1_CAPT           0b111

//Prescaler
#define ADC_PRE_2               0
#define ADC_PRE_4               2
#define ADC_PRE_8               3
#define ADC_PRE_16              4
#define ADC_PRE_32              5
#define ADC_PRE_64              6
#define ADC_PRE_128             7

typedef struct 
{
	u8*  Channel ;
	u16* Result  ;
	u8   Size    ;
	void (*NotificationFunc)(void);
}Chain_t ;


void ADC_voidInit               ( void);
u8   ADC_u8GetResultSync        ( u8 Copy_u8Channel , u16* Copy_pu16Result                                         );
u8   ADC_u8StartConversionAsynch( u8 Copy_u8Channel , u16* Copy_pu16Reading , void(*Copy_pvNotificationFunc)(void) );
u8   ADC_u8StartChainAsynch     ( Chain_t * Copy_Chain);

void ADC_voidEnable           (void);
void ADC_voidDisable          (void);
void ADC_voidInterruptEnable  (void);
void ADC_voidInterruptDisable (void);

u8 ADC_u8SetPrescaler (u8 Copy_u8Prescaler);

u8 ADC_u8SetTriggerSource (u8 Copy_u8TriggerSource) ;
u8 ADC_u8EnableAutoTrigger  (void) ;
u8 ADC_u8DisableAutoTrigger (void) ;

u8 ADC_u8StartFreeRunningAsynch (u8 Copy_u8Channel , u16 * Copy_pu16Result , void (*Copy_pvNotificationFunc)(void)) ;
u8 ADC_u8StopFreeRunning (void) ;


#endif /* ADC_INTERFACE_H_ */
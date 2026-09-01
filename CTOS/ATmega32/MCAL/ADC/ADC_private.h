/*
 *  file Name : ADC_private.h
 *  Created on: 30/8/2026
 *  Author    : Khaled Ahmed Elwan
 *  Description : 
 */
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADC_PRE_MASK				0b11111000
#define ADC_CH_MASK				    0b11100000

/* ADMUX Bits   */
#define ADMUX_REFS1         7							//Reference selection bit1
#define ADMUX_REFS0         6							//Reference selection bit0
#define ADMUX_ADLAR         5							//ADC left adjust result

#define ADC_CHANNEL_0  0
#define ADC_CHANNEL_1  1
#define ADC_CHANNEL_2  2



#define ADMUX     *((volatile u8 *)0x27)
#define ADSAR	  *((volatile u8*)0x26)		//ADC control and status register A
#define ADCL      *((volatile u8 *)0x24)
#define ADCH      *((volatile u8 *)0x25)


#define SFIOR  *((volatile u8 *)0x50)



#define ADC_DATA_RE 		*((volatile u16*)0x24)		//ADC Low + High	



#define ADSAR_ADEN			7							//ADC enable
#define ADSAR_ADSC			6                           //Start conversion
#define ADSAR_ADATE		    5                           //Auto trigger enable
#define ADSAR_ADIF			4                           //Interrupt flag
#define ADSAR_ADIE			3                           //Interrupt enable
#define ADSAR_ADPS2		    2                           //Prescaler bit2
#define ADSAR_ADPS1		    1                           //Prescaler bit1
#define ADSAR_ADPS0		    0                           //Prescaler bit0


#define ADTS0         5
#define ADTS1         6
#define ADTS2         7
#define ADTS_MASK     0b00011111


/*==================== ADC ISR States ====================*/
#define SINGLE_CHANNEL_ASYNCH   0
#define FREE_RUNNING_ASYNCH     1    
#define CHAIN_CHANNEL_ASYNCH    2


#define IDLE 			0
#define BUSY			1
/*ADC Function Return Error States*/
#define OK               0
#define NULL_POINTER     1
#define BUSY_STATE        2
#define TIMEOUT_STATE     3
#define WRONG_OPTION      4

#endif

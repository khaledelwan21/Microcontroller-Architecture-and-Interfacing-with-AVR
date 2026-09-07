/*
 *  file Name : SPI_interface.h
 *  Created on: 7/9/2026
 *  Author    : Khaled Ahmed Elwan
 *  Description : 
 */

 #ifndef SPI_INTERFACE_H_
 #define SPI_INTERFACE_H_



void SPI_VoidInit(void);
u8 SPI_u8Tranceive (u8 Copy_u8TData , u8 * Copy_u8RData) ;
u8 SPI_u8BufferTranceiverSynch (u8 * Copy_u8TData , u8 * Copy_u8RData , u8 Copy_u8BufferSize) ;


#define SPI_INTERRUPT_DISABLE					0
#define SPI_INTERRUPT_ENABLE 					1

#define SPI_DISABLE								0
#define SPI_ENABLE 								1

#define SPI_DATA_LSB_FIRST 						0
#define SPI_DATA_MSP_FIRST 						1

#define SPI_MASTER								0
#define SPI_SLAVE 								1

#define SPI_RISING_LEADING_FALLING_TRAILING 	0
#define SPI_FALLING_LEADING_RISING_TRAILING		1

#define SPI_SAMPLE_LEADING_SETUP_TRAILING 		0
#define SPI_SETUP_LEADING_SAMPLE_TRAILING		1

#define SPI_FREQ_DIVIDED_BY_2					0
#define SPI_FREQ_DIVIDED_BY_4					1
#define SPI_FREQ_DIVIDED_BY_8					2
#define SPI_FREQ_DIVIDED_BY_16					3
#define SPI_FREQ_DIVIDED_BY_32					4
#define SPI_FREQ_DIVIDED_BY_64					5
#define SPI_FREQ_DIVIDED_BY_128					6



#endif
/*
 *  file Name : SPI_private.h
 *  Created on: 7/9/2026
 *  Author    : Khaled Ahmed Elwan
 *  Description : 
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/*SPI Register */
#define SPI_SPCR_REG  *((volatile u8*)0x2D)
#define SPI_SPSR_REG  *((volatile u8*)0x2E)
#define SPI_SPDR_REG  *((volatile u8*)0x2F)

/*SPI Control Register */
#define SPCR_SPIE			7
#define SPCR_SPE			6
#define SPCR_DORD			5
#define SPCR_MSTR			4
#define SPCR_CPOL			3
#define SPCR_CPHA			2
#define SPCR_SPR1			1
#define SPCR_SPR0			0
/*SPI Status Register */
#define SPSR_SPIF			7
#define SPSR_WCOL			6
#define SPSR_SPI2X			0




#endif
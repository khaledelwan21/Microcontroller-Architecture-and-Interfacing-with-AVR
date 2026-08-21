/*
 * main.c
 *
 *  Created on: Aug 21, 2026
 *      Author: khaled
 */


/*
 * main.c
 *
 *  Created on: Aug 21, 2026
 *      Author: khaled
 */


#define F_CPU 11059200UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= (1 << PD1);   // PB0 Output

    while (1)
    {

        PORTD &= ~(1 << PD1);  // LED OFF

    }
}

/*
 * BLINK.c
 *
 * Created: 27-09-2020 7.50.20 PM
 * Author : Subhranil Das
 */ 


// Blinking the inbuilt LED on a Arduino NANO


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>						// THIS HEADER IS NEEDED TO USE THE DELAY FUNCTION

int main(void)
{
    DDRB |= 1<<PORTB5;						// DATA DIRECTION OF PORTB PIN 5 SET TO OUTPUT
	
    while (1) 
    {
		PORTB |= 1<<PORTB5;					// PORTB BIT 5 SET TO 1 WHICH SETS THE OUTPUT HIGH
		_delay_ms(100);						// WAIT 100 MS 
		PORTB &= ~(1<<PORTB5);				// PORTB BIT 5 SET TO 0 WHICH SETS THE OUTPUT LOW
		_delay_ms(900);						// WAIT 900 MS
    }
}


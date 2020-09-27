/*
 * UART.c
 *
 * Created: 27-09-2020 9.39.55 PM
 * Author : Subhranil Das
 */ 

#define F_CPU 16000000

#include <util/delay.h>
#include <avr/io.h>
#include "USART_ATMEGA328.h"

int main(void)
{
	USART_Init(MYUBRR);
    
    while (1) 
    {
		
		
		USART_Write("Hello World \n");
		_delay_ms(1000);
    }
}

/*
 * ADC.c
 *
 * Created: 29-09-2020 9.06.24 PM
 * Author : Subhranil Das
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "USART_ATMEGA328.h"

void INIT_ADC(void);
int ADC_READ(uint8_t);

int main(void)
{
	
	USART_Init(MYUBRR);
    INIT_ADC();
	
    while (1) 
    {
		int val = ADC_READ(0);
		USART_Write_int(val);
		USART_Write(" ");
		val = ADC_READ(1);
		USART_Write_int(val);
		USART_Write(" ");
		val = ADC_READ(2);
		USART_Write_int(val);
		USART_Write(" ");
		val = ADC_READ(3);
		USART_Write_int(val);
		USART_Write(" ");
		val = ADC_READ(4);
		USART_Write_int(val);
		USART_Write(" ");
		val = ADC_READ(5);
		USART_Write_int(val);
		USART_Write(" \n");
		
		_delay_ms(100);
    }
}

void INIT_ADC(void){
	
	ADMUX = 0b01000000;
	ADCSRA = 0b10000100;
	
}

int ADC_READ(uint8_t channel){
	DIDR0 = channel;
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	ADCSRA |= (1<<ADIF);
	return ADC;
}


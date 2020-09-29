#ifndef USART_ATMEGA328
#define USART_ATMEGA328

#include <avr/interrupt.h>
#include <stdio.h>

/* UART RELATED DEFINITIONS */
#define FOSC 16000000
#define BAUD 57600								// ANY BAUD ABOVE THIS IS HIGHLY ERROR AFFECTED IN THIS MICRO DONT USE
#define MYUBRR FOSC/16/BAUD-1
/* END OF UART RELATED DEFINITIONS */

/* ALL UART RELATED FUNCTIONS AND VARIABLES */

void USART_Init(unsigned int);
void USART_Transmit(unsigned char);
void USART_Write(char *);
void USART_Write_int(int);
void USART_Write_float(float);

char rx_data;
char rx_buffer[32];
int count_max = 32;
int count = 0;

/* END OF ALL UART RELATED FUNCTIONS AND VARIABLES */


void USART_Init(unsigned int ubrr){
	
	UBRR0H = (char)(ubrr>>8);
	UBRR0L = (char)(ubrr);
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0C = (3<<UCSZ00);
	
}

void USART_Transmit(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void USART_Write(char *data)
{
	for (int i = 0;data[i] != '\0' ; i++){
		USART_Transmit(data[i]);
	}
}

void USART_Write_int(int data)
{
	char arr[20];
	sprintf(arr,"%d", data);
	USART_Write(arr);
}
void USART_Write_float(float val){
	char arr[20];
	sprintf(arr,"%f",val);
	USART_Write(arr);
}

ISR(USART_RX_vect){
	rx_data = UDR0;
	if(count == count_max) count = 0;
	rx_buffer[count] = rx_data;
	count++;
}


#endif
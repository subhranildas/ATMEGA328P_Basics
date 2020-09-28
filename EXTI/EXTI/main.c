/*
 * EXTI.c
 *
 * Created: 29-09-2020 3.01.34 AM
 * Author : Subhranil Das
 */ 

#define  F_CPU 16000000


#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>								// Awesome header to use bool without any hassle
#include "USART_ATMEGA328.h"						// UART header 

void INIT_EXTI0(bool rising, bool falling);
void INIT_EXTI1(bool rising, bool falling);

/*	--Some Recommendation--	*/
// Always try to use rising or falling edge interrupts
// For Rising edge interrupt use an external pull down for stability
// For both Rising and falling interrupt based on application either use internal pull up or external pull down
// As low level interrupt does not require clock use it for wake up from sleep mode cases
/*	-----------------------	*/

int main(void)
{
	sei();											// Enable global interrupt
	USART_Init(MYUBRR);								// USART Enabled 
	
    INIT_EXTI0(true,false);							// Rising edge interrupt enabled External pull down required
	INIT_EXTI1(false,true);							// Falling edge interrupt enabled Internal pull up is enabled in software
	
	USART_Write("Interrupt Test Ready >>>> \n");
    while (1) 
    {
    }
}

void INIT_EXTI0(bool rising, bool falling){
	
	if(rising == true && falling == true){
		EICRA |= (1<<ISC00);
		EICRA &= ~(1<<ISC01);
	}
	else if(rising == true && falling == false){
		EICRA |= (1<<ISC00);
		EICRA |= (1<<ISC01);
		
	}
	else if(rising == false && falling == true){
		EICRA &= ~(1<<ISC00);
		EICRA |= (1<<ISC01);
		PORTD |= (1<<PORTD2);
	}
	else{
		/* ANY LOW LABEL CAUSES AN INTERRUPT */
		EICRA &= ~(1<<ISC00);
		EICRA &= ~(1<<ISC01);
		PORTD |= (1<<PORTD2);
	}
	
	EIMSK |= (1<<INT0);
}

void INIT_EXTI1(bool rising, bool falling){
	if(rising == true && falling == true){
		EICRA |= (1<<ISC10);
		EICRA &= ~(1<<ISC11);
	}
	else if(rising == true && falling == false){
		EICRA |= (1<<ISC10);
		EICRA |= (1<<ISC11);
		
	}
	else if(rising == false && falling == true){
		EICRA &= ~(1<<ISC10);
		EICRA |= (1<<ISC11);
		PORTD |= (1<<PORTD3);
	}
	else{
		/* ANY LOW LABEL CAUSES AN INTERRUPT */
		EICRA &= ~(1<<ISC10);
		EICRA &= ~(1<<ISC11);
		PORTD |= (1<<PORTD3);
	}
	
	EIMSK |= (1<<INT1);
}


// INTERRUPT 0 VECT
ISR(INT0_vect){
	USART_Write("Interrupt 0 triggered \n");
}
// INTERRUPT 1 VECT
ISR(INT1_vect){
	USART_Write("Interrupt 1 triggered \n");
}
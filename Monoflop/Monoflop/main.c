/*
 * Monoflop.c
 *
 * Created: 28.11.2023 15:21:50
 * Author : Parsa
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#define LOW_TIME_MS 50
#define HIGH_TIME_MS 500

volatile uint16_t counter = 0;
volatile bool active = false;

ISR(TIMER0_COMPA_vect) {
	if(active == true){
		++counter;
	}
}

ISR(INT0_vect) {
	if(active == false){
		active = true;
		counter = 0;
		TCCR0B |= (1 << CS02);
	}
}

void initInt0() {
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);
	EIFR |= (1 << INTF0);
}

void initTimer0() {
	TCCR0A |= (1 << WGM01);
	OCR0A = 63;
	TIMSK0 |= (1 << OCIE0A);
	TIFR0 |= (1 << OCF0A);
}

int main(void) {
	initTimer0();
	initInt0();
	
	sei();
	
	DDRA = 0xFF;
	PORTA = 0x00;
	
	while (1) {
		if (active) {
			if(counter >= LOW_TIME_MS + HIGH_TIME_MS){
				PORTA &= ~(1 << PINA0);
				TCCR0B &= ~(1 << CS02);
				active = false;
				} else if(counter >= LOW_TIME_MS){
				PORTA |= (1 << PINA0);
			}
			} else {
			PORTA &= ~(1 << PINA0);
		}
	}
}



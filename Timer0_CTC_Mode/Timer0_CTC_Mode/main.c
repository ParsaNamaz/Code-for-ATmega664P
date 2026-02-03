/*
 * Timer0_CTC_Mode.c
 *
 * Created: 13.10.2023 14:04:59
 * Author : Parsa
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void initTimer0() {
	TCCR0A = (1 << WGM01);
	TCCR0A &= ~((1<<WGM02)|(1<<WGM00));
	TCCR0B |= ((1<<CS00)|(1<<CS02)); //Prescaler clk/1024
	TCCR0B &= ~((1<<CS01));
	OCR0A = 93;
	TIMSK0 |= (1 << OCIE0A);
}
int main() {
	DDRB |= (1 << PB4);
	PORTB &= ~(1 << PB4);
	initTimer0();
	sei();
	while (1) {
	}
	return 0;
}
ISR(TIMER0_COMPA_vect) {
	// Toggle PB4 (Invertiere den Zustand)
	PORTB ^= (1 << PB4);
}


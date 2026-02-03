/*
 * CTC_Timer1.c
 *
 * Created: 18.10.2023 09:40:33
 * Author : Parsa
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
volatile uint8_t portBState = 0;
void initTimer1() {
	TCCR1A = 0;
	TCCR1B = (1 << WGM12);  // CTC-Modus aktivieren
	TCCR1B |= (1 << CS12) | (1 << CS10);
	OCR1A = 46874;
	TIMSK1 = (1 << OCIE1A);  // Aktiviere den Compare Match Interrupt für Timer1
}
int main() {
	DDRB = 0xFF;
	initTimer1();
	sei();
	while (1) {
	}
	return 0;
}
ISR(TIMER1_COMPA_vect) {
	portBState++;
	PORTB = portBState;
}

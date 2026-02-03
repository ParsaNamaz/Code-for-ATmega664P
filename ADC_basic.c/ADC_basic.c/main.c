/*
 * ADC_basic.c.c
 *
 * Created: 05.12.2023 15:35:39
 * Author : Parsa
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

volatile uint8_t ergebnis;

void initADC(){
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1);
	//ADMUX |= (1<<MUX1);
	ADMUX |= (1<<ADLAR);
	ADMUX |= (1<<REFS0);
}

intiTIMER1(){
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);
	TIMSK1 = (1<<OCIE1A);
	OCR1A=1562;
}

ISR(TIMER1_COMPA_vect){
	ADCSRA |= (1<<ADSC);
	while(ADCSRA &(1<<ADSC)){
	}
	ergebnis = ADCH;
	PORTC = ergebnis;
	
}

int main(void)
{
	initADC();
	intiTIMER1();
	DDRC = 0xFF;
	DDRA = 0x00;
	PORTC = 0x00;
	sei();
	while (1)
	{
		
	}
}

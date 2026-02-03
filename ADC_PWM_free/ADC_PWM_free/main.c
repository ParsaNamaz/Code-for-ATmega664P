/*
 * ADC_PWM_free.c
 *
 * Created: 02.01.2024 11:35:47
 * Author : Parsa
 */ 

#include <avr/io.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#define F_CPU 16000000

InitADC() {
	ADCSRA |= (1 << ADEN); //Enable
	ADCSRA |= (1 << ADSC); //Start Conversion
	ADCSRA |= (1 << ADIE); //Interrupt enable
	
	ADCSRA |= (1 << ADPS2) || (1 << ADPS1);     //Prescaler setzen

	ADMUX |= (1 << ADLAR);     //Ergebnis Linksbündig
	ADMUX |= (1 << REFS0);    //Referenzspannung auf Vcc
	
	//Auto trigger enable
	ADCSRA |= (1 << ADATE);
}

InitFastPWM() {
	//Timermode -> Fast PWM
	TCCR0A |= (1 << WGM00);
	TCCR0A |= (1 << WGM01);
	
	//Prescaler auf 8 setzen
	TCCR0B |= (0 << CS00);
	TCCR0B |= (1 << CS01);
	TCCR0B |= (0 << CS02);
	
	//Set to inverting mode
	//TCCR0A |= (1 << COM0A0);
	TCCR0A |= (1 << COM0A1);
	
	//Timer Interrupts aktivieren
	TIMSK0 = (1 << OCIE0A);
}

ISR(ADC_vect) {
	OCR0A = ADCH;
}

int main(void)
{
	DDRB = 0xFF;
	InitADC();
	InitFastPWM();
	sei();
	
	while (1)
	{
	}
}




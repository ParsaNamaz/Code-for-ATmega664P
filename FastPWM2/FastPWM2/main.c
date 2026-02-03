/*
 * FastPWM2.c
 *
 * Created: 17.11.2023 11:08:40
 * Author : Parsa
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>


uint8_t cnt=0;
void initTimer0(void){
	TCCR0A |= (1 << WGM00);
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS01);
	//TCCR0A |= (1 << COM0A0);
	TCCR0A |= (1 << COM0A1);
	TIMSK0 |= (1 << OCIE0A);
}
ISR(TIMER0_COMPA_vect){
	cnt++;
	
if(cnt==30){
	OCR0A += 1;
	OCR0A = OCR0A % 254;
	cnt=0;
}

	
}

int main(void)
{
    DDRB = 0xFF;
    initTimer0();
    sei();
    /* Replace with your application code */
    while (1) 
    {
    }
}


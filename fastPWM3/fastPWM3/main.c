/*
 * fastPWM3.c
 *
 * Created: 21.11.2023 15:11:40
 * Author : Parsa
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
const uint16_t pwmtable_8D[32]=

{

	0, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 11, 13, 16, 19, 23,

	27, 32, 38, 45, 54, 64, 76, 91, 108, 128, 152, 181, 215, 255

};

uint8_t cnt=0;
uint8_t i=0;
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
	if(cnt==200){
		i++;
		OCR0A = pwmtable_8D[i];
		OCR0A = OCR0A % 254;
		cnt=0;
		if(i>=32){
			i=0;
		}
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


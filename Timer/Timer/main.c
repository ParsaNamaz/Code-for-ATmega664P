/*
 * Interrupt-C.c
 *
 * Created: 21.03.2023 08:02:41
 * Author : Starkey
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#undef F_CPU
#define F_CPU 16000000
#define NUMINT 61






void initializeTimer(){
	//TIMER1_COMPA_vect = 0x4000;
	TCCR0A = 0x00;
	TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00);
	TCCR0B = 0x05;
	OCR0A = 0xFF;
	TIMSK0 |= (1 << TOIE0);
}

void toggleLED(){
	static uint8_t ledStatus = 0;
	ledStatus = (ledStatus == 0) ? 1:0;
	PORTC = ledStatus;
}


int main(void){
	
	DDRC |= (1 << 0); //write to port c
	
	initializeTimer();
	sei();
    while (1)  {
		
		
		
    }
}

ISR(TIMER0_OVF_vect){
	
	static uint8_t cnt = 0;
	cnt++;
	cnt %= NUMINT;
	
	if (cnt == 0)
	{
		
		toggleLED();
	}
	
}


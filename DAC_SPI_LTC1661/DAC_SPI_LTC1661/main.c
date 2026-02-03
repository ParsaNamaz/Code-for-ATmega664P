/*
 * DAC_SPI_LTC1661.c
 *
 * Created: 20.02.2024 15:32:50
 * Author : parsa
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
uint16_t volt=0;
void initSPI() {
	DDRB |= (1<<PB4) | (1<<PB5) | (1<<PB7); 
	SPCR |= (1<<SPE) | (1<<MSTR); 
	SPCR |= (1<<SPR0); 
}

void SPITrans(uint16_t data) {
	PORTB &= ~(1<<PB4); 
	SPDR = ((data >> 6) & 0x0F) | 0x90; 
	while(!(SPSR & (1<<SPIF))); 
	SPDR = data << 2; 
	while(!(SPSR & (1<<SPIF))); 
	PORTB |= (1<<PB4); 
}

int main(void) {
	initSPI();
	sei();
	while (1) {
		if(volt>=0b1001111111111100){
			volt=0b1001000000000000;
			}else{
				volt=volt+4;
			}
		SPITrans(volt);
	}
	return 0;
}
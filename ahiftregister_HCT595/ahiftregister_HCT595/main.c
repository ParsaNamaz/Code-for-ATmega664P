/*
 * ahiftregister_HCT595.c
 *
 * Created: 30.01.2024 15:01:56
 * Author : parsa
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void SPI_Init(){
	// Set SS, MOSI, SCK as output
	DDRB |= (1<<PB4) | (1<<PB5) | (1<<PB7);
	// Enable SPI, set as Master, set clock rate fck/16
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR1);
}

void SPI_trans(unsigned char data){
	// Select the slave (active low SS)
	PORTB &= ~(1<<PB0);
	// Load data into the buffer
	SPDR = data;
	// Wait until transmission is complete
	while(!(SPSR & (1<<SPIF)));
	// Deselect the slave
	PORTB |= (1<<PB0);
}
int main(void)
{
	// Initialize SPI
	SPI_Init();
	// Set PB0 and PB1 as output
	DDRB |= (1<<PB0) | (1<<PB1);
	while (1)
	{
		// Transmit 0xAA using SPI
		SPI_trans(0xAA);
		// Delay for 500 ms
		_delay_ms(500);
		// Transmit 0x55 using SPI
		SPI_trans(0x55);
		// Delay for 500 ms
		_delay_ms(500);
	}
}


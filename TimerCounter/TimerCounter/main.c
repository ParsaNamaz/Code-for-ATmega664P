#include <avr/io.h>
#include <avr/interrupt.h>

// BCD TABLE is located in Flash Mem // contains the Address of the first element of the list
uint8_t BCD_TABLE [] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};

volatile uint8_t count = 0; // initial count value

ISR(TIMER0_OVF_vect) // Timer0 OVF interrupt service routine
{
	count++; // increment count value
}

int main(void)
{
	// read input data from Port A
	// write bits 7:4
	DDRB = (1 << PINB4) | (1 << PINB5) |(1 << PINB6) |(1 << PINB7);

	// digits a-g, "." are connected to PORTB
	DDRA = 0xFF;

	// enable Timer0 OVF interrupt
	TCCR0B |= (1 << CS02) | (1 << CS00); // prescaler = 1024
	TIMSK0 |= (1 << TOIE0); // enable Timer0 OVF interrupt
	sei(); // enable global interrupts

	while (1)
	{
		uint8_t digits_in = (PINB & 0x0F);
		uint8_t dot_a_g = BCD_TABLE[digits_in];

		if (count >= 20) // count for 1 second (assuming prescaler is set to 1024)
		{
			count = 0; // reset count value
			static uint8_t num = 0; // static variable to remember last displayed digit

			num++; // increment number
			if (num > 9) num = 0; // reset number if greater than 9

			PORTA = BCD_TABLE[num]; // display number on 7-segment display
		}
	}
}
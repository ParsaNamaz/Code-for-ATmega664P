/*
 * Seg7_Single.c
 *
 * Created: 07.03.2023 08:06:14
 * Author : Parsa
 */ 

#include <avr/io.h>
// BCD_TABLE contains the Address of the first element of the list
// BCD_TABLE is located in Flash Memory
uint8_t BCD_TABLE [] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47};

int main(void)
{
    // READ INPUT DATA FROM PORTA BITS 3:0
	// Write Bits 7:4
	DDRA = (1<<PINA7) | (1 <<PINA6) | (1<<PINA5) | (1<<PINA4);
	
	// digits a-g, "." are connected to PORTB
	DDRB = 0xFF;
	
	uint8_t digits_in =(PINA & 0x0F); //read data from PORTA (3.0)
	uint8_t dot_a_g = 0;
    while (1) 
    {
		digits_in =(PINA & 0x0F);
		dot_a_g=BCD_TABLE[digits_in];
		PORTB= dot_a_g;
		
		
    }
}



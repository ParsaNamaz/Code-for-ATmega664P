/*
 * Blink01.c
 *
 * Created: 19.09.2023 14:57:05
 * Author : Parsa
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRD |=(1<<PD7);
    while (1) 
    {
		PORTD ^=(1<<PD7);
		
		
    }
}


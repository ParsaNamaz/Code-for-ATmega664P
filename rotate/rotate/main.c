/*
 * rotate.c
 * Created: 19.09.2023 15:38:26
 * Author : Parsa
 * controller:ATmega644P
 * rotate lower 6bit on PortA
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
uint8_t rotate(uint8_t); //rotate funktion
int main(void)
{
	uint8_t led = 0b00000101;
	DDRA = 0xFF;
	PORTA =led;
	while (1)
	{
		PORTA=led;
		_delay_ms(1000);
		led=rotate(led);
	}
}
uint8_t rotate(uint8_t led) {
	led = (led << 1); //shifting bit to left
	if (led>=64) { //deleting bit and puting it on the first place 
		led=led-64+1;
		} 
	return led;
}



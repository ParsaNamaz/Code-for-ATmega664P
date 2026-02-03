/*
 * rotate_timer.c
 *
 * Created: 03.10.2023 15:56:55
 * Author : Parsa
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
uint8_t led = 0b0000111;
uint8_t loop = 63;
void initTimer0(){
	TCCR0A &= ~((1<<WGM01)|(1<<WGM00)); //clear WGM01 and WGM00 -> Normal Mode
	TCCR0B &= ~((1<<WGM02)); // clear WGM02 -> Normal Mode
	TCCR0B |= ((1<<CS00)|(1<<CS02)); //Prescaler clk/1024
	TCCR0B &= ~((1<<CS01));//Prescaler clk/1024
	TIMSK0 |= (1<<TOIE0);//Timer Overflow Interrupt enable
}
ISR(TIMER0_OVF_vect){
	loop--;
	if(loop == 0){
		led = rotate(led);
		loop = 63;
	}
}
int rotate(int temp){
	temp <<= 1; // left shift
	if(temp >= 64) // 6 bit

	{
		temp = temp - 64 + 1; // reset
	}
	PORTA = temp;
	return temp;
}
int main(void)
{
	initTimer0();
	DDRA = 0xFF;
	PORTA = led;
	sei();
	while (1)
	{
	}
}

/*
 * ADC.c
 *
 * Created: 16.05.2023 13:26:35
 * Author : Parsa
 */ 



	 

	 #include <avr/io.h>
	 #include <avr/interrupt.h>
	 #include <stdlib.h>
	 #include <stdio.h>

	 // BCD TABLE is located in Flash Mem // contains the Address of the first element of the list
	 uint8_t BCD_TABLE [] = {0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F, 0x00};

	 static uint8_t count = 0; // initial count value
	 static uint8_t H = 0;
	 static uint8_t Z = 0;
	 static uint8_t E = 0;
	 static uint16_t input = 0;
	 static uint16_t cnt = 0;

	 I

	 ISR(TIMER0_OVF_vect){
		 cnt++;
	 }


	 void intialiseADC(){
		 ADMUX |= (1 << REFS0) | (1 << ADLAR) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);
		 ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
		 ADCSRB |= (0 << ADTS2);
	 }

	 int main(void)
	 {
		 intialiseADC();
		 DDRD = 0xFF; // Multiplexing write
		 DDRC = 0xFF; // LED write
		 
		 
		 
		 
		 // enable Timer0 OVF interrupt
		 TCCR0B |= (1 << CS02);  // prescaler = 1024
		 TIMSK0 |= (1 << TOIE0); // enable Timer0 OVF interrupt
		 sei(); // enable global interrupts

		 while (1)
		 {
			 
			 
			 // Multiplexing.exe
			 
			 static uint8_t num = 0;
			 num++;
			 if (num > 2) {num = 0;}
			 if(num==0){
				 PORTD = 0x04;
				 PORTC = BCD_TABLE[H];
			 }
			 if(num==1) {
				 PORTD = 0x02;
				 PORTC = BCD_TABLE[Z];
			 }
			 if(num==2){
				 PORTD = 0x01;
				 PORTC = BCD_TABLE[E];
			 }
			 
			 
			 // PinsA read here!!!!
			 input = ADCH * 2;
			 if(cnt > 30){
				 E = input % 10;
				 cnt = 0;
			 }
			 input /= 10;
			 Z = input % 10;
			 input /= 10;
			 H = input % 10;
			 
			 if(E == 0 && Z == 0 && H == 0){
				 E = 10;
			 }
			 if(Z == 0 & H == 0){
				 Z = 10;
			 }
			 if(H == 0){
				 H = 10;
			 }
			 
			 
			 
		 }
		 
		 
	 }
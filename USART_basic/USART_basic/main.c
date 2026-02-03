/*
 * USART_basic.c
 *
 * Created: 09.04.2024 15:34:01
 * Author : parsa
 */ 

#include <avr/io.h>

void InitUART(unsigned int baudRate)
{
	DDRB = 0xFF; // Setzt alle Pins des Port B als Ausgänge
	UBRR0H = (unsigned char)(baudRate>>8); // Setzt die höherwertigen Bits der Baudrate
	UBRR0L = (unsigned char)baudRate; // Setzt die niederwertigen Bits der Baudrate
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Aktiviert den Empfänger und Sender
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); // Legt das Rahmenformat fest: 8 Datenbits, 1 Stoppbit, keine Parität
}

void SendData( unsigned char dataToSend )
{
	while ( !( UCSR0A & (1<<UDRE0)) ); // Wartet, bis der Übertragungspuffer leer ist
	UDR0 = dataToSend; // Legt die Daten in den Puffer, sendet die Daten
}

unsigned char ReceiveData( void )
{
	while ( !(UCSR0A & (1<<RXC0)) ); // Wartet, bis Daten empfangen wurden
	return UDR0; // Holt die empfangenen Daten aus dem Puffer und gibt sie zurück
}

int main(void)
{
	char *message = {"Hallo"}; // Nachricht, die gesendet werden soll
	InitUART(103); // Initialisiert den UART mit der Baudrate 9600
	DDRC = 0xFF; // Setzt alle Pins des Port C als Ausgänge
	while (1)
	{
		if(ReceiveData() == 's'){ // Wenn das empfangene Zeichen 's' ist
			
			for(int i = 0; i < 5; i++){ // Sendet jedes Zeichen der Nachricht "Hallo"
				SendData(message[i]);
			}
		}
	}
}



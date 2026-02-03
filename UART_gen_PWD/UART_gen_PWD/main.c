/*
 * UART_gen_PWD.c
 *
 * Created: 16.04.2024 14:55:28
 * Author : parsa
 */ 

#include <avr/io.h>
#include <stdlib.h> // Für die Funktion rand()

void InitUART0(unsigned int baudRate)
{
	DDRB = 0xFF; // Setzt alle Pins des Port B als Ausgänge
	UBRR0H = (unsigned char)(baudRate>>8); // Setzt die höherwertigen Bits der Baudrate
	UBRR0L = (unsigned char)baudRate; // Setzt die niederwertigen Bits der Baudrate
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Aktiviert den Empfänger und Sender
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00)|(1<<UPM01); // Legt das Rahmenformat fest: 8 Datenbits, 2 Stoppbits, even parity
}

void InitUART1(unsigned int baudRate)
{
	DDRB = 0xFF; // Setzt alle Pins des Port B als Ausgänge
	UBRR1H = (unsigned char)(baudRate>>8); // Setzt die höherwertigen Bits der Baudrate
	UBRR1L = (unsigned char)baudRate; // Setzt die niederwertigen Bits der Baudrate
	UCSR1B = (1<<RXEN1)|(1<<TXEN1); // Aktiviert den Empfänger und Sender
	UCSR1C = (1<<UCSZ11)|(1<<UCSZ10)|(1<<UPM11); // Legt das Rahmenformat fest: 8 Datenbits, 2 Stoppbits, even parity
}

void SendData0(unsigned char dataToSend)
{
	while (!(UCSR0A & (1<<UDRE0))); // Wartet, bis der Übertragungspuffer leer ist
	UDR0 = dataToSend; // Legt die Daten in den Puffer, sendet die Daten
}

void SendData1(unsigned char dataToSend)
{
	while (!(UCSR1A & (1<<UDRE1))); // Wartet, bis der Übertragungspuffer leer ist
	UDR1 = dataToSend; // Legt die Daten in den Puffer, sendet die Daten
}

unsigned char ReceiveData(void)
{
	while (!(UCSR0A & (1<<RXC0))); // Wartet, bis Daten empfangen wurden
	return UDR0; // Holt die empfangenen Daten aus dem Puffer und gibt sie zurück
}

char getRandomUpperCaseLetter()
{
	return 'A' + rand() % 26; // Generiert zufälligen Großbuchstaben von 'A' bis 'Z'
}

char getRandomLowerCaseLetter()
{
	return 'a' + rand() % 26; // Generiert zufälligen Kleinbuchstaben von 'a' bis 'z'
}

int main(void)
{
	InitUART0(103); // Initialisiert den UART mit der Baudrate 9600
	InitUART1(103);
	DDRC = 0xFF; // Setzt alle Pins des Port C als Ausgänge

	srand(42); // Initialisiert den Zufallszahlengenerator mit einem festen Wert für die Reproduzierbarkeit

	while (1)
	{
		if (ReceiveData() == 'g') // Wenn das empfangene Zeichen 'g' ist
		{
			char password[6]; // Passwort als Array von 5 Zeichen plus Nullterminator
			
			// Generiere das Passwort
			int upperCount = 0;
			int lowerCount = 0;
			for (int i = 0; i < 5; i++)
			{
				if (upperCount < 3 && (lowerCount == 2 || rand() % 2 == 0))
				{
					password[i] = getRandomUpperCaseLetter(); // Großbuchstabe
					upperCount++;
				}
				else
				{
					password[i] = getRandomLowerCaseLetter(); // Kleinbuchstabe
					lowerCount++;
				}
			}
			password[5] = '\0'; // Nullterminator

			// Sende das Passwort über UART0 undt UART1
			for (int i = 0; i < 5; i++)
			{
				SendData0(password[i]);
				SendData1(password[i]);
			}
			
			
		}
	}
}



#include <avr/io.h>

void InitUART0(unsigned int baudRate)
{
	DDRB = 0xFF; // Setzt alle Pins des Port B als Ausgänge
	UBRR0H = (unsigned char)(baudRate>>8); // Setzt die höherwertigen Bits der Baudrate
	UBRR0L = (unsigned char)baudRate; // Setzt die niederwertigen Bits der Baudrate
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Aktiviert den Empfänger und Sender
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00)|(1<<UPM01); // Legt das Rahmenformat fest: 8 Datenbits, 2 Stoppbits, even parity
}

void InitUART1(unsigned int baudRate)
{
	DDRB = 0xFF; // Setzt alle Pins des Port B als Ausgänge
	UBRR1H = (unsigned char)(baudRate>>8); // Setzt die höherwertigen Bits der Baudrate
	UBRR1L = (unsigned char)baudRate; // Setzt die niederwertigen Bits der Baudrate
	UCSR1B = (1<<RXEN1)|(1<<TXEN1); // Aktiviert den Empfänger und Sender
	UCSR1C = (1<<UCSZ11)|(1<<UCSZ10)|(1<<UPM11); // Legt das Rahmenformat fest: 8 Datenbits, 2 Stoppbits, even parity
}

unsigned char ReceiveData(void)
{
	while (!(UCSR0A & (1<<RXC0))); // Wartet, bis Daten empfangen wurden
	return UDR0; // Holt die empfangenen Daten aus dem Puffer und gibt sie zurück
}

unsigned char ReceiveData1(void)
{
	while (!(UCSR1A & (1<<RXC1))); // Wartet, bis Daten empfangen wurden
	return UDR1; // Holt die empfangenen Daten aus dem Puffer und gibt sie zurück
}

void SendData(unsigned char dataToSend)
{
	while (!(UCSR0A & (1<<UDRE0))); // Wartet, bis der Übertragungspuffer leer ist
	UDR0 = dataToSend; // Legt die Daten in den Puffer, sendet die Daten
}

int main(void)
{
	int AnzPasswort = 0;
	InitUART0(103); // Initialisiert den UART mit der Baudrate 9600
	InitUART1(103);
	DDRD = 0xFF; // Setzt alle Pins des Port D als Ausgänge
	
	while (1)
	{
		// Empfange das Passwort von Crumb1
		char password[6];
		for (int i = 0; i < 5; i++) {
			password[i] = ReceiveData1();
		}
		password[5] = '\0';
		
		// Zähle die Anzahl der 'x'-Zeichen im Passwort
		int xCount = 0;
		for (int i = 0; i < 5; i++) {
			if (password[i] == 'x' || password[i] == 'X') {
				xCount++;
			}
		}
		AnzPasswort=AnzPasswort+5;
		// Sende die Anzahl der 'x'-Zeichen an den Terminalserver (HTERM)
		SendData(xCount + '0');
		SendData('/');
		if(AnzPasswort>9){
			AnzPasswort=0;
			SendData()
		}
		SendData(AnzPasswort+'0');
		SendData('/');
		
		for(int i=0; i<5; i++){
			SendData(password[i]);
		}
		
	}
}
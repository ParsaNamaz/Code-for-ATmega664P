/*
 * Normalformen.c
 *
 * Created: 28.03.2023 18:44:18
 * Author : Parsa
 */ 

#include <avr/io.h>             // Input/Output Library für AVR
#include <util/delay.h>         // Library für _delay_ms()

#define delay (1000.0)          // Zeit zwischen den ausgaben in ms

int main(void) {
	DDRA = 0x07;                // Setzt die ersten 3 Bits von PORTA auf Ausgang
	uint8_t out = 0;            // Variable für die Ausgabe

	while (1) {                 // Endlosschleife
		PORTA = out;            // Schreibt den Wert von out in PORTA
		out++;                  // Erhöht den Wert von out um 1

		if(out > 0x07){         // Wenn out größer als 0x07 ist
			out = 0;            // Setzt out auf 0
		}

		_delay_ms(delay);       // Wartet für die delay konstante
	}
}


/*
 * I2C Basic.c
 *
 * Created: 14.03.2024 13:02:02
 * Author : parsa
 */ 
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000	// 16MHz
#define WR_DEV 0x90		// Write Device address 0x90
#define RD_DEV 0x91		// Read Device address 0x91
#define BITRATE 42		// Overall division factor 100

void TWInit(unsigned char bitrate) {
	// Set SCL to 100kHz
	TWBR |= bitrate;
	TWSR = 0x00;		// Set division factor 4^0 = 1
}

void TWTransmit(unsigned char address, unsigned char data_tx) {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);		// Set start condition
	while(!(TWCR & (1 << TWINT)));							// Wait until TWINT is set
	TWDR = address;
	TWCR = (1 << TWINT) | (1 << TWEN);						// Send address
	while(!(TWCR & (1 << TWINT)));							// Wait until TWINT is set
	TWDR = data_tx;
	TWCR = (1 << TWINT) | (1 << TWEN);						// Send data
	while(!(TWCR & (1 << TWINT)));							// Wait until TWINT is set
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);		// Set stop condition
}

uint16_t TWReceive(unsigned char address) {
	uint16_t data_HB, data_LB;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);		// Set start condition
	while(!(TWCR & (1 << TWINT)));							// Wait until TWINT is set
	TWDR = address;
	TWCR = (1 << TWINT) | (1 << TWEN);						// Send address
	while(!(TWCR & (1 << TWINT)));							// Wait until TWINT is set
	// Acknowledge status can be directly added to the data read transfer
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);		// Start receiving 1st data + ACK
	while(!(TWCR & (1 << TWINT)));							// Wait until TWINT is set
	data_HB = TWDR;
	TWCR = (1 << TWINT) | (1 << TWEN);						// Start receiving 2nd data + NACK
	while(!(TWCR & (1 << TWINT)));							// Wait until TWINT is set
	data_LB = TWDR;
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);		// Set stop condition
	return (data_HB << 8) | data_LB;
}

int main(void)
{
	TWInit(BITRATE);
	DDRA = 0xFF;
	while (1)
	{
		PORTA = TWReceive(RD_DEV) >> 8;
		_delay_us(50);
	}
}
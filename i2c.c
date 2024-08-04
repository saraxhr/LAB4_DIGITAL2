/*
 * i2c.c
 *
 * Created: 8/2/2024 11:48:14 AM
 *  Author: sarax
 */ 

#include "i2c.h"
#include <util/twi.h>

void I2C_init(void) {
	// Configurar el reloj I2C
	TWSR = 0x00;
	TWBR = ((F_CPU/SCL_CLOCK) - 16) / 2;
}

void I2C_start(void) {
	// Enviar condición de inicio
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void I2C_stop(void) {
	// Enviar condición de parada
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
	while (TWCR & (1 << TWSTO));
}

void I2C_write(uint8_t data) {
	// Cargar datos en el registro de datos
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

uint8_t I2C_read_ack(void) {
	// Leer con ACK
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t I2C_read_nack(void) {
	// Leer sin ACK
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

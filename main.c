/*
 * maestro.c
 *
 * Created: 8/2/2024 11:57:38 AM
 * Author : sarax
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include "LCD8.h"
#include "i2c.h"

// Direcciones de los esclavos
#define SLAVE1_ADDRESS 0x08
#define SLAVE2_ADDRESS 0x09

// Prototipo de la función para convertir entero a cadena
void intToStr(uint16_t num, char* str);

void setup(void);
void loop(void);

int main(void) {
	setup();
	while (1) {
		loop();
	}
}

void setup() {
	// Inicializar el bus I2C y la pantalla LCD
	I2C_init();
	InLCD();
}

void loop() {
	// Variables para almacenar valores recibidos
	uint8_t contador = 0;
	uint16_t potValue = 0;

	// Solicitar valor del contador al esclavo 1
	I2C_start();
	I2C_write((SLAVE1_ADDRESS << 1) | 0); // Dirección + bit de escritura
	I2C_stop();

	I2C_start();
	I2C_write((SLAVE1_ADDRESS << 1) | 1); // Dirección + bit de lectura
	contador = I2C_read_nack(); // Leer el valor del contador
	I2C_stop();

	// Solicitar valor del potenciómetro al esclavo 2
	I2C_start();
	I2C_write((SLAVE2_ADDRESS << 1) | 0); // Dirección + bit de escritura
	I2C_stop();

	I2C_start();
	I2C_write((SLAVE2_ADDRESS << 1) | 1); // Dirección + bit de lectura
	potValue = I2C_read_ack() << 8; // Leer la parte alta
	potValue |= I2C_read_nack(); // Leer la parte baja
	I2C_stop();

	// Mostrar valores en la pantalla LCD
	LCD_CMD(0x01); // Limpiar pantalla
	LCD_W_String("Cont: ");
	char buffer[16];  // Tamaño adecuado para la cadena
	intToStr(contador, buffer);  // Convertir contador a cadena
	LCD_W_String(buffer);

	LCD_cursor(1, 2);
	LCD_W_String("Pot: ");
	intToStr(potValue, buffer);  // Convertir valor del potenciómetro a cadena
	LCD_W_String(buffer);

	_delay_ms(500); // Esperar un momento antes de la próxima lectura
}

void intToStr(uint16_t num, char* str) {
	// Inicializar el índice y el buffer temporal
	int i = 0;
	char temp[6];  // Buffer temporal para los dígitos (máximo 5 dígitos + terminador)

	// Convertir cada dígito del número a la base deseada
	do {
		temp[i++] = (num % 10) + '0';  // Obtener el dígito y convertirlo a carácter
		num /= 10;
	} while (num > 0);

	// Invertir la cadena para obtener el orden correcto
	int j;
	for (j = 0; j < i; j++) {
		str[j] = temp[i - j - 1];
	}

	str[i] = '\0';  // Agregar terminador de cadena
}

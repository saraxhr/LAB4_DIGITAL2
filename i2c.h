/*
 * i2c.h
 *
 * Created: 8/2/2024 11:47:57 AM
 *  Author: sarax
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#define F_CPU 16000000UL
#define SCL_CLOCK 100000L

void I2C_init(void);
void I2C_start(void);
void I2C_stop(void);
void I2C_write(uint8_t data);
uint8_t I2C_read_ack(void);
uint8_t I2C_read_nack(void);

#endif /* I2C_H_ */

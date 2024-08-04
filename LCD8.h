/*
 * LCD8.h
 *
 * Created: 8/2/2024 11:14:49 AM
 *  Author: sarax
 */ 


#ifndef LCD8_H_
#define LCD8_H_

#include <avr/io.h>
#include <util/delay.h>

// Prototipos de funciones para el control del LCD
void InLCD(void);
void Puerto(char a);
void LCD_CMD(char b);
void LCD_Write(char c);
void LCD_W_String(char *d);
void shift_izq(void);
void shift_der(void);
void LCD_cursor(char c, char f);

#endif /* LCD8_H_ */

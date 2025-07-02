#ifndef MATRIX8x8_H
#define MATRIX8x8_H

#include <avr/io.h>

// Configuración de pines (ajusta según tu conexión)
#define MATRIX_ROW_PORT   PORTD
#define MATRIX_ROW_DDR    DDRD
#define MATRIX_COL_PORT   PORTB
#define MATRIX_COL_DDR    DDRB

// Pines de filas (PORTD)
#define ROW0  PD0
#define ROW1  PD1
#define ROW2  PD2
#define ROW3  PD3
#define ROW4  PD4
#define ROW5  PD5
#define ROW6  PD6
#define ROW7  PD7

// Pines de columnas (PORTB)
#define COL0  PB0
#define COL1  PB1
#define COL2  PB2
#define COL3  PB3
#define COL4  PB4
#define COL5  PB5
#define COL6  PB6
#define COL7  PB7

// Funciones
void matrix8x8_init(void);
void matrix8x8_display_static(const uint8_t pattern[8]);

#endif
#ifndef MAX7219_H
#define MAX7219_H

#include <avr/io.h>
#include <util/delay.h>

// Configuración de pines SPI
#define MAX7219_PORT    PORTB
#define MAX7219_DDR     DDRB
#define MAX7219_PIN     PINB

#define MAX7219_CS      PB2     // Pin CS (Chip Select) - Pin 10
#define MAX7219_MOSI    PB3     // Pin MOSI (Data) - Pin 11  
#define MAX7219_SCK     PB5     // Pin SCK (Clock) - Pin 13

// Registros del MAX7219
#define MAX7219_REG_NOOP        0x00
#define MAX7219_REG_DIGIT0      0x01
#define MAX7219_REG_DIGIT1      0x02
#define MAX7219_REG_DIGIT2      0x03
#define MAX7219_REG_DIGIT3      0x04
#define MAX7219_REG_DIGIT4      0x05
#define MAX7219_REG_DIGIT5      0x06
#define MAX7219_REG_DIGIT6      0x07
#define MAX7219_REG_DIGIT7      0x08
#define MAX7219_REG_DECODE      0x09
#define MAX7219_REG_INTENSITY   0x0A
#define MAX7219_REG_SCANLIMIT   0x0B
#define MAX7219_REG_SHUTDOWN    0x0C
#define MAX7219_REG_DISPLAYTEST 0x0F

// Valores para registros
#define MAX7219_SHUTDOWN_MODE   0x00
#define MAX7219_NORMAL_MODE     0x01
#define MAX7219_DECODE_NONE     0x00
#define MAX7219_DECODE_ALL      0xFF
#define MAX7219_TEST_ON         0x01
#define MAX7219_TEST_OFF        0x00

// Macros para control de pines
#define MAX7219_CS_HIGH()       (MAX7219_PORT |= (1 << MAX7219_CS))
#define MAX7219_CS_LOW()        (MAX7219_PORT &= ~(1 << MAX7219_CS))
#define MAX7219_MOSI_HIGH()     (MAX7219_PORT |= (1 << MAX7219_MOSI))
#define MAX7219_MOSI_LOW()      (MAX7219_PORT &= ~(1 << MAX7219_MOSI))
#define MAX7219_SCK_HIGH()      (MAX7219_PORT |= (1 << MAX7219_SCK))
#define MAX7219_SCK_LOW()       (MAX7219_PORT &= ~(1 << MAX7219_SCK))

// Funciones públicas
void max7219_init(void);
void max7219_send_byte(uint8_t data);
void max7219_write_register(uint8_t address, uint8_t data);
void max7219_set_intensity(uint8_t intensity);
void max7219_clear_display(void);
void max7219_set_pixel(uint8_t row, uint8_t col, uint8_t state);
void max7219_set_row(uint8_t row, uint8_t data);
void max7219_set_column(uint8_t col, uint8_t data);
void max7219_display_pattern(uint8_t pattern[8]);
void max7219_shutdown(uint8_t mode);
void max7219_test_display(uint8_t test);
void max7219_fill_display(uint8_t value);
void max7219_invert_display(void);
void max7219_scroll_left(void);
void max7219_scroll_right(void);
void max7219_scroll_up(void);
void max7219_scroll_down(void);

#endif // MAX7219_H
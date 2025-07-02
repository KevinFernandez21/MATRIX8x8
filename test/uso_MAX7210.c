//#define F_CPU 16000000UL  // Frecuencia del reloj del microcontrolador

#include <avr/io.h>
#include <util/delay.h>
#include "HAL/MAX7219.h"

// Patrones de ejemplo
uint8_t smiley[8] = {
    0b00111100,
    0b01000010,
    0b10100101,
    0b10000001,
    0b10100101,
    0b10011001,
    0b01000010,
    0b00111100
};

uint8_t heart[8] = {
    0b00000000,
    0b01100110,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100,
    0b00011000,
    0b00000000
};

uint8_t arrow_right[8] = {
    0b00010000,
    0b00110000,
    0b01110000,
    0b11111111,
    0b11111111,
    0b01110000,
    0b00110000,
    0b00010000
};

uint8_t cross[8] = {
    0b00011000,
    0b00011000,
    0b00011000,
    0b11111111,
    0b11111111,
    0b00011000,
    0b00011000,
    0b00011000
};

uint8_t checkerboard1[8] = {
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101
};

uint8_t checkerboard2[8] = {
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010,
    0b01010101,
    0b10101010
};

int main(void) {
    // Inicializar el MAX7219
    max7219_init();
    
    while (1) {
        // Test 1: Mostrar patrones predefinidos
        max7219_display_pattern(smiley);
        _delay_ms(20);
        
        max7219_display_pattern(heart);
        _delay_ms(20);
        
        max7219_display_pattern(arrow_right);
        _delay_ms(20);
        
        max7219_display_pattern(cross);
        _delay_ms(20);
        
        
        // Test 3: Limpiar display
        max7219_clear_display();
        _delay_ms(20);
        
        // Test 4: Encender fila por fila
        for (uint8_t row = 0; row < 8; row++) {
            max7219_set_row(row, 0xFF);
            _delay_ms(20);
        }
        _delay_ms(20);
        
        // Test 5: Apagar fila por fila
        for (uint8_t row = 0; row < 8; row++) {
            max7219_set_row(row, 0x00);
            _delay_ms(20);
        }
        
        // Test 6: Encender columna por columna
        for (uint8_t col = 0; col < 8; col++) {
            max7219_set_column(col, 0xFF);
            _delay_ms(20);
        }
        _delay_ms(20);
        
        // Test 7: Apagar columna por columna
        for (uint8_t col = 0; col < 8; col++) {
            max7219_set_column(col, 0x00);
            _delay_ms(20);
        }
        
        // Test 10: Pixel que rebota
        max7219_clear_display();
        int8_t x = 0, y = 0;
        int8_t dx = 1, dy = 1;
        
        for (uint8_t i = 0; i < 100; i++) {
            max7219_clear_display();
            max7219_set_pixel(y, x, 1);
            x += dx;
            y += dy;
            if (x >= 7 || x <= 0) dx = -dx;
            if (y >= 7 || y <= 0) dy = -dy;
            
            _delay_ms(5);
        }
        
        max7219_clear_display();
        _delay_ms(1000);
    }
    
    return 0;
}
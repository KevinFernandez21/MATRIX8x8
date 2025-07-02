#include "HAL/MATRIX8x8.h"

int main(void) {
    matrix8x8_init();
    
    // Ejemplo: Dibujar una X
    uint8_t pattern[8] = {
        0b10000001,
        0b01000010,
        0b00100100,
        0b00011000,
        0b00011000,
        0b00100100,
        0b01000010,
        0b10000001
    };
    
    matrix8x8_display_pattern(pattern);
    
    while (1) {
        matrix8x8_refresh();  // Llamar continuamente para refrescar
        _delay_ms(2);         // Pequeña pausa entre refrescos
    }
}
#include "HAL/MATRIX8x8.h"

int main(void) {
    matrix8x8_init();

    // Patrón de la X (1 = LED encendido)
    uint8_t x_pattern[8] = {
        0b10000001,
        0b01000010,
        0b00100100,
        0b00011000,
        0b00011000,
        0b00100100,
        0b01000010,
        0b10000001
    };

    // Mostrar la X estáticamente
    matrix8x8_display_static(x_pattern);

    while (1) {
        // No se necesita refresco
    }
}
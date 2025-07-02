#include "MATRIX8x8.h"

void matrix8x8_init(void) {
    // Configurar filas y columnas como salidas
    MATRIX_ROW_DDR |= 0xFF; // Todas las filas (PORTD) como salidas
    MATRIX_COL_DDR |= 0xFF; // Todas las columnas (PORTB) como salidas
    
    // Apagar inicialmente
    MATRIX_ROW_PORT = 0x00;  // Filas en LOW (ánodo común)
    MATRIX_COL_PORT = 0xFF;  // Columnas en HIGH (cátodo común)
}

void matrix8x8_display_static(const uint8_t pattern[8]) {
    // Encender todas las filas simultáneamente (ánodo común)
    MATRIX_ROW_PORT = 0xFF;
    
    // Establecer el patrón de columnas (cátodo común)
    MATRIX_COL_PORT = ~pattern[0]; // Invertir bits para cátodos
    
    // Nota: Para matrices de cátodo común, usa:
    // MATRIX_ROW_PORT = ~0x00;
    // MATRIX_COL_PORT = pattern[0];
}
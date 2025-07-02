#include "max7219.h"

// Buffer interno para mantener el estado de la matriz
static uint8_t display_buffer[8];

/**
 * Inicializa el MAX7219
 */
void max7219_init(void) {
    // Configurar pines como salida
    MAX7219_DDR |= (1 << MAX7219_CS) | (1 << MAX7219_MOSI) | (1 << MAX7219_SCK);
    
    // Estado inicial correcto
    MAX7219_CS_HIGH();
    MAX7219_SCK_LOW();
    MAX7219_MOSI_LOW();
    
    _delay_ms(100);  // Delay inicial más largo
    
    // Secuencia de inicialización correcta
    max7219_write_register(MAX7219_REG_SHUTDOWN, MAX7219_SHUTDOWN_MODE);   // Shutdown mode
    _delay_ms(10);
    
    max7219_write_register(MAX7219_REG_DISPLAYTEST, MAX7219_TEST_OFF);     // Display test off
    _delay_ms(10);
    
    max7219_write_register(MAX7219_REG_DECODE, MAX7219_DECODE_NONE);       // No decode
    _delay_ms(10);
    
    max7219_write_register(MAX7219_REG_SCANLIMIT, 0x07);                   // Scan all digits (0-7)
    _delay_ms(10);
    
    max7219_write_register(MAX7219_REG_INTENSITY, 0x0F);                   // Maximum intensity
    _delay_ms(10);
    
    // Limpiar todas las filas
    for (uint8_t i = 0; i < 8; i++) {
        display_buffer[i] = 0x00;
        max7219_write_register(MAX7219_REG_DIGIT0 + i, 0x00);
        _delay_ms(5);
    }
    
    max7219_write_register(MAX7219_REG_SHUTDOWN, MAX7219_NORMAL_MODE);     // Normal mode
    _delay_ms(10);
}

/**
 * Envía un byte por SPI software
 */
void max7219_send_byte(uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        // Clock bajo antes de cambiar datos
        MAX7219_SCK_LOW();
        _delay_us(1);
        
        // Establecer el bit de datos (MSB primero)
        if (data & 0x80) {
            MAX7219_MOSI_HIGH();
        } else {
            MAX7219_MOSI_LOW();
        }
        _delay_us(1);
        
        // Clock alto para capturar el dato
        MAX7219_SCK_HIGH();
        _delay_us(1);
        
        // Shift para el siguiente bit
        data <<= 1;
    }
    // Dejar clock en bajo
    MAX7219_SCK_LOW();
}

/**
 * Escribe en un registro del MAX7219
 */
void max7219_write_register(uint8_t address, uint8_t data) {
    MAX7219_CS_LOW();
    _delay_us(1);
    
    max7219_send_byte(address);
    max7219_send_byte(data);
    
    _delay_us(1);
    MAX7219_CS_HIGH();
    _delay_us(50);  // Delay más largo entre comandos
}

/**
 * Establece la intensidad del display (0-15)
 */
void max7219_set_intensity(uint8_t intensity) {
    if (intensity > 15) intensity = 15;
    max7219_write_register(MAX7219_REG_INTENSITY, intensity);
}

/**
 * Limpia todo el display
 */
void max7219_clear_display(void) {
    for (uint8_t i = 0; i < 8; i++) {
        display_buffer[i] = 0x00;
        max7219_write_register(MAX7219_REG_DIGIT0 + i, 0x00);
    }
}

/**
 * Establece un pixel individual (row: 0-7, col: 0-7)
 */
void max7219_set_pixel(uint8_t row, uint8_t col, uint8_t state) {
    if (row > 7 || col > 7) return;
    
    if (state) {
        display_buffer[row] |= (1 << col);
    } else {
        display_buffer[row] &= ~(1 << col);
    }
    
    max7219_write_register(MAX7219_REG_DIGIT0 + row, display_buffer[row]);
}

/**
 * Establece una fila completa
 */
void max7219_set_row(uint8_t row, uint8_t data) {
    if (row > 7) return;
    
    display_buffer[row] = data;
    max7219_write_register(MAX7219_REG_DIGIT0 + row, data);
}

/**
 * Establece una columna completa
 */
void max7219_set_column(uint8_t col, uint8_t data) {
    if (col > 7) return;
    
    for (uint8_t row = 0; row < 8; row++) {
        if (data & (1 << row)) {
            display_buffer[row] |= (1 << col);
        } else {
            display_buffer[row] &= ~(1 << col);
        }
        max7219_write_register(MAX7219_REG_DIGIT0 + row, display_buffer[row]);
    }
}

/**
 * Muestra un patrón completo de 8x8
 */
void max7219_display_pattern(uint8_t pattern[8]) {
    for (uint8_t i = 0; i < 8; i++) {
        display_buffer[i] = pattern[i];
        max7219_write_register(MAX7219_REG_DIGIT0 + i, pattern[i]);
    }
}

/**
 * Control de shutdown (0 = shutdown, 1 = normal)
 */
void max7219_shutdown(uint8_t mode) {
    max7219_write_register(MAX7219_REG_SHUTDOWN, mode ? MAX7219_NORMAL_MODE : MAX7219_SHUTDOWN_MODE);
}

/**
 * Test del display (0 = off, 1 = on)
 */
void max7219_test_display(uint8_t test) {
    max7219_write_register(MAX7219_REG_DISPLAYTEST, test ? MAX7219_TEST_ON : MAX7219_TEST_OFF);
}

/**
 * Llena todo el display con un valor
 */
void max7219_fill_display(uint8_t value) {
    for (uint8_t i = 0; i < 8; i++) {
        display_buffer[i] = value;
        max7219_write_register(MAX7219_REG_DIGIT0 + i, value);
    }
}

/**
 * Invierte todos los píxeles del display
 */
void max7219_invert_display(void) {
    for (uint8_t i = 0; i < 8; i++) {
        display_buffer[i] = ~display_buffer[i];
        max7219_write_register(MAX7219_REG_DIGIT0 + i, display_buffer[i]);
    }
}

/**
 * Desplaza el contenido hacia la izquierda
 */
void max7219_scroll_left(void) {
    for (uint8_t i = 0; i < 8; i++) {
        display_buffer[i] <<= 1;
        max7219_write_register(MAX7219_REG_DIGIT0 + i, display_buffer[i]);
    }
}

/**
 * Desplaza el contenido hacia la derecha
 */
void max7219_scroll_right(void) {
    for (uint8_t i = 0; i < 8; i++) {
        display_buffer[i] >>= 1;
        max7219_write_register(MAX7219_REG_DIGIT0 + i, display_buffer[i]);
    }
}

/**
 * Desplaza el contenido hacia arriba
 */
void max7219_scroll_up(void) {
    // Mover datos una posición hacia arriba
    for (uint8_t i = 0; i < 7; i++) {
        display_buffer[i] = display_buffer[i + 1];
        max7219_write_register(MAX7219_REG_DIGIT0 + i, display_buffer[i]);
    }
    // La última fila se queda en 0
    display_buffer[7] = 0x00;
    max7219_write_register(MAX7219_REG_DIGIT7, 0x00);
}

/**
 * Desplaza el contenido hacia abajo
 */
void max7219_scroll_down(void) {
    // Mover datos una posición hacia abajo
    for (uint8_t i = 7; i > 0; i--) {
        display_buffer[i] = display_buffer[i - 1];
        max7219_write_register(MAX7219_REG_DIGIT0 + i, display_buffer[i]);
    }
    // La primera fila se queda en 0
    display_buffer[0] = 0x00;
    max7219_write_register(MAX7219_REG_DIGIT0, 0x00);
}
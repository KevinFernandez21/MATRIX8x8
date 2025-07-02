#include <avr/io.h>
#include <util/delay.h>

// Definiciones de pines según tu circuito original
#define MAX7219_CS      PB2     // Pin 10 - LOAD
#define MAX7219_MOSI    PB3     // Pin 11 - DIN  
#define MAX7219_SCK     PB5     // Pin 13 - CLK

// Macros
#define CS_HIGH()   (PORTB |= (1 << MAX7219_CS))
#define CS_LOW()    (PORTB &= ~(1 << MAX7219_CS))
#define MOSI_HIGH() (PORTB |= (1 << MAX7219_MOSI))
#define MOSI_LOW()  (PORTB &= ~(1 << MAX7219_MOSI))
#define SCK_HIGH()  (PORTB |= (1 << MAX7219_SCK))
#define SCK_LOW()   (PORTB &= ~(1 << MAX7219_SCK))

void send_byte(uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        // Clock bajo antes de cambiar datos
        SCK_LOW();
        _delay_us(1);
        
        // Establecer el bit de datos (MSB primero)
        if (data & 0x80) {
            MOSI_HIGH();
        } else {
            MOSI_LOW();
        }
        _delay_us(1);
        
        // Clock alto para capturar el dato
        SCK_HIGH();
        _delay_us(1);
        
        // Shift para el siguiente bit
        data <<= 1;
    }
    // Dejar clock en bajo
    SCK_LOW();
}

void write_register(uint8_t address, uint8_t data) {
    CS_LOW();
    _delay_us(1);
    
    send_byte(address);
    send_byte(data);
    
    _delay_us(1);
    CS_HIGH();
    _delay_us(50);  // Delay más largo entre comandos
}

void init_max7219(void) {
    // Configurar pines como salida
    DDRB |= (1 << MAX7219_CS) | (1 << MAX7219_MOSI) | (1 << MAX7219_SCK);
    
    // Estado inicial correcto
    CS_HIGH();
    SCK_LOW();
    MOSI_LOW();
    
    _delay_ms(100);  // Delay inicial más largo
    
    // Secuencia de inicialización correcta
    write_register(0x0C, 0x00);  // Shutdown mode
    _delay_ms(10);
    
    write_register(0x0F, 0x00);  // Display test: off
    _delay_ms(10);
    
    write_register(0x09, 0x00);  // Decode mode: ninguno
    _delay_ms(10);
    
    write_register(0x0B, 0x07);  // Scan limit: mostrar 8 dígitos (0-7)
    _delay_ms(10);
    
    write_register(0x0A, 0x0F);  // Intensidad: máxima
    _delay_ms(10);
    
    // Limpiar todas las filas
    for (uint8_t i = 1; i <= 8; i++) {
        write_register(i, 0x00);
        _delay_ms(5);
    }
    
    write_register(0x0C, 0x01);  // Modo normal
    _delay_ms(10);
}

int main(void) {
    init_max7219();
    
    while (1) {
        // Test básico: una fila a la vez
        for (uint8_t row = 1; row <= 8; row++) {
            write_register(row, 0xFF);  // Encender toda la fila
            _delay_ms(300);
            write_register(row, 0x00);  // Apagar la fila
            _delay_ms(100);
        }
        
        _delay_ms(500);
        
        // Test: todas las filas encendidas
        for (uint8_t row = 1; row <= 8; row++) {
            write_register(row, 0xFF);
        }
        _delay_ms(1000);
        
        // Test: todas las filas apagadas
        for (uint8_t row = 1; row <= 8; row++) {
            write_register(row, 0x00);
        }
        _delay_ms(500);
        
        // Test: patrón de ajedrez
        for (uint8_t row = 1; row <= 8; row++) {
            if (row % 2 == 1) {
                write_register(row, 0xAA);  // 10101010
            } else {
                write_register(row, 0x55);  // 01010101
            }
        }
        _delay_ms(1000);
        
        // Limpiar
        for (uint8_t row = 1; row <= 8; row++) {
            write_register(row, 0x00);
        }
        _delay_ms(500);
        
        // Test: pixel por pixel
        for (uint8_t row = 1; row <= 8; row++) {
            for (uint8_t col = 0; col < 8; col++) {
                write_register(row, (1 << col));
                _delay_ms(100);
            }
            write_register(row, 0x00);
        }
    }
    
    return 0;
}
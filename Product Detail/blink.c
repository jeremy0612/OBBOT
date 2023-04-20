#define F_CPU 2000000UL  // Set CPU clock frequency to 1MHz

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << PB0);  // Set PB0 pin as output
    
    while(1) 
    {
        PORTB ^= (1 << PB0);  // Toggle PB0 pin
        _delay_ms(1000);       // Delay for 500ms
    }
    
    return 0;
}

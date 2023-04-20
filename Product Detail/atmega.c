#define F_CPU 1000000UL  // Replace 1000000 with the frequency of your microcontroller in Hz

#include <avr/io.h>
#include <util/delay.h>

#define MOTOR1_PWM_PIN    PB1   // PB1 is OC1A pin, used for PWM output for motor 1
#define MOTOR2_PWM_PIN    PB2   // PB2 is OC1B pin, used for PWM output for motor 2

#define MOTOR1_ENABLE_PIN PD5   // PD5 is used as enable pin for motor 1
#define MOTOR2_ENABLE_PIN PD6   // PD6 is used as enable pin for motor 2

void timer1_init(void)
{
    // Set timer1 in fast PWM mode, with TOP value 0xFF
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);
    
    // Set prescaler to 8
    TCCR1B |= (1 << CS11);
    
    // Set PWM pins as output
    DDRB |= (1 << MOTOR1_PWM_PIN) | (1 << MOTOR2_PWM_PIN);
}

void motors_init(void)
{
    // Set motor enable pins as output
    DDRD |= (1 << MOTOR1_ENABLE_PIN) | (1 << MOTOR2_ENABLE_PIN);
    
    // Disable both motors initially
    PORTD &= ~((1 << MOTOR1_ENABLE_PIN) | (1 << MOTOR2_ENABLE_PIN));
}

void set_motor1_speed(uint8_t speed)
{
    OCR1A = speed;
}

void set_motor2_speed(uint8_t speed)
{
    OCR1B = speed;
}

void enable_motor1(void)
{
    PORTD |= (1 << MOTOR1_ENABLE_PIN);
}

void disable_motor1(void)
{
    PORTD &= ~(1 << MOTOR1_ENABLE_PIN);
}

void enable_motor2(void)
{
    PORTD |= (1 << MOTOR2_ENABLE_PIN);
}

void disable_motor2(void)
{
    PORTD &= ~(1 << MOTOR2_ENABLE_PIN);
}

int main(void)
{
    motors_init();
    timer1_init();
    
    while(1)
    {
        // Set motor 1 to rotate clockwise
        set_motor1_speed(200);
        enable_motor1();
        
        // Set motor 2 to rotate counterclockwise
        set_motor2_speed(100);
        enable_motor2();
        
        _delay_ms(5000);  // Run motors for 5 seconds
        
        disable_motor1();
        disable_motor2();
        
        _delay_ms(2000);  // Wait for 2 seconds before changing motor direction
    }
}

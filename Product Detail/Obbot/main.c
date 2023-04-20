#define F_CPU 2000000UL
#define UART_BAUD 19200
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "HCSR04.h"
#define C0 PC0  // Chân kết nối với cảm biến MQ5
#define PD_ALL 0xff
#define PATTERN_STOP 0b00000000
#define PATTERN_FORWARD  0b10100101
#define PATTERN_BACKWARD 0b01011010
#define PATTERN_LEFT 0b01101001
#define PATTERN_RIGHT 0b10010110
#define PATTERN_CIRCULAR 0b10101000


#define BAUDRATE ((F_CPU + (UART_BAUD * 4UL))/(UART_BAUD * 8UL)-1)
// #define PATTERN_RIGHT_1 Ob
void CLK()
{
    PORTD |= (1 << PD6);
    _delay_ms(10);
    PORTD &= ~(1 << PD6);
}
void ShiftData(uint8_t data) 
{  
    uint8_t i;
    for (i = 0; i < 8; i++) 
    {
        PORTD &= ~(1 << PD5);    
        PORTD |= ((data >> i) & 1) << PD5;
        CLK();
    }
}
void DC_motor(uint8_t mode)
{
    PORTD&= ~(1<<PD7);
    _delay_ms(5);
    uint8_t data=0x00;
    switch (mode)
    {
        case 0:
        data = PATTERN_STOP;
        break;
        case 1:
        data = PATTERN_FORWARD;
        break;
        case 2:
        data = PATTERN_BACKWARD;
        break;
        case 3:
        data = PATTERN_LEFT;
        break;
        case 4:
        data = PATTERN_RIGHT;
        break;
        case 5:
        data = PATTERN_CIRCULAR;
        break;
    }
    ShiftData(data);
    PORTD|=(1<<PD7);
    _delay_ms(1000);        

}
void uart_init (unsigned int ubrr)
{
    // the gcc compiler is able to update UBRRH and UBRRL on its own
    UBRRH = (unsigned char)(ubrr>>8);
    UBRRL = (unsigned char)ubrr;                        //
    UCSRA = (1 << U2X);                         // enable 2x mode
    UCSRB = (1<<TXEN)|(1<<RXEN);                // enable receiver and transmitter
    UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);   // 8bit data format
}

void uart_send_char(unsigned char data)
{
    while (!(UCSRA & (1<<UDRE))); // Wait for empty transmit buffer
    UDR = data; // Send data
}

void uart_send_string(char* str)
{
    while (*str)
        uart_send_char(*str++);
}

uint8_t uart_receive(void)
{
    while (!(UCSRA & (1<<RXC))); // Wait for data to be received
    return UDR; // Get and return received data from buffer
}
void setup() 
{
  // Cấu hình ADC
  ADMUX |= (1 << REFS0);  // Chọn độ chính xác của ADC (AVCC with external capacitor at AREF pin)
  ADCSRA |= (1 << ADEN);  // Bật ADC
}
void mq2_value() 
{
    uint16_t adc_value;
    setup();
  
    // Đọc giá trị ADC từ chân kết nối với MQ5
    ADMUX = (ADMUX & 0xF0) | (C0 & 0x0F);  // Chọn kênh ADC
    ADCSRA |= (1 << ADSC);  // Bắt đầu chuyển đổi ADC

    // Chờ cho quá trình chuyển đổi ADC hoàn thành
    while (ADCSRA & (1 << ADSC));

    // Đọc giá trị ADC
    adc_value = ADC ;
    uart_send_char('G');
    
    uint8_t digit1, digit2, digit3, digit4;
    digit1 = (int)adc_value / 1000;
    digit2 = ((int)adc_value / 100) % 10;
    digit3 = ((int)adc_value / 10) % 10;
    digit4 = (int)adc_value % 10;
    uart_send_char(digit1+48);
    uart_send_char(digit2+48);
    uart_send_char(digit3+48);
    uart_send_char(digit4+48);
    
    uart_send_char('-');
    uart_send_char('-');
    _delay_ms(200); 
}

int main(void)
{
    uart_init(BAUDRATE); // Initialize UART module       
    HCSR04Init();  
    DDRB |= (1 << PB0);  // Set PB0 pin as output  
    DDRD |=  (1 << PB1)|(1 << PB2) | (1 << PB3)|(1 << PB4); 
    DDRD |= (1 << PD5)|(1 << PD6) | (1 << PD7);
    DC_motor(1);                                           	
    uint8_t t;
    //uint16_t d;
    while(1)
    {
        /*
        d = ultrasonic();
        if(d < 6)
            PORTB ^= (1 << PB0);  // Toggle PB0 pin

        mq2_value();
        */

        if(UCSRA & (1<<RXC)) // Wait for data to be received
        {
            t = UDR; // Get and return received data from buffer
            if(t == 'u')
            {
                DC_motor(1);
                _delay_ms(500);
                DC_motor(0);
            }
            else if(t == 'r')
            {
                DC_motor(2);
                _delay_ms(500);
                DC_motor(0);
            }
            else if(t == 'l')
            {
                DC_motor(3);
                _delay_ms(500);
                DC_motor(0);
            }
        }
        t = 0;
        _delay_ms(200);
    }

}
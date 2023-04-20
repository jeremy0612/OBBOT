#define F_CPU 2000000UL
#define UART_BAUD 19200
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define C0 PC0  // Chân kết nối với cảm biến MQ5



#define BAUDRATE ((F_CPU + (UART_BAUD * 4UL))/(UART_BAUD * 8UL)-1)
char result[4];
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
    /*
    while (adc_value>0)
    {
        int temp = adc_value%10;
        uart_send_char(temp+48);
        adc_value /= 10;
    }
    */
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
    
    //return adc_value;
    // Tính giá trị điện áp từ giá trị ADC
    //voltage = (adc_value / 1024.0) * 5.0;

    // Tính giá trị nồng độ từ giá trị điện áp
    //mq_value = (voltage - 1.4) / 0.02;

    
 
}

int main(void)
{
    // Set PB0 as an output pin
    //DDRB |= (1 << PB0);
    uart_init(BAUDRATE); // Initialize UART module
    //int x=1234;
    while (1)
    {
        //PORTB ^= (1 << PB0);
        // Send data through HC-06
        //unsigned char i;
       //uart_send_string((char*)&x);

       //uart_send_string(mq2_value());
       mq2_value();
       //uart_send_char(); 
        
        _delay_ms(500);
    }
}
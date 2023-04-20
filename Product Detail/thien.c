#define F_CPU 2000000UL
#define UART_BAUD 19200
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define C0 PC0  // Chân kết nối với cảm biến MQ5
#define US_ERROR		-1      
#define	US_NO_OBSTACLE	-2
#define rs PD0                 
#define en PD1                 
#define US_PORT PORTC         
#define	US_PIN	PINC            
#define US_DDR 	DDRC         
#define US_TRIG_POS	PC2        
#define US_ECHO_POS	PC1 


void HCSR04Init()
{
	US_DDR|=(1<<US_TRIG_POS);
}
void HCSR04Trigger()
{  	
	US_PORT|=(1<<US_TRIG_POS);		
	_delay_us(15);					
	US_PORT&=~(1<<US_TRIG_POS);	
}
uint16_t GetPulseWidth()
{
	uint32_t i,result;
	for(i=0;i<600000;i++)
	{
		if(!(US_PIN & (1<<US_ECHO_POS)))
		  continue;	
		else
		  break;		
	}
	if(i==600000)
	   return US_ERROR;	
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);	
	TCNT1=0x00;			
	for(i=0;i<600000;i++)              
	{
		if(US_PIN & (1<<US_ECHO_POS))
		{
			if(TCNT1 > 60000) 
                break;
            else
                continue;  
		}
		else
    		break;
	}
	if(i==600000)
	   return US_NO_OBSTACLE;	
	result=TCNT1;         
	TCCR1B=0x00;
	if(result > 60000)
	   return US_NO_OBSTACLE;	
	else
	   return (result>>1);
}
uint16_t ultrasonic()
{
    HCSR04Trigger(); 
    uint16_t r=GetPulseWidth();                         
    uint16_t distance=(r*0.034/2.0)*8;
    return distance;
}
ISR(INT0_vect0){
    if(PORTB & (1<<PB0) == 1)
    {
        PORTD &= ~(1<<PD7);
        uint8_t data;
        data = PATTERN_BACKWARD;
        ShiftData(data);
        PORTD |= (1<<PD7);
        _delay_ms(10);
    }
    //return;
}

int main(void)
{
    GICR |= (1<<INT0);//KHAI BAO INTERUPT THANH GHI GICR
    MCUCR |= (1<<ISC01); //KHAI BAO NGAT 
    sei();//khai bao ngat toan cuc tren status-regis

    uart_init(BAUDRATE); // Initialize UART module       
    HCSR04Init();  
    DDRB |= (1 << PB0);  // Set PB0 pin as output  
    DDRD |=  (1 << PB1)|(1 << PB2) | (1 << PB3)|(1 << PB4); 
    DDRD |= (1 << PD5)|(1 << PD6) | (1 << PD7);
    DC_motor(0);      
                                         	
    uint8_t t;
    uint16_t d;
    while(1)
    {
        
        d = ultrasonic();
        if(d < 6)
            PORTB ^= (1 << PB0);  // Toggle PB0 pin


        mq2_value();
        

        while(UCSRA & (1<<RXC)) // Wait for data to be received
        {
            t = UDR; // Get and return received data from buffer
            if(t == 'u')
            {
                DC_motor(1);
                _delay_ms(1000);
                DC_motor(0);
            }
            else if(t == 'r')
            {
                DC_motor(2);
                _delay_ms(1000);
                DC_motor(0);
            }
            else if(t == 'l')
            {
                DC_motor(3);
                _delay_ms(1000);
                DC_motor(0);
            }
            else if(t == 'd')
            {
                DC_motor(4);
                _delay_ms(1000);
                DC_motor(0);
            }
            
        }
        t = 0;
        _delay_ms(50);
    }

}

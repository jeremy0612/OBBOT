#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
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

ISR(TIMER1_COMPA_vect)
{
    PORTB ^= (1 << PB0);  // Toggle PB0 pin
}
int main(void)
{
    HCSR04Init();  
    DDRB |= (1 << PB0);  // Set PB0 pin as output  
    //uint16_t d;
    while(1)
    {
        /*
        d = ultrasonic();
        if(d < 6)
            PORTB ^= (1 << PB0);
            _delay_ms(500);
           //sei(); 
        */
        PORTB ^= (1 << PB0);
        _delay_ms(50);
    }

}

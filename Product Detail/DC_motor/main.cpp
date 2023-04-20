#define F_CPU 2000000UL 
#include <avr/io.h>
#include <util/delay.h>

void DC_motor(uint8_t mode)
{
			switch (mode)
			{
				case 0:
					PORTD &= ~(1 << PD0);
					PORTD &= ~(1 << PD1);
					PORTD &= ~(1 << PD2);
					PORTD &= ~(1 << PD3);
					PORTD &= ~(1 << PD4);
					PORTD &= ~(1 << PD5);
					PORTD &= ~(1 << PD6);
					PORTD &= ~(1 << PD7);
					break;
				case 1:					
					PORTD |= (1 << PD0);
					PORTD &= ~(1 << PD1);
					PORTD |= (1 << PD2);
					PORTD &= ~(1 << PD3);
					PORTD &= ~(1 << PD4);
					PORTD |= (1 << PD5);
					PORTD &= ~(1 << PD6);
					PORTD |= (1 << PD7);
					break;
				case 2:
					PORTD &= ~(1 << PD0);
					PORTD |= (1 << PD1);
					PORTD &= ~(1 << PD2);
					PORTD |= (1 << PD3);
					PORTD |= (1 << PD4);
					PORTD &= ~(1 << PD5);
					PORTD |= (1 << PD6);
					PORTD &= ~(1 << PD7);
					break;
				case 3:
					PORTD |= (1 << PD0);
					PORTD &= ~(1 << PD1);
					PORTD &= ~(1 << PD2);
					PORTD |= (1 << PD3);
					PORTD &= ~(1 << PD4);
					PORTD |= (1 << PD5);
					PORTD |= (1 << PD6);
					PORTD &= ~(1 << PD7);
					break;
				case 5:
					PORTD |= (1 << PD1);
					PORTD &= ~(1 << PD0);
					PORTD &= ~(1 << PD3);
					PORTD |= (1 << PD2);
					PORTD &= ~(1 << PD5);
					PORTD |= (1 << PD4);
					PORTD |= (1 << PD7);
					PORTD &= ~(1 << PD6);
					break;
			}
			_delay_ms(1000); 
			return;
}

int main(void)
{
	DDRB &= ~(1 << PB0); 
	DDRD |= (1 << PD0) | (1 << PD1)|(1 << PD2) | (1 << PD3)|(1 << PD4) | (1 << PD5)|(1 << PD6) | (1 << PD7); // Set PD0-PD7 as output

	uint8_t mode = 0; 

	while (1)
	{			
		if(mode == 6)
			mode = 0;
		DC_motor(mode);
		mode++;
	}
}

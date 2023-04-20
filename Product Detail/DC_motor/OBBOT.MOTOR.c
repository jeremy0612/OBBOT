#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>

#define PD_ALL 0xff
#define PATTERN_STOP 0b00000000
#define PATTERN_FORWARD	 0b10100101
#define PATTERN_BACKWARD 0b01011010
#define PATTERN_LEFT 0b01101001
#define PATTERN_RIGHT 0b10010110
#define PATTERN_LEFT_1 0b10101000
// #define PATTERN_RIGHT_1 Ob
void CLK(){
	PORTD |= (1 << PD6);
	PORTD &= ~(1 << PD6);
}
uint8_t STOP()
{
	return PATTERN_STOP;
}

uint8_t FORWARD()
{
	return PATTERN_FORWARD;
}

uint8_t BACKWARD()
{
	return PATTERN_BACKWARD;
}

uint8_t TOLEFT()
{
	return PATTERN_LEFT;
}

uint8_t TORIGHT()
{
	return PATTERN_RIGHT;
}

uint8_t CIRCULAR()
{
	return PATTERN_LEFT_1;
}

void ShiftData(uint8_t data) {  
    uint8_t i;
    for (i = 0; i < 8; i++) {
        PORTD &= ~(1 << PD5);    
        PORTD |= ((data >> i) & 1) << PD5;
        CLK();
    }
}

int main(void)
{
	//DDRB &= ~(1 << PB0);
	//DDRD |= PD_ALL; // Set PD0-PD7 as output
	DDRD |= (1 << PD5)|(1 << PD6) | (1 << PD7);
	//uint8_t mode = 0;
	
	uint8_t mode=0;
	while (1)
	{
		if(mode == 6)
			mode = 1;
		PORTD&= ~(1<<PD7);
		_delay_ms(50);
		uint8_t data=0x00;
		switch (mode)
		{
			case 0:
			data = STOP();
			break;
			case 1:
			data = FORWARD();
			break;
			case 2:
			data = BACKWARD();
			break;
			case 3:
			data = TOLEFT();
			break;
			case 4:
			data = TORIGHT();
			break;
			case 5:
			data = CIRCULAR();
			break;
		}
		ShiftData(data);
		PORTD|=(1<<PD7);
		_delay_ms(1000);
		mode++;
	}
}

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

void dung()
{
	PORTD = PATTERN_STOP;
}

void chaythang()
{
	PORTD = PATTERN_FORWARD;
}

void chaylui()
{
	PORTD = PATTERN_BACKWARD;
}

void chaytrai()
{
	PORTD = PATTERN_LEFT;
}

void chayphai()
{
	PORTD = PATTERN_RIGHT;
}

void cheotrai()
{
	PORTD= PATTERN_LEFT_1;
}
int main(void)
{
	DDRB &= ~(1 << PB0);
	DDRD |= PD_ALL; // Set PD0-PD7 as output

	uint8_t mode = 0;
	while (1)
	{
		if (!(PINB & (1 << PB0)))
		{
			mode = (mode + 1) % 6;

			switch (mode)
			{
				case 0:
				dung();
				break;
				case 1:
				chaythang();
				break;
				case 2:
				chaylui();
				break;
				case 3:
				chaytrai();
				break;
				case 4:
				chayphai();
				break;
				case 5:
				cheotrai();
				break;
			}
			_delay_ms(100);
		}
	}
}

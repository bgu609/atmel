/*
 * stepmotor.c
 *
 * Created: 2020-06-18 오전 9:32:41
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

unsigned char step[8] = {0b10000000, 0b11000000, 0b01000000, 0b01100000, 0b00100000, 0b00110000, 0b00010000, 0b10010000};

int main(void)
{
	unsigned int i = 0;
	
	DDRD = 0xf0;
	
    while (1) 
    {
		PORTD = step[i];
		i++;
		if(i==8) i=0;
		_delay_ms(10);
		
		
		/*PORTD = 0b00110000;
		_delay_ms(10);
		PORTD = 0b10010000;
		_delay_ms(10);
		PORTD = 0b11000000;
		_delay_ms(10);
		PORTD = 0b01100000;
		_delay_ms(10);*/
    }
}


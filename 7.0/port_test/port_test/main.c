/*
 * port_test.c
 *
 * Created: 2020-06-12 오후 2:10:28
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char LED_Data = 0x00;
	DDRA = 0x0f;
	while(1) {
		PORTA = LED_Data;
		LED_Data++;
		
		if(LED_Data>0x0f) LED_Data=0;
		_delay_ms(1000);
	}
	/*
	while(1) {
		DDRA = 0x03;
		PORTA = 0x0f;
		_delay_ms(500);
		PORTA = 0x00;
		_delay_ms(500);
		
		DDRA = 0x0C;
		PORTA = 0x0f;
		_delay_ms(500);
		PORTA = 0x00;
		_delay_ms(500);
		
		DDRA = 0x01;
		PORTA = 0x0f;
		_delay_ms(500);
		PORTA = 0x00;
		
		DDRA = 0x02;
		PORTA = 0x0f;
		_delay_ms(500);
		PORTA = 0x00;
		
		DDRA = 0x04;
		PORTA = 0x0f;
		_delay_ms(500);
		PORTA = 0x00;
		
		DDRA = 0x08;
		PORTA = 0x0f;
		_delay_ms(500);
		PORTA = 0x00;
		
		_delay_ms(500);
	}*/
	return 0;
}
/*
 * sqLED.c
 *
 * Created: 2020-06-12 오후 4:00:09
 * Author : PKNU
 */

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char LED_Data = 0x01;
	//unsigned char LED_RESET = LED_Data;
	//int switching = 0;
	
	DDRA = 0xff;
	
	while(1) {
		for(int i=0; i<14; i++) {
			PORTA = LED_Data;
			
			if(i<7) {
				LED_Data <<= 1;
			}
			else {
				LED_Data >>= 1;
			}
			
			_delay_ms(500);
		}
		
		
		/*
		PORTA = LED_Data;
		_delay_ms(500);
		PORTA = LED_RESET;
		
		if(switching == 0) {
			LED_Data = LED_Data * 2;
			if(LED_Data == 0x80) {
				switching = 1;
			}
		}
		else if(switching == 1) {
			LED_Data = LED_Data / 2;
			if(LED_Data == 0x01) {
				switching = 0;
			}
		}
		else {
			LED_Data = 0x01;
			LED_RESET = LED_Data;
			switching = 0;
		}*/
		
		/*
		//DDRA = 0x01;
		PORTA = 0x01;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x02;
		PORTA = 0x02;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x04;
		PORTA = 0x04;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x08;
		PORTA = 0x08;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x10;
		PORTA = 0x10;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x20;
		PORTA = 0x20;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x40;
		PORTA = 0x40;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x80;
		PORTA = 0x80;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x40;
		PORTA = 0x40;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x20;
		PORTA = 0x20;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x10;
		PORTA = 0x10;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x08;
		PORTA = 0x08;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x04;
		PORTA = 0x04;
		_delay_ms(500);
		PORTA = 0x00;
		
		//DDRA = 0x02;
		PORTA = 0x02;
		_delay_ms(500);
		PORTA = 0x00;*/
	}
	return 0;
}


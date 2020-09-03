/*
 * interrupt.c
 *
 * Created: 2020-06-15 오후 1:52:36
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_STOP = 0;
//volatile unsigned char Shift_flag = 1;
volatile unsigned char cnt = 0;

int main(void)
{
	unsigned char FND_DATA_TBL[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x67,0x77,0x7c,0x39,0x5e,0x79,0x08,0x80};
	
	DDRA = 0xff;
	DDRD = 0x00;
	
	EICRA = 0x82;
	EIMSK = 0x09;
	EIFR = 0x09;
	
	sei();
	
	while(1)
	{
		PORTA = FND_DATA_TBL[cnt];
		if(Time_STOP == 0)
		{
			cnt++;
			if(cnt>17) cnt = 0;
		}
		_delay_ms(200);
	}
	
	/*
	DDRA = 0xff;
	DDRE = 0x00;
	
	EICRB = 0xc0;
	EIMSK = 0x80;
	EIFR = 0x80;
	
	sei();
	
	while(1)
	{
		PORTA = FND_DATA_TBL[cnt];
		if(Time_STOP == 0)
		{
			cnt++;
			if(cnt>17) cnt=0;
		}
		_delay_ms(200);
	}
	*/
	
	/*
    unsigned char LED_Data = 0x01;
	
	DDRA = 0xff;
	DDRE = 0x00;
	DDRD = 0x00;
	
	EICRA = 0x02;
	EICRB = 0x02;
	
	EIMSK = 0x11;
	EIFR = 0x11;
	
	sei();
	
	while(1)
	{
		PORTA = LED_Data;
		if(Shift_flag == 1)
		{
			if(LED_Data == 0x80) LED_Data = 0x01;
			else LED_Data <<= 1;
		}
		else if(Shift_flag == 2)
		{
			if(LED_Data == 0x01) LED_Data = 0x80;
			else LED_Data >>= 1;
		}
		_delay_ms(100);
	}
	*/
	
	/*
	DDRA = 0xff;
	DDRE = 0x00;
	EICRB = 0x03;
	EIMSK = 0x10;
	EIFR = 0x10;
	sei();
	
    while (1) 
    {
		PORTA = LED_Data;
		if(Time_STOP == 0) {
			if(LED_Data == 0x80) LED_Data = 0x01;
			else LED_Data <<= 1;	
		}
		_delay_ms(100);
    }
	*/
}

SIGNAL(INT0_vect)
{
	cli();
	Time_STOP = 1;
	cnt = 0;
	sei();
}

SIGNAL(INT3_vect)
{
	cli();
	Time_STOP = 0;
	sei();
}

/*
SIGNAL(INT7_vect)
{
	cli();
	if(Time_STOP==0)
	{
		Time_STOP = 1;
	}
	else
	{
		Time_STOP = 0;
	}
	sei();
}
*/

/*
SIGNAL(INT0_vect)
{
	cli();
	Shift_flag = 1;
	sei();
}

SIGNAL(INT4_vect)
{
	cli();
	Shift_flag = 2;
	sei();
}
*/

/*
SIGNAL(INT4_vect) {
	cli();
	
	if(Time_STOP == 0) Time_STOP = 1;
	else Time_STOP = 0;
	
	sei();
}
*/
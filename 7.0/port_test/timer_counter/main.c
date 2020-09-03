/*
 * timer_counter.c
 *
 * Created: 2020-06-15 오후 4:34:26
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

//volatile unsigned char LED_Data = 0x00;
//unsigned char timer0Cnt = 0;
//unsigned char timer2Cnt = 0, Shift_flag = 0;
unsigned char FND_DATA__TBL[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x67,0x77,0x7c,0x39,0x5e,0x79,0x71,0x08,0x80};
volatile unsigned char time_s=0;
volatile unsigned char Time_STOP=0;
unsigned char timer0Cnt = 0;

int main(void)
{
	DDRA = 0xff;
	DDRE = 0x00;
	
	TCCR2 = 0b00000101; // |= ( 1 << CS22 ) | ( 1 << CS20);
	//OCR2 = 183;
	TIMSK = 0b10000000; // |= ( 1 << OCIE2 );
	TIFR |= 1 << OCF2;
	
	EICRB = 0b00000011; // |= ( 1 << ISC41 ) | ( 1 << ISC40 );
	EIMSK = 0b00010000; // |= 1 << INT4;
	EIFR = 0b00010000; // |= 1 << INTF4;
	
	sei();
	
	while(1)
	{
		PORTA = FND_DATA__TBL[time_s];
	}
	return 0;
	
	
	/*
	DDRA = 0xff;
	
	TCCR0 = 0x07;
	//OCR0 = 183;
	TIMSK = 0x02;
	TIFR |= 1 << OCF0;
	
	sei();
	
	while(1)
	{
		PORTA = FND_DATA__TBL[time_s];
	}
	return 0;
	*/
	
	/*
	DDRC = 0xff;
	TCCR0 = 0x06;
	
	TCNT0 = 183;
	TIMSK = 0x01;
	TIFR |= 1 << TOV0;
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	return 0;
	*/
	
	
	/*
	DDRC = 0xff;
	TCCR2 = 0x05;
	//TCNT2 = 183;
	TIMSK = 0x40;
	TIFR |= 1 << TOV2;
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	return 0;
	*/
}



SIGNAL(TIMER2_COMP_vect)
{
	cli();
	//OCR2 += 183;
	timer0Cnt++;
	if(timer0Cnt == 36)
	{
		if(Time_STOP == 0)
		{
			if(time_s >= 16) time_s = 0;
			else time_s++;
		}
		timer0Cnt = 0;
	}
	sei();
}

SIGNAL(INT4_vect)
{
	cli();
	if(Time_STOP == 0) Time_STOP = 1;
	else Time_STOP = 0;
	
	sei();
}





/*
SIGNAL(TIMER0_COMP_vect)
{
	cli();
	//OCR0 += 183;
	timer0Cnt++;
	
	if(timer0Cnt == 36)
	{
		if(time_s >= 16) time_s = 0;
		else time_s++;
		
		timer0Cnt = 0;
	}
	sei();
}
*/

/*
SIGNAL(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = 183;
	timer0Cnt++;
	
	if(timer0Cnt == 400)
	{
		LED_Data++;
		if(LED_Data>0xff) LED_Data = 0;
		timer0Cnt = 0;
	}
	sei();
}
*/



/*
SIGNAL(TIMER2_OVF_vect)
{
	cli();
	TCNT2 = 183;
	timer2Cnt++;
	
	if(timer2Cnt == 50)
	{
		if(Shift_flag == 0)
		{
			LED_Data <<= 1;
			if(LED_Data == 0x80) Shift_flag = 1;
		}
		else
		{
			LED_Data >>= 1;
			if(LED_Data == 0x01) Shift_flag = 0;
		}
		timer2Cnt = 0;
	}
	sei();
}
*/


/*
volatile unsigned char LED_Data = 0x00;
unsigned char timer0Cnt=0;
SIGNAL(TIMER0_OVF_vect);

int main(void)
{
	DDRC = 0xff;
	TCCR0 = 0x07;
	TCNT0 = 183;
	TIMSK = 0x01;
	TIFR |= 1 << TOV0;
	sei();
	
    while (1) 
    {
		PORTC = LED_Data;
    }
}

SIGNAL(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = 183;
	timer0Cnt++;
	if(timer0Cnt == 100)
	{
		LED_Data++;
		if(LED_Data > 0xff) LED_Data = 0;
		timer0Cnt = 0;
	}
	sei();
}
*/
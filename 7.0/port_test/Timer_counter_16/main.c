/*
 * Timer_counter_16.c
 *
 * Created: 2020-06-16 오전 11:34:09
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};

volatile unsigned char time_s = 0;
volatile unsigned FND_flag = 0, edge_flag = 0;
//volatile unsigned char LED_Data = 0x00;
//unsigned char timer1Cnt = 0;

int main(void)
{
	DDRA = 0xff;
	DDRB = 0xf0;
	DDRE = 0x00;
	
	//TCCR1A = 0x00;
	//TCCR1B = 0b00000101;
	TCCR3A = 0x00;
	TCCR3B = 0b01000101;
	
	//OCR1A = 7200;
	ETIMSK = 0b00100000;
	ETIFR |= (1 << ICF3);
	
	sei();
	
	PORTA = FND_DATA_TBL[0];
	PORTB = 0b11100000;
	while(1)
	{
		if(FND_flag)
		{
			if(time_s > 15) time_s = 15;
			PORTA = FND_DATA_TBL[time_s];
			FND_flag = 0;
		}
	}
	return 0;
	
	/*while(1)
	{
		PORTA = FND_DATA_TBL[time_s];
		PORTB = 0b11100000;
	}
	return 0;*/
	
	/*DDRC = 0xff;
	
	TCCR3A = 0b00000000;
	TCCR3B = 0b00000101;
	
	TCNT3 = 65536-7200;
	ETIMSK = 0b00000100;
	ETIFR |= (1 << TOV3);
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	return 0;*/
	
	/*DDRC = 0xff;
	
	TCCR1A = 0b00000000;
	TCCR1B = 0b00000001;
	
	TCNT1 = 0;
	TIMSK = 0b00000100;
	TIFR |= (1 << TOV1);
	
	sei();
	
    while (1) 
    {
		PORTC = LED_Data;
    }
	return 0;*/
}

SIGNAL(TIMER3_CAPT_vect)
{
	cli();
	
	unsigned int count_check;
	if(edge_flag == 0)
	{
		TCCR3B = 0b00000101;
		TCNT3 = 0;
		ICR3 = 0;
		edge_flag = 1;
	}
	else
	{
		TCCR3B = 0x01000101;
		count_check = ICR3;
		time_s = count_check / 720;
		
		FND_flag = 1;
		edge_flag = 0;
	}
	
	sei();
}

/*SIGNAL(TIMER1_COMPA_vect)
{
	cli();
	
	OCR1A += 7200;
	if(time_s>=17) time_s = 0;
	else time_s++;
	
	sei();
}*/

/*SIGNAL(TIMER3_OVF_vect)
{
	cli();
	TCNT3 = 65536-7200;
	LED_Data++;
	if(LED_Data > 0xff) LED_Data = 0;
	
	sei();
}*/

/*SIGNAL(TIMER1_OVF_vect)
{
	cli();
	
	timer1Cnt++;
	if(timer1Cnt == 128)
	{
		LED_Data++;
		
		if(LED_Data > 0xff) LED_Data = 0;
		
		timer1Cnt = 0;
	}
	sei();
}*/
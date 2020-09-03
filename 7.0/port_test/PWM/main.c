/*
 * PWM.c
 *
 * Created: 2020-06-17 오전 10:38:31
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//volatile int Light = 0;
//volatile unsigned char Light_flag = 1;
unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
volatile unsigned char sound_flag = 1;

int main(void)
{
	DDRD = 0x00;
	DDRE = 0b00001000;
	
	TCCR3A = 0x00;
	TCCR3B = 0b00011001;
	TCCR3C = 0x00;
	
	TCNT3= 0x00;
	EICRA = 0xff;
	EICRB = 0xff;
	EIMSK = 0xff;
	EIFR = 0xff;
	
	sei();
	
	while(1)
	{
		if(sound_flag)
		{
			_delay_ms(2000);
			TCCR3A = 0x00;
			sound_flag = 0;
		}
	}
	
	/*unsigned char piano = 0;
	
	DDRB = 0b10000000;
	
	TCCR1A |= 0b00001010;
	TCCR1B |= 0b00011001;
	TCCR1C = 0x00;
	TCNT1 = 0x00;
	
	while(1)
	{
		ICR1 = 7372800/DoReMi[piano];
		OCR1C = ICR1 / 8;
		piano++;
		
		if(8 < piano) piano = 0;
		_delay_ms(1000);
	}*/
	
	
	/*DDRB = 0b10000000;
	DDRD = 0x00;
	DDRE = 0x00;
	
	TCCR2 = 0b01100010;
	TCNT2 = 0x00;
	
	EICRA = 0xff;
	EICRB = 0xff;
	EIMSK = 0xff;
	EIFR = 0xff;
	
	sei();
	
    while (1) 
    {
		if(Light_flag)
		{
			OCR2 = Light;
			Light_flag = 0;
		}
    }*/
}

SIGNAL(INT0_vect)
{
	cli();
	
	ICR3 = 7372800/DoReMi[0]/10;
	TCCR3A = 0b01000000;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT1_vect)
{
	cli();
	
	ICR3 = 7372800/DoReMi[1]/10;
	TCCR3A = 0b01000000;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT2_vect)
{
	cli();
	
	ICR3 = 7372800/DoReMi[2]/10;
	TCCR3A = 0b01000000;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT3_vect)
{
	cli();
	
	ICR3 = 7372800/DoReMi[3]/10;
	TCCR3A = 0b01000000;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT4_vect)
{
	cli();
	
	ICR3 = 7372800/DoReMi[4]/10;
	TCCR3A = 0b01000000;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT5_vect)
{
	cli();
	
	ICR3 = 7372800/DoReMi[5]/10;
	TCCR3A = 0b01000000;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT6_vect)
{
	cli();
	
	ICR3 = 7372800/DoReMi[6]/10;
	TCCR3A = 0b01000000;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT7_vect)
{
	cli();
	
	ICR3 = 7372800/DoReMi[7]/10;
	TCCR3A = 0b01000000;
	sound_flag = 1;
	
	sei();
}










/*SIGNAL(INT0_vect)
{
	cli();
	
	Light = 0;
	Light_flag = 1;
	
	sei();
}

SIGNAL(INT1_vect)
{
	cli();
	
	Light -= 26;
	if(Light < 0) Light = 0;
	Light_flag = 1;
	
	sei();
}

SIGNAL(INT2_vect)
{
	cli();
	
	Light += 26;
	if(Light > 255) Light = 255;
	Light_flag = 1;
	
	sei();
}

SIGNAL(INT3_vect)
{
	cli();
	
	Light -= 51;
	if(Light < 0) Light = 0;
	Light_flag = 1;
	
	sei();
}

SIGNAL(INT4_vect)
{
	cli();
	
	Light += 51;
	if(Light > 255) Light = 255;
	Light_flag = 1;
	
	sei();
}

SIGNAL(INT5_vect)
{
	cli();
	
	Light -= 127;
	if(Light < 0) Light = 0;
	Light_flag = 1;
	
	sei();
}

SIGNAL(INT6_vect)
{
	cli();
	
	Light += 127;
	if(Light > 255) Light = 255;
	Light_flag = 1;
	
	sei();
}

SIGNAL(INT7_vect)
{
	cli();
	
	Light = 255;
	Light_flag = 1;
	
	sei();
}*/
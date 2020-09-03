/*
 * ADC_application.c
 *
 * Created: 2020-06-16 오후 4:54:12
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Lcd.h"


int main(void)
{
	DDRA = 0xff;
	DDRF = 0x02;
	PORTF = 0x02;
	EIMSK = 0xff;
	EIFR = 0xff;
	
	unsigned int AdData = 0;
	LcdInit_4bit();
	
	char sen[20];
	
	ADMUX = 0x00;
	ADCSRA = 0b10000110;
	
    while (1) 
    {
		ADCSRA |= 0b01000000;
		
		while((ADCSRA & 0b00010000) == 0x00);
		
		AdData = ADC;
		
		unsigned int AdData4 = (AdData/1000)%10; unsigned char Data4 = 0; sprintf(Data4, "%d", AdData4);
		unsigned int AdData3 = (AdData/100)%10; unsigned char Data3 = 0; sprintf(Data3, "%d", AdData3);
		unsigned int AdData2 = (AdData/10)%10; unsigned char Data2 = 0; sprintf(Data2, "%d", AdData2);
		unsigned int AdData1 = (AdData)%10; unsigned char Data1 = 0; sprintf(Data1, "%d", AdData1);
		
		Lcd_Pos(0,0);
		Lcd_STR(" Cds: ");
		Lcd_CHAR(Data4+'0');
		Lcd_CHAR(Data3+'0');
		Lcd_CHAR(Data2+'0');
		Lcd_CHAR(Data1+'0');
		
		sprintf(sen, "%s%d", " Cds : ", AdData);
		Lcd_STR(sen);
		_delay_ms(500);
    }
}


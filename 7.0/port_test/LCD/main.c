/*
 * LCD.c
 *
 * Created: 2020-06-16 오후 1:51:21
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "Lcd.h"

volatile unsigned char Swap = 0; // 구구단 선택
int i = 0, k = 0;
int temp;

int main(void)
{
	DDRA = 0xff;
	DDRB = 0xff; // 인터럽트 디버깅용 led 연결
	DDRD = 0x00;
	DDRE = 0x00;
	
	EICRA = 0b10101010; // 0~8번 버튼 하강시 인터럽트
	EICRB = 0b10101010;
	EIMSK = 0xff;
	EIFR = 0xff;
	
	sei();
	
	Byte title[] = "2~9 product";
	Byte msg[] = "input button >>";
	Byte num1[8], num2[8], result[8]; // 숫자 >>> 문자열 전환용
	
	LcdInit_4bit();
	
	while (1) 
    {
		if(Swap == 0) {
			PORTB = 0x00; // 대기 화면
			Lcd_Pos(0,0);
			Lcd_STR(title);
			Lcd_Pos(1,0);
			Lcd_STR(msg);
		}
		else {
			LcdInit_4bit(); // 대기화면 지우고 시작
			
			temp = i; // 연산 도중 인터럽트로 인한 i의 변화, 그로인한 연산 오류 방지
			sprintf(num1, "%d", temp);
			
			for(int j=1; j<10; j++)
			{	
				k = temp * j; // 연산 결과값
				sprintf(num2, "%d", j);
				sprintf(result, "%d", k);
				
				Lcd_Pos(0,0); Lcd_STR(num1);
				Lcd_Pos(0,3); Lcd_CHAR('X');
				Lcd_Pos(0,5); Lcd_STR(num2);
				_delay_ms(1000);
				
				Lcd_Pos(1,1); Lcd_CHAR('=');
				Lcd_Pos(1,3); Lcd_STR(result);
				_delay_ms(2000);
				LcdInit_4bit();
			}
			
			Swap = 0; // 연산 후 대기화면으로 초기화
		}
    }
}

SIGNAL(INT0_vect)
{
	cli();
	PORTB = 0x01;
	Swap = 2;
	i = 2; // 문자열을 숫자로 바꾸는 방법 모르겠음
	sei();
}

SIGNAL(INT1_vect)
{
	cli();
	PORTB = 0x02;
	Swap = 3;
	i = 3;
	sei();
}

SIGNAL(INT2_vect)
{
	cli();
	PORTB = 0x04;
	Swap = 4;
	i = 4;
	sei();
}

SIGNAL(INT3_vect)
{
	cli();
	PORTB = 0x08;
	Swap = 5;
	i = 5;
	sei();
}

SIGNAL(INT4_vect)
{
	cli();
	PORTB = 0x10;
	Swap = 6;
	i = 6;
	sei();
}

SIGNAL(INT5_vect)
{
	cli();
	PORTB = 0x20;
	Swap = 7;
	i = 7;
	sei();
}

SIGNAL(INT6_vect)
{
	cli();
	PORTB = 0x40;
	Swap = 8;
	i = 8;
	sei();
}

SIGNAL(INT7_vect)
{
	cli();
	PORTB = 0x80;
	Swap = 9;
	i = 9;
	sei();
}
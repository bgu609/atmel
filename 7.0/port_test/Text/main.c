/*
 * Test.c
 *
 * Created: 2020-06-18 오전 10:19:39
 * Author : BGW
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

volatile unsigned char Func_flag = 0;
volatile unsigned char rotate = 0;
unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
unsigned char step[8] = {0b10000000, 0b11000000, 0b01000000, 0b01100000, 0b00100000, 0b00110000, 0b00010000, 0b10010000};

void (*reset)(void) = 0x0000; // 함수포인터로 리셋벡터
void putch(unsigned char data);
void putch_Str(char *str);
unsigned char getch();

int main(void)
{
	unsigned char text[] = "\r\n++++ Menu ++++\r\nL : LED\r\nC : CDS\r\n0 ~ 7 : PIANO\r\nS : Step Motor\r\npush button : stop\r\n"; // text
	unsigned char i = 0;
	
	DDRA = 0xff; // LED
	unsigned char LED_data = 0x01; // LED
	
	unsigned int AdData = 0; // 10bit ADC value
	ADMUX = 0x00; // ADC0
	ADCSRA = 0b10000111; // ADC 허가
	
	DDRE = 0b00001000; // PE3 출력
	TCCR3A = 0x00; // WGM3(1:0) = "00"
	TCCR3B = 0b00011001; // WGM3(3:2) = "11", CS3(2:0) = "001"
	TCCR3C = 0x00; // WGM3(3:0) = "1110", FastPWM, 모드 14
	TCNT3 = 0x00; // 타이머 3카운터 초기화
	
	DDRD = 0xf0; // step motor 출력, 0~3 스위치 입력
	
	EICRA = 0b00000010; // 0번 스위치 하강시 인터럽트
	EIMSK = 0x01; // 0번 스위치만 허용
	EIFR = 0x01;
	
	sei();
	
	UCSR0A = 0x00;
	UCSR0B = 0b00011000; // Rx Tx enable
	UCSR0C = 0b00000110; // 비동기
	
	UBRR0H = 0x00;
	UBRR0L = 0b00000111; // 115200 bps
	
	putch_Str(text); // text
	
    while (1) 
    {
		if(Func_flag == 'L') // LED 동작
		{
			unsigned int j=0;
			
			while(1) {
				PORTA = LED_data; // LED 시작
				if(j<7) {
					LED_data <<= 1; // 좌로 이동
				}
				else {
					LED_data >>= 1; // 우로 이동
				}
				
				if((UCSR0A & 0x80)) // 전송준비 확인
				{
					Func_flag = UDR0; // 데이터 전송
					UCSR0A |= 0x80;
					
					if(Func_flag != 'L') // 전송된 데이터가 L 모드가 아니면 종료
					{
						break;
					}
				}
				else
				{
					j++;
					if(j==14) j=0;
					_delay_ms(500);
				}
			}
			
			LED_data = 0x01; // LED 초기화
			PORTA = 0x00; // LED 초기화
		}
		else if(Func_flag == 'C')
		{
			ADCSRA |= 0b01000000; // ADSC AD 개시
			while((ADCSRA & 0x10)==0x00); // ADIF AD 기다림
			AdData = ADC; // 전압이 디지털로 변환된 값
			unsigned char chData[32];
			sprintf(chData, "%d", AdData); // int >> str
			putch_Str("\r\nCDS : ");
			putch_Str(chData); // str 출력
			putch_Str("\r\n");
			
			Func_flag = 0; // flag 초기화
		}
		else if(Func_flag == 'S')
		{
			if(rotate==0) // 회전 선택지
			{
				putch_Str("rotate direction select (f/r) : ");
				rotate = getch();
				putch(rotate);
				putch_Str("\r\n");
			}
			else if(rotate == 'f') // 정방향
			{
				while(1)
				{
					PORTD = step[i];
					i++;
					if(i==8) i=0;
					_delay_ms(10);
					
					if((UCSR0A & 0x80)) // 전송준비 확인
					{
						rotate = UDR0; // 데이터 전송
						UCSR0A |= 0x80;
						
						if(rotate != 'f') // 전송된 데이터가 방향과 일치하지 않으면 종료
						{
							putch(rotate);
							putch_Str("\r\n");
							break;
						}
					}
				}
			}
			else if(rotate == 'r') // 역방향
			{
				while(1)
				{
					if(i==0) i=8;
					PORTD = step[i];
					i--;
					_delay_ms(10);
					
					if((UCSR0A & 0x80)) // 전송준비 확인
					{
						rotate = UDR0; // 데이터 전송
						UCSR0A |= 0x80;
						
						if(rotate != 'r') // 전송된 데이터가 방향과 일치하지 않으면 종료
						{
							putch(rotate);
							putch_Str("\r\n");
							break;
						}
					}
				}
			}
			else if(rotate == 'q') // 회전 종료
			{
				putch_Str("select quit\r\n");
				rotate = 0; // flag 초기화
				Func_flag = 0; // flag 초기화
			}
			else // 오류
			{
				putch_Str("undefined rotate\r\n");
				rotate = 0; // flag 초기화
			}
		}
		else
		{
			Func_flag = getch(); // flag 입력
			
			switch(Func_flag) // 음계발생
			{
				case '0':
				ICR3 = 7372800 / DoReMi[0]/10;
				TCCR3A = 0b01000000;
				_delay_ms(500);
				TCCR3A = 0x00;
				break;
				
				case '1':
				ICR3 = 7372800 / DoReMi[1]/10;
				TCCR3A = 0b01000000;
				_delay_ms(500);
				TCCR3A = 0x00;
				break;
				
				case '2':
				ICR3 = 7372800 / DoReMi[2]/10;
				TCCR3A = 0b01000000;
				_delay_ms(500);
				TCCR3A = 0x00;
				break;
				
				case '3':
				ICR3 = 7372800 / DoReMi[3]/10;
				TCCR3A = 0b01000000;
				_delay_ms(500);
				TCCR3A = 0x00;
				break;
				
				case '4':
				ICR3 = 7372800 / DoReMi[4]/10;
				TCCR3A = 0b01000000;
				_delay_ms(500);
				TCCR3A = 0x00;
				break;
				
				case '5':
				ICR3 = 7372800 / DoReMi[5]/10;
				TCCR3A = 0b01000000;
				_delay_ms(500);
				TCCR3A = 0x00;
				break;
				
				case '6':
				ICR3 = 7372800 / DoReMi[6]/10;
				TCCR3A = 0b01000000;
				_delay_ms(500);
				TCCR3A = 0x00;
				break;
				
				case '7':
				ICR3 = 7372800 / DoReMi[7]/10;
				TCCR3A = 0b01000000;
				_delay_ms(500);
				TCCR3A = 0x00;
				break;
			}
		}
    }
}


SIGNAL(INT0_vect) // 0번 스위치 인터럽트
{
	cli();
	
	PORTA = 0x00; // LED 초기화
	reset(); // 프로그램 동작 정지
	
	sei();
}


void putch(unsigned char data) // 문자 출력
{
	while((UCSR0A & 0x20)==0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

void putch_Str(char *str) // 문자열 출력
{
	unsigned char i=0;
	while(str[i]!='\0')
	{
		putch(str[i++]);
	}
}

unsigned char getch() // 데이터 입력
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data=UDR0;
	UCSR0A |= 0x80;
	return data;
}
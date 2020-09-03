/*
 * UART.c
 *
 * Created: 2020-06-17 오후 3:04:36
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char TX_flag = 0;
volatile char TX_data = 0;

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

void putch(unsigned char data)
{
	while((UCSR0A & 0x20)==0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

void putch_Str(char *str)
{
	unsigned char i=0;
	while(str[i]!='\0')
	{
		putch(str[i++]);
	}
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data=UDR0;
	UCSR0A |= 0x80;
	return data;
}

int main(void)
{
	unsigned char text[] = "\r\nWelcome! edgeiLAB\r\n USART 0 Test Program.\r\n";
	unsigned char echo[] = "ECHO >> ";
	//unsigned char next[] = "\r\n";
	//unsigned int input = 9;
	unsigned char chinput;
	unsigned char i = 0;
	
	DDRE = 0b00001000;
	TCCR3A = 0x00;
	TCCR3B = 0b00011001;
	TCCR3C = 0x00;
	TCNT3 = 0x00;
	
	UCSR0A = 0x00;
	UCSR0B = 0b00011000;
	UCSR0C = 0b00000110;
	
	UBRR0H = 0x00;
	UBRR0L = 0b00000111;
	
	while(text[i]!='\0')
	{
		putch(text[i++]);
	}
	i=0;
	while(echo[i]!='\0')
	{
		putch(echo[i++]);
	}
	
	while(1)
	{
		chinput=getch();
		if(chinput!='\0')
		{
			putch(chinput);
			switch(chinput)
			{
				case '0':
				ICR3 = 7372800 / DoReMi[0]/10;
				break;
				
				case '1':
				ICR3 = 7372800 / DoReMi[1]/10;
				break;
				
				case '2':
				ICR3 = 7372800 / DoReMi[2]/10;
				break;
				
				case '3':
				ICR3 = 7372800 / DoReMi[3]/10;
				break;
				
				case '4':
				ICR3 = 7372800 / DoReMi[4]/10;
				break;
				
				case '5':
				ICR3 = 7372800 / DoReMi[5]/10;
				break;
				
				case '6':
				ICR3 = 7372800 / DoReMi[6]/10;
				break;
				
				case '7':
				ICR3 = 7372800 / DoReMi[7]/10;
				break;
			}
			
			TCCR3A = 0b01000000;
			_delay_ms(500);
			TCCR3A = 0x00;
		}
		else
		{
			TCCR3A = 0x00;
		}
		
		/*
		i=0;
		while(next[i]!='\0')
		{
			putch(next[i++]);
		}*/
	}
	
	/*DDRD = 0x00;
	DDRE = 0b00000010;
	UCSR0A = 0x00;
	UCSR0B = 0b00011000;
	UCSR0C = 0b00000110;
	UBRR0H = 0x00;
	UBRR0L = 0b00000111;
	
	EICRA = 0xff;
	EICRB = 0xff;
	EIMSK = 0xff;
	EIFR = 0xff;
	
	sei();
	
	while(1)
	{
		if(TX_flag == 1)
		{
			putch_Str("\n\r Input Switch : ");
			putch(TX_data);
			TX_flag = 0;
		}
	}*/
	
	
	/*unsigned char text[] = "Hello World \r\n";
	unsigned char i=0;
	
	DDRE = 0xfe;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x07;
	
    while (text[i]!='\0') 
    {
		putch(text[i++]);
    }*/
}
/*
SIGNAL(INT0_vect)
{
	cli();
	TX_data = '0';
	TX_flag = 1;
	sei();
}

SIGNAL(INT1_vect)
{
	cli();
	TX_data = '1';
	TX_flag = 1;
	sei();
}

SIGNAL(INT2_vect)
{
	cli();
	TX_data = '2';
	TX_flag = 1;
	sei();
}

SIGNAL(INT3_vect)
{
	cli();
	TX_data = '3';
	TX_flag = 1;
	sei();
}

SIGNAL(INT4_vect)
{
	cli();
	TX_data = '4';
	TX_flag = 1;
	sei();
}

SIGNAL(INT5_vect)
{
	cli();
	TX_data = '5';
	TX_flag = 1;
	sei();
}

SIGNAL(INT6_vect)
{
	cli();
	TX_data = '6';
	TX_flag = 1;
	sei();
}

SIGNAL(INT7_vect)
{
	cli();
	TX_data = '7';
	TX_flag = 1;
	sei();
}*/
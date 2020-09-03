/*
 * FND_LED.c
 *
 * Created: 2020-06-15 오전 10:45:23
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

//int Count_TR(unsigned char flag);

int main(void)
{
	unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
	int cnt = 0;
	int next = 0;
	int nxt_cnt = 0x07;
	//unsigned char Switch_flag = 0;
	
	DDRA = 0xff;
	DDRE = 0x0f;
	
    while (1) 
    {
		PORTA = FND_DATA_TBL[cnt];
		PORTE = nxt_cnt;
		
		cnt++;
		
		if(cnt>15) {
			cnt = 0;
			switch(next) {
				case 0:
				next++;
				nxt_cnt = 0x03;
				break;
				
				case 1:
				next++;
				nxt_cnt = 0x01;
				break;
				
				case 2:
				next=0;
				nxt_cnt = 0x07;
				break;
			}
		}
		_delay_ms(500);
		
		/*
		Switch_flag = PINB;
		while(PINB != 0x00);
		
		if(Switch_flag != 0) cnt += Count_TR(Switch_flag);
		
		if(cnt<0) cnt = 0;
		else if(cnt>15) cnt = 15;
		
		PORTA = FND_DATA_TBL[cnt];
		_delay_ms(100);
		*/
		
		/*
		cnt++;
		if(cnt>17) cnt=0;
		_delay_ms(500);
		*/
		
		/*
		PORTA = 0b00111111; // 0
		_delay_ms(500);
		PORTA = 0b00000110; // 1
		_delay_ms(500);
		PORTA = 0b01011011; // 2
		_delay_ms(500);
		PORTA = 0b01111001; // 3
		_delay_ms(500);
		*/
    }
}

int Count_TR(unsigned char flag) {
	int count = 0;
	switch(flag) {
		case 0x01:
		count = 1;
		break;
		
		case 0x02:
		count = 2;
		break;
		
		case 0x10:
		count = 4;
		break;
		
		case 0x20:
		count = 8;
		break;
		
		case 0x04:
		count = -1;
		break;
		
		case 0x08:
		count = -2;
		break;
		
		case 0x40:
		count = -4;
		break;
		
		case 0x80:
		count = -8;
	}
	
	return count;
}
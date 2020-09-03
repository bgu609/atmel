/*
 * input.c
 *
 * Created: 2020-06-12 오후 5:16:01
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char Switch_flag = 0, Switch_flag_pre = 0x01;
	
	DDRA = 0xff;
	DDRB = 0x00;
	PORTA = 0x00;
    while (1) 
    {
		Switch_flag = PINB >> 4;
		if((Switch_flag == 0x01)||(Switch_flag == 0x02)||(Switch_flag == 0x04)||(Switch_flag == 0x08)) {
			Switch_flag_pre = Switch_flag;
		}
		
		PORTA ^= 0x0f;
		
		if(Switch_flag_pre == 0x01) _delay_ms(250);
		else if(Switch_flag_pre == 0x02) _delay_ms(500);
		else if(Switch_flag_pre == 0x04) _delay_ms(750);
		else if(Switch_flag_pre == 0x08) _delay_ms(1000);
    }
}


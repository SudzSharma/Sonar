/*
 * Servo_Motor.c
 *
 * Created: 12/4/2015 2:51:37 PM
 * Author : Win Pro
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	int i;
    DDRD=(1<<5);/* Replace with your application code */
	TCCR1A=(1<<WGM11)|(0<<WGM10)|(0<<COM1A0)|(1<<COM1A1);//Clear on Comapare Match
	TCCR1B=(1<<WGM12)|(1<<WGM13)|(1<<CS12)|(1<<CS10);
  

	ICR1=312;



    while (1) 
    {
		
		
		for(i=9;i<=38;i++)
		{
			OCR1A=i;
			_delay_ms(10);
		}
		
		for(i=38;i>=9;i--)
		{
			OCR1A=i;
			_delay_ms(10);
		}
		
    }
}


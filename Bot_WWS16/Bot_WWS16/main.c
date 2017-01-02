#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>



volatile unsigned int ovf=0;
volatile float distance=0;
volatile int flag=0;
volatile float temp;
volatile int a=0;
uint16_t ax=0,by=0;

void forward()
{
	DDRC=255;
	PORTC=0b00001111;
}

void backward()
{
	DDRC=255;
	PORTC=0b00110101;
}

void right()
{
	DDRC=255;
	PORTC=0b00011101;
}

void left()
{
	DDRC=255;
	
	PORTC=0b00100111;
}

void brake()
{
	DDRC=225;
	PORTC=225;
}



ISR(TIMER0_OVF_vect)
{
	PORTB|=(1<<3);
	ovf++;
	
}


ISR(INT0_vect)
{

	temp=(ovf*255.0)+TCNT0;
	distance=(float)((temp*16300.0)/16000000.0);//Speed of Sound taken as 323 m/s Approx


	PORTB|=(0<<1);
	_delay_us(2);
	PORTB|=(1<<1);
	_delay_us(10);
	PORTB|=(0<<1);
	
	ovf=0;
	TCNT0=0;
}


void setup() {
	DDRB=255;
	TCCR0=(1<<CS00);//Prescaler=0.
	TIMSK=(1<<TOIE0);//OVF Interrupt Enable.

	//int i=0;

	
	GICR=(1<<INT0);
	MCUCR=(1<<ISC01);//Falling Edge Interrupt Set.
	sei();
	
	PORTB|=(0<<1);
	_delay_us(2);
	PORTB|=(1<<1);
	_delay_us(10);
	PORTB|=(0<<1);
	
	ovf=0;
	TCNT0=0;
}

int main()
{
	setup();

	int i=0;
	while(1)
	{
		if(ovf>735)
		{
			
			PORTB|=(0<<1);
			_delay_us(2);
			PORTB|=(1<<1);
			_delay_us(10);
			PORTB|=(0<<1);
			
			ovf=0;
			TCNT0=0;
		}


		if(distance>20)
		{

			PORTB=(1<<7);

		}
		else
		{

			PORTB=(1<<5);

			
			DDRD|=(1<<5);/* Replace with your application code */
			TCCR1A=(1<<WGM11)|(0<<WGM10)|(0<<COM1A0)|(1<<COM1A1);//Clear on Compare Match FAST PWM.
			TCCR1B=(1<<WGM12)|(1<<WGM13)|(1<<CS12)|(1<<CS10);
			
			ICR1=312;


			for(i=14;i<=34;i++)
			{

				OCR1A=i;
				_delay_ms(25);

			}
			_delay_ms(100);

			for(i=34;i>=14;i--)
			{

				OCR1A=i;
				_delay_ms(25);
			}

			_delay_ms(100);

			DDRD=0;

			_delay_ms(300);
		}



				ADMUX=(1<<REFS0)|(1<<REFS1)|(1<<ADLAR)|(0<<MUX0);
				ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

				ADCSRA|=(1<<ADSC);

				while(ADCSRA&(1<<ADSC))
				{
					
				}

				ax=ADC;

				ADMUX=0;
				ADCSRA=0;

				ADMUX=(1<<REFS0)|(1<<REFS1)|(1<<ADLAR)|(1<<MUX0);
				ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADSC);

				while(ADCSRA&(1<<ADSC))
				{
					
				}

				by=ADC;

				//Serial.print(a);Serial.print("  a and b   ");Serial.println(b);


				if(ax>45500)
				{
					//Serial.println("Back");
					//	DDRB=255;
					//PORTB=0b00000010;
					backward();
				}

				else if(ax<37000)
				{
					//Serial.println("Forward");
					//	DDRB=255;
					//	PORTB=0b00000100;
					forward();
				}


				else if(by>46000)
				{
					//Serial.println("left");
					//DDRB=255;
					//PORTB=0b00001000;
					left();
				}

				else if(by<37000)
				{
					//Serial.println("right");
					//DDRB=255;
					//PORTB=0b00010000;
					right();
				}
				else
				{

					//DDRB=255;
					//PORTB=0;
					brake();
				}


	}


}
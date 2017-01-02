#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>


//#define Trig PB1
//#define Echo INT0 PD3

volatile unsigned int ovf=0;
volatile float distance=0;
volatile int flag=0;
volatile float temp;
volatile int a=0;



ISR(TIMER0_OVF_vect)
{
PORTB|=(1<<3);
	ovf++;
	
}


ISR(INT0_vect)
{

	temp=(ovf*255.0)+TCNT0;
	distance=(float)((temp*16300.0)/16000000.0);//Speed of Sound taken as 323 m/s Approx


	//delay(10);
	/*
	digitalWrite(Trig,LOW);
	delayMicroseconds(2);
	digitalWrite(Trig,HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig,LOW);
	
	*/
	PORTB|=(0<<1);
	_delay_us(2);
	PORTB|=(1<<1);
	_delay_us(10);
	PORTB|=(0<<1);
	
	ovf=0;
	TCNT0=0;
}


void setup() {
	// put your setup code here, to run once:
	//pinMode(Trig,OUTPUT);
	DDRB=255;
	//pinMode(Echo,INPUT);


	//Serial.begin(115200);
	//TCCR1A=0;
	TCCR0=(1<<CS00);//Prescaler=0.
	TIMSK=(1<<TOIE0);//OVF Interrupt Enable.
	
	GICR=(1<<INT0);
	MCUCR=(1<<ISC01);//Falling Edge Interrupt Set.
	sei();
	/*
	digitalWrite(Trig,LOW);
	delayMicroseconds(2);
	digitalWrite(Trig,HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig,LOW);
	*/
	
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
	// put your main code here, to run repeatedly:
	/*
	Serial.print("DISTANCE");
	Serial.print("     ");
	Serial.print(distance);
	Serial.print("     ");Serial.print("OVF");
	Serial.print("     ");
	Serial.print(ovf);
	Serial.print("     ");
	Serial.println(temp);
	*/
	setup();

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
	}

	}


}


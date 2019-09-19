/*
 * LABSI_SM.c
 *
 * Created: 19/09/2019 10:38:03
 * Author : Luis Silva
 * Author : João Loureiro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


void init()
{
	/*PORTS Configurations*/	
	DDRB=(1<<DDB2);		// PB2 > PWM	(OUT)
	DDRC=(1<<DDC0);		// PC0 > ADC0	(IN)
	DDRD=(1<<DDD6);		// PD6 > LED_BLINK	(OUT)
	
	PORTC=0xFF;			//	PULL-UPS ON
	PORTD=0xFF;			//	PULL-UPS ON & LED
	PORTB=~(1<<DDB2);	//	TOGGLE LED
	
	
	/*Timers Configurations*/
	
	/*Timer 0*/
	TCCR0A = (2<<COM0A0)|(3<<WGM00);	//Fast PWM não invertido, modo 3
	TCCR0B |= (5<<CS00);				//PRESCALER=1024 TIMER ligado
	TIMSK0 |= (1<<TOIE0);				//Overflow interrupt ativado
	OCR0A=0;							//aplicar valor inicial (LED Teste)
	
	/*Timer 1*/
	TCCR1A = (2<<COM1A0)|(2<<WGM10);    // non-inverted, Modo PWM=14
	TCCR1B = (3<<WGM12)|(4<<CS10);      // PWM=14, prescaler=256
	ICR1 = 62499;						// periodo = 1s
	OCR1A = 31249;						// 50% duty-cycle
	
	
	/*ADC Configurations*/	
	ADMUX=(1<<REFS0)|(1<<ADLAR);						// AVcc, Align Left (ADCH), MUX CH0
	ADCSRA=(1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(7<<ADPS0);	// ADC enable, Adc Auto trigger, Adc interrupt, prescaler 128
	ADCSRB=(4<<ADTS0);									// Adc auto-trigger source: TC0 Overflow

	
	sei();				// enable interrupts
}


ISR(ADC_vect)
{
	OCR0A=ADCH;			// put ADCH value on OCR0A pin
}


ISR(TIMER0_OVF_vect)
{
}

int main(void)
{
    init();
	
    while (1) 
    {
    }
}

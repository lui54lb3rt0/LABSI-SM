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
	/*PORTS COnfigurations*/	
//	DDRC=(1<<DDC0);		// PC0 > ADC0	(IN)
	DDRD=(1<<DDD6);		// PD6 > OC0A	(OUT)
	
	PORTC=0xFF;			//	PULL-UPS ON
	PORTD=0xFF;			//	PULL-UPS ON e LED

	
	
	
	/*ADC COnfigurations*/	
/*	ADMUX=(1<<REFS0)|(1<<ADLAR);						// AVcc, Align Left (ADCH), MUX CH0
	ADCSRA=(1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(7<<ADPS0);	// ADC enable, Adc Auto trigger, Adc interrupt, prescaler 128
	ADCSRB=(4<<ADTS0);									// Adc auto-trigger source: TC0 Overflow
*/
	
	sei();				// enable interrupts
}

/*
ISR(ADC_vect)
{
	OCR0A=ADCH;			// put ADCH value on OCR0A pin
}
*/

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

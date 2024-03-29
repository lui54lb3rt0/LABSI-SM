/********************************************************
	Language		:	C
	Year			:	2019/2020
	Class			:	LABSI
	Authors			:	Lu�s Silva | Jo�o Loureiro
	E-mail			:	1101420@isep.ipp.pt | 1131109@isep.ipp.pt
*********************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

/* Interrupts */
ISR(TIMER1_COMPA_vect)	
{
}

ISR(TIMER0_OVF_vect)
{
}

ISR(ADC_vect)
{
	OCR0A=ADCH;			// Copy ADCH register to OCR0A to change the duty-cycle of the PWM
}

/* Functions */
void inic()
{
	/* Ports configuration */
	DDRB = 0x02;		// Set PB1 as output OC1A (Pin 15)
	DDRC = 0x00;		// Set PORTC as input (ADC)
	DDRD = (1<<DDD6);	// Set PD6 as output OC0A (Pin 12)
	
	PORTC = 0xFF;		// PULL-UPS ON
	PORTD = 0xFF;		// PULL-UPS ON and LED
	
	/* Timer 0 */
	TCCR0A = (1<<COM0A1) | (1<<WGM01) | (1<<WGM00) ;	// Clear OC0A | Fast PWM 
	TCCR0B = (1<<CS02) | (1<<CS00);						// PRESCALER=1024
	TIMSK0 |= (1<<TOIE0);								// Overflow interrupt enable
	OCR0A=0;											// PWM = 0 
	
	/* Timer 1 toggle LED*/
	TCCR1A = (1 << COM1A0);					// Enable OC1A to toggle led
	TCCR1B = (1 << CS12) | (1 << WGM12);	// CLKIO/256 (From prescaler) | Mode CTC
	TIMSK1 |= (1 << OCIE1A);				// Enable TIMER1
	OCR1A = 31250;							// Total timer ticks to 1Hz

	/* ADC */
	ADMUX = (1<<REFS0)|(1<<ADLAR);							// AVcc | align left | ch0
	ADCSRA = (1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(7<<ADPS0);		// Enable conversion | ADC Auto trigger | ADC interrupt | PS 128
	ADCSRB = (1<<ADTS2);									// TC0 Overflow to start conversion
	
	sei();									// Enable interrupts
}

/* Main code */
int main(void)
{
	inic();									// Execute Inic function to set the parameters of the uC
	while(1){								// while loop
		
	}
}
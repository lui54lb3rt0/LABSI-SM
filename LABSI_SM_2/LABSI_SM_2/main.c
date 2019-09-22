#include <avr/io.h>
#include <avr/interrupt.h>



void ler_ad()
{
	ADCSRA = ADCSRA | 0b01000000;
	while ((ADCSRA & (1<<ADSC)) !=0);
	OCR0A = ADCH;
}

void inic()
{
	DDRB = 0x02;		// Set PB1 as output
	DDRC = 0x00;
	DDRD = (1<<DDD6);
			
	PORTC = 0xFF;		// PULL-UPS

	PORTD = 0xFF;
	
	/* Timer 0 */
	TCCR0A = (2<<COM0A0)|(3<<WGM00);	//Toggle OC0A | Fast PWM non-inverted, modo 3
	TCCR0B |= (2<<CS00);				//PRESCALER=1024 TIMER enable
	TIMSK0 |= (1<<TOIE0);				//Overflow interrupt enable
	OCR0A=0;							//PWM = 0 
	
	
	/* Timer 1 toggle LED*/
	TCCR1A = (1 << COM1A0);					// ativar OC1A to toggle led
	TCCR1B = (1 << CS12) | (1 << WGM12);	// CLKIO/256 (From prescaler) | Mode CTC
	TIMSK1 |= (1 << OCIE1A);				// Enable TIMER1
	OCR1A = 31250;							// Total timer ticks para 1Hz      62500

	/* ADC */
	
	ADMUX = 0b01100000;//(1<<REFS0)|(1<<ADLAR);							// AVcc, align left, ch0
	ADCSRA = 0b10000111;//(1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(7<<ADPS0);		// Enable conversion | Adc Auto trigger, Adc interrupt, prescaler 128
	ADCSRB = (1<<ADTS2);									// TC0 Overflow
	
	sei();
	
}

ISR(TIMER1_COMPA_vect)
{
}

ISR(TIMER0_OVF_vect)
{
	ler_ad();
}

ISR(ADC_vect)
{
	//	OCR0A=ADCH;					// valor duty cycle
}



int main(void)
{
	inic();
	while(1){
		
	}
}
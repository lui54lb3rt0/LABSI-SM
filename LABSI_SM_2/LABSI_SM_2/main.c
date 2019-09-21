#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect)
{
	//	PORTD = PORTD^0b10000000;		//não é necessário uma vez que temos o pino OC1A a fazer o toggle automático com o timer
}

void inic()
{
	DDRB = 0x02;		// Set PB1 as output
	DDRC = 0x00;
		
	PORTC = 0xFF;		// PULL-UPS
	PORTB = 0x00;		// Led off on startup
	
	
	/* Timer 0 */
	TCCR0A = (2<<COM0A0)|(3<<WGM00);	//Fast PWM non-inverted, modo 3
	TCCR0B |= (5<<CS00);				//PRESCALER=1024 TIMER enable
	TIMSK0 |= (1<<TOIE0);				//Overflow interrupt enable
	OCR0A=0;							//PWM = 0
	
	
	/* Timer 1 toggle LED*/
	TCCR1A = (1 << COM1A0);					// ativar OC1A to toggle led
	TCCR1B = (1 << CS12) | (1 << WGM12);	// CLKIO/256 (From prescaler) | Mode CTC
	
	OCR1A = 31250;	// Total timer ticks para 1Hz      62500

	TIMSK1 |= (1 << OCIE1A);		// Enable TIMER1
	
	
}

int main(void)
{
	inic();
	while(1){}
}
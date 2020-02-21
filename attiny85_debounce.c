/* Simple button debounce code on ATTiny85. */
/* stoverbabcock@gmail.com					*/

#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DEBOUNCE_DELAY	400
#define BLINK_TIMES		6
#define BLINK_DELAY		75

static inline void irqsetup(void)
{
	GIMSK |= (1<<PCIE);		// pin change interrupt enable.
	PCMSK |= (1<< PCINT0);	// pin change interrupt enable for PCINT0.
	sei();					// enable interrupts	
}

ISR(PCINT0_vect)
{
	cli(); // disable all interrupts.
	
	volatile unsigned char i = 0;
	
	if(~PINB & (1<<PB1))
	{
		_delay_ms(DEBOUNCE_DELAY);
		if(~PINB & (1<<PB0))
		{
			for(i=0;i<BLINK_TIMES;i++)
			{
				PORTB ^= (1<<PB1);		
				_delay_ms(BLINK_DELAY);
			}	
		
		}
	}
					
	sei(); // re-enable all interrupts.
}

int main (void) 
{
	DDRB |= (1<<PB1);	// PB1 is output (LED)
	PORTB |= (1<<PB0);	// enable pullup on PB0. and PCINT0 irq.
	
	irqsetup();	
	
	while(1)
	{		
	}
	
	return 0;
}

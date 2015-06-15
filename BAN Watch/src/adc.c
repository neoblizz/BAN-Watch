#ifndef sbi(var, mask)
#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))
#endif

#ifndef _AVR_IOMXX0_1_H_
#include <iomxx0_1.h>
#endif

#include <avr/wdt.h>

int ADC_INIT(void);

int T_flag = 0;

int ADC_INIT(void)
{
	//Config for AVCC Ref, Left-Aligned Data, Mux to ADC4
	ADMUX = ( (1 << REFS0) | (1 << ADLAR) | (1 << MUX2) );
	cbi(ADMUX, REFS1);
	cbi(ADMUX, MUX4);
	cbi(ADMUX, MUX3);
	cbi(ADMUX, MUX1);
	cbi(ADMUX, MUX0);
	cbi(ADCSRB, MUX5);
	
	//Enable the ADC and ADC interrupt.  Start the ADC.
	//Prescaler at /128.  I have no idea if that's what we want.  But seems like slower=safer atm
	ADCSRA = ( (1 << ADEN) | (1 << ADSC) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
	
	//Free-running mode.  **Guitar Solo**
	//Bit 7 is set to zero b/c the data sheet says it has to be. I'm not kidding.
	cbi(ADCSRB, 7);
	cbi(ADCSRB, ADTS2);
	cbi(ADCSRB, ADTS1);
	cbi(ADCSRB, ADTS0);
	
	//Turn off everything but ADC4
	DIDR0 |= 1;
	DIDR2 |= 1;
	cbi(DIDR0, ADC4D);
	
	return 0;
}

ISR(ADC_vect)
{
	//Turns on the light if a accell of greater than 50% the max is detected. (1.5 / 8 g)
	//if ( (ADCH >= 0x80) & !( LED&(1 << LED0) & !T_flag ) )
	if (ADCH >= 0x80)
	{
		
		if (!T_flag)
		{
		LED_ON();
		cli();
		
		// wdt_reset();
		WDTCSR = (1<<WDCE);
		cbi(MCUSR, WDRF);
		cbi(WDTCSR, WDE);
		cbi(WDTCSR, WDIF);
		
		WDTCSR |= ( (1 << WDIE) | (1 << WDCE) | (1 << WDP3) | (1 << WDP0) );
		cbi(WDTCSR, WDP2);
		cbi(WDTCSR, WDP1);
		
		sei();
		
		T_flag = 1;	
		}
		
		
	}
	/*
	if (T_flag && (ADCH <= 0x05))
	{
		s2_flag = 1;
	}
	*/
}

ISR(WDT_vect)
{
	LED_TOGGLE();
	_delay_ms(10);
	//T_flag = 0;
}

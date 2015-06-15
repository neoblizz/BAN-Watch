/*
 * \file -> axl.c
 * \associated header -> axl.h
 * \conf -> N/A
 *
 * \brief -> This file takes care of initialization and interrupt functions
 * of the accelerometer on the board; w/ 3 axis acceleration detection.
 *
 * \description begin ->
 *
 * ADC_INIT(); initializes the ADCs to be used for the accelerometer.
 * ISR(ADC); creates an interrupt handler for the adc, and samples it accordingly.
 * The ISR also trigers the timer to detect a specific type of motion from the 
 * accelerometer, that being the handshake motion. An upward acceleration, which is
 * how a handshake first begins starts the timer when it crosses the +ve threshold,
 * when few seconds expire, the adc reads the downward acceleration value and compares
 * it with -ve threshold. If both the thresholds are crossed, the handshake is complete
 * and data is ready to send.
 *
 * \description end <-
 *
 * \revision history begin ->
 *
 * Tim Pollard		[06/03/2015]: SPI accelerometer initialized.
 * Tim Pollard		[06/04/2015]: Problem detected in hardware; SPI is removed.
 * Tim Pollard		[06/04/2015]: ADC init and delta functions created, flags added.
 * Tim Pollard		[06/05/2015]: Timers incorporated.
 *
 * \revision history end <-
 *
 * \known bugs begin ->
 *
 * \known bugs end <-
 *
 * \license -> license.h
 *
 */

/* INCLUDES */
#include "axl.h"

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

void ADC_PULSE (void) {
	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect)
{
	
	
	/*ADC_VAL = (int) ADCH;
	if (FIRST_ADC == 1)
	{
		FIRST_ADC = 0;
		ADC_LAST = ADC_VAL;
	}
	ADC_D = ADC_VAL - ADC_LAST;
	
	if ((ADC_D > 1) & (T_flag == 0))
	{
		LED_ON();
		
		T_flag = 1;
		TIMER_INIT();
	}
	if ((ADC_D < -1 ) & (T_flag == 1))
	{
		
		TIMSK5 &= ~(1 << TOIE0);
		T_flag = 2;
	}
	
	ADC_LAST = ADC_VAL;*/
	
	//Turns on the light if a accell of greater than 50% the max is detected. (1.5 / 8 g)
	
	if ((ADCH >= 0xAA) & (T_flag == 0))
	{
		LED_ON();
		
		T_flag = 1;
		TIMER_INIT();
	}
	if ((ADCH <= 0x96) & (T_flag == 1))
	{
		
		TIMSK5 &= ~(1 << TOIE0);
		T_flag = 2;
	}
	
}
/*
 *	\see -> axl.c
 */

/* INCLUDES */
#include "timer.h"

int TIMER_INIT(void)
{
	TCCR5A &= 0;
	TCCR5B &= 0;
	TCCR5B |= ( (1 << CS51) | (1 << CS50));  // clk/64
	TCCR5C &= 0;
	TIMSK5 |= (1 << TOIE0);
	//sbi(TIMSK5, TOIE0);
	return 0;
}

ISR(TIMER5_OVF_vect)
{
	LED_OFF();
	T_flag = 0;
	TIMSK5 &= ~(1 << TOIE0);
}

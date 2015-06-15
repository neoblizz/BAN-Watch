/*
 * \file -> led.c
 * \associated header -> led.h
 * \conf -> N/A
 *
 * \brief -> 
 *
 * \description begin ->
 *
 *
 * \description end <-
 *
 * \usage start ->
 *			
 *
 * \usage end <-
 *
 * \revision history begin ->
 *
 * Muhammad Osama	[06/07/2015]: File created and associated header definitions
 *								  initialized.
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
#include "led.h"

void LED_INIT (void) {
	// LED (PORTA3) AS OUTPUT = 1
	DDRLED |= (1 << LED0);
	LED = 0xFF;
	LED = 0;
}

void LED_ON (void) {
	LED |= (1 << LED0);
}

void LED_OFF (void) {
	LED &= ~(1 << LED0);
}

void LED_TOGGLE (void) {
	LED ^= (1 << LED0);
}
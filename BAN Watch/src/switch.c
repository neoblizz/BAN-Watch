/*
 * \file -> switch.c
 * \associated header -> switch.h
 * \conf -> N/a
 *
 * \brief -> Switch control file used to dedicate the appropriate ports and pins
 * 	to the quick use defined statements. Acts as a driver for the switches.
 *
 * \description begin ->
 *
 *	This file uses three baremetal functions to address the input of all the 
 *  switches. SW_INIT() to initialize the direction registers as inputs for switch
 *  control, switch auto mode, and switch power. iskey() function dedicated to determine
 *  if any key was pressed or not, and finally getkey() function determines which
 *  key was pressed among the three.
 *
 * \description end <-
 *
 * \usage start ->
 *
 *	SWCTL: Switch dedicated for control features, it mainly determines which watch is
 * 		   sending the data, and which watch is receiving the incoming data. An alternate
 *		   function for SWCTL (Switch Control) is also an UP arrow (↑) used to manipulate
 *		   the up direction on the display's menu.
 *
 *	SWAUTO: Switch dedicated to turn on/off the automatic transfer feature (communication 
 *		    protocol), watch opperating in this mode does not require any initial input as
 *			to how the data will flow from one hand to another. An alternate function for 
 *			SWAUTO (Switch Auto) is also DOWN arrow (↓) used to manipulate down direction
 *			on the display's menu.
 *
 *	SWPWR: Switch dedicated for power modes of the processor, it is responsible to make the
 *		   watch enter sleep mode, which allows the user to save power and only activate when
 *		   an external interrupt occurs by the accelerometer. An alternate function for this 
 *		   switch is also a Select Key (S) for the display's menu.
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
 *	1. Intrrupt control is limited due to incorrect port choice on the processor.
 *
 * \known bugs end <-
 *
 * \license -> license.h
 *
 */

/* INCLUDES */
#include "switch.h"

void SW_INIT (void) {
	
	// SWITCHES AS INPUTS
	DDRSW &= ~(1 << SWCTL);		// CTL
	DDRSW &= ~(1 << SWAUTO);	// AUTO
	DDRSW &= ~(1 << SWPWR);		// PWR

}

int iskey (void) {
	return (PINA & ((1 << SWCTL) | (1 << SWAUTO) | (1 << SWPWR)));
}

int getkey (void) {
	int swctl = PINA & (1 << SWCTL);
	int swauto = PINA & (1 << SWAUTO);
	int swpwr = PINA & (1 << SWPWR);
	
	if (swctl) {
		return 1;				// CTL is pressed
	} else if (swauto) {
		return 2;				// AUTO is pressed
	} else if (swpwr) {
		return 3;				// PWR is pressed
	} else {
		return 0;				// Undefined
	}
	
}
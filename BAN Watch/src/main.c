/*
 * \file -> main.c
 * \associated header -> main.h
 * \conf -> conf_board.h
 *
 * \brief -> main of the product Body Area Networking (BAN) Watch,
 * calls all the initialization and begins the start sequence of
 * the software. The operating system, when initialized is a stand
 * alone program.
 *
 * \description begin ->
 *
 * BAN operating system holds variety of features that communicate
 * with each other and attempt to create a smooth experience for the users.
 * main.c is a file dedicated to the major includes and initialization of
 * the hardware associated with the product. The initializations consist
 * of the following peripherals:
 * 
 *		1. Power Management
 *		2. UART Communication Protocol: Bluetooth
 *		3. SPI Communication Protocol:
 *			(a) Accelerometer
 *			(b) JTAG Debugger
 *		4. Switches and LEDs
 *		5. Analog To Digital Samplers
 *		6. Frequency Filtering BAN (FFBAN) Communication Protocol
 *			(a) BAN Receiver
 *				(ii) Fast Fourier Transformation (FFT)
 *			(b) BAN Transceiver
 *				(i) Pulse Width Modulator
 *		7. Timer Delays
 *			(a) _delay_ms();
 *			(b) _delay_us();
 * 
 * A handshake motion of +-4G is detected by the accelerometer and is
 * transfered to the processor, which escapes the sleep mode and begins
 * the data transfer. Bluetooth can be used to program user's contact info-
 * rmation into the watch.
 *
 * \description end <-
 *
 * \revision history begin ->
 *
 * Muhammad Osama	[05/27/2015]: Creation of the file; while(1) loop and basics.
 * Muhammad Osama	[05/29/2015]: UART initializations added to the file.
 * Muhammad Osama	[05/30/2015]: Successful UART transfer protocol.
 * Muhammad Osama	[05/30/2015]: UART protocol moved -> uart.c.
 * Tim Pollard		[06/04/2015]: Accelerometer initialized and moved -> Accelerometer.c.
 * Tim Pollard		[06/04/2015]: Clock speed changed from 1MHz to 8MHz.
 * Muhammad Osama	[06/05/2015]: ASERT enabled for debugging.
 * Tim Pollard		[06/06/2015]: BAN protocol moved -> ban.c.
 * Bruce Yan		[06/06/2015]: GOLDELOX Serial Comm for display -> display.c.
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
#include "main.h"


/*
 * \function -> int main(void);
 *
 * \brief -> main function of the firmware, used to initialize the hardware and
 * start the while(1) loop.
 *
 * \args -> void
 *
 * \return -> int
 *
 */
int main(void)
{
	HardwareSetup();
	
	while (1) {
		
		// Wait for next character
		/*while (!BAN_char_waiting());
		BAN_Received = (char) BAN_getchar();
		BAN_putchar(BAN_Received);*/
		_delay_ms(100);
		
		ADC_PULSE();
		
		_delay_ms(10);
		if (T_flag == 1) {
			
			for (cnt = 0; cnt < strlen(tim); cnt++) {
				BAN_putchar(tim[cnt]);
			}
			LED_ON();
			
			_delay_ms(100);
			
		} else if (T_flag == 2) {
			for (cnt = 0; cnt < strlen(bruce); cnt++) {
				BAN_putchar(bruce[cnt]);
			}
			LED_TOGGLE();
			
			_delay_ms(100);
		} else if (T_flag == 0) {
			for (cnt = 0; cnt < strlen(muhammad); cnt++) {
				BAN_putchar(muhammad[cnt]);
			}
			LED_OFF();
			_delay_ms(100);
		}
	}
	
	// while (true);
	
}


/*
 * \function -> void HardwareSetup(void);
 *
 * \brief -> Hardware setup, called in main and it then calls all the init statements
 * including turning on the global interrupts. The initilizations include;
 *		LED_INIT();
 *		SW_INIT();
 *		BAN_init();
 *		uart_init();
 *		display_init();
 *		accl();
 *
 * \args -> void
 *
 * \return -> void
 *
 */
void HardwareSetup(void)
{
	/* INITIALIZATIONS */
	
	LED_INIT();			// Initialize LED
	
	// SW_INIT();			// Initialize SW
	ADC_INIT();
	
	// cli();				// Disable interrupts
	// uart_init();
	// sei();
	
	cli();
	// display_init();
	BAN_init();
	sei();				// Enable interrupts
	
}

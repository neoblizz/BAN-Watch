/*
 * \file -> uart.c
 * \associated header -> uart.h
 * \conf -> ringbuffer.h
 *
 * \brief -> This file, and ban.c, display.c all uses the UART transfer protocol.
 * This file specifically deals with the bluetooth transfer from a mobile phone,
 * and also a way to debug the entire PCB system to echo the results out.
 *
 * \description begin ->
 *
 * uart_init(); Initializations.
 * uart_putchar(); Puts the character in output ringbuffer.
 * uart_getchar(); Gets the character from input ringbuffer.
 * uart_char_waiting(); Waits for a character.
 * ISR(Rx, Empty); Initializes the vector table for the UART interrupt handlers.
 * 
 *
 * \description end <-
 *
 * \revision history begin ->
 *
 * Muhammad Osama	[06/01/2015]: Created the file and initializations.
 * Muhammad Osama	[06/02/2015]: Port changes from UBRR1H to UBRR0H.
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
#include "uart.h"

/**
 * Initialize the UART with correct baud rate settings
 *
 * This function will initialize the UART baud rate registers with the correct
 * values using the AVR libc setbaud utility. In addition set the UART to
 * 8-bit, 1 stop and no parity.
 */
static void uart_init(void)
{
#if defined UBRR0H
	// get the values from the setbaud tool
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
#else
#error "Device is not supported by the driver"
#endif

#if USE_2X
	UCSR0A |= (1 << U2X0);
#endif

	// enable RX and TX and set interrupts on rx complete
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

	// 8-bit, 1 stop bit, no parity, asynchronous UART
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (0 << USBS0) |
			(0 << UPM01) | (0 << UPM00) | (0 << UMSEL01) |
			(0 << UMSEL00);

	// initialize the in and out buffer for the UART
	ring_BTbuffer_out = ring_buffer_init(out_BTbuffer, BUFFER_SIZE);
	ring_BTbuffer_in = ring_buffer_init(in_BTbuffer, BUFFER_SIZE);
}

/**
 * Function for putting a char in the UART buffer
 */
static inline void uart_putchar(uint8_t data)
{
	// Disable interrupts to get exclusive access to ring_buffer_out.
	cli();
	if (ring_buffer_is_empty(&ring_BTbuffer_out)) {
		// First data in buffer, enable data ready interrupt
		UCSR0B |=  (1 << UDRIE0);
	}
	// Put data in buffer
	ring_buffer_put(&ring_BTbuffer_out, data);

	// Re-enable interrupts
	sei();
}

/**
 * Function for getting a char from the UART receive buffer
 */
static inline uint8_t uart_getchar(void)
{
	return ring_buffer_get(&ring_BTbuffer_in);
}


/**
 *	Function to check if we have a char waiting in the UART receive buffer
 */
static inline bool uart_char_waiting(void)
{
	return !ring_buffer_is_empty(&ring_BTbuffer_in);
}


/* UART0 Send */
ISR(UART0_DATA_EMPTY_IRQ)
{
	// If there is data in the ring buffer, fetch it and send it
	if (!ring_buffer_is_empty(&ring_BTbuffer_out)) {
		UDR0 = ring_buffer_get(&ring_BTbuffer_out);
	}
	else {
		// No more data to send, turn off data ready interrupt
		UCSR0B &= ~(1 << UDRIE0);
	}
}

/* UART0 Receive */
ISR(UART0_RX_IRQ)
{
	ring_buffer_put(&ring_BTbuffer_in, UDR0);
}
/*
 *	\see -> uart.c
 */

/* INCLUDES */
#include "display.h"

/**
 * Initialize the UART with correct baud rate settings
 *
 * This function will initialize the UART baud rate registers with the correct
 * values using the AVR libc setbaud utility. In addition set the UART to
 * 8-bit, 1 stop and no parity.
 */
static void display_init(void)
{
#if defined UBRR2H
	// get the values from the setbaud tool
	UBRR2H = UBRRH_VALUE;
	UBRR2L = UBRRL_VALUE;
#else
#error "Device is not supported by the driver"
#endif

#if USE_2X
	UCSR2A |= (1 << U2X2);
#endif

	// enable RX and TX and set interrupts on rx complete
	UCSR2B = (1 << RXEN2) | (1 << TXEN2) | (1 << RXCIE2);

	// 8-bit, 1 stop bit, no parity, asynchronous UART
	UCSR2C = (1 << UCSZ21) | (1 << UCSZ20) | (0 << USBS2) |
			(0 << UPM21) | (0 << UPM20) | (0 << UMSEL21) |
			(0 << UMSEL20);

	// initialize the in and out buffer for the UART
	ring_Displaybuffer_out = ring_buffer_init(out_Displaybuffer, DISPLAY_BUFFER_SIZE);
	ring_Displaybuffer_in = ring_buffer_init(in_Displaybuffer, DISPLAY_BUFFER_SIZE);
}

/**
 * Function for putting a char in the UART buffer
 */
static inline void display_putchar(uint8_t data)
{
	// Disable interrupts to get exclusive access to ring_buffer_out.
	cli();
	if (ring_buffer_is_empty(&ring_Displaybuffer_out)) {
		// First data in buffer, enable data ready interrupt
		UCSR2B |=  (1 << UDRIE2);
	}
	// Put data in buffer
	ring_buffer_put(&ring_Displaybuffer_out, data);

	// Re-enable interrupts
	sei();
}

/**
 * Function for getting a char from the UART receive buffer
 */
static inline uint8_t display_getchar(void)
{
	return ring_buffer_get(&ring_Displaybuffer_in);
}


/**
 *	Function to check if we have a char waiting in the UART receive buffer
 */
static inline bool display_char_waiting(void)
{
	return !ring_buffer_is_empty(&ring_Displaybuffer_in);
}


/* UART0 Send */
ISR(UART2_DATA_EMPTY_IRQ)
{
	// If there is data in the ring buffer, fetch it and send it
	if (!ring_buffer_is_empty(&ring_Displaybuffer_out)) {
		UDR2 = ring_buffer_get(&ring_Displaybuffer_out);
	}
	else {
		// No more data to send, turn off data ready interrupt
		UCSR2B &= ~(1 << UDRIE2);
	}
}

/* UART0 Receive */
ISR(UART2_RX_IRQ)
{
	ring_buffer_put(&ring_Displaybuffer_in, UDR2);
}
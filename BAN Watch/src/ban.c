/*
 *	\see -> uart.c
 */

/* INCLUDES */
#include "ban.h"

/**
 * Initialize the UART with correct baud rate settings
 *
 * This function will initialize the UART baud rate registers with the correct
 * values using the AVR libc setbaud utility. In addition set the UART to
 * 8-bit, 1 stop and no parity.
 */

static void BAN_init(void)
{
#if defined UBRR1H
	// get the values from the setbaud tool
	UBRR1H = UBRRH_VALUE;
	UBRR1L = UBRRL_VALUE;
#else
#error "Device is not supported by the driver"
#endif

#if USE_2X
	UCSR1A |= (1 << U2X1);
#endif

	// enable RX and TX and set interrupts on rx complete
	UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);

	// 8-bit, 1 stop bit, no parity, asynchronous UART
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10) | (0 << USBS1) |
			(0 << UPM11) | (0 << UPM10) | (0 << UMSEL11) |
			(0 << UMSEL10);

	// initialize the in and out buffer for the UART
	ring_BANbuffer_out = ring_buffer_init(out_BANbuffer, BAN_BUFFER_SIZE);
	ring_BANbuffer_in = ring_buffer_init(in_BANbuffer, BAN_BUFFER_SIZE);
}

/**
 * Function for putting a char in the UART buffer
 */
static inline void BAN_putchar(uint8_t data)
{
	// Disable interrupts to get exclusive access to ring_buffer_out.
	cli();
	if (ring_buffer_is_empty(&ring_BANbuffer_out)) {
		// First data in buffer, enable data ready interrupt
		UCSR1B |=  (1 << UDRIE1);
	}
	// Put data in buffer
	ring_buffer_put(&ring_BANbuffer_out, data);

	// Re-enable interrupts
	sei();
}

/**
 * Function for getting a char from the UART receive buffer
 */
static inline uint8_t BAN_getchar(void)
{
	return ring_buffer_get(&ring_BANbuffer_in);
}


/**
 *	Function to check if we have a char waiting in the UART receive buffer
 */
static inline bool BAN_char_waiting(void)
{
	return !ring_buffer_is_empty(&ring_BANbuffer_in);
}


/* UART1 Send */
ISR(UART1_DATA_EMPTY_IRQ)
{
	// If there is data in the ring buffer, fetch it and send it
	if (!ring_buffer_is_empty(&ring_BANbuffer_out)) {
		UDR1 = ring_buffer_get(&ring_BANbuffer_out);
	}
	else {
		// No more data to send, turn off data ready interrupt
		UCSR1B &= ~(1 << UDRIE1);
	}
}

/* UART0 Receive */
ISR(UART1_RX_IRQ)
{
	ring_buffer_put(&ring_BANbuffer_in, UDR1);
}
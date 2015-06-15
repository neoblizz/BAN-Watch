/* DEFINES */
#define UART0_DATA_EMPTY_IRQ USART0_UDRE_vect		/* Define the UART data buffer ready interrupt vector */
#define UART0_RX_IRQ USART0_RX_vect					/* Define the UART data */

#define BUFFER_SIZE 20								/* Buffer Size for UART */

/* DECLERATIONS */
uint8_t out_BTbuffer[BUFFER_SIZE];					/* Output Buffer for Bluetooth UART */
uint8_t in_BTbuffer[BUFFER_SIZE];					/* Input Buffer for Bluetooth UART */

/* Ring buffers to use for the UART */
struct ring_buffer ring_BTbuffer_out;
struct ring_buffer ring_BTbuffer_in;

/* How to send a character array to BT? */
/*	
	for (cnt = 0; cnt < strlen(bruce); cnt++) {
		uart_putchar(bruce[cnt]);
	} 
*/

/* How to receive a character array to BT? */
/*	
	cnt = 0;
	do {
	// Wait for next character
	while (!uart_char_waiting());
	// data = BAN_getchar();
	BAN_Received[cnt] = (char) uart_getchar();

	// Compare to what we sent
	// Assert (data == bruce[cnt++]);

	cnt++;
	} while (cnt < strlen(bruce));
*/
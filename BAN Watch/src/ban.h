/* DEFINES */
#define UART1_DATA_EMPTY_IRQ USART1_UDRE_vect			/* Define the UART data buffer ready interrupt vector */
#define UART1_RX_IRQ USART1_RX_vect						/* Define the UART data */

#define BAN_BUFFER_SIZE 20								/* Buffer Size for UART */

/* DECLERATIONS */
uint8_t out_BANbuffer[BAN_BUFFER_SIZE];					/* Output Buffer for UART */
uint8_t in_BANbuffer[BAN_BUFFER_SIZE];					/* Input Buffer for UART */

/* Ring buffers to use for the BAN */
struct ring_buffer ring_BANbuffer_out;
struct ring_buffer ring_BANbuffer_in;
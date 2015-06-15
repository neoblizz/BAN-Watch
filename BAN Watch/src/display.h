/* TYPEDEF */
typedef unsigned int WORD;
typedef unsigned long long DWORD; 
typedef unsigned int HANDLE;

/* DEFINES */
#define UART2_DATA_EMPTY_IRQ USART2_UDRE_vect					/* Define the UART data buffer ready interrupt vector */
#define UART2_RX_IRQ USART2_RX_vect								/* Define the UART data */
#define DISPLAY_BUFFER_SIZE 20									/* Buffer Size for UART */

/* DECLERATIONS */
uint8_t out_Displaybuffer[DISPLAY_BUFFER_SIZE];					/* Output Buffer for Display UART */
uint8_t in_Displaybuffer[DISPLAY_BUFFER_SIZE];					/* Input Buffer for Display UART */

/* Ring buffers to use for the UART */
struct ring_buffer ring_Displaybuffer_out;
struct ring_buffer ring_Displaybuffer_in;

/* FUNCTION DECLERATIONS */
// int OLED_display(void);
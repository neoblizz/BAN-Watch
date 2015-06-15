/* INCLUDES */
#include "clock.h"

#include <avr/io.h>
#include <util/delay.h>

#include <string.h>
#include <stdbool.h>

#include <util/setbaud.h>
#include <avr/interrupt.h>

/* GLOBAL DECLERATIONS */
uint8_t cnt;										

/* TEST DECLERATIONS */
char BAN_Received;
int T_flag = 0;

const char bruce[] = "Bruce Yan\r\n";
const char muhammad[] = "Muhammad Osama\r\n";
const char tim[] = "Tim Pollard\r\n";
const char josh[] = "Josh Fromm\r\n";
const char james[]= "James Goin\r\n";



#include "ring_buffer.h"
// #include "uart.c"
#include "led.c"
#include "timer.c"
#include "axl.c"
#include "ban.c"
// #include "switch.c"
// #include "display.c"

/* FUNCTION DECLERATIONS */
void HardwareSetup(void);
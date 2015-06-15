/* DEFINES */
#ifndef BIT_SET_MACROS
#define BIT_SET_MACROS 1
#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))
#endif

/* INCLUDES */
#ifndef _AVR_IOMXX0_1_H_
#include <iomxx0_1.h>
#endif

/* FUNCTION DECLERATIONS */
int TIMER_INIT(void);
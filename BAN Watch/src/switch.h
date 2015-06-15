/* DEFINES */
#define SW PINA
#define DDRSW DDRA

#define SWCTL	PA0
#define SWAUTO	PA1
#define SWPWR	PA2

/* FUNCTION DECLERATIONS */
void SW_INIT (void);
int iskey (void);
int getkey (void);
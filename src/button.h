// button.h

#ifndef BUTTON_H
#define BUTTON_H

#include "sys_type.h"
// Define button 
typedef enum button {
	PB_1 = 0,
	PB_2,
	PB_INVALID
}buttons_t;


#define DEBOUNCE_START 			0x01u
#define DEBOUNCE_END			0x02u

#define BUTTON_PRESSED 			0x00u
#define BUTTON_RELEASED 		0x01u

static void button1_debounce(void);
static void button2_debounce(void);

extern ui8_t button1_get_state(void);
extern ui8_t button2_get_state(void);

#endif // BUTTON_H

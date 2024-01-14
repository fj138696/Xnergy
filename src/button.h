// button.h

#ifndef BUTTON_H
#define BUTTON_H

#include "sys_type.h"

// Define button 

typedef struct {
    ui8_t state;
    ui8_t read;
    ui8_t logic_level; //setting of ACTIVE HIGH or ACTIVE LOW
    ui8_t edge_type;
} button_sts_t;


#define DETECTED_RISING_EDGE 			0x00u
#define DETECTED_FALLING_EDGE			0x01u

#define BUTTON_PRESSED 			0x00u
#define BUTTON_RELEASED 		0x01u

static void button1_debounce(void);
static void button2_debounce(void);

extern ui8_t button1_get_state(void);
extern ui8_t button2_get_state(void);

#endif // BUTTON_H

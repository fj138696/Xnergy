// led.h

#ifndef LED_H
#define LED_H

#include "sys_type.h"

// Define LED states
typedef enum {
    LED_OFF =0,
    LED_ON,
    LED_BLINK_ON,
    LED_BLINK_OFF
} led_state_t;


typedef enum {
	GREEN =0,
	RED,
}led_number_t;
// Initialize the LED module
void led_init(void);

// Set the LED state
extern void set_led(led_number_t led_number, led_state_t onoff_state, ui8_t interval);

#endif // LED_H

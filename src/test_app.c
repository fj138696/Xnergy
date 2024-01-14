/* test_app.c */
/** Assumptions: 
* Button 1 pressed for 1sec - GREEN LED is ON and Blinking for 1sec 
* Button 2 pressed for 5sec - RED LED is ON continously 
**/

#include "led.h"
#include "button.h"
#include "timer.h"

ui8_t button1;
ui8_t button2;

/* Button1 event handler after 1sec */
void test_app_button1_handler(void) {
    // Handle Button A press event
	button1 = button1_get_state();

    if (button1 == BUTTON_RELEASED) {
		set_led(GREEN, LED_ON, 1); /*Blink for 1sec*/
	}
	return;

}

void test_app_button2_handler(void) {
     // Handle Button A press event
	button2 = button2_get_state();

	if (button2 == BUTTON_RELEASED) {
		set_led(RED, LED_ON, 0);
	}
	return;
}


void test_app_main(void) {

	button1 = button1_get_state();
	if(button1 == BUTTON_PRESSED){
		const static timer_param_t test_1s_param = {
			100u,				/* cyclic counter, 1sec*/
			TIMER_SINGLE,		/* cyclic single*/
			TIMER_LOW,			/* Timer ID, LOW(10ms) or HIGH(1ms)*/
			&test_app_button1_handler
		};
		timer_create(&test_1s_param); /* assume that timer module will call the test_app_button1_handler every 1s*/
	}
	return;
}
void test_app_init(void) {

	const static timer_param_t test_app_param = {
		10u,				/* cyclic counter * Timer ID type, 100ms*/
		TIMER_CYCLIC,		/* cyclic single*/
		TIMER_LOW,			/* Timer ID type, LOW(10ms) or HIGH(1ms) depends on MCU*/
		&test_app_main
	};

	timer_create(&test_app_param); /* assume that timer module will call the test_app_main every 100ms*/

	// initialize button
	return;

}
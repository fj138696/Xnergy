// button.c

#include "button.h"
#include "gpio.h" 
#include "timer.h" 

ui8_t button1_state;
ui8_t button1_read; 

ui8_t button2_state;
ui8_t button2_read;

ui8_t button1_debounce_state;
ui8_t button2_debounce_state;

static void button1_set_port(void) {

	// Configure GPIO for buttons as input
	/* depending on MCU datasheet */
	GPIO0_REGISTER_OUT = BIT_DISABLE;
	GPIO0_REGISTER_IN = BIT_ENABLE;

	/* Interrupt Setting Registers GPIO Port 0 */
	/* depeding on MCU datasheet */
	/* Disable External Interrupt*/
	GPIO0_EXTERNAL_INTERRUPT_REGISTER_CONDITION = TRIGGER_FALLING_EDGE;
	/* Enable External Interrupt*/


	/* Input Capture Register for GPIO Port 0	*/
	/* depeding on MCU datasheet */
	GPIO0_SETTING_1 = ACTIVE_HIGH;				/* Active high setting */
	GPIO0_SETTING_2 = BOTH_EDGE_DETECT_ENABLE; 	/* Assume same interrupt for both edge detection */
	return;

}

static void button2_set_port(void) {
	// Configure GPIO for buttons as input
	/* depending on MCU datasheet */
	GPIO1_REGISTER_OUT = BIT_DISABLE;
	GPIO1_REGISTER_IN = BIT_ENABLE;

	/* Interrupt Setting Registers GPIO Port 0 */
	/* depeding on MCU datasheet */
	/* Disable External Interrupt*/
	GPIO1_EXTERNAL_INTERRUPT_REGISTER_CONDITION = TRIGGER_FALLING_EDGE;
	/* Enable External Interrupt*/


	/* Input Capture Register for GPIO Port 0	*/
	/* depeding on MCU datasheet */
	GPIO1_SETTING_1 = ACTIVE_HIGH; 					/* Active high setting */
	GPIO1_SETTING_2 = BOTH_EDGE_DETECT_ENABLE; 		/* Assume same interrupt for both edge detection */
	return;

}

void button1_interrupt_handler(void) {
	/* Assume same interrupt for both edge detection */
	if (button1_debounce_state == DEBOUNCE_END) {
		button1_debounce_state = DEBOUNCE_START;	/* Detected the START FALLING edge*/

	}
	else if (button1_debounce_state == DEBOUNCE_START) {
		button1_debounce_state = DEBOUNCE_END;		/* Detected the END RISING edge*/
	}
	return;

}

void button2_interrupt_handler(void) {
	/* Assume same interrupt for both edge detection */
	if (button2_debounce_state == DEBOUNCE_END) {
		button2_debounce_state = DEBOUNCE_START;	/* Detected the START FALLING edge*/

	}
	else if (button2_debounce_state == DEBOUNCE_START){
		button2_debounce_state = DEBOUNCE_END;		/* Detected the END RISING edge*/
	}
	return;

}

ui8_t button1_get_state(void){
	return 	button1_state;
}

ui8_t button2_get_state(void){
	return 	button2_state;
}



void button1_debounce(void) {
	if (button1_debounce_state == DEBOUNCE_START)
	{
		button1_read = (button1_read << 1) | GPIO0_READ_PIN(); /* Check button pressed for 40ms */

		if (button1_read == 0xffu) {
			button1_state = BUTTON_PRESSED;
		}
	}
	else if (button1_debounce_state == DEBOUNCE_END) {
		button1_state = BUTTON_RELEASED;
	}
	return;
}

void button2_debounce(void) {
	if (button2_debounce_state == DEBOUNCE_START)
	{
		button2_read = (button2_read << 1) | GPIO0_READ_PIN(); /* Check button pressed for 40ms */

		if (button2_read == 0xffu) {
			button2_state = BUTTON_PRESSED;
		}
	}
	else if (button2_debounce_state == DEBOUNCE_END) {
		button2_state = BUTTON_RELEASED;
	}
	return;

}

static void button_init(void){

	const static timer_param_t button1_debounce_param = {
		5u,					/* cyclic counter, 5ms*/
		TIMER_CYCLIC,		/* cyclic single*/
		TIMER_HIGH,			/* Timer ID, HIGH(1ms)*/
		& button1_debounce
	};

	timer_create(&button1_debounce_param); /* assume that timer will call the button_param every 5ms*/

	const static timer_param_t button2_debounce_param = {
	5u,					/* cyclic counter, 5ms*/
	TIMER_CYCLIC,		/* cyclic single*/
	TIMER_HIGH,			/* Timer ID, HIGH(1ms)*/
	&button1_debounce
	};

	timer_create(&button1_debounce_param); /* assume that timer will call the button_param every 5ms*/

	// call interrupt_disable();
	
	// initialize buttons
	button1_set_port();
	button2_set_port();
	
	// call interrupt_enable();
	
	gpio0_interrupt_set_handler(&button1_interrupt_handler);
	gpio1_interrupt_set_handler(&button2_interrupt_handler);

	button1_debounce_state = DEBOUNCE_END;
	button1_state = BUTTON_RELEASED;
	
	button2_debounce_state = DEBOUNCE_END; 
	button1_state = BUTTON_RELEASED;
	
	return;
}


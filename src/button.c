// button.c

#include "button.h"
#include "gpio.h" 
#include "timer.h" 

/* Explicit Buttons are declared for simplicity and less memory overhead*/
button_sts_t button1;
ui8_t last_button1_read;

button_sts_t button2;
ui8_t last_button2_read;

static void button1_set_port(void) {

	// Configure GPIO for buttons as input
	/* depending on MCU datasheet */
	GPIO0_REGISTER_OUT = BIT_DISABLE;
	GPIO0_REGISTER_IN = BIT_ENABLE;

	return;

}

static void button2_set_port(void) {
	// Configure GPIO for buttons as input
	/* depending on MCU datasheet */
	GPIO1_REGISTER_OUT = BIT_DISABLE;
	GPIO1_REGISTER_IN = BIT_ENABLE;

	/* Interrupt Setting Registers GPIO Port 0 */
	return;

}


ui8_t button1_get_state(void){
	return 	button1.state;
}

ui8_t button2_get_state(void){
	return 	button2.state;
}

// Function to handle level detection
void button_level_detector(ui8_t currentLevel, ui8_t *state, ui8_t stableState) {
	if (currentLevel == stableState) {
		*state = BUTTON_PRESSED;
	}
	else {
		*state = BUTTON_RELEASED;
	}
}

// Function to handle edge detection
void button_edge_detector(ui8_t currentLevel, ui8_t lastLevel, ui8_t* state, ui8_t risingEdgeState, ui8_t fallingEdgeState) {
	if (currentLevel == risingEdgeState 
		&& lastLevel == fallingEdgeState) {
		*state = BUTTON_PRESSED;	//DETECTED_RISING_EDGE
	}
	else if (currentLevel == fallingEdgeState 
			 && lastLevel == risingEdgeState) {
		*state = BUTTON_RELEASED;	//DETECTED_FALLING_EDGE
	}

}

void button1_debounce(void) {
	button1.read = (button1.read << 1) | GPIO0_READ_PIN(); // Check button state for 40ms

	if (button1.logic_level == ACTIVE_HIGH) {
		if (button1.edge_type == TRIGGER_LEVEL) {
			// Level detection for active-high configuration
			button_level_detector(button1.read, &button1.state, 0xFFu);
		}
		else if (button1.edge_type == TRIGGER_EDGE) {
			// Edge detection for active-high configuration
			button_edge_detector(button1.read, last_button1_read, &button1.state, 0xFFu, 0x00u);
		}

	}
	else if (button1.logic_level == ACTIVE_LOW) {
		if (button1.edge_type == TRIGGER_LEVEL) {
			// Level detection for active-high configuration
			button_level_detector(button1.read, &button1.state, 0x00u);
		}
		else if (button1.edge_type == TRIGGER_EDGE) {
			// Edge detection for active-high configuration
			button_edge_detector(button1.read, last_button1_read, &button1.state, 0x00u, 0xFFu);
		}
	}
	last_button1_read = button1.read;

	return;
}

void button2_debounce(void) {
	button2.read = (button2.read << 1) | GPIO1_READ_PIN(); // Check button state for 40ms

	if (button2.logic_level == ACTIVE_HIGH) {
		if (button2.edge_type == TRIGGER_LEVEL) {
			// Level detection for active-high configuration
			button_level_detector(button2.read, &button2.state, 0xFFu);
		}
		else if (button2.edge_type == TRIGGER_EDGE) {
			// Edge detection for active-high configuration
			button_edge_detector(button2.read, last_button2_read, &button2.state, 0xFFu, 0x00u);
		}

	}
	else if (button2.logic_level == ACTIVE_LOW) {
		if (button2.edge_type == TRIGGER_LEVEL) {
			// Level detection for active-high configuration
			button_level_detector(button2.read, &button2.state, 0x00u);
		}
		else if (button2.edge_type == TRIGGER_EDGE) {
			// Edge detection for active-high configuration
			button_edge_detector(button2.read, last_button2_read, &button2.state, 0x00u, 0xFFu);
		}
	}
	last_button2_read = button2.read;

	return;
}

/*cyclic handler for 5ms*/
void button_main(void) {

	button1_debounce();
	button2_debounce();
	return;

}
/* Assume this is called in the Main function */
static void button_init(void){

	const static timer_param_t button_param = {
		5u,					/* cyclic counter, 5ms*/
		TIMER_CYCLIC,		/* cyclic single*/
		TIMER_HIGH,			/* Timer ID, HIGH(1ms)*/
		&button_main
	};

	timer_create(&button_param); /* assume that timer will call the button_param every 5ms*/

	
	// initialize buttons
	button1.logic_level = ACTIVE_HIGH;
	button1.edge_type = TRIGGER_EDGE;
	button1.state = BUTTON_RELEASED;
	// call interrupt_disable();
	button1_set_port();
	// call interrupt_enable();

	button2.logic_level = ACTIVE_LOW;
	button2.edge_type = TRIGGER_LEVEL;
	button2.state = BUTTON_RELEASED;
	// call interrupt_disable();
	button2_set_port();
	// call interrupt_enable();

	
	return;
}


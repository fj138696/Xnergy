// led.c
#include "led.h"
#include "gpio.h"  /* Replace with the actual header for your microcontroller */
#include "timer.h" 

ui8_t led_green_state;
ui8_t led_green_blink_state;
ui8_t led_green_blink_interval;
ui8_t led_green_blink_ctr;


ui8_t led_red_state;
ui8_t led_red_blink_state;
ui8_t led_red_blink_interval;
ui8_t led_red_blink_ctr;


void led_green_set_port(void){
	
	// Configure GPIO for buttons as input
	/* depending on MCU datasheet */
    GPIO2_REGISTER_OUT = BIT_ENABLE;
    GPIO2_REGISTER_IN = BIT_DISABLE;
	return;

}


void led_red_set_port(void) {

	// Configure GPIO for buttons as input
	/* depending on MCU datasheet */
	GPIO3_REGISTER_OUT = BIT_ENABLE;
	GPIO3_REGISTER_IN = BIT_DISABLE;
	return;

}
void led_green(high_low on_off) {
	GPIO2_SET_PIN(on_off);
}

void led_red(high_low on_off) {
	GPIO3_SET_PIN(on_off);
}

void led_blink_handler(void) {
	if (led_green_state == LED_ON) {
		if (led_green_blink_ctr == 0) {
			if (led_green_state == LED_BLINK_ON) {
				led_green(LED_OFF);
				led_green_state = LED_BLINK_OFF;
			}
			else {
				led_green(LED_ON);
				led_green_state = LED_BLINK_ON;
			}
			led_green_blink_ctr = led_green_blink_interval; // restart counter
		}
		else {
			led_green_blink_ctr--;
		}
	}
	if (led_red_state == LED_ON) {
		if (led_red_blink_ctr == 0) {
			if (led_red_state == LED_BLINK_ON) {
				led_red(LED_OFF);
				led_red_state = LED_BLINK_OFF;
			}
			else {
				led_red(LED_ON);
				led_red_state = LED_BLINK_ON;
			}
			led_red_blink_ctr = led_red_blink_interval; // restart counter
		}
		else {
			led_red_blink_ctr--;
		}
	}

	return;
}



static void led_green_ope(led_state_t onoff_state, ui8_t interval){ // assume blink interval is in sec, if 0 constant ON

	if(onoff_state == LED_ON){
		led_green_state = LED_ON;
		if (interval > 0) {
			led_green_blink_interval = (interval * SEC_TO_MS) / 100u;
			led_green_state = LED_BLINK_ON;
			led_green_blink_ctr = interval;
		}
		led_green(LED_ON);
	}

	if (onoff_state == LED_OFF) {
		led_green_state = LED_OFF;
		led_green(LED_OFF);
	}
}

static void led_red_ope(led_state_t onoff_state, ui8_t interval) { // assume blink interval is in sec, if 0 constant ON

	if (onoff_state == LED_ON) {
		led_red_state = LED_ON;
		if (interval > 0) {
			led_red_blink_interval = (interval * SEC_TO_MS) / 100u;
			led_red_state = LED_BLINK_ON;
			led_red_blink_ctr = interval;
		}
		led_red(LED_ON);
	}

	if (onoff_state == LED_OFF) {
		led_red_state = LED_OFF;
		led_red(LED_OFF);
	}
}

void set_led(led_number_t led_number, led_state_t onoff_state, ui8_t interval)
{
	switch(led_number)
	{	case GREEN:
			led_green_ope(onoff_state, interval);
		case RED:
			led_red_ope(onoff_state, interval);
		default:
		break;
	}
	
	return;
}

void led_init(void){

	const static timer_param_t led_blink_param = {
		10u,				/* cyclic counter, 100ms*/
		TIMER_CYCLIC,		/* cyclic single*/
		TIMER_LOW,			/* Timer ID, HIGH(10ms)*/
		&led_blink_handler
	};
	
	timer_create(&led_blink_param); /* assume that timer 100ms*/
	
	led_green_set_port(); /* GREEN */
	led_red_set_port(); /* RED */
	
	return;
}


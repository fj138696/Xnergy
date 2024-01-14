// gpio.h

#ifndef GPIO_H
#define GPIO_H

#include "sys_type.h"

#define ACTIVE_HIGH				0x00u
#define ACTIVE_LOW				0x01u

#define TRIGGER_RISING_EDGE 	0x00u
#define TRIGGER_FALLING_EDGE 	0x01u
#define TRIGGER_HIGH_LVL 		0x02u
#define TRIGGER_LOW_LVL		 	0x03u

#define BOTH_EDGE_DETECT_DISABLE		0x00u 
#define BOTH_EDGE_DETECT_ENABLE			0x01u

ui8_t GPIO0_REGISTER_OUT;
ui8_t GPIO0_REGISTER_IN;
ui8_t GPIO0_EXTERNAL_INTERRUPT_REGISTER_CONDITION;
ui8_t GPIO0_SETTING_1;
ui8_t GPIO0_SETTING_2;

ui8_t GPIO1_REGISTER_OUT;
ui8_t GPIO1_REGISTER_IN;
ui8_t GPIO1_EXTERNAL_INTERRUPT_REGISTER_CONDITION;
ui8_t GPIO1_SETTING_1;
ui8_t GPIO1_SETTING_2;

ui8_t GPIO2_REGISTER_OUT;
ui8_t GPIO2_REGISTER_IN;
ui8_t GPIO2_EXTERNAL_INTERRUPT_REGISTER_CONDITION;
ui8_t GPIO2_SETTING_1;
ui8_t GPIO2_SETTING_2;

ui8_t GPIO3_REGISTER_OUT;
ui8_t GPIO3_REGISTER_IN;
ui8_t GPIO3_EXTERNAL_INTERRUPT_REGISTER_CONDITION;
ui8_t GPIO3_SETTING_1;
ui8_t GPIO3_SETTING_2;

typedef ui8_t high_low;

extern high_low GPIO0_READ_PIN(void);
extern void GPIO0_SET_PIN(high_low hl);


extern high_low GPIO1_READ_PIN(void);
extern void GPIO1_SET_PIN(high_low hl);


extern high_low GPIO2_READ_PIN(void);
extern void GPIO2_SET_PIN(high_low hl);
	 
extern high_low GPIO3_READ_PIN(void);
extern void GPIO3_SET_PIN(high_low hl);


extern void gpio0_interrupt_set_handler(funcp_t  int_handler);
extern void gpio1_interrupt_set_handler(funcp_t  int_handler);

#endif // GPIO_H



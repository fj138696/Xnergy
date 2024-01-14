// timer.h

#ifndef TIMER_H
#define TIMER_H

#include "sys_type.h"

typedef enum {
	TIMER_CYCLIC = 0,
	TIMER_SINGLE = 1
}timer_t;

typedef enum {
	TIMER_LOW = 0u,
	TIMER_HIGH
}timer_id_t;

typedef struct {
	ui8_t count;			/* cyclic counter, 1sec*/
	timer_t type;			/* cyclic single*/
	ui8_t id;				/* Timer ID, LOW(10ms) or HIGH(1ms)*/
	funcp_t  timer_handler;
}timer_param_t;

#define SEC_TO_MS 1000u
extern void timer_create(const timer_param_t *attr_paramater);

#endif // TIMER_H



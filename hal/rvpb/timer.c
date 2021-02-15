#include "stdint.h"
#include "timer.h"
#include "haltimer.h"
#include "halinterrupt.h"

extern volatile timer_t* timer;
static void interrupt_handler(void);
static uint32_t internal_1ms_counter;

void hal_timer_init(void)
{
	// timer interface reset
	timer->timerxcontrol.bits.timeren = 0;
	timer->timerxcontrol.bits.timermode = 0;
	timer->timerxcontrol.bits.oneshot = 0;
	timer->timerxcontrol.bits.timersize = 0;
	timer->timerxcontrol.bits.timerpre = 0;
	timer->timerxcontrol.bits.intenable = 1;
	timer->timerxload = 0;
	timer->timerxvalue = 0xFFFFFFFF;
	
	// set periodic mode
	timer->timerxcontrol.bits.timermode = TIMER_PERIODIC;
	timer->timerxcontrol.bits.timersize = TIMER_32BIT_COUNTER;
	timer->timerxcontrol.bits.oneshot = 0;
	timer->timerxcontrol.bits.timerpre = 0;
	timer->timerxcontrol.bits.intenable = 1;

	uint32_t interval = TIMER_10HZ_INTERVAL / 100;

	timer->timerxload = interval;
	timer->timerxcontrol.bits.timeren = 1;

	internal_1ms_counter = 0;

	// register timer interrupt handler
	hal_interrupt_enable(TIMER_INTERRUPT);
	hal_interrupt_register_handler(interrupt_handler, TIMER_INTERRUPT);

}

uint32_t hal_timer_get_1ms_counter(void)
{
	return internal_1ms_counter;
}

static void interrupt_handler(void)
{
	internal_1ms_counter++;
	timer->timerxintclr = 1;
}



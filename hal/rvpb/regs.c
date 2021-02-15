#include "stdint.h"
#include "uart.h"
#include "interrupt.h"
#include "timer.h"

volatile PL011_t*	uart = (PL011_t *)UART_BASE_ADDRESS0;
volatile giccput_t* giccpu = (giccput_t *)GIC_CPU_BASE;
volatile gicdist_t* gicdist = (gicdist_t *)GIC_DIST_BASE;
volatile timer_t* timer = (timer_t *)TIMER_CPU_BASE;

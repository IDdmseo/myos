#include "stdint.h"
#include "stdbool.h"
#include "haluart.h"
#include "halinterrupt.h"
#include "haltimer.h"
#include "stdio.h"
#include "stdlib.h"

static void hw_init(void);
static void printf_test(void);
static void timer_test(void);

void main(void)
{
	hw_init();
	
	printf_test();
	timer_test();

	while(true);
}

static void hw_init(void)
{
	hal_interrupt_init();
	hal_uart_init();
	hal_timer_init();
}

static void printf_test(void)
{
	char* str = "printf pointer test";
	char* nullptr = 0;
	uint32_t i = 5;
	uint32_t* sysctrl0 = (uint32_t *)0x10001000;

	dprintf("%s\n", "hello printf");
	dprintf("ouput string pointer: %s\n", str);
	dprintf("%s is null pointer, %u number\n", nullptr, 10);
	dprintf("%u = 5\n", i);
	dprintf("dec=%u hex=%x\n", 0xff, 0xff);
	dprintf("SYSCTRL0 %x\n", *sysctrl0);
}

static void timer_test(void)
{
	while(true){
		dprintf("current count: %u\n", hal_timer_get_1ms_counter());
	}

}


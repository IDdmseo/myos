#include "stdint.h"
#include "stdbool.h"
#include "haluart.h"
#include "halinterrupt.h"
#include "haltimer.h"
#include "stdio.h"
#include "stdlib.h"
#include "kernel.h"

static void hw_init(void);
static void printf_test(void);
static void timer_test(void);
static void kernel_init(void);

void user_task0(void);
void user_task1(void);
void user_task2(void);

void main(void)
{
	hw_init();
	printf_test();
//	timer_test();
	kernel_init();

	while(true);
}

static void hw_init(void)
{
	hal_interrupt_init();
	hal_uart_init();
	hal_timer_init();
}

static void kernel_init(void)
{
	uint32_t taskid;

	kernel_task_init();

	taskid = kernel_task_create(user_task0);
	if(taskid == NOT_ENOUGH_TASK_NUM) {
		putstr("task0 creation fail\n");
	}

	taskid = kernel_task_create(user_task1);
	if(taskid == NOT_ENOUGH_TASK_NUM) {
		putstr("task1 creation fail\n");
	}

	taskid = kernel_task_create(user_task2);
	if(taskid == NOT_ENOUGH_TASK_NUM) {
		putstr("task2 creation fail\n");
	}

	kernel_start();
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
		dprintf("current count: %u\n", hal_timer_get_1ms_counter() / 1000);
		delay(1000);
	}

}

void user_task0(void)
{
	uint32_t local = 0;
	while(true){
		dprintf("user_task0 sp = 0x%x\n", &local);
		delay(1000);
		kernel_yield();
	}
}

void user_task1(void)
{
	uint32_t local = 0;
	while(true) {
		dprintf("user_task1 sp = 0x%x\n", &local);
		delay(1000);
		kernel_yield();
	}
}

void user_task2(void)
{
	uint32_t local = 0;
	while(true) {
		dprintf("user_task2 sp = 0x%x\n", &local);
		delay(1000);
		kernel_yield();
	}
}


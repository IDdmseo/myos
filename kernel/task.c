#include "stdint.h"
#include "stdbool.h"

#include "ARMv7AR.h"
#include "task.h"

/*
 * set these variables to avoid dynamic allocation for each tasks in kernel.
 * each task stack size = 1MB
 * 
 */

static kerneltcb_t sfree_task_pool[MAX_TASK_NUM];
static uint32_t sallocated_tcb_index;

void kernel_task_init(void)
{
	sllocated_tcb_index = 0;

	for(uint32_t i = 0; i < MAX_TASK_NUM; i++) {
		sfree_task_pool[i].spsr = ARM_MODE_BIT_SYS;
		sfree_task_pool[i].lr = 0;
		sfree_task_pool[i].pc = 0;

		sfree_task_pool[i].stack_base = (uint8_t *)(TASK_STACK_START + (i*USR_TASK_STACK_SIZE));
		sfree_task_pool[i].sp = (uint32_t)sfree_task_pool[i].stack_base + USR_TASK_STACK_SIZE - 4;
	}
}

uint32_t kernel_task_create(kerneltaskfunc_t startfunc)
{
	kerneltcb_t* new_tcb = &sfree_task_pool[sallocated_tcb_index++];

	if(sallocated_tcb_index > MAX_TASK_NUM) {
		return NOT_ENOUGH_TASK_NUM;
	}

	new_tcb->pc = (uint32_t)startfunc;

	return (sallocated_tcb_index - 1);
}


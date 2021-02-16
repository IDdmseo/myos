#ifndef KERNEL_TASK_H_
#define KERNEL_TASK_H_

#include "mmap.h"

#define NOT_ENOUGH_TASK_NUM	0xFFFFFFFF
#define USR_TASK_STACK_SIZE	0x100000

typedef struct kerneltaskcontext_t {
	uint32_t spsr;			// program status register
	uint32_t reg[13];		// r0 - r12 for GPR
	uint32_t sp;			// stack register (r13)
	uint32_t lr;			// link register (r14)
	uint32_t pc;			// program counter (r15)
	
	uint8_t* stack_base;	// meta-data for task
} kerneltcb_t;

typedef void (*kerneltaskfunc_t)(void);

void kernel_task_init(void);
uint32_t kernel_task_create(kerneltaskfunc_t startfunc);

#endif

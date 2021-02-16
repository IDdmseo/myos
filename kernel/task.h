#ifndef KERNEL_TASK_H_
#define KERNEL_TASK_H_

#include "mmap.h"

#define NOT_ENOUGH_TASK_NUM	0xFFFFFFFF
#define USR_TASK_STACK_SIZE	0x100000

#define MAX_TASK_NUM		(TASK_STACK_SIZE	/	USR_TASK_STACK_SIZE)

typedef struct kerneltaskcontext_t {
	uint32_t spsr;			// program status register
	uint32_t reg[13];		// r0 - r12 for GPR
	uint32_t pc;			// program counter (r15)
	
} kerneltaskcontext_t;

typedef struct kerneltcb_t {
	uint32_t sp;
	uint8_t* stack_base;
} kerneltcb_t;

static kerneltcb_t	stask_list[MAX_TASK_NUM];
static kerneltcb_t* scurrent_tcb;
static kerneltcb_t* snext_tcb;
static uint32_t		sallocated_tcb_index;
static uint32_t		scurrent_tcb_index;

typedef void (*kerneltaskfunc_t)(void);
uint32_t kernel_task_create(kerneltaskfunc_t startfunc);

void kernel_task_init(void);
void kernel_task_start(void);
void kernel_task_scheduler(void);
void kernel_task_context_switch(void);

static void save_context(void);
static void restore_context(void);
static kerneltcb_t* rr_scheduler(void);

#endif

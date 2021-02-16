#include "stdint.h"
#include "stdbool.h"

#include "ARMv7AR.h"
#include "task.h"

void kernel_task_init(void)
{
	sallocated_tcb_index = 0;
	scurrent_tcb_index = 0;

	for(uint32_t i = 0; i < MAX_TASK_NUM; i++) {
		stask_list[i].stack_base = (uint8_t *)(TASK_STACK_START + (i*USR_TASK_STACK_SIZE));
		stask_list[i].sp = (uint32_t)stask_list[i].stack_base + USR_TASK_STACK_SIZE - 4;

		stask_list[i].sp -= sizeof(kerneltaskcontext_t);
		kerneltaskcontext_t* ctx = (kerneltaskcontext_t *)stask_list[i].sp;
		ctx->pc = 0;
		ctx->spsr = ARM_MODE_BIT_SYS;
	}

}

void kernel_task_start(void)
{
	snext_tcb = &stask_list[scurrent_tcb_index];
	restore_context();
}

uint32_t kernel_task_create(kerneltaskfunc_t startfunc)
{
	kerneltcb_t* new_tcb = &stask_list[sallocated_tcb_index++];

	if(sallocated_tcb_index > MAX_TASK_NUM) {
		return NOT_ENOUGH_TASK_NUM;
	}

	kerneltaskcontext_t* ctx = (kerneltaskcontext_t *)new_tcb->sp;
	ctx->pc = (uint32_t)startfunc;

	return (sallocated_tcb_index - 1);

}

static kerneltcb_t* rr_scheduler(void)
{
	scurrent_tcb_index++;
	scurrent_tcb_index %= sallocated_tcb_index;

	return &stask_list[scurrent_tcb_index];

}

void kernel_task_scheduler(void)
{
	scurrent_tcb = &stask_list[scurrent_tcb_index];
	snext_tcb = rr_scheduler();

	kernel_task_context_switch();

}

__attribute__ ((naked)) void kernel_task_context_switch(void)
{
	__asm__ ("B save_context");
	__asm__ ("B restore_context");

}

static __attribute__ ((naked)) void save_context(void)
{
	// save current task context(lr, cpsr, GPR) into the current task stack
	__asm__ ("push	{lr}");
	__asm__ ("push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
	__asm__ ("mrs	r0, cpsr");
	__asm__ ("push  {r0}");

	// save current task stack pointer into the current tcb
	__asm__ ("ldr	r0, =scurrent_tcb");
	__asm__ ("ldr	r0, [r0]");
	__asm__ ("stmia	r0!, {sp}");

}

static __attribute__ ((naked)) void restore_context(void)
{
	// restore next task stack pointer from the next tcb
	__asm__ ("ldr	r0, =snext_tcb");
	__asm__ ("ldr	r0, [r0]");
	__asm__ ("ldmia	r0!, {sp}");
	// restore next task context from the next task stack
	__asm__ ("pop	{r0}");
	__asm__ ("msr	cpsr, r0");
	__asm__ ("pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
	__asm__ ("pop {pc}");

}

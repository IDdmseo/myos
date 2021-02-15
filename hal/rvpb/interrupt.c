#include "stdint.h"
#include "memio.h"
#include "interrupt.h"
#include "halinterrupt.h"
#include "armcpu.h"

extern volatile giccput_t* giccpu;
extern volatile gicdist_t* gicdist;

static interhdlr_fptr shandler[INTERRUPT_HANDLER_NUM];

void hal_interrupt_init(void)
{
	giccpu->cpucontrol.bits.enable = 1;
	giccpu->prioritymask.bits.prioritymask = GIC_PRIORITY_MASK_NONE;
	gicdist->distributorctrl.bits.enable = 1;

	for (uint32_t i = 0; i < INTERRUPT_HANDLER_NUM; i++) shandler[i] = NULL;

	enable_irq();
}

void hal_interrupt_enable(uint32_t interrupt_num)
{
	if ((interrupt_num < GIC_IRQ_START) || (GIC_IRQ_END < interrupt_num)) return;

	uint32_t bit_num = interrupt_num - GIC_IRQ_START;

	if (bit_num < GIC_IRQ_START) SET_BIT(gicdist->setenable1, bit_num);
	else {
		bit_num -= GIC_IRQ_START;
		SET_BIT(gicdist->setenable2, bit_num);
	}

}

void hal_interrupt_disable(uint32_t interrupt_num)
{
	if ((interrupt_num < GIC_IRQ_START) || (GIC_IRQ_END < interrupt_num)) return;

	uint32_t bit_num = interrupt_num - GIC_IRQ_START;
	
	if (bit_num < GIC_IRQ_START) CLR_BIT(gicdist->setenable1, bit_num);
	else {
		bit_num -= GIC_IRQ_START;
		CLR_BIT(gicdist->setenable2, bit_num);
	}

}

void hal_interrupt_register_handler(interhdlr_fptr handler, uint32_t interrupt_num)
{
	shandler[interrupt_num] = handler;
}

void hal_interrupt_run_handler(void)
{
	uint32_t interrupt_num = giccpu->interruptack.bits.interruptid;

	if (shandler[interrupt_num] != NULL) shandler[interrupt_num]();

	giccpu->endofinterrupt.bits.interruptid = interrupt_num;
}


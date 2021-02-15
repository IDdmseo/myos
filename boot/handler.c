#include "stdbool.h"
#include "stdint.h"
#include "halinterrupt.h"

 __attribute__ ((interrupt ("IRQ"))) void irq_Handler(void)
{
    hal_interrupt_run_handler();
}

 __attribute__ ((interrupt ("FIQ"))) void fiq_Handler(void)
{
    while(true);
}
